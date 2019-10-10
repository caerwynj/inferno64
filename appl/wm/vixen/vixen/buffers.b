Pos: adt {
	l, c:	int;  # line, column

	cmp:		fn(a, b: Pos): int;
	order:		fn(a, b: Pos): (Pos, Pos);
	eq:		fn(a, b: Pos): int;
	parse:		fn(s: string): Pos;
	text:		fn(p: self Pos): string;
};
nullpos: Pos;

Colkeep, Colstart, Colfirstnonblank, Colend, Colpastnewline: con -iota-1;  # mvline's colmv
Cursor: adt {
	b:	ref Buf;
	o:	int;	# offset into buf.  o can be set to length of buffer
	pos:	Pos;

	clone:		fn(c: self ref Cursor): ref Cursor;
	char:		fn(c: self ref Cursor): int;
	charprev:	fn(c: self ref Cursor): int;
	prev,
	next:		fn(c: self ref Cursor): int;
	walk:		fn(c: self ref Cursor, rev: int): int;

	mvchar,
	mvcol:		fn(c: self ref Cursor, col: int): ref Cursor;
	mvline:		fn(c: self ref Cursor, rel: int, colmv: int): ref Cursor;
	mvpos:		fn(c: self ref Cursor, p: Pos): ref Cursor;
	mvlineend:	fn(c: self ref Cursor, nl: int): ref Cursor;
	mvword,
	mvwordend:	fn(c: self ref Cursor, capital: int, n: int): ref Cursor;
	mvfirst:	fn(c: self ref Cursor): ref Cursor;
	mvsentence:	fn(c: self ref Cursor, prev: int): ref Cursor;
	mvparagraph:	fn(c: self ref Cursor, prev: int): ref Cursor;
	mvskip:		fn(c: self ref Cursor, cl: string): ref Cursor;

	word:		fn(c: self ref Cursor): (ref Cursor, ref Cursor);
	pathpattern:	fn(c: self ref Cursor, search: int): (ref Cursor, ref Cursor);
	findchar:	fn(c: self ref Cursor, cl: string, rev: int): ref Cursor;
	findstr:	fn(c: self ref Cursor, s: string, rev: int): ref Cursor;
	findlinechar:	fn(c: self ref Cursor, x: int, rev: int): ref Cursor;

	cmp:		fn(a, b: ref Cursor): int;
	order:		fn(a, b: ref Cursor): (ref Cursor, ref Cursor);
	diff:		fn(a, b: ref Cursor): int;
	linelength:	fn(c: self ref Cursor, nl: int): int;
	text:		fn(c: self ref Cursor): string;
};

Buf: adt {
	s:	string;
	nlines:	int;

	new:		fn(): ref Buf;
	get:		fn(b: self ref Buf, f, t: ref Cursor): string;
	del:		fn(b: self ref Buf, f, t: ref Cursor): string;
	ins:		fn(b: self ref Buf, w: ref Cursor, s: string): ref Cursor;
	set:		fn(b: self ref Buf, s: string);
	cursor:		fn(b: self ref Buf, o: int): ref Cursor;
	pos:		fn(b: self ref Buf, pos: Pos): ref Cursor;
	lines:		fn(b: self ref Buf): int;
	chars:		fn(b: self ref Buf): int;
	end:		fn(b: self ref Buf): ref Cursor;
	str:		fn(b: self ref Buf): string;
};


checkcursor(c: ref Cursor)
{
	if(c.o < 0 || c.o > len c.b.s)
		raise "cursor.o invalid";
	cc := ref *c;
	cc.o = 0;
	cc.pos = Pos (1, 0);
	while(c.o != cc.o)
		cc.next();
	if(!Pos.eq(c.pos, cc.pos))
		raise sprint("cursor has wrong pos, got %s, pos should be %s", c.text(), cc.pos.text());
}

Pos.cmp(a, b: Pos): int
{
	if(a.l < b.l || a.l == b.l && a.c < b.c) return -1;
	if(a.l > b.l || a.l == b.l && a.c > b.c) return 1;
	return 0;
}

Pos.order(a, b: Pos): (Pos, Pos)
{
	if(a.l > b.l || (a.l == b.l && a.c > b.c))
		return (b, a);
	return (a, b);
}

Pos.eq(a, b: Pos): int
{
	return a.l == b.l && a.c == b.c;
}

Pos.parse(s: string): Pos
{
	(a, b) := str->splitstrl(s, ".");
	if(b != nil)
		b = b[1:];
	return Pos (int a, int b);
}

Pos.text(p: self Pos): string
{
	return sprint("%d.%d", p.l, p.c);
}


Cursor.clone(c: self ref Cursor): ref Cursor
{
	return ref *c;
}

