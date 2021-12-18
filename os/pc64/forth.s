#include "mem.h"

/*

The bigger goal is to replace the dis vm with forth
forth outputs to stdout.
But, the input needs to be fixed.
make this into a devforth like device that reads commands and outputs the result.
replace variable with value (as in open firmware), to avoid exposing addresses

 forth kernel, amd64 9front variant

 Register usage:

	Original usage
 TOS: AX top of stack register
 SP:  SP parameter stack pointer, grows towards lower memory (downwards)
 RP:  BP (= RARG) return stack pointer, grows towards higher memory (upwards)
 AP:  SI address pointer
 W:   DI work register (holds CFA)
 	BX, CX, DX, R8-R15 temporary registers

plan9 assembler puts the first argument in BP (RARG), return value in AX.

	Changed to
 Leaving AX, SP, BP (RARG), R14, R15 alone to not mess with the C environment

 TOP: BX top of stack register
 PSP: DX parameter stack pointer, grows towards lower memory (downwards)
 RSP: R8 return stack pointer, grows towards higher memory (upwards)
 IP:  R9 instruction pointer
 W:   R10 work register (holds CFA)
 UP:  R11 register holding the start of this process's heap memory
 UPE: R12 register holding the end of this process's heap memory -- TODO, use this
	CX, SI, DI, R13 temporary registers

coding standard
: <name> (S input-stack --- output-stack) (R --- )
	(G descriptive glossary text)
	f1 f2  ( interim stack picture) \ programmers explanatory comment
		.. fn ;

Heap memory map: uses 8 pages at the start, will increase by *2 when filled up
high memory
Return stack 1 page (4096 bytes, BY2PG, 512 entries) at FFSTART
	|
	|
	v (grows downwards)
	^ (grows upwards)
	|
	|
tib, text input buffer 1024 bytes (until the next page?)
Parameter stack 1 page (BY2PG, 512 entries) at FFEND-4096
	|
	|
	v (grows downwards)
Pad
	^ (grows upwards)
	|
	|
User dictionary	upto  pages from the start
	word buffer 512 bytes
	error string buffer 128 bytes
		latest dictionary entry, Dtop
			need this as the system definitions and
			user definitions are not continuous
		dictionary pointer, Dp
		forth stack pointer, forthpsp
		heap size, heapsize
		heap start, heapstart, also in UP
UP: forth variables
low memory

TODO Move variable space out of the dictionary from #forth
11:31 < joe9> In x86 you want to keep the code in a different section than variables -- why?
11:31 < joe9> in my port, I am keeping them together.
11:32 < joe9> it gets messy with different sections.
11:32 < veltas> For performance reasons, if you are writing to a cache line with code in it I think there is a performance penalty
11:33 < veltas> Because x86 has a separate instruction and data cache in L1, but is kind enough to abstract this away. So you can write over executing code, but it causes some synchronisation that might be expensive. And I would expect this to be done on a cache-line granularity
11:39 < veltas> So you could end up with code running slower just because it happens to be defined after space for some data that's in active use... not good

*/

#define TOP BX /* top of stack register */
#define PSP DX /* parameter stack pointer, grows towards lower memory (downwards) */
#define RSP R8 /* return stack pointer, grows towards higher memory (upwards) */
#define IP  R9 /* instruction pointer */
#define W   R10/* work register (holds CFA) */
#define UP	R11/* start of heap memory */
#define UPE	R12/* end of heap memory */

#define PSTACK_SIZE BY2PG
#define RSTACK_SIZE BY2PG

/* putting this above the asm code as the v_dp define is needed by _main */
/*	m_ for primitive/macro word cfa
	mc_ for primtive/macro word constants
	c_ for colon word cfa
	ci_ for colon immediate word cfa
	v_ for colon variable word cfa

	CONSTANTS - capital letters
	Variables - initial capital case
	words - lower case
 */

/* HEAPSTART, HEAPEND, HERE, DTOP are loaded by the caller */
TEXT	forthmain(SB), 1, $-4		/* no stack storage required */

	/* Argument has the start of heap */
	MOVQ RARG, UP		/* start of heap memory */
	MOVQ 8(UP), UPE		/* HEAPEND populated by the caller */

	MOVQ UP, RSP
	ADDQ $RSTACK_END, RSP	/* return stack pointer, reset */

	MOVQ UP, PSP
	ADDQ $PSTACK_END, PSP	/* parameter stack pointer - stack setup, clear */
	MOVQ PSP, 24(UP)		/* parameter stack pointer store, for forth to c */

	/* execute boot */
	MOVQ UP, CX
	ADDQ $DTOP, CX	/* address of last defined word (c_boot) is at DTOP */
	MOVQ (CX), IP	/* IP = address of c_boot */
	ADDQ $24, IP	/* to get to the parameter field address of boot word */

