implement Transport;

include "common.m";
include "transport.m";

tls: Tls;

# local copies from CU
sys: Sys;
U: Url;
	Parsedurl: import U;
S: String;
DI: Dial;
CU: CharonUtils;
	Netconn, ByteSource, Header, config : import CU;

GEMINID:	con 1965;	# Default Gemini port
BLOCKSIZE:	con 4096;

dbg := 0;

init(c: CharonUtils)
{
	CU = c;
	sys = load Sys Sys->PATH;
	U = load Url Url->PATH;
	if(U != nil)
		U->init();
	S = load String String->PATH;
	DI = load Dial Dial->PATH;
	dbg = int (CU->config).dbg['n'];
}

connect(nc: ref Netconn, bs: ref ByteSource)
{
	dialhost := nc.host;
	dialport := string nc.port;
	addr := DI->netmkaddr(dialhost, "net", dialport);
	err := "";
	if(dbg)
		sys->print("gemini %d: dialing %s\n", nc.id, addr);
	nc.conn = DI->dial(addr, nil);
	if(nc.conn == nil) {
		syserr := sys->sprint("%r");
		if(S->prefix("cs: dns: no translation found", syserr))
			err = "unknown host";
		else
			err = sys->sprint("couldn't connect: %s", syserr);
	}
	else {
		if(dbg) {
			sys->print("gemini %d: connected, starting TLS\n", nc.id);
			if(nc.conn.dfd != nil)
				sys->print("gemini %d: dfd=%d\n", nc.id, nc.conn.dfd.fd);
			else
				sys->print("gemini %d: dfd is nil!\n", nc.id);
		}
		if(tls == nil) {
			m := load Tls Tls->PATH;
			if(m == nil)
				err = sys->sprint("can't load Tls module: %r");
			else
				tls = m;
		}
		if(err == "")
			(nc.tlsfd, err) = tls->tlsclient(nc.conn.dfd, nc.host);
		if(dbg) {
			if(nc.tlsfd != nil)
				sys->print("gemini %d: tlsfd=%d\n", nc.id, nc.tlsfd.fd);
			else
				sys->print("gemini %d: tls failed: %s\n", nc.id, err);
		}
	}
	if(err == "") {
		nc.connected = 1;
		nc.state = CU->NCgethdr;
	}
	else {
		if(dbg)
			sys->print("gemini %d: connection failed: %s\n", nc.id, err);
		bs.err = err;
		closeconn(nc);
	}
}

writereq(nc: ref Netconn, bs: ref ByteSource)
{
	u := bs.req.url;
	reqstr := u.tostring() + "\r\n";
	reqbytes := array of byte reqstr;
	if(dbg)
		sys->print("gemini %d: sending request: %s", nc.id, reqstr);
	n := sys->write(nc.tlsfd, reqbytes, len reqbytes);
	if(n < 0) {
		bs.err = sys->sprint("error writing request: %r");
		closeconn(nc);
	}
}

