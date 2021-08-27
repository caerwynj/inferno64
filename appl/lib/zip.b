implement Zip;

include "sys.m";
	sys: Sys;
	sprint: import sys;
include "draw.m";
include "arg.m";
include "bufio.m";
	bufio: Bufio;
	Iobuf: import bufio;
include "daytime.m";
	dt: Daytime;
include "encoding.m";
	base16: Encoding;
include "filter.m";
	inflate: Filter;
include "convcs.m";
	convcs: Convcs;
	cp437: Btos;
include "zip.m";

comprmethods := array[] of {
	"uncompressed",
	"shrunk",
	"reduce, factor 1",
	"reduce, factor 2",
	"reduce, factor 3",
	"reduce, factor 4",
	"implode",
	"tokenize",
	"deflate",
	"deflate64",
	"pkware implode",
	nil,
	"bzip2",
	nil,
	"lzma",
Mibmterse =>
	"ibm terse (new)",
Mlz77z =>
	"ibm lz77 z",
Mwavpack =>
	"wavpack",
Mppmdi1 =>
	"PPMd version I, rev 1",
};

Crc32poly: con int 16redb88320;  # reversed standard crc-32
crc32tab: array of int;


init(): string
{
	sys = load Sys Sys->PATH;
	bufio = load Bufio Bufio->PATH;
	base16 = load Encoding Encoding->BASE16PATH;
	dt = load Daytime Daytime->PATH;
	inflate = load Filter Filter->INFLATEPATH;
	inflate->init();
	convcs = load Convcs Convcs->PATH;
	err := convcs->init(nil);
	if(err == nil)
		(cp437, err) = convcs->getbtos("cp437");
	if(err != nil)
		err = "convcs: "+err;

	crc32tab = mkcrctab(Crc32poly);

	return err;
}


sanitizepath(s: string): string
{
	endslash := s != nil && s[len s-1] == '/';
	r: list of string;
	for(l := sys->tokenize(s, "/").t1; l != nil; l = tl l)
		case hd l {
		"." =>	;
		".." =>	if(r != nil) r = tl r;
		* =>	r = hd l::r;
		}
	rs := "";
	for(r = rev(r); r != nil; r = tl r)
		rs += "/"+hd r;
	if(rs != nil)
		rs = rs[1:];
	if(endslash)
		rs[len rs] = '/';
	return rs;
}

Extra.parse(d: array of byte): (ref Extra, string)
{
	e := ref Extra;
	{
		o := 0;
		while(o < len d) {
			id: int;
			buf: array of byte;
			(id, o) = g16(d, o);
			(buf, o) = gstr(d, o);
			e.l = ref (id, buf)::e.l;
		}
	} exception {
	"get:*" =>
		return (nil, sprint("bad extra"));
	}
	e.l = rev(e.l);
	return (e, nil);
}

Extra.pack(e: self ref Extra): array of byte
{
	n := 0;
	if(e != nil)
		l := e.l;
	for(t := l; t != nil; t = tl t)
		n += 2+2+len (hd t).t1;
	buf := array[n] of byte;
	o := 0;
	for(; l != nil; l = tl l) {
		(id, dat) := *hd l;
		o = p16(buf, o, id);
		o = p16(buf, o, len dat);
		o = pbuf(buf, o, dat);
	}
	return buf;
}

Extra.text(e: self ref Extra): string
{
	s: string;
	for(l := e.l; l != nil; l = tl l)
		s += sprint(", 0x%04ux=%s", (hd l).t0, base16->enc((hd l).t1));
	if(s != nil)
		s = s[2:];
	return "Extra("+s+")";
}


Fhdr.mk(x: ref CDFhdr): ref Fhdr
{
	return ref Fhdr (
		x.versneeded,
		x.flags,
		x.comprmethod,
		x.filemtime,
		x.filemdate,
		x.mtime,
		x.crc32,
		x.comprsize,
		x.uncomprsize,
		x.filename,
		ref *x.extra,
		big 0);
}

