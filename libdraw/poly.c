#include "lib9.h"
#include "draw.h"

static
uchar*
addcoord(uchar *p, int oldx, int newx)
{
	int dx;

	dx = newx-oldx;
	/* does dx fit in 7 signed bits? */
	if((unsigned)(dx - -0x40) <= 0x7F)
		*p++ = dx&0x7F;
	else{
		*p++ = 0x80 | (newx&0x7F);
		*p++ = newx>>7;
		*p++ = newx>>15;
	}
	return p;
}

static
void
dopoly(int cmd, Image *dst, Point *pp, int np, int end0, int end1, int radius, Image *src, Point *sp, Drawop op)
{
	uchar *a, *t, *u;
	int i, ox, oy;

	if(np == 0)
		return;
	t = malloc(np*2*3);
	if(t == nil)
		return;
	u = t;
	ox = oy = 0;
	for(i=0; i<np; i++){
		u = addcoord(u, ox, pp[i].x);
		ox = pp[i].x;
		u = addcoord(u, oy, pp[i].y);
		oy = pp[i].y;
	}

	_setdrawop(dst->display, op);

	a = bufimage(dst->display, 1+4+2+4+4+4+4+2*4+(u-t));
	if(a == 0){
		free(t);
		_drawprint(2, "image poly: %r\n");
		return;
	}
	a[0] = cmd;
	BP32INT(a+1, dst->id);
	BP16INT(a+5, np-1);
	BP32INT(a+7, end0);
	BP32INT(a+11, end1);
	BP32INT(a+15, radius);
	BP32INT(a+19, src->id);
	BP32INT(a+23, sp->x);
	BP32INT(a+27, sp->y);
	memmove(a+31, t, u-t);
	free(t);
}

void
poly(Image *dst, Point *p, int np, int end0, int end1, int radius, Image *src, Point sp)
{
	dopoly('p', dst, p, np, end0, end1, radius, src, &sp, SoverD);
}

void
polyop(Image *dst, Point *p, int np, int end0, int end1, int radius, Image *src, Point sp, Drawop op)
{
	dopoly('p', dst, p, np, end0, end1, radius, src, &sp, op);
}

void
fillpoly(Image *dst, Point *p, int np, int wind, Image *src, Point sp)
{
	dopoly('P', dst, p, np, wind, 0, 0, src, &sp, SoverD);
}

void
fillpolyop(Image *dst, Point *p, int np, int wind, Image *src, Point sp, Drawop op)
{
	dopoly('P', dst, p, np, wind, 0, 0, src, &sp, op);
}
