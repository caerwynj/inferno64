implement T;

include "opt/powerman/tap/module/t.m";
include "../../../module/examplelib.m";
	examplelib: ExampleLib;


test()
{
	plan(1);

	examplelib = load ExampleLib ExampleLib->PATH;
	if(examplelib == nil)
		bail_out(sprint("load %s: %r",ExampleLib->PATH));

	{ examplelib->init(); } exception e { "*"=>catched(e); }
	raised(nil, "init() doesn't raise");
}