gethdr(nc: ref Netconn, bs: ref ByteSource)
{
	hdr := Header.new();
	hdr.actual = bs.req.url;
	hdr.base = bs.req.url;

	# Read the response header line: <STATUS><SPACE><META>\r\n
	# Maximum header is 2 + 1 + 1024 + 2 = 1029 bytes
	buf := array[1030] of byte;
	i := 0;
	for(;;) {
		if(i >= len buf) {
			bs.err = "gemini response header too long";
			closeconn(nc);
			return;
		}
		n := sys->read(nc.tlsfd, buf[i:i+1], 1);
		if(n <= 0) {
			bs.err = "gemini: unexpected EOF reading header";
			closeconn(nc);
			return;
		}
		i++;
		if(i >= 2 && buf[i-2] == byte '\r' && buf[i-1] == byte '\n')
			break;
	}

	# Strip trailing \r\n
	line := string buf[0:i-2];
	if(dbg)
		sys->print("gemini %d: response: %s\n", nc.id, line);

	if(len line < 2) {
		bs.err = "gemini: malformed response header";
		closeconn(nc);
		return;
	}

	# Parse status code (two digits)
	status := 0;
	for(j := 0; j < 2 && j < len line; j++) {
		c := int line[j];
		if(c < '0' || c > '9') {
			bs.err = "gemini: invalid status code";
			closeconn(nc);
			return;
		}
		status = status * 10 + (c - '0');
	}

	# Parse meta (after space)
	meta := "";
	if(len line > 3 && line[2] == ' ')
		meta = line[3:];
	else if(len line > 2)
		meta = line[2:];

	if(dbg)
		sys->print("gemini %d: status=%d meta=%s\n", nc.id, status, meta);

	hdr.length = -1;	# unknown, read until EOF

	case status / 10 {
	1 =>
		# Input request - display prompt as a page
		hdr.code = CU->HCOk;
		hdr.mtype = CU->TextGemini;
		# Synthesize a page with the prompt text
		# Store prompt in tbuf so getdata returns it
		prompt := "# Input Requested\n\n" + meta + "\n";
		nc.tbuf = array of byte prompt;
		bs.hdr = hdr;
		closeconn(nc);
		return;
	2 =>
		# Success
		hdr.code = CU->HCOk;
		if(meta == "" || meta == "text/gemini")
			hdr.mtype = CU->TextGemini;
		else
			setmtype(hdr, meta);
	3 =>
		# Redirect
		if(status == 31)
			hdr.code = CU->HCMovedPerm;
		else
			hdr.code = CU->HCMovedTemp;
		if(meta != "") {
			rurl := U->parse(meta);
			if(rurl.scheme == nil)
				rurl = U->mkabs(rurl, bs.req.url);
			hdr.location = rurl;
		}
		hdr.mtype = CU->TextPlain;
	4 or 5 =>
		# Temporary/Permanent failure
		if(status == 51)
			hdr.code = CU->HCNotFound;
		else if(status == 53)
			hdr.code = CU->HCForbidden;
		else
			hdr.code = CU->HCServerError;
		hdr.msg = meta;
		hdr.mtype = CU->TextGemini;
		# Synthesize error page
		errpage := "# Error " + string status + "\n\n" + meta + "\n";
		nc.tbuf = array of byte errpage;
		bs.hdr = hdr;
		closeconn(nc);
		return;
	6 =>
		# Client certificate required
		hdr.code = CU->HCForbidden;
		hdr.msg = "Client certificate required: " + meta;
		hdr.mtype = CU->TextGemini;
		errpage := "# Certificate Required\n\n" + meta + "\n";
		nc.tbuf = array of byte errpage;
		bs.hdr = hdr;
		closeconn(nc);
		return;
	* =>
		bs.err = "gemini: unknown status " + string status;
		closeconn(nc);
		return;
	}

	bs.hdr = hdr;
}

# Parse MIME type from meta field, set hdr.mtype
setmtype(hdr: ref Header, meta: string)
{
	# Extract type before any parameters (;charset= etc)
	ty := meta;
	for(i := 0; i < len ty; i++)
		if(ty[i] == ';') {
			# Check for charset parameter
			parms := ty[i+1:];
			ty = ty[0:i];
			setcharset(hdr, parms);
			break;
		}
	ty = strip(ty);
	# Look up in the media type table
	hdr.setmediatype("", array[0] of byte);
	# Try direct match against known types
	for(j := 0; j < len CU->mnames; j++) {
		if(CU->mnames[j] == S->tolower(ty)) {
			hdr.mtype = j;
			return;
		}
	}
	# Unknown type - try file extension guessing from URL
	# or fall back to octet-stream
	hdr.mtype = CU->UnknownType;
}

setcharset(hdr: ref Header, parms: string)
{
	# Look for charset=value
	s := S->tolower(strip(parms));
	if(S->prefix("charset=", s))
		hdr.chset = strip(s[8:]);
}

strip(s: string): string
{
	i := 0;
	while(i < len s && (s[i] == ' ' || s[i] == '\t'))
		i++;
	j := len s;
	while(j > i && (s[j-1] == ' ' || s[j-1] == '\t'))
		j--;
	return s[i:j];
}

getdata(nc: ref Netconn, bs: ref ByteSource): int
{
	if(bs.data == nil || bs.edata >= len bs.data) {
		closeconn(nc);
		return 0;
	}
	buf := bs.data[bs.edata:];
	n := len buf;
	if(nc.tbuf != nil) {
		# Return synthesized content (error/input pages)
		if(n >= len nc.tbuf) {
			n = len nc.tbuf;
			buf[:] = nc.tbuf;
			nc.tbuf = nil;
			return n;
		}
		buf[:] = nc.tbuf[:n];
		nc.tbuf = nc.tbuf[n:];
		return n;
	}
	fd := nc.tlsfd;
	if(fd == nil) {
		# Connection already closed (synthesized pages)
		return 0;
	}
	n = sys->read(fd, buf, n);
	if(dbg > 1)
		sys->print("gemini %d: read %d bytes\n", nc.id, n);
	if(n <= 0) {
		closeconn(nc);
		if(n < 0)
			bs.err = sys->sprint("%r");
	}
	return n;
}

defaultport(nil: string): int
{
	return GEMINID;
}

closeconn(nc: ref Netconn)
{
	nc.tlsfd = nil;
	nc.conn = nil;
	nc.connected = 0;
}
