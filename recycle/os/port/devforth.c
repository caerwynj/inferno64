#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

#include	"forth.h"

static int debug = 0;
extern Fentry fentries[];

/*
 1. Provides #f/forth/new to start new forth processes
 2. pipe data between the readers and writers of #f/forth/pid/(stdin stdout stderr)
		do not do this. too much work. use the existing mechanism.
		use the parent's Fgrp - easy, simple and it works fine
	-- the above is wrong. It is hard to separate out the process if it is using the parent's fd's.
		For now, use the stdin, stdout and stderr mechanism.
		If the performance is good enough, add more syscalls and then replace dis/init with forth
TODO
	add initial memsize to Qnew
 */
enum
{
	Argslen		= 256,
	NForthproc	= 256,
	QMAX		= 192*1024-1,

	Qtopdir		= 0,	/* #f */
	Qforthdir,	/* #f/forth */
	Qnew,		/* #f/forth/new */
	Qfprocdir,	/* per forth proc */
	Qctl,
	Qvars,
	/* Qlisten, might be good to have later on for servers */
};

/*
 * Qids are set in path:
 *	 4 bits of file type (qids above)
 *	23 bits of process slot number (procindex(pid)) + 1; 0 means not attached to forth proc
 *	     in vers,
 *	32 bits of pid, for consistency checking

struct Qid
{
	u64	path;
		5 bits of file type (qids above)
		59 bits of process slot number (procindex(pid)) + 1; 0 means not attached to forth proc
	u32	vers; pid, for consistency checking
	uchar	type; QTFILE | QTDIR;
} Qid;
also, keeping Chan.aux = Proc* of the corresponding forthproc
 */
#define	QSHIFT	5	/* location in qid of proc slot # */

#define	QID(q)		((((u32)(q).path)&0x0000001F)>>0)
#define	SLOT(q)		(((((u32)(q).path)&0x07FFFFFE0)>>QSHIFT)-1)
#define	PID(q)		((q).vers)
#define	NOTEID(q)	((q).vers)

/* TODO implement NEWPGRP */
typedef struct Params Params;
struct Params
{
	u8 newenv, newfd, newns, shmem, nodevs, redirfds;
	s32 stdinfd, stdoutfd, stderrfd;
	s32 *keepfds, *closefds;
	s32 nkeepfds, nclosefds;
	char *args;
	int nargs;	/* number of bytes in args */
};

int nforthprocs = 0;
Proc *fhead, *ftail;
static QLock forthlock;
static char forthname[] = "forth";
extern intptr forthmain(u8 *);

static void
flock(void)
{
	qlock(&forthlock);
}

static int
canflock(void)
{
	return canqlock(&forthlock);
}

static void
funlock(void)
{
	qunlock(&forthlock);
}