/* lodsl could make this simpler. But, this is more comprehensible
	why not JMP* (W)?

Address   0     8    16
aword : docol  40   ...
Address   40    48
bword : docol   72
Address   72    80
cword : docol  ....
at docol address, some assembly instruction
Assume IP = 8
 */
#define NEXT	MOVQ (IP), W;	/* W = 40, contents of address in IP, some word's code field address */ \
		MOVQ (W), CX;	/* TOP = docol, Get the address in the address in IP = code field address */ \
		ADDQ $8, IP; 	/* move IP further, IP = 16 */ \
		JMP* CX;		/* Start executing at docol address, JMP* = jump to a non-relative address */

#define PUSH(r)	SUBQ $8, PSP; \
			MOVQ r, (PSP);
#define POP(r)	MOVQ (PSP), r; \
			ADDQ $8, PSP;
#define RPUSH(r)	SUBQ $8, RSP; \
			MOVQ r, (RSP);
#define RPOP(r)	MOVQ (RSP), r; \
			ADDQ $8, RSP;

	NEXT

TEXT	reset(SB), 1, $-4
	MOVQ UP, RSP
	ADDQ $RSTACK_END, RSP
	NEXT

TEXT	clear(SB), 1, $-4
	MOVQ UP, PSP
	ADDQ $PSTACK_END, PSP
	NEXT

TEXT	colon(SB), 1, $-4
	RPUSH(IP)
	LEAQ 8(W), IP
	NEXT

TEXT	exitcolon(SB), 1, $-4
	RPOP(IP)
	NEXT

TEXT	dodoes(SB), 1, $-4	/* ( -- a ) */
	RPUSH(IP)
	MOVQ 8(W),IP
	PUSH(TOP)
	LEAQ 16(W), TOP
	NEXT

TEXT	jump(SB), 1, $-4	/* ( -- ) */
	MOVQ (IP),IP
	NEXT

/*
	( f -- ) cjump address
	if true, skip the address and continue
	else, go to the address
 */
TEXT	cjump(SB), 1, $-4	/* ( f -- ) */
	MOVQ (IP), CX	/* get the next address */
	ADDQ $8, IP	/* move esi beyond that */
	TESTQ TOP, TOP
	JNZ .l1		/* if true, move along */
	MOVQ CX, IP	/* if false, go to the above address */
.l1:
	POP(TOP)
	NEXT

/*
callable by forth primitives to check address
	( a -- -1|0|1 )
	argument 1 in TOP = address
	return value in TOP
	-1			0			1
	if UP < address < UPE
		return 0	within range
	else if address < UP
		return -1	below UP
	else if UPE < address
		return 1	above UP
 */
TEXT	inup(SB), 1, $-4
	CMPQ TOP, UPE
	JGT aboveupe	/* a > UPE */
	CMPQ TOP, UP
	JLT belowup		/* a < UP */
	MOVQ $0, TOP	/* could use XORQ TOP, TOP to zero too */
	RET
belowup:
	MOVQ $-1, TOP
	RET
aboveupe:
	MOVQ $1, TOP
	RET

/*
callable by forth primitives to check address
	( n a -- -1|0|1 )
	argument 1 in TOP = address
	return value in TOP
	-1			0			1
	if UP < address && address+n < UPE
		return 0	within range
	else if address < UP
		return -1	below UP
	else if UPE < address+n
		return 1	above UP
 */
TEXT	bufinup(SB), 1, $-4
	POP(CX)
	CMPQ CX, $0 	/* negative n? */
	JLT belowup		/* TODO have an appropriate error message */
	ADDQ TOP, CX
	CMPQ CX, UPE	/* a+n, UPE */
	JGT aboveupe	/* a+n > UPE */
	CMPQ TOP, UP
	JLT belowup		/* a < UP */
	MOVQ $0, TOP
	RET

invalidaddress:
	/* TODO need error reporting here */
	RET

