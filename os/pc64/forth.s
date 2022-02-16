#include "mem.h"

/*

Goal is to replace the dis vm with forth

 forth kernel, amd64 9front variant

 Register usage:

	Original usage
 TOS: AX top of stack register
 SP:  SP parameter stack pointer, grows towards lower memory (downwards)
 RP:  BP (= RARG) return stack pointer, grows towards higher memory (upwards)
 AP:  SI address pointer
 W:   DI work register (holds CFA)
 	BX, CX, DX, R8-R15 temporary registers

plan9 amd64 assembler puts the first argument in BP (RARG), return value in AX.

	Changed to
 Leaving AX, SP, BP (RARG), R14 (up Proc), R15 (m Mach) alone to not mess with the C environment

 TOP: BX top of stack register
 PSP: DX parameter stack pointer, grows towards lower memory (downwards)
 RSP: R8 return stack pointer, grows towards lower memory (downwards)
 IP:  R9 interpretive pointer
 W:   R10 current word pointer (holds CFA). F83 uses SI (lodsl in NEXT). As C uses AX, not bothering with lodsl.
 UP:  R11 register holding the start of the memory for this process
 UPE: R12 register holding the end of the memory for this process
	CX, SI, DI, R13 temporary registers

coding standard
: <name> (S input-stack --- output-stack) (R --- )
	(G descriptive glossary text)
	f1 f2  ( interim stack picture) \ programmers explanatory comment
		.. fn ;

Heap memory map: uses n+ pages at the start
		not bothering with increase by *2 when filled up, for now
	check mem.h for the memory map
	Keeps static code/data at the start and variable data to the end
		For performance reasons, if you are writing to a cache line with code in it,
		I think there is a performance penalty. Because x86 has a separate instruction
		and data cache in L1, but is kind enough to abstract this away. So you can write
		over executing code, but it causes some synchronisation that might be expensive.
		And I would expect this to be done on a cache-line granularity. So you could
		end up with code running slower just because it happens to be defined after
		space for some data that's in active use... not good - veltas on #forth

high memory
	word buffer 512 bytes
	error string buffer 128 bytes
		latest dictionary entry, Dtop
			need this as the system definitions and
			user definitions are not continuous
		dictionary pointer, Dp, Dtop, Args
		forth stack pointer, forthpsp
forth variables
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
Pad is 256 bytes from here
	^ (grows upwards)
	|
	|
User dictionary	upto n pages from the start
UPE: memory end
UP: memory start
	forth constants
low memory

TODO Move variable space out of the dictionary from #forth
11:31 < joe9> In x86 you want to keep the code in a different section than variables -- why?
11:31 < joe9> in my port, I am keeping them together.
11:32 < joe9> it gets messy with different sections.
*/

#define TOP BX /* top of stack register */
#define PSP DX /* parameter stack pointer, grows towards lower memory (downwards) */
#define RSP R8 /* return stack pointer, grows towards lower memory (downwards) */
#define IP  R9 /* interpretive pointer */
#define W   R10/* current word pointer (holds CFA). F83 uses SI (lodsl in NEXT). As C uses AX, not using lodsl */
#define UP	R11/* start of user proram memory */
#define UPE	R12/* end of user program memory */

#define PSTACK_SIZE BY2PG
#define RSTACK_SIZE BY2PG

/* putting this above the asm code as the v_dp define is needed by _main */
/*
	M_ for primitive/macro word cfa
	MC_ for primtive/macro word constants
	C_ for colon word cfa
	CI_ for colon immediate word cfa
	V_ for colon variable word cfa

	CONSTANTS - capital letters
	Variables - initial capital case, at runtime puts the address of the location on the data stack
	words - lower case
	'name - address of name

	(word) - compiler or runtime helper words
		(sliteral) puts the following counted string on the stack
		(literal) puts the following cell on the stack
		(constant), (:)
	[word] - uses the next instruction as the parameter
		such as:
			[char] a - does something with a. a's location is in IP
			char - does something with the next input word

	stack notations
		cs counted-string
		'text address of text
		n number
 */

