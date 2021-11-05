#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"
#include	<interp.h>

/* Ref	pidalloc; */
int	schedgain = 30;	/* units in seconds */
int	nrdy;

ulong	delayedscheds;	/* statistics */
ulong	skipscheds;
ulong	preempts;
s32	prevpid;

/* bitmap of priorities of procs ready to run. When any process is
 * queued, the bit corresponding to that priority gets set.
 * when there are no more processes to run at a priority, then the
 * corresponding bit gets cleared.
 */
static u32	occupied;

static struct Procalloc
{
	Lock;
	Proc*	arena;
	Proc*	free;
} procalloc;

/* multiple run queues by priority, different from Brian's book
 * Per Brian's book, it is the struct Procs == struct Schedq.
 * Now, inferno maintains multiple Schedq based on priority.
 */
static Schedq	runq[Nrq];
int	nrdy;

char *statename[] =
{			/* BUG: generate automatically */
	"Dead",
	"Moribund",
	"Ready",
	"Scheding",
	"Running",
	"Queueing",
	"QueueingR",
	"QueueingW",
	"Wakeme",
	"Broken",
	"Stopped",
	"Rendez",
	"Waitrelease",
};

static void pidinit(void);
static void pidfree(Proc*);

/*
 * The kernel scheduler state is in m->sched. It is set to the address
 * of schedinit().
 * When sched() is switching processes, it transfers control to the kernel
 * scheduler by using the m->sched label. The kernel scheduler then updates
 * the running process's state and picks the next process to run.
 * By using m->sched, we are creating a loop from sched() to schedinit()
 * after every process switch.
 *
 * inferno does not change the process priorities. So, ignoring updatecpu().
 * process priorities are set with setpri()
 */
/*
 * Always splhi()'ed.
 */
void
schedinit(void)		/* never returns */
{
	setlabel(&m->sched);
	if(up != nil) {
/*
		if((e = up->edf) && (e->flags & Admitted))
			edfrecord(up);
*/
		m->proc = nil;
		switch(up->state) {
		case Running:
			/*
			 * process state from Runnning -> Ready
			 * gets put to the back of the run queue
			 */
			ready(up);
			break;
		case Moribund:
			up->state = Dead;
/*
			edfstop(up);
			if(up->edf){
				free(up->edf);
				up->edf = nil;
			}
*/
			lock(&procalloc);
			up->mach = nil;
			up->qnext = procalloc.free;
			procalloc.free = up;
			/* proc is free now, make sure unlock() wont touch it */
			up = procalloc.Lock.p = nil;
			unlock(&procalloc);

			sched();
		}
		coherence();
		/* flag to indicate that the process has saved itself
		 * for the next run
		 */
		up->mach = nil;
		up = nil;
	}
	sched();
}

static void
procswitch(void)
{
	uvlong t;

	/* statistics */
	m->cs++;

	cycles(&t);
	up->pcycles += t;

	procsave(up);

	if(!setlabel(&up->sched))
		gotolabel(&m->sched);

	/* process wakes up here next time */
	procrestore(up);

	cycles(&t);
	up->pcycles -= t;
}

/*
 *  If changing this routine, look also at sleep().  It
 *  contains a copy of the guts of sched().
 */
void
sched(void)
{
	Proc *p;

	if(m->ilockdepth != 0)
		panic("cpu%d: ilockdepth %d, last lock %#p at %#p, sched called from %#p",
			m->machno,
			m->ilockdepth,
			up != nil ? up->lastilock: nil,
			(up != nil && up->lastilock != nil) ? up->lastilock->pc: 0,
			getcallerpc(&p+2));
	if(up != nil) {
		/*
		 * Delay the sched until the process gives up the locks
		 * it is holding.  This avoids dumb lock loops.
		 * Don't delay if the process is Moribund.
		 * It called sched to die.
		 * But do sched eventually.  This avoids a missing unlock
		 * from hanging the entire kernel. 
		 * But don't reschedule procs holding palloc or procalloc.
		 * Those are far too important to be holding while asleep.
		 *
		 * This test is not exact.  There can still be a few instructions
		 * in the middle of taslock when a process holds a lock
		 * but Lock.p has not yet been initialized.
		 */
		if(up->nlocks)
		if(up->state != Moribund)
		if(up->delaysched < 20
/*		|| palloc.Lock.p == up
		|| fscache.Lock.p == up
*/
		|| procalloc.Lock.p == up){
			up->delaysched++;
 			delayedscheds++;
			return;
		}
		up->delaysched = 0;
		splhi();
		procswitch();
		spllo();
		return;
	}
	/* if up == nil, it is the scheduler process after the
	 * previous process state has been saved and also the
	 * first time entering schedinit()
	 */
	p = runproc();
	up = p;
	up->state = Running;
	up->mach = MACHP(m->machno);
	m->proc = up;
	gotolabel(&up->sched);
}

