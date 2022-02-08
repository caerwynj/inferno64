#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

#define	SEARCHER(q) ((u32)(q).path)
#define	SOURCEFD(q)	((q).vers)

/*
	An fd created here might be used by different processes at the same time
	if the processes are sharing the Fgrp. Hence, the need for locks.
 */
/*
	len is the space available in the reader's buffer
	For now, assuming that the delimiter is 1 char.
 */
typedef struct Searcher Searcher;
struct Searcher
{
	u32 qidpath;
	char name[KNAMELEN];
	u8	*(*endfn)(u8 *startp, u8 *endp); /* function pointer that returns the number of bytes to send */
};
QLock lexlock;

typedef struct Bin	Bin;
struct Bin
{
	QLock;
	Ref;
	u32	sourcefd;
	Chan *sourcechan;	/* for reading more data, instead of using fd2chan() for each read() */
	u8 *buf, *readp, *writep;
	s8 eof;
	u32 bufsize;
	u64 off;
};

typedef struct Binreader Binreader;
struct Binreader
{
	Bin *bin;
	Searcher *searcher;
};

enum
{
	Qtopdir = 0,
	Qfddir,
	Qword,
	Qline,
	Qdoublequote,
	Qcloseparen,
	Qbuffer,
};

static u8 *endofword(u8 *startp, u8 *endp);
static u8 *endofnewline(u8 *startp, u8 *endp);
static u8 *endofdoublequote(u8 *startp, u8 *endp);
static u8 *endofcloseparen(u8 *startp, u8 *endp);
static u8 *readuntil(u8 *startp, u8 *endp);
u16	bintype = 0;

Searcher	searchers[] =
{
	Qword,	"word", endofword,
	Qline,	"line", endofnewline,
	Qdoublequote,	"doublequote", endofdoublequote,
	Qcloseparen,	"closeparen", endofcloseparen,
	Qbuffer,	"buffer", readuntil,	/* to read contents without a delimiter, such as the last non-delimited content */
};

/*
 *  create a bin, no streams are created until an open
 */
static Chan*
binattach(char *spec)
{
	Chan *c;

	c = devattach('n', spec);
	mkqid(&c->qid, Qtopdir, 0, QTDIR);
	return c;
}

static int
bingen(Chan *c, char*, Dirtab *, int, int i, Dir *dp)
{
	Qid q;
	u32 nsourcefds, nfd, ns;
	char fdname[5];
	Searcher *l;

	/*
	 * if I do .. from #n or #n/0
	 */
	if(i == DEVDOTDOT){
		devdir(c, c->qid, "#n", 0, eve, 0555, dp);
		return 1;
	}
	if(SEARCHER(c->qid) == Qtopdir){
		if(i > up->fgrp->maxfd)
			return -1;
		nsourcefds = 0;
		for(nfd = 0; nfd < up->fgrp->maxfd; nfd++){
			if(up->fgrp->fd[nfd] != nil &&
				up->fgrp->fd[nfd]->type != bintype &&
				(up->fgrp->fd[nfd]->mode == OREAD || up->fgrp->fd[nfd]->mode == ORDWR))
				nsourcefds++;
			if(nsourcefds == i){
				snprint(fdname,5,"%d",nfd);
				mkqid(&q, Qfddir, nfd, QTDIR); /* source fd in qid.vers */
				devdir(c, q, fdname, 0, eve, 0555, dp);
				return 1;
			}
		}
		return -1;
	}

	/* within an fd's dir, show the list of searchers as files */
	ns = 0;
	for(l = searchers; l != nil; l++){
		ns++;
		if(i == ns){
			mkqid(&q, l->qidpath, c->qid.vers, QTFILE);
			devdir(c, q, l->name, 0, eve, 0400, dp);
			return 1;
		}
	}
	return -1;
}

