
TEXT asmarg1(SB), 1, $-4
	MOVQ	SP, 0(RARG)		/* store SP to the address in the first argument */
	MOVQ	0(SP), BX		/* store return PC - top of stack */
	MOVQ	BX, 8(RARG)		/*		to the next location at the same address */
	MOVL	$0, AX			/* return 0 */
	RET

TEXT asmarg2(SB), 1, $0
	MOVQ	SP, 0(RARG)		/* store SP to the address in the first argument */
	MOVQ	0(SP), BX		/* store return PC - top of stack */
	MOVQ	BX, 8(RARG)		/*		to the next location at the same address */
	MOVL	$0, AX			/* return 0 */
	RET
