implement Brutus;

include "sys.m";
	sys: Sys;

include "draw.m";
	draw: Draw;
	Context, Point, Font, Display, Image, Rect: import draw;
	ctxt: ref Context;

include "tk.m";
	tk: Tk;

include "tkclient.m";
	tkclient: Tkclient;

include "dialog.m";
	dialog: Dialog;

include "selectfile.m";
	selectfile: Selectfile;

include	"bufio.m";
	bufio: Bufio;
	Iobuf: import bufio;

include "imagefile.m";
	imageremap: Imageremap;
	readgif: RImagefile;
	readjpg: RImagefile;
	readpng: RImagefile;

include	"workdir.m";

include	"plumbmsg.m";
	plumbmsg: Plumbmsg;
	Msg: import plumbmsg;

include	"brutus.m";

DEFFONT:	con "/fonts/lucidasans/unicode.8.font";
DEFSIZE:	con 10;
DEFTAG:		con "Roman.10";
SETFONT:	con " -font "+DEFFONT+" ";
FOCUS:		con "focus .ft.t";
NOSEL:		con ".ft.t tag remove sel sel.first sel.last";
UPDATE:		con "update";

BS:		con 8;		# ^h backspace character
BSW:		con 23;		# ^w bacspace word
BSL:		con 21;		# ^u backspace line
ESC:		con 27;		# ^[ cut selection

Name:	con "Brutus";

# build menu
menu_cfg := array[] of {
	# menu
	"menu .m",
	".m add command -text Cut -command {send edit cut}",
	".m add command -text Paste -command {send edit paste}",
	".m add command -text Snarf -command {send edit snarf}",
	".m add command -text Look -command {send edit look}",
};

brutus_cfg := array[] of {
	# buttons
	"button .b.Bold -text B -command {send cmd mdbold}",
	"button .b.Italic -text I -command {send cmd mditalic}",
	"button .b.H1 -text H1 -command {send cmd mdheading 1}",
	"button .b.H2 -text H2 -command {send cmd mdheading 2}",
	"button .b.H3 -text H3 -command {send cmd mdheading 3}",
	"button .b.View -text Raw -command {send cmd mdview}",
	"button .b.Put -text Put -command {send cmd put} -state disabled",

	# text
	"frame .ft",
	"scrollbar .ft.scroll -command {.ft.t yview}",
	"text .ft.t -height 7c -tabs {1c} -wrap word -yscrollcommand {.ft.scroll set}",
	FOCUS,

	# pack
	"pack .b.File .b.Bold .b.Italic .b.H1 .b.H2 .b.H3 .b.View .b.Put -side left",
	"pack .b -anchor w",
	"pack .ft.scroll -side left -fill y",
	"pack .ft.t -fill both -expand 1",
	"pack .ft -fill both -expand 1",
	"pack propagate . 0",
};

control_cfg := array[] of {
	# text
	"frame .ft",
	"scrollbar .ft.scroll -command {.ft.t yview}",
	"text .ft.t -height 4c -wrap word -yscrollcommand {.ft.scroll set}",
	"pack .b.File",
	"pack .b -anchor w",
	"pack .ft.scroll -side left -fill y",
	"pack .ft.t -fill both -expand 1",
	"pack .ft -fill both -expand 1",
	"pack propagate . 0",
};

# bindings to build nice controls in text widget
input_cfg := array[] of {
	# input
	"bind .ft.t <Key> {send keys {%A}}",
	"bind .ft.t <Control-h> {send keys {%A}}",
	"bind .ft.t <Control-w> {send keys {%A}}",
	"bind .ft.t <Control-u> {send keys {%A}}",
	"bind .ft.t <Button-1> +{grab set .ft.t; send but1 pressed}",
	"bind .ft.t <Double-Button-1> +{grab set .ft.t; send but1 pressed}",
	"bind .ft.t <ButtonRelease-1> +{grab release .ft.t; send but1 released}",
	"bind .ft.t <Button-2> {send but2 %X %Y}",
	"bind .ft.t <Motion-Button-2-Button-1> {}",
	"bind .ft.t <Motion-Button-2> {}",
	"bind .ft.t <ButtonPress-3> {send but3 pressed}",
	"bind .ft.t <ButtonRelease-3> {send but3 released %x %y}",
	"bind .ft.t <Motion-Button-3> {}",
	"bind .ft.t <Motion-Button-3-Button-1> {}",
	"bind .ft.t <Double-Button-3> {}",
	"bind .ft.t <Double-ButtonRelease-3> {}",
	"bind .ft.t <FocusIn> +{send cmd focus}",
	UPDATE
};

fontname = array[NFONT] of {
	"Roman",
	"Italic",
	"Bold",
	"Type",
};

sizename = array[NSIZE] of {
	"6",
	"8",
	"10",
	"12",
	"16",
};

# Tag names and their configurations used for markdown rendering.
tagname = array[NTAG] of {
	"Roman.6",
	"Roman.8",
	"Roman.10",
	"Roman.12",
	"Roman.16",
	"Italic.6",
	"Italic.8",
	"Italic.10",
	"Italic.12",
	"Italic.16",
	"Bold.6",
	"Bold.8",
	"Bold.10",
	"Bold.12",
	"Bold.16",
	"Type.6",
	"Type.8",
	"Type.10",
	"Type.12",
	"Type.16",
	"Example",
	"Caption",
	"List",
	"List-elem",
	"Label",
	"Label-ref",
	"Exercise",
	"Heading",
	"No-fill",
	"Author",
	"Title",
	"Index",
	"Index-topic",
};

tagconfig = array[NTAG] of {
	"-font /fonts/lucidasans/unicode.6.font",
	"-font /fonts/lucidasans/unicode.7.font",
	"-font /fonts/lucidasans/unicode.8.font",
	"-font /fonts/lucidasans/unicode.10.font",
	"-font /fonts/lucidasans/unicode.13.font",
	"-font /fonts/lucidasans/italiclatin1.6.font",
	"-font /fonts/lucidasans/italiclatin1.7.font",
	"-font /fonts/lucidasans/italiclatin1.8.font",
	"-font /fonts/lucidasans/italiclatin1.10.font",
	"-font /fonts/lucidasans/italiclatin1.13.font",
	"-font /fonts/lucidasans/boldlatin1.6.font",
	"-font /fonts/lucidasans/boldlatin1.7.font",
	"-font /fonts/lucidasans/boldlatin1.8.font",
	"-font /fonts/lucidasans/boldlatin1.10.font",
	"-font /fonts/lucidasans/boldlatin1.13.font",
	"-font /fonts/lucidasans/typelatin1.6.font",
	"-font /fonts/lucidasans/typelatin1.7.font",
	"-font /fonts/pelm/latin1.9.font",
	"-font /fonts/pelm/ascii.12.font",
	"-font /fonts/pelm/ascii.16.font",
	"-foreground #444444 -lmargin1 1c -lmargin2 1c; .ft.t tag lower Example",
	"-foreground #444444; .ft.t tag lower Caption",
	"-foreground #444444 -lmargin1 1c -lmargin2 1c; .ft.t tag lower List",
	"-foreground #0000A0; .ft.t tag lower List-elem",
	"-foreground #444444; .ft.t tag lower Label",
	"-foreground #444444; .ft.t tag lower Label-ref",
	"-foreground #444444; .ft.t tag lower Exercise",
	"-foreground #444444; .ft.t tag lower Heading",
	"-foreground #444444; .ft.t tag lower No-fill",
	"-foreground #444444; .ft.t tag lower Author",
	"-foreground #444444; .ft.t tag lower Title",
	"-foreground #444444; .ft.t tag lower Index",
	"-foreground #444444; .ft.t tag lower Index-topic",
};

enabled := array[] of {"disabled", "normal"};

# alignment for table cells (subset of what table.b used)
Aleft, Acenter, Aright: con iota;

# Horizontal / vertical padding between table cells.
TABHPAD: con 10;
TABVPAD: con 4;

# Font style indices for table cells (match the internal ordering used
# by table.b).  Only the sizes actually rendered are populated; picking
# a different size per cell means opening another font.
TBL_NFONT: con 4;
TBL_NSIZE: con 5;
TBL_NFONTTAG: con TBL_NFONT * TBL_NSIZE;

TBL_Roman,
TBL_Italic,
TBL_Bold,
TBL_Type: con iota;

TBL_Size6,
TBL_Size8,
TBL_Size10,
TBL_Size12,
TBL_Size16: con iota;

# Font files keyed by (style*TBL_NSIZE + size).
tbl_fontnames := array[TBL_NFONTTAG] of {
	"/fonts/lucidasans/unicode.6.font",
	"/fonts/lucidasans/unicode.7.font",
	"/fonts/lucidasans/unicode.8.font",
	"/fonts/lucidasans/unicode.10.font",
	"/fonts/lucidasans/unicode.13.font",
	"/fonts/lucidasans/italiclatin1.6.font",
	"/fonts/lucidasans/italiclatin1.7.font",
	"/fonts/lucidasans/italiclatin1.8.font",
	"/fonts/lucidasans/italiclatin1.10.font",
	"/fonts/lucidasans/italiclatin1.13.font",
	"/fonts/lucidasans/boldlatin1.6.font",
	"/fonts/lucidasans/boldlatin1.7.font",
	"/fonts/lucidasans/boldlatin1.8.font",
	"/fonts/lucidasans/boldlatin1.10.font",
	"/fonts/lucidasans/boldlatin1.13.font",
	"/fonts/lucidasans/typelatin1.6.font",
	"/fonts/lucidasans/typelatin1.7.font",
	"/fonts/pelm/latin1.9.font",
	"/fonts/pelm/ascii.12.font",
	"/fonts/pelm/ascii.16.font",
};

tbl_fontrefs := array[TBL_NFONTTAG] of ref Font;
tbl_fontused := array[TBL_NFONTTAG] of { * => 0 };

File: adt
{
	tk:			ref Tk->Toplevel;
	isctl:			int;
	name:		string;
	dirty:		int;
	size:			int;		# base font size used for markdown
	configed:	array of int;
	button1:		int;
	button3:		int;
	rawview:	int;		# 1 iff currently showing raw markdown source
	tables:		list of ref MdTable;
	tablectr:	int;
	images:		list of ref MdImage;
	imagectr:	int;
};

MdTable: adt
{
	canv:	string;		# full widget path of the embedded canvas
	src:	string;		# original markdown block (with trailing \n)
};

MdImage: adt
{
	canv:	string;		# full widget path of the embedded canvas
	img:	string;		# Tk image resource name
	src:	string;		# original markdown line (with trailing \n)
};

# Per-cell text run rendered in a single font.
TblItem: adt
{
	s:		string;
	fontnum:	int;
	pos:		Point;
	width:	int;
	next:		cyclic ref TblItem;
};

TblCell: adt
{
	items:	ref TblItem;
	halign:	int;
	width:	int;
	height:	int;
	ascent:	int;
	pos:		Point;	# nw corner of cell, in canvas coords
	row:		int;
	col:		int;
};

