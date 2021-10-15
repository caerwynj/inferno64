typedef struct BIOS32si	BIOS32si;
typedef struct BIOS32ci	BIOS32ci;
typedef struct Conf	Conf;
typedef struct Confmem	Confmem;
typedef struct FPssestate	FPssestate;
typedef struct FPavxstate	FPavxstate;
typedef struct FPsave	FPsave;
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
	u32	sr;
	uintptr	pc;
	u32	pri;
	void *p;	/* Proc */
	Mach *m;
	u16 isilock;
	u32 lockcycles;
};

struct Label
{
	uintptr	sp;
	uintptr	pc;
};

struct FPssestate
{
	u16int	fcw;			/* x87 control word */
	u16int	fsw;			/* x87 status word */
	u8int	ftw;			/* x87 tag word */
	u8int	zero;			/* 0 */
	u16int	fop;			/* last x87 opcode */
	u64int	rip;			/* last x87 instruction pointer */
	u64int	rdp;			/* last x87 data pointer */
	u32	mxcsr;			/* MMX control and status */
	u32	mxcsrmask;		/* supported MMX feature bits */
	uchar	st[128];		/* shared 64-bit media and x87 regs */
	uchar	xmm[256];		/* 128-bit media regs */
	uchar	ign[96];		/* reserved, ignored */
};

struct FPavxstate
{
	FPssestate;
	uchar	header[64];		/* XSAVE header */
	uchar	ymm[256];		/* upper 128-bit regs (AVX) */
};

struct FPsave
{
	FPavxstate;
};

enum
{
	/* this is a state */
	FPinit=		0,
	FPactive=	1,
	FPinactive=	2,

	/*
	 * the following are bits that can be or'd into the state.
	 *
	 * this is biased so that FPinit, FPactive and FPinactive
	 * without any flags refer to user fp state in fpslot[0].
	 */
	FPillegal=	1<<8,	/* fp forbidden in note handler */
	FPpush=		2<<8,	/* trap on use and initialize new fpslot */
	FPnouser=	4<<8,	/* fpslot[0] is kernel regs */
	FPkernel=	8<<8,	/* fp use in kernel (user in fpslot[0] when !FPnouser) */

	FPindexs=	16,
	FPindex1=	1<<FPindexs,
	FPindexm=	3<<FPindexs,
};

struct PFPU
{
	int	fpstate;
	FPsave	*fpsave;	/* fpslot[fpstate>>FPindexs] */
	FPsave	*fpslot[(FPindexm+1)>>FPindexs];
};

struct Confmem
{
	uintptr	base;
	uintptr	npage;
};

struct Conf
{
	u32	nmach;		/* processors */
	u32	nproc;		/* processes */
	u32	monitor;	/* has monitor? */
	Confmem mem[16];	/* physical memory */
	uintptr	npage;		/* total physical pages of memory */
	uintptr	nswap;		/* number of swap pages */
	u32	copymode;	/* 0 is copy on write, 1 is copy on reference */
	uintptr	ialloc;		/* max interrupt time allocation in bytes */
	uintptr	pipeqsize;	/* size in bytes of pipe queues */
	u32	nuart;		/* number of uart devices */
};

struct Segdesc
{
	u32	d0;
	u32	d1;
};

/*
 *  MMU structure for PDP, PD, PT pages.
 */
struct MMU
{
	MMU	*next;
	uintptr	*page;
	int	index;
	int	level;
};

/*
 *  MMU stuff in proc
 */
#define NCOLOR 1
struct PMMU
{
	MMU*	mmuhead;
	MMU*	mmutail;
	MMU*	kmaphead;
	MMU*	kmaptail;
	ulong	kmapcount;
	ulong	kmapindex;
	ulong	mmucount;
	
	u64int	dr[8];
	void	*vmx;
};

#include "../port/portdat.h"

struct Tss {
	u32	_0_;
	u32	rsp0[2];
	u32	rsp1[2];
	u32	rsp2[2];
	u32	_28_[2];
	u32	ist[14];
	u16	_92_[5];
	u16	iomap;
};

struct Mach
{
	u32	machno;		/* physical id of processor (KNOWN TO ASSEMBLY) */
	uintptr	splpc;		/* pc of last caller to splhi */

	u64*	pml4;		/* pml4 base for this processor (va) */
	Tss*	tss;		/* tss for this processor */
	Segdesc	*gdt;		/* gdt for this processor */

	Proc*	externup;	/* extern register Proc *up */

