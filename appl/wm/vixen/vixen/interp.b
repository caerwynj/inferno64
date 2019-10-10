xabort(s: string)	{ raise "abort:"+s; }
xmore()			{ raise "more:"; }
xdone()			{ raise "done:"; }
xconsumed()		{ raise "consumed:"; }
xchange()		{ raise "change:"; }
xmoveonly()		{ raise "moveonly:"; }

interp(cc: ref Cmd)
{
	say('i', sprint("interp: mode %s, %s", modes[mode], cc.text()));
	case mode {
	Insert =>	insert(cc, 0);
	Replace =>	insert(cc, 1);
	Command0 =>	command(cc);
	Visual or
	Visualline =>	visual(cc);
	}
}

interpx()
{
	say('i', sprint("interpx: mode %s, %s", modes[mode], cmdcur.text()));
	cc := cmdcur.clone();
	statustext = nil;
	tkplumbclear();
Interp:
	while(cc.more()) {
		{
			interp(cc);
			raise "interp returned";
		} exception ex {
		"abort:*" =>
			# error while executing, discard command
			ex = ex[len "abort:":];
			if(ex != nil)
				statuswarn(ex);
			cmdcur = Cmd.new();
			modeset(Command0);
			register = '"';
			break Interp;
		"consumed:*" =>
			# characters consumed, nothing special to do
			cmdcur = cc;
			statusset();
		"change:*" =>
			# a changing command finished.  store to cmdprev for repeat.
			cmdprev = Cmd.mk(cmdcur.str());
			cmdcur = Cmd.new();
			modeset(Command0);  # calls statusset
			register = '"';
			changesave();
		"done:*" =>
			cmdcur = Cmd.new();
			statusset();
			register = '"';
			changesave();
		"moveonly:*" =>
			# command that was move-only (don't store as cmdprev)
			cmdcur = Cmd.new();
			statusset();
		"more:*" =>
			# more input needed
			statusset();
			break Interp;
		"edit:*" =>
			# input needed from edit entry
			editset(ex[len "edit:":]);
			break Interp;
		}
	}
	up();
}


modeset(m: int)
{
	tkcmd(".t.text tag remove sel 1.0 end");
	case mode {
	Insert or
	Replace =>
		xmarkput('^', cursor);
		if(change != nil)
			pick mm := hd change.l {
			Ins =>
				xregput('.', mm.s);
			}
	}
	mode = m;
	statusset();
}


macro(n: int, s: string)
{
	ocmd := cmdcur;
	while(n-- > 0) {
		cmdcur = Cmd.mk(s);
		interpx();
	}
	cmdcur = ocmd;
}


Beep: adt {
	beeped:	int;
	base:	ref Cursor;
	dst:	ref Cursor;

	mk:	fn(base: ref Cursor): ref Beep;
	set:	fn(b: self ref Beep, c: ref Cursor);
	beepset:	fn(b: self ref Beep, c: ref Cursor);
};

Beep.mk(base: ref Cursor): ref Beep
{
	return ref Beep (0, base.clone(), base);
}

Beep.set(b: self ref Beep, c: ref Cursor)
{
	*b.dst = *c;
}

Beep.beepset(b: self ref Beep, c: ref Cursor)
{
	if(c == nil || Cursor.cmp(b.base, c) == 0)
		b.beeped++;
	else
		b.set(c);
}

