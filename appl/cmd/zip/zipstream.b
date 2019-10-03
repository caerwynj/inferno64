# rewrite zip file, putting central directory at the front of the file.

implement Zipstream;

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
include "filter.m";
	deflate: Filter;
include "zip.m";
	zip: Zip;
	Fhdr, CDFhdr, Endofcdir: import zip;

Zipstream: module {
	init:	fn(nil: ref Draw->Context, args: list of string);
};

dflag: int;
oflag: int;

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	arg := load Arg Arg->PATH;
	bufio = load Bufio Bufio->PATH;
	str = load String String->PATH;
	deflate = load Filter Filter->DEFLATEPATH;
	deflate->init();
	zip = load Zip Zip->PATH;
	zip->init();

	arg->init(args);
	arg->setusage(arg->progname()+" [-d] [-o] zipfile");
	while((c := arg->opt()) != 0)
		case c {
		'd' =>	zip->dflag = dflag++;
		'o' =>	oflag++;
		}
	args = arg->argv();
	if(len args != 1)
		arg->usage();

	fd := sys->open(hd args, Sys->OREAD);
	if(fd == nil)
		fail(sprint("open: %r"));

	(eocd, cdfhdrs, err) := zip->open(fd);
	if(err != nil)
		fail("parsing zip: "+err);

	if(oflag) {
		files := readfiles();
		n := array[len cdfhdrs] of ref CDFhdr;
		for(i := 0; i < len files; i++) {
			j := find(cdfhdrs, files[i]);
			if(j < 0)
				fail(sprint("%#q not in zip file or specified twice", files[i]));
			n[i] = cdfhdrs[j];
			cdfhdrs[j] = nil;
		}
		for(j := 0; j < len cdfhdrs; j++)
			if(cdfhdrs[j] != nil)
				n[i++] = cdfhdrs[j];
		cdfhdrs = n;
	}

	zb := bufio->fopen(sys->fildes(1), bufio->OWRITE);
	if(zb == nil)
		fail(sprint("fopen: %r"));

	# calculate size of cdfhdrs
	o := big 0;
	for(i := 0; i < len cdfhdrs; i++)
		o += big len cdfhdrs[i].pack();
	cdsz := o;

	eocd.cdirsize = cdsz;
	eocd.cdiroffset = big 0;
	o += big len eocd.pack();

	# fix the offsets in the cdfhdrs & fhdrs, store original offsets
	origoff := array[len cdfhdrs] of big;
	fhdrs := array[len cdfhdrs] of ref Fhdr;
	for(i = 0; i < len fhdrs; i++) {
		cdf := cdfhdrs[i];
		f: ref Fhdr;
		(f, err) = Fhdr.read(fd, cdf.reloffset);
		if(err != nil)
			fail("reading local file header: "+err);
		origoff[i] = f.dataoff;
		cdf.reloffset = o;
		fhdrs[i] = Fhdr.mk(cdf);
		o += big len fhdrs[i].pack()+fhdrs[i].comprsize;
	}

	# write the cdfhdrs
	for(i = 0; i < len cdfhdrs; i++) {
		if(zb.write(buf := cdfhdrs[i].pack(), len buf) != len buf)
			fail(sprint("write: %r"));
	}
	# a copy of the end of central directory structure (to keep other zip code happy)
	if(zb.write(buf := eocd.pack(), len buf) != len buf)
		fail(sprint("write: %r"));

	# write the fhdrs & file contents
	for(i = 0; i < len fhdrs; i++) {
		if(zb.write(buf = fhdrs[i].pack(), len buf) != len buf || copyrange(fd, origoff[i], fhdrs[i].comprsize, zb) < 0)
			fail(sprint("write: %r"));
	}

	if(zb.offset() != o)
		fail(sprint("inconsitent offset after rewriting central directory and files, expected offset %bd, saw %bd", o, zb.offset()));

	# write the eocd, this one is typically found by code parsing the zip file
	if(zb.write(buf = eocd.pack(), len buf) != len buf || zb.flush() == bufio->ERROR)
		fail(sprint("write: %r"));
}

readfiles(): array of string
{
	b := bufio->fopen(sys->fildes(0), bufio->OREAD);
	if(b == nil)
		fail(sprint("fopen: %r"));
	l: list of string;
	for(;;) {
		s := b.gets('\n');
		if(s == nil)
			break;
		if(s[len s-1] == '\n')
			s = s[:len s-1];
		l = s::l;
	}
	f := array[len l] of string;
	i := len f-1;
	for(; l != nil; l = tl l)
		f[i--] = hd l;
	return f;
}

find(h: array of ref CDFhdr, s: string): int
{
	for(i := 0; i < len h; i++)
		if(h[i] != nil && h[i].filename == s)
			return i;
	return -1;
}

copyrange(fd: ref Sys->FD, off: big, n: big, zb: ref Iobuf): int
{
	buf := array[sys->ATOMICIO] of byte;
	while(n > big 0) {
		if(n > big len buf)
			nn := len buf;
		else
			nn = int n;
		r := preadn(fd, buf, nn, off);
		if(r < 0)
			return -1;
		else if(r != nn) {
			sys->werrstr("short read");
			return -1;
		}
		if(zb.write(buf, r) != r)
			return -1;
		off += big r;
		n -= big r;
	}
	return 0;
}

preadn(fd: ref Sys->FD, buf: array of byte, n: int, off: big): int
{
	org := n;
	while(n > 0) {
		nn := sys->pread(fd, buf, n, off);
		if(nn < 0)
			return nn;
		if(nn == 0)
			break;
		n -= nn;
		off += big nn;
		buf = buf[nn:];
	}
	return org-n;
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
