# keep track of vixen instances, register plumb dst "edit" and forward plumb messages

implement Vixenplumb;

include "sys.m";
	sys: Sys;
	sprint: import sys;
include "draw.m";
	draw: Draw;
include "arg.m";
include "string.m";
	str: String;
include "plumbmsg.m";
	plumbmsg: Plumbmsg;
	Msg: import plumbmsg;
include "sh.m";
	sh: Sh;
include "names.m";
	names: Names;

Vixenplumb: module {
	init:	fn(ctxt: ref Draw->Context, argv: list of string);
};

dflag := 0;

Client: adt {
	fid:	int;
	path:	string;  # path being edited
	rc:	Sys->Rread;  # for read
	pending:	string;  # pending string for next rc

	text:	fn(c: self ref Client): string;
};

Client.text(c: self ref Client): string
{
	return sprint("Client(fid %d, path %q, rc nil %d, pending %q)", c.fid, c.path, c.rc == nil, c.pending);
}


clients: list of ref Client;
drawcontext: ref Draw->Context;

Iomax: con 8*1024;  # max file2chan message size, also in vixenplumbreader() in vixen

init(ctxt: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	if(ctxt == nil)
		fail("no window context");
	drawcontext = ctxt;
	draw = load Draw Draw->PATH;
	arg := load Arg Arg->PATH;
	str = load String String->PATH;
	plumbmsg = load Plumbmsg Plumbmsg->PATH;
	sh = load Sh Sh->PATH;
	sh->initialise();
	names = load Names Names->PATH;

	sys->pctl(Sys->NEWPGRP, nil);

	arg->init(args);
	arg->setusage(arg->progname()+" [-d] [path]");
	while((c := arg->opt()) != 0)
		case c {
		'd' =>	dflag++;
		* =>	arg->usage();
		}
	args = arg->argv();
	pathpat: string;
	case len args {
	0 =>	{}
	1 =>	pathpat = hd args;
	* =>	arg->usage();
	}

	if(plumbmsg->init(0, "edit", 0) < 0)
		fail(sprint("plumb init: %r"));

	fio := sys->file2chan("/chan", "vixenplumb");
	if(fio == nil)
		fail(sprint("file2chan: %r"));

	msgc := chan of ref Msg;
	spawn plumbreceiver(msgc);

	if(pathpat != nil) {
		wd := workdir();
		spawn edit(wd, pathget(wd, pathpat));
	}

	spawn serve(fio, msgc);
}

serve(fio: ref Sys->FileIO, msgc: chan of ref Msg)
{
	for(;;) alt {
	m := <-msgc =>
		if(m == nil)
			fail("nil plumbmsg received");
		handle(m);
		
	(nil, count, fid, rc) := <-fio.read =>
		if(rc == nil) {
			del(fid);
		} else if(count < Iomax) {
			rc <-= (nil, sprint("read > Iomax (%d)", Iomax));
		} else {
			putrc(fid, rc);
		}
		
	(nil, data, fid, rc) := <-fio.write =>
		if(rc == nil)
			del(fid);
		else {
			err := set(fid, string data);
			rc <-= (len data, err);
		}
	}
}

# given a working dir and a pathpat consisting of either absolute or relative path
# and an optional colon and address, return the final path and the pattern
pathget(wd, pathpat: string): (string, string)
{
	(path, pat) := str->splitstrr(pathpat, ":");
	if(path == nil) {
		path = pat;
		pat = nil;
	} else
		path = path[:len path-1];
	if(!str->prefix("/", path) && !str->prefix("#", path))
		path = wd+"/"+path;
	if(pat == nil)
		pat = ".";
	path = names->cleanname(path);
	return (path, pat);
}

edit(wd: string, pathpat: (string, string))
{
	sys->pctl(Sys->FORKNS, nil);  # separate working directory
	(path, pat) := pathpat;
	sys->chdir(wd);
	say(sprint("edit, wd %q, path %q, pat %q", wd, path, pat));
	if(pat == nil)
		args := list of {"wm/vixen", path};
	else
		args = list of {"wm/vixen", "-c", ":"+pat, path};
	sh->run(drawcontext, args);
}

write(fd: ref Sys->FD, s: string, pidc: chan of int, rc: chan of (int, string))
{
	pidc <-= pid();
	if(sys->write(fd, buf := array of byte s, len buf) != len buf)
		rc <-= (0, sprint("write: %r"));
}

