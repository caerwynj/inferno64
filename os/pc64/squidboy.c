#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"
#include "io.h"
#include "ureg.h"

#include "mp.h"

extern void _stts(void);

static void
squidboy(Apic* apic)
{
print("starting squidboy\n");
	machinit();
	mmuinit();
	cpuidentify();
	if(arch->clockinit)
		arch->clockinit();
	cpuidprint();
	syncclock();
	active.machs[m->machno] = 1;
	apic->online = 1;
	lapicinit(apic);
	lapiconline();
	timersinit();
	_stts();
	schedinit();
}

void
mpstartap(Apic* apic)
{
	uintptr *apbootp, *pml4/*, *pdp0*/;
	Segdesc *gdt;
	Mach *mach;
	uchar *p, *q;
	int i;

print("mpstartap apic->machno %d: \n", apic->machno);
	/*
	 * Initialise the AP page-tables and Mach structure.
	 * Xspanalloc will panic if an allocation can't be made.
	 */
	p = xspanalloc(1*PTSZ + BY2PG + MACHSIZE, BY2PG, 0);
	pml4 = (uintptr*)p;
	p += PTSZ;
	/* pdp0 = (uintptr*)p;
	p += PTSZ; */
	gdt = (Segdesc*)p;
	p += BY2PG;
	mach = (Mach*)p;

	memset(pml4, 0, PTSZ);
	/*memset(pdp0, 0, PTSZ);*/
	memset(gdt, 0, BY2PG);
	memset(mach, 0, MACHSIZE);

	mach->machno = apic->machno;
	mach->pml4 = pml4;
	mach->gdt  = gdt;	/* filled by mmuinit */
	MACHP(mach->machno) = mach;

	/*
	 * share the page tables across all processors except for pml4
	 * they should be static at this point
	 */
	for(i=0; i<BY2PG/8; i+=8){
		pml4[i] = MACHP(0)->pml4[i];
if(pml4[i] != 0)
print("mpstartap i %d pml4[i] 0x%p MACHP(0)->pml4[i] 0x%p\n", i, pml4[i], MACHP(0)->pml4[i]);
	}

	/*
	 * Tell the AP where its kernel vector and pdb are.
	 * The offsets are known in the AP bootstrap code.
	 */
	apbootp = (uintptr*)(APBOOTSTRAP+0x08);
	apbootp[0] = (uintptr)squidboy;	/* assembler jumps here eventually */
	apbootp[1] = (uintptr)PADDR(pml4);
	apbootp[2] = (uintptr)apic;
	apbootp[3] = (uintptr)mach;
	apbootp[4] |= (uintptr)m->havenx<<11;	/* EFER */
for(i=0;i<80;i++){
	print(" %x", *((uchar*)APBOOTSTRAP+i));
}
print("\n");

	/*
	 * Universal Startup Algorithm.
	 */
	p = KADDR(0x467);		/* warm-reset vector */
	*p++ = PADDR(APBOOTSTRAP);
	*p++ = PADDR(APBOOTSTRAP)>>8;
	i = (PADDR(APBOOTSTRAP) & ~0xFFFF)/16;
	/* code assumes i==0 */
	if(i != 0)
		print("mp: bad APBOOTSTRAP i 0x%ux\n", i);
	*p++ = i;
	*p = i>>8;
	print("p 0x%p PADDR(APBOOTSTRAP) 0x%p (PADDR(APBOOTSTRAP) & ~0xFFFF)/16 0x%p\n",
			p, PADDR(APBOOTSTRAP), (PADDR(APBOOTSTRAP) & ~0xFFFF)/16);
	for(q = (uchar*)KADDR(0x467); q<=p; q++){
		print("	q 0x%p *q 0x%x",q, *q);
	}
	print("\n");
	coherence();

	nvramwrite(0x0F, 0x0A);	/* shutdown code: warm reset upon init ipi */
	lapicstartap(apic, PADDR(APBOOTSTRAP));
	for(i = 0; i < 100000; i++){
		if(arch->fastclock == tscticks)
			cycles(&m->tscticks);	/* for ap's syncclock(); */
		if(apic->online){
print("online\n");
			break;
		}
		delay(1);
	}
print("nvramwrite(0x0F, 000)\n");
	nvramwrite(0x0F, 0x00);
}
