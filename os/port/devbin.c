#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

#define	WHICHFILE(q) ((q).path)
#define	SOURCEFD(q)	((q).vers)
int debug = 0;

/*
	An fd created here might be used by different processes at the same time
	if the processes are sharing the Fgrp. Hence, the need for locks.
 TODO
	add a ctl file to add searchers at run time (format: name <end byte>\n)
 */
/*
	len is the space available in the reader's buffer
	For now, assuming that the delimiter is 1 char.
 */
typedef struct Searcher Searcher;
struct Searcher
{
	u32 whichfile;
	char name[KNAMELEN];
	/* function pointer to identify the content to send */
	s32 (*contentfn)(u8 *readp, u8 *writep, u8 **startp, s32 maxn, u8 **nextreadp);
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
	Qbufferlength,	/* show the remaining bytes in the buffer */
	Qbuffer,
	Qword,
	Qline,
	Qdoublequote,
	Qcloseparen,
};

static s32 wordfn(u8 *readp, u8 *writep, u8 **startp, s32 maxn, u8 **nextreadp);
static s32 linefn(u8 *readp, u8 *writep, u8 **startp, s32 maxn, u8 **nextreadp);
static s32 doublequotefn(u8 *readp, u8 *writep, u8 **startp, s32 maxn, u8 **nextreadp);
static s32 closeparenfn(u8 *readp, u8 *writep, u8 **startp, s32 maxn, u8 **nextreadp);
static s32 readmax(u8 *readp, u8 *writep, u8 **startp, s32 maxn, u8 **nextreadp);
u16	bintype = 0;

