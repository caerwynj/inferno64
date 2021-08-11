#
#	simple Init that calls /dis/init, a shell script to continue initialization
#
implement Init;

include "sys.m";
include "draw.m";

sys: Sys;
FD: import sys;
print, fprint, bind: import sys;

stderr:	ref sys->FD;						# standard error FD

Init: module
{
	init:	fn(nil: ref Draw->Context, nil: list of string);
};

Sh: module
{
	init:	fn(ctxt: ref Draw->Context, argv: list of string);
};

init(nil: ref Draw->Context, nil: list of string)
{
	sys = load Sys Sys->PATH;
	stderr = sys->fildes(2);

	sys->print("Welcome to Inferno...\n");

	# set up basic devices, ignoring errors
	# 9front does this in the shell. Can move them to dis/init later
	sys->bind("#b", "/dev", sys->MAFTER);	# kbd
	sys->bind("#c", "/dev", sys->MAFTER);	# console device
	sys->bind("#d", "/fd", Sys->MREPL);		# dup(3)
	sys->bind("#e", "/env", sys->MAFTER);	# env
#	sys->bind("#i", "/dev", sys->MREPL);	# draw device
	sys->bind("#l", "/net", sys->MAFTER);	# Network interfaces
	sys->bind("#m","/dev",sys->MAFTER);     # pointer/mouse
	sys->bind("#p", "/prog", sys->MREPL);	# prog device
	sys->bind("#r", "/dev", sys->MAFTER);	# rtc
	sys->bind("#t", "/dev", sys->MAFTER);	# serial line
#	sys->bind("#v","/dev",sys->MAFTER);     # VGA
	sys->bind("#I", "/net", sys->MAFTER);	# IP
	sys->bind("#P","/dev",sys->MAFTER);		# arch
#	sys->bind("#P/realmode","/dev",sys->MAFTER); # not in the arch(3). What is this for?
#	sys->bind("#P/realmodemem","/dev",sys->MAFTER);# not in the arch(3). What is this for?
#	sys->bind("#O", "/dev", sys->MAFTER);	# Modem
	sys->bind("#S", "/dev", sys->MAFTER);	# Disks
#	sys->bind("#T","/dev",sys->MAFTER);		# Touchscreen
#	sys->bind("#W","/dev",sys->MAFTER);		# Flash

	# TODO '#c/sysenv' seems obsolete
	#sys->print("srv()\n");
	#srv();

	sys->print("loading /dis/sh.dis\n");
	sh := load Sh "/dis/sh.dis";
	(s, nil) := sys->stat("/dis/init");
	if(s == 0){
		sys->print("spawn sh -n /dis/init\n");
		spawn sh->init(nil, "sh" :: "-x" :: "-n" :: "/dis/init" :: nil);
	} else {
		sys->fprint(stderr, "init: cannot find /dis/init: %r\n");
		spawn sh->init(nil, "-n" :: nil);
	}
}

srv()
{
	remotedebug := sysenv("remotedebug");
	if(remotedebug != "1")
		return;

	sys->print("srv...");
	if(echoto("#t/eia0ctl", "b38400") < 0)
		return;

	fd := sys->open("/dev/eia0", Sys->ORDWR);
	if (fd == nil) {
		sys->print("eia data open: %r\n");
		return;
	}
	if (sys->export(fd, "/", Sys->EXPASYNC) < 0) {
		sys->print("export: %r\n");
		return;
	}
	sys->print("ok\n");
}

sysenv(param: string): string
{
	fd := sys->open("#c/sysenv", sys->OREAD);
	if (fd == nil)
		return(nil);
	buf := array[4096] of byte;
	nb := sys->read(fd, buf, len buf);
	(nfl,fl) := sys->tokenize(string buf, "\n");
	while (fl != nil) {
		pair := hd fl;
		(npl, pl) := sys->tokenize(pair, "=");
		if (npl > 1) {
			if ((hd pl) == param)
				return hd tl pl;
		}
		fl = tl fl;
	}
	return nil ;
}

echoto(fname, str: string): int
{
	fd := sys->open(fname, Sys->OWRITE);
	if(fd == nil) {
		sys->print("%s: %r\n", fname);
		return -1;
	}
	x := array of byte str;
	if(sys->write(fd, x, len x) == -1) {
		sys->print("write: %r\n");
		return -1;
	}
	return 0;
}
