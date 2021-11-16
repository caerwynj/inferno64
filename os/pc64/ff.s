#include "mem.h"

/*

The bigger goal is to replace the dis vm with ff
ff outputs to screen now.
But, the input needs to be fixed.
make this into a devff like device that reads commands and outputs the result.
replace variable with value (as in open firmware), to avoid exposing addresses

 ff kernel, amd64 9front variant

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
	CX, SI, DI, R11-R15 temporary registers

coding standard
: <name> (S input-stack --- output-stack) (R --- )
	(G descriptive glossary text)
	f1 f2  ( interim stack picture) \ programmers explanatory comment
		.. fn ;

Memory map:
Return stack 4096 bytes at FFSTART
	|
	|
	v (grows downwards)
Others 4096 bytes
	system variables
	word buffer
	tib, text input buffer
Parameter stack 4096 bytes at FFEND-4096
	^ (grows upwards)
	|
	|
SSTACK_END = FFEND
*/

#define SSTACK_SIZE 4096
#define RSTACK_SIZE 4096
#define	LAST $centry_c_boot(SB) /* last defined word, should generate this */
#define	SSTACK_END FFEND

/* putting this above the asm code as the v_dp define is needed by _main */
/*	m_ for primitive/macro word cfa
	mc_ for primtive/macro word constants
	c_ for colon word cfa
	ci_ for colon immediate word cfa
	v_ for colon variable word cfa
 */
#include "primitives.s"

#define PUSHALL \
	PUSHQ	R13; \
	PUSHQ	R12; \
	PUSHQ	R11; \
	PUSHQ	R10; \
	PUSHQ	R9; \
	PUSHQ	R8; \
	PUSHQ	R8; \
	PUSHQ	R10; \
	PUSHQ	R9; \
	PUSHQ	DX; \
	PUSHQ	CX; \
	PUSHQ	BX; \
	PUSHQ	TOS;
#define POPALL \
	POPQ	TOS; \
	POPQ	BX; \
	POPQ	CX; \
	POPQ	DX; \
	POPQ	R9; \
	POPQ	R10; \
	POPQ	R8; \
	POPQ	R8; \
	POPQ	R9; \
	POPQ	R10; \
	POPQ	R11; \
	POPQ	R12; \
	POPQ	R13;
#define PUSHREGS \
	PUSHQ	R8; \
	PUSHQ	R10; \
	PUSHQ	R9; \
	PUSHQ	TOS;
#define POPREGS \
	POPQ	TOS; \
	POPQ	R9; \
	POPQ	R10; \
	POPQ	R8;

#define FF_TO_C_0 \
	PUSHREGS; \
	MOVQ DX, ffsp<>(SB); \
	MOVQ csp<>(SB), DX; \
	POPREGS;

#define FF_TO_C_1 \
	MOVQ TOS, BX; \
	POPQ TOS; /* drop TOS from the parameter stack */ \
	FF_TO_C_0 \
	MOVQ BX, R8; /* 1st argument in R8 == RARG */

/* ( 1st_parameter 2nd_parameter -- ) */
#define FF_TO_C_2 /* for calling a c function with 2 parameters */ \
	MOVQ TOS, CX; \
	POPQ TOS; \
	FF_TO_C_1 \
	MOVQ CX, 8(DX) \

/* ( 1st_parameter 2nd_parameter 3rd_parameter -- ) */
#define FF_TO_C_3 /* for calling a c function with 3 parameters */ \
	MOVQ TOS, DX; \
	POPQ TOS; \
	FF_TO_C_2 \
	MOVQ DX, 16(DX) \

/* no arguments when calling ff from C, for now */
#define C_TO_FF \
	PUSHREGS; \
	MOVQ DX, csp<>(SB); \
	MOVQ ffsp<>(SB), DX; \
	POPREGS;