fhdrsig := array[] of {byte 'P', byte 'K', byte 3, byte 4};
Fhdr.parse(buf: array of byte, off: big): (ref Fhdr, string)
{
	if(len buf < 4 || bufcmp(buf[:4], fhdrsig) != 0)
		return (nil, sprint("not a local file header"));
	o := 4;
	f := ref Fhdr;
	{
		(f.versneeded, o) = g16(buf, o);
		(f.flags, o) = g16(buf, o);
		(f.comprmethod, o) = g16(buf, o);
		(f.filemtime, o) = g16(buf, o);
		(f.filemdate, o) = g16(buf, o);
		f.mtime = mtimedos2unix(f.filemtime, f.filemdate);
		(f.crc32, o) = g32(buf, o);
		(f.comprsize, o) = g32(buf, o);
		(f.uncomprsize, o) = g32(buf, o);
		flen, extralen: int;
		(flen, o) = g16(buf, o);
		(extralen, o) = g16(buf, o);
		(f.filename, o) = gbufstr(f.flags&Futf8, flen, buf, o);
		f.filename = sanitizepath(f.filename);
		extra: array of byte;
		(extra, o) = gbuf(extralen, buf, o);
		err: string;
		(f.extra, err) = Extra.parse(extra);
		if(err != nil)
			return (nil, "bad extra for local file header: "+err);
		f.dataoff = off+big o;
	} exception {
	"get:*" =>
		return (nil, sprint("short buffer for local file header (o %d, len %d)", o, len buf));
	}
	return (f, nil);
}

Fhdr.read(fd: ref Sys->FD, off: big): (ref Fhdr, string)
{
	minwidth: con 4+5*2+3*4+2*2;
	n := preadn(fd, buf0 := array[minwidth] of byte, len buf0, off);
	if(n < 0)
		return (nil, sprint("read: %r"));
	if(n != len buf0)
		return (nil, "short read");
	flen := g16(buf0, len buf0-4).t0;
	extralen := g16(buf0, len buf0-2).t0;
	buf1 := array[flen+extralen] of byte;
	if(len buf1 > 0) {
		n = preadn(fd, buf1, len buf1, off+big minwidth);
		if(n < 0)
			return (nil, sprint("read: %r"));
		if(n != len buf1)
			return (nil, "short read");
	}
	buf := array[len buf0+len buf1] of byte;
	buf[:] = buf0;
	buf[len buf0:] = buf1;
	return Fhdr.parse(buf, off);
}

Fhdr.pack(f: self ref Fhdr): array of byte
{
	filename := array of byte f.filename;
	ebuf := f.extra.pack();
	buf := array[4+5*2+3*4+2+len filename+2+len ebuf] of byte;

	(f.filemtime, f.filemdate) = mtimeunix2dos(f.mtime);

	o := 0;
	o = pbuf(buf, o, fhdrsig);
	o = p16(buf, o, f.versneeded);
	o = p16(buf, o, f.flags);
	o = p16(buf, o, f.comprmethod);
	o = p16(buf, o, f.filemtime);
	o = p16(buf, o, f.filemdate);
	o = p32(buf, o, f.crc32);
	o = p32(buf, o, f.comprsize);
	o = p32(buf, o, f.uncomprsize);
	o = p16(buf, o, len filename);
	o = p16(buf, o, len ebuf);
	o = pbuf(buf, o, filename);
	o = pbuf(buf, o, ebuf);
	return buf;
}

Fhdr.text(f: self ref Fhdr): string
{
	return sprint("Fhdr(versneeded %d (%s), flags %ux, comprmethod %d/%s, mtime %d, crc32 %bd, comprsize %bd, uncomprsize %bd, filename %q, %s, dataoff %bd)",
		f.versneeded, versstr(f.versneeded),
		f.flags,
		f.comprmethod, comprmethod(f.comprmethod),
		f.mtime,
		f.crc32,
		f.comprsize, f.uncomprsize,
		f.filename,
		f.extra.text(),
		f.dataoff);
}


mask(n: int): int
{
	return (1<<n)-1;
}

mtimeunix2dos(m: int): (int, int)
{
	tm := dt->local(m);
	s := tm.sec | tm.min<<5 | tm.hour<<11;
	d := tm.mday | (tm.mon+1)<<5 | (tm.year-80)<<9;
	return (s, d);
}