TEXT validateaddress(SB), 1, $0 /* a -- */
	CALL inup(SB)
	MOVQ TOP, CX
	POP(TOP)
	CMPQ CX, $0
	JNE	invalidaddress
	RET

TEXT validatebuffer(SB), 1, $0 /* n a -- */
	CALL bufinup(SB)
	MOVQ TOP, CX
	POP(TOP)
	CMPQ CX, $0
	JNE	invalidaddress
	RET

TEXT	fetch(SB), 1, $-4	/* ( a -- n) */
	PUSH(TOP)
	CALL validateaddress(SB)	/* a a -- a */
	MOVQ (TOP), TOP
	NEXT

TEXT	store(SB), 1, $-4	/* ( n a -- ) */
	PUSH(TOP)
	CALL validateaddress(SB)	/* a a -- a */
	POP(CX)
	MOVQ CX, (TOP)
	POP(TOP)
	NEXT

TEXT	cfetch(SB), 1, $-4	/* ( a -- c ) */
	PUSH(TOP)
	CALL validateaddress(SB)	/* a a -- a */
	XORQ CX, CX
	MOVB (TOP), CL
	MOVQ CX, TOP
	NEXT

TEXT	cstore(SB), 1, $-4	/* ( c a -- ) */
	PUSH(TOP)
	CALL validateaddress(SB)	/* c a a -- c a */
	POP(CX)
	MOVB CL, (TOP)
	POP(TOP)
	NEXT

TEXT	terminate(SB), 1, $-4	/* ( n -- ) */
	MOVQ TOP, AX
	RET

TEXT	fthdump(SB), 1, $-4	/* ( n -- ) */
	CALL dumpstack(SB)
	RET

#include "bindings.s"

TEXT	mmap(SB), 1, $-4	/* ( a1 -- a2 ) */
	MOVQ $-1, TOP	/* unimplemented */

TEXT	variable(SB), 1, $-4	/* ( -- a ) */
	PUSH(TOP)
	LEAQ 8(W), TOP
	NEXT

TEXT	constant(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOP)
	MOVQ 8(W), TOP
	NEXT

TEXT	literal(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOP)
	MOVQ (IP), TOP
	ADDQ $8, IP
	NEXT

/* TODO not sure about this */
TEXT	sliteral(SB), 1, $-4	/* ( -- a n ) */
	PUSH(TOP)
	XORQ TOP,TOP
	MOVB (IP), BL
	INCQ IP
	PUSH(IP)
	ADDQ TOP, IP
	ADDQ $7, IP
	ANDQ $~7, IP
	NEXT

/*
puts the top 2 entries of the data stack in the return stack
	( limit index -- ) (R -- index limit )
 */
TEXT	doinit(SB), 1, $-4	/* ( hi lo -- ) (R -- lo hi */
	RPUSH(TOP)
	POP(TOP)
	RPUSH(TOP)
	POP(TOP)
	NEXT

/*
needs testing to follow https://github.com/mark4th/x64
	check the notes
	return stack would have
		current index
		end index
	(R index limit -- )
	increment index
	when limit > index, go to the address next to doloop
 */
TEXT	doloop(SB), 1, $-4
	INCQ 8(RSP)
doloop1:
	MOVQ 8(RSP), CX
	CMPQ CX, 0(RSP)
	JGE .l4
	MOVQ (IP), IP
	NEXT
.l4:
	ADDQ $16, RSP
	ADDQ $8, IP
	NEXT

TEXT	doploop(SB), 1, $-4	/* ( n -- ) */
	ADDQ TOP, 16(RSP)
	POP(TOP)
	JMP doloop1

TEXT	rfetch(SB), 1, $-4	/* ( -- n ) no change in RSP */
	PUSH(TOP)
	MOVQ (RSP), TOP
	NEXT

TEXT	rpop(SB), 1, $-4	/* ( -- n ) (R n -- )*/
	PUSH(TOP)
	RPOP(TOP)
	NEXT

TEXT	rpush(SB), 1, $-4	/* ( n -- ) (R -- n ) */
	RPUSH(TOP)
	POP(TOP)
	NEXT

TEXT	i(SB), 1, $-4	/* ( -- index ) (R index limit -- index limit ) */
	PUSH(TOP)
	MOVQ 8(RSP), TOP
	NEXT

