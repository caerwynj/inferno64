	.file	"asm-OpenBSD-amd64.S"

#include <sys/syscall.h>
#include <machine/asm.h>

/*
 * executeonnewstack(void *tos, void (*tramp)(void *arg), void *arg)
 */

	.type	 ournewstack,@function
	.global	executeonnewstack
executeonnewstack:
	pushq	%rbp
	movq	%rsp, %rbp
	pushq	%rsi

	movq	16(%rbp), %rsi	/* get tos */
	subq	$8, %rsi
	movq	32(%rbp), %rax
	movq	%rax, (%rsi)	/* stash arg on new stack */
	subq	$8, %rsi
	movq	24(%rbp), %rax
	movq	%rax, (%rsi)	/* stash tramp on new stack */
	mov	%rsi, %rsp	/* swap stacks pronto */
	popq	%rax		/* recover the tramp address */
	call	*%rax		/* and jump to it (ho ho) */

	/* if we return here, tramp didn't do it's job */

	addq	$16, %rsp	/* clean up for pose value */

	leaq	SYS_exit, %rax
	int	$0x80

/*
 * unlockandexit(int *key)
 *
 * NB: the return status may be rubbish if the stack is reused
 *	between the unlock and the system call, but this should
 *	not matter since no task is waiting for the result
 */

	.type	unlockandexit,@function
	.global	unlockandexit
unlockandexit:
	pushq	%rbp
	movq	%rsp, %rbp

	movq	16(%rbp), %rsi		/* get the key address */
	pushq	$0			/* exit status 0 */
	movq	$0, %rax		/* unlock the stack allocator */
	movq	%rax, (%rsi)
	leaq	SYS_exit, %rax		/* call exit */
	int	$0x80

/*
 * umult(ulong m1, ulong m2, ulong *hi)
 * umult(rdi, rsi, rdx) - as per system v abi
 * 	store rdx in rbp as mul returns the high value in rdx 
 */

	.type	umult,@function
	.global	umult
umult:
	pushq	%rbp
	movq	%rdx, %rbp	/* save the 3rd argument (for the high of the result) */
	movq	%rdi, %rax	/* loading the 1st argument */
	movq	%rsi, %rdx	/* loading the 2nd argument */
	mul	%rdx
	movq	%rdx, (%rbp)
	popq	%rbp
	ret

	.type	FPsave,@function
	.global	FPsave
FPsave:
	fstenv	(%rdi)
	ret

	.type	FPrestore,@function
	.global	FPrestore
FPrestore:
	fldenv	(%rdi)
	ret

	.type	getcallerpc,@function
	.global	getcallerpc
getcallerpc:
	movq	8(%rdi), %rax /* rdi has the first argument to a function */
	ret

	.type	_tas,@function
	.globl	_tas
_tas:
	movl	$1, %eax
	xchgl	%eax, 0(%rdi)		/* rdi has the first argument to a function */
	ret
