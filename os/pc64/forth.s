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
 Leaving AX, SP, BP (RARG) alone to not mess with the C environment

 TOS: BX top of stack register
 PSP: DX parameter stack pointer, grows towards lower memory (downwards)
 RSP: R8 return stack pointer, grows towards higher memory (upwards)
 IP:  R9 instruction pointer
 W:   R10 work register (holds CFA)
 H0:  R11 register holding the start of this process's heap memory
	CX, SI, DI, R12-R15 temporary registers

coding standard
: <name> (S input-stack --- output-stack) (R --- )
	(G descriptive glossary text)
	f1 f2  ( interim stack picture) \ programmers explanatory comment
		.. fn ;

Heap memory map: uses 8 pages at the start, will increase by *2 when filled up
Variables
	system variables
		heap start, heapstart, also in H0
		heap size, heapsize
		forth stack pointer, forthsp
		dictionary top, dtop
	error string buffer 128 bytes
	word buffer 512 bytes
	tib, text input buffer 1024 bytes (until the next page?)
User dictionary	upto 6 pages from the start
Return stack 1 page (4096 bytes, BY2PG, 512 entries) at FFSTART
	|
	|
	v (grows downwards)
Parameter stack 1 page (BY2PG, 512 entries) at FFEND-4096
	^ (grows upwards)
	|
	|
SSTACK_END = FORTHEND
*/

#define TOP BX /* top of stack register */
#define PSP DX /* parameter stack pointer, grows towards lower memory (downwards) */
#define RSP R8 /* return stack pointer, grows towards higher memory (upwards) */
#define IP  R9 /* instruction pointer */
#define W   R10/* work register (holds CFA) */
#define H0	R11/* start of heap memory */

#define PSTACK_SIZE BY2PG
#define RSTACK_SIZE BY2PG

#define HEAPSTART	(0ull)
#define HEAPSIZE	(HEAPSTART+8)
#define FORTHSP		(HEAPSTART+16)
#define DTOP		(HEAPSTART+24)
#define ERRSTR		(HEAPSTART+32)
#define WORDB		(HEAPSTART+160)	/* word buffer */
#define TIB			(HEAPSTART+672)	/* text input buffer */
#define DICTIONARY	(HEAPSTART+2048)
#define DICTIONARY_END	(HEAPSTART+(6*BY2PG))
#define RSTACK		(HEAPSTART+(6*BY2PG))
#define PSTACK_END	(RSTACK+(2*BY2PG))
#define FORTHEND 	PSTACK_END

#define	LAST $centry_c_boot(SB) /* last defined word, should generate this */

TEXT	tib(SB), 1, $-4
	MOVQ H0, TOP
	ADDQ $TIB, TOP
	NEXT

TEXT	wordb(SB), 1, $-4
	MOVQ H0, TOP
	ADDQ $WORDB, TOP
	NEXT

TEXT	h(SB), 1, $-4
	MOVQ H0, TOP
	ADDQ $DTOP, TOP
	NEXT

TEXT	dp(SB), 1, $-4
	MOVQ H0, TOP
	ADDQ $DTOP, TOP
	NEXT

TEXT	s0(SB), 1, $-4
	MOVQ H0, TOP
	ADDQ $FORTHEND, TOP
	NEXT

TEXT	forthsp(SB), 1, $-4
	MOVQ H0, TOP
	ADDQ $FORTHSP, TOP
	NEXT

/* putting this above the asm code as the v_dp define is needed by _main */
/*	m_ for primitive/macro word cfa
	mc_ for primtive/macro word constants
	c_ for colon word cfa
	ci_ for colon immediate word cfa
	v_ for colon variable word cfa
 */
#include "primitives.s"

