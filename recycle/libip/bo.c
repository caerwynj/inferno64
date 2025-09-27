#include "u.h"
#include "kern.h"
#include "ip.h"

void
hnputv(void *p, u64 v)
{
	uchar *a;

	a = p;
	a[0] = v>>56;
	a[1] = v>>48;
	a[2] = v>>40;
	a[3] = v>>32;
	a[4] = v>>24;
	a[5] = v>>16;
	a[6] = v>>8;
	a[7] = v;
}

void
hnputl(void *p, u32 v)
{
	uchar *a;

	a = p;
	a[0] = v>>24;
	a[1] = v>>16;
	a[2] = v>>8;
	a[3] = v;
}

void
hnputs(void *p, u16 v)
{
	uchar *a;

	a = p;
	a[0] = v>>8;
	a[1] = v;
}

u64
nhgetv(void *p)
{
	uchar *a;
	u64 v;

	a = p;
	v = (uvlong)a[0]<<56;
	v |= (uvlong)a[1]<<48;
	v |= (uvlong)a[2]<<40;
	v |= (uvlong)a[3]<<32;
	v |= a[4]<<24;
	v |= a[5]<<16;
	v |= a[6]<<8;
	v |= a[7]<<0;
	return v;
}

u32
nhgetl(void *p)
{
	uchar *a;

	a = p;
	return (a[0]<<24)|(a[1]<<16)|(a[2]<<8)|(a[3]<<0);
}

u16
nhgets(void *p)
{
	uchar *a;

	a = p;
	return (a[0]<<8)|(a[1]<<0);
}
