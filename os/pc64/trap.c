#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"io.h"
#include	"ureg.h"
#include	"../port/error.h"

int (*breakhandler)(Ureg *ur, Proc*);

static void debugbpt(Ureg*, void*);
static void faultamd64(Ureg*, void*);
static void doublefault(Ureg*, void*);
static void unexpected(Ureg*, void*);
static void _dumpstack(Ureg*);

static Lock vctllock;
static Vctl *vctl[256];

enum
{
	Ntimevec = 20		/* number of time buckets for each intr */
};
ulong intrtimes[256][Ntimevec];

void
intrenable(int irq, void (*f)(Ureg*, void*), void* a, int tbdf, char *name)
{
	int vno;
	Vctl *v;

	if(f == nil){
		print("intrenable: nil handler for %d, tbdf 0x%uX for %s\n",
			irq, tbdf, name);
		return;
	}

	v = xalloc(sizeof(Vctl));
	v->isintr = 1;
	v->irq = irq;
	v->tbdf = tbdf;
	v->f = f;
	v->a = a;
	strncpy(v->name, name, KNAMELEN-1);
	v->name[KNAMELEN-1] = 0;

	ilock(&vctllock);
	vno = arch->intrenable(v);
	if(vno == -1){
		iunlock(&vctllock);
		print("intrenable: couldn't enable irq %d, tbdf 0x%uX for %s\n",
			irq, tbdf, v->name);
		xfree(v);
		return;
	}
	if(vctl[vno]){
		if(vctl[vno]->isr != v->isr || vctl[vno]->eoi != v->eoi)
			panic("intrenable: handler: %s %s %luX %luX %luX %luX\n",
				vctl[vno]->name, v->name,
				vctl[vno]->isr, v->isr, vctl[vno]->eoi, v->eoi);
		v->next = vctl[vno];
	}
	vctl[vno] = v;
	iunlock(&vctllock);
}

int
intrdisable(int irq, void (*f)(Ureg *, void *), void *a, int tbdf, char *name)
{
	Vctl **pv, *v;
	int vno;

	/*
	 * For now, none of this will work with the APIC code,
	 * there is no mapping between irq and vector as the IRQ
	 * is pretty meaningless.
	 */
	if(arch->intrvecno == nil)
		return -1;
	vno = arch->intrvecno(irq);
	ilock(&vctllock);
	pv = &vctl[vno];
	while (*pv && 
		  ((*pv)->irq != irq || (*pv)->tbdf != tbdf || (*pv)->f != f || (*pv)->a != a ||
		   strcmp((*pv)->name, name)))
		pv = &((*pv)->next);
	assert(*pv);

	v = *pv;
	*pv = (*pv)->next;	/* Link out the entry */
	
	if(vctl[vno] == nil && arch->intrdisable != nil)
		arch->intrdisable(irq);
	iunlock(&vctllock);
	xfree(v);
	return 0;
}

static s32
irqallocread(Chan*, void *vbuf, s32 n, s64 offset)
{
	char *buf, *p, str[2*(11+1)+KNAMELEN+1+1];
	int m, vno;
	long oldn;
	Vctl *v;

	if(n < 0 || offset < 0)
		error(Ebadarg);

	oldn = n;
	buf = vbuf;
	for(vno=0; vno<nelem(vctl); vno++){
		for(v=vctl[vno]; v; v=v->next){
			m = snprint(str, sizeof str, "%11d %11d %.*s\n", vno, v->irq, KNAMELEN, v->name);
			if(m <= offset)	/* if do not want this, skip entry */
				offset -= m;
			else{
				/* skip offset bytes */
				m -= offset;
				p = str+offset;
				offset = 0;

				/* write at most max(n,m) bytes */
				if(m > n)
					m = n;
				memmove(buf, p, m);
				n -= m;
				buf += m;

				if(n == 0)
					return oldn;
			}	
		}
	}
	return oldn - n;
}

