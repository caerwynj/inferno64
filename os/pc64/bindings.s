
/*
This file is the forth equivalent of os/port/inferno.c
	It contains forth bindings for the functions in os/port/sysfile.c
 */
/*
plan9 assembler puts the first argument in R8 (RARG), return value in AX.
	Caller saves registers - plan9 convention
	not maintaining the values of the temporary registers or EFLAGS
*/
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
//TEXT	ff_to_c(SB), $0	/* ( argn .. arg2 arg1 nargs -- ) (G move args to C stack) */
//	POPQ SI			/* get my return PC from the stack */
//	MOVQ TOP, CX	/* check nargs */
//	POP(TOP)
//	TESTQ $0, CX
//	JZ .ff_to_c_done /* no args */
//	MOVQ TOP, RARG	/* 1st argument is put in RARG also */
//.ff_to_c_again:
//	PUSHQ TOP
//	POP(TOP)
//	LOOP .ff_to_c_again
//.ff_to_c_done:
//	STOREFORTH
//	JMP* SI /* go back to the caller */

#define STORE(x,y) \
	MOVQ $y, CX; \
	ADDQ UM, CX; \
	MOVQ x, 0(CX);

#define	STOREFORTH \
	STORE(TOP,FORTHTOP);\
	STORE(PSP,FORTHPSP);\
	STORE(RSP,FORTHRSP);\
	STORE(IP,FORTHIP);\
	STORE(W,FORTHW);\
	STORE(UM,FORTHUM);\
	STORE(UME,FORTHUME);

#define RESTORE(x,y) \
	MOVQ $x, CX; \
	ADDQ UM, CX; \
	MOVQ 0(CX), y;

#define RESTOREFORTH \
	RESTORE(FORTHTOP,TOP);\
	RESTORE(FORTHPSP,PSP);\
	RESTORE(FORTHRSP,RSP);\
	RESTORE(FORTHIP,IP);\
	RESTORE(FORTHW,W);\
	RESTORE(FORTHUM,UM);\
	RESTORE(FORTHUME,UME);

#define C_TO_F_0 \
	RESTOREFORTH;

#define C_TO_F_1 /* there is a returned argument */\
	C_TO_F_0; \
	PUSH(TOP); \
	MOVQ AX, TOP;	/* C puts the return value in AX */\

#define F_TO_C_3 \
	MOVQ TOP, 16(SP);\
	POP(TOP);\
	MOVQ TOP, 8(SP);\
	POP(TOP);\
	MOVQ TOP, RARG;\
	POP(TOP);\
	STOREFORTH;

#define F_TO_C_2 \
	MOVQ TOP, 8(SP);\
	POP(TOP);\
	MOVQ TOP, RARG;\
	POP(TOP);\
	STOREFORTH;

#define F_TO_C_1 \
	MOVQ TOP, RARG;\
	POP(TOP);\
	STOREFORTH;

TEXT	sysopen(SB), 1, $24	/* ( cstr mode -- fd ) */
	MOVQ UM, 16(SP)
	F_TO_C_2
	CALL kopen(SB)
	MOVQ 16(SP), UM
	C_TO_F_1
	ADDQ $24, SP
	NEXT

TEXT	sysclose(SB), 1, $16	/* ( fd -- n ) */
	MOVQ UM, 8(SP)
	F_TO_C_1
	CALL kclose(SB)
	MOVQ 24(SP), UM
	C_TO_F_1
	ADDQ $16, SP
	NEXT

/*
 * no link register in amd64
 * 3 arguments for kwrite = 24 bytes
 * 1 local for storing UM = 8 bytes
 * 1 local for storing fd
 * Hence, need 40 bytes on the stack
 * if fd == 0 and read return value == 0 == End of file, terminate
 */
	PUSH(TOP)		/* ( fd a n n ) */
	MOVQ 8(PSP), CX	/*  CX = a  ( fd a n n ) */
	PUSH(CX)		/* ( fd a n a n ) */

	CALL validatebuffer(SB)	/* ( fd a n a n -- fd a n ) */

#define CHECKBUFFER	\
	MOVQ TOP, CX; \
	CMPQ CX, $0;	/* negative n? */\
	JLT belowum;	/* TODO have an appropriate error message */\
	ADDQ (PSP), CX;	/* CX = a+n */\
	CMPQ CX, UME;	/* a+n, UME */\
	JGT aboveume;	/* a+n > UME */\
	CMPQ (PSP), UM;	/* a, UM */\
	JLT belowum;	/* a < UM */

TEXT	sysread(SB), 1, $40	/* ( fd a n -- n2 ) */

	CHECKBUFFER;

	MOVQ 8(PSP), CX
	MOVQ CX, 32(SP)	/* storing the fd to double check later */
	MOVQ UM, 24(SP)
	F_TO_C_3
	CALL kread(SB)
	MOVQ 24(SP), UM
	C_TO_F_1

	CMPQ TOP, $-1		/* return value == -1? */
	JEQ fsread_checkfd	/* return value = -1 */
	TESTQ TOP, TOP		/* check if read return value == 0 */
	JNZ fsread_continue
fsread_checkfd:
	MOVQ 32(SP), CX		/* read return value == 0, check if fd is stdin */
	TESTQ CX, CX
	JNZ fsread_continue

	/* and fd == 0, terminate */
	ADDQ $40, SP
	JMP _fthterminate

fsread_continue:
	ADDQ $40, SP
	NEXT

/*
 * no link register in amd64
 * 3 arguments for kwrite = 24 bytes
 * 1 local for storing UM = 8 bytes
 * Hence, need 32 bytes on the stack
 */
TEXT	syswrite(SB), 1, $32	/* ( fd a n -- n2|-1 ) */

	CHECKBUFFER

	MOVQ UM, 24(SP)
	F_TO_C_3
	CALL kwrite(SB)
	MOVQ 24(SP), UM
	C_TO_F_1
	ADDQ $32, SP
	NEXT

TEXT	sysseek(SB), 1, $32	/* ( fd pos type -- n ) */
	MOVQ UM, 24(SP)
	F_TO_C_3
	CALL kseek(SB)
	MOVQ 24(SP), UM
	C_TO_F_1
	ADDQ $32, SP
	NEXT

TEXT	syscreate(SB), 1, $32	/* ( cstr mode perm -- fd ) */
	MOVQ UM, 24(SP)
	F_TO_C_3
	CALL kcreate(SB)
	MOVQ 24(SP), UM
	C_TO_F_1
	ADDQ $32, SP
	NEXT

TEXT	sysbind(SB), 1, $32	/* ( cstrold cstrnew flags -- int ) */
	MOVQ UM, 24(SP)
	F_TO_C_3
	CALL kbind(SB)
	MOVQ 24(SP), UM
	C_TO_F_1
	ADDQ $32, SP
	NEXT

#define F_TO_C_5 \
	MOVQ TOP, 32(SP);\
	POP(TOP);\
	MOVQ TOP, 24(SP);\
	POP(TOP);\
	MOVQ TOP, 16(SP);\
	POP(TOP);\
	MOVQ TOP, 8(SP);\
	POP(TOP);\
	MOVQ TOP, RARG;\
	POP(TOP);\
	STOREFORTH;

TEXT	sysmount(SB), 1, $48	/* ( fd afd cstrold flags spec -- int ) */
	MOVQ UM, 40(SP)
	F_TO_C_5
	CALL kmount(SB)
	MOVQ 40(SP), UM
	C_TO_F_1
	ADDQ $48, SP
	NEXT
