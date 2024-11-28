#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"
#include "interp.h"

#define left	u.s.bhl
#define right	u.s.bhr
#define fwd	u.s.bhf
#define prev	u.s.bhv
#define parent	u.s.bhp

#define RESERVED	512*1024

struct Pool
{
	char*	name;
	int	pnum;
	uintptr	maxsize;
	intptr	quanta;
	int	chunk;
	uintptr	ressize;
	uintptr	cursize;
	uintptr	arenasize;
	uintptr	hw;
	Lock	l;
	Bhdr*	root;
	Bhdr*	chain;
	uintptr	nalloc;
	uintptr	nfree;
	intptr	nbrk;
	intptr	lastfree;
	int	warn;
	void	(*move)(void*, void*);
};

/* keep the quanta above the size of 5 pointers and 2 longs else the next block
	will be getting overwritten by the header -- starts a corruption hunt
	when pointer size = 8 bytes, then 63 = 2^q -1
		for 4 bytes, 31
	TODO make this a macro?
	for allocpc and reallocpc, 2 * 8 = 16 bytes get added
	so, minimum size = 2*4 + 2*8 + 5*8 = 64, using 127 to satisfy 2^q -1
 */
static
struct
{
	int	n;
	Pool	pool[MAXPOOL];
	// Lock	l;
} table = {
	3,
	{
		{ "main",  0, 	32*1024*1024, 127,  512*1024, 0, 31*1024*1024 },
		{ "heap",  1, 	32*1024*1024, 127,  512*1024, 0, 31*1024*1024 },
		{ "image", 2,   64*1024*1024+256, 127, 4*1024*1024, 1, 63*1024*1024 },
	}
};

Pool*	mainmem = &table.pool[0];
Pool*	heapmem = &table.pool[1];
Pool*	imagmem = &table.pool[2];

static void _auditmemloc(char *, void *);
void (*auditmemloc)(char *, void *) = _auditmemloc;
static void _poolfault(void *, char *, uintptr);
void (*poolfault)(void *, char *, uintptr) = _poolfault;

int
memusehigh(void)
{
	return 	mainmem->cursize > mainmem->ressize ||
			heapmem->cursize > heapmem->ressize ||
			imagmem->cursize > imagmem->ressize;
}

void
poolimmutable(void *v)
{
	Bhdr *b;

	D2B(b, v);
	b->magic = MAGIC_I;
}

void
poolmutable(void *v)
{
	Bhdr *b;

	D2B(b, v);
	b->magic = MAGIC_A;
	/* ((Heap*)v)->color = mutator; */
}

char*
poolname(Pool *p)
{
	return p->name;
}

Bhdr*
poolchain(Pool *p)
{
	return p->chain;
}

void
pooldel(Pool *p, Bhdr *t)
{
	Bhdr *s, *f, *rp, *q;

	if(t->parent == nil && p->root != t) {
		t->prev->fwd = t->fwd;
		t->fwd->prev = t->prev;
		return;
	}

	if(t->fwd != t) {
		f = t->fwd;
		s = t->parent;
		f->parent = s;
		if(s == nil)
			p->root = f;
		else {
			if(s->left == t)
				s->left = f;
			else
				s->right = f;
		}

		rp = t->left;
		f->left = rp;
		if(rp != nil)
			rp->parent = f;
		rp = t->right;
		f->right = rp;
		if(rp != nil)
			rp->parent = f;

		t->prev->fwd = t->fwd;
		t->fwd->prev = t->prev;
		return;
	}

	if(t->left == nil)
		rp = t->right;
	else {
		if(t->right == nil)
			rp = t->left;
		else {
			f = t;
			rp = t->right;
			s = rp->left;
			while(s != nil) {
				f = rp;
				rp = s;
				s = rp->left;
			}
			if(f != t) {
				s = rp->right;
				f->left = s;
				if(s != nil)
					s->parent = f;
				s = t->right;
				rp->right = s;
				if(s != nil)
					s->parent = rp;
			}
			s = t->left;
			rp->left = s;
			s->parent = rp;
		}
	}
	q = t->parent;
	if(q == nil)
		p->root = rp;
	else {
		if(t == q->left)
			q->left = rp;
		else
			q->right = rp;
	}
	if(rp != nil)
		rp->parent = q;
}

