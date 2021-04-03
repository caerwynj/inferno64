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
	a := 15;
	b := 3;
	c : int;

	case a {
	0 => sys->print("is zero\n");
	1 to 10 => sys->print("is between 1 and 10\n");
	11 to 20 => sys->print("is between 11 and 20\n");
	* => sys->print("is default\n");
	}
}
