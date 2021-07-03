	.file	"getcallerpc-OpenBSD-amd64.S"

	.type	getcallerpc,@function
	.global	getcallerpc
getcallerpc:
	movq	8(%rsp), %rax
	movq	-8(%rax), %rax
	ret