runeditnew(fd0: ref Sys->FD, dir: string, pidc: chan of int, rc: chan of (int, string))
{
	pidc <-= pid();
	sys->pctl(Sys->NEWFD|Sys->FORKNS|Sys->FORKENV, list of {fd0.fd, 1, 2});
	sys->dup(fd0.fd, 0);
	err := sh->run(drawcontext, list of {"wm/vixen", "-i", dir});
	rc <-= (1, err);
}

editnew(dir, data: string)
{
	sys->pctl(Sys->FORKNS, nil);  # separate working directory
	if(sys->chdir(dir) < 0)
		return warn(sprint("chdir %q: %r", dir));
	
	sys->pctl(Sys->NEWFD, list of {1, 2});
	if(sys->pipe(fd0 := array[2] of ref Sys->FD) < 0)
		return warn(sprint("pipe: %r"));

	pidc := chan of int;
	rc := chan of (int, string); # done, err
	spawn write(fd0[0], data, pidc, rc);
	writepid := <-pidc;
	spawn runeditnew(fd0[1], dir, pidc, rc);
	runpid := <-pidc;
	fd0 = nil;

	(done, err) := <-rc;
	if(err != nil)
		warn(err);
	kill(writepid);
	if(!done)
		killgrp(runpid);
}

handle(m: ref Msg)
{
	# see if it exists, if so, send it the pattern
	# otherwise, start a new wm/vixen
	say(sprint("msg: %s", string m.pack()));
	case m.kind {
	"text" =>
		(path, pat) := pathget(m.dir, string m.data);
		c := findpath(path);
		if(c == nil) {
			spawn edit(m.dir, (path, pat));
		} else {
			c.pending = pat;
			respond(c);
		}
	"newtext" =>
		c := findpath(m.dir);
		if(c == nil) {
			spawn editnew(names->cleanname(m.dir), string m.data);
		} else {
			c.pending = string m.data;
			respond(c);
		}
	* =>
		return warn(sprint("kind %q ignored", m.kind));
	}
}

respond(c: ref Client)
{
	say(sprint("respond, c %s", c.text()));
	if(c.rc != nil && c.pending != nil) {
		c.rc <-= (array of byte c.pending, nil);
		c.rc = nil;
		c.pending = nil;
	}
}

putrc(fid: int, rc: Sys->Rread)
{
	say(sprint("putrc, fid %d", fid));
	for(l := clients; l != nil; l = tl l) {
		c := hd l;
		if(c.fid == fid) {
			if(c.rc != nil)
				rc <-= (nil, "one read at a time please");
			else {
				c.rc = rc;
				respond(c);
			}
			return;
		}
	}
	c := ref Client (fid, nil, rc, "");
	clients = c::clients;
	say(sprint("putrc, new client %s", c.text()));
}

del(fid: int)
{
	nc: list of ref Client;
	for(l := clients; l != nil; l = tl l)
		if((hd l).fid != fid)
			nc = hd l::nc;
	clients = nc;
}

findpath(path: string): ref Client
{
	for(l := clients; l != nil; l = tl l)
		if((hd l).path == path)
			return hd l;
	return nil;
}

set(fid: int, path: string): string
{
	o := findpath(path);
	for(l := clients; l != nil; l = tl l) {
		c := hd l;
		if(c.fid == fid) {
			if(o != nil && o != c)
				return "file already open";
			say(sprint("new path for client, fid %d, old path %q, new path %q", fid, c.path, path));
			c.path = path;
			return nil;
		}
	}
	c := ref Client (fid, path, nil, "");
	clients = c::clients;
	say(sprint("set, new client %s", c.text()));
	return nil;
}

plumbreceiver(msgc: chan of ref Msg)
{
	for(;;)
		msgc <-= Msg.recv();
}

workdir(): string
{
	return sys->fd2path(sys->open(".", Sys->OREAD));
}

pid(): int
{
	return sys->pctl(0, nil);
}

progctl(pid: int, s: string)
{
	sys->fprint(sys->open(sprint("/prog/%d/ctl", pid), sys->OWRITE), "%s", s);
}

kill(pid: int)
{
	progctl(pid, "kill");
}

killgrp(pid: int)
{
	progctl(pid, "killgrp");
}

say(s: string)
{
	if(dflag)
		warn(s);
}

warn(s: string)
{
	sys->fprint(sys->fildes(2), "%s\n", s);
}

fail(s: string)
{
	warn(s);
	killgrp(pid());
	raise "fail:"+s;
}
