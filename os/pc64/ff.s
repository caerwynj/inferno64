#include "mem.h"

/*

The bigger goal is to replace the dis vm with ff
ff outputs to screen now.
But, the input needs to be fixed.
make this into a devff like device that reads commands and outputs the result.
replace variable with value (as in open firmware), to avoid exposing addresses

 ff kernel, amd64 9front variant

 Register usage:

 TOS: AX top of stack register
 SP:  SP parameter stack pointer, grows towards lower memory (downwards)
 RP:  BP (= RARG) return stack pointer, grows towards higher memory (upwards)
 AP:  SI address pointer
 W:   DI work register (holds CFA)
 	BX, CX, DX, R8-R15 temporary registers

plan9 assembler puts the first argument in BP (RARG), return value in AX.

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

/*
plan9 assembler puts the first argument in BP (RARG), return value in AX.
	For calling a C function with a parameter:
		Store AX somewhere
		POPQ AX
		PUSHA
		Store ff's SP
		Restore C's SP
		POPA	-- this should not be needed as C is caller save
		MOVQ from somewhere to BP
		-- call the c function
	For calling a C function without a parameter:
		PUSHA
		Store ff's SP
		Restore C's SP
		POPA	-- this should not be needed as C is caller save
		-- call the c function
	For coming back from a C function: -- ignoring the return value
		PUSHA	-- this should not be needed as C is caller save
		Store C's SP
		Restore ff's SP
		POPA
	ignoring the EFLAGS register, for now
	not bothering with maintaining the values of the temporary registers
*/
#define PUSHALL \
	PUSHQ	R13; \
	PUSHQ	R12; \
	PUSHQ	R11; \
	PUSHQ	R10; \
	PUSHQ	R9; \
	PUSHQ	R8; \
	PUSHQ	BP; \
	PUSHQ	DI; \
	PUSHQ	SI; \
	PUSHQ	DX; \
	PUSHQ	CX; \
	PUSHQ	BX; \
	PUSHQ	AX;
#define POPALL \
	POPQ	AX; \
	POPQ	BX; \
	POPQ	CX; \
	POPQ	DX; \
	POPQ	SI; \
	POPQ	DI; \
	POPQ	BP; \
	POPQ	R8; \
	POPQ	R9; \
	POPQ	R10; \
	POPQ	R11; \
	POPQ	R12; \
	POPQ	R13;
#define PUSHREGS \
	PUSHQ	BP; \
	PUSHQ	DI; \
	PUSHQ	SI; \
	PUSHQ	AX;
#define POPREGS \
	POPQ	AX; \
	POPQ	SI; \
	POPQ	DI; \
	POPQ	BP; \

#define FF_TO_C_0 \
	PUSHREGS; \
	MOVQ SP, ffsp<>(SB); \
	MOVQ csp<>(SB), SP; \
	POPREGS;

#define FF_TO_C_1 \
	MOVQ AX, BX; \
	POPQ AX; /* drop AX from the parameter stack */ \
	FF_TO_C_0 \
	MOVQ BX, BP; /* 1st argument in BP == RARG */

/* ( 1st_parameter 2nd_parameter -- ) */
#define FF_TO_C_2 /* for calling a c function with 2 parameters */ \
	MOVQ AX, CX; \
	POPQ AX; \
	FF_TO_C_1 \
	MOVQ CX, 8(SP) \

/* ( 1st_parameter 2nd_parameter 3rd_parameter -- ) */
#define FF_TO_C_3 /* for calling a c function with 3 parameters */ \
	MOVQ AX, DX; \
	POPQ AX; \
	FF_TO_C_2 \
	MOVQ DX, 16(SP) \

/* no arguments when calling ff from C, for now */
#define C_TO_FF \
	PUSHREGS; \
	MOVQ SP, csp<>(SB); \
	MOVQ ffsp<>(SB), SP; \
	POPREGS;