TblRow: adt
{
	cells:	array of ref TblCell;
	height:	int;
	ascent:	int;
	pos:		Point;
};

TblCol: adt
{
	width:	int;
	halign:	int;
	pos:		Point;
};

Tbl: adt
{
	nrow:	int;
	ncol:	int;
	width:	int;
	height:	int;
	border:	int;
	cols:		array of ref TblCol;
	rows:		array of ref TblRow;
};

menuindex := "0";
snarftext := "";
central: chan of (ref File, string);
files:	array of ref File;	# global but modified only by control thread
plumbed := 0;
curdir := "";

init(c: ref Context, argv: list of string)
{
	ctxt = c;
	sys = load Sys Sys->PATH;
 	draw = load Draw Draw->PATH;
	tk = load Tk Tk->PATH;
	tkclient = load Tkclient Tkclient->PATH;
	dialog = load Dialog Dialog->PATH;
	selectfile = load Selectfile Selectfile->PATH;
	bufio = load Bufio Bufio->PATH;
	plumbmsg = load Plumbmsg Plumbmsg->PATH;

	if(plumbmsg->init(1, "markdown", 1000) >= 0){
		plumbed = 1;
		workdir := load Workdir Workdir->PATH;
		curdir = workdir->init();
		workdir = nil;
	}

	tkclient->init();
	if (ctxt == nil) {
		ctxt = tkclient->makedrawcontext();
		if (ctxt == nil) {
		sys->fprint(sys->fildes(2), "brutus: no window context\n");
		raise "fail:bad context";
		}
	}
	dialog->init();
	selectfile->init();
	sys->pctl(Sys->NEWPGRP, nil);	# so we can pass "exit" command to tkclient

	file := "";
	if(argv != nil)
		argv = tl argv;
	if(argv != nil)
		file = hd argv;
	central = chan of (ref File, string);
	spawn control(ctxt);
	<-central;
	spawn brutus(ctxt, file);
}

# build menu button for dynamically generated menu
buttoncfg(label, enable: string): string
{
	return "label .b."+label+" -text "+label + " " + enable +
		";bind .b."+label+" <Button-1> {send cmd "+label+"}" +
		";bind .b."+label+" <ButtonRelease-1> {}" +
		";bind .b."+label+" <Motion-Button-1> {}" +
		";bind .b."+label+" <Double-Button-1> {}" +
		";bind .b."+label+" <Double-ButtonRelease-1> {}" +
		";bind .b."+label+" <Enter> {.b."+label+" configure -background #EEEEEE}" +
		";bind .b."+label+" <Leave> {.b."+label+" configure -background #DDDDDD}";
}

tkchans(t: ref Tk->Toplevel): (chan of string, chan of string, chan of string, chan of string, chan of string, chan of string, chan of string)
{
	keys := chan of string;
	tk->namechan(t, keys, "keys");
	edit := chan of string;
	tk->namechan(t, edit, "edit");
	cmd := chan of string;
	tk->namechan(t, cmd, "cmd");
	but1 := chan of string;
	tk->namechan(t, but1, "but1");
	but2 := chan of string;
	tk->namechan(t, but2, "but2");
	but3 := chan of string;
	tk->namechan(t, but3, "but3");
	drag := chan of string;
	tk->namechan(t, drag, "Wm_drag");
	return (keys, edit, cmd, but1, but2, but3, drag);
}

control(ctxt: ref Context)
{
	(t, titlectl) := tkclient->toplevel(ctxt, SETFONT, Name, Tkclient->Appl);

	# f is not used to store anything, just to simplify interfaces
	# shared by control and brutus
	f := ref File (t, 1, "", 0, DEFSIZE, nil, 0, 0, 0, nil, 0, nil, 0);

	tkcmds(t, menu_cfg);
	tkcmd(t, "frame .b");
	tkcmd(t, buttoncfg("File", ""));
	tkcmds(t, control_cfg);
	tkcmds(t, input_cfg);
	files = array[1] of ref File;
	files[0] = f;

	(keys, edit, cmd, but1, but2, but3, drag) := tkchans(t);

	tkcmd(t, ".ft.t mark set typingstart 1.0; .ft.t mark gravity typingstart left");
	central <-= (nil, "");	# signal readiness
	curfile: ref File;

	plumbc := chan of (string, string);
	spawn plumbproc(plumbc);

	tkclient->startinput(t, "kbd"::"ptr"::nil);
	tkclient->onscreen(t, nil);
	tkclient->wmctl(t, "task");
	for(;;) alt {
	s := <-t.ctxt.kbd =>
		tk->keyboard(t, s);
	s := <-t.ctxt.ptr =>
		tk->pointer(t, *s);

	menu := <-t.ctxt.ctl or
	menu = <-t.wreq or
	menu = <-titlectl =>
		if(menu == "exit"){
			if(shutdown(ctxt, t)){
				killplumb();
				tkclient->wmctl(t, menu);
			}
			break;
		}
		tkclient->wmctl(t, menu);

	ecmd := <-edit =>
		editor(f, ecmd);
		tkcmd(t, FOCUS);

	c := <-cmd =>
		(nil, s) := sys->tokenize(c, " ");
		case hd s {
		* =>
			sys->print("unknown control cmd %s\n",c );
		"File" =>
			filemenu(t, 0);
		"new" =>
			(name, ok) := getfilename(ctxt, t, "file for new window", f.name, 1);
			if(ok)
				spawn brutus(ctxt, name);
		"select" =>
			n := int hd tl s;
			if(n > len files)
				break;
			if(n > 0)
				curfile = files[n];
			tkcmd(files[n].tk, ". map; raise .; focus .ft.t");
		"focus" =>
			;
		}

	(file, action) := <-central =>
		(nil, s) := sys->tokenize(action, " ");
		case hd s {
		* =>
			sys->print("control unknown central command %s\n", action);
		"new" =>
			curfile = file;
			nfiles := array[len files+1] of ref File;
			nfiles[0:] = files;
			files = nfiles;
			nfiles = nil;	# make sure references don't linger
			files[len files-1] = file;
		"name" =>
			index := 0;
			for(i:=1; i<len files; i++)
				if(files[i] == file){
					index = i;
					break;
				}
			if(index == 0)
				sys->print("can't find file\n");
		"focus" =>
			if(file != f)
				curfile = file;
		"select" =>
			n := int hd tl s;
			if(n >= len files)
				break;
			if(n > 0)
				curfile = files[n];
			tkcmd(files[n].tk, ". map; raise .; focus .ft.t; update");
		"exiting" =>
			if(file == nil)
				break;
			if(file == curfile)
				curfile = nil;
			index := 0;
			for(i:=1; i<len files; i++)
				if(files[i] == file){
					index = i;
					break;
				}
			if(index == 0)
				sys->print("can't find file\n");
			else{
				# make a new one rather than slice, to clean up references
				nfiles := array[len files-1] of ref File;
				for(i=0; i<index; i++)
					nfiles[i] = files[i];
				for(; i<len nfiles; i++)
					nfiles[i] = files[i+1];
				files = nfiles;
			}
			file = nil;
		}

	c := <-keys =>
		char := typing(f, c);
		if(curfile!=nil && char=='\n' && insat(t, "end"))
			execute(t, curfile, tkcmd(t, ".ft.t get insert-1line insert"));

	c := <-but1 =>
		mousebut1(f, c);

	c := <-but2 =>
		mousebut2(f, c);

	c := <-but3 =>
		mousebut3(f, c);

	c := <-drag =>
		if(len c < 6 || c[0:5] != "path=")
			break;
		spawn brutus(ctxt, c[5:]);

	(fname, addr) := <-plumbc =>
		for(i:=1; i<len files; i++)
			if(files[i].name == fname){
				tkcmd(files[i].tk, ". map; raise .; focus .ft.t");
				showaddr(files[i], addr);
				break;
			}
		if(i == len files){
			if(addr != "")
				spawn brutus(ctxt, fname+":"+addr);
			else
				spawn brutus(ctxt, fname);
		}
	}
}

brutus(ctxt: ref Context, filename: string)
{
	addr := "";
	for(i:=len filename; --i>0; ){
		if(filename[i] == ':'){
			(ok, nil) := sys->stat(filename[0:i]);
			if(ok >= 0){
				addr = filename[i+1:];
				filename = filename[0:i];
				break;
			}
		}
	}

	(t, titlectl)  := tkclient->toplevel(ctxt, SETFONT, Name, Tkclient->Appl);

	f := ref File (t, 0, filename, 0, DEFSIZE, nil, 0, 0, 0, nil, 0, nil, 0);
	f.configed = array[NTAG] of {* => 0};

	tkcmds(t, menu_cfg);
	tkcmd(t, "frame .b");
	tkcmd(t, buttoncfg("File", ""));

	tkcmds(t, brutus_cfg);
	tkcmds(t, input_cfg);

	(keys, edit, cmd, but1, but2, but3, drag) := tkchans(t);

	# Pre-configure the tags we'll use for markdown rendering.
	configfont(f, DEFTAG);
	configfont(f, "Bold.10");
	configfont(f, "Bold.12");
	configfont(f, "Bold.16");
	configfont(f, "Italic.10");
	configfont(f, "Type.10");
	configfont(f, "Heading");
	configfont(f, "List");
	configfont(f, "List-elem");
	configfont(f, "Example");
	tkcmd(t, ".ft.t mark set typingstart 1.0; .ft.t mark gravity typingstart left");
	tkcmd(t, "image create bitmap waiting -file cursor.wait");

	central <-= (f, "new");
	setfilename(f, filename);

	if(filename != "")
		if(loadfile(f, filename) < 0)
			dialog->prompt(ctxt, t.image, "error -fg red",
				"Open file",
				sys->sprint("Can't read %s:\n%r", filename),
				0, "Continue" :: nil);
		else
			showaddr(f, addr);

	tkclient->onscreen(t, nil);
	tkclient->startinput(t, "kbd"::"ptr"::nil);
	for(;;) alt {
	s := <-t.ctxt.kbd =>
		tk->keyboard(t, s);
	s := <-t.ctxt.ptr =>
		tk->pointer(t, *s);

	menu := <-t.ctxt.ctl or
	menu = <-t.wreq or
	menu = <-titlectl =>
		case menu {
		"exit" =>
			if(f.dirty){
				action := confirm(ctxt, t, nameof(f)+" is dirty", 1);
				case action {
				"cancel" =>
					continue;
				"exitclean" =>
					if(dumpfile(f, f.name) < 0)
						continue;
					break;
				"exitdirty" =>
					break;
				}
			}
			central <-= (f, "exiting");
			# this one tears down temporaries holding references to f
			central <-= (nil, "exiting");
			return;
		"task" =>
			tkcmd(t, ". unmap");
		* =>
			tkclient->wmctl(t, menu);
		}

	ecmd := <-edit =>
		editor(f, ecmd);
		tkcmd(t, FOCUS);

	command := <-cmd =>
		(nil, c) := sys->tokenize(command, " ");
		case hd c {
		* =>
			sys->print("unknown command %s\n", command);
		"File" =>
			filemenu(t, 1);
		"new" =>
			(name, ok) := getfilename(ctxt, t, "file for new window", f.name, 1);
			if(ok)
				spawn brutus(ctxt, name);
		"open" =>
			if(f.dirty){
				action := confirm(ctxt, t, nameof(f)+" is dirty", 1);
				case action {
				"cancel" =>
					continue;
				"exitclean" =>
					if(dumpfile(f, f.name) < 0)
						continue;
					break;
				"exitdirty" =>
					break;
				}
			}
			(name, ok) := getfilename(ctxt, t, "file for this window", f.name, 1);
			if(ok && name!=""){
				setfilename(f, name);
				if(loadfile(f, name) < 0){
					tkcmd(t, ".ft.t delete 1.0 end");
					dialog->prompt(ctxt, t.image, "error -fg red",
						"Open file",
						sys->sprint("Can't open %s:\n%r", name),
						0, "Continue"::nil);
				}
			}
		"name" =>
			(name, ok) := getfilename(ctxt, t, "remembered file name", f.name, 1);
			if(ok){
				if(name != f.name){
					setfilename(f, name);
					dirty(f, 1);
				}
			}
		"write" =>
			(name, ok) := getfilename(ctxt, t, "file to write", f.name, 1);
			if(ok && name!=""){
				if(f.name == ""){
					setfilename(f, name);
					dirty(f, 1);
				}
				dumpfile(f, name);
			}
		"select" =>
			central <-= (f, command);
		"put" =>
			dumpfile(f, f.name);
		"mdbold" =>
			if(mdtoggletag(f, "Bold."+string f.size))
				dirty(f, 1);
		"mditalic" =>
			if(mdtoggletag(f, "Italic."+string f.size))
				dirty(f, 1);
		"mdheading" =>
			level := 1;
			if(tl c != nil)
				level = int hd tl c;
			if(mdapplyheading(f, level))
				dirty(f, 1);
		"mdview" =>
			mdviewtoggle(f);
		"focus" =>
			central <-= (f, "focus");
		}

	c := <-keys =>
		typing(f, c);

	c := <-but1 =>
		mousebut1(f, c);

	c := <-but2 =>
		mousebut2(f, c);

	c := <-but3 =>
		mousebut3(f, c);

	c := <-drag =>
		if(len c < 6 || c[0:5] != "path=")
			break;
		spawn brutus(ctxt, c[5:]);
	}
}

