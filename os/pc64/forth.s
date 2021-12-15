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
TEXT	forthmain(SB), 1, $0		/* not a tail function, can RET back to the caller */
	/* Argument has the start of heap */
	MOVQ RARG, UP		/* start of heap memory */
	MOVQ 8(UP), UPE		/* HEAPEND populated by the caller */

	MOVQ UP, RSP
	ADDQ $RSTACK_END, RSP	/* return stack pointer, reset */

	MOVQ UP, PSP
	ADDQ $PSTACK_END, PSP	/* parameter stack pointer - stack setup, clear */
	MOVQ PSP, 16(UP)		/* parameter stack pointer store, for forth to c */

	/* execute boot */
	MOVQ UP, IP
	ADDQ $DTOP, IP	/* last defined word should be c_boot */
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
		JMP* CX; /* Start executing at docol address, JMP* = jump to a non-relative address */

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

/* TODO change to allow only fetches from a certain memory range */
TEXT	fetch(SB), 1, $-4	/* ( a -- n) */
	ADDQ UP, TOP
	MOVQ (TOP), TOP
	NEXT

/* TODO change to allow stores to a certain memory range only */
TEXT	store(SB), 1, $-4	/* ( n a -- ) */
	ADDQ UP, TOP
	POP(CX)
	MOVQ CX, (TOP)
	POP(TOP)
	NEXT

/* TODO change to allow only fetches from a certain memory range */
TEXT	cfetch(SB), 1, $-4	/* ( a -- c ) */
	ADDQ UP, TOP
	XORQ CX, CX
	MOVB (TOP), CL
	POP(TOP)
	NEXT

/* TODO change to allow only fetches from a certain memory range */
TEXT	cstore(SB), 1, $-4	/* ( c a -- ) */
	ADDQ UP, TOP
	POP(CX)
	MOVB CL, (TOP)
	POP(TOP)
	NEXT

/* TODO fix this */
TEXT	terminate(SB), 1, $-4	/* ( n -- ) */
	POP(TOP)
	NEXT

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

/* puts the top 2 entries of the data stack in the return stack */
TEXT	doinit(SB), 1, $-4	/* ( hi lo -- ) */
	MOVQ TOP, (RSP)
	POP(TOP)
	MOVQ TOP, 8(RSP)
	POP(TOP)
	ADDQ $16, RSP
	NEXT

/* not sure if this works, needs testing to follow https://github.com/mark4th/x64
	check the notes
	return stack would have
		current index
		end index
	(R lo hi -- )
	increment lo
	when hi > lo, go to the address next to doloop
 */
TEXT	doloop(SB), 1, $-4
	INCQ -16(RSP)
doloop1:
	MOVQ -16(RSP), CX
	CMPQ CX, -8(RSP)
	JGE .l4
	MOVQ (IP), IP
	NEXT
.l4:
	SUBQ $16, RSP
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

TEXT	rpop(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOP)
	RPOP(TOP)
	NEXT

TEXT	rpush(SB), 1, $-4	/* ( n -- ) */
	RPUSH(TOP)
	POP(TOP)
	NEXT

TEXT	i(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOP)
	MOVQ -16(RSP), TOP
	NEXT

TEXT	j(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOP)
	MOVQ -32(RSP), TOP
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

/* if x < y then y - x > 0, no sign flag
	intel manual says destination operand - source operand
	but, 9front assemblers seem to work differently
	compare x and y == CMP x, y
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

TEXT	lshift(SB), 1, $-4	/* ( n1 n2 -- n ) */
	MOVQ TOP, CX
	POP(TOP)
	SHLQ CL, TOP
	NEXT
	
TEXT	rshift(SB), 1, $-4	/* ( n1 n2 -- n ) */
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

TEXT	cmove(SB), 1, $-4	/* ( a1 a2 n -- ) */
	MOVQ TOP, CX
	POP(W)
	MOVQ IP, CX
	POP(IP)
	REP; MOVSB
	MOVQ CX, IP
	POP(TOP)
	NEXT

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
