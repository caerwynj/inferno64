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

	if(len argv < 3)
		usage();

	argv = tl argv;

	out := tl argv;
	s := "";
	for(l := out; l != nil; l = tl l){
		w := hd l;
		(toks, nil) := str->qtokenize(w);
		if(len toks > 1)
			w = str->quoted(w :: nil);
		s += w + " ";
	}
	(nil, err) := str->qtokenize(s);
	if(err != "")
		s = str->quoted(out);

	sys->print("%s\n", s);

	exit;
}

usage() {
	sys->fprint(stderr, "usage: tl (list 'of tokens')\n");
	exit;
}