typing(f: ref File, c: string): int
{
	t := f.tk;
	char := c[1];
	if(char == '\\')
		char = c[2];
	update := ";.ft.t see insert;"+UPDATE;
	if(char != ESC)
		cut(f, 1);
	case char {
	* =>
		tkcmd(t, ".ft.t insert insert "+c+update);
		dirty(f, 1);
	ESC =>
		if(nullsel(t))
			tkcmd(t, ".ft.t tag add sel typingstart insert;"+
					".ft.t mark set typingstart insert");
		else
			cut(f, 1);
		tkcmd(t, UPDATE);
	BS =>
		bs(f, "c");
	BSL =>
		bs(f, "l");
	BSW =>
		bs(f, "w");
	}
	return char;
}

bs(f: ref File, c: string)
{
	if(!insat(f.tk, "1.0")){
		tkcmd(f.tk, ".ft.t tkTextDelIns -"+c+";.ft.t see insert;"+UPDATE);
		dirty(f, 1);
	}
}

mousebut1(f: ref File, c: string)
{
	f.button1 = (c == "pressed");
	f.button3 = 0;	# abort any pending button 3 action
	tkcmd(f.tk, ".ft.t mark set typingstart insert");
}

mousebut2(f: ref File, c: string)
{
	if(f.button1){
		cut(f, 1);
		tk->cmd(f.tk, UPDATE);
	}else{
		(nil, l) := sys->tokenize(c, " ");
		x := int hd l - 50;
		y := int hd tl l - int tk->cmd(f.tk, ".m yposition "+menuindex) - 10;
		tkcmd(f.tk, ".m activate "+menuindex+"; .m post "+string x+" "+string y+
			"; update");
	}
}

mousebut3(f: ref File, c: string)
{
	t := f.tk;
	if(c == "pressed"){
		f.button3 = 1;
		if(f.button1){
			paste(f);
			tk->cmd(t, "update");
		}
		return;
	}
	if(!plumbed || f.button3==0 || f.button1!=0)
		return;
	f.button3 = 0;
	# Plumb message triggered by release of button 3
	(nil, l) := sys->tokenize(c, " ");
	x := int hd tl l;
	y := int hd tl tl l;
	index := tk->cmd(t, ".ft.t index @"+string x+","+string y);
	selindex := tk->cmd(t, ".ft.t tag ranges sel");
	if(selindex != "")
		insel := tk->cmd(t, ".ft.t compare sel.first <= "+index)=="1" &&
			tk->cmd(t, ".ft.t compare sel.last >= "+index)=="1";
	else
		insel = 0;
	attr := "";
	if(insel)
		text := tk->cmd(t, ".ft.t get sel.first sel.last");
	else{
		(nil, w) := sys->tokenize(index, ".");
		charno := int hd tl w;
		left := tk->cmd(t, ".ft.t index {"+index+" linestart}");
		right := tk->cmd(t, ".ft.t index {"+index+" lineend}");
		line := tk->cmd(t, ".ft.t get "+left+" "+right);
		for(i:=charno; i>0; --i)
			if(line[i-1]==' ' || line[i-1]=='\t')
				break;
		for(j:=charno; j<len line; j++)
			if(line[j]==' ' || line[j]=='\t')
				break;
		text = line[i:j];
		attr = "click="+string (charno-i);
	}
	msg := ref Msg(
		"Brutus",
		"",
		directory(f),
		"text",
		attr,
		array of byte text);
	if(msg.send() < 0)
		sys->fprint(sys->fildes(2), "brutus: plumbing write error: %r\n");
}

directory(f: ref File): string
{
	for(i:=len f.name; --i>=0;)
		if(f.name[i] == '/'){
			if(i == 0)
				i++;
			return f.name[0:i];
		}
	return curdir;
}

filemenu(t: ref tk->Toplevel, buttons: int)
{
	tkcmd(t, "menu .b.Filemenu");
	tkcmd(t, ".b.Filemenu add command -label New -command {send cmd new}");
	if(buttons){
		tkcmd(t, ".b.Filemenu add command -label Open -command {send cmd open}");
		tkcmd(t, ".b.Filemenu add command -label Name -command {send cmd name}");
		tkcmd(t, ".b.Filemenu add command -label Write -command {send cmd write}");
	}
	tkcmd(t, ".b.Filemenu add command -label {["+Name+"]} -command {send cmd select 0}");
	if(files != nil)
		for(i:=1; i<len files; i++){
			name := nameof(files[i]);
			if(files[i].dirty)
				name = "{' "+name+"}";
			else
				name = "{  "+name+"}";
			tkcmd(t, ".b.Filemenu add command -label "+name+
				" -command {send cmd select "+string i+"}");
		}
	tkcmd(t, "bind .b.Filemenu <Unmap> {destroy .b.Filemenu}");
	x := tk->cmd(t, ".ft.scroll cget actx");
	y := tk->cmd(t, ".ft.scroll cget acty");
	tkcmd(t, ".b.Filemenu post "+x+" "+y+"; grab set .b.Filemenu; update");
}

basepath(file: string): (string, string)
{
	for(i := len file-1; i >= 0; i--) {
		if(file[i] == '/')
			return (file[0:i], file[i+1:]);
	}
	return (".", file);
}

putbut(f: ref File)
{
	state := enabled[f.dirty];
	if(f.name != "")
		tkcmd(f.tk, ".b.Put configure -state "+state+"; update");
}

dirty(f: ref File, nowdirty: int)
{
	if(f.isctl)
		return;
	old := f.dirty;
	f.dirty = nowdirty;
	if(old != nowdirty){
		setfilename(f, f.name);
		putbut(f);
	}
}

setfilename(f: ref File, name: string)
{
	oldname := f.name;
	f.name = name;
	if(oldname=="" && name!="")
		putbut(f);
	name = Name + ": \"" +nameof(f)+ "\"";
	if(f.dirty)
		name += " (dirty)";
	tkclient->settitle(f.tk, name);
	tkcmd(f.tk, UPDATE);
	central <-= (f, "name");
}

configfont(f: ref File, tag: string)
{
	for(i:=0; i<NTAG; i++)
		if(tag == tagname[i]){
			if(f.configed[i] == 0){
				tkcmd(f.tk, ".ft.t tag configure "+tag+" "+tagconfig[i]);
				f.configed[i] = 1;
			}
			return;
		}
	sys->print("Brutus: can't configure font %s\n", tag);
}

insat(t: ref Tk->Toplevel, mark: string): int
{
	return tkcmd(t, ".ft.t compare insert == "+mark) == "1";
}

isalnum(s: string): int
{
	if(s == "")
		return 0;
	c := s[0];
	if('a' <= c && c <= 'z')
		return 1;
	if('A' <= c && c <= 'Z')
		return 1;
	if('0' <= c && c <= '9')
		return 1;
	if(c == '_')
		return 1;
	if(c > 16rA0)
		return 1;
	return 0;
}

editor(f: ref File, ecmd: string)
{

	case ecmd {
	"cut" =>
		menuindex = "0";
		cut(f, 1);

	"paste" =>
		menuindex = "1";
		paste(f);

	"snarf" =>
		menuindex = "2";
		if(nullsel(f.tk))
			return;
		snarf(f);

	"look" =>
		menuindex = "3";
		look(f);
	}
	tkcmd(f.tk, UPDATE);
}

nullsel(t: ref Tk->Toplevel): int
{
	return tkcmd(t, ".ft.t tag ranges sel") == "";
}

cut(f: ref File, snarfit: int)
{
	if(nullsel(f.tk))
		return;
	dirty(f, 1);
	if(snarfit)
		snarf(f);
	tkcmd(f.tk, ".ft.t mark set insert sel.first;.ft.t delete sel.first sel.last");
}

snarf(f: ref File)
{
	(nil, sel) := sys->tokenize(tkcmd(f.tk, ".ft.t tag ranges sel"), " ");
	snarftext = tkcmd(f.tk, ".ft.t get "+hd sel+" "+hd tl sel);
	tkclient->snarfput(snarftext);
}

paste(f: ref File)
{
	snarftext = tkclient->snarfget();
	if(snarftext == "")
		return;
	cut(f, 0);
	dirty(f, 1);
	t := f.tk;
	start := tkcmd(t, ".ft.t index insert");
	tkcmd(t, ".ft.t insert insert "+tk->quote(snarftext));
	tkcmd(t, ".ft.t tag add sel "+start+" insert");
}

look(f: ref File)
{
	t := f.tk;
	(sel0, sel1) := word(t);
	if(sel0 == nil)
		return;
	text := tkcmd(t, ".ft.t get "+sel0+" "+sel1);
	if(text == nil)
		return;
	tkcmd(t, "cursor -image waiting; update");
	search(nil, f, text, 0, 0);
	tkcmd(t, "cursor -default; update");
}

