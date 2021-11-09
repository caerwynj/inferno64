#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

#define DBG if(1)print

static void
unlockfgrp(Fgrp *f)
{
	int ex;

	ex = f->exceed;
	f->exceed = 0;
	unlock(f);
	if(ex)
		pprint("warning: process exceeds %d file descriptors\n", ex);
}

int
growfd(Fgrp *f, int fd)	/* fd is always >= 0 */
{
	Chan **newfd, **oldfd;
	uchar *newflag, *oldflag;
	int nfd;

	nfd = f->nfd;
	if(fd < nfd)
		return 0;
	if(fd >= nfd+DELTAFD)
		return -1;	/* out of range */
	/*
	 * Unbounded allocation is unwise; besides, there are only 16 bits
	 * of fid in 9P
	 */
	if(nfd >= MAXNFD){
    Exhausted:
		print("no free file descriptors\n");
		return -1;
	}
	oldfd = f->fd;
	oldflag = f->flag;
	newfd = malloc((nfd+DELTAFD)*sizeof(newfd[0]));
	if(newfd == nil)
		goto Exhausted;
	memmove(newfd, oldfd, nfd*sizeof(newfd[0]));
	newflag = malloc((nfd+DELTAFD)*sizeof(newflag[0]));
	if(newflag == nil){
		free(newfd);
		goto Exhausted;
	}
	memmove(newflag, oldflag, nfd*sizeof(newflag[0]));
	f->fd = newfd;
	f->flag = newflag;
	f->nfd = nfd+DELTAFD;
	if(fd > f->maxfd){
		if(fd/100 > f->maxfd/100)
			f->exceed = (fd/100)*100;
		f->maxfd = fd;
	}
	free(oldfd);
	free(oldflag);
	return 1;
}

/*
 *  this assumes that the fgrp is locked
 */
int
findfreefd(Fgrp *f, int start)
{
	int fd;

	for(fd=start; fd<f->nfd; fd++)
		if(f->fd[fd] == nil)
			break;
	if(fd >= f->nfd && growfd(f, fd) < 0)
		return -1;
	return fd;
}

int
newfd(Chan *c, int mode)
{
	int fd, flag;
	Fgrp *f;

	f = up->env->fgrp;
	lock(f);
	fd = findfreefd(f, 0);
	if(fd < 0){
		unlockfgrp(f);
		return -1;
	}
	if(fd > f->maxfd)
		f->maxfd = fd;
	f->fd[fd] = c;

	/* per file-descriptor flags */
	flag = 0;
	if(mode & OCEXEC)
		flag |= CCEXEC;
	f->flag[fd] = flag;

	unlockfgrp(f);
	return fd;
}

int
newfd2(int fd[2], Chan *c[2])
{
	Fgrp *f;

	f = up->env->fgrp;
	lock(f);
	fd[0] = findfreefd(f, 0);
	if(fd[0] < 0){
		unlockfgrp(f);
		return -1;
	}
	fd[1] = findfreefd(f, fd[0]+1);
	if(fd[1] < 0){
		unlockfgrp(f);
		return -1;
	}
	if(fd[1] > f->maxfd)
		f->maxfd = fd[1];
	f->fd[fd[0]] = c[0];
	f->fd[fd[1]] = c[1];
	f->flag[fd[0]] = 0;
	f->flag[fd[1]] = 0;
	unlockfgrp(f);
	return 0;
}

Chan*
fdtochan(Fgrp *f, int fd, int mode, int chkmnt, int iref)
{
	Chan *c;

	c = nil;

	lock(f);
	if(fd<0 || f->maxfd<fd || (c = f->fd[fd])==nil) {
		unlock(f);
		error(Ebadfd);
	}
	if(iref)
		incref(c);
	unlock(f);

	if(chkmnt && (c->flag&CMSG)) {
		if(iref)
			cclose(c);
		error(Ebadusefd);
	}

	if(mode<0 || c->mode==ORDWR)
		return c;

	if((mode&OTRUNC) && c->mode==OREAD) {
		if(iref)
			cclose(c);
		error(Ebadusefd);
	}

	if((mode&~OTRUNC) != c->mode) {
		if(iref)
			cclose(c);
		error(Ebadusefd);
	}

	return c;
}