void
trapenable(int vno, void (*f)(Ureg*, void*), void* a, char *name)
{
	Vctl *v;

	if(f == nil)
		panic("trapenable: nil handler for %d, for %s\n",
			vno, name);
	if(vno < 0 || vno >= VectorPIC)
		panic("trapenable: vno %d out of range\n", vno);
	if((v = xalloc(sizeof(Vctl))) == nil){
		panic("trapenable: out of memory");
	}
	v->tbdf = BUSUNKNOWN;
	v->f = f;
	v->a = a;
	v->irq = -1;
	v->cpu = -1;
	strncpy(v->name, name, KNAMELEN);
	v->name[KNAMELEN-1] = 0;

	lock(&vctllock);
	if(vctl[vno])
		v->next = vctl[vno]->next;
	vctl[vno] = v;
	unlock(&vctllock);
}

static void
nmihandler(Ureg *ureg, void*)
{
	iprint("cpu%d: nmi PC %#p, status %ux\n",
		m->machno, ureg->pc, inb(0x61));
	while(m->machno != 0)
		;
}

static void
nmienable(void)
{
	int x;

	trapenable(VectorNMI, nmihandler, nil, "nmi");

	/*
	 * Hack: should be locked with NVRAM access.
	 */
	outb(0x70, 0x80);		/* NMI latch clear */
	outb(0x70, 0);

	x = inb(0x61) & 0x07;		/* Enable NMI */
	outb(0x61, 0x08|x);
	outb(0x61, x);
}

void
trapinit0(void)
{
	u32 d1, v;
	uintptr vaddr;
	Segdesc *idt;
	uintptr ptr[2];

	idt = (Segdesc*)IDTADDR;
	vaddr = (uintptr)vectortable;
	for(v = 0; v < 256; v++){
		d1 = (vaddr & 0xFFFF0000)|SEGP;
		switch(v){
		case VectorBPT:
			d1 |= SEGPL(0)|SEGIG;
			break;

		case VectorSYSCALL:
			d1 |= SEGPL(0)|SEGIG;
			break;

		default:
			d1 |= SEGPL(0)|SEGIG;
			break;
		}

		idt->d0 = (vaddr & 0xFFFF)|(KESEL<<16);
		idt->d1 = d1;
		idt++;

		idt->d0 = (vaddr >> 32);
		idt->d1 = 0;
		idt++;

		vaddr += 6;
	}
	((ushort*)&ptr[1])[-1] = sizeof(Segdesc)*512-1;
	ptr[1] = (uintptr)IDTADDR;
	lidt(&((ushort*)&ptr[1])[-1]);
}

void
trapinit(void)
{
	/*
	 * Special traps.
	 * Syscall() is called directly without going through trap().
	 */
	trapenable(VectorBPT, debugbpt, 0, "debugpt");
	trapenable(VectorPF, faultamd64, 0, "faultamd64");
	trapenable(Vector2F, doublefault, 0, "doublefault");
	trapenable(Vector15, unexpected, 0, "unexpected");

	nmienable();

	/* 9front calls this irqinit() */
	addarchfile("irqalloc", 0444, irqallocread, nil);
}

static char* excname[32] = {
	"divide error",
	"debug exception",
	"nonmaskable interrupt",
	"breakpoint",
	"overflow",
	"bounds check",
	"invalid opcode",
	"coprocessor not available",
	"double fault",
	"coprocessor segment overrun",
	"invalid TSS",
	"segment not present",
	"stack exception",
	"general protection violation",
	"page fault",
	"15 (reserved)",
	"coprocessor error",
	"alignment check",
	"machine check",
	"19 (reserved)",
	"20 (reserved)",
	"21 (reserved)",
	"22 (reserved)",
	"23 (reserved)",
	"24 (reserved)",
	"25 (reserved)",
	"26 (reserved)",
	"27 (reserved)",
	"28 (reserved)",
	"29 (reserved)",
	"30 (reserved)",
	"31 (reserved)",
};

/*
 *  keep histogram of interrupt service times
 */
void
intrtime(Mach*, int vno)
{
	USED(vno);
}

/*
 *  All traps come here.  It is slower to have all traps call trap()
 *  rather than directly vectoring the handler.  However, this avoids a
 *  lot of code duplication and possible bugs.  The only exception is
 *  VectorSYSCALL.
 *  Trap is called with interrupts disabled via interrupt-gates.
 */
