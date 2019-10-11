IOBuf: module
{
	PATH: con "/dis/lib/iobuf.dis";

	init: fn();

	ReadBuf: adt{
		new:		fn(fd: ref Sys->FD, bufsize: int): ref ReadBuf;
		newc:		fn(queuesize, bufsize: int): ref ReadBuf;
		setsep:		fn(r: self ref ReadBuf, sep: string, strip: int);
		reads:		fn(r: self ref ReadBuf): array of byte;
		readn:		fn(r: self ref ReadBuf, n: int): array of byte;
		fill:		fn(r: self ref ReadBuf, data: array of byte, wc: Sys->Rwrite);
		# Internal:
		buf:		array of byte;
		s:		int;
		e:		int;
		sep:		array of byte;
		strip:		int;
		reader:		ref fn(r: ref ReadBuf): int;
		is_eof:		int;
		fd:		ref Sys->FD;
		leftover:	array of byte;
		queue:		chan of array of byte;
		pending:	chan of (array of byte, Sys->Rwrite);
		is_pending:	chan of int;
	};

	WriteBuf: adt{
		new:		fn(fd: ref Sys->FD, bufsize: int): ref WriteBuf;
		newc:		fn(bufsize: int): ref WriteBuf;
		write:		fn(w: self ref WriteBuf, buf: array of byte);
		writeln:	fn(w: self ref WriteBuf, buf: array of byte);
		flush:		fn(w: self ref WriteBuf);
		eof:		fn(w: self ref WriteBuf);
		request:	fn(w: self ref WriteBuf, n: int, rc: Sys->Rread);
		# Internal:
		buf:		array of byte;
		s:		int;
		e:		int;
		writer:		ref fn(w: ref WriteBuf);
		fd:		ref Sys->FD;
		pending:	chan of (int, Sys->Rread);
	};
};
