variable Controlfd
variable Datafd
struct Conf
{
	/* locally generated */
	char	*type;
	char	*dev;
	char	mpoint[32];
	int	cfd;			/* ifc control channel */
	int	rfd;			/* iproute control channel */
	char	*cputype;
	uchar	hwa[32];		/* hardware address */
	int	hwatype;
	int	hwalen;
	uchar	cid[32];
	int	cidlen;
	char	*baud;

	/* learned info */
	uchar	gaddr[IPaddrlen];
	uchar	laddr[IPaddrlen];
	uchar	mask[IPaddrlen];
	uchar	raddr[IPaddrlen];
	uchar	dns[8*IPaddrlen];
	uchar	fs[2*IPaddrlen];
	uchar	auth[2*IPaddrlen];
	uchar	ntp[2*IPaddrlen];
	int	mtu;

	/* dhcp specific */
	int	state; Phase
	int	fd;
	ulong	xid;
	ulong	starttime;
	char	sname[64];
	char	hostname[256];
	char	domainname[256];
	char	dnsdomain[256];
	uchar	server[IPaddrlen];	/* server IP address */
	ulong	offered;		/* offered lease time */
	ulong	lease;			/* lease time */
	ulong	resend;			/* # of resends for current state */
	ulong	timeout;		/* time to timeout - seconds */

	/*
	 * IPv6
	 */

	/* router-advertisement related */
	uchar	sendra;
	uchar	recvra;
	uchar	mflag;
	uchar	oflag;
	int 	maxraint; /* rfc2461, p.39: 4sec ≤ maxraint ≤ 1800sec, def 600 */
	int	minraint;	/* 3sec ≤ minraint ≤ 0.75*maxraint */
	int	linkmtu;
	int	routerlt;	/* router life time */
	int	reachtime;	/* 3,600,000 msec, default 0 */
	int	rxmitra;	/* default 0 */
	int	ttl;		/* default 0 (unspecified) */

	/* prefix related */
	uchar	lladdr[IPaddrlen];
	uchar	v6pref[IPaddrlen];
	int	prefixlen;
	uchar	onlink;		/* flag: address is `on-link' */
	uchar	autoflag;	/* flag: autonomous */
	ulong	validlt;	/* valid lifetime (seconds) */
	ulong	preflt;		/* preferred lifetime (seconds) */
};

variable Message 127 vallot \ allot 128 bytes on the variable heap for Message

a!	\ ( a c -- a+1 ) swap 1+ dup >r ! r> ;
ipnoaddr ( a -- a+4 ) \ stores 4 0's at a
	4 0 do 0 a! loop

: addnulladdr	
	hex
	" add " Message swap ( a am n ) cmove
	Message 5 + ipnoaddr
	020 ( a space ) a! ( a+4+4+1 )
	ipnoaddr ( a+4+4+1+4 )
	Message 13 Controlfd @ write-file

listen open
	start openlisten
	variable Data 	127 vallot
	variable Devdir	39 vallot
	" /net/udp!*!68" Data swap cmov
	announce Data Devdir
	" headers" Controlfd @ write-file

	sprint(data, "%s/data", devdir);
	fd = open(data, ORDWR);
	if(fd < 0)
		sysfatal("open %s: %r", data);
	close(cfd);
	return fd;
	forget openlisten

52 constant UDPHDRSIZE

vhere constant Bootp 100 vallot
	variable Bootp 100 vallot
: Header	Bootp ;
: Opcode	Bootp 4 + ;
: Hardware	Bootp 5 + ;
: Type	Hardware ;
: Hardware.type	Hardware ;
: Hardware.length	Hardware 1+ ;
: Hops	Bootp 6 + ;
: Xid	Bootp 7 + ;
: Seconds	Bootp 9 + ;
: Flags	Bootp 11 + ;
: Client.Ip.Address	Bootp 13 + ;
: Yield.Ip.Address	Bootp 13 + ;
: Server.Ip.Address	Bootp 13 + ;
: Gateway.Ip.Address	Bootp 13 + ;
: Client.Hardware.Address	Bootp 14 + ;
: Server.hostname Bootp 15 + ;
: File Bootp 16 + ;
: Magic	Bootp 17 + ;
: Data	Bootp 18 + ;

