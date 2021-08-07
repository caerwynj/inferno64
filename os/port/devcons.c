#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"
#include	<version.h>
#include	"mp.h"
#include	"libsec.h"
#include	"keyboard.h"

extern int cflag;
extern int keepbroken;

void	(*serwrite)(char *, int);

void	(*consdebug)(void) = nil;
void	(*screenputs)(char*, int) = nil;

Queue*	serialoq;		/* serial console output */
Queue*	kprintoq;		/* console output, for /dev/kprint */
ulong	kprintinuse;	/* test and set whether /dev/kprint is open */
int	iprintscreenputs = 1;

int	panicking;

char*	sysname;
char*	eve;

enum
{
	CMreboot,
	CMhalt,
	CMpanic,
	CMbroken,
	CMnobroken,
	CMconsole,
};

static Cmdtab sysctlcmd[] =
{
	CMreboot,	"reboot",	0,
	CMhalt,	"halt", 0,
	CMpanic,	"panic", 0,
	CMconsole,	"console", 1,
	CMbroken,	"broken", 0,
	CMnobroken,	"nobroken", 0,
};

void
printinit(void)
{
}

/*
 *  return true if current user is eve
 */
int
iseve(void)
{
	Osenv *o;

	o = up->env;
	return strcmp(eve, o->user) == 0;
}

static int
consactive(void)
{
	if(serialoq)
		return qlen(serialoq) > 0;
	return 0;
}

static void
prflush(void)
{
	ulong now;

	now = m->ticks;
	while(consactive())
		if(m->ticks - now >= HZ)
			break;
}

static void
kmesgputs(char *str, int n)
{
	uint nn, d;

	ilock(&kmesg.lk);
	/* take the tail of huge writes */
	if(n > sizeof kmesg.buf){
		d = n - sizeof kmesg.buf;
		str += d;
		n -= d;
	}

	/* slide the buffer down to make room */
	nn = kmesg.n;
	if(nn + n >= sizeof kmesg.buf){
		d = nn + n - sizeof kmesg.buf;
		if(d)
			memmove(kmesg.buf, kmesg.buf+d, sizeof kmesg.buf-d);
		nn -= d;
	}

	/* copy the data in */
	memmove(kmesg.buf+nn, str, n);
	nn += n;
	kmesg.n = nn;
	iunlock(&kmesg.lk);
}

/*
 *   Print a string on the console.  Convert \n to \r\n for serial
 *   line consoles.  Locking of the queues is left up to the screen
 *   or uart code.  Multi-line messages to serial consoles may get
 *   interspersed with other messages.
 */
static void
putstrn0(char *str, int n, int usewrite)
{
	int m;
	char *t;
	int (*wq)(Queue*, void*, int);

	/*
	 *  how many different output devices do we need?
	 */
	kmesgputs(str, n);

	/*
	 *  if someone is reading /dev/kprint,
	 *  put the message there.
	 *  if not and there's an attached bit mapped display,
	 *  put the message there.
	 *
	 *  if there's a serial line being used as a console,
	 *  put the message there.
	 */
	wq = usewrite && islo() ? qwrite : qiwrite;
	if(kprintoq != nil && !qisclosed(kprintoq))
		(*wq)(kprintoq, str, n);
	else if(screenputs != nil)
		screenputs(str, n);

	if(serialoq == nil){
		uartputs(str, n);
		return;
	}

	while(n > 0) {
		t = memchr(str, '\n', n);
		if(t != nil) {
			m = t-str;
			(*wq)(serialoq, str, m);
			(*wq)(serialoq, "\r\n", 2);
			n -= m+1;
			str = t+1;
		} else {
			(*wq)(serialoq, str, n);
			break;
		}
	}
}

void
putstrn(char *str, int n)
{
	putstrn0(str, n, 0);
}

