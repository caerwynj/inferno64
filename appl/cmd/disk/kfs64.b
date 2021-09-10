implement Kfs64;

#
# TO DO:
#	- sync proc; Bmod; process structure
#	- swiz?

# Differences from kfs
#	updating all file offsets, sizes and block numbers to 64 bits
#	triple, quadruple, and quintuple-indirect blocks
#	filename size 104 bytes
#	keeping the default bufsize of 1024 bytes
#	added halt to shutdown using disk/kfscmd
#	using hwblock to represent the highest touched block number
#		to avoid reaming all the free space at once
#		only ream some more blocks after hwblock, when we need space
#	allow wstat on directories

include "sys.m";
	sys: Sys;
	Qid, Dir: import Sys;
	DMEXCL, DMAPPEND, DMDIR: import Sys;
	QTEXCL, QTAPPEND, QTDIR: import Sys;

include "draw.m";

include "styx.m";
	styx: Styx;
	Tmsg, Rmsg: import styx;
	NOFID, OEXEC, ORCLOSE, OREAD, OWRITE, ORDWR, OTRUNC: import Styx;
	IOHDRSZ: import Styx;

include "daytime.m";
	daytime: Daytime;
	now: import daytime;

include "arg.m";

Kfs64: module
{
	init:	fn(nil: ref Draw->Context, nil: list of string);
};

MAXBUFSIZE:	con 16*1024;
DEFAULTBUFSIZE:	con 1024;

#
#  fundamental constants
#
	# keeps Dentrysize to 252
NAMELEN:	con 112; # ext2, ext3, ext4, zfs - 255 bytes, kfs - 28, cwfs - 144
NDBLOCK:	con 8;	# number of direct blocks in Dentry
NIBLOCK:	con 5;	# max depth of indirect blocks in Dentry - quintuple-indirect blocks
MAXFILESIZE:	con big 16r7FFFFFFFFFFFFFFF;	# Plan 9's limit (kfs's size is signed)

SUPERADDR: con big 1;	# block address of Super block
ROOTADDR: con big 2;	# block address of root Dentry

QPDIR:	con (big 1<<31);
QPNONE: con big 0;
QPROOT: con big 1;
QPSUPER: con big 2;

#
# don't change, these are the mode bits on disc
#
DALLOC: con 16r8000;
DDIR:	con 16r4000;
DAPND:	con 16r2000;
DLOCK:	con 16r1000;
DREAD:	con 4;
DWRITE:	con 2;
DEXEC:	con 1;

#
# other constants
#

MINUTE:	con 60;
TLOCK:	con 5*MINUTE;
NTLOCK:	con 200;	# number of active file locks

Buffering: con 1;

FID1, FID2, FID3: con 1+iota;

None: con 0;	# user ID for "none"
Noworld: con 9999;	# conventional id for "noworld" group

Lock: adt
{
	c: chan of int;
	new:	fn(): ref Lock;
	lock:	fn(c: self ref Lock);
	canlock:	fn(c: self ref Lock): int;
	unlock:	fn(c: self ref Lock);
};

Dentry: adt
{
	name:	string;
	uid:	int;
	gid:	int;
	muid:	int;	# not set by plan 9's kfs
	mode:	int;	# mode bits on disc: DALLOC etc
	qid:	Qid;	# 9p1 format on disc
	size:	big;	# only 64-bits on disc, and Plan 9 limits it to signed
	atime:	int;
	mtime:	int;

	iob:	ref Iobuf;	# locked block containing directory entry
	buf:	array of byte;	# pointer into block to packed directory entry
	mod:	int;	# bits of buf that need updating

	unpack:	fn(a: array of byte): ref Dentry;
		# slot is an index to the Dentry in a block
	get:	fn(p: ref Iobuf, slot: int): ref Dentry; # read Dentry from a slot in the iobuf array
		# read from device addr into iobuf array
		# then read Dentry from a slot in that array
	geta:	fn(d: ref Device, addr: big, slot: int, qpath: big, mode: int): (ref Dentry, string);
	getd:	fn(f: ref File, mode: int): (ref Dentry, string); # refresh the Direntry from device
	put:	fn(d: self ref Dentry); # update packed Dentry in memory and save it to device
	access:	fn(d: self ref Dentry, f: int, uid: int); # update Dentry times
	change:	fn(d: self ref Dentry, f: int); # tag Dentry as changed
	release:	fn(d: self ref Dentry); # release Dentry and packed memory of it

		# a is the block number of the Direntry being retrieved
	getblk:	fn(d: self ref Dentry, a: big, tag: int): ref Iobuf;
	getblk1:	fn(d: self ref Dentry, a: big, tag: int): ref Iobuf;
		# boffset is offset from the start of a block, so should never be more than the block size
	putblk:	fn (d: self ref Dentry, a: big, tag: int, boffset: int, b: array of byte): ref Iobuf;
	rel2abs:	fn(d: self ref Dentry, a: big, tag: int, putb: int): big;
	trunc:	fn(d: self ref Dentry, uid: int);
	update:	fn(d: self ref Dentry);
	print:	fn(d: self ref Dentry, msg: string);
};

Uname, Uids, Umode, Uqid, Usize, Utime: con 1<<iota;	# Dentry.mod

#
# disc structure:
#	Tag:	unused[4] pad[2] tag[2] path[8]
#	using unused[4] to align to 64 bits
Tagsize: con 4+2+2+8;

Tag: adt
{
	tag:	int;
	path:	big;

	unpack:	fn(a: array of byte): Tag;
	pack:	fn(t: self Tag, a: array of byte);
};

Superb: adt
{
	iob:	ref Iobuf;	# buffer pool?

	fstart:	big;	# starting block
	fsize:	big;	# size in blocks
	tfree:	big;	# total number of free blocks
	qidgen:	big;	# generator for unique ids
		# using hwblock to avoid reaming all blocks in the beginning
		#	or while building the list of free blocks in check()
		# It is assumed that fsize-hwblock are all free blocks as kfs64 has not
		#	touched them yet
	hwblock: big;	# highest touched block number, high-water block number

	fsok:	int;

		# free block pointers list until the block end
		# nfree[4] number of free block pointers in this list
		# free[FEPERBLK*8]
	fbuf:	array of byte;	# nfree[4] free[FEPERBLK*8]; aliased into containing block

	get:	fn(dev: ref Device, flags: int): ref Superb;
	touched:	fn(s: self ref Superb);
	put:	fn(s: self ref Superb);
	print:	fn(s: self ref Superb);

	pack:	fn(s: self ref Superb, a: array of byte);
	unpack:	fn(a: array of byte): ref Superb;
};

Device: adt
{
	fd:	ref Sys->FD;
	ronly:	int;
	# could put locks here if necessary
	# partitioning by ds(3)
};

#
# one for each locked qid
#
Tlock: adt
{
	dev:	ref Device;
	time:	int;
	qpath:	big;
	file:	cyclic ref File;	# TO DO: probably not needed
};

File: adt
{
	qlock:	chan of int;
	qid:	Qid;
	wpath:	ref Wpath;
	tlock:	cyclic ref Tlock;		# if file is locked
	fs:	ref Device;
		# Dentry is in this relative block number of parent directorys' blocks
	addr:	big;	#	addr name is misleading
					#	it is not the actual block address on the disk
	slot:	int;	# only useful when DIRPERBUF > 1 for the index in block
	lastra:	big;	# read ahead address, block number
	fid:	int;
	uid:	int;
	open:	int;
	cons:	int;	# if opened by console
		# d* fields for maintaining state while traversing directories
	doffset: big;	# directory reading
	dvers:	int;
	daddr:	big;	# state for next read, different from kfs
	dslot:	int;	# state for next read

	new:	fn(fid: int): ref File;
	access:	fn(f: self ref File, d: ref Dentry, mode: int): int;
	lock:	fn(f: self ref File);
	unlock:	fn(f: self ref File);
};

FREAD, FWRITE, FREMOV, FWSTAT: con 1<<iota;	# File.open

Chan: adt
{
	fd:	ref Sys->FD;			# fd request came in on
#	rlock, wlock: QLock;		# lock for reading/writing messages on cp
	flags:	int;
	flist:	list of ref File;			# active files
	fqlock:	chan of int;
#	reflock:	RWLock;		# lock for Tflush
	msize:	int;			# version

	new:	fn(fd: ref Sys->FD): ref Chan;
	getfid:	fn(c: self ref Chan, fid: int, flag: int): ref File;
	putfid:	fn(c: self ref Chan, f: ref File);
	flock: fn(nil: self ref Chan);
	funlock:	fn(nil: self ref Chan);
};

# buffer pool = array of Hiob's = hiob
#	implements a locality based cache (lru cache).
#	hb := hiob[addr%len hiob]; is used to figure out
#		which array element to use
# wrapper over a list of IO buffers
Hiob: adt
{
	link:	ref Iobuf;	# TO DO: eliminate circular list
	lk:	ref Lock;		# used while scrolling the list
	niob: int;

	newbuf:	fn(h: self ref Hiob): ref Iobuf;
};

# memory unit corresponding to a block maintained in a doubly linked list
Iobuf: adt
{
	qlock:	chan of int;
	dev:	ref Device;
	fore:	cyclic ref Iobuf;		# lru hash chain
	back:	cyclic ref Iobuf;		# for lru
	iobuf:	array of byte;		# only active while locked
	xiobuf:	array of byte;	# "real" buffer pointer
	addr:	big;
	flags:	int;

	get:	fn(dev: ref Device, addr: big, flags: int):ref Iobuf;
	put:	fn(iob: self ref Iobuf);
	lock:	fn(iob: self ref Iobuf);
	canlock:	fn(iob: self ref Iobuf): int;
	unlock:	fn(iob: self ref Iobuf);

	checktag:	fn(iob: self ref Iobuf, tag: int, qpath: big): int;
	settag:	fn(iob: self ref Iobuf, tag: int, qpath: big);
	print: fn(iob: self ref Iobuf, msg: string);
};

Wpath: adt
{
	up: cyclic ref Wpath;		# pointer upwards in path
	addr: big;		# directory entry addr
	slot: int;		# directory entry slot
};

#
#  error codes generated from the file server
#
Eaccess: con "access permission denied";
Ealloc: con "phase error -- directory entry not allocated";
Eauth: con "authentication failed";
Eauthmsg: con "kfs: authentication not required";
Ebadspc: con "attach -- bad specifier";
Ebadu: con "attach -- privileged user";
Ebroken: con "close/read/write -- lock is broken";
Echar: con "bad character in directory name";
Econvert: con "protocol botch";
Ecount: con "read/write -- count too big";
Edir1: con "walk -- in a non-directory";
Edir2: con "create -- in a non-directory";
Edot: con "create -- . and .. illegal names";
Eempty: con "remove -- directory not empty";
Eentry: con "directory entry not found";
Eexist: con "create -- file exists";
Efid: con "unknown fid";
Efidinuse: con "fid already in use";
Efull: con "file system full";
Elocked: con "open/create -- file is locked";
Emode: con "open/create -- unknown mode";
Ename: con "create/wstat -- bad character in file name";
Enotd: con "wstat -- attempt to change directory";
Enotg: con "wstat -- not in group";
Enotl: con "wstat -- attempt to change length";
Enotm: con "wstat -- unknown type/mode";
Enotu: con "wstat -- not owner";
Eoffset: con "read/write -- offset negative";
Eopen: con "read/write -- on non open fid";
Ephase: con "phase error -- cannot happen";
Eqid: con "phase error -- qid does not match";
Eqidmode: con "wstat -- qid.qtype/dir.mode mismatch";
Eronly: con "file system read only";
Ersc: con "it's russ's fault.  bug him.";
Esystem: con "kfs system error";
Etoolong: con "name too long";
Etoobig: con "write -- file size limit";
Ewalk: con "walk -- too many (system wide)";

#
#  tags on block
#
Tnone,
Tsuper,			# the super block
Tdir,			# directory contents
Tind1,			# points to blocks - direct pointer
Tind2,			# points to Tind1 - indirect pointer
Tind3,			# points to Tind2 - double indirect pointer
Tind4,			# points to Tind3 - triple indirect pointer
Tind5,			# points to Tind4 - quadruple indirect pointer
Tind6,			# points to Tind5 - quintuple indirect pointer
Tfile,			# file contents
Tfree,			# in free list
Tbuck,			# cache fs bucket - why?
Tvirgo,			# fake worm virgin bits - why?
Tcache,			# cw cache things - why?
MAXTAG: con iota;

#
#  flags to Iobuf.get
#
	Bread,	# read the block if miss
	Bprobe,	# return null if miss
	Bmod,	# set modified bit in buffer
	Bimm,	# set immediate bit in buffer
	Bres:		# never renamed
	con 1<<iota;

#
#  check flags
#
	Crdall,	# read all files
	Ctag,	# rebuild tags
	Cpfile,	# print files
	Cpdir,	# print directories
	Cfree,	# rebuild free list
	Cream,	# clear all bad tags
	Cbad,	# clear all bad blocks
	Ctouch,	# touch old dir and indir
	Cquiet:	# report just nasty things
	con 1<<iota;

#
#  buffer size variables, determined by RBUFSIZE
#
# could be named better but left alone for conformity
#	BUF = block in these variables
RBUFSIZE	:= DEFAULTBUFSIZE;	# block size, real block size
BUFSIZE		:= DEFAULTBUFSIZE-Tagsize;	# RBUFSIZE-Tagsize; # usable block size
DIRPERBUF	:= 4;		# number of Dentries per block
INDPERBUF	:= big 126; # BUFSIZE/8; # number of pointers in a block
	# number of blocks representable by a double indirect block of pointers
INDPERBUF2	:= big 15876; # INDPERBUF*INDPERBUF;
	# number of blocks representable by a triple indirect block of pointers
INDPERBUF3	:= big 2000376; # INDPERBUF*INDPERBUF2;
	# number of blocks representable by a quadruple indirect block of pointers
INDPERBUF4	:= big 252047376; # INDPERBUF*INDPERBUF3;
	# number of blocks representable by a quintuple indirect block of pointers
INDPERBUF5	:= big 31757969376; # INDPERBUF*INDPERBUF4;
	# list of free blocks maintained in a Tfree block
FEPERBUF	:= 120; # (BUFSIZE - Super1size -4)/8;

emptyblock: array of byte;

wrenfd: ref Sys->FD;
thedevice: ref Device;
devnone: ref Device;
wstatallow := 0;
writeallow := 0;
writegroup := 0;

ream := 0;
readonly := 0;
noatime := 0;
localfs: con 1;
conschan: ref Chan;
consuid := -1;
consgid := -1;
debug := 0;
kfsname: string;
consoleout: chan of string;
mainlock: ref Lock;
pids: list of int;
stdout : ref Sys->FD;
progresslen := 0;

