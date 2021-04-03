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
	a : string;
	b := "yes";

	b[1] = 'E';
	sys->print("should print yEs result %s\n", b);
	a[0] = 112;
	sys->print("should print p result %s\n", a);
	a[0] = 'h';
	a[len a] = 'e';
	a[len a] = 'l';
	a[len a] = 'l';
	a[len a] = 'o';
	sys->print("should print hello result %s\n", a);
	c := int "65";
	sys->print("should print 65 result %d\n", c);
	h := "Hello";
	w := "World";
	g := h + " " + w + " " + "!";
	sys->print("should print Hello World ! result %s\n", g);
}