long
kchanio(void *vc, void *buf, int n, int mode)
{
	int r;
	Chan *c;

	c = vc;
	if(waserror())
		return -1;

	if(mode == OREAD)
		r = devtab[c->type]->read(c, buf, n, c->offset);
	else
		r = devtab[c->type]->write(c, buf, n, c->offset);

	lock(c);
	c->offset += r;
	unlock(c);
	poperror();
	return r;
}

int
openmode(ulong o)
{
	if(o >= (OTRUNC|OCEXEC|ORCLOSE|OEXEC))
		error(Ebadarg);
	o &= ~(OTRUNC|OCEXEC|ORCLOSE);
	if(o > OEXEC)
		error(Ebadarg);
	if(o == OEXEC)
		return OREAD;
	return o;
}

void
fdclose(Fgrp *f, int fd, int flag)
{
	Chan *c;

	lock(f);
	c = fd <= f->maxfd ? f->fd[fd] : nil;
	if(c == nil || (flag != 0 && ((f->flag[fd]|c->flag)&flag) == 0)){
		unlock(f);
		return;
	}
	f->fd[fd] = nil;
	if(fd == f->maxfd){
		while(fd > 0 && f->fd[fd] == nil)
			f->maxfd = --fd;
	}
	unlock(f);
	cclose(c);
}

int
kchdir(char *path)
{
	Chan *c;
	Pgrp *pg;

	if(waserror())
		return -1;

	c = namec(path, Atodir, 0, 0);
	pg = up->env->pgrp;
	cclose(pg->dot);
	pg->dot = c;
	poperror();
	return 0;
}

int
kfgrpclose(Fgrp *f, int fd)
{
	if(waserror())
		return -1;

	/*
	 * Take no reference on the chan because we don't really need the
	 * data structure, and are calling fdtochan only for error checks.
	 * fdclose takes care of processes racing through here.
	 */
	fdtochan(f, fd, -1, 0, 0);
	fdclose(f, fd, 0);
	poperror();
	return 0;
}

int
kclose(int fd)
{
	return kfgrpclose(up->env->fgrp, fd);
}

int
kcreate(char *path, int mode, ulong perm)
{
	int fd;
	Chan *c;

	if(waserror())
		return -1;

	openmode(mode&~OEXCL);	/* error check only; OEXCL okay here */
	c = namec(path, Acreate, mode, perm);
	if(waserror()) {
		cclose(c);
		nexterror();
	}
	fd = newfd(c, mode);
	if(fd < 0)
		error(Enofd);
	poperror();

	poperror();
	return fd;
}

int
kdup(int old, int new)
{
	int fd;
	Chan *c, *oc;
	Fgrp *f = up->env->fgrp;

	if(waserror())
		return -1;

	c = fdtochan(up->env->fgrp, old, -1, 0, 1);
	if(c->qid.type & QTAUTH)
		error(Eperm);
	fd = new;
	if(fd != -1){
		lock(f);
		if(fd<0 || growfd(f, fd) < 0) {
			unlockfgrp(f);
			cclose(c);
			error(Ebadfd);
		}
		if(fd > f->maxfd)
			f->maxfd = fd;
		oc = f->fd[fd];
		f->fd[fd] = c;
		f->flag[fd] = 0;
		unlockfgrp(f);
		if(oc)
			cclose(oc);
	}else{
		if(waserror()) {
			cclose(c);
			nexterror();
		}
		fd = newfd(c, 0);
		if(fd < 0)
			error(Enofd);
		poperror();
	}
	poperror();
	return fd;
}

int
kfstat(int fd, uchar *buf, int n)
{
	Chan *c;

	if(waserror())
		return -1;

	c = fdtochan(up->env->fgrp, fd, -1, 0, 1);
	if(waserror()) {
		cclose(c);
		nexterror();
	}
	devtab[c->type]->stat(c, buf, n);

	poperror();
	cclose(c);

	poperror();
	return n;
}

char*
kfd2path(int fd)
{
	Chan *c;
	char *s;

	if(waserror())
		return nil;
	c = fdtochan(up->env->fgrp, fd, -1, 0, 1);
	s = nil;
	if(c->path != nil){
		s = malloc(c->path->len+1);
		if(s == nil){
			cclose(c);
			error(Enomem);
		}
		memmove(s, c->path->s, c->path->len+1);
		cclose(c);
	}
	poperror();
	return s;
}

