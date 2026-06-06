implement Pinboard;

#
# Pinboard: a RISC OS 3.7-style desktop surface for Inferno wm.
#
# A frameless, full-screen, always-bottom window that holds pinned
# icons at arbitrary positions and serves /chan/pinboard, a
# line-oriented text protocol:
#
#   pin <path> [<x> <y>]   add an icon (auto-placed if x/y omitted)
#   unpin <path>           remove an icon by path
#   backdrop <imgpath>     replace the desktop backdrop (.bit only)
#   clear                  remove every pinned icon (keeps backdrop)
#
# Interactive behaviour:
#   B1 on icon         select that icon, drag to move
#   B1 on empty space  deselect all
#   B3 drag on empty   rubber-band select group
#   B1 drag on a       move whole selection together
#     selected icon
#   B2 anywhere        post context menu (Remove / Clear backdrop / Tidy)
#   Double-B1 on icon  activate: run !App's !Run, otherwise plumb the path
#
# State is purely in-memory: nothing is persisted across restarts.
#

include "sys.m";
	sys: Sys;

include "draw.m";
	draw: Draw;
	Point, Rect, Context: import draw;

include "tk.m";
	tk: Tk;
	Toplevel: import tk;

include "tkclient.m";
	tkclient: Tkclient;

include "string.m";
	str: String;

include "plumbmsg.m";
	plumbmsg: Plumbmsg;
	Msg: import plumbmsg;

include "sh.m";

include "newns.m";

include "env.m";

Pinboard: module
{
	init: fn(ctxt: ref Draw->Context, argv: list of string);
};

# Canvas geometry per icon. The image is drawn centered at (x,y);
# the text label sits centred at (x, y + LabelDY); the optional
# selection outline is a (W x H) rectangle centred on the icon.
IconW:    con 48;
IconH:    con 48;
LabelDY:  con 28;
SelW:     con 56;
SelH:     con 56;
SlotDX:   con 96;	# auto-place grid pitch
SlotDY:   con 80;
SlotPad:  con 20;	# leave a margin around the screen edge

# Inferno Tk only recognises a small fixed set of colour names; use
# hex literals to avoid depending on additions to that table.
Bgcolor:  con "#5b7d8a";	# muted desktop teal
Selcolor: con "#ffcc00";	# yellow selection outline (Inferno-like)

Pin: adt
{
	pid:      int;		# stable internal id
	path:     string;	# full path of the pinned object
	label:    string;	# basename, used as caption
	x, y:     int;		# canvas-local centre of the icon
	iconname: string;	# tk image name for the icon
	imgid:    string;	# canvas image item id
	txtid:    string;	# canvas text item id
	selid:    string;	# canvas rect item id, or "" if not selected
};

drawctxt: ref Draw->Context;	# saved for child launches

pintop:   ref Toplevel;
screenr:  Rect;
pins:     list of ref Pin;
nextpid:  int;

# Icon image cache: (.bit path -> tk image name)
iconcache: list of (string, string);
nexticon:  int;

# Single backdrop image item — at most one, identified by tag "backdrop".
backdropName: string;	# tk image name in use, or ""
backdropPath: string;	# source file path (remembered so reads can dump it)
nextbackdrop: int;	# counter for unique tk image names

# Snapshot served via pinIO.read. Regenerated on a read at offset 0
# and kept for follow-on reads at higher offsets so a single cat/cp
# operation sees a consistent snapshot even if pins change mid-read.
readsnap: array of byte;

# Rubber-band state
selecting: int;
selX0, selY0: int;

# Drag state
dragging: int;
dragX, dragY: int;

# Plumbing
plumbed: int;

badmodule(p: string)
{
	sys->fprint(sys->fildes(2), "pinboard: cannot load %s: %r\n", p);
	raise "fail:bad module";
}

