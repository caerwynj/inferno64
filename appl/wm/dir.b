implement WmDir;

include "sys.m";
	sys: Sys;
	Dir: import sys;

include "draw.m";
	draw: Draw;
	ctxt: ref Draw->Context;
	Font: import draw;

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

Fontwidth: 	int;
font:		string;
Xwidth:		con 50;

WmDir: module
{
	init:	fn(ctxt: ref Draw->Context, argv: list of string);
};

Wm: module
{
	init:	fn(ctxt: ref Draw->Context, argv: list of string);
};

Command: module
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
};

cmdname: string;
sysnam: string;
plumbed := 0;

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
	w.conf = chan of string;
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
	drawdir(w);
	tk->cmd(t, "update; cursor -default");
	tk->cmd(t, "bind . <Configure> {send cf conf}");
	tkclient->onscreen(t, nil);
	tkclient->startinput(t, "kbd"::"ptr"::nil);

	<-winlock;
	windows = w :: windows;
	winlock <-= 1;

	spawn window_loop(w);
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
			remove_window(w);
			exit;
		}
		tkclient->wmctl(t, s);
	<-w.conf =>
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
		#sys->print("action %s\n", action);
		case action[0] {
		'R' =>
			if (w.dragging) {
				#sys->print("release\n");
				w.dragging = 0;
				tk->cmd(t, "grab release .fc.c; cursor -default");
				(nil, toks) := sys->tokenize(action, " ");
				if (len toks >= 3) {
					x := int hd tl toks;
					y := int hd tl tl toks;
					resolve_drop(w, w.dragitem, x, y);
				}
			}
			continue f;
		}

		nd := int action[1:];
		if(nd > len w.de)
			break;
		case action[0] {
		'1' =>
			button1(w, w.de[nd]);
		'3' =>
			button3(w, w.de[nd]);
		'm' =>
			if (!w.dragging) {
				#sys->print("dragging\n");
				w.dragging = 1;
				w.dragitem = w.de[nd];
				tk->cmd(t, "grab set .fc.c; cursor -bitmap cursor.drag");
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

button1(w: ref FilerWin, item: ref Dir)
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
	w := int tk->cmd(t, ".fc.c cget actwidth");

	longest := 0;
	for(i := 0; i < w_win.nde; i++) {
		l := len w_win.de[i].name;
		if(l > longest)
			longest = l;
	}
	if(longest > 12)
		longest = 12;
	longest += 2;

	minw := (longest*Fontwidth);
	if( w < minw ){
		w = minw + int tk->cmd(t, ".fc.scroll cget actwidth");
		tk->cmd(t, ". configure -width "+string w);
		w = minw;
	}

	xwid := Xwidth;
	x := w/minw;
	if (x == 0)
		x = 1;
	x = w/x;
	if(x > xwid)
		xwid = x;

	x = xwid/2;
	y := 20;
	max_lines := 1;

	for(i = 0; i < w_win.nde; i++) {
		if(w_win.hide && i > 0 && w_win.de[i].name[0] == '.')
			continue;
		sx := string x;
		ft := filetype(t, w_win.de[i], w_win.de[i].name);
		img := ft.tkname;
		
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
		tk->cmd(t, base+" <Button-2> {send fc 2 "+string i+"}");
		tk->cmd(t, base+" <Motion-Button-2> {}");
		tk->cmd(t, base+" <Button-3> {send fc 3 "+string i+"}");
		tk->cmd(t, base+" <Motion-Button-3> {}");
		tk->cmd(t, base+" <Motion-Button-1> {send fc m "+string i+"}");

		# Bindings for the text
		base = ".fc.c bind "+id_txt;
		tk->cmd(t, base+" <Double-Button-1> {send fc 1 "+string i+"}");
		tk->cmd(t, base+" <Button-2> {send fc 2 "+string i+"}");
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
	x = int tk->cmd(t, ".fc.c cget actwidth");
	tk->cmd(t, ".fc.c configure -scrollregion { 0 0 "+string x+" "+string y+"}");
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
