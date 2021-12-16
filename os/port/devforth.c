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
	/* Qlisten, might be good to have later on for servers */
};

/*
 * Qids are, in path:
 *	 4 bits of file type (qids above)
 *	23 bits of process slot number (procindex(pid)) + 1; 0 means not attached to forth proc
 *	     in vers,
 *	32 bits of pid, for consistency checking
 */
#define	QSHIFT	5	/* location in qid of proc slot # */

#define	QID(q)		((((u32)(q).path)&0x0000001F)>>0)
#define	SLOT(q)		(((((u32)(q).path)&0x07FFFFFE0)>>QSHIFT)-1)
#define	PID(q)		((q).vers)
#define	NOTEID(q)	((q).vers)

/* TODO kproc or mechanism to garbage collect these Forthproc */
typedef struct Forthproc Forthproc;
struct Forthproc
{
	Proc *p;
	Forthproc *prev, *next;
};

int nforthprocs = 0;
Forthproc *fhead, *ftail;
static	QLock	forthlock;

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
			DBG("Header 0x%zx: 0x%zx 0x%zx ", h, *(intptr*)h, dtop);
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
	DBG("loadforthdictionary fmem 0x%zx h 0x%zx dtop 0x%zx (intptr*)(fmem + DTOP) 0x%zx *(intptr*)(fmem + DTOP) 0x%zx\n",
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
	print("fentries[0].name %s\n", fentries[0].hdr.name);
	print("fentries[1].name %s nfentries %d\n", fentries[1].hdr.name, nelem(fentries));
	if(waserror())
		print("forthentry waserror(): %r\n");
	forthmain((u8*)fmem);
	free(fmem);
	pexit("exit", 0);
}

Forthproc *
newforthproc(void)
{
	Proc *p;
	Pgrp *pg;
	Fgrp *fg;
	Egrp *eg;
	Forthproc *f;
	void *forthmem;

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

	pg = up->env->pgrp;
	if(pg == nil)
		panic("newforthproc: nil process group\n");
	incref(pg);
	p->env->pgrp = pg;

	fg = up->env->fgrp;
	if(fg != nil)
		incref(fg);
	p->env->fgrp = fg;

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

	f = malloc(sizeof(Forthproc));
	if(f == nil)
		panic("newforthproc\n");
	forthmem = malloc(FORTHHEAPSIZE);
	if(forthmem == nil)
		panic("newforthproc forthmem == nil\n");

	/* store the start address at that address too - magic check */
	((intptr*)forthmem)[0] = (intptr)forthmem;	/* heap start */
	((intptr*)forthmem)[1] = (intptr)forthmem+FORTHHEAPSIZE-1; /* heap end */
	if(fhead == nil){
		fhead = ftail = f;
	}else{
		ftail->next = f;
		f->prev = ftail;
		ftail = f;
	}
	f->p = p;
	nforthprocs++;

/*	p->kpfun = func;
	p->kparg = arg;
	kprocchild(p, linkproc);*/
/* this does all of the above 3 lines */
	kprocchild(p, forthentry, forthmem);

	strcpy(p->text, "forth");

	memset(p->time, 0, sizeof(p->time));
	p->time[TReal] = MACHP(0)->ticks;
/*	cycles(&p->kentry);
	p->pcycles = -p->kentry;*/

	qunlock(&p->debug);
	p->psstate = nil;

	ready(p);
	return f;
}

/*
 * mostly the same as procgen() of devproc.c
 *	and drawgen() of devdraw.c
 * TODO get the permissions from Proc.procmode
 */
static int
forthgen(Chan *c, char *name, Dirtab *, int, int s, Dir *dp)
{
	Qid q;
	Forthproc *f;
	char *ename;
	u32 pid, path;
	s32 slot, i, t;
	Proc *p;

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
	DBG("forthgen s == DEVDOTDOT c->path %s name %s s %d mode 0x%ux c->qid.path 0x%zux "
		"slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n",
		chanpath(c), name, s, c->mode, c->qid.path, SLOT(c->qid),
		QID(c->qid), c->qid.vers, c->qid.type, c->qid.type);
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
	DBG("forthgen Qtopdir c->path %s name %s s %d mode 0x%ux c->qid.path 0x%zux "
		"slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n",
		chanpath(c), name, s, c->mode, c->qid.path, SLOT(c->qid),
		QID(c->qid), c->qid.vers, c->qid.type, c->qid.type);
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
	DBG("forthgen Qforthdir c->path %s name %s s %d mode 0x%ux c->qid.path 0x%zux "
		"slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n",
		chanpath(c), name, s, c->mode, c->qid.path, SLOT(c->qid),
		QID(c->qid), c->qid.vers, c->qid.type, c->qid.type);
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
		}else{
			s = s-1;
			if(s >= nforthprocs)
				return -1;
			i = 0;
			for(f = fhead; f != nil && i < s; f=f->next, i++)
				;
			if(f == nil || f->p == nil || f->p->pid == 0)
				return -1;
			pid = f->p->pid;
			if(pid==0)
				return -1;
			slot = procindex(pid);
			if(slot < 0)
				return -1;
		}
		DBG("forthgen Qforthdir slot %d\n", slot);
		/*
		 * String comparison is done in devwalk so name must match its formatted pid
		*/
		p = proctab(slot);
		snprint(up->genbuf, sizeof(up->genbuf), "%ud", pid);
		if(name != nil && strcmp(name, up->genbuf) != 0)
			return -1;
		mkqid(&q, ((slot+1)<<QSHIFT)|Qfprocdir, pid, QTDIR);
		devdir(c, q, up->genbuf, 0, p->env->user, 0555, dp);
	DBG("forthgen pid dir c->path %s name %s s %d mode 0x%ux c->qid.path 0x%zux "
		"slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n",
		chanpath(c), name, s, c->mode, c->qid.path, SLOT(c->qid),
		QID(c->qid), c->qid.vers, c->qid.type, c->qid.type);
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

