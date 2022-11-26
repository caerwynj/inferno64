#include "lib9.h"
#include "isa.h"
#include "interp.h"
#include "kernel.h"
#include "dynld.h"
#define DBG if(0) print

static int debug = 0;

Module*
readmod(char *path, Module *m, int sync)
{
	Dir *d;
	int fd, n, dynld;
	uchar *code;
	Module *ans;
	u32 length;

	if(path[0] == '$') {
		if(m == nil)
			kwerrstr("module not built-in");
		return m;
	}

	ans = nil;
	code = nil;
	length = 0;
	dynld = 0;

	if(sync)
		release();

	d = nil;
	fd = kopen(path, OREAD);
	if(fd < 0){
		DBG("readmod path %s, fd < 0\n", path);
		goto done;
	}

	if((d = kdirfstat(fd)) == nil){
		DBG("readmod (d = kdirfstat(fd)) == nil for path %s\n", path);
		goto done;
	}

	if(m != nil) {
		if(d->dev == m->dev && d->type == m->dtype &&
		   d->mtime == m->mtime &&
		   d->qid.type == m->qid.type && d->qid.path == m->qid.path && d->qid.vers == m->qid.vers) {
			DBG("readmod check failed for path %s\n", path);
			ans = m;
			goto done;
		}
	}

	if(d->length < 0 || d->length >= 8*1024*1024){
		kwerrstr("implausible length");
		goto done;
	}
	if((d->mode&0111) && dynldable(fd)){
		dynld = 1;
		goto done1;
	}
	length = d->length;
	code = mallocz(length, 0);
	if(code == nil)
		goto done;

	n = kread(fd, code, length);
	if(n != length) {
		DBG("readmod kread failed on path %s length %d, read n %d\n", path, length, n);
		free(code);
		code = nil;
	}
done:
	if(fd >= 0)
		kclose(fd);
done1:
	if(sync)
		acquire();
	if(m != nil && ans == nil)
		unload(m);
	if(code != nil) {
		ans = parsemod(path, code, length, d);
		free(code);
	}
	else if(dynld){
		kseek(fd, 0, 0);
		ans = newdyncode(fd, path, d);
		kclose(fd);
	}
	free(d);
	return ans;
}