TEXT	ffmain(SB), 1, $-4		/* _main(SB), 1, $-4 without the libc */
	/* The last dictionary entry address is stored in dtop.
	 * The location of dtop is stored in the variable dp.
	 * To get the location of dtop, get the value in the parameter field
	 * (link + name(1+2) + code field address = 24 bytes) of the dp
	 * dictionary entry.
	 */
	PUSHREGS
	MOVQ SP, csp<>(SB); /* store C stack pointer */
	MOVQ $FFEND, SP	/* setting up stack */
	/*
	 * dtop address is stored in the parameter field address(24-32 bytes) of mventry_dp
	 */
	MOVQ mventry_dp+24(SB), BX	/* now, BX = dtop address */
	MOVQ (BX), AX	/* AX = *BX = $LAST = boot word address (defined last, stored at dtop) */
				/* if 6a allows multiple symbols per address, then 
					the above 3 instructions would have been
					MOVQ (($mventry_dp+24(SB))), AX */
	/*
	 * Could do this instead of the calculations below
	 * LEAQ 24(AX), SI
	 */
	ADDQ $16, AX	/* AX += link (8 bytes) + len (1 byte) + minimum for align to 8 bytes */
	XORQ CX, CX
	MOVB 8(BX), CL	/* CL = length of boot name */
	ADDQ CX, AX		/* AX += len */
	ANDQ $~7, AX	/* AX = address of boot's code - 8 bytes */
	LEAQ 8(AX), SI	/* SI = L257 = start of boot code = has docol address there
					 * skipping over docol as we do not need to save the SI
					 * could have done LEAQ 24(AX), SI
					 */

/* lodsl could make this simpler. But, this is more comprehensible
	why not JMP* (DI)?
 */
#define NEXT	MOVQ (SI), DI; \
		ADDQ $8, SI; \
		MOVQ (DI), BX; \
		JMP* BX;

	NEXT

TEXT	ffprint(SB), 1, $-4
	FF_TO_C_2
	CALL screenput(SB)
	C_TO_FF
	NEXT

TEXT	reset(SB), 1, $-4
	MOVQ $FFSTART, BP
	NEXT

TEXT	clear(SB), 1, $-4
	MOVQ $FFEND, SP
	NEXT

TEXT	colon(SB), 1, $-4
	MOVQ SI,(BP)
	ADDQ $8, BP
	LEAQ 8(DI), SI
	NEXT

TEXT	exitcolon(SB), 1, $-4
	SUBQ $8, BP
	MOVQ (BP), SI
	NEXT

TEXT	dodoes(SB), 1, $-4	/* ( -- a ) */
	MOVQ SI,(BP)
	ADDQ $8,BP
	MOVQ 8(DI),SI
	PUSHQ AX
	LEAQ 16(DI), AX
	NEXT

TEXT	jump(SB), 1, $-4	/* ( -- ) */
	MOVQ (SI),SI
	NEXT

/* ( f -- ) cjump address
	if true, skip the address and continue
	else, go to the address */
TEXT	cjump(SB), 1, $-4	/* ( f -- ) */
	MOVQ (SI), BX	/* get the next address */
	ADDQ $8, SI	/* move esi beyond that */
	TESTQ AX, AX
	JNZ .l1		/* if true, move along */
	MOVQ BX, SI	/* if false, go to the above address */
.l1:
	POPQ AX
	NEXT

TEXT	fetch(SB), 1, $-4	/* ( a -- n) */
	MOVQ (AX), AX
	NEXT

TEXT	store(SB), 1, $-4	/* ( n a -- ) */
	POPQ (AX)
	POPQ AX
	NEXT

TEXT	cfetch(SB), 1, $-4	/* ( a -- c ) */
	XORQ BX, BX
	MOVB (AX), BL
	MOVQ BX, AX
	NEXT

TEXT	cstore(SB), 1, $-4	/* ( c a -- ) */
	POPQ BX
	MOVB BL, (AX)
	POPQ AX
	NEXT

TEXT	terminate(SB), 1, $-4	/* ( n -- ) */
	XORQ BX, BX
	TESTQ AX, AX
	JZ .l2
	MOVQ $failtext(SB), BX
.l2:
	/* PUSHQ BX */
	/* SUBQ $8, SP */	/* dummy retaddr */
	MOVQ BX, a0+0(FP)	/* address of exit status? status = nil? */
	MOVQ $8, RARG	/* EXITS */
	SYSCALL		/* syscall for exit */

