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
	c := array [1] of {1};
	sys->print("print the 1st element %d\n", c[0]);
}