init(ctxt: ref Draw->Context, nil: list of string)
{
	sys = load Sys Sys->PATH;
	draw = load Draw Draw->PATH;
	if(draw == nil)
		badmodule(Draw->PATH);
	tk = load Tk Tk->PATH;
	if(tk == nil)
		badmodule(Tk->PATH);
	tkclient = load Tkclient Tkclient->PATH;
	if(tkclient == nil)
		badmodule(Tkclient->PATH);
	str = load String String->PATH;
	if(str == nil)
		badmodule(String->PATH);
	plumbmsg = load Plumbmsg Plumbmsg->PATH;
	if(plumbmsg != nil && plumbmsg->init(1, nil, 0) >= 0)
		plumbed = 1;

	tkclient->init();

	if(ctxt == nil){
		sys->fprint(sys->fildes(2), "pinboard: must run under a window manager\n");
		raise "fail:no wm";
	}
	drawctxt = ctxt;

	# New process group so we can be killed cleanly, plus a forked
	# namespace so any binds we do later don't leak back to the wm.
	# Crucially do NOT rebind "#s" on /chan here: srv keys a fresh
	# namespace per pgrp when attached with no spec, so a rebind
	# would create a private srv that other apps couldn't see. By
	# using the inherited /chan (toolbar's srv mount), the file2chan
	# entry is visible from every wm-launched process.
	sys->pctl(Sys->NEWPGRP|Sys->FORKNS, nil);

	pinIO := sys->file2chan("/chan", "pinboard");
	if(pinIO == nil){
		sys->fprint(sys->fildes(2), "pinboard: cannot make /chan/pinboard: %r\n");
		raise "fail:file2chan";
	}

	mouse := chan of string;
	pintop = buildtop(ctxt, mouse);

	# Become the desktop: never auto-raised, sit at the bottom.
	tkclient->wmctl(pintop, "sticky on");
	tkclient->wmctl(pintop, "lower");

	# Residual bytes from a write that didn't end on a newline.
	residual: array of byte;

	for(;;) alt {
	k := <-pintop.ctxt.kbd =>
		tk->keyboard(pintop, k);
	p := <-pintop.ctxt.ptr =>
		tk->pointer(pintop, *p);
	c := <-pintop.ctxt.ctl or
	c = <-pintop.wreq =>
		case msgverb(c) {
		"rect" =>
			tkclient->wmctl(pintop, c);
			screenr = pintop.screenr;
			relayout();
			# Reshape may have lifted us; insist on the back.
			tkclient->wmctl(pintop, "lower");
		* =>
			tkclient->wmctl(pintop, c);
		}
	m := <-mouse =>
		handlemouse(m);
	(off, data, nil, wc) := <-pinIO.write =>
		if(wc == nil)
			break;
		nread := len data;
		if(off == 0 && len residual > 0)
			residual = nil;
		buf := array[len residual + len data] of byte;
		buf[0:] = residual;
		buf[len residual:] = data;
		residual = consume(buf);
		alt {
		wc <-= (nread, nil) => ;
		* => ;
		}
	(off, nbytes, nil, rc) := <-pinIO.read =>
		if(rc == nil)
			break;
		# Re-snapshot at the start of every read sequence so each
		# `cat /chan/pinboard` reflects the latest state.
		if(off == 0)
			readsnap = snapshot();
		data: array of byte;
		if(off < len readsnap){
			e := off + nbytes;
			if(e > len readsnap)
				e = len readsnap;
			data = readsnap[off:e];
		}
		alt {
		rc <-= (data, nil) => ;
		* => ;
		}
	}
}

