implement Fibonacci;

include "sys.m";

sys : Sys;
MAX : con 50;
chan1, chan2, chan4 : chan of int;
chan3 : chan of string;

Fibonacci : module
{
	init : fn();
};

init()
{
	sys = load Sys Sys->PATH;

	chan1 = chan of int;
	chan2 = chan of int;
	chan4 = chan of int;
	chan3 = chan of string;

	str := "string test";
	sys->print("string test: %s %d\n", str, len str);
	sys->print("0	.\n	..\n");
	spawn f(0,1);
	spawn f1(0,1);
	spawn f3(0,1);
	spawn f2();
	for (i := 0; i<10; i++){
		sys->print("loop counter %d\n", i);
		alt
		{
			a := <- chan1 =>
			{
				sys->print("%d: Read from chan1 %d\n", i, a);
			}
	
			b := <- chan2 =>
			{
				sys->print("%d: Read from chan2 %d\n", i, b);
			}
			c := <- chan4 =>
			{
				sys->print("%d: Read from chan4 %d\n", i, c);
			}
	
			chan3 <- = "Orange" =>
			{
				sys->print("Send on chan3\n");
			}
	
			* =>
			{
				sys->print("Default action\n");
			}
		}
	}
	sys->print("Spawned threads completed.\n");
}

f(a, b : int)
{
	sys->print("%-3d", a + b);
	chan1 <-= a+b;
	for (i := 0; i <= a+b; i++)
	{
		sys->print(".");
	}
	sys->print("\n");

	if (a+b < MAX)
	{
		f(b, a+b);
	}

	chan1 <-= 0;
	sys->print("exiting f\n"); 
}

f1(a, b : int)
{
	sys->print("%-3d", a + b);
	chan2 <-= a+b;
	for (i := 0; i <= a+b; i++)
	{
		sys->print(".");
	}
	sys->print("\n");

	if (a+b < MAX)
	{
		f(b, a+b);
	}

	chan2 <-= 1;
	sys->print("exiting f1\n"); 
}

f3(a, b : int)
{
	sys->print("%-3d", a + b);
	chan4 <-= a+b;
	for (i := 0; i <= a+b; i++)
	{
		sys->print(".");
	}
	sys->print("\n");

	if (a+b < MAX)
	{
		f(b, a+b);
	}

	chan4 <-= 1;
	sys->print("exiting f3\n"); 
}

f2()
{
	x : string;
	x = <- chan3;
	sys->print("exiting f2, received\n"); 
}
