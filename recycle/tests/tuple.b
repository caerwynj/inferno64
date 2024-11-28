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
	d := ("Jane", "Doe", 22, 3.8, -10);
	major : string;
	gpa : real;
	a : int;

	(major, nil, nil, gpa, a) = d;
	sys->print("should print Jane result %s\n", major);
	sys->print("should print 3.8 result %g\n", gpa);
	sys->print("should print -10 result %d\n", a);
}
