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
	c := array [] of {"jimbox", "pip", "squek"};

	sys->print("should print jimbox result %s\n", c[0]);
	sys->print("should print squek result %s\n", c[2]);
}