void
pooladd(Pool *p, Bhdr *q)
{
	int size;
	Bhdr *tp, *t;

	q->magic = MAGIC_F;

	q->left = nil;
	q->right = nil;
	q->parent = nil;
	q->fwd = q;
	q->prev = q;

	t = p->root;
	if(t == nil) {
		p->root = q;
		return;
	}

	size = q->size;

	tp = nil;
	while(t != nil) {
		if(size == t->size) {
			q->prev = t->prev;
			q->prev->fwd = q;
			q->fwd = t;
			t->prev = q;
			return;
		}
		tp = t;
		if(size < t->size)
			t = t->left;
		else
			t = t->right;
	}

	q->parent = tp;
	if(size < tp->size)
		tp->left = q;
	else
		tp->right = q;
}

void
poolsummary(void)
{
	int x = 0;
	char buf[400];

	print("\n");
	print("    cursize     maxsize       hw         nalloc       nfree      nbrk       max      name\n");

	x=poolread( buf, sizeof buf - 1, x );
	buf[x] = 0;
	putstrn(buf, x);
	print("\n");
}

void*
poolalloc(Pool *p, uintptr asize)
{
	Bhdr *q, *t;
	intptr alloc, ldr, ns, frag;
	intptr osize, size;
	Prog *prog;

	// if(asize >= 1024*1024*1024)	/* for sanity and to avoid overflow */
	//	return nil;
/*	if(p->cursize > p->ressize &&
		(prog = currun()) != nil &&
		prog->flags&Prestricted){
		print("poolalloc exception\n");
		return nil;
	}*/
	size = asize;
	osize = size;
	size = (size + BHDRSIZE + p->quanta) & ~(p->quanta);

	ilock(&p->l);
	p->nalloc++;

	t = p->root;
	q = nil;
	while(t) {
		if(t->size == size) {
			t = t->fwd;
			pooldel(p, t);
			t->magic = MAGIC_A;
			p->cursize += t->size;
			if(p->cursize > p->hw)
				p->hw = p->cursize;
			iunlock(&p->l);
			return B2D(t);
		}
		if(size < t->size) {
			q = t;
			t = t->left;
		}
		else
			t = t->right;
	}
	if(q != nil) {
		pooldel(p, q);
		q->magic = MAGIC_A;
		frag = q->size - size;
		if(frag < (size>>2) && frag < 0x8000) {
			p->cursize += q->size;
			if(p->cursize > p->hw)
				p->hw = p->cursize;
			iunlock(&p->l);
			return B2D(q);
		}
		/* Split */
		ns = q->size - size;
		q->size = size;
		B2T(q)->hdr = q;
		t = B2NB(q);
		t->size = ns;
		B2T(t)->hdr = t;
		pooladd(p, t);
		p->cursize += q->size;
		if(p->cursize > p->hw)
			p->hw = p->cursize;
		iunlock(&p->l);
		return B2D(q);
	}

	ns = p->chunk;
	if(size > ns)
		ns = size;
	ldr = p->quanta+1;

	alloc = ns+ldr+ldr;
	p->arenasize += alloc;
	if(p->arenasize > p->maxsize) {
		p->arenasize -= alloc;
		ns = p->maxsize-p->arenasize-ldr-ldr;
		ns &= ~p->quanta;
		if (ns < size) {
			if(poolcompact(p)) {
				iunlock(&p->l);
				return poolalloc(p, osize);
			}

			iunlock(&p->l);
			if(p->warn)
				return nil;
			p->warn = 1;
			if (p != mainmem || ns > 512)
				print("arena too large: %s size %zd cursize %zud arenasize %zud maxsize %zud, alloc = %zd\n", p->name, osize, p->cursize, p->arenasize, p->maxsize, alloc);
			return nil;
		}
		alloc = ns+ldr+ldr;
		p->arenasize += alloc;
	}

	p->nbrk++;
	t = xalloc(alloc);
	if(t == nil) {
		p->nbrk--;
		iunlock(&p->l);
		return nil;
	}
	/* Double alignment */
	t = (Bhdr *)(((uintptr)t + 7) & ~7);

	/* TBS xmerge */
	if(0 && p->chain != nil && (char*)t-(char*)B2LIMIT(p->chain)-ldr == 0){
		/* can merge chains */
		if(0)print("merging chains %p and %p in %s\n", p->chain, t, p->name);
		q = B2LIMIT(p->chain);
		q->magic = MAGIC_A;
		q->size = alloc;
		B2T(q)->hdr = q;
		t = B2NB(q);
		t->magic = MAGIC_E;
		p->chain->csize += alloc;
		p->cursize += alloc;
		iunlock(&p->l);
		poolfree(p, B2D(q));		/* for backward merge */
		return poolalloc(p, osize);
	}

	t->magic = MAGIC_E;		/* Make a leader */
	t->size = ldr;
	t->csize = ns+ldr;
	t->clink = p->chain;
	p->chain = t;
	B2T(t)->hdr = t;
	t = B2NB(t);

	t->magic = MAGIC_A;		/* Make the block we are going to return */
	t->size = size;
	B2T(t)->hdr = t;
	q = t;

	ns -= size;			/* Free the rest */
	if(ns > 0) {
		q = B2NB(t);
		q->size = ns;
		B2T(q)->hdr = q;
		pooladd(p, q);
	}
	B2NB(q)->magic = MAGIC_E;	/* Mark the end of the chunk */

	p->cursize += t->size;
	if(p->cursize > p->hw)
		p->hw = p->cursize;
	iunlock(&p->l);
	return B2D(t);
}