zerotm: ref dt->Tm;
mtimedos2unix(s, d: int): int
{
	if(zerotm == nil)
		zerotm = dt->local(dt->now());
	tm := ref *zerotm;
	tm.sec	= (s>>0) & mask(5);
	tm.min	= (s>>5) & mask(6);
	tm.hour	= (s>>11) & mask(5);
	tm.mday	= (d>>0) & mask(5);
	tm.mon	= ((d>>5) & mask(4))-1;
	tm.year	= ((d>>9) & mask(7))+80;
	tm.wday	= 0;
	tm.yday	= 0;
	return dt->tm2epoch(tm);
}

CDFhdr.mk(f: ref Fhdr, off: big): ref CDFhdr
{
	return ref CDFhdr (
		f.versneeded,  # we're not claiming to be unix, because then unzip sets 0 for permissions when absent
                f.versneeded,
		f.flags,
		f.comprmethod,
		f.filemtime,
		f.filemdate,
		f.mtime,
		f.crc32,
		f.comprsize,
		f.uncomprsize,
		f.filename,
		f.extra,
		nil,
		0,
		0,
		big 0,
		off);
}

cdirfhdrsig := array[] of {byte 'P', byte 'K', byte 1, byte 2};

CDFhdr.parse(buf: array of byte): (ref CDFhdr, string)
{
	if(len buf < 4 || bufcmp(buf[:4], cdirfhdrsig) != 0)
		return (nil, "not a central directory file header");
	f := ref CDFhdr;
	o := 4;
	{
		(f.versmadeby, o) = g16(buf, o);
		(f.versneeded, o) = g16(buf, o);
		(f.flags, o) = g16(buf, o);
		if(f.flags & Fcdirencrypted)
			return (nil, "central directory is encrypted, not supported");
		(f.comprmethod, o) = g16(buf, o);
		(f.filemtime, o) = g16(buf, o);
		(f.filemdate, o) = g16(buf, o);
		f.mtime = mtimedos2unix(f.filemtime, f.filemdate);
		(f.crc32, o) = g32(buf, o);
		(f.comprsize, o) = g32(buf, o);
		(f.uncomprsize, o) = g32(buf, o);
		flen, extralen, commentlen: int;
		(flen, o) = g16(buf, o);
		(extralen, o) = g16(buf, o);
		(commentlen, o) = g16(buf, o);
		(f.disknrstart, o) = g16(buf, o);
		(f.intattr, o) = g16(buf, o);
		(f.extattr, o) = g32(buf, o);
		(f.reloffset, o) = g32(buf, o);
		(f.filename, o) = gbufstr(f.flags&Futf8, flen, buf, o);
		f.filename = sanitizepath(f.filename);
		extra: array of byte;
		(extra, o) = gbuf(extralen, buf, o);
		err: string;
		(f.extra, err) = Extra.parse(extra);
		if(err != nil)
			return (nil, sprint("bad extra for central directory file header"));
		(f.comment, o) = gbufstr(f.flags&Futf8, commentlen, buf, o);
		if(o != len buf)
			say(sprint("%d trailing bytes after parsing central directory file header", len buf-o));
	} exception {
	"get:*" =>
		return (nil, sprint("short buffer for central directory file header (o %d, len %d)", o, len buf));
	}
	return (f, nil);
}

CDFhdr.read(b: ref Bufio->Iobuf): (ref CDFhdr, string)
{
	buf0 := array[4+6*2+3*4+5*2+2*4] of byte;
	if(breadn(b, buf0, len buf0) != len buf0)
		return (nil, sprint("short read on central directory file header"));
	if(bufcmp(buf0[:4], cdirfhdrsig) != 0)
		return (nil, sprint("not signature of central directory file header"));
	lenoff := 4+6*2+3*4;
	n := g16(buf0, lenoff).t0;
	n += g16(buf0, lenoff+2).t0;
	n += g16(buf0, lenoff+4).t0;
	buf1 := array[n] of byte;
	if(breadn(b, buf1, len buf1) != len buf1)
		return (nil, sprint("short read on filename/extra/comment section of central directory file header"));
	buf := array[len buf0+len buf1] of byte;
	buf[:] = buf0;
	buf[len buf0:] = buf1;
	return CDFhdr.parse(buf);
}