/*
 * ready(p) is simpler as we do not change process priorities
 * puts the current process at the end of the run queue
 * p->state = Running -> Ready
 */
void
ready(Proc *p)
{
	int s;
	Schedq *rq;

	if(p->state == Ready){
		print("double ready %s %ud pc %p\n", p->text, p->pid, getcallerpc(&p));
		return;
	}

	s = splhi();
/*
	if(edfready(p)){
		splx(s);
		return;
	}
*/

	/* 9front does this. Not sure what it does yet
	if(up != p && (p->wired == nil || p->wired == MACHP(m->machno)))
		m->readied = p;	*//* group scheduling */

	/* add to the end of the run queue */
	rq = &runq[p->priority];
	lock(runq);
	p->rnext = 0;
	if(rq->tail)
		rq->tail->rnext = p;
	else
		rq->head = p;
	rq->tail = p;
	rq->n++;
	nrdy++;
	occupied |= 1<<p->priority;
	p->state = Ready;
	unlock(runq);
	splx(s);
}

int
anyready(void)
{
	/* same priority only */
	return occupied & (1<<up->priority);
}

/*
 * the higher the priority, the lower the number
 * unlike 9front
 */
int
anyhigher(void)
{
	return occupied & ((1<<up->priority)-1);
}

/*
 *  here at the end of non-clock interrupts to see if we should preempt the
 *  current process.  Returns 1 if preempted, 0 otherwise.
 *  similar to 9front's preempted()
 */
int
preemption(int tick)
{
	if(up != nil && up->state == Running &&
		up->preempted == 0 &&
		active.exiting == 0 &&
		(anyhigher() || tick && anyready())){
		up->preempted = 1;
		sched();
		splhi();
		up->preempted = 0;
		return 1;
	}
	return 0;
}

Proc*
runproc(void)
{
	Schedq *rq, *erq;
	Proc *p, *tp, *last;
	u64 start, now;
	int i;
/*	void (*pt)(Proc*, int, vlong); */

	start = perfticks();
	preempts++;

	erq = runq + Nrq - 1;
loop:
	/*
	 *  find a process that last ran on this processor (affinity),
	 *  or one that can be moved to this processor.
	 */
	spllo();
	for(i = 0;; i++){
		/*
		 * find the highest priority target process that this
		 * processor can run given affinity constraints.
		 * when i == 0, thats where we pick the associated procs
		 * after this, we take anyone even from other cores
		 */
		for(rq = runq; rq <= erq; rq++){
			for(tp = rq->head; tp != nil; tp = tp->rnext){
				if(tp->mp == nil || tp->mp == MACHP(m->machno)
				|| (tp->wired == nil && i > 0))
					goto found;
			}
		}

		/* waste time or halt the CPU */
		idlehands();

		/* remember how much time we're here */
		now = perfticks();
		m->perf.inidle += now-start;
		start = now;
	}

found:
/*	print("runproc\n");
	procdump();
*/
	splhi();
	/*
	 * try to remove the process from a scheduling queue
	 * similar to 9front's dequeueproc()
	 */
	if(!canlock(runq))
		goto loop;

	/*
	 *  the queue may have changed before we locked runq,
	 *  refind the target process.
	 */
	last = nil;
	for(p = rq->head; p != nil; p = p->rnext){
		if(p == tp)
			break;
		last = p;
	}

	/*
	 *  p->mach==0 only when process state is saved
	 */
	if(p == nil || p->mach != nil){
		unlock(runq);
		goto loop;
	}
	/* if p is the last in the run queue
	 * update run queue tail to point to the last */
	if(p->rnext == nil)
		rq->tail = last;
	/* remove p from the linked list */
	if(last != nil)
		last->rnext = p->rnext;
	else
		rq->head = p->rnext;
	/* no other procs in the run queue */
	if(rq->head == nil){
		rq->tail = nil;
		occupied &= ~(1<<p->priority);
	}
	rq->n--;
	nrdy--;
	if(p->dbgstop){
		p->state = Stopped;
		unlock(runq);
		goto loop;
	}
	if(p->state != Ready)
		print("runproc %s %ud %s\n", p->text, p->pid, statename[p->state]);
	unlock(runq);

	p->state = Scheding;
	p->mp = MACHP(m->machno);

/*	if(edflock(p)){
		edfrun(p, rq == &runq[PriEdf]);	*//* start deadline timer and do admin *//*
		edfunlock();
	}
	pt = proctrace;
	if(pt != nil)
		pt(p, SRun, 0);
*/
/* for debugging */
/*	if(p->pid != prevpid){
		prevpid = p->pid;
		if(p->type == Interp && p->iprog != nil){
			print(" %d:%s,%d %s ",
				p->pid, p->text, ((Prog*)p->iprog)->pid, ((Prog*)p->iprog)->R.M->m->path);
		}else
			print(" %d:%s", p->pid, p->text);
	}else
		print(".");
*/
	return p;
}