void
trap(Ureg* ureg)
{
	int i, vno;
	char buf[ERRMAX];
	Vctl *ctl, *v;
	Mach *mach;

	vno = ureg->trap;
	if(ctl = vctl[vno]){
		if(ctl->isintr){
			m->intr++;
			if(vno >= VectorPIC && vno != VectorSYSCALL)
				m->lastintr = ctl->irq;
		}

		if(ctl->isr)
			ctl->isr(vno);
		for(v = ctl; v != nil; v = v->next){
			if(v->f)
				v->f(ureg, v->a);
		}
		if(ctl->eoi)
			ctl->eoi(vno);

		if(ctl->isintr){
			if(up && ctl->irq != IrqTIMER && ctl->irq != IrqCLOCK)
				preemption(0);
		}
	}
	else if(vno <= nelem(excname) && up->type == Interp){
		spllo();
		sprint(buf, "sys: trap: %s pc 0x%zx", excname[vno], ureg->pc);
		error(buf);
	}
	else if(vno >= VectorPIC && vno != VectorSYSCALL){
		/*
		 * An unknown interrupt.
		 * Check for a default IRQ7. This can happen when
		 * the IRQ input goes away before the acknowledge.
		 * In this case, a 'default IRQ7' is generated, but
		 * the corresponding bit in the ISR isn't set.
		 * In fact, just ignore all such interrupts.
		 */

		/* call all interrupt routines, just in case */
		for(i = VectorPIC; i <= MaxIrqLAPIC; i++){
			ctl = vctl[i];
			if(ctl == nil)
				continue;
			if(!ctl->isintr)
				continue;
			for(v = ctl; v != nil; v = v->next){
				if(v->f)
					v->f(ureg, v->a);
			}
			/* should we do this? */
			if(ctl->eoi)
				ctl->eoi(i);
		}

		/* clear the interrupt */
		i8259isr(vno);
			
		if(1)print("cpu%d: spurious interrupt %d, last %d",
			m->machno, vno, m->lastintr);
		if(1)if(conf.nmach > 1){
			for(i = 0; i < MAXMACH; i++){
				if(active.machs[i] == 0)
					continue;
				mach = MACHP(i);
				if(m->machno == mach->machno)
					continue;
				print(" cpu%d: last %d",
					mach->machno, mach->lastintr);
			}
			print("\n");
		}
		m->spuriousintr++;
		return;
	}
	else{
		if(vno == VectorNMI){
			nmienable();
			if(m->machno != 0){
				print("cpu%d: PC %8.8zuX\n",
					m->machno, ureg->pc);
			}
		}
		dumpregs(ureg);
		if(vno < nelem(excname))
			panic("%s", excname[vno]);
		panic("unknown trap/intr: %d\n", vno);
	}

	/* delaysched set because we held a lock or because our quantum ended */
	if(up && up->delaysched){
		sched();
		splhi();
	}
}

/*
 *  dump registers
 */
void
dumpregs2(Ureg* ureg)
{
	if(up)
		print("cpu%d: registers for %s %ud\n",
			m->machno, up->text, up->pid);
	else
		print("cpu%d: registers for kernel\n", m->machno);
	print("FLAGS=%zux TRAP=%zux ECODE=%zux PC=%zux",
		ureg->flags, ureg->trap, ureg->ecode, ureg->pc);
	print(" SS=%4.4zuX USP=%zux\n", ureg->ss & 0xFFFF, ureg->usp);
	print("  AX %8.8zuX  BX %8.8zuX  CX %8.8zuX  DX %8.8zuX\n",
		ureg->ax, ureg->bx, ureg->cx, ureg->dx);
	print("  SI %8.8zuX  DI %8.8zuX  BP %8.8zuX\n",
		ureg->si, ureg->di, ureg->bp);
	print("  CS %4.4zux  DS %4.4ux  ES %4.4ux  FS %4.4ux  GS %4.4ux\n",
		ureg->cs & 0xFFFF, ureg->ds & 0xFFFF, ureg->es & 0xFFFF,
		ureg->fs & 0xFFFF, ureg->gs & 0xFFFF);
}