CDFhdr.pack(f: self ref CDFhdr): array of byte
{
	filename := array of byte f.filename;
	comment := array of byte f.comment;
	ebuf := f.extra.pack();
	buf := array[4+6*2+3*4+2+len filename+2+len ebuf+2+len comment+2*2+2*4] of byte;

	(f.filemtime, f.filemdate) = mtimeunix2dos(f.mtime);

	o := 0;
	o = pbuf(buf, o, cdirfhdrsig);
	o = p16(buf, o, f.versmadeby);
	o = p16(buf, o, f.versneeded);
	o = p16(buf, o, f.flags);
	o = p16(buf, o, f.comprmethod);
	o = p16(buf, o, f.filemtime);
	o = p16(buf, o, f.filemdate);
	o = p32(buf, o, f.crc32);
	o = p32(buf, o, f.comprsize);
	o = p32(buf, o, f.uncomprsize);
	o = p16(buf, o, len filename);
	o = p16(buf, o, len ebuf);
	o = p16(buf, o, len comment);
	o = p16(buf, o, f.disknrstart);
	o = p16(buf, o, f.intattr);
	o = p32(buf, o, f.extattr);
	o = p32(buf, o, f.reloffset);
	o = pbuf(buf, o, filename);
	o = pbuf(buf, o, ebuf);
	o = pbuf(buf, o, comment);
	return buf;
}

CDFhdr.text(f: self ref CDFhdr): string
{
	return sprint("CDFhdr(version: madeby %d (%s), needed %d (%s); flags %02ux, comprmethod %d/%s, mtime %d, crc32 %bux, comprsize %bd, uncomprsize %bd, file %q, %s, comment %q, disknrstart %d, intattr %02x, extattr %04bux, reloffset %bd)",
		f.versmadeby, versstr(f.versmadeby),
		f.versneeded, versstr(f.versneeded),
		f.flags, f.comprmethod, comprmethod(f.comprmethod),
		f.mtime, f.crc32, f.comprsize, f.uncomprsize,
		f.filename,
		f.extra.text(),
		f.comment,
		f.disknrstart,
		f.intattr, f.extattr, f.reloffset);
}


eocentraldirsig := array[] of {byte 'P', byte 'K', byte 5, byte 6};
Endofcdir.parse(buf: array of byte): (ref Endofcdir, string)
{
	e := ref Endofcdir;
	if(len buf < 4 || bufcmp(buf[:4], eocentraldirsig) != 0)
		return (nil, "not end of central directory");
	o := 4;
	{
		(e.disknr, o) = g16(buf, o);
		(e.diskcdir, o) = g16(buf, o);
		(e.diskcdirentries, o) = g16(buf, o);
		(e.cdirentries, o) = g16(buf, o);
		(e.cdirsize, o) = g32(buf, o);
		(e.cdiroffset, o) = g32(buf, o);
		(e.comment, o) = gstr(buf, o);
		if(o != len buf)
			say(sprint("%d trailing bytes after end of central directory", len buf-o));
	} exception {
	"get:*" =>
		return (nil, sprint("short buffer for end of central directory buffer, (o %d, len %d)", o, len buf));
	}
	return (e, nil);
}

Endofcdir.pack(e: self ref Endofcdir): array of byte
{
	buf := array[4+4*2+2*4+2+len e.comment] of byte;
	o := 0;
	o = pbuf(buf, o, eocentraldirsig);
	o = p16(buf, o, e.disknr);
	o = p16(buf, o, e.diskcdir);
	o = p16(buf, o, e.diskcdirentries);
	o = p16(buf, o, e.cdirentries);
	o = p32(buf, o, e.cdirsize);
	o = p32(buf, o, e.cdiroffset);
	o = p16(buf, o, len e.comment);
	o = pbuf(buf, o, e.comment);
	return buf;
}

Endofcdir.text(e: self ref Endofcdir): string
{
	return sprint("Endofcdir(disk: nr %d, cdir %d, cdirentries %d;  cdir: entries %d, size %bd, offset %bd;  comment %q)",
		e.disknr, e.diskcdir, e.diskcdirentries, e.cdirentries, e.cdirsize, e.cdiroffset, string e.comment);
}


comprmethod(m: int): string
{
	if(m < 0 || m >= len comprmethods || comprmethods[m] == nil)
		return "unknown";
	return comprmethods[m];
}

