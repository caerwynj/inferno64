#include "lib9.h"

#undef malloc
#undef free
#undef realloc
#undef calloc

void*
kmalloc(size_t size)
{
	return malloc(size);
}

void
kfree(void *v)
{
	return free(v);
}

void*
krealloc(void *v, size_t size)
{
	return realloc(v, size);
}

void*
kcalloc(size_t n, size_t szelem)
{
	return malloc(n*szelem);
}	

void*
mallocz(size_t n, int clr)
{
	void *v;
	v = malloc(n);
	if(v && clr) {
		memset(v, 0, n);
	}
	return v;
}
