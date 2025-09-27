#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"

static Lock fmtl;

void
_fmtlock(void)
{
	lock(&fmtl);
}

void
_fmtunlock(void)
{
	unlock(&fmtl);
}

int
_efgfmt(Fmt*)
{
	return -1;
}

/* %r does not do anything when used within the kernel.
 * It works from limbo though as the lib9 errfmt() is
 * different.
 */
int
errfmt(Fmt *)
{
	return -1;
}
