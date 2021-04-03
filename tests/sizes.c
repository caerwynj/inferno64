#include "lib9.h"

void
main(int argc, char *argv[])
{
	print("sizes --\n");
	print("sizeof(int) %d\n", sizeof(int));
	print("sizeof(double) %d\n", sizeof(double));
	print("sizeof(float) %d\n", sizeof(float));
	print("sizeof(long) %d\n", sizeof(long));
	print("sizeof(intptr) %d\n", sizeof(intptr));
	exits(nil);
}
