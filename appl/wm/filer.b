implement WmDir;

include "sys.m";
	sys: Sys;
	Dir: import sys;

include "draw.m";
	draw: Draw;
	ctxt: ref Draw->Context;
	Font, Rect: import draw;

include "tk.m";
	tk: Tk;
	Toplevel: import tk;

include "tkclient.m";
	tkclient: Tkclient;

include "dialog.m";
	dialog: Dialog;

include "readdir.m";
	readdir: Readdir;

include "daytime.m";
	daytime: Daytime;

include "plumbmsg.m";
	plumbmsg: Plumbmsg;
	Msg: import plumbmsg;

include "env.m";

include "arrays.m";
	arrays: Arrays;

include "string.m";
	strings: String;

include "sh.m";

include "newns.m";

Fontwidth: 	int;
font:		string;
IconColW:	con 96;	# icon column: wide enough for ~12-char names without wrap
MINCOL:		con 2;	# minimum icon columns even on a narrow window

WmDir: module
{
	init:	fn(ctxt: ref Draw->Context, argv: list of string);
};

Wm: module
{
	init:	fn(ctxt: ref Draw->Context, argv: list of string);
};

Ft: adt
{
	ext:	string;
	cmd:	string;
	tkname:	string;
	icon:	string;
	loaded:	int;
	givearg:	int;
};

dirwin_cfg := array[] of {
	# Lay out the screen
	"frame .fc",
	"scrollbar .fc.scroll -command {.fc.c yview}",

	"canvas .fc.c -relief sunken -yscrollincrement 25"+
		" -borderwidth 2 -width 10c -height 300"+
		" -yscrollcommand {.fc.scroll set} $font",

	"frame .mbar",
	"menubutton .mbar.opt -text {Options} -menu .opt",
	".mbar configure $font",
	".mbar.opt configure $font",
	"pack .mbar.opt -side left",
	"pack .fc.scroll -side left -fill y",
	"pack .fc.c -fill both -expand 1",
	"pack .mbar -fill x",
	"pack .fc -fill both -expand 1",
	"pack propagate . 0",

	# prepare cursor
	"image create bitmap waiting -file cursor.wait",

	# Build the options menu
	"menu .opt",
	".opt configure $font",
	".opt add radiobutton -text {by name}"+
		" -variable sort -value n -command {send opt sort}",
	".opt add radiobutton -text {by access}"+
		" -variable sort -value a -command {send opt sort}",
	".opt add radiobutton -text {by modify}"+
		" -variable sort -value m -command {send opt sort}",
	".opt add radiobutton -text {by size}"+
		" -variable sort -value s -command {send opt sort}",
	".opt add separator",
	".opt add radiobutton -text {use icons}"+
		" -variable show -value i -command {send opt icon}",
	".opt add radiobutton -text {use text}"
		+" -variable show -value t -command {send opt text}",
	".opt add separator",
	".opt add radiobutton -text {hide dotfiles}"
		+" -variable hide -value h -command {send opt hidedot}",
	".opt add radiobutton -text {show dotfiles}"
		+" -variable hide -value s -command {send opt showdot}",
	".opt add separator",
	".opt add checkbutton -text {Walk} -command {send opt walk}",
};

FilerWin: adt
{
	t: ref Toplevel;
	wmctl: chan of string;
	filecmd: chan of string;
	conf: chan of string;
	opt: chan of string;
	
	key: int;
	walk: int;
	path: string;
	usetext: int;
	nde: int;
	now: int;
	de: array of ref Sys->Dir;
	hide: int;

	dragging: int;
	dragitem: ref Sys->Dir;

	appicons: list of (string, string);	# (approot, registered tk image name)
	curwidth: int;				# last-known toplevel width (from %w on <Configure>)
};

cmdname: string;
sysnam: string;
plumbed := 0;

# Floating "ghost" toplevel shared across all filer windows: a tiny
# borderless Tk toplevel that shows the dragged item's icon and is
# reshaped to follow the cursor while a drag is in progress. Created
# lazily on the first drag.
GhostMargin: con 4;             # px around the icon inside the ghost
dragghost: ref Toplevel;
dragghosticonpath: string;     # last-shown .bit path; "" = nothing set yet
dragghostvisible: int;

winlock: chan of int;
windows: list of ref FilerWin;

filetypes: array of ref Ft;
deftype: ref Ft;
dirtype: ref Ft;