int
kfauth(int fd, char *aname)
{
	Chan *c, *ac;

	if(waserror())
		return -1;

	validname(aname, 1);
	c = fdtochan(up->env->fgrp, fd, ORDWR, 0, 1);
	if(waserror()){
		cclose(c);
		nexterror();
	}

	ac = mntauth(c, aname);

	/* at this point ac is responsible for keeping c alive */
	poperror();	/* c */
	cclose(c);

	if(waserror()){
		cclose(ac);
		nexterror();
	}

	fd = newfd(ac, 0);
	if(fd < 0)
		error(Enofd);
	poperror();	/* ac */

	poperror();

	return fd;
}

int
kfversion(int fd, uint msize, char *vers, uint arglen)
{
	int m;
	Chan *c;

	if(waserror())
		return -1;

	/* check there's a NUL in the version string */
	if(arglen==0 || memchr(vers, 0, arglen)==0)
		error(Ebadarg);

	c = fdtochan(up->env->fgrp, fd, ORDWR, 0, 1);
	if(waserror()){
		cclose(c);
		nexterror();
	}

	m = mntversion(c, vers, msize, arglen);

	poperror();
	cclose(c);

	poperror();
	return m;
}

int
kpipe(int ufd[2])
{
	static char *datastr[] = {"data", "data1"};
	int fd[2];
	Chan *c[2];

	ufd[0] = ufd[1] = fd[0] = fd[1] = -1;
	c[0] = namec("#|", Atodir, 0, 0);
	c[1] = nil;
	if(waserror()) {
		if(c[0] != nil)
			cclose(c[0]);
		if(c[1] != nil)
			cclose(c[1]);
		return -1;
	}
	c[1] = cclone(c[0]);
	if(walk(&c[0], datastr+0, 1, 1, nil) < 0)
		error(Egreg);
	if(walk(&c[1], datastr+1, 1, 1, nil) < 0)
		error(Egreg);
	c[0] = devtab[c[0]->type]->open(c[0], ORDWR);
	c[1] = devtab[c[1]->type]->open(c[1], ORDWR);
	if(newfd2(fd, c) < 0)
		error(Enofd); 
	ufd[0] = fd[0];
	ufd[1] = fd[1];
	poperror();
	return 0;
}

static int
dirfixed(uchar *p, uchar *e, Dir *d)
{
	int len;

	len = GBIT16(p)+BIT16SZ;
	if(p + len > e)
		return -1;

	p += BIT16SZ;	/* ignore size */
	d->type = devno(GBIT16(p), 1);
	p += BIT16SZ;
	d->dev = GBIT32(p);
	p += BIT32SZ;
	d->qid.type = GBIT8(p);
	p += BIT8SZ;
	d->qid.vers = GBIT32(p);
	p += BIT32SZ;
	d->qid.path = GBIT64(p);
	p += BIT64SZ;
	d->mode = GBIT32(p);
	p += BIT32SZ;
	d->atime = GBIT32(p);
	p += BIT32SZ;
	d->mtime = GBIT32(p);
	p += BIT32SZ;
	d->length = GBIT64(p);

	return len;
}

static char*
dirname(uchar *p, int *n)
{
	p += BIT16SZ+BIT16SZ+BIT32SZ+BIT8SZ+BIT32SZ+BIT64SZ
		+ BIT32SZ+BIT32SZ+BIT32SZ+BIT64SZ;
	*n = GBIT16(p);
	return (char*)p+BIT16SZ;
}

static long
dirsetname(char *name, int len, uchar *p, long n, long maxn)
{
	char *oname;
	int olen;
	long nn;

	if(n == BIT16SZ)
		return BIT16SZ;

	oname = dirname(p, &olen);

	nn = n+len-olen;
	PBIT16(p, nn-BIT16SZ);
	if(nn > maxn)
		return BIT16SZ;

	if(len != olen)
		memmove(oname+len, oname+olen, p+n-(uchar*)(oname+olen));
	PBIT16((uchar*)(oname-2), len);
	memmove(oname, name, len);
	return nn;
}

/*
 * Mountfix might have caused the fixed results of the directory read
 * to overflow the buffer.  Catch the overflow in c->dirrock.
 */
