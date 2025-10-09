
TEXT	tramp(SB),$0
					/* RARG has the first argument - new stack */
					/* even though the first argument is in RARG, the 0(FP) is still filled with some value */
					/* FP is 64 bytes from SP(?) as there is a SUBQ $0x40, SP on function entry */
	MOVQ	fn+8(FP), CX		/* func to exec - second argument */
	MOVQ	arg+16(FP),DX		/* argument to the function */

	LEAQ	-16(RARG), SP	/* new stack */
	MOVQ	DX, RARG
	PUSHQ	RARG		/* not sure why I need this, but, using it to balance the POPQ below */
	CALL	*CX
	POPQ	AX

	MOVQ	$0, RARG
	PUSHQ	RARG		/* not sure why I need this PUSHQ and CALL. Why not just a JMP to _exits() */
	CALL	_exits(SB)
	POPQ	AX
	RET

TEXT	vstack(SB),$0
				/* MOVL	arg+0(FP), AX not needed as the first argument is in RARG */
	MOVQ	ustack(SB), SP
	PUSHQ	RARG		/* cannot figure out why I need this. But, the compiler will not compile without this */
	CALL	exectramp(SB)
	POPQ	AX /* dammit ken! */
	RET

TEXT	FPsave(SB), 1, $0
	FSTENV	0(RARG)	/* in amd64, the first argument is passed in RARG */
	RET

TEXT	FPrestore(SB), 1, $0
	FLDENV	0(RARG)
	RET