inittypes()
{
	deftype = ref Ft("", "/dis/wm/edit.dis", "WmDir_Dis", "file", 0, 1);
	dirtype = ref Ft("", nil, "WmDir_Dir", "dir", 0, 1);
	filetypes = array[] of {
		ref Ft("dis", nil, "WmDis_Pic", "dis", 0, 0),
		ref Ft("bit", "/dis/wm/view.dis", "WmDir_Pic", "pic", 0, 1),
		ref Ft("gif", "/dis/wm/view.dis", "WmDir_Pic", "pic", 0, 1),
		ref Ft("jpg", "/dis/wm/view.dis", "WmDir_Pic", "pic", 0, 1),
		ref Ft("jpeg", "/dis/wm/view.dis", "WmDir_Pic", "pic", 0, 1),
		ref Ft("mask", "/dis/wm/view.dis", "WmDir_Pic", "pic", 0, 1),
	};
}

init(env: ref Draw->Context, argv: list of string)
{
	ctxt = env;

	sys  = load Sys Sys->PATH;
	if (ctxt == nil) {
		sys->fprint(sys->fildes(2), "dir: no window context\n");
		raise "fail:bad context";
	}
	# Run in our own pgrp like wm/edit and the other wm apps do.
	# Without this we share wm/wm's pgrp via sh's '&' (runasync only
	# does FORKFD), and the wm's per-client cleanup path may not see
	# us fully gone until our pgrp dies. With our own pgrp, when the
	# last window_loop thread exits, the pgrp collapses and the wm
	# observes the /chan/wmctl disconnect immediately.
	sys->pctl(Sys->NEWPGRP, nil);
	draw = load Draw Draw->PATH;
	tk   = load Tk Tk->PATH;
	tkclient = load Tkclient Tkclient->PATH;
	dialog = load Dialog Dialog->PATH;
	readdir = load Readdir Readdir->PATH;
	plumbmsg = load Plumbmsg Plumbmsg->PATH;
	if(plumbmsg != nil && plumbmsg->init(1, nil, 0) >= 0)
		plumbed = 1;
	environ := load Env Env->PATH;
	arrays = load Arrays Arrays->PATH;
	strings = load String String->PATH;

	font = environ->getenv("font");
	if(font == nil)
		font = "/fonts/pelm/unicode.8.font";

	# Graceful guards?
	Fontwidth = Font.open(ctxt.display, font).width(" ");

	font = " -font " + font + " ";

	tkclient->init();
	dialog->init();
	inittypes();

	cmdname = hd argv;
	sysnam = sysname()+":";

	winlock = chan[1] of int;
	winlock <-= 1;
	create_window(argv);
}

create_window(argv: list of string)
{
	(t, wmctl) := tkclient->toplevel(ctxt, "", "", Tkclient->Appl);

	w := ref FilerWin;
	w.t = t;
	w.wmctl = wmctl;
	w.filecmd = chan of string;
	# Buffered so Tk's <Configure> sends during a drag don't block,
	# letting the conf-handler drain to the most recent width.
	w.conf = chan[32] of string;
	w.opt = chan of string;
	w.key = readdir->NAME;
	w.walk = 0;
	w.usetext = 0;
	w.nde = 0;
	w.now = 0;
	w.path = "";
	w.dragging = 0;
	w.hide = 1;

	tk->cmd(t, "cursor -image waiting");

	# Initialize images unconditionally for this specific window
	s0 := sys->sprint("image create bitmap %s -file %s.bit -maskfile %s.mask", deftype.tkname, deftype.icon, deftype.icon);
	tk->cmd(t, s0);
	s1 := sys->sprint("image create bitmap %s -file %s.bit -maskfile %s.mask", dirtype.tkname, dirtype.icon, dirtype.icon);
	tk->cmd(t, s1);
	# Default icon for !App folders that ship no icon of their own.
	tk->cmd(t, "image create bitmap WmDir_AppDef -file bomb.bit -maskfile bomb.mask");
	for (i := 0; i < len filetypes; i++) {
		s := sys->sprint("image create bitmap %s -file %s.bit -maskfile %s.mask", filetypes[i].tkname, filetypes[i].icon, filetypes[i].icon);
		tk->cmd(t, s);
	}

	tk->namechan(t, w.filecmd, "fc");
	tk->namechan(t, w.conf, "cf");
	tk->namechan(t, w.opt, "opt");

	argv = tl argv;
	if(argv == nil)
		getdir(w, "");
	else
		getdir(w, hd argv);

	# Patch in font (need a replaceall?)
	dirwin_cfg = arrays->map(dirwin_cfg, fontify);

	for (c:=0; c<len dirwin_cfg; c++)
		tk->cmd(t, dirwin_cfg[c]);
	tk->cmd(t, "bind .fc.c <ButtonRelease-1> {send fc R %X %Y}");
	# Canvas-wide motion fires even when the cursor leaves the items
	# (grab keeps focus on .fc.c). We use it to drag the floating
	# ghost across the whole screen.
	tk->cmd(t, "bind .fc.c <Motion-Button-1> {send fc M %X %Y}");
	# Bind Configure on the canvas only -- its %w is the canvas's own
	# width, which is exactly what drawdirico needs (the scrollbar is
	# a sibling, not inside the canvas).
	tk->cmd(t, "bind .fc.c <Configure> {send cf %w}");
	tkclient->onscreen(t, nil);
	tkclient->startinput(t, "kbd"::"ptr"::nil);
	# Geometry settled; seed curwidth from the canvas actwidth, then draw.
	tk->cmd(t, "update");
	w.curwidth = int tk->cmd(t, ".fc.c cget -actwidth");
	drawdir(w);
	tk->cmd(t, "update; cursor -default");

	<-winlock;
	windows = w :: windows;
	winlock <-= 1;

	spawn window_loop(w);
}

