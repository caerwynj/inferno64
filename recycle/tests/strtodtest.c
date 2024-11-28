#include "lib9.h"
#include "interp.h"

extern	double	strtod(const char *, char **);

void
main(int argc, char *argv[])
{
	char *str = "1e400";
	double d, d1;
	unsigned long u1 = 10;

	fmtinstall('g', gfltconv);
	fmtinstall('G', gfltconv);
	fmtinstall('e', gfltconv);
	/* fmtinstall('E', gfltconv); */	/* avoid clash with ether address */
	fmtinstall(0x00c9, gfltconv);	/* L'É' */
	fmtinstall('f', gfltconv);
	print("strtodtest --\n");
	d = strtod(str,nil);
	d1 = 4.;
	print("infinity %g %e %f %g %d\n", d, d, d, d1, u1); // infinity
	exits(nil);
}
