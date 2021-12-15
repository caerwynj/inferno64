
/*
: tests ; watch -e 'cmp.s$' 'mk 6.cmp && ./6.cmp; echo $status'
*/

TEXT	main+0(SB),0,$16
	MOVQ $20, BX
	MOVQ $10, AX 
	CMPQ AX, BX
/* if AX < BX then BX - AX > 0, no sign flag */
	JLT .true
	MOVQ $0, AX
	JMP .exit
.true:
	MOVQ $9, AX
.exit:
	MOVQ	$truemsg(SB), BP
	CALL	_exits+0(SB)
	RET

DATA	truemsg+0(SB)/5, $"true\z"
GLOBL	truemsg(SB), $5
DATA	falsemsg+0(SB)/6, $"false\z"
GLOBL	falsemsg(SB), $6


	END