static Walkqid*
binwalk(Chan *c, Chan *nc, char **name, int nname)
{
	Walkqid *wq;

print("binwalk chanpath(c) %s chanpath %s nname %d\n", chanpath(c), chanpath(nc), nname);
	wq = devwalk(c, nc, name, nname, nil, 0, bingen);
	if(wq != nil && wq->clone != nil && wq->clone != c){
		wq->clone->aux = nil;
	}
print("binwalk chanpath(wq->clone) %s\n", chanpath(wq->clone));
	return wq;
}

static s32
binstat(Chan *c, uchar *db, s32 n)
{
	int i;
	i = devstat(c, db, n, nil, 0, bingen);
	return i;
}

/*
 *  check all the existing fd's for any open to find this sourcefd.
 * 	if found, use that for the Bin
 */
static Chan*
binopen(Chan *c, u32 omode)
{
	Bin *bin;
	u32 sourcefd, nfd;
	Binreader *l;

	if(c->qid.type & QTDIR){
		if(omode != OREAD)
			error(Ebadarg);
		c->mode = omode;
		c->flag |= COPEN;
		c->offset = 0;
		return c;
	}

	if(omode != OREAD)
		error(Ebadarg);
	if(SEARCHER(c->qid) <= Qfddir)
		error(Ebadarg);

	sourcefd = SOURCEFD(c->qid);
	if(sourcefd > up->fgrp->maxfd)
		error(Ebadarg);
	if(up->fgrp->fd[sourcefd] == nil ||
		up->fgrp->fd[sourcefd]->type == bintype)
		error(Ebadarg);
	if(up->fgrp->fd[sourcefd]->mode != OREAD ||
		up->fgrp->fd[sourcefd]->mode != ORDWR)
		error(Ebadarg);

	/* check if this fd has been opened for reading */
	bin = nil;
	for(nfd = 0; nfd < up->fgrp->maxfd; nfd++){
		if(up->fgrp->fd[nfd] != nil &&
			up->fgrp->fd[nfd]->type == bintype &&
			((Binreader*)up->fgrp->fd[nfd]->aux)->bin->sourcefd == sourcefd){
			bin = ((Binreader*)up->fgrp->fd[nfd]->aux)->bin;
			qlock(bin);
			incref(bin);
			qunlock(bin);	
		}
	}
	l = malloc(sizeof(Binreader));
	if(l == nil)
		panic("exhausted memory");
	if(bin == nil){
		bin = malloc(sizeof(Bin));
		if(bin == nil)
			panic("exhausted memory");
		l->bin = bin;
		incref(bin);
	} else
		l->bin = bin;

	qlock(bin);
	if(bin->buf == nil){
		bin->buf = malloc(conf.pipeqsize);
		bin->readp = bin->writep = bin->buf;
		bin->sourcechan = up->fgrp->fd[sourcefd]; /* what if the sourcefd is closed in the meanwhile? */
		bin->bufsize = conf.pipeqsize;
	}
	qunlock(bin);
	c->aux = l;
	c->mode = openmode(omode);
	c->flag |= COPEN;
	c->offset = 0;
	c->iounit = conf.pipeqsize;
	return c;
}

static void
binclose(Chan *c)
{
	Bin *bin;
	Binreader *l;

print("binclose: c->path %s\n", chanpath(c));
	l = c->aux;
	if(l != nil){
		bin = l->bin;
		if(bin != nil){
			qlock(bin);
			decref(bin);
			if(bin->ref == 0){
				free(bin->buf);
				free(bin);
			}else
				qunlock(bin);
		}
	}
}

s32
refill(Bin *bin)
{
	s32 nr, n;

	if(bin->eof == 1)
		return 0;
	if(bin->writep == nil)
		bin->writep = bin->buf;
	if(bin->readp == nil)
		bin->readp = bin->buf;

	if(bin->readp > bin->buf){
		n = bin->writep-bin->readp;
		memmove(bin->buf, bin->readp, n);
		bin->writep -= n;
		bin->readp = bin->buf;
	}

	nr = devtab[bin->sourcechan->type]->read(bin->sourcechan, bin->writep,
												 bin->bufsize-(bin->writep-bin->readp),
												 bin->sourcechan->offset);
	if(nr == 0)
		bin->eof = 1;

	bin->writep += nr;
	return nr;
}