static Params
parseparams(char *params)
{
	struct Params p = {0};
	s8 *s, *e, *end;
	s32 i;

	p.newenv = p.newfd = p.newns = 1;
	p.shmem = p.nodevs = p.redirfds = 0;
	p.stdinfd = 0;
	p.stdoutfd = 1;
	p.stderrfd = 2;
	p.nkeepfds = p.nclosefds = 0;
	p.keepfds = p.closefds = nil;
	if(params == nil)
		return p;
	s = params;
	end = s+strlen(params)+1;
	while (s != nil && s < end){
		if(cistrncmp("NEWENV", s, 6) == 0){
			p.newenv = 1;
			s+=6;
		}else if(cistrncmp("FORKENV", s, 7) == 0){
			p.newenv = 0;
			s+=7;
		}else if(cistrncmp("NEWFD", s, 5) == 0){
			p.newfd = 1;
			s+=5;
		}else if(cistrncmp("FORKFD", s, 6) == 0){
			p.newfd = 0;
			s+=6;
		}else if(cistrncmp("NEWNS", s, 5) == 0){
			p.newns = 1;
			s+=5;
		}else if(cistrncmp("FORKNS", s, 6) == 0){
			p.newns = 0;
			s+=6;
		}else if(cistrncmp("NEWSHMEM", s, 8) == 0){
			p.shmem = 2;
			s+=8;
		}else if(cistrncmp("SHMEM", s, 5) == 0){
			p.shmem = 1;
			s+=5;
		}else if(cistrncmp("NOSHMEM", s, 7) == 0){
			p.shmem = 0;
			s+=7;
		}else if(cistrncmp("DEVS", s, 4) == 0){
			p.nodevs = 0;
			s+=4;
		}else if(cistrncmp("NODEVS", s, 6) == 0){
			p.nodevs = 1;
			s+=6;
		}else if(cistrncmp("REDIRFDS", s, 8) == 0){
			p.redirfds = 1;
			s += 8;
			for(i=0; i<3; i++){
				if(i == 0)
					p.stdinfd = strtol(s,&e,0);
				else if(i == 1)
					p.stdoutfd = strtol(s,&e,0);
				else if(i == 2)
					p.stderrfd = strtol(s,&e,0);
				if(s == e)
					break;
				s = e+1;
			}
		}else if(cistrncmp("KEEPFDS", s, 7) == 0){
			s += 7;
			p.keepfds = smalloc(up->fgrp->nfd*sizeof(s32));
			for(i=0; ;i++,p.nkeepfds++){
				if(i>=up->fgrp->nfd){
					print("should not happen\n");
					error(Etoobig);
				}
				p.keepfds[i] = strtol(s, &e, 0);
				if(s == e)
					break;
				s = e+1;
			}
		}else if(cistrncmp("CLOSEFDS", s, 8) == 0){
			s += 8;
			p.closefds = smalloc(up->fgrp->nfd*sizeof(s32));
			for(i=0; ;i++,p.nclosefds++){
				if(i>=up->fgrp->nfd){
					print("should not happen\n");
					error(Etoobig);
				}
				p.closefds[i] = strtol(s, &e, 0);
				if(s == e)
					break;
				s = e+1;
			}
		}else if(cistrncmp("ARGS", s, 4) == 0){ // until the end or Argslen = 256 bytes
			s += 4;
			p.nargs = strlen(s);
			p.args = malloc(p.nargs);
			strncpy(p.args, s, p.nargs);
		}else if(*s == ' ' || *s == '	' || *s == '\r' || *s == '\n'){
			/* would be nice to use isspace(*s) here */
			s++;
		}else if(*s == '\0' || *s < 'A' || *s > 'z'){
			/* would be nice to use isalpha(*s) here */
			break;
		}else{
			print("parseparams: unknown parameter -%s- -%s- cistrncmp(\"NEWENV\", s, 6) %d %d %d\n",
					params, s, cistrncmp("NEWENV", s, 6), cistrncmp("newenv", s, 6),
					cistrncmp("newenv", "NEWENV", 6));
			error(Ebadctl);
		}
	}
	if(1 == 1){
		print("parseparams newenv %d newfd %d newns %d shmem %d nodevs %d\n"
				"	redirfds %d %d %d\n"
				"	args %d: %s\n",
				p.newenv, p.newfd, p.newns, p.shmem, p.nodevs,
				p.stdinfd, p.stdoutfd, p.stderrfd,
				p.nargs, p.args);
		if(p.nclosefds > 0){
			print("	closefds ");
			for(i = 0; i < p.nclosefds; i++){
				print(" %d", p.closefds[i]);
			}
			print("\n");
		}
		if(p.nkeepfds > 0){
			print("	keepfds ");
			for(i = 0; i < p.nkeepfds; i++){
				print(" %d", p.keepfds[i]);
			}
			print("\n");
		}
	}
	return p;
}

