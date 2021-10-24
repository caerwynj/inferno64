#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"
#include "../port/error.h"
#include "edf.h"

long maxlockcycles;
long maxilockcycles;
long cumlockcycles;
long cumilockcycles;
uintptr maxlockpc;
uintptr maxilockpc;

struct
{
	ulong	locks;
	ulong	glare;
	ulong	inglare;
} lockstats;

static void
dumplockmem(char *tag, Lock *l)
{
	uchar *cp;
	int i;

	iprint("%s: ", tag);
	cp = (uchar*)l;
	for(i = 0; i < 64; i++)
		iprint("%2.2ux ", cp[i]);
	iprint("\n");
}

void
lockloop(Lock *l, uintptr pc)
{
	extern int panicking;
	Proc *p;

	if(panicking)
		return;

	p = l->p;
	print("lock %#p loop key %#ux pc %#p held by pc %#p proc %ud\n",
		l, l->key, pc, l->pc, p ? p->pid : 0);
	dumpaproc(up);
	if(p != nil)
		dumpaproc(p);
}

/* if looped to obtain a lock, return 1. Else, return 0 */
int
lock(Lock *l)
{
	int i;
	uintptr pc;

	pc = getcallerpc(&l);

	lockstats.locks++;
	if(up)
		up->nlocks++;	/* prevent being scheded */
	if(tas(&l->key) == 0){ /* got the lock on the 1st attempt, done */
		if(up){
				up->lastlock = l;
				l->priority = up->priority;
				up->priority = PriLock;
			}
		l->pc = pc;
		l->p = up;
		l->m = MACHP(m->machno);
		l->isilock = 0;
#ifdef LOCKCYCLES
		l->lockcycles = -lcycles();
#endif
		return 0;
	}
	if(up)
		up->nlocks--;

	lockstats.glare++;
	for(;;){
		lockstats.inglare++;
		i = 0;
		while(l->key){
			if(conf.nmach < 2 && up && up->state == Running && islo()
				/* && up->edf && (up->edf->flags & Admitted)*/){
				/*
				 * Priority inversion, yield on a uniprocessor; on a
				 * multiprocessor, the other processor will unlock
				 */
				print("inversion %#p pc %#p proc %zud held by pc %#p proc %zud\n",
					l, pc, up != nil ? up->pid : 0, l->pc, l->p != nil ? ((Proc*)l->p)->pid : 0);
				/* up->edf->d = todget(nil);*/	/* yield to process with lock */
				up->pc = pc;
				sched();
			}
			if(i++ > 100000000){
				i = 0;
				lockloop(l, pc);
			}
		}
		if(up)
			up->nlocks++;
		if(tas(&l->key) == 0){
			if(up){
				up->lastlock = l;
				l->priority = up->priority;
				up->priority = PriLock;
			}
			l->pc = pc;
			l->p = up;
			l->m = MACHP(m->machno);
			l->isilock = 0;
#ifdef LOCKCYCLES
			l->lockcycles = -lcycles();
#endif
			return 1;
		}
		if(up)
			up->nlocks--;
	}
}

void
ilock(Lock *l)
{
	ulong x;
	uintptr pc;

	pc = getcallerpc(&l);
	lockstats.locks++;

	x = splhi();
	if(tas(&l->key) != 0){
		lockstats.glare++;
		if(conf.nmach < 2)
			panic("ilock: no way out: pc 0x%zux:"
					" lock 0x%p held by pc 0x%zux",
					pc, l, l->pc);
		/*
		 * Cannot also check l->pc, l->m, or l->isilock here
		 * because they might just not be set yet, or
		 * (for pc and m) the lock might have just been unlocked.
		 */
		for(;;){
			lockstats.inglare++;
			splx(x);
			while(l->key)
				;
			x = splhi();
			if(tas(&l->key) == 0)
				goto acquire;
		}
	}
acquire:
	m->ilockdepth++;
	if(up)
		up->lastilock = l;
	l->sr = x;
	l->pc = pc;
	l->p = up;
	l->m = MACHP(m->machno);
	l->isilock = 1;
#ifdef LOCKCYCLES
	l->lockcycles = -lcycles();
#endif
}

int
canlock(Lock *l)
{
	if(up)
		up->nlocks++;
	if(tas(&l->key) != 0){
		if(up)
			up->nlocks--;
		return 0;
	}

	if(up){
		up->lastlock = l;
		l->priority = up->priority;
		up->priority = PriLock;
	}
	l->pc = getcallerpc(&l);
	l->p = up;
	l->m = MACHP(m->machno);
	l->isilock = 0;
#ifdef LOCKCYCLES
	l->lockcycles = -lcycles();
#endif
	return 1;
}

void
unlock(Lock *l)
{
	int pri;
#ifdef LOCKCYCLES
	l->lockcycles += lcycles();
	cumlockcycles += l->lockcycles;
	if(l->lockcycles > maxlockcycles){
		maxlockcycles = l->lockcycles;
		maxlockpc = l->pc;
	}
#endif
	if(l->key == 0)
		print("unlock(%#p): not locked: pc %#p up->pid %d up->text %s\n",
			l, getcallerpc(&l), up->pid, up->text);
	if(l->isilock)
		print("unlock(%#p) of ilock: pc %#p, held by %#p up->pid %d up->text %s\n",
			l, getcallerpc(&l), l->pc, up->pid, up->text);
	if(l->p != up){
		print("unlock(%#p): up changed: pc %#p, acquired at pc %#p,"
				" lock p %#p, unlock up %#p up->pid %d up->text %s up->mach->machno %d\n",
			l, getcallerpc(&l), l->pc, l->p, up, up->pid, up->text, up->mach->machno);
		dumpaproc(l->p);
		dumpaproc(up);
	}
	pri = l->priority;
	l->pc = 0;
	l->p = nil;
	l->m = nil;
	coherence();
	l->key = 0;

	if(up){
		up->priority = pri;
		up->lastlock = nil;
		if(--up->nlocks == 0 && up->delaysched && islo()){
			/*
			 * Call sched if the need arose while locks were held
			 * But, don't do it from interrupt routines, hence the islo() test
			 */
			sched();
		}
	}
}

uintptr ilockpcs[0x100] = { [0xff] = 1 };
static int n;

void
iunlock(Lock *l)
{
	ulong sr;

#ifdef LOCKCYCLES
	l->lockcycles += lcycles();
	cumilockcycles += l->lockcycles;
	if(l->lockcycles > maxilockcycles){
		maxilockcycles = l->lockcycles;
		maxilockpc = l->pc;
	}
	if(l->lockcycles > 2400)
		ilockpcs[n++ & 0xff]  = l->pc;
#endif
	if(l->key == 0)
		print("iunlock(%#p): not locked: pc %#p\n", l, getcallerpc(&l));
	if(!l->isilock)
		print("iunlock(%#p) of lock: pc %#p, held by %#p\n", l, getcallerpc(&l), l->pc);
	if(islo())
		print("iunlock(%#p) while lo: pc %#p, held by %#p\n", l, getcallerpc(&l), l->pc);

	sr = l->sr;
	l->sr = 0;
	l->pc = 0;
	l->p = nil;
	l->m = nil;
	coherence();
	l->key = 0;
	m->ilockdepth--;
	if(up)
		up->lastilock = nil;
	splx(sr);
}
