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
	0 => sys->print("begins with a vowel\n");
	1 => sys->print("begins with a consonant\n");
	2 => sys->print("begins with a consonant\n");
	3 => sys->print("begins with a consonant\n");
	4 => sys->print("begins with a consonant\n");
	* => sys->print("sorry don't understand\n");
	}
}