/* HEAPSTART, HEAPEND, HERE, DTOP, VHERE are loaded by the caller */
TEXT	forthmain(SB), 1, $-4		/* no stack storage required */

	/* Argument has the start of heap */
	MOVQ RARG, UP		/* start of heap memory */

	MOVQ RARG, UPE
	ADDQ $FORTHUPE, UPE
	MOVQ (UPE), UPE		/* HEAPEND populated by the caller in FORTHUPE */

	MOVQ UP, RSP
	ADDQ $RSTACK, RSP	/* return stack pointer, reset */

	MOVQ UP, PSP
	ADDQ $PSTACK, PSP	/* parameter stack pointer - stack setup, clear */

	/* execute boot */
	MOVQ UP, CX
	ADDQ $DTOP, CX	/* address of last defined word (c_boot) is at DTOP */
	MOVQ (CX), IP	/* IP = address of c_boot */
	ADDQ $24, IP	/* to get to the parameter field address of boot word */

	/* clear TOP */
	XORQ TOP, TOP

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
	ADDQ $RSTACK, RSP
	NEXT

TEXT	clear(SB), 1, $-4
	MOVQ UP, PSP
	ADDQ $PSTACK, PSP
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

TEXT	deferred(SB), 1, $-4
	MOVQ 8(W), W
	MOVQ (W), CX
	JMP* CX

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

#define CHECKADDRESS \
	CMPQ TOP, UPE; \
	JGT aboveupe;	/* a > UPE */\
	CMPQ TOP, UP;\
	JLT belowup;	/* a < UP */

TEXT	execute(SB), 1, $-4	/* ( ... a -- ... ) */
	CHECKADDRESS
	MOVQ TOP, W
	POP(TOP)
	MOVQ (W), CX
	JMP* CX

TEXT	fetch(SB), 1, $-4	/* ( a -- n) */
	CHECKADDRESS
	MOVQ (TOP), TOP
	NEXT

TEXT	store(SB), 1, $-4	/* ( n a -- ) */
	CHECKADDRESS
	POP(CX)
	MOVQ CX, (TOP)
	POP(TOP)
	NEXT

TEXT	cfetch(SB), 1, $-4	/* ( a -- c ) */
	CHECKADDRESS
	XORQ CX, CX
	MOVB (TOP), CL
	MOVQ CX, TOP
	NEXT

TEXT	cstore(SB), 1, $-4	/* ( c a -- ) */
	CHECKADDRESS
	POP(CX)
	MOVB CL, (TOP)
	POP(TOP)
	NEXT

TEXT	terminate(SB), 1, $-4	/* ( n -- ) */
_fthterminate:
	MOVQ TOP, AX
	RET

TEXT	fthdump(SB), 1, $8	/* ( n -- ) */
	INT $0
	RET

#include "bindings.s"

TEXT	mmap(SB), 1, $-4	/* ( a1 -- a2 ) */
	MOVQ $-1, TOP	/* unimplemented */

/*
 * Traditionally, the pfa of variable has the value.
 * But, to keep the populated dictionary read-only, we
 * moved the variables to the variables area.
 * Now, pfa holds the address where the value is stored
 * instead of the actual value.
 * With this change, there is no difference in how the
 * costant cfa and variable cfa work. They both load the
 * value in the pfa to the top of the stack. The only
 * difference is that the value in the pfa is an address
 * for the variable and the actual value for the constant.
 */
TEXT	variable(SB), 1, $-4	/* ( -- a ) */
	PUSH(TOP)
	MOVQ 8(W), TOP	/*	LEAQ 8(W), TOP */
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

/* ( -- a n) and set IP = aligned(IP+count) */
TEXT	sliteral(SB), 1, $-4	/* ( -- a n ) */
	PUSH(TOP)
	XORQ TOP,TOP
	MOVB (IP), BL	/* move the count from (IP) to BL (lower byte of TOP) */
	INCQ IP
	PUSH(IP)		/* push IP onto the stack */
	ADDQ TOP, IP
	ADDQ $7, IP
	ANDQ $~7, IP	/* set IP += count, then align the IP to the next cell */
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

TEXT	unloop(SB), 1, $-4
	ADDQ $16, RSP
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

/* TODO
	*\/	for the quotient ( *\/ nip )
	*\/MOD for the remainder and quotient
 */
TEXT	multiplyslashmod(SB), 1, $-4	/* ( n1 n2 n3 -- remainder((n1*n2)/n3) quotient((n1*n2)/n3) */
	POP(CX)
	IMULQ CX,TOP
	NEXT