word(t: ref Tk->Toplevel): (string, string)
{
	start := "sel.first";
	end := "sel.last";
	if(nullsel(t)){
		insert := tkcmd(t, ".ft.t index insert");
		start = tkcmd(t, ".ft.t index {insert wordstart}");
		if(insert == start){	# tk's definition of 'wordstart' is bogus
			a0 := isalnum(tk->cmd(t, ".ft.t get insert-1chars"));
			a1 := isalnum(tk->cmd(t, ".ft.t get insert"));
			if(a0==0 && a1==0)
				return (nil, nil);
			if(a1 == 0)
				start = tkcmd(t, ".ft.t index {insert-1chars wordstart}");
		}
		end = tkcmd(t, ".ft.t index {"+start+" wordend}");
		if(start == end)
			return (nil, nil);
	}
	return (start, end);
}

# splitl based on indices rather than slices.  this version returns char
# position of the matching character.
splitl(str: string, i, j: int, pat: string): int
{
	while(i < j){
		c := str[i];
		for(k:=len pat-1; k>=0; k--)
			if(c == pat[k])
				return i;
		i++;
	}
	return i;
}

# Insert text at the cursor with the given list of tags.  The tag
# argument is a whitespace-separated list of tag names (e.g. "Heading
# Bold.16").  Tk's `.ft.t insert` expects the tag list as a single Tcl
# list, so we wrap it in braces; otherwise multi-tag lists get parsed
# as "chars tag chars tag ...".
mdput(f: ref File, s, tag: string)
{
	if(s == "")
		return;
	tkcmd(f.tk, ".ft.t insert insert "+tk->quote(s)+" {"+tag+"}");
}

# Parse inline markdown (bold, italic, inline code) within a single
# line.  basetag is the space-separated tag list that applies to plain
# text on this line.
mdinline(f: ref File, line, basetag: string)
{
	end := len line;
	sizestr := string f.size;
	i := 0;
	while(i < end){
		j := i;
		while(j < end){
			c := line[j];
			if(c=='`' || c=='*' || c=='_' || c=='\\')
				break;
			j++;
		}
		if(j > i)
			mdput(f, line[i:j], basetag);
		if(j >= end)
			return;
		c := line[j];
		if(c == '\\' && j+1 < end){
			mdput(f, line[j+1:j+2], basetag);
			i = j+2;
			continue;
		}
		if(c == '`'){
			k := j+1;
			while(k < end && line[k] != '`')
				k++;
			if(k < end){
				tag := "Type."+sizestr;
				configfont(f, tag);
				mdput(f, line[j+1:k], basetag+" "+tag);
				i = k+1;
				continue;
			}
			mdput(f, line[j:j+1], basetag);
			i = j+1;
			continue;
		}
		# '*' or '_': bold if doubled, italic otherwise
		if(j+1 < end && line[j+1] == c){
			k := j+2;
			found := 0;
			while(k+1 < end){
				if(line[k] == c && line[k+1] == c){
					found = 1;
					break;
				}
				k++;
			}
			if(found){
				tag := "Bold."+sizestr;
				configfont(f, tag);
				mdput(f, line[j+2:k], basetag+" "+tag);
				i = k+2;
				continue;
			}
		}
		k := j+1;
		found := 0;
		while(k < end){
			if(line[k] == c){
				found = 1;
				break;
			}
			k++;
		}
		if(found){
			tag := "Italic."+sizestr;
			configfont(f, tag);
			mdput(f, line[j+1:k], basetag+" "+tag);
			i = k+1;
			continue;
		}
		mdput(f, line[j:j+1], basetag);
		i = j+1;
	}
}

# Parse markdown text and insert it into the text widget with tags.
mdinsert(f: ref File, md: string)
{
	configfont(f, DEFTAG);
	lines := mdlines(md);
	n := len lines;
	i := 0;
	while(i < n){
		line := lines[i];
		# fenced code block
		if(len line >= 3 && line[0:3] == "```"){
			code := "";
			i++;
			while(i < n){
				if(len lines[i] >= 3 && lines[i][0:3] == "```"){
					i++;
					break;
				}
				if(code != "")
					code += "\n";
				code += lines[i];
				i++;
			}
			configfont(f, "Example");
			mdput(f, code+"\n", "Example");
			continue;
		}
		# pipe-syntax table
		(nlines, cells, align) := mdtableblock(lines, i);
		if(nlines > 0){
			src := "";
			for(k := 0; k < nlines; k++){
				if(src != "")
					src += "\n";
				src += lines[i+k];
			}
			src += "\n";
			err := mdrendertable(f, cells, align, src);
			if(err != "")
				sys->print("%s: table error: %s\n", Name, err);
			i += nlines;
			continue;
		}
		# standalone image: ![alt](path)
		(imgok, imgalt, imgpath) := mdimageblock(line);
		if(imgok){
			err := mdrenderimage(f, imgalt, imgpath, line+"\n");
			if(err != "")
				sys->print("%s: image error: %s\n", Name, err);
			i++;
			continue;
		}
		# heading
		if(len line >= 2 && line[0] == '#'){
			level := 0;
			while(level < len line && line[level] == '#')
				level++;
			if(level >= 1 && level <= 6 && level < len line && line[level] == ' '){
				text := line[level+1:];
				sz := "10";
				if(level == 1)
					sz = "16";
				else if(level == 2)
					sz = "12";
				btag := "Bold."+sz;
				configfont(f, "Heading");
				configfont(f, btag);
				tag := "Heading "+btag;
				mdinline(f, text, tag);
				mdput(f, "\n", tag);
				i++;
				continue;
			}
		}
		# bullet list item
		if(len line >= 2 && (line[0] == '-' || line[0] == '*') && line[1] == ' '){
			text := line[2:];
			configfont(f, "List");
			configfont(f, "List-elem");
			tag := "List List-elem";
			mdinline(f, text, tag);
			mdput(f, "\n", tag);
			i++;
			continue;
		}
		# indented code block (4+ spaces)
		if(len line >= 4 && line[0:4] == "    "){
			configfont(f, "Example");
			mdput(f, line[4:]+"\n", "Example");
			i++;
			continue;
		}
		# blank line -> paragraph break
		if(line == ""){
			mdput(f, "\n", DEFTAG);
			i++;
			continue;
		}
		# plain paragraph line
		mdinline(f, line, DEFTAG);
		mdput(f, "\n", DEFTAG);
		i++;
	}
}

# Apply or remove a font tag on the current selection (or word at cursor).
# Returns 1 if the widget was modified.
mdtoggletag(f: ref File, tag: string): int
{
	t := f.tk;
	(sel0, sel1) := word(t);
	if(sel0 == nil)
		return 0;
	configfont(f, tag);
	names := tkcmd(t, ".ft.t tag names "+sel0);
	(nil, nl) := sys->tokenize(names, " ");
	has := 0;
	for(ll:=nl; ll!=nil; ll=tl ll)
		if(hd ll == tag){
			has = 1;
			break;
		}
	if(has){
		tkcmd(t, ".ft.t tag remove "+tag+" "+sel0+" "+sel1);
	}else{
		# remove other bold/italic variants in the range so one font wins
		family := "";
		if(len tag > 5 && tag[0:5] == "Bold.")
			family = "Bold.";
		else if(len tag > 7 && tag[0:7] == "Italic.")
			family = "Italic.";
		if(family != "")
			for(i:=0; i<NSIZE; i++){
				other := family+sizename[i];
				if(other != tag)
					tkcmd(t, ".ft.t tag remove "+other+" "+sel0+" "+sel1);
			}
		tkcmd(t, ".ft.t tag add "+tag+" "+sel0+" "+sel1);
	}
	tkcmd(t, UPDATE);
	return 1;
}

# Apply a markdown heading (level 1..3) to the lines covered by the selection.
mdapplyheading(f: ref File, level: int): int
{
	t := f.tk;
	(sel0, sel1) := word(t);
	if(sel0 == nil)
		return 0;
	sz := "10";
	if(level == 1)
		sz = "16";
	else if(level == 2)
		sz = "12";
	btag := "Bold."+sz;
	configfont(f, "Heading");
	configfont(f, btag);
	start := tkcmd(t, ".ft.t index {"+sel0+" linestart}");
	endidx := tkcmd(t, ".ft.t index {"+sel1+" lineend}");
	# remove other bold sizes so the new heading level wins
	for(i:=0; i<NSIZE; i++){
		other := "Bold."+sizename[i];
		if(other != btag)
			tkcmd(t, ".ft.t tag remove "+other+" "+start+" "+endidx);
	}
	tkcmd(t, ".ft.t tag add Heading "+start+" "+endidx);
	tkcmd(t, ".ft.t tag add "+btag+" "+start+" "+endidx);
	tkcmd(t, UPDATE);
	return 1;
}

# Toggle between the rendered view and the raw markdown source view.
# The button label shows the target state (click "Raw" to go raw, then
# it becomes "Render").
mdviewtoggle(f: ref File)
{
	t := f.tk;
	if(f.rawview){
		# raw -> rendered: re-parse current text as markdown
		src := tkcmd(t, ".ft.t get 1.0 {end - 1 char}");
		tkcmd(t, ".ft.t delete 1.0 end");
		mdcleartables(f);
		mdclearimages(f);
		mdinsert(f, src);
		f.rawview = 0;
		tkcmd(t, ".b.View configure -text Raw");
	}else{
		# rendered -> raw: dump to markdown, replace with plain text
		md := mddump(f);
		tkcmd(t, ".ft.t delete 1.0 end");
		mdcleartables(f);
		mdclearimages(f);
		if(md != "")
			tkcmd(t, ".ft.t insert 1.0 "+tk->quote(md));
		f.rawview = 1;
		tkcmd(t, ".b.View configure -text Render");
	}
	tkcmd(t, ".ft.t mark set insert 1.0; update");
}

