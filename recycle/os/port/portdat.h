typedef struct Alarms	Alarms;
typedef struct Block	Block;
typedef struct Bkpt Bkpt;
typedef struct BkptCond BkptCond;
typedef struct Chan	Chan;
typedef struct Cmdbuf	Cmdbuf;
typedef struct Cmdtab	Cmdtab;
typedef struct Cname	Cname;
typedef struct Crypt	Crypt;
typedef struct Dev	Dev;
typedef struct DevConf	DevConf;
typedef struct Dirtab	Dirtab;
typedef struct Edf	Edf;
typedef struct Egrp	Egrp;
typedef struct Evalue	Evalue;
typedef struct Fgrp	Fgrp;
typedef struct List	List;
typedef struct Log	Log;
typedef struct Logflag	Logflag;
typedef struct Mntcache Mntcache;
typedef struct Mntparam Mntparam;
typedef struct Mount	Mount;
typedef struct Mntrah	Mntrah;
typedef struct Mntrpc	Mntrpc;
typedef struct Mntproc	Mntproc;
typedef struct Mntwalk	Mntwalk;
typedef struct Mnt	Mnt;
typedef struct Mhead	Mhead;
typedef struct Note	Note;
typedef struct Path	Path;
typedef struct Perf	Perf;
typedef struct Pgrp	Pgrp;
typedef struct Proc	Proc;
typedef struct PMach	PMach;
typedef struct QLock	QLock;
typedef struct Queue	Queue;
typedef struct Ref	Ref;
typedef struct Rendez	Rendez;
typedef struct Rept	Rept;
typedef struct Rootdata	Rootdata;
typedef struct Rgrp	Rgrp;
typedef struct RWlock	RWlock;
typedef struct Schedq	Schedq;
typedef struct Signerkey Signerkey;
typedef struct Skeyset	Skeyset;
typedef struct Talarm	Talarm;
typedef struct Timer	Timer;
typedef struct Timers	Timers;
typedef struct PhysUart PhysUart;
typedef struct Uart Uart;
typedef struct Waitq	Waitq;
typedef struct Walkqid	Walkqid;
typedef struct Watchpt	Watchpt;
typedef struct Watchdog	Watchdog;
typedef int    Devgen(Chan*, char*, Dirtab*, int, int, Dir*);

#pragma incomplete DevConf
#pragma incomplete Edf
#pragma incomplete Mntcache
#pragma incomplete Mntrpc
#pragma incomplete Queue
#pragma incomplete Timers

#include "fcall.h"
#include <pool.h>

/*
 * sticking with inferno's definition of Ref
 * as it keeps the incref() and decref() simple
 * and also puts the proc on the fast path by the
 * scheduler's priorities (PriLock)
 */
struct Ref
{
	Lock	l;
	s32	ref;
};

struct Rendez
{
	Lock;
	Proc	*p;
};

struct Rept
{
	Lock	l;
	Rendez	r;
	void	*o;
	s32	t;
	s32	(*active)(void*);
	s32	(*ck)(void*, int);
	void	(*f)(void*);	/* called with VM acquire()'d */
};

enum
{
	Nopin =	-1
};

struct QLock
{
	Lock	use;	/* to access Qlock structure */
	Proc	*head;	/* next process waiting for object */
	Proc	*tail;	/* last process waiting for object */
	s32	locked;		/* flag */
};

struct RWlock
{
	Lock	use;
	Proc	*head;		/* list of waiting processes */
	Proc	*tail;
	uintptr	wpc;		/* pc of writer */
	Proc	*wproc;		/* writing proc */
	int	readers;	/* number of readers */
	int	writer;		/* number of writers */
};

struct Talarm
{
	Lock;
	Proc*	list;
};

struct Alarms
{
	QLock;
	Proc*	head;
};

struct Rootdata
{
	s32	dotdot;
	void	*ptr;
	s32	size;
	s32	*sizep;
};

/*
 * Access types in namec & channel flags
 */
