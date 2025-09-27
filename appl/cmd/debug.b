implement Debugger;
include "sys.m";
sys: Sys;
print, sprint: import sys;
include "draw.m";
include "string.m";
str: String;
tobig, toint, toreal, tolower, toupper: import str;
include "bufio.m";
bufio: Bufio;
Iobuf: import bufio;
include "debug.m";
debug: Debug;
Prog, Exp, Module, Sym, Src, Pos: import debug;
include "sh.m";
sh: Sh;

srcfile: string;
disfile: string;
sblfile: string;
breakpoints: list of string;
tos : ref Exp;
localvars: ref Exp;
argvars: ref Exp;
modulevars: ref Exp;
currline: int;

Debugger:module
{ 
	init:fn(ctxt: ref Draw->Context, argv: list of string); 
};

init(nil: ref Draw->Context, argv: list of string)
{
	sys = load Sys Sys->PATH;
	str = load String String->PATH;
	bufio = load Bufio Bufio->PATH;
	debug = load Debug Debug->PATH;
	debug->init();
	sh = load Sh Sh->PATH;
	main(argv);
}

main(argv: list of string)
{
	line: string;
	prog: ref Prog;
	s: string;
	last: list of string;
	exp: array of ref Exp;
	sym: ref Sym;

	in := bufio->fopen(sys->fildes(0), Bufio->OREAD);
	print("> ");
	while ((line = in.gets('\n')) != nil) {
		(n, l) := sys->tokenize(line, " \n\r\t");
		if (len l == 0)
			l = last;
		case hd l {
		"quit" or "q" =>
			exit;
		"run" =>
			(prog, s) = debug->startprog(hd tl l, ".", nil, tl l);
			if(prog == nil)
				print("error %s\n", s);
		"cont" or "c" =>
			s = prog.cont();
			if(s != nil)
				print("%s\n", s);
		"step" or "s"  =>
			s = prog.step(Debug->StepStmt);
			if(s != nil)
				print("%s\n", s);
			stack(prog);
		"next" or "n" =>
			s = prog.step(Debug->StepOver);
			if(s != nil)
				print("%s\n", s);
			stack(prog);
		"ret" or "r" =>
			s = prog.step(Debug->StepOut);
			if(s != nil)
				print("%s\n", s);
		"start" =>
			s = prog.start();
			if(s != nil)
				print("%s\n", s);
		"stop" =>
			s = prog.stop();
			if(s != nil)
				print("%s\n", s);
		"unstop" =>
			s = prog.unstop();
			if(s != nil)
				print("%s\n", s);
		"kill" =>
			s = prog.kill();
			if(s != nil)
				print("%s\n", s);
		"status" or "ps" =>
               		(pgrp, user, state, mod) := prog.status();
			print("%d %s %s %s\n", pgrp, user, state, mod);
		"stack" or "bt" =>
			(exp, s) = prog.stack();
			if(s != nil) {
				print("%s\n", s);
				continue;
			}
			for(i:=0; i < len exp; i++) {
				exp[i].m.stdsym();
				exp[i].findsym();
				print("%s %s\n", exp[i].name, exp[i].srcstr());
			}
			disfile = exp[0].m.dis();
			sblfile = exp[0].m.sbl();
			if (sblfile != nil) {
				srcfile = str->replace(sblfile, ".sbl", ".b", -1);
				(sym, s) = debug->sym(sblfile);
				if(s != nil)
					print("err %s\n", s);
			}
			print("sbl %s \n", sblfile);
			print("dis %s \n", disfile);
			print("src %s \n", srcfile);
		"sym" =>
			(sym, s) = debug->sym(hd tl l);
			if(s != nil){
				print("err %s\n", s);
				continue;
			}
			(exp, s) = prog.stack();
			if(s != nil) 
				print("%s\n", s);
			for(i:=0; i < len exp; i++) {
				exp[i].m.addsym(sym);
				print("sbl %s \n", exp[i].m.sbl());
				print("dis %s \n", exp[i].m.dis());
				print("%s %s\n", exp[i].name, exp[i].srcstr());
			}
		"pctosrc" =>
			if(sym == nil) {
				(exp, s) = prog.stack();
				if(s != nil) print("%s\n", s);
				if (len exp > 0 && exp[0].m.sbl() != nil) {
					(sym, s) = debug->sym(exp[0].m.sbl());
					if (s != nil) print("%s\n", s);
				}
			}

			if(sym != nil){
				src := sym.pctosrc(int(hd tl l));
				if(src != nil)
					print("%s:%d.%d\n", src.start.file, src.start.line, src.start.pos);
			}
		"srctopc" => 
			if(sym != nil){
				l = tl l;
				f := hd l;
				l = tl l;
				ln := int(hd l);
				ss := ref Src(Pos(f,ln,0),Pos(f,ln+1,0));
				print("pc %d\n", sym.srctopc(ss));
			}
		"brk" =>
			l = tl l;
			ln := int(hd l);
			ss := ref Src(Pos(srcfile,ln,0),Pos(srcfile,ln+1,0));
			pc := sym.srctopc(ss);
			s = prog.setbpt(disfile, pc);
			if(s != nil)
				print("%s\n", s);
			breakpoints = sprint("%s:%d", srcfile, ln)  :: breakpoints;
			for (bp := breakpoints; bp != nil; bp = tl bp)
				print("breakpoint %s\n", hd bp);
		"src" =>
			srcfile = hd tl l;	
		"list" or "l" =>
			if(srcfile != nil) {
				l = tl l;
				if (l != nil) 
					sh->system(nil, sprint("sed -n '%sp' %s", hd l, srcfile));
				else
					sh->system(nil, sprint("sed -n '%d,%dp' %s", currline, currline+10, srcfile));
			} else print("err unknown srcfile\n");
		"expand" =>
			if(len l > 1)
				expand(hd tl l);
		"!" =>
			sh->system(nil, line[1:]);
		"help" =>
			print("run file.dis args	; program to debug with args\n");
			print("brk lineno		; set breakpoint in current file\n");
			print("src file.b		; source file for listing\n");
			print("next			; step over next statement\n");
			print("step			; step into next statement\n");
			print("ret			; continue until return\n");
			print("cont			; continue until breakpoint\n");
			print("kill			; kill the program\n");
			print("stop			; stop running program\n");
			print("unstop			; unstop \n");
			print("status			; print status from prog(3)\n");
			print("stack			; print stack\n");
			print("list begin,end		; list lines from source file\n");
			print("expand symbol		; expand and display value of symbol\n");
			print("quit 			; quit\n");
		* =>
			print("unknown %s\n", hd l);
		}
		last = l;
		print("> ");
	}
}

stack(prog: ref Prog)
{
	(exp, s) := prog.stack();
	if(s != nil) 
		print("%s\n", s);
	tos = exp[0];
	tos.m.stdsym();
	tos.findsym();
	src := tos.srcstr();
	print("%s %s\n", tos.name, src);
	(file, rest) := str->splitl(src, ":");
	(lnum, pos) := str->splitl(rest[1:], ".");
	currline = int(lnum);
	sh->system(nil, sprint("sed -n '%sp' %s", lnum, file));
	expand("tos");
}

expand(symbol: string)
{
	exp: array of ref Exp;
	case symbol {
	"tos" => exp = tos.expand();
	"locals" => exp = localvars.expand();
	"args" => exp = argvars.expand();
	"module" => exp = modulevars.expand();
	* => exp = tos.expand();
	}
	for (i:=0;i< len exp;i++){
		case exp[i].name {
		"locals" => localvars = exp[i];
		"args" => argvars = exp[i];
		"module" => modulevars = exp[i];
		* => print("%s %s\n", exp[i].name, exp[i].val().t0);
		}
	}
}	