open(fd: ref Sys->FD): (ref Endofcdir, array of ref CDFhdr, string)
{
	{
		return open0(fd);
	} exception e {
	"open0:*" =>
		return (nil, nil, e[len "open0:":]);
	}
}

error(s: string)
{
	raise "open0:"+s;
}

open0(fd: ref Sys->FD): (ref Endofcdir, array of ref CDFhdr, string)
{
	(ok, dir) := sys->fstat(fd);
	if(ok < 0)
		error(sprint("stat: %r"));
	size := dir.length;
	off := size-big (8*1024);
	if(off < big 0)
		off = big 0;
	n := preadn(fd, buf := array[int (size-off)] of byte, len buf, off);
	if(n < 0)
		error(sprint("read: %r"));
	buf = buf[:n];
	(o, eerr) := findeocdir(buf);
	if(eerr != nil)
		error("cannot parse file: "+eerr);
	off += big o;

	(eocdir, err) := Endofcdir.parse(buf[o:]);
	if(err != nil)
		error("parsing end of central directory: "+err);

	if(eocdir.disknr != 0 || eocdir.diskcdirentries != eocdir.cdirentries)
		error("split zip file, not supported");

	b := bufio->fopen(fd, Bufio->OREAD);
	if(b == nil)
		error(sprint("fopen: %r"));
	if(b.seek(eocdir.cdiroffset, Bufio->SEEKSTART) != eocdir.cdiroffset)
		error(sprint("seek to central directory: %r"));
	a := array[eocdir.cdirentries] of ref CDFhdr;
	for(i := 0; i < len a; i++) {
		(fhdr, ferr) := CDFhdr.read(b);
		if(ferr != nil)
			error("reading central directory file header: "+ferr);
		a[i] = fhdr;
	}

	return (eocdir, a, nil);
}

findeocdir(buf: array of byte): (int, string)
{
	for(o := len buf-(4+2+2+2+2+4+4+2); o >= 0; o--)
		if(buf[o] == byte 'P' && bufcmp(buf[o:o+4], eocentraldirsig) == 0)
			return (o, nil);
	return (-1, "cannot find end of central directory");
}

supported(f: ref Fhdr): string
{
	if((f.versneeded & 255) > Version)
		return sprint("version too low for opening file, have %s, need %s", versstr(Version), versstr(f.versneeded & 255));
	if(f.flags & Fcompressedpatched)
		return "file is a patch, not supported";
	if(f.flags & Fstrongcrypto)
		return "file is new-style encrypted, not supported";
	if(f.flags & Fencrypted)
		return "file is encrypted, not supported";
	return nil;
}

openfile(fd: ref Sys->FD, cdf: ref CDFhdr): (ref Sys->FD, ref Fhdr, string)
{
	(f, err) := Fhdr.read(fd, cdf.reloffset);
	if(err != nil)
		return (nil, nil, err);

	err = supported(f);
	if(err != nil)
		return (nil, nil, err);

	zfd: ref Sys->FD;
	case f.comprmethod {
	Mplain =>
		zfd = pushbuf(fd, f.dataoff, int f.uncomprsize, cdf.crc32);
	Mdeflate =>
		# xxx +1 is a hack to prevent "premature end of stream" from our inflate.  is our inflate broken or is it info-zip 3.0?
		zfd = pushfilter(fd, f.dataoff, 1+int f.comprsize, cdf.crc32);
	* =>
		return (nil, nil, sprint("compression method %q not supported", comprmethod(f.comprmethod)));
	}
	if(zfd == nil)
		return (nil, nil, "opening file in zip failed");
	return (zfd, f, nil);
}

readfhdr(fd: ref Sys->FD, cdf: ref CDFhdr): (ref Fhdr, string)
{
	(f, err) := Fhdr.read(fd, cdf.reloffset);
	if(err == nil)
		err = supported(f);
	return (f, err);
}

# no crc32 protection, assumes supportedness has been checked already.
pread(fd: ref Sys->FD, f: ref Fhdr, buf: array of byte, n: int, off: big): int
{
	if(f.comprmethod != Mplain) {
		sys->werrstr("file is not plain (uncompressed)");
		return -1;
	}
	if(off > f.uncomprsize)
		off = f.uncomprsize;
	if(off+big n > f.uncomprsize)
		n = int (f.uncomprsize-off);
	return sys->pread(fd, buf, n, f.dataoff+off);
}

