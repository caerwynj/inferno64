implement Dhcpd;

include "sys.m";
	sys: Sys;
	sprint: import sys;
include "draw.m";
include "arg.m";
include "bufio.m";
	bufio: Bufio;
	Iobuf: import bufio;
include "string.m";
	str: String;
include "daytime.m";
	daytime: Daytime;
include "attrdb.m";
	attrdb: Attrdb;
	Attr, Db, Dbentry: import attrdb;
include "ip.m";
	ip: IP;
	IPaddr, Udphdr: import ip;
include "ether.m";
	ether: Ether;
include "lists.m";
	lists: Lists;
include "encoding.m";
	base16: Encoding;
include "dhcpserver.m";
	dhcp: Dhcpserver;
	Dhcpmsg, Opt: import dhcp;
include "ipval.m";
	ipval: Ipval;

Dhcpd: module
{
	init: fn(nil: ref Draw->Context, args: list of string);
};

dflag: int;
sflag: int;

siaddr: IPaddr;
sysname: string;
net: string;
ndb: ref Db;
ndbfile := "/lib/ndb/local";
statedir := "/services/dhcpd";
leasetime := 24*3600;
bootpfd: ref Sys->FD;


Range: adt {
	ip:	IPaddr;
	n:	int;
};
ranges: list of Range;

Addr: adt {
	ip:		IPaddr;
	pick {
	Fixed =>
	Dynamic =>
		hwaddr:		array of byte;
		clientid:	array of byte;
		leasestart:	int;
		leasetime:	int;	# 0 means unassigned
		hostname:	string;
	}
};

pool: array of ref Addr.Dynamic;
pooloff: int;


# dhcp options -> ndb attributes
optattrs := array[] of {
dhcp->Osubnetmask	=> "ipmask",
dhcp->Orouters		=> "ipgw",
dhcp->Odns		=> "dns",
dhcp->Ohostname		=> "sys",
dhcp->Odomainname	=> "dnsdomain",
dhcp->Orootpath		=> "rootpath",
#dhcp->Obroadcast	=> "ipbroadcast",

dhcp->Oleasetime	=> "leasetime",
#dhcp->Ovendorclass	=> "dhcpvendorclass",
dhcp->Otftpservername	=> "tftp",
dhcp->Obootfile		=> "bootf",
};

# TODO -l is a temporary hack
# BUG is using the sysname to find the ip from the ndb
#	sysname could be used for the interface bound to /net
#	and dhcpd might be using -x /net.alt
# 9front's dhcpd finds the relevant ip using the argument ip address
# until that functionality is added, use -l argument to set the
#	local ip address
init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	bufio = load Bufio Bufio->PATH;
	arg := load Arg Arg->PATH;
	str = load String String->PATH;
	daytime = load Daytime Daytime->PATH;
	attrdb = load Attrdb Attrdb->PATH;
	attrdb->init();
	ip = load IP IP->PATH;
	ip->init();
	ether = load Ether Ether->PATH;
	ether->init();
	lists = load Lists Lists->PATH;
	base16 = load Encoding Encoding->BASE16PATH;
	dhcp = load Dhcpserver Dhcpserver->PATH;
	dhcp->init();
	ipval = load Ipval Ipval->PATH;
	ipaddr : string;

	arg->init(args);
	arg->setusage(arg->progname()+" [-ds] [-f file] [-x network] [-l ipaddr] [ipaddr n ...]");
	while((o := arg->opt()) != 0)
		case o {
		'd' =>	dflag++;
		's' =>	sflag++;
		'x' =>	net = arg->earg();
		'f' =>	ndbfile = arg->earg();
		'l' =>	ipaddr = arg->earg();
		* =>	arg->usage();
		}
	args = arg->argv();
	if(len args % 2 != 0)
		arg->usage();
	for(; args != nil; args = tl tl args)
		addrange(hd args, hd tl args);
	poolmake();
	poolreadstate();
	pooldump();

	sys->pctl(Sys->FORKFD|Sys->FORKNS, nil);

	if(!sflag) {
		ndb = Db.open(ndbfile);
		if(ndb == nil)
			fail(sprint("db open %q: %r", ndbfile));

		if(ipaddr == nil){
			sysname = readfile("/dev/sysname");
			if(sysname == nil)
				fail("could not determine system name, /dev/sysname");

			(e, nil) := ndb.findbyattr(nil, "sys", sysname, "ip");
			if(e != nil)
				ipaddr = e.findfirst("ip");
		}
		ok: int;
		(ok, siaddr) = IPaddr.parse(ipaddr);
		if(ok < 0 || !siaddr.isv4() || siaddr.eq(ip->v4noaddr))
			fail(sprint("could not determine ip for system name %q", sysname));
		say("local ip address is "+siaddr.text());
	}

	addr := net+"udp!*!bootp";
	(ok, c) := sys->announce(addr);
	if(ok < 0)
		fail(sprint("announce %s: %r", addr));
	say("announced "+addr);
	if(sys->fprint(c.cfd, "headers") < 0)
		fail(sprint("setting headers mode: %r"));

	path := c.dir+"/data";
	bootpfd = sys->open(path, sys->ORDWR);
	if(bootpfd == nil)
		fail(sprint("open %s: %r", path));
	spawn server();
}