static void
mountrock(Chan *c, uchar *p, uchar **pe)
{
	uchar *e, *r;
	int len, n;

	e = *pe;

	/* find last directory entry */
	for(;;){
		len = BIT16SZ+GBIT16(p);
		if(p+len >= e)
			break;
		p += len;
	}

	/* save it away */
	qlock(&c->rockqlock);
	if(c->nrock+len > c->mrock){
		n = ROUND(c->nrock+len, 1024);
		r = smalloc(n);
		memmove(r, c->dirrock, c->nrock);
		free(c->dirrock);
		c->dirrock = r;
		c->mrock = n;
	}
	memmove(c->dirrock+c->nrock, p, len);
	c->nrock += len;
	qunlock(&c->rockqlock);

	/* drop it */
	*pe = p;
}

/*
 * Satisfy a directory read with the results saved in c->dirrock.
 */
static int
mountrockread(Chan *c, uchar *op, s32 n, s32 *nn)
{
	long dirlen;
	uchar *rp, *erp, *ep, *p;

	/* common case */
	if(c->nrock == 0)
		return 0;

	/* copy out what we can */
	qlock(&c->rockqlock);
	rp = c->dirrock;
	erp = rp+c->nrock;
	p = op;
	ep = p+n;
	while(rp+BIT16SZ <= erp){
		dirlen = BIT16SZ+GBIT16(rp);
		if(p+dirlen > ep)
			break;
		memmove(p, rp, dirlen);
		p += dirlen;
		rp += dirlen;
	}

	if(p == op){
		qunlock(&c->rockqlock);
		return 0;
	}

	/* shift the rest */
	if(rp != erp)
		memmove(c->dirrock, rp, erp-rp);
	c->nrock = erp - rp;

	*nn = p - op;
	qunlock(&c->rockqlock);
	return 1;
}

static void
mountrewind(Chan *c)
{
	c->nrock = 0;
}

/*
 * Rewrite the results of a directory read to reflect current 
 * name space bindings and mounts.  Specifically, replace
 * directory entries for bind and mount points with the results
 * of statting what is mounted there.  Except leave the old names.
 */
static long
mountfix(Chan *c, uchar *op, s32 n, s32 maxn)
{
	char *name;
	int nbuf, nname;
	Chan *nc;
	Mhead *mh;
	Mount *m;
	uchar *p;
	int dirlen, rest;
	long l;
	uchar *buf, *e;
	Dir d;

	p = op;
	buf = nil;
	nbuf = 0;
	for(e=&p[n]; p+BIT16SZ<e; p+=dirlen){
		dirlen = dirfixed(p, e, &d);
		if(dirlen < 0)
			break;
		nc = nil;
		mh = nil;
		if(findmount(&nc, &mh, d.type, d.dev, d.qid)){
			/*
			 * If it's a union directory and the original is
			 * in the union, don't rewrite anything.
			 */
			rlock(&mh->lock);
			for(m = mh->mount; m != nil; m = m->next){
				if(eqchantdqid(m->to, d.type, d.dev, d.qid, 1)){
					runlock(&mh->lock);
					goto Norewrite;
				}
			}
			runlock(&mh->lock);

			name = dirname(p, &nname);
			/*
			 * Do the stat but fix the name.  If it fails, leave old entry.
			 * BUG: If it fails because there isn't room for the entry,
			 * what can we do?  Nothing, really.  Might as well skip it.
			 */
			if(buf == nil){
				nbuf = 4096;
				buf = smalloc(nbuf);
			}
			if(waserror())
				goto Norewrite;
			l = devtab[nc->type]->stat(nc, buf, nbuf);
			l = dirsetname(name, nname, buf, l, nbuf);
			if(l == BIT16SZ)
				error("dirsetname");
			poperror();

			/*
			 * Shift data in buffer to accomodate new entry,
			 * possibly overflowing into rock.
			 */
			rest = e - (p+dirlen);
			if(l > dirlen){
				while(p+l+rest > op+maxn){
					mountrock(c, p, &e);
					if(e == p){
						dirlen = 0;
						goto Norewrite;
					}
					rest = e - (p+dirlen);
				}
			}
			if(l != dirlen){
				memmove(p+l, p+dirlen, rest);
				dirlen = l;
				e = p+dirlen+rest;
			}

			/*
			 * Rewrite directory entry.
			 */
			memmove(p, buf, l);

		    Norewrite:
			cclose(nc);
			putmhead(mh);
		}
	}
	if(buf != nil)
		free(buf);

	if(p != e)
		error("oops in rockfix");

	return e-op;
}

