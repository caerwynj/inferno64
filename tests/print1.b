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
	sys->print("init %g %f\n", 3.14, 1.48);
	sys->print("init %d\n", -1);
}