enum
{
	Aaccess,			/* as in stat, wstat */
	Abind,			/* for left-hand-side of bind */
	Atodir,				/* as in chdir */
	Aopen,				/* for i/o */
	Amount,				/* to be mounted or mounted upon */
	Acreate,			/* is to be created */
	Aremove,			/* will be removed by caller */

	COPEN	= 0x0001,		/* for i/o */
	CMSG	= 0x0002,		/* the message channel for a mount */
	CCEXEC	= 0x0008,		/* close on exec */
	CFREE	= 0x0010,		/* not in use */
	CRCLOSE	= 0x0020,		/* remove on close */
	CCACHE	= 0x0080,		/* client cache */
};

enum
{
	BINTR		=	(1<<0),
	BFREE		=	(1<<1),
	Bipck	=	(1<<2),		/* ip checksum */
	Budpck	=	(1<<3),		/* udp checksum */
	Btcpck	=	(1<<4),		/* tcp checksum */
	Bpktck	=	(1<<5),		/* packet checksum */
};

struct Block
{
	Block*	next;
	Block*	list;
	uchar*	rp;			/* first unconsumed byte */
	uchar*	wp;			/* first empty byte */
	uchar*	lim;			/* 1 past the end of the buffer */
	uchar*	base;			/* start of the buffer */
	void	(*free)(Block*);
	u16	flag;
	u16	checksum;		/* IP checksum of complete packet (minus media header) */
};
#define BLEN(s)	((s)->wp - (s)->rp)
#define BALLOC(s) ((s)->lim - (s)->base)

struct Chan
{
	Ref;
	Lock;
	Chan	*next;		/* allocation */
	Chan	*link;
	s64	offset;			/* in fd */
	s64	devoffset;		/* in underlying device; see read */
	u16	type;
	u32	dev;
	u16	mode;			/* read/write */
	u16	flag;
	Qid	qid;
	s32	fid;			/* for devmnt */
	u32	iounit;			/* chunk size for i/o; 0==default */
	Mhead	*umh;		/* mount point that derived Chan; used in unionread */
	Chan	*umc;		/* channel in union; held for union read */
	QLock	umqlock;	/* serialize unionreads */
	s32	uri;			/* union read index */
	s32	dri;			/* devdirread index */
	uchar	*dirrock;	/* directory entry rock for translations */
	int	nrock;
	int	mrock;
	QLock	rockqlock;
	int	ismtpt;
	Mntcache	*mcp;	/* Mount cache pointer */
	Mnt	*mux;			/* Mnt for clients using me for messages */
	union {
		void	*aux;
		u32	mid;		/* for ns in devproc */
	};
	Chan	*mchan;		/* channel to mounted server */
	Qid	mqid;			/* qid of root of mount point */
	Path	*path;
};

struct Path
{
	Ref;
	char	*s;
	Chan	**mtpt;		/* mtpt history */
	int	len;			/* strlen(s) */
	int	alen;			/* allocated length of s */
	int	mlen;			/* number of path elements */
	int	malen;			/* allocated length of mtpt */
};

struct Dev
{
	s32	dc;
	char	*name;

	void	(*reset)(void);
	void	(*init)(void);
	void	(*shutdown)(void);
	Chan*	(*attach)(char*);
	Walkqid*	(*walk)(Chan*, Chan*, char**, s32);
	s32	(*stat)(Chan*, uchar*, s32);
	Chan*	(*open)(Chan*, u32);
	void	(*create)(Chan*, char*, u32, u32);
	void	(*close)(Chan*);
	s32	(*read)(Chan*, void*, s32, s64);
	Block*	(*bread)(Chan*, s32, u32);
	s32	(*write)(Chan*, void*, s32, s64);
	s32	(*bwrite)(Chan*, Block*, u32);
	void	(*remove)(Chan*);
	s32	(*wstat)(Chan*, uchar*, s32);
	void	(*power)(s32);	/* power mgt: power(1) → on, power (0) → off */
	s32	(*config)(s32, char*, DevConf*);
};

struct Dirtab
{
	char	name[KNAMELEN];
	Qid	qid;
	s64	length;
	s32	perm;
};

