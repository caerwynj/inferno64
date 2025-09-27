typedef struct BIOS32si	BIOS32si;
typedef struct BIOS32ci	BIOS32ci;
typedef struct Conf	Conf;
typedef union FPsave	FPsave;
typedef struct FPx87state FPx87state;
typedef struct FPssestate FPssestate;
typedef struct PFPU	PFPU;
typedef ulong Instr;
typedef struct ISAConf	ISAConf;
typedef struct Label	Label;
typedef struct Lock	Lock;
typedef struct MMU	MMU;
typedef struct Mach	Mach;
typedef struct Notsave	Notsave;
typedef struct PCArch	PCArch;
typedef struct Pcidev	Pcidev;
typedef struct PCMmap	PCMmap;
typedef struct PCMslot	PCMslot;
typedef struct Page	Page;
typedef struct PMMU	PMMU;
typedef struct Segdesc	Segdesc;
typedef struct Tss	Tss;
typedef s64		Tval;
typedef struct Ureg	Ureg;
typedef struct Vctl	Vctl;

#pragma incomplete BIOS32si
#pragma incomplete Pcidev
#pragma incomplete Ureg
#pragma incomplete Vctl


struct Lock
{
	u32	key;
	u32	sr;	/* value returned by splhi() */
	uintptr	pc;	/* lock() caller */
	u32	priority;
	void *p;	/* Proc */
	Mach *m;
	u16 isilock;
	u32 lockcycles;
};

struct Label
{
	ulong	sp;
	ulong	pc;
};

struct	FPx87state		/* x87 fp state */
{
	ushort	control;
	ushort	r1;
	ushort	status;
	ushort	r2;
	ushort	tag;
	ushort	r3;
	ulong	pc;
	ushort	selector;
	ushort	opcode;
	ulong	operand;
	ushort	oselector;
	ushort	r4;
	uchar	regs[80];	/* floating point registers */
};

struct	FPssestate		/* SSE fp state */
{
	ushort	fcw;		/* control */
	ushort	fsw;		/* status */
	ushort	ftw;		/* tag */
	ushort	fop;		/* opcode */
	ulong	fpuip;		/* pc */
	ushort	cs;		/* pc segment */
	ushort	rsrvd1;		/* reserved */
	ulong	fpudp;		/* data pointer */
	ushort	ds;		/* data pointer segment */
	ushort	rsrvd2;
	ulong	mxcsr;		/* MXCSR register state */
	ulong	mxcsr_mask;	/* MXCSR mask register */
	uchar	xregs[480];	/* extended registers */
};

union FPsave {
	FPx87state;
	FPssestate;
};

struct PFPU
{
	int	fpstate;
	FPsave	*fpsave;
};

enum
{
	/* this is a state */
	FPinit=		0,
	FPactive=	1,
	FPinactive=	2,

	/* the following is a bit that can be or'd into the state */
	FPillegal=	0x100,
};

struct Conf
{
	ulong	nmach;		/* processors */
	ulong	nproc;		/* processes */
	ulong	monitor;	/* has monitor? */
	ulong	npage0;		/* total physical pages of memory */
	ulong	npage1;		/* total physical pages of memory */
	ulong	npage;		/* total physical pages of memory */
	ulong	base0;		/* base of bank 0 */
	ulong	base1;		/* base of bank 1 */
	ulong	copymode;	/* 0 is copy on write, 1 is copy on reference */
	ulong	ialloc;		/* max interrupt time allocation in bytes */
	ulong	pipeqsize;	/* size in bytes of pipe queues */
	int	nuart;		/* number of uart devices */
};

struct Segdesc
{
	ulong	d0;
	ulong	d1;
};

/*
 *  MMU stuff in proc
 */
#define NCOLOR 1
#define	NPROCSEG	3	/* number of per process descriptors */
struct PMMU
{
	Page*	mmupdb;			/* page directory base */
	Page*	mmufree;		/* unused page table pages */
	Page*	mmuused;		/* used page table pages */
	Page*	kmaptable;		/* page table used by kmap */
	uint	lastkmap;		/* last entry used by kmap */
	int	nkmap;			/* number of current kmaps */

	Segdesc	gdt[NPROCSEG];	/* per process descriptors */
	Segdesc	*ldt;	/* local descriptor table */
	int	nldt;	/* number of ldt descriptors allocated */
	
	u32int	dr[8];			/* debug registers */
	void	*vmx;
};

#include "../port/portdat.h"

