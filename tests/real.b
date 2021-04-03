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
	r : real;

	r = 3.14;
	sys->print("should print 3.14 result %g\n", r);
	sys->print("should print 3.14 result %f\n", r);
}