Nosetjump, Setjump: con iota;
move(cc: ref Cmd, mult, setjump: int, cr: ref Cursor)
{
	say('i', "move: "+cc.text());
	c := cc.clone();
	numstr := c.xgetnum();
	num := 1;
	if(numstr != nil)
		num = int numstr;
	num *= mult;

	b := Beep.mk(cr);

	jump := 0;
	newcolsnap := 1;

	case x := c.xget() {
	kb->Home or
	'0' =>	b.set(cr.mvcol(0));
	kb->Left or
	'h' =>	b.beepset(cr.mvchar(-num));
	kb->Right or
	'l' =>	b.beepset(cr.mvchar(+num));
	' ' =>
		nc := cr.clone();
		nc.next();
		b.beepset(nc);
	'w' =>	b.beepset(cr.mvword(0, +num));
	'W' =>	b.beepset(cr.mvword(1, +num));
	'b' =>	b.beepset(cr.mvword(0, -num));
	'B' =>	b.beepset(cr.mvword(1, -num));
	'e' =>	b.beepset(cr.mvwordend(0, +num));
	'E' =>	b.beepset(cr.mvwordend(1, +num));
	'G' =>	
		if(numstr == nil)
			b.set(text.end());
		else
			b.set(text.pos(Pos (num, 0)).mvfirst());
		jump = 1;
	kb->End or
	'$' =>	b.set(cr.mvline(+num-1, Colend));
	'^' =>	b.set(cr.mvfirst());
	'-' =>	b.set(cr.mvline(-num, Colfirstnonblank));
	'+' or
	'\n' =>	b.beepset(cr.mvline(+num, Colfirstnonblank));
	'_' =>	b.beepset(cr.mvline(num-1, Colfirstnonblank));
	'f' or
	'F' or
	't' or
	'T' or
	';' or
	',' =>
		if((x == ';' || x == ',') && lastfind == 0)
			xabort("no previous find");
		y: int;
		case x {
		';' =>
			x = lastfind;
			y = lastfindchar;
		',' =>
			x = swapcasex(lastfind);
			y = lastfindchar;
		* =>
			y = c.xget();
			lastfind = x;
			lastfindchar = y;
		}
		rev := x == 'F' || x == 'T';
		nc := cr;
		while(num--) {
			nc = nc.findlinechar(y, rev);
			if(nc == nil)
				xabort("not found");
		}
		if(x == 't' && nc.pos.c > 0)
			nc.prev();
		if(x == 'T' && nc.char() != '\n')
			nc.next();
		b.beepset(nc);
	'/' or
	'?' =>
		s := xeditget(c, sprint("%c", x));
		searchreverse = (x == '?');
		ms, me: ref Cursor;
		if(s == nil || searchset(s)) {
			(ms, me) = search(0, searchreverse, searchregex, cr);
			b.beepset(ms);
			if(ms == nil)
				break;
		}
		if(ms != nil)
			tkhighlight(ms, me);
		jump = 1;
	'n' or
	'N' =>
		rev := x == 'N';
		ms, me: ref Cursor;
		while(num--) {
			(ms, me) = search(rev, searchreverse, searchregex, b.dst);
			b.beepset(ms);
			if(ms == nil)
				break;
		}
		if(ms != nil)
			tkhighlight(ms, me);
		jump = 1;
	'*' or
	'#' =>	
		(ws, we) := cursor.word();
		if(ws == nil)
			xabort("no word under cursor");
		rev := x == '#';
		ss := text.get(ws, we);
		#Wordbreak: con "\\;\\]\\;\\-\\.\\^\\$\\(\\)\\*\\+\\?\\|\\[\\\\ \t!\"#%&',/:;<=>@\\^_`{|}~\\[";
		#Wordbreak: con " \t";
		#restr := sprint("(^|[%s])%s($|[%s])", Wordbreak, ss, Wordbreak);
		restr := ss;
		(re, err) := regex->compile(restr, 0);
		if(err != nil)
			xabort("bad pattern (internal error)");
		if(rev)
			b.beepset(ws);
		ms, me: ref Cursor;
		while(num--) {
			(ms, me) = search(rev, 0, re, b.dst);
			b.beepset(ms);
			if(ms == nil)
				break;
		}
		if(ms != nil)
			tkhighlight(ms, me);
		jump = 1;
	'%' =>
		if(numstr != nil) {
			# move to percentage of file, in lines
			perc := int numstr;
			if(perc > 0 && perc <= 100)
				b.beepset(text.pos(Pos (perc*text.lines()/100, Colfirstnonblank)));
			else
				b.beepset(nil);
		} else {
			# move to matching (){}[].  if other char under cursor, search forward for one.
			if(cr.char() < 0)
				break;
			nc := b.dst.clone();
			if(!str->in(nc.char(), "(){}[]"))
				nc = nc.findchar("(){}[]", 0);
			if(nc != nil) {
				sep: string;
				case look := nc.char() {
				'(' or ')' =>	sep = "()";
				'{' or '}' =>	sep = "{}";
				'[' or ']' =>	sep = "[]";
				}
				rev := nc.char() == sep[1];
				level := 1;
				nc.walk(rev);
				for(;;) {
					nc = nc.findchar(sep, rev);
					if(nc == nil)
						break;
					if(nc.char() != look)
						--level;
					else
						++level;
					if(level <= 0)
						break;
					nc.walk(rev);
				}
			}
			b.beepset(nc);
		}
		jump = 1;
	'|' =>
		n := 0;
		if(numstr != nil)
			n = int numstr;
		b.set(cr.mvcol(n*mult));
	'(' or
	')' =>
		prev := x == '(';
		while(num--) {
			nc := b.dst.mvsentence(prev);
			b.beepset(nc);
			if(nc == nil)
				break;
		}
		jump = 1;
	'{' or
	'}' =>
		prev := x == '{';
		while(num--) {
			nc := b.dst.mvparagraph(prev);
			b.beepset(nc);
			if(nc == nil)
				break;
		}
		jump = 1;
	'`' =>
		b.set(xmarkget(c.xget()));
		jump = 1;
	'\'' =>
		b.set(xmarkget(c.xget()).mvfirst());
		jump = 1;
	'H' or
	'M' or
	'L' =>
		(ps, pe) := tkvisible();
		l: int;
		case x {
		'H' =>	l = min(ps.l+num-1, pe.l);
		'M' =>	l = (ps.l+pe.l)/2;
		'L' =>	l = max(ps.l, pe.l-num+1);
		}
		b.set(cr.mvpos(Pos (l, 0)).mvfirst());
	'g' =>
		case c.xget() {
		'g' =>
			if(numstr == nil)
				b.set(text.pos(Pos(1, 0)));
			else
				b.set(text.pos(Pos (num, 0)).mvfirst());
			jump = 1;
		'o' =>
			b.set(text.cursor(num-1));
			jump = 1;
		}
	* =>
		colkeep := Colkeep;
		if(colsnap >= 0)
			colkeep = colsnap;
		case x {
		kb->APP|'n' or
		kb->Down or
		'j' =>		b.beepset(cr.mvline(+num, colkeep));
		kb->APP|'p' or
		kb->Up or
		'k' =>		b.beepset(cr.mvline(-num, colkeep));
		kb->APP|'b' or
		kb->Pgup =>	b.beepset(cr.mvline(-num*max(1, tklinesvisible()), colkeep));
		kb->APP|'f' or
		kb->Pgdown =>	b.beepset(cr.mvline(+num*max(1, tklinesvisible()), colkeep));
		kb->APP|'u' =>	b.beepset(cr.mvline(-num*max(1, tklinesvisible()/2), colkeep));
		kb->APP|'d' =>	b.beepset(cr.mvline(+num*max(1, tklinesvisible()/2), colkeep));
		kb->APP|'y' =>
			ps := tkvisibletop();
			if(ps.l <= 1 && ps.c == 0)
				break;
			l := ps.l-1;
			# change one line at a time so tk doesn't center location
			while(num-- && l >= 1)
				tkcmd(sprint(".t.text see %d.0; update", l--));
			pe := tkvisiblebottom();
			nc := cr;
			if(Pos.cmp(nc.pos, pe) > 0)
				nc = text.pos(Pos (pe.l, 0));
			b.set(nc);
		kb->APP|'e' =>
			pe := tkvisiblebottom();
			nl := text.lines();
			if(pe.l >= nl)
				break;
			l := pe.l+1;
			# change one line at a time so tk doesn't center location
			while(num-- && l <= nl)
				tkcmd(sprint(".t.text see %d.0; update", l++));
			ps := tkvisibletop();
			nc := cr;
			if(Pos.cmp(nc.pos, ps) < 0)
				nc = text.pos(ps);
			b.set(nc);
		* =>
			xabort(sprint("bad command %c", x));
		}
		newcolsnap = 0;
	}
	if(newcolsnap)
		colsnap = b.dst.pos.c;
	*cc = *c;
	if(b.beeped)
		statuswarn("beep!");
	if(jump && setjump && !b.beeped)
		xmarkput('`', b.base);
}


