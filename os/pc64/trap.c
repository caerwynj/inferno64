#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"io.h"
#include	"ureg.h"
#include	"../port/error.h"

Vctl *vctl[256];	/* defined in pc/irq.c */

extern int irqhandled(Ureg*, int);
extern void irqinit(void);

int (*breakhandler)(Ureg *ur, Proc*);

static void debugbpt(Ureg*, void*);
static void faultamd64(Ureg*, void*);
static void doublefault(Ureg*, void*);
static void unexpected(Ureg*, void*);
static void _dumpstack(Ureg*);
static void dumpureg(Ureg* ureg);

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
	irqinit();

	nmienable();

	/*
	 * Special traps.
	 * Syscall() is called directly without going through trap().
	 */
	/* 9front specific trapenable(VectorDE, debugexc, 0, "debugexc"); */
	trapenable(VectorBPT, debugbpt, 0, "debugpt");
	trapenable(VectorPF, faultamd64, 0, "faultamd64");
	trapenable(Vector2F, doublefault, 0, "doublefault");
	trapenable(Vector15, unexpected, 0, "unexpected");
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

void
dumprstack(intptr h, intptr rsp, intptr he)
{
	intptr i;
	int l=0;

	print("Forth return stack h 0x%zx rsp 0x%zx RSTACK 0x%zx he 0x%zx\n",
			h, rsp, h+RSTACK, he);
	if(he == 0 || h == 0 || rsp < h || rsp >= he || h+RSTACK < h || h+RSTACK >= he)
		return;
	for(i = h + RSTACK-8; i >= rsp; i-=8){
		print("	0x%zx: 0x%zx", i, *(intptr*)i);
		l++;
		if(l == 3){
			l = 0;
			print("\n");
		}
	}
	print("\n");
}