# Produce the current pinboard state as the same text protocol the
# write side accepts: the backdrop line (if any), followed by one
# `pin <path> <x> <y>` per icon. Writing the result back to
# /chan/pinboard restores the same arrangement.
snapshot(): array of byte
{
	# Walk `pins` in reverse so the dump is in insertion order — not
	# strictly necessary, but it makes hand-edited snapshots easier
	# to read.
	rev: list of ref Pin;
	for(pl := pins; pl != nil; pl = tl pl)
		rev = hd pl :: rev;
	s := "";
	if(backdropPath != "")
		s += sys->sprint("backdrop %s\n", backdropPath);
	for(l := rev; l != nil; l = tl l){
		p := hd l;
		s += sys->sprint("pin %s %d %d\n", p.path, p.x, p.y);
	}
	return array of byte s;
}

# Build the full-screen Plain toplevel, the canvas and the context menu.
buildtop(ctxt: ref Draw->Context, mouse: chan of string): ref Toplevel
{
	(t, nil) := tkclient->toplevel(ctxt, nil, "Pinboard", Tkclient->Plain);
	screenr = t.screenr;

	tk->namechan(t, mouse, "mouse");

	# Build the canvas first, then freeze the toplevel size: without
	# pack-propagate 0, the toplevel would shrink to the canvas's
	# (empty) natural size rather than the screen rect we configure.
	cmd(t, "canvas .c -borderwidth 0 -bg " + Bgcolor);
	cmd(t, "pack .c -fill both -expand 1");
	cmd(t, "pack propagate . 0");

	cmd(t, ". configure -bd 0 -bg " + Bgcolor +
		" -x " + string screenr.min.x +
		" -y " + string screenr.min.y +
		" -width " + string screenr.dx() +
		" -height " + string screenr.dy());

	# Canvas-wide bindings. Item bindings for Double-Button-1 are
	# added per-pin so activate sees a pid, not coords.
	cmd(t, "bind .c <ButtonPress-1>   {send mouse press1 %x %y}");
	cmd(t, "bind .c <Motion-Button-1> {send mouse motion1 %x %y}");
	cmd(t, "bind .c <ButtonRelease-1> {send mouse release1 %x %y}");
	cmd(t, "bind .c <ButtonPress-3>   {send mouse press3 %x %y}");
	cmd(t, "bind .c <Motion-Button-3> {send mouse motion3 %x %y}");
	cmd(t, "bind .c <ButtonRelease-3> {send mouse release3 %x %y}");
	cmd(t, "bind .c <ButtonPress-2>   {send mouse menu %x %y}");
	cmd(t, "bind .c <Double-Button-1> {send mouse activate %x %y}");

	# Context menu.
	cmd(t, "menu .m");
	cmd(t, ".m add command -label {Remove}         -command {send mouse remove}");
	cmd(t, ".m add command -label {Clear backdrop} -command {send mouse clrback}");
	cmd(t, ".m add command -label {Tidy}           -command {send mouse tidy}");

	tkclient->startinput(t, "ptr" :: "control" :: nil);
	tkclient->onscreen(t, "exact");
	return t;
}

# Pull one bare verb (the first whitespace-delimited word) out of a
# wmctl message so the dispatch above can switch on it.
msgverb(s: string): string
{
	(nil, toks) := sys->tokenize(s, " \t");
	if(toks == nil)
		return s;
	return hd toks;
}

# Reflow on host-window resize: clamp icons that fell off-screen.
relayout()
{
	cmd(pintop, ". configure -x " + string screenr.min.x +
		" -y " + string screenr.min.y +
		" -width " + string screenr.dx() +
		" -height " + string screenr.dy());
	maxx := screenr.dx() - IconW/2;
	maxy := screenr.dy() - (IconH/2 + LabelDY);
	for(l := pins; l != nil; l = tl l){
		p := hd l;
		nx := p.x;
		ny := p.y;
		if(nx < IconW/2)        nx = IconW/2;
		if(nx > maxx)            nx = maxx;
		if(ny < IconH/2)        ny = IconH/2;
		if(ny > maxy)            ny = maxy;
		if(nx != p.x || ny != p.y)
			movepin(p, nx - p.x, ny - p.y);
	}
}

