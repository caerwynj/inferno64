# Interpreter for the canonical esoteric language.
# Compiles to bytecode, minimal optimizations, done for fun.
# Pete Elmore (pete at debu dot gs), New Year's Day 2014
# Released into the public domain.

implement Bf;

include "sys.m"; sys: Sys;
include "draw.m";
include "arg.m";

Bf: module {
	init: fn(nil: ref Draw->Context, args: list of string);
	ARENASZ: con 1024 * 1024;
	EXIT, ADD, JZ, JNZ, ADDP, READ, WRITE: con iota;
};

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	arg := load Arg Arg->PATH;

	arg->init(args);
	arg->setusage("games/bf [-d|-c] [program.bf|-e inline-program]");

	eflag := 0;
	outputmode := 0;
	source := "";
	while ((opt := arg->opt()) != 0) {
		case opt {
		'e' =>
			eflag = 1;
			source = arg->arg();
		'd' =>
			outputmode = 1;
		'c' =>
			outputmode = 2;
		* =>
			arg->usage();
		}
	}
	args = arg->argv();
	if(!eflag) {
		if(len args != 1)
			arg->usage();
		else
			source = readfile(hd args);
	}

	code := compile(source);
	case outputmode {
	0 => execute(code, array[ARENASZ] of { * => byte 0 });
	1 => sys->print("%s", disassemble(code));
	2 => sys->print("%s", bf2limbo(code));
	}
}

compile(p: string): array of int
{
	marks: list of int = nil;
	code := array[len p * 2 + 1] of { * => EXIT };
	pc := 0;
	n: int;
	for(i := 0; i < len p; i++) {
		case p[i] {
		'-' or '+' =>
			n = 0;
			while(i < len p) {
				if(p[i] == '-')
					n--;
				else if(p[i] == '+')
					n++;
				else {
					i--;
					break;
				}
				i++;
			}
			if(n) {
				code[pc++] = ADD;
				code[pc++] = n;
			}
		'<' or '>' =>
			n = 0;
			while(i < len p) {
				if(p[i] == '<')
					n--;
				else if(p[i] == '>')
					n++;
				else {
					i--;
					break;
				}
				i++;
			}
			if(n) {
				code[pc++] = ADDP;
				code[pc++] = n;
			}
		',' => code[pc++] = READ;
		'.' => code[pc++] = WRITE;
		'[' =>
			code[pc++] = JZ;
			marks = pc++ :: marks;
		']' =>
			if(marks == nil) {
				sys->fprint(sys->fildes(2), "bf: unmatched ']' at character %d.", pc);
				raise "fail:errors";
			}
			c := hd marks;
			marks = tl marks;
			code[pc++] = JNZ;
			code[c] = pc;
			code[pc++] = c;
		}
	}
	if(marks != nil) {
		sys->fprint(sys->fildes(2), "bf: unmatched '['.");
		raise "fail:errors";
	}
	return code[:pc + 1];
}

execute(code: array of int, arena: array of byte)
{
	pc := 0;
	p := 0;
	buf := array[1] of byte;
	stopreading := 0;
	for(;;) {
		case code[pc] {
		ADD =>
			arena[p] += byte code[++pc];
		ADDP =>
			p += code[++pc];
			while(p < 0)
				p += len arena;
			p = p % len arena;
		READ =>
			arena[p] = byte -1;
			if(!stopreading) {
				n := sys->read(sys->fildes(0), buf, 1);
				if(n < 1)
					stopreading = 1;
				else
					arena[p] = buf[0];
			}
		WRITE =>
			buf[0] = arena[p];
			sys->write(sys->fildes(1), buf, 1);
		JNZ =>
			if(arena[p] != byte 0)
				pc = code[pc + 1];
			else
				pc++;
		JZ =>
			if(arena[p] == byte 0)
				pc = code[pc + 1];
			else
				pc++;
		EXIT => return;
		}
		pc++;
	}
}

disassemble(code: array of int): string
{
	s := "";
	for(i := 0; i < len code && code[i] != EXIT; i++) {
		s += sys->sprint("[0x%08x]  0x%02x  ", i, code[i]);
		case code[i] {
		ADD => s += sys->sprint("add   %d", code[++i]);
		ADDP => s += sys->sprint("addp  %d", code[++i]);
		READ => s += "read ";
		WRITE => s += "write";
		JNZ => s += sys->sprint("jnz   0x%08x", code[++i]);
		JZ => s += sys->sprint("jz    0x%08x", code[++i]);
		* => s += sys->sprint(">>>>>>BUG %d / 0x%08x", code[i], code[i]);
		}
		s += "\n";
	}
	return s;
}

bf2limbo(code: array of int): string
{
	indent := 1;
	s := "implement BfProg;\n" +
		"include \"sys.m\"; sys: Sys;\n" +
		"include \"draw.m\";\n" +
		"BfProg: module {\n" +
		"\tinit: fn(nil: ref Draw->Context, nil: list of string);\n" +
		"};\n" +
		"init(nil: ref Draw->Context, nil: list of string)\n{\n" +
		"\tsys = load Sys Sys->PATH;\n" +
		"\tp := 0;\n" +
		"\tstopreading := 0;\n" +
		"\tn := 0;\n" +
		"\tbuf := array[1] of byte;\n" +
		"\tarena := array[" + string ARENASZ + "] of { * => byte 0 };\n" +
		"\n";
	for(i := 0; i < len code && code[i] != EXIT; i++) {
		case code[i] {
		ADD => s += indents(indent) + "arena[p] += byte " + string code[++i] + ";\n";
		ADDP =>
			s += indents(indent) + "p += " + string code[++i] + ";\n" +
				indents(indent) + "while(p < 0)\n" +
				indents(indent + 1) + "p += len arena;\n" +
				indents(indent) + "p = p % len arena;\n";
		READ =>
			s += indents(indent) + "arena[p] = byte -1;\n" +
				indents(indent) + "if(!stopreading) {\n" +
				indents(indent + 1) + "n = sys->read(sys->fildes(0), buf, 1);\n" +
				indents(indent + 1) + "if(n < 1)\n" +
				indents(indent + 2) + "stopreading = 1;\n" +
				indents(indent + 1) + "else\n" +
				indents(indent + 2) + "arena[p] = buf[0];\n" +
				indents(indent) + "}\n";
		WRITE =>
			s += indents(indent) + "buf[0] = arena[p];\n" +
				indents(indent) + "sys->write(sys->fildes(1), buf, 1);\n";
		JNZ =>
			indent--;
			s += indents(indent) + "}\n";
			i++;
		JZ =>
			s += indents(indent) + "while(arena[p] != byte 0) {\n";
			indent++;
			i++;
		}
		
	}
	return s + "}\n";
}

indents(i: int): string
{
	r := "";
	while(i > 0) {
		r += "\t";
		i--;
	}
	return r;
}

readfile(fname: string): string
{
	fd := sys->open(fname, Sys->OREAD);
	if(fd == nil)
		die(fname);

	src := "";
	buf := array[Sys->ATOMICIO] of byte;
	while((n := sys->read(fd, buf, len buf)) > 0) {
		src += string buf[:n];
	}
	return src;
}

die(s: string)
{
	sys->fprint(sys->fildes(2), "bf: %s: %r\n", s);
	raise "fail:errors";
}