void
loadforthdictionary(u8 *fmem)
{
	intptr i;
	Fentry *f;
	u8 *h, *dtop, *vh, nbytes, len;
	Bhdr *b;

	h = fmem+DICTIONARY;
	dtop = nil;
	vh = fmem+FORTHVARS;
	DBG("loadforthdictionary fmem 0x%p\n"
			"	here 0x%p dtop 0x%p there 0x%p\n"
			"	(intptr*)(fmem + DTOP) 0x%p *(intptr*)(fmem + DTOP) 0x%zX\n"
			"	PSTACK 0x%p (intptr*)(fmem + PSTACK) 0x%p\n"
			"	RSTACK 0x%p (intptr*)(fmem + RSTACK) 0x%p\n"
			"	FORTHEND 0x%p (intptr*)(fmem + FORTHEND) 0x%p\n",
			fmem, h, dtop, vh,
			(intptr*)(fmem + DTOP), *(intptr*)(fmem + DTOP),
			PSTACK, (intptr*)(fmem + PSTACK),
			RSTACK, (intptr*)(fmem + RSTACK),
			FORTHEND, (intptr*)(fmem + FORTHEND));
	for(i=0; i < nelem(fentries); i++){
		f = &fentries[i];
		if(f->what == Sourceline){
			DBG("%s\n", f->desc);
		}else if(f->what == Here && f->type == Absolute){
			h = fmem+DICTIONARY+f->here;
			*(intptr*)h = f->p;
			DBG("	%s 0x%zX: 0x%zX %lld: %lld\n", f->desc, (intptr)h, *(intptr*)h, (intptr)h, *(intptr*)h);
		}else if(f->what == Here && f->type == Absoluteptr){
			h = fmem+DICTIONARY+f->here;
			*(intptr*)h = (intptr)f->ptr;
			DBG("	%s 0x%zX: 0x%zX %lld: %lld\n", f->desc, (intptr)h, *(intptr*)h, (intptr)h, *(intptr*)h);
		}else if(f->what == Here && f->type == Byte){
			h = fmem+DICTIONARY+f->here;
			*(s8*)h = f->b;
			DBG("	%s 0x%zX: 0x%d %lld: %d\n", f->desc, (intptr)h, *(char*)h, (intptr)h, *(char*)h);
		}else if(f->what == Here && f->type == Chars){
			h = fmem+DICTIONARY+f->here;
			len = strlen(f->str);
			strncpy((s8*)h, f->str, len);
			DBG("	%s 0x%zX: %s %lld: %s\n", f->desc, (intptr)h, (char*)h, (intptr)h, (char*)h);
		}else if(f->what == Here && f->type == Relative){
			h = fmem+DICTIONARY+f->here;
			*(intptr*)h = (intptr)fmem+f->p;
			DBG("	%s 0x%zX: 0x%zX %lld: %lld\n", f->desc, (intptr)h, *(intptr*)h, (intptr)h, *(intptr*)h);
		}else if(f->what == Here && f->type == Relativedictionary){
			h = fmem+DICTIONARY+f->here;
			*(intptr*)h = (intptr)fmem+DICTIONARY+f->p;
			DBG("	%s 0x%zX: 0x%zX %lld: %lld\n", f->desc, (intptr)h, *(intptr*)h, (intptr)h, *(intptr*)h);
		}else if(f->what == Here && f->type == Relativevar){
			h = fmem+DICTIONARY+f->here;
			*(intptr*)h = (intptr)fmem+f->p;
			DBG("	%s 0x%zX: 0x%zX %lld: %lld\n", f->desc, (intptr)h, *(intptr*)h, (intptr)h, *(intptr*)h);
		}else if(f->what == Here && f->type == End){
			h = fmem+DICTIONARY+f->here;
			DBG("	%s 0x%zX %lld\n", f->desc, (intptr)h, (intptr)h);
		}else if(f->what == There && f->type == End){
			vh = fmem+FORTHVARS+f->there;
			DBG("	%s 0x%zX %lld\n", f->desc, (intptr)vh, (intptr)vh);
		}else if(f->what == Dtop){
			dtop = (u8*)fmem+DICTIONARY+f->p;
			DBG("	%s 0x%zX %lld\n", f->desc, (intptr)dtop, (intptr)dtop);
		} else {
			panic("loadforthdictionary unknown Fentry: %s\n", f->desc);
		}
	}
	*(intptr*)(fmem + HERE) = (intptr)h;
	*(intptr*)(fmem + DTOP) = (intptr)dtop;
	*(intptr*)(fmem + THERE) = (intptr)vh;
	*(intptr*)(fmem + FTHPID) = up->pid;
	*(intptr*)(fmem + FTHPARENTPID) = up->parentpid;
	*(intptr*)(fmem + FORTHUP) = (intptr)fmem;	/* heap start */
	*(intptr*)(fmem + FORTHUPE) = (intptr)fmem+FORTHHEAPSIZE-1; /* heap end, TODO make the size variable */

	nbytes = snprint((char*)fmem + ARGSFILENAME+1, 32, "#p/%d/args", up->pid);
	*(u8*)(fmem + ARGSFILENAME) = nbytes;

	print("loadforthdictionary fmem 0x%p\n"
			"	here 0x%p dtop 0x%p there 0x%p\n"
			"	(intptr*)(fmem + DTOP) 0x%p *(intptr*)(fmem + DTOP) 0x%zX\n"
			"	PSTACK 0x%p (intptr*)(fmem + PSTACK) 0x%p\n"
			"	RSTACK 0x%p (intptr*)(fmem + RSTACK) 0x%p\n"
			"	FORTHEND 0x%p (intptr*)(fmem + FORTHEND) 0x%p\n",
			fmem, h, dtop, vh,
			(intptr*)(fmem + DTOP), *(intptr*)(fmem + DTOP),
			PSTACK, (intptr*)(fmem + PSTACK),
			RSTACK, (intptr*)(fmem + RSTACK),
			FORTHEND, (intptr*)(fmem + FORTHEND));
	D2B(b, fmem);
	DBG("Bhdr b 0x%p b->magic 0x%x b->size %zd b->allocpc 0x%zX\n",
			b, b->magic, b->size, b->allocpc);
}

/* also called by init0 for the init forth proc */
void
goforth(void *fmem)
{
	/* load dictionary */
	loadforthdictionary((u8*)fmem);
	print("goforth pid %d forthmem 0x%zx end 0x%zx forthmem+RSTACK 0x%zx\n",
		up->pid, (intptr)fmem, ((intptr*)fmem)[1], (intptr)fmem+RSTACK);
	DBG("nfentries %d\n", nelem(fentries));
	DBG("up->kstack 0x%p\n", up->kstack);
	if(waserror()){
		print("goforth error: %r\n");
		nexterror();
	}else
		forthmain((u8*)fmem);
	poperror();
	free(fmem);

	flock();
	if(up->fnext == nil && up->fprev == nil){
		fhead = nil;
		ftail = nil;
	}else if(up->fnext == nil){
		up->fprev->fnext = nil;
		ftail = up->fprev;
	}
	nforthprocs--;
	funlock();
	pexit("exit", 0);
}

