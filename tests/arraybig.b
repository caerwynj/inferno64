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
	a : array of int;
	b := array[64] of int;
	c := array [] of {"jimbox", "pip", "squek"};
	e := array [4] of {* => 3};
	d := array [4] of {* => 3.14};
	w := array [] of {0 or 2 or 4 or 6 or 8 => 1,
			1 or 3 or 5 or 7 or 9 => 0};
	z := array[20] of {0 or 2 or 4 or 6 or 8 => 1,
			1 or 3 or 5 or 7 or 9 => 0,
			* => -1
			};
	y : array of array of big;
	story := array [] of {"I", "should", "get", "a", "life"};
	task := story[2:];
	dream := task[0][:1] + "0" + task[0][2:] + " " +task[1] + " " + task[2];

	sys->print("should print jimbox result %s\n", c[0]);
	sys->print("should print 3 result %d\n", e[0]);
	sys->print("should print 3.14 result %g %f\n", d[0], d[0]);
	sys->print("should print 1 result %d\n", w[0]);
	sys->print("should print -1 result %-d\n", z[11]);
	sys->print("should print gOt a life result %s\n", dream);
}
