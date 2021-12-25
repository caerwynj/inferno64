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
	add ref's to frq, fwq and ferrq
 */
enum
{
	NForthproc	= 256,
	QMAX		= 192*1024-1,

	Qtopdir		= 0,
	Qforthdir,
	Qnew,
	Qfprocdir,
	Qctl,
	Qvars,
	Qstdin,
	Qstdout,
	Qstderr,
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

int nforthprocs = 0;
Proc *fhead, *ftail;
static QLock forthlock;

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

void
loadforthdictionary(u8 *fmem)
{
	intptr i;
	Fentry *f;
	u8 *h, *dtop;
	int n;

	h = fmem+DICTIONARY;
	dtop = nil;
	for(i=0; i < nelem(fentries); i++){
		f = &fentries[i];
		if(f->type == Header){
			*(intptr*)h = (intptr)dtop;
			DBG("Header 0x%p: 0x%zx 0x%p ", h, *(intptr*)h, dtop);
			dtop = h;
			h += sizeof(intptr);
			*h = f->hdr.len;
			DBG("len 0x%zx: 0x%d ", h, *h);
			h++;
			strncpy((s8*)h, f->hdr.name, f->hdr.len);
			DBG("name 0x%zx: ", h);
			for(n = 0; n < f->hdr.len; n++){
				DBG("%c", *(h+n));
			}
			h += f->hdr.len;
			if((f->hdr.len+1)%8 > 0){
				h += 8-((f->hdr.len+1)%8);
			}
			*(intptr*)h = (intptr)f->hdr.cfa;
			DBG(" cfa 0x%zx: 0x%zx 0x%zx\n", h, *(intptr*)h, (intptr)f->hdr.cfa);
			h += sizeof(intptr);
		}else if(f->type == IHeader){
			*(intptr*)h = (intptr)dtop;
			DBG("IHeader 0x%zx: 0x%zx 0x%zx ", h, *(intptr*)h, dtop);
			dtop = h;
			h += sizeof(intptr);
			*h = f->hdr.len | (1<<7);
			DBG("len 0x%zx: 0x%d ", h, *h);
			h++;
			strncpy((s8*)h, f->hdr.name, f->hdr.len);
			DBG("name 0x%zx: ", h);
			for(n = 0; n < f->hdr.len; n++){
				DBG("%c", *(h+n));
			}
			h += f->hdr.len;
			if((f->hdr.len+1)%8 > 0){
				h += 8-((f->hdr.len+1)%8);
			}
			*(intptr*)h = (intptr)f->hdr.cfa;
			DBG(" cfa 0x%zx: 0x%zx 0x%zx\n", h, *(intptr*)h, (intptr)f->hdr.cfa);
			h += sizeof(intptr);
		}else if(f->type == Absolute){
			*(intptr*)h = f->p;
			DBG("	0x%zx: 0x%zx 0x%zx\n", h, *(intptr*)h, (intptr)f->p);
			h += sizeof(intptr);
		}else if(f->type == FromH0){
			*(intptr*)h = (intptr)fmem+DICTIONARY+f->p;
			DBG("	0x%zx: 0x%zx 0x%zx\n", h, *(intptr*)h, (intptr)fmem+DICTIONARY+f->p);
			h += sizeof(intptr);
		}else if(f->type == Chars){
			strcpy((s8*)h, f->str);
			h += strlen(f->str);
			h++; /* leave the terminating null byte alone, though not required by forth */
		} else {
			panic("loadforthdictionary unknown Fentry\n");
		}
	}
	*(intptr*)(fmem + HERE) = (intptr)h;
	*(intptr*)(fmem + DTOP) = (intptr)dtop;
	print("loadforthdictionary fmem 0x%zx h 0x%zx dtop 0x%zx\n"
		" (intptr*)(fmem + DTOP) 0x%zx *(intptr*)(fmem + DTOP) 0x%zx\n",
		fmem, (intptr)h, (intptr)dtop, (intptr*)(fmem + DTOP), *(intptr*)(fmem + DTOP));
}

extern intptr forthmain(u8 *);
void
forthentry(void *fmem)
{
	up->type = Forth;
	print("forthentry pid %d forthmem 0x%zx end 0x%zx forthmem+RSTACK_END 0x%zx\n",
		up->pid, (intptr)fmem, ((intptr*)fmem)[1], (intptr)fmem+RSTACK_END);
	loadforthdictionary((u8*)fmem);

	/* load dictionary */
	print("forthentry pid %d forthmem 0x%zx end 0x%zx forthmem+RSTACK_END 0x%zx\n",
		up->pid, (intptr)fmem, ((intptr*)fmem)[1], (intptr)fmem+RSTACK_END);
	DBG("fentries[0].name %s\n", fentries[0].hdr.name);
	DBG("fentries[1].name %s nfentries %d\n", fentries[1].hdr.name, nelem(fentries));
	if(waserror()){
		print("forthentry error: %r\n");
		poperror();
	}else
		forthmain((u8*)fmem);
print("after forthmain\n");
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
	qfree(up->frq);
	qfree(up->fwq);
	qfree(up->ferrq);
	print("before pexit\n");
	pexit("exit", 0);
}

Proc *
newforthproc(Chan *cin, Chan *cout, Chan *cerr)
{
	Proc *p;
	Pgrp *pg;
	Fgrp *fg;
	Egrp *eg;
	s32 slot;
	char path[64];

	while((p = newproc()) == nil){
/* TODO		freebroken(); */
		resrcwait("no procs for kproc");
	}

	qlock(&p->debug);
	p->psstate = 0;
	p->kp = 0;

	p->fpsave = up->fpsave;
	p->nerrlab = 0;

	kstrdup(&p->env->user, up->env->user);

	pg = newpgrp();
	pgrpcpy(pg, up->env->pgrp);
	if(pg == nil)
		panic("newforthproc: nil process group\n");
	p->env->pgrp = pg;

	fg = dupfgrp(up->env->fgrp);
	if(fg == nil)
		panic("newforthproc: nil file descriptor group\n");
	p->env->fgrp = fg;
	fg->fd[0]->mode = up->env->fgrp->fd[0]->mode;
	fg->fd[1]->mode = up->env->fgrp->fd[1]->mode;
	fg->fd[2]->mode = up->env->fgrp->fd[2]->mode;
	cclose(fg->fd[0]);
	cclose(fg->fd[1]);
	cclose(fg->fd[2]);
	cin->mode = up->env->fgrp->fd[0]->mode;
	cout->mode = up->env->fgrp->fd[1]->mode;
	cerr->mode = up->env->fgrp->fd[2]->mode;
		slot = procindex(p->pid);
		if(slot < 0)
			panic("forthopen");
	mkqid(&cin->qid, Qstdin|((slot+1)<<QSHIFT), p->pid, QTFILE);
	mkqid(&cout->qid, Qstdout|((slot+1)<<QSHIFT), p->pid, QTFILE);
	mkqid(&cerr->qid, Qstderr|((slot+1)<<QSHIFT), p->pid, QTFILE);
	snprint(path, 64, "#f/forth/%ud/stdin", p->pid);
	cin->path = newpath(path);
	fg->fd[0] = cin;
	snprint(path, 64, "#f/forth/%ud/stdout", p->pid);
	cout->path = newpath(path);
	fg->fd[1] = cout;
	snprint(path, 64, "#f/forth/%ud/stderr", p->pid);
	cerr->path = newpath(path);
	fg->fd[2] = cerr;

	/* need a waserror() around these */
	/* not bothering with kick() functions */
	p->frq = qopen(QMAX, Qcoalesce, nil, nil);
	p->fwq = qopen(QMAX, Qcoalesce, nil, nil);
	p->ferrq = qopen(QMAX, Qcoalesce, nil, nil);
	if(p->frq == nil || p->fwq == nil || p->ferrq == nil)
		error(Enomem);

	eg = up->env->egrp;
	if(eg != nil)
		incref(eg);
	p->env->egrp = eg;

	p->nnote = 0;
	p->notify = nil;
	p->notified = 0;
	p->notepending = 0;

	p->procmode = 0640;
	p->privatemem = 0;
	p->noswap = 0;
	p->hang = 0;
	p->kp = 0;

	p->fmem = malloc(FORTHHEAPSIZE);
	if(p->fmem == nil)
		panic("newforthproc p->fmem == nil\n");

	/* store the start address at that address too - magic check */
	((intptr*)p->fmem)[0] = (intptr)p->fmem;	/* heap start */
	((intptr*)p->fmem)[1] = (intptr)p->fmem+FORTHHEAPSIZE-1; /* heap end */

	/* already under flock() */
	if(fhead == nil){
		fhead = ftail = p;
	}else{
		ftail->fnext = p;
		p->fprev = ftail;
		ftail = p;
	}
	nforthprocs++;

/*	p->kpfun = func;
	p->kparg = arg;
	kprocchild(p, linkproc);*/
/* this does all of the above 3 lines */
	kprocchild(p, forthentry, p->fmem);

	strcpy(p->text, "forth");

	memset(p->time, 0, sizeof(p->time));
	p->time[TReal] = MACHP(0)->ticks;
/*	cycles(&p->kentry);
	p->pcycles = -p->kentry;*/

	qunlock(&p->debug);
	p->psstate = nil;

	ready(p);
	return p;
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
			"	c->aux 0x%zx c->type 0x%x\n",
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
		devdir(c, q, up->genbuf, 0, p->env->user, 0555, dp);
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
		devdir(c, q, "ctl", 0, p->env->user, 0600, dp);
		break;
	case 1:
		mkqid(&q, path|Qvars, c->qid.vers, QTFILE);
		devdir(c, q, "vars", 0, p->env->user, 0600, dp);
		break;
	case 2:
		mkqid(&q, path|Qstdin, c->qid.vers, QTFILE);
		devdir(c, q, "stdin", 0, p->env->user, 0600, dp);
		break;
	case 3:
		mkqid(&q, path|Qstdout, c->qid.vers, QTFILE);
		devdir(c, q, "stdout", 0, p->env->user, 0600, dp);
		break;
	case 4:
		mkqid(&q, path|Qstderr, c->qid.vers, QTFILE);
		devdir(c, q, "stderr", 0, p->env->user, 0600, dp);
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
	return c;
}

/* The values in wq->clone (not nc) are used for the new Chan. */
static Walkqid*
forthwalk(Chan *c, Chan *nc, char **name, s32 nname)
{
	Walkqid* wq;
	s32 slot;

	DBG("forthwalk c->path %s mode 0x%ux\n"
		"	c->qid.path 0x%zux slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n"
		"	c->aux 0x%zx c->type 0x%ux\n",
		chanpath(c), c->mode, c->qid.path, SLOT(c->qid),
		QID(c->qid), c->qid.vers, c->qid.type, c->qid.type,
		c->aux, c->type);
	if(debug == 1)
		for(int i = 0; i < nname; i++){
			print("	i %d name %s\n", i, name[i]);
		}
	if(QID(c->qid) >= Qfprocdir){
		slot = procindex(c->qid.vers);
		if(slot < 0){
			print("forthopen c->qid.type & QTDIR slot < 0 -- should not be happening\n");
			error(Eprocdied);
		}
		c->aux = proctab(slot);
	}else{
		c->aux = nil;
	}
	DBG("forthwalk c->path %s mode 0x%ux\n"
		"	c->qid.path 0x%zux slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n"
		"	c->aux 0x%zx\n",
		chanpath(c), c->mode, c->qid.path, SLOT(c->qid),
		QID(c->qid), c->qid.vers, c->qid.type, c->qid.type,
		c->aux);
	wq = devwalk(c, nc, name, nname, nil, 0, forthgen);
	if(wq != nil && wq->clone != nil && wq->clone != c){
		if(QID(wq->clone->qid) >= Qfprocdir){
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
			"	wq->clone->aux 0x%zx\n",
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
	if(strcmp(up->env->user, "none") != 0)
		return;
	if(iseve())
		return;
	error(Eperm);
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
	Proc *f;
	Chan *cin, *cout, *cerr;

	DBG("forthopen c->path %s mode 0x%ux omode0 0x%ux\n"
		"	c->qid.path 0x%zux slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n"
		"	c->aux 0x%zx\n",
		chanpath(c), c->mode, omode0, c->qid.path, SLOT(c->qid),
		QID(c->qid), c->qid.vers, c->qid.type, c->qid.type,
		c->aux);
	if(c->qid.type & QTDIR){
		DBG("forthopen c->qid.type & QTDIR c->path %s mode 0x%ux omode0 0x%ux\n"
			"	c->qid.path 0x%zux slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux c->aux 0x%zx\n",
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
			"	tc->qid.type %d 0x%ux tc->aux 0x%zx\n",
			chanpath(tc), tc->mode, omode0, tc->qid.path, SLOT(tc->qid),
			QID(tc->qid), tc->qid.vers, tc->qid.type, tc->qid.type,
			tc->qid.type & QTDIR, tc->qid.type & QTDIR, tc->aux);
		return tc;
	}

	flock();
	if(waserror()){
		funlock();
		nexterror();
	}
	if(QID(c->qid) == Qnew){
		/* TODO set path */
		cin = devclone(c);
		cout = devclone(c);
		cerr = devclone(c);
		DBG("forthopen QID(c->qid) == Qnew c->path %s cin->path %s\n",
				chanpath(c), chanpath(cin));
		f = newforthproc(cin, cout, cerr);
		c->aux = cin->aux = cout->aux = cerr->aux = f;
		if(f == nil)
			error(Enodev);
		slot = procindex(f->pid);
		if(slot < 0)
			panic("forthopen");
		mkqid(&c->qid, Qctl|(slot+1)<<QSHIFT, f->pid, QTFILE);
		char path[64];
		snprint(path, 64, "#f/forth/%ud/ctl", f->pid);
		free(c->path);
		c->path = newpath(path);
		DBG("forthopen: new proc pid %d slot %d SLOT(c->qid) %d chanpath(c) %s\n",
				f->pid, slot, SLOT(c->qid), chanpath(c));
	}
	funlock();
	poperror();

	p = proctab(SLOT(c->qid));
	eqlock(&p->debug);
	if(waserror()){
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
	case Qstdin:
	case Qstdout:
	case Qstderr:
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
	if(waserror()){
		print("forthopen cclose(tc) waserror() loop\n");
		cclose(tc);
		nexterror();
	}
	poperror();

	qunlock(&p->debug);
	poperror(); /* eqlock */
	DBG("forthopen returning tc->path %s mode 0x%ux omode0 0x%ux\n"
			"	tc->qid.path 0x%zux slot %d qid %d tc->qid.vers %d tc->qid.type %d 0x%ux\n"
			"	tc->aux 0x%zx\n",
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

s32
forthread(Chan *c, void *buf, s32 n, s64 off)
{
	Proc *p, *f;
	char str[16] = "";
	s32 rv = 0;
	
	DBG("forthread c->path %s up->pid %d\n", chanpath(c), up->pid);
	DBG("forthread c->path %s mode 0x%ux\n"
			"	c->qid.path 0x%zux slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n"
			"	c->aux 0x%zx\n",
			chanpath(c), c->mode, c->qid.path, SLOT(c->qid),
			QID(c->qid), c->qid.vers, c->qid.type, c->qid.type,
			c->aux);
	if(c->qid.type & QTDIR)
		return devdirread(c, buf, n, nil, 0, forthgen);

	f = c->aux;
	p = proctab(SLOT(c->qid));
	DBG("forthread c->path %s f->pid %d p->pid %d\n", chanpath(c), f->pid, p->pid);
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

/*	eqlock(&p->debug);
	if(waserror()){
		qunlock(&p->debug);
		nexterror();
	}*/
	switch(QID(c->qid)){
	case Qctl:
		snprint(str, 16, "%d", p->pid);
		rv = readstr(off, buf, n, str);
		break;
	case Qvars: /* TODO */
		error(Ebadarg);
	case Qstdin:
		rv = qread(f->frq, buf, n);
/*		str[rv]='\0';
		rv = readstr(0, buf, rv, str);
		DBG("forthread c->path %s up->pid %d f 0x%zx f->frq 0x%zx rv %d buf %s\n",
				chanpath(c), up->pid, f, f->frq, rv, buf); */
		break;
	case Qstdout:
		rv = qread(f->fwq, buf, n);
/*		str[rv]='\0';
		rv = readstr(off, buf, rv, str);
		DBG("forthread c->path %s up->pid %d f 0x%zx rv %d buf %s\n",
			chanpath(c), up->pid, f, rv, buf); */
		break;
	case Qstderr:
		rv = qread(f->ferrq, buf, n);
		break;
	default:
		print("unknown qid in forthread\n");
		error(Egreg);
	}

/*	qunlock(&p->debug);
	poperror();*/
	DBG("forthread c->path %s returning rv %d bytes f->pid %d\n", chanpath(c), rv, f->pid);
	return rv;
}

static s32
forthwrite(Chan *c, void *buf, s32 n, s64)
{
	Proc *p, *f;
	s32 rv = 0;

	DBG("forthwrite c->path %s up->pid %d\n", chanpath(c), up->pid);
	DBG("forthwrite c->path %s mode 0x%ux\n"
			"	c->qid.path 0x%zux slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n"
			"	c->aux 0x%zx\n",
			chanpath(c), c->mode, c->qid.path, SLOT(c->qid),
			QID(c->qid), c->qid.vers, c->qid.type, c->qid.type,
			c->aux);
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

/*	eqlock(&p->debug);
	if(waserror()){
		qunlock(&p->debug);
		nexterror();
	}*/
	switch(QID(c->qid)){
	case Qctl:
		print("forthwrite: writing to Qctl, ignored\n");
		break;
	case Qvars: /* TODO */
		error(Ebadarg);
	case Qstdin:
		((char*)buf)[n] = '\0';
		DBG("forthwrite c->path %s up->pid %d f 0x%zx f->frq 0x%zx n %d buf %s\n",
				chanpath(c), up->pid, f, f->frq, n, buf);
		rv = qwrite(f->frq, buf, n);
		DBG("forthwrite after qwrite\n");
		break;
	case Qstdout:
		rv = qwrite(f->fwq, buf, n);
		break;
	case Qstderr:
		rv = qwrite(f->ferrq, buf, n);
		break;
	default:
		print("unknown qid in forthwriten");
		error(Egreg);
	}

/*	qunlock(&p->debug);
	poperror();*/
	DBG("forthwrite written rv %d out of %d bytes\n", rv, n);
	return rv;
}

Dev forthdevtab = {
	'f',
	"forth",

	devreset,
	devinit,
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
