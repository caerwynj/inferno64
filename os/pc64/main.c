#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"io.h"
#include	"ureg.h"
#include	"rebootcode.i"

#define X86STEPPING(x)	((x) & 0x0F)
#define X86MODEL(x)	(((x)>>4) & 0x0F)
#define X86FAMILY(x)	(((x)>>8) & 0x0F)

Conf conf;
int idle_spin;

extern ulong kerndate;
extern void bootscreeninit(void);
extern int main_pool_pcnt;
extern int heap_pool_pcnt;
extern int image_pool_pcnt;
int	pckdebug;

static  uchar *sp;	/* stack pointer for /boot */

char bootdisk[KNAMELEN];

/* until I sort out the mp initialization issue */
extern void startaps(void);

static void
doc(char *m)
{
	/*int i;*/
	print("%s...\n", m);
	/*for(i = 0; i < 100*1024*1024; i++)
		i++;*/
}

enum {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
	Nvideo = 80*25,
};

extern u64 MemMin;
u32 nchars = 0;

void
writemsg(char *msg, int msglen)
{
	u8 *video = (u8*)0xB8000;
	u8 colour = VGA_COLOR_LIGHT_GREY | (VGA_COLOR_BLACK<<4);
	u32 i;

	if(nchars == 0){
		memset(video, 0, Nvideo*2);
	}else if(nchars + msglen >= Nvideo){
		memmove(video, video+(2*msglen), 2*(nchars-msglen));
		nchars -= msglen;
	}
	video += nchars*2;
	for(i = nchars; i < nchars+msglen; i++){
		*video++ = *msg++;
		*video++ = colour;
	}
	nchars += msglen;
}

void
ptedebug(uintptr pa, char *desc)
{
	uintptr *pml4e, *pdpe, *pde;
	char pdestr[64] = "unmapped";

	pml4e = mmuwalk((uintptr*)PML4ADDR, pa, 3, 0);
	pdpe = mmuwalk((uintptr*)PML4ADDR, pa, 2, 0);
	pde = mmuwalk((uintptr*)PML4ADDR, pa, 1, 0);
	if((intptr)pde > 0){
		snprint(pdestr, 64, "at 0x%p i %zd has 0x%p",
				pde, ((intptr)pde-(intptr)PD0ADDR)/sizeof(intptr), *pde);
	}
	print("\tpage of address 0x%zux (%s) with pml4 at 0x%p\n"
			"\t\tpml4 entry at 0x%p i %zd has 0x%p\n"
			"\t\tpdp entry at 0x%p i %zd has 0x%p\n"
			"\t\tpd entry %s\n",
			pa, desc, m->pml4,
			pml4e, (pml4e-m->pml4)/sizeof(intptr), *pml4e,
			pdpe, ((intptr)pdpe-(intptr)PDPADDR)/sizeof(intptr), *pdpe,
			pdestr);
}

void
showconfig(void)
{
	showconf();
	print("Important Addresses\n"
		"\tkdzero 0x%p confaddr 0x%p apbootstrap 0x%p idtaddr 0x%p\n"
		"\tcpu0mach 0x%p cpu0sp 0x%p cpu0gdt 0x%p\n"
		"\tcpu0pml4 0x%p cpu0pdp 0x%p  cpu0pd 0x%p\n"
		"\tcpu0end 0x%p\n",
		(void*)KDZERO, CONFADDR,APBOOTSTRAP,
		IDTADDR, CPU0MACH, CPU0SP, GDTADDR,
		PML4ADDR, PDPADDR, PD0ADDR, CPU0END);
	print("Some page table entries\n");
	ptedebug(1*MiB,"1 MiB");
	ptedebug(2*MiB,"2 MiB");
	ptedebug(400*MiB,"400 MiB");
	ptedebug(466*MiB,"466 MiB");
	ptedebug(468*MiB,"468 MiB");
	ptedebug(470*MiB,"470 MiB");
	ptedebug(512*MiB,"512 MiB");
	ptedebug(1*GiB,"1 GiB");
	ptedebug(4ull*GiB,"4 GiB");
}

/* to check from acid on whether the data segment is being trashed */
/* static int globaldatatest = 0x12345678; */
void
main(void)
{
	outb(0x3F2, 0x00);		/* botch: turn off the floppy motor */

	mach0init();
	bootargsinit();
	trapinit0();			/* set up idt, check notes on why so early */
	ioinit();
	i8250console();
	quotefmtinstall();
	screeninit();
	print("\nInferno release built at %lud\n", kerndate);
	showconfig();
	cpuidentify();
	meminit0();			/* builds the memmap */
	doc("archinit");
	archinit();
	doc("arch->clockinit");
	if(arch->clockinit)
		arch->clockinit();
	doc("meminit");
	meminit();			/* builds the conf.mem entries */
	doc("confinit");
	confinit();
	doc("xinit");
	xinit();
	/* TODO 9front does this for dma
	if(i8237alloc != nil)
		i8237alloc(); */
	doc("pcicfginit");
	pcicfginit();
	doc("bootscreeninit");
	bootscreeninit();	/* vga maps pages for the frame buffer TODO bug causes an i8042 system reset in poolsizeinit() */
	trapinit();
	printinit();
	cpuidprint();
	doc("mmuinit");
	mmuinit();		/* builds the page tables, lgdt, lidt */
	memmapdump();
	doc("poolsizeinit");
	poolsizeinit();
	memmapdump();
	doc("eve inferno");
	eve = strdup("inferno");
	doc("arch->intrinit");
	if(arch->intrinit){	/* launches other processors on an mp */
		doc("intrinit");
		arch->intrinit();
	}
	doc("timersinit");
	timersinit();
	doc("mathinit");
	mathinit();
	if(arch->clockenable){
		doc("clockinit");
		arch->clockenable();
	}
	doc("procinit");
	procinit();
	doc("links");
	links(); /* runs etherlink() of the link'ed ethernet devices */
	doc("chandevreset");
	chandevreset(); /* reset() all devices */
	doc("userinit");
	userinit(); /* calls init0, which calls chandevinit to init() all devices */
	doc("schedinit");
	active.thunderbirdsarego = 1;
	schedinit();
}