/*
 * not using memset 0 on the Proc structure
 * to avoid leaking KSTACK
 */
Proc*
newproc(void)
{
	Proc *p;

	lock(&procalloc);
	p = procalloc.free;
	if(p == nil || (p->kstack == nil && (p->kstack = malloc(KSTACK)) == nil)){
		unlock(&procalloc);
		return nil;
	}
	procalloc.free = p->qnext;
	p->qnext = nil;
	unlock(&procalloc);

	p->psstate = "New";
	p->fpstate = FPinit;
	p->procctl = 0;
	p->dbgreg = nil;
	p->nerrlab = 0;
	p->type = Unknown;
	p->state = Scheding;
	p->priority = PriNormal;
	p->mach = 0;
	p->qnext = 0;
	p->kp = 0;
	p->killed = 0; /* TODO replace these 2 with notepending */
	p->swipend = 0;
	p->nlocks = 0;
	p->delaysched = 0;
	memset(&p->defenv, 0, sizeof(p->defenv));
	p->env = &p->defenv;
	kstrdup(&p->env->user, "*nouser");
	p->env->errstr = p->env->errbuf0;
	p->env->syserrstr = p->env->errbuf1;

	/* sched params */
	p->mp = 0;
	p->wired = 0;
	p->edf = nil;
	p->noteid = 0;
	p->trace = 0;

	/* replaced with pidalloc() in kproc */
/*	p->pid = incref(&pidalloc);
	if(p->pid == 0)
		panic("pidalloc"); */
	if(p->kstack == 0)
		p->kstack = smalloc(KSTACK);
	addprog(p);

	return p;
}

/*
 * wire this proc to a machine
 */
void
procwired(Proc *p, int bm)
{
	Proc *pp;
	int i;
	char nwired[MAXMACH];
	Mach *wm;

	if(bm < 0){
		/* pick a machine to wire to */
		memset(nwired, 0, sizeof(nwired));
		p->wired = nil;
		for(i=0; i<conf.nproc; i++){
			pp = proctab(i);
			wm = pp->wired;
			if(wm != nil && pp->pid)
				nwired[wm->machno]++;
		}
		bm = 0;
		for(i=0; i<conf.nmach; i++)
			if(nwired[i] < nwired[bm])
				bm = i;
	} else {
		/* use the virtual machine requested */
		bm = bm % conf.nmach;
	}

	p->wired = MACHP(bm);
	p->mp = p->wired;
}

int
setpri(int priority)
{
	int p;

	/* called by up so not on run queue */
	p = up->priority;
	up->priority = priority;
	if(up->state == Running && anyhigher())
		sched();
	return p;
}