Cursor.char(c: self ref Cursor): int
{
	if(c.o < 0 || c.o >= len c.b.s)
		return -1;
	return c.b.s[c.o];
}

Cursor.charprev(c: self ref Cursor): int
{
	o := c.o-1;
	if(o < 0 || o >= len c.b.s)
		return -1;
	return c.b.s[o];
}

# move back one char in the buffer and return it.
# if already at start, return -1.
Cursor.prev(c: self ref Cursor): int
{
	if(c.o <= 0)
		return -1;
	r := c.b.s[--c.o];
	--c.pos.c;
	if(r == '\n') {
		--c.pos.l;
		c.pos.c = linelength(c, c.o);
	} else if(c.pos.c < 0)
		raise "bogus col";
	return r;
}

# return length of line without newline, don't use c.pos.c, it may be wrong
linelength(c: ref Cursor, o: int): int
{
	for(so := o; so > 0 && c.b.s[so-1] != '\n'; --so)
		{}
	for(eo := o; eo < len c.b.s && c.b.s[eo] != '\n'; ++eo)
		{}
	return eo-so;
}


# move cursor forward, return the character under it.
# if already under last character, we move forward, but return -1.
Cursor.next(c: self ref Cursor): int
{
	if(c.o >= len c.b.s)
		return -1;
	x := c.b.s[c.o];
	++c.o;
	++c.pos.c;
	if(x == '\n') {
		++c.pos.l;
		c.pos.c = 0;
	}
	if(c.o >= len c.b.s)
		return -1;
	return c.b.s[c.o];
}

Cursor.walk(c: self ref Cursor, rev: int): int
{
	if(rev)
		return c.prev();
	return c.next();
}

# move cursor by 'rel' characters, staying on the same line.
Cursor.mvchar(cc: self ref Cursor, rel: int): ref Cursor
{
	c := cc.clone();
	while(rel > 0) {
		x := c.char();
		if(x < 0 || x == '\n')
			break;
		c.next();
		--rel;
	}
	while(rel < 0) {
		x := c.charprev();
		if(x < 0 || x == '\n')
			break;
		c.prev();
		++rel;
	}
	checkcursor(c);
	return c;
}

# move cursor by 'rel' lines, try to keep cursor on same col.
Cursor.mvline(c: self ref Cursor, rel: int, colmv: int): ref Cursor
{
	c = c.clone();
	col := 0;
	if(colmv == Colkeep)
		col = c.pos.c;
	else if(colmv >= 0)
		col = colmv;
	c = c.mvpos(Pos (max(1, c.pos.l+rel), col));
	case colmv {
	Colkeep =>	{}
	Colstart =>	{}
	Colfirstnonblank =>	c = c.mvfirst();
	Colend =>		c = c.mvlineend(0);
	Colpastnewline =>	c = c.mvlineend(1);
	* =>
		if(colmv < 0)
			raise "bad colmv";
	}
	return c;
}

# move to column on current line, moving to end if col is past end of line
Cursor.mvcol(c: self ref Cursor, col: int): ref Cursor
{
	if(col < 0)
		col = 0;
	if(col > c.pos.c)
		col = min(c.linelength(0), col);
	cc := ref Cursor (c.b, c.o+col-c.pos.c, Pos (c.pos.l, col));
	checkcursor(cc);
	return cc;
}

Cursor.mvpos(cc: self ref Cursor, p: Pos): ref Cursor
{
	return cc.b.pos(p);
}

Cursor.mvlineend(c: self ref Cursor, nl: int): ref Cursor
{
	c = c.clone();
	x := c.char();
	while(x >= 0 && x != '\n')
		x = c.next();
	if(nl && x == '\n')
		c.next();
	return c;
}

Cursor.cmp(a, b: ref Cursor): int
{
	if(a.o == b.o) return 0;
	if(a.o < b.o) return -1;
	return 1;
}

Cursor.order(a, b: ref Cursor): (ref Cursor, ref Cursor)
{
	if(a.o > b.o)
		return (b, a);
	return (a, b);
}

Cursor.diff(a, b: ref Cursor): int
{
	return b.o-a.o;
}

# return length of line, including newline if present and nl is set
Cursor.linelength(cc: self ref Cursor, nl: int): int
{
	if(nl)
		nl = 1;
	# find newline or end of file
	c := cc.clone();
	x := c.char();
	for(;;) {
		if(x < 0)
			return c.pos.c;
		if(x == '\n')
			return c.pos.c+nl;
		x = c.next();
	}
}

whitespace: con " \t\n";
interpunction: con "!\"#$%&'()*+,./:;<=>?@\\]^_`{|}~-[";
whitespaceinterpunction: con " \t\n!\"#$%&'()*+,./:;<=>?@\\]^_`{|}~-[";
Cursor.mvword(cc: self ref Cursor, capital: int, n: int): ref Cursor
{
	c := cc.clone();
	while(n > 0) {
		mvwordforward(c, capital);
		n--;
	}
	while(n < 0) {
		mvwordbackward(c, capital);
		n++;
	}
	checkcursor(c);
	return c;
}

