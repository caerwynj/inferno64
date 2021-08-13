implement Dhcpserver;

include "sys.m";
	sys: Sys;
	sprint: import sys;
include "ip.m";
	ip: IP;
	IPaddr: import ip;
include "encoding.m";
	base16: Encoding;
include "lists.m";
	lists: Lists;
include "ether.m";
	ether: Ether;
include "dhcpd.m";

debug: con 0;

tdnames := array[] of {
	nil, "discover", "offer", "request", "decline", "ack", "nak", "release", "inform",
};

# option value types, for converting to text
OTstr, OTips, OTint16, OTint32, OTother: con iota;
optstring := array[] of {
	Ohostname, Odomainname, Orootpath, Omessage, Otftpservername, Obootfile,
};
optips := array[] of {
	Osubnetmask, Orouters, Odns, Obroadcast, Oreqipaddr, Oserverid,
};
optint16 := array[] of {
	Omaxmsgsize,
};
optint32 := array[] of {
	Oleasetime, Orenewaltime, Orebindingtime,
};

optnames := array[] of {
Opad		=> "pad",
Oend		=> "end",
Osubnetmask	=> "ipmask",
Orouters	=> "ipgw",
Odns		=> "dns",
Ohostname	=> "sys",
Odomainname	=> "dnsdomain",
Orootpath	=> "rootpath",
Obroadcast	=> "ipbroadcast",

Oreqipaddr	=> "reqipaddr",
Oleasetime	=> "leasetime",
Ooptionoverload => "optionoverload",
Odhcpmsgtype	=> "dhcpmsgtype",
Oserverid	=> "serverid",
Oparamreq	=> "paramreq",
Omessage	=> "message",
Omaxmsgsize	=> "maxmsgsize",
Orenewaltime	=> "renewaltime",
Orebindingtime	=> "rebindingtime",
Ovendorclass	=> "vendorclass",
Oclientid	=> "clientid",
Otftpservername => "tftp",
Obootfile	=> "bootf",
};


init()
{
	sys = load Sys Sys->PATH;
	ip = load IP IP->PATH;
	ip->init();
	base16 = load Encoding Encoding->BASE16PATH;
	lists = load Lists Lists->PATH;
	ether = load Ether Ether->PATH;
	ether->init();
}

optsparse(d: array of byte): list of ref Opt
{
	if(g32(d, 0).t0 != Moptions)
		return nil;

	l: list of ref Opt;
	o := 4;
	while(o < len d) {
		code := int d[o++];
		if(code == Oend)
			break;
		if(code == Opad)
			continue;
		if(o >= len d) {
			say("bad options, length outside packet");
			return nil;
		}
		n := int d[o++];
		if(o+n > len d) {
			say("bad options, value outside packet");
			return nil;
		}
		l = ref Opt(code, d[o:o+n])::l;
		o += n;
	}
	return lists->reverse(l);
}

optssize(l: list of ref Opt): int
{
	o := 4;
	for(; l != nil; l = tl l)
		case (hd l).code {
		Opad or
		Oend =>
			o += 1;
		* =>
			o += 1+1+len (hd l).v;
		}
	return o;
}

optspack(l: list of ref Opt, buf: array of byte)
{
	if(l == nil)
		return;

	o := 0;
	o = p32(buf, o, Moptions);
	for(; l != nil; l = tl l) {
		opt := hd l;
		if(o >= len buf)
			return warn("response options too long (code)");
		buf[o++] = byte opt.code;
		if(opt.code == Opad)
			continue;
		if(opt.code == Oend) {
			if(len l != 1)
				raise "option 'end' not last";
			break;
		}

		if(o+1+len opt.v > len buf)
			return warn("response options too long (len/value)");
		buf[o++] = byte len opt.v;
		buf[o:] = opt.v;
		o += len opt.v;
	}
}

optname(code: int): string
{
	if(code >= 0 && code < len optnames)
		s := optnames[code];
	if(s == nil)
		s = string code;
	return s;
}

has(a: array of int, v: int): int
{
	for(i := 0; i < len a; i++)
		if(a[i] == v)
			return 1;
	return 0;
}

opttype(code: int): int
{
	if(has(optstring, code))
		return OTstr;
	if(has(optips, code))
		return OTips;
	if(has(optint16, code))
		return OTint16;
	if(has(optint32, code))
		return OTint32;
	return OTother;
}

optstext(l: list of ref Opt): string
{
	s := "";
	for(; l != nil; l = tl l) {
		o := hd l;
		s += "\t\t"+optname(o.code);
		if(o.v == nil) {
			s += "\n";
			continue;
		}
		s += "=";
		ot := opttype(o.code);
		if(o.code == Odhcpmsgtype && len o.v == 1 && (t := int o.v[0]) >= 0 && t < len tdnames && tdnames[t] != nil) {
			s += sprint("%s", tdnames[t]);
		} else if(ot == OTstr) {
			s += sprint("\"%s\"", string o.v);
		} else if(ot == OTips && len o.v % 4 == 0) {
			v := o.v;
			ips := "";
			while(len v >= 4) {
				ips += ","+IPaddr.newv4(v[:4]).text();
				v = v[4:];
			}
			if(ips != nil)
				ips = ips[1:];
			s += sprint("%s", ips);
		} else if(ot == OTint16 && len o.v == 2) {
			s += sprint("%d", g16(o.v, 0).t0);
		} else if(ot == OTint32 && len o.v == 4) {
			s += sprint("%d", g32(o.v, 0).t0);
		} else {
			s += sprint("'%s'", base16->enc(o.v));
		}
		s += "\n";
	}
	return s;
}

