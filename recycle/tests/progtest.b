implement Progtest;
include "sys.m";
	sys: Sys;
include "daytime.m";
include "draw.m";

#18:19 < qrstuv> even if running only one program, it will be slow
#18:22 < qrstuv> write yourself a limbo test program that does an i++ ten million times
#18:22 < joe7> I do not understand why it should be slow when running one program. ok, will do the test program to understand it better.
#18:22 < qrstuv> run it with the jitters off and go boil a cup of coffee
#18:22 < qrstuv> then turn the jitters on and run it again
#18:23 < qrstuv> it'll take maybe 66% as long as the first run
#18:23 < joe7> no jitters on amd64. As of now, it will probably crash with an arena error.
#18:23 < qrstuv> then turn off libinterp/comp-386.c:/RESCHED, recompile, and run your test program again with jitters
#18:23 < joe7> about memory.
#18:23 < qrstuv> and you will notice the difference
#18:23 < joe7> ok, thanks. will do.

Progtest: module
{
	init: fn(nil: ref Draw->Context, args: list of string);
};

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	daytime := load Daytime Daytime->PATH;
#	i := 0;
	j := 0;

	sys->print("Testing the prog scheduler\n");
	sys->print("	start %s\n", daytime->time());
	for(i := 0; i<1000*1000*1000; i++){
		;
	}
	sys->print("j %d i %d\n", j, i);
	sys->print("	  end %s\n", daytime->time());
}
