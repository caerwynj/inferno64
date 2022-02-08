#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

#define	SEARCHER(q) ((u32)(q).path)
#define	SOURCEFD(q)	((q).vers)

/*
	len is the space available in the reader's buffer
	For now, assuming that the delimiter is 1 char.
 */
typedef struct Searcher Searcher;
struct Searcher
{
	u32 qidpath;
	char name[KNAMELEN];
	u8	*(*searchfn)(u8 *startp, u8 *endp, u32 len); /* function pointer that returns the number of bytes to send */
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
};

static u8 *findword(u8 *startp, u8 *endp, u32 len);
static u8 *findnewline(u8 *startp, u8 *endp, u32 len);
static u8 *finddoublequote(u8 *startp, u8 *endp, u32 len);
static u8 *findcloseparen(u8 *startp, u8 *endp, u32 len);
u16	bintype = 0;

Searcher	searchers[] =
{
	Qword,	"word",	findword,
	Qline,	"line",	findnewline,
	Qdoublequote,	"doublequote",	finddoublequote,
	Qcloseparen,	"closeparen",	findcloseparen,
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
	 * if I do .. from #o or #o/0
	 */
	if(i == DEVDOTDOT){
		devdir(c, c->qid, "#o", 0, eve, 0555, dp);
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

	wq = devwalk(c, nc, name, nname, nil, 0, bingen);
	if(wq != nil && wq->clone != nil && wq->clone != c){
		wq->clone->aux = nil;
	}
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

	l = c->aux;
	bin = l->bin;
	qlock(bin);
	decref(bin);
	if(bin->ref == 0){
		free(bin->buf);
		free(bin);
	}else
		qunlock(bin);	
}

static s32
binread(Chan *c, void *va, s32 n, s64)
{
	Bin *bin;
	Searcher *s;
	u32 nr;
	u8 *p;
	u32 rv;

	if(c->qid.type == QTDIR){
		return devdirread(c, va, n, nil, 0, bingen);
	}

	bin = ((Binreader*)c->aux)->bin;
	s = ((Binreader*)c->aux)->searcher;
	if(bin->buf == nil)
		panic("should no be happening");

	qlock(bin);
	if(bin->readp == bin->writep){
		nr = devtab[bin->sourcechan->type]->read(bin->sourcechan, bin->buf,
												 bin->bufsize,
												 bin->sourcechan->offset);
		bin->readp = bin->buf;
		bin->writep = bin->buf+nr;
	}

Search: /* doing this while holding a lock, not sure if it is smart */
	p = s->searchfn(bin->readp, bin->writep, n);
	if(p > bin->readp){
		/* p+1 to skip the delimiter */
		rv = p+1-bin->readp;
		memmove(va, bin->readp, rv);
		bin->readp = p+1;
	}else{
		/* there is no delimiter between readp and writep */
		if(bin->writep -bin->readp > n){
			/* if there is no delimiter in the read buffer size, just send that much out */
			memmove(va, bin->readp, n);
			bin->readp += n;
			rv = n;
		}else{
			/* move the contents to the start of the buffer and read more */
			memmove(bin->buf, bin->readp, bin->writep-bin->readp);
			bin->writep -= bin->readp-bin->buf;
			bin->readp = bin->buf;
			nr = devtab[bin->sourcechan->type]->read(bin->sourcechan, bin->writep,
														bin->bufsize-(bin->writep-bin->buf),
														bin->sourcechan->offset);
			bin->writep += nr;
			goto Search;
		}		
	}
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

static u8 *
findword(u8 *startp, u8 *endp, u32 len)
{
	u8 *p, *ep;

	if(endp - startp > len)
		ep = startp+len;
	else
		ep = endp;
	for(p = startp; p<ep; p++){
		if(*p == ' ' || *p == '	' || *p == '\n')
			break;
	}
	return p;
}

static u8 *
findnewline(u8 *startp, u8 *endp, u32 len)
{
	u8 *p, *ep;

	if(endp - startp > len)
		ep = startp+len;
	else
		ep = endp;
	for(p = startp; p<ep; p++){
		if(*p == '\n')
			break;
	}
	return p;
}

static u8 *
finddoublequote(u8 *startp, u8 *endp, u32 len)
{
	u8 *p, *ep;

	if(endp - startp > len)
		ep = startp+len;
	else
		ep = endp;
	for(p = startp; p<ep; p++){
		if(*p == 0x22) /* " = 0x22 = 34 */
			break;
	}
	return p;
}

static u8 *
findcloseparen(u8 *startp, u8 *endp, u32 len)
{
	u8 *p, *ep;

	if(endp - startp > len)
		ep = startp+len;
	else
		ep = endp;
	for(p = startp; p<ep; p++){
		if(*p == 0x29) /* ) = 0x29 = 41 */
			break;
	}
	return p;
}