void
procinit(void)
{
	Proc *p;
	int i;

	print("procinit conf.nproc %d\n", conf.nproc);
	p = xalloc(conf.nproc*sizeof(Proc));
	if(p == nil){
		xsummary();
		panic("cannot allocate %ud procs (%udMB)",
			conf.nproc, conf.nproc*sizeof(Proc)/(1024*1024));
	}
	procalloc.arena = p;
	procalloc.free = p;

	p = procalloc.free;
	for(i=0; i<conf.nproc-1; i++,p++)
		p->qnext = p+1;
	p->qnext = 0;

	pidinit();
	/* debugkey('p', "processes", procdump, 0); */
}

/*
 *  sleep if a condition is not true.  Another process will
 *  awaken us after it sets the condition.  When we awaken
 *  the condition may no longer be true.
 *
 *  we lock both the process and the rendezvous to keep r->p
 *  and p->r synchronized.
 */
void
sleep(Rendez *r, int (*f)(void*), void *arg)
{
	int s;
/*	void (*pt)(Proc*, int, vlong);*/

	if(up == nil)
		panic("sleep() not in process (%zux)", getcallerpc(&r));
	/*
	 * spl is to allow lock to be called
	 * at interrupt time. lock is mutual exclusion
	 */
	s = splhi();

	if(up->nlocks)
		print("process %d name %s sleeps with %d locks held,"
				" last lock %#p locked at pc %#p, sleep called from %#p\n",
			up->pid, up->text, up->nlocks,
			up->lastlock, up->lastlock->pc, getcallerpc(&r));

	lock(r);
	lock(&up->rlock);
	if(r->p != nil){
		print("double sleep called from %#p, %ud %ud\n", getcallerpc(&r), r->p->pid, up->pid);
		dumpstack();
		panic("sleep");
	}

	/*
	 *  Wakeup only knows there may be something to do by testing
	 *  r->p in order to get something to lock on.
	 *  Flush that information out to memory in case the sleep is
	 *  committed.
	 */
	r->p = up;

	if(up->notepending || f(arg)){
		/*
		 *  if condition happened or a note is pending
		 *  never mind
		 */
		r->p = nil;
		unlock(&up->rlock);
		unlock(r);
	}else{
		/*
		 * now we are committed to
		 * change state and call scheduler
		 */
/*		pt = proctrace;
		if(pt != nil)
			pt(up, SSleep, 0); */
		up->state = Wakeme;
		up->r = r;	/* for swiproc */
		unlock(&up->rlock);
		unlock(r);
		procswitch();
	}

	if(up->notepending) {
		up->notepending = 0;
		splx(s);
		interrupted();
	}
	splx(s);
}

void
interrupted(void)
{
	if(up->procctl == Proc_exitme && up->env->closingfgrp != nil)
		forceclosefgrp();
	error(Eintr);
}

static int
tfn(void *arg)
{
	return up->trend == nil || up->tfn(arg);
}

void
twakeup(Ureg*, Timer *t)
{
	Proc *p;
	Rendez *trend;

	p = t->ta;
	trend = p->trend;
	if(trend != nil){
		p->trend = nil;
		wakeup(trend);
	}
}

void
tsleep(Rendez *r, int (*fn)(void*), void *arg, s32 ms)
{
	if(up->tt != nil){
		print("%s %ud: tsleep timer active: mode %d, tf %#p, pc %#p\n",
			up->text, up->pid, up->tmode, up->tf, getcallerpc(&r));
		timerdel(up);
	}
	up->tns = MS2NS(ms);
	up->tf = twakeup;
	up->tmode = Trelative;
	up->ta = up;
	up->trend = r;
	up->tfn = fn;
	timeradd(up);

	if(waserror()){
		up->trend = nil;
		timerdel(up);
		nexterror();
	}
	sleep(r, tfn, arg);
	up->trend = nil;
	timerdel(up);
	poperror();
}

/*
 *  Expects that only one process can call wakeup for any given Rendez.
 *  We hold both locks to ensure that r->p and p->r remain consistent.
 *  Richard Miller has a better solution that doesn't require both to
 *  be held simultaneously, but I'm a paranoid - presotto.
 */