# Tear down a single window without disturbing its siblings. We can't use
# tkclient->wmctl's "exit" (it does killgrp, which would kill every filer
# window in our shared pgrp), so we dismantle this one window by hand:
#
#  1. ". unmap" releases the toplevel's on-screen image on the filer side.
#     This is the same primitive minimize uses (tkclient.b: ". unmap").
#     It's needed because the wm's Client.remove() only unlinks the client
#     from the z-order -- it does NOT free the window image, and the image
#     is referenced from BOTH sides (the wm's Client.wins and our tk
#     Toplevel). Dropping just the wm side (by closing the connection) left
#     the window drawn because tk still held the image; unmapping drops our
#     side so the pixels actually go away.
#
#  2. Overwriting connfd with /dev/null clunks this window's /chan/wmctl
#     fid so wmsrv sees this one client disconnect and removes its Client
#     (the same trick launch_app uses on inherited wmctl fds). Merely
#     nil-ing the Limbo reference wasn't enough -- a lingering reference
#     keeps the FD object alive, so the fid never clunks on its own.
#
# Without this, a closed child window lingered visible-but-dead until the
# last window closed and the whole pgrp died, taking every window with it.
close_window(w: ref FilerWin)
{
	t := w.t;
	if (t == nil)
		return;
	tk->cmd(t, ". unmap; update");
	if (t.ctxt != nil && t.ctxt.connfd != nil) {
		nfd := sys->open("/dev/null", Sys->ORDWR);
		if (nfd != nil)
			sys->dup(nfd.fd, t.ctxt.connfd.fd);
		t.ctxt.connfd = nil;
	}
}

remove_window(w: ref FilerWin)
{
	<-winlock;
	nwindows: list of ref FilerWin = nil;
	for (l := windows; l != nil; l = tl l) {
		if (hd l != w)
			nwindows = (hd l) :: nwindows;
	}
	windows = nwindows;
	winlock <-= 1;
	if (windows == nil)
		exit;
}