void
poolfree(Pool *p, void *v)
{
	Bhdr *b, *c;
	/* extern Bhdr *ptr; defined in libinterp/gc.c */

	D2B(b, v);

	ilock(&p->l);
	p->nfree++;
	p->cursize -= b->size;

	c = B2NB(b);
	if(c->magic == MAGIC_F) {	/* Join forward */
		/*if(c == ptr)
			ptr = b; */
		pooldel(p, c);
		c->magic = 0;
		b->size += c->size;
		B2T(b)->hdr = b;
	}

	c = B2PT(b)->hdr;
	if(c->magic == MAGIC_F) {	/* Join backward */
		/*if(b == ptr)
			ptr = c; */
		pooldel(p, c);
		b->magic = 0;
		c->size += b->size;
		b = c;
		B2T(b)->hdr = b;
	}

	pooladd(p, b);
	iunlock(&p->l);
}

void *
poolrealloc(Pool *p, void *v, uintptr size)
{
	Bhdr *b;
	void *nv;
	intptr osize;

	// if(size >= 1024*1024*1024)	/* for sanity and to avoid overflow */
	//	return nil;
	if(size == 0){
		poolfree(p, v);
		return nil;
	}
	SET(osize);
	if(v != nil){
		ilock(&p->l);
		D2B(b, v);
		osize = b->size - BHDRSIZE;
		iunlock(&p->l);
		if(osize >= size)
			return v;
	}
	nv = poolalloc(p, size);
	if(nv != nil && v != nil){
		memmove(nv, v, osize);
		poolfree(p, v);
	}
	return nv;
}

uintptr
poolmsize(Pool *p, void *v)
{
	Bhdr *b;
	uintptr size;

	if(v == nil)
		return 0;
	ilock(&p->l);
	D2B(b, v);
	size = b->size - BHDRSIZE;
	iunlock(&p->l);
	return size;
}

static uintptr
poolmax(Pool *p)
{
	Bhdr *t;
	uintptr size;

	ilock(&p->l);
	size = p->maxsize - p->cursize;
	t = p->root;
	if(t != nil) {
		while(t->right != nil)
			t = t->right;
		if(size < t->size)
			size = t->size;
	}
	if(size >= BHDRSIZE)
		size -= BHDRSIZE;
	iunlock(&p->l);
	return size;
}

