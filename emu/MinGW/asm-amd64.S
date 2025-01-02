	.file	"asm-MinGW-amd64.S"
	.text

/*
 * umult(ulong m1, ulong m2, ulong *hi)
 */
/* TODO does not use correct arguments for MinGW */
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

	.global	FPsave
FPsave:
	fstenv (%rcx)
	ret

	.global	FPrestore
FPrestore:
	fldenv	(%rcx)
	ret

	.globl	_tas
_tas:
	movl	$1, %eax
	xchgl	%eax, 0(%rcx)		/* rdi has the first argument to a function */
	ret

