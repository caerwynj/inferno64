/*
 * Memory and machine-specific definitions.  Used in C and assembler.
 */
#define KiB		1024u			/* Kibi 0x0000000000000400 */
#define MiB		1048576u		/* Mebi 0x0000000000100000 */
#define GiB		1073741824u		/* Gibi 0x0000000040000000 */
#define TiB		1099511627776ull	/* Tebi 0x0000010000000000 */
#define PiB		1125899906842624ull	/* Pebi 0x0004000000000000 */
#define EiB		1152921504606846976ull	/* Exbi 0x1000000000000000 */

#define MIN(a, b)	((a) < (b)? (a): (b))
#define MAX(a, b)	((a) > (b)? (a): (b))

#define ALIGNED(p, a)	(!(((uintptr)(p)) & ((a)-1)))

/*
 * Sizes
 */
#define	BI2BY		8			/* bits per byte */
#define	BI2WD		32			/* bits per word */
#define	BY2WD		8			/* bytes per word */
#define	BY2V		8			/* bytes per double word */
#define	BY2PG		(0x1000ull)	/* bytes per page */
#define	WD2PG		(BY2PG/BY2WD)	/* words per page */
#define	PGSHIFT		12			/* log(BY2PG) */
#define	ROUND(s, sz)	(((s)+((sz)-1))&~((sz)-1))
#define	PGROUND(s)	ROUND(s, BY2PG)
#define	BLOCKALIGN	8
#define	FPalign		64

#define	MAXMACH		128			/* max # cpus system can run */
#define	KSTACK		(32*KiB)	/* Size of kernel stack */
#define	MACHSIZE	(2*KSTACK)

/*
 * Time
 */
#define	HZ		(100)			/* clock frequency */
#define	MS2HZ		(1000/HZ)		/* millisec per clock tick */
#define	TK2SEC(t)	((t)/HZ)		/* ticks to seconds */
#define	MS2TK(t)	((((uintptr)(t))*HZ)/1000)	/* milliseconds to ticks */

/*
 *  Address spaces. Kernel, sorted by address.
 */
#define KZERO		(0ull)			/* with identity mapping, KZERO = 0 */
/* Leave the 1st MiB to the BIOS (0 to 1MiB-1)
 * From the first MiB to KTZERO is used by the global data tables
 * acid expects plan9 userspace program text at 2MiB. So, having KTZERO at 2MiB
 * 1MiB for l.s data structures  (1 to 2MiB-1)
 * check the e820 memory map to see the available memory
 */
#define KDZERO		(0x100000ull)
#define KTZERO		(0x200000ull)
#define VMAPSIZE  (512ull*GiB)

/*
 * Fundamental addresses
 */
	/* free conventional memory starts from 0x500 as per the
	 * 	BIOS memory map
	 * But, using 0x1200ull to be in sync with 9front source built 9boot*
	 * 	executables
	 */
#define	CONFADDR	(0x1200ull)		/* info passed from boot loader */
	/* Both these should be below 1MiB as they are addressed from real
	 * mode which can address only upto 1MiB.
	 * check the e820 memory map to figure out the availble memory below
	 * 1MiB
	 * The intel manual mentions a 4KiB (0x1000) page for ap bootstrap code
	 * sync these values in os/pc64/mkfile too
	 */
#define	REBOOTADDR	(0x2000ull)	/* reboot code - physical address */
#define	APBOOTSTRAP	(0x3000ull)	/* Application Processor (AP) bootstrap code */

#define	IDTADDR		(KDZERO+0x0ull)	/* idt */
#define GDTADDR		(KDZERO+0x1000ull)	/* gdt */
#define	CPU0MACH	(KDZERO+0x2000ull)	/* Mach for bootstrap processor (BSP) */
#define CPU0END		(KDZERO+0x12000ull)	/* CPU0MACH + (MACHSIZE = 64 KiB = 0x10 000) */
										/* MACHSIZE includes stack size */
#define CPU0SP		CPU0END
#define FFSTART		(KDZERO+0x12000ull) /* FF stacks, system variables, tib, word buffer */
#define FFEND		(KDZERO+0x15000ull) /* 3 pages */
/* 1 PD table has 512 entries
 * each entry maps to a 2MB page
 * 512 entries maps 1GiB and occupies 512*8 = 4096 bytes
 */
