implement Vixen;

include "sys.m";
	sys: Sys;
	sprint: import sys;
include "draw.m";
	draw: Draw;
include "arg.m";
include "bufio.m";
	bufio: Bufio;
	Iobuf: import bufio;
include "string.m";
	str: String;
include "tk.m";
	tk: Tk;
include "tkclient.m";
	tkclient: Tkclient;
include "keyboard.m";
	kb: Keyboard;
include "regex.m";
	regex: Regex;
include "plumbmsg.m";
	plumbmsg: Plumbmsg;
	Msg: import plumbmsg;
include "names.m";
	names: Names;
include "sh.m";
	sh: Sh;

include "vixen/buffers.b";
include "vixen/change.b";
include "vixen/cmd.b";
include "vixen/ex.b";
include "vixen/filter.b";
include "vixen/interp.b";
include "vixen/misc.b";
include "vixen/subs.b";

Vixen: module {
	init:	fn(ctxt: ref Draw->Context, argv: list of string);
};


iflag: int;

# 't' for tk events
# 'k' for tk commands
# 'e' for edit
# 'x' for ex
# 'i' for interp (insert/replace, command, visual, move)
# 'd' for misc
# 'c' for cursor
# 'u' for change (undo)
# 'm' for modifications (textdel, textinsert)
debug := array[128] of {* => int 0};
startupmacro: string;  # macro to interpret at startup after opening the file

Insert, Replace, Command0, Visual, Visualline: con iota;  # modes
modes := array[] of {"insert", "replace", "command", "visual", "visual line"};


# parameter "rec" to textdel & textins.
Cnone, Cmod, Cmodrepl, Cchange, Cchangerepl,	# how to record as change, for undo
Csetcursorlo, Csetcursorhi,			# where (if) to set cursor
Csetreg: con 1<<iota;				# whether to set "last change" register
Cchangemask: con Csetcursorlo-1;
Csetcursormask: con Csetcursorlo|Csetcursorhi;

mode: int;
visualstart: ref Cursor;  # start of visual select, non-nil when mode == Visual or Visualline
visualend: ref Cursor;  # end of visual select
cmdcur: ref Cmd;  # current command
cmdprev: ref Cmd;  # previous (completed) command, for '.'
recordreg := -1;  # register currently recording to, < 0 when not recording
record: string;  # chars typed while recording, set to register when done
colsnap := -1;  # column to snap vertical movements to.  only valid >= 0

filename: string;  # may be nil initially
filefd: ref Sys->FD;  # may be nil initially
filestat: Sys->Dir;  # stat after previous read or write, to check before writing.  only valid if filefd not nil.

modified: int;  # whether text has unsaved changes
text: ref Buf;  # contents
textgen: big;   # generation of text, increased on each changed, restored on undo/redo.
textgenlast: big;  # last used gen
cursor: ref Cursor;  # current position in text

statustext: string;  # info/warning/error text to display in status bar

searchregex: Regex->Re;  # current search, set by [/?*#]
searchreverse: int;  # whether search is in reverse, for [nN]
searchcache: array of (int, int);  # cache of search results, only valid if textgen is searchcachegen.
searchcachegen := big -1;

lastfind: int;  # last find command, one of tTfF, for ';' and ','
lastfindchar: int;  # parameter to lastfind

lastmacro: int; # last macro execution, for '@@'

edithist: list of string;  # history of edit commands, hd is last typed
edithistcur := -1;  # currently selected history item, -1 when none
edithisttext: string;  # text currently prefix-searching for (nil at start, after edit field changed, and esc)

completecache: array of string;  # matches with completetext.  invalid when nil
completetext: string;  # text for which completecache is the completion
completeindex: int;  # current index in completecache results

change: ref Change;  # current change (with 1 modification) that is being created (while in insert mode)
changes: array of ref Change;  # change history, for undo.  first elem is oldest change.
changeindex: int;  # points to next new/last undone change.  may be one past end of 'changes'.

# marks & registers are index by ascii char, not all are valid though
marks := array[128] of ref Cursor;
registers := array[128] of string;
register := '"';  # register to write next text deletion to

b3start: ref Pos; # start of button3 press
b3prev: ref Pos;  # previous position while button3 down

statusvisible := 1;  # whether tk frame with status label is visible (and edit entry is not)

highlightstart, highlightend: ref Cursor;  # range to highlight for search match, can be nil
plumbvisible: int;  # whether address or last inserted text is visible (cleared on interp)

vpfd: ref Sys->FD;  # fd to /chan/vixenplumb, for handling plumbing

plumbed: int;
top: ref Tk->Toplevel;
wmctl: chan of string;
drawcontext: ref Draw->Context;

# text selection color scheme.  Green for plumbing.
Normal, Green: con iota;

tkcmds0 := array[] of {
"frame .t",
"text .t.text -background black -foreground white -yscrollcommand {.t.vscroll set}",
"scrollbar .t.vscroll -command {.t.text yview}",
"frame .s",
"label .s.status -text status",
"frame .e",
"entry .e.edit",

"bind .e.edit <Key-\n> {send edit return}",
"bind .e.edit {<Key-\t>} {send edit tab}",
"bind .e.edit <KeyPress> +{send edit press %K}",
"bind .t.text <KeyPress> {send key %K}",
"bind .t.text <ButtonPress-1> {send text b1down @%x,%y}",
"bind .t.text <ButtonRelease-1> {send text b1up @%x,%y}",
"bind .t.text <ButtonPress-3> {send text b3down @%x,%y}",
"bind .t.text <ButtonRelease-3> {send text b3up @%x,%y}",
"bind .t.text <Configure> {send text resized}",

".t.text tag configure eof -foreground blue -background white",
".t.text tag configure search -background yellow -foreground black",
".t.text tag configure plumb -background blue -foreground white",
".t.text tag raise sel",

"pack .t.vscroll -fill y -side left",
"pack .t.text -fill both -expand 1 -side right",
"pack .t -fill both -expand 1",

"pack .s.status -fill x -side left",
"pack .s -fill x -side bottom -after .t",

"pack .e.edit -fill x -expand 1 -side left",
#"pack .e -fill x -side bottom -after .t",

"pack propagate . 0",
". configure -width 700 -height 500",
"focus .t.text",
};

