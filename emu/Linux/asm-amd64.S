	.file	"asm-Linux-amd64.S"
	.text

/*
 * umult(ulong m1, ulong m2, ulong *hi)
 */

	.type	umult,@function
	.global	umult
umult:
	pushq	%rbp
	movq	%rsp, %rbp
	pushq	%rbx  /* not %rsi ? */

	movq	16(%rbp), %rax
	movq	24(%rbp), %rbx
	mulq	%rbx
	movq	32(%rbp), %rbx
	movq	%rdx, (%rbx)

	popq	%rbx
	popq	%rbp
	ret
/*
	.type	FPsave,@function
	.global	FPsave
FPsave:
	fstenv (%rdi)
	ret

	.type	FPrestore,@function
	.global	FPrestore
FPrestore:
	fldenv	(%rdi)
	ret
*/
	.type	_tas,@function
	.globl	_tas
_tas:
	movl	$1, %eax
	xchgl	%eax, 0(%rdi)		/* rdi has the first argument to a function */
	ret

