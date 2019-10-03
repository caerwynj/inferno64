implement AMinus;

include "sys.m"; sys: Sys;
include "draw.m";
include "bufio.m"; bufio: Bufio;
	Iobuf: import bufio;

AMinus: module {
	init: fn(nil: ref Draw->Context, args: list of string);
};

pname: string;

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	bufio = load Bufio Bufio->PATH;

	indents := "\t";

	if(args != nil) {
		pname = hd args;
		args = tl args;
	} else {
		pname = "a-";
	}

	if(args != nil)
		indents = hd args;

	unindent(indents);
}

unindent(s: string)
{
	stdin := bufio->fopen(sys->fildes(0), bufio->OREAD);
	if(stdin == nil) {
		sys->fprint(sys->fildes(2), "%s: Couldn't create a bufio:  %r\n", pname);
		raise "fail:errors";
	}

	while((line := stdin.gets('\n')) != nil) {
		if(len line >= len s && line[0:len s] == s)
			line = line[len s:];
		sys->print("%s", line);
	}
}