Dhcpmsg.unpack(buf: array of byte): (ref Dhcpmsg, string)
{
	if(len buf < Minmsglen)
		return (nil, sprint("too short, %d < minimum %d", len buf, Minmsglen));

	m := ref Dhcpmsg;
	o := 0;
	m.op = int buf[o++];
	m.htype = int buf[o++];
	m.hlen = int buf[o++];
	if(m.hlen > 16)
		return (nil, sprint("bad hlen %d", m.hlen));
	m.hops = int buf[o++];
	(m.xid, o) = g32(buf, o);
	(m.secs, o) = g16(buf, o);
	(m.flags, o) = g16(buf, o);
	m.ciaddr = IPaddr.newv4(buf[o:o+4]);
	o += 4;
	m.yiaddr = IPaddr.newv4(buf[o:o+4]);
	o += 4;
	m.siaddr = IPaddr.newv4(buf[o:o+4]);
	o += 4;
	m.giaddr = IPaddr.newv4(buf[o:o+4]);
	o += 4;
	m.chaddr = buf[o:o+m.hlen];
	o += 16;
	m.sname = cstr(buf[o:o+64]);
	o += 64;
	m.file = cstr(buf[o:o+128]);
	o += 128;
	m.options = buf[o:];
	m.opts = optsparse(m.options);
	return (m, nil);
}

Dhcpmsg.pack(m: self ref Dhcpmsg): array of byte
{
	size := 7*4+16+64+128;

	# for dhcp, no minimum length.  bootp needs 64 bytes options.
	optsize := len m.options;
	if(len m.options >= 4 && g32(m.options, 0).t0 == Moptions)
		optsize = optssize(m.opts);
	if(0 && optsize < 64)
		optsize = 64;
	size += optsize;

	buf := array[size] of {* => byte 0};
	o := 0;
	buf[o++] = byte m.op;
	buf[o++] = byte m.htype;
	buf[o++] = byte m.hlen;
	buf[o++] = byte m.hops;
	o = p32(buf, o, m.xid);
	o = p16(buf, o, m.secs);
	o = p16(buf, o, m.flags);
	o = pbuf(buf, o, m.ciaddr.v4());
	o = pbuf(buf, o, m.yiaddr.v4());
	o = pbuf(buf, o, m.siaddr.v4());
	o = pbuf(buf, o, m.giaddr.v4());
	buf[o:] = m.chaddr;
	o += 16;
	buf[o:] = array of byte m.sname;
	o += 64;
	buf[o:] = array of byte m.file;
	o += 128;
	if(len m.options >= 4 && g32(m.options, 0).t0 == Moptions)
		optspack(m.opts, buf[o:]);
	else if(m.options != nil)
		buf[o:] = m.options;
	return buf;
}

Dhcpmsg.text(m: self ref Dhcpmsg): string
{
	s := "Dhcpmsg(\n";
	s += sprint("	op=%d\n", int m.op);
	s += sprint("	htype=%d\n", m.htype);
	s += sprint("	hlen=%d\n", m.hlen);
	s += sprint("	hops=%d\n", m.hops);
	s += sprint("	xid=%ud\n", m.xid);
	s += sprint("	secs=%ud\n", m.secs);
	s += sprint("	ciaddr=%s\n", m.ciaddr.text());
	s += sprint("	yiaddr=%s\n", m.yiaddr.text());
	s += sprint("	siaddr=%s\n", m.siaddr.text());
	s += sprint("	giaddr=%s\n", m.giaddr.text());
	s += sprint("	hwaddr=%q\n", ether->text(m.chaddr));
	s += sprint("	sname=%q\n", m.sname);
	s += sprint("	file=%q\n", m.file);
	if(len m.options >= 4) {
		magic := g32(m.options, 0).t0;
		s += sprint("	magic=%#ux\n", magic);
		if(magic == Moptions) {
			s += "\toptions=(\n";
			s += optstext(m.opts);
			s += "\t)\n";
		} else if (magic == Mp9)
			s += sprint("\toptions=%q\n", cstr(m.options[4:]));
	}
	s += ")";
	return s;
}

cstr(buf: array of byte): string
{
	for(i := 0; i < len buf; i++)
		if(buf[i] == byte 0)
			break;
	return string buf[:i];
}

g32(d: array of byte, o: int): (int, int)
{
	v := 0;
	v |= int d[o++]<<24;
	v |= int d[o++]<<16;
	v |= int d[o++]<<8;
	v |= int d[o++]<<0;
	return (v, o);
}

g16(d: array of byte, o: int): (int, int)
{
	v := 0;
	v |= int d[o++]<<8;
	v |= int d[o++]<<0;
	return (v, o);
}

p32(d: array of byte, o: int, v: int): int
{
	d[o++] = byte (v>>24);
	d[o++] = byte (v>>16);
	d[o++] = byte (v>>8);
	d[o++] = byte (v>>0);
	return o;
}

p16(d: array of byte, o: int, v: int): int
{
	d[o++] = byte (v>>8);
	d[o++] = byte (v>>0);
	return o;
}

pbuf(d: array of byte, o: int, buf: array of byte): int
{
	d[o:] = buf;
	return o+len buf;
}

warn(s: string)
{
	say(s);
}

say(s: string)
{
	if(debug)
		sys->fprint(sys->fildes(2), "%s\n", s);
}
