Epubcontainer: module {
	PATH:	con "/dis/ebook/epubcontainer.dis";

	init:	fn(xmlmod: Xml): string;
	open:	fn(f: string, warnings: chan of (Xml->Locator, string)): (string, string);
		# returns (opf path, error)
	parsecontainer: fn(f: string, warnings: chan of (Xml->Locator, string)): (string, string);
	close:	fn();
};
