
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
*/
TEXT	ff_to_c(SB), 1, $-4	/* ( argn .. arg2 arg1 nargs -- ) (G move args to C stack) */
	POPQ SI			/* get the return PC from the stack */
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
	PUSH(TOP)
	PUSH(RSP)
	PUSH(IP)
	PUSH(W)
	MOVQ PSP, forthsp(SB);
	JMP* SI /* go back to the caller */

TEXT	c_to_ff_0(SB), 1, $-4	/* no returned argument */
	MOVQ forthsp(SB), PSP
	POP(W)
	POP(IP)
	POP(RSP)
	POP(TOP)
	RET
TEXT	c_to_ff_1(SB), 1, $-4	/* there is a returned argument */
	CALL c_to_ff_0(SB)
	PUSH(TOP)
	MOVQ AX, TOP	/* C puts the return value in AX */
	RET

TEXT	fthopen(SB), 1, $-4	/* ( mode cstr -- fd ) */
	PUSH(TOP)
	MOVQ $2, TOP
	CALL ff_to_c(SB)
	CALL kopen(SB)
	CALL c_to_ff_1(SB)
	NEXT

TEXT	fthclose(SB), 1, $-4	/* ( fd -- n ) */
	PUSH(TOP)
	MOVQ $1, TOP
	CALL ff_to_c(SB)
	CALL kclose(SB)
	CALL c_to_ff_1(SB)
	NEXT

TEXT	fthread(SB), 1, $-4	/* ( n a fd -- n2 ) */
	PUSH(TOP)
	MOVQ $3, TOP
	CALL ff_to_c(SB)
	CALL kread(SB)
	CALL c_to_ff_1(SB)
	NEXT

TEXT	fthwrite(SB), 1, $-4	/* ( n a fd -- n2 ) */
	PUSH(TOP)
	MOVQ $3, TOP
	CALL ff_to_c(SB)
	CALL kwrite(SB)
	CALL c_to_ff_1(SB)
	NEXT

TEXT	fthseek(SB), 1, $-4	/* ( type pos fd -- n ) */
	PUSH(TOP)
	MOVQ $3, TOP
	CALL ff_to_c(SB)
	CALL kseek(SB)
	CALL c_to_ff_1(SB)
	NEXT
