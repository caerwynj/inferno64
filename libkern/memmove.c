#include	"lib9.h"

/* for testing only */
void*
memcpy(void *a1, void *a2, uintptr n)
{
	return memmove(a1, a2, n);
}

void*
memmove(void *a1, void *a2, uintptr n)
{
	char *s1, *s2;

	s1 = a1;
	s2 = a2;
	if((s2 < s1) && (s2+n > s1))
		goto back;
	while(n > 0) {
		*s1++ = *s2++;
		n--;
	}
	return a1;

back:
	s1 += n;
	s2 += n;
	while(n > 0) {
		*--s1 = *--s2;
		n--;
	}
	return a1;
}