# Walk the tagged dump of the widget and emit markdown text.
#
# The SGML dump can emit tags in any order at a given position.  In
# particular, <Bold.16> typically appears before <Heading> at the start
# of a heading line.  That means when we see Bold open we don't yet
# know whether the upcoming text is inside a heading (in which case
# we must not emit "**") or a plain paragraph (where we must).  So we
# defer the emission of the bold / italic / code markers until we
# reach a visible character, at which point every tag that opens at
# this position has been observed and we can make the decision.
mddump(f: ref File): string
{
	t := f.tk;
	s := sgml(t, "1.0", "end");

	out := "";

	# "open" flags mean we have already emitted an opening marker
	# that needs a matching closer.  "pend" flags mean a tag is
	# active but we haven't committed a marker yet.
	boldopen := 0;
	boldpend := 0;
	italicopen := 0;
	italicpend := 0;
	codeopen := 0;
	codepend := 0;

	heading := 0;
	example := 0;
	boldsize := 10;
	atlinestart := 1;
	pendinghead := 0;
	pendinglist := 0;
	inlist := 0;

	end := len s;
	i := 0;
	while(i < end){
		c := s[i];
		if(c == '<'){
			(nc, tag, on) := tagstring(s, i, end);
			if(nc >= 0){
				if(tag == "Heading"){
					heading = on;
					if(on)
						pendinghead = 1;
					else
						pendinghead = 0;
				}else if(len tag > 5 && tag[0:5] == "Bold."){
					if(on){
						sz := int tag[5:];
						if(sz > 0)
							boldsize = sz;
						if(!heading && !example)
							boldpend = 1;
					}else{
						if(boldopen){
							out += "**";
							boldopen = 0;
						}
						boldpend = 0;
					}
				}else if(len tag > 7 && tag[0:7] == "Italic."){
					if(on){
						if(!heading && !example)
							italicpend = 1;
					}else{
						if(italicopen){
							out += "*";
							italicopen = 0;
						}
						italicpend = 0;
					}
				}else if(len tag > 5 && tag[0:5] == "Type."){
					if(on){
						if(!heading && !example)
							codepend = 1;
					}else{
						if(codeopen){
							out += "`";
							codeopen = 0;
						}
						codepend = 0;
					}
				}else if(tag == "Example"){
					if(on){
						example = 1;
						if(!atlinestart){
							out += "\n";
							atlinestart = 1;
						}
						out += "```\n";
					}else{
						example = 0;
						if(!atlinestart){
							out += "\n";
							atlinestart = 1;
						}
						out += "```\n";
					}
				}else if(tag == "List-elem"){
					if(on){
						pendinglist = 1;
						inlist = 1;
					}else{
						pendinglist = 0;
						inlist = 0;
					}
				}else if(len tag > 7 && tag[0:7] == "Window "){
					# Embedded widget: look up the original markdown
					# source and splice it back into the output.
					name := tag[7:];
					src := mdfindtable(f, name);
					if(src == "")
						src = mdfindimage(f, name);
					if(src != ""){
						if(!atlinestart)
							out += "\n";
						out += src;
						atlinestart = 1;
					}
				}
				# other tags: ignore
				i += nc;
				continue;
			}
			# fall through: literal '<'
		}

		# Everything below emits one visible character (possibly after
		# flushing any pending prefix / inline markers).
		ch: string;
		if(c == '&' && i+4 <= end && s[i:i+4] == "&lt;"){
			ch = "<";
			i += 4;
		}else{
			ch = s[i:i+1];
			i++;
		}

		if(ch == "\n"){
			# close any open inline markers so they don't leak across lines
			if(codeopen){
				out += "`";
				codeopen = 0;
			}
			if(italicopen){
				out += "*";
				italicopen = 0;
			}
			if(boldopen){
				out += "**";
				boldopen = 0;
			}
			# discard pending markers that never reached a char
			boldpend = 0;
			italicpend = 0;
			codepend = 0;
			pendinghead = 0;
			pendinglist = 0;
			out += "\n";
			atlinestart = 1;
			# consecutive list items share the same <List-elem> tag in
			# the sgml dump, so re-arm the "- " prefix for the next line
			if(inlist)
				pendinglist = 1;
			continue;
		}

		if(pendinghead){
			if(boldsize >= 16) out += "# ";
			else if(boldsize >= 12) out += "## ";
			else out += "### ";
			pendinghead = 0;
		}
		if(pendinglist){
			out += "- ";
			pendinglist = 0;
		}
		if(!heading && !example){
			if(boldpend){
				out += "**";
				boldpend = 0;
				boldopen = 1;
			}
			if(italicpend){
				out += "*";
				italicpend = 0;
				italicopen = 1;
			}
			if(codepend){
				out += "`";
				codepend = 0;
				codeopen = 1;
			}
		}
		out += ch;
		atlinestart = 0;
	}
	# close any still-open markers at EOF
	if(codeopen) out += "`";
	if(italicopen) out += "*";
	if(boldopen) out += "**";
	return out;
}

# s[i] is known to be a less-than sign
tagstring(s: string, i, end: int): (int, string, int)
{
	tag: string;

	j := splitl(s, i+1, end, ">");
	if(j==end || s[j]!='>')
		return (-1, "", 0);
	nc := (j-i)+1;
	on := 1;
	if(s[i+1] == '/'){
		on = 0;
		i++;
	}
	tag = s[i+1:j];
	return (nc, tag, on);
}

sgml(t: ref Tk->Toplevel, start, end: string): string
{
	# turn off selection, to avoid getting that in output
	sel := tkcmd(t, ".ft.t tag ranges sel");
	if(sel != "")
		tkcmd(t, ".ft.t tag remove sel "+sel);
	s := tkcmd(t, ".ft.t dump -sgml "+start+" "+end);
	if(sel != "")
		tkcmd(t, ".ft.t tag add sel "+sel);
	return s;
}

# Parse a pipe-syntax markdown table starting at lines[i].
# Returns (n, cells, align): n is the number of consumed lines
# (0 if no match), cells is cells[row][col] with headers as row 0,
# and align[col] is Aleft / Acenter / Aright from the separator row.
mdtableblock(lines: array of string, start: int)
	: (int, array of array of string, array of int)
{
	if(start+1 >= len lines)
		return (0, nil, nil);
	header := lines[start];
	sep := lines[start+1];
	if(!mdtableishead(header) || !mdtableissep(sep))
		return (0, nil, nil);
	hcells := mdtablesplit(header);
	scells := mdtablesplit(sep);
	ncol := len hcells;
	if(ncol == 0 || len scells != ncol)
		return (0, nil, nil);

	align := array[ncol] of int;
	for(k := 0; k < ncol; k++)
		align[k] = mdtablealign(scells[k]);

	rows := list of {hcells};
	i := start + 2;
	while(i < len lines){
		if(!mdtableishead(lines[i]))
			break;
		c := mdtablesplit(lines[i]);
		if(len c != ncol){
			# pad / truncate to match the header width
			padded := array[ncol] of string;
			for(k = 0; k < ncol; k++){
				if(k < len c)
					padded[k] = c[k];
				else
					padded[k] = "";
			}
			c = padded;
		}
		rows = c :: rows;
		i++;
	}
	nrow := 0;
	for(l := rows; l != nil; l = tl l)
		nrow++;
	cells := array[nrow] of array of string;
	# rows is in reverse order
	idx := nrow - 1;
	for(l = rows; l != nil; l = tl l){
		cells[idx] = hd l;
		idx--;
	}
	return (i - start, cells, align);
}

# Does the line look like a table row (contains at least one '|')?
mdtableishead(s: string): int
{
	for(i := 0; i < len s; i++)
		if(s[i] == '|')
			return 1;
	return 0;
}

# Is the line a separator row (pipes, dashes, colons, whitespace only)?
mdtableissep(s: string): int
{
	# must have at least one '-' and at least one '|'
	seenpipe := 0;
	seendash := 0;
	for(i := 0; i < len s; i++){
		c := s[i];
		case c {
		'|' =>
			seenpipe = 1;
		'-' =>
			seendash = 1;
		':' or ' ' or '\t' =>
			;
		* =>
			return 0;
		}
	}
	return seenpipe && seendash;
}

