implement Lszip;

include "sys.m";
	sys: Sys;
	sprint: import sys;
include "draw.m";
include "arg.m";
include "bufio.m";
include "zip.m";
	zip: Zip;
	Fhdr, CDFhdr, Endofcdir: import zip;

Lszip: module {
	init:	fn(nil: ref Draw->Context, args: list of string);
};

dflag: int;

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	arg := load Arg Arg->PATH;
	zip = load Zip Zip->PATH;
	zip->init();

	arg->init(args);
	arg->setusage(arg->progname()+" [-d] file");
	while((c := arg->opt()) != 0)
		case c {
		'd' =>	zip->dflag = dflag++;
		* =>	arg->usage();
		}
	args = arg->argv();
	if(len args != 1)
		arg->usage();

	fd := sys->open(hd args, Sys->OREAD);
	if(fd == nil)
		fail(sprint("open: %r"));

	(nil, fhdrs, err) := zip->open(fd);
	if(err != nil)
		fail("parsing zip: "+err);

	for(i := 0; i < len fhdrs; i++)
		sys->print("%q\n", fhdrs[i].filename);
}

fail(s: string)
{
	sys->fprint(sys->fildes(2), "%s\n", s);
	raise "fail:"+s;
}
