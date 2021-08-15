Dhcpserver: module
{
	PATH:	con "/dis/lib/dhcpserver.dis";

	init:	fn();

	Minmsglen:	con 7*8+16+64+128;  # dhcp clients may have no options

	# flags
	Fbroadcast:	con 1<<15;

	Mp9:		con 16r70392020; # "p9  "
	Moptions:	con 16r63825363; # rfc2132

	# bootp/dhcp
	Opad:	con 0;
	Oend:	con 255;
	Osubnetmask:	con 1;
	Orouters:	con 3;
	Odns:		con 6;
	Ohostname:	con 12;
	Odomainname:	con 15;
	Orootpath:	con 17;
	Obroadcast:	con 28;
	# dhcp only
	Oreqipaddr,
	Oleasetime,
	Ooptionoverload,
	Odhcpmsgtype,
	Oserverid,
	Oparamreq,
	Omessage,
	Omaxmsgsize,
	Orenewaltime,
	Orebindingtime,
	Ovendorclass,
	Oclientid:	con 50+iota;
	Otftpservername,
	Obootfile:	con 66+iota;

	Trequest, Treply: con 1+iota;
	TDdiscover, TDoffer, TDrequest, TDdecline, TDack, TDnak, TDrelease, TDinform: con 1+iota;

	Opt: adt {
		code:	int;
		v:	array of byte;
	};

	Dhcpmsg: adt
	{
		op:	int;
		htype:	int;
		hlen:	int;
		hops:	int;
		xid:	int;
		secs:	int;
		flags:	int;
		ciaddr:	IPaddr;
		yiaddr:	IPaddr;
		siaddr:	IPaddr;
		giaddr:	IPaddr;
		chaddr:	array of byte;
		sname:	string;
		file:	string;
		options:	array of byte;
		opts:	list of ref Opt;

		unpack:	fn(a: array of byte): (ref Dhcpmsg, string);
		pack:	fn(bp: self ref Dhcpmsg): array of byte;
		text:	fn(bp: self ref Dhcpmsg): string;
	};
};
