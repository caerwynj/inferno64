#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

static int debug = 0;

/*
	Provides #r to notify when the pipes have data to be read
	#r/canread	watch 0 3 4 # to watch for data on fd[0], fd[3] and fd[4]

	why not add this to devproc? Too much complexity in devproc?
		It belongs there..
		instead of 2 files (watch and ready). Use 1 file (canread).
 */
enum
{
	NFD = 16,

	Qcanread = 0,
};

typedef struct Readyfd Readyfd;
struct Readyfd
{
	s32 fd;
	Queue *q;
	s32 ready;
	Proc *kproc;
	Queue *commq;	/* same as Canread.commq */
	u8 stop;
};

typedef struct Canread Canread;
struct Canread
{
	Readyfd rfd[NFD];
	s32 nrfd;
	Queue *commq;	/* queue for the different watcher kproc's to communicate */
};

static int
crgen(Chan *c, char *name, Dirtab*, int, int s, Dir *dp)
{
	Qid q;

	if(s == DEVDOTDOT){
		devdir(c, c->qid, "#R", 0, eve, 0775, dp);
		return 1;
	}

	if(s == 0){
		mkqid(&q, Qcanread, 0, QTFILE);
		devdir(c, q, "canread", 0, eve, 0664, dp);
		return 1;
	}
	return -1;
}

static Chan*
crattach(char *spec)
{
	Chan *c;

	if(up->canread == nil)
		up->canread = malloc(sizeof(Canread));

	if(up->canread == nil)
		error(Enomem);

	c = devattach('R', spec);
	mkqid(&c->qid, 0, 0, QTDIR);
	return c;
}

static Walkqid*
crwalk(Chan *c, Chan *nc, char **name, int nname)
{
	return devwalk(c, nc, name, nname, 0, 0, crgen);
}

static int
crstat(Chan *c, uchar *db, int n)
{
	return devstat(c, db, n, 0, 0, crgen);
}

static Chan*
cropen(Chan *c, u32 omode)
{
	Canread *r;
	int trunc, i;

	if((r = up->canread) == nil)
		error(Enonexist);

	if(c->qid.type & QTDIR) {
		if(omode != OREAD)
			error(Eperm);
	}else if(c->qid.path == Qcanread){
		if(r->commq == nil)
			r->commq = qopen(1024, 0, 0, 0);
		trunc = omode & OTRUNC;
		if(trunc) { /* shoud be Qwatch */
			for(i = 0; i < r->nrfd; i++){
				r->rfd[i].stop = 1;
				/* TODO shutdown kproc's send a note to any running kprocs */
			}
			r->nrfd = 0;
		}
	}else {
		error(Enonexist);
	}
	c->mode = openmode(omode);
	c->offset = 0;
	c->flag |= COPEN;
	return c;
}

static void
crcreate(Chan *c, char *name, u32 omode, u32)
{

	if(up->canread == nil)
		error(Enonexist);

	error(Eexist);
}

crread(Chan *c, void *a, s32 n, s64)
{
	Canread *r;
	if(c->qid.type & QTDIR)
		return devdirread(c, a, n, 0, 0, crgen);

	if((r = up->canread) == nil)
		error(Enonexist);

	return qread(r->commq, a, n);
}

/* TODO close kproc by sending a note */
static void
stopwatchers(void)
{
	Canread *r;
	int i;

	if((r = up->canread) == nil)
		error(Enonexist);

	if(r->commq != nil)
		qhangup(r->commq, nil);
	for(i = 0; i < r->nrfd; i++){
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
startwatcher(void *p)
{
	char s[16];
	s32 wv, n;
	Readyfd *rfd;

	if(p == nil)
		error(Enonexist);

	rfd = p;
	rfd->kproc = up;
	while(rfd->stop == 0 && wv != 0 && wv != -1){
		qhasdata(rfd->q);
		n = snprint(s, 16, "%d\n", rfd->fd);
		wv = qwrite(rfd->commq, s, n);
	}
}

/* read the space separated fd's and add them to the Readyfd* list */
static s32
crwrite(Chan *c, void *a, s32 n, s64 offset)
{
	s8 *s, *p, *end, name[KNAMELEN];
	s32 nfd, fd, i;
	Canread *r;

	if((r = up->canread) == nil)
		error(Enonexist);

	stopwatchers();
	r->nrfd = 0;
	end = (s8*)a+n;
	s = (s8*)a;
	nfd = 0;
	while(s < end){
		fd = -1;
		fd = strtoul(s, &p, 0);
		if(s == p || fd == -1)
			break;
		s = p;
		nfd++;
		if(nfd > NFD)
			error(Etoobig);
		i = r->nrfd;
		r->rfd[i].fd = fd;
		r->rfd[i].ready = 0;
		r->rfd[i].commq = r->commq;
		snprint(name, KNAMELEN, "watch %d for %d", fd, up->pid);
		kproc(name, startwatcher, (void*)&(r->rfd[i]), 0);
		r->nrfd++;
	}

	return n;
}

static void
crclose(Chan *c)
{
	stopwatchers();
}

Dev readydevtab = {
	'R',
	"ready",

	devreset,
	devinit,
	devshutdown,
	crattach,
	crwalk,
	crstat,
	cropen,
	crcreate,
	crclose,
	crread,
	devbread,
	crwrite,
	devbwrite,
	devremove,
	devwstat
};