window_loop(w: ref FilerWin)
{
	t := w.t;
	menu := "";

f:	for(;;) alt {
	s := <-t.ctxt.kbd =>
		tk->keyboard(t, s);
	s := <-t.ctxt.ptr =>
		tk->pointer(t, *s);
	s := <-t.ctxt.ctl or
	s = <-t.wreq or
	s = <-w.wmctl =>
		if (s == "exit") {
			close_window(w);
			remove_window(w);
			exit;
		}
		tkclient->wmctl(t, s);
		# WM-driven reshape: tkclient updates top.screenr but
		# the <Configure> binding doesn't always fire, so redraw
		# explicitly whenever we see a "rect" wmctl.
		(nil, toks) := sys->tokenize(s, " \t\n");
		if(toks != nil && hd toks == "rect") {
			tk->cmd(t, "update");
			tk->cmd(t, ".fc.c delete all");
			drawdir(w);
			tk->cmd(t, "update");
		}
	cs := <-w.conf =>
		# %w from <Configure>: canvas width. A drag fires many
		# events; drain the (buffered) queue, then force an update
		# and read the canvas's CURRENT actwidth -- which may be
		# fresher than even the latest queued %w.
	drain:
		for(;;) alt {
		next := <-w.conf =>
			cs = next;
		* =>
			break drain;
		}
		tk->cmd(t, "update");
		actw := int tk->cmd(t, ".fc.c cget -actwidth");
		if(actw > 0)
			w.curwidth = actw;
		else {
			nw := int cs;
			if(nw > 0)
				w.curwidth = nw;
		}
		tk->cmd(t, ".fc.c delete all");
		drawdir(w);
		tk->cmd(t, ".fc.c yview moveto 0; update");
	mopt := <-w.opt =>
		case mopt {
		"refresh" =>
			getdir(w, w.path);
			# fallthrough to UI update
		"sort" =>
			case tk->cmd(t, "variable sort") {
			"n" => w.key = readdir->NAME;
			"a" => w.key = readdir->ATIME;
			"m" => w.key = readdir->MTIME;
			"s" => w.key = readdir->SIZE;
			}
			(w.de, w.nde) = readdir->sortdir(w.de, w.key);
		"walk" =>
			w.walk = !w.walk;
			continue f;
		"text" =>
			w.usetext = 1;
		"icon" =>
			w.usetext = 0;
		"showdot" =>
			w.hide = 0;
		"hidedot" =>
			w.hide = 1;
		}
		tk->cmd(t, ".fc.c delete all");
		drawdir(w);
		tk->cmd(t, ".fc.c yview moveto 0; update");
	action := <-w.filecmd =>
		case action[0] {
		'R' =>
			if (w.dragging) {
				w.dragging = 0;
				tk->cmd(t, "grab release .fc.c; cursor -default");
				hide_ghost();
				(nil, toks) := sys->tokenize(action, " ");
				if (len toks >= 3) {
					x := int hd tl toks;
					y := int hd tl tl toks;
					resolve_drop(w, w.dragitem, x, y);
				}
			}
			continue f;
		'M' =>
			# Canvas-wide motion: move the ghost so the user sees
			# the icon following the cursor even when outside the
			# filer window.
			if (w.dragging) {
				(nil, toks) := sys->tokenize(action, " ");
				if (len toks >= 3) {
					x := int hd tl toks;
					y := int hd tl tl toks;
					show_ghost(x, y);
				}
			}
			continue f;
		}

		nd := int action[1:];
		if(nd > len w.de)
			break;
		case action[0] {
		'1' =>
			button1(w, w.de[nd], 0);
		'2' =>
			button1(w, w.de[nd], 1);
		'3' =>
			button3(w, w.de[nd]);
		'm' =>
			if (!w.dragging) {
				w.dragging = 1;
				w.dragitem = w.de[nd];
				tk->cmd(t, "grab set .fc.c; cursor -bitmap cursor.drag");
				# Configure the floating ghost so the first
				# canvas-wide motion event makes it visible.
				set_ghost_icon(w, w.dragitem);
			}
		}
	}
}

getdir(w: ref FilerWin, dir: string)
{
	t := w.t;
	if(dir == "")
		dir = "/";

	w.path = dir;
	if (w.path[len w.path - 1] != '/')
		w.path[len w.path] = '/';

	(w.de, w.nde) = readdir->init(w.path, w.key);
	if(w.nde < 0) {
		dialog->prompt(ctxt, t.image, "error -fg red",
				"Read directory",
				sys->sprint("Error reading \"%s\"\n%r", w.path),
				0, "Exit"::nil);
		remove_window(w);
		exit;
	}

	if(w.path != "/") {
		(ok, d) := sys->stat("..");
		if(ok >= 0) {
			dot := array[w.nde+1] of ref Dir;
			dot[0] = ref d;
			dot[0].name = "..";
			dot[1:] = w.de;
			w.de = dot;
			w.nde++;
		}
	}

	for(i := 0; i < w.nde; i++) {
		s := w.de[i].name;
		l := len s;
		if(l > 4 && s[l-4:] == ".dis")
			w.de[i].mode |= 8r111;
	}
	tkclient->settitle(t, sysnam+w.path);
}

defcursor(t: ref Toplevel)
{
	tk->cmd(t, "cursor -default");
}

# asfolder != 0 opens an !App folder in the filer instead of launching it
# (middle-button double-click), mirroring Shift+double-click on RISC OS.
button1(w: ref FilerWin, item: ref Dir, asfolder: int)
{
	t := w.t;
	mod: Wm;

	tk->cmd(t, "cursor -image waiting");
	npath := w.path;
	name := item.name + "/";
	if(item.name == "..") {
		i := len w.path - 2;
		while(i > 0 && w.path[i] != '/')
			i--;
		npath = w.path[0:i];
		name = "/";
	}

	exec := npath+name[0:len name-1];
	ft := filetype(t, item, exec);

	if(item.mode & Sys->DMDIR) {
		if(!asfolder && isapp(exec)) {
			defcursor(t);
			spawn launch_app(exec);
			return;
		}
		if(w.walk != 0) {
			w.path = npath;
			getdir(w, npath+name);
			tk->cmd(t, ".fc.c delete all");
			drawdir(w);
			tk->cmd(t, ".fc.c yview moveto 0; update");
			defcursor(t);
			return;
		}
		defcursor(t);
		create_window(cmdname :: npath+name :: nil);
		return;
	}

	button3(w, item);
	return;
}

