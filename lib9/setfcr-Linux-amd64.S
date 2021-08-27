
#define	FN(x)	.type x,@function; .global x; x
#define	ENT	subq $32, %rsp
#define	RET	addq $32, %rsp; ret

	.file	"setfcr-Linux-amd64.S"
FN(setfcr):
	ENT
	xorb	$0x3f, %al
	movq	%rax, (%rsp)
	fwait
	fldcw	(%rsp)
	RET

FN(getfcr):
	ENT
	fwait
	fstcw	(%rsp)
	movw	(%rsp), %ax
	andq	$0xffffff, %rax
	xorb	$0x3f, %al
	RET

FN(getfsr):
	ENT
	fwait
	fstsw	(%rsp)
	movw	(%rsp), %ax
	andq	$0xffffff, %rax
	RET

FN(setfsr):
	fclex
	ret