# Split a byte buffer into newline-terminated lines, dispatch each
# complete line, and return the (possibly empty) tail bytes that
# didn't end on a newline.
consume(buf: array of byte): array of byte
{
	start := 0;
	for(i := 0; i < len buf; i++){
		if(buf[i] == byte '\n'){
			line := string buf[start:i];
			start = i + 1;
			# strip trailing CR if any
			if(len line > 0 && line[len line-1] == '\r')
				line = line[0:len line-1];
			if(line != "")
				dispatch(line);
		}
	}
	if(start == len buf)
		return nil;
	tail := array[len buf - start] of byte;
	tail[0:] = buf[start:];
	return tail;
}

# Execute one protocol line. Unknown verbs are ignored to keep the
# file2chan write path forgiving for shell users.
dispatch(line: string)
{
	(nil, toks) := sys->tokenize(line, " \t");
	if(toks == nil)
		return;
	verb := hd toks;
	args := tl toks;
	case verb {
	"pin" =>
		if(args == nil)
			return;
		path := hd args;
		args = tl args;
		x := -1;
		y := -1;
		if(args != nil && tl args != nil){
			x = int hd args;
			y = int hd tl args;
		}
		cmdpin(path, x, y);
	"unpin" =>
		if(args == nil)
			return;
		cmdunpin(hd args);
	"backdrop" =>
		if(args == nil)
			return;
		cmdbackdrop(hd args);
	"clear" =>
		cmdclear();
	* =>
		;
	}
}

# basename component of a path (mirrors the filer's helper).
basename(path: string): string
{
	if(path == nil)
		return nil;
	if(path[len path-1] == '/')
		path = path[0:len path-1];
	for(i := len path - 1; i >= 0; i--)
		if(path[i] == '/')
			return path[i+1:];
	return path;
}

# RISC OS-style app folder test: name begins with '!' and contains '!Boot'.
isapp(path: string): int
{
	if(path == nil)
		return 0;
	if(path[len path-1] == '/')
		path = path[0:len path-1];
	base := basename(path);
	if(base == nil || base[0] != '!')
		return 0;
	(ok, nil) := sys->stat(path + "/!Boot");
	return ok >= 0;
}

# Pick an icon name for a path. Mirrors the filer's type table so a
# folder gets dir.bit, a .dis gets dis.bit, image formats get
# pic.bit, !App folders get their own bundled icon, and everything
# else falls back to file.bit. All icons live under /icons/tk/.
iconfor(path: string): string
{
	# !App folders win first: they're directories but ship their own
	# colour icon.
	if(isapp(path)){
		ap := path;
		if(ap[len ap-1] == '/')
			ap = ap[0:len ap-1];
		iconbase := ap + "/icons/" + basename(ap);
		(ok, nil) := sys->stat(iconbase + ".bit");
		if(ok >= 0)
			return registericon(iconbase + ".bit", iconbase + ".mask");
		# fall through to the generic dir/file icons
	}

	(ok, d) := sys->stat(path);
	if(ok >= 0 && (d.mode & Sys->DMDIR))
		return registericon("dir.bit", "dir.mask");

	# Extension-keyed icon, matching dir.b's filetypes table.
	base := basename(path);
	suffix := "";
	for(i := len base - 2; i >= 0; i--)
		if(base[i] == '.'){
			suffix = base[i+1:];
			break;
		}
	# Normalise to lowercase so .JPG behaves like .jpg.
	if(suffix != "")
		for(j := 0; j < len suffix; j++)
			if(suffix[j] >= 'A' && suffix[j] <= 'Z')
				suffix[j] += ('a' - 'A');
	case suffix {
	"dis" =>
		return registericon("dis.bit", "dis.mask");
	"bit" or "gif" or "jpg" or "jpeg" or "png" or "mask" =>
		return registericon("pic.bit", "pic.mask");
	}
	return registericon("file.bit", "file.mask");
}