void
initializeforthproc(Proc *p, Params *params)
{
	Pgrp *pg;
	Fgrp *fg;
	Egrp *eg;
	s32 i, j;
	Chan *c;

	qlock(&p->debug);
	p->psstate = 0;
	p->kp = 0;

	p->fpsave = up->fpsave;
	p->nerrlab = 0;

	kstrdup(&p->user, up->user);

	if(params->newenv == 1)
		eg = newegrp();
	else{
		eg = up->egrp;
		if(eg != nil)
			incref(eg);
	}
	p->egrp = eg;

	pg = newpgrp();
	if(params->newns == 0)
		pgrpcpy(pg, up->pgrp);
	if(pg == nil)
		panic("newforthproc: nil process group\n");
	pg->nodevs = params->nodevs;
	p->pgrp = pg;

	/*
		shmem = 0, NOSHMEM no shared memory
		shmem = 1, SHMEM share memory
		shmem = 2, NEWSHMEM new shared memory, leave it as nil, attach() will create it
	 */
	if(params->shmem == 0 || params->shmem == 2){
		p->shm = nil;
	}else if(params->shmem == 1){
		if(up->shm == nil)
			up->shm = shmgrpnew();

		p->shm = up->shm;
		incref(up->shm);
	}

	fg = dupfgrp(up->fgrp);
	if(fg == nil)
		panic("newforthproc: nil file descriptor group\n");
	p->fgrp = fg;

	if(params->redirfds == 1){
		/* similar to kdup() */
		if(params->stdinfd != 0){
			fdclose(fg, 0, 0);
			c = fg->fd[params->stdinfd];
			if(c == nil)
				error(Ebadfd);
			incref(c);
			fg->fd[0] = c;
			fg->flag[0] = fg->flag[params->stdinfd];
print("stdinfd devtab[c->type]->dc %c c 0x%p chanpath(c) %s c->aux 0x%p\n", devtab[c->type]->dc, c, chanpath(c), c->aux);
		}
		if(params->stdoutfd != 1){
			fdclose(fg, 1, 0);
			c = fg->fd[params->stdoutfd];
			if(c == nil)
				error(Ebadfd);
			incref(c);
			fg->fd[1] = c;
			fg->flag[1] = fg->flag[params->stdoutfd];
		}
		if(params->stderrfd != 2){
			fdclose(fg, 2, 0);
			c = fg->fd[params->stderrfd];
			if(c == nil)
				error(Ebadfd);
			incref(c);
			fg->fd[2] = c;
			fg->flag[2] = fg->flag[params->stderrfd];
		}
	}
	if(params->nkeepfds > 0){
		/* close all except those in keepfds */
		for(i=0; i<fg->nfd; i++){
			if(fg->fd[i] == nil)
				continue;
			for(j=0; j<params->nkeepfds; j++)
				if(params->keepfds[j]==i)
					continue;
			fdclose(fg, i, 0);
		}
	}
	if(params->nclosefds > 0){
		/* close those in closefds */
		for(i=0; i<fg->nfd; i++){
			if(fg->fd[i] == nil)
				continue;
			for(j=0; j<params->nclosefds; j++)
				if(params->closefds[j]==i)
					fdclose(fg, i, 0);
		}
	}

	if(1 == 1){
		for(i=0; i<fg->nfd; i++){
			if(fg->fd[i] == nil)
				continue;
			print("fd %d chanpath(c) %s\n", i, chanpath(fg->fd[i]));
		}
	}

	p->nnote = 0;
	p->notify = nil;
	p->notified = 0;
	p->notepending = 0;

	p->procmode = 0640;
	p->privatemem = 0;
	p->noswap = 0;
	p->hang = 0;
	p->kp = 0;

	p->args = params->args;
	p->nargs = params->nargs;

	p->fmem = mallocalign(FORTHHEAPSIZE, BY2PG, 0, 0);
	if(p->fmem == nil)
		panic("newforthproc p->fmem == nil\n");

	*(intptr*)((char*)p->fmem+FORTHUP) = (intptr)p->fmem;	/* heap start */
	*(intptr*)((char*)p->fmem+FORTHUPE) = (intptr)p->fmem+FORTHHEAPSIZE-1; /* heap end */

/*	p->kpfun = func;
	p->kparg = arg;
	kprocchild(p, linkproc);*/
/* this does all of the above 3 lines */
	kprocchild(p, goforth, p->fmem);

	p->text = forthname; /* TODO change this to a kstrdup(), else pexit() free() will error */

	memset(p->time, 0, sizeof(p->time));
	p->time[TReal] = MACHP(0)->ticks;
/*	cycles(&p->kentry);
	p->pcycles = -p->kentry;*/

	p->fisgo = 1;
	qunlock(&p->debug);
	p->psstate = nil;

	print("initializeforthproc: ready p->pid %d\n", p->pid);
	ready(p);
}

