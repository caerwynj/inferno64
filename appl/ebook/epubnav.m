Epubnav: module {
	PATH:	con "/dis/ebook/epubnav.dis";

	NavPoint: adt {
		label:	string;
		href:	string;
	};

	init:	fn(xmlmod: Xml);
	parse:	fn(f: string, warnings: chan of (Xml->Locator, string)): (list of ref NavPoint, string);
};
