Cmd: adt {
	i:	int; # index of next char to return
	s:	string;
	n1,
	n2:	string;

	new:		fn(): ref Cmd;
	mk:		fn(s: string): ref Cmd;
	clone:		fn(c: self ref Cmd): ref Cmd;
	char:		fn(c: self ref Cmd): int;
	get:		fn(c: self ref Cmd): int;
	xget:		fn(c: self ref Cmd): int;
	put:		fn(c: self ref Cmd, c: int);
	unget:		fn(c: self ref Cmd);
	havenum:	fn(c: self ref Cmd): int;
	more:		fn(c: self ref Cmd): int;
	rem:		fn(c: self ref Cmd): string;
	num1:		fn(c: self ref Cmd, def: int): int;
	num2:		fn(c: self ref Cmd, def: int): int;
	getint:		fn(c: self ref Cmd, def: int): int;
	getnum:		fn(c: self ref Cmd): string;
	xgetnum:	fn(c: self ref Cmd): string;
	getnum1:	fn(c: self ref Cmd);
	getnum2:	fn(c: self ref Cmd);
	xgetnum1:	fn(c: self ref Cmd);
	xgetnum2:	fn(c: self ref Cmd);
	str:		fn(c: self ref Cmd): string;
	text:		fn(c: self ref Cmd): string;
};

Cmd.new(): ref Cmd
{
	return Cmd.mk(nil);
}

Cmd.mk(s: string): ref Cmd
{
	return ref Cmd (0, s, "", "");
}

Cmd.clone(c: self ref Cmd): ref Cmd
{
	return ref *c;
}

Cmd.char(c: self ref Cmd): int
{
	if(c.i >= len c.s)
		return -1;
	return c.s[c.i];
}

Cmd.get(c: self ref Cmd): int
{
	if(c.i >= len c.s)
		return -1;
	return c.s[c.i++];
}

Cmd.xget(c: self ref Cmd): int
{
	if(!c.more())
		raise "more:";
	x := c.get();
	if(x == kb->Esc)
		raise "abort:";
	return x;
}

Cmd.put(c: self ref Cmd, x: int)
{
	c.s[len c.s] = x;
}

Cmd.unget(c: self ref Cmd)
{
	if(c.i <= 0)
		raise "unget at index <= 0";
	--c.i;
}

# whether we have a whole num in the buffer
Cmd.havenum(c: self ref Cmd): int
{
	x := c.char();
	if(x < 0 || !str->in(x, "1-9"))
		return 0;
	# look for a non-num to finish the num
	for(i := c.i+1; i < len c.s; i++) {
		x = c.s[i];
		if(x < '0' || x > '9')
			return 1;
	}
	return 0;
}

Cmd.more(c: self ref Cmd): int
{
	return c.i < len c.s;
}

Cmd.rem(c: self ref Cmd): string
{
	return c.s[c.i:];
}

Cmd.num1(c: self ref Cmd, def: int): int
{
	if(c.n1 == nil)
		return def;
	return int c.n1;
}

Cmd.num2(c: self ref Cmd, def: int): int
{
	if(c.n2 == nil)
		return def;
	return int c.n2;
}

# getint reads as many digits as possible.
# getnum below is for movements, where a num is only complete if it ends with a non-digit.
Cmd.getint(c: self ref Cmd, def: int): int
{
	s: string;
	while(c.more() && str->in(c.char(), "0-9"))
		s[len s] = c.get();
	if(s != nil)
		def = int s;
	return def;
}

Cmd.getnum(c: self ref Cmd): string
{
	s := "";
	if(c.havenum()) {
		s[len s] = c.get();
		while(c.more() && str->in(c.char(), "0-9"))
			s[len s] = c.get();
	}
	return s;
}

Cmd.xgetnum(c: self ref Cmd): string
{
	x := c.char();
	if(x >= 0 && str->in(x, "1-9") && !c.havenum())
		raise "more:";
	return c.getnum();
}

Cmd.getnum1(c: self ref Cmd)
{
	c.n1 = c.getnum();
}

Cmd.getnum2(c: self ref Cmd)
{

	c.n2 = c.getnum();
}

Cmd.xgetnum1(c: self ref Cmd)
{
	c.n1 = c.xgetnum();
}

Cmd.xgetnum2(c: self ref Cmd)
{
	c.n2 = c.xgetnum();
}

Cmd.str(c: self ref Cmd): string
{
	return c.s;
}

Cmd.text(c: self ref Cmd): string
{
	return sprint("Cmd(i=%d, s=%q, n1=%q, n2=%q)", c.i, c.s, c.n1, c.n2);
}