struct Walkqid
{
	Chan	*clone;
	s32	nqid;
	Qid	qid[1];
};

enum
{
	NSMAX	=	1000,
	NSLOG	=	7,
	NSCACHE	=	(1<<NSLOG),
};

struct Mntwalk				/* state for /proc/#/ns */
{
	s32		cddone;
	u32	id;
	Mhead	*mh;
	Mount	*cm;
};

/*
 * *order is used to build a temporary mountid sorted linked
 * list by pgrpcpy() to preserve the mountid allocation order
 * of the source pgrp.
 * Alternative would be to build an array of copied mounts and
 * qsort() it at the end before allocating mountid's.
 */
struct Mount
{
	u32	mountid;
	Mount	*next;
	Mount	*order;
	Chan	*to;			/* channel replacing channel */
	s32	mflag;
	char	*spec;
};

struct Mhead
{
	Ref;
	RWlock	lock;
	Chan	*from;			/* channel mounted upon */
	Mount	*mount;			/* what's mounted upon it */
	Mhead	*hash;			/* Hash chain */
};

struct Mntrah
{
	Rendez;

	ulong	vers;

	vlong	off;
	vlong	seq;

	uint	i;
	Mntrpc	*r[8];
};

struct Mntproc
{
	Rendez;

	Mnt	*m;
	Mntrpc	*r;
	void	*a;
	void	(*f)(Mntrpc*, void*);
};

struct Mnt
{
	Lock;
	/* references are counted using c->ref; channels on this mount point incref(c->mchan) == Mnt.c */
	Chan	*c;		/* Channel to file service */
	Proc	*rip;		/* Reader in progress */
	Mntrpc	*queue;		/* Queue of pending requests on this channel */
	Mntproc	defered[8];	/* Worker processes for defered RPCs (read ahead) */
	u32	id;		/* Multiplexer id for channel check */
	Mnt	*list;		/* Free list */
	s32	flags;		/* cache */
	s32	msize;		/* data + IOHDRSZ */
	char	*version;			/* 9P version */
	Queue	*q;		/* input queue */
};

enum
{
	NUser,				/* note provided externally */
	NExit,				/* deliver note quietly */
	NDebug,				/* print debug message */
};

struct Note
{
	char	msg[ERRMAX];
	int	flag;			/* whether system posted it */
};

enum
{
	RENDLOG	=	5,
	RENDHASH =	1<<RENDLOG,		/* Hash to lookup rendezvous tags */
	MNTLOG	=	5,
	MNTHASH =	1<<MNTLOG,		/* Hash to walk mount table */
	DELTAFD=		20,		/* allocation quantum for process file descriptors */
	MAXNFD =		4000,		/* max per process file descriptors */
	MAXKEY =		8,	/* keys for signed modules */
	NFD =		100,		/* per process file descriptors */
	ENVLOG =	5,
	ENVHASH =	1<<ENVLOG,	/* Egrp hash for variable lookup */
};
#define REND(p,s)	((p)->rendhash[(s)&((1<<RENDLOG)-1)])
#define MOUNTH(p,qid)	((p)->mnthash[(qid).path&((1<<MNTLOG)-1)])

struct Mntparam {
	Chan*	chan;
	Chan*	authchan;
	char*	spec;
	s32	flags;
};

/*
 * All processes in a process group share the namespace.
 * Hence, this can be called the namespace group too
 */
struct Pgrp
{
	Ref;				/* also used as a lock when mounting */
	RWlock	ns;			/* Namespace n read/one write lock */
	int	noattach;
	Mhead*	mnthash[MNTHASH];
	u32	pgrpid;
	QLock	debug;			/* single access via devproc.c */
	QLock	nsh;
	s32	progmode;
	Chan*	dot;
	Chan*	slash;
	s32	nodevs;
	s32	pin;
};

/*
 * Array of Chan* (Every file is a Chan* in the server).
 * fd (file descriptor) is the file's index in that array.
 * fdtochan(fd) => Chan*
 */
