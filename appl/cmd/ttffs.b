implement Ttffs;

# serve (over styx) ttf's as inferno/plan 9 (sub)fonts in arbitrary sizes.
# fonts and subfonts are not listed in the directory, but can be walked to.
# the font and subfont files are generated on the fly.
# subfonts contain at most 128 glyphs.
# at first read of a font, it is parsed and its glyph ranges determined.
#
# for each font file (fontpath/*.ttf) the following files are served:
# <name>.<style>.<size>.font
# <name>.<style>.<size>.<index>
#
# the second form are subfonts, index starts at 1.  index 1 always has the single char 0.

include "sys.m";
	sys: Sys;
	sprint: import sys;
include "draw.m";
	draw: Draw;
	Display, Rect, Point, Image: import draw;
include "arg.m";
include "bufio.m";
	bufio: Bufio;
	Iobuf: import bufio;
include "string.m";
	str: String;
include "styx.m";
	styx: Styx;
	Tmsg, Rmsg: import styx;
include "styxservers.m";
	styxservers: Styxservers;
	Styxserver, Fid, Navigator, Navop: import styxservers;
	nametree: Nametree;
	Tree: import nametree;
	Enotfound: import styxservers;
include "freetype.m";
	ft: Freetype;
	Face, Glyph: import ft;
include "readdir.m";
	readdir: Readdir;
include "tables.m";
	tables: Tables;
	Table, Strhash: import tables;

Ttffs: module {
	init:	fn(nil: ref Draw->Context, args: list of string);
};

dflag: int;
fontpath := "/fonts/ttf";
mtpt: con "/mnt/ft";

disp: ref Display;
srv: ref Styxserver;
styles := array[] of {"r", "i", "b", "ib"};

Qroot, Qindex: con iota;
idgen := 2;

Font: adt {
	sane,
	family:	string;
	ranges:	array of ref (int, int);	# sorted, start-end inclusive
	styles:	cyclic array of ref Style;	# indexed by Face.style
};

Style: adt {
	f:	ref Font;
	dir:	ref Sys->Dir;
	path:	string;
	fc:	ref Face;
	sizes:	cyclic ref Table[cyclic ref Size];	# size
};

Size: adt {
	id:	int;	# qid.path.  subfonts are id+Size.range
	st:	cyclic ref Style;
	range:	int;	# index for Font.ranges.  0 is .font, 1 is first in range
	size:	int;
	dat:	array of byte;
	nuse:	int;
};

fonts: ref Strhash[ref Font];	# family
sanefonts: ref Strhash[ref Font];  # sane name
sizes: ref Table[ref Size];	# qid.path


init(ctxt: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	if(ctxt == nil || (disp = ctxt.display) == nil)
		fail("no display");
	draw = load Draw Draw->PATH;
	arg := load Arg Arg->PATH;
	bufio = load Bufio Bufio->PATH;
	str = load String String->PATH;
	ft = load Freetype Freetype->PATH;
	styx = load Styx Styx->PATH;
	styx->init();
	styxservers = load Styxservers Styxservers->PATH;
	styxservers->init(styx);
	nametree = load Nametree Nametree->PATH;
	nametree->init();
	readdir = load Readdir Readdir->PATH;
	tables = load Tables Tables->PATH;

	sys->pctl(Sys->NEWPGRP, nil);

	Mflag := 0;

	arg->init(args);
	arg->setusage(arg->progname()+" [-dM] [-p fontpath]");
	while((c := arg->opt()) != 0)
		case c {
		'd' =>	dflag++;
		'p' =>	fontpath = arg->arg();
		'M' =>	Mflag++;
		* =>	arg->usage();
		}
	args = arg->argv();
	if(args != nil)
		arg->usage();

	fonts = fonts.new(11, nil);
	sanefonts = sanefonts.new(11, nil);
	sizes = sizes.new(11, nil);

	fds := array[2] of ref Sys->FD;
	fd := sys->fildes(0);
	if(!Mflag) {
		if(sys->pipe(fds) < 0)
			fail(sprint("pipe: %r"));
		fd = fds[0];
	}

	navc := chan of ref Navop;
	spawn navigator(navc);
	msgc: chan of ref Tmsg;
	(msgc, srv) = Styxserver.new(fd, Navigator.new(navc), big Qroot);

	if(Mflag)
		return main(msgc);

	spawn main(msgc);
	if(sys->mount(fds[1], nil, mtpt, sys->MAFTER, nil) < 0)
		fail(sprint("mount: %r"));
	return;
}