Proc*
wakeup(Rendez *r)
{
	Proc *p;
	int s;

	s = splhi();

	lock(r);
	p = r->p;

	if(p != nil){
		lock(&p->rlock);
		if(p->state != Wakeme || p->r != r){
			iprint("%p %p %d\n", p->r, r, p->state);
			panic("wakeup: state");
		}
		r->p = nil;
		p->r = nil;
		ready(p);
		unlock(&p->rlock);
	}
	unlock(r);

	splx(s);

	return p;
}

/*
 *  if waking a sleeping process, this routine must hold both
 *  p->rlock and r->lock.  However, it can't know them in
 *  the same order as wakeup causing a possible lock ordering
 *  deadlock.  We break the deadlock by giving up the p->rlock
 *  lock if we can't get the r->lock and retrying.
 */
int
postnote(Proc *p, int dolock, char *n, int flag)
{
	int s, ret;
	QLock *q;

	if(p == nil)
		return 0;

	if(dolock)
		qlock(&p->debug);

	if(p->pid == 0){
		if(dolock)
			qunlock(&p->debug);
		return 0;
	}

	if(n != nil && flag != NUser && (p->notify == nil || p->notified))
		p->nnote = 0;

	ret = 0;
	if(p->nnote < NNOTE && n != nil) {
		kstrcpy(p->note[p->nnote].msg, n, ERRMAX);
		p->note[p->nnote++].flag = flag;
		ret = 1;
	}
	p->notepending = 1;
	if(dolock)
		qunlock(&p->debug);

	/* this loop is to avoid lock ordering problems. */
	for(;;){
		Rendez *r;

		s = splhi();
		lock(&p->rlock);
		r = p->r;

		/* waiting for a wakeup? */
		if(r == nil)
			break;	/* no */

		/* try for the second lock */
		if(canlock(r)){
			if(p->state != Wakeme || r->p != p)
				panic("postnote: state %d %d %d", r->p != p, p->r != r, p->state);
			p->r = nil;
			r->p = nil;
			ready(p);
			unlock(r);
			break;
		}

		/* give other process time to get out of critical section and try again */
		unlock(&p->rlock);
		splx(s);
		sched();
	}
	unlock(&p->rlock);
	splx(s);

	switch(p->state){
	case Queueing:
		/* Try and pull out of a eqlock */
		if((q = p->eql) != nil){
			lock(&q->use);
			if(p->state == Queueing && p->eql == q){
				Proc *d, *l;

				for(l = nil, d = q->head; d != nil; l = d, d = d->qnext){
					if(d == p){
						if(l != nil)
							l->qnext = p->qnext;
						else
							q->head = p->qnext;
						if(p->qnext == nil)
							q->tail = l;
						p->qnext = nil;
						p->eql = nil;	/* not taken */
						ready(p);
						break;
					}
				}
			}
			unlock(&q->use);
		}
		break;
	case Rendezvous:
		/* Try and pull out of a rendezvous */
		lock(p->env->rgrp);
		if(p->state == Rendezvous) {
			Proc *d, **l;

			l = &REND(p->env->rgrp, p->rendtag);
			for(d = *l; d != nil; d = d->rendhash) {
				if(d == p) {
					*l = p->rendhash;
					p->rendval = ~0;
					ready(p);
					break;
				}
				l = &d->rendhash;
			}
		}
		unlock(p->env->rgrp);
		break;
	}
	return ret;
}

/*
 * 9front maintains broken processes. Not bothering with them
 * as there should not be any broken proc's in inferno
 */

void
notkilled(void)
{
	lock(&up->rlock);
	up->killed = 0;
	unlock(&up->rlock);
}

void
pexit(char*, int)
{
	Osenv *o;

	up->alarm = 0;

	o = up->env;
	if(o != nil){
		closefgrp(o->fgrp);
		closepgrp(o->pgrp);
		closeegrp(o->egrp);
		closesigs(o->sigs);
	}

/*
	edfstop(up);
*/
	qlock(&up->debug);
	pidfree(up);
	qunlock(&up->debug);
	up->state = Moribund;
	sched();
	panic("pexit");
}

