enum {
	MaxEther	= 64,
	Ntypes		= 8,
};

typedef struct Ether Ether;
struct Ether {
	ISAConf;			/* hardware info */

	s32	ctlrno;
	s32	tbdf;			/* type+busno+devno+funcno */
	s32	minmtu;
	s32 	maxmtu;
	uchar	ea[Eaddrlen];

	void	(*attach)(Ether*);	/* filled in by reset routine */
	void	(*detach)(Ether*);
	void	(*transmit)(Ether*);
	/* TODO removed in 9front void	(*interrupt)(Ureg*, void*); */
	s32	(*ifstat)(Ether*, void*, s32, u32);
	s32 	(*ctl)(Ether*, void*, s32); /* custom ctl messages */
	void	(*power)(Ether*, s32);	/* power on/off */
	void	(*shutdown)(Ether*);	/* shutdown hardware before reboot */
	void	*ctlr;

	Queue*	oq;

	Netif;
};

extern Block* etheriq(Ether*, Block*, s32);
extern void addethercard(char*, int(*)(Ether*));
extern u32 ethercrc(uchar*, s32);
extern s32 parseether(uchar*, char*);

#define NEXT(x, l)	(((x)+1)%(l))
#define PREV(x, l)	(((x) == 0) ? (l)-1: (x)-1)
#define	HOWMANY(x, y)	(((x)+((y)-1))/(y))
#define ROUNDUP(x, y)	(HOWMANY((x), (y))*(y))
