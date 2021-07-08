#include "lib9.h"
#include "draw.h"

void
line(Image *dst, Point p0, Point p1, int end0, int end1, int radius, Image *src, Point sp)
{
	lineop(dst, p0, p1, end0, end1, radius, src, sp, SoverD);
}

void
lineop(Image *dst, Point p0, Point p1, int end0, int end1, int radius, Image *src, Point sp, Drawop op)
{
	uchar *a;

	_setdrawop(dst->display, op);

	a = bufimage(dst->display, 1+4+2*4+2*4+4+4+4+4+2*4);
	if(a == 0){
		_drawprint(2, "image line: %r\n");
		return;
	}
	a[0] = 'L';
	BP32INT(a+1, dst->id);
	BP32INT(a+5, p0.x);
	BP32INT(a+9, p0.y);
	BP32INT(a+13, p1.x);
	BP32INT(a+17, p1.y);
	BP32INT(a+21, end0);
	BP32INT(a+25, end1);
	BP32INT(a+29, radius);
	BP32INT(a+33, src->id);
	BP32INT(a+37, sp.x);
	BP32INT(a+41, sp.y);
}