#define PML4ADDR	(KDZERO+0x15000ull)
#define PDPADDR		(KDZERO+0x16000ull)	/* KZERO=0 .. 512GiB */
#define PD0ADDR		(KDZERO+0x17000ull)	/* KZERO=0 .. 1GiB */
#define PT0ADDR		(KDZERO+0x18000ull)	/* KZERO=0 .. 2MiB */
#define PT1ADDR		(KDZERO+0x19000ull)	/* 2MiB .. 4MiB */
#define PT2ADDR		(KDZERO+0x1a000ull)	/* 4MiB .. 6MiB */
#define PT3ADDR		(KDZERO+0x1b000ull)	/* 6MiB .. 8MiB */
						/* fill with page tables until KTZERO */

/*
 * Where configuration info is left for us by 9boot.
 * (e.g. why parse the .ini file twice?).
 * Free memory until REBOOTADDR
 */
#define BOOTLINE	((char*)CONFADDR)
#define BOOTLINELEN	64
#define BOOTARGS	((char*)(CONFADDR+BOOTLINELEN))
	/* 9front uses -0x200 to end on a page boundary */
#define BOOTARGSLEN	(4096-0x200-BOOTLINELEN)

/*
 *  known x86 segments (in GDT) and their selectors
 */
#define	NULLSEG	0	/* null segment */
#define	KESEG	1	/* kernel executable */
#define KDSEG	2	/* kernel data */
#define UE32SEG	3	/* user executable 32bit */
#define	UDSEG	4	/* user data/stack */
#define	UESEG	5	/* user executable 64bit */
#define	TSSSEG	8	/* task segment (two descriptors) */

#define	NGDT	10	/* number of GDT entries required */

#define	SELGDT	(0<<2)	/* selector is in gdt */
#define	SELLDT	(1<<2)	/* selector is in ldt */

#define	SELECTOR(i, t, p)	(((i)<<3) | (t) | (p))

#define	NULLSEL	SELECTOR(NULLSEG, SELGDT, 0)
#define KDSEL	SELECTOR(KDSEG, SELGDT, 0)
#define	KESEL	SELECTOR(KESEG, SELGDT, 0)
#define	UE32SEL	SELECTOR(UE32SEG, SELGDT, 3)
#define	UDSEL	SELECTOR(UDSEG, SELGDT, 3)
#define	UESEL	SELECTOR(UESEG, SELGDT, 3)
#define	TSSSEL	SELECTOR(TSSSEG, SELGDT, 0)

/*
 *  fields in segment descriptors
 */
#define	SEGDATA	(0x10<<8)	/* data/stack segment */
#define	SEGEXEC	(0x18<<8)	/* executable segment */
#define	SEGTSS	(0x9<<8)	/* TSS segment */
#define	SEGCG	(0x0C<<8)	/* call gate */
#define	SEGIG	(0x0E<<8)	/* interrupt gate */
#define	SEGTG	(0x0F<<8)	/* trap gate */
#define	SEGLDT	(0x02<<8)	/* local descriptor table */
#define	SEGTYPE	(0x1F<<8)

#define	SEGP	(1<<15)		/* segment present */
#define	SEGPL(x) ((x)<<13)	/* priority level */
#define	SEGB	(1<<22)		/* granularity 1==4k (for expand-down) */
#define	SEGD	(1<<22)		/* default 1==32bit (for code) */
#define	SEGE	(1<<10)		/* expand down */
#define	SEGW	(1<<9)		/* writable (for data/stack) */
#define	SEGR	(1<<9)		/* readable (for code) */
#define SEGL	(1<<21)		/* 64 bit */
#define	SEGG	(1<<23)		/* granularity 1==4k (for other) */

/*
 *  virtual MMU
 */
#define	PTEMAPMEM	(1ull*MiB)	
#define	PTEPERTAB	(PTEMAPMEM/BY2PG)
#define	SEGMAPSIZE	65536
#define	SSEGMAPSIZE	16
#define	PPN(x)		((x)&~(1ull<<63 | BY2PG-1))

