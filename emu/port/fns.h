ulong	FPcontrol(ulong,ulong);
ulong	FPstatus(ulong,ulong);
void		FPsave(void*);
void		FPrestore(void*);
void		Sleep(Rendez*, int (*)(void*), void*);
int		Wakeup(Rendez*);
void		FPinit(void);
void		addprog(Proc*);
Block*	adjustblock(Block*, int);
Block*	allocb(int);
Block*	bl2mem(uchar*, Block*, int);
int	blocklen(Block*);
char*	c2name(Chan*);
int		canlock(Lock*);
int		canqlock(QLock*);
void		cclose(Chan*);
void		chandevinit(void);
void		chanfree(Chan*);
Dir*		chandirstat(Chan*);
void		cinit(void);
char*	clipread(void);
int		clipwrite(char*);
/*void	(*coherence)(void); moved this to port/main.c to avoid the duplicate symbols error */
void		copen(Chan*);
void		cmderror(Cmdbuf*, char*);
Block*	concatblock(Block*);
int		cread(Chan*, uchar*, int, vlong);
void		cwrite(Chan*, uchar*, int, vlong);
Chan*	cunique(Chan*);
void		cupdate(Chan*, uchar*, int, vlong);
char*	cleanname(char*);
Chan*	cclone(Chan*);
void		closeegrp(Egrp*);
void		closefgrp(Fgrp*);
void		closepgrp(Pgrp*);
void		closesigs(Skeyset*);
int		cmount(Chan*, Chan*, int, char*);
Chan*	createdir(Chan*, Mhead*);
void		cunmount(Chan*, Chan*);
int		decref(Ref*);
long		devbwrite(Chan*, Block*, ulong);
void		devcreate(Chan*, char*, int, ulong);
void		devdir(Chan*, Qid, char*, long, char*, long, Dir*);
long		devdirread(Chan*, char*, long, Dirtab*, int, Devgen*);
void		devinit(void);
int		devno(int, int);
Dev*		devbyname(char*);
void		devpermcheck(char*, ulong, int);
void		devremove(Chan*);
int		devstat(Chan*, uchar*, int, Dirtab*, int, Devgen*);
long		devtabread(Chan*, void*, long, vlong);
int		devwstat(Chan*, uchar*, int);
Chan*	devattach(int, char*);
Block*	devbread(Chan*, long, ulong);
Chan*	devclone(Chan*);
Devgen	devgen;
Chan*	devopen(Chan*, int, Dirtab*, int, Devgen*);
Walkqid*	devwalk(Chan*, Chan*, char**, int, Dirtab*, int, Devgen*);
void		disfault(void*, char*);
void		disinit(void*);
int		domount(Chan**, Mhead**);
void	drawqlock(void);
void	drawqunlock(void);
Fgrp*	dupfgrp(Fgrp*);
void		egrpcpy(Egrp*, Egrp*);
int		emptystr(char*);
void		emuinit(void*);
int		eqchan(Chan*, Chan*, int);
int		eqqid(Qid, Qid);
void		error(char*);
void		errorf(char*, ...);
#pragma varargck argpos errorf 1
void		excinit(void);
void		exhausted(char*);
int		export(int, char*, int);
Chan*	fdtochan(Fgrp*, int, int, int, int);
int		findmount(Chan**, Mhead**, int, int, Qid);
void		freeb(Block*);
void		freeblist(Block*);
void		freeskey(Signerkey*);
uintptr	getcallerpc(void*);
ulong	getFPcontrol(void);
ulong	getFPstatus(void);
void		gkbdputc(Queue*, int);
int		incref(Ref*);
int		iprint(char*, ...);
void		isdir(Chan*);
int		isdotdot(char*);
int		iseve(void);
int		kannounce(char*, char*);
int		kdial(char*, char*, char*, int*);
void		kproc(char*, void (*)(void*), void*, int);
void	kprocinit(Proc*);
int		kfgrpclose(Fgrp*, int);
void		ksetenv(char*, char*, int);
void		kstrcpy(char*, char*, int);
void		kstrdup(char**, char*);
long		latin1(uchar*, int);
void		libinit(char*);
void		links(void);
void		lock(Lock*);
Cmdtab*		lookupcmd(Cmdbuf*, Cmdtab*, int);
Block*	mem2bl(uchar*, int);
int		memusehigh(void);
int		memlow(void);
void		mkqid(Qid*, vlong, ulong, int);
Qid	mkuqid(Chan*, Uqid*);
Chan*		mntauth(Chan*, char*);
long		mntversion(Chan*, char*, int, int);
void		mountfree(Mount*);
void		mousetrack(int, int, int, int);
void		muxclose(Mnt*);
Chan*	namec(char*, int, int, ulong);
Chan*	newchan(void);
Cname*	newcname(char*);
Egrp*	newegrp(void);
Fgrp*	newfgrp(Fgrp*);
Mount*	newmount(Mhead*, Chan*, int, char*);
Pgrp*	newpgrp(void);
Proc*	newproc(void);
void		nexterror(void);
void		nofence(void);
void		notkilled(void);
int		openmode(ulong);
void		osblock(void);
void*		oscmd(char**, int, char*, int*);
int		oscmdwait(void*, char*, int);
int		oscmdkill(void*);
void		oscmdfree(void*);
void		oserror(void);
void		oserrstr(char*, uint);
void		oslongjmp(void*, osjmpbuf, int);
long		osmillisec(void);
int		osmillisleep(ulong);
void		osready(Proc*);
int		limbosleep(ulong);
vlong	osusectime(void);
Block*	packblock(Block*);
Block*	padblock(Block*, int);
void		panic(char*, ...);
Cmdbuf*		parsecmd(char*, int);
void		pexit(char*, int);
void		pgrpcpy(Pgrp*, Pgrp*);
int		progfdprint(Chan*, int, int, char*, int);
void		putenvq(char*, char*, int);
void		putenvqv(char*, char**, int, int);
void		putmhead(Mhead*);
Block*	pullupblock(Block*, int);
Block*	pullupqueue(Queue*, int);
void		qaddlist(Queue*, Block*);
Block*	qbread(Queue*, int);
long		qbwrite(Queue*, Block*);
Queue*		qbypass(void (*)(void*, Block*), void*);
int		qcanread(Queue*);
void		qclose(Queue*);
int		qisclosed(Queue*);
int		qconsume(Queue*, void*, int);
Block*	qcopy(Queue*, int, ulong);
int		qdiscard(Queue*, int);
void		qflush(Queue*);
void		qfree(Queue*);
int		qfull(Queue*);
Block*	qget(Queue*);
void		qhangup(Queue*, char*);
int		qiwrite(Queue*, void*, int);
int		qlen(Queue*);
void		qlock(QLock*);
void		qnoblock(Queue*, int);
Queue*	qopen(int, int, void (*)(void*), void*);
int		qpass(Queue*, Block*);
int		qproduce(Queue*, void*, int);
void		qputback(Queue*, Block*);
long		qread(Queue*, void*, int);
Block*	qremove(Queue*);
void		qreopen(Queue*);
void		qsetlimit(Queue*, int);
int		qstate(Queue*);
void		qunlock(QLock*);
int		qwindow(Queue*);
int		qwrite(Queue*, void*, int);
ulong	randomread(void *xp, ulong n);
void	randominit(void);
int		readkbd(void);
int		readnum(ulong, char*, ulong, ulong, int);
int		readnum_vlong(ulong, char*, ulong, vlong, int);
int		readstr(ulong, char*, ulong, char*);
#define	seconds()	(osusectime()/1000000)
void		seterror(char*, ...);
void		setid(char*, int);
void	setpointer(int, int);
char*	skipslash(char*);
void		srvrtinit(void);
void		swiproc(Proc*, int);
Block*	trimblock(Block*, int, int);
long		unionread(Chan*, void*, long);
void		unlock(Lock*);
Uqid*	uqidalloc(Uqidtab*, Chan*);
void		uqidinit(Uqidtab*);
void		freeuqid(Uqidtab*, Uqid*);
void		validname(char*, int);
void		validstat(uchar*, int);
void		validwstatname(char*);
void		vmachine(void*);
int		walk(Chan**, char**, int, int, int*);
void		cleanexit(int);
void		oshostintr(Proc*);
void		osenter(void);
void		osleave(void);
void		oslopri(void);
void		ospause(void);
void		osyield(void);
void		osreboot(char*, char**);
uintptr	poolmaxsize(void);
Pool*	poolmk(char*, int, int, int);
void		hnputv(void*, vlong);
void		hnputl(void*, ulong);
void		hnputs(void*, ushort);
vlong		nhgetv(void*);
ulong		nhgetl(void*);
ushort		nhgets(void*);
void*	smalloc(uintptr);

/* Namespace Emulation */
int		kbind(char*, char*, int);
int		kclose(int);
int		kcreate(char*, int, ulong);
int		kdup(int, int);
int		kfstat(int, uchar*, int);
int		kfwstat(int, uchar*, int);
int		kmount(int, int, char*, int, char*);
int		kunmount(char*, char*);
int		kopen(char*, int);
s32		kread(int, void*, s32);
int		kremove(char*);
vlong	kseek(int, vlong, int);
int		kstat(char*, uchar*, int);
s32		kwrite(int, void*, s32);
int		kwstat(char*, uchar*, int);
Dir*		kdirstat(char*);
Dir*		kdirfstat(int);
int		kdirwstat(char*, Dir*);
int		kdirfwstat(int, Dir*);
long		kdirread(int, Dir**);
int		klisten(char*, char*);

Cname*	addelem(Cname*, char*);
void		cleancname(Cname*);
void		cnameclose(Cname*);

#pragma varargck argpos iprint 1
