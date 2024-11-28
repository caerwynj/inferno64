#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"

#define datoff		((uintptr)((Xhdr*)0)->data)

enum
{
	Chunk		= 64*1024,
	Nhole		= 128,
	Magichole	= 0xDeadBabe,
};

typedef struct Hole Hole;
typedef struct Xalloc Xalloc;
typedef struct Xhdr Xhdr;

struct Hole
{
	uintptr	addr;
	u64	size;
	uintptr	top;
	Hole*	link;
};

struct Xhdr
{
	u64	size;
	u32	magix;
	char	data[1];
};

struct Xalloc
{
	Lock;
	Hole	hole[Nhole];
	Hole*	flist;	/* front of list */
	Hole*	table;
};

static Xalloc	xlists;

static void
ixprt()
{
	xsummary();
	ixsummary();
}

void
xinit(void)
{
	Hole *h, *eh;
	Confmem *cm;
	int i;

	eh = &xlists.hole[Nhole-1];
	for(h = xlists.hole; h < eh; h++)
		h->link = h+1;

	xlists.flist = xlists.hole;

	for(i=0; i<nelem(conf.mem); i++){
		cm = &conf.mem[i];
		xhole(cm->base, cm->npage*BY2PG);
	}

	/* debugkey('x', "xalloc/ialloc", ixprt, 0); */
	xsummary();
}

void*
xspanalloc(uintptr size, s32 align, uintptr span)
{
	uintptr a, v, t;

	a = (uintptr)xalloc(size+align+span);
	if(a == 0)
		panic("xspanalloc: %zud %d %zux\n", size, align, span);

	if(span > 2) {
		v = (a + span) & ~(span-1);
		t = v - a;
		if(t > 0)
			xhole(PADDR(a), t);
		t = a + span - v;
		if(t > 0)
			xhole(PADDR(v+size+align), t);
	}
	else
		v = a;

	if(align > 1)
		v = (v + align) & ~(align-1);

	return (void*)v;
}

void*
xallocz(uintptr size, s32 zero)
{
	Xhdr *p;
	Hole *h, **l;

	size += BY2V + sizeof(Xhdr);
	size &= ~(BY2V-1);

	ilock(&xlists);
	l = &xlists.table;
	for(h = *l; h; h = h->link) {
		if(h->size >= size) {
			p = (Xhdr*)h->addr;
			h->addr += size;
			h->size -= size;
			if(h->size == 0) {
				*l = h->link;
				h->link = xlists.flist;
				xlists.flist = h;
			}
			iunlock(&xlists);
			p = KADDR(p);
			p->magix = Magichole;
			p->size = size;
			if(zero)
				memset(p->data, 0, size);
			return p->data;
		}
		l = &h->link;
	}
	iunlock(&xlists);
	return nil;
}

void*
xalloc(uintptr size)
{
	return xallocz(size, 1);
}

void
xfree(void *p)
{
	Xhdr *x;

	x = (Xhdr*)((uintptr)p - datoff);
	if(x->magix != Magichole) {
		xsummary();
		panic("xfree(0x%p) 0x%ux!=0x%ux", p, (u32)Magichole, x->magix);
	}
	xhole(PADDR(x), x->size);
}

int
xmerge(void *vp, void *vq)
{
	Xhdr *p, *q;

	p = (Xhdr*)(((uintptr)vp - offsetof(Xhdr, data[0])));
	q = (Xhdr*)(((uintptr)vq - offsetof(Xhdr, data[0])));
	if(p->magix != Magichole || q->magix != Magichole) {
		xsummary();
		panic("xmerge(%#p, %#p) bad magic %#ux, %#ux\n",
			vp, vq, p->magix, q->magix);
	}
	if((uchar*)p+p->size == (uchar*)q) {
		p->size += q->size;
		return 1;
	}
	return 0;
}

void
xhole(uintptr addr, uintptr size)
{
	uintptr top;
	Hole *h, *c, **l;

	if(size == 0)
		return;

	top = addr + size;
	ilock(&xlists);
	l = &xlists.table;
	for(h = *l; h; h = h->link) {
		if(h->top == addr) {
			h->size += size;
			h->top = h->addr+h->size;
			c = h->link;
			if(c && h->top == c->addr) {
				h->top += c->size;
				h->size += c->size;
				h->link = c->link;
				c->link = xlists.flist;
				xlists.flist = c;
			}
			iunlock(&xlists);
			return;
		}
		if(h->addr > addr)
			break;
		l = &h->link;
	}
	if(h && top == h->addr) {
		h->addr -= size;
		h->size += size;
		iunlock(&xlists);
		return;
	}

	if(xlists.flist == nil) {
		iunlock(&xlists);
		print("xfree: no free holes, leaked %zud bytes\n", size);
		return;
	}

	h = xlists.flist;
	xlists.flist = h->link;
	h->addr = addr;
	h->top = top;
	h->size = size;
	h->link = *l;
	*l = h;
	iunlock(&xlists);
}

void
xsummary(void)
{
	s64 i;
	Hole *h;

	i = 0;
	for(h = xlists.flist; h; h = h->link)
		i++;

	print("%lld holes free\n", i);
	i = 0;
	for(h = xlists.table; h; h = h->link){
		print("%.8zux %.8zux %zud\n", h->addr, h->top, h->size);
		i += h->size;
	}
	print("%lld bytes free\n", i);
}