# Cache and create a tk bitmap image. The cache is keyed by the .bit
# path so repeated pins of the same kind only register once.
registericon(bitpath, maskpath: string): string
{
	for(l := iconcache; l != nil; l = tl l){
		(p, n) := hd l;
		if(p == bitpath)
			return n;
	}
	name := sys->sprint("PB_ico_%d", nexticon++);
	bf := bitpath;
	mf := maskpath;
	# Paths that look absolute go through Tk's '@' verbatim escape.
	if(len bitpath > 0 && bitpath[0] == '/')
		bf = "@" + bitpath;
	if(len maskpath > 0 && maskpath[0] == '/')
		mf = "@" + maskpath;
	e := tk->cmd(pintop, sys->sprint("image create bitmap %s -file %s -maskfile %s",
		name, bf, mf));
	if(e == nil || e[0] == '!'){
		# Mask file couldn't be loaded; fall back to image-only so
		# the icon still appears, then warn so the missing mask is
		# noticed in the log without flooding it on every pin.
		e = tk->cmd(pintop, sys->sprint("image create bitmap %s -file %s", name, bf));
		if(e == nil || e[0] == '!')
			return "";
		sys->fprint(sys->fildes(2), "pinboard: %q registered without mask\n", bitpath);
	}
	iconcache = (bitpath, name) :: iconcache;
	return name;
}

# Find a free (x,y) for a pin that didn't specify coordinates: walk
# the screen row-major, skipping slots already taken by other pins.
nextslot(): (int, int)
{
	cols := (screenr.dx() - 2*SlotPad) / SlotDX;
	if(cols < 1) cols = 1;
	rows := (screenr.dy() - 2*SlotPad) / SlotDY;
	if(rows < 1) rows = 1;
	for(r := 0; r < rows; r++){
		for(c := 0; c < cols; c++){
			cx := SlotPad + c*SlotDX + IconW/2;
			cy := SlotPad + r*SlotDY + IconH/2;
			busy := 0;
			for(l := pins; l != nil; l = tl l){
				q := hd l;
				if(abs(q.x - cx) < SlotDX/2 && abs(q.y - cy) < SlotDY/2){
					busy = 1;
					break;
				}
			}
			if(!busy)
				return (cx, cy);
		}
	}
	# Board is full — overlap somewhere predictable.
	return (SlotPad + IconW/2, SlotPad + IconH/2);
}

abs(n: int): int
{
	if(n < 0) return -n;
	return n;
}

cmdpin(path: string, x, y: int)
{
	# Refuse silently if path doesn't exist; better than a stale icon.
	(ok, nil) := sys->stat(path);
	if(ok < 0)
		return;
	icon := iconfor(path);
	if(icon == "")
		return;
	if(x < 0 || y < 0)
		(x, y) = nextslot();
	# Clamp into the canvas.
	(x, y) = clamp(x, y);

	p := ref Pin;
	p.pid = nextpid++;
	p.path = path;
	p.label = basename(path);
	p.x = x;
	p.y = y;
	p.iconname = icon;
	tag := sys->sprint("pid%d", p.pid);
	p.imgid = cmd(pintop, sys->sprint(".c create image %d %d -anchor center -image %s -tags {pin %s img}",
		x, y, icon, tag));
	p.txtid = cmd(pintop, sys->sprint(".c create text %d %d -anchor n -text {%s} -justify center -tags {pin %s txt}",
		x, y + LabelDY, p.label, tag));
	p.selid = "";

	# Per-item double-click so activate sees a pid, not coords.
	cmd(pintop, sys->sprint(".c bind %s <Double-Button-1> {send mouse hit %d}", p.imgid, p.pid));
	cmd(pintop, sys->sprint(".c bind %s <Double-Button-1> {send mouse hit %d}", p.txtid, p.pid));

	pins = p :: pins;
	# Force a redraw now: this entry-point is reached from the
	# file2chan write handler, between user events, so without an
	# explicit update Tk holds the dirty canvas in its queue until
	# the next event (a mouse click) flushes it.
	cmd(pintop, "update");
}