xwarn(s: string): array of ref (int, int)
{
	warn(s);
	return nil;
}

# read cached glyph ranges available in the font
readranges(path: string, mtime: int): array of ref (int, int)
{
	fd := sys->open(path, Sys->OREAD);
	if(fd == nil)
		return xwarn(sprint("open %q: %r", path));
	(ok, d) := sys->fstat(fd);
	if(ok != 0)
		return xwarn(sprint("fstat %q: %r", path));
	if(d.mtime <= mtime)
		return xwarn(sprint("%q: older than ttf, ignoring", path));
	if(sys->readn(fd, buf := array[int d.length] of byte, len buf) != len buf)
		return xwarn(sprint("readn %q: %r", path));
	s := string buf;
	r: list of ref (int, int);
	for(l := sys->tokenize(s, "\n").t1; l != nil; l = tl l) {
		x := sys->tokenize(hd l, " ").t1;
		if(len x != 2)
			return xwarn(sprint("%q: bad glyph range line: %q", path, hd l));
		(a, rem0) := str->toint(hd x, 10);
		(b, rem1) := str->toint(hd tl x, 10);
		if(rem0 != nil || rem1 != nil || b < a || b > 64*1024 || r != nil && a <= (hd r).t1)
			return xwarn(sprint("%q: invalid glyph range: %q", path, hd l));
		r = ref (a, b)::r;
	}
	return l2a(rev(r));
}

genranges(f: ref Face): array of ref (int, int)
{
	r := list of {ref (0, 0)};
	max := 64*1024;
	i := 1;
	while(i < max) {
		for(; i < max && !f.haschar(i); i++)
			{}
		s := i;
		for(; i < max && f.haschar(i); i++)
			{}
		e := i;
		while(s < e) {
			n := e-s;
			if(n > 128)
				n = 128;
			if(dflag > 1) say(sprint("range %d-%d", s, s+n-1));
			r = ref (s, s+n-1)::r;
			s += n;
		}
	}
	return l2a(rev(r));
}

indexdat: array of byte;
indexmtime: int;
mkindex(): array of byte
{
say("mkindex0");
	(ok, dir) := sys->stat(fontpath);
	if(ok != 0) {
		warn(sprint("stat %q: %r", fontpath));
		return nil;
	}
	if(indexdat != nil && indexmtime == dir.mtime)
		return indexdat;

say("mkindex1");
	nfonts := fonts.new(11, nil);
	nsanefonts := sanefonts.new(11, nil);
	nsizes := sizes.new(11, nil);

	(a, n) := readdir->init(fontpath, Readdir->NONE);
	if(n < 0)
		return nil;
	for(i := 0; i < len a; i++) {
		if(!suffix(".ttf", a[i].name) && !suffix(".otf", a[i].name))
			continue;
		name := a[i].name;
		name = name[:len name-len ".ttf"];

		path := sprint("%s/%s", fontpath, a[i].name);
		fc := ft->newface(path, 0);
		if(fc == nil) {
			warn(sprint("newface %q: %r", path));
			continue;
		}

if(dflag) say(sprint("have face, nfaces=%d index=%d style=%d height=%d ascent=%d familyname=%q stylename=%q",
			fc.nfaces, fc.index, fc.style, fc.height, fc.ascent, fc.familyname, fc.stylename));

		rpath := sprint("%s/ranges.%s", fontpath, name);
		ranges := readranges(rpath, a[i].mtime);
		if(ranges == nil) {
			ranges = genranges(fc);
			s := "";
			for(j := 0; j < len ranges; j++)
				s += sprint("%d %d\n", ranges[j].t0, ranges[j].t1);
			fd := sys->create(rpath, Sys->OWRITE, 8r666);
			if(fd == nil || sys->write(fd, buf := array of byte s, len buf) != len buf)
				warn(sprint("create or write %q: %r", rpath));
		}

		f := nfonts.find(fc.familyname);
		if(f == nil) {
			sane := sanitize(fc.familyname);
			while(nsanefonts.find(sane) != nil)
				sane += "0";
			f = ref Font(sane, fc.familyname, ranges, array[len styles] of ref Style);
			nfonts.add(f.family, f);
			nsanefonts.add(f.sane, f);
		} else if(f.styles[fc.style] != nil) {
			warn(sprint("duplicate style %#q", styles[fc.style]));
			continue;
		}
		st := ref Style(f, ref dir, path, fc, nil);
		st.sizes = st.sizes.new(11, nil);
		f.styles[st.fc.style] = st;
		for(l := tabitems(st.sizes); l != nil; l = tl l) {
			(nil, size) := *hd l;
			nsizes.add(size.id, size);
		}
	}
	s := "";
	for(l := strtabitems(nfonts); l != nil; l = tl l) {
		f := (hd l).t1;
		st := "";
		for(i = 0; i < len styles; i++)
			if(f.styles[i] != nil)
				st += ","+styles[i];
		s += sprint("%q %q\n", f.sane, sprint(".%s.%s.2-", f.family, st[1:]));
	}

	# ensure we don't mkindex immediately after writing ranges files
	(ok, dir) = sys->stat(fontpath);
	if(ok != 0) {
		warn(sprint("stat: %q: %r", fontpath));
		return nil;
	}

	fonts = nfonts;
	sanefonts = nsanefonts;
	sizes = nsizes;
	indexdat = array of byte s;
	indexmtime = dir.mtime;
	return indexdat;
}

