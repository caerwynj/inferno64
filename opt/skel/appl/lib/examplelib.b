implement ExampleLib;

include "sys.m";
	sys: Sys;
include "../../module/examplelib.m";


init()
{
	sys = load Sys Sys->PATH;
	sys->print("Hello from ExampleLib->init()\n");
}
