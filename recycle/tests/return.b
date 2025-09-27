implement Emuinit;
include "sys.m";
	sys: Sys;

Emuinit: module
{
	init: fn();
};

init()
{
	sys = load Sys Sys->PATH;
	a : int;

	a = calc(100);
	sys->print("returned %d\n", a);
}

calc(n: int): int
{
	a : int;

	a = n * n + 100;
	return a;
}