struct Fgrp
{
	Ref;
	Lock;
	Proc	*rendhash[RENDHASH];	/* Rendezvous tag hash */
	Chan	**fd;
	uchar	*flag;			/* per file-descriptor flags (CCEXEC) */
	s32	nfd;			/* number allocated */
	s32	maxfd;			/* highest fd in use */
	s32	minfd;			/* lower bound on free fd */
	s32	exceed;			/* debugging */
};

struct Rgrp
{
	Ref;
	Lock;
	Proc	*rendhash[RENDHASH];	/* Rendezvous tag hash */
};

struct Evalue
{
	char	*value;
	int	len;
	ulong	vers;
	uvlong	path;			/* qid.path: Egrp.path << 32 | index (of Egrp.ent[]) */
	Evalue	*hash;
	char	name[];
};

struct Egrp
{
	Ref;
	RWlock;
	Evalue	**ent;
	int	nent;			/* numer of slots in ent[] */
	int	low;			/* lowest free index in ent[] */
	int	alloc;			/* bytes allocated for env */
	ulong	path;			/* generator for qid path */
	ulong	vers;			/* of Egrp */
	Evalue	*hash[ENVHASH];		/* hashtable for name lookup */
};

struct Signerkey
{
	Ref;
	char*	owner;
	u16	footprint;
	u32	expires;
	void*	alg;
	void*	pk;
	void	(*pkfree)(void*);
};

struct Skeyset
{
	Ref;
	QLock;
	u32	flags;
	char*	devs;
	s32	nkey;
	Signerkey	*keys[MAXKEY];
};

struct Waitq
{
	Waitmsg	w;
	Waitq	*next;
};

/*
 * fasttick timer interrupts
 */
enum {
	/* Mode */
	Trelative,	/* timer programmed in ns from now */
	Tabsolute,	/* timer programmed in ns since epoch - not used in 9front */
	Tperiodic,	/* periodic timer, period in ns */
};

struct Timer
{
	/* Public interface */
	int	tmode;		/* See above */
	vlong	tns;		/* meaning defined by mode */
	void	(*tf)(Ureg*, Timer*);
	void	*ta;
	/* Internal */
	Lock;
	Mach	*tactive;	/* The cpu that tf is active on */
	Timers	*tt;		/* Timers queue this timer runs on */
	Tval	tticks;		/* tns converted to ticks */
	Tval	twhen;		/* ns represented in fastticks */
	Timer	*tnext;
};

enum
{
	Dead = 0,		/* Process states */
	Moribund,
	Ready,
	Scheding,
	Running,
	Queueing,
	QueueingR,
	QueueingW,
	Wakeme,
	Broken,
	Stopped,
	Rendezvous,
	Waitrelease,

	Proc_stopme = 1, 	/* devproc requests */
	Proc_exitme,
	Proc_traceme,
	Proc_exitbig,
	Proc_tracesyscall,

	TUser = 0, 		/* Proc.time */
	TSys,
	TReal,
	TCUser,
	TCSys,
	TCReal,

	NERR		= 64,
	NNOTE = 5,

	Unknown		= 0,
	IdleGC,
	Interp,
	Forth,
	BusyGC,

	Npriq		= 20,		/* number of scheduler priority levels */
	Nrq		= Npriq+2,	/* number of priority levels including real time */
	PriRelease	= Npriq,	/* released edf processes */
	PriEdf		= Npriq+1,	/* active edf processes */
	PriNormal	= 10,		/* base priority for normal processes */
	PriExtra	= Npriq-1,	/* edf processes at high best-effort pri */
	PriKproc	= 13,		/* base priority for kernel processes */
	PriRoot		= 13,		/* base priority for root processes */

	/* used by inferno, remove them at some point when /prog is removed */
	PriLock		= Npriq,	/* Holding Spin lock */
	PriRealtime = Npriq+1,	/* Video telephony */
	PriHicodec	= Npriq,	/* MPEG codec */
	PriLocodec	= Npriq,	/* Audio codec */
	PriHi		= Npriq,	/* Important task */
	PriLo		= 7,
	PriBackground = 4,
};