/* 9front uses a macro for this. why? */
Proc*
proctab(int i)
{
	return &procalloc.arena[i];
}

void
dumpaproc(Proc *p)
{
	char *s;
	char tmp[14];

	s = p->psstate;
	if(s == nil)
		s = "kproc";
	if(p->state == Wakeme)
		snprint(tmp, sizeof(tmp), " /%.8lux", p->r);
	else
		*tmp = '\0';
	print("%p:%3ud:%14s pc %.8zux %s/%s qpc %.8zux priority %d%s\n",
		p, p->pid, p->text, p->pc, s, statename[p->state], p->qpc,
		p->priority, tmp);
}

void
procdump(void)
{
	int i;
	Proc *p;

	for(i=0; i<conf.nproc; i++) {
		p = &procalloc.arena[i];
		if(p->state == Dead)
			continue;

		dumpaproc(p);
	}
}

void
kproc(char *name, void (*func)(void *), void *arg, int flags)
{
	Proc *p;
	Pgrp *pg;
	Fgrp *fg;
	Egrp *eg;

	while((p = newproc()) == nil){
/* TODO		freebroken(); */
		resrcwait("no procs for kproc");
	}

	qlock(&p->debug);
	p->psstate = 0;
	p->kp = 1;

	p->fpsave = up->fpsave;
/*	p->scallnr = up->scallnr; */
	p->nerrlab = 0;

	kstrdup(&p->env->user, up->env->user);
	if(flags & KPDUPPG) {
		pg = up->env->pgrp;
		incref(pg);
		p->env->pgrp = pg;
	}
	if(flags & KPDUPFDG) {
		fg = up->env->fgrp;
		incref(fg);
		p->env->fgrp = fg;
	}
	if(flags & KPDUPENVG) {
		eg = up->env->egrp;
		if(eg != nil)
			incref(eg);
		p->env->egrp = eg;
	}

	p->nnote = 0;
	p->notify = nil;
	p->notified = 0;
	p->notepending = 0;

	p->procmode = 0640;
	p->privatemem = 1;
	p->noswap = 1;
	p->hang = 0;
	p->kp = 1;

/*	p->kpfun = func;
	p->kparg = arg;
	kprocchild(p, linkproc);*/
/* this does all of the above 3 lines */
	kprocchild(p, func, arg);

	strcpy(p->text, name);

/*	if(kpgrp == nil)
		kpgrp = newpgrp();
	p->pgrp = kpgrp;
	incref(kpgrp);*/

	memset(p->time, 0, sizeof(p->time));
	p->time[TReal] = MACHP(0)->ticks;
/*	cycles(&p->kentry);
	p->pcycles = -p->kentry;*/

	pidalloc(p);

	qunlock(&p->debug);

/*	procpriority(p, PriKproc, 0);*/

	p->psstate = nil;
	ready(p);
}

void
errorf(char *fmt, ...)
{
	va_list arg;
	char buf[PRINTSIZE];

	va_start(arg, fmt);
	vseprint(buf, buf+sizeof(buf), fmt, arg);
	va_end(arg);
	error(buf);
}

void
error(char *err)
{
	if(up == nil)
		panic("error(%s) not in a process", err);
	spllo();
	if(up->nerrlab > NERR)
		panic("error stack too deep");
	if(err != up->env->errstr)
		kstrcpy(up->env->errstr, err, ERRMAX);
	setlabel(&up->errlab[NERR-1]);
	nexterror();
}

#include "errstr.h"

/* Set kernel error string */
void
kerrstr(char *err, uint size)
{

	char tmp[ERRMAX];

	kstrcpy(tmp, up->env->errstr, sizeof(tmp));
	kstrcpy(up->env->errstr, err, ERRMAX);
	kstrcpy(err, tmp, size);
}

/* Get kernel error string */
void
kgerrstr(char *err, uint size)
{
	char tmp[ERRMAX];

	kstrcpy(tmp, up->env->errstr, sizeof(tmp));
	kstrcpy(up->env->errstr, err, ERRMAX);
	kstrcpy(err, tmp, size);
}

