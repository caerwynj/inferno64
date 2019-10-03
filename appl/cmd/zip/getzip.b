implement Getzip;

include "sys.m";
	sys: Sys;
	sprint: import sys;
include "draw.m";
include "arg.m";
include "string.m";
	str: String;
include "bufio.m";
include "zip.m";
	zip: Zip;
	Fhdr, CDFhdr, Endofcdir: import zip;

Getzip: module {
	init:	fn(nil: ref Draw->Context, args: list of string);
};

dflag: int;
kflag: int;
vflag: int;

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	arg := load Arg Arg->PATH;
	str = load String String->PATH;
	zip = load Zip Zip->PATH;
	zip->init();

	# for zip library
	sys->pctl(Sys->FORKNS, nil);
	if(sys->bind("#s", "/chan", Sys->MREPL) < 0)
		fail(sprint("bind /chan: %r"));

	arg->init(args);
	arg->setusage(arg->progname()+" [-dkv] zipfile [path ...]");
	while((c := arg->opt()) != 0)
		case c {
		'd' =>	zip->dflag = dflag++;
		'k' =>	kflag++;
		'v' =>	vflag++;
		* =>	arg->usage();
		}
	args = arg->argv();
	if(len args == 0)
		arg->usage();

	fd := sys->open(hd args, Sys->OREAD);
	if(fd == nil)
		fail(sprint("open: %r"));

	(nil, fhdrs, err) := zip->open(fd);
	if(err != nil)
		fail("parsing zip: "+err);

	all := tl args == nil;
	paths: array of string;
	if(!all) {
		i := 0;
		paths = array[len args-1] of string;
		for(l := tl args; l != nil; l = tl l)
			paths[i++] = zip->sanitizepath(hd l);
	}
File:
	for(i := 0; i < len fhdrs && (all || len paths > 0 && paths[0] != nil); i++) {
		if(!all && !match(paths, fhdrs[i].filename))
			continue;

		f := "./"+fhdrs[i].filename;
		if(f[len f-1] == '/') {
			merr := mkdirs(f[2:]);
			if(merr != nil) {
				warn(merr);
				continue;
			}
			if(vflag)
				sys->print("%q\n", fhdrs[i].filename);
			continue;
		} else
			mkdirs(str->splitstrr(f[2:], "/").t0);

		(zfd, nil, zerr) := zip->openfile(fd, fhdrs[i]);
		if(zerr != nil) {
			warn(sprint("open %q in zip file: %s", f, zerr));
			continue;
		}

		flags := Sys->OWRITE;
		if(kflag)
			flags = Sys->OEXCL;
		ofd := sys->create(f, flags, 8r666);
		if(ofd == nil) {
			warn(sprint("create %q: %r", f));
			continue;
		}

		buf := array[Sys->ATOMICIO] of byte;
		for(;;) {
			n := sys->read(zfd, buf, len buf);
			if(n < 0) {
				warn(sprint("reading from %q from zip: %r", f));
				continue File;
			}
			if(n == 0)
				break;
			if(sys->write(ofd, buf, n) != n)
				warn(sprint("writing %q: %r", f));
		}

		if(vflag)
			sys->print("%q\n", fhdrs[i].filename);
	}

	for(i = 0; !all && i < len paths && paths[i] != nil; i++)
		warn(sprint("path %q not in archive", paths[i++]));
}

mkdirs(s: string): string
{
	p := "";
	lasterr := 0;
	for(l := sys->tokenize(s, "/").t1; l != nil; l = tl l) {
		if(p != nil)
			p[len p] = '/';
		p += hd l;
		lasterr = sys->create(p, Sys->OEXCL|Sys->OREAD, Sys->DMDIR|8r777) == nil;
	}
	if(lasterr)
		return sprint("create ./%q: %r", p);
	return nil;
}

match(paths: array of string, s: string): int
{
	for(i := 0; i < len paths; i++)
		if(paths[i] == nil) {
			return 0;
		} else if(paths[i] == s) {
			paths[i:] = paths[i+1:];
			paths[len paths-1] = nil;
			return 1;
		}
	return 0;
}

warn(s: string)
{
	sys->fprint(sys->fildes(2), "%s\n", s);
}

fail(s: string)
{
	warn(s);
	raise "fail:"+s;
}
