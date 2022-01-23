#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"
#include	"edf.h"
#include	<trace.h>
#include	"tos.h"
#include	<interp.h>
#include	"ureg.h"

static int debug = 0;

int	schedgain = 30;	/* units in seconds */
int	nrdy;

void updatecpu(Proc*);
int reprioritize(Proc*);

ulong	delayedscheds;	/* statistics */
ulong	skipscheds;
ulong	preempts;
ulong	pload;
s32	prevpid;

static struct Procalloc
{
	Lock;
	Proc*	arena;
	Proc*	free;
} procalloc;

enum
{
	Q=10,
	DQ=4,
	Scaling=2,
};

/* multiple run queues by priority, different from Brian's book
 * Per Brian's book, it is the struct Procs == struct Schedq.
 * Now, inferno maintains multiple Schedq based on priority.
 */
Schedq	runq[Nrq];
ulong	runvec;

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

static void rebalance(void);
static void pidinit(void);
static void pidfree(Proc*);

/*
 There is a loop created between schedinit() and a process' run path.
 In schedinit(), setlabel(&m->sched) sets a pc and stack pointer
	in the Mach for a process to return to.
 In procswitch()(called by sched(), the setlabel(&up->sched) stores the
	return pc and stack pointer of the run path in Proc and goes to the pc
	in m->sched to start the scheduler loop.
 In sched(), we use the pc and sp in Proc.sched to resume execution later on.
 Thus the stacks and execution paths are switched from the Mach (scheduler)
	to that of a specific process.

 The execution path from Mach.sched to Proc.sched is the kernel scheduler run path
 The execution path from Proc.sched to Mach.sched is the process run path

 first process on entering schedinit() sets up Mach.sched
 process run path calls sched(), which calls procswitch()
	stack and pc changed to the contents of Mach.sched() - scheduler run path
	schedinit() adds the current running process to the end of ready queue, sets up = nil
		and calls sched()
	sched() picks the next process to run (runproc()) and switches to
		that Proc's pc and sp.

	schedinit() calls sched() after setting up = nil and putting the running process in the ready queue

  The kernel scheduler state is in m->sched. It is set to the address
  of schedinit().
  When sched() is switching processes, it transfers control to the kernel
  scheduler by using the m->sched label. The kernel scheduler then updates
  the running process's state and picks the next process to run.
  By using m->sched, we are creating a loop from sched() to schedinit()
  after every process switch.
 */
/*
 * Always splhi()'ed.
 */
