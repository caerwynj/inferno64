# File: drawcontext.b

implement DrawContext;

include "sys.m";
include "draw.m";

sys : Sys;
draw : Draw;
Screen, Display : import draw;

DrawContext : module
{
	init : fn(ctxt : ref Draw->Context, args : list of string);
};

init (ctxt : ref Draw->Context, nil : list of string)
{
	sys = load Sys Sys->PATH;
	draw = load Draw Draw->PATH;
	if(draw == nil){
		sys->fprint(sys->filedes(2), "cannot load Draw module\n");
		raise "fail: bad module";
	}

	if (ctxt == nil)
	{
		sys->print("No valid graphics contetx, allocating a new one...\n");
		display := Display.allocate(nil);
		screen := Screen.allocate(display.image, display.rgb(99,99,99), 1);
		ctxt = ref (screen, display, nil, nil, nil, nil, nil);
	}
}
