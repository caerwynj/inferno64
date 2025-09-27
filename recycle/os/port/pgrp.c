#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

static Ref pgrpid;
static Ref mountid;

enum {
	Whinesecs = 10,		/* frequency of out-of-resources printing */
};

static Ref mountid;

void
dumpmount(char *s, Mount *m)
{
	if(m == nil)
		return;

	print("%smountid %d spec %s",
			s, m->mountid, m->spec);
	dumpchan("to", m->to);
}

void
dumpmhead(char *s, Mhead *mh)
{
	Mount *m;

	if(mh == nil)
		return;

	USED(s);
	dumpchan("		from ", mh->from);
	print("			to\n");
	m = mh->mount;
	dumpmount("			", m);
	print("				next\n");
	for(m = m->next; m != nil; m = m->next) {
		dumpmount("			", m);
	}
}

void
dumppgrp(char *s, Pgrp *p)
{
	int i;
	Mhead *mh;

	if(p == nil)
		return;

	rlock(&p->ns);
	print("%s%p:%3ud slash %s dot %s\n		mnthash\n",
			s, p, p->pgrpid, chanpath(p->slash), chanpath(p->dot));
	for(i = 0; i<MNTHASH; i++){
		print("		i %d\n", i);
		for(mh = p->mnthash[i]; mh != nil; mh = mh->hash){
			rlock(&mh->lock);
			dumpmhead("		", mh);
			runlock(&mh->lock);
		}
	}
	runlock(&p->ns);
}

Pgrp*
newpgrp(void)
{
	Pgrp *p;

	p = smalloc(sizeof(Pgrp));
	p->ref = 1;
	p->pgrpid = incref(&pgrpid);
	p->progmode = 0644;
	return p;
}

Rgrp*
newrgrp(void)
{
	Rgrp *r;

	r = smalloc(sizeof(Rgrp));
	r->ref = 1;
	return r;
}

void
closergrp(Rgrp *r)
{
	if(decref(r) == 0)
		free(r);
}

void
closepgrp(Pgrp *p)
{
	Mhead **h, **e, *f;
	Mount *m;
	
	if(p == nil || decref(p))
		return;

	e = &p->mnthash[MNTHASH];
	for(h = p->mnthash; h < e; h++) {
		while((f = *h) != nil){
			*h = f->hash;
			wlock(&f->lock);
			m = f->mount;
			f->mount = nil;
			wunlock(&f->lock);
			mountfree(m);
			putmhead(f);
		}
	}
	cclose(p->dot);
	cclose(p->slash);
	free(p);
}

static void
pgrpinsert(Mount **order, Mount *m)
{
	Mount *f;

	m->order = nil;
	for(f = *order; f != nil; f = f->order) {
		if(m->mountid < f->mountid) {
			m->order = f;
			*order = m;
			return;
		}
		order = &f->order;
	}
	*order = m;
}

/*
 * pgrpcpy MUST preserve the mountid allocation order of the parent group
 * Hence, uses Mount.order to build a sorted linked list of mounts while
 * copying the mounts.
 */
void
pgrpcpy(Pgrp *to, Pgrp *from)
{
	int i;
	Mount *n, *m, **link, *order;
	Mhead *f, **l, *mh;

/*	print("pgrpcpy to->pgrpid %d from->pgrpid %d\n", to->pgrpid, from->pgrpid);
	dumppgrp("	from	\n	", from); */
	wlock(&to->ns);
	rlock(&from->ns);
	order = nil;
	for(i = 0; i < MNTHASH; i++) {
		l = &to->mnthash[i];
		for(f = from->mnthash[i]; f != nil; f = f->hash) {
			rlock(&f->lock);
			mh = newmhead(f->from);
			*l = mh;
			l = &mh->hash;
			link = &mh->mount;
			for(m = f->mount; m != nil; m = m->next) {
				n = smalloc(sizeof(Mount));
				n->mountid = m->mountid;
				n->mflag = m->mflag;
				n->to = m->to;
				incref(n->to);
				if(m->spec != nil)
					kstrdup(&n->spec, m->spec);
				pgrpinsert(&order, n);
				*link = n;
				link = &n->next;
			}
			runlock(&f->lock);
		}
	}
	/*
	 * Allocate mount ids in the same sequence as the parent group
	 */
	for(m = order; m != nil; m = m->order)
		m->mountid = incref(&mountid);

	to->progmode = from->progmode;
	to->slash = cclone(from->slash);
	to->dot = cclone(from->dot);
	to->nodevs = from->nodevs;

	runlock(&from->ns);
	wunlock(&to->ns);
/*	dumppgrp("	to	\n	", to); */
}

/* not used by 9front. why?
 *	because, we need to be connected to the parent to communicate
 *	hence, dupfgrp() is used
 */