mvwordforward(c: ref Cursor, cap: int)
{
	x := c.char();
	if(cap)
		stop := whitespace;
	else
		stop = whitespaceinterpunction;

	if(!cap && str->in(x, interpunction))
		while(x >= 0 && str->in(x, interpunction))
			x = c.next();
	while(x >= 0 && !str->in(x, stop))
		x = c.next();
	while(x >= 0 && str->in(x, whitespace))
		x = c.next();
}

mvwordbackward(c: ref Cursor, cap: int)
{
	c.prev();
	x: int;
	x = c.char();
	while(x >= 0 && str->in(x, whitespace))
		x = c.prev();
	if(cap) {
		# read back until whitespace
		c.prev();
		while((x = c.charprev()) >= 0 && !str->in(x, whitespace))
			c.prev();
	} else {
		# if interpunction, read to start of it.
		# otherwise read to end of last whitespace/interpunction
		x = c.char();
		if(x < 0) {
			# nothing
		} else if(str->in(x, interpunction)) {
			while((x = c.charprev()) >= 0 && str->in(x, interpunction))
				c.prev();
		} else {
			while((x = c.charprev()) >= 0 && !str->in(x, whitespaceinterpunction))
				c.prev();
		}
	}
}

Cursor.mvwordend(cc: self ref Cursor, cap: int, n: int): ref Cursor
{
	if(n < 0)
		raise "bad mvwordend";
	c := cc.clone();
	while(n-- > 0) {
		c.next();
		x := c.char();
		while(x >= 0 && str->in(x, whitespace))
			x = c.next();
		if(cap || str->in(x, interpunction))
			stop := whitespace;
		else
			stop = whitespaceinterpunction;
		while(x >= 0 && !str->in(x, stop))
			x = c.next();
	}
	checkcursor(c);
	return c;
}

Cursor.mvfirst(c: self ref Cursor): ref Cursor
{
	return c.clone().mvcol(0).mvskip(" \t");
}

Cursor.mvsentence(c: self ref Cursor, prev: int): ref Cursor
{
	c = c.clone();
	Lineend: con ".!?";
	if(prev) {
		# beginning of previous sentence
		y := c.prev();
		while(y >= 0 && (str->in(y, Lineend) || str->in(y, whitespace)))
			y = c.prev();
		c = c.findchar(Lineend, 1);
		if(c != nil)
			c = c.mvskip(Lineend+whitespace);
		else
			c = text.cursor(0);
	} else {
		c = c.mvskip("^"+Lineend);
		c = c.mvskip(Lineend+whitespace);
	}
	return c;
}

Cursor.mvparagraph(c: self ref Cursor, prev: int): ref Cursor
{
	c = c.clone();
	if(prev) {
		x := c.prev();
		while(x == '\n')
			x = c.prev();
		c = c.findstr("\n\n", 1);
		if(c == nil)
			c = text.cursor(0);
		else
			c.next();
	} else {
		x := c.char();
		while(x == '\n')
			x = c.next();
		c = c.findstr("\n\n", 0);
		if(c == nil)
			c = text.end();
		else
			c.next();
	}
	return c;
}

Cursor.mvskip(cc: self ref Cursor, cl: string): ref Cursor
{
	c := cc.clone();
	x := c.char();
	while(x >= 0 && str->in(x, cl))
		x = c.next();
	return c;
}

# return start & end of word under cursor.  (nil, nil) if cursor not under a word.
Cursor.word(c: self ref Cursor): (ref Cursor, ref Cursor)
{
	x := c.char();
	if(x < 0 || str->in(x, whitespaceinterpunction))
		return (nil, nil);
	a := c.clone();
	b := c.clone();
	while((x = a.charprev()) > 0 && !str->in(x, whitespaceinterpunction))
		a.prev();
	x = b.char();
	while(x > 0 && !str->in(x, whitespaceinterpunction))
		x = b.next();
	return (a, b);
}

# return start & end of path and optionally pattern under cursor.
# (nil, nil) if no path is under the cursor, or no path could be found with `search' set.
Cursor.pathpattern(c: self ref Cursor, search: int): (ref Cursor, ref Cursor)
{
	# read a file:address pattern (not whole line!), also look backwards.
	# this could be done with a vim-like text object "motion" some day.
	Break: con " \t\n!\"'(),;<>?[]{}";
	c = c.clone();
	if(search)
		c = c.mvskip(" \t\n");
	else if(str->in(c.char(), whitespace))
		return (nil, nil);
	ce := c.clone();
	for(;;) {
		x := c.charprev();
		if(x < 0 || has(x, Break))
			break;
		c.prev();
	}
	ncolon := 0;
	x := ce.char();
	for(;;) {
		if(x < 0 || has(x, Break))
			break;
		if(x == ':' && ++ncolon >= 2)
			break;
		x = ce.next();
	}
	return (c, ce);
}

