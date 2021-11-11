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
	sys->bind("#e", "/env", sys->MREPL|sys->MCREATE);	# environment
#	sys->bind("#i", "/dev", sys->MREPL);	# draw device
	sys->bind("#l0", "/net", sys->MAFTER);	# Ehernet device
	sys->bind("#m","/dev",sys->MAFTER);     # pointer/mouse
	sys->bind("#p", "/prog", sys->MREPL);	# prog device
	sys->bind("#r", "/dev", sys->MAFTER);	# rtc
	sys->bind("#t", "/dev", sys->MAFTER);	# serial line
#	sys->bind("#v","/dev",sys->MAFTER);     # VGA
	sys->bind("#I0", "/net", sys->MAFTER);	# IP
	sys->bind("#P","/dev",sys->MAFTER);		# arch
#	sys->bind("#P/realmode","/dev",sys->MAFTER); # not in the arch(3). What is this for?
#	sys->bind("#P/realmodemem","/dev",sys->MAFTER);# not in the arch(3). What is this for?
#	sys->bind("#O", "/dev", sys->MAFTER);	# Modem
	sys->bind("#S", "/dev", sys->MAFTER);	# Disks
#	sys->bind("#T","/dev",sys->MAFTER);		# Touchscreen
#	sys->bind("#W","/dev",sys->MAFTER);		# Flash
#	sys->bind("#o", "/proc", sys->MREPL);	# proc device

	# set clock
	#	does not handle bootp provided time source
	now := getclock("#r/rtc");
	now *= big 1000000;
	setclock("#c/time", now);

	# TODO '#c/sysenv' seems obsolete
	#sys->print("srv()\n");
	#srv();

	# using -n to use this namespace instead of re-creating the binds above
	sys->print("loading /dis/sh.dis\n");
	sh := load Sh "/dis/sh.dis";
	(s, nil) := sys->stat("/dis/init");
	if(s == 0){
		sys->print("spawn sh -n /dis/init\n");
		{
			sh->init(nil, "sh" :: "-n" :: "/dis/init" :: nil);
		} exception e {
			"*" =>
				sys->fprint(stderr, "dis/init status: %s\nStarting fallback shell\n", e);
				# fallback console
				sh1 := load Sh "/dis/sh.dis";
				sys->print("sh -n\n");
				sh1->init(nil, "sh" :: "-n" :: nil);
		}
	}{
		# fallback console
		sh1 := load Sh "/dis/sh.dis";
		sys->print("sh -n -x\n");
		sh1->init(nil, "sh" :: "-n" :: "-x" :: nil);
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

getclock(timefile: string): big
{
	now := big 0;
	if(timefile != nil){
		fd := sys->open(timefile, Sys->OREAD);
		if(fd != nil){
			b := array[64] of byte;
			n := sys->read(fd, b, len b-1);
			if(n > 0){
				now = big string b[0:n];
				if(now <= big 16r20000000)
					now = big 0;	# remote itself is not initialised
			}
		}
	}
	return now;
}

setclock(timefile: string, now: big)
{
	fd := sys->open(timefile, sys->OWRITE);
	if (fd == nil) {
		sys->print("init: can't open %s: %r", timefile);
		return;
	}

	b := sys->aprint("%ubd", now);
	if (sys->write(fd, b, len b) != len b)
		sys->print("init: can't write to %s: %r", timefile);
}
