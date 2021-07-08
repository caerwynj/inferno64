#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

extern Rootdata rootdata[];
extern Dirtab roottab[];
extern int	rootmaxq;

static Chan*
rootattach(char *spec)
{
	int i;
	ulong len;
	Rootdata *r;

	if(*spec)
		error(Ebadspec);
	for (i = 0; i < rootmaxq; i++){
		r = &rootdata[i];
		if (r->sizep){
			len = *r->sizep;
			r->size = len;
			roottab[i].length = len;
		}
	}
	return devattach('/', spec);
}

static int
rootgen(Chan *c, char *name, Dirtab *tab, int nd, int s, Dir *dp)
{
	int p, i;
	Rootdata *r;

	if(s == DEVDOTDOT){
		p = rootdata[c->qid.path].dotdot;
		c->qid.path = p;
		c->qid.type = QTDIR;
		name = "#/";
		if(p != 0){
			for(i = 0; i < rootmaxq; i++)
				if(roottab[i].qid.path == c->qid.path){
					name = roottab[i].name;
					break;
				}
		}
		devdir(c, c->qid, name, 0, eve, 0555, dp);
		return 1;
	}
	if(name != nil){
		isdir(c);
		r = &rootdata[(int)c->qid.path];
		tab = r->ptr;
		for(i=0; i<r->size; i++, tab++)
			if(strcmp(tab->name, name) == 0){
				devdir(c, tab->qid, tab->name, tab->length, eve, tab->perm, dp);
				return 1;
			}
		return -1;
	}
	if(s >= nd)
		return -1;
	tab += s;
	devdir(c, tab->qid, tab->name, tab->length, eve, tab->perm, dp);
	return 1;
}

static Walkqid*
rootwalk(Chan *c, Chan *nc, char **name, s32 nname)
{
	u32 p;

	p = c->qid.path;
	if(nname == 0)
		p = rootdata[p].dotdot;
	return devwalk(c, nc, name, nname, rootdata[p].ptr, rootdata[p].size, rootgen);
}

static s32
rootstat(Chan *c, uchar *dp, s32 n)
{
	int p;

	p = rootdata[c->qid.path].dotdot;
	return devstat(c, dp, n, rootdata[p].ptr, rootdata[p].size, rootgen);
}

static Chan*
rootopen(Chan *c, u32 omode)
{
	int p;

	p = rootdata[c->qid.path].dotdot;
	return devopen(c, omode, rootdata[p].ptr, rootdata[p].size, rootgen);
}

/*
 * sysremove() knows this is a nop
 */
static void	 
rootclose(Chan*)
{
}

static s32
rootread(Chan *c, void *buf, s32 n, s64 offset)
{
	u32 p, len;
	uchar *data;

	p = c->qid.path;
	if(c->qid.type & QTDIR)
		return devdirread(c, buf, n, rootdata[p].ptr, rootdata[p].size, rootgen);
	len = rootdata[p].size;
	if(offset < 0 || offset >= len)
		return 0;
	if(offset+n > len)
		n = len - offset;
	data = rootdata[p].ptr;
	memmove(buf, data+offset, n);
	return n;
}

static s32
rootwrite(Chan*, void*, s32, s64)
{
	error(Eperm);
	return 0;
}

Dev rootdevtab = {
	'/',
	"root",

	devreset,
	devinit,
	devshutdown,
	rootattach,
	rootwalk,
	rootstat,
	rootopen,
	devcreate,
	rootclose,
	rootread,
	devbread,
	rootwrite,
	devbwrite,
	devremove,
	devwstat,
};