void
schedinit(void)		/* never returns */
{
	Edf *e;

	setlabel(&m->sched);
	if(up != nil) {
		if((e = up->edf) && (e->flags & Admitted))
			edfrecord(up);
		m->proc = nil;
		switch(up->state){
		default:
			updatecpu(up);
			break;
		case Running:
			/*
			 * process state from Runnning -> Ready
			 * gets put to the back of the run queue
			 */
			ready(up);
			break;
		case Moribund:
			up->state = Dead;
			edfstop(up);
			if(up->edf != nil){
				free(up->edf);
				up->edf = nil;
			}

			/* mmurelease(up); linear memory on 9front */

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

/*
int
kenter(Ureg *ureg)
{
	int user;

	user = userureg(ureg);
	if(user){
		up->dbgreg = ureg;
		cycles(&up->kentry);
	}
	return user;
}

void
kexit(Ureg*)
{
	uvlong t;
	Tos *tos;

	cycles(&t);

	\/* precise time accounting, kernel exit *\/
	tos = (Tos*)(USTKTOP-sizeof(Tos));
	tos->kcycles += t - up->kentry;
	tos->pcycles = t + up->pcycles;
	tos->pid = up->pid;
}
*/

static void
procswitch(void)
{
	uvlong t;

	/* statistics */
	m->cs++;

	cycles(&t);
	up->kentry -= t;
	up->pcycles += t;

	procsave(up);

	if(setlabel(&up->sched) == 0) /* always returns 0 */
		gotolabel(&m->sched);

	/* process wakes up here next time */
	procrestore(up);

	cycles(&t);
	up->kentry += t;
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
		/*|| palloc.Lock.p == up
		|| fscache.Lock.p == up */
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
	if(p->edf == nil){
		updatecpu(p);
		p->priority = reprioritize(p);
	}
	if(p != m->readied)
		m->schedticks = m->ticks + HZ/10;
	m->readied = nil;
	up = p;
	up->state = Running;
	up->mach = MACHP(m->machno);
	m->proc = up;
	gotolabel(&up->sched);
}

int
anyready(void)
{
	return runvec;
}

int
anyhigher(void)
{
	return runvec & ~((1<<(up->priority+1))-1);
}

/*
 *  here once per clock tick to see if we should resched
 */
void
hzsched(void)
{
	/* once a second, rebalance will reprioritize ready procs */
	if(m->machno == 0)
		rebalance();

	/* unless preempted, get to run for at least 100ms */
	if(anyhigher()
	|| (!up->fixedpri && (long)(m->ticks - m->schedticks) > 0 && anyready())){
		m->readied = nil;	/* avoid cooperative scheduling */
		up->delaysched++;
	}
}

/*
 *  here at the end of non-clock interrupts to see if we should preempt the
 *  current process.  Returns 1 if preempted, 0 otherwise.
 */
int
preempted(void)
{
	if(up != nil && up->state == Running)
	if(up->preempted == 0)
	if(anyhigher())
	if(!active.exiting){
		m->readied = nil;	/* avoid cooperative scheduling */
		up->preempted = 1;
		sched();
		splhi();
		up->preempted = 0;
		return 1;
	}
	return 0;
}

/*
 * Update the cpu time average for this particular process,
 * which is about to change from up -> not up or vice versa.
 * p->lastupdate is the last time an updatecpu happened.
 *
 * The cpu time average is a decaying average that lasts
 * about D clock ticks.  D is chosen to be approximately
 * the cpu time of a cpu-intensive "quick job".  A job has to run
 * for approximately D clock ticks before we home in on its 
 * actual cpu usage.  Thus if you manage to get in and get out
 * quickly, you won't be penalized during your burst.  Once you
 * start using your share of the cpu for more than about D
 * clock ticks though, your p->cpu hits 1000 (1.0) and you end up 
 * below all the other quick jobs.  Interactive tasks, because
 * they basically always use less than their fair share of cpu,
 * will be rewarded.
 *
 * If the process has not been running, then we want to
 * apply the filter
 *
 *	cpu = cpu * (D-1)/D
 *
 * n times, yielding 
 * 
 *	cpu = cpu * ((D-1)/D)^n
 *
 * but D is big enough that this is approximately 
 *
 * 	cpu = cpu * (D-n)/D
 *
 * so we use that instead.
 * 
 * If the process has been running, we apply the filter to
 * 1 - cpu, yielding a similar equation.  Note that cpu is 
 * stored in fixed point (* 1000).
 *
 * Updatecpu must be called before changing up, in order
 * to maintain accurate cpu usage statistics.  It can be called
 * at any time to bring the stats for a given proc up-to-date.
 */
void
updatecpu(Proc *p)
{
	ulong t, ocpu, n, D;

	if(p->edf != nil)
		return;

	t = MACHP(0)->ticks*Scaling + Scaling/2;
	n = t - p->lastupdate;
	if(n == 0)
		return;
	p->lastupdate = t;

	D = schedgain*HZ*Scaling;
	if(n > D)
		n = D;

	ocpu = p->cpu;
	if(p != up)
		p->cpu = (ocpu*(D-n))/D;
	else{
		t = 1000 - ocpu;
		t = (t*(D-n))/D;
		p->cpu = 1000 - t;
	}
//iprint("pid %lud %s for %lud cpu %lud -> %lud\n", p->pid,p==up?"active":"inactive",n, ocpu,p->cpu);
}

/*
 * On average, p has used p->cpu of a cpu recently.
 * Its fair share is conf.nmach/m->load of a cpu.  If it has been getting
 * too much, penalize it.  If it has been getting not enough, reward it.
 * I don't think you can get much more than your fair share that 
 * often, so most of the queues are for using less.  Having a priority
 * of 3 means you're just right.  Having a higher priority (up to p->basepri) 
 * means you're not using as much as you could.
 */
int
reprioritize(Proc *p)
{
	int fairshare, n, load, ratio;

	load = MACHP(0)->load;
	if(load == 0)
		return p->basepri;

	/*
	 * fairshare = 1.000 * conf.nmach * 1.000/load,
	 * except the decimal point is moved three places
	 * on both load and fairshare.
	 */
	fairshare = (conf.nmach*1000*1000)/load;
	n = p->cpu;
	if(n == 0)
		n = 1;
	ratio = (fairshare+n/2) / n;
	if(ratio > p->basepri)
		ratio = p->basepri;
	if(ratio < 0)
		panic("reprioritize");
//iprint("pid %lud cpu %lud load %d fair %d pri %d\n", p->pid, p->cpu, load, fairshare, ratio);
	return ratio;
}

/*
 * add a process to a scheduling queue
 */
void
queueproc(Schedq *rq, Proc *p)
{
	int pri;

	pri = rq - runq;
	lock(runq);
	p->priority = pri;
	p->rnext = nil;
	if(rq->tail != nil)
		rq->tail->rnext = p;
	else
		rq->head = p;
	rq->tail = p;
	rq->n++;
	nrdy++;
	runvec |= 1<<pri;
	unlock(runq);
}

/*
 *  try to remove a process from a scheduling queue (called splhi)
 */
Proc*
dequeueproc(Schedq *rq, Proc *tp)
{
	Proc *l, *p;

	if(!canlock(runq))
		return nil;

	/*
	 *  the queue may have changed before we locked runq,
	 *  refind the target process.
	 */
	l = nil;
	for(p = rq->head; p != nil; p = p->rnext){
		if(p == tp)
			break;
		l = p;
	}

	/*
	 *  p->mach==0 only when process state is saved
	 */
	if(p == nil || p->mach != nil){
		unlock(runq);
		return nil;
	}
	if(p->rnext == nil)
		rq->tail = l;
	if(l != nil)
		l->rnext = p->rnext;
	else
		rq->head = p->rnext;
	if(rq->head == nil)
		runvec &= ~(1<<(rq-runq));
	rq->n--;
	nrdy--;
	if(p->state != Ready)
		print("dequeueproc %s %ud %s\n", p->text, p->pid, statename[p->state]);

	unlock(runq);
	return p;
}

/*
 *  ready(p) picks a new priority for a process and sticks it in the
 *  runq for that priority.
 */
void
ready(Proc *p)
{
	int s, pri;
	Schedq *rq;
	void (*pt)(Proc*, int, vlong);

	if(p->state == Ready){
		print("double ready %s %ud pc %p\n", p->text, p->pid, getcallerpc(&p));
		return;
	}

	s = splhi();
	if(edfready(p)){
		splx(s);
		return;
	}

	if(up != p && (p->wired == nil || p->wired == MACHP(m->machno)))
		m->readied = p;	/* group scheduling */

	updatecpu(p);
	pri = reprioritize(p);
	p->priority = pri;
	rq = &runq[pri];
	p->state = Ready;
	queueproc(rq, p);
	pt = proctrace;
	if(pt != nil)
		pt(p, SReady, 0);
	splx(s);
}

/*
 *  yield the processor and drop our priority
 */
void
yield(void)
{
	if(anyready()){
		/* pretend we just used 1/2 tick */
		up->lastupdate -= Scaling/2;  
		sched();
	}
}

/*
 *  recalculate priorities once a second.  We need to do this
 *  since priorities will otherwise only be recalculated when
 *  the running process blocks.
 */
ulong balancetime;

static void
rebalance(void)
{
	int pri, npri, x;
	Schedq *rq;
	Proc *p;
	ulong t;

	t = m->ticks;
	if(t - balancetime < HZ)
		return;
	balancetime = t;

	for(pri=0, rq=runq; pri<Npriq; pri++, rq++){
another:
		p = rq->head;
		if(p == nil)
			continue;
		if(pri == p->basepri)
			continue;
		updatecpu(p);
		npri = reprioritize(p);
		if(npri != pri){
			x = splhi();
			p = dequeueproc(rq, p);
			if(p != nil)
				queueproc(&runq[npri], p);
			splx(x);
			goto another;
		}
	}
}

/*
 *  pick a process to run
 */
Proc*
runproc(void)
{
	Schedq *rq;
	Proc *p;
	ulong start, now;
	int i;
	void (*pt)(Proc*, int, vlong);

	start = perfticks();

	/* cooperative scheduling until the clock ticks */
	if((p = m->readied) != nil && p->mach == nil && p->state == Ready
	&& (p->wired == nil || p->wired == MACHP(m->machno))
	&& runq[Nrq-1].head == nil && runq[Nrq-2].head == nil){
		skipscheds++;
		rq = &runq[p->priority];
		goto found;
	}

	preempts++;

loop:
	/*
	 *  find a process that last ran on this processor (affinity),
	 *  or one that can be moved to this processor.
	 */
	spllo();
	for(i = 0;; i++){
		/*
		 *  find the highest priority target process that this
		 *  processor can run given affinity constraints.
		 *
		 */
		for(rq = &runq[Nrq-1]; rq >= runq; rq--){
			for(p = rq->head; p != nil; p = p->rnext){
				if(p->mp == nil || p->mp == MACHP(m->machno)
				|| (p->wired == nil && i > 0))
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
	splhi();
	p = dequeueproc(rq, p);
	if(p == nil)
		goto loop;

	p->state = Scheding;
	p->mp = MACHP(m->machno);

	if(edflock(p)){
		edfrun(p, rq == &runq[PriEdf]);	/* start deadline timer and do admin */
		edfunlock();
	}
	pt = proctrace;
	if(pt != nil)
		pt(p, SRun, 0);
	return p;
}

/*
 * not using memset 0 on the Proc structure
 * to avoid leaking KSTACK
TODO fpusetup() and procsetup() of 9front
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
	p->ureg = nil;
	p->dbgreg = nil;
	p->nerrlab = 0;
	p->type = Unknown;
	p->nlocks = 0;
	p->delaysched = 0;
	p->trace = 0;

	memset(&p->defenv, 0, sizeof(p->defenv));
	p->env = &p->defenv;
	kstrdup(&p->env->user, "*nouser");
	p->env->errstr = p->env->errbuf0;
	p->env->syserrstr = p->env->errbuf1;

	/*
	 * a user process. kproc() can change it as it needs.
	 */
	up->kp = 0;
	up->noswap = 0;
	up->privatemem = 0;
	/* sched params */
	p->mp = 0;
	p->wired = 0;
	procpriority(p, PriNormal, 0);
	p->cpu = 0;
	p->lastupdate = MACHP(0)->ticks*Scaling;
	p->edf = nil;

	pidalloc(p);
	if(p->pid == 0)
		panic("pidalloc");
	/* addprog(p); no more dis */

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

void
procpriority(Proc *p, int pri, int fixed)
{
	if(pri >= Npriq)
		pri = Npriq - 1;
	else if(pri < 0)
		pri = 0;
	p->basepri = pri;
	p->priority = pri;
	if(fixed){
		p->fixedpri = 1;
	} else {
		p->fixedpri = 0;
	}
}

/* called procinit0 on 9front */
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
	void (*pt)(Proc*, int, vlong);

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
		pt = proctrace;
		if(pt != nil)
			pt(up, SSleep, 0);
		up->state = Wakeme;
		up->r = r;	/* for swiproc */
		unlock(&up->rlock);
		unlock(r);
		procswitch();
	}

	if(up->notepending) {
		up->nnote = 0;
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

void
shownotes(Proc *p)
{
	int i;

	print("p 0x%p pid %d nnote %d notified %d lastnote flag %d msg %s\n",
		p, p->pid, p->nnote, p->notified, p->lastnote.flag, p->lastnote.msg);
	for(i = 0; i < p->nnote; i++){
		print("i %d msg %s flag %d\n", i, p->note[i].msg, p->note[i].flag);
	}
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
 * weird thing: keep at most NBROKEN around
 */
#define	NBROKEN 4
struct
{
	QLock;
	int	n;
	Proc	*p[NBROKEN];
}broken;

static void
addbroken(void)
{
	qlock(&broken);
	if(broken.n == NBROKEN) {
		ready(broken.p[0]);
		memmove(&broken.p[0], &broken.p[1], sizeof(Proc*)*(NBROKEN-1));
		--broken.n;
	}
	broken.p[broken.n++] = up;
	qunlock(&broken);

	edfstop(up);
	up->state = Broken;
	up->psstate = nil;
	sched();
}

void
unbreak(Proc *p)
{
	int b;

	qlock(&broken);
	for(b=0; b < broken.n; b++)
		if(broken.p[b] == p) {
			broken.n--;
			memmove(&broken.p[b], &broken.p[b+1],
					sizeof(Proc*)*(NBROKEN-(b+1)));
			ready(p);
			break;
		}
	qunlock(&broken);
}

int
freebroken(void)
{
	int i, n;

	qlock(&broken);
	n = broken.n;
	for(i=0; i<n; i++) {
		ready(broken.p[i]);
		broken.p[i] = nil;
	}
	broken.n = 0;
	qunlock(&broken);
	return n;
}


void
notkilled(void)
{
	lock(&up->rlock);
	up->killed = 0;
	unlock(&up->rlock);
}

void
pexit(char *exitstr, int freemem)
{
	Proc *p;
/*	Segment **s;*/
	ulong utime, stime;
	Waitq *wq;
	Fgrp *fgrp;
	Egrp *egrp;
	Rgrp *rgrp;
	Pgrp *pgrp;
	Chan *dot;
	void (*pt)(Proc*, int, vlong);

	up->fpstate &= ~FPillegal;
	up->alarm = 0;
	timerdel(up);
	pt = proctrace;
	if(pt != nil)
		pt(up, SDead, 0);

	/* nil out all the resources under lock (free later) */
	qlock(&up->debug);
	fgrp = up->env->fgrp;
	up->env->fgrp = nil;
	egrp = up->env->egrp;
	up->env->egrp = nil;
	rgrp = up->env->rgrp;
	up->env->rgrp = nil;
/*	dot = up->env->pgrp->dot;
	up->env->pgrp->dot = nil;*/
	pgrp = up->env->pgrp;
	up->env->pgrp = nil;
	qunlock(&up->debug);

	if(fgrp != nil)
		closefgrp(fgrp);
	if(egrp != nil)
		closeegrp(egrp);
	if(rgrp != nil)
		closergrp(rgrp);
/*	if(dot != nil)
		cclose(dot); closepgrp() takes care of this */
	if(pgrp != nil)
		closepgrp(pgrp);
	if(up->parentpid == 0){
		if(exitstr == nil)
			exitstr = "unknown";
		panic("boot process died: %s", exitstr);
	}

	p = up->parent;
	if(p != nil && p->pid == up->parentpid && p->state != Broken){
		wq = smalloc(sizeof(Waitq));
		wq->w.pid = up->pid;
		utime = up->time[TUser] + up->time[TCUser];
		stime = up->time[TSys] + up->time[TCSys];
		wq->w.time[TUser] = tk2ms(utime);
		wq->w.time[TSys] = tk2ms(stime);
		wq->w.time[TReal] = tk2ms(MACHP(0)->ticks - up->time[TReal]);
		if(exitstr != nil && exitstr[0])
			snprint(wq->w.msg, sizeof(wq->w.msg), "%s %ud: %s", up->text, up->pid, exitstr);
		else
			wq->w.msg[0] = '\0';

		lock(&p->exl);
		/*
		 * Check that parent is still alive.
		 */
		if(p->pid == up->parentpid && p->state != Broken) {
			p->nchild--;
			p->time[TCUser] += utime;
			p->time[TCSys] += stime;
			/*
			 * If there would be more than 128 wait records
			 * processes for my parent, then don't leave a wait
			 * record behind.  This helps prevent badly written
			 * daemon processes from accumulating lots of wait
			 * records.
		 	 */
			if(p->nwait < 128) {
				wq->next = p->waitq;
				p->waitq = wq;
				p->nwait++;
				wq = nil;
				wakeup(&p->waitr);
			}
		}
		unlock(&p->exl);
		if(wq != nil)
			free(wq);
	}

	if(!freemem)
		addbroken();

	qlock(&up->debug);

	lock(&up->exl);		/* Prevent my children from leaving waits */
	pidfree(up);
	up->parent = nil;
	up->nchild = up->nwait = 0;
	wakeup(&up->waitr);
	unlock(&up->exl);

	while((wq = up->waitq) != nil){
		up->waitq = wq->next;
		free(wq);
	}

	/* release debuggers */
	if(up->pdbg != nil) {
		wakeup(&up->pdbg->sleep);
		up->pdbg = nil;
	}
	if(up->syscalltrace != nil) {
		free(up->syscalltrace);
		up->syscalltrace = nil;
	}
	if(up->watchpt != nil){
		free(up->watchpt);
		up->watchpt = nil;
	}
	up->nwatchpt = 0;
	qunlock(&up->debug);

/*	qlock(&up->seglock);
	for(s = up->seg; s < &up->seg[NSEG]; s++) {
		if(*s != nil) {
			putseg(*s);
			*s = nil;
		}
	}
	qunlock(&up->seglock);*/

	edfstop(up);
	up->state = Moribund;
	sched();
	panic("pexit");
}

static int
haswaitq(void *x)
{
	return ((Proc*)x)->waitq != nil;
}

ulong
pwait(Waitmsg *w)
{
	ulong cpid;
	Waitq *wq;

	if(!canqlock(&up->qwaitr))
		error(Einuse);

	if(waserror()) {
		qunlock(&up->qwaitr);
		nexterror();
	}

	lock(&up->exl);
	while(up->waitq == nil) {
		if(up->nchild == 0) {
			unlock(&up->exl);
			error(Enochild);
		}
		unlock(&up->exl);
		sleep(&up->waitr, haswaitq, up);
		lock(&up->exl);
	}
	wq = up->waitq;
	up->waitq = wq->next;
	up->nwait--;
	unlock(&up->exl);

	qunlock(&up->qwaitr);
	poperror();

	if(w != nil)
		memmove(w, &wq->w, sizeof(Waitmsg));
	cpid = wq->w.pid;
	free(wq);
	return cpid;
}


/* macro for speed? */
Proc*
proctab(int i)
{
#define proctab(x) (&procalloc.arena[(x)])
	return proctab(i);
}

void
dumpaproc(Proc *p)
{
	/*ulong bss; 9front shows this */
	char *s;

	if(p == nil)
		return;

	/*bss = 0;
	if(p->seg[BSEG] != nil)
		bss = p->seg[BSEG]->top;*/

	s = p->psstate;
	if(s == nil)
		s = statename[p->state];
	print("%3ud:%10s pc %#p dbgpc %#p  %8s (%s) ut %d st %d bss %ux qpc %#p nl %d nd %ud lpc %#p pri %ud\n",
		p->pid, p->text, p->pc, dbgpc(p),  s, statename[p->state],
		p->time[0], p->time[1], 0/*bss*/, p->qpc, p->nlocks, p->delaysched,
		p->lastlock ? p->lastlock->pc : 0, p->priority);
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
		dumppgrp("	", p->env->pgrp);
	}
}

/* different from 9front, need to change after dis is removed */
void
kproc(char *name, void (*func)(void *), void *arg, int flags)
{
	Proc *p;
	Pgrp *pg;
	Fgrp *fg;
	Egrp *eg;

	while((p = newproc()) == nil){
		freebroken();
		resrcwait("no procs for kproc");
	}

	qlock(&p->debug);
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

	kstrdup(&p->env->user, up->env->user);
	kstrdup(&p->text, name);
	kstrdup(&p->args, "");
	p->nargs = 0;
	p->setargs = 0;

/*	if(kpgrp == nil)
		kpgrp = newpgrp();
	p->pgrp = kpgrp;
	incref(kpgrp);*/

	p->kp = 1;

	memset(p->time, 0, sizeof(p->time));
	p->time[TReal] = MACHP(0)->ticks;
	cycles(&p->kentry);
	p->pcycles = -p->kentry;

	/* pidalloc(p); is done in newproc() */

	p->fpsave = up->fpsave;
/*	p->scallnr = up->scallnr; */
	p->nerrlab = 0;

	qunlock(&p->debug);

	procpriority(p, PriKproc, 0);

	p->psstate = nil;
	ready(p);
}

/*
 *  called splhi() by notify().  See comment in notify for the
 *  reasoning.
 */
void
procctl(void)
{
	char *state;
	ulong s;

	switch(up->procctl) {
	case Proc_exitbig:
		spllo();
		up->fpstate &= ~FPillegal;
		pprint("Killed: Insufficient physical memory\n");
		pexit("Killed: Insufficient physical memory", 1);

	case Proc_exitme:
		spllo();		/* pexit has locks in it */
		pexit("Killed", 1);

	case Proc_traceme:
		if(up->nnote == 0)
			return;
		/* No break */

	case Proc_stopme:
		up->procctl = 0;
		state = up->psstate;
		up->psstate = "Stopped";
		/* free a waiting debugger */
		s = spllo();
		qlock(&up->debug);
		if(up->pdbg != nil) {
			wakeup(&up->pdbg->sleep);
			up->pdbg = nil;
		}
		qunlock(&up->debug);
		splhi();
		up->state = Stopped;
		sched();
		up->psstate = state;
		splx(s);
		return;
	}
}

#include "errstr.h"

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
showerrlabs(char *str)
{
	int i;

	print("%s caller 0x%zx\n", str, getcallerpc(&str));
	for(i=0; i<up->nerrlab; i++){
		print("	i %d SP 0x%p PC 0x%p\n", i, up->errlab[i].sp, up->errlab[i].pc);
	}
}

void
error(char *err)
{
	if(up == nil)
		panic("error(%s) not in a process", err);
	spllo();
	if(up->nerrlab >= NERR)
		panic("error stack too deep");
	if(err == nil)
		panic("error: nil parameter");
	kstrcpy(up->env->errstr, err, ERRMAX);
	setlabel(&up->errlab[NERR-1]);
	if(emptystr(err) == 1){
		DBG("error nil error err %s caller 0x%p up->pid %d\n", err, getcallerpc(&err), up->pid);
		up->env->errpc = 0;
		/* showerrlabs("error == nil"); */
	}else{
		DBG("error err %s caller 0x%p up->pid %d\n", err, getcallerpc(&err), up->pid);
		up->env->errpc = getcallerpc(&err);
		/* proactively show issues */
		/* print("up->nerrlab %d error %s raised by 0x%zx\n",
			up->nerrlab, err, getcallerpc(&err)); */
		/* showerrlabs("error != nil"); */
	}
	nexterror();
}

void
nexterror(void)
{
	if(up->nerrlab < 1)
		panic("nothing on the error stack to go back to");
	gotolabel(&up->errlab[--up->nerrlab]);
}


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
 *  change ownership to 'new' of all processes owned by 'old'.  Used when
 *  eve changes.
 */
void
renameuser(char *old, char *new)
{
	Proc *p;
	int i;

	for(i = 0; i < conf.nproc; i++){
		p = proctab(i);
		qlock(&p->debug);
		if(p->user != nil && strcmp(old, p->user) == 0)
			kstrdup(&p->user, new);
		qunlock(&p->debug);
	}
}

void
procsetuser(char *new)
{
	qlock(&up->debug);
	kstrdup(&up->user, new);
	up->basepri = PriNormal;
	qunlock(&up->debug);
}

/*
 *  time accounting called by clock() splhi'd
 */
void
accounttime(void)
{
	Proc *p;
	ulong n, per;
	static ulong nrun;

	p = m->proc;
	if(p != nil) {
		nrun++;
		p->time[p->insyscall]++;
	}

	/* calculate decaying duty cycles */
	n = perfticks();
	per = n - m->perf.last;
	m->perf.last = n;
	per = ((uvlong)m->perf.period*(HZ-1) + per)/HZ;
	if(per != 0)
		m->perf.period = per;

	m->perf.avg_inidle = ((uvlong)m->perf.avg_inidle*(HZ-1)+m->perf.inidle)/HZ;
	m->perf.inidle = 0;

	m->perf.avg_inintr = ((uvlong)m->perf.avg_inintr*(HZ-1)+m->perf.inintr)/HZ;
	m->perf.inintr = 0;

	/* only one processor gets to compute system load averages */
	if(m->machno != 0)
		return;

	/*
	 * calculate decaying load average.
	 * if we decay by (n-1)/n then it takes
	 * n clock ticks to go from load L to .36 L once
	 * things quiet down.  it takes about 5 n clock
	 * ticks to go to zero.  so using HZ means this is
	 * approximately the load over the last second,
	 * with a tail lasting about 5 seconds.
	 */
	n = nrun;
	nrun = 0;
	n = (nrdy+n)*1000*100;
	pload = ((uvlong)pload*(HZ-1)+n)/HZ;
	m->load = pload/100;
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

static ulong
setparentpid(Proc *p, Proc *pp)
{
	Pid *i;

	i = pidadd(pp->pid);
	return p->parentpid = i->pid;
}

/*
 *  allocate pid, noteid and parentpid to a process
 */
ulong
pidalloc(Proc *p)
{
	Pid *i;

	/* skip for the boot process */
	if(up != nil)
		setparentpid(p, up);
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

	if(p->parentpid != 0)
		piddel(pidlookup(p->parentpid));

	p->pid = p->noteid = p->parentpid = 0;
}