addrange(ipaddr, ns: string)
{
	# parse addr, generate end address
	(ok, ipa) := IPaddr.parse(ipaddr);
	if(ok < 0 || !ipa.isv4() || ipa.eq(ip->v4noaddr) || ipa.eq(ip->noaddr) || ipa.ismulticast())
		fail(sprint("bad ip %q", ipaddr));

	(n, rem) := str->toint(ns, 10);
	if(rem != nil || n <= 0)
		fail(sprint("bad count %q", ns));
	start := ipa.v4();
	if(int start[3]+n > 255)
		fail(sprint("range extends past subnet, %q %q", ipaddr, ns));

	# check that there is no address overlap
	for(l := ranges; l != nil; l = tl l) {
		r := hd l;
		rstart := r.ip.v4();
		if(!eq(start[:3], rstart[:3]))
			continue;
		s := int start[3];
		rs := int rstart[3];
		e := s+n;
		re := rs+r.n;
		if(s <= rs && e >= re || s >= rs && s < re || e > rs && e < re)
			fail(sprint("ranges overlap, %q %d with %q %d", r.ip.text(), r.n, ipaddr, n));
	}

	# record the new range
	ranges = Range (ipa, n)::ranges;
}

# we order by longest unused.
addrge(a, b: ref Addr.Dynamic): int
{
	if(a.leasetime == 0 && b.leasetime == 0) {
		if(a.leasestart == b.leasestart)
			return ipcmp(a.ip, b.ip) >= 0;
		return a.leasestart >= b.leasestart;
	}
	if(a.leasetime == 0)
		return 0;
	if(b.leasetime == 0)
		return 1;
	return a.leasestart+a.leasetime >= b.leasestart+b.leasetime;
}

poolmake()
{
	la: list of ref Addr.Dynamic;
	for(l := ranges; l != nil; l = tl l) {
		r := hd l;
		s := r.ip.v4();
		for(i := 0; i < r.n; i++) {
			ipa := IPaddr.newv4(s);
			a := ref Addr.Dynamic (ipa, nil, nil, 0, 0, nil);
			la = a::la;
			s[3]++;
		}
	}
	pool = l2a(la);
	sort(pool, addrge);
	pooloff = 0;
}

readstatefile(ipfile: string)
{
	(ok, ipa) := IPaddr.parse(ipfile);
	if(ok < 0)
		return;
	a := poolfindip(ipa);
	if(a == nil)
		return;

	path := sprint("%s/%s", statedir, ipfile);
	s := readfile(path);
	if(s == nil)
		return warn(sprint("statefile %q: %r;  ignoring", path));

	# hwaddr clientid leasestart leasetime hostname
	t := str->unquoted(s);
	if(len t != 5)
		return warn(sprint("statefile %q: bad format, ignoring", path));

	a.hwaddr = base16->dec(hd t);
	t = tl t;
	a.clientid = base16->dec(hd t);
	t = tl t;
	a.leasestart = int hd t;
	t = tl t;
	a.leasetime = int hd t;
	t = tl t;
	a.hostname = hd t;
	t = tl t;
}

writestatefile(a: ref Addr.Dynamic)
{
	path := sprint("%s/%s", statedir, a.ip.text());
	s := sprint("%q %q %d %d %q\n", hex(a.hwaddr), hex(a.clientid), a.leasestart, a.leasetime, a.hostname);
	err := writefile(path, s);
	if(err != nil)
		warn(sprint("write %q: %s", path, err));
}