/*
 *  physical MMU
 */
#define	PTEVALID	(1ull<<0)
#define	PTEWT		(1ull<<3)
#define	PTEUNCACHED	(1ull<<4)
#define	PTECACHED	(0ull<<4)
#define	PTEWRITE	(1ull<<1)
#define	PTERONLY	(0ull<<1)
#define	PTEKERNEL	(0ull<<2)
#define	PTEUSER		(1ull<<2)
#define	PTESIZE		(1ull<<7)
#define	PTEGLOBAL	(1ull<<8)
#define	PTENOEXEC	((uvlong)m->havenx<<63)

/*
 * Hierarchical Page Tables.
 * For example, traditional IA-32 paging structures have 2 levels,
 * level 1 is the PD, and level 0 the PT pages; with IA-32e paging,
 * level 3 is the PML4(!), level 2 the PDP, level 1 the PD,
 * and level 0 the PT pages. The PTLX macro gives an index into the
 * page-table page at level 'l' for the virtual address 'v'.
 */
#define PTSZ		(4*KiB)			/* page table page size */
#define PTSHIFT		9			/*  */

#define PTLX(v, l)	(((v)>>(((l)*PTSHIFT)+PGSHIFT)) & ((1<<PTSHIFT)-1))
#define PGLSZ(l)	(1ull<<(((l)*PTSHIFT)+PGSHIFT))

/*
 * Macros for calculating offsets within the page directory base
 * and page tables. 
 */
#define	PDX(va)		((((uintptr)(va))>>22) & 0x03FF)
#define	PTX(va)		((((uintptr)(va))>>12) & 0x03FF)

#define	getpgcolor(a)	0

/* PAT entry used for write combining */
#define PATWC	7

#define RMACH		R15			/* m-> */
#define RUSER		R14			/* up-> */

#define USTKTOP		(up->kstack+KSTACK)

/* forth memory map */
/*
 * user table at the start unlike in Starting Forth as it will be
 * easy to get to the variables with a known offset from C
 */
#define HEAPSTART	(0ull)

/* keeping the dictionary at the start to ease debugging of
	dictionary addresses in forth.h
 */
#define DICTIONARY	(HEAPSTART)				/* dictionary ends at (HEAPSTART+(16*BY2PG)) */
#define PSTACK		(HEAPSTART+(17*BY2PG))	/* upto (HEAPSTART+(16*BY2PG)), going down */
#define TIB			(HEAPSTART+(17*BY2PG))	/* text input buffer */
#define RSTACK		(HEAPSTART+(19*BY2PG))	/* upto (HEAPSTART+(18*BY2PG)), going down */

										/* 256 allows these to be counted strings */
#define WORDB		(RSTACK+(BY2WD*0))	/* word buffer = 32*8 = 256 */
#define ERRSTR		(RSTACK+(BY2WD*32))	/* errstr size = 32*8 = 256 bytes */
#define FTHPID		(RSTACK+(BY2WD*64))
#define FTHPARENTPID	(RSTACK+(BY2WD*65))
#define ARGSFILENAME	(RSTACK+(BY2WD*66))	/* counted string, 18 bytes is enough, 64 bytes #p/<pid>args */

/* storage for saving Forth registers when calling C */
#define FORTHTOP	(RSTACK+(BY2WD*74))
#define FORTHPSP	(RSTACK+(BY2WD*75))
#define FORTHRSP	(RSTACK+(BY2WD*76))
#define FORTHIP		(RSTACK+(BY2WD*77))
#define FORTHW		(RSTACK+(BY2WD*78))
#define FORTHUP		(RSTACK+(BY2WD*79))
#define FORTHUPE	(RSTACK+(BY2WD*80))
#define HERE		(RSTACK+(BY2WD*81))
#define DTOP		(RSTACK+(BY2WD*82))
#define THERE		(RSTACK+(BY2WD*83))	/* store FORTHVARS here at boot */

#define FORTHVARS	(RSTACK+(BY2WD*84))

#define FORTHEND	(HEAPSTART+(24*BY2PG))
#define HEAPEND		(FORTHEND)
#define FORTHHEAPSIZE	FORTHEND
