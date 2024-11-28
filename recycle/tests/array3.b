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
	z := array[2] of {* => -1};
	d := array [3] of {* => 3.14};

	sys->print("should print -1 result %d\n", z[1]);
	sys->print("should print 3.14 result %g %f\n", d[0], d[0]);
}