void
dumppstack(intptr h, intptr psp, intptr he)
{
	intptr i;
	int l=0;

	print("Forth parameter stack h 0x%zx psp 0x%zx PSTACK 0x%zx he 0x%zx\n",
			h, psp, h+PSTACK, he);
	if(he == 0 || h == 0 || psp < h || psp >= he || h+PSTACK < h || h+PSTACK >= he)
		return;
	for(i = h + PSTACK-8; i >= psp; i-=8){
		print("	0x%zx: 0x%zx", i, *(intptr*)i);
		l++;
		if(l == 3){
			l = 0;
			print("\n");
		}
	}
	print("\n");
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
				preempted();
		}
	}
	else if(vno <= nelem(excname) && up->type == Interp){
		spllo();
		sprint(buf, "sys: trap: %s pc 0x%zx", excname[vno], ureg->pc);
		print(buf);
		dumpregs(ureg);
		_dumpstack(ureg);
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
			
		if(0)print("cpu%d: spurious interrupt %d, last %d",
			m->machno, vno, m->lastintr);
		if(0)if(conf.nmach > 1){
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
		dumpureg(ureg);
		dumpregs(ureg);
		if(vno < nelem(excname)){
			dumprstack(ureg->r11, ureg->r8, ureg->r12);
			dumppstack(ureg->r11, ureg->dx, ureg->r12);
			_dumpstack(ureg);
			panic("%s", excname[vno]);
		}
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
	print("  AX %8.8zuX  BX TOP %8.8zuX  CX %8.8zuX  DX PSP %8.8zuX\n",
		ureg->ax, ureg->bx, ureg->cx, ureg->dx);
	print("  SI %8.8zuX  DI %8.8zuX  BP %8.8zuX\n",
		ureg->si, ureg->di, ureg->bp);
	print("  CS %4.4zux  DS %4.4ux  ES %4.4ux  FS %4.4ux  GS %4.4ux\n",
		ureg->cs & 0xFFFF, ureg->ds & 0xFFFF, ureg->es & 0xFFFF,
		ureg->fs & 0xFFFF, ureg->gs & 0xFFFF);
	print("  R8 RSP %8.8zux  R9 IP %8.8zzux  R10 W %8.8zux\n"
			"  R11 UP %8.8zux  R12 UPE %8.8zux  R13 %8.8zux\n",
		ureg->r8, ureg->r9, ureg->r10,
		ureg->r11, ureg->r12, ureg->r13);
	print("  R14 up %8.8zux  R15 m %8.8zux\n",
		ureg->r14, ureg->r15);
}

void
dumpregs(Ureg* ureg)
{
	extern ulong etext;
	vlong mca, mct;
	intptr *i;

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
	print("\n  ur %lux up %lux ureg->bp & ~0xFFF %zx\n", ureg, up, ureg->bp & ~0xFFF);
	if((ureg->bp & ~0xFFF) == FFSTART){
		for(i = (intptr*)FFSTART; i<=(intptr*)ureg->bp; i++){
			print("0x%p: 0x%zx\n", i, *i);
		}
		for(i = (intptr*)FFEND; i>=(intptr*)ureg->sp; i--){
			print("0x%p: 0x%zx\n", i, *i);
		}
	}
}
/* displays in the order pushed into the stack */
void
dumpureg(Ureg* ureg)
{
	if(up)
		print("cpu%d: registers for %s %ud\n",
			m->machno, up->text, up->pid);
	else
		print("cpu%d: registers for kernel\n", m->machno);

	print("SS %4.4zuX SP %zux\n", ureg->ss & 0xFFFF, ureg->usp);
	print("	FLAGS %zux CS %zux PC %zux ECODE %zux TRAP %zux\n",
		ureg->flags, ureg->cs, ureg->pc, ureg->ecode, ureg->trap);
	print("	GS %4.4zux  FS %4.4ux  ES %4.4ux  DS %4.4ux\n",
		ureg->gs & 0xFFFF, ureg->fs & 0xFFFF, ureg->es & 0xFFFF,
		ureg->ds & 0xFFFF);

	print("	R15 m %8.8zux  R14 up %8.8zux R13 %8.8zux\n",
		ureg->r15, ureg->r14, ureg->r13);
	print("	R12 UPE %8.8zux	R11 UP %8.8zzux	R10 W %8.8zux\n"
			"	R9 IP %8.8zux	R8 RSP %8.8zux\n",
		ureg->r12, ureg->r11, ureg->r10,
		ureg->r9, ureg->r8);
	print("	BP RARG %8.8zux	DI %8.8zzux	SI %8.8zux\n"
			"	DX PSP %8.8zux	CX %8.8zux	BX TOP %8.8zux\n"
			"	AX %8.8zux\n",
		ureg->bp, ureg->di, ureg->si,
		ureg->dx, ureg->cx, ureg->bx,
		ureg->ax);
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
	int onlypc = 0;

	print("ktrace /kernel/path pc 0x%zux sp 0x%zux &l 0x%zux up 0x%p\n", ureg->pc, ureg->sp, &l, up);
	i = 0;
	if(up &&
		(uintptr)&l >= (uintptr)up->kstack &&
		(uintptr)&l <= (uintptr)up->kstack+KSTACK){
		estack = (uintptr)up->kstack+KSTACK;
		print("up->kstack 0x%zux estack 0x%zux\n",(uintptr)up->kstack, estack);
	}else if((uintptr)&l >= (uintptr)m->stack &&
		(uintptr)&l <= (uintptr)m+BY2PG){
		estack = (uintptr)m+MACHSIZE;
		print("m->stack 0x%zux estack 0x%zux\n",(uintptr)m->stack, estack);
	}else{
		if(up)
			print("up->kstack 0x%zux\n", (uintptr)up->kstack);
		else
			print("m->stack 0x%zux\n", (uintptr)m->stack);
		return;
	}

	for(l=(uintptr)&l; l<estack; l+=sizeof(intptr)){
		v = *(uintptr*)l;
		if(onlypc){
			if(KTZERO < v && v < (uintptr)&etext){
				/*
				 * we could Pick off general CALL (((uchar*)v)[-5] == 0xE8)
				 * and CALL indirect through AX (((uchar*)v)[-2] == 0xFF && ((uchar*)v)[-2] == 0xD0),
				 * but this is too clever and misses faulting address.
				 */
				print("%.8zux=%.8zux ", l, v);
				i++;
			}
		}else{
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
	snprint(buf, sizeof(buf), "trap: fault %s pc=0x%zux addr=0x%zux\n",
			read ? "read" : "write", ureg->pc, addr);
print(buf);
	dumpregs(ureg);
	dumprstack(ureg->r11, ureg->r8, ureg->r12);
	dumppstack(ureg->r11, ureg->dx, ureg->r12);
dumpstack();
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
	up->kpfun(up->kparg);
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
	p->kparg = arg;
}

uintptr
dbgpc(Proc *p)
{
	Ureg *ureg;

	ureg = p->dbgreg;
	if(ureg == 0)
		return 0;

	return ureg->pc;
}
