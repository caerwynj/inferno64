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
	a := 1;
	b := 3;
	c : int;

	case a {
	0 => sys->print("is zero\n");
	1 => sys->print("is 1\n");
	2 => sys->print("is 2\n");
	* => sys->print("is default\n");
	}
}
