filter1(cmd: string, fd0, fd1: ref Sys->FD, stderr: int, resc: chan of (string, string), pidc: chan of int)
{
	pidc <-= pid();
	sys->pctl(Sys->NEWFD|Sys->FORKNS|Sys->FORKENV, list of {fd0.fd, fd1.fd, 2});
	sys->dup(fd0.fd, 0);
	sys->dup(fd1.fd, 1);
	if(stderr)
		sys->dup(fd1.fd, 2);
	fd0 = fd1 = nil;
	err := sh->system(drawcontext, cmd);
	if(err != nil)
		resc <-= (nil, err);
}

writer(fd: ref Sys->FD, s: string, resc: chan of (string, string), pidc: chan of int)
{
	pidc <-= pid();
	if(sys->write(fd, buf := array of byte s, len buf) != len buf)
		resc <-= (nil, sprint("writing to command: %r"));
}

reader(fd: ref Sys->FD, resc: chan of (string, string), pidc: chan of int)
{
	pidc <-= pid();
	s := "";
	b := bufio->fopen(fd, Bufio->OREAD);
	if(b == nil) {
		resc <-= (nil, sprint("fopen: %r"));
		return;
	}
	for(;;)
	case c := b.getc() {
	Bufio->EOF =>
		resc <-= (s, nil);
		return;
	Bufio->ERROR =>
		resc <-= (nil, sprint("reading from command: %r"));
		return;
	* =>
		s[len s] = c;
	}
}

filter0(cmd, input: string, stderr: int, outc: chan of (string, string))
{
	sys->pctl(Sys->NEWFD, list of {2});
	fd0 := array[2] of ref Sys->FD;
	fd1 := array[2] of ref Sys->FD;
	if(sys->pipe(fd0) < 0 || sys->pipe(fd1) < 0) {
		outc <-= (nil, sprint("pipe: %r"));
		return;
	}
	pidc := chan of int;
	resc := chan of (string, string);
	spawn writer(fd0[1], input, resc, pidc);
	wpid := <-pidc;
	spawn reader(fd1[1], resc, pidc);
	rpid := <-pidc;
	spawn filter1(cmd, fd0[0], fd1[0], stderr, resc, pidc);
	fpid := <-pidc;
	fd0 = fd1 = nil;

	(res, err) := <-resc;
	kill(wpid);
	kill(rpid);
	kill(fpid);
	outc <-= (res, err);
}

filter(cmd, input: string, stderr: int): (string, string)
{
	spawn filter0(cmd, input, stderr, outc := chan of (string, string));
	return <-outc;
}
