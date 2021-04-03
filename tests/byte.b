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
	a := byte 1;
	b := byte 255;

	a = a + (byte 10);
	b = b + (byte 10);
	sys->print("a expected 11 calculated %d, b expected 9 calculated %d\n", (int a), (int b));
}