tkaddeof()
{
	tkcmd(".t.text insert end \u0003");
	tkcmd(".t.text tag add eof {end -1c} end");
}

tkbinds()
{
	tkcmd(sprint("bind .e.edit <Key-%c> {send edit esc}", kb->Esc));

	tkcmd(sprint("bind .e.edit <Key-%c> {send edit up}", kb->Up));
	tkcmd(sprint("bind .e.edit <Key-%c> {send edit down}", kb->Down));

	binds := array[] of {'a', '<', 'b', 'd', 'e','>', 'f', 'h', 'k', 'n', 'o', 'p', 'u', 'v', 'w'};
	for(i := 0; i < len binds; i++)
		tkcmd(sprint("bind .t.text <Control-\\%c> {}", binds[i]));
	binds = array[] of {
		kb->Home, kb->Left, kb->End, kb->Right,
		kb->Del, kb->Down, kb->Up, kb->Pgdown, kb->Pgup
	};
	for(i = 0; i < len binds; i++)
		tkcmd(sprint("bind .t.text <Key-\\%c> {send key %%K}", binds[i]));

	binds = array[] of {'h', 'w', 'u', 'f', 'b', 'd', 'y', 'e', 'l', 'g', 'r', 'n', 'p'};
	for(i = 0; i < len binds; i++)
		tkcmd(sprint("bind .t.text <Control-\\%c> {send key %x}", binds[i], kb->APP|binds[i]));
}