/*
 * Looking from c, return the Dir entry at the index s
 *
 * mostly the same as procgen() of devproc.c
 *	and drawgen() of devdraw.c
 *
 * TODO get the permissions from Proc.procmode
		DBG("forthgen s == DEVDOTDOT c->path %s name %s s %d mode 0x%ux c->qid.path 0x%zux "
			"slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n",
			chanpath(c), name, s, c->mode, c->qid.path, SLOT(c->qid),
			QID(c->qid), c->qid.vers, c->qid.type, c->qid.type);
 */
static int
forthgen(Chan *c, char *name, Dirtab *, int, int s, Dir *dp)
{
	Qid q;
	char *ename;
	u32 pid, path;
	s32 slot, i, t;
	Proc *p, *f;

	DBG("forthgen c->path %s name %s s %d mode 0x%ux c->qid.path 0x%zux\n"
			"	slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n"
			"	c->aux 0x%p c->type 0x%x\n",
			chanpath(c), name, s, c->mode, c->qid.path, SLOT(c->qid),
			QID(c->qid), c->qid.vers, c->qid.type, c->qid.type,
			c->aux, c->type);
	/*
	 * if I do .. from #f or #f/forth
	 */
	if(s == DEVDOTDOT){
		switch(QID(c->qid)){
		case Qtopdir:
		case Qforthdir: /* the parent of #f/forth is #f */
			mkqid(&q, Qtopdir, 0, QTDIR);
			devdir(c, q, "#f", 0, eve, 0555, dp);
			break;
		case Qfprocdir:
			mkqid(&q, Qforthdir, 0, QTDIR);
			devdir(c, q, "forth", 0, eve, 0555, dp);
			break;
		default:
			panic("drawwalk %llux", c->qid.path);
		}
		return 1;
	}

	/*
	 * Top level directory contains the name of the device.
	 */
	t = QID(c->qid);
	switch(t){
	case Qtopdir:
		if(s == 0){
			mkqid(&q, Qforthdir, 0, QTDIR);
			devdir(c, q, "forth", 0, eve, 0555, dp);
			return 1;
		}
		return -1;
	}

	/*
	 * Second level contains "new" plus all the forth procs.
	 */
	switch(t){
	case Qforthdir:
		if(s == 0){
	case Qnew:	/* this label is just a comment(?), has no purpose */
		mkqid(&q, Qnew, 0, QTFILE);
		devdir(c, q, "new", 0, eve, 0666, dp);
		DBG("forthgen Qforthdir s == 0 returning Dir\n"
				"	name %s qid.path 0x%zux slot %d qid %d qid.vers %d qid.type %d 0x%ux\n"
				"	mode 0x%ux type 0x%ux\n",
				dp->name, dp->qid.path, SLOT(dp->qid), QID(dp->qid), dp->qid.vers, dp->qid.type,
					dp->qid.type,
				dp->mode, dp->type);
		return 1;
		}

		DBG("forthgen Qforthdir name %s s %d nforthprocs %d\n", name, s, nforthprocs);
		if(nforthprocs == 0)
			return -1;
		if(name != nil){
			/* ignore s and use name to find pid */
			pid = strtol(name, &ename, 10);
			if(pid==0 || ename[0]!='\0')
				return -1;
			slot = procindex(pid);
			if(slot < 0)
				return -1;
		}else{ /* without a pid in the name, use the s'th item from the list of forthproc's */
			s = s-1;
			if(s >= nforthprocs)
				return -1;
			i = 0;
			for(f = fhead; f != nil && i < s; f=f->fnext, i++)
				;
			if(f == nil || f->pid == 0)
				return -1;
			pid = f->pid;
			if(pid==0)
				return -1;
			slot = procindex(pid);
			if(slot < 0)
				return -1;
		}
		/*
		 * String comparison is done in devwalk so name must match its formatted pid
		*/
		p = proctab(slot);
		snprint(up->genbuf, sizeof(up->genbuf), "%ud", pid);
		if(name != nil && strcmp(name, up->genbuf) != 0)
			return -1;
		mkqid(&q, Qfprocdir|((slot+1)<<QSHIFT), pid, QTDIR);
		devdir(c, q, up->genbuf, 0, p->user, 0555, dp);
		DBG("forthgen Qforthdir s %d returning Dir\n"
				"	name %s qid.path 0x%zux slot %d qid %d qid.vers %d qid.type %d 0x%ux\n"
				"	mode 0x%ux type 0x%ux\n",
				s,
				dp->name, dp->qid.path, SLOT(dp->qid), QID(dp->qid), dp->qid.vers, dp->qid.type,
					dp->qid.type,
				dp->mode, dp->type);
		return 1;
	}

	/*
	 * Third level.
	 */
	p = proctab(SLOT(c->qid));
	path = c->qid.path&~((1<<QSHIFT)-1);	/* slot component */
	switch(s){
	case 0:
		mkqid(&q, path|Qctl, c->qid.vers, QTFILE);
		devdir(c, q, "ctl", 0, p->user, 0600, dp);
		break;
	case 1:
		mkqid(&q, path|Qvars, c->qid.vers, QTFILE);
		devdir(c, q, "vars", 0, p->user, 0600, dp);
		break;
	default:
		return -1;
	}
	return 1;
}

