implement T;

include "opt/powerman/tap/module/t.m";
include "sh.m";


test()
{
	plan(1);

	examplecmd := load Command "/opt/skel/dis/cmd/examplecmd.dis";
	ok(examplecmd != nil, "examplecmd loaded as Command");
}
