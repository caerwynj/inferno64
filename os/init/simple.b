#
#	simple Init that calls /dis/init, a shell script to continue initialization
#
implement Init;

include "sys.m";
include "draw.m";

sys: Sys;
FD, Connection, sprint, Dir: import sys;
print, fprint, open, bind, mount, dial, sleep, read: import sys;

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
	sys->bind("#d", "/fd", Sys->MREPL);
	sys->bind("#S", "/dev", sys->MAFTER);	# Disks
#	sys->bind("#l", "/net", sys->MAFTER);	# Network interfaces
#	sys->bind("#I", "/net", sys->MAFTER);	# IP
	sys->bind("#p", "/prog", sys->MREPL);	# prog device
	sys->bind("#t", "/dev", sys->MAFTER);	# serial line
	sys->bind("#c", "/dev", sys->MAFTER);	# console device
#	sys->bind("#P","/dev",sys->MAFTER);
#	sys->bind("#P/realmode","/dev",sys->MAFTER);	# arch
#	sys->bind("#P/realmodemem","/dev",sys->MAFTER);
	sys->bind("#i", "/dev", sys->MREPL);	# draw device
#	sys->bind("#v","/dev",sys->MAFTER);     # VGA
#	sys->bind("#m","/dev",sys->MAFTER);     # pointer/mouse
#	sys->bind("#W","/dev",sys->MAFTER);	# Flash
#	sys->bind("#O", "/dev", sys->MAFTER);	# Modem
#	sys->bind("#T","/dev",sys->MAFTER);	# Touchscreen

	sys->print("after the binds\n");
	sh := load Sh "/dis/sh.dis";
	(s, nil) := sys->stat("/dis/init");
	if(s == 0){
	sys->print("spawn sh -n /dis/init\n");
		spawn sh->init(nil, "sh" :: "-n" :: "/dis/init" :: nil);
	} else {
		sys->fprint(stderr, "init: cannot find /dis/init: %r\n");
		spawn sh->init(nil, nil);
	} 
}