noqid: Qid;

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	styx = load Styx Styx->PATH;
	daytime = load Daytime Daytime->PATH;

	styx->init();

	arg := load Arg Arg->PATH;
	if(arg == nil)
		error(sys->sprint("can't load %s: %r", Arg->PATH));
	arg->init(args);
	arg->setusage("disk/kfs [-r [-b blocksize]] [-cADPRW] [-n name] kfsfile");
	bufsize := DEFAULTBUFSIZE;
	nocheck := 0;
	while((o := arg->opt()) != 0)
		case o {
		'c' => nocheck = 1;
		'r' =>	ream = 1;
		'b' => bufsize = int arg->earg();
		'D' => debug = !debug;
		'P' => writeallow = 1;
		'W' => wstatallow = 1;
		'R' => readonly = 1;
		'A' => noatime = 1;	# mainly useful for flash
		'n' => kfsname = arg->earg();
		* =>	arg->usage();
		}
	args = arg->argv();
	if(args == nil)
		arg->usage();
	arg = nil;

	devnone = ref Device(nil, 1);
	mainlock = Lock.new();

	conschan = Chan.new(nil);
	conschan.msize = Styx->MAXRPC;

	mode := Sys->ORDWR;
	if(readonly)
		mode = Sys->OREAD;
	wrenfd = sys->open(hd args, mode);
	if(wrenfd == nil)
		error(sys->sprint("can't open %s: %r", hd args));
	thedevice = ref Device(wrenfd, readonly);
	if(ream){
		if(bufsize <= 0 || bufsize % 512 || bufsize > MAXBUFSIZE)
			error(sys->sprint("invalid block size %d", bufsize));
		RBUFSIZE = bufsize;
		wrenream(thedevice);
	}else{
		if(!wreninit(thedevice))
			error("kfs magic in trouble");
	}
	BUFSIZE = RBUFSIZE - Tagsize;
	DIRPERBUF = BUFSIZE / Dentrysize;
	INDPERBUF = big (BUFSIZE/8); # number of pointers in a block
		# number of blocks representable by a double indirect block of pointers
	INDPERBUF2 = INDPERBUF*INDPERBUF;
		# number of blocks representable by a triple indirect block of pointers
	INDPERBUF3 = INDPERBUF*INDPERBUF2;
		# number of blocks representable by a quadruple indirect block of pointers
	INDPERBUF4 = INDPERBUF*INDPERBUF3;
		# number of blocks representable by a quintuple indirect block of pointers
	INDPERBUF5 = INDPERBUF*INDPERBUF4;
		# -4 for the nfree[4] of Fbuf
		# number of possible free block pointers in super block 
		# the -4 to store the number of freeblockpointers
	FEPERBUF = (BUFSIZE - Super1size - 4) / 8;
	emptyblock = array[RBUFSIZE] of {* => byte 0};

	if(debug){
		sys->print("QPDIR 0x%bx %bd	QPNONE %bx	QPROOT %bx	QPSUPER %bx\n",
					QPDIR, QPDIR, QPNONE, QPROOT, QPSUPER);
		sys->print("RBUFSIZE %d	Tagsize %d	BUFSIZE %d	Dentrysize %d\n",
					RBUFSIZE, Tagsize, BUFSIZE, Dentrysize);
		sys->print("DIRPERBUF %d	INDPERBUF %bd	FEPERBUF %d\n",
					DIRPERBUF, INDPERBUF, FEPERBUF);
		sys->print("INDPERBUF2 %bd	INDPERBUF3 %bd	INDPERBUF4 %bd\n",
					INDPERBUF2, INDPERBUF3, INDPERBUF4);
		sys->print("INDPERBUF5 %bd\n", INDPERBUF5);
	}
	iobufinit(500);	# initialize buffer pool of 500 buffers in groups of 5

	if(ream){
		if(debug)
			sys->print("started reaming\n");
		superream(thedevice, SUPERADDR);
		rootream(thedevice, ROOTADDR);
		wstatallow = writeallow = 1;
	}
	if(wrencheck(wrenfd))
		error("kfs super/root in trouble");

	if(debug)
		sys->print("ream %d readonly %d !read %d !readonly %d\n",
					ream, readonly, !ream, !readonly);
	if(!ream && !readonly && !superok(0)){
		sys->print("kfs needs check\n");
		if(!nocheck)
#			check(thedevice, Cquiet|Cfree);
			check(thedevice, Cfree);
	}

	(d, e) := Dentry.geta(thedevice, ROOTADDR, 0, QPROOT, Bread);
	if(d != nil && !(d.mode & DDIR))
		e = "not a directory";
	if(e != nil)
		error("bad root: "+e);
	if(debug)
		d.print("root");
	d.put();

	sys->pctl(Sys->FORKFD|Sys->NEWPGRP, nil);

	sys->pctl(Sys->NEWFD, wrenfd.fd :: 0 :: 1 :: 2 :: nil);
	wrenfd = sys->fildes(wrenfd.fd);
	thedevice.fd = wrenfd;

	c := chan of int;

	if(Buffering){
		spawn syncproc(c);
		pid := <-c;
		if(pid)
			pids = pid :: pids;
	}
	cmdchan := chan of int;
	spawn consinit(c, cmdchan);
	pid := <- c;
	if(pid)
		pids = pid :: pids;

	spawn kfs(sys->fildes(0), cmdchan);
}

error(s: string)
{
	sys->fprint(sys->fildes(2), "kfs: %s\n", s);
	for(; pids != nil; pids = tl pids)
		kill(hd pids);
	raise "fail:error";
}

panic(s: string)
{
	sys->fprint(sys->fildes(2), "kfs: panic: %s\n", s);
	for(; pids != nil; pids = tl pids)
		kill(hd pids);
	raise "panic";
}

progress(s: string)
{
	bs := array[1] of { byte 16r8 };
	for(i:=0; i<progresslen; i++)
		sys->write(stdout,bs,1);
	sys->print("%s",s);
	progresslen = len s;
}

syncproc(c: chan of int)
{
	c <-= 0;
}

shutdown()
{
	for(; pids != nil; pids = tl pids)
		kill(hd pids);
	# TO DO: when Bmod deferred, must sync
	# sync super block
	if(!readonly && superok(1)){
		# ;
	}
	iobufclear();
}

kill(pid: int)
{
	fd := sys->open("#p/"+string pid+"/ctl", Sys->OWRITE);
	if(fd != nil)
		sys->fprint(fd, "kill");
}

#
# limited file system support for console
#
kattach(fid: int): string
{
	return applycons(ref Tmsg.Attach(1, fid, NOFID, "adm", "")).t1;
}

kopen(oldfid: int, newfid: int, names: array of string, mode: int): string
{
	(r1, e1) := applycons(ref Tmsg.Walk(1, oldfid, newfid, names));
	if(r1 != nil){
		pick m := r1 {
		Walk =>
			if(len m.qids != len names){
				kclose(newfid);
				cprint(Eexist);
				return Eexist;
			}
		* =>
			return "unexpected reply";
		}
		(r1, e1) = applycons(ref Tmsg.Open(1, newfid, mode));
		if(e1 != nil){
			kclose(newfid);
			cprint(sys->sprint("open: %s", e1));
		}
	}
	return e1;
}

kread(fid: int, offset: big, nbytes: int): (array of byte, string)
{
	(r, e) := applycons(ref Tmsg.Read(1, fid, offset, nbytes));
	if(r != nil){
		pick m := r {
		Read =>
			return (m.data, nil);
		* =>
			return (nil, "unexpected reply");
		}
	}
	cprint(sys->sprint("read error: %s", e));
	return (nil, e);
}

kclose(fid: int)
{
	applycons(ref Tmsg.Clunk(1, fid));
}

applycons(t: ref Tmsg): (ref Rmsg, string)
{
	r := apply(conschan, t);
	pick m := r {
	Error =>
		if(debug)
			cprint(sys->sprint("%s: %s\n", t.text(), m.ename));
		return (nil, m.ename);
	}
	return (r, nil);
}

#
# always reads /adm/users in userinit(), then
# optionally serves the command file, if used.
#
Req: adt {
	nbytes:	int;
	rc:	chan of (array of byte, string);
};

consinit(c: chan of int, cmdchan: chan of int)
{
	kattach(FID1);
	userinit();
	if(kfsname == nil){
		c <-= 0;
		exit;
	}
	cfname := "kfs."+kfsname+".cmd";
	sys->bind("#s", "/chan", Sys->MBEFORE);
	file := sys->file2chan("/chan", cfname);
	if(file == nil)
		error(sys->sprint("can't create /chan/%s: %r", cfname));
	c <-= sys->pctl(0, nil);
	consc := chan of string;
	checkend := chan of int;
	cdata: array of byte;
	pending: ref Req;
	cfid := -1;
	for(;;) alt{
	(nil, nbytes, fid, rc) := <-file.read =>
		if(rc == nil)
			break;
		if(cfid == -1)
			cfid = fid;
		if(fid != cfid || pending != nil){
			rc <-= (nil, "kfs.cmd is busy");
			break;
		}
		if(cdata != nil){
			cdata = reply(rc, nbytes, cdata);
			break;
		}
		if(nbytes <= 0 || consoleout == nil){
			rc <-= (nil, nil);
			break;
		}
		pending = ref Req(nbytes, rc);
		consc = consoleout;
	(nil, data, fid, wc) := <-file.write =>
		if(cfid == -1)
			cfid = fid;
		if(wc == nil){
			if(fid == cfid){
				cfid = -1;
				pending = nil;
				cdata = nil;	# discard unread data from last command
				if((consc = consoleout) == nil)
					consc = chan of string;
			}
			break;
		}
		if(fid != cfid){
			wc <-= (0, "kfs.cmd is busy");
			break;
		}
		(nf, fld) := sys->tokenize(string data, " \t\n\r");
		if(nf < 1){
			wc <-= (0, "illegal kfs request");
			break;
		}
		case hd fld {
		"check" =>
			if(consoleout != nil){
				wc <-= (0, "check in progress");
				break;
			}
			f := 0;
			if(nf > 1){
				f = checkflags(hd tl fld);
				if(f < 0){
					wc <-= (0, "illegal check flag: "+hd tl fld);
					break;
				}
			}
			consoleout = chan of string;
			spawn checkproc(checkend, f);
			wc <-= (len data, nil);
			consc = consoleout;
		"users" or "user" =>
			cmd_users();
			wc <-= (len data, nil);
		"sync" =>
			# nothing TO DO until writes are buffered
			wc <-= (len data, nil);
		"allow" =>
			wstatallow = writeallow = 1;
			wc <-= (len data, nil);
		"allowoff" or "disallow" =>
			wstatallow = writeallow = 0;
			wc <-= (len data, nil);
		"halt" =>
			cmdchan <-= 0;
			wc <-= (len data, nil);
		* =>
			wc <-= (0, "unknown kfs request");
			continue;
		}
	<-checkend =>
		consoleout = nil;
		consc = chan of string;
	s := <-consc =>
		#sys->print("<-%s\n", s);
		req := pending;
		pending = nil;
		if(req != nil)
			cdata = reply(req.rc, req.nbytes, array of byte s);
		else
			cdata = array of byte s;
		if(cdata != nil && cfid != -1)
			consc = chan of string;
	}
}

reply(rc: chan of (array of byte, string), nbytes: int, a: array of byte): array of byte
{
	if(len a < nbytes)
		nbytes = len a;
	rc <-= (a[0:nbytes], nil);
	if(nbytes == len a)
		return nil;
	return a[nbytes:];
}

checkproc(c: chan of int, flags: int)
{
	mainlock.lock();
	check(thedevice, flags);
	mainlock.unlock();
	c <-= 1;
}

#
# normal kfs service
#
kfs(rfd: ref Sys->FD, cmdchan: chan of int)
{
	cp := Chan.new(rfd);
	tmsgchan := chan of ref Tmsg;
	msizechan := chan of int;
	spawn tmsgreader(rfd, tmsgchan, msizechan);
	msizechan <- = cp.msize;
	loop: for(;;)
	alt
	{
		<- cmdchan => break loop;
		t := <- tmsgchan =>
		{
			if(t == nil)
				break loop;
			else{
				r := apply(cp, t);
				pick m := r {
				Error =>
					r.tag = t.tag;
				}
				if(debug)
					sys->print("-> %s\n", r.text());
				rbuf := r.pack();
				if(rbuf == nil)
					panic("Rmsg.pack");
				if(sys->write(rfd, rbuf, len rbuf) != len rbuf)
					panic("mount write");
			}
			msizechan <- = cp.msize;
		}
	}
	shutdown();
}
tmsgreader(rfd: ref Sys->FD, tmsgchan: chan of ref Tmsg, msizechan: chan of int)
{
	msize := <- msizechan;
	while((t := Tmsg.read(rfd, msize)) != nil){
		if(debug)
			sys->print("<- %s\n", t.text());
		tmsgchan <- = t;
		msize = <- msizechan;
		t = nil;
	}
	tmsgchan <- = t;
}

apply(cp: ref Chan, t: ref Tmsg): ref Rmsg
{
	mainlock.lock();	# TO DO: this is just to keep console and kfs from colliding
	r: ref Rmsg;
	pick m := t {
	Readerror =>
		error(sys->sprint("mount read error: %s", m.error));
	Version =>
		r = rversion(cp, m);
	Auth =>
		r = rauth(cp, m);
	Flush =>
		r = rflush(cp, m);
	Attach =>
		r = rattach(cp, m);
	Walk =>
		r = rwalk(cp, m);
	Open =>
		r = ropen(cp, m);
	Create =>
		r = rcreate(cp, m);
	Read =>
		r = rread(cp, m);
	Write =>
		r = rwrite(cp, m);
	Clunk =>
		r = rclunk(cp, m);
	Remove =>
		r = rremove(cp, m);
	Stat =>
		r = rstat(cp, m);
	Wstat =>
		r = rwstat(cp, m);
	* =>
		panic("Styx mtype");
		return nil;
	}
	mainlock.unlock();
	return r;
}

rversion(cp: ref Chan, t: ref Tmsg.Version): ref Rmsg
{
	cp.msize = RBUFSIZE+IOHDRSZ;
	if(cp.msize < Styx->MAXRPC)
		cp.msize = Styx->MAXRPC;
	(msize, version) := styx->compatible(t, Styx->MAXRPC, Styx->VERSION);
	if(msize < 256)
		return ref Rmsg.Error(t.tag, "message size too small");
	return ref Rmsg.Version(t.tag, msize, version);
}

rauth(nil: ref Chan, t: ref Tmsg.Auth): ref Rmsg
{
	return ref Rmsg.Error(t.tag, Eauthmsg);
}

rflush(nil: ref Chan, t: ref Tmsg.Flush): ref Rmsg
{
	# runlock(cp.reflock);
	# wlock(cp.reflock);
	# wunlock(cp.reflock);
	# rlock(cp.reflock);
	return ref Rmsg.Flush(t.tag);
}

err(t: ref Tmsg, s: string): ref Rmsg.Error
{
	return ref Rmsg.Error(t.tag, s);
}

ferr(t: ref Tmsg, s: string, file: ref File, p: ref Iobuf): ref Rmsg.Error
{
	if(p != nil)
		p.put();
	if(file != nil)
		file.unlock();
	return ref Rmsg.Error(t.tag, s);
}

File.new(fid: int): ref File
{
	f := ref File;
	f.qlock = chan[1] of int;
	f.fid = fid;
	f.cons = 0;
	f.tlock = nil;
	f.wpath = nil;
	f.doffset = big 0;
	f.dvers = 0;
	f.daddr = big 0;
	f.dslot = 0;
	f.uid = None;
	f.cons = 0;
#	f.cuid = None;
	return f;
}

#
# returns a locked file structure
#

Chan.getfid(cp: self ref Chan, fid: int, flag: int): ref File
{
	if(fid == NOFID)
		return nil;
	cp.flock();
	for(l := cp.flist; l != nil; l = tl l){
		f := hd l;
		if(f.fid == fid){
			cp.funlock();
			if(flag)
				return nil;	# fid in use
			f.lock();
			if(f.fid == fid)
				return f;
			f.unlock();
			cp.flock();
		}
	}
	if(flag == 0){
		sys->print("kfs: cannot find %H.%ud", cp, fid);
		cp.funlock();
		return nil;
	}
	f := File.new(fid);
	f.lock();
	cp.flist = f :: cp.flist;
	cp.funlock();
	return f;
}

Chan.putfid(cp: self ref Chan, f: ref File)
{
	cp.flock();
	nl: list of ref File;
	for(x := cp.flist; x != nil; x = tl x)
		if(hd x != f)
			nl = hd x :: nl;
	cp.flist = nl;
	cp.funlock();
	f.unlock();
}

File.lock(f: self ref File)
{
	f.qlock <-= 1;
}

File.unlock(f: self ref File)
{
	<-f.qlock;
}