clamp(x, y: int): (int, int)
{
	maxx := screenr.dx() - IconW/2;
	maxy := screenr.dy() - (IconH/2 + LabelDY);
	if(x < IconW/2) x = IconW/2;
	if(x > maxx)    x = maxx;
	if(y < IconH/2) y = IconH/2;
	if(y > maxy)    y = maxy;
	return (x, y);
}

cmdunpin(path: string)
{
	npins: list of ref Pin;
	for(l := pins; l != nil; l = tl l){
		p := hd l;
		if(p.path == path)
			erasepin(p);
		else
			npins = p :: npins;
	}
	pins = npins;
	cmd(pintop, "update");
}

cmdclear()
{
	for(l := pins; l != nil; l = tl l)
		erasepin(hd l);
	pins = nil;
	cmd(pintop, "update");
}

erasepin(p: ref Pin)
{
	cmd(pintop, ".c delete " + p.imgid);
	cmd(pintop, ".c delete " + p.txtid);
	if(p.selid != "")
		cmd(pintop, ".c delete " + p.selid);
}

cmdbackdrop(path: string)
{
	# v1 supports .bit only. The canvas image item is laid down at
	# (0,0) and lowered beneath every pinned icon.
	name := sys->sprint("PB_back_%d", nextbackdrop++);
	tp := path;
	if(len path > 0 && path[0] == '/')
		tp = "@" + path;
	e := tk->cmd(pintop, sys->sprint("image create bitmap %s -file %s", name, tp));
	if(e == nil || e[0] == '!')
		return;
	cmd(pintop, ".c delete backdrop");
	if(backdropName != "")
		cmd(pintop, "image delete " + backdropName);
	cmd(pintop, sys->sprint(".c create image 0 0 -anchor nw -image %s -tags backdrop", name));
	cmd(pintop, ".c lower backdrop");
	backdropName = name;
	backdropPath = path;
	cmd(pintop, "update");
}