/* in nested do loops, j is the outer loop's index */
TEXT	j(SB), 1, $-4	/* ( -- index1 ) (R index1 limit1 index2 limit2 -- index1 limit1 index2 limit2 ) */
	PUSH(TOP)
	MOVQ 24(RSP), TOP
	NEXT

TEXT	plus(SB), 1, $-4	/* ( n1 n2 -- n ) */
	POP(CX)
	ADDQ CX, TOP
	NEXT  

TEXT	minus(SB), 1, $-4	/* ( n1 n2 -- n ) */
	MOVQ TOP, CX
	POP(TOP)
	SUBQ CX, TOP
	NEXT

TEXT	multiply(SB), 1, $-4	/* ( n1 n2 -- n1*n2 ) */
	POP(CX)
	IMULQ CX,TOP
	NEXT

TEXT	slashmod(SB), 1, $-4	/* ( n1 n2 -- remainder quotient ) n1/n2 */
	MOVQ (PSP), CX /* CX = n1 */
	PUSHQ DX /* DX == PSP, store DX and AX as they are used by CDQ and IDIV */
	PUSHQ AX
	XORQ DX, DX /* DX = 0 */
	MOVQ CX, AX /* AX = n1 */
	CDQ 		/* RAX -> RDX:RAX sign extension */
	IDIVQ TOP	/* RDX:RAX / TOP => Quotient in RAX, Remainder in RDX */
	MOVQ DX, CX	/* CX = remainder */
	MOVQ AX, TOP /* TOP = quotient */
	POPQ AX
	POPQ DX
	MOVQ CX, (PSP) /* -- remainder quotient */
	NEXT

TEXT	uslashmod(SB), 1, $-4	/* ( u1 u2 -- uremainder uquotient ) */
	MOVQ (PSP), CX /* CX = n1 */
	PUSHQ DX /* DX == PSP, store DX and AX as they are used by CDQ and IDIV */
	PUSHQ AX
	XORQ DX, DX /* DX = 0 */
	MOVQ CX, AX /* AX = n1 */
	IDIVQ TOP	/* RDX:RAX / TOP => Quotient in RAX, Remainder in RDX */
	MOVQ DX, CX	/* CX = remainder */
	MOVQ AX, TOP /* TOP = quotient */
	POPQ AX
	POPQ DX
	MOVQ CX, (PSP) /* -- uremainder uquotient */
	NEXT

	MOVQ TOP, TOP
	MOVQ (PSP), TOP
	XORQ PSP, PSP
	DIVQ TOP
	MOVQ PSP, (PSP)
	NEXT

TEXT	binand(SB), 1, $-4	/* ( n1 n2 -- n ) */
	ANDQ (PSP), TOP
	ADDQ $8, PSP
	NEXT

TEXT	binor(SB), 1, $-4	/* ( n1 n2 -- n ) */
	ORQ (PSP), TOP
	ADDQ $8, PSP
	NEXT

TEXT	binxor(SB), 1, $-4	/* ( n1 n2 -- n ) */
	XORQ (PSP), TOP
	ADDQ $8, PSP
	NEXT

TEXT	xswap(SB), 1, $-4	/* ( x y -- y x ) */
	XCHGQ TOP, (PSP)
	NEXT

TEXT	drop(SB), 1, $-4	/* ( x -- ) */
	POP(TOP)
	NEXT

TEXT	dup(SB), 1, $-4	/* ( x -- x x ) */
	PUSH(TOP)
	NEXT

TEXT	over(SB), 1, $-4	/* ( x y -- x y x ) */
	PUSH(TOP)
	MOVQ 8(PSP), TOP
	NEXT

TEXT	equal(SB), 1, $-4	/* ( x y -- f ) */
	POP(CX)
	CMPQ CX, TOP
	JEQ .true
	XORQ TOP, TOP
	NEXT
TEXT	true(SB), 1, $-4
.true:
	MOVQ $-1, TOP
	NEXT
	
TEXT	greater(SB), 1, $-4	/* ( x y -- f ) */
	POP(CX)
	CMPQ CX, TOP
	JGT .true
	XORQ TOP, TOP
	NEXT

/*
if x < y then y - x > 0, no sign flag
	intel manual says destination operand - source operand
	9front comparision operators make the usage more english-like
	For, CMP x,y; JGT greater can be read as
	compare x and y; if x > y, goto greater
	check tests/cmp.s for tests
 */