int
snprint(char *s, int n, char *fmt, ...)
{
	va_list arg;

	va_start(arg, fmt);
	n = vseprint(s, s+n, fmt, arg) - s;
	va_end(arg);

	return n;
}

int
sprint(char *s, char *fmt, ...)
{
	int n;
	va_list arg;

	va_start(arg, fmt);
	n = vseprint(s, s+PRINTSIZE, fmt, arg) - s;
	va_end(arg);

	return n;
}

int
print(char *fmt, ...)
{
	int n;
	va_list arg;
	char buf[PRINTSIZE];

	va_start(arg, fmt);
	n = vseprint(buf, buf+sizeof(buf), fmt, arg) - buf;
	va_end(arg);
	putstrn(buf, n);

	return n;
}

int
fprint(int fd, char *fmt, ...)
{
	int n;
	va_list arg;
	char buf[PRINTSIZE];

	USED(fd);
	va_start(arg, fmt);
	n = vseprint(buf, buf+sizeof(buf), fmt, arg) - buf;
	va_end(arg);
	putstrn(buf, n);

	return n;
}

/*
 * Want to interlock iprints to avoid interlaced output on 
 * multiprocessor, but don't want to deadlock if one processor
 * dies during print and another has something important to say.
 * Make a good faith effort.
 */
static Lock iprintlock;
static int
iprintcanlock(Lock *l)
{
	int i;
	
	for(i=0; i<1000; i++){
		if(canlock(l))
			return 1;
		if(l->m == MACHP(m->machno))
			return 0;
		microdelay(100);
	}
	return 0;
}

int
iprint(char *fmt, ...)
{
	int n, s, locked;
	va_list arg;
	char buf[PRINTSIZE];

	s = splhi();
	va_start(arg, fmt);
	n = vseprint(buf, buf+sizeof(buf), fmt, arg) - buf;
	va_end(arg);
	locked = iprintcanlock(&iprintlock);
	if(screenputs != nil && iprintscreenputs)
		screenputs(buf, n);
	uartputs(buf, n);
	if(locked)
		unlock(&iprintlock);
	splx(s);

	return n;
}

void
panic(char *fmt, ...)
{
	int s;
	va_list arg;
	char buf[PRINTSIZE];

	kprintoq = nil;	/* don't try to write to /dev/kprint */

	if(panicking)
		for(;;);
	panicking = 1;

	s = splhi();
	strcpy(buf, "panic: ");
	va_start(arg, fmt);
	vseprint(buf+strlen(buf), buf+sizeof(buf), fmt, arg);
	va_end(arg);
	iprint("%s\n", buf);
	if(consdebug)
		(*consdebug)();
	splx(s);
	prflush();
	dumpstack();

	/* reboot cpu servers and headless machines when not debugging */
	if(getconf("*debug") == nil)
	if(!conf.monitor)
		exit(1);

	/* otherwise, just hang */
	while(islo()) idlehands();
	for(;;);
}

void
_assert(char *fmt)
{
	panic("assert failed at %#p: %s", getcallerpc(&fmt), fmt);
}

/*
 * mainly for libmp
 */
void
sysfatal(char *fmt, ...)
{
	char err[256];
	va_list arg;

	va_start(arg, fmt);
	vseprint(err, err + sizeof err, fmt, arg);
	va_end(arg);
	panic("sysfatal: %s", err);
}

int
pprint(char *fmt, ...)
{
	int n;
	Chan *c;
	va_list arg;
	char buf[2*PRINTSIZE];

	if(up == nil || up->env->fgrp == nil)
		return 0;

	c = up->env->fgrp->fd[2];
	if(c==nil || (c->flag&CMSG)!=0 || (c->mode!=OWRITE && c->mode!=ORDWR))
		return 0;
	n = snprint(buf, sizeof buf, "%s %ud: ", up->text, up->pid);
	va_start(arg, fmt);
	n = vseprint(buf+n, buf+sizeof(buf), fmt, arg) - buf;
	va_end(arg);

	if(waserror())
		return 0;
	devtab[c->type]->write(c, buf, n, c->offset);
	poperror();

	lock(c);
	c->offset += n;
	unlock(c);

	return n;
}

