implement NewNamespace;

# This is a programized version of newns(2) in the style of 9front's newns(8)
# You may need to call this doing something like
#	; newns -d -n ./namespace `{whatis pwd}

include "sys.m";
	sys: Sys;
	FD: import sys;
include "draw.m";
include "arg.m";
include "newns.m";
include "sh.m";
include "string.m";

NewNamespace: module {
	init: fn(ctx: ref Draw->Context, argv: list of string);
};

debug: int;

init(ctx: ref Draw->Context, argv: list of string) {
	sys = load Sys Sys->PATH;
	fprint, fildes: import sys;
	arg := load Arg Arg->PATH;
	if(arg == nil)
		raise "Could not load " + Arg->PATH;
	ns := load Newns Newns->PATH;
	if(ns == nil)
		raise "Could not load " + Newns->PATH;

	forkns := 1;
	debug = 0;
	nsf := "";
	user := readfile("/dev/user");

	arg->init(argv);
	arg->setusage("newns [-ad] [-n namespace] [-u user] command arg⋯");

	while((o := arg->opt()) != 0)
		case o {
		'a' =>	forkns = 0;	# Affect the current process namespace
		'd' =>	debug = 1;
		'n' =>	nsf = arg->earg();
		'u' =>	user = arg->earg();
		* =>		arg->usage();
		}

	argv = arg->argv();
	argc := len argv;

	if(argc <= 0)
		arg->usage();

	cmd := hd argv;

	if(debug) {
		fprint(fildes(2), "Argc = %d\nCmd = %s\n", argc, cmd);
		fprint(fildes(2), "Args:\n");
		for(a := argv; a != nil; a = tl a)
			fprint(fildes(2), "\t%s\n", hd a);
	}

	if(forkns)
		sys->pctl(sys->FORKNS, nil);

	if(nsf != nil) {
		err := ns->newns(user, nsf);
		if(err != nil)
			raise "err: newns(2) failed ­ " + err;
	}

	cmd = lookup(cmd);

	c := load Command cmd;
	if(c == nil)
		raise sys->sprint("err: could not load program %s ­ %r", cmd);

	spawn c->init(ctx, argv);
}

# Try to do a $path-style lookup for a shorthand command
# You're supposed to use sh.m, but that's a lot of infra
# $path = (/dis .)
lookup(cmd: string): string {
	# We can probably trust paths already possessing a leading /
	if(cmd[0] == '/')
		return cmd;

	# Trust a ./
	if(len cmd > 1) {
		pref := cmd[:2];
		if(pref == "./")
			return cmd;
	}

	sprint, OREAD: import sys;

	c := sprint("/dis/%s", cmd);
	if(tryopen(c))
		return c;

	c = sprint("./%s", cmd);
	if(tryopen(c))
		return c;

	# Try the same logic, but after appending .dis in case it was forgotten
	if(! contains(cmd, ".dis"))
		cmd = sprint("%s.dis", cmd);
	else
		return cmd;	# Give up

	c = sprint("/dis/%s", cmd);
	if(tryopen(c))
		return c;

	c = sprint("./%s", cmd);
	if(tryopen(c))
		return c;

	return cmd;
}

# Try to open helper for lookup()
tryopen(c: string): int {
	if(debug)
		sys->fprint(sys->fildes(2), "Trying: %s\n", c);

	fd := sys->open(c, sys->OREAD);
	if(fd != nil) {
		# Make sure it's not a directory - can't exec those ☺
		(err, dir) := sys->fstat(fd);
		if(err >= 0)
			if(! (dir.mode & Sys->DMDIR))
				return 1;
		# Maybe handle error?
	}

	return 0;
}

# Reads a (small) file into a string
readfile(f: string): string {
	fd := sys->open(f, sys->OREAD);
	if(fd == nil)
		return nil;

	buf := array[8192] of byte;
	n := sys->read(fd, buf, len buf);
	if(n < 0)
		return nil;

	return string buf[0:n];	
}

# Check whether a string s₀ contains another string s₁
contains(s₀, s₁: string ): int {
	s₀len := len s₀;
	s₁len := len s₁;

	if(s₁ == s₀)
		return 1;

	if(s₁len - s₀len < 0)
		return 0;

	# fooduckbar contains duck
	# dlen = 4
	# flen = 10
	# x₀ = 0
	# x₁ = 4
	# f[x₀:x₁]
	x₀ := 0;
	x₁ := s₁len;

	while(x₁ <= s₀len) {
		s := s₀[x₀:x₁];
		if(s == s₁)
			return 1;

		x₀++;
		x₁++;
	}

	return 0;
}