TEXT	less(SB), 1, $-4	/* ( x y -- f ) */
	POP(CX)
	CMPQ CX, TOP
	JLT .true
	XORQ TOP, TOP
	NEXT

TEXT	stackptr(SB), 1, $-4	/* ( -- a ) does not include TOP! */
	PUSH(TOP)
	MOVQ PSP, TOP
	NEXT

TEXT	lshift(SB), 1, $-4	/* ( n1 n2 -- n1<<n2 ) */
	MOVQ TOP, CX
	POP(TOP)
	SHLQ CL, TOP
	NEXT
	
TEXT	rshift(SB), 1, $-4	/* ( n1 n2 -- n1>>n2 ) */
	MOVQ TOP, CX
	POP(TOP)
	SHRQ CL, TOP
	NEXT

TEXT	rshifta(SB), 1, $-4	/* ( n1 n2 -- n ) */
	MOVQ TOP, CX
	POP(TOP)
	SARQ CL, TOP
	NEXT

TEXT	execute(SB), 1, $-4	/* ( ... a -- ... ) */
	PUSH(TOP)
	CALL validateaddress(SB)	/* a a -- a */
	MOVQ TOP, W
	POP(TOP)
	MOVQ (W), CX
	JMP CX

TEXT	deferred(SB), 1, $-4
	MOVQ 8(W), W
	MOVQ (W), CX
	JMP CX

TEXT	unloop(SB), 1, $-4
	ADDQ $16, RSP
	NEXT

/* TODO validateaddress on both addresses */
TEXT	cmove(SB), 1, $-4	/* ( a1 a2 n -- ) */
	MOVQ TOP, CX
	POP(W)
	MOVQ IP, CX
	POP(IP)
	REP; MOVSB
	MOVQ CX, IP
	POP(TOP)
	NEXT

/* TODO validateaddress on both addresses */
TEXT	cmoveb(SB), 1, $-4	/* ( a1 a2 n -- ) */
	MOVQ TOP, CX
	POP(W)
	DECQ TOP
	ADDQ TOP, W
	MOVQ IP, CX
	POP(IP)
	ADDQ TOP, IP
	STD
	REP; MOVSB
	CLD
	MOVQ CX, IP
	POP(TOP)
	NEXT

TEXT	cas(SB), 1, $-4	/* ( a old new -- f ) */
	MOVQ TOP, DI	/* new */
	POP(TOP)	/* old */
	POP(SI)	/* addr */
	LOCK; CMPXCHGQ DI, (SI)
	JE .true
	XORQ TOP, TOP
	/* pause -- no equivalent in 6a ? */
	NEXT

TEXT	S0(SB), 1, $-4	/* S0 needs a calculation to come up with the value */
	PUSH(TOP)
	MOVQ UP, TOP
	ADDQ $PSTACK_END, TOP
	NEXT

TEXT	H0(SB), 1, $-4	/* user pointer, start of heap */
	PUSH(TOP)
	MOVQ UP, TOP
	NEXT

TEXT	Wordb(SB), 1, $-4	/* WORDB location */
	PUSH(TOP)
	MOVQ UP, TOP
	ADDQ $WORDB, TOP
	NEXT

TEXT	Tib(SB), 1, $-4		/* TIB location */
	PUSH(TOP)
	MOVQ UP, TOP
	ADDQ $TIB, TOP
	NEXT

TEXT	Dp(SB), 1, $-4	/* S0 needs a calculation to come up with the value */
	PUSH(TOP)
	MOVQ UP, TOP
	ADDQ $HERE, TOP
	NEXT

TEXT	Dtop(SB), 1, $-4	/* S0 needs a calculation to come up with the value */
	PUSH(TOP)
	MOVQ UP, TOP
	ADDQ $DTOP, TOP
	NEXT

TEXT	Args(SB), 1, $-4
	PUSH(TOP)
	MOVQ UP, TOP
	ADDQ $ARGS, TOP
	NEXT

/*
 * variables used by the core words. Using variable code word instead of known locations.
#define	VARIABLE(name, location)	TEXT	name(SB), 1, $-4 ;\
	PUSH(TOP); \
	MOVQ UP, TOP ;\
	ADDQ location, TOP ;\
	NEXT;
VARIABLE(Tib, $TIB)
 */

TEXT	forthend(SB), 1, $-4

	END