Chan.new(fd: ref Sys->FD): ref Chan
{
	c := ref Chan;
	c.fd = fd;
	c.fqlock = chan[1] of int;
#	rlock, wlock: QLock;		# lock for reading/writing messages on cp
	c.flags = 0;
#	reflock:	RWLock;		# lock for Tflush
	c.msize = 0;	# set by rversion
	return c;
}

Chan.flock(c: self ref Chan)
{
	c.fqlock <-= 1;
}

Chan.funlock(c: self ref Chan)
{
	<-c.fqlock;
}

rattach(cp: ref Chan, t: ref Tmsg.Attach): ref Rmsg
{
	if(t.aname != "" && t.aname != "main")
		return err(t, Ebadspc);
	file := cp.getfid(t.fid, 1);
	if(file == nil)
		return err(t, Efidinuse);
	p := Iobuf.get(thedevice, ROOTADDR, Bread);
	if(p == nil){
		cp.putfid(file);
		return err(t, "can't access root block");
	}
	d := Dentry.get(p, 0);
	if(d == nil || p.checktag(Tdir, QPROOT) || (d.mode & DALLOC) == 0 || (d.mode & DDIR) == 0){
		p.put();
		cp.putfid(file);
		return err(t, Ealloc);
	}
	if(file.access(d, DEXEC)){
		p.put();
		cp.putfid(file);
		return err(t, Eaccess);
	}
	d.access(FREAD, file.uid);
	file.fs = thedevice;
	file.qid = d.qid;
	file.addr = p.addr;
	file.slot = 0;
	file.open = 0;
	file.uid = strtouid(t.uname);
	file.wpath = nil;
	p.put();
	qid := file.qid;
	file.unlock();
	return ref Rmsg.Attach(t.tag, qid);
}

clone(nfile: ref File, file: ref File)
{
	nfile.qid = file.qid;
	nfile.wpath = file.wpath;
	nfile.fs = file.fs;
	nfile.addr = file.addr;
	nfile.slot = file.slot;
	nfile.uid = file.uid;
#	nfile.cuid = None;
	nfile.open = file.open & ~FREMOV;
}

walkname(file: ref File, wname: string): (string, Qid)
{
	#
	# File must not have been opened for I/O by an open
	# or create message and must represent a directory.
	#
	if(file.open != 0)
		return (Emode, noqid);

	(d, e) := Dentry.getd(file, Bread);
	if(d == nil)
		return (e, noqid);
	if(!(d.mode & DDIR)){
		d.put();
		return (Edir1, noqid);
	}

	#
	# For walked elements the implied user must
	# have permission to search the directory.
	#
	if(file.access(d, DEXEC)){
		d.put();
		return (Eaccess, noqid);
	}
	d.access(FREAD, file.uid);

	if(wname == "." || wname == ".." && file.wpath == nil){
		d.put();
		return (nil, file.qid);
	}

	d1: ref Dentry;	# entry for wname, if found
	slot: int;

	if(wname == ".."){
		d.put();
		addr := file.wpath.addr;
		slot = file.wpath.slot;
		(d1, e) = Dentry.geta(file.fs, addr, slot, QPNONE, Bread);
		if(d1 == nil)
			return (e, noqid);
		file.wpath = file.wpath.up;
	}else{

	Search:
		for(addr := big 0; ; addr++){
			if(d.iob == nil){
				(d, e) = Dentry.getd(file, Bread);
				if(d == nil)
					return (e, noqid);
			}
			p1 := d.getblk1(addr, 0);
			if(p1 == nil || p1.checktag(Tdir, d.qid.path)){
				if(p1 != nil)
					p1.put();
				return (Eentry, noqid);
			}
			for(slot = 0; slot < DIRPERBUF; slot++){
				d1 = Dentry.get(p1, slot);
				if(!(d1.mode & DALLOC))
					continue;
				if(wname != d1.name)
					continue;
				#
				# update walk path
				#
				file.wpath = ref Wpath(file.wpath, file.addr, file.slot);
				# TODO test is this needed? slot += DIRPERBUF*addr;
				break Search;
			}
			p1.put();
		}
		d.put();
	}

	file.addr = d1.iob.addr;
	file.slot = slot;
	file.qid = d1.qid;
	d1.put();
	return (nil, file.qid);
}

rwalk(cp: ref Chan, t: ref Tmsg.Walk): ref Rmsg
{
	nfile, tfile: ref File;
	q: Qid;

	# The file identified by t.fid must be valid in the
	# current session and must not have been opened for I/O
	# by an open or create message.

	if((file := cp.getfid(t.fid, 0)) == nil)
		return err(t, Efid);
	if(file.open != 0)
		return ferr(t, Emode, file, nil);

	# If newfid is not the same as fid, allocate a new file;
	# a side effect is checking newfid is not already in use (error);
	# if there are no names to walk this will be equivalent to a
	# simple 'clone' operation.
	# Otherwise, fid and newfid are the same and if there are names
	# to walk make a copy of 'file' to be used during the walk as
	# 'file' must only be updated on success.
	# Finally, it's a no-op if newfid is the same as fid and t.nwname
	# is 0.

	nwqid := 0;
	if(t.newfid != t.fid){
		if((nfile = cp.getfid(t.newfid, 1)) == nil)
			return ferr(t, Efidinuse, file, nil);
	}
	else if(len t.names != 0)
		nfile = tfile = File.new(NOFID);
	else{
		file.unlock();
		return ref Rmsg.Walk(t.tag, nil);
	}
	clone(nfile, file);

	r := ref Rmsg.Walk(t.tag, array[len t.names] of Qid);
	error: string;
	for(nwname := 0; nwname < len t.names; nwname++){
		(error, q) = walkname(nfile, t.names[nwname]);
		if(error != nil)
			break;
		r.qids[nwqid++] = q;
	}

	if(len t.names == 0){

		# Newfid must be different to fid (see above)
		# so this is a simple 'clone' operation - there's
		# nothing to do except unlock unless there's
		# an error.

		nfile.unlock();
		if(error != nil)
			cp.putfid(nfile);
	}else if(nwqid < len t.names){
		#
		# Didn't walk all elements, 'clunk' nfile
		# and leave 'file' alone.
		# Clear error if some of the elements were
		# walked OK.
		#
		if(nfile != tfile)
			cp.putfid(nfile);
		if(nwqid != 0)
			error = nil;
		r.qids = r.qids[0:nwqid];
	}else{
		#
		# Walked all elements. If newfid is the same
		# as fid must update 'file' from the temporary
		# copy used during the walk.
		# Otherwise just unlock (when using tfile there's
		# no need to unlock as it's a local).
		#
		if(nfile == tfile){
			file.qid = nfile.qid;
			file.wpath = nfile.wpath;
			file.addr = nfile.addr;
			file.slot = nfile.slot;
		}else
			nfile.unlock();
	}
	file.unlock();

	if(error != nil)
		return err(t, error);
	return r;
}

ropen(cp: ref Chan, f: ref Tmsg.Open): ref Rmsg
{
	wok := cp == conschan || writeallow;

	if((file := cp.getfid(f.fid, 0)) == nil)
		return err(f, Efid);

	#
	# if remove on close, check access here
	#
	ro := isro(file.fs) || (writegroup && !ingroup(file.uid, writegroup));
	if(f.mode & ORCLOSE){
		if(ro)
			return ferr(f, Eronly, file, nil);
		#
		# check on parent directory of file to be deleted
		#
		if(file.wpath == nil || file.wpath.addr == file.addr)
			return ferr(f, Ephase, file, nil);
		p := Iobuf.get(file.fs, file.wpath.addr, Bread);
		if(p == nil || p.checktag(Tdir, QPNONE))
			return ferr(f, Ephase, file, p);
		if((d := Dentry.get(p, file.wpath.slot)) == nil || !(d.mode & DALLOC))
			return ferr(f, Ephase, file, p);
		if(file.access(d, DWRITE))
			return ferr(f, Eaccess, file, p);
		p.put();
	}
	(d, e) := Dentry.getd(file, Bread);
	if(d == nil)
		return ferr(f, e, file, nil);
	p := d.iob;
	qid := d.qid;
	fmod: int;
	case f.mode & 7 {

	OREAD =>
		if(file.access(d, DREAD) && !wok)
			return ferr(f, Eaccess, file, p);
		fmod = FREAD;

	OWRITE =>
		if((d.mode & DDIR) || (file.access(d, DWRITE) && !wok))
			return ferr(f, Eaccess, file, p);
		if(ro)
			return ferr(f, Eronly, file, p);
		fmod = FWRITE;

	ORDWR =>
		if((d.mode & DDIR)
		|| (file.access(d, DREAD) && !wok)
		|| (file.access(d, DWRITE) && !wok))
			return ferr(f, Eaccess, file, p);
		if(ro)
			return ferr(f, Eronly, file, p);
		fmod = FREAD+FWRITE;

	OEXEC =>
		if((d.mode & DDIR) || (file.access(d, DEXEC) && !wok))
			return ferr(f, Eaccess, file, p);
		fmod = FREAD;

	* =>
		return ferr(f, Emode, file, p);
	}
	if(f.mode & OTRUNC){
		if((d.mode & DDIR) || (file.access(d, DWRITE) && !wok))
			return ferr(f, Eaccess, file, p);
		if(ro)
			return ferr(f, Eronly, file, p);
	}
	if(d.mode & DLOCK){
		if((t := tlocked(file, d)) == nil)
			return ferr(f, Elocked, file, p);
		file.tlock = t;
		t.file = file;
	}
	if(f.mode & ORCLOSE)
		fmod |= FREMOV;
	file.open = fmod;
	if((f.mode & OTRUNC) && !(d.mode & DAPND)){
		d.trunc(file.uid);
		qid.vers = d.qid.vers;
	}
	file.lastra = big 1;
	p.put();
	file.unlock();
	return ref Rmsg.Open(f.tag, qid, cp.msize-IOHDRSZ);
}

rcreate(cp: ref Chan, f: ref Tmsg.Create): ref Rmsg
{
	wok := cp == conschan || writeallow;

	if((file := cp.getfid(f.fid, 0)) == nil)
		return err(f, Efid);
	if(isro(file.fs) || (writegroup && !ingroup(file.uid, writegroup)))
		return ferr(f, Eronly, file, nil);

	(d, e) := Dentry.getd(file, Bread);
	if(e != nil)
		return ferr(f, e, file, nil);
	p := d.iob;
	if(!(d.mode & DDIR))
		return ferr(f, Edir2, file, p);
	if(file.access(d, DWRITE) && !wok)
		return ferr(f, Eaccess, file, p);
	d.access(FREAD, file.uid);

	#
	# Check the name is valid and will fit in an old
	# directory entry.
	#
	if((l := checkname9p2(f.name)) == 0)
		return ferr(f, Ename, file, p);
	if(l+1 > NAMELEN)
		return ferr(f, Etoolong, file, p);
	if(f.name == "." || f.name == "..")
		return ferr(f, Edot, file, p);

	# loop through all directory children to check for duplicates
	addr1 := big 0;	# block with first empty slot, if any
	slot1 := 0;
	for(addr := big 0; ; addr++){
		if((p1 := d.getblk(addr, 0)) == nil){
			# no more directory children
			# if an empty slot was found, use it
			# else create an empty block for the new Dentry
			if(addr1 != big 0)
				break;
			p1 = d.putblk(addr, Tdir, 0, emptyblock[0:BUFSIZE]);
		}
		if(p1 == nil)
			return ferr(f, Efull, file, p);
		if(p1.checktag(Tdir, d.qid.path)){
			p1.put();
			return ferr(f, Ephase, file, p);
		}

		for(slot := 0; slot < DIRPERBUF; slot++){
			d1 := Dentry.get(p1, slot);
		if(!(d1.mode & DALLOC)){
				if(addr1 == big 0){
					# use the first empty slot for creating
					addr1 = p1.addr;
					slot1 = slot; # + addr*DIRPERBUF; # TODO
				}
				continue;
			}
			# check all 
			if(f.name == d1.name){
				p1.put();
				return ferr(f, Eexist, file, p);
			}
		}
		p1.put();
	}

	fmod: int;

	case f.mode & 7 {
	OEXEC or
	OREAD =>		# seems only useful to make directories
		fmod = FREAD;

	OWRITE =>
		fmod = FWRITE;

	ORDWR =>
		fmod = FREAD+FWRITE;

	* =>
		return ferr(f, Emode, file, p);
	}
	if(f.perm & DMDIR)
		if((f.mode & OTRUNC) || (f.perm & DMAPPEND) || (fmod & FWRITE))
			return ferr(f, Eaccess, file, p);

	# do it

	path := qidpathgen(file.fs);
	if((p1 := Iobuf.get(file.fs, addr1, Bread|Bimm|Bmod)) == nil)
		return ferr(f, Ephase, file, p);
	d1 := Dentry.get(p1, slot1);
	if(d1 == nil || p1.checktag(Tdir, d.qid.path)){
		p.put();
		return ferr(f, Ephase, file, p1);
	}
	if(d1.mode & DALLOC){
		p.put();
		return ferr(f, Ephase, file, p1);
	}

	d1.name = f.name;
	if(cp == conschan){
		d1.uid = consuid;
		d1.gid = consgid;
	}
	else{
		d1.uid = file.uid;
		d1.gid = d.gid;
		f.perm &= d.mode | ~8r666;
		if(f.perm & DMDIR)
			f.perm &= d.mode | ~8r777;
	}
	d1.qid.path = big path;
	d1.qid.vers = 0;
	d1.mode = DALLOC | (f.perm & 8r777);
	if(f.perm & DMDIR)
		d1.mode |= DDIR;
	if(f.perm & DMAPPEND)
		d1.mode |= DAPND;
	t: ref Tlock;
	if(f.perm & DMEXCL){
		d1.mode |= DLOCK;
		t = tlocked(file, d1);
		# if nil, out of tlock structures
	}
	d1.access(FWRITE, file.uid);
	d1.size = big 0; # should not be needed as we start off with an emptyblock anyway
	d1.change(~0);
	d1.update();
	qid := mkqid(path, 0, d1.mode);
	p1.put();
	d.size += big Dentrysize;
	d.change(~0);
	d.access(FWRITE, file.uid);
	d.update();
	p.put();

	#
	# do a walk to new directory entry
	#
	file.wpath = ref Wpath(file.wpath, file.addr, file.slot);
	file.qid = qid;
	file.tlock = t;
	if(t != nil)
		t.file = file;
	file.lastra = big 1;
	if(f.mode & ORCLOSE)
		fmod |= FREMOV;
	file.open = fmod;
	file.addr = addr1;
	file.slot = slot1;
	file.unlock();
	return ref Rmsg.Create(f.tag, qid, cp.msize-IOHDRSZ);
}

dirread(cp: ref Chan, f: ref Tmsg.Read, file: ref File, d: ref Dentry): ref Rmsg
{
	p1: ref Iobuf;
	d1: ref Dentry;

	count := f.count;
	data := array[count] of byte;
	offset := f.offset;
	iounit := cp.msize-IOHDRSZ;
	if(count > iounit)
		count = iounit;

	# Pick up where we left off last time if nothing has changed,
	# otherwise must scan from the beginning.

	addr: big;
	start: big;
	slot: int;

	if(offset == file.doffset){	# && file.qid.vers == file.dvers
		addr = file.daddr;
		slot = file.dslot;
		start = offset;
	}
	else{
		addr = big 0;
		slot = 0;
		start = big 0;
	}

	nread := 0;
Dread:
	for(;;){
		if(d.iob == nil){
			#
			# This is just a check to ensure the entry hasn't
			# gone away during the read of each directory block.
			#
			e: string;
			(d, e) = Dentry.getd(file, Bread);
			if(d == nil)
				return ferr(f, e, file, nil);
		}
		p1 = d.getblk1(addr, 0);
		if(p1 == nil)
			break;
		if(p1.checktag(Tdir, QPNONE))
			return ferr(f, Ephase, file, p1);
		for(; slot < DIRPERBUF; slot++){
			d1 = Dentry.get(p1, slot);
			if(!(d1.mode & DALLOC))
				continue;
			dir := dir9p2(d1);
			n := styx->packdirsize(dir);
			if(n > count-nread){
				p1.put();
				break Dread;
			}
			data[nread:] = styx->packdir(dir);
			start += big n;
			if(start < offset)
				continue;
			if(count < n){
				p1.put();
				break Dread;
			}
			count -= n;
			nread += n;
			offset += big n;
		}
		p1.put();
		slot = 0;
		addr++;
	}

	file.doffset = offset;
	file.dvers = file.qid.vers;
	file.daddr = addr;
	file.dslot = slot;

	d.put();
	file.unlock();
	return ref Rmsg.Read(f.tag, data[0:nread]);
}

