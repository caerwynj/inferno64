# zipfs design
# 
# at startup we read the entire central directory,
# set up a styxservers nametree and serve from that.
# bit 62 of the qid denotes the directory bit.
#
# if a file is not compressed and -p was set, we read directly through
# the zipfile's fd (no crc protection).
# otherwise, on first read of a file, we open a fd for that file.
# sequential or higher-than-current offset reads reuse the fd.
# random reads to before the current offset reopen the file and
# seek to the desired location by reading & discarding data.

implement Zipfs;

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
include "daytime.m";
	daytime: Daytime;
include "styx.m";
	styx: Styx;
	Tmsg, Rmsg: import Styx;
include "styxservers.m";
	styxservers: Styxservers;
	Styxserver, Fid, Navigator, Navop: import styxservers;
	nametree: Nametree;
	Tree: import nametree;
include "tables.m";
	tables: Tables;
	Table, Strhash: import tables;
include "zip.m";
	zip: Zip;
	Fhdr, CDFhdr, Endofcdir: import zip;

Zipfs: module {
	init:	fn(nil: ref Draw->Context, args: list of string);
};


# directories for styx nametree
Zdir: adt {
	name:	string;
	qid:	big;
	pqid:	big;
};

# opened file from zip archive
Zfile: adt {
	fid:	int;
	fd:	ref Sys->FD;
	off:	big;
	cdf:	ref CDFhdr;
	f:	ref Fhdr;
};

Qiddir: con big 1<<62;

zipfd: ref Sys->FD;
srv: ref Styxserver;
files: array of ref Fhdr;
zdirs: ref Strhash[ref Zdir]; # indexed by full path without trailing slash
rootzdir: ref Zdir;
dirgen: int;

cdirfhdrs: array of ref CDFhdr;

zfiles: ref Table[ref Zfile]; # indexed by fid

Dflag: int;
dflag: int;
pflag: int;
now: int;

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	arg := load Arg Arg->PATH;
	bufio = load Bufio Bufio->PATH;
	str = load String String->PATH;
	daytime = load Daytime Daytime->PATH;
	styx = load Styx Styx->PATH;
	styx->init();
	styxservers = load Styxservers Styxservers->PATH;
	styxservers->init(styx);
	nametree = load Nametree Nametree->PATH;
	nametree->init();
	tables = load Tables Tables->PATH;
	zip = load Zip Zip->PATH;
	zip->init();

	# for zip library
	sys->pctl(Sys->NEWPGRP|Sys->FORKNS, nil);
	if(sys->bind("#s", "/chan", Sys->MREPL) < 0)
		fail(sprint("bind /chan: %r"));

	arg->init(args);
	arg->setusage(arg->progname()+" [-Ddp] zipfile");
	while((c := arg->opt()) != 0)
		case c {
		'D' =>	styxservers->traceset(Dflag++);
		'd' =>	zip->dflag = dflag++;
		'p' =>	pflag++;
		* =>	arg->usage();
		}
	args = arg->argv();
	if(len args != 1)
		arg->usage();

	zdirs = zdirs.new(101, nil);

	zipfd = sys->open(hd args, Sys->OREAD);
	if(zipfd == nil)
		fail(sprint("open: %r"));

	err: string;
	(nil, cdirfhdrs, err) = zip->open(zipfd);
	if(err != nil)
		fail("parsing zip: "+err);

	now = daytime->now();
	(tree, treeop) := nametree->start();
	rzd := rootzdir = ref Zdir (".", big 0|Qiddir, big 0|Qiddir);
	tree.create(rzd.pqid, dir(rzd.name, rzd.qid, now, big 0));

	for(i := 0; i < len cdirfhdrs; i++) {
		f := cdirfhdrs[i];
		fs := f.filename;
		(path, name) := str->splitstrr(fs, "/");
		zd := ensuredir(tree, path);
		if(fs == nil || fs[len fs-1] == '/')
			continue;
		qid := big (i+1);
		tree.create(zd.qid, dir(name, qid, f.mtime, f.uncomprsize));
	}
	zdirs = nil;

	zfiles = zfiles.new(31, nil);

	msgc: chan of ref Tmsg;
	(msgc, srv) = Styxserver.new(sys->fildes(0), Navigator.new(treeop), big 0|Qiddir);
	spawn styxsrv(msgc);
}

