implement Fibonacci;

include "sys.m";

sys : Sys;
MAX : con 50;
x : chan of int;

Fibonacci : module
{
	init : fn();
};

init()
{
	sys = load Sys Sys->PATH;

	x = chan of int;
	sys->print("0	.\n	..\n");
	spawn f(0,1);

	<-x;
	sys->print("main thread completed.\n");
}

f(a, b : int)
{
	sys->print("%-3d", a + b);
	for (i := 0; i <= a+b; i++)
	{
		sys->print(".");
	}
	sys->print("\n");

	if (a+b < MAX)
	{
		f(b, a+b);
	}

	x <-= 0;
	sys->print("Spawned thread completed.\n");
}
