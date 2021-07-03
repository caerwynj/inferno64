#include "lib9.h"
#include "draw.h"

enum
{
	Max = 100
};

Point
string(Image *dst, Point pt, Image *src, Point sp, Font *f, char *s)
{
	return _string(dst, pt, src, sp, f, s, nil, 1<<24, dst->clipr, nil, ZP, SoverD);
}

Point
stringop(Image *dst, Point pt, Image *src, Point sp, Font *f, char *s, Drawop op)
{
	return _string(dst, pt, src, sp, f, s, nil, 1<<24, dst->clipr, nil, ZP, op);
}

Point
stringn(Image *dst, Point pt, Image *src, Point sp, Font *f, char *s, int len)
{
	return _string(dst, pt, src, sp, f, s, nil, len, dst->clipr, nil, ZP, SoverD);
}

Point
stringnop(Image *dst, Point pt, Image *src, Point sp, Font *f, char *s, int len, Drawop op)
{
	return _string(dst, pt, src, sp, f, s, nil, len, dst->clipr, nil, ZP, op);
}

Point
runestring(Image *dst, Point pt, Image *src, Point sp, Font *f, Rune *r)
{
	return _string(dst, pt, src, sp, f, nil, r, 1<<24, dst->clipr, nil, ZP, SoverD);
}

Point
runestringop(Image *dst, Point pt, Image *src, Point sp, Font *f, Rune *r, Drawop op)
{
	return _string(dst, pt, src, sp, f, nil, r, 1<<24, dst->clipr, nil, ZP, op);
}

Point
runestringn(Image *dst, Point pt, Image *src, Point sp, Font *f, Rune *r, int len)
{
	return _string(dst, pt, src, sp, f, nil, r, len, dst->clipr, nil, ZP, SoverD);
}

Point
runestringnop(Image *dst, Point pt, Image *src, Point sp, Font *f, Rune *r, int len, Drawop op)
{
	return _string(dst, pt, src, sp, f, nil, r, len, dst->clipr, nil, ZP, op);
}

Point
_string(Image *dst, Point pt, Image *src, Point sp, Font *f, char *s, Rune *r, int len, Rectangle clipr, Image *bg, Point bgp, Drawop op)
{
	int m, n, wid, max;
	ushort cbuf[Max], *c, *ec;
	uchar *b;
	char *subfontname;
	char **sptr;
	Rune **rptr;
	Font *def;

	if(s == nil){
		s = "";
		sptr = nil;
	}else
		sptr = &s;
	if(r == nil){
		r = (Rune*) L"";
		rptr = nil;
	}else
		rptr = &r;
	while((*s || *r) && len){
		max = Max;
		if(len < max)
			max = len;
		n = cachechars(f, sptr, rptr, cbuf, max, &wid, &subfontname);
		if(n > 0){
			_setdrawop(dst->display, op);

			m = 47+2*n;
			if(bg)
				m += 4+2*4;
			b = bufimage(dst->display, m);
			if(b == 0){
				_drawprint(2, "string: %r\n");
				break;
			}
			if(bg)
				b[0] = 'x';
			else
				b[0] = 's';
			BP32INT(b+1, dst->id);
			BP32INT(b+5, src->id);
			BP32INT(b+9, f->cacheimage->id);
			BP32INT(b+13, pt.x);
			BP32INT(b+17, pt.y+f->ascent);
			BP32INT(b+21, clipr.min.x);
			BP32INT(b+25, clipr.min.y);
			BP32INT(b+29, clipr.max.x);
			BP32INT(b+33, clipr.max.y);
			BP32INT(b+37, sp.x);
			BP32INT(b+41, sp.y);
			BP16INT(b+45, n);
			b += 47;
			if(bg){
				BP32INT(b, bg->id);
				BP32INT(b+4, bgp.x);
				BP32INT(b+8, bgp.y);
				b += 12;
			}
			ec = &cbuf[n];
			for(c=cbuf; c<ec; c++, b+=2)
				BP16INT(b, *c);
			pt.x += wid;
			bgp.x += wid;
			agefont(f);
			len -= n;
		}
		if(subfontname){
			if(_getsubfont(f->display, subfontname) == 0){
				def = f->display->defaultfont;
				if(def && f!=def)
					f = def;
				else
					break;
			}
		}
	}
	return pt;
}