static s32
binread(Chan *c, void *va, s32 n, s64)
{
	Bin *bin;
	Searcher *s;
	u8 *p, *ep, *nextreadp;
	u32 rv, nremaining;

	if(c->qid.type == QTDIR){
		return devdirread(c, va, n, nil, 0, bingen);
	}

	bin = ((Binreader*)c->aux)->bin;
	s = ((Binreader*)c->aux)->searcher;
	if(bin->buf == nil)
		panic("should no be happening");

	/* do not allow arbitrarily high read buffer sizes */
	if(n > bin->bufsize)
		error(Ebadarg);

	qlock(bin);
	if(s->qidpath == Qbuffer && bin->eof == 1){
		nremaining = bin->writep-bin->readp;
		if(nremaining == 0)
			rv = 0;
		else if(nremaining > 0){
			rv = nremaining > n ? n : nremaining;
			memmove(va, bin->readp, n);
			bin->readp += rv;
		}
		goto Exit;
	}
	if(bin->readp == bin->writep){
		if(bin->eof == 1){	/* nothing more to read */
			rv = 0;
			goto Exit;
		}else
			refill(bin);
	}

Search: /* doing this while holding a lock, not sure if it is smart */
	if(bin->writep-bin->readp > n)
		ep = bin->readp+n;
	else
		ep = bin->writep;
	nextreadp = s->endfn(bin->readp, ep);
	if(nextreadp == nil){
		if(bin->writep-bin->readp > n){
			/* delimiter not found, send n bytes */
			memmove(va, bin->readp, n);
			bin->readp += n;
			rv = n;
			goto Exit;
		}else{
			refill(bin);
			goto Search;
		}
	}else{
		/* delimiter found within n bytes */
		rv = nextreadp-bin->readp;
		memmove(va, bin->readp, rv);
		bin->readp = nextreadp;
		goto Exit;
	}
Exit:
	qunlock(bin);
	return rv;
}

void
bininit(void)
{
	bintype = devno('n', 0);
}

s32
binwrite(Chan *, void *, s32, s64)
{
	error(Ebadarg);
	return -1;
}

Dev bindevtab = {
	'n',
	"bin",

	devreset,
	bininit,
	devshutdown,
	binattach,
	binwalk,
	binstat,
	binopen,
	devcreate,
	binclose,
	binread,
	devbread,
	binwrite,
	devbwrite,
	devremove,
	devwstat,
};

/* to read contents without a delimiter, such as the last non-delimited content */
static u8 *
readuntil(u8 *startp, u8 *endp)
{
	return endp;
}

static u8 *
endofword(u8 *startp, u8 *endp)
{
	u8 *p;

	for(p = startp; p<endp; p++){
		if(*p == ' ' || *p == '	' || *p == '\n')
			return p+1;
	}
	return nil;
}

static u8 *
endofnewline(u8 *startp, u8 *endp)
{
	u8 *p;

	for(p = startp; p<endp; p++){
		if(*p == '\n')
			return p+1;
	}
	return nil;
}

static u8 *
endofdoublequote(u8 *startp, u8 *endp)
{
	u8 *p;

	for(p = startp; p<endp; p++){
		if(*p == 0x22) /* " = 0x22 = 34 */
			return p+1;
	}
	return nil;
}

static u8 *
endofcloseparen(u8 *startp, u8 *endp)
{
	u8 *p;

	for(p = startp; p<endp; p++){
		if(*p == 0x29) /* ) = 0x29 = 41 */
			return p+1;
	}
	return nil;
}