applinit(mod: Wm, ctxt: ref Draw->Context, args: list of string)
{
	sys->pctl(sys->NEWPGRP|sys->FORKFD, nil);
	spawn mod->init(ctxt, args);
}

# basename component of a path, ignoring a trailing '/'
basename(path: string): string
{
	if(path != nil && path[len path-1] == '/')
		path = path[0:len path-1];
	for(i := len path-1; i >= 0; i--)
		if(path[i] == '/')
			return path[i+1:];
	return path;
}

# A RISC OS-style app folder: name begins with '!' and contains a '!Boot' file.
isapp(path: string): int
{
	if(path == nil)
		return 0;
	base := basename(path);
	if(base == nil || base[0] != '!')
		return 0;
	if(path[len path-1] == '/')
		path = path[0:len path-1];
	(ok, nil) := sys->stat(path + "/!Boot");
	return ok >= 0;
}

# Register (once per window) the app's own icon from <approot>/icons/<name>.bit.
# Returns the tk image name, or the shared WmDir_AppDef (bomb) icon when the
# app ships no icon of its own.
app_icon(w: ref FilerWin, approot: string): string
{
	if(approot[len approot-1] == '/')
		approot = approot[0:len approot-1];
	for(l := w.appicons; l != nil; l = tl l) {
		(p, tkname) := hd l;
		if(p == approot)
			return tkname;
	}
	iconbase := approot + "/icons/" + basename(approot);
	(ok, nil) := sys->stat(iconbase + ".bit");
	if(ok < 0)
		return "WmDir_AppDef";
	name := sys->sprint("WmDir_App_%d", len w.appicons);
	# '@' tells tk to use the path verbatim instead of prefixing /icons/tk/.
	tk->cmd(w.t, sys->sprint("image create bitmap %s -file @%s.bit -maskfile @%s.mask",
		name, iconbase, iconbase));
	w.appicons = (approot, name) :: w.appicons;
	return name;
}

# Resolve the file paths for the .bit / .mask pair to use as the drag
# ghost's image. The bitpath is given in tk's "image create bitmap"
# syntax — relative names live in /icons/tk/, absolute paths use the
# '@' prefix so tk uses them verbatim. The .mask may not exist for
# every shipped icon; callers fall back gracefully when it doesn't.
ghost_icon_paths(w: ref FilerWin, item: ref Dir): (string, string)
{
	fullpath := w.path + item.name;
	if((item.mode & Sys->DMDIR) && isapp(fullpath)) {
		base := fullpath;
		if(base[len base-1] == '/')
			base = base[0:len base-1];
		iconbase := base + "/icons/" + basename(base);
		(ok, nil) := sys->stat(iconbase + ".bit");
		if(ok >= 0)
			return ("@"+iconbase+".bit", "@"+iconbase+".mask");
		return ("bomb.bit", "bomb.mask");	# !App with no icon
	}
	if(item.mode & Sys->DMDIR)
		return ("dir.bit", "dir.mask");
	suffix := "";
	name := item.name;
	for(j := len name-2; j >= 0; j--) {
		if(name[j] == '.') {
			suffix = name[j+1:];
			break;
		}
	}
	if(suffix != "" && suffix[0] >= 'A' && suffix[0] <= 'Z') {
		s := suffix;
		for(k := 0; k < len s; k++)
			s[k] += ('A' - 'a');
		suffix = s;
	}
	for(i := 0; i < len filetypes; i++)
		if(suffix == filetypes[i].ext)
			return (filetypes[i].icon+".bit", filetypes[i].icon+".mask");
	return ("file.bit", "file.mask");
}

# Lazy-create the floating ghost toplevel on first use. It's a Plain
# (no titlebar) toplevel containing a single label; we set the label's
# image on each drag-start and reshape the toplevel on each motion.
# Hiding it during idle is done by reshaping it off-screen so we
# never pay for a map/unmap round-trip in the hot path.
ensure_ghost()
{
	if(dragghost != nil)
		return;
	(gt, nil) := tkclient->toplevel(ctxt, nil, "drag", Tkclient->Plain);
	tk->cmd(gt, ". configure -bd 0 -bg white");
	tk->cmd(gt, "label .l -borderwidth 0 -bg white");
	tk->cmd(gt, "pack .l");
	# Park off-screen until the first drag positions us.
	tkclient->wmctl(gt, "!reshape . -1 -1000 -1000 -900 -900 exact");
	dragghost = gt;
	dragghosticonpath = "";
	dragghostvisible = 0;
}

