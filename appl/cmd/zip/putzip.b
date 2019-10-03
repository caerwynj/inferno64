implement Putzip;

include "sys.m";
	sys: Sys;
	sprint: import sys;
include "draw.m";
include "arg.m";
include "bufio.m";
	bufio: Bufio;
	Iobuf: import bufio;
include "string.m";
	str: String;
include "lists.m";
	lists: Lists;
include "filter.m";
	deflate: Filter;
include "zip.m";
	zip: Zip;
	Fhdr, CDFhdr, Endofcdir: import zip;

Putzip: module {
	init:	fn(nil: ref Draw->Context, args: list of string);
};

dflag: int;
vflag: int;
pflag: int;

zb: ref Iobuf;
fileheaders: list of ref (big, ref Fhdr);

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	arg := load Arg Arg->PATH;
	bufio = load Bufio Bufio->PATH;
	str = load String String->PATH;
	lists = load Lists Lists->PATH;
	deflate = load Filter Filter->DEFLATEPATH;
	deflate->init();
	zip = load Zip Zip->PATH;
	zip->init();

	arg->init(args);
	arg->setusage(arg->progname()+" [-dvp] zipfile [path ...]");
	while((c := arg->opt()) != 0)
		case c {
		'd' =>	zip->dflag = dflag++;
		'v' =>	vflag++;
		'p' =>	pflag++;
		* =>	arg->usage();
		}
	args = arg->argv();
	if(len args == 0)
		arg->usage();

	zfd := sys->create(hd args, Sys->OWRITE|Sys->OEXCL, 8r666);
	if(zfd == nil)
		fail(sprint("create %q: %r", hd args));
	zb = bufio->fopen(zfd, Sys->OWRITE);
	if(zb == nil)
		fail(sprint("fopen: %r"));

	args = tl args;
	if(args == nil) {
		b := bufio->fopen(sys->fildes(0), Bufio->OREAD);
		if(b == nil)
			fail(sprint("fopen: %r"));
		for(;;) {
			s := b.gets('\n');
			if(s == nil)
				break;
			if(s != nil && s[len s-1] == '\n')
				s = s[:len s-1];
			put(s, 0);
		}
	} else {
		for(; args != nil; args = tl args)
			put(hd args, 1);
	}

	eocd := ref Endofcdir (0, 0, len fileheaders, len fileheaders, big 0, big 0, nil);
	eocd.cdiroffset = zb.offset();
	for(l := lists->reverse(fileheaders); l != nil; l = tl l) {
		(foff, f) := *hd l;
		cdf := CDFhdr.mk(f, foff);
		buf := cdf.pack();
		if(zb.write(buf, len buf) != len buf)
			fail(sprint("writing central directory file header: %r"));
		eocd.cdirsize += big len buf;
	}

	ebuf := eocd.pack();
	if(zb.write(ebuf, len ebuf) != len ebuf || zb.flush() == Bufio->ERROR)
		fail(sprint("writing end of central directory: %r"));
}

put(s: string, recur: int)
{
	if(s == nil)
		warn("refusing to add empty filename");

	fd := sys->open(s, Sys->OREAD);
	if(fd == nil)
		return warn(sprint("open %q: %r, skipping", s));
	(ok, dir) := sys->fstat(fd);
	if(ok < 0)
		return warn(sprint("fstat %q: %r, skipping", s));

	if(dir.mode & Sys->DMDIR)
		putdir(s, fd, dir, recur);
	else
		putfile(s, fd, dir);
}

mkfhdr(mtime: int, s: string): ref Fhdr
{
	f := ref Fhdr;
	f.versneeded = 20;
	f.flags = zip->Futf8;
	f.comprmethod = zip->Mdeflate;
	if(pflag)
		f.comprmethod = zip->Mplain;
	f.mtime = mtime;
	f.filename = zip->sanitizepath(s);
	f.comprsize = big 0;
	f.uncomprsize = big 0;
	f.crc32 = big 0;
	return f;
}

