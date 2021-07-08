#include "lib9.h"
#include "draw.h"

void
replclipr(Image *i, int repl, Rectangle clipr)
{
	uchar *b;

	b = bufimage(i->display, 22);
	if (b == 0) {
		_drawprint(2, "replclipr: no bufimage\n");
		return;
	}
	b[0] = 'c';
	BP32INT(b+1, i->id);
	repl = repl!=0;
	b[5] = repl;
	BP32INT(b+6, clipr.min.x);
	BP32INT(b+10, clipr.min.y);
	BP32INT(b+14, clipr.max.x);
	BP32INT(b+18, clipr.max.y);
	i->repl = repl;
	i->clipr = clipr;
}