void
dumpregs(Ureg* ureg)
{
	extern ulong etext;
	vlong mca, mct;

	dumpregs2(ureg);

	/*
	 * Processor control registers.
	 * If machine check exception, time stamp counter, page size extensions
	 * or enhanced virtual 8086 mode extensions are supported, there is a
	 * CR4. If there is a CR4 and machine check extensions, read the machine
	 * check address and machine check type registers if RDMSR supported.
	 */
	print("  CR0 %8.8zux CR2 %8.8zux CR3 %8.8zux",
		getcr0(), getcr2(), getcr3());
	if(m->cpuiddx & 0x9A){
		print(" CR4 %8.8zux", getcr4());
		if((m->cpuiddx & 0xA0) == 0xA0){
			rdmsr(0x00, &mca);
			rdmsr(0x01, &mct);
			print("\n  MCA %8.8zux MCT %8.8zux", mca, mct);
		}
	}
	print("\n  ur %lux up %lux\n", ureg, up);
}

/*
 * Fill in enough of Ureg to get a stack trace, and call a function.
 * Used by debugging interface rdb.
 */
void
callwithureg(void (*fn)(Ureg*))
{
	Ureg ureg;
	ureg.pc = getcallerpc(&fn);
	ureg.sp = (uintptr)&fn;
	fn(&ureg);
}

static void
_dumpstack(Ureg *ureg)
{
	uintptr l, v, i, estack;
	extern uintptr etext;

	print("ktrace /kernel/path %.8zux %.8zux\n", ureg->pc, ureg->sp);
	i = 0;
	if(up &&
		(uintptr)&l >= (uintptr)up->kstack &&
		(uintptr)&l <= (uintptr)up->kstack+KSTACK)
		estack = (uintptr)up->kstack+KSTACK;
	else if((uintptr)&l >= (uintptr)m->stack &&
		(uintptr)&l <= (uintptr)m+BY2PG)
		estack = (uintptr)m+MACHSIZE;
	else
		return;

	for(l=(uintptr)&l; l<estack; l+=sizeof(intptr)){
		v = *(uintptr*)l;
		if(KTZERO < v && v < (uintptr)&etext){
			/*
			 * we could Pick off general CALL (((uchar*)v)[-5] == 0xE8)
			 * and CALL indirect through AX (((uchar*)v)[-2] == 0xFF && ((uchar*)v)[-2] == 0xD0),
			 * but this is too clever and misses faulting address.
			 */
			print("%.8zux=%.8zux ", l, v);
			i++;
		}
		if(i == 4){
			i = 0;
			print("\n");
		}
	}
	if(i)
		print("\n");
}

void
dumpstack(void)
{
	callwithureg(_dumpstack);
}

static void
debugbpt(Ureg* ureg, void*)
{
	char buf[ERRMAX];

	if(breakhandler != nil){
		breakhandler(ureg, up);
		return;
	}
	if(up == 0)
		panic("kernel bpt");
	/* restore pc to instruction that caused the trap */
	ureg->pc--;
	sprint(buf, "sys: breakpoint");
	error(buf);
}

static void
doublefault(Ureg*, void*)
{
	panic("double fault");
}

static void
unexpected(Ureg* ureg, void*)
{
	print("unexpected trap %zud; ignoring\n", ureg->trap);
}

static void
faultamd64(Ureg* ureg, void*)
{
	uintptr addr;
	int read, user;
	char buf[ERRMAX];

	addr = getcr2();
	user = (ureg->cs & 0xFFFF) == KESEL;
	if(!user && mmukmapsync(addr))
		return;
	read = !(ureg->ecode & 2);
	spllo();
	snprint(buf, sizeof(buf), "trap: fault %s pc=0x%zux addr=0x%zux",
			read ? "read" : "write", ureg->pc, addr);
	if(up->type == Interp)
		disfault(ureg, buf);
	dumpregs(ureg);
	print("fault: %s\n", buf);
	panic("fault: %s\n", buf);
}

static void
linkproc(void)
{
	spllo();
	up->kpfun(up->arg);
	pexit("kproc dying", 0);
}

void
kprocchild(Proc* p, void (*func)(void*), void* arg)
{
	/*
	 * gotolabel() needs a word on the stack in
	 * which to place the return PC used to jump
	 * to linkproc().
	 */
	p->sched.pc = (uintptr)linkproc;
	p->sched.sp = (uintptr)p->kstack+KSTACK-BY2WD;

	p->kpfun = func;
	p->arg = arg;
}



ulong
dbgpc(Proc *p)
{
	Ureg *ureg;

	ureg = p->dbgreg;
	if(ureg == 0)
		return 0;

	return ureg->pc;
}