TEXT	forthmain(SB), 1, $-4		/* _main(SB), 1, $-4 without the libc */
	/* Argument has the start of heap */
	MOVQ RARG, H0		/* start of heap memory */

	MOVQ H0, RSP
	ADDQ $RSTACK, RSP	/* return stack pointer */

	MOVQ H0, PSP
	ADDQ $FORTHEND, PSP	/* parameter stack pointer - stack setup */

	MOVQ H0, TOP
	ADDQ $HEAPSTART, TOP
	MOVQ TOP, (H0)		/* store the start address at that address too - magic check */
	ADDQ $FORTHEND, TOP
	MOVQ TOP, $HEAPSIZE

	/* The last dictionary entry address is stored in dtop.
	 * The location of dtop is stored in the variable dp.
	 * To get the location of dtop, get the value in the parameter field
	 * (link + name(1+2) + code field address = 24 bytes) of the dp
	 * dictionary entry.
	 */
	/*
	 * dtop address is stored in the parameter field address(24-32 bytes) of mventry_dp
	 */
	MOVQ mventry_dp+24(SB), SI	/* now, SI = dtop address */
	MOVQ (SI), TOP	/* TOP = *CX = $LAST = boot word address (defined last, stored at dtop) */
				/* if 6a allows multiple symbols per address, then 
					the above 3 instructions would have been
					MOVQ (($mventry_dp+24(SB))), TOP */
	/*
	 * Could do this instead of the calculations below
	 * LEAQ 24(TOP), IP
	 */
	ADDQ $16, TOP	/* TOP += link (8 bytes) + len (1 byte) + minimum for align to 8 bytes */
	XORQ CX, CX
	MOVB 8(SI), CL	/* CL = length of boot name */
	ADDQ CX, TOP	/* TOP += len */
	ANDQ $~7, TOP	/* TOP = address of boot's code - 8 bytes */
	LEAQ 8(TOP), IP	/* IP = L257 = start of boot code = has docol address there
					 * skipping over docol as we do not need to save the IP
					 */

	MOVQ $centry_c_boot(SB), IP
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
		MOVQ (W), TOP;	/* TOP = docol, Get the address in the address in IP = code field address */ \
		ADDQ $8, IP; 	/* move IP further, IP = 16 */ \
		JMP* TOP; /* Start executing at docol address, JMP* = jump to a non-relative address */

#define PUSH(r)	SUBQ $8, PSP; \
			MOVQ r, (PSP)
#define POP(r)	MOVQ (PSP), r; \
			ADDQ $8, PSP

	NEXT

TEXT	reset(SB), 1, $-4
	MOVQ $FFSTART, RSP
	NEXT

TEXT	clear(SB), 1, $-4
	MOVQ $FFEND, PSP
	NEXT

TEXT	colon(SB), 1, $-4
	MOVQ IP,(RSP)
	ADDQ $8, RSP
	LEAQ 8(W), IP
	NEXT

TEXT	exitcolon(SB), 1, $-4
	SUBQ $8, RSP
	MOVQ (RSP), IP
	NEXT

TEXT	dodoes(SB), 1, $-4	/* ( -- a ) */
	MOVQ IP,(RSP)
	ADDQ $8,RSP
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
	MOVQ (TOP), TOP
	NEXT

/* TODO change to allow stores to a certain memory range only */
TEXT	store(SB), 1, $-4	/* ( n a -- ) */
	POP(CX)
	MOVQ CX, (TOP)
	POP(TOP)
	NEXT

TEXT	cfetch(SB), 1, $-4	/* ( a -- c ) */
	XORQ CX, CX
	MOVB (TOP), CL
	POP(TOP)
	NEXT

TEXT	cstore(SB), 1, $-4	/* ( c a -- ) */
	POP(CX)
	MOVB CL, (TOP)
	POP(TOP)
	NEXT

/* TODO fix this */
TEXT	terminate(SB), 1, $-4	/* ( n -- ) */
	XORQ CX, CX
	TESTQ TOP, TOP
	JZ .l2
	MOVQ $failtext(SB), TOP
.l2:
	/* PUSHQ CX */
	/* SUBQ $8, PSP */	/* dummy retaddr */
	MOVQ CX, a0+0(FP)	/* address of exit status? status = nil? */
	MOVQ $8, RARG	/* EXITS */
	SYSCALL		/* TODO syscall for exit */

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
	ADDQ TOP, -16(RSP)
	POP(TOP)
	JMP doloop1

TEXT	rfetch(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOP)
	MOVQ -8(RSP), TOP
	NEXT

TEXT	rpush(SB), 1, $-4	/* ( n -- ) */
	MOVQ TOP,(RSP)
	POP(TOP)
	ADDQ $8,RSP
	NEXT

TEXT	rpop(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOP)
	SUBQ $8, RSP
	MOVQ (RSP), TOP
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
	SUBQ $16, RSP
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

TEXT	forthend(SB), 1, $-4

#include "words.s"

	END