init(ctxt: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	if(ctxt == nil)
		fail("no window context");
	drawcontext = ctxt;
	draw = load Draw Draw->PATH;
	arg := load Arg Arg->PATH;
	bufio = load Bufio Bufio->PATH;
	str = load String String->PATH;
	tk = load Tk Tk->PATH;
	tkclient = load Tkclient Tkclient->PATH;
	regex = load Regex Regex->PATH;
	plumbmsg = load Plumbmsg Plumbmsg->PATH;
	names = load Names Names->PATH;
	sh = load Sh Sh->PATH;
	sh->initialise();

	sys->pctl(Sys->NEWPGRP|Sys->FORKNS, nil);

	arg->init(args);
	arg->setusage(arg->progname()+" [-d debug] [-c macro] [-i] path");
	while((c := arg->opt()) != 0)
		case c {
		'c' =>	startupmacro = arg->arg();
		'd' =>
			s := arg->arg();
			for(i := 0; i < len s; i++)
				case x := s[i] {
				'+' =>		debug = array[128] of {* => 1};
				'a' to 'z' =>	debug[x]++;
				* =>		fail(sprint("debug char %c a-z or +", x));
				}
		'i' =>	iflag++;
		* =>	arg->usage();
		}
	args = arg->argv();
	case len args {
	0 =>	{}
	1 =>	filename = hd args;
	* =>	arg->usage();
	}

	plumbed = plumbmsg->init(1, nil, 0) >= 0;

	vpc := chan of (string, string);
	vpfd = sys->open("/chan/vixenplumb", Sys->ORDWR);
	if(vpfd != nil)
		spawn vixenplumbreader(vpfd, vpc);
	else
		warn(sprint("no plumbing, open /chan/vixenplumb: %r"));

	text = text.new();
	cursor = text.pos(Pos(1, 0));
	xmarkput('`', cursor);
	cmdcur = Cmd.new();
	xregput('!', "mk");

	openerr: string;
	if(filename != nil) {
		filefd = sys->open(filename, Sys->ORDWR);
		if(filefd == nil)
			openerr = sprint("%r");
		else {
			ok: int;
			(ok, filestat) = sys->fstat(filefd);
			if(ok < 0) {
				openerr = sprint("stat: %r");
				filefd = nil;
			}
		}
		# if filefd is nil, we warn that this is a new file when tk is initialized
	}

	tkclient->init();
	(top, wmctl) = tkclient->toplevel(ctxt, "", "vixen", Tkclient->Appl);

	textc := chan of string;
	keyc := chan of string;
	editc := chan of string;
	tk->namechan(top, textc, "text");
	tk->namechan(top, keyc, "key");
	tk->namechan(top, editc, "edit");
	tkcmds(tkcmds0);
	tkselcolor(Normal);
	tkbinds();

	if(filename != nil)
		filenameset(filename);

	if(filename != nil && filefd == nil) {
		(ok, dir) := sys->stat(filename);
		if(ok < 0)
			statuswarn(sprint("new file %q", filename));
		else if(dir.mode & Sys->DMDIR)
			statuswarn(sprint("%q is directory", filename));
		else
			statuswarn(sprint("open: %s", openerr));
	}
	if(iflag)
		oerr := textfill(sys->fildes(0));
	else if(filefd != nil)
		oerr = textfill(filefd);
	if(oerr != nil)
		statuswarn("reading: "+oerr);
	tkaddeof();
	up();

	modeset(Command0);

	if(startupmacro != nil) {
		cmdcur = Cmd.mk(startupmacro);
		interpx();
	}

	tkclient->onscreen(top, nil);
	tkclient->startinput(top, "kbd"::"ptr"::nil);

	for(;;) alt {
	s := <-top.ctxt.kbd =>
		tk->keyboard(top, s);

	s := <-top.ctxt.ptr =>
		tk->pointer(top, *s);

	s := <-top.ctxt.ctl or
	s = <-top.wreq =>
		tkclient->wmctl(top, s);

	menu := <-wmctl =>
		case menu {
		"exit" =>	quit();
		* =>		tkclient->wmctl(top, menu);
		}

	txt := <-textc =>
		# special keys/mouse from text widget
		say('t', sprint("text: %q", txt));
		(nil, t) := sys->tokenize(txt, " ");
		case hd t {
		"b1down" =>
			v := tkcmd(".t.text index "+hd tl t);
			if(str->prefix("!", v))
				break;
			pos := Pos.parse(v);
			modeset(Command0);
			cursorset(text.pos(pos));
			tkselectionset(cursor.pos, cursor.pos);
			tkselcolor(Normal);
		"b1up" =>
			v := tkcmd(".t.text index "+hd tl t);
			if(str->prefix("!", v))
				break;
			nc := text.pos(Pos.parse(v));
			ranges := tkcmd(".t.text tag ranges sel");
			if(ranges != nil) {
				(nil, l) := sys->tokenize(ranges, " ");
				if(len l != 2) {
					tkcmd(".t.text tag remove sel "+ranges);
					warn(sprint("bad selection range %q?", ranges));
					continue;
				}
				modeset(Visual);
				visualstart = text.pos(Pos.parse(hd l));
				cursor = text.pos(Pos.parse(hd tl l));
				if(Cursor.cmp(nc, cursor) < 0)
					(cursor, visualstart) = (visualstart, cursor);
				visualend = cursor.clone();
				cursorset(cursor);
			}
		"b3down" =>
			v := tkcmd(".t.text index "+hd tl t);
			if(str->prefix("!", v))
				break;
			pos := ref Pos.parse(v);
			if(b3start == nil) {
				tkselectionset(cursor.pos, cursor.pos);
				tkselcolor(Green);
				b3start = b3prev = pos;
			} else if(!Pos.eq(*pos, *b3prev)) {
				(a, b) := Pos.order(*pos, *b3start);
				tkselectionset(a, b);
				b3prev = pos;
			}
			say('t', sprint("b3down at char %s", (*pos).text()));
		"b3up" =>
			v := tkcmd(".t.text index "+hd tl t);
			if(str->prefix("!", v))
				break;
			pos := Pos.parse(v);
			say('t', sprint("b3up at char %s", pos.text()));
			if(Pos.eq(*b3start, pos)) {
				cx := text.pos(pos);
				(cs, ce) := cx.pathpattern(0);
				if(cs == nil)
					statuswarn("not a path");
				else
					plumb(text.get(cs, ce), nil, plumbdir());
			} else {
				cs := text.pos(*b3start);
				ce := text.pos(pos);
				(cs, ce) = Cursor.order(cs, ce);
				plumb(text.get(cs, ce), nil, plumbdir());
			}
			b3start = b3prev = nil;
			case mode {
			Visual or
			Visualline =>
				cursorset(cursor);
				visualset();
			* =>
				tkcmd(sprint(".t.text tag remove sel 1.0 end"));
			}
			tkselcolor(Normal);
		"resized" =>
			tkcmd(".t.text see insert");
		* =>
			warn(sprint("text unhandled, %q", txt));
		}
		up();

	s := <-keyc =>
		# keys from text widget
		say('t', sprint("cmd: %q", s));
		(x, rem) := str->toint(s, 16);
		if(rem != nil) {
			warn(sprint("bogus char code %q, ignoring", s));
			continue;
		}
		key(x);
		interpx();

	e := <-editc =>
		# special keys from edit widget
		say('t', sprint("edit: %q", e));
		editinput(e);
		up();

	(s, err) := <-vpc =>
		say('d', sprint("vpc, s %q, err %q", s, err));
		if(err != nil) {
			statuswarn("vixenplumb failed: "+err);
			continue;
		}
		if(iflag) {
			ps := text.end();
			textins(Cchange, ps, s);
			tkplumbshow(ps.pos, text.end().pos);
			tkcmd(sprint(".t.text see %s", ps.pos.text()));
		} else {
			nc: ref Cursor;
			(nc, err) = address(Cmd.mk(s), cursor);
			if(err != nil) {
				statuswarn(sprint("bad address from vixenplumb: %q: %s", s, err));
			} else {
				cursorset(nc);
				tkplumbshow(nc.mvcol(0).pos, nc.mvlineend(1).pos);
				statuswarn(sprint("new address from vixenplumb: %s", s));
			}
		}
		tkclient->wmctl(top, "raise");
		tkclient->wmctl(top, "kbdfocus 1");
		tkclient->onscreen(top, "onscreen");
		up();
	}
}

filenameset(s: string)
{
	filename = names->cleanname(names->rooted(workdir(), s));
	if(isdir(filename) && (filename != nil && filename[len filename-1] != '/'))
		filename[len filename] = '/';
	tkclient->settitle(top, "vixen "+filename);
	if(vpfd != nil) {
		f := filename;
		if(f[len f-1] == '/')
			f = f[:len f-1];
		if(sys->fprint(vpfd, "%s", f) < 0)
			statuswarn(sprint("telling vixenplumb about filename: %r"));
	}
}

vixenplumbreader(fd: ref Sys->FD, vpc: chan of (string, string))
{
	buf := array[8*1024] of byte;  # Iomax in vixenplumb
	for(;;) {
		n := sys->read(fd, buf, len buf);
		if(n <= 0) {
			err := "eof";
			if(n < 0)
				err = sprint("%r");
			vpc <-= (nil, err);
			break;
		}
		s := string buf[:n];
		vpc <-= (s, nil);
	}
}

