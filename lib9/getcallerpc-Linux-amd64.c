#include <lib9.h>

uintptr
getcallerpc(void *x)
{
//uintptr *lp;

//	lp = x;

//	return lp[-1];
	return (uintptr) __builtin_return_address(0);
}