poolreadstate()
{
	fd := sys->open(statedir, Sys->OREAD);
	if(fd == nil)
		return warn(sprint("open %q: %r;  will not keep state", statedir));
	for(;;) {
		(n, d) := sys->dirread(fd);
		if(n < 0)
			return warn(sprint("dirread %q: %r;  state not read", statedir));
		if(n == 0)
			break;
		for(i := 0; i < n; i++)
			readstatefile(d[i].name);
	}
}

pooldump()
{
	say("pool:");
	for(i := 0; i < len pool; i++)
		say(sprint("\t%s", pool[i].ip.text()));
	say("end pool");
}

server()
{
	buf := array[2048] of byte;
	say("starting server loop");
	say("server <-> client");
	for(;;) {
		n := sys->read(bootpfd, buf, len buf);
		if(n < 0)
			return warn(sprint("read packet: %r"));
		say(sprint("read packet: %d bytes", n));
		serve(buf[:n]);
	}
}

serve(buf: array of byte)
{
	if(len buf < IP->Udphdrlen)
		return say(sprint("short udp header: %d bytes", len buf));
	hdr := Udphdr.unpack(buf, IP->Udphdrlen);
	say(sprint("udp read, remote %q!%d, local %q!%d, ifcaddr %q", hdr.raddr.text(), hdr.rport, hdr.laddr.text(), hdr.lport, hdr.ifcaddr.text()));
	buf = buf[IP->Udphdrlen:];

	(im, err) := Dhcpmsg.unpack(buf);
	if(err != nil)
		return say("parsing dhcpmsg: "+err);
	if(sflag || dflag >= 2)
		say("-> "+im.text());
	if(sflag)
		return;

	if(im.op != dhcp->Trequest)
		return say("message is reply, not request;  ignoring");
	if(im.htype != 1 || im.hlen != 6)
		return say("hardware type not ether; ignoring");

	if(ndb.changed() && ndb.reopen() < 0)
		return warn(sprint("reopening ndb file: %r"));

	om: ref Dhcpmsg;
	t := dhcpmsgtype(im);
	if(t < 0) {
		say("bootp request");
	} else {
		say("dhcp request");
			# server <- client
		say("<- "+im.text()); # 9p debug message direction
		om = dhcpsrv(t, im);
	}

	if(om != nil) {
			# server -> client
		say("-> "+om.text()); # 9p debug message direction
		obuf := om.pack();

		ipdest := im.giaddr;
		if(ipdest.eq(ip->v4noaddr)) {
			if(im.flags & dhcp->Fbroadcast)
				ipdest = ip->v4bcast;
			else
				ipdest = ip->v4bcast; # xxx
		}

		hdr.raddr = ipdest;
		hdr.laddr = siaddr;
		hdr.ifcaddr = siaddr;
		hdr.rport = 68;
		hdr.lport = 67;
		pkt := array[ip->Udphdrlen+len obuf] of byte;
		hdr.pack(pkt, ip->Udphdrlen);
		pkt[ip->Udphdrlen:] = obuf;
		say(sprint("udp write, remote %q!%d, local %q!%d, ifcaddr %q", hdr.raddr.text(), hdr.rport, hdr.laddr.text(), hdr.lport, hdr.ifcaddr.text()));
		if(sys->write(bootpfd, pkt, len pkt) != len pkt)
			warn(sprint("udp write: %r"));
	}
}

dhcpmsgtype(m: ref Dhcpmsg): int
{
	if(g32(m.options) == dhcp->Moptions)
		for(l := m.opts; l != nil; l = tl l)
			if((hd l).code == dhcp->Odhcpmsgtype && len (hd l).v == 1)
				return int (hd l).v[0];
	return -1;
}

getoption(m: ref Dhcpmsg, code: int): array of byte
{
	for(l := m.opts; l != nil; l = tl l)
		if((hd l).code == code)
			return (hd l).v;
	return nil;
}

getoptionip(m: ref Dhcpmsg, code: int): ref IPaddr
{
	v := getoption(m, code);
	if(v != nil && len v == 4)
		ipa := ref IPaddr.newv4(v);
	return ipa;
}

ethertext0(hwaddr: array of byte): string
{
	return ether->text(hwaddr);
}

ethertext1(hwaddr: array of byte): string
{
	s := ether->text(hwaddr);
	if(len s != 12)  # 6 bytes in hex, as mentioned by ether(2)
		return s;
	return sprint("%s:%s:%s:%s:%s:%s", s[0:2], s[2:4], s[4:6], s[6:8], s[8:10], s[10:12]);
}