insert(c: ref Cmd, repl: int)
{
	say('i', sprint("insert/replace, c %s", c.text()));
	(cmod, cchange) := (Cmod, Cchange);
	if(repl)
		(cmod, cchange) = (Cmodrepl, Cchangerepl);
	while(c.more())
		case x := c.get() {
		kb->Esc =>	
				if(inserted())
					cursorset(cursor.mvchar(-1));
				xchange();
		kb->APP|'h' or
		kb->Del =>	textdel(cmod|Csetcursorlo, cursor.mvchar(-1), nil);
		kb->APP|'w' =>	textdel(cmod|Csetcursorlo, cursor.mvword(0, -1), nil);
		kb->APP|'u' =>	textdel(cmod|Csetcursorlo, cursor.mvcol(0), nil);
		* =>
			if(repl && x == '\n' || cursor.char() == '\n')
				(cmod, cchange) = (Cmod, Cchange);
			textins(cchange|Csetcursorhi, nil, sprint("%c", x));
		}
	xconsumed();
}

visual(cc: ref Cmd)
{
	c := cc.clone();
	c.xgetnum1();

	(vs, ve) := visualrange();
	say('i', sprint("visual, vs %s, ve %s", vs.text(), ve.text()));

	case x := c.xget() {
	kb->Esc =>
		xabort(nil);
	'd' or
	'D' =>
		textdel(Cchange|Csetcursorlo|Csetreg, vs, ve);
	'p' =>
		textrepl(Cchange|Csetcursorlo, vs, ve, xregget(register));
	'y' =>
		xregput(register, text.get(vs, ve));
	'J' =>
		join(vs, ve, 1);
	'<' or
	'>' =>
		indent(vs.mvcol(0), ve, x == '<');
	'r' =>
		y := c.xget();
		s: string;
		n := abs(Cursor.diff(vs, ve));
		while(n--)
			s[len s] = y;
		mv := Csetcursorlo;
		if(y == '\n')
			mv = Csetcursorhi;
		textrepl(Cchange|mv, vs, ve, s);
	'!' =>
		ex(xeditget(c, ":'<,'>!"));
	':' =>
		ex(xeditget(c, ":'<,'>"));
	'~' =>
		textrepl(Cchange|Csetcursorlo, vs, ve, swapcase(text.get(vs, ve)));
	'g' =>
		case c.xget() {
		'J' =>
			join(vs, ve, 0);
		'~' =>
			textrepl(Cchange|Csetcursorlo, vs, ve, swapcase(text.get(vs, ve)));
		'u' =>
			textrepl(Cchange|Csetcursorlo, vs, ve, str->tolower(text.get(vs, ve)));
		'U' =>
			textrepl(Cchange|Csetcursorlo, vs, ve, str->toupper(text.get(vs, ve)));
		'p' or
		'P' =>
			plumb(text.get(vs, ve), nil, plumbdir());
		* =>
			c = cc.clone();
			move(c, 1, Setjump, ce := cursor.clone());
			visualend = ce.clone();
			visualset();
			cursorset(ce);
			*cc = *c;
			xconsumed();
		}
	* =>
		case x {
		'q' =>
			recordq(c);
		* =>
			case x {
			kb->APP|'l' =>
				redraw();
			'o' =>
				(cursor, visualstart) = (visualstart, cursor);
				visualset();
				cursorset(cursor);
			'"' =>
				xregset(c.xget());
			'c' or
			's' =>
				textdel(Cchange|Csetcursorlo, vs, ve);
				modeset(Insert);
			'C' or
			'S' or
			'R' =>
				if(mode != Visualline)
					ve = ve.mvlineend(1);
				textdel(Cchange|Csetcursorlo, vs.mvcol(0), ve);
				modeset(Insert);
			* =>
				c = cc.clone();
				move(c, 1, Setjump, ce := cursor.clone());
				visualend = ce.clone();
				visualset();
				cursorset(ce);
			}
			*cc = *c;
			xconsumed();
		}
		*cc = *c;
		xdone();
	}
	*cc = *c;
	xchange();
}

