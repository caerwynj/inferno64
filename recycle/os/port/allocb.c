#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

enum
{
	Hdrspc		= 64,		/* leave room for high-level headers */
	Bdead		= 0x51494F42,	/* "QIOB" */
};

struct
{
	Lock;
	uintptr	bytes;
} ialloc;

/*
 *  allocate blocks (round data base address to 64 bit boundary).
 *  if mallocz gives us more than we asked for, leave room at the front
 *  for header.
 */
Block*
_allocb(s32 size)
{
	Block *b;
	uintptr addr;
	int n;

	b = mallocz(sizeof(Block)+size+Hdrspc+(BY2V-1), 0);
	if(b == nil)
		return nil;

	b->next = nil;
	b->list = nil;
	b->free = nil;
	b->flag = 0;

	addr = (uintptr)b;
	addr = ROUND(addr + sizeof(Block), BY2V);
	b->base = (uchar*)addr;
	b->lim = ((uchar*)b) + msize(b);
	b->rp = b->base;
	n = b->lim - b->base - size;
	b->rp += n & ~(BY2V-1);
	b->wp = b->rp;

	return b;
}

/* TODO Add Bhdr attributes here */
void
showblockheader(Block *b, intptr pc, char *str)
{
	iprint("%s called by 0x%8.8luX, pid %d base 0x%8.8luX lim 0x%8.8luX\n"
			"	next 0x%8.8luX rp 0x%8.8luX wp 0x%8.8luX malloctag 0x%8.8luX\n",
			str, pc, up->pid,
			b->base, b->lim, b->next,
			b->rp, b->wp, getmalloctag(b));
}

Block*
allocb(int size)
{
	Block *b;

	if(0 && up == nil)
		panic("allocb outside process: %8.8zux", getcallerpc(&size));
	b = _allocb(size);
	if(b == 0)
		exhausted("Blocks");
	setmalloctag(b, getcallerpc(&size));
	/* showblockheader(b, getcallerpc(&size), "allocb()"); */
	return b;
}

/*
 *  interrupt time allocation
 */
Block*
iallocb(int size)
{
	Block *b;

	if(ialloc.bytes > conf.ialloc){
		print("iallocb: limited %lud/%lud\n", ialloc.bytes, conf.ialloc);
		return nil;
	}

	b = _allocb(size);
	if(b == nil){
		print("iallocb: no memory %lud/%lud\n", ialloc.bytes, conf.ialloc);
		return nil;
	}
	setmalloctag(b, getcallerpc(&size));
	b->flag = BINTR;

	ilock(&ialloc);
	ialloc.bytes += b->lim - b->base;
	iunlock(&ialloc);

	return b;
}

void checkbl(Block *b, char *msg, intptr pc);
void
freeb(Block *b)
{
	void *dead = (void*)Bdead;

	if(b == nil)
		return;

	/*
	 * drivers which perform non cache coherent DMA manage their own buffer
	 * pool of uncached buffers and provide their own free routine.
	 */
	if(b->free) {
		/* checkbl(b, "checking block before free'ing\n", getcallerpc(&b));
		print("freeb b 0x%zx b->free 0x%zx\n", b, (intptr)b->free); */
		b->free(b);
		return;
	}
	if(b->flag & BINTR) {
		ilock(&ialloc);
		ialloc.bytes -= b->lim - b->base;
		iunlock(&ialloc);
	}

	/* poison the block in case someone is still holding onto it */
	b->next = dead;
	b->rp = dead;
	b->wp = dead;
	b->lim = dead;
	b->base = dead;

	free(b);
}

/* same as checkb but with more details for debugging */
void
checkbl(Block *b, char *msg, intptr pc)
{
	void *dead = (void*)Bdead;

	if(b == dead)
		panic("checkb b %s %lux", msg, b);
	if(b->base == dead || b->lim == dead || b->next == dead
	  || b->rp == dead || b->wp == dead){
		showblockheader(b, pc, "freeb() dead");
		panic("checkb dead: %s\n", msg);
	}

	if(b->base > b->lim){
		showblockheader(b, pc, "freeb() 0");
		panic("checkb 0 %s %lux %lux", msg, b->base, b->lim);
	}
	if(b->rp < b->base){
		showblockheader(b, pc, "freeb() 1");
		panic("checkb 1 %s %lux %lux", msg, b->base, b->rp);
	}
	if(b->wp < b->base)
		panic("checkb 2 %s %lux %lux", msg, b->base, b->wp);
	if(b->rp > b->lim)
		panic("checkb 3 %s %lux %lux", msg, b->rp, b->lim);
	if(b->wp > b->lim)
		panic("checkb 4 %s %lux %lux", msg, b->wp, b->lim);

}
void
checkb(Block *b, char *msg)
{
	void *dead = (void*)Bdead;

	if(b == dead)
		panic("checkb b %s %lux", msg, b);
	if(b->base == dead || b->lim == dead || b->next == dead
	  || b->rp == dead || b->wp == dead){
		print("checkb: base 0x%8.8luX lim 0x%8.8luX next 0x%8.8luX\n",
			b->base, b->lim, b->next);
		print("checkb: rp 0x%8.8luX wp 0x%8.8luX\n", b->rp, b->wp);
		panic("checkb dead: %s\n", msg);
	}

	if(b->base > b->lim)
		panic("checkb 0 %s %lux %lux", msg, b->base, b->lim);
	if(b->rp < b->base)
		panic("checkb 1 %s %lux %lux", msg, b->base, b->rp);
	if(b->wp < b->base)
		panic("checkb 2 %s %lux %lux", msg, b->base, b->wp);
	if(b->rp > b->lim)
		panic("checkb 3 %s %lux %lux", msg, b->rp, b->lim);
	if(b->wp > b->lim)
		panic("checkb 4 %s %lux %lux", msg, b->wp, b->lim);

}

void
iallocsummary(void)
{
	print("ialloc %ud/%ud\n", ialloc.bytes, conf.ialloc);
}
