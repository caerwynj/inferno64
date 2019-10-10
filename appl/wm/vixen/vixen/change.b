Mod: adt {
	o: int;
	p: Pos;
	s: string;
	pick {
	Ins or
	Del =>
		# o & p are for start of change
	}

	invert:	fn(m: self ref Mod): ref Mod;
	text:	fn(m: self ref Mod): string;
};

Change: adt {
	inverted:	int;  # whether this is inverted.  significant for cursor position after applying
	l:	list of ref Mod;  # hd of list is last modification (also at later positions in file)
	ogen, ngen:	big;  # gen before and after this change

	beginpos:	fn(c: self ref Change): Pos;
	invert:		fn(c: self ref Change): ref Change;
	text:		fn(c: self ref Change): string;
};


Mod.invert(mm: self ref Mod): ref Mod
{
	pick m := mm {
	Ins =>	return ref Mod.Del (m.o, m.p, m.s);
	Del =>	return ref Mod.Ins (m.o, m.p, m.s);
	}
}

modtags := array[] of {"Ins", "Del"};
Mod.text(mm: self ref Mod): string
{
	s := sprint("Mod.%s(", modtags[tagof mm]);
	pick m := mm {
	Ins =>	s += sprint("o=%d, p=%s, s=%q", m.o, m.p.text(), m.s);
	Del =>	s += sprint("o=%d, p=%s, s=%q", m.o, m.p.text(), m.s);
	}
	s += ")";
	return s;
}

Change.beginpos(c: self ref Change): Pos
{
	if(c.inverted)
		m := hd c.l;
	else
		m = hd rev(c.l);
	return m.p;
}

Change.invert(cc: self ref Change): ref Change
{
	c := ref Change (!cc.inverted, nil, cc.ngen, cc.ogen);
	for(l := rev(cc.l); l != nil; l = tl l)
		c.l = (hd l).invert()::c.l;
	return c;
}

Change.text(c: self ref Change): string
{
	s := sprint("Change(inverted=%d, ogen=%bd, ngen=%bd\n", c.inverted, c.ogen, c.ngen);
	for(l := c.l; l != nil; l = tl l)
		s += "\t"+(hd l).text()+"\n";
	s += ")";
	return s;
}
