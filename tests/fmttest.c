#include "lib9.h"

/*
	lib9 does not install e, f, and g - so no float or double format
		inferno-os/lib9/fmt.c
			knownfmt
 */

void
main(int argc, char *argv[])
{
	print("fmttest --\n");
	print("hello world inferno-os\n");
	print("x: %x\n", 0x87654321);
	print("d: %d\n", 0x87654321);
	print("s: %s\n", "hi there");
	print("c: %c\n", '!');
	print("smiley: %C\n", (Rune)0x263a);

	print("%020.10d\n", 100);
	print("%d %d %d\n", 1, 2222, 33333333);
	print("%019d\n", 0);
	print("%08d %08d %08d\n", 1, 2222, 33333333);
	print("%08d %08d %08d\n", 1, 2222, 33333333);
	print("%x %X %b\n", 0x11111111, 0xabcd1234, 12345);
	print("%lld %lld %lld\n", 1LL, 222222222LL, 3333333333333LL);
	print("%019lld %019lld %019lld\n", 1LL, 222222222LL, 3333333333333LL);
	print("%020lld %020lld %020lld\n", 1LL, 222222222LL, 3333333333333LL);
	print("%llx %llX %llb\n", 0x111111111111LL, 0xabcd12345678LL, 112342345LL);
	exits(nil);
}
