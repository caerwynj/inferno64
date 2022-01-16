#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

static int debug = 0;

/*
 1. Provides #h/shm for shared user memory
 2. similar to env(3)

How is this different from devenv?
	O(1) for read and write
	using array index as the path to keep lookups to O(1)
	Keep c->aux = Svalue*
		So, can read/write directly
	attach() incref's Sgrp
	open() incref's Svalue
	close() decref's Svalue
	If the length is greater than 1 read/write IO unit, then
		this mechanism fails. Need an shmbig that puts rlock/wlock
		at open() for that to work.

TODO
	needs some mechanism in devforth.c to create up->shm - attach() and up->shm == nil
	kcreate() binding
	forth: test
		create write close
		open read close
	error if iounit(0 fd) > len

not doing
	Behaves like a pipe after the current version and len are read.
	Any further reads block until new data is written
		not doing this. If a pipe is needed, use a pipe

up->shm = Shmgrp*
c->aux (for QTFile) = Svalue*
c->qid.path = array index of Svalue* in Sgrp.ent[]
 */
enum
{
	DELTAENV = 32,
	Maxshmsize = 1024,
};

/*
struct Qid
{
	u64	path; == array index of Svalue* in ent
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

For shmbig:
open(WRITE)	wlock()
open(READ)	rlock()
open(RDWR)	wlock()
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
	u8 dead;	/* set by remove() */
};

typedef struct Sgrp Sgrp;
struct Sgrp
{
	Ref;
	RWlock;
	union{		/* array of Svalue pointers */
		Svalue	**entries;
		Svalue	**ent;
	};
	int	nent;	/* number of entries used */
	int	ment;	/* maximum number of entries */
	u32	vers;	/* of Sgrp */
};

Sgrp* newshmgrp(void);
static int shmwriteable(Chan *c);

static Svalue*
shmlookupname(Sgrp *g, char *name)
{
	Svalue **ent, **eent;

	if(name == nil)
		return nil;

	ent = g->ent;
	for(eent = ent + g->nent; ent < eent; ent++){
		if(name[0] == (*ent)->name[0] && strcmp((*ent)->name, name) == 0)
			return *ent;
	}
	return nil;
}

static Svalue*
shmlookuppath(Sgrp *g, s64 qidpath)
{
	if(qidpath == -1)
		return nil;
	if(qidpath >= g->nent)
		return nil;

	return g->ent[qidpath];
}

/* same as envlookup */
static Svalue*
shmlookup(Sgrp *g, char *name, s64 qidpath)
{
	if(qidpath != -1)
		return shmlookuppath(g, qidpath);

	if(name != nil)
		return shmlookupname(g, name);

	return nil;
}

static s32
shmlookupidx(Sgrp *g, char *name)
{
	Svalue **ent;
	s32 i;

	if(name == nil)
		return -1;

	for(i = 0, ent = g->ent; i < g->nent; i++, ent++){
		if(name[0] == (*ent)->name[0] && strcmp((*ent)->name, name) == 0)
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
		devdir(c, c->qid, "#h", 0, eve, 0775, dp);
		return 1;
	}

	if((g = up->shm) == nil)
		return -1;

	i = -1;
	rlock(g);
	if(name != nil){
		i = shmlookupidx(g, name);
	}
	if(i == -1 && s >= 0 && s < g->nent)
		i = s;
	if(i == -1 || i >= g->nent){
		runlock(g);
		return -1;
	}

	v = g->ent[i];
	if(v == nil || name != nil && (strlen(v->name) >= sizeof(up->genbuf))) {
		runlock(g);
		return -1;
	}

	/* make sure name string continues to exist after we release lock */
	kstrcpy(up->genbuf, v->name, sizeof up->genbuf);
	mkqid(&q, i, v->vers, QTFILE);
	devdir(c, q, up->genbuf, v->len, eve, 0664, dp);
	return 1;
}

static Chan*
shmattach(char *spec)
{
	Chan *c;

	if(up->shm == nil)
		up->shm = newshmgrp();

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

	wq = devwalk(c, nc, name, nname, 0, 0, shmgen);
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

	s = devstat(c, db, n, 0, 0, shmgen);
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
		c->mode = openmode(omode);
		c->offset = 0;
		c->flag |= COPEN;
		return c;
	}

	trunc = omode & OTRUNC;
	if(omode != OREAD && shmwriteable(c) == 0)
		error(Eperm);
	if(trunc)
		wlock(g);
	else
		rlock(g);

	c->aux = v = shmlookuppath(g, c->qid.path);
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

	c->mode = openmode(omode);
	incref(v);
	c->offset = 0;
	c->flag |= COPEN;
	return c;
}