putdir(s: string, fd: ref Sys->FD, dir: Sys->Dir, recur: int)
{
	if(s[len s-1] != '/')
		s[len s] = '/';
	f := mkfhdr(dir.mtime, s);
	foff := zb.offset();
	fbuf := f.pack();
	if(zb.write(fbuf, len fbuf) != len fbuf)
		fail(sprint("write: %r"));
	fileheaders = ref (foff, f)::fileheaders;
	if(vflag)
		sys->print("%s\n", s);

	if(!recur)
		return;

	for(;;) {
		(n, dirs) := sys->dirread(fd);
		if(n < 0)
			return warn(sprint("listing %q: %r", s));
		if(n == 0)
			break;
		for(i := 0; i < len dirs; i++)
			put(s+dirs[i].name, recur);
	}
}

putfile(s: string, fd: ref Sys->FD, dir: Sys->Dir)
{
	f := mkfhdr(dir.mtime, s);
	if(vflag)
		sys->print("%s\n", s);

	foff := zb.offset();

	# write partially filled header, prevents fs holes
	fbuf := f.pack();
	if(zb.write(fbuf, len fbuf) != len fbuf)
		fail(sprint("write: %r"));

	if(f.comprmethod == zip->Mplain)
		putplain(fd, f);
	else
		putdeflate(fd, f, s);

	# rewrite file header, now complete.  restore offset afterwards
	off := zb.offset();
	fbuf = f.pack();
	if(zb.seek(foff, Bufio->SEEKSTART) < big 0)
		fail(sprint("seek to file header: %r"));
	if(zb.write(fbuf, len fbuf) != len fbuf)
		fail(sprint("write %q file header: %r", s));
	if(zb.seek(off, Bufio->SEEKSTART) < big 0)
		fail(sprint("seek to past compressed contents: %r"));

	fileheaders = ref (foff, f)::fileheaders;
}

putplain(fd: ref Sys->FD, f: ref Fhdr)
{
	crc := ~0;

	buf := array[sys->ATOMICIO] of byte;
	for(;;) {
		n := sys->read(fd, buf, len buf);
		if(n == 0)
			break;
		if(n < 0)
			fail(sprint("read: %r"));
		if(zb.write(buf, n) != n)
			fail(sprint("write: %r"));
		crc = zip->crc32(crc, buf[:n]);
		f.uncomprsize += big n;
	}
	f.comprsize = f.uncomprsize;
	f.crc32 = big ~crc;
}

putdeflate(fd: ref Sys->FD, f: ref Fhdr, s: string)
{
	rqc := deflate->start("");
	pick r := <-rqc {
	Start =>	;
	* =>	fail(sprint("bad first filter msg"));
	}

	crc := ~0;
Filter:
	for(;;) pick rq := <-rqc {
	Fill =>
		n := sys->read(fd, rq.buf, len rq.buf);
		if(n >= 0)
			crc = zip->crc32(crc, rq.buf[:n]); 
		rq.reply <-= n;
		if(n < 0)
			fail(sprint("reading %q: %r", s));
		f.uncomprsize += big n;
	Result =>
		if(zb.write(rq.buf, len rq.buf) != len rq.buf)
			fail(sprint("writing %q compressed: %r", s));
		f.comprsize += big len rq.buf;
		rq.reply <-= 0;
	Finished =>
		if(len rq.buf != 0)
			fail(sprint("deflate leftover bytes..."));
		break Filter;
	Info =>
		say("deflate: "+rq.msg);
	Error =>
		fail("deflate error: "+rq.e);
	}

	f.crc32 = big ~crc;
}

warn(s: string)
{
	sys->fprint(sys->fildes(2), "%s\n", s);
}

say(s: string)
{
	if(dflag)
		warn(s);
}

fail(s: string)
{
	warn(s);
	raise "fail:"+s;
}
