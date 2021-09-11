implement Netaddr;

include "sys.m";
	sys: Sys;
	read, write: import sys;

include "draw.m";

include "ip.m";
	ip: IP;
	IPaddr: import ip;

# objective: 
#	input: addr/mask or addr mask
#	output: addr & mask
#% ./netaddr.dis 127.0.0.8 /104
#127.0.0.0
#% ./netaddr.dis 127.0.0.8/104
#127.0.0.0
#% ./netaddr.dis 127.0.0.8 255.255.0.0
#127.0.0.0
Netaddr: module
{
	init:	fn(nil: ref Draw->Context, nil: list of string);
};

usage()
{
	sys->fprint(sys->fildes(2), "Usage: netaddr (addr mask | addr/mask)\n");
	raise "fail:usage";
}

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	ip = load IP IP->PATH;

#	for(as:=args; as != nil; as = tl as){
#		sys->print("arg %s\n", hd as);
#	}
	if(len args < 2 || len args > 3)
		usage();
	args = tl args;

	ip->init();
	if(len args == 1){
		cidraddr := hd args;
		(e,ipa, ipm) := IPaddr.parsecidr(cidraddr);
		if(e != 0){
			sys->fprint(sys->fildes(2), "netaddr: parsecidr cidraddr %s: %r\n", cidraddr);
			raise "fail: parsecidr %r";
		}
		output(ipa,ipm);
	}else{
		addr := hd args;
		mask := hd tl args;
		(e,ipa) := IPaddr.parse(addr);
		if(e != 0){
			sys->fprint(sys->fildes(2), "netaddr: parse addr %s: %r\n", addr);
			raise "fail: parse %r";
		}
		(em,ipm) := IPaddr.parsemask(mask);
		if(em != 0){
			sys->fprint(sys->fildes(2), "netaddr: parse mask %s: %r\n", mask);
			raise "fail: parse %r";
		}
		output(ipa,ipm);
	}
}
output(ipa: IPaddr, ipm: IPaddr)
{
#		sys->print("ip %s mask %s\n", ipa.text(), ipm.text());
		o := ipa.mask(ipm);
		sys->print("%s\n", o.text());
}
