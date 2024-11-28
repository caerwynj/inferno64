TEXT	FPsave(SB), 1, $0	/* save FPU environment without waiting */
	MOVQ	RARG, AX
	FSTENV	0(AX)
	RET
 
TEXT	FPrestore(SB), 1, $0	/* restore FPU environment without waiting */
	MOVQ	RARG, AX
	FLDENV	0(AX)
	RET