int
poolread(char *va, int count, u64 offset)
{
	Pool *p;
	int n, i, signed_off;

	n = 0;
	signed_off = offset;
	for(i = 0; i < table.n; i++) {
		p = &table.pool[i];
		n += snprint(va+n, count-n, "%11zud %11zud %11zud %11zud %11zud %11d %11zud %s\n",
			p->cursize,
			p->maxsize,
			p->hw,
			p->nalloc,
			p->nfree,
			p->nbrk,
			poolmax(p),
			p->name);

		if(signed_off > 0) {
			signed_off -= n;
			if(signed_off < 0) {
				memmove(va, va+n+signed_off, -signed_off);
				n = -signed_off;
			}
			else
				n = 0;
		}

	}
	return n;
}

/* this function signature is tied to the system's libc.h */
void*
malloc(ulong size)
{
	void *v;

	v = poolalloc(mainmem, size);
	if(v != nil){
		setmalloctag(v, getcallerpc(&size));
		setrealloctag(v, 0);
		memset(v, 0, size);
	}
	return v;
}

void*
smalloc(uintptr size)
{
	void *v;

	for(;;) {
		v = poolalloc(mainmem, size);
		if(v != nil)
			break;
		tsleep(&up->sleep, return0, 0, 100);
	}
	setmalloctag(v, getcallerpc(&size));
	setrealloctag(v, 0);
	memset(v, 0, size);
	return v;
}

void*
mallocz(ulong size, int clr)
{
	void *v;

	v = poolalloc(mainmem, size);
	if(v != nil){
		setmalloctag(v, getcallerpc(&size));
		setrealloctag(v, 0);
		if(clr)
			memset(v, 0, size);
	}
	return v;
}

/* on 9front, mallocalign() returns a pointer to a buffer that
	satisfies the alignment, offset and span requirements.

	As inferno keeps track of buffers at a lesser granularity,
	it is harder to keep track of the small memory areas
	that will have to be skipped for alignment.

	Instead of taking the responsibility of accounting for
	those memory areas, this function returns a buffer
	which will have a pointer that satisfies the size, alignment,
	offset and span requirements. It will be upto the caller
	to use it is wants. When free'ing, it needs to ensure that
	it frees using the Bhdr.u.data pointer and not any other
	pointer in that buffer.

	Alternate implementation:
	The free() function finds the Bhdr that contains the
	pointer being free'ed and frees that Bhdr. This breaks
	the assumption that the pointer passed to free() is
	always Bhdr.u.data.

12:25 < joe7> cinap_lenrek: any comments on this? http://okturing.com/src/11617/body
12:26 < joe7> I have 2 ways of implementing mallocalign on inferno. The second (alternative implementation) approach lies closer to what 9front does.(I think).
12:27 < joe7> just want to run it by you..
12:27 < cinap_lenrek> joe7: obviously you want it to be symmetic
12:27 < cinap_lenrek> like dont push that extra complexity to the caller
12:27 < cinap_lenrek> the rest is just implementation detail
12:28 < joe7> izaki, there is a way to read nvram and secstore keys automatically in the boot process.
12:29 < joe7> cinap_lenrek: so, making the free more robust seems the obvious choice. Instead of assuming that free will always receive the data pointer, we make the assumption that the pointer being freed can be any where in a buffer's data space.
12:30 < cinap_lenrek> no.
12:30 < cinap_lenrek> free needs to be called exactly on the pointer returned from mallocalign
12:30 < joe7> so, someone needs to record the pointer returned by mallocalign..
12:31 < joe7> the allocator only keeps track of the Bhdr's in the Pool structure now.
12:31 < cinap_lenrek> or mark it with a header to find the Bhdr
12:31 < cinap_lenrek> or some padding bytes
12:31 < joe7> good idea, thanks, will think through.
12:32 < cinap_lenrek> i think pool has align magic for this
12:32 < cinap_lenrek> so free is kind of search for the Bhdr
12:32 < cinap_lenrek> but thats an implementation details
12:33 < cinap_lenrek> but calling free() on something other than the pointer returned by mallocalign should be undefined
12:33 < cinap_lenrek> and you shouldnt rely on it
 */
