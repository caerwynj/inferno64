# File: draw-example(2)

implement Test;

include "sys.m";
include "draw.m";

Test: module
{
	init:	fn(ctxt: ref Draw->Context, argv: list of string);
};

init(nil: ref Draw->Context, nil: list of string)
{
	sys := load Sys Sys->PATH;
	draw := load Draw Draw->PATH;
	Display, Font, Rect, Point, Image, Screen: import draw;

	display := draw->Display.allocate(nil);
	disp := display.image;
	red := display.color(Draw->Red);
	blue := display.color(Draw->Blue);
	white := display.color(Draw->White);
	yellow := display.color(Draw->Yellow);

	red.r.max.x = 640;
	red.r.max.y = 480;
	red.clipr.min.x = 0;
	red.clipr.min.y = 0;
	red.clipr.max.x = 600;
	red.clipr.max.y = 400;
	white.r.max.x = 640;
	white.r.max.y = 480;
	white.clipr.min.x = 200;
	white.clipr.min.y = 400;
	white.clipr.max.x = 640;
	white.clipr.max.y = 480;
	sys->print("red r .min.x %d .min.y %d .max.x %d .max.y %d\n",
		red.r.min.x, red.r.min.y, red.r.max.x, red.r.max.y);
	#sys->print("red clipr .min.x %d .min.y %d .max.x %d .max.y %d\n",
	#	red.clipr.min.x, red.clipr.min.y,
	#	red.clipr.max.x, red.clipr.max.y);
	sys->print("disp r .min.x %d .min.y %d .max.x %d .max.y %d\n",
		disp.r.min.x, disp.r.min.y, disp.r.max.x, disp.r.max.y);
	sys->sleep(5000);
	disp.draw(disp.r, red, red, disp.r.min);
	sys->sleep(5000);
	disp.draw(disp.r, white, white, disp.r.min);
	sys->sleep(50000);
}