TEXT	ffmain(SB), 1, $-4		/* _main(SB), 1, $-4 without the libc */
	/* The last dictionary entry address is stored in dtop.
	 * The location of dtop is stored in the variable dp.
	 * To get the location of dtop, get the value in the parameter field
	 * (link + name(1+2) + code field address = 24 bytes) of the dp
	 * dictionary entry.
	 */
	MOVQ $FFEND, PSP	/* setting up stack */
	/*
	 * dtop address is stored in the parameter field address(24-32 bytes) of mventry_dp
	 */
	MOVQ mventry_dp+24(SB), SI	/* now, SI = dtop address */
	MOVQ (SI), TOS	/* TOS = *CX = $LAST = boot word address (defined last, stored at dtop) */
				/* if 6a allows multiple symbols per address, then 
					the above 3 instructions would have been
					MOVQ (($mventry_dp+24(SB))), TOS */
	/*
	 * Could do this instead of the calculations below
	 * LEAQ 24(TOS), IP
	 */
	ADDQ $16, TOS	/* TOS += link (8 bytes) + len (1 byte) + minimum for align to 8 bytes */
	XORQ CX, CX
	MOVB 8(SI), CL	/* CL = length of boot name */
	ADDQ CX, TOS		/* TOS += len */
	ANDQ $~7, TOS	/* TOS = address of boot's code - 8 bytes */
	LEAQ 8(TOS), IP	/* IP = L257 = start of boot code = has docol address there
					 * skipping over docol as we do not need to save the IP
					 */

/* lodsl could make this simpler. But, this is more comprehensible
	why not JMP* (W)?
 */
#define NEXT	MOVQ (IP), W; /* W = Address next to the DOCOL of boot */ \
		ADDQ $8, IP; /* move IP further = DOCOL address + 16 */ \
		MOVQ (W), TOS; /* TOS = code field address of the 1st instruction after DOCOL of boot */ \
		JMP* TOS; /* Start executing that code field address */
/*
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
		MOVQ (W), TOS;	/* TOS = docol, Get the address in the address in IP = code field address */ \
		ADDQ $8, IP; 	/* move IP further, IP = 16 */ \
		JMP* TOS; /* Start executing at docol address, JMP* = jump to a non-relative address */

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
	PUSH(TOS)
	LEAQ 16(W), TOS
	NEXT

TEXT	jump(SB), 1, $-4	/* ( -- ) */
	MOVQ (IP),IP
	NEXT

/* ( f -- ) cjump address
	if true, skip the address and continue
	else, go to the address */
TEXT	cjump(SB), 1, $-4	/* ( f -- ) */
	MOVQ (IP), TOS	/* get the next address */
	ADDQ $8, IP	/* move esi beyond that */
	TESTQ TOS, TOS
	JNZ .l1		/* if true, move along */
	MOVQ TOS, IP	/* if false, go to the above address */