: send ( type -- )
	
: bootreply ( a n -- )
	dup 300 < if ." bootreply: short bootp packet" terminate then
	over >Xid Xid 4 c= not if exit then
	over >Op c@ dup BOOTREPLY != if ." bootreply: bad op" emit exit then drop
	options

: lease	( time -- )	dup 0= if MIN_LEASE then Lease !
: serverid	( ipaddr -- )	TODO check address Server !

: offer ( a n -- )
	Phase @ SELECTING != if exit then
	2dup IP_ADDRESS_LEASE_TIME ( a n a n mtype ) search time@ ( a n time ) lease
	2dup SERVER_IDENTIFIER ( a n a n mtype ) search ipaddr@ ( a n ipaddr ) serverid
	over >Your_ip_address addr@ v4>v6 Localaddress !
	over >Server_name Sname 64 cmove ( TODO make this a counted string )
		." server " Server .ipaddr ." name " Sname 64 type cr
	Lease @ Offered !
	REQUESTING Phase !
	REQUEST send

: ack ( a n -- )
	Phase @
		dup REQUESTING != >r
		dup RENEWING != >r
		dup REBINDING != r> r> and and if exit then
	2dup IP_ADDRESS_LEASE_TIME ( a n a n mtype ) search time@ ( a n time ) lease
	parse options

: nak ( a n -- )	2drop INIT Phase !

: dhcpreply ( a n -- )
	2dup bootreply
	2dup DHCP_MESSAGE_TYPE ( a n a n mtype ) search ( a n amtype ) c@ ( a n mtype )
	dup DHCPOFFER = if offer exit else
	dup	DHCPACK	=	if ack exit else
	dup	DHCPNAK	=	if nak exit else
		then then then
	." dhcpreply: unknown type" emit 2drop

: ask
	Phase @
		dup SELECTING =	if 0 Offered ! DISCOVER send else
		dup RENEWING =	if REQUEST	send else
							." correspond invalid phase" terminate
			then then drop

\ split the short to 2 bytes
: split2 ( n -- low high )
	hex dup ( n n )
	0F0 and 8 rshift >r
	 0F and r>
	decimal

\ split the long to 4 bytes
: split4 ( n -- c0 c1 c2 c3 )
	hex dup ( n n )
	0F000 and 24 rshift >r
	 0F00 and 16 rshift >r
	  0F0 and 8  rshift >r
	   0F and ( c0 )
	r> ( c0 c1 ) r> r> ( c0 c1 c2 c3 ) 
	decimal

\ rename put* functions to hnput* functions
: put	( low .. high a n -- a+n ) \ store n bytes at a in big endian, high goes first
	dup 0 = if ." put with n 0" terminate then
	0 do dup ( low .. high a a ) >r c! r> 1+ ( low .. high-1 a+1 ) loop
: put8	( byte a -- a+1 )	1 put ;
: put16	( short a -- a+2 )	>r split2 r> 2 put ;
: put32	( long a -- a+4 )	>r split4 r> 4 put ;
: putn	( source a n -- a+n ) 2dup + >r \ (R a+n )
	cmove r> ;

