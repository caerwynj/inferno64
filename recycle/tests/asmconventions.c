#include <u.h>
#include <libc.h>

extern void asmarg1(int);
extern void asmarg2(int);

/*
check the generated asm and the calling conventions. use 6c -S asmconventions.c
check the inferno.notes for the explanation
*/

s64
arg0(void)
{
	return 8+4;
}

s64
arg1(s64 a)
{
	return a+4;
}

s64
arg2(s64 a, s64 b)
{
	return a+arg1(a)+b;
}

s64
arg3(s64 a, s64 b, s64 c)
{
	return a+b+c;
}

s64
arg3caller(s64 a, s64 b, s64 c)
{
	return arg3(a+10,b+20,c+30);
}

s64
arg2local2(s64 a, s64 b)
{
	s64 c = 10, d = 20;

	c = arg1(a);
	d = c+arg1(b)+a;
	return d;
}

s64
arg2local2s(s64 a, s64 b)
{
	s64 c = 10, d = 20;

	c += arg2(a,d);
	d = c+a+2;
	return d;
}

s64
arg2local6s(s64 a, s64 b)
{
	s64 c = 10, d = 20, e = 30, f = 40, g = 50, h = 60;

	c = arg2(a,d);
	d = c+a+2+f+g+h;
	return d;
}

s64
arg3local1(s64 a, s64 b, s64 c)
{
	int d = 50;

	return arg3(a+10,b+20,c+30+d+10);
}

s64
arg3local2(s64 a, s64 b, s64 c)
{
	int d = 50, e = 60;

	return arg3(a+10,b+20+e+10,c+30+d+10);
}

void
main(int, void**)
{
	arg3local2(1,2,3);
	exits("");
}