rread(cp: ref Chan, f: ref Tmsg.Read): ref Rmsg
{
	if((file := cp.getfid(f.fid, 0)) == nil)
		return err(f, Efid);
	if(!(file.open & FREAD))
		return ferr(f, Eopen, file, nil);
	count := f.count;
	iounit := cp.msize-IOHDRSZ;
	if(count < 0 || count > iounit)
		return ferr(f, Ecount, file, nil);
	offset := f.offset;
	if(offset < big 0)
		return ferr(f, Eoffset, file, nil);

	(d, e) := Dentry.getd(file, Bread);
	if(d == nil)
		return ferr(f, e, file, nil);
	if((t := file.tlock) != nil){
		tim := now();
		if(t.time < tim || t.file != file){
			d.put();
			return ferr(f, Ebroken, file, nil);
		}
		# renew the lock
		t.time = tim + TLOCK;
	}
	d.access(FREAD, file.uid);
	if(d.mode & DDIR)
		return dirread(cp, f, file, d);

	if(offset+big count > d.size)
		count = int (d.size - offset);
	if(count < 0)
		count = 0;
	data := array[count] of byte;
	nread := 0;
	if(d.iob == nil){
		# must check and reacquire entry
		(d, e) = Dentry.getd(file, Bread);
		if(d == nil)
			return ferr(f, e, file, nil);
	}
	while(count > 0){
		if(d.iob == nil){
			# must check and reacquire entry
			(d, e) = Dentry.getd(file, Bread);
			if(d == nil)
				return ferr(f, e, file, nil);
		}
		addr := offset / big BUFSIZE;
		if(addr == file.lastra+big 1)
			;	# dbufread(p, d, addr+1);
		file.lastra = addr;
		o := int (offset % big BUFSIZE);
		n := BUFSIZE - o;
		if(n > count)
			n = count;
		p1 := d.getblk1(addr, 0);
		if(p1 != nil){
			if(p1.checktag(Tfile, QPNONE)){
				p1.put();
				return ferr(f, Ephase, file, nil);
			}
			data[nread:] = p1.iobuf[o:o+n];
			p1.put();
		}else
			data[nread:] = emptyblock[0:n];
		count -= n;
		nread += n;
		offset += big n;
	}
	d.put();
	file.unlock();
	return ref Rmsg.Read(f.tag, data[0:nread]);
}

rwrite(cp: ref Chan, f: ref Tmsg.Write): ref Rmsg
{
	if((file := cp.getfid(f.fid, 0)) == nil)
		return err(f, Efid);
	if(!(file.open & FWRITE))
		return ferr(f, Eopen, file, nil);
	if(isro(file.fs) || (writegroup && !ingroup(file.uid, writegroup)))
		return ferr(f, Eronly, file, nil);
	count := len f.data;
	if(count < 0 || count > cp.msize-IOHDRSZ)
		return ferr(f, Ecount, file, nil);
	offset := f.offset;
	if(offset < big 0)
		return ferr(f, Eoffset, file, nil);

	(d, e) := Dentry.getd(file, Bread|Bmod);
	if(d == nil)
		return ferr(f, e, file, nil);
	if((t := file.tlock) != nil){
		tim := now();
		if(t.time < tim || t.file != file){
			d.put();
			return ferr(f, Ebroken, file, nil);
		}
		# renew the lock
		t.time = tim + TLOCK;
	}
	d.access(FWRITE, file.uid);
	if(d.mode & DAPND)
		offset = d.size;
	end := offset + big count;
	if(end > d.size){
		if(end > MAXFILESIZE)
			return ferr(f, Etoobig, file, nil);
	}
	d.update();

	nwrite := 0;
	while(count > 0){
		if(d.iob == nil){
			# must check and reacquire entry
			(d, e) = Dentry.getd(file, Bread|Bmod);
			if(d == nil)
				return ferr(f, e, file, nil);
		}
		addr := offset / big BUFSIZE;
		o := int (offset % big BUFSIZE);
		n := BUFSIZE - o;
		if(n > count)
			n = count;
		qpath := d.qid.path;
		p1 := d.putblk(addr, Tfile, o, f.data[nwrite:nwrite+n]);
		if(p1 == nil)
			return ferr(f, Efull, file, nil);
		if(p1.checktag(Tfile, qpath)){
			p1.put();
			return ferr(f, Ealloc, file, nil);
		}
		count -= n;
		nwrite += n;
		offset += big n;
		if(d.size < offset){
			d.size = offset;
			d.change(Usize);
		}
		p1.put();
	}
	d.put();
	file.unlock();
	return ref Rmsg.Write(f.tag, nwrite);
}

# slots are not given back. They are reused on a create though.
# Hence, the directory size does not decrease.
doremove(f: ref File, iscon: int): string
{
	if(isro(f.fs) || f.cons == 0 && (writegroup && !ingroup(f.uid, writegroup)))
		return Eronly;
	#
	# check permission on parent directory of file to be deleted
	#
	if(f.wpath == nil || f.wpath.addr == f.addr)
		return Ephase;
	(d1, e1) := Dentry.geta(f.fs, f.wpath.addr, f.wpath.slot, QPNONE, Bread);
	if(e1 != nil)
		return e1;
	if(!iscon && f.access(d1, DWRITE)){
		d1.put();
		return Eaccess;
	}
	d1.access(FWRITE, f.uid);
	d1.put();

	#
	# check on file to be deleted
	#
	(d, e) := Dentry.getd(f, Bread);
	if(e != nil)
		return e;

	#
	# if deleting a directory, make sure it is empty
	#
	if(d.mode & DDIR)
	for(addr:=big 0; (p1 := d.getblk(addr, 0)) != nil; addr++){
		if(p1.checktag(Tdir, d.qid.path)){
			p1.put();
			d.put();
			return Ephase;
		}
		for(slot:=0; slot<DIRPERBUF; slot++){
			d1 = Dentry.get(p1, slot);
			if(!(d1.mode & DALLOC))
				continue;
			p1.put();
			d.put();
			return Eempty;
		}
		p1.put();
	}

	#
	# do it
	#
	d.trunc(f.uid);
	d.buf[0:] = emptyblock[0:Dentrysize];
	d.put();
	return nil;
}

clunk(cp: ref Chan, file: ref File, remove: int, wok: int): string
{
	if((t := file.tlock) != nil){
		if(t.file == file)
			t.time = 0;		# free the lock
		file.tlock = nil;
	}
	if(remove)
		error := doremove(file, wok);
	file.open = 0;
	file.wpath = nil;
	cp.putfid(file);

	return error;
}

rclunk(cp: ref Chan, t: ref Tmsg.Clunk): ref Rmsg
{
	if((file := cp.getfid(t.fid, 0)) == nil)
		return err(t, Efid);
	clunk(cp, file, file.open & FREMOV, 0);
	return ref Rmsg.Clunk(t.tag);
}

rremove(cp: ref Chan, t: ref Tmsg.Remove): ref Rmsg
{
	if((file := cp.getfid(t.fid, 0)) == nil)
		return err(t, Efid);
	e :=  clunk(cp, file, 1, cp == conschan);
	if(e != nil)
		return err(t, e);
	return ref Rmsg.Remove(t.tag);
}

rstat(cp: ref Chan, f: ref Tmsg.Stat): ref Rmsg
{
	if((file := cp.getfid(f.fid, 0)) == nil)
		return err(f, Efid);
	(d, e) := Dentry.getd(file, Bread);
	if(d == nil)
		return ferr(f, e, file, nil);
	dir := dir9p2(d);
	if(d.qid.path == QPROOT)	# stat of root gives time
		dir.atime = now();
	d.put();
	if(styx->packdirsize(dir) > cp.msize-IOHDRSZ)
		return ferr(f, Ersc, file, nil);
	file.unlock();

	return ref Rmsg.Stat(f.tag, dir);
}

rwstat(cp: ref Chan, f: ref Tmsg.Wstat): ref Rmsg
{
	if((file := cp.getfid(f.fid, 0)) == nil)
		return err(f, Efid);

	# if user none, can't do anything unless in allow mode

	if(file.uid == None && !wstatallow)
		return ferr(f, Eaccess, file, nil);

	if(isro(file.fs) || (writegroup && !ingroup(file.uid, writegroup)))
		return ferr(f, Eronly, file, nil);

	#
	# first get parent
	#
	p1: ref Iobuf;
	d1: ref Dentry;
	if(file.wpath != nil){
		p1 = Iobuf.get(file.fs, file.wpath.addr, Bread);
		if(p1 == nil)
			return ferr(f, Ephase, file, p1);
		d1 = Dentry.get(p1, file.wpath.slot);
		if(d1 == nil || p1.checktag(Tdir, QPNONE) || !(d1.mode & DALLOC))
			return ferr(f, Ephase, file, p1);
	}

	#
	# now the file
	#
	(d, e) := Dentry.getd(file, Bread);
	if(d == nil)
		return ferr(f, e, file, p1);

	#
	# Convert the message and fix up
	# fields not to be changed.
	#
	dir := f.stat;
	if(dir.uid == nil)
		uid := d.uid;
	else
		uid = strtouid(dir.uid);
	if(dir.gid == nil)
		gid := d.gid;
	else
		gid = strtouid(dir.gid);
	if(dir.name == nil)
		dir.name = d.name;
	else{
		if((l := checkname9p2(dir.name)) == 0){
			d.put();
			return ferr(f, Ename, file, p1);
		}
		if(l+1 > NAMELEN){
			d.put();
			return ferr(f, Etoolong, file, p1);
		}
	}

	# Before doing sanity checks, find out what the
	# new 'mode' should be:
	# if 'type' and 'mode' are both defaults, take the
	# new mode from the old directory entry;
	# else if 'type' is the default, use the new mode entry;
	# else if 'mode' is the default, create the new mode from
	# 'type' or'ed with the old directory mode;
	# else neither are defaults, use the new mode but check
	# it agrees with 'type'.
	# checking for the default value of 16rFFFFFFFF also as the
	# conversion from Dir.mode (u32) to Sys_Dir.mode(intptr)
	# loses the top 4 bytes and ~0 will not match in those circumstances
	if(dir.qid.qtype == 16rFF && (dir.mode == ~0||big dir.mode == big 16rFFFFFFFF)){
		dir.mode = d.mode & 8r777;
		if(d.mode & DLOCK)
			dir.mode |= DMEXCL;
		if(d.mode & DAPND)
			dir.mode |= DMAPPEND;
		if(d.mode & DDIR)
			dir.mode |= DMDIR;
	}
	else if(dir.qid.qtype == 16rFF){
		# nothing to do
	}
	else if(dir.mode == ~0||big dir.mode == big 16rFFFFFFFF){
		dir.mode = (dir.qid.qtype<<24)|(d.mode & 8r777);
	}
	else if(dir.qid.qtype != ((dir.mode>>24) & 16rFF)){
		d.put();
		return ferr(f, Eqidmode, file, p1);
	}

	# Check for unknown type/mode bits
	# and an attempt to change the directory bit.

	if(dir.mode & ~(DMDIR|DMAPPEND|DMEXCL|8r777)){
		d.put();
		return ferr(f, Enotm, file, p1);
	}
	if(d.mode & DDIR)
		mode := DMDIR;
	else
		mode = 0;
# allow wstat on directories. Why not?
#	if((dir.mode^mode) & DMDIR){
#		d.put();
#		return ferr(f, Enotd, file, p1);
#	}

	if(dir.mtime == ~0)
		dir.mtime = d.mtime;
	if(dir.length == ~big 0)
		dir.length = big d.size;


	# Currently, can't change length.

	if(dir.length != big d.size){
		d.put();
		return ferr(f, Enotl, file, p1);
	}


	# if chown,
	# must be god
	# wstatallow set to allow chown during boot

	if(uid != d.uid && !wstatallow){
		d.put();
		return ferr(f, Enotu, file, p1);
	}

	# if chgroup,
	# must be either
	#	a) owner and in new group
	#	b) leader of both groups
	# wstatallow and writeallow are set to allow chgrp during boot

	while(gid != d.gid){
		if(wstatallow || writeallow)
			break;
		if(d.uid == file.uid && ingroup(file.uid, gid))
			break;
		if(leadgroup(file.uid, gid))
			if(leadgroup(file.uid, d.gid))
				break;
		d.put();
		return ferr(f, Enotg, file, p1);
	}

	# if rename,
	# must have write permission in parent
	while(d.name != dir.name){

		# drop entry to prevent deadlock, then
		# check that destination name is valid and unique

		d.put();
		if(checkname9p2(dir.name) == 0 || d1 == nil)
			return ferr(f, Ename, file, p1);
		if(dir.name == "." || dir.name == "..")
			return ferr(f, Edot, file, p1);


		for(addr := big 0; ; addr++){
			if((p := d1.getblk(addr, 0)) == nil)
				break;
			if(p.checktag(Tdir, d1.qid.path)){
				p.put();
				continue;
			}
			for(slot := 0; slot < DIRPERBUF; slot++){
				d = Dentry.get(p, slot);
				if(!(d.mode & DALLOC))
					continue;
				if(dir.name == d.name){
					p.put();
					return ferr(f, Eexist, file, p1);
				}
			}
			p.put();
		}

		# reacquire entry

		(d, nil) = Dentry.getd(file, Bread);
		if(d == nil)
			return ferr(f, Ephase, file, p1);

		if(wstatallow || writeallow) # set to allow rename during boot
			break;
		if(d1 == nil || file.access(d1, DWRITE)){
			d.put();
			return ferr(f, Eaccess, file, p1);
		}
		break;
	}

	# if mode/time, either
	#	a) owner
	#	b) leader of either group

	mode = dir.mode & 8r777;
	if(dir.mode & DMAPPEND)
		mode |= DAPND;
	if(dir.mode & DMEXCL)
		mode |= DLOCK;
	while(d.mtime != dir.mtime || ((d.mode^mode) & (DAPND|DLOCK|8r777))){
		if(wstatallow)			# set to allow chmod during boot
			break;
		if(d.uid == file.uid)
			break;
		if(leadgroup(file.uid, gid))
			break;
		if(leadgroup(file.uid, d.gid))
			break;
		d.put();
		return ferr(f, Enotu, file, p1);
	}
	d.mtime = dir.mtime;
	d.uid = uid;
	d.gid = gid;
	d.mode = (mode & (DAPND|DLOCK|8r777)) | (d.mode & (DALLOC|DDIR));

	d.name = dir.name;
	d.access(FWSTAT, file.uid);
	d.change(~0);
	d.put();

	if(p1 != nil)
		p1.put();
	file.unlock();

	return ref Rmsg.Wstat(f.tag);
}

superok(set: int): int
{
	sb := Superb.get(thedevice, Bread|Bmod|Bimm);
	ok := sb.fsok;
	sb.fsok = set;
	if(debug){
		sys->print("superok ok %d\n", ok);
		sb.print();
	}
	sb.touched();
	sb.put();
	return ok;
}

