#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

static int debug = 0;

/*
 1. Provides #h/shm for shared user memory
How is this different from devshm?
	O(1) for read and write
	Behaves like a pipe after the current version and len are read.
	Any further reads block until new data is written
	using array index as the path to keep lookups to O(1)
	Keep c->aux = Svalue*
		So, can read/write directly
TODO
	needs some mechanism in devforth.c to create up->shm

up->shm = Shmgrp*
c->aux (for QTFile) = Svalue*
c->qid.path = array index of Svalue* in Sgrp.ent[] +1
 */
enum
{
	DELTAENV = 32,
};

/*
struct Qid
{
	u64	path; == array index of Svalue* in ent +1
	u32	vers; for version control
	uchar	type; QTFILE | QTDIR;
} Qid;
also, keeping Chan.aux = for QTFILE, Svalue*. For QTDIR, Sgrp (up->shm).

gen()
walk()	rlock() group
create()	wlock() group
					reuse any value with ref == 0 and dead == 1 before realloc
				incref() on the opened value
open()		incref() on the opened value
read()		rlock() on value
stat()		same as read()
write()		wlock() on value
close()		decref() on the closed value
				wlock() value
					if dead == 1 and ref == 0, free name, value and Svalue
				wlock() group. set array entry to nil
remove()	wlock() value
				set dead = 1
				if ref == 0, free name, value and Svalue
				wlock() group. set array entry to nil

newforthproc() when it uses an Sgrp, incref's
when closing, decref's and closes Sgrp when ref == 0
		remove() all values
			if successful, then free Sgrp
 */

/*
 * shared memory data structures. Modeled after Egrp.
 */
typedef struct Svalue Svalue;
struct Svalue
{
	Ref;
	RWlock;
	char	*name;
	char	*value;
	s32	len;
	s32 vers;
};

typedef struct Sgrp Sgrp;
struct Sgrp
{
	Ref;
	RWlock;
	union{		/* array of Svalue pointers */
		Svalue	*entries;
		Svalue	*ent;
	};
	int	nent;	/* number of entries used */
	int	ment;	/* maximum number of entries */
	u32	vers;	/* of Sgrp */
};

static Svalue*
shmlookupname(Sgrp *g, char *name)
{
	Svalue *v, *ev;

	if(name == nil)
		return nil;

	v = g->ent;
	for(ev = v + g->nent; v < ev; v++){
		if(name[0] == v->name[0] && strcmp(v->name, name) == 0))
			return v;
	}
	return nil;
}

static Svalue*
shmlookuppath(Sgrp *g, s64 qidpath)
{
	Svalue *v, *ev;

	if(qidpath == -1)
		return nil;
	if(qidpath > g->nent)
		return nil;

	return g->ent[qidpath-1];
}

/* same as envlookup */
static Evalue*
shmlookup(Sgrp *g, char *name, s64 qidpath)
{
	if(qidpath != -1)
		return shmlookuppath(sg, qidpath);

	if(name != nil)
		return shmlookupname(sg, name);

	return nil;
}

static s32
shmlookupidx(Sgrp *g, char *name)
{
	Svalue *v, *ev;
	s32 i;

	if(name == nil)
		return -1;

	for(i = 0, v = g->ent; i < g->nent; i++, v++){
		if(name[0] == v->name[0] && strcmp(v->name, name) == 0))
			return i;
	}
	return -1;
}

/* the caller should rlock() the Sgrp */
static int
shmgen(Chan *c, char *name, Dirtab*, int, int s, Dir *dp)
{
	Sgrp *g;
	Svalue *v;
	Qid q;
	s32 i;

	if(s == DEVDOTDOT){
		devdir(c, c->qid, "#s", 0, eve, 0775, dp);
		return 1;
	}

	if((g = up->shm) == nil)
		return -1;

	i = -1;
	if(name != nil)
		i = shmlookupidx(g, name);
	if((name == nil || i == -1) && s <= g->nent)
		i = s;
	if(i == -1)
		return -1;

	v = g->ent[i];
	if(v == nil || name != nil && (strlen(v->name) >= sizeof(up->genbuf))) {
		return -1;
	}

	/* make sure name string continues to exist after we release lock */
	kstrcpy(up->genbuf, v->name, sizeof up->genbuf);
	mkqid(&q, i+1, v->vers, QTFILE);
	devdir(c, q, up->genbuf, v->len, eve, 0664, dp);
	return 1;
}

