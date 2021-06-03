implement Engridden;

include "sys.m";
	sys: Sys;
include "draw.m";
include "string.m";
include "env.m";
include "arg.m";
include "bufio.m";

stderr: ref Sys->FD;

Engridden: module {
	init:	fn(nil: ref Draw->Context, argv: list of string);
};


# Mount ourselves into the public grid
# $pubgridreg sets the public grid registry dialstr
init(nil: ref Draw->Context, argv: list of string)
{
	sys = load Sys Sys->PATH;
	str := load String String->PATH;
	env := load Env Env->PATH;
	arg := load Arg Arg->PATH;
	bio := load Bufio Bufio->PATH;
	Iobuf: import bio;

	reg := env->getenv("pubgridreg");
	mtpt := "/mnt/registry";
	ndir := "/n";

	arg->init(argv);
	arg->setusage("engridden [-r tcp!registry] [-m /mnt/registry] [-n /n]");
	while((c := arg->opt()) != 0)
	case c {
		'm' => mtpt = arg->earg();
		'r' => reg = arg->earg();
		'n' => ndir = arg->earg();
		* => arg->usage();
	}
	argv = arg->argv();

	if(reg == ""){
		sys->print("err: $pubgridreg or '-r' must be provided to mount a registry\n");
		exit;
	}
	
	sys->print("Mounting public grid registry %s…\n", reg);

	if(dialmount(reg, mtpt) < 0)
		exit;

	buf := bio->open(mtpt + "/index", Bufio->OREAD);
	if(buf == nil){
		sys->print("err: open failed → %r\n");
		exit;
	}

Read:
	for(;;){
		line := buf.gets('\n');
		if(line == "")
			break Read;

		(toks, err) := str->qtokenize(line);
		if(err != nil){
			sys->print("fail: can't parse line → %s\n", line);
			continue Read;
		}

		if(len toks < 2){
			sys->print("fail: not enough tokens in line → %s\n", line);
			continue Read;
		}

		dialstr := hd toks;
		name := "";
		toks = tl toks;

		# Modeled after 9p.zone's registry
		for(; toks != nil; toks = tl toks){
			case hd toks {
			"description" =>
				toks = tl toks;
				name = hd toks;

			* => 
				;
			}
		}

		if(dialstr == ""){
			sys->print("fail: no dialstring in line → %s\n", line);
			continue Read;
		}

		if(name == ""){
			sys->print("fail: could not find 'description' value in line → %s\n", line);
			continue Read;
		}
		at := ndir + "/" + name;

		sys->print("Mounting %s at %s…\n", dialstr, at);

		if(dialmount(dialstr, at) < 0)
			continue Read;
	}

	sys->print("Done.\n");

	exit;
}

dialmount(dialstr, mtpt: string): int {
	(ok, conn) := sys->dial(dialstr, nil);
	if(ok < 0){
		sys->print("err: dial failed for %s → %r\n", dialstr);
		return ok;
	}

	ok = sys->mount(conn.dfd, nil, mtpt, Sys->MREPL|Sys->MCREATE, nil);
	if(ok < 0){
		sys->print("err: mount failed for %s → %r\n", mtpt);
		return ok;
	}

	return 0;
}