# Selection / drag / rubber-band / activation, all multiplexed
# through the `mouse` channel.
handlemouse(m: string)
{
	(nil, toks) := sys->tokenize(m, " \t");
	if(toks == nil)
		return;
	verb := hd toks;
	args := tl toks;
	case verb {
	"press1" =>
		if(args == nil || tl args == nil) return;
		x := int hd args;
		y := int hd tl args;
		# Determine whether the press landed on a pinned icon.
		p := pinat(x, y);
		if(p == nil){
			clearselection();
			return;
		}
		# If user pressed an unselected pin, replace the selection
		# with just that pin; otherwise keep the existing group
		# so the whole lot can be dragged.
		if(p.selid == ""){
			clearselection();
			select(p);
		}
		dragging = 1;
		dragX = x;
		dragY = y;
	"motion1" =>
		if(!dragging || args == nil || tl args == nil) return;
		x := int hd args;
		y := int hd tl args;
		dx := x - dragX;
		dy := y - dragY;
		dragX = x;
		dragY = y;
		for(l := pins; l != nil; l = tl l){
			q := hd l;
			if(q.selid != "")
				movepin(q, dx, dy);
		}
	"release1" =>
		dragging = 0;
		for(l := pins; l != nil; l = tl l){
			q := hd l;
			if(q.selid == "") continue;
			(nx, ny) := clamp(q.x, q.y);
			if(nx != q.x || ny != q.y)
				movepin(q, nx - q.x, ny - q.y);
		}
	"press3" =>
		if(args == nil || tl args == nil) return;
		# Only start a rubber-band when pressed on empty space.
		x := int hd args;
		y := int hd tl args;
		if(pinat(x, y) != nil)
			return;
		selecting = 1;
		selX0 = x;
		selY0 = y;
		clearselection();
		# Inferno Tk's canvas rectangle item has no -dash; use a
		# thin solid outline for the rubber-band instead.
		cmd(pintop, sys->sprint(".c create rectangle %d %d %d %d -outline %s -tags rb",
			x, y, x, y, Selcolor));
	"motion3" =>
		if(!selecting || args == nil || tl args == nil) return;
		x := int hd args;
		y := int hd tl args;
		cmd(pintop, sys->sprint(".c coords rb %d %d %d %d", selX0, selY0, x, y));
	"release3" =>
		if(!selecting || args == nil || tl args == nil) return;
		x := int hd args;
		y := int hd tl args;
		selecting = 0;
		(x1, y1) := (selX0, selY0);
		(x2, y2) := (x, y);
		if(x1 > x2) (x1, x2) = (x2, x1);
		if(y1 > y2) (y1, y2) = (y2, y1);
		hits := tk->cmd(pintop, sys->sprint(".c find overlapping %d %d %d %d", x1, y1, x2, y2));
		cmd(pintop, ".c delete rb");
		# `hits` is a whitespace-separated list of canvas item ids.
		(nil, idstr) := sys->tokenize(hits, " \t");
		for(il := idstr; il != nil; il = tl il){
			id := hd il;
			# Each pin owns two items (image + text); locate by id.
			for(l := pins; l != nil; l = tl l){
				q := hd l;
				if((q.imgid == id || q.txtid == id) && q.selid == "")
					select(q);
			}
		}
	"menu" =>
		if(args == nil || tl args == nil) return;
		# %x/%y on a canvas binding are canvas-local. The Tk menu
		# wants screen-relative coordinates, so add the canvas's
		# screen origin.
		mx := int hd args;
		my := int hd tl args;
		mx += screenr.min.x;
		my += screenr.min.y;
		cmd(pintop, sys->sprint(".m post %d %d", mx, my));
	"activate" =>
		# Empty-canvas double-click — nothing to do.
		;
	"hit" =>
		if(args == nil) return;
		pid := int hd args;
		# The first press of the double-click already selected the
		# pin and would leave its outline behind after activation;
		# clear the selection so a launched icon doesn't appear to
		# still be selected.
		clearselection();
		dragging = 0;
		for(l := pins; l != nil; l = tl l){
			q := hd l;
			if(q.pid == pid){
				activate(q.path);
				break;
			}
		}
	"remove" =>
		npins: list of ref Pin;
		for(l := pins; l != nil; l = tl l){
			q := hd l;
			if(q.selid != "")
				erasepin(q);
			else
				npins = q :: npins;
		}
		pins = npins;
	"clrback" =>
		backdropPath = "";
		cmd(pintop, ".c delete backdrop");
		if(backdropName != "")
			cmd(pintop, "image delete " + backdropName);
		backdropName = "";
		cmd(pintop, "update");
	"tidy" =>
		tidy();
	}
}

# Find the topmost pin under (x,y) on the canvas. The hit area is
# the selection rectangle's bbox plus the label below the icon, so
# clicking the caption picks the pin too. A near-miss into empty
# space remains a deselect.
pinat(x, y: int): ref Pin
{
	for(l := pins; l != nil; l = tl l){
		p := hd l;
		if(x >= p.x - SelW/2 && x < p.x + SelW/2 &&
		   y >= p.y - IconH/2 && y < p.y + LabelDY + 20)
			return p;
	}
	return nil;
}

select(p: ref Pin)
{
	if(p.selid != "")
		return;
	p.selid = cmd(pintop, sys->sprint(".c create rectangle %d %d %d %d -outline %s -width 2 -tags sel",
		p.x - SelW/2, p.y - SelH/2, p.x + SelW/2, p.y + SelH/2, Selcolor));
	cmd(pintop, ".c lower " + p.selid + " " + p.imgid);
}