etherip(hwaddr: array of byte): ref IPaddr
{
	(e, nil) := ndb.findbyattr(nil, "ether", ethertext0(hwaddr), "ip");
	if(e == nil)
		(e, nil) = ndb.findbyattr(nil, "ether", ethertext1(hwaddr), "ip");
	if(e == nil)
		return nil;
	ipaddr := e.findfirst("ip");
	if(ipaddr == nil)
		return nil;
	(ok, eipa) := IPaddr.parse(ipaddr);
	if(ok < 0)
		return nil;
	return ref eipa;
}

None, Hit, Bad: con iota;
etheripmatch(hwaddr: array of byte, ipa: IPaddr): int
{
	(e, nil) := ndb.findbyattr(nil, "ether", ether->text(hwaddr), "ip");
	if(e == nil)
		(e, nil) = ndb.findbyattr(nil, "ether", ethertext1(hwaddr), "ip");
	if(e != nil)
		ipaddr := e.findfirst("ip");
	if(ipaddr == nil)
		return None;
	(ok, eipa) := IPaddr.parse(ipaddr);
	if(ok < 0 || !ipa.eq(eipa))
		return Bad;
	return Hit;
}

leasematch(a: ref Addr.Dynamic, hwaddr, clientid: array of byte): int
{
	if(clientid != nil && a.clientid != nil)
		return eq(clientid, a.clientid);
	return eq(hwaddr, a.hwaddr);
}

poolfindip(ipa: IPaddr): ref Addr.Dynamic
{
	for(i := 0; i < len pool; i++)
		if(pool[i].ip.eq(ipa))
			return pool[i];
	return nil;
}

poolfind(hwaddr, clientid: array of byte): ref Addr.Dynamic
{
	for(i := 0; i < len pool; i++)
		if(leasematch(pool[i], hwaddr, clientid))
			return pool[i];
	return nil;
}

poolnextfree(): ref Addr.Dynamic
{
	# we walk through the pool with pooloff.  if the next is leased,
	# try again from the start, but not before sorting longest unused to the front.
	now := daytime->now();
	if(leased(now, pool[pooloff])) {
		pooloff = 0;
		sort(pool, addrge);
	}
	if(leased(now, pool[pooloff]))
		return nil;
	return pool[pooloff++];
}

leased(now: int, a: ref Addr.Dynamic): int
{
	return a.leasetime != 0 && now <= a.leasestart+a.leasetime;
}

getlease(ipa: ref IPaddr, hwaddr, clientid: array of byte, otherok: int): ref Addr
{
	# check for fixed address
	hwip := etherip(hwaddr);
	if(hwip != nil)
		return ref Addr.Fixed (*hwip);

	# look for current/stale lease for this hwaddr/clientid first
	if(otherok) {
		a := poolfind(hwaddr, clientid);
		if(a != nil)
			return a;
	}

	# attempt to return the requested ip address
	if(ipa != nil) {
		now := daytime->now();
		a := poolfindip(*ipa);
		if(a != nil && (leasematch(a, hwaddr, clientid) || !leased(now, a)))
			return a;
		if(!otherok)
			return nil;
	}

	# return any address
	return poolnextfree();
}

clearlease(aa: ref Addr)
{
	pick a := aa {
	Dynamic =>
		a.leasetime = 0;
		writestatefile(a);
	}
}

putlease(aa: ref Addr, hwaddr, clientid: array of byte, leasetime: int, hostname: string)
{
	pick a := aa {
	Dynamic =>
		a.hwaddr = hwaddr;
		a.clientid = clientid;
		a.leasestart = daytime->now();
		a.leasetime = leasetime;
		a.hostname = hostname;
		writestatefile(a);
	}
}

findlease(ipa: IPaddr, hwaddr, clientid: array of byte): ref Addr
{
	match := etheripmatch(hwaddr, ipa);
	say(sprint("findlease, ip %s, hwaddr %s clientid %s, match %d (none,hit,bad)",
			ipa.text(), hex(hwaddr), hex(clientid), match));
	case match {
	Bad =>	return nil;
	None =>	break;
	Hit =>	return ref Addr.Fixed (ipa);
	}

	now := daytime->now();
	for(i := 0; i < len pool; i++) {
		a := pool[i];
		if(!a.ip.eq(ipa))
			continue;
		if(!leased(now, a) || leasematch(a, hwaddr, clientid))
			return a;
		break;
	}
	return nil;
}