enum{
	Qdir,
	Qcons,
	Qsysctl,
	Qconsctl,
	Qdrivers,
	Qhostowner,
	Qkeyboard,
	Qklog,		/* same as 9front's kmesg */
	Qkprint,	/* tail of kprint's and cons. Why not just a tail of klog? Why is this needed? */
	Qscancode,
	Qmemory,
	Qmsec,
	Qnull,
	Qrandom,
	Qnotquiterandom,
	Qsysname,
	Qtime,
	Quser,
	Qjit,
};

static Dirtab consdir[]=
{
	".",	{Qdir, 0, QTDIR},	0,		DMDIR|0555,
	"cons",		{Qcons},	0,		0660,
	"sysctl",	{Qsysctl},	0,		0644,
	"drivers",	{Qdrivers},	0,		0444,
	"hostowner",	{Qhostowner},	0,	0644,
	"keyboard",	{Qkeyboard},	0,		0666,
	"klog",		{Qklog},	0,		0444,
	"kprint",		{Qkprint},	0,		0444,
	"scancode",	{Qscancode},	0,		0444,
	"memory",	{Qmemory},	0,		0444,
	"msec",		{Qmsec},	NUMSIZE,	0444,
	"null",		{Qnull},	0,		0666,
	"random",	{Qrandom},	0,		0444,
	"notquiterandom", {Qnotquiterandom}, 0,	0444,
	"sysname",	{Qsysname},	0,		0664,
	"time",		{Qtime},	0,		0664,
	"user",		{Quser},	0,	0644,
	"jit",		{Qjit},	0,	0666,
};

ulong	boottime;		/* seconds since epoch at boot */

long
seconds(void)
{
	return boottime + TK2SEC(MACHP(0)->ticks);
}

vlong
mseconds(void)
{
	return ((vlong)boottime*1000)+((vlong)(TK2MS(MACHP(0)->ticks)));
}

vlong
osusectime(void)
{
	return (((vlong)boottime*1000)+((vlong)(TK2MS(MACHP(0)->ticks)))*1000);
}

vlong
nsec(void)
{
	return osusectime()*1000;	/* TO DO */
}

int
readnum(ulong off, char *buf, ulong n, ulong val, int size)
{
	char tmp[64];

	if(size > 64) size = 64;

	snprint(tmp, sizeof(tmp), "%*.0lud ", size, val);
	if(off >= size)
		return 0;
	if(off+n > size)
		n = size-off;
	memmove(buf, tmp+off, n);
	return n;
}

int
readstr(ulong off, char *buf, ulong n, char *str)
{
	int size;

	size = strlen(str);
	if(off >= size)
		return 0;
	if(off+n > size)
		n = size-off;
	memmove(buf, str+off, n);
	return n;
}

void
fddump()
{
	Proc *p;
	Osenv *o;
	int i;
	Chan *c;

	p = proctab(6);
	o = p->env;
	for(i = 0; i <= o->fgrp->maxfd; i++) {
		if((c = o->fgrp->fd[i]) == nil)
			continue;
		print("%d: %s\n", i, c->name == nil? "???": c->name->s);
	}
}

static void
qpanic(Rune)
{
	panic("User requested panic.");
}

static void
rexit(Rune)
{
	exit(0);
}

static void
consinit(void)
{
	todinit();
	randominit();
/*
	debugkey('f', "files/6", fddump, 0);
	debugkey('q', "panic", qpanic, 1);
	debugkey('r', "exit", rexit, 1);
*/
}

static Chan*
consattach(char *spec)
{
	return devattach('c', spec);
}

static Walkqid*
conswalk(Chan *c, Chan *nc, char **name, s32 nname)
{
	return devwalk(c, nc, name, nname, consdir, nelem(consdir), devgen);
}