editinput(e: string)
{
	case e {
	"return" =>
		s := tkcmd(".e.edit get");
		if(s == nil)
			raise "empty string from entry";
		say('e', sprint("edit command: %q", s));
		s = s[1:];  # first char has already been read
		tkcmd(".e.edit delete 0 end");
		edithistput(s);
		for(i := 0; i < len s; i++)
			key(s[i]);
		key('\n');
		interpx();
		tkcmd("focus .t.text");
	"tab" =>
		Completebreak: con " \t!\"\'#$%&'()*+,:;<=>?@\\]^_`{|}~";
		s := tkcmd(".e.edit get");
		i := int tkcmd(".e.edit index insert");
		while(i-1 >= 0 && !str->in(s[i-1], Completebreak))
			--i;
		s = s[i:];
		r: string;
		++completeindex;
		if(completecache != nil && completeindex >= len completecache) {
			r = completetext;
			completecache = nil;
		} else {
			if(completecache == nil) {
				err: string;
				(completecache, err) = complete(s);
				if(err != nil)
					return statuswarn("complete: "+err);
				if(len completecache == 0)
					return statuswarn("no match");
				completeindex = 0;
				completetext = s;
			}
			r = completecache[completeindex];
			if(len completecache == 1)
				completecache = nil;
		}
		tkcmd(sprint(".e.edit delete %d end", i));
		tkcmd(".e.edit insert end '"+r);
	"up" or
	"down" =>
		# if up/down was down without esc or text editing afterwards,
		# we use the originally typed text to search, not what's currently in the edit field.
		a := l2a(rev(edithist));
		say('e', sprint("edithist, edithistcur=%d:", edithistcur));
		for(i := 0; i < len a; i++)
			say('e', sprint("%3d %s", i, a[i]));
		editnavigate(e == "up");
	"esc" =>
		editesc();
	* =>
		if(str->prefix("press ", e)) {
			(x, rem) := str->toint(e[len "press ":], 16);
			if(rem != nil)
				return warn(sprint("bad edit press %q", e));

			# key presses are interpreted by tk widget first, then sent here.
			# on e.g. ^h of last char, we see an empty string in the entry, so we abort.
			if(x != '\n' && tkcmd(".e.edit get") == nil)
				editesc();

			# we get up/down and other specials too, they don't change the text
			if((x & kb->Spec) != kb->Spec && x != '\t') {
				edithistcur = -1;
				edithisttext = nil;
				completecache = nil;
			}
		} else
			warn(sprint("unhandled edit command %q", e));
	}
}

# key from text widget or from macro execute
key(x: int)
{
	if(recordreg >= 0)
		record[len record] = x;
	cmdcur.put(x);
}


editesc()
{
	tkcmd(".e.edit delete 0 end");
	edithistcur = -1;
	edithisttext = nil;
	tkcmd("focus .t.text");
	key(kb->Esc);
	interpx();
}

editset0(index: int, s: string)
{
	edithistcur = index;
	tkcmd(sprint("focus .e.edit; .e.edit delete 0 end; .e.edit insert 0 '%s", s));
}

editset(s: string)
{
	editset0(-1, s);
}

xeditget(c: ref Cmd, pre: string): string
{
	if(statusvisible) {
		tkcmd("pack forget .s; pack .e -fill x -side bottom -after .t");
		statusvisible = 0;
	}

	if(!c.more())
		raise "edit:"+pre;

	if(c.char() == kb->Esc)
		xabort(nil);
	s: string;
Read:
	for(;;)
		case x := c.get() {
		-1 =>
			# text from .e.entry has a newline, but don't require one from -c or '@'
			break Read;
		'\n' =>
			say('e', sprint("xeditget, returning %q", s));
			break Read;
		* =>
			s[len s] = x;
		}
	r := pre[0];
	if(r == '?')
		r = '/';
	xregput(r, s);
	return s; 
}

editnavigate(up: int)
{
	if(edithisttext == nil)
		edithisttext = tkcmd(".e.edit get");
	a := l2a(rev(edithist));
	if(up) {
		for(i := edithistcur+1; i < len a; ++i)
			if(str->prefix(edithisttext, a[i]))
				return editset0(i, a[i]);
	} else {
		for(i := edithistcur-1; i >= 0; --i)
			if(str->prefix(edithisttext, a[i]))
				return editset0(i, a[i]);
	}
	statuswarn("no match");
}

edithistput(s: string)
{
	if(s != nil) {
		edithist = s::edithist;
		edithistcur = -1;
	}
}

complete(pre: string): (array of string, string)
{
	(path, f) := str->splitstrr(pre, "/");
say('e', sprint("complete, pre %q, path %q, f %q", pre, path, f));
	dir := path;
	if(path == nil)
		dir = ".";
	fd := sys->open(dir, Sys->OREAD);
	if(fd == nil)
		return (nil, sprint("open: %r"));
	l: list of string;
	for(;;) {
		(n, a) := sys->dirread(fd);
		if(n == 0)
			break;
		if(n < 0)
			return (nil, sprint("dirread: %r"));
		for(i := 0; i < n; i++)
			if(str->prefix(f, a[i].name)) {
				s := path+a[i].name;
				if(a[i].mode & Sys->DMDIR)
					s += "/";
				l = s::l;
			}
	}
	return (l2a(rev(l)), nil);
}

# return directory to plumb from:  dir where filename is in, or workdir if no filename is set
plumbdir(): string
{
	if(filename == nil)
		return workdir();
	return names->dirname(filename);
}

plumb(s, kind, dir: string)
{
	if(!plumbed)
		return statuswarn("cannot plumb");
	if(kind == nil)
		kind = "text";
	msg := ref Msg("vixen", "", dir, kind, "", array of byte s);
	say('d', sprint("plumbing %s", string msg.pack()));
	msg.send();
}