static void*
alignptr(void *v, u32 align, s32 offset)
{
	char *c;
	u32 off;

	c = v;
	if(align){
		off = ((u32)(uintptr)c) % align;
		if(off != offset){
			offset -= off;
			if(offset < 0)
				offset += align;
			c += offset;
		}
	}
	return c;
}
void*
mallocalign(uintptr dsize, u32 align, s32 offset, u32 span)
{
	uintptr asize;
	void *v;
	char *c;
	int skip;
	Balign *ba;
	Bhdr *b;

	/*
	 * allocate block
	 * 	dsize bytes
	 *	addr == offset (modulo align)
	 *	does not cross span-byte block boundary
	 *
	 * to satisfy alignment, just allocate an extra
	 * align bytes and then shift appropriately.
	 *
	 * to satisfy span, try once and see if we're
	 * lucky.  the second time, allocate 2x asize
	 * so that we definitely get one not crossing
	 * the boundary.
	 */
	if(align){
		if(offset < 0)
			offset = align - ((-offset)%align);
		offset %= align;
	}
	asize = dsize+align+sizeof(Balign);
	v = mallocz(asize, 1);
	if(v == nil)
		return nil;
	if(span && (uintptr)v/span != ((uintptr)v+asize)/span){
		/* try again */
		free(v);
		v = mallocz(2*asize, 1);
		if(v == nil)
			return nil;
	}

	/*
	 * figure out what pointer we want to return
	 */
	c = alignptr(v, align, offset);
	if(span && (uintptr)c/span != (uintptr)(c+dsize-1)/span){
		c += span - (uintptr)c%span;
		c = alignptr(c, align, offset);
		if((uintptr)c/span != (uintptr)(c+dsize-1)/span){
			free(v);
			werrstr("cannot satisfy dsize %lud span %lud with align %lud+%ld", dsize, span, align, offset);
			return nil;
		}
	}
	skip = c - (char*)v;
	if(skip == 0){ /* perfect match, Hallelujah */
		return c;
	}else if (skip < sizeof(Balign)){
		/* TODO this situation should be handled, error for now */
		werrstr("skip %d < sizeof(Balign) %d cannot satisfy dsize %lud span %lud with align %lud+%ld", skip, sizeof(Balign), dsize, span, align, offset);
		return nil;
	}else{
		/* add the Balign header to point back to the header */
		ba = (Balign*)(c-sizeof(Balign));
		D2B(b,v);
		ba->hdr = b;
		setmalloctag(v, getcallerpc(&dsize));
		if(0)print("mallocalign dsize %zd align %d 0x%x offset %d span %d\n"
			"	b 0x%p b->magic 0x%x b->size %zd\n"
			"	ba 0x%p ba->hdr 0x%p v 0x%p c 0x%p\n",
			dsize, align, align, offset, span, b, b->magic, b->size,
			ba, ba->hdr, v, c);
		return c;
	}
}

void
free(void *v)
{
	Bhdr *b;

	if(v != nil) {
		D2B(b, v);
		poolfree(mainmem, v);
	}
}

/* this function signature is tied to emu which is tied to the system's libc.h */
void*
realloc(void *v, ulong size)
{
	void *nv;

	if(size == 0)
		return malloc(size);	/* temporary change until realloc calls can be checked */
	nv = poolrealloc(mainmem, v, size);
	if(nv != nil) {
		nv = (uintptr*)nv;
		setrealloctag(nv, getcallerpc(&v));
		if(v == nil)
			setmalloctag(v, getcallerpc(&v));
	}
	return nv;
}

void
setmalloctag(void *v, uintptr pc)
{
	Bhdr *b;

	if(v != nil){
		D2B(b, v);
		b->allocpc = pc;
	}
}

uintptr
getmalloctag(void *v)
{
	Bhdr *b;

	if(v == nil)
		return ~0;
	D2B(b, v);
	return b->allocpc;
}

void
setrealloctag(void *v, uintptr pc)
{
	Bhdr *b;

	if(v != nil){
		D2B(b, v);
		b->reallocpc = pc;
	}
}