static Chan*
forthattach(char *spec)
{
	Chan *c;

	DBG("forthattach spec %s\n", spec);
	c = devattach('f', spec);
	mkqid(&c->qid, Qtopdir, 0, QTDIR);
	DBG("forthattach c->path %s mode 0x%ux\n"
		"	c->qid.path 0x%zux slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n"
		"	c->aux 0x%p c->type 0x%ux devtab[c->type]->dc %c\n",
		chanpath(c), c->mode, c->qid.path, SLOT(c->qid),
		QID(c->qid), c->qid.vers, c->qid.type, c->qid.type,
		c->aux, c->type, devtab[c->type]->dc);
	return c;
}

/* The values in wq->clone (not nc) are used for the new Chan. */
static Walkqid*
forthwalk(Chan *c, Chan *nc, char **name, s32 nname)
{
	Walkqid* wq;
	s32 slot;

	DBG("forthwalk c->path %s mode 0x%ux\n"
		"		c->qid.path 0x%zux slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n"
		"		c->aux 0x%p c->type 0x%ux\n",
		chanpath(c), c->mode, c->qid.path, SLOT(c->qid),
		QID(c->qid), c->qid.vers, c->qid.type, c->qid.type,
		c->aux, c->type);
	DBG("	nname %d\n", nname);
	if(debug == 1)
		for(int i = 0; i < nname; i++)
			print("	i %d name %s\n", i, name[i]);

	if(QID(c->qid) >= Qfprocdir && c->aux == nil)
		print("c->aux is nil - should not be happening\n");

	wq = devwalk(c, nc, name, nname, nil, 0, forthgen);

	/* devwalk() clones c to nc and wq->clone->aux.
		It sets the wq->clone->qid to the qid that matches a forthgen() entry.
		forthgen() sets up the Dir (which does not include c->aux)
		Hence,
			when walking from #f/forth/pid to #f/forth/pid/file, wq->clone->aux is taken from c
			when walking from #f or #f/forth to #f/forth/pid or below, wq->clone->aux = nil
		setting wq->clone->aux to the corresponding forth Proc* when the walk is to #f/forth/pid and below
	 */
	if(wq != nil && wq->clone != nil && wq->clone != c){
		if(QID(wq->clone->qid) >= Qfprocdir){
			if(wq->clone->aux != nil)
				return wq;
			slot = procindex(wq->clone->qid.vers);
			if(slot < 0){
				print("forthopen wq->clone->qid.type & QTDIR slot < 0 -- should not be happening\n");
				error(Eprocdied);
			}
			wq->clone->aux = proctab(slot);
		}else{
			wq->clone->aux = nil;
		}
		DBG("forthwalk wq->clone->path %s mode 0x%ux\n"
			"	wq->clone->qid.path 0x%zux slot %d qid %d wq->clone->qid.vers %d\n"
			"	wq->clone->qid.type %d 0x%ux\n"
			"	wq->clone->aux 0x%p\n",
			chanpath(nc), wq->clone->mode,
			wq->clone->qid.path, SLOT(wq->clone->qid), QID(wq->clone->qid), wq->clone->qid.vers,
			wq->clone->qid.type, wq->clone->qid.type,
			wq->clone->aux);
	}
	return wq;
}

static int
forthstat(Chan *c, uchar *db, s32 n)
{
	int i;
	DBG("forthstat c->path %s\n", chanpath(c));
	i = devstat(c, db, n, nil, 0, forthgen);
	DBG("forthstat after c->path %s c->mode 0x%ux\n", chanpath(c), c->mode);
	return i;
}

/*
 * this is from devproc.c
 *  none can't read or write state on other
 *  processes.  This is to contain access of
 *  servers running as none should they be
 *  subverted by, for example, a stack attack.
 */
static void
nonone(Proc *p)
{
	if(p == up)
		return;
	if(strcmp(up->user, "none") != 0)
		return;
	if(iseve())
		return;
	error(Eperm);
}

Proc *
newforthproc(void)
{
	Proc *p;

	flock();
	if(waserror()){
		funlock();
		nexterror();
	}
	while((p = newproc()) == nil){
		freebroken();
		resrcwait("no procs for kproc");
	}
	p->fisgo = 0; /* until the pctl message comes through */
	kstrdup(&p->user, up->user);

	if(fhead == nil){
		fhead = ftail = p;
	}else{
		ftail->fnext = p;
		p->fprev = ftail;
		ftail = p;
	}
	nforthprocs++;
	funlock();
	poperror();
	return p;
}

/*
	 Opening the new file creates a forth process.	The file
	 descriptor returned from the open(2) will point to the	con-
	 trol file, ctl, of the	newly created forth process.  Reading
	 ctl returns a text string representing	the pid.
 */