changesave()
{
	if(change == nil)
		return;
	changeadd(change);
	change = nil;
}

changeadd(c: ref Change)
{
	if(changeindex < len changes) {
		changes = changes[:changeindex+1];
	} else {
		n := array[len changes+1] of ref Change;
		n[:] = changes;
		changes = n;
	}
	if(c.ogen == c.ngen)
		raise "storing a change with same orig as new gen?";
	c.ngen = textgen;
	say('u', "changeadd, storing:");
	say('u', c.text());
	changes[changeindex++] = c;
}

apply(c: ref Change): int
{
	say('u', "apply:");
	say('u', c.text());
	for(l := c.l; l != nil; l = tl l)
		pick m := hd l {
		Ins =>	textins(Cnone, text.pos(m.p), m.s);
		Del =>	textdel(Cnone, text.pos(m.p), text.cursor(m.o+len m.s));
		}
	textgen = c.ngen;
	cursorset(text.pos(c.beginpos()));
	return 1;
}

undo()
{
	say('u', sprint("undo, changeindex=%d, len changes=%d", changeindex, len changes));
	if(changeindex == 0)
		return statuswarn("already at oldest change");
	if(apply(changes[changeindex-1].invert()))
		--changeindex;
}

redo()
{
	say('u', "redo");
	if(changeindex >= len changes)
		return statuswarn("already at newest change");;
	c := ref *changes[changeindex];
	c.l = rev(c.l);
	if(apply(c))
		++changeindex;
}


searchset(s: string): int
{
	searchcachegen = big -1;
	searchcache = nil;
	err: string;
	(searchregex, err) = regex->compile(s, 0);
	if(err != nil) {
		searchregex = nil;
		statuswarn("bad pattern");
		return 0;
	}
	return 1;
}

searchall(re: Regex->Re): array of (int, int)
{
	if(textgen == searchcachegen)
		return searchcache;

	l: list of (int, int);
	o := 0;
	s := text.str();
	sol := 1;
	while(o < len s) {
		for(e := o; e < len s && s[e] != '\n'; ++e)
			{}
		r := regex->executese(re, s, (o, e), sol, 1);
		if(len r >= 1 && r[0].t0 >= 0) {
			l = r[0]::l;
			o = r[0].t1;
			sol = 0;
		} else {
			sol = 1;
			o = e+1;
		}
	}
	r := array[len l] of (int, int);
	for(i := len r-1; i >= 0; --i) {
		r[i] = hd l;
		l = tl l;
	}
	searchcache = r;
	searchcachegen = textgen;
	return r;
}

search(rev, srev: int, re: Regex->Re, cr: ref Cursor): (ref Cursor, ref Cursor)
{
	if(re == nil) {
		statuswarn("no search pattern set");
		return (nil, nil);
	}
	if(srev)
		rev = !rev;
	
	r := searchall(re);
	if(len r == 0 || r[0].t0 < 0) {
		statuswarn("pattern not found");
		return (nil, nil);
	}
	i: int;
	if(rev) {
		for(i = len r-1; i >= 0; i--)
			if(r[i].t0 < cr.o)
				break;
		if(i < 0) {
			i = len r-1;
			statuswarn("search wrapped");
		}
	} else {
		for(i = 0; i < len r; i++)
			if(r[i].t0 > cr.o)
				break;
		if(i >= len r) {
			i = 0;
			statuswarn("search wrapped");
		}
	}
	return (text.cursor(r[i].t0), text.cursor(r[i].t1));
}


xregset(c: int)
{
	# we don't know if it will be for get or set yet, so % is valid
	if(c != '%')
		xregcanput(c);
	register = c;
}

xregget(c: int): string
{
	(s, err) := regget(c);
	if(err == nil && s == nil)
		err = sprint("register %c empty", c);
	if(err != nil)
		xabort(err);
	return s;
}

xregcanput(c: int)
{
	case c {
	'a' to 'z' or
	'/' or
	':' or
	'.' or
	'"' or
	'A' to 'Z' or
	'*' or
	'!' =>	return;
	'%' =>	xabort("register % is read-only");
	* =>	xabort(sprint("bad register %c", c));
	}
}

xregput(x: int, s: string)
{
	err := regput(x, s);
	if(err != nil)
		xabort(err);
}

regget(c: int): (string, string)
{
	r: string;
	case c {
	'a' to 'z' or
	'/' or
	':' or
	'.' or
	'"' or
	'!' =>		r = registers[c];
	'A' to 'Z' =>	r = registers[c-'A'+'a'];
	'%' =>		r = filename;
	'*' =>		r = tkclient->snarfget();
	* =>		return (nil, sprint("bad register %c", c));
	}
	return (r, nil);
}

regput(c: int, s: string): string
{
	case c {
	'a' to 'z' or
	'/' or
	':' or
	'.' or
	'"' or
	'!' =>
		registers[c] = s;
	'A' to 'Z' =>
		registers[c-'A'+'a'] += s;
	'%' =>
		return "register % is read-only";
	'*' =>
		tkclient->snarfput(s);
		return nil;
	* =>	
		return sprint("bad register %c", c);
	}
	return nil;
}


markget(c: int): (ref Cursor, string)
{
	m: ref Cursor;
	case c {
	'a' to 'z' or
	'`' or
	'\'' or
	'.' or
	'^' =>	m = marks[c];
	'<' or
	'>' =>
		if(mode != Visual && mode != Visualline)
			return (nil, "selection not set");
		(vs, ve) := visualrange();
		case c {
		'<' =>	m = vs;
		'>' =>	m = ve;
		}
	* =>
		return (nil, sprint("bad mark %c", c));
	}
	if(m == nil)
		return (nil, sprint("mark %c not set", c));
	return (m, nil);
}

