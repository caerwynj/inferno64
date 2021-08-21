#include		"u.h"
#include		"../port/lib.h"
#include		"mem.h"
#include		"dat.h"
#include		"fns.h"
#include		"../port/error.h"

#include		"ip.h"

typedef struct NatProto NatProto;
typedef struct NatAddr NatAddr;
typedef struct Nat Nat;

/*
 * NAT.
 */
struct Nat
{
	uchar	src[IPv4addrlen];	/* Source address */
	uchar	sport[2];		/* Source port */
	uchar	lport[2];		/* Local port */
	uchar	proto;			/* Protocol */
	long	time;			/* Time */
	Conv	*conv;			/* Conversation */
	Nat		*next;			/* Next node */
};

/*
 * Protocol list.
 */
struct NatProto
{
	uchar	proto;			/* Protocol */
	int	sport;			/* Source port offset */
	int	dport;			/* Destination port offset */
	int	cksum;			/* Checksum offset */
	int	timeout;		/* Timeout */
};

/*
 * Address list.
 */
struct NatAddr
{
	uchar	src[IPaddrlen];		/* Source address */
	uchar	mask[IPaddrlen];	/* Source address mask */
	uchar	net[IPaddrlen];		/* Source network address */
	Iplifc	*dst;			/* Destination interface */
	NatAddr	*next;			/* Next node */
};

static Nat *head = nil;
static NatAddr *addrhead = nil;

/*
 * Timeouts for ICMP, TCP and UDP are respectively confirmed
 * in RFC 5508, RFC 5382 and RFC 4787.
 */
static NatProto prototab[] =
{
	{ 1, 4, 4, 2, 60*1000 },		/* ICMP */
	{ 6, 0, 2, 16, (2*60*60+4*60)*1000 },	/* TCP */
	{ 17, 0, 2, 6, 2*60*1000 },		/* UDP */
	{ 40, 6, 8, 0, 10*30*1000 },		/* IL */
	{ 255, 0, 2, 6, 2*60*1000 },		/* RUDP */
	{ 0 }
};

NatProto*	parseproto(uchar);
void		natprepend(Nat*);
Nat*		natexistout(uchar*, uchar, uchar*);
Nat*		natexistin(uchar, uchar*);
int		natdelete(uchar*, uchar, uchar*);
int		natpurge(uchar);
Nat*		natlport(Proto*, Ip4hdr*, uchar*);
int		natgc(uchar);
void		checksumadjust(uchar*, uchar*, int, uchar*, int);
Iplifc*		natonifco(Ipifc*, Ip4hdr*);
Iplifc*		natonifci(Ipifc*);
void		nataddrprepend(NatAddr*);
NatAddr*	nataddrexist(uchar*, uchar*, Iplifc*);
int		addnataddr(uchar*, uchar*, Iplifc*);
int		removenataddr(uchar*, uchar*, Iplifc*);
void		shownataddr(void);
void		flushnataddr(void);

/*
 * Return protocol attributes if known.
 */
NatProto*
parseproto(uchar proto)
{
	NatProto *np;

	for(np = prototab; np->proto; np++)
		if(proto == np->proto)
			return np;

	return nil;
}

/*
 * Output NAT.
 * Return -1 if the packet must be NATed but the protocol is unknown.
 */
int
nato(Block *b, Ipifc *ifc, Fs *f)
{
	Nat *n;		/* NAT table */
	NatProto *np;	/* Protocol list */
	Iplifc *lifc;	/* Logical interface */
	Ip4hdr *h;	/* Source IPv4 header */
	Proto *p;	/* New protocol */
	uchar *laddr;	/* Local address on Iplifc */
	uchar *sport;	/* Source port */
	uchar *cksum;	/* Source checksum */

	h = (Ip4hdr*)(b->rp);

	/* Verify on which logical interface NAT is enabled,
           and if this source address must be translated */
	if((lifc=natonifco(ifc, h)) == nil)
		return 0;

	laddr = lifc->local+IPv4off;
	p = Fsrcvpcolx(f, h->proto);

	if(ip4cmp(h->src, laddr) != 0){
		if((np=parseproto(h->proto)) != nil){
			/* Protocol layer */
			sport = (b->rp)+sizeof(Ip4hdr)+np->sport;
			cksum = (b->rp)+sizeof(Ip4hdr)+np->cksum;
			if((n = natlport(p, h, sport)) == nil)
				return -1;
			memmove(sport, n->lport, 2);
			checksumadjust(cksum, n->sport, 2, n->lport, 2);
			if(np->proto != 1)
				/* ICMP checksum doesn't include IP header */
				checksumadjust(cksum, n->src, IPv4addrlen,
					laddr, IPv4addrlen);
			/* IP layer */
			ip4move(h->src, laddr);
			checksumadjust(h->cksum, n->src, IPv4addrlen,
				h->src, IPv4addrlen);
			return 0;
		}else{
			netlog(f, Lognat, "nat: unknown protocol %d\n", h->proto);
			return -1;
		}
	}

	return 0;
}