Searcher	searchers[] =
{
	Qbufferlength, "bufferlength", readmax, /* irrelevant function, not used */
	Qbuffer, "buffer", readmax,	/* to read contents without a delimiter, such as the last non-delimited content */
	Qword, "word", wordfn,
	Qline, "line", linefn,
	Qdoublequote, "doublequote", doublequotefn,
	Qcloseparen, "closeparen", closeparenfn,
};

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
	if(WHICHFILE(c->qid) == Qtopdir){
		if(i > up->fgrp->maxfd)
			return -1;
		nsourcefds = 0;

		for(nfd = 0; nfd <= up->fgrp->maxfd; nfd++){
			if(up->fgrp->fd[nfd] != nil &&
				up->fgrp->fd[nfd]->type != bintype &&
				(up->fgrp->fd[nfd]->mode == OREAD ||
				 up->fgrp->fd[nfd]->mode == ORDWR)){
				if(nsourcefds == i){
					snprint(fdname,5,"%d",nfd);
					mkqid(&q, Qfddir, nfd, QTDIR); /* source fd in qid.vers */
					devdir(c, q, fdname, 0, eve, 0555, dp);
					return 1;
				}
				nsourcefds++;
			}
		}
		return -1;
	}

	/* within an fd's dir, show the list of searchers as files */
	ns = 0;
	for(l = searchers; l != nil; l++, ns++){
		if(i == ns){
			mkqid(&q, l->whichfile, c->qid.vers, QTFILE);
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
	Binreader *br;
	Searcher *s;
	u64 whichfile;

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
	if(WHICHFILE(c->qid) <= Qfddir)
		error(Ebadarg);

	sourcefd = SOURCEFD(c->qid);
	if(sourcefd > up->fgrp->maxfd)
		error(Ebadarg);
	if(up->fgrp->fd[sourcefd] == nil ||
		up->fgrp->fd[sourcefd]->type == bintype)
		error(Ebadarg);
	if(up->fgrp->fd[sourcefd]->mode != OREAD &&
		up->fgrp->fd[sourcefd]->mode != ORDWR)
		error(Ebadarg);

	/* find any other buffering file that has opened
		this source fd, so the Buffer is used
		by both to keep the pointers in sync */
	bin = nil;
	for(nfd = 0; nfd <= up->fgrp->maxfd; nfd++){
		if(up->fgrp->fd[nfd] != nil &&
			up->fgrp->fd[nfd]->type == bintype &&
			up->fgrp->fd[nfd]->aux != nil &&
			((Binreader*)up->fgrp->fd[nfd]->aux)->bin->sourcefd == sourcefd){
			bin = ((Binreader*)up->fgrp->fd[nfd]->aux)->bin;
			DBG("binopen found bin chanpath(c) %s br %p bin %p\n", chanpath(c), up->fgrp->fd[nfd]->aux, bin);
			qlock(bin);
			incref(bin);
			qunlock(bin);	
		}
	}
	br = malloc(sizeof(Binreader));
	if(br == nil)
		panic("exhausted memory");
	if(bin == nil){
		bin = malloc(sizeof(Bin));
		if(bin == nil)
			panic("exhausted memory");
		br->bin = bin;
		bin->eof=0;
		bin->sourcefd = sourcefd;
		incref(bin);
		DBG("binopen new bin chanpath(c) %s br %p bin %p\n", chanpath(c), br, bin);
	} else
		br->bin = bin;

	DBG("binopen chanpath(c) %s br %p bin %p\n", chanpath(c), br, bin);
	whichfile = WHICHFILE(c->qid);
	for(s = searchers; s != nil; s++){
		if(whichfile == s->whichfile){
			br->searcher = s;
			break;
		}
	}
	if(br->searcher == nil)
		error(Ebadarg);

	qlock(bin);
	if(bin->buf == nil){
		bin->buf = malloc(conf.pipeqsize);
		bin->readp = bin->writep = bin->buf;
		bin->sourcechan = up->fgrp->fd[sourcefd]; /* what if the sourcefd is closed in the meanwhile? */
		bin->bufsize = conf.pipeqsize;
	}
	qunlock(bin);
	c->aux = br;
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

	/* print("binclose: chanpath(c) %s\n", chanpath(c)); */
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

	if(bin->readp == bin->writep){
		bin->readp = bin->writep = bin->buf;
		DBG("refill: same readp 0x%p writep 0x%p\n",
				bin->readp, bin->writep);
	}else if(bin->readp > bin->buf){
		n = bin->writep-bin->readp;
		memmove(bin->buf, bin->readp, n);
		bin->writep = bin->buf+n;
		bin->readp = bin->buf;
		DBG("refill: move readp 0x%p writep 0x%p\n",
				bin->readp, bin->writep);
	}

	DBG("refill: read devtab[n].name %s devtab[n].dc %d"
		"	bin->sourcechan->type %d bin->sourcechan->offset %lld\n",
		devtab[bin->sourcechan->type]->name, devtab[bin->sourcechan->type]->dc,
		bin->sourcechan->type, bin->sourcechan->offset);
	nr = devtab[bin->sourcechan->type]->read(bin->sourcechan, bin->writep,
												 bin->bufsize-(bin->writep-bin->readp),
												 bin->sourcechan->offset);
	DBG("refill: read nr %d bin->sourcechan->offset %lld\n", nr, bin->sourcechan->offset);
	if(nr == 0)
		bin->eof = 1;

	bin->writep += nr;

	/* check the notes of rread in os/port/sysfile.c for details */
	lock(bin->sourcechan);
	bin->sourcechan->devoffset += nr;
	bin->sourcechan->offset += nr;
	unlock(bin->sourcechan);

	return nr;
}

/*
	end of file is not a delimiter
 */
static s32
binread(Chan *c, void *va, s32 n, s64)
{
	Bin *bin;
	Searcher *s;
	u8 *startp, *nextreadp;
	u32 rv, nremaining;
	char nlenstr[10];
	s32 nsend;

	if(c->qid.type == QTDIR){
		return devdirread(c, va, n, nil, 0, bingen);
	}

	DBG("binread: chanpath(c) %s n %d\n", chanpath(c), n);
	rv = 0;
	bin = ((Binreader*)c->aux)->bin;
	s = ((Binreader*)c->aux)->searcher;
	if(bin->buf == nil)
		panic("should no be happening");

	/* do not allow arbitrarily high read buffer sizes */
	if(n > bin->bufsize)
		error(Ebadarg);

	DBG("binread: starting chanpath(c) %s %s readp 0x%p writep 0x%p maxn %d\n",
		chanpath(c), s->name, bin->readp, bin->writep, n);
	qlock(bin);
	if(s->whichfile == Qbufferlength){
		rv = snprint(nlenstr, 10, "%lld\n", bin->writep-bin->readp);
		goto Exit;
	}
	if(s->whichfile == Qbuffer && bin->eof == 1){
		nremaining = bin->writep-bin->readp;
		if(nremaining == 0)
			rv = 0;
		else if(nremaining > 0){
			rv = nremaining > n ? n : nremaining;
			memmove(va, bin->readp, rv);
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
	DBG("binread: chanpath(c) %s %s readp 0x%p writep 0x%p maxn %d\n",
		chanpath(c), s->name, bin->readp, bin->writep, n);
	nsend = s->contentfn(bin->readp, bin->writep, &startp, n, &nextreadp);
	DBG("binread: nsend %d startp 0x%p nextreadp 0x%p\n", nsend, startp, nextreadp);
	if(nsend == 0 && bin->eof == 0){
		refill(bin);
		goto Search;
	}
		memmove(va, startp, nsend);
		bin->readp = nextreadp;
		rv = nsend;
Exit:
	DBG("binread: ending chanpath(c) %s %s readp 0x%p writep 0x%p maxn %d\n",
		chanpath(c), s->name, bin->readp, bin->writep, n);
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
readuntil(u8 *, u8 *endp)
{
	return endp;
}

static s32
readmax(u8 *readp, u8 *writep, u8 **startp, s32 maxn, u8 **nextreadp)
{
	*startp = readp;
	*nextreadp = writep;

	/* nothing to send */
	if(readp == writep)
		return 0;

	if(writep-readp > maxn){
		*nextreadp = readp+maxn;
		return maxn;
	}
	return writep-readp;
}

/*
	without a blank line at the end, the last word without an ending
	word delimiter gets skipped. This is how all Plan9 apps are working.
	Sticking to that policy.
	Hence, the application should read the buffer for the last word
		no, leave it alone. not worth the complexity.
	\<carriage return> will skip the next line
 */
static s32
wordfn(u8 *readp, u8 *writep, u8 **startp, s32 maxn, u8 **nextreadp)
{
	u8 *p;
	s32 n;

	*startp = *nextreadp = readp;

	/* nothing to send */
	if(readp == writep)
		return 0;

	/* skip starting delimiters */
	for(p = readp; p<writep; p++){
		if(*p == ' ' || *p == '	' || *p == '\n')
			continue;
		else
			break;
	}

	*startp = *nextreadp = p; /* disregard until p */

	/* all content is delimiters */
	if(p == writep){
		return 0;
	}

	/* find ending delimiter */
	for(n=0; p<writep && n < maxn; p++){
		if(*p == ' ' || *p == '	' || *p == '\n'){
			*nextreadp = p+1; /* skip this for the next read */
			return n;
		}
		n++;
	}

	/* no delimiter found in maxn bytes, send maxn */
	if(n == maxn){
		*nextreadp += maxn;
		return maxn;
	}

	/* no delimiter found before writep */
	return 0;
}

static s32
linefn(u8 *readp, u8 *writep, u8 **startp, s32 maxn, u8 **nextreadp)
{
	u8 *p;
	s32 n;

	*startp = *nextreadp = readp;

	/* nothing to send */
	if(readp == writep)
		return 0;

	/* skip starting delimiters */
	for(p = readp; p<writep; p++){
		if(*p == '\n')
			continue;
		else
			break;
	}

	*startp = *nextreadp = p; /* disregard until p */

	/* all content is delimiters */
	if(p == writep){
		return 0;
	}

	/* find ending delimiter */
	for(n=0; p<writep && n < maxn; p++){
		DBG("linefn: read p 0x%p *p %d\n", p, *p);
		if(*p == '\n'){
			*nextreadp = p+1; /* skip this for the next read */
			return n;
		}
		n++;
	}

	/* no delimiter found in maxn bytes, send maxn */
	if(n == maxn){
		*nextreadp += maxn;
		return maxn;
	}

	/* no delimiter found before writep */
	return 0;
}

/* read until c and skip c for the next read */
static s32
until(u8 *readp, u8 *writep, u8 **startp, s32 maxn, u8 **nextreadp, u8 c)
{
	u8 *p;
	s32 n;

	*startp = *nextreadp = readp;

	/* nothing to send */
	if(readp == writep)
		return 0;

	/* find ending delimiter */
	for(n=0; p<writep && n < maxn; p++){
		if(*p == c){
			*nextreadp = p+1; /* skip this for the next read */
			return n;
		}
		n++;
	}

	/* no delimiter found in maxn bytes, send maxn */
	if(n == maxn){
		*nextreadp += maxn;
		return maxn;
	}

	return 0;
}

/* find a double quote */
static s32
doublequotefn(u8 *readp, u8 *writep, u8 **startp, s32 maxn, u8 **nextreadp)
{
	/* " = 0x22 = 34 */
	return until(readp, writep, startp, maxn, nextreadp, 0x22);
}

static s32
closeparenfn(u8 *readp, u8 *writep, u8 **startp, s32 maxn, u8 **nextreadp)
{
	/* ) = 0x29 = 41 */
	return until(readp, writep, startp, maxn, nextreadp, 0x29);
}

