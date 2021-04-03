#include "lib9.h"
#include "interp.h"

void
main(int argc, char *argv[])
{
	char *str = "1e400";

	fmtinstall('g', gfltconv);
	fmtinstall('G', gfltconv);
	fmtinstall('e', gfltconv);
	/* fmtinstall('E', gfltconv); */	/* avoid clash with ether address */
	fmtinstall(0x00c9, gfltconv);	/* L'É' */
	fmtinstall('f', gfltconv);

	print("gfmttest --\n");
	print("g: %g %g %g\n", 3.14159, 3.14159e10, 3.14159e-10);
	print("e: %e %e %e\n", 3.14159, 3.14159e10, 3.14159e-10);
	print("f: %f %f %f\n", 3.14159, 3.14159e10, 3.14159e-10);
	print("3.14: %f %g %e\n", 3.14000, 3.14000, 3.14000);
	print("%g %.18g\n", 2e25, 2e25);
	print("%2.18g\n", 1.0);
	print("%2.18f\n", 1.0);
	print("%f\n", 3.1415927/4);
	print("%d\n", 23);
	print("%0.10d\n", 12345);

	print("infinity %g\n", strtod(str,nil)); // infinity
	print("NaN %g\n", 0./0.); // NaN
	print("Eps %g\n", 2.2204460492503131e-16); // Eps
	print("pi %g\n", 3.14159265358979323846); // pi
	exits(nil);
}