/*

teaching C programming language
<cinap_lenrek> c is very simple language  [18:01]
<cinap_lenrek> Glats: this just takes practice.  [18:02]
<cinap_lenrek> Glats: how many languages can you read?
<Glats> java, golang, js, ruby , php and a little c++  [18:03]
<cinap_lenrek> Glats: so you shouldnt have much difficulty reading c  [18:05]
<cinap_lenrek> Glats: anything specific you have difficulty with in c?  [18:06]
<Glats> now i dont understand the folder structure
<Glats> and where is the "main()"  [18:07]
<cinap_lenrek> folder struture?
<Glats> sorry
<cinap_lenrek> you mean modules?
<Glats> structure  [18:08]
<Glats> yeah
<cinap_lenrek> or you mean the struct data types?
<Glats> and where start the program i mean the main function
<cinap_lenrek> ok
<cinap_lenrek> so thats a bit tautological  [18:09]
<cinap_lenrek> a c program consists just of a bunch of functions
<cinap_lenrek> and the main function is just the one where execution starts
<cinap_lenrek> when one program does a exec() the os replaces the text/data segment of the process with the new one and jumps to the new programs main function, passing the arguments  [18:10]
<cinap_lenrek> its mostly a convention
<cinap_lenrek> not really language specific
<cinap_lenrek> when you look close
<cinap_lenrek> libc has a bunch of assembly that sets up a stack and then manually jumps to main()  [18:11]
<cinap_lenrek> a c compiler only knows how to compile functions
<cinap_lenrek> and whats a function?
<cinap_lenrek> its also a convention
<cinap_lenrek> its some hunk of code with a entry point and a calling convention on how to pass it parameters  [18:12]
<cinap_lenrek> and a way to return from the function
<cinap_lenrek> a function can be written in other languages, in a program
<cinap_lenrek> like assembly
<cinap_lenrek> or be implemented as a system call  [18:13]
<cinap_lenrek> anyway
<cinap_lenrek> you run the c compiler on a c source file
<cinap_lenrek> and it generates these hunks of code
<cinap_lenrek> and a symbol table
<cinap_lenrek> and then you use a linker to cat all these hunks together, and make all the addresses absolute  [18:14]
<cinap_lenrek> and you get one huge hunk of code with a entry point, which is the main... or some assembly that then jumps to the main
<cinap_lenrek> the linker also figures out which functions are needed  [18:15]
<cinap_lenrek> and can leave out .o files that it doesnt need
<cinap_lenrek> thats why libraries often have one function per .c file
<cinap_lenrek> so if you dont use the function, the linker can omit the object code from the resulting binary
<cinap_lenrek> does this make sense?  [18:17]
<Glats> of course
<Glats> perfectly
<cinap_lenrek> experiment
<cinap_lenrek> B /tmp/a.c
<joe9> cinap_lenrek: that is the most concise and accurate description of C.  [18:18]
<cinap_lenrek> int
<cinap_lenrek> add(int a, int b)
<cinap_lenrek> {
<cinap_lenrek> return a+b;
<cinap_lenrek> }
<cinap_lenrek> very simple function
<cinap_lenrek> 6c -S a.c
<cinap_lenrek> term% 6c -S a.c
<cinap_lenrek> TEXT add+0(SB),0,$0
<cinap_lenrek> MOVL BP,AX
<cinap_lenrek> ADDL b+8(FP),AX
<cinap_lenrek> RET ,
<cinap_lenrek> thats what the c compiler produces  [18:19]
<cinap_lenrek> the "int a" parameter is passed in BP register here
<cinap_lenrek> thats just the calling convention of amd64
<cinap_lenrek> the first arg is passed in BP register
<cinap_lenrek> (on plan9
<cinap_lenrek> and b+8(FP) is the second parameter "int b", from the stack  [18:20]
<cinap_lenrek> return value is passed in AX register
<cinap_lenrek> int
<cinap_lenrek> sub(int a, int b)
<cinap_lenrek> {
<cinap_lenrek> return a-b;
<cinap_lenrek> }
<cinap_lenrek> put a second function there, repeat
<cinap_lenrek> and it just prints two functions in assembly  [18:21]
<cinap_lenrek> note, theres no main() in this file
<cinap_lenrek> but it compile everything just fine  [18:22]
<cinap_lenrek> the -S flag just make it print assembly
<cinap_lenrek> now, lets try to link it
<cinap_lenrek> term% 6l a.6
<cinap_lenrek> _main: undefined: main in _main
<cinap_lenrek> crazy!
<cinap_lenrek> whats _main?
<cinap_lenrek> thats the assembly function i told you before  [18:23]
<cinap_lenrek> that sets up the stack and then calls main()
<cinap_lenrek> but here, the linker cannot find a main() function in the symbol table because he havnt made one
<cinap_lenrek> you could make a second .c file
<cinap_lenrek> b.c
<cinap_lenrek> and have a main() function in there
<cinap_lenrek> and then it would be able to link a.6 and b.6 together and that would work  [18:24]
<cinap_lenrek> anyway
<cinap_lenrek> if you call a functoin in c, for the compiler, its mostly just a name  [18:25]
<cinap_lenrek> (and a function signature (parameter types))
<cinap_lenrek> later, the linker resolves this name
<cinap_lenrek> everything gets resolved at link time  [18:26]
<Glats> pretty cool
<Glats> thnks you so much
<cinap_lenrek> you know function "prototypes"?
<cinap_lenrek> the stuff in the .h files?
<Glats> nope :/
<cinap_lenrek> thats basically to tell the compiler which arguments and types are there  [18:27]
<qeed> just read a c book man
<Glats> and you can import it?
<Glats> to the .c files right?
<cinap_lenrek> its just so the compiler can warn you when you pass the wrong types
<cinap_lenrek> its just a promise, that later, at link time, that function will be there  [18:28]
<cinap_lenrek> the linker only cares about functions that get actually *USED*
<Glats> like a signature?  [18:29]
<cinap_lenrek> there are signatures involved
<cinap_lenrek> so that what the c compiler thinks the parameter types are and whats in already compiled object files matches  [18:30]
<Glats> ok
<cinap_lenrek> tho thats plan9 specific
<cinap_lenrek> i mean, c doesnt mandate this
<cinap_lenrek> it could as well just assume everything matches always  [18:31]
<cinap_lenrek> theres just one namespace
<cinap_lenrek> someone calls add(1,2);  [18:32]
<cinap_lenrek> compiler puts CALL add(SB) in the object file
<cinap_lenrek> linker just looks for a symbol called "add" in all the object files
<cinap_lenrek> and then produces the *actual* machine code with the name replaced by its memory address
<Glats> nice  [18:35]
<cinap_lenrek> note
<Glats> i got you
<cinap_lenrek> this isnt really c :)
<cinap_lenrek> more like how the plan9 (and many other) c compilers/linkers work
<cinap_lenrek> you could as well make a c compiler that only uses single .c files  [18:36]
<cinap_lenrek> and has no support for modules
<cinap_lenrek> or a interpreter
<cinap_lenrek> or one that dynamically compiles c files
<Glats> thank you again. and i hope not bother you. I will read more code  [18:37]
<cinap_lenrek> another hint  [18:38]
<cinap_lenrek> .a files are basically just zip files with many .o files in them
<cinap_lenrek> (without the compression)
<cinap_lenrek> ar(6)
<Glats> nice  [18:40]

19:03 < joe7> Text callfunction(SB), 0, $-4 or $0 or whatever has nothing to do with the contents of the stack. It is used to set the SP location in the callee.
19:03 < joe7> does that make sense?
19:11 < ori> depends on what you mean by 'has nothign to do with the contents of the stack'
19:11 < ori> it says how much stack space callfuntion() is going to use.
19:11 < ori> which is the same as the value of SP in the callee
19:12 < joe7> if we do a call callfunction(SB), the stack still has the return pc (the pc after the call)?
19:12 < joe7> I am trying to figure out how setlabel in l.s works.
19:13 < joe7> I see the procswitch() calls setlabel()
19:13 < joe7> but, I am not able to visualize the stack contents as 0(SP) is the return pc in setlabel().
19:14 < joe7> that return pc is the instruction after the if(!setlabel(&up->sched).. call?
19:14 < joe7> or the is return pc the pc after the caller of procswitch()?
19:17 < joe7> MOVQ0(SP), BX -- store return PC 
19:17 < joe7> so 0(SP) is the return PC.
19:18 < joe7> I am trying to figure out what return PC is?
19:18 < joe7> the instruction after call setlabel()? or, the instruction after procswitch()?
19:55 < ori> the instruction after the function call.
19:56 < ori> this is just x86: read the docs for the call instruction
20:09 < joe7> What did the $-4 do then? SP would be the same with $-4 or $0, correct?
21:06 < ori> joe7: dunnoo.
21:08 < ori> reading /sys/doc/asm.ps, it says 'On machines with a link register, such as MIPS and SPARC, the special value -4 instructs the loader to genreate no PC save and restore instructions, even if the function is not a leaf.'
21:23 < joe7> so, on amd64, -4 does nothing?
21:27 < ori> dunno, assemble it and see?
21:27 < ori> *disassemble it and see?
21:29 < joe7> what tool do you use for disassembling?
21:35 < ori> acid
21:41 < ori> asm(func)
21:43 < joe7> isn't that what 6c -S does?
21:44 < joe7> It does not show how the relationship between SP and return PC.
21:50 < joe7> http://okturing.com/src/12786/body the first local adds 16 bytes to that number and the second local does not change the number.
22:02 < ori> joe7: no.
22:02 < ori> 6c -s obviously shows the asm before the linker does anything with it.
22:02 < ori> asm sees it after.
Day changed to 14 Dec 2021
02:43 < cinap_lenrek> joe7: 0(SP) is return pc, yes
02:44 < k0ga> cinap_lenrek: hi!
02:44 < k0ga> cinap_lenrek: I already have the house
02:44 < cinap_lenrek> joe7: and the $-4 offset in the TEXT is a flag
02:44 < cinap_lenrek> its not a real offset
02:44 < cinap_lenrek> k0ga: WOOOO!!!!
02:44 < k0ga> I told quinq yesterday that maybe it is a good idea if you guys go there this weekend
02:46 < cinap_lenrek> k0ga: yeah, cool
02:48 < cinap_lenrek> joe7: also note, the stack on most archs need to be aligned!
02:48 < k0ga> cinap_lenrek: talk with quinq and fer about it please ;)
02:48 < cinap_lenrek> k0ga: okay! :)
02:49 < k0ga> 10:48 < cinap_lenrek> joe7: also note, the stack on most archs need to be aligned! <- and in the few were the arch doesn't need it the compiler needs it
02:50 < cinap_lenrek> joe7: and 4 isnt aligned on 64 bit arch... needs to be 8 byte aligned...
02:50 < cinap_lenrek> or even 16 with elf abi
02:50 < k0ga> cinap_lenrek: hahahahahahah
02:50 < cinap_lenrek> because intel screwed up their mmx

05:55 < joe7> 02:44 < cinap_lenrek> joe7: and the $-4 offset in the TEXT is a flag -- I am trying to figure out what the flag does on amd64?
05:55 < joe7> do not reserve any memory for the locals?
05:56 < joe7> Isn't that what $0 would do?
05:56 < joe7> too.
05:56 < joe7> So, how is $-4 different on amd64?

11:39 < joe7> ori, cinap_lenrek the src() and asm() show totally different things (I think). Just want to check if this makes sense to you http://okturing.com/src/12788/body
11:40 < joe7> I am not even sure if asm() is showing the same code as src()
11:41 < Leimy> khm: Face McShooty... that's all I have to say :-)
11:42 < piroko> khm: oh man I definitely lost it at ?bonerfarts?
11:42 < piroko> my sense of humor has never been called mature though
11:43 < Leimy> oh it's juevenile for sure... and that's part of why I like it.
12:11 < cinap_lenrek> jor7: off
12:11 < cinap_lenrek> jor7: no idea whats going on there
12:12 < cinap_lenrek> works fine with our kernel
12:12 < joe7> the code is not 9front code. but, 9ferno's. ok, will try with teh 9front kernel.
12:12 < joe7> thanks.
12:13 < joe7> cinap_lenrek: I am reading the mailing list to find answers to my questions. I found this by you: 
              https://marc.info/?l=9fans&m=145436696708016&w=2
12:13 < cinap_lenrek> tho theres a odd thing that it is one line ahead
12:13 < joe7> but, 0(FP) would be the return PC, correct?
12:13 < cinap_lenrek> maybe that is the issue
12:14 < joe7> I understand that technically 0(FP) should be the first argument.
12:14 < cinap_lenrek> and the assembler generates off by one line numbers in the debug info
12:14 < joe7> is there a better way to use asm() in acid to see the assembly of a function?
12:15 < joe7> or, is it asm(), casm()...
12:15 < cinap_lenrek> joe7 ? but, 0(FP) would be the return PC, correct?
12:15 < cinap_lenrek> no
12:15 < cinap_lenrek> i dont think so
12:16 < cinap_lenrek> 0(SP) is
12:16 < cinap_lenrek> i mean
12:16 < cinap_lenrek> lets try it
12:16 < joe7> http://okturing.com/src/12789/body is how I understand the SP and FP relationship.
12:16 < cinap_lenrek> TEXT _main(SB), $-4
12:16 < cinap_lenrek> MOV 0(FP), AX
12:17 < joe7> another thing I could not understand is why do you use $-4 for assembly? It does not make a difference in amd64, correct?
12:17 < joe7> Why not just $0 then?
12:18 < joe7> I understand that it is a flag. But, I cannot figure out what the difference between $-4 and $0 is (on amd64).
12:19 < quinq> k0ga, sure, when?
12:21 < cinap_lenrek> acid: asm(_main)
12:21 < cinap_lenrek> _main 0x0000000000010028 MOV 8(SP),R0
12:21 < cinap_lenrek> _main+0x4 0x000000000001002c RETURN
12:21 < cinap_lenrek> acid: asm(_main)
12:21 < cinap_lenrek> _main 0x0000000000010028 MOV 8(SP),R0
12:21 < cinap_lenrek> _main+0x4 0x000000000001002c RETURN
12:21 < cinap_lenrek> TEXT _main(SB), $0
12:21 < cinap_lenrek> MOV 0(FP), R0
12:21 < cinap_lenrek> RETURN
12:21 < cinap_lenrek> so no.
12:21 < cinap_lenrek> 0(FP) is the first arg
12:23 < joe7> My mistake is that I am looking at SP and FP as stack pointers. I probably should be looking at them as data structures. Where x(FP) refers to argument x(?)
12:23 < joe7> I understand that they translate to stack pointers.
12:23 < cinap_lenrek> its not a real register
12:24 < cinap_lenrek> its an offset of the stack pointer
12:24 < joe7> is there space in the stack for 0(FP)?
12:25 < joe7>  its an offset of the stack pointer -- it tends to be so for the 2nd and so on arguments.
12:25 < joe7> but, thinking about FP as an offset to the stack pointer falls down when we consider 0(FP), correct?
12:25 < cinap_lenrek> why?
12:26 < joe7> Is there space in the stack for 0(FP)?
12:26 < cinap_lenrek> yes, theres a slot reserved for 0(FP) as well
12:26 < cinap_lenrek> even if it is passed as a register
12:26 < joe7> http://okturing.com/src/12789/body in this example, then FP = address 0?
12:26 < cinap_lenrek> in case we need to save it, we can put it back on the stack
12:27 < joe7> so, 0(SP) is return pc. 8(SP) is the callee's second argument?
12:27 < joe7> 0(SP) is my (caller) return pc
12:27 < cinap_lenrek> return pc is in 0(FP)
12:27 < cinap_lenrek> 1st argument is in BP
12:27 < cinap_lenrek> 2nd argument is at 8(FP)
12:28 < cinap_lenrek> look, this cant both be true
12:28 < cinap_lenrek> 1st argument is *PASSED* in BP, but 0(FP) should be valid as well
12:28 < joe7> so, what is the x(SP) for the first argument?
12:28 < cinap_lenrek> 8(SP)
12:28 < joe7> it is not 8(SP) as that woud be the second argument.
12:29 < cinap_lenrek> how?
12:30 < joe7> http://okturing.com/src/12790/body
12:30 < joe7>         ADDQ    $20,DI
12:30 < joe7>         MOVQ    DI,8(SP)
12:30 < joe7> is for the second argument
12:31 < joe7> We know that 0(SP) is the return pc already.
12:31 < joe7> so, there is no x(SP) for the first argument
12:32 < cinap_lenrek> thats the compiler output
12:32 < cinap_lenrek> now link it and disassemble it
12:33 < cinap_lenrek> it will emit code where it moves the stack pointer right after entry to allocate space for the arguments for the call arg3()
12:33 < cinap_lenrek> then FP accesses take this into account
12:33 < cinap_lenrek> basically, the whole idea for FP is that it is always pointing to YOUR call frame arguments
12:33 < joe7> ok, thanks. will check it out. BTW, if I am writing asm, I should assume that 0(SP) = return pc, 8(SP) = second argument, correct?
12:34 < cinap_lenrek> no matter what other local variables you allocated
12:34 < joe7> yes, what you say about FP and SP as stack pointers might make sense after the linker magic.
12:34 < cinap_lenrek> 8(SP) is the slot of the first argument
12:34 < cinap_lenrek> 16(SP) is the second argument
12:34 < cinap_lenrek> note, on *ENTRY*
12:35 < cinap_lenrek> the caller doesnt know how much local variables a function will use
12:35 < joe7> are you talking after the linker, disassembly?
12:35 < cinap_lenrek> the function itself will have a prolog to move the stack pointer by the amount needed for local vars
12:35 < cinap_lenrek> what?
12:36 < cinap_lenrek> after the linker, FP is gone
12:36 < cinap_lenrek> its like a handy macro
12:36 < cinap_lenrek> in the actual machine code it will reference only SP
12:36 < joe7> before the linker, this is wrong. < cinap_lenrek> 8(SP) is the slot of the first argument
12:36 < joe7> it is referring to the second argument.
12:38 < cinap_lenrek> joe7: maybe i'm confused, but then you just show me where this is the case
12:38 < joe7> http://okturing.com/src/12790/body
12:39 < joe7> b+20 is to 8(SP)
12:39 < cinap_lenrek> no
12:39 < cinap_lenrek> thats the new callframe!
12:39 < cinap_lenrek> thats the callframe for arg3() call
12:39 < cinap_lenrek> and you have to remember that the CALL also *PUSHES* the returnpc
12:40 < Leimy> Thank Wheeler... stupid subroutines
12:40 < joe7> I am confused now.
12:40 < joe7> in arg3caller, SP is the stack pointer of this function. FP is the call frame of this function.
12:41 < joe7> when arg3() is entered, the FP there would be a stack pointer somewhere related to the SP of the caller, correct?
12:41 < cinap_lenrek> this is x86
12:41 < cinap_lenrek> a call will PUSH the returnpc on the stack
12:41 < cinap_lenrek> theres no link register like on risc
12:41 < cinap_lenrek> so on entry, the world looks different
12:42 < joe7> the FP in the callee 
12:42 < cinap_lenrek> yes
12:42 < joe7> would be somehow related to the SP of the caler, correct?
12:42 < cinap_lenrek> wtf are you talking about?
12:42 < joe7> for example, 8(SP) in caller == 0(FP) in callee?
12:43 < joe7> assuming that is the first argument.
12:43 < cinap_lenrek> how often do i need to repeat that CALL instruction subtracts 8 from the stack pointer?
12:44 < joe7> that is what I do not understand.
12:44 < sigrid> joe7: https://www.felixcloutier.com/x86/call
12:44 < sigrid> (great read)
12:46 < joe7> but, SP and FP are psuedo registers. SP is not the actual stack pointer.
12:47 < cinap_lenrek> no
12:47 < joe7> SP is a psuedo register with offsets for this function(?)
12:47 < sigrid> on 386 and amd64 SP IS actual register
12:47 < cinap_lenrek> just assemble and link the code you pasted and see
12:47 < joe7> ok, thanks.

*/