uintptr
getrealloctag(void *v)
{
	Bhdr *b;

	if(v == nil)
		return ~0;
	D2B(b, v);
	return b->reallocpc;
}

ulong
msize(void *v)
{
	if(v == nil)
		return 0;
	return poolmsize(mainmem, v);
}

/* this function signature is tied to emu which is tied to the system's libc.h */
void*
calloc(ulong n, ulong szelem)
{
	return malloc(n*szelem);
}

void
pooldump(Bhdr *b, int d, int c)
{
	Bhdr *t;

	if(b == nil)
		return;

	print("%.8p %.8p %.8p %c %4d %zud (f %.8p p %.8p)\n",
		b, b->left, b->right, c, d, b->size, b->fwd, b->prev);
	d++;
	for(t = b->fwd; t != b; t = t->fwd)
		print("\t%.8p %.8p %.8p\n", t, t->prev, t->fwd);
	pooldump(b->left, d, 'l');
	pooldump(b->right, d, 'r');
}

void
poolshow(void)
{
	int i;

	for(i = 0; i < table.n; i++) {
		print("Arena: %s root=%.8p\n", table.pool[i].name, table.pool[i].root);
		pooldump(table.pool[i].root, 0, 'R');
	}
}

void
poolsetcompact(Pool *p, void (*move)(void*, void*))
{
	p->move = move;
}

int
poolcompact(Pool *pool)
{
	Bhdr *base, *limit, *ptr, *end, *next;
	int compacted, nb;

	if(pool->move == nil || pool->lastfree == pool->nfree)
		return 0;

	pool->lastfree = pool->nfree;

	base = pool->chain;
	ptr = B2NB(base);	/* First Block in arena has clink */
	limit = B2LIMIT(base);
	compacted = 0;

	pool->root = nil;
	end = ptr;
	while(base != nil) {
		next = B2NB(ptr);
		if(ptr->magic == MAGIC_A || ptr->magic == MAGIC_I) {
			if(ptr != end) {
				memmove(end, ptr, ptr->size);
				pool->move(B2D(ptr), B2D(end));
				compacted = 1;
			}
			end = B2NB(end);
		}
		if(next >= limit) {
			nb = (uchar*)limit - (uchar*)end;
			if(nb > 0){
				if(nb < pool->quanta+1)
					panic("poolcompact: leftover too small\n");
				end->size = nb;
				B2T(end)->hdr = end;
				pooladd(pool, end);
			}
			base = base->clink;
			if(base == nil)
				break;
			ptr = B2NB(base);
			end = ptr;	/* could do better by copying between chains */
			limit = B2LIMIT(base);
		} else
			ptr = next;
	}

	return compacted;
}

void
poolsize(Pool *p, uintptr max, int contig)
{
	void *x;

	print("poolsize max %llud contig %d\n", max, contig);
	p->maxsize = max;
	if(max == 0)
		p->ressize = max;
	else if(max < RESERVED)
		p->ressize = max;
	else
		p->ressize = max-RESERVED;
	if (contig && max > 0) {
		p->chunk = max-1024;
		print("poolsize: poolalloc() contig chunk 0x%zx %zd\n", p->chunk, p->chunk);
		x = poolalloc(p, p->chunk);
		if(x == nil)
			panic("poolsize: don't have %d bytes\n", p->chunk);
		print("poolsize: before poolfree()\n");
		poolfree(p, x);
		print("poolsize: after poolfree()\n");
		p->hw = 0;
	}
}

static void
_poolfault(void *v, char *msg, uintptr c)
{
	auditmemloc(msg, v);
	panic("%s %p (from %p/%zux)", msg, v, getcallerpc(&v), c);
}

static void
dumpvl(char *msg, uintptr *v, int n)
{
	int i, l;

	l = print("%s at %p: ", msg, v);
	for(i = 0; i < n; i++) {
		if(l >= 60) {
			print("\n");
			l = print("    %p: ", v);
		}
		l += print(" %zux", *v++);
	}
	print("\n");
	USED(l);
}