static Chan*
shmattach(char *spec)
{
	Chan *c;
	Sgrp *g;

	if(up->shm == nil)
		error(Enonexist);

	c = devattach('h', spec);
	mkqid(&c->qid, 0, 0, QTDIR);
	c->aux = up->shm;
	return c;
}

/* also sets walked Chan.aux to Svalue* */
static Walkqid*
shmwalk(Chan *c, Chan *nc, char **name, int nname)
{
	Walkqid *wq;

	rlock(up->shm);
	wq = devwalk(c, nc, name, nname, 0, 0, shmgen);
	if(wq != nil && wq->clone != nil && wq->clone != c){
		wq->clone->aux = up->shm->ent[wq->clone->qid.path-1];
		DBG("shmwalk wq->clone->path %s mode 0x%ux\n"
			"	wq->clone->qid.path 0x%zux wq->clone->qid.vers %d\n"
			"	wq->clone->qid.type %d 0x%ux\n"
			"	wq->clone->aux 0x%zx\n",
			chanpath(nc), wq->clone->mode,
			wq->clone->qid.path, wq->clone->qid.vers,
			wq->clone->qid.type, wq->clone->qid.type,
			wq->clone->aux);
	}
	runlock(up->shm);
	return wq;
}

static int
shmstat(Chan *c, uchar *db, int n)
{
	Sgrp *g;
	int s;

	if((g = up->shm) == nil)
		error(Enonexist);

	if(c->qid.type & QTDIR)
		c->qid.vers = g->vers;

	rlock(g);
	s = devstat(c, db, n, 0, 0, shmgen);
	runlock(g);
	return s;
}

static Chan*
shmopen(Chan *c, u32 omode)
{
	Sgrp *g;
	Svalue *v;
	int trunc;

	if((g = up->shm) == nil)
		error(Enonexist);

	if(c->qid.type & QTDIR) {
		if(omode != OREAD)
			error(Eperm);
	}
	else {
		trunc = omode & OTRUNC;
		if(omode != OREAD && shmwriteable(c) == 0)
			error(Eperm);
		if(trunc)
			wlock(g);
		else
			rlock(g);

		v = c->aux;
		if(v == nil) {
			if(trunc)
				wunlock(g);
			else
				runlock(g);
			error(Enonexist);
		}
		if(trunc && v->value != nil) {
			v->vers++;
			free(v->value);
			v->value = nil;
			v->len = 0;
		}
		if(trunc)
			wunlock(g);
		else
			runlock(g);
	}
	c->mode = openmode(omode);
	incref(v);
	c->offset = 0;
	c->flag |= COPEN;
	return c;
}

static void
shmcreate(Chan *c, char *name, u32 omode, u32)
{
	Sgrp *g;
	Svalue *v, *ev;
	s32 i;

	if(c->qid.type != QTDIR || shmwriteable(c) == 0)
		error(Eperm);

	if(strlen(name) >= sizeof(up->genbuf))
		error(Etoolong);

	if((g = up->shm) == nil)
		error(Enonexist);

	omode = openmode(omode);

	wlock(g);
	if(waserror()) {
		wunlock(g);
		nexterror();
	}

	if(shmlookup(g, name, -1) != nil)
		error(Eexist);

	if(g->nent == g->ment){
		Evalue *tmp;

		g->ment += DELTAENV;
		if((tmp = realloc(g->ent, sizeof(intptr)*g->ment)) == nil){
			g->ment -= DELTAENV;
			error(Enomem);
		}
		g->ent = tmp;
	}
	g->vers++;
	/* find any remove'd entries to reuse */
	for(i = 0; i < g->nent; i++){
		if(g->ent[i] == nil)
			goto found;
	}
	i = g->nent;
	g->nent++;
found:
	v = smalloc(sizeof(Svalue));
	v->value = nil;
	v->len = v->vers = 0;
	v->name = smalloc(strlen(name)+1);
	strcpy(v->name, name);
	mkqid(&c->qid, i+1, 0, QTFILE);
	incref(v);
	g->ent[i] = v;
	wunlock(g);
	poperror();

	c->aux = v;
	c->offset = 0;
	c->mode = omode;
	c->flag |= COPEN;
	return;
}

/*
when offset > len, return 0
if offset == 0 and c->qid.vers == Tag.vers,
	block
 */
