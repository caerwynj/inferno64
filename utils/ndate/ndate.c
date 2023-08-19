#include	<lib9.h>

int
main(void)
{
	ulong t;

	t = time(0);
	print("%lud\n", t);
	return 0;
}
