implement Epubcontainer;

include "sys.m";
	sys: Sys;

include "draw.m";

include "bufio.m";

include "xml.m";
	xml: Xml;
	Attributes, Locator, Parser: import xml;

include "epubcontainer.m";

Zipfs: module {
	init:	fn(nil: ref Draw->Context, args: list of string);
};

mountpoint: con "/mnt/epub";
mounted := 0;

init(xmlmod: Xml): string
{
	sys = load Sys Sys->PATH;
	xml = xmlmod;
	return nil;
}

open(f: string, warnings: chan of (Xml->Locator, string)): (string, string)
{
	if(mounted)
		close();

	# make path absolute so zipfs can find it after namespace fork
	if(f == nil || len f == 0)
		return (nil, "empty file path");
	if(f[0] != '/'){
		fd := sys->open(".", Sys->OREAD);
		if(fd == nil)
			return (nil, sys->sprint("cannot get cwd: %r"));
		cwd := sys->fd2path(fd);
		if(cwd == nil)
			return (nil, sys->sprint("fd2path: %r"));
		f = cwd + "/" + f;
	}

	# fork namespace so mount is local to this process
	sys->pctl(Sys->FORKNS, nil);

	# create mount point
	sys->create(mountpoint, Sys->OREAD, Sys->DMDIR | 8r755);

	# set up pipe for styx communication with zipfs
	p := array[2] of ref Sys->FD;
	if(sys->pipe(p) < 0)
		return (nil, sys->sprint("pipe: %r"));

	spawn runzipfs(p[0], f);
	p[0] = nil;

	if(sys->mount(p[1], nil, mountpoint, Sys->MREPL, nil) < 0)
		return (nil, sys->sprint("mount zipfs: %r"));
	p[1] = nil;
	mounted = 1;

	# parse META-INF/container.xml to find the OPF rootfile
	containerpath := mountpoint + "/META-INF/container.xml";
	(opfpath, err) := parsecontainer(containerpath, warnings);
	if(err != nil){
		close();
		return (nil, err);
	}

	return (mountpoint + "/" + opfpath, nil);
}

close()
{
	if(mounted){
		sys->unmount(nil, mountpoint);
		mounted = 0;
	}
}

runzipfs(srvfd: ref Sys->FD, zippath: string)
{
	sys->dup(srvfd.fd, 0);
	srvfd = nil;

	zipfs := load Zipfs "/dis/zip/zipfs.dis";
	if(zipfs == nil){
		sys->fprint(sys->fildes(2), "epubcontainer: cannot load zipfs: %r\n");
		return;
	}
	zipfs->init(nil, "zipfs" :: zippath :: nil);
}

parsecontainer(f: string, warnings: chan of (Xml->Locator, string)): (string, string)
{
	(x, err) := xml->open(f, warnings, nil);
	if(x == nil)
		return (nil, "cannot open container.xml: " + err);

	# look for <container><rootfiles><rootfile full-path="..." .../>
	while((xi := x.next()) != nil){
		pick t := xi {
		Tag =>
			if(t.name == "container"){
				x.down();
				while((xi2 := x.next()) != nil){
					pick t2 := xi2 {
					Tag =>
						if(t2.name == "rootfiles"){
							x.down();
							while((xi3 := x.next()) != nil){
								pick t3 := xi3 {
								Tag =>
									if(t3.name == "rootfile"){
										path := t3.attrs.get("full-path");
										if(path != nil)
											return (path, nil);
									}
								}
							}
							x.up();
						}
					}
				}
				x.up();
			}
		}
	}
	return (nil, "no rootfile found in container.xml");
}