struct Schedq
{
	Lock;
	Proc*	head;
	Proc*	tail;
	int	n;
};

/* Needs a default environment to create new processes (spawn, not fork)
 *
 * When using forth for the userspace, forth's stack is in fmem.
 * The kstack is used for everything else. Hence, there is no
 * stack switching to kstack on a syscall. Forth uses
 * DX and R8 for stack manipulations to avoid
 * messing around with SP.
 */
struct Proc
{
	Label	sched;		/* known to l.s */
	char	*kstack;	/* known to l.s in 9front to switch to the kernel stack on syscallentry */
	Mach	*mach;		/* machine running this proc */
	char	*text;
	char	*user;

	char	*args;
	int	nargs;		/* number of bytes of args */
	int	setargs;	/* process changed its args */

	Proc	*rnext;		/* next process in run queue */
	Proc	*qnext;		/* next process on queue for a QLock */

	char	*psstate;	/* What /proc/#/status reports */
	s32		state;

	u32	pid;
	u32	noteid;		/* Equivalent of note group */
	u32	parentpid;

	Proc	*parent;	/* Process to send wait record on exit */
	Lock	exl;		/* Lock count and waitq */
	Waitq	*waitq;		/* Exited processes wait children */
	int	nchild;		/* Number of living children */
	int	nwait;		/* Number of uncollected wait records */
	QLock	qwaitr;
	Rendez	waitr;		/* Place to hang out in wait */

/*	QLock	seglock;	\/* locked whenever seg[] changes *\/
	Segment	*seg[NSEG];*/

	Pgrp	*pgrp;		/* Process group for namespace */
	Egrp 	*egrp;		/* Environment group */
	Fgrp	*fgrp;		/* File descriptor group */
	Rgrp	*rgrp;		/* Rendez group */

	Fgrp	*closingfgrp;	/* used during teardown */

	int	insyscall;
	u32	time[6];	/* User, Sys, Real; child U, S, R */

	u64	kentry;		/* Kernel entry time stamp (for profiling) */
	/*
	 * pcycles: cycles spent in this process (updated on procswitch)
	 * when this is the current proc and we're in the kernel
	 * (procrestores outnumber procsaves by one)
	 * the number of cycles spent in the proc is pcycles + cycles()
	 * when this is not the current process or we're in user mode
	 * (procrestores and procsaves balance), it is pcycles.
	 */
	s64	pcycles;

	QLock	debug;		/* to access debugging elements of User */
	Proc	*pdbg;		/* the debugging process */
	/*
	 * Pgrp.progmode is used by inferno and procmode by 9front
	 * Leaving them different, for now
	 */
	u32	procmode;	/* proc device default file mode */
	int	privatemem;	/* proc does not let anyone read mem */
	int	noswap;		/* process is not swappable */
	int	hang;		/* hang at next exec for debug */
	int	procctl;	/* Control for /proc debugging */
	uintptr	pc;		/* DEBUG only */

	Lock	rlock;		/* sync sleep/wakeup with postnote */
	Rendez	*r;		/* rendezvous point slept on */
	Rendez	sleep;		/* place for syssleep/debug */
	int	notepending;	/* note issued but not acted on */
	int	kp;		/* true if a kernel process */
	Proc	*palarm;	/* Next alarm time */
	ulong	alarm;		/* Time of call */
/*	int	newtlb;	*/	/* Pager has changed my pte's, I must flush */

	uintptr	rendtag;	/* Tag for rendezvous */
	uintptr	rendval;	/* Value for rendezvous */
	Proc	*rendhash;	/* Hash list for tag values */

	Timer;			/* For tsleep and real-time, has twhen of inferno */
	Rendez	*trend;
	int	(*tfn)(void*);
	void	(*kpfun)(void*);
	void	*kparg;

/*	Sargs	s;		*//* TODO uncomment this and scallnr syscall arguments */
/*	int	scallnr;	*//* sys call number */
	int	nerrlab;
	Label	errlab[NERR];
	char	*syserrstr;	/* last error from a system call, errbuf0 or 1 */
	char	*errstr;	/* reason we're unwinding the error stack, errbuf1 or 0 */
	char	errbuf0[ERRMAX];
	char	errbuf1[ERRMAX];
	char	genbuf[128];	/* buffer used e.g. for last name element from namec */
	Chan	*slash;
	Chan	*dot;