static Chan*
forthopen(Chan *c, u32 omode0)
{
	Proc *p;
	Chan *tc;
	u32 pid, omode;
	s32 slot;

	DBG("forthopen c->path %s mode 0x%ux omode0 0x%ux\n"
		"	c->qid.path 0x%zux slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n"
		"	c->aux 0x%p\n",
		chanpath(c), c->mode, omode0, c->qid.path, SLOT(c->qid),
		QID(c->qid), c->qid.vers, c->qid.type, c->qid.type,
		c->aux);
	if(c->qid.type & QTDIR){
		DBG("forthopen c->qid.type & QTDIR c->path %s mode 0x%ux omode0 0x%ux\n"
			"	c->qid.path 0x%zux slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux c->aux 0x%p\n",
			chanpath(c), c->mode, omode0, c->qid.path, SLOT(c->qid),
			QID(c->qid), c->qid.vers, c->qid.type, c->qid.type, c->aux);
		tc = devopen(c, omode0, nil, 0, forthgen);
		if(QID(tc->qid) == Qfprocdir){
			slot = procindex(tc->qid.vers);
			if(slot < 0){
				print("forthopen c->qid.type & QTDIR slot < 0 -- should not be happening\n");
			}
			tc->aux = proctab(slot);
		}
		DBG("forthopen tc->qid.type & QTDIR tc->path %s mode 0x%ux omode0 0x%ux\n"
			"	tc->qid.path 0x%zux slot %d qid %d tc->qid.vers %d tc->qid.type %d 0x%ux\n"
			"	tc->qid.type %d 0x%ux tc->aux 0x%p\n",
			chanpath(tc), tc->mode, omode0, tc->qid.path, SLOT(tc->qid),
			QID(tc->qid), tc->qid.vers, tc->qid.type, tc->qid.type,
			tc->qid.type & QTDIR, tc->qid.type & QTDIR, tc->aux);
		return tc;
	}

	if(QID(c->qid) == Qnew){
		p = newforthproc();
		c->aux = p;
		slot = procindex(p->pid);
		if(slot < 0)
			panic("forthopen");
		mkqid(&c->qid, Qctl|(slot+1)<<QSHIFT, p->pid, QTFILE);
		char path[64];
		snprint(path, 64, "#f/forth/%ud/ctl", p->pid);
		free(c->path);
		c->path = newpath(path);
		print("forthopen: new proc pid %d slot %d SLOT(c->qid) %d chanpath(c) %s\n"
				"	c->aux 0x%p\n",
				p->pid, slot, SLOT(c->qid), chanpath(c), c->aux);
	}

	p = proctab(SLOT(c->qid));
	eqlock(&p->debug);
	if(waserror()){
		print("forthopen: waserror() loop\n");
		qunlock(&p->debug);
		nexterror();
	}
	pid = PID(c->qid);
	if(p->pid != pid){
		print("forthopen Eprocdied\n");
		error(Eprocdied);
	}

	omode = openmode(omode0);

	switch(QID(c->qid)){
	case Qnew:
		break;
	case Qctl:
		break;
	case Qvars:
		if(p->kp || p->privatemem)
			error(Eperm);
		break;
	default:
		print("forthopen error Egreg %#ux\n", QID(c->qid));
		error(Egreg);
	}
	nonone(p);

	/* Affix pid to qid */
	if(pid == 0){
		print("forthopen Eprocdied\n");
		error(Eprocdied);
	}
	c->qid.vers = pid;

	tc = devopen(c, omode, 0, 0, forthgen);

	qunlock(&p->debug);
	poperror(); /* eqlock */
	DBG("forthopen returning tc->path %s mode 0x%ux omode0 0x%ux\n"
			"	tc->qid.path 0x%zux slot %d qid %d tc->qid.vers %d tc->qid.type %d 0x%ux\n"
			"	tc->aux 0x%p\n",
			chanpath(c), tc->mode, omode0, tc->qid.path, SLOT(tc->qid),
			QID(tc->qid), tc->qid.vers, tc->qid.type, tc->qid.type,
			tc->aux);
	return tc;
}

static void
forthclose(Chan *c)
{
	DBG("forthclose c->path %s up->pid %d c->ref %d\n",
			chanpath(c), up->pid, c->ref);
	/* TODO close the Chan*? */
	return;
}

/*
	DBG("forthread c->path %s up->pid %d\n", chanpath(c), up->pid);
	DBG("forthread c->path %s mode 0x%ux\n"
			"	c->qid.path 0x%zux slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n"
			"	c->aux 0x%p\n",
			chanpath(c), c->mode, c->qid.path, SLOT(c->qid),
			QID(c->qid), c->qid.vers, c->qid.type, c->qid.type,
			c->aux);
	DBG("forthread c->path %s f->pid %d p->pid %d\n", chanpath(c), f->pid, p->pid);
		str[rv]='\0';
		rv = readstr(0, buf, rv, str);
		DBG("forthread c->path %s up->pid %d f 0x%zx f->frq 0x%zx rv %d buf %s\n",
				chanpath(c), up->pid, f, f->frq, rv, buf);
		str[rv]='\0';
		rv = readstr(off, buf, rv, str);
		DBG("forthread c->path %s up->pid %d f 0x%zx rv %d buf %s\n",
			chanpath(c), up->pid, f, rv, buf);
	DBG("forthread c->path %s returning rv %d bytes f->pid %d\n", chanpath(c), rv, f->pid);
 */
