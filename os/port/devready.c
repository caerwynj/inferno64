#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

static int debug = 0;

/*
	Provides #r to notify when the pipes have data to be read
	#r/watch	watch 0 3 4 # to watch for data on fd[0], fd[3] and fd[4]
	#r/ready	reads the fd ready to be read

	TODO why not add this to devproc? Too much complexity in devproc?
		It belongs there..
		instead of 2 files (watch and ready). Use 1 file (canread).

	#r/canread

up->shm = Ready*
c->aux = 
 */
enum
{
	NFD = 16,

	Qcanread = 0,
	Qready
};

/*
struct Qid
{
	u64	path; Qctl or Qready
	u32	vers; for version control
	uchar	type; QTFILE | QTDIR;
} Qid;
also, keeping Chan.aux = for QTFILE, Svalue*. For QTDIR, Sgrp (up->shm).
 */

Why do I even need locks? It does not work across processes anyway
typedef struct Readyfd;
struct Readyfd
{
	Qlock;
	s32 fd;
	Queue *q;
	s32 ready;
	u8 stop;
	Proc *kproc;
};

typedef struct Ready;
struct Ready
{
	Qlock;
	Readyfd *rfd[[NFD];
	s32 nrfd;
	Queue *commq;	/* queue for the different watcher kproc's to communicate */
};

static int
rgen(Chan *c, char *name, Dirtab*, int, int s, Dir *dp)
{
	Sgrp *g;
	Svalue *v;
	Qid q;
	s32 i;

	if(s == DEVDOTDOT){
		devdir(c, c->qid, "#s", 0, eve, 0775, dp);
		return 1;
	}

	if(c->qid == Qcanread){
		mkqid(&q, Qcanread, 0, QTFILE);
		devdir(c, q, "canread", 0, eve, 0664, dp);
		return 1;
	}
	return -1;
}

static Chan*
rattach(char *spec)
{
	Chan *c;
	Sgrp *g;

	c = devattach('r', spec);
	mkqid(&c->qid, 0, 0, QTDIR);
	return c;
}

static Walkqid*
rwalk(Chan *c, Chan *nc, char **name, int nname)
{
	Walkqid *wq;

	qlock(up->readyfds);
	wq = devwalk(c, nc, name, nname, 0, 0, shmgen);
	if(wq != nil && wq->clone != nil && wq->clone != c){
		wq->clone->aux = up->readyfds;
		DBG("shmwalk wq->clone->path %s mode 0x%ux\n"
			"	wq->clone->qid.path 0x%zux wq->clone->qid.vers %d\n"
			"	wq->clone->qid.type %d 0x%ux\n"
			"	wq->clone->aux 0x%zx\n",
			chanpath(nc), wq->clone->mode,
			wq->clone->qid.path, wq->clone->qid.vers,
			wq->clone->qid.type, wq->clone->qid.type,
			wq->clone->aux);
	}
	qunlock(up->readyfds);
	return wq;
}

static int
rstat(Chan *c, uchar *db, int n)
{
	qlock(up->readyfds);
	s = devstat(c, db, n, 0, 0, shmgen);
	qunlock(up->readyfds);
	return s;
}

static Chan*
ropen(Chan *c, u32 omode)
{
	Ready *r;
	int trunc;

	if((r = up->readyfds) == nil)
		error(Enonexist);

	if(c->qid.type & QTDIR) {
		if(omode != OREAD)
			error(Eperm);
	}else if(c->qid.path == Qready && omode != OREAD){
			error(Eperm);
	}else {
		trunc = omode & OTRUNC;
		if(omode != OREAD)
			error(Eperm);

		qlock(r);
		r->commq = qopen(1024, 0, 0, 0);
		if(trunc) { /* shoud be Qwatch */
			for(i = 0; i < r->nrfd; i++){
				r->rfd[i].stop = 1;
				/* TODO shutdown kproc's send a note to any running kprocs */
			}
			r->nrfd = 0;
		}
		qunlock(r);
	}
	c->mode = openmode(omode);
	c->offset = 0;
	c->flag |= COPEN;
	return c;
}

static void
rcreate(Chan *c, char *name, u32 omode, u32)
{
	Sgrp *g;
	Svalue *v, *ev;
	s32 i;

	if((r = up->readyfds) == nil)
		error(Enonexist);

	error(Eexist);
}

rread(Chan *c, void *a, s32 n, s64 off)
{
	Sgrp *g;
	Svalue *v;
	u64 offset = off;

	if(c->qid.type & QTDIR)
		return devdirread(c, a, n, 0, 0, shmgen);

	if((r = up->readyfds) == nil)
		error(Enonexist);

	return qread(r->commq, a, n);
}

/* TODO close kproc by sending a note */
static void
stopwatchers(void)
{
	Ready *r;

	if((r = up->readyfds) == nil)
		error(Enonexist);

	if(r->commq != nil)
		qhangup(r->commq, nil);
	for(i = 0; i < r->rnfd; i++){
		r->rfd[i].stop = 1;
		r->rfd[i].fd = -1;
	}
}

/*
	wrap this in an alarm() so it does not block forever?
	should be using qread() instead? qcanread does not block(?)
	TODO double check wv values
 */
static void
startwatcher(Readyfd *rfd)
{
	char s[16];

	rfd->kproc = up;
	while(rfd->stop == 0 && wv != 0 && wv != -1){
		qhasdata(rfd->q);
		n = snprint(s, 16, "%d\n", rfd->fd);
		wv = qwrite(rfd->commq, s, n);
	}
}

/* read the space separated fd's and add them to the Readyfd* list */
static s32
rwrite(Chan *c, void *a, s32 n, s64)
{
	u8 *s, *n, *end, name[KNAMELEN];
	s32 nfd, fd;

	if(n <= 0)
		return 0;
	if(offset > Maxshmsize || n > (Maxshmsize - offset))
		error(Etoobig);

	if((r = up->readyfds) == nil)
		error(Enonexist);

	stopwatchers();
	r->nrfd = 0;
	end = (u8*)a+n;
	s = (u8*)a;
	nfd = 0;
	while(s < end){
		fd = -1;
		fd = strtoul(s, &n, 0);
		if(s == n || fd == -1)
			break;
		s = n;
		nfd++;
		if(nfd > NFD)
			error(Etoobig);
		i = r->nrfd;
		r->rfd[i].fd = fd;
		r->rfd[i].ready = 0;
		r->rfd[i].commq = r->commq;
		snprint(name, KNAMELEN, "watch %d for %d", fd, up->pid);
		kproc(name, startwatcher, &r->rfd[i], 0);
		r->nrfd++;
	}
	qunlock(r);

	return n;
}

static void
shmclose(Chan *c)
{
	stopwatchers();
}

Dev shmdevtab = {
	'r',
	"ready",

	devreset,
	devinit,
	devshutdown,
	rattach,
	rwalk,
	rstat,
	ropen,
	rcreate,
	rclose,
	rread,
	devbread,
	rwrite,
	devbwrite,
	devremove,
	devwstat
};