xmarkget(c: int): ref Cursor
{
	(m, err) := markget(c);
	if(err != nil)
		xabort(err);
	return m;
}

xmarkput(c: int, m: ref Cursor)
{
	m = m.clone();
	case c {
	'a' to 'z' or
	'.' or
	'^' =>	marks[c] = m;
	'`' or
	'\'' =>	marks['`'] = marks['\''] = m;
	# < and > cannot be set explicitly
	* =>	xabort(sprint("bad mark %c", c));
	}
}

# fix marks, cs-ce have just been deleted (and their positions are no longer valid!)
markfixdel(cs, ce: ref Cursor)
{
	for(i := 0; i < len marks; i++) {
		m := marks[i];
		if(m == nil || m.o < cs.o)
			continue;
		if(m.o < ce.o)
			marks[i] = nil;
		else
			marks[i] = text.cursor(m.o-Cursor.diff(cs, ce));
	}
}

# fix marks, n bytes have just been inserted at cs
markfixins(cs: ref Cursor, n: int)
{
	for(i := 0; i < len marks; i++) {
		m := marks[i];
		if(m == nil || m.o < cs.o)
			continue;
		marks[i] = text.cursor(m.o+n);
	}
}


# 'q' was received while in command or visual mode.
recordq(c: ref Cmd)
{
	say('d', sprint("recordq, recordreg %c, record %q, c %s", recordreg, record, c.text()));
	if(recordreg >= 0) {
		xregput(recordreg, record[:len record-1]); # strip last 'q' at end
		say('d', sprint("register %c now %q", recordreg, registers[recordreg]));
		record = nil;
		recordreg = -1;
	} else {
		y := c.xget();
		xregcanput(y);
		recordreg = y;
	}
}

# whether text was inserted/replaced
inserted(): int
{
	if(change != nil)
		pick m := hd change.l {
		Ins =>
			return m.o+len m.s == cursor.o;
		}
	return 0;
}

textrepl(rec: int, a, b: ref Cursor, s: string)
{
	if(a == nil)
		a = cursor;
	if(b == nil)
		b = cursor;
	textdel(rec, a, b);
	textins(rec, a, s);
}

# delete from a to b.
# rec indicates whether a Change must be recorded,
# where the cursor should be,
# and whether the last change register should be set.
textdel(rec: int, a, b: ref Cursor)
{
	tkhighlightclear();

	if(a == nil)
		a = cursor;
	if(b == nil)
		b = cursor;

	setreg := rec & Csetreg;
	setcursor := rec & Csetcursormask;

	swap := Cursor.cmp(a, b) > 0;
	if(swap)
		(a, b) = (b, a);
	s := text.get(a, b);

	rec &= Cchangemask;
Change:
	case rec {
	Cnone =>
		{}
	Cmodrepl =>
		say('m', sprint("textdel, Cmodrepl, s %q, a %s, b %s", s, a.text(), b.text()));
		if(change == nil)
			return statuswarn("beep!");
		pick m := hd change.l {
		Ins =>
			say('m', "textdel, last was insert");
			if(m.o+len m.s != b.o)
				raise "delete during replace should be at end of previous insert";
			if(len s > len m.s) {
				a = text.cursor(b.o-len m.s);
				s = text.get(a, b);
			}
			m.s = m.s[:len m.s-len s];
			# we check below whether we have to remove this Mod.Ins
		Del =>
			say('m', "textdel, last was del");
			return statuswarn("beep!");
		}
	Cmod or
	Cchange =>
		if(change != nil)
			pick m := hd change.l {
			Ins =>
				if(m.o+len m.s == b.o) {
					if(len s > len m.s) {
						a = text.cursor(b.o-len m.s);
						s = text.get(a, b);
					}
					m.s = m.s[:len m.s-len s];
					if(m.s == nil) {
						change.l = tl change.l;
						if(change.l == nil)
							change = nil;
					}
					break Change;
				}
			Del =>
				if(rec != Cmod && rec != Cmodrepl && m.o == a.o) {
					m.s += s;
					break Change;
				}
			}
		if(rec == Cmod)
			return statuswarn("beep!");
		if(change == nil)
			change = ref Change (0, nil, textgen, ~big 0);
		change.l = ref Mod.Del (a.o, a.pos, s)::change.l;
	Cchangerepl =>
		raise "should not happen";
	* =>
		raise "bad rec";
	}
	if(setreg)
		xregput(register, s);
	tkcmd(sprint(".t.text delete %s %s", a.pos.text(), b.pos.text()));
	text.del(a, b);
	textgen = textgenlast++;;
	markfixdel(a, b);
	if(rec != Cnone)
		xmarkput('.', a);

	if(rec == Cmodrepl) {
		# Mod.Del may be absent, eg when replace was started at end of file
		if(tl change.l != nil) {
			pick m := hd tl change.l {
			Del =>
				# if a is in this del, remove till end of it, and insert at the cursor
				if(a.o >= m.o && a.o < m.o+len m.s) {
					nn := a.o-m.o;
					os := m.s[nn:];
					m.s = m.s[:nn];
					text.ins(a, os);
					textgen = textgenlast++;
					markfixins(a, len os);
					tkcmd(sprint(".t.text insert %s '%s", a.pos.text(), os));
					if(a.o+len os >= text.chars())
						tkcmd(sprint(".t.text tag remove eof %s {%s +%dc}", a.pos.text(), a.pos.text(), len os));
				}
			}
		}
		pick m := hd change.l {
		Ins =>
			if(m.s == nil)
				change.l = tl change.l;
		}
		pick m := hd change.l {
		Del =>
			if(m.s == nil)
				change.l = tl change.l;
		}
		if(change.l == nil)
			change = nil;
	}
	if(setcursor) {
		n: ref Cursor;
		case setcursor {
		0 =>		{}
		Csetcursorlo =>	n = a;
		Csetcursorhi =>	n = b;
		* =>		raise "bad rec";
		}
		cursorset(n);
	}
}

