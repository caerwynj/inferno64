ex(s: string)
{
	{
		err := ex0(s, cursor);
		if(err != nil)
			statuswarn(err);
	} exception x {
	"ex:*" =>
		statuswarn(x[len "ex:":]);
	}
}

exerror(s: string)
{
	raise "ex:"+s;
}

exgetc(c: ref Cmd): int
{
	if(!c.more())
		exerror(sprint("command not complete: %s", c.str()));
	return c.get();
}

SepRequired, SepOptional: con iota;
exreadsep(c: ref Cmd, sep: int)
{
	if(!c.more() || !str->in(c.char(), " \t")) {
		if(sep == SepRequired)
			exerror("missing whitespace separator");
	} else {
		while(str->in(c.char(), " \t"))
			c.get();
	}
}

RemNonempty, RemEmpty: con iota;
exrem(c: ref Cmd, rem: int): string
{
	s := c.rem();
	if(s == nil && rem == RemNonempty)
		exerror("empty parameter");
	return s;
}

exempty(c: ref Cmd)
{
	if(c.more())
		exerror("trailing characters");
}

exnoaddr(c: ref Cursor)
{
	if(c != nil)
		exerror("illegal address");
}

# pass in end of range, must be nil
exnorange(c: ref Cursor)
{
	if(c != nil)
		exerror("illegal range");
}

optget(c: ref Cmd, x: int): int
{
	if(c.char() != x)
		return 0;
	c.get();
	return 1;
}

# interpret remainder of Cmd as filename or filter, read/execute it and return result
exreadarg(c: ref Cmd): string
{
	exreadsep(c, SepOptional);
	filt := optget(c, '!');
	exreadsep(c, SepOptional);

	cmd := exrem(c, RemNonempty);
	if(filt)
		(res, err) := filter(cmd, "", 0);
	else
		(res, err) = readfile(cmd);
	if(err != nil)
		exerror(err);
	return res;
}

ex0(excmd: string, dot: ref Cursor): string
{
	if(excmd == nil)
		return nil;

	c := Cmd.mk(excmd);
	(cs, ce, err) := range(c, dot);
	if(err != nil)
		return "bad range: "+err;
	(csdef, cedef) := (cs, ce);
	if(csdef == nil)
		csdef = dot.mvcol(0);
	if(cedef == nil)
		cedef = csdef.mvlineend(1);

	case x := c.get() {
	'!' =>
		# :!command		run command
		# :addr!command		replace line with output from command (that gets the original line as input)
		# :addr,addr!command	replace lines ...
		cmd := c.rem();
		say('x', sprint("! on %q", cmd));
		if(cs == nil) {
			err = sh->system(drawcontext, cmd);
			if(err != nil)
				return "error: "+err;
		} else {
			if(ce == nil) {
				cs = cs.mvcol(0);
				ce = cs.mvline(1, Colstart);
			}
			txt := text.get(cs, ce);
			say('x', sprint("input is: %q", txt));
			res: string;
			(res, err) = filter(cmd, txt, 1);
			if(err != nil) {
				statuswarn("error: "+err);
				res = err;
			}
			say('x', "result is: "+res);
			textdel(Cchange|Csetcursorlo, cs, ce);
			textins(Cchange, nil, res);
		}
	's' =>
		# if no range, then current line (cursor) only.
		# if 1 address, only that line.
		# otherwise, substitute in that range
		if(cs == nil)
			cs = dot;
		if(ce == nil) {
			cs = cs.mvcol(0);
			ce = cs.mvlineend(1);
		}
		sep := exgetc(c);
		src, dst: string;
		(src, err) = patternget(c, sep);
		if(err == nil)
			(dst, err) = patternget(c, sep);
		if(err != nil)
			return "missing parameters";
		g := optget(c, 'g');
		exempty(c);
		err = substitute(cs, ce, src, dst, g);
		if(err != nil)
			return err;
	'r' =>
		if(cs == nil)
			cs = dot.mvlineend(1);
		if(ce != nil)
			cs = ce.mvlineend(1);

		res := exreadarg(c);
		textins(Cchange|Csetcursorhi, cs, res);
	'w' or
	'q' =>
		if(cs != nil && ce == nil)
			ce = cs.mvlineend(1);
		c.unget();
		w := optget(c, 'w');
		q := optget(c, 'q');
		force := optget(c, '!');

		if(q && cs != nil)
			return "range not allowed";

		ofilename: string;
		exreadsep(c, SepOptional);
		append := 0;
		if(c.more()) {
			ofilename = c.rem();
			if(str->prefix(">>", ofilename)) {
				append = 1;
				ofilename = ofilename[len ">>":];
			} else if(filename == nil)
				filenameset(ofilename);
		} else
			ofilename = filename;

		err: string;
		if(w) {
			if(append)
				err = textappend(ofilename, cs, ce);
			else
				err = textwrite(force, ofilename, cs, ce);
			if(err != nil)
				statuswarn(err);
			else {
				statuswarn("written");
				if(!append && cs == nil)
					modified = 0;
			}
		}
		if(q) {
			if(err == nil && (!modified || force))
				quit();
			if(err == nil)
				statuswarn("unsaved changes, use :q!");
		}
	'x' =>
		force := optget(c, '!');
		exempty(c);
		writemodifiedquit(force);
	'c' =>
		case exgetc(c) {
		'd' =>
			# change dir.  ignore range/address.
			exreadsep(c, SepRequired);
			if(sys->chdir(exrem(c, RemNonempty)) < 0)
				exerror(sprint("cd: %r"));
		* =>
			exerror(sprint("bad ex command: %q", excmd));
		}
	'f' =>
		if(!c.more()) {
			if(filename == nil)
				statuswarn("(no filename)");
			else
				statuswarn(filename);
		} else {
			exreadsep(c, SepRequired);
			filenameset(exrem(c, RemNonempty));
			filefd = nil;
			statusset();
		}
	'g' =>
		# [range]g[!]/pattern/command
		not := optget(c, '!');

		pat: string;
		(pat, err) = patternget(c, exgetc(c));
		if(err != nil)
			return err;
		# xxx on empty pat, use last?
		
		re: Regex->Re;
		(re, err) = regex->compile(pat, 0);
		if(err != nil)
			return "bad regex: "+err;
		exreadsep(c, SepOptional);
		arg := exrem(c, RemNonempty);

		# below needs more care: 
		# first all changes must be collected (one for each matching line)
		# then they all must be executed.
		return "'g' not yet supported";

		while(Cursor.cmp(csdef, cedef) < 0) {
			s := text.get(csdef, csdef.mvlineend(0));
			a := regex->executese(re, s, (0, len s), 1, 1);
			match := len a >= 1 && a[0].t0 >= 0;
			if(match && !not || !match && not) {
				{
					err = ex0(arg, cs);
					if(err != nil)
						return err;
				} exception ex {
				"ex:*" =>
					return ex[len "ex:":];
				}
			}
			csdef = csdef.mvlineend(1);
		}
	'D' =>
		# toggle debug string
		exreadsep(c, SepOptional);
		s := exrem(c, RemNonempty);
		for(i := 0; i < len s; i++)
			case y := s[i] {
			'-' =>		debug = array[128] of {* => 0};
			'+' =>		debug = array[128] of {* => 1};
			'a' to 'z' =>	debug[y] = !debug[y];
			* =>	exerror(sprint("bad debug char %c", y));
			}
	'b' =>
		s: string;
		if(!c.more()) {
			(s, err) = regget('!');
			if(err == nil && s == nil)
				err = "no previous command";
		} else {
			exreadsep(c, SepRequired);
			s = exrem(c, RemNonempty);
		}
		r: string;
		if(err == nil)
			(r, err) = filter(s, "", 1);
		say('x', sprint(":b on %q, err %q, r %q", s, err, r));
		if(err != nil)
			exerror(err);
		plumb(r, "newtext", workdir());
		err = regput('!', s);
		if(err != nil)
			exerror(err);
		
	* =>
		if(x >= 0)
			c.unget();
		exempty(c);
		if(ce != nil)
			cs = nil;
		if(cs == nil)
			break;
		cursorset(cs.mvfirst());
	}
	return nil;
}

