
/*
plan9 assembler puts the first argument in R8 (RARG), return value in AX.
	Caller saves registers - plan9 convention
	not maintaining the values of the temporary registers or EFLAGS
*/

#define STORE(x,y) \
	MOVQ $y, CX; \
	ADDQ UP, CX; \
	MOVQ x, 0(CX)

#define	STOREFORTH \
	STORE(TOP,FORTHTOP);\
	STORE(PSP,FORTHPSP);\
	STORE(RSP,FORTHRSP);\
	STORE(IP,FORTHIP);\
	STORE(W,FORTHW);\
	STORE(UP,FORTHUP);

#define RESTORE(x,y) \
	MOVQ $x, CX; \
	ADDQ UP, CX; \
	MOVQ 0(CX), y;

#define RESTOREFORTH \
	RESTORE(FORTHTOP,TOP);\
	RESTORE(FORTHPSP,PSP);\
	RESTORE(FORTHRSP,RSP);\
	RESTORE(FORTHIP,IP);\
	RESTORE(FORTHW,W);\
	RESTORE(FORTHUP,UP);

/*
using
	( 2nd_parameter 1st_parameter -- )	mode fd open
		simpler code, more comprehensible with the 1st arg next to the call - my opinion
instead of
	( 1st_parameter 2nd_parameter -- ) 	fd mode open
might revisit this later after a trial

there is no forth word for this. It is call'able by the bindings subroutines
cannot get this to work and I cannot decipher it with all the psuedo register nonsense
*/
TEXT	ff_to_c(SB), $0	/* ( argn .. arg2 arg1 nargs -- ) (G move args to C stack) */
	POPQ SI			/* get my return PC from the stack */
	MOVQ TOP, CX	/* check nargs */
	POP(TOP)
	TESTQ $0, CX
	JZ .ff_to_c_done /* no args */
	MOVQ TOP, RARG	/* 1st argument is put in RARG also */
.ff_to_c_again:
	PUSHQ TOP
	POP(TOP)
	LOOP .ff_to_c_again
.ff_to_c_done:
	STOREFORTH
	JMP* SI /* go back to the caller */

#define C_TO_F_0 \
	RESTOREFORTH;

#define C_TO_F_1 /* there is a returned argument */\
	C_TO_F_0; \
	PUSH(TOP); \
	MOVQ AX, TOP;	/* C puts the return value in AX */\

#define F_TO_C_3 \
	MOVQ TOP, RARG;\
	POP(TOP);\
	MOVQ TOP, 8(SP);\
	POP(TOP);\
	MOVQ TOP, 16(SP);\
	POP(TOP);\
	STOREFORTH;

#define F_TO_C_2 \
	MOVQ TOP, RARG;\
	POP(TOP);\
	MOVQ TOP, 8(SP);\
	POP(TOP);\
	STOREFORTH;

#define F_TO_C_1 \
	MOVQ TOP, RARG;\
	POP(TOP);\
	STOREFORTH;

TEXT	fthopen(SB), 1, $-4	/* ( mode cstr -- fd ) */
	F_TO_C_2
	CALL kopen(SB)
	C_TO_F_1
	NEXT

TEXT	fthclose(SB), 1, $-4	/* ( fd -- n ) */
	F_TO_C_1
	CALL kclose(SB)
	C_TO_F_1
	NEXT

TEXT	fthread(SB), 1, $-4	/* ( n a fd -- n2 ) */
	MOVQ (PSP), CX	/* address = start of heap + address */
	ADDQ UP, CX
	MOVQ CX, (PSP)
	F_TO_C_3
	CALL kread(SB)
	C_TO_F_1
	NEXT

TEXT	fthwrite(SB), 1, $-4	/* ( n a fd -- n2 ) */
	MOVQ (PSP), CX	/* address = start of heap + address */
	ADDQ UP, CX
	MOVQ CX, (PSP)
	F_TO_C_3
	CALL kwrite(SB)
	C_TO_F_1
	NEXT

TEXT	fthseek(SB), 1, $-4	/* ( type pos fd -- n ) */
	F_TO_C_3
	CALL kseek(SB)
	C_TO_F_1
	NEXT
