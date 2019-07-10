implement Seq;

include "sys.m";
	sys: Sys;

include "draw.m";

include "arg.m";

include "bufio.m";
	bio: Bufio;
	Iobuf: import bio;

Seq: module {
	init: fn(nil: ref Draw->Context, args: list of string);
};

out: ref Iobuf;

# Print a sequence of numbers in steps of a given increment
init(nil: ref Draw->Context, args: list of string) {
	sys = load Sys Sys->PATH;
	arg := load Arg Arg->PATH;
	if(arg == nil)
		raise "Arg is nil";
	bio = load Bufio Bufio->PATH;
	if(bio == nil)
		raise "Bio is nil";

	arg->init(args);
	out = bio->open("/fd/1", bio->OWRITE);

	# TODO: [-w] [-f format]
	# Note: Limbo doesn't seem to like non-constant format specifiers
	arg->setusage("seq [first [increment]] last");
	args = arg->argv();
	argc := len(args);

	step := 1.0;
	first := 1.0;
	last: real;
	printer: ref fn(i: real) = iprint;

	case argc {
	1 => 
		# Seq [1,last]
		last = real hd args;
	2 =>
		# Seq [first,last]
		first = real hd args;
		last = real hd tl args;
	3 =>
		# Seq [first,last] by step increment
		first = real hd args;
		step = real hd tl args;
		last = real hd tl tl args;
	* => arg->usage();
	}

	if(isfloat(first) || isfloat(step) || isfloat(last))
		printer = rprint;

	# Iterate
	for(i := first; i <= last; i += step)
		printer(i);

	out.flush();
	out.close();
	exit;
}

# Print int
iprint(i: real) {
	out.puts(sys->sprint("%d\n", int i));
}

# Print real
rprint(i: real) {
	out.puts(sys->sprint("%g\n", i));
}

# Determine if functionally float by truncating and comparing the difference
# 2.5 - 2.0 = 0.5 != 0.0 ;; 3.0 - 3.0 = 0.0 == 0.0
isfloat(r: real): int {
	i := int r;
	ir := real i;

	if(r - ir == 0.0)
		return 0;

	return 1;
}
