#include "lib9.h"
#include "kernel.h"
#include <isa.h>
#include "interp.h"
#include "runt.h"
#include "tlsmod.h"
#include <libsec.h>
#include "raise.h"

extern Sys_FD*	mkfd(int fd);

void
Tls_tlsclient(void *fp)
{
	F_Tls_tlsclient *f;
	int sfd, infd;
	TLSconn conn;
	char *sname;

	f = fp;
	f->ret->t0 = H;
	f->ret->t1 = H;

	if(f->fd == H)
		error("nil fd");
	infd = f->fd->fd;

	memset(&conn, 0, sizeof conn);
	sname = nil;
	if(f->servername != H)
		sname = string2c(f->servername);
	conn.serverName = sname;

	sfd = tlsClient(infd, &conn);
	/* do NOT free sname: string2c returns ptr into String object, not a heap alloc */

	if(sfd < 0){
		char ebuf[ERRMAX];
		kgerrstr(ebuf, sizeof ebuf);
		f->ret->t0 = H;
		f->ret->t1 = c2string(ebuf, strlen(ebuf));
		return;
	}
	f->ret->t0 = mkfd(sfd);
	f->ret->t1 = H;
}

void
Tls_tlsserver(void *fp)
{
	F_Tls_tlsserver *f;
	int sfd, infd;
	TLSconn conn;

	f = fp;
	f->ret->t0 = H;
	f->ret->t1 = H;

	if(f->fd == H)
		error("nil fd");
	infd = f->fd->fd;

	memset(&conn, 0, sizeof conn);

	sfd = tlsServer(infd, &conn);
	if(sfd < 0){
		char ebuf[ERRMAX];
		kgerrstr(ebuf, sizeof ebuf);
		f->ret->t0 = H;
		f->ret->t1 = c2string(ebuf, strlen(ebuf));
		return;
	}
	f->ret->t0 = mkfd(sfd);
	f->ret->t1 = H;
}

void
tlsmodinit(void)
{
	builtinmod("$Tls", Tlsmodtab, Tlsmodlen);
}
