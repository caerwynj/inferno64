#include "lib9.h"

extern char etext[];
extern char end[];
#define	BY2PG		(0x1000ull)		/* bytes per page */
#define	ROUND(s, sz)	(((s)+((sz)-1))&~((sz)-1))
#define	PGROUND(s)	ROUND(s, 0x200000)

#define KDZERO (PGROUND((uintptr)etext))
#define	CONFADDR 	(KDZERO+ 0x1200ull)
#define	CPU0 	(KDZERO+ 0x1300ull)

#define PTSZ		(4*KiB)			/* page table page size */
#define PTSHIFT		9			/*  */

#define	PGSHIFT		12			/* log(BY2PG) */
#define PGLSZ(l)	(1ull<<(((l)*PTSHIFT)+PGSHIFT))
#define KiB		1024u			/* Kibi 0x0000000000000400 */
#define MiB		1048576u		/* Mebi 0x0000000000100000 */
#define GiB		1073741824u		/* Gibi 0x0000000040000000 */
#define TiB		1099511627776ull	/* Tebi 0x0000010000000000 */
#define PiB		1125899906842624ull	/* Pebi 0x0004000000000000 */
#define EiB		1152921504606846976ull	/* Exbi 0x1000000000000000 */
#define PTLX(v, l)	(((v)>>(((l)*PTSHIFT)+PGSHIFT)) & ((1<<PTSHIFT)-1))

double
canontod(u32 v[2])
{
	union { double d; u32 ul[2]; } a;
	print("|");
	a.d = 1.;
	print(".");
	if(a.ul[0]) {
		a.ul[0] = v[0];
		a.ul[1] = v[1];
	}
	else {
		a.ul[1] = v[0];
		a.ul[0] = v[1];
	}
	print(",");
	return a.d;
}

void
main(int argc, char *argv[])
{
	double d;
	u32 v[2] = {0,0};
	d = canontod(v);
	print("sizes --\n");
	print("sizeof(int) %d\n", sizeof(int));
	print("sizeof(double) %d\n", sizeof(double));
	print("sizeof(float) %d\n", sizeof(float));
	print("sizeof(long) %d\n", sizeof(long));
	print("sizeof(intptr) %d\n", sizeof(intptr));
	print("etext %p KZERO %zx CONFADDR %zx calc %zx\n",
		etext, (intptr)KDZERO, (intptr)CONFADDR, (intptr)(CPU0-CONFADDR));
	print("end %p PGROUND(end) %zx\n",
		end, PGROUND((uintptr)end));
	print("PGLSZ(0) 0x%zux PGLSZ(1) 0x%zx $(PGLSZ(1)-1) 0x%zux $~(PGLSZ(1)-1) 0x%zux 0x%zux\n",
		PGLSZ(0), PGLSZ(1), (PGLSZ(1)-1), ~(PGLSZ(1)-1), ((0x31bd8c + (PGLSZ(1)-1)) & ~(PGLSZ(1)-1))-0x200000);
	print("PTLX(0x1000, 3) 0x%zux\n", (uintptr)PTLX(0x1000, 3));
	print("PTLX(0x1000, 2) 0x%zux\n", (uintptr)PTLX(0x1000, 2));
	print("PTLX(0x1000, 1) 0x%zux\n", (uintptr)PTLX(0x1000, 1));
	print("PTLX(0x1000, 0) 0x%zux\n", (uintptr)PTLX(0x1000, 0));
	print("PTLX(0x200000, 3) 0x%zux\n", (uintptr)PTLX(0x200000, 3));
	print("PTLX(0x200000, 2) 0x%zux\n", (uintptr)PTLX(0x200000, 2));
	print("PTLX(0x200000, 1) 0x%zux\n", (uintptr)PTLX(0x200000, 1));
	print("PTLX(0x200000, 0) 0x%zux\n", (uintptr)PTLX(0x200000, 0));
	print("PTLX(512*GiB, 3) 0x%zux\n", (uintptr)PTLX((uintptr)512*GiB, 3));
	print("PTLX(512*GiB, 2) 0x%zux\n", (uintptr)PTLX((uintptr)512*GiB, 2));
	print("PTLX(512*GiB, 1) 0x%zux\n", (uintptr)PTLX((uintptr)512*GiB, 1));
	print("PTLX(512*GiB, 0) 0x%zux\n", (uintptr)PTLX((uintptr)512*GiB, 0));
	print("PTLX(1*GiB, 3) 0x%zux\n", (uintptr)PTLX(1*GiB, 3));
	print("PTLX(1*GiB, 2) 0x%zux\n", (uintptr)PTLX(1*GiB, 2));
	print("PTLX(1*GiB, 1) 0x%zux\n", (uintptr)PTLX(1*GiB, 1));
	print("PTLX(1*GiB, 0) 0x%zux\n", (uintptr)PTLX(1*GiB, 0));
	exits(nil);
}