sanitize(s: string): string
{
	s = str->tolower(s);
	r: string;
	for(i := 0; i < len s; i++)
		case c := s[i] {
		' ' or '\t' or '-' =>
			if(r != nil && r[len r-1] != '-')
				r[len r] = '-';
		'.' =>	{}
		* =>	r[len r] = c;
		}
	return r;
}

mkname(s: ref Size): string
{
	st := s.st;
	fc := st.fc;
	f := st.f;
	if(s.range == 0)
		return sprint("%s.%s.%d.font", f.sane, styles[fc.style], s.size);
	return sprint("%s.%s.%d.%d", f.sane, styles[fc.style], s.size, s.range);
}

mkdat(f: ref Size): array of byte
{
	if(f.dat == nil) {
		if(f.range == 0)
			f.dat = mkfont(f);
		else
			f.dat = mksubfont(f);
	}
	return f.dat;
}

mkfont(sz: ref Size): array of byte
{
	f := sz.st.f;
	fc := sz.st.fc;
	fc.setcharsize(sz.size<<6, 0, 0);
	s := sprint("%d %d\n", fc.height, fc.ascent);
	for(i := 0; i < len f.ranges; i++) {
		(a, b) := *f.ranges[i];
		s += sprint("0x%04x\t0x%04x\t%q\n", a, b, sprint("%s.%s.%d.%d", f.sane, styles[fc.style], sz.size, i+1));
	}
	return array of byte s;
}

mksubfont(sz: ref Size): array of byte
{
	(s, l) := *sz.st.f.ranges[sz.range-1];
	fc := sz.st.fc;
	fc.setcharsize(sz.size<<6, 0, 0);

	imgs := array[l+1-s] of ref Image;
	n := l+1-s;
	width := 0;
	left := array[len imgs+1] of {* => 0};
	advance := array[len imgs+1] of {* => 0};
	for(i := 0; i < n; i++) {
		c := s+i;
		g := fc.loadglyph(c);
		if(g == nil)
			fail(sprint("no glyph for %c (%#x)", c, c));
if(dflag) say(sprint("glyph %#x, width=%d height=%d top=%d left=%d advance=%d,%d", c, g.width, g.height, g.top, g.left, g.advance.x>>6, g.advance.y>>6));
		r := Rect((0,0), (g.width, fc.height));
		img := imgs[i] = disp.newimage(r, Draw->GREY8, 0, Draw->Black);
		gr: Rect;
		gr.min = (0,fc.ascent-g.top);
		gr.max = gr.min.add((g.width, g.height));
		img.writepixels(gr, g.bitmap);

		width += g.width;
		left[i] = g.left;
		advance[i] = g.advance.x>>6;
	}

	oimghdr := 0;
	obuf := oimghdr + 5*12;
	osubfhdr := obuf + fc.height*width;
	ochars := osubfhdr + 3*12;
	oend := ochars + (len imgs+1)*6;
	buf := array[oend] of byte;

	fontr := Rect((0,0), (width,fc.height));
	fontimg := disp.newimage(fontr, Draw->GREY8, 0, Draw->Black);
	buf[oimghdr:] = sys->aprint("%11s %11d %11d %11d %11d ", "k8", 0, 0, fontr.max.x, fontr.max.y);
	x := 0;
	buf[osubfhdr:] = sys->aprint("%11d %11d %11d ", len imgs, fc.height, fc.ascent);
	o := ochars;
	for(i = 0; i < len imgs+1; i++) {
		if(i < len imgs)
			img := imgs[i];
		buf[o++] = byte (x>>0);
		buf[o++] = byte (x>>8);
		buf[o++] = byte 0;		# top
		buf[o++] = byte fc.height;	# bottom
		buf[o++] = byte left[i];	# left
		if(img == nil) {
			buf[o++] = byte 0;	# width
			break;
		}
		buf[o++] = byte advance[i];	# width
		r := fontr;
		r.min.x = x;
		fontimg.draw(r, disp.white, img, Point(0,0));
		x += img.r.dx();
	}
	if(o != len buf)
		raise "bad pack";
	r := fontimg.readpixels(fontimg.r, buf[obuf:]);
	if(r != osubfhdr-obuf)
		fail(sprint("readpixels, got %d, expected %d: %r", r, osubfhdr-obuf));
	return buf;
}

