/*
 * int _tas(int *p)
 *
 * Test-and-set: atomically read *p and set it to non-zero.
 * Returns the old value.
 *
 * x0 = pointer to int
 * Returns: old value in x0
 */
	.global	_tas
	.type	_tas, %function
_tas:
	mov	w1, #1		/* value to store */
1:
	ldaxr	w2, [x0]	/* load exclusive with acquire */
	cbnz	w2, 2f		/* if already set, return old value */
	stlxr	w3, w1, [x0]	/* store exclusive with release */
	cbnz	w3, 1b		/* retry if store failed */
2:
	mov	w0, w2		/* return old value */
	ret
	.size	_tas, .-_tas