/* Set kernel error string, using formatted print */
void
kwerrstr(char *fmt, ...)
{
	va_list arg;
	char buf[ERRMAX];

	va_start(arg, fmt);
	vseprint(buf, buf+sizeof(buf), fmt, arg);
	va_end(arg);
	kstrcpy(up->env->errstr, buf, ERRMAX);
}

void
werrstr(char *fmt, ...)
{
	va_list arg;
	char buf[ERRMAX];

	va_start(arg, fmt);
	vseprint(buf, buf+sizeof(buf), fmt, arg);
	va_end(arg);
	kstrcpy(up->env->errstr, buf, ERRMAX);
}

void
nexterror(void)
{
	gotolabel(&up->errlab[--up->nerrlab]);
}

/* for dynamic modules - functions not macros */
	
void*
waserr(void)
{
	up->nerrlab++;
	return &up->errlab[up->nerrlab-1];
}

void
poperr(void)
{
	up->nerrlab--;
}

char*
enverror(void)
{
	return up->env->errstr;
}

void
exhausted(char *resource)
{
	char buf[64];

	snprint(buf, sizeof(buf), "no free %s", resource);
	iprint("%s\n", buf);
	error(buf);
}

/*
 *  change ownership to 'new' of all processes owned by 'old'.  Used when
 *  eve changes.
 */
void
renameuser(char *old, char *new)
{
	Proc *p, *ep;
	Osenv *o;

	ep = procalloc.arena+conf.nproc;
	for(p = procalloc.arena; p < ep; p++) {
		o = &p->defenv;
		if(o->user != nil && strcmp(o->user, old) == 0)
			kstrdup(&o->user, new);
	}
}

int
return0(void*)
{
	return 0;
}

void
setid(char *name, int owner)
{
	if(!owner || iseve())
		kstrdup(&up->env->user, name);
}

/* TODO no idea what this rptproc() does
 * something to do with repeat of tk actions
 */
void
rptwakeup(void *o, void *ar)
{
	Rept *r;

	r = ar;
	if(r == nil)
		return;
	lock(&r->l);
	r->o = o;
	unlock(&r->l);
	wakeup(&r->r);
}

static int
rptactive(void *a)
{
	Rept *r = a;
	int i;
	lock(&r->l);
	i = r->active(r->o);
	unlock(&r->l);
	return i;
}

static void
rproc(void *a)
{
	long now, then;
	ulong t;
	int i;
	void *o;
	Rept *r;

	r = a;
	t = r->t;

Wait:
	sleep(&r->r, rptactive, r);
	lock(&r->l);
	o = r->o;
	unlock(&r->l);
	then = TK2MS(MACHP(0)->ticks);
	for(;;){
		tsleep(&up->sleep, return0, nil, t);
		now = TK2MS(MACHP(0)->ticks);
		if(waserror())
			break;
		i = r->ck(o, now-then);
		poperror();
		if(i == -1)
			goto Wait;
		if(i == 0)
			continue;
		then = now;
		acquire();
		if(waserror()) {
			release();
			break;
		}
		r->f(o);
		poperror();
		release();
	}
	pexit("", 0);
}

void*
rptproc(char *s, int t, void *o, int (*active)(void*), int (*ck)(void*, int), void (*f)(void*))
{
	Rept *r;

	r = mallocz(sizeof(Rept), 1);
	if(r == nil)
		return nil;
	r->t = t;
	r->active = active;
	r->ck = ck;
	r->f = f;
	r->o = o;
	kproc(s, rproc, r, KPDUP);
	return r;
}

s32
getpid(void)
{
	return up->pid;
}

/*
 *  A Pid structure is a reference counted hashtable entry
 *  with "pid" being the key and "procindex" being the value.
 *  A entry is allocated atomically by changing the key from
 *  negative or zero to the positive process id number.
 *  Pid's outlive ther Proc's as long as other processes hold
 *  a reference to them such as noteid or parentpid.
 *  This prevents pid reuse when the pid generator wraps.
 */
typedef struct Pid Pid;
struct Pid
{
	Ref;
	long	pid;
	int	procindex;
};

