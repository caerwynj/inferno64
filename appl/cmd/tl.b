implement Tl;

include "sys.m";
	sys: Sys;

include "draw.m";

include "string.m";

stderr: ref Sys->FD;

Tl: module {
	init:	fn(nil: ref Draw->Context, argv: list of string);
};


init(nil: ref Draw->Context, argv: list of string)
{
	sys = load Sys Sys->PATH;
	stderr = sys->fildes(2);
	str := load String String->PATH;

	if(len argv < 2)
		usage();

	argv = tl argv;

	out := str->quoted(tl str->unquoted(str->quoted(argv)));
	sys->print("%s\n", out);

	exit;
}

usage() {
	sys->fprint(stderr, "usage: tl (list 'of tokens')\n");
	exit;
}
