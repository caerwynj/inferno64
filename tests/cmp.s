
/*
: tests ; watch -e 'cmp.s$' 'mk 6.cmp && ./6.cmp; echo $status'
*/
/*
if x < y then y - x > 0, no sign flag
	intel manual says destination operand - source operand
	9front comparision operators make the usage more english-like
	For, CMP x,y; JGT greater can be read as
	compare x and y; if x > y, goto greater
	check tests/cmp.s for tests
 */

TEXT	main+0(SB),0,$16
	MOVQ $20, BX
	MOVQ $30, AX 
	CMPQ AX, BX
/* if AX < BX then BX - AX > 0, no sign flag */
	JGT .true
	MOVQ $falsemsg(SB), BP
	JMP .exit
.true:
	MOVQ $truemsg(SB), BP
.exit:
	CALL	_exits+0(SB)
	RET

DATA	truemsg+0(SB)/5, $"true\z"
GLOBL	truemsg(SB), $5
DATA	falsemsg+0(SB)/6, $"false\z"
GLOBL	falsemsg(SB), $6


	END