main(msgc: chan of ref Tmsg)
{
	sys->pctl(Sys->FORKNS, nil);
more:
	for(;;) {
		mm := <-msgc;
		if(mm == nil)
			break more;
		pick m := mm {
		Readerror =>
			warn("read: "+m.error);
			break more;
		* =>
			handle(mm);
			pick x := mm {
			Clunk or
			Remove =>
				cacheclean();
			}
		}
	}
	killgrp(pid());
}

cacheclean()
{
	for(k := tabitems(sizes); k != nil; k = tl k)
		(hd k).t1.nuse = 0;
	for(l := srv.allfids(); l != nil; l = tl l) {
		fid := hd l;
		f := sizes.find(int fid.path);
		if(fid.isopen)
			f.nuse++;
	}
	for(k = tabitems(sizes); k != nil; k = tl k) {
		sz := (hd k).t1;
		if(sz.nuse == 0 && sz.dat != nil) {
			if(dflag) say(sprint("freeing %s.%s.%d.%d", sz.st.f.sane, styles[sz.st.fc.style], sz.size, sz.range));
			sz.dat = nil;
		}
	}
}

navigator(navc: chan of ref Navop)
{
	for(;;)
		navigate(<-navc);
}

navreply(op: ref Navop, d: ref Sys->Dir, err: string)
{
	op.reply <-= (d, err);
}

navigate(op: ref Navop)
{
	pick x := op {
	Stat =>
		case int x.path {
		Qroot =>
			navreply(x, ref dirroot(), nil);
		Qindex =>
			navreply(x, ref dirindex(), nil);
		* =>
			mkindex();  # ensure up to date index
			f := sizes.find(int x.path);
			if(f == nil)
				return navreply(x, nil, sprint("missing Size for qid.path %bd/%#bx", x.path, x.path));
			d := ref dir(mkname(f), int x.path, 8r444, len mkdat(f), 0);
			navreply(x, d, nil);
		}
	Walk =>
		if(x.name == "..")
			return navreply(x, ref dirroot(), nil);
		if(x.path != big Qroot)
			return navreply(x, nil, Enotfound);

		if(x.name == "index")
			return navreply(x, ref dirindex(), nil);

		mkindex();  # ensure up to date index
		name, style, size, suf: string;
		s := x.name;
		(s, suf) = str->splitstrr(s, ".");
		if(s != nil)
			(s, size) = str->splitstrr(s[:len s-1], ".");
		if(s != nil)
			(name, style) = str->splitstrr(s[:len s-1], ".");
		if(name == nil)
			return navreply(x, nil, Enotfound);
		name = name[:len name-1];
if(dflag) say(sprint("walk, name %q, style %q, size %q, suf %q", name, style, size, suf));

		# format is good
		f := sanefonts.find(name);
		if(f == nil)
			return navreply(x, nil, "no such font");
		sti := find(styles, style);
		if(sti < 0 || f.styles[sti] == nil)
			return navreply(x, nil, "no such style");
		(szs, rem) := str->toint(size, 10);
		if(rem != nil)
			return navreply(x, nil, Enotfound);
		if(szs <= 1)
			return navreply(x, nil, "no such size");

		r := 0;
		if(suf != "font") {
			(r, rem) = str->toint(suf, 10);
			if(rem != nil || r <= 0 || r > len f.ranges)
				return navreply(x, nil, "no such range");
		}

		st := f.styles[sti];
		xsz := st.sizes.find(szs);
		if(xsz == nil) {
			xsz = ref Size(idgen++, st, 0, szs, nil, 0);
			sizes.add(xsz.id, xsz);
			for(i := 0; i < len f.ranges; i++) {
				ssz := ref Size(idgen++, st, 1+i, szs, nil, 0);
				sizes.add(ssz.id, ssz);
			}
			st.sizes.add(xsz.size, xsz);
		}
		sz := sizes.find(xsz.id+r);
		navreply(x, ref dir(x.name, sz.id, 8r444, len mkdat(sz), 0), nil);

	Readdir =>
		dirs := array[] of {ref dirindex()};
		s := x.offset;
		if(s > len dirs)
			s = len dirs;
		e := x.offset+x.count;
		if(e > len dirs)
			e = len dirs;
		while(s < e)
			navreply(x, dirs[s++], nil);
		navreply(x, nil, nil);
	}
}

