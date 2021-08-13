implement Ipval;

include "sys.m";
	sys: Sys;
	sprint: import sys;
include "bufio.m";
include "ip.m";
	ip: IP;
	IPaddr: import ip;
include "attrdb.m";
	attrdb: Attrdb;
	Db, Dbptr, Dbentry: import attrdb;
include "ipval.m";


init()
{
	if(sys != nil)
		return;

	sys = load Sys Sys->PATH;
	ip = load IP IP->PATH;
	ip->init();
	attrdb = load Attrdb Attrdb->PATH;
	attrdb->init();
	Db.open("/dev/null");  # force bufio to load...
}

findval(db: ref Db, ipaddr: string, rattr: string): (string, string)
{
	init();

	(l, err) := findvals(db, ipaddr, rattr::nil);
	v: string;
	if(err == nil && len l == 1)
		v = (hd l).t1;
	return (v, err);
}

has(l: list of (string, string), k: string): int
{
	for(; l != nil; l = tl l)
		if((hd l).t0 == k)
			return 1;
	return 0;
}

dbipval(db: ref Db, ipaddr: string, attr: string): string
{
	(e, nil) := db.findbyattr(nil, "ip", ipaddr, attr);
	if(e != nil)
		v := e.findfirst(attr);
	return v;
}

dbipnetmatch(e: ref Dbentry, ipa: IPaddr): array of byte
{
	eipaddr := e.findfirst("ip");
	eipmask := e.findfirst("ipmask");
	(ok0, eipa) := IPaddr.parse(eipaddr);
	(ok1, eipm) := IPaddr.parsemask(eipmask);
	if(ok0 < 0 || ok1 < 0)
		return nil;
	if(!ipa.mask(eipm).eq(eipa))
		return nil;
	return eipm.v6();
}

# compare the mask.  a >= b when a's mask is less specific than b's:  when the first different byte of the mask has a lower value.
# if the masks are the same, we use the position in the ndb file.
v6maskge(a, b: ref (int, array of byte, ref Dbentry)): int
{
	ma := a.t1;
	mb := b.t1;

	for(i := 0; i < len ma; i++)
		if(ma[i] != mb[i])
			return ma[i] <= mb[i];
	return a.t0 >= b.t0;
}

dbipnets(db: ref Db, ipaddr: string): array of ref Dbentry
{
	l: list of ref (int, array of byte, ref Dbentry);  # seq, v6 mask, db entry

	(ok, ipa) := IPaddr.parse(ipaddr);
	if(ok < 0)
		return nil;

	next: ref Dbptr;
	seq := 0;
	for(;;) {
		e: ref Dbentry;
		(e, next) = db.find(next, "ipnet");
		if(e != nil) {
			v6m := dbipnetmatch(e, ipa);
			if(v6m != nil)
				l = ref (seq++, v6m, e)::l;
		}
		if(e == nil || next == nil)
			break;
	}

	# use seq & v6 mask to sort, then extract db entries
	a := l2a(l);
	sort(a, v6maskge);
	r := array[len a] of ref Dbentry;
	for(i := 0; i < len a; i++)
		r[i] = a[i].t2;
	return r;
}

findvals(db: ref Db, ipaddr: string, rattrs: list of string): (list of (string, string), string)
{
	init();

	r: list of (string, string);

	# first look for explict matches to ip address
	for(l := rattrs; l != nil; l = tl l) {
		v := dbipval(db, ipaddr, hd l);
		if(v != nil)
			r = (hd l, v)::r;
	}

	# take remaining attributes from matching ipnet entries
	ipn := dbipnets(db, ipaddr);
	for(i := 0; len r < len rattrs && i < len ipn; i++) {
		dbe := ipn[i];
		for(l = rattrs; l != nil; l = tl l) {
			v := dbe.findfirst(hd l);
			if(v != nil && !has(r, hd l))
				r = (hd l, v)::r;
		}
	}

	return (r, nil);
}

l2a[T](l: list of T): array of T
{
	a := array[len l] of T;
	i := 0;
	for(; l != nil; l = tl l)
		a[i++] = hd l;
	return a;
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
