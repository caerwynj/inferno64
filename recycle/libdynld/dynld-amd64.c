#include "lib9.h"
#include <a.out.h>
#include <dynld.h>

#define	CHK(i,ntab)	if((unsigned)(i)>=(ntab))return "bad relocation index"

long
dynmagic(void)
{
	return DYN_MAGIC | I_MAGIC;
}

char*
dynreloc(uchar *b, uintptr p, int m, Dynsym **tab, int ntab)
{
	int i;
	uintptr v, *pp;

	p += (uintptr)b;
	pp = (uintptr*)p;
	v = *pp;
	switch(m){
	case 0:
		v += (uintptr)b;
		break;
	case 1:
		i = v>>22;
		v &= 0x3fffff;
		CHK(i, ntab);
		v += tab[i]->addr;
		break;
	case 2:
		i = v>>22;
		CHK(i, ntab);
		v = tab[i]->addr -p-4;
		break;
	default:
		return "bad relocation mode";
	}
	*pp = v;
	return nil;
}