shmread(Chan *c, void *a, s32 n, s64 off)
{
	Sgrp *g;
	Svalue *v;
	u64 offset = off;

	if(c->qid.type & QTDIR)
		return devdirread(c, a, n, 0, 0, shmgen);

	if((g = up->shm) == nil)
		error(Enonexist);

	if((v = c->aux) == nil || v->dead == 1)
		error(Enonexist);

	rlock(v);
	if(offset >= v->len || v->value == nil)
		n = 0;
	else if(offset + n > v->len)
		n = v->len - offset;
	if(n <= 0)
		n = 0;
	else
		memmove(a, v->value+offset, n);
	c->qid.vers = v->qid.vers;
	runlock(v);

	return n;
}

static s32
shmwrite(Chan *c, void *a, s32 n, s64 off)
{
	char *s;
	ulong len;
	Sgrp *eg;
	Svalue *e;
	u64 offset = off;

	if(n <= 0)
		return 0;
	if(offset > Maxshmsize || n > (Maxshmsize - offset))
		error(Etoobig);

	if((g = up->shm) == nil)
		error(Enonexist);

	if((v = c->aux) == nil || v->dead == 1)
		error(Enonexist);

	wlock(v);
	len = offset+n;
	if(len > e->len) {
		s = realloc(e->value, len);
		if(s == nil){
			wunlock(v);
			error(Enomem);
		}
		memset(s+offset, 0, n);
		v->value = s;
		v->len = len;
	}
	memmove(v->value+offset, a, n);
	v->vers++;
	c->qid.vers = v->vers;
	wunlock(v);

	return n;
}

static void
shmclose(Chan *c)
{
	Sgrp *g;
	Svalue *v;
	s32 d;

	if(c->qid.type & QTDIR)
		return;

	if((g = up->shm) == nil)
		error(Enonexist);

	if((v = c->aux) == nil)
		error(Enonexist);

	d = decref(v);

	if(v->dead == 1 && d <= 0){
		shmremove(c);
	}
	if(c->flag & COPEN){
		/*
		 * cclose can't fail, so errors from remove will be ignored.
		 * since permissions aren't checked,
		 * shmremove can't not remove it if its there.
		 */
		if(c->flag & CRCLOSE && !waserror()){
			shmremove(c);
			poperror();
		}
	}
}

static void
shmremove(Chan *c)
{
	Sgrp *eg;
	Svalue *e;

	if(c->qid.type & QTDIR)
		return;

	if((g = up->shm) == nil)
		error(Enonexist);

	if((v = c->aux) == nil)
		error(Enonexist);

	wlock(v);
	v->dead = 1;
	if(v->r.ref > 0){
		wunlock(v);
		return;
	}
	if(v->name != nil)
		free(v->name);
	if(v->value != nil)
		free(v->value);
	wunlock(v);

	wlock(g);
	g->ent[c->qid.path-1] = nil;
	free(v);
	wunlock(g);
}

Dev shmdevtab = {
	'h',
	"shm",

	devreset,
	devinit,
	devshutdown,
	shmattach,
	shmwalk,
	shmstat,
	shmopen,
	shmcreate,
	shmclose,
	shmread,
	devbread,
	shmwrite,
	devbwrite,
	shmremove,
	devwstat
};

/*
 * kernel interface to shmironment variables
 */
Sgrp*
newshmgrp(void)
{
	Sgrp	*e;

	e = smalloc(sizeof(Sgrp));
	incref(e);
	return e;
}

void
closesgrp(Sgrp *g)
{
	Svalue *v, *ev;

	if(g == nil)
		return;
	if(decref(eg) == 0){
		v = g->ent;
		for(i = 0, ev = v + g->nent; v < ev; v++, i++){
			if(v == nil)
				continue;
			wlock(v);
			free(v->name);
			free(v->value);
			g->ent[i] = nil;
			/* wunlock(v); */
			free(v);
		}
		free(g->ent);
		free(g);
	}
}

static int
shmwriteable(Chan *c)
{
	return c->aux == nil || c->aux == up->shm;
}

/* same as shmcpy() of 9front */
void
sgrpcpy(Sgrp *to, Sgrp *from)
{
	Svalue *e, *ee, *ne;

	rlock(from);
	to->ment = ROUND(from->nent, DELTAENV);
	to->ent = smalloc(to->ment*sizeof(to->ent[0]));
	ne = to->ent;
	e = from->ent;
	for(ee = e + from->nent; e < ee; e++, ne++){
		ne->name = smalloc(strlen(e->name)+1);
		strcpy(ne->name, e->name);
		if(e->value != nil){
			ne->value = smalloc(e->len);
			memmove(ne->value, e->value, e->len);
			ne->len = e->len;
		}
		mkqid(&ne->qid, ++to->path, 0, QTFILE);
	}
	to->nent = from->nent;
	runlock(from);
}