TEXT	testfsopen(SB), 1, $-4
	PUSHQ SI	/* for some reason, the syscall is changing SI and DI */
	PUSHQ BP
	PUSHQ $0	/* OREAD */
	PUSHQ $name(SB)
	PUSHQ $0	/* dummy retaddr */
	MOVQ $14, RARG	/* open */
	SYSCALL
	ADDQ $24, SP
	POPQ BP
	POPQ SI
	NEXT
	NOP
	NOP
	NOP
	NOP
	NOP

/* man errstr */
TEXT	errstr(SB), 1, $-4
	PUSHQ SI	/* for some reason, the syscall is changing SI and DI */
	PUSHQ BP
	PUSHQ AX

	PUSHQ $128	/* size */
	PUSHQ $errstrbuffer(SB) /* buf */
	PUSHQ $0	/* dummy retaddr */
	MOVQ $41, RARG	/* errstr */
	SYSCALL
	ADDQ $24, SP

	MOVQ $-1, BX	/* -1LL (seek pos) */
	PUSHQ BX	/* offset */
	PUSHQ $128	/* size, could use c's strlen for the exact size */
	PUSHQ $errstrbuffer(SB) /* buf */
	PUSHQ $2	/* assuming that stderr = 2 */
	PUSHQ $0	/* dummy retaddr */
	MOVQ $51, RARG	/* PWRITE */
	SYSCALL
	ADDQ $40, SP

	POPQ AX
	POPQ BP
	POPQ SI
	NEXT
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

TEXT	fsopen(SB), 1, $-4	/* ( cstr flags mode -- fd ) */
	POPQ BX		/* flags */
	POPQ CX		/* name */
	PUSHQ SI	/* for some reason, the syscall is changing SI and DI */
	PUSHQ BP
	PUSHQ AX
	MOVQ $14, RARG	/* OPEN */
	TESTQ $512, BX	/* O_CREAT? */
	JZ .l3
	MOVQ $22, RARG	/* CREATE */
.l3:
	ANDQ $0xF, BX	/* retain only OREAD, OWRITE, ORDWR */
	PUSHQ BX
	PUSHQ CX
	PUSHQ $0	/* dummy retaddr */
	SYSCALL
	ADDQ $32, SP
	POPQ BP
	POPQ SI
	NEXT
	NOP
	NOP
	NOP
	NOP
	NOP

TEXT	fsclose(SB), 1, $-4	/* ( fd -- n ) */
	PUSHQ SI	/* for some reason, the syscall is changing SI and DI */
	PUSHQ BP
	PUSHQ AX	/* fd */
	PUSHQ $0	/* dummy retaddr */
	MOVQ $4, RARG	/* CLOSE */
	SYSCALL
	ADDQ $16, SP	/* removing the pushed parameters */
	POPQ BP
	POPQ SI
	NEXT
	NOP
	NOP
	NOP
	NOP
	NOP

TEXT	fsread(SB), 1, $-4	/* ( a n fd -- n2 ) */
	POPQ CX		/* size */
	POPQ DX		/* buf */
	PUSHQ SI	/* for some reason, the syscall is changing SI and DI */
	PUSHQ BP
	MOVQ $-1, BX	/* -1LL (seek pos) */
	PUSHQ BX	/* offset */
	PUSHQ CX	/* size */
	PUSHQ DX	/* buf */
	PUSHQ AX	/* fd */
	PUSHQ $0	/* dummy retaddr */
	MOVQ $50, RARG	/* PREAD */
	SYSCALL		/* return value in AX */
	ADDQ $40, SP
	POPQ BP		/* restore return stack pointer */
	POPQ SI
	NEXT
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

TEXT	fswrite(SB), 1, $-4	/* ( a n fd -- n2 ) */
	POPQ CX		/* size */
	POPQ DX		/* buf */
	PUSHQ SI	/* for some reason, the syscall is changing SI and DI */
	PUSHQ BP
	MOVQ $-1, BX	/* -1LL (seek pos) */
	PUSHQ BX	/* offset */
	PUSHQ CX	/* size */
	PUSHQ DX	/* buf */
	PUSHQ AX	/* fd */
	PUSHQ $0	/* dummy retaddr */
	MOVQ $51, RARG	/* PWRITE */
	SYSCALL
	ADDQ $40, SP
	POPQ BP
	POPQ SI
	NEXT
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

