#include <u.h>
#include <libc.h>

#define H		((void*)(-1))

void
main(int, void**)
{
	intptr **q, *v = H;
	char buf[512];
	int n;

	q = &v;
	if(*q == H)
		print("equal to H\n");
	if(*q != H)
		print("not equal to H\n");
	print("testing q=0x%p *q=0x%p v=0x%p\n", q, *q, v);
	fprint(2, "testing the 2 fd\n");
	n = read(0,buf,18);
	fprint(1, "read %d bytes from 0: %s\n", n, buf);
	exits(0);
}
