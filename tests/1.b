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
	sys->print("init 1\n");
	a := 1;
	b := 3;
	c : int;
	d : string;

	d = "string init";
	c = a*b + b*b*b*b + a;
	sys->print("Completed running 1.b: c=%d\n", c);
}