textins(rec: int, c: ref Cursor, s: string)
{
	tkhighlightclear();

	if(c == nil)
		c = cursor;

	setcursor := rec&Csetcursormask;
	rec &= Cchangemask;

Change:
	case rec {
	Cnone =>
		{}
	Cmod or 
	Cmodrepl =>
		raise "should not happen";
	Cchange or
	Cchangerepl =>
		ins := 0;
		if(change != nil) {
			pick m := hd change.l {
			Ins =>
				if(m.o+len m.s == c.o) {
					m.s += s;
					ins = 1;
				}
			}
		}
		if(!ins) {
			if(change == nil)
				change = ref Change (0, nil, textgen, ~big 0);
			change.l = ref Mod.Ins (c.o, c.pos, s)::change.l;
		}
		if(rec == Cchangerepl) {
			n := min(len s, len text.str()-c.o);
			if(n > 0) {
				(a, b) := (text.cursor(c.o), text.cursor(c.o+n));
				tkcmd(sprint(".t.text delete %s %s", a.pos.text(), b.pos.text()));
				os := text.del(a, b);
				textgen = textgenlast++;
				markfixdel(a, b);
				if(tl change.l != nil) {
					pick m := hd tl change.l {
					Del =>
						if(c.o == m.o+len m.s) {
							m.s += os;
							break Change;
						}
					}
				}
				m := ref Mod.Del (c.o, c.pos, os);
				change.l = hd change.l::m::tl change.l;
			}
		}
	* =>
		raise "bad rec";
	}

	tkcmd(sprint(".t.text insert %s '%s", c.pos.text(), s));
	if(c.o+len s >= text.chars())
		tkcmd(sprint(".t.text tag remove eof %s {%s +%dc}", c.pos.text(), c.pos.text(), len s));
	nc := text.ins(c, s);
	textgen = textgenlast++;
	markfixins(c, len s);
	case setcursor {
	0 =>	{}
	Csetcursorlo =>	cursorset(c);
	Csetcursorhi =>	cursorset(nc);
	* =>	raise "bad rec";
	}

	modified = 1;
	say('m', sprint("textins, inserted %q, cursor now %s", s, cursor.text()));
}


textfill(fd: ref Sys->FD): string
{
	b := bufio->fopen(fd, Sys->OREAD);
	if(b == nil)
		return sprint("fopen: %r");
	s: string;
	n := 0;
	for(;;) {
		case x := b.getc() {
		Bufio->EOF =>
			tkcmd(".t.text insert end '"+s);
			text.set(s);
			return nil;
		bufio->ERROR =>
			return sprint("read: %r");
		* =>
			s[n++] = x;
		}
	}
}

writemodifiedquit(force: int)
{
	if(modified) {
		if(filename == nil)
			return statuswarn("no filename set");
		err := textwrite(force, filename, nil, nil);
		if(err != nil)
			return statuswarn(err);
		modified = 0;
	}
	if(modified && !force)
		return statuswarn("unsaved changes");
	quit();
}

# write cs-ce to f (force makes it overwrite f when it exists or when cs/ce is not nil).
textwrite(force: int, f: string, cs, ce: ref Cursor): string
{
	fd: ref Sys->FD;
	if(f == nil)
		return "no filename set";
	if(filefd == nil || f != filename) {
		fd = sys->open(f, Sys->ORDWR);
		if(fd != nil && !force)
			return "file already exists";
		if(fd == nil)
			fd = sys->create(f, Sys->ORDWR, 8r666);
		if(fd == nil)
			return sprint("create: %r");
		if(f == filename)
			filefd = fd;
	} else {
		(ok, st) := sys->fstat(filefd);
		if(ok < 0)
			return sprint("stat: %r");
		if(!force) {
			if(st.qid.vers != filestat.qid.vers)
				return sprint("file's qid version has changed, not writing");
			if(st.mtime != filestat.mtime || st.length != filestat.length)
				return sprint("file's length or mtime has changed, not writing");
		}
		sys->seek(filefd, big 0, Sys->SEEKSTART);
		d := sys->nulldir;
		d.length = big 0;
		if(sys->fwstat(filefd, d) < 0)
			return sprint("truncate %q: %r", f);
		fd = filefd;
	}
	err := bufwritefd(text, cs, ce, fd);
	if(filefd != nil) {
		ok: int;
		(ok, filestat) = sys->fstat(filefd);
		if(ok < 0)
			return sprint("stat after write: %r");
	}
	return err;
}

textappend(f: string, cs, ce: ref Cursor): string
{
	if(cs == nil)
		s := text.str();
	else
		s = text.get(cs, ce);
	b := bufio->open(f, Sys->OWRITE);
	if(b == nil)
		return sprint("open: %r");
	b.seek(big 0, bufio->SEEKEND);
	if(b.puts(s) == Bufio->ERROR || b.flush() == Bufio->ERROR)
		return sprint("write: %r");
	return nil;
}

readfile(f: string): (string, string)
{
	b := bufio->open(f, Bufio->OREAD);
	if(b == nil)
		return (nil, sprint("open: %r"));
	s := "";
	for(;;)
	case c := b.getc() {
	Bufio->EOF =>	return (s, nil);
	Bufio->ERROR =>	return (nil, sprint("read: %r"));
	* =>		s[len s] = c;
	}
}