cvtstr(d: array of byte, isutf8: int): string
{
	if(isutf8)
		return string d;
	return cp437->btos(Convcs->Startstate, d, -1).t1;
}

versstr(v: int): string
{
	v &= 255;
	return sprint("%d.%d", v/10, v%10);
}

filegen: int;
fileio(): (ref Sys->FD, ref Sys->FileIO)
{
	f := sprint("f%d", filegen++);
	fio := sys->file2chan("/chan", f);
	if(fio != nil)
		rfd := sys->open("/chan/"+f, Sys->OREAD);
	return (rfd, fio);
}

# as long as reads are sequential, keep track of the crc and verify at eof
pushbuf0(fd: ref Sys->FD, off: big, n: int, fdc: chan of ref Sys->FD, hdrcrc: big)
{
	(rfd, fio) := fileio();
	fdc <-= rfd;
	if(rfd == nil)
		return;

	prevoff := big 0;
	docrc := 1;
	crc := ~0;
	end := off+big n;
Fio:
	for(;;) {
		(roff0, count, nil, rc) := <-fio.read;
		if(rc == nil)
			return;
		roff := off+big roff0;
		rend := roff+big count;
		if(roff < off)
			roff = off;
		if(rend > end)
			rend = end;
		nn := sys->pread(fd, buf := array[int (rend-roff)] of byte, len buf, roff);
		if(nn < 0) {
			rc <-= (nil, sprint("%r"));
			continue;
		}
		docrc = docrc && prevoff == roff0;
		if(docrc) {
			crc = crc32(crc, buf[:nn]);
			if(nn == 0 && ~crc != int hdrcrc) {
				rc <-= (nil, sprint("crc mismatch, expected %bux, calculated %ux", hdrcrc, ~crc));
				break Fio;
			}
			prevoff += big nn;
		}
		rc <-= (buf[:nn], nil);
	}
}

pushbuf(fd: ref Sys->FD, off: big, n: int, hdrcrc: big): ref Sys->FD
{
	spawn pushbuf0(fd, off, n, fdc := chan of ref Sys->FD, hdrcrc);
	return <-fdc;
}

pushfilter0(fd: ref Sys->FD, off: big, n: int, fdc: chan of ref Sys->FD, hdrcrc: big)
{
	(rfd, fio) := fileio();
	fdc <-= rfd;
	if(rfd == nil)
		return;

	rqc := inflate->start("");
	pid: int;
	pick srq := <-rqc {
	Start =>
		pid = srq.pid;
	* =>
		return;
	}

	crc := ~0;
	poff := big 0;  # previous offset read
	buf := array[0] of byte;
Fio:
	for(;;) {
		(roff, count, nil, rc) := <-fio.read;
		if(rc == nil)
			break Fio;
		if(roff != poff) {
			rc <-= (nil, "random reads not allowed");
			break Fio;
		}

	Filter:
		while(len buf == 0)
			pick rq := <-rqc {
			Start =>
				rc <-= (nil, "bogus start message from filter");
				break Fio;
			Fill =>
				give := len rq.buf;
				if(give > n)
					give = n;
				nn := sys->pread(fd, rq.buf, give, off);
				rq.reply <-= nn;
				if(nn < 0) {
					rc <-= (nil, sprint("read: %r"));
					break Fio;
				}
				off += big nn;
				n -= nn;
			Result =>
				crc = crc32(crc, rq.buf);
				buf = array[len rq.buf] of byte;
				buf[:] = rq.buf;
				rq.reply <-= 0;
				break Filter;
			Finished =>
				if(len rq.buf != 0)
					say(sprint("%d leftover bytes", len rq.buf));
				crc = ~crc;
				if(crc != int hdrcrc) {
					rc <-= (nil, sprint("crc mismatch, expected %bux, calculated %ux", hdrcrc, crc));
					break Fio;
				}
				rc <-= (array[0] of byte, nil);
				break Fio;
			Info =>
				say("inflate: "+rq.msg);
			Error =>
				rc <-= (nil, rq.e);
				break Fio;
			}

		give := count;
		if(give > len buf)
			give = len buf;
		r := buf[:give];
		buf = buf[give:];
		poff += big give;
		rc <-= (r, nil);
	}
	kill(pid);
}