ipopt(code: int, s: string): ref Opt
{
	(ok, ipa) := IPaddr.parse(s);
	if(ok < 0 || !ipa.isvalid() || !ipa.isv4()) {
		warn(sprint("bad config, code %d, ip %q", code, s));
		return nil;
	}
	return ref Opt (code, ipa.v4());
}

ipmaskopt(code: int, s: string): ref Opt
{
	(ok, ipa) := IPaddr.parsemask(s);
	if(ok < 0) {
		warn(sprint("bad config, code %d, ipmask %q", code, s));
		return nil;
	}
	return ref Opt (code, ipa.v4());
}

intopt(code: int, v: int): ref Opt
{
	buf := array[4] of byte;
	p32(buf, v);
	return ref Opt (code, buf);
}

Config: adt {
	opts:	list of ref Opt;
	bootf:	string;
	nextserver:	ref IPaddr;
	leasetime:	int;
};

getconfig(ipaddr: string, req: array of byte, leasetimes: int): ref Config
{
	rattrs: list of string;
	say(sprint("getconfig ipaddr %s", ipaddr));
	for(i := 0; i < len req; i++) {
		r := int req[i];
		say(sprint("getconfig r %d", r));
		if(r >= 0 && r < len optattrs && optattrs[r] != nil){
			say(sprint("getconfig r %d %s", r, optattrs[r]));
			rattrs = optattrs[r]::rattrs;
		}
	}
	leasetime0 := leasetime;
	if(leasetimes)
		rattrs = "leasetime"::rattrs;
	rattrs = "ipmask"::"bootf"::"nextserver"::rattrs;
	bootf: string;
	nextserver: ref IPaddr;

	# xxx for dns we should get all matches, not just a single dns server
	opts: list of ref Opt;
	(r, err) := ipval->findvals(ndb, ipaddr, rattrs);
	if(err != nil){
		say(sprint("getconfig ipval->findvals(ndb, ipaddr, rattrs) returns err %s", err));
		return nil;
	}
	for(; r != nil; r = tl r) {
		(k, v) := hd r;
		say(sprint("getconfig k %s v %s", k, v));
		if(v == nil){
			say(sprint("getconfig k %s v == nil\n", k));
			continue;
		}
		say(sprint("getconfig k %s v %s", k, v));
		o: ref Opt;
		case k {
		"sys" =>	o = ref Opt (dhcp->Ohostname, array of byte v);
		"ipmask" =>	o = ipmaskopt(dhcp->Osubnetmask, v);
		"ipgw" =>	o = ipopt(dhcp->Orouters, v);
		"dns" =>	o = ipopt(dhcp->Odns, v);
		"dnsdomain" =>	o = ref Opt (dhcp->Odomainname, array of byte v);
		"bootf" =>	bootf = v;
		"nextserver" =>
				(ok, ipa) := IPaddr.parse(v);
				if(ok >= 0 && ipa.isv4())
					nextserver = ref ipa;
		"tftp" =>	o = ref Opt (dhcp->Otftpservername, array of byte v);
		"leasetime" =>	leasetime0 = int v;
		}
		if(o != nil)
			opts = o::opts;
	}
	if(leasetimes) {
		if(leasetime0 <= 1)
			leasetime0 = leasetime;
		opts = intopt(dhcp->Oleasetime, leasetime0)::opts;
		opts = intopt(dhcp->Orenewaltime, 1*leasetime0/2)::opts;
		opts = intopt(dhcp->Orebindingtime, 7*leasetime0/8)::opts;
	}
	if(bootf == nil)
		nextserver = nil;
	opts = ref Opt (dhcp->Oserverid, siaddr.v4())::opts;
	return ref Config (opts, bootf, nextserver, leasetime0);
}


# client requests seeks new lease
dhcpdiscover(im, om: ref Dhcpmsg)
{
	if(!im.ciaddr.eq(ip->v4noaddr))
		return say("ignoring bad dhcp discover, ciaddr set");

	clientid := getoption(im, dhcp->Oclientid);
	reqip := getoptionip(im, dhcp->Oreqipaddr);
	a := getlease(reqip, im.chaddr, clientid, 1);
	if(a == nil)
		return warn("no address available, ignoring dhcp discover");

	paramreq := getoption(im, dhcp->Oparamreq);
	c := getconfig(a.ip.text(), paramreq, 1);
	om.file = c.bootf;
	if(c.nextserver != nil)
		om.siaddr = *c.nextserver;
	om.opts = c.opts;

	om.op = dhcp->Treply;
	om.yiaddr = a.ip;

	msgtype := ref Opt (dhcp->Odhcpmsgtype, array[] of {byte dhcp->TDoffer});
	om.opts = msgtype::om.opts;
}