static u32
wstat(Chan *c, uchar *d, int nd)
{
	u32 l;
	int namelen;

	if(waserror()){
		cclose(c);
		nexterror();
	}
	if(c->ismtpt){
		/*
		 * Renaming mount points is disallowed to avoid surprises
		 * (which should be renamed? the mount point or the mounted Chan?).
		 */
		dirname(d, &namelen);
		if(namelen)
			nameerror(chanpath(c), Eismtpt);
	}
	l = devtab[c->type]->wstat(c, d, nd);
	poperror();
	cclose(c);
	return l;
}

int
kfwstat(int fd, uchar *buf, int n)
{
	Chan *c;

	if(waserror())
		return -1;

	validstat(buf, n);
	c = fdtochan(up->env->fgrp, fd, -1, 1, 1);
	return (wstat(c, buf, n));
}

static int
bindmount(int ismount, int fd, int afd, char* arg0, char* arg1, int flag, char* spec)
{
	int ret;
	Chan *c0, *c1, *ac, *bc;

	if((flag&~MMASK) || (flag&MORDER)==(MBEFORE|MAFTER))
		error(Ebadarg);

	if(ismount){
		spec = validnamedup(spec, 1);
		if(waserror()){
			free(spec);
			nexterror();
		}

		if(up->env->pgrp->noattach)
			error(Enoattach);

		ac = nil;
		bc = fdtochan(up->env->fgrp, fd, ORDWR, 0, 1);
		if(waserror()) {
			if(ac != nil)
				cclose(ac);
			cclose(bc);
			nexterror();
		}

		if(afd >= 0)
			ac = fdtochan(up->env->fgrp, afd, ORDWR, 0, 1);

		c0 = mntattach(bc, ac, spec, flag&MCACHE);
		poperror();	/* ac bc */
		if(ac != nil)
			cclose(ac);
		cclose(bc);
	}else{
		spec = nil;
		c0 = namec(arg0, Abind, 0, 0);
	}

	if(waserror()){
		cclose(c0);
		nexterror();
	}

	c1 = namec(arg1, Amount, 0, 0);
	if(waserror()){
		cclose(c1);
		nexterror();
	}

	ret = cmount(c0, c1, flag, spec);

	poperror();
	cclose(c1);
	poperror();
	cclose(c0);
	if(ismount){
		fdclose(up->env->fgrp, fd, 0);
		poperror();
		free(spec);
	}
	return ret;
}

int
kbind(char *new, char *old, int flags)
{
	return bindmount(0, -1, -1, new, old, flags, nil);
}

int
kmount(int fd, int afd, char *old, int flags, char *spec)
{
	return bindmount(1, fd, afd, nil, old, flags, spec);
}

int
kunmount(char *name, char *old)
{
	Chan *cmount, *cmounted;

	cmounted = nil;
	cmount = namec(old, Amount, 0, 0);
	if(waserror()) {
		cclose(cmount);
		if(cmounted != nil)
			cclose(cmounted);
		nexterror();
	}
	if(name != nil) {
		/*
		 * This has to be namec(..., Aopen, ...) because
		 * if arg[0] is something like /srv/cs or /fd/0,
		 * opening it is the only way to get at the real
		 * Chan underneath.
		 */
		cmounted = namec(name, Aopen, OREAD, 0);
	}
	cunmount(cmount, cmounted);
	poperror();
	cclose(cmount);
	if(cmounted != nil)
		cclose(cmounted);
	return 0;
}

int
kopen(char *path, int mode)
{
	int fd;
	Chan *c;

	if(waserror())
		return -1;

	openmode(mode);                         /* error check only */
	c = namec(path, Aopen, mode, 0);
	if(waserror()){
		cclose(c);
		nexterror();
	}
	fd = newfd(c, mode);
	if(fd < 0)
		error(Enofd);
	poperror();

	poperror();
	return fd;
}

