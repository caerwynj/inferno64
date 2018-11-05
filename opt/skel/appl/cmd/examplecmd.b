implement ExampleCmd;

include "sys.m";
	sys: Sys;
	sprint: import sys;
include "draw.m";
include "opt/powerman/logger/module/logger.m";
	logger: Logger;
	log, ERR, WARN, NOTICE, INFO, DEBUG: import logger;
include "arg.m";
include "opt/skel/module/examplelib.m";


ExampleCmd: module
{
	init: fn(nil: ref Draw->Context, argv: list of string);
};

init(nil: ref Draw->Context, argv: list of string)
{
	sys		=  load Sys Sys->PATH;
	logger		=  checkload(load Logger Logger->PATH, "Logger");
	logger->init();
	arg		:= checkload(load Arg Arg->PATH, "Arg");
	arg->init(argv);
	logger->progname(arg->progname());
	examplelib	:= checkload(load ExampleLib ExampleLib->PATH, "ExampleLib");
	examplelib->init();

	arg->setusage(sprint("%s [-v]", arg->progname()));
	while((p := arg->opt()) != 0)
		case p {
		'v' =>	logger->verbose++;
		* =>	arg->usage();
		}
	argv = arg->argv();
	if(len argv != 0)
		arg->usage();

	log(DEBUG,  "Hello from ExampleCmd->init()");
	log(INFO,   "Hello from ExampleCmd->init()");
	log(NOTICE, "Hello from ExampleCmd->init()");
	log(WARN,   "Hello from ExampleCmd->init()");
	log(ERR,    "Hello from ExampleCmd->init()");
}


###

fail(s: string)
{
	if(logger != nil)
		log(ERR, s);
	else
		sys->fprint(sys->fildes(2), "%s\n", s);
	raise "fail:"+s;
}

checkload[T](x: T, s: string): T
{
	if(x == nil)
		fail(sprint("load: %s: %r", s));
	return x;
}