\ put in host network order - big endian
: arrange ( .. 'placer len code a -- )
	put8 ( .. 'placer len a+1 ) \ put the code type
	put8 ( .. 'placer a+2 )		\ put the length
	swap execute 				\ let the placer do the rest

: optionstring ( countedstring code a -- a+stringlength )
	>r >r count ( stringaddress length ) ' putn over ( stringaddress length 'placer length ) \ (R a code )
	r> r> arrange

: get	( a n -- high .. low a+n ) \ get n bytes at a in big endian, high comes first
	0 do dup ( a a ) >r c@ r> 1+ ( high a+1 ) loop
: get8	( a -- byte a+1 )	1 get ;
: get16	( a -- short a+2 )	2 get >r join2 r> ;
: get32	( a -- long a+4 )	4 get >r join4 r> ;

: save8	( destination a -- byte a+1 )	get drop swap ! ;
: save16	( destination a -- short a+2 )	get16 drop swap ! ;
: save32 ( destination a -- ) get32 drop swap ! ;
: saven	( destination a n -- a+n ) 2dup + >r \ (R a+n )
	>r swap >r ( a destination n ) cmove ;
: check	( receivedlength expectedlength -- )
	2dup != if ." check lengths do not match" emit emit then
: extract ( destination len 'puller code a -- )
	dup 1+ @ 5 pick check	( destination len 'puller code a -- )
	nip swap >r swap r> execute
: pull ( destination 'puller code a --  ) \ if a1 == 0, option with that code not found
	>Limit @ swap ( code end begin )
	2dup = if ." pull at the end " emit emit emit terminate then
	begin dup i c@ = if r> rdrop extract exit
						else i 1+ c@ then
	( 'puller code skip ) +loop

: place ( low .. high len type a -- a+1+len ) \ store the option at a
	dup >r c! ( low .. high len ) \ (R a )
	r@ 1+ ( low .. high len a ) over >r c!  ( low .. high ) \ (R a len ) type and len stored at a
	r> r> 2 + ( low .. high len a+2 ) swap ( low .. high a+2 len ) put

\ put in host network order - big endian
: hnput ( a n n -- a+n ) \ (G put in host network order )
	dup 2 = if drop ( a n ) swap >r short r> ( low high a )    2 put exit then
	dup 4 = if drop ( a n ) swap >r long  r> ( c0 c1 c2 c3 a ) 4 put exit then
	." unknown number of bytes" emit terminate

12 constant OPTION.HOSTNAME
50 constant OPTION.REQUESTED_IP_ADDRESS
55 constant OPTION.PARAMETER_REQUEST_LIST
60 constant OPTION.VENDOR.CLASS.IDENTIFIER
255 constant OPTION.END

: discover ( a )
	dup >Remote.address IPv4bcast swap IPADDRESSLENGTH cmove
	TODO add hostname OPTION.HOSTNAME option
	TODO add " plan9_amd64" OPTION.VENDOR.CLASS.IDENTIFIER option
	TODO add requeted OPTION.PARAMETER_REQUEST_LIST option
	TODO add requeted OPTION.REQUESTED_IP_ADDRESS Local option

: request ( a )
	Phase @
		dup RENEWING   = if renew  else
		dup REBINDING  = if rebind else
		dup REQUESTING = if request else
			then then then drop
	dup >Remote.address IPv4bcast swap IPADDRESSLENGTH cmove
	TODO add hostname OPTION.HOSTNAME option
	TODO add " plan9_amd64" OPTION.VENDOR.CLASS.IDENTIFIER option
	TODO add requeted OPTION.PARAMETER_REQUEST_LIST option
	TODO add requeted OPTION.REQUESTED_IP_ADDRESS Local option

: release ( a )
	send raddr
	v6tov4 ciaddr
	TODO add requeted OPTION.REQUESTED_IP_ADDRESS Local option
	TODO add Serverid requeted OPTION.REQUESTED_IP_ADDRESS Local option

: build ( type a -- ) \ build the dhcp message at a
	dup >Rport 67 2 hnput
	BOOTREQUEST over >Op c!
	dup >Xid Xid @ 4 hnput
	dup >Secs
		time Starttime @ -
		2 hnput
	dup >Flags 0 2 hnput
	dup >Magic >r 99 83 130 99 r> 4 put
	dup >Chaddr Hardware.address swap Hardware.address.length cmove
	dup >Htype Hardware.type @ swap c!
	dup >Hlen Hardware.address.length @ swap c!
	2dup ( type a type a ) >Optiondata swap c!
	swap ( a type )
	dup DISCOVER = if drop discover else
	dup REQUEST  = if drop request  else
	dup RELEASE  = if drop release  else
		." dhcpsend: unknown message type" emit terminate
		then then then
	TODO add OPTION.END option

: dhcpsend ( type -- )
	pad dup erase ( a ) build send

timer
	time Timeout @ < if exit then
	Phase @
		dup INIT  = if exit then
		dup BOUND = if exit then
		dup SELECTING =
		over REQUESTING = or
		over REBINDING = or
			if Phase @ SELECTING = if discover else request then
				time 4 + Timeout !
				Resend 1+ Resend @ 5 > if INIT Phase ! then
			then
		dup RENEWING = if
							time 1 + Timeout !
							Resend 1+ Resend @ 3 > if REBINDING Phase ! 0 Resend ! then
						then

correspond
	Xid !
	Start !
	Phase !
	ask
	0 Resend !
	time 4 + Timeout !
	begin
		receive timer
		Phase @ dup SBOUND != swap SINIT != and
	until

configure
	add ipnoaddr ipnoaddr send
	correspond
	remove ipnoaddr ipnoaddr send

void
dhcpquery(int needconfig, int startstate)
{
	if(needconfig)
		addnulladdr();

	conf.fd = openlisten();
	if(conf.fd < 0){
		conf.state = Sinit;
		return;
	}
	notify(catch);

	conf.xid = lrand();
	conf.starttime = time(0);
	conf.state = startstate;
	switch(startstate){
	case Sselecting:
		conf.offered = 0;
		dhcpsend(Discover);
		break;
	case Srenewing:
		dhcpsend(Request);
		break;
	default:
		sysfatal("internal error 0");
	}
	conf.resend = 0;
	conf.timeout = time(0) + 4;

	while(conf.state != Sbound && conf.state != Sinit){
		dhcprecv();
		dhcptimer();
	}
	close(conf.fd);

	if(needconfig)
		removenulladdr();
}
static void
dhcptimer(void)
{
	ulong now;

	now = time(0);
	if(now < conf.timeout)
		return;

	switch(conf.state) {
	default:
		sysfatal("dhcptimer: unknown state %d", conf.state);
	case Sinit:
	case Sbound:
		break;
	case Sselecting:
	case Srequesting:
	case Srebinding:
		dhcpsend(conf.state == Sselecting? Discover: Request);
		conf.timeout = now + 4;
		if(++conf.resend > 5)
			conf.state = Sinit;
		break;
	case Srenewing:
		dhcpsend(Request);
		conf.timeout = now + 1;
		if(++conf.resend > 3) {
			conf.state = Srebinding;
			conf.resend = 0;
		}
		break;
	}
}

static void
dhcpsend(int type)
{
	Bootp bp;
	uchar *p;
	int n;
	uchar vendor[64];
	Udphdr *up = (Udphdr*)bp.udphdr;

	memset(&bp, 0, sizeof bp);

	hnputs(up->rport, 67);
	bp.op = Bootrequest;
	hnputl(bp.xid, conf.xid);
	hnputs(bp.secs, time(0)-conf.starttime);
	hnputs(bp.flags, 0);
	memmove(bp.optmagic, optmagic, 4);
	if(conf.hwatype >= 0 && conf.hwalen < sizeof bp.chaddr){
		memmove(bp.chaddr, conf.hwa, conf.hwalen);
		bp.hlen = conf.hwalen;
		bp.htype = conf.hwatype;
	}
	p = bp.optdata;
	p = optaddbyte(p, ODtype, type);
	p = optadd(p, ODclientid, conf.cid, conf.cidlen);
	switch(type) {
	default:
		sysfatal("dhcpsend: unknown message type: %d", type);
	case Discover:
		ipmove(up->raddr, IPv4bcast);	/* broadcast */
		if(*conf.hostname && sendhostname)
			p = optaddstr(p, OBhostname, conf.hostname);
		if(plan9){
			n = snprint((char*)vendor, sizeof vendor,
				"plan9_%s", conf.cputype);
			p = optaddvec(p, ODvendorclass, vendor, n);
		}
		p = optaddvec(p, ODparams, requested, nrequested);
		if(validip(conf.laddr))
			p = optaddaddr(p, ODipaddr, conf.laddr);
		break;
	case Request:
		switch(conf.state){
		case Srenewing:
			ipmove(up->raddr, conf.server);
			v6tov4(bp.ciaddr, conf.laddr);
			break;
		case Srebinding:
			ipmove(up->raddr, IPv4bcast);	/* broadcast */
			v6tov4(bp.ciaddr, conf.laddr);
			break;
		case Srequesting:
			ipmove(up->raddr, IPv4bcast);	/* broadcast */
			p = optaddaddr(p, ODipaddr, conf.laddr);
			p = optaddaddr(p, ODserverid, conf.server);
			break;
		}
		p = optaddulong(p, ODlease, conf.offered);
		if(plan9){
			n = snprint((char*)vendor, sizeof vendor,
				"plan9_%s", conf.cputype);
			p = optaddvec(p, ODvendorclass, vendor, n);
		}
		p = optaddvec(p, ODparams, requested, nrequested);
		if(*conf.hostname && sendhostname)
			p = optaddstr(p, OBhostname, conf.hostname);
		break;
	case Release:
		ipmove(up->raddr, conf.server);
		v6tov4(bp.ciaddr, conf.laddr);
		p = optaddaddr(p, ODipaddr, conf.laddr);
		p = optaddaddr(p, ODserverid, conf.server);
		break;
	}

	*p++ = OBend;

	n = p - (uchar*)&bp;
	USED(n);

	/*
	 *  We use a maximum size DHCP packet to survive the
	 *  All_Aboard NAT package from Internet Share.  It
	 *  always replies to DHCP requests with a packet of the
	 *  same size, so if the request is too short the reply
	 *  is truncated.
	 */
	if(write(conf.fd, &bp, sizeof bp) != sizeof bp)
		warning("dhcpsend: write failed: %r");
}

static void
dhcprecv(void)
{
	int i, n, type;
	ulong lease;
	char err[ERRMAX];
	uchar buf[8000], vopts[256], taddr[IPaddrlen];
	Bootp *bp;

	memset(buf, 0, sizeof buf);
	alarm(1000);
	n = read(conf.fd, buf, sizeof buf);
	alarm(0);

	if(n < 0){
		rerrstr(err, sizeof err);
		if(strstr(err, "interrupt") == nil)
			warning("dhcprecv: bad read: %s", err);
		else
			DEBUG("dhcprecv: read timed out");
		return;
	}

	bp = parsebootp(buf, n);
	if(bp == 0) {
		DEBUG("parsebootp failed: dropping packet");
		return;
	}

	type = optgetbyte(bp->optdata, ODtype);
	switch(type) {
	default:
		warning("dhcprecv: unknown type: %d", type);
		break;
	case Offer:
		DEBUG("got offer from %V ", bp->siaddr);
		if(conf.state != Sselecting)
			break;
		lease = optgetulong(bp->optdata, ODlease);
		if(lease == 0){
			/*
			 * The All_Aboard NAT package from Internet Share
			 * doesn't give a lease time, so we have to assume one.
			 */
			warning("Offer with %lud lease, using %d", lease, MinLease);
			lease = MinLease;
		}
		DEBUG("lease=%lud ", lease);
		if(!optgetaddr(bp->optdata, ODserverid, conf.server)) {
			warning("Offer from server with invalid serverid");
			break;
		}

		v4tov6(conf.laddr, bp->yiaddr);
		memmove(conf.sname, bp->sname, sizeof conf.sname);
		conf.sname[sizeof conf.sname-1] = 0;
		DEBUG("server=%I sname=%s", conf.server, conf.sname);
		conf.offered = lease;
		conf.state = Srequesting;
		dhcpsend(Request);
		conf.resend = 0;
		conf.timeout = time(0) + 4;
		break;
	case Ack:
		DEBUG("got ack from %V ", bp->siaddr);
		if (conf.state != Srequesting && conf.state != Srenewing &&
		    conf.state != Srebinding)
			break;

		/* ignore a bad lease */
		lease = optgetulong(bp->optdata, ODlease);
		if(lease == 0){
			/*
			 * The All_Aboard NAT package from Internet Share
			 * doesn't give a lease time, so we have to assume one.
			 */
			warning("Ack with %lud lease, using %d", lease, MinLease);
			lease = MinLease;
		}
		DEBUG("lease=%lud ", lease);

		/* address and mask */
		if(!validip(conf.laddr) || !Oflag)
			v4tov6(conf.laddr, bp->yiaddr);
		if(!validip(conf.mask) || !Oflag){
			if(!optgetaddr(bp->optdata, OBmask, conf.mask))
				ipmove(conf.mask, IPnoaddr);
			if(ipcmp(conf.mask, IPv4bcast) == 0)
				ipmove(conf.mask, IPnoaddr);
		}
		DEBUG("ipaddr=%I ipmask=%M ", conf.laddr, conf.mask);

		/*
		 * get a router address either from the router option
		 * or from the router that forwarded the dhcp packet
		 */
		if(validip(conf.gaddr) && Oflag) {
			DEBUG("ipgw=%I ", conf.gaddr);
		} else if(optgetaddr(bp->optdata, OBrouter, conf.gaddr)){
			DEBUG("ipgw=%I ", conf.gaddr);
		} else if(memcmp(bp->giaddr, IPnoaddr+IPv4off, IPv4addrlen)!=0){
			v4tov6(conf.gaddr, bp->giaddr);
			DEBUG("giaddr=%I ", conf.gaddr);
		}

		/* get dns servers */
		memset(conf.dns, 0, sizeof conf.dns);
		n = optgetaddrs(bp->optdata, OBdnserver, conf.dns,
			sizeof conf.dns/IPaddrlen);
		for(i = 0; i < n; i++)
			DEBUG("dns=%I ", conf.dns + i*IPaddrlen);

		/* get ntp servers */
		memset(conf.ntp, 0, sizeof conf.ntp);
		n = optgetaddrs(bp->optdata, OBntpserver, conf.ntp,
			sizeof conf.ntp/IPaddrlen);
		for(i = 0; i < n; i++)
			DEBUG("ntp=%I ", conf.ntp + i*IPaddrlen);

		/* get names */
		if(optgetstr(bp->optdata, OBhostname,
			conf.hostname, sizeof conf.hostname))
			DEBUG("hostname=%s ", conf.hostname);
		if(optgetstr(bp->optdata, OBdomainname,
			conf.domainname, sizeof conf.domainname))
			DEBUG("domainname=%s ", conf.domainname);
		if(optgetnames(bp->optdata, ODdnsdomain,
			conf.dnsdomain, sizeof conf.dnsdomain))
			DEBUG("dnsdomain=%s ", conf.dnsdomain);

		/* get anything else we asked for */
		getoptions(bp->optdata);

		/* get plan9-specific options */
		n = optgetvec(bp->optdata, OBvendorinfo, vopts, sizeof vopts-1);
		if(n > 0 && parseoptions(vopts, n) == 0){
			if(validip(conf.fs) && Oflag)
				n = 1;
			else {
				n = optgetp9addrs(vopts, OP9fs, conf.fs, 2);
				if (n == 0)
					n = optgetaddrs(vopts, OP9fsv4,
						conf.fs, 2);
			}
			for(i = 0; i < n; i++)
				DEBUG("fs=%I ", conf.fs + i*IPaddrlen);

			if(validip(conf.auth) && Oflag)
				n = 1;
			else {
				n = optgetp9addrs(vopts, OP9auth, conf.auth, 2);
				if (n == 0)
					n = optgetaddrs(vopts, OP9authv4,
						conf.auth, 2);
			}
			for(i = 0; i < n; i++)
				DEBUG("auth=%I ", conf.auth + i*IPaddrlen);

			n = optgetp9addrs(vopts, OP9ipaddr, taddr, 1);
			if (n > 0)
				ipmove(conf.laddr, taddr);
			n = optgetp9addrs(vopts, OP9ipmask, taddr, 1);
			if (n > 0)
				ipmove(conf.mask, taddr);
			n = optgetp9addrs(vopts, OP9ipgw, taddr, 1);
			if (n > 0)
				ipmove(conf.gaddr, taddr);
			DEBUG("new ipaddr=%I new ipmask=%M new ipgw=%I",
				conf.laddr, conf.mask, conf.gaddr);
		}
		conf.lease = lease;
		conf.state = Sbound;
		DEBUG("server=%I sname=%s", conf.server, conf.sname);
		break;
	case Nak:
		conf.state = Sinit;
		warning("recved dhcpnak on %s", conf.mpoint);
		break;
	}
}