# Configure the ghost's icon for `item`. Cached so a long drag of a
# single item only does one Tk image swap.
set_ghost_icon(w: ref FilerWin, item: ref Dir)
{
	ensure_ghost();
	(bitp, maskp) := ghost_icon_paths(w, item);
	if(bitp == dragghosticonpath)
		return;
	dragghosticonpath = bitp;
	tk->cmd(dragghost, "image delete dragicon");	# no-op if absent
	e := tk->cmd(dragghost, sys->sprint("image create bitmap dragicon -file %s -maskfile %s", bitp, maskp));
	if(e != nil && e[0] == '!')
		tk->cmd(dragghost, sys->sprint("image create bitmap dragicon -file %s", bitp));
	tk->cmd(dragghost, ".l configure -image dragicon");
}

# Move the ghost so its top-left is near (sx, sy) in screen coords.
# A small offset keeps the cursor visible above the icon rather than
# centred on it, matching how desktop drags usually feel. The size is
# read straight off the image (image width/height) so we never end up
# with a too-large white square around a small icon — `tk rect` of the
# toplevel can be stale here because the pack manager may not have
# re-run yet after the most recent image swap.
show_ghost(sx, sy: int)
{
	if(dragghost == nil)
		return;
	iw := int tk->cmd(dragghost, "image width dragicon");
	ih := int tk->cmd(dragghost, "image height dragicon");
	if(iw <= 0) iw = 40;
	if(ih <= 0) ih = 30;
	x := sx + GhostMargin;
	y := sy + GhostMargin;
	tkclient->wmctl(dragghost, sys->sprint("!reshape . -1 %d %d %d %d exact",
		x, y, x + iw, y + ih));
	dragghostvisible = 1;
}

# Park the ghost off-screen until the next drag.
hide_ghost()
{
	if(dragghost == nil || !dragghostvisible)
		return;
	tkclient->wmctl(dragghost, "!reshape . -1 -1000 -1000 -900 -900 exact");
	dragghostvisible = 0;
}

# Launch a RISC OS-style app folder: fork a private namespace, apply the app's
# '!Boot' namespace file (with $approot bound to the folder), then run '!Run'.
launch_app(approot: string)
{
	if(approot[len approot-1] == '/')
		approot = approot[0:len approot-1];
	sys->pctl(Sys->NEWPGRP|Sys->FORKFD|Sys->FORKNS|Sys->FORKENV, nil);

	# After FORKFD we hold a COPY of every filer fd, including each
	# window's /chan/wmctl connection. If we leave them open, sh's
	# runasync (the '&' background fork) will copy them again into
	# the launched app's fd table, and the wm won't see our window's
	# disconnect until the app exits -- which is exactly the "filer
	# stays visible until !App quits" bug. Overwrite each inherited
	# wmctl fd with /dev/null in this process so the ref count on
	# the real wmctl chan goes back to just the filer's own.
	<-winlock;
	wins := windows;
	winlock <-= 1;
	nfd := sys->open("/dev/null", Sys->ORDWR);
	if(nfd != nil) {
		for(l := wins; l != nil; l = tl l) {
			ww := hd l;
			if(ww.t != nil && ww.t.ctxt != nil && ww.t.ctxt.connfd != nil)
				sys->dup(nfd.fd, ww.t.ctxt.connfd.fd);
		}
	}

	environ := load Env Env->PATH;
	if(environ != nil) {
		environ->setenv("approot", approot);
		# Hint to tkclient (via $wmicon) where to find this app's
		# toolbar icon when it minimizes. Only set when the icon
		# file actually exists, so apps without one show text.
		iconp := approot + "/icons/" + basename(approot) + ".bit";
		(ok, nil) := sys->stat(iconp);
		if(ok >= 0)
			environ->setenv("wmicon", iconp);
	}

	ns := load Newns Newns->PATH;
	if(ns != nil) {
		err := ns->newns(nil, approot + "/!Boot");
		if(err != nil) {
			sys->fprint(sys->fildes(2), "wmdir: !Boot %s: %s\n", approot, err);
			return;
		}
	}

	sh := load Sh Sh->PATH;
	if(sh == nil) {
		sys->fprint(sys->fildes(2), "wmdir: cannot load %s: %r\n", Sh->PATH);
		return;
	}
	# Launch the way wm/wm launches its children: sh->run with '{$*&}'
	# so sh forks the !Run script into the background and returns,
	# rather than holding this thread inside sh->init for the
	# lifetime of the app.
	sh->run(ctxt, "{$*&}" :: approot + "/!Run" :: nil);
}