# little-endian
get2(a: array of byte, o: int): int
{
	return (int a[o+1]<<8) | int a[o];
}

get2s(a: array of byte, o: int): int
{
	v := (int a[o+1]<<8) | int a[o];
	if(v & 16r8000)
		v |= ~0 << 8;
	return v;
}

get4(a: array of byte, o: int): int
{
	return (int a[o+3]<<24) | (int a[o+2] << 16) | (int a[o+1]<<8) | int a[o];
}

get8(a: array of byte, o: int): big
{
	return (big a[o+7]<<56) | (big a[o+6] << 48) | (big a[o+5]<<40) | (big a[o+4]<<32) | (big a[o+3]<<24) | (big a[o+2] << 16) | (big a[o+1]<<8) | big a[o];
}

put2(a: array of byte, o: int, v: int)
{
	a[o] = byte v;
	a[o+1] = byte (v>>8);
}

put4(a: array of byte, o: int, v: int)
{
	a[o] = byte v;
	a[o+1] = byte (v>>8);
	a[o+2] = byte (v>>16);
	a[o+3] = byte (v>>24);
}

put8(a: array of byte, o: int, v: big)
{
	a[o] = byte v;
	a[o+1] = byte (v>>8);
	a[o+2] = byte (v>>16);
	a[o+3] = byte (v>>24);
	a[o+4] = byte (v>>32);
	a[o+5] = byte (v>>40);
	a[o+6] = byte (v>>48);
	a[o+7] = byte (v>>56);
}

Tag.unpack(a: array of byte): Tag
{
	return Tag(get2(a,6), get8(a,8));
}

Tag.pack(t: self Tag, a: array of byte)
{
	put2(a, 6, t.tag);
	if(t.path != QPNONE)
		put8(a, 8, t.path & ~QPDIR);
}

Superb.get(dev: ref Device, flags: int): ref Superb
{
	p := Iobuf.get(dev, SUPERADDR, flags);
	if(p == nil)
		return nil;
	if(p.checktag(Tsuper, QPSUPER)){
		p.put();
		return nil;
	}
	sb := Superb.unpack(p.iobuf);
	sb.iob = p;
	return sb;
}

Superb.touched(s: self ref Superb)
{
	s.iob.flags |= Bmod;
}

Superb.put(sb: self ref Superb)
{
	if(sb.iob == nil)
		return;
	if(sb.iob.flags & Bmod)
		sb.pack(sb.iob.iobuf);
	sb.iob.put();
	sb.iob = nil;
}

#  this is the disk structure
# Superb:
#	Super1;
#	Fbuf	fbuf;
# Fbuf:
#	nfree[4]	# 4 bytes of this and 4 bytes of fsok gets the below to a multiple of 8 address
#	free[]	# based on BUFSIZE
#  Super1:
#	u64	fstart;		# starting block address, mostly 1. leaving out 0 if someone craps
#	u64	fsize;		# total number of blocks on this device
#	u64	tfree;		# total number of free blocks on this device
#	u64	qidgen;		# generator for unique ids
#	u64	hwblock;	# highest touched block number, high water block number
#	s32	fsok;		# file system ok
#	u64	roraddr;	# dump root addr 		- obsolete, unused in this program
#	u64	last;		# last super block addr	- obsolete, unused in this program
#	u64	next;		# next super block addr	- obsolete, unused in this program

Ofstart: con 0;
Ofsize: con Ofstart+8;
Otfree: con Ofsize+8;
Oqidgen: con Otfree+8;
Ohwblock: con Oqidgen+8;
Ofsok: con Ohwblock+8;
#	Ororaddr: con Ofsok+8;
#	Olast: con Ororaddr+8;
#	Onext: con Olast+8;
Super1size: con Ofsok+4; # 44

Superb.unpack(a: array of byte): ref Superb
{
	s := ref Superb;
	s.fstart = get8(a, Ofstart);
	s.fsize = get8(a, Ofsize);
	s.tfree = get8(a, Otfree);
	s.qidgen = get8(a, Oqidgen);
	s.hwblock = get8(a, Ohwblock);
	s.fsok = get4(a, Ofsok);
	s.fbuf = a[Super1size:];
	return s;
}

Superb.pack(s: self ref Superb, a: array of byte)
{
	put8(a, Ofstart, s.fstart);
	put8(a, Ofsize, s.fsize);
	put8(a, Otfree, s.tfree);
	put8(a, Oqidgen, s.qidgen);
	put8(a, Ohwblock, s.hwblock);
	put4(a, Ofsok, s.fsok);
}

Superb.print(sb: self ref Superb)
{
	sys->print("fstart=%bud fsize=%bud tfree=%bud qidgen=%bud hwblock=%bud fsok=%d\n",
		sb.fstart, sb.fsize, sb.tfree, sb.qidgen, sb.hwblock, sb.fsok);
}

Dentry.get(p: ref Iobuf, slot: int): ref Dentry
{
	if(p == nil)
		return nil;
	buf := p.iobuf[slot*Dentrysize:];
	d := Dentry.unpack(buf);
	d.iob = p;
	d.buf = buf;
	return d;
}
# any Dentry at that addr and slot
Dentry.geta(fs: ref Device, addr: big, slot: int, qpath: big, mode: int): (ref Dentry, string)
{
	p := Iobuf.get(fs, addr, mode);
	if(p == nil || p.checktag(Tdir, qpath)){
		if(p != nil)
			p.put();
		return (nil, Ealloc);
	}
	d := Dentry.get(p, slot);
	if(d == nil || !(d.mode & DALLOC)){
		p.put();
		return (nil, Ealloc);
	}
	return (d, nil);
}

Dentry.getd(file: ref File, mode: int): (ref Dentry, string)
{
	(d, e) := Dentry.geta(file.fs, file.addr, file.slot, QPNONE, mode);	# QPNONE should be file.wpath's path
	if(e != nil)
		return (nil, e);
	if(file.qid.path != d.qid.path || (file.qid.qtype&QTDIR) != (d.qid.qtype&QTDIR)){
		d.put();
		return (nil, Eqid);
	}
	return (d, nil);
}

# for 4 Dentries per block
# RBUFSIZE - 16 Tagsize = BUFSIZE
# BUFSIZE / 4 = Dentrysize
# RBUFSIZE = 1024, BUFSIZE = 1008, Dentry size = 252
# Dentry size 252 - 140 = NAMELEN 112
#  this is the disk structure:
#	u8	name[NAMELEN];
#	u16	uid;
#	u16	gid;		[2*2] 4
#	u16	mode;
#		#define	DALLOC	0x8000
#		#define	DDIR	0x4000
#		#define	DAPND	0x2000
#		#define	DLOCK	0x1000
#		#define	DREAD	0x4
#		#define	DWRITE	0x2
#		#define	DEXEC	0x1
#	[u16 muid]		[2*2] 8
#	Qid.path;			[8]	16
#	Qid.version;		[4]	20
#	u64	size;			[8]	28
#	u64	dblock[NDBLOCK];[8*8]	92
#	u64	iblock[NIBLOCK];[8*5]	132
#	u32	atime;					136
#	u32	mtime;					140
#	Dentry size = 252

Oname: con 0;
Ouid: con Oname+NAMELEN;
Ogid: con Ouid+2;
Omode: con Ogid+2;
Omuid: con Omode+2;
Opath: con Omuid+2;
Overs: con Opath+8;
Osize: con Overs+4;
Odblock: con Osize+8;
Oiblock: con Odblock+NDBLOCK*8;
Oatime: con Oiblock+NIBLOCK*8;
Omtime: con Oatime+4;
Dentrysize: con Omtime+4; # kept to 252 = BUFSIZE/4 = (RBUFSIZE -Tagsize)/4

Dentry.unpack(a: array of byte): ref Dentry
{
	d := ref Dentry;
	for(i:=0; i<NAMELEN; i++)
		if(int a[Oname+i] == 0)
			break;
	d.name = string a[Oname:Oname+i];
	d.uid = get2s(a, Ouid);
	d.gid = get2s(a, Ogid);
	d.mode = get2(a, Omode);
	d.muid = get2(a, Omuid);	# note: not set by Plan 9's kfs
	d.qid = mkqid(get8(a, Opath), get4(a, Overs), d.mode);
	d.size = big get8(a, Osize);
	d.atime = get4(a, Oatime);
	d.mtime = get4(a, Omtime);
	d.mod = 0;
	return d;
}

Dentry.change(d: self ref Dentry, f: int)
{
	d.mod |= f;
}

Dentry.update(d: self ref Dentry)
{
	f := d.mod;
	d.mod = 0;
	if(d.iob == nil || (d.iob.flags & Bmod) == 0){
		if(f != 0)
			panic("Dentry.update");
		return;
	}
	a := d.buf;
	if(f & Uname){
		b := array of byte d.name;
		for(i := 0; i < NAMELEN; i++)
			if(i < len b)
				a[Oname+i] = b[i];
			else
				a[Oname+i] = byte 0;
	}
	if(f & Uids){
		put2(a, Ouid, d.uid);
		put2(a, Ogid, d.gid);
	}
	if(f & Umode)
		put2(a, Omode, d.mode);
	if(f & Uqid){
		path := d.qid.path;
		if(d.mode & DDIR)
			path |= QPDIR;
		put8(a, Opath, path);
		put4(a, Overs, d.qid.vers);
	}
	if(f & Usize)
		put8(a, Osize, d.size);
	if(f & Utime){
		put4(a, Omtime, d.mtime);
		put4(a, Oatime, d.atime);
	}
	d.iob.flags |= Bmod;
}

Dentry.access(d: self ref Dentry, f: int, uid: int)
{
	if((p := d.iob) != nil && !readonly){
		if((f & (FWRITE|FWSTAT)) == 0 && noatime)
			return;
		if(f & (FREAD|FWRITE|FWSTAT)){
			d.atime = now();
			put4(d.buf, Oatime, d.atime);
			p.flags |= Bmod;
		}
		if(f & FWRITE){
			d.mtime = now();
			put4(d.buf, Omtime, d.mtime);
			d.muid = uid;
			put2(d.buf, Omuid, uid);
			d.qid.vers++;
			put4(d.buf, Overs, d.qid.vers);
			p.flags |= Bmod;
		}
	}
}

#
# release the directory entry buffer and thus the
# lock on both buffer and entry, typically during i/o,
# to be reacquired later if needed
#
Dentry.release(d: self ref Dentry)
{
	if(d.iob != nil){
		d.update();
		d.iob.put();
		d.iob = nil;
		d.buf = nil;
	}
}

# get the a'th block number
#	when tag != 0, allocate a'th block if empty
Dentry.getblk(d: self ref Dentry, a: big, tag: int): ref Iobuf
{
	addr := d.rel2abs(a, tag, 0);
	if(addr == big 0)
		return nil;
	return Iobuf.get(thedevice, addr, Bread);
}

#
# same as Dentry.getblk but calls d.release
# to reduce interference.
#
Dentry.getblk1(d: self ref Dentry, a: big, tag: int): ref Iobuf
{
	addr := d.rel2abs(a, tag, 1);
	if(addr == big 0)
		return nil;
	return Iobuf.get(thedevice, addr, Bread);
}

Dentry.rel2abs(d: self ref Dentry, a: big, tag: int, putb: int): big
{
	if(a < big 0){
		sys->print("Dentry.rel2abs: neg\n");
		return big 0;
	}
	p := d.iob;
	if(p == nil || d.buf == nil)
		panic("nil iob");
	data := d.buf;
	qpath := d.qid.path;
	dev := p.dev;
	if(a < big NDBLOCK){
		addr := get8(data, Odblock+int a*8);
		if(putb)
			d.release();
		return addr;
	}
	a -= big NDBLOCK;
	if(a < INDPERBUF){
		addr := get8(data, Oiblock);
		if(putb)
			d.release();
		return  indfetch(dev, qpath, addr, a, Tind1);
	}
	a -= INDPERBUF;
	if(a < INDPERBUF2){
		addr := get8(data, Oiblock+1*8);
		if(putb)
			d.release();
		addr = indfetch(dev, qpath, addr, a/INDPERBUF, Tind2);
		return indfetch(dev, qpath, addr, a%INDPERBUF, Tind1);
	}
	a -= INDPERBUF2;
	if(a < INDPERBUF3){
		addr := get8(data, Oiblock+2*8);
		if(putb)
			d.release();
		addr = indfetch(dev, qpath, addr, a/INDPERBUF2, Tind3);
		addr = indfetch(dev, qpath, addr, a/INDPERBUF, Tind2);
		return indfetch(dev, qpath, addr, a%INDPERBUF, Tind1);
	}
	a -= INDPERBUF3;
	if(a < INDPERBUF4){
		addr := get8(data, Oiblock+3*8);
		if(putb)
			d.release();
		addr = indfetch(dev, qpath, addr, a/INDPERBUF3, Tind4);
		addr = indfetch(dev, qpath, addr, a/INDPERBUF2, Tind3);
		addr = indfetch(dev, qpath, addr, a/INDPERBUF, Tind2);
		return indfetch(dev, qpath, addr, a%INDPERBUF, Tind1);
	}
	a -= INDPERBUF4;
	if(a < INDPERBUF5){
		addr := get8(data, Oiblock+4*8);
		if(putb)
			d.release();
		addr = indfetch(dev, qpath, addr, a/INDPERBUF4, Tind5);
		addr = indfetch(dev, qpath, addr, a/INDPERBUF3, Tind4);
		addr = indfetch(dev, qpath, addr, a/INDPERBUF2, Tind3);
		addr = indfetch(dev, qpath, addr, a/INDPERBUF, Tind2);
		return indfetch(dev, qpath, addr, a%INDPERBUF, Tind1);
	}
	if(putb)
		d.release();
	sys->print("Dentry.rel2abs: trip indirect a %bd tag %d %s putb %d\n", a, tag, tagname(tag),putb);
	return big 0;
}

indfetch(dev: ref Device, path: big, addr: big, a: big, itag: int): big
{
	if(addr == big 0)
		return big 0;
	bp := Iobuf.get(dev, addr, Bread);
	if(bp == nil){
		cprint("ind fetch bp = nil\n");
		return big 0;
	}
	if(bp.checktag(itag, path)){
		cprint("ind fetch tag\n");
		bp.put();
		return big 0;
	}
	addr = get8(bp.iobuf, int a*8);
	bp.put();
	return addr;
}

#
# save b to the a'th block of this Dentry at boffset
# 	boffset is offset from the start of a block, so should never be more than the block size
#
Dentry.putblk(d: self ref Dentry, a: big, tag: int, boffset: int, b: array of byte): ref Iobuf
{
	if(a < big 0){
		cprint("Dentry.rel2abs: neg\n");
		return nil;
	}
	p := d.iob;
	if(p == nil || d.buf == nil)
		panic("nil iob");
	data := d.buf;
	qpath := d.qid.path;
	dev := p.dev;
	if(a < big NDBLOCK){
		p1 := putdata(dev, qpath, d.iob, data[Odblock:], a, tag, boffset, b);
		return p1;
	}
	a -= big NDBLOCK;
	if(a < INDPERBUF){
		p1 := indstore(dev, qpath, d.iob, data[Oiblock:], a, Tind1, tag, boffset, b);
		return p1;
	}
	a -= INDPERBUF;
	if(a < INDPERBUF2){
		p1 := indstore(dev, qpath, d.iob, data[Oiblock+1*8:], a, Tind2, tag, boffset, b);
		return p1;
	}
	a -= INDPERBUF2;
	if(a < INDPERBUF3){
		p1 := indstore(dev, qpath, d.iob, data[Oiblock+2*8:], a, Tind3, tag, boffset, b);
		return p1;
	}
	a -= INDPERBUF3;
	if(a < INDPERBUF4){
		p1 := indstore(dev, qpath, d.iob, data[Oiblock+3*8:], a, Tind4, tag, boffset, b);
		return p1;
	}
	a -= INDPERBUF4;
	if(a < INDPERBUF5){
		p1 := indstore(dev, qpath, d.iob, data[Oiblock+4*8:], a, Tind5, tag, boffset, b);
		return p1;
	}
	sys->print("Dentry.buf: trip indirect a %bd tag %d %s\n", a, tag, tagname(tag));
	return nil;
}