TEXT	fsseek(SB), 1, $-4	/* ( pos fd -- n ) */
	POPQ BX		/* offset */
	PUSHQ SI	/* for some reason, the syscall is changing SI and DI */
	PUSHQ BP
	XORQ DX, DX	/* type 0 */
	PUSHQ DX	/* type 0 */
	PUSHQ BX	/* offset */
	PUSHQ AX  	/* fd */
	PUSHQ $0	/* dummy retaddr */
	MOVQ $39, RARG	/* SEEK */
	SYSCALL
	ADDQ $32, SP	/* remove the pushed parameters */
	POPQ BP
	POPQ SI
	NEXT

TEXT	mmap(SB), 1, $-4	/* ( a1 -- a2 ) */
	MOVQ $-1, AX	/* unimplemented */

TEXT	variable(SB), 1, $-4	/* ( -- a ) */
	PUSHQ AX
	LEAQ 8(DI), AX
	NEXT

TEXT	constant(SB), 1, $-4	/* ( -- n ) */
	PUSHQ AX
	MOVQ 8(DI), AX
	NEXT

TEXT	literal(SB), 1, $-4	/* ( -- n ) */
	PUSHQ AX
	MOVQ (SI), AX
	ADDQ $8, SI
	NEXT

TEXT	sliteral(SB), 1, $-4	/* ( -- a n ) */
	PUSHQ AX
	XORQ AX,AX
	MOVB (SI), AL
	INCQ SI
	PUSHQ SI
	ADDQ AX, SI
	ADDQ $7, SI
	ANDQ $~7, SI
	NEXT

/* puts the top 2 entries of the data stack in the return stack */
TEXT	doinit(SB), 1, $-4	/* ( hi lo -- ) */
	MOVQ AX, (BP)
	POPQ AX
	MOVQ AX, 8(BP)
	POPQ AX
	ADDQ $16, BP
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
	INCQ -16(BP)
doloop1:
	MOVQ -16(BP), BX
	CMPQ BX, -8(BP)
	JGE .l4
	MOVQ (SI), SI
	NEXT
.l4:
	SUBQ $16, BP
	ADDQ $8, SI
	NEXT

TEXT	doploop(SB), 1, $-4	/* ( n -- ) */
	ADDQ AX, -16(BP)
	POPQ AX
	JMP doloop1

TEXT	rfetch(SB), 1, $-4	/* ( -- n ) */
	PUSHQ AX
	MOVQ -8(BP), AX
	NEXT

TEXT	rpush(SB), 1, $-4	/* ( n -- ) */
	MOVQ AX,(BP)
	POPQ AX
	ADDQ $8,BP
	NEXT

TEXT	rpop(SB), 1, $-4	/* ( -- n ) */
	PUSHQ AX
	SUBQ $8, BP
	MOVQ (BP), AX
	NEXT

TEXT	i(SB), 1, $-4	/* ( -- n ) */
	PUSHQ AX
	MOVQ -16(BP), AX
	NEXT

TEXT	j(SB), 1, $-4	/* ( -- n ) */
	PUSHQ AX
	MOVQ -32(BP), AX
	NEXT

TEXT	plus(SB), 1, $-4	/* ( n1 n2 -- n ) */
	POPQ BX
	ADDQ BX, AX
	NEXT  

TEXT	minus(SB), 1, $-4	/* ( n1 n2 -- n ) */
	POPQ BX
	SUBQ AX, BX
	MOVQ BX, AX
	NEXT

TEXT	multiply(SB), 1, $-4	/* ( n1 n2 -- n ) */
	POPQ BX
	IMULQ BX
	NEXT

TEXT	slashmod(SB), 1, $-4	/* ( n1 n2 -- n3 n4 ) */
	MOVQ AX, BX
	MOVQ (SP), AX
	CDQ
	IDIVQ BX
	MOVQ AX, (SP)
	NEXT

TEXT	uslashmod(SB), 1, $-4	/* ( u1 u2 -- u3 u4 ) */
	MOVQ AX, BX
	MOVQ (SP), AX
	XORQ DX, DX
	DIVQ BX
	MOVQ DX, (SP)
	NEXT

TEXT	binand(SB), 1, $-4	/* ( n1 n2 -- n ) */
	ANDQ (SP), AX
	ADDQ $8, SP
	NEXT