typedef struct Tss {
	ulong	link;			/* link (old TSS selector) */
	ulong	esp0;			/* privilege level 0 stack pointer */
	ulong	ss0;			/* privilege level 0 stack selector */
	ulong	esp1;			/* privilege level 1 stack pointer */
	ulong	ss1;			/* privilege level 1 stack selector */
	ulong	esp2;			/* privilege level 2 stack pointer */
	ulong	ss2;			/* privilege level 2 stack selector */
	ulong	cr3;			/* page directory base register */
	ulong	eip;			/* instruction pointer */
	ulong	eflags;			/* flags register */
	ulong	eax;			/* general registers */
	ulong 	ecx;
	ulong	edx;
	ulong	ebx;
	ulong	esp;
	ulong	ebp;
	ulong	esi;
	ulong	edi;
	ulong	es;			/* segment selectors */
	ulong	cs;
	ulong	ss;
	ulong	ds;
	ulong	fs;
	ulong	gs;
	ulong	ldt;			/* selector for task's LDT */
	ulong	iomap;			/* I/O map base address + T-bit */
};

struct Mach
{
	int	machno;			/* physical id of processor (KNOWN TO ASSEMBLY) */
	ulong	splpc;		/* pc of last caller to splhi */

	ulong*	pdb;		/* page directory base for this processor (va) */
	Tss*	tss;		/* tss for this processor */
	Segdesc	*gdt;		/* gdt for this processor */

	Proc*	externup;		/* extern register Proc *up */

	ulong	ticks;		/* of the clock since boot time */
	Proc*	proc;		/* current process on this processor */
	Label	sched;		/* scheduler wakeup */
	Lock	alarmlock;	/* access to alarm list */
	void*	alarm;		/* alarms bound to this clock */
	int	inclockintr;

	int	nrdy;
	int	ilockdepth;

	int	loopconst;

	Lock	apictimerlock;
	int	cpumhz;
	uvlong	cyclefreq;		/* Frequency of user readable cycle counter */
	uvlong	cpuhz;
	int	cpuidax;
	int	cpuiddx;
	char	cpuidid[16];
	char*	cpuidtype;
	int	havetsc;
	int	havepge;
	uvlong	tscticks;
	uvlong	tscoff;
	int	intr;
	ulong	spuriousintr;
	int	lastintr;

	vlong	mtrrcap;
	vlong	mtrrdef;
	vlong	mtrrfix[11];
	vlong	mtrrvar[32];		/* 256 max. */

	int	stack[1];
};

struct
{
	Lock;
	int	machs;			/* bitmap of active CPUs */
	int	exiting;		/* shutdown */
	int	ispanic;		/* shutdown in response to a panic */
	int	thunderbirdsarego;	/* lets the added processors continue to schedinit */
}active;


/*
 *  routines for things outside the PC model, like power management
 */
struct PCArch
{
	char*	id;
	s32	(*ident)(void);		/* this should be in the model */
	void	(*reset)(void);		/* this should be in the model */
	s32	(*serialpower)(s32);	/* 1 == on, 0 == off */
	s32	(*modempower)(s32);	/* 1 == on, 0 == off */

	void	(*intrinit)(void);
	s32	(*intrassign)(Vctl*);
	s32	(*intrirqno)(s32, s32);
	s32	(*intrvecno)(s32);
	s32	(*intrspurious)(s32);
	void	(*introff)(void);
	void	(*intron)(void);

	void	(*clockinit)(void);
	void	(*clockenable)(void);
	u64	(*fastclock)(u64*);
	void	(*timerset)(u64);
};

/*
 *  a parsed plan9.ini line
 */
#define NISAOPT		8

struct ISAConf {
	char	*type;
	ulong	port;
	int	irq;
	ulong	dma;
	ulong	mem;
	ulong	size;
	ulong	freq;

	int	nopt;
	char	*opt[NISAOPT];
};

extern PCArch	*arch;			/* PC architecture */

/*
 * Each processor sees its own Mach structure at address MACHADDR.
 * However, the Mach structures must also be available via the per-processor
 * MMU information array machp, mainly for disambiguation and access to
 * the clock which is only maintained by the bootstrap processor (0).
 */
Mach* machp[MAXMACH];

#define	MACHP(n)	(machp[n])

extern Mach	*m;
//extern Proc	*up;
#define up	(((Mach*)MACHADDR)->externup)

extern int swcursor;

/*
 *  hardware info about a device
 */
typedef struct {
	ulong	port;	
	int	size;
} Devport;

struct DevConf
{
	ulong	intnum;			/* interrupt number */
	char	*type;			/* card type, malloced */
	int	nports;			/* Number of ports */
	Devport	*ports;			/* The ports themselves */
};

typedef struct BIOS32ci {		/* BIOS32 Calling Interface */
	u32	eax;
	u32	ebx;
	u32	ecx;
	u32	edx;
	u32	esi;
	u32	edi;
} BIOS32ci;