# finally storing the data
putdata(dev: ref Device, qpath: big, p: ref Iobuf, buf: array of byte, a: big, tag: int, boffset: int, b: array of byte): ref Iobuf
{
		addr := get8(buf, int a* 8);
		if(addr == big 0 && tag){
			addr = balloc(dev, tag, qpath);
			put8(buf, int a* 8, addr);
			p.flags |= Bmod|Bimm;
		}
		p1 := Iobuf.get(thedevice, addr, Bread);
		p1.iobuf[boffset:] = b;
		p1.flags |= Bmod;
		p1.put();
		return Iobuf.get(thedevice, addr, Bread);
}

indoffset(tag: int): big
{
	case tag
	{
		Tind1 => return INDPERBUF;
		Tind2 => return INDPERBUF2;
		Tind3 => return INDPERBUF3;
		Tind4 => return INDPERBUF4;
		Tind5 => return INDPERBUF5;
		* => cprint("unknown tag");
			return big 0;
	}
	return big 0;
}

# walk the indirect pointer tree to the relevant data block and put data there
#	if there is no indirect pointer yet to this data block, create one
indstore(dev: ref Device, qpath: big, p: ref Iobuf, buf: array of byte, a: big, itag: int, tag: int, boffset: int, b: array of byte): ref Iobuf
{
	indoff := indoffset(itag);
	addrloc := int (a/indoff)*8;
	addr := get8(buf, addrloc);
	if(addr == big 0 && tag){
		addr = balloc(dev, itag, qpath);
		put8(buf, addrloc, addr);
		p.flags |= Bmod|Bimm;
	}
	p1 := Iobuf.get(thedevice, addr, Bread);
	p2 : ref Iobuf;
	if(itag == Tind1)
			p2 = putdata(dev, qpath, p1, p1.iobuf, a%indoff, tag, boffset, b);
	else
			p2 = indstore(dev, qpath, p1, p1.iobuf, a%indoff, itag-1, tag, boffset, b);
	p1.flags |= Bmod;
	p1.put();
	return p2;
}

# allocate a disk block
balloc(dev: ref Device, tag: int, qpath: big): big
{
	# TO DO: cache superblock to reduce pack/unpack
	sb := Superb.get(dev, Bread|Bmod);
	if(sb == nil)
		panic("balloc: super block");
	n := get4(sb.fbuf, 0);
	n--;
	sb.tfree--;
	if(n < 0 || n >= FEPERBUF)
		panic("balloc: bad freelist");
	if(sb.hwblock <= big 0)
		panic(sys->sprint("balloct bad hwblock <= 0: %bd", sb.hwblock));
	a := get8(sb.fbuf, 4+n*8);
	if(n == 0){
		if(a == big 0){
			# out of free space within hwblock blocks
			#	extend hwblock and add those new blocks as free space
			if(sb.hwblock < sb.fsize-big 1){
				end := sb.hwblock+big FEPERBUF**2;
				if(end > sb.fsize -big 1)
					end = sb.fsize -big 1;
				if(debug)
					sys->print("balloc: used up all free space, allocating upto %bd\n", end);
				for(i := end; i>sb.hwblock; i--){
					addfree(dev, i, sb);
				}
				sb.hwblock = end;
				sb.touched();
				if(debug)
					sb.print();
				sb.put();
				return balloc(dev, tag, qpath);
			}
			sb.tfree = big 0;
			sb.touched();
			if(debug)
				sb.print();
			sb.put();
			return big 0;
		}
		bp := Iobuf.get(dev, a, Bread);
		if(bp == nil || bp.checktag(Tfree, QPNONE)){
			# no more free space
			if(bp != nil)
				bp.put();
			sb.put();
			return big 0;
		}
		sb.fbuf[0:] = bp.iobuf[0:4+FEPERBUF*8];
		sb.touched();
		bp.put();
	}else{
		put4(sb.fbuf, 0, n);
		sb.touched();
	}
	bp := Iobuf.get(dev, a, Bmod);
	bp.iobuf[0:] = emptyblock;
	bp.settag(tag, qpath);
	if(tag == Tind1 || tag == Tind2  ||tag == Tind3 ||
		tag == Tind4 || tag == Tind5 || tag == Tind6 ||
		tag == Tdir)
		bp.flags |= Bimm;
	bp.put();
	sb.put();
	return a;
}
# add a freed block to the list of free blocks
#	recursively drills through indirect pointer blocks
bfree(dev: ref Device, addr: big, d: int)
{
	if(addr == big 0)
		return;
	if(d > 0){
		d--;
		p := Iobuf.get(dev, addr, Bread);
		if(p != nil){
			for(i:=int INDPERBUF-1; i>=0; i--){
				a := get8(p.iobuf, i*8);
				bfree(dev, a, d);
			}
			p.put();
		}
	}

	# stop outstanding i/o
	p := Iobuf.get(dev, addr, Bprobe);
	if(p != nil){
		p.flags &= ~(Bmod|Bimm);
		p.put();
	}

	s := Superb.get(dev, Bread|Bmod);
	if(s == nil)
		panic("bfree: super block");
	addfree(dev, addr, s);
	s.put();
}
# add the freed block to the list of free blocks in super block
addfree(dev: ref Device, addr: big, sb: ref Superb)
{
	if(addr >= sb.fsize){
		sys->print("addfree: bad addr %bud\n", addr);
		return;
	}
	n := get4(sb.fbuf, 0);
	if(n < 0 || n > FEPERBUF)
		panic("addfree: bad freelist");
	if(n >= FEPERBUF){
		p := Iobuf.get(dev, addr, Bmod);
		if(p == nil)
			panic("addfree: Iobuf.get");
		p.iobuf[0:] = sb.fbuf[0:4+FEPERBUF*8];
		sb.fbuf[0:] = emptyblock[0:4+FEPERBUF*8];	# clear it for debugging
		p.settag(Tfree, QPNONE);
		p.put();
		n = 0;
	}
	put8(sb.fbuf, 4+n*8, addr);
	put4(sb.fbuf, 0, n+1);
	sb.tfree++;
	if(addr >= sb.fsize)
		sb.fsize = addr+big 1;
	sb.touched();
}

qidpathgen(dev: ref Device): big
{
	sb := Superb.get(dev, Bread|Bmod);
	if(sb == nil)
		panic("qidpathgen: super block");
	sb.qidgen++;
	path := sb.qidgen;
	sb.touched();
	sb.put();
	return path;
}

Dentry.trunc(d: self ref Dentry, uid: int)
{
	p := d.iob;
	data := d.buf;
	for(i:=NIBLOCK-1; i>=0; i--){
		bfree(p.dev, get8(data, Oiblock+i*8), i+1);
		put8(data, Odblock+i*8, big 0);
	}
	for(i=NDBLOCK-1; i>=0; i--){
		bfree(p.dev, get8(data, Odblock+i*8), 0);
		put8(data, Odblock+i*8, big 0);
	}
	d.size = big 0;
	d.change(Usize);
	p.flags |= Bmod|Bimm;
	d.access(FWRITE, uid);
	d.update();
}

Dentry.put(d: self ref Dentry)
{
	p := d.iob;
	if(p == nil || d.buf == nil)
		return;
	d.update();
	p.put();
	d.iob = nil;
	d.buf = nil;
}

Dentry.print(d: self ref Dentry, msg: string)
{
	sys->print("%s name=%#q len name %d len array of byte d.name %d uid=%d gid=%d mode=#%8.8ux qid.path=#%bux qid.vers=%ud size=%bud\n",
		msg, d.name, len d.name, len array of byte d.name, d.uid, d.gid, d.mode, d.qid.path, d.qid.vers, d.size);
	p := d.iob;
	if(p != nil && (data := p.iobuf) != nil){
		for(slot:=0; slot<BUFSIZE/Dentrysize; slot++){
			qid := get8(data, slot*Dentrysize+Opath);
			qid &=  ~QPDIR;
			if(qid!= big 0 && d.qid.path == qid){
				sys->print("\tdblock=");
				for(i := 0; i < NDBLOCK; i++)
					sys->print(" %bd", get8(data, slot*Dentrysize+Odblock+i*8));
				sys->print("\tiblock=");
				for(i = 0; i < NIBLOCK; i++)
					sys->print(" %bd", get8(data, slot*Dentrysize+Oiblock+i*8));
				sys->print("\n");
			}
		}
	}
}

HWidth: con 5;	# initial number of buffers in each doubly linked list

# buffer pool = array of Hiob's = hiob
#	implements a locality based cache (lru cache).
#	hb := hiob[addr%len hiob]; is used to figure out
#		which array element to use
hiob: array of ref Hiob;

iobufinit(niob: int)
{
	nhiob := niob/HWidth;
	while(!prime(nhiob))
		nhiob++;
	hiob = array[nhiob] of {* => ref Hiob(nil, Lock.new(), 0)};
	# allocate the buffers now
	for(i := 0; i < len hiob; i++){
		h := hiob[i];
		while(h.niob < HWidth)
			h.newbuf();
	}
}

iobufclear()
{
	# eliminate the cyclic references
	for(i := 0; i < len hiob; i++){
		h := hiob[i];
		while(--h.niob >= 0){
			p := hiob[i].link;
			hiob[i].link = p.fore;
			p.fore = p.back = nil;
			p = nil;
		}
	}
}

prime(n: int): int
{
	if((n%2) == 0)
		return 0;
	for(i:=3;; i+=2) {
		if((n%i) == 0)
			return 0;
		if(i*i >= n)
			return 1;
	}
}

Hiob.newbuf(hb: self ref Hiob): ref Iobuf
{
	# hb must be locked
	p := ref Iobuf;
	p.qlock = chan[1] of int;
	q := hb.link;
	if(q != nil){
		p.fore = q;
		p.back = q.back;
		q.back = p;
		p.back.fore = p;
	}else{
		hb.link = p;
		p.fore = p;
		p.back = p;
	}
	p.dev = devnone;
	p.addr = big -1;
	p.flags = 0;
	p.xiobuf = array[RBUFSIZE] of byte;
	hb.niob++;
	return p;
}

Iobuf.get(dev: ref Device, addr: big, flags: int): ref Iobuf
{
	hb := hiob[int (addr%big len hiob)];
	p: ref Iobuf;
Search:
	for(;;){
		hb.lk.lock();
		s := hb.link;

		# see if it's active
		p = s;
		do{
			if(p.addr == addr && p.dev == dev){
				if(p != s){
					p.back.fore = p.fore;
					p.fore.back = p.back;
					p.fore = s;
					p.back = s.back;
					s.back = p;
					p.back.fore = p;
					hb.link = p;
				}
				hb.lk.unlock();
				p.lock();
				if(p.addr != addr || p.dev != dev){
					# lost race
					p.unlock();
					continue Search;
				}
				p.flags |= flags;
				p.iobuf = p.xiobuf;
				return p;
			}
		}while((p = p.fore) != s);
		if(flags == Bprobe){
			hb.lk.unlock();
			return nil;
		}

		# steal the oldest unlocked buffer
		do{
			p = s.back;
			if(p.canlock()){
				# TO DO: if Bmod, write it out and restart Hashed
				# for now we needn't because Iobuf.put is synchronous
				if(p.flags & Bmod)
					sys->print("Bmod unexpected (%bud)\n", p.addr);
				hb.link = p;
				p.dev = dev;
				p.addr = addr;
				p.flags = flags;
				break Search;
			}
			s = p;
		}while(p != hb.link);

		# no unlocked blocks available; add a new one
		p = hb.newbuf();
		p.lock();	# return it locked
		break;
	}

	p.dev = dev;
	p.addr = addr;
	p.flags = flags;
	hb.lk.unlock();
	p.iobuf = p.xiobuf;
	if(flags & Bread){
		if(wrenread(dev.fd, addr, p.iobuf)){
			eprint(sys->sprint("error reading block %bud: %r", addr));
			p.flags = 0;
			p.dev = devnone;
			p.addr = big -1;
			p.iobuf = nil;
			p.unlock();
			return nil;
		}
	}
	return p;
}

Iobuf.put(p: self ref Iobuf)
{
	if(p.flags & Bmod)
		p.flags |= Bimm;	# temporary; see comment in Iobuf.get
	if(p.flags & Bimm){
		if(!(p.flags & Bmod))
			eprint(sys->sprint("imm and no mod (%bd)", p.addr));
		if(!wrenwrite(p.dev.fd, p.addr, p.iobuf))
			p.flags &= ~(Bmod|Bimm);
		else
			panic(sys->sprint("error writing block %bud: %r", p.addr));
	}
	p.iobuf = nil;
	p.unlock();
}

Iobuf.lock(p: self ref Iobuf)
{
	p.qlock <-= 1;
}

Iobuf.canlock(p: self ref Iobuf): int
{
	alt{
	p.qlock <-= 1 =>
		return 1;
	* =>
		return 0;
	}
}

Iobuf.unlock(p: self ref Iobuf)
{
	<-p.qlock;
}

File.access(f: self ref File, d: ref Dentry, m: int): int
{
	if(wstatallow)
		return 0;

	# none gets only other permissions

	if(f.uid != None){
		if(f.uid == d.uid)	# owner
			if((m<<6) & d.mode)
				return 0;
		if(ingroup(f.uid, d.gid))	# group membership
			if((m<<3) & d.mode)
				return 0;
	}

	#
	# other access for everyone except members of group "noworld"
	#
	if(m & d.mode){
		#
		# walk directories regardless.
		# otherwise it's impossible to get
		# from the root to noworld's directories.
		#
		if((d.mode & DDIR) && (m == DEXEC))
			return 0;
		if(!ingroup(f.uid, Noworld))
			return 0;
	}
	return 1;
}

tagname(t: int): string
{
	case t {
	Tnone =>	return "Tnone";
	Tsuper =>	return "Tsuper";
	Tdir => return "Tdir";
	Tind1 => return "Tind1";
	Tind2 => return "Tind2";
	Tind3 => return "Tind3";
	Tind4 => return "Tind4";
	Tind5 => return "Tind5";
	Tind6 => return "Tind6";
	Tfile => return "Tfile";
	Tfree => return "Tfree";
	Tbuck => return "Tbuck";
	Tvirgo => return "Tvirgo";
	Tcache => return "Tcache";
	* =>	return sys->sprint("%d", t);
	}
}

# should be called nottag
#	returns a +ve value if the tag or qpath do not match
Iobuf.checktag(p: self ref Iobuf, tag: int, qpath: big): int
{
	t := Tag.unpack(p.iobuf[BUFSIZE:]);
	if(t.tag != tag){
		if(1)
			eprint(sys->sprint("	tag = %s; expected %s; addr = %bud\n",
				tagname(t.tag), tagname(tag), p.addr));
		return 2;
	}
	if(qpath != QPNONE){
		qpath &= ~QPDIR;
		if(qpath != t.path){
			if(qpath == (t.path&~QPDIR))	# old bug
				return 0;
			if(1)
				eprint(sys->sprint("	tag/path = %bux; expected %s/%bux\n",
					t.path, tagname(tag), qpath));
			return 1;
		}
	}
	return 0;
}

Iobuf.settag(p: self ref Iobuf, tag: int, qpath: big)
{
	Tag(tag, qpath).pack(p.iobuf[BUFSIZE:]);
	p.flags |= Bmod;
}

badmagic := 0;
wmagic := "kfs wren device\n";