static s32
consstat(Chan *c, uchar *dp, s32 n)
{
	return devstat(c, dp, n, consdir, nelem(consdir), devgen);
}

static Chan*
consopen(Chan *c, u32 omode)
{
	c->aux = nil;
	c = devopen(c, omode, consdir, nelem(consdir), devgen);
	switch((u64)c->qid.path){
	case Qkprint:
		if(tas(&kprintinuse) != 0){
			c->flag &= ~COPEN;
			error(Einuse);
		}
		if(kprintoq == nil){
			kprintoq = qopen(8*1024, Qcoalesce, 0, 0);
			if(kprintoq == nil){
				c->flag &= ~COPEN;
				error(Enomem);
			}
			qnoblock(kprintoq, 1);
		}else
			qreopen(kprintoq);
		c->iounit = qiomaxatomic;
		break;
	}
	return c;
}

static void
consclose(Chan *c)
{
	switch((u64)c->qid.path){
	/* close of kprint allows other opens */
	case Qkprint:
		if(c->flag & COPEN){
			kprintinuse = 0;
			qhangup(kprintoq, nil);
		}
		break;
	}
}

static s32
consread(Chan *c, void *buf, s32 n, s64 offset)
{
	int l;
	Osenv *o;
	int i;
	char *p, tmp[128];

	if(n <= 0)
		return n;
	o = up->env;
	switch((u64)c->qid.path){
	case Qdir:
		return devdirread(c, buf, n, consdir, nelem(consdir), devgen);
	case Qsysctl:
		return readstr(offset, buf, n, VERSION);
	case Qcons:
		error(Egreg);

	case Qtime:
		snprint(tmp, sizeof(tmp), "%.lld", (vlong)mseconds()*1000);
		return readstr(offset, buf, n, tmp);

	case Qhostowner:
		return readstr(offset, buf, n, eve);

	case Quser:
		return readstr(offset, buf, n, o->user);

	case Qjit:
		snprint(tmp, sizeof(tmp), "%d", cflag);
		return readstr(offset, buf, n, tmp);

	case Qnull:
		return 0;

	case Qmsec:
		return readnum(offset, buf, n, TK2MS(MACHP(0)->ticks), NUMSIZE);

	case Qsysname:
		if(sysname == nil)
			return 0;
		return readstr(offset, buf, n, sysname);

	case Qnotquiterandom:
		genrandom(buf, n);
		return n;

	case Qrandom:
		return randomread(buf, n);

	case Qmemory:
		return poolread(buf, n, offset);

	case Qdrivers:
		p = malloc(READSTR);
		if(p == nil)
			error(Enomem);
		l = 0;
		for(i = 0; devtab[i] != nil; i++)
			l += snprint(p+l, READSTR-l, "#%C %s\n", devtab[i]->dc,  devtab[i]->name);
		if(waserror()){
			free(p);
			nexterror();
		}
		n = readstr(offset, buf, n, p);
		free(p);
		poperror();
		return n;

	case Qklog:
		/*
		 * This is unlocked to avoid tying up a process
		 * that's writing to the buffer.  kmesg.n never 
		 * gets smaller, so worst case the reader will
		 * see a slurred buffer.
		 */
		if(offset >= kmesg.n)
			n = 0;
		else{
			if(offset+n > kmesg.n)
				n = kmesg.n - offset;
			memmove(buf, kmesg.buf+offset, n);
		}
		return n;

	case Qkprint:
		return qread(kprintoq, buf, n);

	default:
		print("consread %llud\n", c->qid.path);
		error(Egreg);
	}
	return -1;		/* never reached */
}

