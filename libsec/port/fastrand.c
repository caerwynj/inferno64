#include "os.h"
#include <libsec.h>

/* 
 *  use the X917 random number generator to create random
 *  numbers (faster than truerand() but not as random).
 */
u32
fastrand(void)
{
	u32 x;
	
	genrandom((uchar*)&x, sizeof x);
	return x;
}