long
unionread(Chan *c, void *va, long n)
{
	int i;
	long nr;
	Mhead *m;
	Mount *mount;

	qlock(&c->umqlock);
	m = c->umh;
	rlock(&m->lock);
	mount = m->mount;
	/* bring mount in sync with c->uri and c->umc */
	for(i = 0; mount != nil && i < c->uri; i++)
		mount = mount->next;

	nr = 0;
	while(mount != nil) {
		/* Error causes component of union to be skipped */
		if(mount->to && !waserror()) {
			if(c->umc == nil){
				c->umc = cclone(mount->to);
				c->umc = devtab[c->umc->type]->open(c->umc, OREAD);
			}
	
			nr = devtab[c->umc->type]->read(c->umc, va, n, c->umc->offset);
			if(nr < 0)
				nr = 0;	/* dev.c can return -1 */
			c->umc->offset += nr;
			poperror();
		}
		if(nr > 0)
			break;

		/* Advance to next element */
		c->uri++;
		if(c->umc != nil) {
			cclose(c->umc);
			c->umc = nil;
		}
		mount = mount->next;
	}
	runlock(&m->lock);
	qunlock(&c->umqlock);
	return nr;
}

static void
unionrewind(Chan *c)
{
	qlock(&c->umqlock);
	c->uri = 0;
	if(c->umc != nil){
		cclose(c->umc);
		c->umc = nil;
	}
	qunlock(&c->umqlock);
}

static s32
rread(int fd, void *p, s32 n, s64 *offp)
{
	s32 nn, nnn;
	Chan *c;
	s64 off;

	c = fdtochan(up->env->fgrp, fd, OREAD, 1, 1);

	if(waserror()){
		cclose(c);
		nexterror();
	}

	/*
	 * The offset is passed through on directories, normally.
	 * Sysseek complains, but pread is used by servers like exportfs,
	 * that shouldn't need to worry about this issue.
	 *
	 * Notice that c->devoffset is the offset that c's dev is seeing.
	 * The number of bytes read on this fd (c->offset) may be different
	 * due to rewritings in rockfix.
	 */
	if(offp == nil)	/* use and maintain channel's offset */
		off = c->offset;
	else
		off = *offp;
	if(off < 0)
		error(Enegoff);

	if(off == 0){	/* rewind to the beginning of the directory */
		if(offp == nil || (c->qid.type & QTDIR)){
			c->offset = 0;
			c->devoffset = 0;
		}
		mountrewind(c);
		unionrewind(c);
	}

	if(c->qid.type & QTDIR){
		if(mountrockread(c, p, n, &nn)){
			/* do nothing: mountrockread filled buffer */
		}else if(c->umh != nil)
			nn = unionread(c, p, n);
		else{
			if(off != c->offset)
				error(Edirseek);
			nn = devtab[c->type]->read(c, p, n, c->devoffset);
		}
		nnn = mountfix(c, p, nn, n);
	}else
		nnn = nn = devtab[c->type]->read(c, p, n, off);

	if(offp == nil || (c->qid.type & QTDIR)){
		lock(c);
		c->devoffset += nn;
		c->offset += nnn;
		unlock(c);
	}

	poperror();
	cclose(c);
	return nnn;
}

s32
kread(int fd, void *va, s32 n)
{
	return rread(fd, va, n, nil);
}

s32
kpread(int fd, void *va, s32 n, s64 off)
{
	s64 *offp;

	if(off != ~0ULL)
		offp = &off;
	else
		offp = nil;
	return rread(fd, va, n, offp);
}

int
kremove(char *path)
{
	Chan *c;

	c = namec(path, Aremove, 0, 0);
	/*
	 * Removing mount points is disallowed to avoid surprises
	 * (which should be removed: the mount point or the mounted Chan?).
	 */
	if(c->ismtpt){
		cclose(c);
		error(Eismtpt);
	}
	if(waserror()){
		c->type = 0;	/* see below */
		cclose(c);
		nexterror();
	}
	devtab[c->type]->remove(c);
	/*
	 * Remove clunks the fid, but we need to recover the Chan
	 * so fake it up.  rootclose() is known to be a nop.
	 */
	c->type = 0;
	poperror();
	cclose(c);
	return 0;
}