static void
shmcreate(Chan *c, char *name, u32 omode, u32 perm)
{
	Sgrp *g;
	Svalue *v;
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
		Svalue **tmp;

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
		if(((Svalue*)g->ent[i]) == nil)
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
	mkqid(&c->qid, i, 0, QTFILE);
	incref(v);
	g->ent[i] = v;
	wunlock(g);
	poperror();

	c->aux = v;
	c->offset = 0;
	c->mode = omode;
	c->flag |= COPEN;
print("devshm: created c->type %d devtab[c->type]->dc %c chanpath(c) %s c->qid.path 0x%ux c->qid.type 0x%ux\n",
	c->type, devtab[c->type]->dc, chanpath(c), c->qid.path, c->qid.type);
	return;
}

/*
when offset > len, return 0
if offset == 0 and c->qid.vers == Tag.vers,
	block
 */
shmread(Chan *c, void *a, s32 n, s64 off)
{
	Svalue *v;
	u64 offset = off;

	if(up->shm == nil)
		error(Enonexist);

	if(c->qid.type & QTDIR)
		return devdirread(c, a, n, 0, 0, shmgen);

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
	c->qid.vers = v->vers;
	runlock(v);

	return n;
}

static s32
shmwrite(Chan *c, void *a, s32 n, s64 off)
{
	char *s;
	ulong len;
	Svalue *v;
	u64 offset = off;

	if(n <= 0)
		return 0;
	if(offset > Maxshmsize || n > (Maxshmsize - offset))
		error(Etoobig);

	if(up->shm == nil)
		error(Enonexist);

	if((v = c->aux) == nil || v->dead == 1)
		error(Enonexist);

	wlock(v);
	len = offset+n;
	if(len > v->len) {
		s = realloc(v->value, len);
		if(s == nil){
			wunlock(v);
			error(Enomem);
		}
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
shmremove(Chan *c)
{
	Sgrp *g;
	Svalue *v;

	if(c->qid.type & QTDIR)
		return;

	if((g = up->shm) == nil)
		error(Enonexist);

	if((v = c->aux) == nil)
		error(Enonexist);

	wlock(v);
	v->dead = 1;
	if(v->ref > 0){
		wunlock(v);
		return;
	}
	if(v->name != nil)
		free(v->name);
	if(v->value != nil)
		free(v->value);
	wunlock(v);

	wlock(g);
	g->ent[c->qid.path] = nil;
	free(v);
	wunlock(g);
}

static void
shmclose(Chan *c)
{
	Svalue *v;
	s32 d;

	if(c->qid.type & QTDIR)
		return;

	if(up->shm == nil)
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
	Svalue **ent, **eent;
	s32 i;

	if(g == nil)
		return;
	if(decref(g) <= 0){
		ent = g->ent;
		for(i = 0, eent = ent + g->nent; ent < eent; ent++, i++){
			if(ent == nil)
				continue;
			wlock(*ent);
			free((*ent)->name);
			free((*ent)->value);
			g->ent[i] = nil;
			/* wunlock(ent); */
			free(ent);
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

/* same as shmcpy() of 9front, a simpler fork()(?) */
/* TODO void
sgrpcpy(Sgrp *to, Sgrp *from)
{
	Svalue **e, **ee, **ne, *v, *nv;

	rlock(from);
	to->ment = ROUND(from->nent, DELTAENV);
	to->ent = smalloc(to->ment*sizeof(to->ent[0]));
	ne = to->ent;
	e = from->ent;
	for(ee = e + from->nent; e < ee; e++, ne++){
		v = *e;
		nv = smalloc(sizeof(Svalue));
		(*ne) = nv;
		nv->name = smalloc(strlen(v->name)+1);
		strcpy(nv->name, v->name);
		if((v->len > 0){
			nv->value = smalloc(v->len);
			memmove(nv->value, v->value, v->len);
			nv->len = v->len;
		}
		mkqid(&ne->qid, ++to->path, 0, QTFILE);
	}
	to->nent = from->nent;
	runlock(from);
}
*/
