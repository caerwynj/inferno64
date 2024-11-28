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
	a : list of string;
	b := list of {"yes", "no"};

	a = "soy" :: a;
	a = "test" :: a;
	sys->print("should print yes result %s\n", hd b);
	c := tl a;
	sys->print("should print 2 no result %d\n", len a);
}
