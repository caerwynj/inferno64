implement Whoami;

# Who are you?

include "sys.m";
	sys: Sys;

include "draw.m";

Whoami: module {
	init: fn(nil: ref Draw->Context, nil: list of string);
};

init(nil: ref Draw->Context, nil: list of string) {
	sys = load Sys Sys->PATH;

	sys->print("%s\n", readfile("/dev/user"));

	exit;
}

# Reads a (small) file into a string
readfile(f: string): string {
	fd := sys->open(f, sys->OREAD);
	if(fd == nil)
		return nil;

	buf := array[8192] of byte;
	n := sys->read(fd, buf, len buf);
	if(n < 0)
		return nil;

	return string buf[0:n];	
}

