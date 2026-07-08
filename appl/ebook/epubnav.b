implement Epubnav;

include "sys.m";
	sys: Sys;

include "draw.m";

include "bufio.m";

include "xml.m";
	xml: Xml;
	Attributes, Locator, Parser, Item: import xml;

include "epubnav.m";

init(xmlmod: Xml)
{
	sys = load Sys Sys->PATH;
	xml = xmlmod;
}

# parse an NCX file and return a flat list of NavPoints in reading order.
# NCX structure:
#   <ncx><navMap>
#     <navPoint id="..." playOrder="...">
#       <navLabel><text>Chapter Title</text></navLabel>
#       <content src="chapter.xhtml"/>
#       <navPoint>...nested...</navPoint>
#     </navPoint>
#   </navMap></ncx>
parse(f: string, warnings: chan of (Xml->Locator, string)): (list of ref NavPoint, string)
{
	(x, err) := xml->open(f, warnings, nil);
	if(x == nil)
		return (nil, "cannot open NCX: " + err);

	# find <navMap>
	while((xi := x.next()) != nil){
		pick t := xi {
		Tag =>
			if(t.name == "navMap"){
				points := parsenavmap(x);
				return (points, nil);
			}
		}
	}
	return (nil, "no navMap found in NCX");
}

# parse children of <navMap> or nested <navPoint>, returning flat list
parsenavmap(x: ref Parser): list of ref NavPoint
{
	result: list of ref NavPoint;
	x.down();
	while((xi := x.next()) != nil){
		pick t := xi {
		Tag =>
			if(t.name == "navPoint"){
				(label, href, children) := parsenavpoint(x);
				if(label != nil || href != nil)
					result = ref NavPoint(label, href) :: result;
				# flatten nested points after parent
				for(; children != nil; children = tl children)
					result = hd children :: result;
			}
		}
	}
	x.up();
	# reverse to get reading order
	rev: list of ref NavPoint;
	for(; result != nil; result = tl result)
		rev = hd result :: rev;
	return rev;
}

# parse a single <navPoint> element
parsenavpoint(x: ref Parser): (string, string, list of ref NavPoint)
{
	label := "";
	href := "";
	children: list of ref NavPoint;
	x.down();
	while((xi := x.next()) != nil){
		pick t := xi {
		Tag =>
			case t.name {
			"navLabel" =>
				label = parselabel(x);
			"content" =>
				href = t.attrs.get("src");
				if(href == nil)
					href = "";
			"navPoint" =>
				(clabel, chref, grandchildren) := parsenavpoint(x);
				if(clabel != nil || chref != nil)
					children = ref NavPoint(clabel, chref) :: children;
				for(; grandchildren != nil; grandchildren = tl grandchildren)
					children = hd grandchildren :: children;
			}
		}
	}
	x.up();
	# reverse children to reading order
	rev: list of ref NavPoint;
	for(; children != nil; children = tl children)
		rev = hd children :: rev;
	return (label, href, rev);
}

# parse <navLabel><text>...</text></navLabel>
parselabel(x: ref Parser): string
{
	s := "";
	x.down();
	while((xi := x.next()) != nil){
		pick t := xi {
		Tag =>
			if(t.name == "text"){
				x.down();
				while((xi2 := x.next()) != nil){
					pick t2 := xi2 {
					Text =>
						s = t2.ch;
					}
				}
				x.up();
			}
		}
	}
	x.up();
	return s;
}
