Zip: module
{
	PATH:	con "/dis/lib/zip.dis";

	dflag:	int;
	init:	fn(): string;

	# compression methods.  only plain & deflate supported.
	Mplain,
	Mshrunk,
	Mreduced1, Mreduced2, Mreduced3, Mreduced4,
	Mimplode, Mtokenize,
	Mdeflate, Mdeflate64,
	Mpkwareimplode,
	Mreserved0,
	Mbzip2,
	Mreserved1,
	Mlzma:		con iota+0;
	Mibmterse,
	Mlz77z:		con iota+18;
	Mwavpack,
	Mppmdi1:	con iota+97;

	# general purpose flags
	Fencrypted:		con 1<<0;
	Flocaldatadescr:	con 1<<3;  # crc & sizes in fhdr are 0, use "data descriptor" following fhdr
	Fcompressedpatched:	con 1<<5;
	Fstrongcrypto:		con 1<<6;
	Futf8:			con 1<<11;
	Fcdirencrypted:		con 1<<13;

	# internal file attributes
	IFArecord:	con 1<<1;

	Version: con 20;	# supported for reading

	Extra: adt {
		l:	list of ref (int, array of byte);

		parse:	fn(d: array of byte): (ref Extra, string);
		pack:	fn(e: self ref Extra): array of byte;
		text:	fn(e: self ref Extra): string;
	};

	Fhdr: adt {
		versneeded:	int;
		flags:		int;
		comprmethod:	int;
		filemtime:	int;
		filemdate:	int;
		mtime:		int;  # not in file, unix epoch mtime based on filemtime & filemdate
		crc32:		big;
		comprsize:	big;
		uncomprsize:	big;
		filename:	string;
		extra:		ref Extra;
		dataoff:	big;  # not in file

		mk:	fn(f: ref CDFhdr): ref Fhdr;
		parse:	fn(buf: array of byte, off: big): (ref Fhdr, string);
		read:	fn(fd: ref Sys->FD, off: big): (ref Fhdr, string);
		pack:	fn(f: self ref Fhdr): array of byte;
		text:	fn(f: self ref Fhdr): string;
	};

	CDFhdr: adt {
		versmadeby:	int;
		versneeded:	int;
		flags:		int;
		comprmethod:	int;
		filemtime:	int;
		filemdate:	int;
		mtime:		int;  # not in file, unix epoch mtime based on filemtime & filemdate
		crc32:		big;
		comprsize:	big;
		uncomprsize:	big;
		filename:	string;
		extra:		ref Extra;
		comment:	string;
		disknrstart:	int;
		intattr:	int;
		extattr:	big;
		reloffset:	big;

		mk:	fn(f: ref Fhdr, off: big): ref CDFhdr;
		parse:	fn(buf: array of byte): (ref CDFhdr, string);
		read:	fn(b: ref Bufio->Iobuf): (ref CDFhdr, string);
		pack:	fn(f: self ref CDFhdr): array of byte;
		text:	fn(f: self ref CDFhdr): string;
	};

	Endofcdir: adt {
		disknr:		int;
		diskcdir:	int;
		diskcdirentries:	int;
		cdirentries:	int;
		cdirsize:	big;
		cdiroffset:	big;
		comment:	array of byte;

		parse:	fn(buf: array of byte): (ref Endofcdir, string);
		pack:	fn(e: self ref Endofcdir): array of byte;
		text:	fn(e: self ref Endofcdir): string;
	};

	comprmethod:	fn(m: int): string;
	open:		fn(fd: ref Sys->FD): (ref Endofcdir, array of ref CDFhdr, string);
	openfile:	fn(fd: ref Sys->FD, f: ref CDFhdr): (ref Sys->FD, ref Fhdr, string);
	readfhdr:	fn(fd: ref Sys->FD, f: ref CDFhdr): (ref Fhdr, string);
	pread:		fn(fd: ref Sys->FD, f: ref Fhdr, buf: array of byte, n: int, off: big): int;
	sanitizepath:	fn(s: string): string;
	crc32:		fn(crc: int, buf: array of byte): int;
};