	Note	note[NNOTE];
	short	nnote;
	short	notified;	/* sysnoted is due */
	Note	lastnote;
	int	(*notify)(void*, char*);

	Lock	*lockwait;
	Lock	*lastlock;	/* debugging */
	Lock	*lastilock;	/* debugging */

	Mach	*wired;
	Mach	*mp;		/* machine this process last ran on */
	int	nlocks;		/* number of locks held by proc */
	u32	delaysched;
	u32	priority;	/* priority level */
	u32	basepri;	/* base priority level */
	uchar	fixedpri;	/* priority level deson't change */
	u32	cpu;		/* cpu average */
	u32	lastupdate;
	uchar	yield;		/* non-zero if the process just did a sleep(0) */
	u32	readytime;	/* time process came ready */
	int	preempted;	/* true if this process hasn't finished the interrupt
				 *  that last preempted it
				 */
	Edf	*edf;		/* if non-null, real-time proc, edf contains scheduling params */
	int	trace;		/* process being traced? */

	uintptr	qpc;		/* pc calling last blocking qlock */
	QLock	*eql;		/* interruptable eqlock */

	void	*ureg;		/* User registers for notes */
	void	*dbgreg;	/* User registers for devproc */

	PFPU;			/* machine specific fpu state */
	PMMU;			/* machine specific mmu state, obsolete on 9ferno amd64? */

	char	*syscalltrace;	/* syscall trace */
	
	Watchpt	*watchpt;	/* watchpoints */
	int	nwatchpt;

	/* forth specific fields */
	Proc	*fprev, *fnext;	/* forth processes linked list */
	void	*fmem;			/* forth process memory - sandboxed except for macro primitives */
	void	*shm;		/* for devshm */
	void	*canread;	/* for devready.c */
	u8		fisgo;	/* 0 while waiting for the pctl message */

	/* not used by 9front. get rid of it at some point */
	intptr errpc;
};

enum
{
	/* kproc flags */
	KPDUPPG		= (1<<0),
	KPDUPFDG	= (1<<1),
	KPDUPENVG	= (1<<2),
	KPDUP = KPDUPPG | KPDUPFDG | KPDUPENVG
};

enum {
	BrkSched,
	BrkNoSched,
};

struct BkptCond
{
	uchar op;
	u32 val;
	BkptCond *next;
};

struct Bkpt
{
	s32 id;
	u32 addr;
	BkptCond *conditions;
	Instr instr;
	void (*handler)(Bkpt*);
	void *aux;
	Bkpt *next;
	Bkpt *link;
};

enum
{
	PRINTSIZE	= 1024 /*256*/,
	NUMSIZE	=	12,		/* size of formatted number */
	MB =		(1024*1024),
	READSTR =	1000,		/* temporary buffer size for device reads */
};

extern	Conf	conf;
extern	char*	conffile;
extern	int	consoleprint;
extern	Dev*	devtab[];
extern	char*	eve;
extern	char	hostdomain[];
extern	int	hwcurs;
extern	Queue*	kprintoq;
extern  Queue	*kbdq;
extern  Queue	*kscanq;
extern  Ref	noteidalloc;
extern	uint	qiomaxatomic;
extern	Queue*	serialoq;
extern	char*	statename[];
extern	char*	sysname;
extern	Talarm	talarm;

/*
 *  action log
 */
struct Log {
	Lock;
	s32	opens;
	char*	buf;
	char	*end;
	char	*rptr;
	s32	len;
	s32	nlog;
	s32	minread;

	s32	logmask;	/* mask of things to debug */

	QLock	readq;
	Rendez	readr;
};

struct Logflag {
	char*	name;
	s32	mask;
};

struct Cmdbuf
{
	char	*buf;
	char	**f;
	s32	nf;
};

