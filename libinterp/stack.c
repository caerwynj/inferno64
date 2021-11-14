#include "lib9.h"
#include "isa.h"
#include "interp.h"
#include "raise.h"
#include <pool.h>

static int debug = 0;

#define T(r)	*((void**)(R.r))

/* same as the one in xec.c */
void
showframe(void *v, void *vt)
{
	uchar *p;
	int i, j;
	Frame *f;
	Type *t;

	f = (Frame*) v;
	t = (Type*) vt;
	print("frame 0x%p type 0x%p t->size %d t->np %d t->map \"",
		v, vt, t->size, t->np);
	for(p = t->map; p < t->map+t->np; p++)
		print(" %.2x", *p);
	print("\"\n");
	for(i = 0; i < t->size/(sizeof(intptr)); i++){
		print("\t%d %d 0x%p\t%zx\t",
			i, i*sizeof(intptr), (intptr*)f+i, *((intptr*)f+i));
		for(j = 0; j < sizeof(intptr); j++){
			print(" %d=0x%02x", j, *((uchar*)f+i*sizeof(intptr)+j));
		}
		print("\n");
	}
}

void
newstack(Prog *p)
{
	int l;
	Type *t;
	Frame *f;
	Stkext *ns;

	f = T(s);

	t = f->t;
	if(t == nil)
		t = SEXTYPE(f)->reg.TR;

	f->lr = nil;
	f->mr = nil;
	f->fp = nil;
	l = p->R.M->m->ss;
	/* 16 bytes for Stkext record keeping
		changed to 40 bytes for amd64 */
	if(l < t->size+sizeof(Stkext))
		l = t->size+sizeof(Stkext);
	ns = mallocz(l, 0);
	if(ns == nil)
		error(exNomem);

	ns->reg.TR = t;
	ns->reg.SP = nil;
	ns->reg.TS = nil;
	ns->reg.EX = nil;
	p->R.EX = ns->stack;
	p->R.TS = ns->stack + l;
	p->R.SP = ns->reg.tos.fu + t->size;
	p->R.FP = ns->reg.tos.fu;

	DBG("newstack R.EX stack extend 0x%p\n"
		"\tTR type register 0x%p R.SP 0x%p R.TS top of stack 0x%p\n"
		"\tR.FP=0x%p R.SP-R.FP=%zd t->size=%d called by 0x%p\n",
		p->R.EX, ns->reg.TR,
		p->R.SP, p->R.TS,
		p->R.FP, p->R.SP - p->R.FP, t->size, getcallerpc(&p));
	memmove(p->R.FP, f, t->size);
	f = (Frame*)p->R.FP;
	f->t = nil;
}

void
extend(void)
{
	int l;
	Type *t;
	Frame *f;
	Stkext *ns;

	t = R.s;
	l = R.M->m->ss;
	/* 16 bytes for Stkext record keeping
		changed to 40 bytes for amd64 */
	if(l < t->size+sizeof(Stkext))
		l = 2*t->size+sizeof(Stkext);
	ns = mallocz(l, 0);
	if(ns == nil)
		error(exNomem);

	ns->reg.TR = t;
	ns->reg.SP = R.SP;
	ns->reg.TS = R.TS;
	ns->reg.EX = R.EX;
	f = ns->reg.tos.fr;
	f->t  = nil;
	f->mr = nil;
	R.s = f;
	R.EX = ns->stack;
	R.TS = ns->stack + l;
	R.SP = ns->reg.tos.fu + t->size;
	if (t->np)
		initmem(t, f);
}

void
unextend(Frame *f)
{
	Stkext *sx;
	Type *t;

	sx = SEXTYPE(f);
	R.SP = sx->reg.SP;
	R.TS = sx->reg.TS;
	R.EX = sx->reg.EX;
	t = sx->reg.TR;
	if (t->np)
		freeptrs(f, t);
	free(sx);
}

void
unframe(void)
{
	Type *t;
	Frame *f;
	Stkext *sx;

	f = (Frame*)R.FP;
	t = f->t;
	if(t == nil)
		t = SEXTYPE(f)->reg.TR;

	R.SP = R.FP+t->size;

	f = T(s);
	if(f->t == nil) {
		sx = SEXTYPE(f);
		R.TS = sx->reg.TS;
		R.EX = sx->reg.EX;
		free(sx);
	}
}