clearselection()
{
	for(l := pins; l != nil; l = tl l){
		p := hd l;
		if(p.selid != ""){
			cmd(pintop, ".c delete " + p.selid);
			p.selid = "";
		}
	}
}

# Shift a pin (and its associated canvas items) by (dx, dy).
movepin(p: ref Pin, dx, dy: int)
{
	cmd(pintop, sys->sprint(".c move %s %d %d", p.imgid, dx, dy));
	cmd(pintop, sys->sprint(".c move %s %d %d", p.txtid, dx, dy));
	if(p.selid != "")
		cmd(pintop, sys->sprint(".c move %s %d %d", p.selid, dx, dy));
	p.x += dx;
	p.y += dy;
}

# Re-flow every pin onto a tidy row-major grid.
tidy()
{
	cols := (screenr.dx() - 2*SlotPad) / SlotDX;
	if(cols < 1) cols = 1;
	i := 0;
	# Walk the list in original order, not reverse-list-order.
	rev: list of ref Pin;
	for(pl := pins; pl != nil; pl = tl pl)
		rev = hd pl :: rev;
	for(l := rev; l != nil; l = tl l){
		p := hd l;
		col := i % cols;
		row := i / cols;
		nx := SlotPad + col*SlotDX + IconW/2;
		ny := SlotPad + row*SlotDY + IconH/2;
		(nx, ny) = clamp(nx, ny);
		movepin(p, nx - p.x, ny - p.y);
		i++;
	}
}

# Activate a pinned path: !App folders run their !Run inside a new
# namespace; anything else is sent through the plumber.
activate(path: string)
{
	if(isapp(path)){
		spawn launch_app(path);
		return;
	}
	if(!plumbed)
		return;
	dir := path;
	for(i := len path - 1; i >= 0; i--)
		if(path[i] == '/'){
			dir = path[0:i];
			break;
		}
	m := ref Msg("pinboard", "", dir, "text", "", array of byte path);
	m.send();
}

# Clone of tk-filer's launch_app: forks a private namespace + env,
# applies !Boot, then asks sh to background-fork !Run so this thread
# returns immediately.
launch_app(approot: string)
{
	if(approot[len approot-1] == '/')
		approot = approot[0:len approot-1];
	sys->pctl(Sys->NEWPGRP|Sys->FORKFD|Sys->FORKNS|Sys->FORKENV, nil);

	# Don't let the child hold the pinboard's wmctl fd open.
	nfd := sys->open("/dev/null", Sys->ORDWR);
	if(nfd != nil && pintop != nil && pintop.ctxt != nil && pintop.ctxt.connfd != nil)
		sys->dup(nfd.fd, pintop.ctxt.connfd.fd);

	environ := load Env Env->PATH;
	if(environ != nil){
		environ->setenv("approot", approot);
		iconp := approot + "/icons/" + basename(approot) + ".bit";
		(ok, nil) := sys->stat(iconp);
		if(ok >= 0)
			environ->setenv("wmicon", iconp);
	}

	ns := load Newns Newns->PATH;
	if(ns != nil){
		err := ns->newns(nil, approot + "/!Boot");
		if(err != nil){
			sys->fprint(sys->fildes(2), "pinboard: !Boot %s: %s\n", approot, err);
			return;
		}
	}
	sh := load Sh Sh->PATH;
	if(sh == nil){
		sys->fprint(sys->fildes(2), "pinboard: cannot load %s: %r\n", Sh->PATH);
		return;
	}
	sh->run(drawctxt, "{$*&}" :: approot + "/!Run" :: nil);
}

# tk->cmd wrapper that logs the failing command — only useful while
# bringing the app up; left in because canvas misuse is otherwise
# hard to diagnose.
cmd(t: ref Toplevel, c: string): string
{
	r := tk->cmd(t, c);
	if(r != nil && r[0] == '!')
		sys->fprint(sys->fildes(2), "pinboard: tk %#q: %s\n", c, r);
	return r;
}