# Split a pipe row into cells, trimming whitespace and stripping
# leading / trailing empty cells produced by surrounding pipes.
mdtablesplit(s: string): array of string
{
	parts := list of {""};
	n := len s;
	# skip one leading pipe if present
	i := 0;
	while(i < n && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if(i < n && s[i] == '|')
		i++;
	cur := "";
	for(; i < n; i++){
		c := s[i];
		if(c == '\\' && i+1 < n){
			cur[len cur] = s[i+1];
			i++;
			continue;
		}
		if(c == '|'){
			parts = cur :: parts;
			cur = "";
			continue;
		}
		cur[len cur] = c;
	}
	# drop trailing empty cell if the row ended with '|'
	trail := 1;
	for(j := len cur-1; j >= 0; j--)
		if(cur[j] != ' ' && cur[j] != '\t'){
			trail = 0;
			break;
		}
	if(!trail)
		parts = cur :: parts;
	n2 := 0;
	for(l := parts; l != nil; l = tl l)
		n2++;
	arr := array[n2] of string;
	idx := n2 - 1;
	for(l = parts; l != nil; l = tl l){
		arr[idx] = mdtrim(hd l);
		idx--;
	}
	return arr;
}

# Decide a column's alignment from its separator cell (":---", "---:", ":-:").
mdtablealign(sep: string): int
{
	left := 0;
	right := 0;
	for(i := 0; i < len sep; i++){
		if(sep[i] == ':'){
			# first colon of the cell marks left; last marks right
			if(left == 0)
				left = 1;
			right = 1;
			# look for subsequent colons
			for(j := i+1; j < len sep; j++)
				if(sep[j] == ':'){
					right = 1;
				}
			break;
		}
	}
	# recompute: left = ':' at start of trimmed cell, right = ':' at end
	t := mdtrim(sep);
	left = len t > 0 && t[0] == ':';
	right = len t > 0 && t[len t - 1] == ':';
	if(left && right)
		return Acenter;
	if(right)
		return Aright;
	return Aleft;
}

mdtrim(s: string): string
{
	i := 0;
	while(i < len s && (s[i] == ' ' || s[i] == '\t'))
		i++;
	j := len s;
	while(j > i && (s[j-1] == ' ' || s[j-1] == '\t'))
		j--;
	return s[i:j];
}

# Split a string on '\n' into an array of lines.  The trailing newline,
# if any, does not produce an empty final element.
mdlines(s: string): array of string
{
	n := 0;
	for(i := 0; i < len s; i++)
		if(s[i] == '\n')
			n++;
	if(len s > 0 && s[len s-1] != '\n')
		n++;
	arr := array[n] of string;
	idx := 0;
	start := 0;
	for(i = 0; i < len s; i++)
		if(s[i] == '\n'){
			arr[idx++] = s[start:i];
			start = i+1;
		}
	if(start < len s)
		arr[idx++] = s[start:];
	return arr;
}

# Convert a cell's raw text into a list of TblItem runs (one per
# styled fragment).  Defaults to the Roman.10 font; bold / italic /
# inline-code runs use matching font families.
tbl_cellitems(text: string): ref TblItem
{
	head: ref TblItem;
	var_tail: ref TblItem;
	end := len text;
	i := 0;
	while(i < end){
		j := i;
		while(j < end){
			c := text[j];
			if(c == '*' || c == '_' || c == '`' || c == '\\')
				break;
			j++;
		}
		if(j > i){
			it := ref TblItem(text[i:j], tbl_fnum(TBL_Roman, TBL_Size10),
				Point(0,0), 0, nil);
			(head, var_tail) = tbl_append(head, var_tail, it);
		}
		if(j >= end)
			break;
		c := text[j];
		if(c == '\\' && j+1 < end){
			it := ref TblItem(text[j+1:j+2], tbl_fnum(TBL_Roman, TBL_Size10),
				Point(0,0), 0, nil);
			(head, var_tail) = tbl_append(head, var_tail, it);
			i = j+2;
			continue;
		}
		if(c == '`'){
			k := j+1;
			while(k < end && text[k] != '`')
				k++;
			if(k < end){
				it := ref TblItem(text[j+1:k],
					tbl_fnum(TBL_Type, TBL_Size10), Point(0,0), 0, nil);
				(head, var_tail) = tbl_append(head, var_tail, it);
				i = k+1;
				continue;
			}
			# unterminated: treat literally
			it := ref TblItem(text[j:j+1], tbl_fnum(TBL_Roman, TBL_Size10),
				Point(0,0), 0, nil);
			(head, var_tail) = tbl_append(head, var_tail, it);
			i = j+1;
			continue;
		}
		# '*' or '_': bold if doubled, italic otherwise
		if(j+1 < end && text[j+1] == c){
			k := j+2;
			found := 0;
			while(k+1 < end){
				if(text[k] == c && text[k+1] == c){
					found = 1;
					break;
				}
				k++;
			}
			if(found){
				it := ref TblItem(text[j+2:k],
					tbl_fnum(TBL_Bold, TBL_Size10), Point(0,0), 0, nil);
				(head, var_tail) = tbl_append(head, var_tail, it);
				i = k+2;
				continue;
			}
		}
		k := j+1;
		found := 0;
		while(k < end){
			if(text[k] == c){
				found = 1;
				break;
			}
			k++;
		}
		if(found){
			it := ref TblItem(text[j+1:k],
				tbl_fnum(TBL_Italic, TBL_Size10), Point(0,0), 0, nil);
			(head, var_tail) = tbl_append(head, var_tail, it);
			i = k+1;
			continue;
		}
		it := ref TblItem(text[j:j+1], tbl_fnum(TBL_Roman, TBL_Size10),
			Point(0,0), 0, nil);
		(head, var_tail) = tbl_append(head, var_tail, it);
		i = j+1;
	}
	return head;
}

tbl_append(head, var_tail, it: ref TblItem): (ref TblItem, ref TblItem)
{
	if(head == nil)
		return (it, it);
	var_tail.next = it;
	return (head, it);
}

tbl_fnum(fstyle, fsize: int): int
{
	n := fstyle * TBL_NSIZE + fsize;
	if(n < 0 || n >= TBL_NFONTTAG)
		n = tbl_fnum(TBL_Roman, TBL_Size10);
	tbl_fontused[n] = 1;
	return n;
}

tbl_loadfonts(display: ref Draw->Display): string
{
	for(i := 0; i < TBL_NFONTTAG; i++){
		if(tbl_fontused[i] && tbl_fontrefs[i] == nil){
			fname := tbl_fontnames[i];
			fnt := Font.open(display, fname);
			if(fnt == nil)
				return sys->sprint("can't open font %s: %r", fname);
			tbl_fontrefs[i] = fnt;
		}
	}
	return "";
}

# Assumes items are set but no geometry.  Computes width / height /
# ascent for a single-line cell, and positions items within it.
tbl_cell_geom(c: ref TblCell)
{
	h := 0;
	a := 0;
	for(it := c.items; it != nil; it = it.next){
		fnt := tbl_fontrefs[it.fontnum];
		if(fnt == nil)
			continue;
		if(fnt.ascent > a){
			h += fnt.ascent - a;
			a = fnt.ascent;
		}
		bh := fnt.height - fnt.ascent;
		if(bh > h - a)
			h = a + bh;
	}
	x := 0;
	for(it = c.items; it != nil; it = it.next){
		fnt := tbl_fontrefs[it.fontnum];
		if(fnt == nil){
			it.width = 0;
			it.pos = Point(x, 0);
			continue;
		}
		it.width = fnt.width(it.s);
		it.pos = Point(x, a - fnt.ascent);
		x += it.width;
	}
	c.width = x;
	c.height = h;
	c.ascent = a;
}

tbl_col_geom(tab: ref Tbl, ci: int)
{
	col := tab.cols[ci];
	col.width = 0;
	for(ri := 0; ri < tab.nrow; ri++){
		c := tab.rows[ri].cells[ci];
		if(c == nil)
			continue;
		if(c.width > col.width)
			col.width = c.width;
	}
}

tbl_row_geom(tab: ref Tbl, ri: int)
{
	row := tab.rows[ri];
	h := 0;
	a := 0;
	for(ci := 0; ci < tab.ncol; ci++){
		c := row.cells[ci];
		if(c == nil)
			continue;
		if(c.height > h)
			h = c.height;
		if(c.ascent > a)
			a = c.ascent;
	}
	row.height = h;
	row.ascent = a;
}

# Assuming row / col geoms are set, position rows, cols, and cells.
tbl_table_geom(tab: ref Tbl)
{
	bd := tab.border;
	orig := Point(0, 0);
	if(bd > 0)
		orig = Point(TABHPAD+bd, TABVPAD+bd);

	o := orig;
	for(ci := 0; ci < tab.ncol; ci++){
		col := tab.cols[ci];
		col.pos = o;
		o.x += col.width;
		if(ci < tab.ncol-1)
			o.x += TABHPAD;
	}
	if(bd > 0)
		o.x += TABHPAD + bd;
	tab.width = o.x;

	o = orig;
	for(ri := 0; ri < tab.nrow; ri++){
		row := tab.rows[ri];
		row.pos = o;
		o.y += row.height;
		if(ri < tab.nrow-1)
			o.y += TABVPAD;
	}
	if(bd > 0)
		o.y += TABVPAD + bd;
	tab.height = o.y;

	# position each cell: origin is at the column's top-left, adjusted
	# for per-cell horizontal alignment.
	for(ri = 0; ri < tab.nrow; ri++){
		row := tab.rows[ri];
		for(ci := 0; ci < tab.ncol; ci++){
			c := row.cells[ci];
			if(c == nil)
				continue;
			col := tab.cols[ci];
			x := col.pos.x;
			y := row.pos.y;
			al := c.halign;
			case al {
			Aright =>
				x += col.width - c.width;
			Acenter =>
				x += (col.width - c.width) / 2;
			}
			# vertical center within the row
			y += (row.height - c.height) / 2;
			c.pos = Point(x, y);
		}
	}
}

# Draw all cell text items on the named canvas.
tbl_create_cells(f: ref File, tab: ref Tbl, canv: string): string
{
	t := f.tk;
	for(ri := 0; ri < tab.nrow; ri++){
		row := tab.rows[ri];
		for(ci := 0; ci < tab.ncol; ci++){
			c := row.cells[ci];
			if(c == nil)
				continue;
			for(it := c.items; it != nil; it = it.next){
				fnt := tbl_fontrefs[it.fontnum];
				if(fnt == nil || it.s == "")
					continue;
				x := c.pos.x + it.pos.x;
				y := c.pos.y + it.pos.y;
				v := tkcmd(t, canv + " create text " + string x + " "
					+ string y + " -anchor nw -font " + fnt.name
					+ " -text " + tk->quote(it.s));
				if(len v > 0 && v[0] == '!')
					return v;
			}
		}
	}
	return "";
}

tbl_create_border(f: ref File, tab: ref Tbl, canv: string): string
{
	t := f.tk;
	bd := tab.border;
	if(bd <= 0)
		return "";
	x1 := bd / 2;
	y1 := bd / 2;
	x2 := tab.width - bd/2 - 1;
	y2 := tab.height - bd/2 - 1;
	v := tkcmd(t, canv + " create rectangle " + string x1 + " " + string y1
		+ " " + string x2 + " " + string y2 + " -width " + string bd);
	if(len v > 0 && v[0] == '!')
		return v;
	return "";
}

# Draw a horizontal rule under the header row, and a vertical rule
# between each pair of columns.
tbl_create_rules(f: ref File, tab: ref Tbl, canv: string): string
{
	t := f.tk;
	if(tab.nrow >= 2){
		y := tab.rows[0].pos.y + tab.rows[0].height + TABVPAD/2;
		v := tkcmd(t, canv + " create line 0 " + string y + " "
			+ string tab.width + " " + string y + " -width 1");
		if(len v > 0 && v[0] == '!')
			return v;
	}
	for(ci := 0; ci < tab.ncol-1; ci++){
		col := tab.cols[ci];
		x := col.pos.x + col.width + TABHPAD/2;
		v := tkcmd(t, canv + " create line " + string x + " 0 "
			+ string x + " " + string tab.height + " -width 1");
		if(len v > 0 && v[0] == '!')
			return v;
	}
	return "";
}

# Build the Tbl object from a parsed cell matrix and alignment vector.
tbl_build(cells: array of array of string, align: array of int): ref Tbl
{
	nrow := len cells;
	if(nrow == 0)
		return nil;
	ncol := len align;
	if(ncol == 0)
		return nil;
	tab := ref Tbl(nrow, ncol, 0, 0, 1, array[ncol] of ref TblCol,
		array[nrow] of ref TblRow);
	for(ci := 0; ci < ncol; ci++)
		tab.cols[ci] = ref TblCol(0, align[ci], Point(0,0));
	for(ri := 0; ri < nrow; ri++){
		row := ref TblRow(array[ncol] of ref TblCell, 0, 0, Point(0,0));
		for(ci = 0; ci < ncol; ci++){
			text := "";
			if(ri < len cells && ci < len cells[ri])
				text = cells[ri][ci];
			items := tbl_cellitems(text);
			# header row is bold
			if(ri == 0)
				items = tbl_promotebold(items);
			c := ref TblCell(items, align[ci], 0, 0, 0, Point(0,0), ri, ci);
			tbl_cell_geom(c);
			row.cells[ci] = c;
		}
		tab.rows[ri] = row;
	}
	for(ci = 0; ci < ncol; ci++)
		tbl_col_geom(tab, ci);
	for(ri = 0; ri < nrow; ri++)
		tbl_row_geom(tab, ri);
	tbl_table_geom(tab);
	return tab;
}

# Upgrade each Roman item in a run to Bold (used for header cells).
tbl_promotebold(head: ref TblItem): ref TblItem
{
	for(it := head; it != nil; it = it.next){
		if(it.fontnum == tbl_fnum(TBL_Roman, TBL_Size10))
			it.fontnum = tbl_fnum(TBL_Bold, TBL_Size10);
	}
	return head;
}

# Render a parsed markdown table at the current insert cursor.  Creates
# a canvas, lays it out, embeds it via `window create`, and records the
# (canvas, source) pair so mddump can round-trip it.
mdrendertable(f: ref File, cells: array of array of string,
	align: array of int, src: string): string
{
	t := f.tk;
	display: ref Draw->Display;
	if(t != nil && t.image != nil)
		display = t.image.display;
	else if(ctxt != nil)
		display = ctxt.display;
	if(display == nil)
		return "no display";
	tab := tbl_build(cells, align);
	if(tab == nil)
		return "empty table";
	err := tbl_loadfonts(display);
	if(err != "")
		return err;
	# rebuild geometry now that fonts are loaded (widths may have been 0
	# during initial cell_geom if fonts weren't yet open)
	for(ri := 0; ri < tab.nrow; ri++)
		for(ci := 0; ci < tab.ncol; ci++)
			tbl_cell_geom(tab.rows[ri].cells[ci]);
	for(ci = 0; ci < tab.ncol; ci++)
		tbl_col_geom(tab, ci);
	for(ri = 0; ri < tab.nrow; ri++)
		tbl_row_geom(tab, ri);
	tbl_table_geom(tab);

	id := f.tablectr;
	f.tablectr = id + 1;
	canv := ".ft.t.table" + string id;
	v := tkcmd(t, "canvas " + canv + " -width " + string tab.width
		+ " -height " + string tab.height);
	if(len v > 0 && v[0] == '!')
		return v;

	err = tbl_create_cells(f, tab, canv);
	if(err != "")
		return err;
	err = tbl_create_border(f, tab, canv);
	if(err != "")
		return err;
	err = tbl_create_rules(f, tab, canv);
	if(err != "")
		return err;

	tkcmd(t, ".ft.t window create insert -window " + canv);
	mdput(f, "\n", DEFTAG);
	f.tables = ref MdTable(canv, src) :: f.tables;
	return "";
}

# Destroy any embedded table canvases and forget them.  Safe to call
# even if f.tables is empty.
mdcleartables(f: ref File)
{
	t := f.tk;
	for(l := f.tables; l != nil; l = tl l){
		m := hd l;
		tkcmd(t, "destroy " + m.canv);
	}
	f.tables = nil;
	f.tablectr = 0;
}

# Look up a canvas path in f.tables by short or long name.  The dump
# stream reports widget paths like ".ft.t.table0"; we compare against
# both the stored path and its trailing component.
mdfindtable(f: ref File, name: string): string
{
	for(l := f.tables; l != nil; l = tl l){
		m := hd l;
		if(m.canv == name)
			return m.src;
		# strip any leading path components: match on last segment
		c := m.canv;
		i := len c;
		while(i > 0 && c[i-1] != '.')
			i--;
		if(c[i:] == name)
			return m.src;
		i = len name;
		while(i > 0 && name[i-1] != '.')
			i--;
		if(name[i:] == c[i:] && c != "" && name != "")
			return m.src;
	}
	return "";
}

# Recognise a standalone markdown image block: the whole line is
# exactly `![alt](path)`.  Returns (1, alt, path) on match, else
# (0, "", "").  Inline images (with surrounding prose) are not
# rendered as embedded widgets - they remain as literal text.
mdimageblock(ln: string)
	: (int, string, string)
{
	n := len ln;
	if(n < 5 || ln[0] != '!' || ln[1] != '[')
		return (0, "", "");
	i := 2;
	while(i < n && ln[i] != ']')
		i++;
	if(i >= n || i+1 >= n || ln[i+1] != '(')
		return (0, "", "");
	altstr := ln[2:i];
	j := i+2;
	while(j < n && ln[j] != ')')
		j++;
	if(j != n-1)
		return (0, "", "");
	path := ln[i+2:j];
	if(path == "")
		return (0, "", "");
	return (1, altstr, path);
}

# Join a parent file's path with a relative image path.  If `file` is
# absolute (starts with '/' or '#') it is returned unchanged.
mdfullname(parent, file: string): string
{
	if(len parent == 0 || (len file > 0 && (file[0] == '/' || file[0] == '#')))
		return file;
	for(i := len parent - 1; i >= 0; i--)
		if(parent[i] == '/')
			return parent[0:i+1] + file;
	return file;
}

mdloadgif(): RImagefile
{
	if(readgif == nil){
		readgif = load RImagefile RImagefile->READGIFPATH;
		if(readgif != nil)
			readgif->init(bufio);
	}
	return readgif;
}

mdloadjpg(): RImagefile
{
	if(readjpg == nil){
		readjpg = load RImagefile RImagefile->READJPGPATH;
		if(readjpg != nil)
			readjpg->init(bufio);
	}
	return readjpg;
}

mdloadpng(): RImagefile
{
	if(readpng == nil){
		readpng = load RImagefile RImagefile->READPNGPATH;
		if(readpng != nil)
			readpng->init(bufio);
	}
	return readpng;
}

mdfiletype(file: string, fd: ref Iobuf): RImagefile
{
	if(len file > 4 && file[len file - 4:] == ".gif")
		return mdloadgif();
	if(len file > 4 && file[len file - 4:] == ".jpg")
		return mdloadjpg();
	if(len file > 5 && file[len file - 5:] == ".jpeg")
		return mdloadjpg();
	if(len file > 4 && file[len file - 4:] == ".png")
		return mdloadpng();
	buf := array[20] of byte;
	if(fd.read(buf, len buf) != len buf)
		return nil;
	fd.seek(big 0, 0);
	if(string buf[0:6] == "GIF87a" || string buf[0:6] == "GIF89a")
		return mdloadgif();
	if(buf[0] == byte 16r89 && buf[1] == byte 'P' && buf[2] == byte 'N' && buf[3] == byte 'G')
		return mdloadpng();
	jpmagic := array[] of {byte 16rFF, byte 16rD8, byte 16rFF, byte 16rE0,
		byte 0, byte 0, byte 'J', byte 'F', byte 'I', byte 'F', byte 0};
	for(i := 0; i < len jpmagic; i++)
		if(jpmagic[i] > byte 0 && buf[i] != jpmagic[i])
			return nil;
	return mdloadjpg();
}

mdtransparency(display: ref Draw->Display, r: ref RImagefile->Rawimage): ref Draw->Image
{
	if(r.transp == 0 || r.nchans != 1)
		return nil;
	i := display.newimage(r.r, display.image.chans, 0, 0);
	if(i == nil)
		return nil;
	pic := r.chans[0];
	npic := len pic;
	mpic := array[npic] of byte;
	index := r.trindex;
	for(j := 0; j < npic; j++)
		if(pic[j] == index)
			mpic[j] = byte 0;
		else
			mpic[j] = byte 16rFF;
	i.writepixels(i.r, mpic);
	return i;
}

# Load an image file.  First tries display.open (Inferno native bitmap
# format), then falls back to GIF / JPEG via the imagefile decoders.
mdloadimage(display: ref Draw->Display, parent, file: string)
	: (ref Draw->Image, ref Draw->Image, string)
{
	path := mdfullname(parent, file);
	im := display.open(path);
	mask: ref Draw->Image;
	if(im != nil)
		return (im, nil, "");

	fd := bufio->open(path, Bufio->OREAD);
	if(fd == nil)
		return (nil, nil, sys->sprint("can't open %s: %r", path));
	mod := mdfiletype(path, fd);
	if(mod == nil)
		return (nil, nil, sys->sprint("unknown image format: %s", path));
	(ri, err) := mod->read(fd);
	if(ri == nil)
		return (nil, nil, sys->sprint("%s: %s", path, err));
	mask = mdtransparency(display, ri);

	if(imageremap == nil){
		imageremap = load Imageremap Imageremap->PATH;
		if(imageremap == nil)
			return (nil, nil, sys->sprint("can't load imageremap: %r"));
	}
	(im, err) = imageremap->remap(ri, display, 1);
	if(im == nil)
		return (nil, nil, sys->sprint("remap %s: %s", path, err));
	return (im, mask, "");
}

# Render a standalone markdown image at the current insert cursor.
# Loads the image, installs it as a Tk image resource, draws it on a
# child canvas of the text widget, embeds the canvas via `window
# create`, and records the (canvas, img, source) triple so mddump can
# round-trip it.
mdrenderimage(f: ref File, alttxt, path, src: string): string
{
	alttxt = nil;
	t := f.tk;
	display: ref Draw->Display;
	if(t != nil && t.image != nil)
		display = t.image.display;
	else if(ctxt != nil)
		display = ctxt.display;
	if(display == nil)
		return "no display";

	parent := "";
	for(k := len f.name - 1; k >= 0; k--)
		if(f.name[k] == '/'){
			parent = f.name[0:k+1];
			break;
		}

	(im, mask, err) := mdloadimage(display, parent, path);
	if(err != "")
		return err;

	id := f.imagectr;
	f.imagectr = id + 1;
	imgname := "brutusimg" + string id;
	canv := ".ft.t.img" + string id;

	v := tkcmd(t, "image create bitmap " + imgname);
	if(len v > 0 && v[0] == '!')
		return v;
	v = tk->putimage(t, imgname, im, mask);
	if(len v > 0 && v[0] == '!'){
		tkcmd(t, "image delete " + imgname);
		return v;
	}
	w := im.r.dx();
	h := im.r.dy();
	v = tkcmd(t, "canvas " + canv + " -width " + string w + " -height " + string h);
	if(len v > 0 && v[0] == '!'){
		tkcmd(t, "image delete " + imgname);
		return v;
	}
	v = tkcmd(t, canv + " create image 0 0 -anchor nw -image " + imgname);
	if(len v > 0 && v[0] == '!'){
		tkcmd(t, "destroy " + canv);
		tkcmd(t, "image delete " + imgname);
		return v;
	}
	tkcmd(t, ".ft.t window create insert -window " + canv);
	mdput(f, "\n", DEFTAG);
	f.images = ref MdImage(canv, imgname, src) :: f.images;
	return "";
}

# Destroy any embedded image canvases (and their backing Tk image
# resources).  Safe to call when f.images is empty.
mdclearimages(f: ref File)
{
	t := f.tk;
	for(l := f.images; l != nil; l = tl l){
		m := hd l;
		tkcmd(t, "destroy " + m.canv);
		tkcmd(t, "image delete " + m.img);
	}
	f.images = nil;
	f.imagectr = 0;
}

# Look up a canvas path in f.images; matches on full path or trailing
# widget component.  Mirrors mdfindtable.
mdfindimage(f: ref File, name: string): string
{
	for(l := f.images; l != nil; l = tl l){
		m := hd l;
		if(m.canv == name)
			return m.src;
		c := m.canv;
		i := len c;
		while(i > 0 && c[i-1] != '.')
			i--;
		if(c[i:] == name)
			return m.src;
	}
	return "";
}

loadfile(f: ref File, file: string): int
{
	f.size = DEFSIZE;
	t := f.tk;
	tkcmd(t, "cursor -image waiting; update");
	r := loadfile1(f, file);
	tkcmd(t, "cursor -default");
	return r;
}

loadfile1(f: ref File, file: string): int
{
	fd := bufio->open(file, Sys->OREAD);
	if(fd == nil)
		return -1;
	(ok, dir) := sys->fstat(fd.fd);
	if(ok < 0){
		fd.close();
		return -1;
	}
	l := int dir.length;
	a := array[l] of byte;
	n := fd.read(a, len a);
	fd.close();
	if(n != len a)
		return -1;
	t := f.tk;
	tkcmd(t, ".ft.t delete 1.0 end");
	mdcleartables(f);
	f.rawview = 0;
	mdinsert(f, string a[0:n]);
	tkcmd(t, ".b.View configure -text Raw");
	dirty(f, 0);
	tkcmd(t, ".ft.t mark set insert 1.0; update");
	return 1;
}

dumpfile(f: ref File, file: string): int
{
	tkcmd(f.tk, "cursor -image waiting");
	r := dumpfile1(f, file);
	tkcmd(f.tk, "cursor -default");
	return r;
}

dumpfile1(f: ref File, file: string): int
{
	if(writefile(f, file) < 0){
		dialog->prompt(ctxt, f.tk.image, "error -fg red",
			"Write file",
			sys->sprint("Can't write %s:\n%r", file),
			0, "Continue"::nil);
		tkcmd(f.tk, FOCUS);
		return -1;
	}
	return 1;
}

writefile(f: ref File, file: string): int
{
	if(file == "")
		return -1;
	fd := bufio->create(file, Sys->OWRITE, 8r666);
	if(fd == nil)
		return -1;

	t := f.tk;
	md: string;
	if(f.rawview)
		md = tkcmd(t, ".ft.t get 1.0 {end - 1 char}");
	else
		md = mddump(f);
	a := array of byte md;
	if(fd.write(a, len a) != len a){
		fd.close();
		return -1;
	}
	if(fd.flush() < 0){
		fd.close();
		return -1;
	}
	fd.close();
	if(file == f.name){
		dirty(f, 0);
		tkcmd(t, UPDATE);
	}
	return 1;
}

shutdown(s: ref Draw->Context, t: ref Tk->Toplevel): int
{
	for(i:=1; i<len files; i++){
		f := files[i];
		if(f.dirty){
			action := confirm(s, t, "file "+nameof(f)+" is dirty", 1);
			case action {
			"cancel" =>
				return 0;
			"exitclean" =>
				if(dumpfile(f, f.name) < 0)
					return 0;
			"exitdirty" =>
				break;
			}
		}
	}
	return 1;
}

nameof(f: ref File): string
{
	s := f.name;
	if(s == "")
		s = "(unnamed)";
	return s;
}

tkcmd(t: ref Tk->Toplevel, s: string): string
{
	res := tk->cmd(t, s);
	if(len res > 0 && res[0] == '!')
		sys->print("%s: tk error executing '%s': %s\n", Name, s, res);
	return res;
}

confirm_cfg := array[] of {
	"frame .f -borderwidth 2 -relief groove -padx 3 -pady 3",
	"frame .f.f",
	"label .f.f.l -text Warning:",
	"label .f.f.m",
	"button .f.exitclean -text {  Write and Proceed  } -width 17w -command {send cmd exitclean}",
	"button .f.exitdirty -text {  Proceed  } -width 17w -command {send cmd exitdirty}",
	"button .f.cancel -text {  Cancel  } -width 17w -command {send cmd cancel}",
	"pack .f.f.l .f.f.m -side left",
	"pack .f.f .f.exitclean .f.exitdirty .f.cancel -padx 10 -pady 10",
	"pack .f",
};

widget(parent: ref Tk->Toplevel, ctxt: ref Draw->Context, cfg: array of string): ref Tk->Toplevel
{
	x := int tk->cmd(parent, ". cget -x");
	y := int tk->cmd(parent, ". cget -y");
	where := sys->sprint("-x %d -y %d ", x+45, y+25);
	(t,nil) := tkclient->toplevel(ctxt, where+SETFONT+" -borderwidth 2 -relief raised", "", tkclient->Plain);
	tkcmds(t, cfg);
	return t;
}

tkcmds(top: ref Tk->Toplevel, a: array of string)
{
	for(i := 0; i < len a; i++)
		tkcmd(top, a[i]);
}

confirm(ctxt: ref Draw->Context, parent: ref Tk->Toplevel, message: string, write: int): string
{
	s := confirm1(ctxt, parent, message, write);
	tkcmd(parent, FOCUS);
	return s;
}

confirm1(ctxt: ref Draw->Context, parent: ref Tk->Toplevel, message: string, write: int): string
{
	t := widget(parent, ctxt, confirm_cfg);
	tkcmd(t, ".f.f.m configure -text '"+message);
	if(write == 0)
		tkcmd(t, "destroy .f.exitclean");
	tkcmd(t, UPDATE);
	tkclient->onscreen(t, "onscreen");
	cmd := chan of string;
	tk->namechan(t, cmd, "cmd");
	tkclient->onscreen(t, "exact");
	tkclient->startinput(t, "ptr"::nil);
	for(;;) alt {
		s := <-t.ctxt.ptr =>
			tk->pointer(t, *s);
		c := <-cmd =>
			return c;
	}
	return <-cmd;
}

getfilename_cfg := array[] of {
	"frame .f",
	"label .f.Message",
	"entry .f.Name -width 25w",
	"button .f.Ok -text {  OK  } -width 14w -command {send cmd ok}",
	"button .f.Browse -text {  Browse  } -width 14w -command {send cmd browse}",
	"button .f.Cancel -text {  Cancel  } -width 14w -command {send cmd cancel}",
	"bind .f.Name <Control-j> {send cmd ok}",
	"pack .f.Message .f.Name .f.Ok .f.Browse .f.Cancel -padx 10 -pady 10",
	"pack .f",
	"focus .f.Name",
};

getfilename(ctxt: ref Draw->Context, parent: ref Tk->Toplevel, message, name: string, browse: int): (string, int)
{
	(s, i) := getfilename1(ctxt, parent, message, name, browse);
	tkcmd(parent, FOCUS);
	return (s, i);
}

getfilename1(ctxt: ref Draw->Context, parent: ref Tk->Toplevel, message, name: string, browse: int): (string, int)
{
	t := widget(parent, ctxt, getfilename_cfg);
	tkcmds(t, getfilename_cfg);

	tkcmd(t, ".f.Message configure -text '"+message);
	tk->cmd(t, ".f.Name insert 0 "+name);
	if(browse == 0)
		tkcmd(t, "destroy .f.Browse");
	tkcmd(t, UPDATE);
	cmd := chan of string;
	tk->namechan(t, cmd, "cmd");
	tkclient->onscreen(t, "exact");
	tkclient->startinput(t, "kbd"::"ptr"::nil);
	for(;;) alt {
		s := <-t.ctxt.kbd =>
			tk->keyboard(t, s);
		s := <-t.ctxt.ptr =>
			tk->pointer(t, *s);
		c := <-cmd =>
			case c {
			"ok" =>
				return (tkcmd(t, ".f.Name get"), 1);
			"cancel" =>
				return ("", 0);
			"browse" =>
				name = tkcmd(t, ".f.Name get");
				(dir, path) := basepath(name);

				pat := list of {
					"* (All files)",
					"*.md (Markdown files)",
					"*.[bm] (Limbo source files)"
				};

				path = selectfile->filename(ctxt, parent.image, message, pat, dir);
				if(path != "")
					name = path;
				tk->cmd(t, ".f.Name delete 0 end; .f.Name insert 0 "+name+";focus .f.Name; update");
				if(path != "")
					return (name, 1);
		}
	}
}

plumbpid: int;
plumbproc(plumbc: chan of (string, string))
{
	plumbpid = sys->pctl(0, nil);

	for(;;){
		msg := Msg.recv();
		if(msg == nil){
			sys->print("Brutus: can't read /chan/plumb.edit: %r\n");
			plumbpid = 0;
			return;
		}
		if(msg.kind != "text"){
			sys->print("Brutus: can't interpret '%s' kind of message\n", msg.kind);
			continue;
		}
		text := string msg.data;
		n := len text;
		addr := "";
		for(j:=0; j<n; j++)
			if(text[j] == ':'){
				addr = text[j+1:];
				break;
			}
		file := text[0:j];
		if(len file>0 && file[0]!='/' && len msg.dir>0){
			if(msg.dir[len msg.dir-1] == '/')
				file = msg.dir+file;
			else
				file = msg.dir+"/"+file;
		}
		plumbc <-= (file, addr);
	}
}

killplumb()
{
	if(plumbed == 0)
		return;
	plumbmsg->shutdown();
	if(plumbpid <= 0)
		return;
	fname := sys->sprint("#p/%d/ctl", plumbpid);
	fd := sys->open(fname, sys->OWRITE);
	if(fd != nil)
		sys->write(fd, array of byte "kill\n", 8);
}

lastpat: string;

execute(cmdwin: ref Tk->Toplevel, f: ref File, cmd: string)
{
	if(len cmd>1 && cmd[len cmd-1]=='\n')
		cmd = cmd[0:len cmd-1];
	if(cmd == "")
		return;
	if(cmd[0] == '/' || cmd[0]=='?'){
		search(cmdwin, f, cmd[1:], cmd[0]=='?', 1);
		return;
	}
	for(i:=0; i<len cmd; i++)
		if(cmd[i]<'0' || '9'<cmd[i]){
			sys->print("bad command %s\n", cmd);
			return;
		}
	t := f.tk;
	line := int cmd;
	if(!nullsel(t))
		tkcmd(t, NOSEL);
	tkcmd(t, ".ft.t tag add sel "+string line+".0 {"+string line+".0 lineend+1char}");
	tkcmd(t, ".ft.t mark set insert "+string line+".0; .ft.t see insert;update");
}

search(cmdwin: ref Tk->Toplevel, f: ref File, pat: string, backwards, uselast: int)
{
	t := f.tk;
	if(pat == nil)
		pat = lastpat;
	else if(uselast)
		lastpat = pat;
	if(pat == nil){
		error(cmdwin, "no pattern");
		return;
	}
	cmd := ".ft.t search ";
	if(backwards)
		cmd += "-backwards ";
	p := "";
	for(i:=0; i<len pat; i++){
		if(pat[i]== '\\' || pat[i]=='{')
			p[len p] = '\\';
		p[len p] = pat[i];
	}
	cmd += "{"+p+"} ";
	null := nullsel(t);
	if(null)
		cmd += "insert";
	else if(backwards)
		cmd += "sel.first";
	else
		cmd += "sel.last";
	s := tk->cmd(t, cmd);
	if(s == "")
		error(cmdwin, "not found");
	else{
		if(!null)
			tkcmd(t, NOSEL);
		tkcmd(t, ".ft.t tag add sel "+s+" "+s+"+"+string len pat+"chars");
		tkcmd(t, ".ft.t mark set insert "+s+";.ft.t see insert; update");
	}
}

showaddr(f: ref File, addr: string)
{
	 if(addr=="")
		return;
	t := f.tk;
	if(addr[0]=='#' || ('0'<=addr[0] && addr[0]<='9')){
		if(!nullsel(t))
			tkcmd(t, NOSEL);
		if(addr[0] == '#'){
			addr = addr[1:];
			tkcmd(t, ".ft.t mark set insert {1.0+"+addr+"char}; .ft.t see insert;update");
		}else{
			tkcmd(t, ".ft.t tag add sel "+addr+".0 {"+addr+".0 lineend+1char}");
			tkcmd(t, ".ft.t mark set insert "+addr+".0; .ft.t see insert;update");
		}
	}
}

error(cmdwin: ref Tk->Toplevel, err: string)
{
	if(cmdwin == nil)
		return;
	tkcmd(cmdwin, ".ft.t insert end '?"+err+"\n");
	if(!nullsel(cmdwin))
		tkcmd(cmdwin, NOSEL);
	tkcmd(cmdwin, ".ft.t mark set insert end");
	tkcmd(cmdwin, ".ft.t mark set typingstart end; update");
}