# client wants an offered lease, renew an existing lease, or refresh an old lease (eg after reboot)
dhcprequest(im, om: ref Dhcpmsg)
{
	ipreq := getoptionip(im, dhcp->Oreqipaddr);
	clientid := getoption(im, dhcp->Oclientid);
	a: ref Addr;
	if(im.ciaddr.eq(ip->v4noaddr)) {
		if(ipreq == nil)
			return say("ignoring bad dhcp request, missing 'requested ip address'");
		a = getlease(ipreq, im.chaddr, clientid, 0);
	} else {
		serverid := getoption(im, dhcp->Oserverid);
		if(serverid != nil)
			return say("ignoring bad dhcp request, renew lease, but 'server identifier' present");
		if(ipreq != nil)
			say("ignoring bad dhcp request, 'requested ip address' present for renewing");
		else
			a = findlease(im.ciaddr, im.chaddr, clientid);
	}
	if(a == nil) {
		om.op = dhcp->Treply;
		msgtype := ref Opt (dhcp->Odhcpmsgtype, array[] of {byte dhcp->TDnak});
		om.opts = msgtype::om.opts;
		return;
	}
	paramreq := getoption(im, dhcp->Oparamreq);
	c := getconfig(a.ip.text(), paramreq, 1);
	om.file = c.bootf;
	if(c.nextserver != nil)
		om.siaddr = *c.nextserver;
	om.opts = c.opts;

	om.op = dhcp->Treply;
	om.yiaddr = a.ip;
	msgtype := ref Opt (dhcp->Odhcpmsgtype, array[] of {byte dhcp->TDack});
	om.opts = msgtype::om.opts;

	hostnamebuf := getoption(im, dhcp->Ohostname);
	if(hostnamebuf != nil)
		hostname := string hostnamebuf;
	putlease(a, im.chaddr, clientid, c.leasetime, hostname);
}

# client rejects offered lease
dhcpdecline(im, nil: ref Dhcpmsg)
{
	if(!im.ciaddr.eq(ip->v4noaddr))
		return say("ignoring bad dhcp decline, ciaddr set");
	if(!im.yiaddr.eq(ip->v4noaddr))
		return say("ignoring bad dhcp decline, yiaddr set");

	serverid := getoption(im, dhcp->Oserverid);
	if(serverid == nil)
		return say("ignoring bad dhcp decline, missing 'server identifier'");
	reqip := getoptionip(im, dhcp->Oreqipaddr);
	if(reqip == nil)
		return say("ignoring bad dhcp decline, missing 'requested ip address'");
	#clientid := getoption(im, dhcp->Oclientid);

	say(sprint("client declined %s", (*reqip).text()));
}

# client gives back lease
dhcprelease(im, nil: ref Dhcpmsg)
{
	if(im.ciaddr.eq(ip->v4noaddr))
		return say("ignoring bad dhcp release, ciaddr not set");
	serverid := getoption(im, dhcp->Oserverid);
	if(serverid == nil)
		return say("ignoring bad dhcp release, missing 'server identifier'");
	if(getoption(im, dhcp->Oreqipaddr) != nil)
		return say("ignoring bad dhcp release, bogus 'requested ip address' present");

	clientid := getoption(im, dhcp->Oclientid);
	a := findlease(im.ciaddr, im.chaddr, clientid);
	if(a == nil)
		return say("bogus dhcp release, ignoring");
	clearlease(a);
}