s32
forthread(Chan *c, void *buf, s32 n, s64 off)
{
	Proc *p, *f;
	char str[16] = "";
	s32 rv = 0;
	
	if(c->qid.type & QTDIR)
		return devdirread(c, buf, n, nil, 0, forthgen);

	f = c->aux;
	p = proctab(SLOT(c->qid));
	if(p->pid != PID(c->qid)){
		print("forthread returning nil p->pid != PID(c->qid) c->path %s"
				"	up->pid %d p->pid %d PID(c->qid) %d\n",
				chanpath(c), up->pid, p->pid, PID(c->qid));
		return readstr(off, buf, n, nil);
	}
	if(f == nil){
		print("forthread c->aux == nil c->path %s up->pid %d PID(c->qid) %d\n",
			chanpath(c), up->pid, PID(c->qid));
		return readstr(off, buf, n, nil);
	}

	DBG("forthread c->path %s f->pid %d\n", chanpath(c), f->pid);
	switch(QID(c->qid)){
	case Qctl:
		snprint(str, 16, "%d", p->pid);
		rv = readstr(off, buf, n, str);
		str[rv]='\0';
		DBG("forthread rv %d buf %s\n", rv, buf);
		break;
	case Qvars: /* TODO */
		error(Ebadarg);
	default:
		print("unknown qid in forthread\n");
		error(Egreg);
	}

	return rv;
}

/*
	DBG("forthwrite c->path %s up->pid %d\n", chanpath(c), up->pid);
	DBG("forthwrite c->path %s mode 0x%ux\n"
			"	c->qid.path 0x%zux slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n"
			"	c->aux 0x%p\n",
			chanpath(c), c->mode, c->qid.path, SLOT(c->qid),
			QID(c->qid), c->qid.vers, c->qid.type, c->qid.type,
			c->aux);
		DBG("forthwrite c->path %s up->pid %d f 0x%p f->frq 0x%p n %d buf %s\n",
				chanpath(c), up->pid, f, f->frq, n, buf);
		((char*)buf)[n] = '\0';
		DBG("forthwrite c->path %s up->pid %d n %d buf %s\n",
				chanpath(c), up->pid, n, buf);
 */
static s32
forthwrite(Chan *c, void *buf, s32 n, s64)
{
	Proc *p, *f;
	s32 rv = 0;
	Params params;

	if(c->qid.type & QTDIR)
		return devdirread(c, buf, n, nil, 0, forthgen);

	f = c->aux;
	p = proctab(SLOT(c->qid));
	if(p->pid != PID(c->qid)){
		print("forthwrite returning nil p->pid != PID(c->qid) c->path %s"
				"	up->pid %d p->pid %d PID(c->qid) %d\n",
				chanpath(c), up->pid, p->pid, PID(c->qid));
		error(Eprocdied);
	}
	if(f == nil){
		print("forthwrite f == nil c->path %s"
				"	up->pid %d p->pid %d PID(c->qid) %d\n",
				chanpath(c), up->pid, p->pid, PID(c->qid));
		error(Eprocdied);
	}

	DBG("forthwrite c->path %s f->pid %d\n", chanpath(c), f->pid);
	switch(QID(c->qid)){
	case Qctl:
		if(f->fisgo == 0){
			/* pctl message */
			((char*)buf)[n] = '\0';
			DBG("forthwrite n %d buf %s\n", n, buf);
			params = parseparams(buf);
			initializeforthproc(f, &params);
		}else
			error(Ebadctl);
		break;
	case Qvars: /* TODO */
		error(Ebadarg);
	default:
		print("unknown qid in forthwriten");
		error(Egreg);
	}
	return rv;
}

/* sets up the forth environment for the forth init */
void
forthinit(void)
{
	Proc *p;

	p = up;
	if(p == nil)
		panic("goforth up == nil\n");

	p->fmem = mallocalign(FORTHHEAPSIZE, BY2PG, 0, 0);
	if(p->fmem == nil)
		panic("goforth p->fmem == nil\n");

	*(intptr*)((char*)p->fmem+FORTHUP) = (intptr)p->fmem;	/* heap start */
	*(intptr*)((char*)p->fmem+FORTHUPE) = (intptr)p->fmem+FORTHHEAPSIZE-1; /* heap end */

	p->fisgo = 1;
}

Dev forthdevtab = {
	'f',
	"forth",

	devreset,
	forthinit,
	devshutdown,
	forthattach,
	forthwalk,
	forthstat,
	forthopen,
	devcreate,
	forthclose,
	forthread,
	devbread,
	forthwrite,
	devbwrite,
	devremove,
	devwstat,
};