# inefficient
# called with empty string (denoting the root directory), or path with trailing slash
ensuredir(tree: ref Tree, s: string): ref Zdir
{
	if(s == nil)
		return rootzdir;
	s = s[:len s-1];

	zd := zdirs.find(s);
	if(zd != nil)
		return zd;

	(ppath, name) := str->splitstrr(s, "/");
	pzd := ensuredir(tree, ppath);
	zd = ref Zdir (name, big ++dirgen|Qiddir, pzd.qid);
	tree.create(pzd.qid, dir(zd.name, zd.qid, now, big 0));
	zdirs.add(s, zd);
	return zd;
}

dir(name: string, qid: big, mtime: int, length: big): Sys->Dir
{
	d := sys->zerodir;
	d.name = name;
	d.uid = "zip";
	d.gid = "zip";
	d.qid.path = qid;
	if((qid & Qiddir) != big 0) {
		d.qid.qtype = Sys->QTDIR;
		d.mode = Sys->DMDIR|8r555;
	} else {
		d.qid.qtype = Sys->QTFILE;
		d.mode = 8r444;
	}
	d.mtime = d.atime = mtime;
	d.length = length;
	return d;
}

styxsrv(msgc: chan of ref Tmsg)
{
done:
	for(;;) alt {
	mm := <-msgc =>
		if(mm == nil)
			break done;
		pick m := mm {
		Readerror =>
			warn("read error: "+m.error);
			break done;
		}
		dostyx(mm);
	}
	killgrp(sys->pctl(0, nil));
}

openzfile(fid: int, qid: big): (ref Zfile, string)
{
	cdf := cdirfhdrs[int qid-1];
	zf := ref Zfile (fid, nil, big 0, cdf, nil);
	err: string;
	if(pflag && cdf.comprmethod == zip->Mplain)
		(zf.f, err) = zip->readfhdr(zipfd, cdf);
	else
		(zf.fd, nil, err) = zip->openfile(zipfd, cdf);
	if(err != nil)
		return (nil, err);
	if(Dflag) warn("zipfs: "+cdf.filename);
	zfiles.add(fid, zf);
	return (zf, nil);
}

zfileseek(zf: ref Zfile, off: big): string
{
	if(zf.off == off)
		return nil;

	if(off < zf.off) {
		(fd, nil, err) := zip->openfile(zipfd, zf.cdf);
		if(err != nil)
			return err;
		zf.fd = fd;
		zf.off = big 0;
	}

	n := int (off-zf.off);
	buf := array[Sys->ATOMICIO] of byte;
	while(n > 0) {
		nn := sys->read(zf.fd, buf, len buf);
		if(nn < 0)
			return sprint("seeking to requested offset: %r");
		if(nn == 0)
			break;  # not there yet, but subsequent reads on zf.fd will/should return eof too
		zf.off += big nn;
		n -= nn;
	}

	return nil;
}

dostyx(mm: ref Tmsg)
{
	pick m := mm {
	Clunk or
	Remove =>
		f := srv.getfid(m.fid);
		if(f != nil && f.isopen && (f.path & Qiddir) == big 0)
			zfiles.del(m.fid);
		srv.default(m);

	Read =>
		f := srv.getfid(m.fid);
		if(f.qtype & Sys->QTDIR)
			return srv.default(m);

		zf := zfiles.find(m.fid);
		if(zf == nil) {
			err: string;
			(zf, err) = openzfile(m.fid, f.path);
			if(err != nil)
				return replyerror(m, err);
		}

		if(zf.f == nil) {
			err := zfileseek(zf, m.offset);
			if(err != nil)
				return replyerror(m, err);
			n := sys->read(zf.fd, buf := array[m.count] of byte, len buf);
			if(n < 0)
				return replyerror(m, sprint("%r"));
			zf.off += big n;
			srv.reply(ref Rmsg.Read(m.tag, buf[:n]));
		} else {
			n := zip->pread(zipfd, zf.f, buf := array[m.count] of byte, len buf, m.offset);
			if(n < 0)
				return replyerror(m, sprint("%r"));
			srv.reply(ref Rmsg.Read(m.tag, buf[:n]));
		}

	* =>
		srv.default(mm);
	}
}

replyerror(m: ref Tmsg, s: string)
{
	srv.reply(ref Rmsg.Error(m.tag, s));
}

killgrp(pid: int)
{
	sys->fprint(sys->open(sprint("/prog/%d/ctl", pid), Sys->OWRITE), "killgrp");
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