s64
kseek(int fd, s64 o, int type)
{
	Chan *c;
	uchar buf[sizeof(Dir)+100];
	Dir dir;
	int n;
	s64 off;

	c = fdtochan(up->env->fgrp, fd, -1, 1, 1);
	if(waserror()){
		cclose(c);
		nexterror();
	}
	if(devtab[c->type]->dc == L'|')
		error(Eisstream);

	off = 0;
	switch(type){
	case 0:
		off = o;
		if((c->qid.type & QTDIR) && off != 0)
			error(Eisdir);
		if(off < 0)
			error(Enegoff);
		c->offset = off;
		break;

	case 1:
		if(c->qid.type & QTDIR)
			error(Eisdir);
		lock(c);	/* lock for read/write update */
		off = o + c->offset;
		if(off < 0){
			unlock(c);
			error(Enegoff);
		}
		c->offset = off;
		unlock(c);
		break;

	case 2:
		if(c->qid.type & QTDIR)
			error(Eisdir);
		n = devtab[c->type]->stat(c, buf, sizeof buf);
		if(convM2D(buf, n, &dir, nil) == 0)
			error("internal error: stat error in seek");
		off = dir.length + o;
		if(off < 0)
			error(Enegoff);
		c->offset = off;
		break;

	default:
		error(Ebadarg);
	}
	c->uri = 0;
	c->dri = 0;
	cclose(c);
	poperror();
	return off;
}

void
validstat(uchar *s, int n)
{
	int m;
	char buf[64];

	if(statcheck(s, n) < 0)
		error(Ebadstat);
	/* verify that name entry is acceptable */
	s += STATFIXLEN - 4*BIT16SZ;	/* location of first string */
	/*
	 * s now points at count for first string.
	 * if it's too long, let the server decide; this is
	 * only for his protection anyway. otherwise
	 * we'd have to allocate and waserror.
	 */
	m = GBIT16(s);
	s += BIT16SZ;
	if(m+1 > sizeof buf)
		return;
	memmove(buf, s, m);
	buf[m] = '\0';
	/* name could be '/' */
	if(strcmp(buf, "/") != 0)
		validname(buf, 0);
}

static char*
pathlast(Path *p)
{
	char *s;

	if(p == nil)
		return nil;
	if(p->len == 0)
		return nil;
	s = strrchr(p->s, '/');
	if(s != nil)
		return s+1;
	return p->s;
}

int
kstat(char *path, uchar *buf, int n)
{
	Chan *c;
	uint r;

	if(waserror())
		return -1;

	c = namec(path, Aaccess, 0, 0);
	if(waserror()){
		cclose(c);
		nexterror();
	}
	r = devtab[c->type]->stat(c, buf, n);
	path = pathlast(c->path);
	if(path != nil)
		r = dirsetname(path, strlen(path), buf, r, n);
	poperror();
	cclose(c);

	poperror();
	return r;
}

static s32
rwrite(int fd, void *buf, s32 len, s64 *offp)
{
	Chan *c;
	s32 m, n;
	s64 off;

	n = 0;
	c = fdtochan(up->env->fgrp, fd, OWRITE, 1, 1);
	if(waserror()) {
		if(offp == nil){
			lock(c);
			c->offset -= n;
			unlock(c);
		}
		cclose(c);
		nexterror();
	}

	if(c->qid.type & QTDIR)
		error(Eisdir);

	n = len;

	if(offp == nil){	/* use and maintain channel's offset */
		lock(c);
		off = c->offset;
		c->offset += n;
		unlock(c);
	}else
		off = *offp;

	if(off < 0)
		error(Enegoff);

	m = devtab[c->type]->write(c, buf, n, off);
	if(offp == nil && m < n){
		lock(c);
		c->offset -= n - m;
		unlock(c);
	}

	poperror();
	cclose(c);
	return m;
}

s32
kwrite(int fd, void *va, s32 n)
{
	return rwrite(fd, va, n, nil);
}

s32
kpwrite(int fd, void *va, s32 n, s64 off)
{
	s64 *offp;

	if(off != ~0ULL)
		offp = &off;
	else
		offp = nil;
	return rwrite(fd, va, n, offp);
}

int
kwstat(char *path, uchar *buf, int n)
{
	Chan *c;
	long l;
	int namelen;

	if(waserror())
		return -1;

	validstat(buf, n);
	c = namec(path, Aaccess, 0, 0);
	if(waserror()){
		cclose(c);
		nexterror();
	}
	if(c->ismtpt){
		/*
		 * Renaming mount points is disallowed to avoid surprises
		 * (which should be renamed? the mount point or the mounted Chan?).
		 */
		dirname(buf, &namelen);
		if(namelen)
			nameerror(chanpath(c), Eismtpt);
	}
	l = devtab[c->type]->wstat(c, buf, n);
	poperror();
	cclose(c);
	return l;
}

