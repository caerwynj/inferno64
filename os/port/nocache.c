#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

/*
 * stubs when no devmnt cache
 */
void
cinit(void)
{
}

int
copen(Chan *c)
{
	c->flag &= ~CCACHE;
	return 0;
}

int
cread(Chan *c, uchar *b, int n, vlong off)
{
	USED(c);
	USED(b);
	USED(n);
	USED(off);
	return 0;
}

void
cwrite(Chan *c, uchar *buf, int n, vlong off)
{
	USED(c);
	USED(buf);
	USED(n);
	USED(off);
}

void
cupdate(Chan *c, uchar *buf,  int n, vlong off)
{
	USED(c);
	USED(buf);
	USED(n);
	USED(off);
}

void
ctrunc(Chan *c)
{
	USED(c);
}

void
cclunk(Chan *c)
{
	USED(c);
}
