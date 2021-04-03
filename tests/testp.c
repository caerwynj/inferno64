#include <u.h>
#include <libc.h>

#define H		((void*)(-1))

void
main(int, void**)
{
	intptr **q, *v = H;

	q = &v;
	if(*q == H)
		print("equal to H\n");
	if(*q != H)
		print("not equal to H\n");
	print("testing q=0x%p *q=0x%p v=0x%p\n", q, *q, v);
	exits(0);
}