struct Cmdtab
{
	s32	index;	/* used by client to switch on result */
	char	*cmd;	/* command name */
	s32	narg;	/* expected #args; 0 ==> variadic */
};

/*
 *  routines to access UART hardware
 */
struct PhysUart
{
	char*	name;
	Uart*	(*pnp)(void);
	void	(*enable)(Uart*, int);
	void	(*disable)(Uart*);
	void	(*kick)(Uart*);
	void	(*dobreak)(Uart*, int);
	int	(*baud)(Uart*, int);
	int	(*bits)(Uart*, int);
	int	(*stop)(Uart*, int);
	int	(*parity)(Uart*, int);
	void	(*modemctl)(Uart*, int);
	void	(*rts)(Uart*, int);
	void	(*dtr)(Uart*, int);
	long	(*status)(Uart*, void*, long, long);
	void	(*fifo)(Uart*, int);
	void	(*power)(Uart*, int);
	int	(*getc)(Uart*);	/* polling versions, for iprint, rdb */
	void	(*putc)(Uart*, int);
};

enum {
	Stagesize=	2048
};

/*
 *  software UART
 */
struct Uart
{
	void*	regs;			/* hardware stuff */
	void*	saveregs;		/* place to put registers on power down */
	char*	name;			/* internal name */
	ulong	freq;			/* clock frequency */
	int	bits;			/* bits per character */
	int	stop;			/* stop bits */
	int	parity;			/* even, odd or no parity */
	int	baud;			/* baud rate */
	PhysUart*phys;
	int	console;		/* used as a serial console */
	int	special;		/* internal kernel device */
	Uart*	next;			/* list of allocated uarts */

	QLock;
	int	type;			/* ?? */
	int	dev;
	int	opens;

	int	enabled;
	Uart	*elist;			/* next enabled interface */

	int	perr;			/* parity errors */
	int	ferr;			/* framing errors */
	int	oerr;			/* rcvr overruns */
	int	berr;			/* no input buffers */
	int	serr;			/* input queue overflow */

	/* buffers */
	int	(*putc)(Queue*, int);
	Queue	*iq;
	Queue	*oq;

	Lock	rlock;
	uchar	istage[Stagesize];
	uchar	*iw;
	uchar	*ir;
	uchar	*ie;

	Lock	tlock;			/* transmit */
	uchar	ostage[Stagesize];
	uchar	*op;
	uchar	*oe;
	int	drain;

	int	modem;			/* hardware flow control on */
	int	xonoff;			/* software flow control on */
	int	blocked;
	int	cts, dsr, dcd, dcdts;	/* keep track of modem status */ 
	int	ctsbackoff;
	int	hup_dsr, hup_dcd;	/* send hangup upstream? */
	int	dohup;

	Rendez	r;
};

extern	Uart*	consuart;
extern	int	rdbstarted;

enum
{
	MAXPOOL		= 8,
};

extern Pool*	mainmem;
extern Pool*	heapmem;
extern Pool*	imagmem;

/*
 *  performance timers, all units in perfticks
 */
struct Perf
{
	u32	intrts;		/* time of last interrupt */
	u32	inintr;		/* time since last clock tick in interrupt handlers */
	u32	avg_inintr;	/* avg time per clock tick in interrupt handlers */
	u32	inidle;		/* time since last clock tick in idle loop */
	u32	avg_inidle;	/* avg time per clock tick in idle loop */
	u32	last;		/* value of perfticks() at last clock tick */
	u32	period;		/* perfticks() per clock tick */
};

struct Watchdog
{
	void	(*enable)(void);	/* watchdog enable */
	void	(*disable)(void);	/* watchdog disable */
	void	(*restart)(void);	/* watchdog restart */
	void	(*stat)(char*, char*);	/* watchdog statistics */
};

struct Watchpt
{
	enum {
		WATCHRD = 1,
		WATCHWR = 2,
		WATCHEX = 4,
	} type;
	uintptr addr, len;
};

struct PMach
{
	Proc*	readied;		/* for runproc */ /* unused in inferno */
	Label	sched;			/* scheduler wakeup */
	ulong	ticks;			/* of the clock since boot time */
	ulong	schedticks;		/* next forced context switch */