statuswarn(s: string)
{
	say('d', "statuswarn: "+s);
	statustext = s;
	statusset();
}

statusset()
{
	s := sprint("%9s ", "("+modes[mode]+")");
	if(recordreg >= 0)
		s += "recording ";
	if(filename == nil)
		s += "(no filename)";
	else
		s += sprint("%q", names->basename(filename, nil));
	s += sprint(", %4d lines, %5d chars, pos %s", text.lines(), text.chars(), cursor.pos.text());
	if(cmdcur.rem() != nil)
		s += ", "+cmdcur.rem();
	if(statustext != nil)
		s += ", "+statustext;
	tkcmd(sprint(".s.status configure -text '%s", s));
	if(!statusvisible) {
		tkcmd("pack forget .e; pack .s -fill x -side bottom -after .t");
		statusvisible = 1;
	}
}

visualrange(): (ref Cursor, ref Cursor)
{
	(a, b) := Cursor.order(visualstart.clone(), visualend.clone());
	if(mode == Visualline) {
		a = a.mvcol(0);
		b = b.mvlineend(1);
	}
	return (a, b);
}

visualset()
{
	(a, b) := visualrange();
	tkselectionset(a.pos, b.pos);
}

tkselectionset(a, b: Pos)
{
	say('t', sprint("selectionset, from %s to %s", a.text(), b.text()));
	tkcmd(".t.text tag remove sel 1.0 end");
	tkcmd(sprint(".t.text tag add sel %s %s", a.text(), b.text()));
}


redraw()
{
	(spos, nil) := tkvisible();
	tkcmd(".t.text delete 1.0 end");
	tkcmd(".t.text insert 1.0 '"+text.str());
	tkaddeof();
	case mode {
	Visual or
	Visualline =>
		visualset();
	}
	cursorset(cursor);
	if(highlightstart != nil)
		tkhighlight(highlightstart, highlightend);
	plumbvisible = 0;
	tkcmd(sprint(".t.text see %s", spos.text()));
}

tkhighlightclear()
{
	if(highlightstart != nil) {
		tkcmd(".t.text tag remove search 1.0 end");
		highlightstart = highlightend = nil;
	}
}

tkhighlight(s, e: ref Cursor)
{
	tkhighlightclear();
	tkcmd(sprint(".t.text tag add search %s %s", s.pos.text(), e.pos.text()));
	(highlightstart, highlightend) = (s, e);
}

tkplumbclear()
{
	if(plumbvisible) {
		tkcmd(".t.text tag remove plumb 1.0 end");
		plumbvisible = 0;
	}
}

tkplumbshow(s, e: Pos)
{
	tkplumbclear();
	tkcmd(sprint(".t.text tag add plumb %s %s", s.text(), e.text()));
	plumbvisible = 1;
}

tkinsertset(p: Pos)
{
	tkcmd(sprint(".t.text mark set insert %s", p.text()));
}

cursorset0(c: ref Cursor, see: int)
{
	say('c', sprint("new cursor: %s", c.text()));
	cursor = c;
	tkinsertset(c.pos);
	if(see)
		tkcmd(sprint(".t.text see %s", c.pos.text()));
}

cursorset(c: ref Cursor)
{
	cursorset0(c, 1);
}

up()
{
	tkcmd("update");
}

tkvisibletop(): Pos
{
	return Pos.parse(tkcmd(".t.text index @0,0"));
}

tkvisiblebottom(): Pos
{
	height := tkcmd(".t.text cget -actheight");
	s := tkcmd(sprint(".t.text index @0,%d", int height-1));
	return Pos.parse(s);
}

tkvisible(): (Pos, Pos)
{
	return (tkvisibletop(), tkvisiblebottom());
}

tklinesvisible(): int
{
	(a, b) := tkvisible();
	return b.l+1-a.l;
}

tkselcolor(w: int)
{
	case w {
	Normal =>	tkcmd(".t.text tag configure sel -background white -foreground black");
	Green =>	tkcmd(".t.text tag configure sel -background green -foreground white");
	}
}

tkcmd(s: string): string
{
	say('k', s);
	r := tk->cmd(top, s);
	if(r != nil && r[0] == '!')
		warn(sprint("tkcmd: %q: %s", s, r));
	if(r != nil)
		say('k', " -> "+r);
	return r;
}

tkcmds(a: array of string)
{
	for(i := 0; i < len a; i++)
		tkcmd(a[i]);
}

quit()
{
	killgrp(pid());
	exit;
}

pid(): int
{
	return sys->pctl(0, nil);
}

progctl(pid: int, s: string)
{
	sys->fprint(sys->open(sprint("/prog/%d/ctl", pid), sys->OWRITE), "%s", s);
}

kill(pid: int)
{
	progctl(pid, "kill");
}

killgrp(pid: int)
{
	progctl(pid, "killgrp");
}

min(a, b: int): int
{
	if(a < b)
		return a;
	return b;
}

max(a, b: int): int
{
	if(a > b)
		return a;
	return b;
}

abs(a: int): int
{
	if(a < 0)
		a = -a;
	return a;
}

l2a[T](l: list of T): array of T
{
	a := array[len l] of T;
	i := 0;
	for(; l != nil; l = tl l)
		a[i++] = hd l;
	return a;
}

rev[T](l: list of T): list of T
{
	r: list of T;
	for(; l != nil; l = tl l)
		r = hd l::r;
	return r;
}

warn(s: string)
{
	sys->fprint(sys->fildes(2), "%s\n", s);
}

say(c: int, s: string)
{
	if(debug[c])
		warn(s);
}

fail(s: string)
{
	warn(s);
	killgrp(pid());
	raise "fail:"+s;
}
