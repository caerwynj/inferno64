OEBpackage: module {
	PATH:	con "/dis/ebook/oebpackage.dis";

	Package: adt {
		file:	string;
		uniqueid:	string;
		version:	string;				# package version ("1.0", "2.0", etc.)
		meta:	list of (string, Xml->Attributes, string);	# dublin-core metadata
		manifest:	list of ref Item;			# all items in the ebook
		spine:	list of ref Item;			# reading order
		guide:	list of ref Reference;
		toc:	string;					# id of NCX toc item (EPUB 2)
		ncxfile:	string;				# resolved path to NCX file

		getmeta:	fn(p: self ref Package, n: string): list of (Xml->Attributes, string);
		locate:	fn(p: self ref Package): int;
	};

	Item: adt {
		id:	string;
		# can we assume that the href doesn't end in #idref?
		href: string;
		mediatype:	string;
		fallback: cyclic ref Item;
		file:	string;	# local file name
		missing:	string;	# if it's missing, why
	};

	Reference: adt {
		sort:	string;		# XXX what's this?
		title:	string;
		href:	string;
	};

	init:	fn(xml: Xml);
	open:	fn(f: string, warnings: chan of (Xml->Locator,string)): (ref Package, string);
};
