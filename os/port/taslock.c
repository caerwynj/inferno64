#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"
#include "../port/error.h"

static void
lockloop(Lock *l, uintptr pc)
{
	extern int panicking;

	if(panicking)
		return;
	setpanic();
	panic("lock loop 0x%p key 0x%ux pc 0x%zux held by pc 0x%zux\n", l, l->key, pc, l->pc);
	panic("lockloop");
}

void
lock(Lock *l)
{
	int i;
	uintptr pc;

	pc = getcallerpc(&l);
	if(up == 0) {
		if (_tas((int*)&l->key) != 0) {
			for(i=0; ; i++) {
				if(_tas((int*)&l->key) == 0)
					break;
				if (i >= 1000000) {
					lockloop(l, pc);
					break;
				}
			}
		}
		l->pc = pc;
		return;
	}

	for(i=0; ; i++) {
		if(_tas((int*)&l->key) == 0)
			break;
		if (i >= 1000) {
			lockloop(l, pc);
			break;
		}
		if(conf.nmach == 1 && up->state == Running && islo()) {
			up->pc = pc;
			sched();
		}
	}
	l->pri = up->pri;
	up->pri = PriLock;
	l->pc = pc;
}

void
ilock(Lock *l)
{
	uintptr x, pc;
	int i;

	pc = getcallerpc(&l);
	x = splhi();
	for(;;) {
		if(_tas((int*)&l->key) == 0) {
			l->sr = x;
			l->pc = pc;
			return;
		}
		if(conf.nmach < 2)
			panic("ilock: no way out: pc 0x%zux: lock 0x%lux held by pc 0x%zux", pc, l, l->pc);
		for(i=0; ; i++) {
			if(l->key == 0)
				break;
			clockcheck();
			if (i > 100000) {
				lockloop(l, pc);
				break;
			}
		}
	}
}

int
canlock(Lock *l)
{
	if(_tas((int*)&l->key))
		return 0;
	if(up){
		l->pri = up->pri;
		up->pri = PriLock;
	}
	l->pc = getcallerpc(&l);
	return 1;
}

void
unlock(Lock *l)
{
	int p;

	if(l->key == 0)
		print("unlock: not locked: pc %zux\n", getcallerpc(&l));
	p = l->pri;
	l->pc = 0;
	l->key = 0;
	coherence();
	if(up && islo()){
		/*
		 * Call sched if the need arose while locks were held
		 * But, don't do it from interrupt routines, hence the islo() test
		 */
		up->pri = p;
		if(up->state == Running && anyhigher())
			sched();
	}
}

void
iunlock(Lock *l)
{
	ulong sr;

	if(l->key == 0)
		print("iunlock: not locked: pc %zux\n", getcallerpc(&l));
	sr = l->sr;
	l->pc = 0;
	l->key = 0;
	coherence();
	splx(sr);
}
