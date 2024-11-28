#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

#include	<libsec.h>

/* machine specific hardware random number generator */
void (*hwrandbuf)(void*, u32) = nil;

static struct
{
	QLock;
	Chachastate;
} *rs;

typedef struct Seedbuf Seedbuf;
struct Seedbuf
{
	ulong		randomcount;
	uchar		buf[64];
	uchar		nbuf;
	uchar		next;
	ushort		bits;

	SHA2_512state	ds;
};

static void
randomsample(Ureg*, Timer *t)
{
	Seedbuf *s = t->ta;

	if(s->randomcount == 0 || s->nbuf >= sizeof(s->buf))
		return;
	s->bits = (s->bits<<2) ^ s->randomcount;
	s->randomcount = 0;
	if(++s->next < 8/2)
		return;
	s->next = 0;
	s->buf[s->nbuf++] ^= s->bits;
}

/*
12:57 < joe7> In os/port/random.c:^randomseed() function, the up variable is used.
	From the timeradd() definition, it should be a Timer * variable.
12:57 < joe7> But, I cannot find the definition of that variable in random.c
12:58 < cinap_lenrek> joe7: the Proc structure has a timer built in
12:58 < cinap_lenrek> joe7: anonymous struct
12:58 < cinap_lenrek> the compiler figures out the offset within the struct
12:59 < joe7> oh, it figures out the offset too? I was thinking that if the
	fields should be at the beginning.
12:59 < cinap_lenrek> nope
12:59 < cinap_lenrek> can be anywhere
12:59 < cinap_lenrek> welcome to plan9 c
12:59 < joe7> I could not figure out how it could do the translation from Proc * to Timer *
13:00 < joe7> thanks.
*/
static void
randomseed(void*)
{
	Seedbuf *s;

	/* TODO
	 * use the secret memory, used to back cryptographic
	 * keys and cipher states.
	 * Not sure if it is relevant to inferno
	s = secalloc(sizeof(Seedbuf));
	*/
	s = smalloc(sizeof(Seedbuf));

	if(hwrandbuf != nil)
		(*hwrandbuf)(s->buf, sizeof(s->buf));

	/* Frequency close but not equal to HZ */
	up->tns = (vlong)(MS2HZ+3)*1000000LL;
	up->tmode = Tperiodic;
	up->tt = nil;
	up->ta = s;
	up->tf = randomsample;
	timeradd(up);
	while(s->nbuf < sizeof(s->buf)){
		if(++s->randomcount <= 100000)
			continue;
		if(anyhigher())
			sched();
	}
	timerdel(up);

	sha2_512(s->buf, sizeof(s->buf), s->buf, &s->ds);
	setupChachastate(rs, s->buf, 32, s->buf+32, 12, 20);
	qunlock(rs);

	/* secfree(s); */
	free(s);

	pexit("", 1);
}

void
randominit(void)
{
	/* rs = secalloc(sizeof(*rs)); */
	rs = smalloc(sizeof(*rs));
	qlock(rs);	/* randomseed() unlocks once seeded */
	kproc("randomseed", randomseed, nil, 0);
}

ulong
randomread(void *p, ulong n)
{
	Chachastate c;

	if(n == 0)
		return 0;

	if(hwrandbuf != nil)
		(*hwrandbuf)(p, n);

	/* copy chacha state, rekey and increment iv */
	qlock(rs);
	c = *rs;
	chacha_encrypt((uchar*)&rs->input[4], 32, &c);
	if(++rs->input[13] == 0)
		if(++rs->input[14] == 0)
			++rs->input[15];
	qunlock(rs);

	/* encrypt the buffer, can fault */
	chacha_encrypt((uchar*)p, n, &c);

	/* prevent state leakage */
	memset(&c, 0, sizeof(c));

	return n;
}

/* used by fastrand() */
void
genrandom(uchar *p, int n)
{
	randomread(p, n);
}

/* used by rand(),nrand() */
long
lrand(void)
{
	/* xoroshiro128+ algorithm */
	static int seeded = 0;
	static uvlong s[2];
	static Lock lk;
	ulong r;

	if(seeded == 0){
		randomread(s, sizeof(s));
		seeded = (s[0] | s[1]) != 0;
	}

	lock(&lk);
	r = (s[0] + s[1]) >> 33;
	s[1] ^= s[0];
 	s[0] = (s[0] << 55 | s[0] >> 9) ^ s[1] ^ (s[1] << 14);
 	s[1] = (s[1] << 36 | s[1] >> 28);
	unlock(&lk);

 	return r;
}