# client has address configured (ciaddr), and just wants config parameters.
# we respond with a dhcp ack similar to dhcprequest, but without:
# - checking the address
# - filling yiaddr
# - sending lease time parameters
dhcpinform(im, om: ref Dhcpmsg)
{
	if(im.ciaddr.eq(ip->v4noaddr))
		return say("ignoring bad dhcp inform, ciaddr not set");
	if(getoption(im, dhcp->Oreqipaddr) != nil)
		return say("ignoring bad dhcp inform, bogus 'requested ip address' present");
	if(getoption(im, dhcp->Oserverid) != nil)
		return say("ignoring bad dhcp inform, bogus 'server identifier' present");
	if(getoption(im, dhcp->Oleasetime) != nil)
		return say("ignoring bad dhcp inform, bogus 'lease time' present");

	paramreq := getoption(im, dhcp->Oparamreq);
	c := getconfig(im.ciaddr.text(), paramreq, 0);
	om.file = c.bootf;
	om.opts = c.opts;
	om.op = dhcp->Treply;
	msgtype := ref Opt (dhcp->Odhcpmsgtype, array[] of {byte dhcp->TDack});
	om.opts = msgtype::om.opts;
	# xxx should unicast the response, not broadcast
}

dhcpsrv(td: int, im: ref Dhcpmsg): ref Dhcpmsg
{
	om := ref *im;
	om.op = ~0;
	om.ciaddr = om.yiaddr = om.giaddr = ip->v4noaddr;
	om.siaddr = siaddr;
	om.chaddr = im.chaddr;
	om.sname = nil;
	om.file = nil;
	om.options = array[4] of byte;
	p32(om.options, dhcp->Moptions);
	om.opts = nil;
	case td {
	dhcp->TDdiscover =>	dhcpdiscover(im, om);
	dhcp->TDrequest =>	dhcprequest(im, om);
	dhcp->TDdecline =>	dhcpdecline(im, om);
	dhcp->TDrelease =>	dhcprelease(im, om);
	dhcp->TDinform =>	dhcpinform(im, om);
	dhcp->TDoffer =>	say("bad, dhcp offer to server port");
	dhcp->TDack =>		say("bad, dhcp ack to server port");
	dhcp->TDnak =>		say("bad, dhcp nak to server port");
	* =>			say(sprint("unrecognized dhcp message type %d", td));
	}
	if(om.op == ~0)
		return nil;
	om.opts = lists->reverse(ref Opt (dhcp->Oend, nil)::om.opts);
	return om;
}

readfile(name: string): string
{
	fd := sys->open(name, Sys->OREAD);
	buf := array[256] of byte;
	n := sys->read(fd, buf, len buf);
	if(n <= 0)
		return nil;
	return string buf[0:n];
}

writefile(name, s: string): string
{
	buf := array of byte s;
	fd := sys->create(name, Sys->OWRITE|Sys->OTRUNC, 8r666);
	if(fd == nil || sys->write(fd, buf, len buf) != len buf)
		return sprint("%r");
	return nil;
}


eq(a, b: array of byte): int
{
	if(len a != len b)
		return 0;
	for(i := 0; i < len a; i++)
		if(a[i] != b[i])
			return 0;
	return 1;
}

ipcmp(ipa, ipb: IPaddr): int
{
	a := ipa.v6();
	b := ipb.v6();
	for(i := 0; i < len a; i++)
		if(a[i] != b[i])
			return int a[i]-int b[i];
	return 0;
}

g32(d: array of byte): int
{
	v := 0;
	v |= int d[0]<<24;
	v |= int d[1]<<16;
	v |= int d[2]<<8;
	v |= int d[3]<<0;
	return v;
}

g16(d: array of byte): int
{
	v := 0;
	v |= int d[2]<<8;
	v |= int d[3]<<0;
	return v;
}

p32(d: array of byte, v: int): int
{
	d[0] = byte (v>>24);
	d[1] = byte (v>>16);
	d[2] = byte (v>>8);
	d[3] = byte (v>>0);
	return 4;
}

p16(d: array of byte, v: int): int
{
	d[0] = byte (v>>8);
	d[1] = byte (v>>0);
	return 2;
}


hex(d: array of byte): string
{
	if(d == nil)
		return "";
	return base16->enc(d);
}

sort[T](a: array of T, ge: ref fn(a, b: T): int)
{
	for(i := 1; i < len a; i++) {
		tmp := a[i];
		for(j := i; j > 0 && ge(a[j-1], tmp); j--)
			a[j] = a[j-1];
		a[j] = tmp;
	}
}

l2a[T](l: list of T): array of T
{
	a := array[len l] of T;
	i := 0;
	for(; l != nil; l = tl l)
		a[i++] = hd l;
	return a;
}

say(s: string)
{
	if(dflag)
		warn(s);
}

warn(s: string)
{
	sys->fprint(sys->fildes(2), "%s\n", s);
}

fail(s: string)
{
	warn(s);
	raise "fail:"+s;
}
