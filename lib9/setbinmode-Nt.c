#include "lib9.h"

extern int _fmode;

void
setbinmode(void)
{
	_fmode = _O_BINARY;
	_setmode(0, _O_BINARY);
	_setmode(1, _O_BINARY);
	_setmode(2, _O_BINARY);
}