# read & evaluate an address.
address(c: ref Cmd, dot: ref Cursor): (ref Cursor, string)
{
	if(dot == nil)
		raise "missing dot";
	n := 0;
	exreadsep(c, SepOptional);
Address:
	while(c.more()) {
		case x := c.get() {
		'.' =>	{}
		'$' =>	dot = text.pos(Pos (text.lines(), 0));
		'0' to '9' =>
			c.unget();
			line := int c.getint(0);
			dot = text.pos(Pos (max(1, line), 0));
		'+' or
		'-' =>
			mult := 1;
			if(x == '-')
				mult = -1;
			dot = dot.mvline(mult*c.getint(1), Colkeep);
		'/' or
		'?' =>
			(pat, err) := patternget(c, x);
			if(err != nil)
				return (nil, "bad pattern: "+err);
			re: Regex->Re;
			(re, err) = regex->compile(pat, 0);
			if(err != nil)
				return (nil, "bad regex: "+err);
			(cs, nil) := search(x == '?', 0, re, dot);
			if(cs == nil)
				return (nil, sprint("pattern %q not found", pat));
			dot = cs;
		'\'' =>
			if(!c.more())
				return (nil, "incomplete mark address");
			x = c.get();
			err: string;
			(dot, err) = markget(x);
			if(err != nil)
				return (nil, err);
		* =>
			c.unget();
			break Address;
		}
		n++;
		exreadsep(c, SepOptional);
	}
	if(n == 0)
		dot = nil;
	return (dot, nil);
}

range(c: ref Cmd, dot: ref Cursor): (ref Cursor, ref Cursor, string)
{
	if(!c.more())
		return (nil, nil, nil);
	case c.get() {
	'%' =>	return (text.cursor(0), text.end(), nil);
	'*' =>	return (nil, nil, "range '*' not implemented");
	}
	c.unget();
	(cs, err) := address(c, dot);
	ce: ref Cursor;
	if(err == nil && cs != nil && (c.char() == ',' || c.char() == ';')) {
		if(c.get() == ';')
			dot = cs;
		(ce, err) = address(c, dot);
	}
	return (cs, ce, err);
}

# read until sep or until end of string
patternget(c: ref Cmd, sep: int): (string, string)
{
	if(str->in(sep, "a-zA-Z0-9 \t\n\"|"))
		return (nil, sprint("bad separator %c", sep));
	s: string;
	while(c.more()) {
		x := c.get();
		if(x == sep)
			break;
		case x {
		'\\' =>
			if(!c.more())
				return (nil, "pattern unfinished");
			if(c.char() == sep)
				x = c.get();
		}
		s[len s] = x;
	}
	return (s, nil);
}
