Tls: module
{
	PATH:	con	"$Tls";

	tlsclient:	fn(fd: ref Sys->FD, servername: string): (ref Sys->FD, string);
	tlsserver:	fn(fd: ref Sys->FD): (ref Sys->FD, string);
};
