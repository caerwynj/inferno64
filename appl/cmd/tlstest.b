implement Tlstest;

include "sys.m";
	sys: Sys;

include "draw.m";

include "tls.m";
	tls: Tls;

Tlstest: module {
	PATH: con "/dis/cmd/tlstest.dis";
	init: fn(ctxt: ref Draw->Context, args: list of string);
};

init(nil: ref Draw->Context, args: list of string)
{
	sys = load Sys Sys->PATH;
	sys->bind("#T", "/dev", Sys->MAFTER);
	tls = load Tls Tls->PATH;
	if(tls == nil){
		sys->fprint(sys->fildes(2), "tlstest: cannot load Tls module: %r\n");
		raise "fail:load";
	}

	addr := "tcp!google.com!443";
	servername := "google.com";
	if(args != nil) {
		args = tl args;
		if(args != nil){
			addr = hd args;
			args = tl args;
		}
		if(args != nil)
			servername = hd args;
	}

	sys->print("dialing %s...\n", addr);
	(ok, conn) := sys->dial(addr, nil);
	if(ok < 0){
		sys->fprint(sys->fildes(2), "tlstest: dial %s: %r\n", addr);
		raise "fail:dial";
	}

	sys->print("starting TLS handshake (sni=%s)...\n", servername);
	(tlsfd, err) := tls->tlsclient(conn.dfd, servername);
	if(tlsfd == nil){
		sys->fprint(sys->fildes(2), "tlstest: tlsclient: %s\n", err);
		raise "fail:tls";
	}

	sys->print("TLS handshake succeeded!\n");

	req := sys->sprint("GET / HTTP/1.0\r\nHost: %s\r\nConnection: close\r\n\r\n", servername);
	reqb := array of byte req;
	sys->write(tlsfd, reqb, len reqb);

	buf := array[4096] of byte;
	n := sys->read(tlsfd, buf, len buf);
	if(n > 0)
		sys->print("%s\n", string buf[0:n]);
	else
		sys->print("(no data read)\n");
}