Fgrp*
newfgrp(Fgrp *old)
{
	Fgrp *new;
	int n;

	new = smalloc(sizeof(Fgrp));
	new->ref = 1;
	n = DELTAFD;
	if(old != nil){
		lock(old);
		if(old->maxfd >= n)
			n = (old->maxfd+1 + DELTAFD-1)/DELTAFD * DELTAFD;
		new->maxfd = old->maxfd;
		unlock(old);
	}
	new->nfd = n;
	new->fd = smalloc(n*sizeof(Chan*));
	return new;
}

Fgrp*
dupfgrp(Fgrp *f)
{
	Fgrp *new;
	Chan *c;
	int i;

	new = smalloc(sizeof(Fgrp));
	if(f == nil){
		new->flag = smalloc(DELTAFD*sizeof(new->flag[0]));
		new->fd = smalloc(DELTAFD*sizeof(new->fd[0]));
		new->nfd = DELTAFD;
		new->ref = 1;
		return new;
	}

	lock(f);
	/* Make new fd list shorter if possible, preserving quantization */
	new->nfd = f->maxfd+1;
	i = new->nfd%DELTAFD;
	if(i != 0)
		new->nfd += DELTAFD - i;
	new->fd = malloc(new->nfd*sizeof(new->fd[0]));
	if(new->fd == nil){
		unlock(f);
		free(new);
		error("no memory for fgrp");
	}
	new->flag = malloc(new->nfd*sizeof(new->flag[0]));
	if(new->flag == nil){
		unlock(f);
		free(new->fd);
		free(new);
		error("no memory for fgrp");
	}
	new->ref = 1;

	new->maxfd = f->maxfd;
	for(i = 0; i <= f->maxfd; i++) {
		if((c = f->fd[i]) != nil){
			incref(c);
			new->fd[i] = c;
			new->flag[i] = f->flag[i];
		}
	}
	unlock(f);

	return new;
}

void
closefgrp(Fgrp *f)
{
	int i;
	Chan *c;

	if(f == nil || decref(f) != 0)
		return;

	/*
	 * If we get into trouble, forceclosefgrp
	 * will bail us out.
	 */
	up->closingfgrp = f;
	for(i = 0; i <= f->maxfd; i++)
		if((c = f->fd[i]) != nil){
			f->fd[i] = nil;
			cclose(c);
		}
	up->closingfgrp = nil;

	free(f->fd);
	free(f->flag);
	free(f);
}

/*
 * Called from interrupted() because up is in the middle
 * of closefgrp and just got a kill ctl message.
 * This usually means that up has wedged because
 * of some kind of deadly embrace with mntclose
 * trying to talk to itself.  To break free, hand the
 * unclosed channels to the close queue.  Once they
 * are finished, the blocked cclose that we've 
 * interrupted will finish by itself.
 */
void
forceclosefgrp(void)
{
	int i;
	Chan *c;
	Fgrp *f;

	if(up->procctl != Proc_exitme || up->closingfgrp == nil){
		print("bad forceclosefgrp call");
		return;
	}

	f = up->closingfgrp;
	for(i = 0; i <= f->maxfd; i++)
		if((c = f->fd[i]) != nil){
			f->fd[i] = nil;
			ccloseq(c);
		}
}

Mount*
newmount(Chan *to, int flag, char *spec)
{
	Mount *m;

	m = smalloc(sizeof(Mount));
	m->to = to;
	incref(to);
	m->mountid = incref(&mountid);
	m->mflag = flag;
	if(spec != nil)
		kstrdup(&m->spec, spec);
	setmalloctag(m, getcallerpc(&to));
	return m;
}
void
mountfree(Mount *m)
{
	Mount *f;

	while((f = m) != nil) {
		m = m->next;
		cclose(f->to);
		free(f->spec);
		free(f);
	}
}

void
resrcwait(char *reason)
{
	static ulong lastwhine;
	ulong now;
	char *p;

	if(up == nil)
		panic("resrcwait: %s", reason);

	p = up->psstate;
	if(reason != nil) {
		if(waserror()){
			up->psstate = p;
			nexterror();
		}
		up->psstate = reason;
		now = seconds();
		/* don't tie up the console with complaints */
		if(now - lastwhine > Whinesecs) {
			lastwhine = now;
			print("%s\n", reason);
		}
	}
	tsleep(&up->sleep, return0, 0, 100+nrand(200));
	if(reason != nil) {
		up->psstate = p;
		poperror();
	}
}

void
closesigs(Skeyset *s)
{
	int i;

	if(s == nil || decref(s) != 0)
		return;
	for(i=0; i<s->nkey; i++)
		freeskey(s->keys[i]);
	free(s);
}

void
freeskey(Signerkey *key)
{
	if(key == nil || decref(key) != 0)
		return;
	free(key->owner);
	(*key->pkfree)(key->pk);
	free(key);
}

/*
 * kernel interface to shm
 */
Sgrp*
shmgrpnew(void)
{
	Sgrp	*e;

	e = smalloc(sizeof(Sgrp));
	incref(e);
	return e;
}

void
shmgrpclose(Sgrp *g)
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