static Walkqid*
forthwalk(Chan *c, Chan *nc, char **name, s32 nname)
{
 Walkqid* wq;
	DBG("forthwalk c->path %s c->mode 0x%ux nc->path %s name[0] %s nname %d\n",
		chanpath(c), c->mode, chanpath(nc), name[0], nname);
	wq = devwalk(c, nc, name, nname, nil, 0, forthgen);
	DBG("forthwalk after c->path %s c->mode 0x%ux nc->path %s name[0] %s nname %d\n",
		chanpath(c), c->mode, chanpath(nc), name[0], nname);
	return wq;
}

static int
forthstat(Chan *c, uchar *db, s32 n)
{
	int i;
	DBG("forthstat c->path %s\n", chanpath(c));
	i= devstat(c, db, n, nil, 0, forthgen);
	DBG("forthstat after c->path %s c->mode 0x%ux\n", chanpath(c), c->mode);
	return n;
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
	u32 pid;
	s32 slot;
	int omode;
	Forthproc *f;

	if(c->qid.type & QTDIR){
	DBG("forthopen c->qid.type & QTDIR c->path %s mode 0x%ux omode0 0x%ux c->qid.path 0x%zux "
		"slot %d qid %d c->qid.vers %d c->qid.type %d 0x%ux\n",
		chanpath(c), c->mode, omode0, c->qid.path, SLOT(c->qid),
		QID(c->qid), c->qid.vers, c->qid.type, c->qid.type);
		tc = devopen(c, omode0, nil, 0, forthgen);
	DBG("forthopen tc->qid.type & QTDIR tc->path %s mode 0x%ux omode0 0x%ux tc->qid.path 0x%zux "
		"slot %d qid %d tc->qid.vers %d tc->qid.type %d 0x%ux\n",
		chanpath(c), tc->mode, omode0, tc->qid.path, SLOT(tc->qid),
		QID(tc->qid), tc->qid.vers, tc->qid.type, tc->qid.type);
		return tc;
	}
		
	flock();
	if(waserror()){
		funlock();
		nexterror();
	}
	if(QID(c->qid) == Qnew){
		/* TODO set path */
print("forthopen called by pid %d text %s\n", up->pid, up->text);
		f = newforthproc();
		if(f == nil)
			error(Enodev);
		slot = procindex(f->p->pid);
		if(slot < 0)
			panic("forthopen");
		mkqid(&c->qid, Qctl|(slot+1)<<QSHIFT, f->p->pid, QTFILE);
		DBG("forthopen: new proc pid %d\n", f->p->pid);
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
	if(p->pid != pid)
		error(Eprocdied);

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
		print("forthopen %#ux\n", QID(c->qid));
		error(Egreg);
	}
	nonone(p);

	/* Affix pid to qid */
	if(pid == 0)
		error(Eprocdied);
	c->qid.vers = pid;

	tc = devopen(c, omode, 0, 0, forthgen);
	if(waserror()){
		cclose(tc);
		nexterror();
	}
	poperror();

	qunlock(&p->debug);
	poperror(); /* eqlock */
	DBG("forthopen returning tc->path %s omode0 0x%ux tc->qid.vers %d up->pid %d\n", chanpath(tc), omode, tc->qid.vers, up->pid);
	return tc;
}

static void
forthclose(Chan *c)
{
	DBG("forthclose c->path %s up->pid %d\n", chanpath(c), up->pid);
	/* TODO close the Chan*? */
	return;
}

s32
forthread(Chan *c, void *a, s32 n, s64 off)
{
	Proc *p;
	Forthproc *f;
	char *buf;
	s32 rv = 0;
	
	DBG("forthread c->path %s up->pid %d\n", chanpath(c), up->pid);
	if(c->qid.type & QTDIR)
		return devdirread(c, a, n, nil, 0, forthgen);

	f = c->aux;
	p = proctab(SLOT(c->qid));
	if(p->pid != PID(c->qid))
		error(Eprocdied);

	eqlock(&p->debug);
	if(waserror()){
		qunlock(&p->debug);
		nexterror();
	}
	switch(QID(c->qid)){
	case Qctl:
		buf = smalloc(16);
		snprint(buf, 16, "%d", p->pid);
		rv = readstr(off, a, n, buf);
		free(buf);
		break;
	case Qvars: /* TODO */
		error(Ebadarg);
	default:
		print("unknown qid in forthread\n");
		error(Egreg);
	}

	qunlock(&p->debug);
	poperror();
	DBG("forthread returning n %d bytes\n", n);
	return rv;
}

static s32
forthwrite(Chan *c, void *a, s32 n, s64)
{
	Proc *p;
	Forthproc *f;

	DBG("forthwrite c->path %s\n", chanpath(c));
	if(c->qid.type & QTDIR)
		return devdirread(c, a, n, nil, 0, forthgen);

	f = c->aux;
	p = proctab(SLOT(c->qid));
	if(p->pid != PID(c->qid))
		error(Eprocdied);

	eqlock(&p->debug);
	if(waserror()){
		qunlock(&p->debug);
		nexterror();
	}
	switch(QID(c->qid)){
	case Qctl:
		print("forthwrite: writing to Qctl, ignored\n");
		break;
	case Qvars: /* TODO */
		error(Ebadarg);
	default:
		print("unknown qid in forthwriten");
		error(Egreg);
	}

	qunlock(&p->debug);
	poperror();
	DBG("forthwrite returning n %d bytes\n", n);
	return n;
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