	u64	ticks;		/* of the clock since boot time */
	Proc*	proc;		/* current process on this processor */
	Label	sched;		/* scheduler wakeup */
	Lock	alarmlock;	/* access to alarm list */
	void*	alarm;		/* alarms bound to this clock */
	u32	inclockintr;

	u32	nrdy;
	u32	ilockdepth;
	Perf	perf;		/* performance counters */

	u32	loopconst;
	int	aalcycles;

	Lock	apictimerlock;
	u32	cpumhz;
	u64	cyclefreq;	/* Frequency of user readable cycle counter */
	u64	cpuhz;
	u32	cpuidax;
	u32	cpuidcx;
	u32	cpuiddx;
	char	cpuidid[16];
	char*	cpuidtype;
	uchar	cpuidfamily;
	uchar	cpuidmodel;
	uchar	cpuidstepping;
	u32	havetsc;
	u32	havepge;
	int	havewatchpt8;
	int	havenx;
	u64	tscticks;
	u64	tscoff;
	u32	intr;
	u32	spuriousintr;
	u32	lastintr;

	u64	dr7;			/* shadow copy of dr7 */
	u64	xcr0;

	s64	mtrrcap;
	s64	mtrrdef;
	s64	mtrrfix[11];
	s64	mtrrvar[32];	/* 256 max. */

	uintptr	stack[1];
};

extern u64 MemMin;

struct
{
	Lock;
	char	machs[MAXMACH];		/* bitmap of active CPUs */
	s32	exiting;	/* shutdown */
	s32	ispanic;	/* shutdown in response to a panic */
	s32	thunderbirdsarego;/* lets the added processors continue to schedinit */
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

/* cpuid instruction result register bits */
enum {
	/* ax */
	Xsaveopt = 1<<0,
	Xsaves = 1<<3,

	/* cx */
	Monitor	= 1<<3,
	Xsave = 1<<26,
	Avx	= 1<<28,

	/* dx */
	Fpuonchip = 1<<0,
	Vmex	= 1<<1,		/* virtual-mode extensions */
	Pse	= 1<<3,		/* page size extensions */
	Tsc	= 1<<4,		/* time-stamp counter */
	Cpumsr	= 1<<5,		/* model-specific registers, rdmsr/wrmsr */
	Pae	= 1<<6,		/* physical-addr extensions */
	Mce	= 1<<7,		/* machine-check exception */
	Cmpxchg8b = 1<<8,
	Cpuapic	= 1<<9,
	Mtrr	= 1<<12,	/* memory-type range regs.  */
	Pge	= 1<<13,	/* page global extension */
	Mca	= 1<<14,	/* machine-check architecture */
	Pat	= 1<<16,	/* page attribute table */
	Pse2	= 1<<17,	/* more page size extensions */
	Clflush = 1<<19,
	Acpif	= 1<<22,	/* therm control msr */
	Mmx	= 1<<23,
	Fxsr	= 1<<24,	/* have SSE FXSAVE/FXRSTOR */
	Sse	= 1<<25,	/* thus sfence instr. */
	Sse2	= 1<<26,	/* thus mfence & lfence instr.s */
	Rdrnd	= 1<<30,	/* RDRAND support bit */
};

enum {						/* MSRs */
	PerfEvtbase	= 0xc0010000,		/* Performance Event Select */
	PerfCtrbase	= 0xc0010004,		/* Performance Counters */

	Efer		= 0xc0000080,		/* Extended Feature Enable */
	Star		= 0xc0000081,		/* Legacy Target IP and [CS]S */
	Lstar		= 0xc0000082,		/* Long Mode Target IP */
	Cstar		= 0xc0000083,		/* Compatibility Target IP */
	Sfmask		= 0xc0000084,		/* SYSCALL Flags Mask */
	FSbase		= 0xc0000100,		/* 64-bit FS Base Address */
	GSbase		= 0xc0000101,		/* 64-bit GS Base Address */
	KernelGSbase	= 0xc0000102,		/* SWAPGS instruction */
};

/*
 *  a parsed plan9.ini line
 */
#define NISAOPT		8

struct ISAConf {
	char	*type;
	u32	port;
	s32	irq;
	u32	dma;
	u32	mem;
	u32	size;
	u32	freq;

	s32	nopt;
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

extern register Mach* m;			/* R15 */
extern register Proc* up;			/* R14 */

extern s32 swcursor;

/*
 *  hardware info about a device
 */
typedef struct {
	u32	port;	
	s32	size;
} Devport;

struct DevConf
{
	u32	intnum;			/* interrupt number */
	char	*type;			/* card type, malloced */
	s32	nports;			/* Number of ports */
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
