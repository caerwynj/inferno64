#include <u.h>
#include <libc.h>

#define H		((void*)(-1))
typedef struct	Point Point;
typedef struct	Rectangle Rectangle;

struct	Point
{
	intptr	x;
	intptr	y;
};

struct Rectangle
{
	Point	min;
	Point	max;
};

Rectangle
Rect(intptr x, intptr y, intptr bx, intptr by)
{
	Rectangle r;

	r.min.x = x;
	r.min.y = y;
	r.max.x = bx;
	r.max.y = by;
	print("Rect x %d y %d bx %d by %d\n", x, y, bx, by);
	print("Rect x %d y %d bx %d by %d\n", r.min.x, r.min.y, r.max.x, r.max.y);
	print("Rect x %x y %x bx %x by %x\n", x, y, bx, by);
	return r;
}

void
main(int, void**)
{
	Rectangle clipr, r;
	intptr i;

	clipr = Rect((intptr)-0x3FFFFFFF, (intptr)-0x3FFFFFFF, (intptr)0x3FFFFFFF, (intptr)0x3FFFFFFF);
	r = Rect(1,1,20,20);
	i = -0x3FFFFFFF;
	print("num %zd i<1 %d\n", i, i<1);
	print("num %zd clipr.min.x<1 %d\n", clipr.min.x, clipr.min.x<1);
	print("rectclip r.min.x %zd < clipr.max.x %zd &&\n"
		"\tclipr.min.x %zd<r.max.x %zd &&\n"
		"\tr.min.y %zd<clipr.max.y %zd &&\n"
		"\tclipr.min.y %zd<r.max.y %zd,"
		"\tcond %d %d %d %d\n\t%d %d\n\t%d\n",
		r.min.x,clipr.max.x , clipr.min.x,r.max.x ,
		r.min.y,clipr.max.y , clipr.min.y,r.max.y,
		r.min.x<clipr.max.x, clipr.min.x<r.max.x,
		r.min.y<clipr.max.y, clipr.min.y<r.max.y,
		r.min.x<clipr.max.x && clipr.min.x<r.max.x,
		r.min.y<clipr.max.y && clipr.min.y<r.max.y,
		r.min.x<clipr.max.x && clipr.min.x<r.max.x &&
		r.min.y<clipr.max.y && clipr.min.y<r.max.y);
	r.min.x = 3221225473;
	print("r.min.x %zd %zd %zd\n",r.min.x, (intptr)(long)r.min.x, (intptr)r.min.x);
	exits(0);
}