button3(w: ref FilerWin, stat: ref Sys->Dir)
{
	if(!plumbed)
		return;
	msg := ref Msg(
		"WmDir",
		"",
		w.path,
		"text",
		"",
		array of byte stat.name);

	msg.send();
}

resolve_drop(src_w: ref FilerWin, src_item: ref Sys->Dir, x: int, y: int)
{
	<-winlock;
	wins := windows;
	winlock <-= 1;

	#sys->print("resolve_drop %s %s %d %d\n", src_w.path, src_item.name, x, y);
	for (l := wins; l != nil; l = tl l) {
		dst_w := hd l;
		if (dst_w == src_w)
			continue;

		actx := int tk->cmd(dst_w.t, ". cget -actx");
		acty := int tk->cmd(dst_w.t, ". cget -acty");
		actw := int tk->cmd(dst_w.t, ". cget -actwidth");
		acth := int tk->cmd(dst_w.t, ". cget -actheight");

		if (x >= actx && x < actx + actw && y >= acty && y < acty + acth) {
			src_path := src_w.path + src_item.name;
			dst_path := dst_w.path + src_item.name;

			mv_mod := load Command "/dis/mv.dis";
			if (mv_mod != nil) {
				sys->print("mv %s %s \n", src_path, dst_path);
				args := "mv" :: src_path :: dst_path :: nil;
				spawn run_mv(mv_mod, ctxt, args, src_w, dst_w);
			}
			return;
		}
	}

	# Drop missed every filer window: forward to the pinboard's
	# file2chan, if one is mounted. Silently no-op when the
	# pinboard isn't running (matches the prior "miss" behaviour).
	src_path := src_w.path + src_item.name;
	fd := sys->open("/chan/pinboard", Sys->OWRITE);
	if (fd != nil)
		sys->fprint(fd, "pin %s %d %d\n", src_path, x, y);
}

run_mv(mod: Command, ctxt: ref Draw->Context, args: list of string, src_w: ref FilerWin, dst_w: ref FilerWin)
{
	sys->pctl(Sys->NEWPGRP|Sys->FORKFD, nil);
	mod->init(ctxt, args);
	if (src_w != nil) src_w.opt <-= "refresh";
	if (dst_w != nil) dst_w.opt <-= "refresh";
}

filetype(t: ref Toplevel, d: ref Dir, path: string): ref Ft
{
	if(d.mode & Sys->DMDIR)
		return loadtype(t, dirtype);

	suffix := "";
	for(j := len path-2; j >= 0; j--) {
		if(path[j] == '.') {
			suffix = path[j+1:];
			break;
		}
	}

	if(suffix == "")
		return loadtype(t, deftype);

	if(suffix[0] >= 'A' && suffix[0] <= 'Z') {
		for(j = 0; j < len suffix; j++)
			suffix[j] += ('A' - 'a');
	}

	for(i := 0; i<len filetypes; i++) {
		if(suffix == filetypes[i].ext)
			return loadtype(t, filetypes[i]);
	}

	return loadtype(t, deftype);
}

loadtype(t: ref Toplevel, ft: ref Ft): ref Ft
{
	if(ft.loaded)
		return ft;

	s := sys->sprint("image create bitmap %s -file %s.bit -maskfile %s.mask",
				ft.tkname, ft.icon, ft.icon);	
	tk->cmd(t, s);

	ft.loaded = 1;
	return ft;
}

drawdir(w: ref FilerWin)
{
	if(w.usetext)
		drawdirtxt(w);
	else
		drawdirico(w);
}

drawdirtxt(w: ref FilerWin)
{
	t := w.t;
	if(daytime == nil) {
		daytime = load Daytime Daytime->PATH;
		if(daytime == nil) {
			dialog->prompt(ctxt, t.image, "error -fg red", "Load Module",
				sys->sprint("Trying to load \"%s\"\n%r", Daytime->PATH),
				0, "Continue"::nil);
			return;
		}
	}
	w.now = daytime->now();

	y := 10;
	for(i := 0; i < w.nde; i++) {
		if(w.hide && i > 0 && w.de[i].name[0] == '.')
			continue;
		tp := "file";
		if(w.de[i].mode & Sys->DMDIR)
			tp = "dir ";
		else
		if(w.de[i].mode & 8r111)
			tp = "exe ";
		s := sys->sprint("%s %7bd %s %s",
			tp,
			w.de[i].length,
			daytime->filet(w.now, w.de[i].mtime),
			w.de[i].name);
		id := tk->cmd(t, ".fc.c create text 10 "+string y+
				" -anchor w -text {"+s+"}");

		base := ".fc.c bind "+id;
		tk->cmd(t, base+" <Double-Button-1> {send fc 1 "+string i+"}");
		tk->cmd(t, base+" <Double-Button-2> {send fc 2 "+string i+"}");
		tk->cmd(t, base+" <Motion-Button-2> {}");
		tk->cmd(t, base+" <Button-3> {send fc 3 "+string i+"}");
		tk->cmd(t, base+" <Motion-Button-3> {}");
		tk->cmd(t, base+" <Motion-Button-1> {send fc m "+string i+"}");
		y += 15;
	}

	x := int tk->cmd(t, ".fc.c cget actwidth");
	tk->cmd(t, ".fc.c configure -scrollregion { 0 0 "+string x+" "+string y+"}");
}

