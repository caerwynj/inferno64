implement Tac;

include "sys.m"; sys: Sys;
include "bufio.m"; bufio: Bufio; Iobuf: import bufio;
include "draw.m";

Tac: module {
	init: fn(nil: ref Draw->Context, args: list of string);
};


stdout: ref Sys->FD;

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	bufio = load Bufio Bufio->PATH;
	stdout = sys->fildes(1);
	args = tl args;

	if(args == nil)
		args = "-" :: nil;

	for(; args != nil; args = tl args) {
		file := hd args;
		if(file != "-") {
			fd := sys->open(file, Sys->OREAD);
			if(fd == nil){
				sys->fprint(sys->fildes(2), "tac: cannot open %s: %r\n", file);
				raise "fail:bad open";
			}
			tac(fd, file);
		} else {
			tac(sys->fildes(0), "<stdin>");
		}
	}
}

tac(fd: ref Sys->FD, file: string)
{
	lines: list of string = nil;
	line: string;

	fio := bufio->fopen(fd, bufio->OREAD);
	if(fio == nil) {
		sys->fprint(sys->fildes(2), "tac: Couldn't create a bufio for %s:  %r\n", file);
		raise "fail:bufio";
	}

	while((line = fio.gets('\n')) != nil)
		lines = line :: lines;

	while(lines != nil) {
		buf := array of byte (hd lines);
		sys->write(stdout, buf, len buf);
		lines = tl lines;
	}
}