commandmove(c: ref Cmd, num1, end: int): (int, ref Cursor)
{
	cc := c.clone();
	cc.xgetnum2();
	num2 := cc.num2(1);
	x := cc.xget();

	if(x == end) {
		*c = *cc;
		return (num2, nil);
	}
	move(c, num1, Nosetjump, ce := cursor.clone());
	return (num2, ce);
}

command(cc: ref Cmd)
{
	c := cc.clone();
	c.xgetnum1();
	num1 := c.num1(1);

	cs := cursor;
	case x := c.xget() {
	kb->Esc =>
		xabort(nil);
	'x' =>
		textdel(Cchange|Csetcursorlo|Csetreg, nil, cursor.mvchar(num1));
	'X' =>
		textdel(Cchange|Csetcursorlo|Csetreg, cursor.mvchar(-num1), nil);
	'd' =>
		(num2, ce) := commandmove(c, num1, 'd');
		if(ce == nil) {
			(cs, ce) = (cursor.mvcol(0), cursor.mvline(num1*num2-1, Colpastnewline));
			textdel(Cchange|Csetcursorlo|Csetreg, cs, ce);
			cursorset(cursor.mvfirst());
		} else
			textdel(Cchange|Csetcursorlo|Csetreg, cs, ce);
	'D' =>
		textdel(Cchange|Csetcursorlo|Csetreg, nil, cursor.mvline(num1-1, Colend));
	'y' =>
		(num2, ce) := commandmove(c, num1, 'y');
		if(ce == nil)
			(cs, ce) = (cs.mvcol(0), cs.mvline(num1*num2-1, Colpastnewline));
		(cs, ce) = Cursor.order(cs, ce);
		xregput(register, text.get(cs, ce));
	'Y' =>
		s := text.get(cursor.mvcol(0), cursor.mvline(num1, Colstart));
		xregput(register, s);
	'p' =>
		s := xregget(register);
		if(s[len s-1] == '\n')
			cs = cs.mvlineend(1);
		else
			cs = cs.mvchar(+1);
		r: string;
		while(num1--)
			r += s;
		textins(Cchange|Csetcursorlo, cs, r);
	'P' =>
		s := xregget(register);
		if(s[len s-1] == '\n')
			cursorset(cursor.mvcol(0));
		r: string;
		while(num1--)
			r += s;
		textins(Cchange, nil, r);
	'<' or
	'>' =>
		(num2, ce) := commandmove(c, num1, x);
		if(ce == nil)
			ce = cursor.mvline(max(0, num1*num2-1), Colend);
		(cs, ce) = Cursor.order(cs, ce);
		indent(cs.mvcol(0), ce.mvlineend(0), x == '<');
	'J' =>
		cs = cursor.mvlineend(0);
		ce := cursor.mvline(max(0, num1), Colpastnewline);
		join(cs, ce, 1);
	'm' =>
		y := c.xget();
		xmarkput(y, cursor);
	'r' =>
		ce := cursor.mvchar(+num1);
		if(Cursor.diff(cursor, ce) < num1)
			xabort(nil);
		y := c.xget();
		textdel(Cchange|Csetcursorlo, nil, ce);
		s: string;
		while(num1--)
			s[len s] = y;
		mv := 0;
		if(y == '\n')
			mv = Csetcursorhi;
		textins(Cchange|mv, nil, s);
	'!' =>
		(num2, ce) := commandmove(c, num1, '!');
		if(ce == nil)
			ce = cs.mvline(num1*num2-1, 0);
		if(cursor.pos.l == ce.pos.l)
			pre := ":.!";
		else
			pre = sprint(":.,%+d!", ce.pos.l-cursor.pos.l);
		s := xeditget(c, pre);
		ex(s);
	'Z' =>
		case c.xget() {
		'Z' =>	writemodifiedquit(0);
		* =>	xabort(nil);
		}
	'~' =>
		ce := cs.mvchar(+num1);
		r := swapcase(text.get(cs, ce));
		textrepl(Cchange|Csetcursorhi, cs, ce, r);
	'g' =>
		case y := c.xget() {
		'J' =>
			cs = cursor.mvlineend(0);
			ce := cursor.mvline(max(1, num1-1), Colstart);
			join(cs, ce, 0);
		'~' =>
			(num2, ce) := commandmove(c, num1, '~');
			if(ce == nil) {
				ce = cursor.mvline(num1*num2-1, Colpastnewline).mvfirst();
				cs = cs.mvfirst();
			}
			(cs, ce) = Cursor.order(cs, ce);
			s := swapcase(text.get(cs, ce));
			textrepl(Cchange|Csetcursorlo, cs, ce, s);
		'u' or
		'U' =>
			(num2, ce) := commandmove(c, num1, y);
			if(ce == nil) {
				ce = cs.mvline(num1*num2-1, Colpastnewline).mvfirst();
				cs = cs.mvfirst();
			}
			(cs, ce) = Cursor.order(cs, ce);
			s := text.get(cs, ce);
			if(y == 'u')
				s = str->tolower(s);
			else
				s = str->toupper(s);
			textrepl(Cchange|Csetcursorlo, cs, ce, s);
		'i' =>
			cursorset(xmarkget('^'));
			modeset(Insert);
			*cc = *c;
			xconsumed();
		'I' =>
			cursorset(cursor.mvcol(0));
			modeset(Insert);
			*cc = *c;
			xconsumed();
		'b' =>
			s := xregget('!');
			(r, err) := filter(s, "", 1);
			say('i', sprint("gb, s %q, err %q, r %q", s, err, r));
			if(err != nil)
				xabort(err);
			plumb(r, "newtext", workdir());
		'p' =>
			(num2, ce) := commandmove(c, num1, 'p');
			if(ce == nil)
				ce = cursor.mvline(num1*num2-1, Colend);
			s := text.get(cs, ce);
			say('i', sprint("plumbing %q", s));
			plumb(s, nil, plumbdir());
		'P' =>
			ce: ref Cursor;
			(cs, ce) = cs.pathpattern(1);
			if(cs == nil)
				xabort("no path under cursor");
			s := text.get(cs, ce);
			say('i', sprint("plumbing %q", s));
			plumb(s, nil, plumbdir());
		* =>
			c = cc.clone();
			move(c, 1, Setjump, ce := cursor.clone());
			cursorset(ce);
			*cc = *c;
			xmoveonly();
		}
	* =>
		case x {
		kb->APP|'g' =>
			statusset();
		kb->APP|'r' =>
			redo();
		kb->APP|'l' =>
			redraw();
		'@' =>
			y := c.xget();
			if(y == '@') {
				if(lastmacro == 0)
					xabort("no previous macro");
				y = lastmacro;
			} else
				lastmacro = y;
			ss := xregget(y);
			macro(num1, ss);
		'Q' or
		':' =>
			ex(xeditget(c, ":"));
		'u' =>
			undo();
		'.' =>
			if(cmdprev == nil)
				xabort("no previous command");
			say('i', sprint("cmdprev: %s", cmdprev.text()));
			cmd := cmdprev.clone();
			while(cmd.more())
				{
					interp(cmd);
					raise "interp returned";
				} exception ex {
				"abort:*" =>	*cc = *c; raise ex;
				"more:*" =>	raise "internal error, repeat needs more chars";
				"consumed:*" =>	{}
				"change:*" =>	*cc = *c; modeset(Command0); xdone();
				"done:*" =>	*cc = *c; raise ex;
				"moveonly:*" =>	raise "internal error, repeat was just movement";  # inspect cmdprev
				"edit:*" =>	raise "internal error, repeat required edit input";
				}
		'q' =>
			recordq(c);
		* =>
			case x {
			'v' or
			'V' =>
				if(x == 'v')
					modeset(Visual);
				else
					modeset(Visualline);
				visualstart = cursor.clone();
				visualend = visualstart.clone();
				visualset();
			'c' =>
				(num2, ce) := commandmove(c, num1, 'c');
				if(ce == nil)
					ce = cursor.mvline(num1*num2, Colpastnewline);
				textdel(Cchange|Csetcursorlo|Csetreg, nil, ce);
				modeset(Insert);
			'C' =>
				textdel(Cchange|Csetcursorlo|Csetreg, nil, cursor.mvlineend(0));
				modeset(Insert);
			's' =>
				cs = cursor.clone();
				ce := cs.mvchar(+num1);
				textdel(Cchange|Csetcursorlo|Csetreg, cs, ce);
				modeset(Insert);
			'S' =>
				textdel(Cchange|Csetcursorlo|Csetreg, cursor.mvcol(0), cursor.mvline(num1-1, Colpastnewline));
				modeset(Insert);
			'i' =>
				modeset(Insert);
			'I' =>
				cursorset(cursor.mvfirst());
				modeset(Insert);
			'a' =>
				cursorset(cursor.mvchar(+1));
				modeset(Insert);
			'A' =>
				cursorset(cursor.mvlineend(0));
				modeset(Insert);
			'o' =>
				modeset(Insert);
				textins(Cchange|Csetcursorhi, cursor.mvlineend(0), "\n");
			'O' =>
				modeset(Insert);
				textins(Cchange|Csetcursorlo, cursor.mvcol(0), "\n");
			'R' =>
				modeset(Replace);
			'"' =>
				xregset(c.xget());
			* =>
				c = cc.clone();
				move(c, 1, Setjump, ce := cursor.clone());
				cursorset(ce);
				*cc = *c;
				xmoveonly();
			}
			*cc = *c;
			xconsumed();
		}
		*cc = *c;
		xdone();
	}
	*cc = *c;
	xchange();
}
