implement Sample;
include "sys.m";
	sys: Sys;

Sample: module
{
	init: fn();
};

init()
{
	sys = load Sys Sys->PATH;
	d := array [4] of {* => 3.14};
	z := array[20] of {0 or 2 or 4 or 6 or 8 => 1,
			1 or 3 or 5 or 7 or 9 => 0,
			* => -1
			};

	sys->print("should print 3.14 result %g %f\n", d[0], d[0]);
	sys->print("should print -1 result %d\n", z[11]);
}