.l1:
	POP(TOS
	NEXT

/* TODO change to allow only fetches from a certain memory range */
TEXT	fetch(SB), 1, $-4	/* ( a -- n) */
	MOVQ (TOS), TOS
	NEXT

/* TODO change to allow stores to a certain memory range only */
TEXT	store(SB), 1, $-4	/* ( n a -- ) */
	POP(CX)
	MOVQ CX, (TOS)
	POP(TOS)
	NEXT

TEXT	cfetch(SB), 1, $-4	/* ( a -- c ) */
	XORQ CX, CX
	MOVB (TOS), CL
	POP(TOS)
	NEXT

TEXT	cstore(SB), 1, $-4	/* ( c a -- ) */
	POP(CX)
	MOVB CL, (TOS)
	POP(TOS)
	NEXT

TEXT	terminate(SB), 1, $-4	/* ( n -- ) */
	XORQ CX, CX
	TESTQ TOS, TOS
	JZ .l2
	MOVQ $failtext(SB), TOS
.l2:
	/* PUSHQ CX */
	/* SUBQ $8, PSP */	/* dummy retaddr */
	MOVQ CX, a0+0(FP)	/* address of exit status? status = nil? */
	MOVQ $8, RARG	/* EXITS */
	SYSCALL		/* TODO syscall for exit */

TEXT	testfsopen(SB), 1, $-4
	PUSHQ SI	/* for some reason, the syscall is changing IP and W */
	PUSHQ BP
	PUSHQ $0	/* OREAD */
	PUSHQ $name(SB)
	PUSHQ $0	/* dummy retaddr */
	MOVQ $14, RARG	/* open */
	SYSCALL
	ADDQ $24, PSP
	POPQ RSP
	POPQ IP
	NEXT
	NOP
	NOP
	NOP
	NOP
	NOP

#include "bindings.s"

TEXT	mmap(SB), 1, $-4	/* ( a1 -- a2 ) */
	MOVQ $-1, TOS	/* unimplemented */

TEXT	variable(SB), 1, $-4	/* ( -- a ) */
	PUSH(TOS)
	LEAQ 8(W), TOS
	NEXT

TEXT	constant(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOS)
	MOVQ 8(W), TOS
	NEXT

TEXT	literal(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOS)
	MOVQ (IP), TOS
	ADDQ $8, IP
	NEXT

TEXT	sliteral(SB), 1, $-4	/* ( -- a n ) */
	PUSH(TOS)
	XORQ TOS,TOS
	MOVB (IP), BL
	INCQ IP
	PUSH(IP)
	ADDQ TOS, IP
	ADDQ $7, IP
	ANDQ $~7, IP
	NEXT

/* puts the top 2 entries of the data stack in the return stack */
TEXT	doinit(SB), 1, $-4	/* ( hi lo -- ) */
	MOVQ TOS, (RSP)
	POP(TOS)
	MOVQ TOS, 8(RSP)
	POP(TOS)
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
	ADDQ TOS, -16(RSP)
	POP(TOS)
	JMP doloop1

TEXT	rfetch(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOS)
	MOVQ -8(RSP), TOS
	NEXT

TEXT	rpush(SB), 1, $-4	/* ( n -- ) */
	MOVQ TOS,(RSP)
	POP(TOS)
	ADDQ $8,RSP
	NEXT

TEXT	rpop(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOS)
	SUBQ $8, RSP
	MOVQ (RSP), TOS
	NEXT

TEXT	i(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOS)
	MOVQ -16(RSP), TOS
	NEXT

TEXT	j(SB), 1, $-4	/* ( -- n ) */
	PUSH(TOS)
	MOVQ -32(RSP), TOS
	NEXT

TEXT	plus(SB), 1, $-4	/* ( n1 n2 -- n ) */
	POP(CX)
	ADDQ CX, TOS
	NEXT  

TEXT	minus(SB), 1, $-4	/* ( n1 n2 -- n ) */
	MOVQ TOS, CX
	POP(TOS)
	SUBQ CX, TOS
	NEXT

TEXT	multiply(SB), 1, $-4	/* ( n1 n2 -- n1*n2 ) */
	POP(CX)
	IMULQ CX,TOS
	NEXT

TEXT	slashmod(SB), 1, $-4	/* ( n1 n2 -- remainder quotient ) n1/n2 */
	MOVQ (PSP), CX /* CX = n1 */
	PUSHQ DX /* DX == PSP, store DX and AX as they are used by CDQ and IDIV */
	PUSHQ AX
	XORQ DX, DX /* DX = 0 */
	MOVQ CX, AX /* AX = n1 */
	CDQ 		/* RAX -> RDX:RAX sign extension */
	IDIVQ TOS	/* RDX:RAX / TOS => Quotient in RAX, Remainder in RDX */
	MOVQ DX, CX	/* CX = remainder */
	MOVQ AX, TOS /* TOS = quotient */
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
	IDIVQ TOS	/* RDX:RAX / TOS => Quotient in RAX, Remainder in RDX */
	MOVQ DX, CX	/* CX = remainder */
	MOVQ AX, TOS /* TOS = quotient */
	POPQ AX
	POPQ DX
	MOVQ CX, (PSP) /* -- uremainder uquotient */
	NEXT

	MOVQ TOS, TOS
	MOVQ (PSP), TOS
	XORQ PSP, PSP
	DIVQ TOS
	MOVQ PSP, (PSP)
	NEXT

TEXT	binand(SB), 1, $-4	/* ( n1 n2 -- n ) */
	ANDQ (PSP), TOS
	ADDQ $8, PSP
	NEXT

TEXT	binor(SB), 1, $-4	/* ( n1 n2 -- n ) */
	ORQ (PSP), TOS
	ADDQ $8, PSP
	NEXT

TEXT	binxor(SB), 1, $-4	/* ( n1 n2 -- n ) */
	XORQ (PSP), TOS
	ADDQ $8, PSP
	NEXT

TEXT	xswap(SB), 1, $-4	/* ( x y -- y x ) */
	XCHGQ TOS, (PSP)
	NEXT

TEXT	drop(SB), 1, $-4	/* ( x -- ) */
	POP(TOS)
	NEXT

TEXT	dup(SB), 1, $-4	/* ( x -- x x ) */
	PUSH(TOS)
	NEXT

TEXT	over(SB), 1, $-4	/* ( x y -- x y x ) */
	PUSH(TOS)
	MOVQ 8(PSP), TOS
	NEXT

TEXT	equal(SB), 1, $-4	/* ( x y -- f ) */
	POP(CX)
	CMPQ CX, TOS
	JEQ .true
	XORQ TOS, TOS
	NEXT
TEXT	true(SB), 1, $-4
.true:
	MOVQ $-1, TOS
	NEXT
	
TEXT	greater(SB), 1, $-4	/* ( x y -- f ) */
	POP(CX)
	CMPQ CX, TOS
	JGT .true
	XORQ TOS, TOS
	NEXT

/* if x < y then y - x > 0, no sign flag
	intel manual says destination operand - source operand
	but, 9front assemblers seem to work differently
	compare x and y == CMP x, y
 */
TEXT	less(SB), 1, $-4	/* ( x y -- f ) */
	POP(CX)
	CMPQ CX, TOS
	JLT .true
	XORQ TOS, TOS
	NEXT

TEXT	stackptr(SB), 1, $-4	/* ( -- a ) does not include TOS! */
	PUSH(TOS)
	MOVQ PSP, TOS
	NEXT

TEXT	lshift(SB), 1, $-4	/* ( n1 n2 -- n ) */
	MOVQ TOS, CX
	POP(TOS)
	SHLQ CL, TOS
	NEXT
	
TEXT	rshift(SB), 1, $-4	/* ( n1 n2 -- n ) */
	MOVQ TOS, CX
	POP(TOS)
	SHRQ CL, TOS
	NEXT

TEXT	rshifta(SB), 1, $-4	/* ( n1 n2 -- n ) */
	MOVQ TOS, CX
	POP(TOS)
	SARQ CL, TOS
	NEXT

TEXT	execute(SB), 1, $-4	/* ( ... a -- ... ) */
	MOVQ TOS, W
	POP(TOS)
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
	MOVQ TOS, CX
	POP(W)
	MOVQ IP, CX
	POP(IP)
	REP; MOVSB
	MOVQ CX, IP
	POP(TOS)
	NEXT

TEXT	cmoveb(SB), 1, $-4	/* ( a1 a2 n -- ) */
	MOVQ TOS, CX
	POP(W)
	DECQ TOS
	ADDQ TOS, W
	MOVQ IP, CX
	POP(IP)
	ADDQ TOS, IP
	STD
	REP; MOVSB
	CLD
	MOVQ CX, IP
	POP(TOS)
	NEXT

TEXT	cas(SB), 1, $-4	/* ( a old new -- f ) */
	MOVQ TOS, DI	/* new */
	POP(TOS)	/* old */
	POP(SI)	/* addr */
	LOCK; CMPXCHGQ DI, (SI)
	JE .true
	XORQ TOS, TOS
	/* pause -- no equivalent in 6a ? */
	NEXT

TEXT	ffend(SB), 1, $-4

#include "words.s"

DATA	failtext(SB)/6, $"error\z"
GLOBL	failtext(SB), $6

DATA	name(SB)/8, $"/tmp/tes"
DATA	name+8(SB)/6, $"t.txt\z"
GLOBL	name(SB), $14

DATA	errstrbuffer(SB)/1, $0
GLOBL	errstrbuffer(SB), $128	/* matches ERRMTOS of libc.h */

DATA	tibuffer(SB)/1, $0
GLOBL	tibuffer(SB), $1024
DATA	wordbuffer(SB)/1, $0
GLOBL	wordbuffer(SB), $256
/* TODO there should not be a heap limit, get rid of this */
/*
DATA	heap(SB)/1, $0
GLOBL	heap(SB), $HEIP_IPZE
*/


DATA	dtop(SB)/8, LAST
GLOBL	dtop(SB), $8
/* 0's until heap allocated */
DATA	htop(SB)/8, $0
GLOBL	htop(SB), $8
DATA	heapend(SB)/8, $0
GLOBL	heapend(SB), $8

GLOBL	ffsp<>(SB), $8
GLOBL	csp<>(SB), $8

	END