enum
{
	DIRSIZE = STATFIXLEN + 32 * 4,
	DIRREADLIM = 2048,	/* should handle the largest reasonable directory entry */
};

Dir*
chandirstat(Chan *c)
{
	Dir *d;
	uchar *buf;
	int n, nd, i;

	nd = DIRSIZE;
	for(i=0; i<2; i++){	/* should work by the second try */
		d = smalloc(sizeof(Dir) + nd);
		buf = (uchar*)&d[1];
		if(waserror()){
			free(d);
			return nil;
		}
		n = devtab[c->type]->stat(c, buf, nd);
		poperror();
		if(n < BIT16SZ){
			free(d);
			return nil;
		}
		nd = GBIT16((uchar*)buf) + BIT16SZ;	/* size needed to store whole stat buffer including count */
		if(nd <= n){
			convM2D(buf, n, d, (char*)&d[1]);
			return d;
		}
		/* else sizeof(Dir)+nd is plenty */
		free(d);
	}
	return nil;

}

Dir*
kdirstat(char *name)
{
	Chan *c;
	Dir *d;

	if(waserror())
		return nil;

	c = namec(name, Aaccess, 0, 0);
	if(waserror()){
		cclose(c);
		nexterror();
	}
	d = chandirstat(c);
	poperror();
	cclose(c);

	poperror();
	return d;
}

Dir*
kdirfstat(int fd)
{
	Chan *c;
	Dir *d;

	if(waserror())
		return nil;

	c = fdtochan(up->env->fgrp, fd, -1, 0, 1);
	if(waserror()) {
		cclose(c);
		nexterror();
	}
	d = chandirstat(c);
	poperror();
	cclose(c);

	poperror();
	return d;
}

int
kdirwstat(char *name, Dir *dir)
{
	uchar *buf;
	int r;

	r = sizeD2M(dir);
	buf = smalloc(r);
	convD2M(dir, buf, r);
	r = kwstat(name, buf, r);
	free(buf);
	return r < 0? r: 0;
}

int
kdirfwstat(int fd, Dir *dir)
{
	uchar *buf;
	int r;

	r = sizeD2M(dir);
	buf = smalloc(r);
	convD2M(dir, buf, r);
	r = kfwstat(fd, buf, r);
	free(buf);
	return r < 0? r: 0;
}

static long
dirpackage(uchar *buf, long ts, Dir **d)
{
	char *s;
	long ss, i, n, nn, m;

	*d = nil;
	if(ts <= 0)
		return ts;

	/*
	 * first find number of all stats, check they look like stats, & size all associated strings
	 */
	ss = 0;
	n = 0;
	for(i = 0; i < ts; i += m){
		m = BIT16SZ + GBIT16(&buf[i]);
		if(statcheck(&buf[i], m) < 0)
			break;
		ss += m;
		n++;
	}

	if(i != ts)
		error("bad directory format");

	*d = malloc(n * sizeof(Dir) + ss);
	if(*d == nil)
		error(Enomem);

	/*
	 * then convert all buffers
	 */
	s = (char*)*d + n * sizeof(Dir);
	nn = 0;
	for(i = 0; i < ts; i += m){
		m = BIT16SZ + GBIT16((uchar*)&buf[i]);
		if(nn >= n || convM2D(&buf[i], m, *d + nn, s) != m){
			free(*d);
			*d = nil;
			error("bad directory entry");
		}
		nn++;
		s += m;
	}

	return nn;
}

long
kdirread(int fd, Dir **d)
{
	uchar *buf;
	long ts;

	*d = nil;
	if(waserror())
		return -1;
	buf = malloc(DIRREADLIM);
	if(buf == nil)
		error(Enomem);
	if(waserror()){
		free(buf);
		nexterror();
	}
	ts = kread(fd, buf, DIRREADLIM);
	if(ts >= 0)
		ts = dirpackage(buf, ts, d);
	poperror();
	free(buf);
	poperror();
	return ts;
}

int
kiounit(int fd)
{
	Chan *c;
	int n;

	c = fdtochan(up->env->fgrp, fd, -1, 0, 1);
	if(waserror()){
		cclose(c);
		return 0;	/* n.b. */
	}
	n = c->iounit;
	poperror();
	cclose(c);
	return n;
}