handle(mm: ref Tmsg)
{
	pick m := mm {
	Read =>
		ff := srv.getfid(m.fid);
		if(ff == nil || ff.path == big Qroot || !ff.isopen)
			break;

		if(ff.path == big Qindex)
			dat := mkindex();
		else {
			f := sizes.find(int ff.path);
			if(f == nil) {
				srv.reply(ref Rmsg.Error(m.tag, "size not found?"));
				return;
			}
			dat = mkdat(f);
		}
		srv.reply(styxservers->readbytes(m, dat));
		return;
	}
	srv.default(mm);
}

dirroot(): Sys->Dir
{
	return dir(".", Qroot, 8r555|Sys->DMDIR, 0, 0);
}

dirindex(): Sys->Dir
{
	mtime := 0;
	(ok, d) := sys->stat(fontpath);
	if(ok == 0)
		mtime = d.mtime;
	return dir("index", Qindex, 8r444, 0, mtime);
}

dir(name: string, path, mode, length, mtime: int): Sys->Dir
{
	d := sys->zerodir;
	d.name = name;
	d.uid = d.gid = "ttffs";
	d.qid.path = big path;
	d.qid.qtype = Sys->QTFILE;
	if(mode&Sys->DMDIR)
		d.qid.qtype = Sys->QTDIR;
	d.mtime = d.atime = mtime;
	d.mode = mode;
	d.length = big length;
	return d;
}

strtabitems[T](t: ref Strhash[T]): list of ref (string, T)
{
	r: list of ref (string, T);
	for(i := 0; i < len t.items; i++)
		for(l := t.items[i]; l != nil; l = tl l)
			r = ref hd l::r;
	return r;
}

tabitems[T](t: ref Table[T]): list of ref (int, T)
{
	r: list of ref (int, T);
	for(i := 0; i < len t.items; i++)
		for(l := t.items[i]; l != nil; l = tl l)
			r = ref hd l::r;
	return r;
}

find(a: array of string, s: string): int
{
	for(i := 0; i < len a; i++)
		if(a[i] == s)
			return i;
	return -1;
}

suffix(suf, s: string): int
{
	return len s >= len suf && suf == s[len s-len suf:];
}

pid(): int
{
	return sys->pctl(0, nil);
}

killgrp(pid: int)
{
	sys->fprint(sys->open(sprint("/prog/%d/ctl", pid), Sys->OWRITE), "killgrp");
}

rev[T](l: list of T): list of T
{
	r: list of T;
	for(; l != nil; l = tl l)
		r = hd l::r;
	return r;
}

l2a[T](l: list of T): array of T
{
	a := array[len l] of T;
	i := 0;
	for(; l != nil; l = tl l)
		a[i++] = hd l;
	return a;
}

fd2: ref Sys->FD;
warn(s: string)
{
	if(fd2 == nil)
		fd2 = sys->fildes(2);
	sys->fprint(fd2, "%s\n", s);
}

say(s: string)
{
	if(dflag)
		warn(s);
}

fail(s: string)
{
	warn(s);
	killgrp(pid());
	raise "fail:"+s;
}