drawdirico(w_win: ref FilerWin)
{
	t := w_win.t;
	# w is the canvas's own width: from the cached %w on <Configure>
	# (always fresh), otherwise read it directly. Subtract the canvas's
	# 2px border on each side. Never resize the toplevel here.
	w := w_win.curwidth;
	if(w == 0)
		w = int tk->cmd(t, ".fc.c cget -actwidth");
	w -= 4;
	if(w < 1)
		w = 1;
	cols := w / IconColW;
	if(cols < MINCOL)
		cols = MINCOL;
	xwid := w / cols;

	x := xwid/2;
	y := 20;
	max_lines := 1;

	for(i := 0; i < w_win.nde; i++) {
		if(w_win.hide && i > 0 && w_win.de[i].name[0] == '.')
			continue;
		sx := string x;
		img: string;
		fullpath := w_win.path + w_win.de[i].name;
		if((w_win.de[i].mode & Sys->DMDIR) && isapp(fullpath)) {
			img = app_icon(w_win, fullpath);
		} else
			img = filetype(t, w_win.de[i], w_win.de[i].name).tkname;

		id := tk->cmd(t, ".fc.c create image "+sx+" "+
				string y+" -image "+img);

		chars := xwid / Fontwidth;
		if (chars < 1) chars = 1;
		
		name := w_win.de[i].name;
		wrapped := "";
		while (len name > chars) {
			wrapped += name[0:chars] + "\n";
			name = name[chars:];
		}
		wrapped += name;
		
		lines := (len w_win.de[i].name + chars - 1) / chars;
		if (lines > max_lines)
			max_lines = lines;
			
		id_txt := tk->cmd(t, ".fc.c create text "+sx+
				" "+string (y+25)+" -text {"+wrapped+"} -justify center");

		# Bindings for the icon
		base := ".fc.c bind "+id;
		tk->cmd(t, base+" <Double-Button-1> {send fc 1 "+string i+"}");
		tk->cmd(t, base+" <Double-Button-2> {send fc 2 "+string i+"}");
		tk->cmd(t, base+" <Motion-Button-2> {}");
		tk->cmd(t, base+" <Button-3> {send fc 3 "+string i+"}");
		tk->cmd(t, base+" <Motion-Button-3> {}");
		tk->cmd(t, base+" <Motion-Button-1> {send fc m "+string i+"}");

		# Bindings for the text
		base = ".fc.c bind "+id_txt;
		tk->cmd(t, base+" <Double-Button-1> {send fc 1 "+string i+"}");
		tk->cmd(t, base+" <Double-Button-2> {send fc 2 "+string i+"}");
		tk->cmd(t, base+" <Motion-Button-2> {}");
		tk->cmd(t, base+" <Button-3> {send fc 3 "+string i+"}");
		tk->cmd(t, base+" <Motion-Button-3> {}");
		tk->cmd(t, base+" <Motion-Button-1> {send fc m "+string i+"}");
		
		x += xwid;
		if(x > w) {
			x = xwid/2;
			y += 35 + max_lines * 15;
			max_lines = 1;
		}
	}
	y += 35 + max_lines * 15;
	tk->cmd(t, ".fc.c configure -scrollregion { 0 0 "+string w+" "+string y+"}");
}

sysname(): string
{
	syspath := "#c";
	if ( cmdname == "wmdir" )
		syspath = "/n/dev";
	fd := sys->open(syspath+"/sysname", sys->OREAD);
	if(fd == nil)
		return "Anon";
	buf := array[128] of byte;
	n := sys->read(fd, buf, len buf);
	if(n < 0) 
		return "Anon";
	return string buf[0:n];
}

# Substitute '$font' with font string
fontify(s: string): string {
	return strings->replace(s, "$font", font, -1);
}