	int	pfault;
	int	cs;
	int	syscall;
	int	load;
	int	intr;
	int	ilockdepth;

	int	flushmmu;		/* make current proc flush it's mmu state */

	int	tlbfault;
	int	tlbpurge;

	Perf	perf;			/* performance counters */

	uvlong	cyclefreq;		/* Frequency of user readable cycle counter */
};

/* queue state bits,  Qmsg, Qcoalesce, and Qkick can be set in qopen */
enum
{
	/* Queue.state */
	Qstarve		= (1<<0),	/* consumer starved */
	Qmsg		= (1<<1),	/* message stream */
	Qclosed		= (1<<2),	/* queue has been closed/hungup */
	Qflow		= (1<<3),	/* producer flow controlled */
	Qcoalesce	= (1<<4),	/* coallesce packets on read */
	Qkick		= (1<<5),	/* always call the kick routine after qwrite */
};

#define DEVDOTDOT -1

#pragma	varargck	argpos	print	1
#pragma	varargck	argpos	snprint	3
#pragma	varargck	argpos	seprint	3
#pragma	varargck	argpos	sprint	2
#pragma	varargck	argpos	fprint	2
#pragma	varargck	argpos	iprint	1
#pragma	varargck	argpos	panic	1
#pragma	varargck	argpos	kwerrstr	1
#pragma	varargck	argpos	kprint	1

#pragma	varargck	type	"lld"	vlong
#pragma	varargck	type	"llx"	vlong
#pragma	varargck	type	"lld"	uvlong
#pragma	varargck	type	"llx"	uvlong
#pragma	varargck	type	"lx"	void*
#pragma	varargck	type	"ld"	long
#pragma	varargck	type	"lx"	long
#pragma	varargck	type	"ld"	ulong
#pragma	varargck	type	"lx"	ulong
#pragma varargck	type	"zd"	intptr
#pragma varargck	type	"zo"	intptr
#pragma varargck	type	"zx"	intptr
#pragma varargck	type	"zd"	uintptr
#pragma varargck	type	"zo"	uintptr
#pragma varargck	type	"zx"	uintptr
#pragma	varargck	type	"d"	int
#pragma	varargck	type	"x"	int
#pragma	varargck	type	"c"	int
#pragma	varargck	type	"C"	int
#pragma	varargck	type	"d"	uint
#pragma	varargck	type	"x"	uint
#pragma	varargck	type	"c"	uint
#pragma	varargck	type	"C"	uint
#pragma	varargck	type	"f"	double
#pragma	varargck	type	"e"	double
#pragma	varargck	type	"g"	double
#pragma	varargck	type	"s"	char*
#pragma	varargck	type	"S"	Rune*
#pragma	varargck	type	"r"	void
#pragma	varargck	type	"%"	void
#pragma	varargck	type	"I"	uchar*
#pragma	varargck	type	"V"	uchar*
#pragma	varargck	type	"E"	uchar*
#pragma	varargck	type	"M"	uchar*
#pragma	varargck	type	"p"	uintptr
#pragma	varargck	type	"p"	void*
#pragma	varargck	type	"q"	char*

/*
 * Log console output so it can be retrieved via /dev/kmesg.
 * This is good for catching boot-time messages after the fact.
 */
struct {
	Lock lk;
	uint n;
	char buf[16384];
} kmesg;

/*
 * shared memory data structures. Modeled after Egrp. used by devshm.
 */
typedef struct Svalue Svalue;
struct Svalue
{
	Ref;
	RWlock;
	char	*name;
	char	*value;
	s32	len;
	s32 vers;
	u8 dead;	/* set by remove() */
};

typedef struct Sgrp Sgrp;
struct Sgrp
{
	Ref;
	RWlock;
	union{		/* array of Svalue pointers */
		Svalue	**entries;
		Svalue	**ent;
	};
	int	nent;	/* number of entries used */
	int	ment;	/* maximum number of entries */
	u32	vers;	/* of Sgrp */
};