/*
 * Input NAT.
 */
void
nati(Block *b, Ipifc *ifc)
{
	Nat *n;		/* NAT table */
	NatProto *np;	/* Protocol list */
	Ip4hdr *h;	/* Source IPv4 header */
	uchar *lport;	/* Our local port, and dst port for the packet */
	uchar *cksum;	/* Source checksum */

	h = (Ip4hdr*)(b->rp);

	/* Verify if NAT is enabled on this interface */
	if(natonifci(ifc) == nil)
		return;

	if((np=parseproto(h->proto)) != nil){
		lport = (b->rp)+sizeof(Ip4hdr)+np->dport;
		if((n=natexistin(h->proto, lport)) != nil){
			/* Protocol layer */
			cksum = (b->rp)+sizeof(Ip4hdr)+np->cksum;
			checksumadjust(cksum, lport, 2, n->sport, 2);
			memmove(lport, n->sport, 2);
			if(np->proto != 1)
				/* ICMP checksum doesn't include IP header */
		   		checksumadjust(cksum, h->dst, IPv4addrlen,
					n->src, IPv4addrlen);
			/* IP layer */
			checksumadjust(h->cksum, h->dst, IPv4addrlen,
				n->src, IPv4addrlen);
			ip4move(h->dst, n->src);
		}
	}
}

/*
 * Add Nat to Nat list.
 */
void
natprepend(Nat *n)
{
	n->next = head;
	head = n;
}

/*
 * Return Nat if it exists in Nat list.
 */
Nat*
natexistout(uchar *src, uchar proto, uchar *sport)
{
	Nat *c;		/* Current node */

	for(c=head; c!=nil; c=c->next)
		if(ip4cmp(src, c->src) == 0 &&
			memcmp(sport, c->sport, 2) == 0 &&
			proto == c->proto){
			c->time = NOW;
			return c;
		}

	return nil;
}

/*
 * Return Nat if it exists in Nat list.
 */
Nat*
natexistin(uchar proto, uchar *lport)
{
	Nat *c;		/* Current node */

	for(c=head; c!=nil; c=c->next)
		if(memcmp(lport, c->lport, 2) == 0 &&
			proto == c->proto){
			c->time = NOW;
			return c;
		}

	return nil;
}

/*
 * Delete Nat in Nat list.
 * Return -1 if it doesn't exist.
 */
int
natdelete(uchar src[IPv4addrlen], uchar proto, uchar sport[2])
{
	Nat *p;		/* Precedent node */
	Nat *c;		/* Current node */

	for(p=nil, c=head; c!=nil; p=c, c=c->next)
		if(ip4cmp(src, c->src) == 0 &&
			memcmp(sport, c->sport, 2) == 0 &&
			proto == c->proto)
			break;

	if(c == nil)
		return -1;

	if(p == nil)
		head = head->next;
	else
		p->next = c->next;

	closeconv(c->conv);
	free(c);

	return 0;
}

/*
 * Purge Nat list.
 */
int
natpurge(uchar proto)
{
	Nat *c;		/* Current node */
	int n;		/* Number of purged connections */

	for(n = 0;; n++){
		do{
			if((c = head) == nil)
				return n;
			head = head->next;
		}while(c->proto != proto);
		closeconv(c->conv);
		free(c);
	}
}

/*
 * Create a new Nat if necessary.
 */
Nat*
natlport(Proto *p, Ip4hdr *h, uchar *sport)
{
	Nat *n;		/* New NAT node */
	Conv *s;	/* New conversation */

	if((n=natexistout(h->src, h->proto, sport)) == nil){
		qlock(p);
		s = Fsprotoclone(p, "network");
		qunlock(p);
		if(s == nil){
			error(Enodev);
			return nil;
		}
		setlport(s);
		n = malloc(sizeof(Nat));
		ip4move(n->src, h->src);
		memmove(n->sport, sport, 2);
		memmove(n->lport, &s->lport, 2);
		n->proto = h->proto;
		n->time = NOW;
		n->conv = s;
		natprepend(n);
	}

	return n;
}

/*
 * Nat list garbage collector.
 */
int
natgc(uchar proto){
	Nat *p;		/* Precedent node */
	Nat *c;		/* Current node */
	NatProto *np;	/* Protocol list */
	int n;		/* Number of garbage collected connections */

	n = 0;
	p = nil;
	c = head;

	np = parseproto(proto);

	while(c != nil){
		if(NOW - c->time > np->timeout){
 			if(p == nil){
 				head = head->next;
				if(proto == c->proto)
					n++;
				closeconv(c->conv);
				free(c);
				p = nil;
				c = head;
 			}else{
 				p->next = c->next;
				if(proto == c->proto)
					n++;
				closeconv(c->conv);
				free(c);
 				c = p->next;
 			}
		}else{
			p = c;
			c = c->next;
		}
	}

	if(n == 0)	/* Prevent Conv saturation */
		n = natpurge(proto);

	return n;
}