/*
	/	for only the quotient
	/mod for the remainder and quotient
	mod for the remainder
 */
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

/*
	Return  the address of the top of the stack, just before sp@ was executed.
	1 2 S0 s@ - hex cr . . . cr gives 18 2 1, so S@ would have been pointing at S0
	18 in hex translates to 3 64-bit cells
 */
TEXT	stackptr(SB), 1, $-4	/* ( -- a ) does not include TOP! */
	MOVQ PSP, CX
	PUSH(TOP)
	MOVQ CX, TOP
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

/* moves n bytes from a1 to a2 */
TEXT	cmove(SB), 1, $-4	/* ( a1 a2 n -- ) */
	PUSH(TOP)
	MOVQ 8(PSP), CX		/* a2 */
	MOVQ CX, TOP
	CALL validateaddress(SB)	/* a1 a2 n a2 -- a1 a2 n */

	PUSH(TOP)
	MOVQ 16(PSP), CX	/* a1 */
	MOVQ CX, TOP
	CALL validateaddress(SB)	/* a1 a2 n a1 -- a1 a2 n */

	POP(DI)
	POP(SI)
	MOVQ TOP, CX
	POP(TOP)			/* SI = a1, DI = a2, CX = n */
	REP; MOVSB
	NEXT

/* moves n bytes from a1+n-1 to a2+n-1 until n = 0 */
TEXT	cmoveb(SB), 1, $-4	/* ( a1 a2 n -- ) */
	PUSH(TOP)
	MOVQ 8(PSP), CX		/* a2 */
	MOVQ CX, TOP
	CALL validateaddress(SB)	/* a1 a2 n a2 -- a1 a2 n */

	PUSH(TOP)
	MOVQ 16(PSP), CX	/* a1 */
	MOVQ CX, TOP
	CALL validateaddress(SB)	/* a1 a2 n a1 -- a1 a2 n */

	MOVQ TOP, CX
	DECQ TOP		/* TOP = n-1, CX = n */
	POP(DI)
	ADDQ TOP, DI
	POP(SI)
	ADDQ TOP, SI
	POP(TOP)		/* CX = n, SI = a1+n-1, DI = a2+n-1 */
	STD
	REP; MOVSB
	CLD
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

/*
 * variables used by the core words. Using variable code word instead of known locations.
#define	VARIABLE(name, location)	TEXT	name(SB), 1, $-4 ;\
	PUSH(TOP); \
	MOVQ UP, TOP ;\
	ADDQ location, TOP ;\
	NEXT;
VARIABLE(Tib, $TIB)
 */

/*
 * routines called by forth asm macros or bindings
 */

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
TEXT	inum(SB), 1, $-4
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
	argument 2 = address
	return value in TOP
	-1			0			1
	if UP < address && address+n < UPE
		return 0	within range
	else if address < UP
		return -1	below UP
	else if UPE < address+n
		return 1	above UP
 */
TEXT	isbufinum(SB), 1, $-4 /* is buffer in user memory? ( a n -- -1|0|1 ) */
	CMPQ TOP, $0 	/* negative n? */
	JLT belowup		/* TODO have an appropriate error message */
	ADDQ (PSP), TOP	/* TOP = a+n */
	CMPQ TOP, UPE	/* a+n, UPE */
	JGT aboveupe	/* a+n > UPE */
	CMPQ (PSP), UP	/* a, UP */
	JLT belowup		/* a < UP */
	ADDQ $8, PSP	/* get rid of a from the stack */
	MOVQ $0, TOP
	RET

invalidaddress:
	/* TODO need error reporting here */
	INT $0x0D	/* general protection error */
	RET

TEXT validateaddress(SB), 1, $0 /* a -- */
	CALL inum(SB)
	MOVQ TOP, CX
	POP(TOP)
	CMPQ CX, $0
	JNE	invalidaddress
	RET

TEXT validatebuffer(SB), 1, $0 /* a n -- */
	CALL isbufinum(SB)
	MOVQ TOP, CX
	POP(TOP)
	CMPQ CX, $0
	JNE	invalidaddress
	RET

TEXT	forthend(SB), 1, $-4

	END
