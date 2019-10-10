Repl: adt {
	l: list of (string, int);  # string, regex match index (only valid >= 0)
};

# parse replacement string
parserepl(s: string): (ref Repl, string)
{
	r := ref Repl;
	d: string;
	for(i := 0; i < len s; i++) {
		case c := s[i] {
		'\\' =>
			if(i+1 >= len s)
				return (nil, "\\ at end of dst pattner");
			++i;
			case c = s[i] {
			'\\' =>
				d[len d] = c;
			'0' to '9' =>
				r.l = (d, c-'0')::r.l;
				d = nil;
			't' =>	d[len d] = '\t';
			'n' =>	d[len d] = '\n';
			'r' =>	d[len d] = '\r';
			'f' =>	d[len d] = '\f';
			* =>
				return (nil, sprint("bad escape \\%c", c));
			}
		* =>
			d[len d] = c;
		}
	}
	if(d != nil)
		r.l = (d, -1)::r.l;
	return (r, nil);
}

# returns list of matches, hd is last in file
refind(re: Regex->Re, s: string, ss, se: int, g: int): list of array of (int, int)
{
	l: list of array of (int, int);
	for(;;) {
		bol := ss == 0 || s[ss-1] == '\n';
		eol := se == len s || s[se] == '\n';
		r := regex->executese(re, s, (ss, se), bol, eol);
		if(len r == 0 || r[0].t0 < 0)
			break;
		l = r::l;
		ss = r[0].t1;
		if(!g)
			break;
	}
	return l;
}

reapply(repl: ref Repl, r: array of (int, int)): string
{
	# build up new string first
	s: string;
	for(l := repl.l; l != nil; l = tl l) {
		(t, i) := hd l;
		s += t;
		if(i >= len r)
			return sprint("bad backreference %d", i);
		if(i < 0 || r[i].t0 < 0)
			continue;
		s += text.str()[r[i].t0:r[i].t1];
	}

	cs := text.cursor(r[0].t0);
	ce := text.cursor(r[0].t1);
	textdel(Cchange|Csetcursorlo, cs, ce);
	textins(Cchange, cs, s);
	return nil;
}

substitute(cs, ce: ref Cursor, src, dst: string, g: int): string
{
	(repl, err) := parserepl(dst);
	re: Regex->Re;
	if(err == nil)
		(re, err) = regex->compile(src, 1);
	if(err != nil)
		return err;

	r := refind(re, text.str(), cs.o, ce.o, g);
	if(r == nil)
		return "no match";
	for(; err == nil && r != nil; r = tl r)
		err = reapply(repl, hd r);
	return err;
}