void
mach0init(void)
{
	conf.nmach = 1;

	MACHP(0) = (Mach*)CPU0MACH;

	m->machno = 0;
	m->pml4 = (u64*)PML4ADDR;
	m->gdt = (Segdesc*)GDTADDR;

	machinit();

	active.machs[0] = 1;
	active.exiting = 0;
}

void
machinit(void)
{
	int machno;
	Segdesc *gdt;
	uintptr *pml4;

	machno = m->machno;
	pml4 = m->pml4;
	gdt = m->gdt;
	memset(m, 0, sizeof(Mach));
	m->machno = machno;
	m->pml4 = pml4;
	m->gdt = gdt;
	m->perf.period = 1;
	m->ilockdepth = 0;

	/*
	 * For polled uart output at boot, need
	 * a default delay constant. 100000 should
	 * be enough for a while. Cpuidentify will
	 * calculate the real value later.
	 */
	m->loopconst = 100000;
}

void
init0(void)
{
	Osenv *o;
	char buf[2*KNAMELEN];

	up->nerrlab = 0;

	spllo();
	if(waserror())
		panic("init0: %r");
	/*
	 * These are o.k. because rootinit is null.
	 * Then early kproc's will have a root and dot.
	 */
	o = up->env;
	o->pgrp->slash = namec("#/", Atodir, 0, 0);
	cnameclose(o->pgrp->slash->name);
	o->pgrp->slash->name = newcname("/");
	o->pgrp->dot = cclone(o->pgrp->slash);

	chandevinit();

	if(!waserror()){
		ksetenv("cputype", "am64", 0);
		//snprint(buf, sizeof(buf), "amd64 %s", conffile);
		//ksetenv("terminal", buf, 0);
		setconfenv();
		poperror();
	}

	poperror();

	disinit("/osinit.dis");
}

void
userinit(void)
{
	Proc *p;
	Osenv *o;

	while((p = newproc()) == nil){
/* TODO		freebroken(); */
		resrcwait("no procs for userinit");
	}
	o = p->env;

	o->fgrp = newfgrp(nil);
	o->egrp = newegrp();
	o->pgrp = newpgrp();
	kstrdup(&o->user, eve);

	strcpy(p->text, "interp");

	/*
	 * Kernel Stack
	 *
	 * N.B. make sure there's
	 *	8 bytes for gotolabel's return PC
	 */
	p->sched.pc = (uintptr)init0;
	p->sched.sp = (uintptr)p->kstack+KSTACK-sizeof(uintptr);

	ready(p);
}

void
confinit(void)
{
	char *p;
	int pcnt;
	u64 maxmem;
	int i;

	if(p = getconf("*maxmem"))
		maxmem = strtoull(p, 0, 0);
	else
		maxmem = 0;
	if(p = getconf("*kernelpercent"))
		pcnt = 100 - strtol(p, 0, 0);
	else
		pcnt = 0;

	conf.npage = 0;
	for(i=0; i<nelem(conf.mem); i++)
		conf.npage += conf.mem[i].npage;

	if(pcnt < 10)
		pcnt = 70;
	conf.ialloc = (((conf.npage*(100-pcnt))/100)/2)*BY2PG;
	conf.nproc = 100 + ((conf.npage*BY2PG)/MiB)*5;
	print("conf.npage %zd conf.ialloc %zud conf.nproc %d\n",
			conf.npage, conf.ialloc, conf.nproc);
	USED(maxmem);
}

void
poolsizeinit(void)
{
	print("poolsizeinit conf.npage %zd\n", conf.npage);
	poolsize(mainmem, ((conf.npage*main_pool_pcnt)/100)*BY2PG, 0);
	poolsize(heapmem, ((conf.npage*heap_pool_pcnt)/100)*BY2PG, 0);
	/* TODO causes a double fault now. needs to be fixed
	poolsize(imagmem, ((conf.npage*image_pool_pcnt)/100)*BY2PG, 1); */
	print("after poolsizeinit\n");
}

/*
 *  Save the mach dependent part of the process state.
 */
void
procsave(Proc *p)
{
	if(m->dr7 != 0){
		m->dr7 = 0;
		putdr7(0);
	}
	if(p->state == Moribund)
		p->dr[7] = 0;

	fpuprocsave(p);

	/*
	 * While this processor is in the scheduler, the process could run
	 * on another processor and exit, returning the page tables to
	 * the free list where they could be reallocated and overwritten.
	 * When this processor eventually has to get an entry from the
	 * trashed page tables it will crash.
	 *
	 * If there's only one processor, this can't happen.
	 * You might think it would be a win not to do this in that case,
	 * especially on VMware, but it turns out not to matter.
	 */
	/* TODO obsolete with linear memory? */
	mmuflushtlb();
}
void
procrestore(Proc *p)
{
	if(p->dr[7] != 0){
		m->dr7 = p->dr[7];
		putdr(p->dr);
	}
	
/*	if(p->vmx != nil)
		vmxprocrestore(p);
*/

	fpuprocrestore(p);
}

void
exit(int ispanic)
{
	USED(ispanic);

	up = 0;
	print("exiting\n");

	/* Shutdown running devices */
	chandevshutdown();

	arch->reset();
}

void
reboot(void)
{
	exit(0);
}