wrenream(dev: ref Device)
{
	if(RBUFSIZE % 512)
		panic(sys->sprint("kfs: bad buffersize(%d): restart a multiple of 512", RBUFSIZE));
	if(RBUFSIZE > MAXBUFSIZE)
		panic(sys->sprint("kfs: bad buffersize(%d): must be at most %d", RBUFSIZE, MAXBUFSIZE));
	sys->print("kfs: reaming the file system using %d byte blocks\n", RBUFSIZE);
	buf := array[RBUFSIZE] of {* => byte 0};
	buf[256:] = sys->aprint("%s%d\n", wmagic, RBUFSIZE);
	if(sys->seek(dev.fd, big 0, 0) < big 0 || sys->write(dev.fd, buf, len buf) != len buf)
		panic("can't ream disk");
}

wreninit(dev: ref Device): int
{
	(ok, nil) := sys->fstat(dev.fd);
	if(ok < 0)
		return 0;
	buf := array[MAXBUFSIZE] of byte;
	sys->seek(dev.fd, big 0, 0);
	n := sys->read(dev.fd, buf, len buf);
	if(n < len buf)
		return 0;
	badmagic = 0;
	RBUFSIZE = DEFAULTBUFSIZE;
	if(string buf[256:256+len wmagic] != wmagic){
		badmagic = 1;
		return 0;
	}
	RBUFSIZE = int string buf[256+len wmagic:256+len wmagic+12];
	if(RBUFSIZE % 512)
		error("bad block size");
	return 1;
}

wrenread(fd: ref Sys->FD, addr: big, a: array of byte): int
{
	return sys->pread(fd, a, len a, addr * big RBUFSIZE) != len a;
}

wrenwrite(fd: ref Sys->FD, addr: big, a: array of byte): int
{
	return sys->pwrite(fd, a, len a, addr * big RBUFSIZE) != len a;
}

wrentag(buf: array of byte, tag: int, qpath: big): int
{
	t := Tag.unpack(buf[BUFSIZE:]);
	return t.tag != tag || (qpath&~QPDIR) != t.path;
}

wrencheck(fd: ref Sys->FD): int
{
	if(badmagic)
		return 1;
	buf := array[RBUFSIZE] of byte;
	if(wrenread(fd, SUPERADDR, buf) || wrentag(buf, Tsuper, QPSUPER) ||
	    wrenread(fd, ROOTADDR, buf) || wrentag(buf, Tdir, QPROOT))
		return 1;
	d0 := Dentry.unpack(buf);
	if(d0.mode & DALLOC)
		return 0;
	return 1;
}

wrensize(dev: ref Device): big
{
	(ok, d) := sys->fstat(dev.fd);
	if(ok < 0)
		return big -1;
	return (d.length / big RBUFSIZE);
}

checkname9p2(s: string): int
{
	for(i := 0; i < len s; i++)
		if(s[i] <= 8r40)
			return 0;
	return styx->utflen(s);
}

isro(d: ref Device): int
{
	return d == nil || d.ronly;
}

tlocks: list of ref Tlock;

tlocked(f: ref File, d: ref Dentry): ref Tlock
{
	tim := now();
	path := d.qid.path;
	t1: ref Tlock;
	for(l := tlocks; l != nil; l = tl l){
		t := hd l;
		if(t.qpath == path && t.time >= tim && t.dev == f.fs)
			return nil;	# it's locked
		if(t.file == nil || t1 == nil && t.time < tim)
			t1 = t;
	}
	t := t1;
	if(t == nil)
		t = ref Tlock;
	t.dev = f.fs;
	t.qpath = path;
	t.time = tim + TLOCK;
	tlocks = t :: tlocks;
	return t;
}

mkqid(path: big, vers: int, mode: int): Qid
{
	qid: Qid;

	qid.path = (path & ~QPDIR);
	qid.vers = vers;
	qid.qtype = 0;
	if(mode & DDIR)
		qid.qtype |= QTDIR;
	if(mode & DAPND)
		qid.qtype |= QTAPPEND;
	if(mode & DLOCK)
		qid.qtype |= QTEXCL;
	return qid;
}

dir9p2(d: ref Dentry): Sys->Dir
{
	dir: Sys->Dir;

	dir.name = d.name;
	dir.uid = uidtostr(d.uid);
	dir.gid = uidtostr(d.gid);
	dir.muid = uidtostr(d.muid);
	dir.qid = d.qid;
	dir.mode = d.mode & 8r777;
	if(d.mode & DDIR)
		dir.mode |= DMDIR;
	if(d.mode & DAPND)
		dir.mode |= DMAPPEND;
	if(d.mode & DLOCK)
		dir.mode |= DMEXCL;
	dir.atime = d.atime;
	dir.mtime = d.mtime;
	dir.length = d.size;
	dir.dtype = 0;
	dir.dev = 0;
	return dir;
}

rootream(dev: ref Device, addr: big)
{
	p := Iobuf.get(dev, addr, Bmod|Bimm);
	p.iobuf[0:] = emptyblock;
	p.settag(Tdir, QPROOT);
	d := Dentry.get(p, 0);
	d.name = "/";
	d.uid = -1;
	d.gid = -1;
	d.mode = DALLOC | DDIR |
		((DREAD|DWRITE|DEXEC) << 6) |
		((DREAD|DWRITE|DEXEC) << 3) |
		((DREAD|DWRITE|DEXEC) << 0);
	d.qid.path = QPROOT;
	d.qid.vers = 0;
	d.qid.qtype = QTDIR;
	d.atime = now();
	d.mtime = d.atime;
	d.change(~0);
	d.access(FREAD|FWRITE, -1);
	d.update();
	p.put();
}

superream(dev: ref Device, addr: big)
{
	fsize := wrensize(dev);
	if(fsize <= big 0)
		panic("file system device size");
	p := Iobuf.get(dev, addr, Bmod|Bimm);
	p.iobuf[0:] = emptyblock;
	p.settag(Tsuper, QPSUPER);
	sb := ref Superb;
	sb.iob = p;
	sb.fstart = big 1;
	sb.fsize = fsize;
	sb.qidgen = big 10;
	sb.tfree = big 0;
	sb.hwblock = big 2; # 0th block left out, super block at 1, root block at 2
	sb.fsok = 0;
	sb.fbuf = p.iobuf[Super1size:];
	put4(sb.fbuf, 0, 1);	# nfree = 1
	msg := "";
#	this is taking forever.
#		Check my notes in the kfs paper and inferno.notes
#		it is more efficient to do this when needed
#	for(i := fsize-big 1; i>=addr+big 2; i--){
	end := sb.fstart+big FEPERBUF**2;
	if(end > sb.fsize -big 1)
		end = sb.fsize -big 1;
	sys->print("kfs: ream %bd out of %bd blocks now:", end, fsize);
	for(i := end; i>=addr+big 2; i--){
		#sys->print("superream i %bd\n", i);
		if(debug){
			msg = sys->sprint(" %bd ", i);
			progress(msg);
		}
		addfree(dev, i, sb); # what does this do?
	}
	sb.hwblock = big end;
	sys->print("done\n");
	sb.put();
}

eprint(s: string)
{
	sys->print("kfs: %s\n", s);
}

#
# /adm/users
#
# uid:user:leader:members[,...]

User: adt {
	uid:	int;
	name:	string;
	leader:	int;
	mem:	list of int;
};

users: list of ref User;

admusers := array[] of {
	(-1, "adm", "adm"),
	(None, "none", "adm"),
	(Noworld, "noworld", nil),
	(10000, "sys", nil),
	(10001, "upas", "upas"),
	(10002, "bootes", "bootes"),
	(10006, "inferno", nil),
};

userinit()
{
	if(!cmd_users() && users == nil){
		cprint("initializing minimal user table");
		defaultusers();
	}
	writegroup = strtouid("write");
}

cmd_users(): int
{
	if(kopen(FID1, FID2, array[] of {"adm", "users"}, OREAD) != nil)
		return 0;
	buf: array of byte;
	for(off := big 0;;){
		(a, e) := kread(FID2, off, Styx->MAXFDATA);
		if(e != nil){
			cprint("/adm/users read error: "+e);
			return 0;
		}
		if(len a == 0)
			break;
		off += big len a;
		if(buf != nil){
			c := array[len buf + len a] of byte;
			if(buf != nil)
				c[0:] = buf;
			c[len buf:] = a;
			buf = c;
		}else
			buf = a;
	}
	kclose(FID2);

	# (uid:name:lead:mem,...\n)+
	(nl, lines) := sys->tokenize(string buf, "\n");
	if(nl == 0){
		cprint("empty /adm/users");
		return 0;
	}
	oldusers := users;
	users = nil;

	# first pass: enter id:name
	for(l := lines; l != nil; l = tl l){
		uid, name, r: string;
		s := hd l;
		if(s == "" || s[0] == '#')
			continue;
		(uid, r) = field(s, ':');
		(name, r) = field(r, ':');
		if(uid == nil || name == nil || string int uid != uid){
			cprint("invalid /adm/users line: "+hd l);
			users = oldusers;
			return 0;
		}
		adduser(int uid, name, nil, nil);
	}

	# second pass: groups and leaders
	for(l = lines; l != nil; l = tl l){
		s := hd l;
		if(s == "" || s[0] == '#')
			continue;
		name, lead, mem, r: string;
		(nil, r) = field(s, ':');	# skip id
		(name, r) = field(r, ':');
		(lead, mem) = field(r, ':');
		(nil, mems) := sys->tokenize(mem, ",\n");
		if(name == nil || lead == nil && mems == nil)
			continue;
		u := finduname(name);
		if(lead != nil){
			lu := strtouid(lead);
			if(lu != None)
				u.leader = lu;
			else if(lead != nil)
				u.leader = u.uid;	# mimic kfs not fs
		}
		mids: list of int = nil;
		for(; mems != nil; mems = tl mems){
			lu := strtouid(hd mems);
			if(lu != None)
				mids = lu :: mids;
		}
		u.mem = mids;
	}

	if(debug)
	for(x := users; x != nil; x = tl x){
		u := hd x;
		sys->print("%d : %q : %d :", u.uid, u.name, u.leader);
		for(y := u.mem; y != nil; y = tl y)
			sys->print(" %d", hd y);
		sys->print("\n");
	}
	return 1;
}

field(s: string, c: int): (string, string)
{
	for(i := 0; i < len s; i++)
		if(s[i] == c)
			return (s[0:i], s[i+1:]);
	return (s, nil);
}

defaultusers()
{
	for(i := 0; i < len admusers; i++){
		(id, name, leader) := admusers[i];
		adduser(id, name, leader, nil);
	}
}

finduname(s: string): ref User
{
	for(l := users; l != nil; l = tl l){
		u := hd l;
		if(u.name == s)
			return u;
	}
	return nil;
}

uidtostr(id: int): string
{
	if(id == None)
		return "none";
	for(l := users; l != nil; l = tl l){
		u := hd l;
		if(u.uid == id)
			return u.name;
	}
	return sys->sprint("#%d", id);
}

leadgroup(ui: int, gi: int): int
{
	for(l := users; l != nil; l = tl l){
		u := hd l;
		if(u.uid == gi){
			if(u.leader == ui)
				return 1;
			if(u.leader == 0)
				return ingroup(ui, gi);
			return 0;
		}
	}
	return 0;
}

strtouid(s: string): int
{
	if(s == "none")
		return None;
	u := finduname(s);
	if(u != nil)
		return u.uid;
	return 0;
}

ingroup(uid: int, gid: int): int
{
	if(uid == gid)
		return 1;
	for(l := users; l != nil; l = tl l){
		u := hd l;
		if(u.uid == gid){
			for(m := u.mem; m != nil; m = tl m)
				if(hd m == uid)
					return 1;
			return 0;
		}
	}
	return 0;
}

baduname(s: string): int
{
	n := checkname9p2(s);
	if(n == 0 || n+1 > NAMELEN || s == "." || s == ".."){
		sys->print("kfs: illegal user name %q\n", s);
		return 1;
	}
	return 0;
}

adduser(id: int, name: string, leader: string, mem: list of string)
{
	if(baduname(name))
		return;
	for(l := users; l != nil; l = tl l){
		u := hd l;
		if(u.uid == id){
			sys->print("kfs: duplicate user ID %d (name %q)\n", id, u.name);
			return;
		}else if(u.name == name){
			sys->print("kfs: duplicate user name %q (id %d)\n", name, u.uid);
			return;
		}
	}
	if(name == leader)
		lid := id;
	else if(leader == nil)
		lid = 0;
	else if(!baduname(leader))
		lid = strtouid(leader);
	else
		return;
	memid: list of int;
	for(; mem != nil; mem = tl mem){
		if(baduname(hd mem))
			return;
		x := strtouid(hd mem);
		if(x != 0)
			memid = x :: memid;
	}
	u := ref User(id, name, lid, memid);
	users = u :: users;
}

Lock.new(): ref Lock
{
	return ref Lock(chan[1] of int);
}

Lock.lock(l: self ref Lock)
{
	l.c <-= 1;
}

Lock.canlock(l: self ref Lock): int
{
	alt{
	l.c <-= 1 =>
		return 1;
	* =>
		return 0;
	}
}

Lock.unlock(l: self ref Lock)
{
	<-l.c;
}

#
# kfs check, could be a separate module if that seemed important
#
# check() kicks off the fsck() on the root directory
# fsck() walks through each child file and directory
#	and marks every block and qid that are being used
#	in amap and qmap. If the child is a directory, then fsck()
#	descends into it and fsck()'s each child.
#	if a bit has already been marked, then we have a duplicate
#	if a block number is <= fstart and >= fsize, then bad

MAXDEPTH: con 100;
MAXNAME: con 4000;

# bit map
# bit array with each bit representing a block
Map: adt {
	lo, hi:	big;
	bits:	array of byte;
	nbad:	big;
	ndup:	big;
	nmark:	big;

	new:	fn(lo, hi: big): ref Map;
	isset:	fn(b: self ref Map, a: big): int;
	mark:	fn(b: self ref Map, a: big): string;
};

Check: adt {
	dev:	ref Device;

	amap:	ref Map;	# bit map of all blocks
	qmap:	ref Map;	# bit map of max qid used + 100

	name:	string;
	nfiles:	big;
	maxq:	big;

	mod:	int;
	flags:	int;
	oldblock:	big;

	depth:	int;
	maxdepth:	int;

	check:	fn(c: self ref Check);
	touch:	fn(c: self ref Check, a: big): int;
	checkdir:	fn(c: self ref Check, a: big, qpath: big): int;
	checkindir:	fn(c: self ref Check, a: big, d: ref Dentry, qpath: big, indir: int): int;
	maked:	fn(c: self ref Check, a: big, s: int, qpath: big): ref Dentry;
	modd:	fn(c: self ref Check, a: big, s: int, d: ref Dentry);
	fsck:		fn(c: self ref Check, d: ref Dentry): int;
	xread:	fn(c: self ref Check, a: big, qpath: big);
	xtag:		fn(c: self ref Check, a: big, tag: int, qpath: big): ref Iobuf;
	ckfreelist:	fn(c: self ref Check, sb: ref Superb);
	mkfreelist:	fn(c: self ref Check, sb: ref Superb);
	amark:	fn(c: self ref Check, a: big): int;
	fmark:	fn(c: self ref Check, a: big): int;
	missing:	fn(c: self ref Check, sb: ref Superb);
	qmark:	fn(c: self ref Check, q: big);
};

check(dev: ref Device, flag: int)
{
	#mainlock.wlock();
	#mainlock.wunlock();
	c := ref Check;
	c.dev = dev;
	c.nfiles = big 0;
	c.maxq = big 0;
	c.mod = 0;
	c.flags = flag;
	c.oldblock = big 0;
	c.depth = 0;
	c.maxdepth = 0;
	c.check();
}

