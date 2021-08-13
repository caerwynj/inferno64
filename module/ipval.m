Ipval: module
{
	PATH:	con "/dis/lib/ipval.dis";

	findval:	fn(db: ref Attrdb->Db, ipaddr: string, rattr: string): (string, string);
	findvals:	fn(db: ref Attrdb->Db, ipaddr: string, rattrs: list of string): (list of (string, string), string);
};
