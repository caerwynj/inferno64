implement Trampoline;

include "sys.m";
	sys: Sys;
	read, write: import sys;

include "draw.m";

include "dial.m";
	dial: Dial;
	Connection: import dial;

# dial'ing an address returns an fd
#	write everything from our stdin to that fd
#	write everything from that fd to our stdout
Trampoline: module
{
	init:	fn(nil: ref Draw->Context, nil: list of string);
};

File: adt
{
	fd:	ref Sys->FD;
	name:	string;
};

usage()
{
	sys->fprint(sys->fildes(2), "Usage: trampoline addr\n");
	raise "fail:usage";
}

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	dial = load Dial Dial->PATH;
	if(dial == nil)
		error(sys->sprint("can't load %s: %r", Dial->PATH));

	for(as:=args; as != nil; as = tl as){
		sys->print("arg %s\n", hd as);
	}
	if(len args != 2)
		usage();
	args = tl args;
	addr := hd args;

	sys->pctl(sys->NEWPGRP, nil);
	connection := dial->dial(addr, nil);

	chan1 := chan of int;
	chan2 := chan of int;
	spawn xfer(sys->fildes(0), connection.dfd, chan1);
	pids : list of int;
	pid := <-chan1;
	if(pid)
		pids = pid :: nil;
	spawn xfer(connection.dfd, sys->fildes(1), chan2);
	pid = <-chan2;
	if(pid)
		pids = pid :: pids;

	alt
	{
		<- chan1 => ;
		<- chan2 => ;
	}
	for(; pids != nil; pids = tl pids)
		kill(hd pids);
}

xfer(rfd, wfd: ref Sys->FD, c: chan of int)
{
	c <-= sys->pctl(0, nil);
	buf := array[2048] of {* => byte 0};
	while((r := read(rfd, buf, len buf)) > 0){
		w := write(wfd, buf, r);
		if(w != r)
			error(sys->sprint("xfer r %d w %d\n", r, w));
	}
}

error(s: string)
{
	sys->fprint(sys->fildes(2), "tee: %s\n", s);
	raise "fail:error";
}

kill(pid: int)
{
	fd := sys->open("#p/"+string pid+"/ctl", Sys->OWRITE);
	if(fd != nil)
		sys->fprint(fd, "kill");
}