pushfilter(fd: ref Sys->FD, off: big, n: int, hdrcrc: big): ref Sys->FD
{
	spawn pushfilter0(fd, off, n, fdc := chan of ref Sys->FD, hdrcrc);
	return <-fdc;
}


bufcmp(a, b: array of byte): int
{
	for(i := 0; i < len a; i++)
		if(a[i] != b[i])
			return int a[i]-int b[i];
	return 0;
}

g16(d: array of byte, o: int): (int, int)
{
	if(o+2 > len d)
		raise "get:short buffer";
	v := 0;
	v |= int d[o++]<<0;
	v |= int d[o++]<<8;
	return (v, o);
}

g32(d: array of byte, o: int): (big, int)
{
	if(o+2 > len d)
		raise "get:short buffer";
	v := big 0;
	v |= big d[o++]<<0;
	v |= big d[o++]<<8;
	v |= big d[o++]<<16;
	v |= big d[o++]<<24;
	return (v, o);
}

gstr(d: array of byte, o: int): (array of byte, int)
{
	n: int;
	(n, o) = g16(d, o);
	if(o+n > len d)
		raise "get:short buffer for string";
	buf := array[n] of byte;
	buf[:] = d[o:o+n];
	return (buf, o+n);
}

gbuf(n: int, d: array of byte, o: int): (array of byte, int)
{
	if(o+n > len d)
		raise "get:short buffer for buffer";
	buf := array[n] of byte;
	buf[:] = d[o:o+n];
	return (buf, o+n);
}

gbufstr(isutf8: int, n: int, d: array of byte, o: int): (string, int)
{
	buf: array of byte;
	(buf, o) = gbuf(n, d, o);
	return (cvtstr(buf, isutf8), o);
}

p16(d: array of byte, o: int, v: int): int
{
	d[o++] = byte (v>>0);
	d[o++] = byte (v>>8);
	return o;
}

p32(d: array of byte, o: int, v: big): int
{
	d[o++] = byte (v>>0);
	d[o++] = byte (v>>8);
	d[o++] = byte (v>>16);
	d[o++] = byte (v>>24);
	return o;
}

pbuf(d: array of byte, o: int, buf: array of byte): int
{
	d[o:] = buf;
	return o+len buf;
}

preadn(fd: ref Sys->FD, buf: array of byte, n: int, off: big): int 
{
	have := 0;
	for(;;) {
		nn := sys->pread(fd, buf[have:], n, off);
		if(nn < 0)
			return nn;
		if(nn == 0)
			break;
		have += nn;
		off += big nn;
		n -= nn;
	}
	return have;
}

breadn(b: ref Iobuf, buf: array of byte, n: int): int
{
	have := 0;
	for(;;) {
		nn := b.read(buf[have:], n-have);
		if(nn < 0)
			return nn;
		if(nn == 0)
			break;
		have += nn;
	}
	return have;
}


mkcrcval(poly, c: int): int
{
	for(j := 0; j < 8; j++)
		if(c & 1)
			c = poly ^ ((c>>1) & 16r7fffffff);
		else
			c = (c>>1) & 16r7fffffff;
	return c;
}

mkcrctab(poly: int): array of int
{
	tab := array[256] of int;
        for(i := 0; i < 256; i++)
		tab[i] = mkcrcval(poly, i);
	return tab;
}

crc32(crc: int, buf: array of byte): int
{
	n := len buf;
	for(i := 0; i < n; i++)
                crc = crc32tab[(crc ^ int buf[i]) & 255] ^ ((crc>>8) & 16rffffff);
	return crc;
}


rev[T](l: list of T): list of T
{
	r: list of T;
	for(; l != nil; l = tl l)
		r = hd l::r;
	return r;
}

kill(pid: int)
{
	sys->fprint(sys->open(sprint("/prog/%d/ctl", pid), Sys->OWRITE), "kill");
}


say(s: string)
{
	if(dflag)
		sys->fprint(sys->fildes(2), "zip: %s\n", s);
}
