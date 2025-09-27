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
	a: int;

	a = sys->print("testinng the return value\n");
	sys->print("print returned %d\n", a);
	a = sys->print("\n");
	sys->print("print returned %d, should have been 1\n", a);
}