# move cursor forward (or backward if rev!=0) until cursor is at char from cl
# return nil if no such cursor exists.
Cursor.findchar(c: self ref Cursor, cl: string, rev: int): ref Cursor
{
	c = c.clone();
	x := c.char();
	for(;;) {
		if(x < 0)
			return nil;
		if(str->in(x, cl))
			return c;
		if(rev)
			x = c.prev();
		else
			x = c.next();
	}
}

Cursor.findstr(c: self ref Cursor, s: string, rev: int): ref Cursor
{
	if(s == nil)
		return c;
	c = c.clone();
	x := c.char();
	while(x > 0) {
		if(s[0] == x && str->prefix(s, c.b.s[c.o:])) {
			say('c', sprint("findstr, have match, c %s", c.text()));
			return c;
		}
		x = c.walk(rev);
	}
	return nil;
}

Cursor.findlinechar(c: self ref Cursor, x: int, rev: int): ref Cursor
{
	c = c.clone();
	y: int;
	if(rev) {
		if(c.pos.c == 0)
			return nil;
		y = c.prev();
		do {
			if(y == x)
				return c;
			y = c.prev();
		} while(c.pos.c >= 0);
	} else {
		if(c.char() == '\n')
			return nil;
		do {
			y = c.next();
			if(y == x)
				return c;
		} while(y >= 0 && y != '\n');
	}
	return nil;
}

Cursor.text(c: self ref Cursor): string
{
	return sprint("Cursor(len b.s=%d, o=%d, pos=%s)", len c.b.s, c.o, c.pos.text());
}


Buf.new(): ref Buf
{
	return ref Buf ("", 1);
}

Buf.get(b: self ref Buf, f, t: ref Cursor): string
{
	return b.s[f.o:t.o];
}

Buf.del(b: self ref Buf, f, t: ref Cursor): string
{
	r := b.s[f.o:t.o];
	b.s = b.s[:f.o]+b.s[t.o:];
	for(i := 0; i < len r; i++)
		if(r[i] == '\n')
			--b.nlines;
	return r;
}

Buf.ins(b: self ref Buf, cc: ref Cursor, s: string): ref Cursor
{
	c := cc.clone();
	for(i := 0; i < len s; i++) {
		x := s[i];
		if(x == '\n')
			++b.nlines;
		if(len b.s == c.o) {
			b.s[c.o] = x;
		} else {
			ns := c.b.s[:c.o];
			ns[len ns] = x;
			ns += c.b.s[c.o:];
			b.s = ns;
		}
		c.next();
	}
	checkcursor(c);
	return c;
}

Buf.set(b: self ref Buf, s: string)
{
	text.s = s;
	b.nlines = 1;
	for(i := 0; i < len s; i++)
		if(s[i] == '\n')
			++b.nlines;
}

Buf.cursor(b: self ref Buf, o: int): ref Cursor
{
	if(o < 0)
		o = 0;
	if(o > len b.s)
		o = len b.s;
	c := ref Cursor (b, 0, Pos (1, 0));
	for(i := 0; i < o; i++) {
		++c.pos.c;
		if(b.s[i] == '\n') {
			c.pos.c = 0;
			++c.pos.l;
		}
	}
	c.o = i;
	return c;
}

Buf.pos(b: self ref Buf, pos: Pos): ref Cursor
{
	if(pos.l < 1 || pos.c < 0)
		raise "bad pos";
	c := ref Cursor (b, 0, Pos (1, 0));

	x := c.char();
	for(;;) {
		if(x < 0 || c.pos.l == pos.l && (x == '\n' || c.pos.c == pos.c))
			break;
		x = c.next();
	}

	say('c', sprint("Buf.pos %s -> %s", pos.text(), c.pos.text()));
	return c;
}

Buf.lines(b: self ref Buf): int
{
	return b.nlines;
}

Buf.chars(b: self ref Buf): int
{
	return len b.s;
}

Buf.end(b: self ref Buf): ref Cursor
{
	return b.cursor(max(0, b.chars()));
}

Buf.str(b: self ref Buf): string
{
	return b.s;
}

# if cs/ce is nil, write whole buf
bufwritefd(b: ref Buf, cs, ce: ref Cursor, fd: ref Sys->FD): string
{
	if(cs == nil)
		buf := array of byte b.s;
	else
		buf = array of byte text.get(cs, ce);
	if(sys->write(fd, buf, len buf) != len buf)
		return "write failed: %r";
	return nil;
}