enum {
	PIDMASK = 0x7FFFFFFF,
	PIDSHIFT = 4,	/* log2 bucket size of the hash table */
};

static Pid *pidhashtab;
static ulong pidhashmask;

static void
pidinit(void)
{
	/*
	 * allocate 3 times conf.nproc Pid structures for the hash table
	 * and round up to a power of two as each process can reference
	 * up to 3 unique Pid structures:
	 *	- pid
	 *	- noteid
	 *	- parentpid
	 */
	pidhashmask = 1<<PIDSHIFT;
	while(pidhashmask < conf.nproc*3)
		pidhashmask <<= 1;

	pidhashtab = xalloc(pidhashmask * sizeof(pidhashtab[0]));
	if(pidhashtab == nil){
		xsummary();
		panic("cannot allocate pid hashtable of size %lud", pidhashmask);
	}

	/* make it a mask */
	pidhashmask--;
}

static Pid*
pidlookup(long pid)
{
	Pid *i, *e;
	long o;

	i = &pidhashtab[(pid<<PIDSHIFT) & pidhashmask];
	for(e = &i[1<<PIDSHIFT]; i < e; i++){
		o = i->pid;
		if(o == pid)
			return i;
		if(o == 0)
			break;
	}
	return nil;
}

/*
 *  increment the reference count of a pid (pid>0)
 *  or allocate a new one (pid<=0)
 */
static Pid*
pidadd(long pid)
{
	Pid *i, *e;
	long o;

	if(pid > 0){
		i = pidlookup(pid);
		if(i != nil)
			incref(i);
		return i;
	}
Again:
	do {
		static Ref gen;
		pid = incref(&gen) & PIDMASK;
	} while(pid == 0 || pidlookup(pid) != nil);

	i = &pidhashtab[(pid<<PIDSHIFT) & pidhashmask];
	for(e = &i[1<<PIDSHIFT]; i < e; i++){
		while((o = i->pid) <= 0){
			if(cmpswap((s32*)&i->pid, o, pid)){
				incref(i);
				return i;
			}
		}
	}
	/* bucket full, try a different pid */
	goto Again;
}

/*
 *  decrement reference count of a pid and free it
 *  when no references are remaining
 */
static void
piddel(Pid *i)
{
	if(decref(i))
		return;
	i->pid = -1;	/* freed */
}

int
procindex(ulong pid)
{
	Pid *i;

	i = pidlookup(pid);
	if(i != nil){
		int x = i->procindex;
		if(proctab(x)->pid == pid)
			return x;
	}
	return -1;
}

ulong
setnoteid(Proc *p, ulong noteid)
{
	Pid *i, *o;

	/*
	 * avoid allocating a new pid when we are the only
	 * user of the noteid
	 */
	o = pidlookup(p->noteid);
	if(noteid == 0 && o->ref == 1)
		return o->pid;

	i = pidadd(noteid);
	if(i == nil)
		error(Ebadarg);
	piddel(o);
	return p->noteid = i->pid;
}

/*
static ulong
setparentpid(Proc *p, Proc *pp)
{
	Pid *i;

	i = pidadd(pp->pid);
	return p->parentpid = i->pid;
} */

/*
 *  allocate pid, noteid and parentpid to a process
 */
ulong
pidalloc(Proc *p)
{
	Pid *i;

	/* skip for the boot process */
/*	if(up != nil)
		setparentpid(p, up);*/
	i = pidadd(0);
	i->procindex = (int)(p - procalloc.arena);

	if(p->noteid == 0){
		incref(i);
		p->noteid = i->pid;
	} else
		pidadd(p->noteid);

	return p->pid = i->pid;
}

/*
 *  release pid, noteid and parentpid from a process
 */
static void
pidfree(Proc *p)
{
	Pid *i;

	i = pidlookup(p->pid);
	piddel(i);

	if(p->noteid != p->pid)
		i = pidlookup(p->noteid);
	piddel(i);

/*	if(p->parentpid != 0)
		piddel(pidlookup(p->parentpid));

	p->pid = p->noteid = p->parentpid = 0;
*/
	p->pid = p->noteid = 0;
}