checkflags(s: string): int
{
	f := 0;
	for(i := 0; i < len s; i++)
		case s[i] {
		'r' =>	f |= Crdall;
		't' => f |= Ctag;
		'P' => f |= Cpfile;
		'p' => f |= Cpdir;
		'f' => f |= Cfree;
		'c' => f |= Cream;
		'd' => f |= Cbad;
		'w' => f |= Ctouch;
		'q' => f |= Cquiet;
		'v' => ;	# old verbose flag; ignored
		* =>	return -1;
	}
	return f;
}

Check.check(c: self ref Check)
{
	sbaddr := SUPERADDR;
	p := c.xtag(sbaddr, Tsuper, QPSUPER);
	if(p == nil){
		cprint(sys->sprint("bad superblock"));
		return;
	}
	sb := Superb.unpack(p.iobuf);
	sb.iob = p;

	fstart := sb.fstart;
	if(fstart != big 1){
		cprint(sys->sprint("invalid superblock"));
		return;
	}
	fsize := sb.fsize;
	if(fsize < fstart || fsize > wrensize(c.dev)){
		cprint(sys->sprint("invalid size in superblock"));
		return;
	}
	hwblock := sb.hwblock;
	if(hwblock < fstart || hwblock > fsize){
		cprint(sys->sprint("invalid hwblock in superblock"));
		return;
	}
	c.amap = Map.new(fstart, hwblock);

	nqid := sb.qidgen+big 100;		# not as much of a botch
	if(nqid > big (1024*1024*8)){
		cprint(sys->sprint("nqid > big (1024*1024*8)"));
		nqid = big (1024*1024*8);
	}
	if(nqid < big (64*1024))
		nqid = big (64*1024);
	c.qmap = Map.new(big 0, nqid);

	c.mod = 0;
	c.depth = 0;
	c.maxdepth = 0;

	if(c.amark(sbaddr))
		{}

	if(!(c.flags & Cquiet))
		cprint(sys->sprint("checking file system: %s", "main"));
	c.nfiles = big 0;
	c.maxq = big 0;

	d := c.maked(ROOTADDR, 0, QPROOT);
	if(d != nil){
		if(c.amark(ROOTADDR))
			{}
		if(c.fsck(d))
			c.modd(ROOTADDR, 0, d);
		if(--c.depth != 0)
			cprint("depth not zero on return");
	}
	if(sb.qidgen < c.maxq)
		cprint(sys->sprint("qid generator low path=%bd maxq=%bd", sb.qidgen, c.maxq));

	nqbad := c.qmap.nbad + c.qmap.ndup;
	c.qmap = nil;	# could use to implement resequence

	ndup := c.amap.ndup;
	nused := c.amap.nmark;

	c.amap.ndup = c.amap.nmark = big 0;	# reset for free list counts
	if(c.flags & Cfree){
		c.name = "free list";
		c.mkfreelist(sb);
		sb.qidgen = c.maxq;
		p.settag(Tsuper, QPNONE);
	}else
		c.ckfreelist(sb);

	nbad := c.amap.nbad;
	nfdup := c.amap.ndup;
	nfree := c.amap.nmark;
	# leave amap for missing, below

	if(c.mod){
		cprint("file system was modified");
		p.settag(Tsuper, QPNONE);
	}

	if(!(c.flags & Cquiet)){
		cprint(sys->sprint("%8bd files", c.nfiles));
		cprint(sys->sprint("%8bd blocks in the file system", fsize-fstart));
		cprint(sys->sprint("%8bd used blocks", nused));
		cprint(sys->sprint("%8bd free blocks", sb.tfree+fsize-hwblock));
	}
	if(!(c.flags & Cfree)){
		if(nfree != sb.tfree)
			cprint(sys->sprint("%8bd free blocks found", nfree));
		if(nfdup > big 0)
			cprint(sys->sprint("%8bd blocks duplicated in the free list", nfdup));
		if(fsize-fstart-nused-nfree > big 0)
			cprint(sys->sprint("%8bd missing blocks", hwblock-fstart-nused-nfree));
	}
	if(ndup > big 0)
		cprint(sys->sprint("%8bd address duplications", ndup));
	if(nbad > big 0)
		cprint(sys->sprint("%8bd bad block addresses", nbad));
	if(nqbad > big 0)
		cprint(sys->sprint("%8bd bad qids", nqbad));
	if(!(c.flags & Cquiet))
		cprint(sys->sprint("%8bd maximum qid path", c.maxq));
	c.missing(sb);

	sb.put();
}

Check.touch(c: self ref Check, a: big): int
{
	if((c.flags&Ctouch) && a > big 0){
		p := Iobuf.get(c.dev, a, Bread|Bmod);
		if(p != nil)
			p.put();
		return 1;
	}
	return 0;
}

# check directory Dentry at address a
Check.checkdir(c: self ref Check, a: big, qpath: big): int
{
	 ns := len c.name;
	 dmod := c.touch(a);
	 for(i:=0; i<DIRPERBUF; i++){
		nd := c.maked(a, i, qpath);
		if(nd == nil)
			break;
		if(c.fsck(nd)){
			c.modd(a, i, nd);
			dmod++;
		}
		c.depth--;
		c.name = c.name[0:ns];
	 }
	 c.name = c.name[0:ns];
	 return dmod;
}

# check a block of pointers to blocks
#	the block pointed to has a Dentry if indirection = 1
#	else it is anoher block of pointers - multiple levels of indirection
#	recursively drills through each level of indirection
Check.checkindir(c: self ref Check, a: big, d: ref Dentry, qpath: big, indir: int): int
{
	dmod := c.touch(a);
	ind := 0;
	case indir
	{
		1 => ind = Tind1;
		2 => ind = Tind2;
		3 => ind = Tind3;
		4 => ind = Tind4;
		5 => ind = Tind5;
		6 => ind = Tind6;
		* => cprint(sys->sprint("Check.checkindir invalid indirection indir %d\n", indir));
			 return dmod+1; # TODO is this correct?
	}
	p := c.xtag(a, ind, qpath);
	if(p == nil)
		return dmod;
	for(i:=0; i<int INDPERBUF; i++){
		a = get8(p.iobuf, i*8);
		if(a == big 0)
			continue;
		if(c.amark(a)){
			if(c.flags & Cbad){
				put8(p.iobuf, i*8, big 0);
				p.flags |= Bmod;
			}
			continue;
		}
		if(d.mode & DDIR){
			if(indir == 1)
				dmod += c.checkdir(a, qpath);
			else
				dmod += c.checkindir(a, d, qpath, indir-1);
		}else if(c.flags & Crdall)
			c.xread(a, qpath);
	}
	p.put();
	return dmod;
}

Check.fsck(c: self ref Check, d: ref Dentry): int
{
	# p: ref Iobuf;
	i: int;
	a, qpath: big;

	if(++c.depth >= c.maxdepth){
		c.maxdepth = c.depth;
		if(c.maxdepth >= MAXDEPTH){
			cprint(sys->sprint("max depth exceeded: %s", c.name));
			return 0;
		}
	}
	dmod := 0;
	if(!(d.mode & DALLOC))
		return 0;
	c.nfiles++;

	ns := len c.name;
	i = styx->utflen(d.name);
	if(i >= NAMELEN){
		d.name[NAMELEN-1] = 0;	# TO DO: not quite right
		cprint(sys->sprint("%q.name (%q) not terminated", c.name, d.name));
		return 0;
	}
	ns += i;
	if(ns >= MAXNAME){
		cprint(sys->sprint("%q.name (%q) name too large", c.name, d.name));
		return 0;
	}
	c.name += d.name;

	if(d.mode & DDIR){
		if(ns > 1)
			c.name += "/";
		if(c.flags & Cpdir)
			cprint(sys->sprint("%s", c.name));
	} else if(c.flags & Cpfile)
		cprint(sys->sprint("%s", c.name));

	qpath = d.qid.path & ~QPDIR;
	c.qmark(qpath);
	if(qpath > c.maxq)
		c.maxq = qpath;
	for(i=0; i<NDBLOCK; i++){
		a = get8(d.buf, Odblock+i*8);
		if(a == big 0)
			continue;
		if(c.amark(a)){
			put8(d.buf, Odblock+i*8, big 0); # erasing the block, something wrong
			dmod++;
			continue;
		}
		if(d.mode & DDIR)
			dmod += c.checkdir(a, qpath);
		else if(c.flags & Crdall)
			c.xread(a, qpath);
	}
	for(i=0; i<NIBLOCK; i++){
		a = get8(d.buf, Oiblock+i*8);
		if(a == big 0)
			continue;
		if(c.amark(a)){
			put8(d.buf, Oiblock+i*8, big 0); # erasing the block, something wrong
			dmod++;
			continue;
		}
		if(d.mode & DDIR)
			dmod += c.checkindir(a, d, qpath, i+1);
		else if(c.flags & Crdall)
			c.xread(a, qpath);
	}
	return dmod;
}

Check.ckfreelist(c: self ref Check, sb: ref Superb)
{
	c.name = "free list";
	cprint(sys->sprint("check %s", c.name));
	fb := sb.fbuf;
	a := SUPERADDR;
	p: ref Iobuf;
	lo := big 0;
	hi := big 0;
	for(;;){
		n := get4(fb, 0);		# nfree
		if(n < 0 || n > FEPERBUF){
			cprint(sys->sprint("check: nfree bad %bd", a));
			break;
		}
		for(i:=1; i<n; i++){
			a = get8(fb, 4+i*8);	# free[i]
			if(a > big 0 && !c.fmark(a)){
				if(lo == big 0 || lo > a)
					lo = a;
				if(hi == big 0 || hi < a)
					hi = a;
			}
		}
		a = get8(fb, 4);	# free[0]
		if(a == big 0)
			break;
		if(c.fmark(a))
			break;
		if(lo == big 0 || lo > a)
			lo = a;
		if(hi == big 0 || hi < a)
			hi = a;
		if(p != nil)
			p.put();
		p = c.xtag(a, Tfree, QPNONE);
		if(p == nil)
			break;
		fb = p.iobuf;
	}
	if(p != nil)
		p.put();
	cprint(sys->sprint("lo = %bd; hi = %bd", lo, hi));
}

#
# make freelist from scratch
#
Check.mkfreelist(c: self ref Check, sb: ref Superb)
{
	sb.fbuf[0:] = emptyblock[0:4+FEPERBUF*8];
	sb.tfree = big 0;
	put4(sb.fbuf, 0, 1);	# nfree = 1
	if(sb.hwblock <= big 0)
		panic(sys->sprint("Check.mkfreelist bad hwblock <= 0: %bd", sb.hwblock));
	for(a:=sb.hwblock-sb.fstart-big 1; a >= big 0; a--){
		i := a>>3;
		if(i < big 0 || i >= big len c.amap.bits)
			continue;
		b := byte (1 << int (a&big 7));
		if((c.amap.bits[int i] & b) != byte 0)
			continue;
		addfree(c.dev, sb.fstart+a, sb);
		c.amap.bits[int i] |= b;
	}
	sb.iob.flags |= Bmod;
}

#
# makes a copy of a Dentry's representation on disc so that
# the rest of the much larger iobuf can be freed.
#
Check.maked(c: self ref Check, a: big, s: int, qpath: big): ref Dentry
{
	p := c.xtag(a, Tdir, qpath);
	if(p == nil)
		return nil;
	d := Dentry.get(p, s);
	if(d == nil)
		return nil;
	copy := array[len d.buf] of byte;
	copy[0:] = d.buf;
	d.put();
	d.buf = copy;
	return d;
}

Check.modd(c: self ref Check, a: big, s: int, d1: ref Dentry)
{
	if(!(c.flags & Cbad))
		return;
	p := Iobuf.get(c.dev, a, Bread);
	d := Dentry.get(p, s);
	if(d == nil){
		if(p != nil)
			p.put();
		return;
	}
	d.buf[0:] = d1.buf;
	p.flags |= Bmod;
	p.put();
}

Check.xread(c: self ref Check, a: big, qpath: big)
{
	p := c.xtag(a, Tfile, qpath);
	if(p != nil)
		p.put();
}

Iobuf.print(iob: self ref Iobuf, msg: string)
{
	sys->print("%s show Iobuf\n", msg);
	buf := iob.iobuf[0:];
	if(iob != nil)
		for(i:= 0; i<RBUFSIZE/8; i++){
			sys->print("%d 0x%bux	", i*8, get8(buf, i*8));
		}
	sys->print("\n");
}

Check.xtag(c: self ref Check, a: big, tag: int, qpath: big): ref Iobuf
{
	if(a == big 0)
		return nil;
	p := Iobuf.get(c.dev, a, Bread);
	if(p == nil){
		cprint(sys->sprint("check: \"%s\": xtag: p null", c.name));
		if(c.flags & (Cream|Ctag)){
			p = Iobuf.get(c.dev, a, Bmod);
			if(p != nil){
				p.iobuf[0:] = emptyblock;
				p.settag(tag, qpath);
				c.mod++;
				return p;
			}
		}
		return nil;
	}
	if(p.checktag(tag, qpath)){
		cprint(sys->sprint("check: \"%s\": xtag: checktag", c.name));
		if(c.flags & Cream)
			p.iobuf[0:] = emptyblock;
		if(c.flags & (Cream|Ctag)){
			p.settag(tag, qpath);
			c.mod++;
		}
		return p;
	}
	return p;
}

Check.amark(c: self ref Check, a: big): int
{
	e := c.amap.mark(a);
	if(e != nil){
		cprint(sys->sprint("check: \"%s\": %s %bd", c.name, e, a));
		return e != "dup";	# don't clear dup blocks because rm might repair
	}
	return 0;
}

Check.fmark(c: self ref Check,a: big): int
{
	e := c.amap.mark(a);
	if(e != nil){
		cprint(sys->sprint("check: \"%s\": %s %bd", c.name, e, a));
		return 1;
	}
	return 0;
}

Check.missing(c: self ref Check, sb: ref Superb)
{
	n := 0;
	for(a:=sb.hwblock-sb.fstart-big 1; a>=big 0; a--){
		i := a>>3;
		b := byte (1 << int (a&big 7));
		if((c.amap.bits[int i] & b) == byte 0){
			cprint(sys->sprint("missing: %bd", sb.fstart+a));
			n++;
		}
		if(n > 10){
			cprint(sys->sprint(" ..."));
			break;
		}
	}
}

Check.qmark(c: self ref Check, qpath: big)
{
	e := c.qmap.mark(qpath);
	if(e != nil){
		if(c.qmap.nbad+c.qmap.ndup < big 20)
			cprint(sys->sprint("check: \"%s\": qid %s 0x%bux", c.name, e, qpath));
	}
}

Map.new(lo, hi: big): ref Map
{
	m := ref Map;
	n := (hi-lo+big 7)>>3;
	m.bits = array[int n] of {* => byte 0};
	m.lo = lo;
	m.hi = hi;
	m.nbad = big 0;
	m.ndup = big 0;
	m.nmark = big 0;
	return m;
}

Map.isset(m: self ref Map, i: big): int
{
	if(i < m.lo || i >= m.hi)
		return -1;	# hard to say
	i -= m.lo;
	return (m.bits[int (i>>3)] & byte (1<< int (i&big 7))) != byte 0;
}

Map.mark(m: self ref Map, i: big): string
{
	if(i < m.lo || i >= m.hi){
		m.nbad++;
		return "out of range";
	}
	i -= m.lo;
	b := byte (1 << int (i&big 7));
	i >>= 3;
	if((m.bits[int i] & b) != byte 0){
		m.ndup++;
		return "dup";
	}
	m.bits[int i] |= b;
	m.nmark++;
	return nil;
}

cprint(s: string)
{
	if(consoleout != nil)
		consoleout <-= s+"\n";
	else
		eprint(s);
}
