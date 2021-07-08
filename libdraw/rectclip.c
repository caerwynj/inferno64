#include "lib9.h"
#include "draw.h"

#define DP if(1){}else print

int
rectclip(Rectangle *rp, Rectangle b)		/* first by reference, second by value */
{
	Rectangle *bp = &b;
	/*
	 * Expand rectXrect() in line for speed
	 */
	DP("rectclip rp->min.x %d < bp->max.x %d &&\n"
		"\tbp->min.x %d<rp->max.x %d &&\n"
		"\trp->min.y %d<bp->max.y %d &&\n"
		"\tbp->min.y %d<rp->max.y %d,"
		"\tcond %d %d %d %d\n\t%d %d\n\t%d\n",
		rp->min.x,bp->max.x , bp->min.x,rp->max.x ,
		rp->min.y,bp->max.y , bp->min.y,rp->max.y,
		
		rp->min.x<bp->max.x, bp->min.x<rp->max.x,
		rp->min.y<bp->max.y, bp->min.y<rp->max.y,
		
		rp->min.x<bp->max.x && bp->min.x<rp->max.x,
		rp->min.y<bp->max.y && bp->min.y<rp->max.y,
		
		rp->min.x<bp->max.x && bp->min.x<rp->max.x &&
		rp->min.y<bp->max.y && bp->min.y<rp->max.y);
	if((rp->min.x<bp->max.x && bp->min.x<rp->max.x &&
	    rp->min.y<bp->max.y && bp->min.y<rp->max.y)==0)
		return 0;
	/* They must overlap */
	if(rp->min.x < bp->min.x)
		rp->min.x = bp->min.x;
	if(rp->min.y < bp->min.y)
		rp->min.y = bp->min.y;
	if(rp->max.x > bp->max.x)
		rp->max.x = bp->max.x;
	if(rp->max.y > bp->max.y)
		rp->max.y = bp->max.y;
	return 1;
}