/*
 * Function checksumadjust from RFC 3022.
 */
void
checksumadjust(uchar *chksum, uchar *optr, int olen, uchar *nptr, int nlen)
{
	long x, old, new;

	x=chksum[0]*256+chksum[1];
	x=~x & 0xffff;
	while(olen){
		old=optr[0]*256+optr[1];
		optr+=2;
		x-=old & 0xffff;
		if(x<=0){
			x--;
			x&=0xffff;
		}
		olen-=2;
	}
	while(nlen){
		new=nptr[0]*256+nptr[1];
		nptr+=2;
		x+=new & 0xffff;
		if(x & 0x10000){
			x++;
			x&=0xffff;
		}
		nlen-=2;
	}
	x=~x & 0xffff;
	chksum[0]=x/256;
	chksum[1]=x & 0xff;
}

/*
 * Add NatAddr to NatAddr list.
 */
void
nataddrprepend(NatAddr *na)
{
	na->next = addrhead;
	addrhead = na;
}

/*
 * Return NatAddr if it exists in NatAddr list.
 */
NatAddr*
nataddrexist(uchar *src, uchar *mask, Iplifc *dst)
{
	NatAddr *c;	/* Current node */

	for(c=addrhead; c!=nil; c=c->next)
		if(ipcmp(src, c->src) == 0 &&
			ipcmp(mask, c->mask) == 0 &&
			dst == c->dst)
			return c;

	return nil;
}

/*
 * Create a new NatAddr.
 * Return -1 if it already exist.
 */
int
addnataddr(uchar *src, uchar *mask, Iplifc *dst)
{
	NatAddr *na;		/* New address node */
	uchar net[IPaddrlen];	/* Network address */

	maskip(src, mask, net);

	if(nataddrexist(src, mask, dst) != nil)
		return -1;

	na = malloc(sizeof(NatAddr));
	ipmove(na->src, src);
	ipmove(na->mask, mask);
	ipmove(na->net, net);
	na->dst = dst;

	nataddrprepend(na);

	return 0;
}

/*
 * Remove a NatAddr.
 * Return -1 if it doesn't exist.
 */
int
removenataddr(uchar *src, uchar *mask, Iplifc *dst)
{
	NatAddr *c;	/* Current node */
	NatAddr *p;	/* Precedent node */

	for(p=nil, c=addrhead; c!=nil; p=c, c=c->next)
		if(ipcmp(src, c->src) == 0 &&
			ipcmp(mask, c->mask) == 0 &&
			dst == c->dst)
			break;

	if(c == nil)
		return -1;

	if(p == nil)
		addrhead = addrhead->next;
	else
		p->next = c->next;

	return 0;
}

/*
 * Display NatAddr list.
 */
void
shownataddr(void)
{
	NatAddr *c;	/* Current node */

	for(c=addrhead; c!=nil; c=c->next)
		print("%I %V %I\n", c->src, c->mask+IPv4off, c->dst->local);
}

/*
 * Flush NatAddr list.
 */
void
flushnataddr(void)
{
	NatAddr *c;	/* Current node */

	while((c=addrhead) != nil){
		addrhead = addrhead->next;
		free(c);
	}
}

/*
 * Return logical interface if NAT is enabled on this interface,
 * and the source address must be translated.
 */
Iplifc*
natonifco(Ipifc *ifc, Ip4hdr* h)
{
	NatAddr *na;		/* Address list */
	Iplifc *lifc;		/* Logical interface */
	uchar src[IPaddrlen];	/* Source address */
	uchar net[IPaddrlen];	/* Source network address */

	for(lifc=ifc->lifc; lifc!=nil; lifc=lifc->next)
		for(na=addrhead; na; na=na->next)
			if(lifc == na->dst){
				/* NAT enabled on this logical interface */
				v4tov6(src, h->src);
				maskip(src, na->mask, net);
				if(ipcmp(net, na->net) == 0)
					/* Source address must be translated */
					return lifc;
			}

	return nil;
}

/*
 * Return logical interface if NAT is enabled on this interface.
 */
Iplifc*
natonifci(Ipifc *ifc)
{
	NatAddr *na;		/* Address list */
	Iplifc *lifc;		/* Logical interface */

	for(lifc=ifc->lifc; lifc!=nil; lifc=lifc->next)
		for(na=addrhead; na; na=na->next)
			if(lifc == na->dst){
				/* NAT enabled on this logical interface */
				return lifc;
			}

	return nil;
}