TEXT	binor(SB), 1, $-4	/* ( n1 n2 -- n ) */
	ORQ (SP), AX
	ADDQ $8, SP
	NEXT

TEXT	binxor(SB), 1, $-4	/* ( n1 n2 -- n ) */
	XORQ (SP), AX
	ADDQ $8, SP
	NEXT

TEXT	xswap(SB), 1, $-4	/* ( x y -- y x ) */
	XCHGQ AX, (SP)
	NEXT

TEXT	drop(SB), 1, $-4	/* ( x -- ) */
	POPQ AX
	NEXT

TEXT	dup(SB), 1, $-4	/* ( x -- x x ) */
	PUSHQ AX
	NEXT

TEXT	over(SB), 1, $-4	/* ( x y -- x y x ) */
	PUSHQ AX
	MOVQ 8(SP), AX
	NEXT

TEXT	equal(SB), 1, $-4	/* ( x y -- f ) */
	POPQ BX
	CMPQ BX, AX
	JEQ .true
	XORQ AX, AX
	NEXT
TEXT	true(SB), 1, $-4
.true:
	MOVQ $-1, AX
	NEXT
	
TEXT	greater(SB), 1, $-4	/* ( x y -- f ) */
	POPQ BX
	CMPQ BX, AX
	JGT .true
	XORQ AX, AX
	NEXT

/* if x < y then y - x > 0, no sign flag
	intel manual says destination operand - source operand
	but, 9front assemblers seem to work differently
	compare x and y == CMP x, y
 */
TEXT	less(SB), 1, $-4	/* ( x y -- f ) */
	POPQ BX
	CMPQ BX, AX
	JLT .true
	XORQ AX, AX
	NEXT

TEXT	stackptr(SB), 1, $-4	/* ( -- a ) does not include TOS! */
	PUSHQ AX
	MOVQ SP, AX
	NEXT

TEXT	lshift(SB), 1, $-4	/* ( n1 n2 -- n ) */
	MOVQ AX, CX
	POPQ AX
	SHLQ CL, AX
	NEXT
	
TEXT	rshift(SB), 1, $-4	/* ( n1 n2 -- n ) */
	MOVQ AX, CX
	POPQ AX
	SHRQ CL, AX
	NEXT

TEXT	rshifta(SB), 1, $-4	/* ( n1 n2 -- n ) */
	MOVQ AX, CX
	POPQ AX
	SARQ CL, AX
	NEXT

TEXT	execute(SB), 1, $-4	/* ( ... a -- ... ) */
	MOVQ AX, DI
	POPQ AX
	MOVQ (DI), BX
	JMP BX

TEXT	deferred(SB), 1, $-4
	MOVQ 8(DI), DI
	MOVQ (DI), BX
	JMP BX

TEXT	unloop(SB), 1, $-4
	SUBQ $16, BP
	NEXT

TEXT	cmove(SB), 1, $-4	/* ( a1 a2 n -- ) */
	MOVQ AX, CX
	POPQ DI
	MOVQ SI, BX
	POPQ SI
	REP; MOVSB
	MOVQ BX, SI
	POPQ AX
	NEXT

TEXT	cmoveb(SB), 1, $-4	/* ( a1 a2 n -- ) */
	MOVQ AX, CX
	POPQ DI
	DECQ AX
	ADDQ AX, DI
	MOVQ SI, BX
	POPQ SI
	ADDQ AX, SI
	STD
	REP; MOVSB
	CLD
	MOVQ BX, SI
	POPQ AX
	NEXT

TEXT	cas(SB), 1, $-4	/* ( a old new -- f ) */
	MOVQ AX, CX	/* new */
	POPQ AX	/* old */
	POPQ BX	/* addr */
	LOCK; CMPXCHGQ CX, (BX)
	JE .true
	XORQ AX, AX
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
GLOBL	errstrbuffer(SB), $128	/* matches ERRMAX of libc.h */

DATA	tibuffer(SB)/1, $0
GLOBL	tibuffer(SB), $1024
DATA	wordbuffer(SB)/1, $0
GLOBL	wordbuffer(SB), $256
/* TODO there should not be a heap limit, get rid of this */
/*
DATA	heap(SB)/1, $0
GLOBL	heap(SB), $HEAP_SIZE
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