static void
corrupted(char *str, char *msg, Pool *p, Bhdr *b, void *v)
{
	print("%s(%p): pool %s CORRUPT: %s at %p'%zud(magic=%ux)\n",
		str, v, p->name, msg, b, b->size, b->magic);
	dumpvl("bad Bhdr", (uintptr *)((uintptr)b & ~3)-4, 10);
}

static void
_auditmemloc(char *str, void *v)
{
	Pool *p;
	Bhdr *bc, *ec, *b, *nb, *fb = nil;
	char *fmsg, *msg;
	uintptr fsz;

	SET(fsz, fmsg, nb);
	for (p = &table.pool[0]; p < &table.pool[nelem(table.pool)]; p++) {
		ilock(&p->l);
		for (bc = p->chain; bc != nil; bc = bc->clink) {
			if (bc->magic != MAGIC_E) {
				iunlock(&p->l);
				corrupted(str, "chain hdr!=MAGIC_E", p, bc, v);
				goto nextpool;
			}
			ec = B2LIMIT(bc);
			if (((Bhdr*)v >= bc) && ((Bhdr*)v < ec)){
				goto found;
			}
		}
		iunlock(&p->l);
nextpool:	;
	}
	print("%s: %lux not in pools\n", str, v);
	return;

found:
	for (b = bc; b < ec; b = nb) {
		switch(b->magic) {
		case MAGIC_F:
			msg = "free blk";
			break;
		case MAGIC_I:
			msg = "immutable block";
			break;
		case MAGIC_A:
			msg = "block";
			break;
		default:
			if (b == bc && b->magic == MAGIC_E) {
				msg = "pool hdr";
				break;
			}
			iunlock(&p->l);
			corrupted(str, "bad magic", p, b, v);
			goto badchunk;
		}
		if (b->size <= 0 || (b->size & p->quanta)) {
			iunlock(&p->l);
			corrupted(str, "bad size", p, b, v);
			goto badchunk;
		}
		if (fb != nil)
			break;
		nb = B2NB(b);
		if ((Bhdr*)v < nb) {
			fb = b;
			fsz = b->size;
			fmsg = msg;
		}
	}
	iunlock(&p->l);
	if (b >= ec) {
		if (b > ec)
			corrupted(str, "chain size mismatch", p, b, v);
		else if (b->magic != MAGIC_E)
			corrupted(str, "chain end!=MAGIC_E", p, b, v);
	}
badchunk:
	if (fb != nil) {
		print("%s: %p in %s:", str, v, p->name);
		if (fb == v)
			print(" is %s '%zux\n", fmsg, fsz);
		else
			print(" in %s at %p B2D 0x%p size %zux ec 0x%p next block 0x%p searched address 0x%p\n",
				fmsg, fb, B2D(fb), fsz, ec, nb, v);
		dumpvl("area", (uintptr *)((uintptr)v & ~3)-4, 20);
	}
}

char *
poolaudit(char*(*audit)(int, Bhdr *))
{
	Pool *p;
	Bhdr *bc, *ec, *b;
	char *r = nil;

	for (p = &table.pool[0]; p < &table.pool[nelem(table.pool)]; p++) {
		ilock(&p->l);
		for (bc = p->chain; bc != nil; bc = bc->clink) {
			if (bc->magic != MAGIC_E) {
				iunlock(&p->l);
				return "bad chain hdr";
			}
			ec = B2LIMIT(bc);
			for (b = bc; b < ec; b = B2NB(b)) {
				if (b->size <= 0 || (b->size & p->quanta))
					r = "bad size in bhdr";
				else
					switch(b->magic) {
					case MAGIC_E:
						if (b != bc) {
							r = "unexpected MAGIC_E";
							break;
						}
					case MAGIC_F:
					case MAGIC_A:
					case MAGIC_I:
						r = audit(p->pnum, b);
						break;
					default:
						r = "bad magic";
					}
				if (r != nil) {
					iunlock(&p->l);
					return r;
				}
			}
			if (b != ec || b->magic != MAGIC_E) {
				iunlock(&p->l);
				return "bad chain ending";
			}
		}
		iunlock(&p->l);
	}
	return r;
}

/*
void
poolinit(void)
{
	debugkey('m', "memory pools", poolsummary, 0);
}
*/