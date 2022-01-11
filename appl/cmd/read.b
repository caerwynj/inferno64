implement Read;
include "sys.m"; 
	sys: Sys;
include "draw.m";

Read: module {
	init: fn(nil: ref Draw->Context, argv: list of string);
};

usage()
{
	sys->fprint(sys->fildes(2), "usage: read [-[ero] offset] count [file]\n");
	raise "fail:usage";
}

init(nil: ref Draw->Context, argv: list of string)
{
	sys = load Sys Sys->PATH;
	# usage: read [-[ero] offset] count
	count := Sys->ATOMICIO;
	offset := big 0;
	seeking := -1;
	fd := sys->fildes(0);
	if (argv != nil)
		argv = tl argv;
	if (argv != nil && hd argv != nil && (hd argv)[0] == '-') {
		if (tl argv == nil)
			usage();
		case hd argv {
		"-o" =>
			seeking = Sys->SEEKSTART;
		"-e" =>
			seeking = Sys->SEEKEND;
		"-r" =>
			seeking = Sys->SEEKRELA;
		* =>
			usage();
		}
		offset = big hd tl argv;
		argv = tl tl argv;
	}
	if (argv != nil) {
		count = int hd argv;
		if (tl argv != nil){
			file := hd tl argv; # usage();
			fd = sys->open(file, Sys->OREAD);
			if(fd == nil){
				sys->fprint(sys->fildes(2), "read: cannot open %s: %r\n", file);
				raise "fail:bad open";
			}
		}
	}
	if (seeking != -1)
		sys->seek(fd, offset, seeking);
	if (count == 0)
		return;
	buf := array[count] of byte;
	n := sys->read(fd, buf, len buf);
	if (n > 0)
		sys->write(sys->fildes(1), buf, n);
	else {
		if (n == -1) {
			sys->fprint(sys->fildes(2), "read: read error: %r\n");
			raise "fail:error";
		}
		raise "fail:eof";
	}
}