static s32
conswrite(Chan *c, void *va, s32 n, s64 offset)
{
	s64 t;
	long l, bp;
	char *a = va;
	Cmdbuf *cb;
	Cmdtab *ct;
	char buf[256];
	int x;

	switch((u64)c->qid.path){
	case Qcons:
		/*
		 * Can't page fault in putstrn, so copy the data locally.
		 */
		l = n;
		while(l > 0){
			bp = l;
			if(bp > sizeof buf)
				bp = sizeof buf;
			memmove(buf, a, bp);
			putstrn0(a, bp, 1);
			a += bp;
			l -= bp;
		}
		break;

	case Qconsctl:
		error(Egreg);
	
	case Qtime:
		if(n >= sizeof(buf))
			n = sizeof(buf)-1;
		strncpy(buf, a, n);
		buf[n] = 0;
		t = strtoll(buf, 0, 0)/1000000;
		boottime = t - TK2SEC(MACHP(0)->ticks);
		break;

	case Qhostowner:
		if(!iseve())
			error(Eperm);
		if(offset != 0 || n >= sizeof(buf))
			error(Ebadarg);
		memmove(buf, a, n);
		buf[n] = '\0';
		if(n > 0 && buf[n-1] == '\n')
			buf[--n] = 0;
		if(n <= 0)
			error(Ebadarg);
		renameuser(eve, buf);
		renameproguser(eve, buf);
		kstrdup(&eve, buf);
		kstrdup(&up->env->user, buf);
		break;

	case Quser:
		if(!iseve())
			error(Eperm);
		if(offset != 0)
			error(Ebadarg);
		if(n <= 0 || n >= sizeof(buf))
			error(Ebadarg);
		strncpy(buf, a, n);
		buf[n] = 0;
		if(buf[n-1] == '\n')
			buf[n-1] = 0;
		kstrdup(&up->env->user, buf);
		break;

	case Qjit:
		if(n >= sizeof(buf))
			n = sizeof(buf)-1;
		strncpy(buf, va, n);
		buf[n] = '\0';
		x = atoi(buf);
		if(x < 0 || x > 9)
			error(Ebadarg);
		cflag = x;
		return n;

	case Qnull:
		break;

	case Qsysname:
		if(offset != 0)
			error(Ebadarg);
		if(n <= 0 || n >= sizeof(buf))
			error(Ebadarg);
		strncpy(buf, a, n);
		buf[n] = 0;
		if(buf[n-1] == '\n')
			buf[n-1] = 0;
		kstrdup(&sysname, buf);
		break;

	case Qsysctl:
		if(!iseve())
			error(Eperm);
		cb = parsecmd(a, n);
		if(waserror()){
			free(cb);
			nexterror();
		}
		ct = lookupcmd(cb, sysctlcmd, nelem(sysctlcmd));
		switch(ct->index){
		case CMreboot:
			reboot();
			break;
		case CMhalt:
			halt();
			break;
		case CMpanic:
			panic("sysctl");
		case CMconsole:
			consoleprint = strcmp(cb->f[1], "off") != 0;
			break;
		case CMbroken:
			keepbroken = 1;
			break;
		case CMnobroken:
			keepbroken = 0;
			break;
		}
		poperror();
		free(cb);
		break;

	default:
		print("conswrite: %llud\n", c->qid.path);
		error(Egreg);
	}
	return n;
}

Dev consdevtab = {
	'c',
	"cons",

	devreset,
	consinit,
	devshutdown,
	consattach,
	conswalk,
	consstat,
	consopen,
	devcreate,
	consclose,
	consread,
	devbread,
	conswrite,
	devbwrite,
	devremove,
	devwstat,
};

static	ulong	randn;

static void
seedrand(void)
{
	randomread((void*)&randn, sizeof(randn));
}

int
nrand(int n)
{
	if(randn == 0)
		seedrand();
	randn = randn*1103515245 + 12345 + MACHP(0)->ticks;
	return (randn>>16) % n;
}

int
rand(void)
{
	nrand(1);
	return randn;
}

ulong
truerand(void)
{
	ulong x;

	randomread(&x, sizeof(x));
	return x;
}
