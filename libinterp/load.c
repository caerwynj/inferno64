#include "lib9.h"
#include "isa.h"
#include "interp.h"
#include "raise.h"
#include <kernel.h>

#define DP if(0){}else print
#define DNP if(1){}else print
#define	A(r)	*((Array**)(r))

Module*	modules;
int	dontcompile = 1; /* TODO compiler is broken on amd64 atleast */

static s32
operand(uchar **p)
{
	int c;
	uchar *cp;

	cp = *p;
	c = cp[0];
	switch(c & 0xC0) {
	case 0x00:
		*p = cp+1;
		return c;
	case 0x40:
		*p = cp+1;
		return c|~0x7F;
	case 0x80:
		*p = cp+2;
		if(c & 0x20)
			c |= ~0x3F;
		else
			c &= 0x3F;
		return (c<<8)|cp[1];		
	case 0xC0:
		*p = cp+4;
		if(c & 0x20)
			c |= ~0x3F;
		else
			c &= 0x3F;
		return (c<<24)|(cp[1]<<16)|(cp[2]<<8)|cp[3];		
	}
	return 0;	
}

static s32
disw(uchar **p)
{
	s32 v;
	uchar *c;

	c = *p;
	v  = c[0] << 24;
	v |= c[1] << 16;
	v |= c[2] << 8;
	v |= c[3];
	*p = c + 4;
	return v;
}

double
canontod(u32 v[2])
{
	union { double d; u32 ul[2]; } a;
	/*print("| 0 0x%ux 1 0x%ux |", v[0], v[1]);*/
	a.d = 1.;
	/*print(".");*/
	if(a.ul[0]) {
		a.ul[0] = v[0];
		a.ul[1] = v[1];
	}
	else {
		a.ul[1] = v[0];
		a.ul[0] = v[1];
	}
	/*print(",");*/
	return a.d;
}

Module*
load(char *path)
{
	return readmod(path, nil, 0);
}

int
brpatch(Inst *ip, Module *m)
{
	switch(ip->op) {
	case ICALL:
	case IJMP:
	case IBEQW:
	case IBNEW:
	case IBLTW:
	case IBLEW:
	case IBGTW:
	case IBGEW:
	case IBEQB:
	case IBNEB:
	case IBLTB:
	case IBLEB:
	case IBGTB:
	case IBGEB:
	case IBEQF:
	case IBNEF:
	case IBLTF:
	case IBLEF:
	case IBGTF:
	case IBGEF:
	case IBEQC:
	case IBNEC:
	case IBLTC:
	case IBLEC:
	case IBGTC:
	case IBGEC:
	case IBEQL:
	case IBNEL:
	case IBLTL:
	case IBLEL:
	case IBGTL:
	case IBGEL:
	case ISPAWN:
		if(ip->d.imm < 0 || ip->d.imm >= m->nprog)
			return 0;
		ip->d.imm = (intptr)&m->prog[ip->d.imm];
		break;
	}
	return 1;
}

void
asmstring(intptr offset, uchar* absoluteoffset, String* stored, int len, uchar *s)
{
	uchar *se;
	int c;

	USED(offset);
	DNP("\tstring\t@mp+%zd=0x%p,len %d at 0x%p:\"", offset, absoluteoffset, len, stored);
	se = s + len;
	for(; s < se; s++){
		c = *s;
		if(c == '\n')
			DNP("\\n");
		else if(c == '\0')
			DNP("\\z");
		else if(c == '"')
			DNP("\\\"");
		else if(c == '\\')
			DNP("\\\\");
		else
			DNP("%c", c);
	}
	DNP("\"\n");
}

Module*
parsemod(char *path, uchar *code, u32 length, Dir *dir)
{
	Heap *h;
	Inst *ip;
	Type *pt;
	String *s;
	Module *m;
	Array *ary;
	u32 ul[2];
	WORD lo, hi;
	int lsize, id, tnp, tsz, siglen;
	int de, isize, dsize, hsize, dasp;
	uchar *mod, sm, *istream, **isp, *si, *addr, *dastack[DADEPTH], *e, *b;
	Link *l;
	intptr i, n, v, pc, entry, entryt;

	DNP("\tsource\t\"%s\"\n", path);
	istream = code;
	isp = &istream;

	m = malloc(sizeof(Module));
	if(m == nil)
		return nil;

	m->dev = dir->dev;
	m->dtype = dir->type;
	m->qid = dir->qid;
	m->mtime = dir->mtime;
	m->origmp = H;
	m->pctab = nil;

	switch(operand(isp)) {
	default:
		kwerrstr("bad magic");
		goto bad;
	case SMAGIC:
		siglen = operand(isp);
		n = length-(*isp-code);
		if(n < 0 || siglen > n){
			kwerrstr("corrupt signature");
			goto bad;
		}
		if(verifysigner(*isp, siglen, *isp+siglen, n-siglen) == 0) {
			kwerrstr("security violation");
			goto bad;
		}
		*isp += siglen;
		break;		
	case XMAGIC:
		if(mustbesigned(path, code, length, dir)){
			kwerrstr("security violation: not signed");
			goto bad;
		}
		break;
	}

	m->rt = operand(isp);
	m->ss = operand(isp);
	isize = operand(isp);
	dsize = operand(isp);
	hsize = operand(isp);
	lsize = operand(isp);
	entry = operand(isp);
	entryt = operand(isp);

	if(isize < 0 || dsize < 0 || hsize < 0 || lsize < 0) {
		kwerrstr("implausible Dis file");
		goto bad;
	}

	DNP("parsemod before instructions isize %d dsize %d hsize %d"
		" lsize %d entry 0x%zx entryt 0x%zx sizeof(Inst) %d\n",
		isize, dsize, hsize, lsize, entry, entryt, sizeof(Inst));
	m->nprog = isize;
	m->prog = mallocz(isize*sizeof(Inst), 0);
	if(m->prog == nil) {
		kwerrstr(exNomem);
		goto bad;
	}

	m->ref = 1;
	ip = m->prog;
	for(i = 0; i < isize; i++) {
		ip->op = *istream++;
		ip->add = *istream++;
		ip->reg = 0;
		ip->s.imm = 0;
		ip->d.imm = 0;
		switch(ip->add & ARM) {
		case AXIMM:
		case AXINF:
		case AXINM:
			ip->reg = operand(isp);
		 	break;
		}
		switch(UXSRC(ip->add)) {
		case SRC(AFP):
		case SRC(AMP):	
		case SRC(AIMM):
			ip->s.ind = operand(isp);
			break;
		case SRC(AIND|AFP):
		case SRC(AIND|AMP):
			ip->s.i.f = operand(isp);
			ip->s.i.s = operand(isp);
			break;
		}
		switch(UXDST(ip->add)) {
		case DST(AFP):
		case DST(AMP):	
			ip->d.ind = operand(isp);
			break;
		case DST(AIMM):
			ip->d.ind = operand(isp);
			if(brpatch(ip, m) == 0) {
				kwerrstr("bad branch addr");
				goto bad;
			}
			break;
		case DST(AIND|AFP):
		case DST(AIND|AMP):
			ip->d.i.f = operand(isp);
			ip->d.i.s = operand(isp);
			break;
		}
		if(i % 10 == 0)
			DNP("#%p\n", ip);
		DNP("	%d %zd %D\n", i, (intptr)ip, ip);
		ip++;		
	}

	DNP("\tentry\t0,%d\n",hsize);
	m->ntype = hsize;
	m->type = malloc(hsize*sizeof(Type*));
	if(m->type == nil) {
		kwerrstr(exNomem);
		goto bad;
	}
	for(i = 0; i < hsize; i++) {
		id = operand(isp);
		if(id > hsize) {
			kwerrstr("heap id range");
			goto bad;
		}
		tsz = operand(isp);
		tnp = operand(isp);
		if(tsz < 0 || tnp < 0 || tnp > 128*1024){
			kwerrstr("implausible Dis file");
			goto bad;
		}
		pt = dtype(freeheap, tsz, istream, tnp);
		if(pt == nil) {
			kwerrstr(exNomem);
			goto bad;
		}
		DNP("\tdesc\t$%d 0x%p has 0x%p of size %d nptrs %d:\"",
			id, m->type+id, pt, tsz, tnp);
		for(e = istream; e < istream+tnp; e++)
			DNP("%.2x", *e);
		DNP("\"\n");
		istream += tnp;
		m->type[id] = pt;
	}

	if(dsize != 0) {
		pt = m->type[0];
		if(pt == 0 || pt->size != dsize) {
			kwerrstr("bad desc for mp");
			goto bad;
		}
		h = heapz(pt);
		m->origmp = H2D(uchar*, h);
		DNP("\tm->origmp 0x%p belongs to heap at 0x%p, uses type at 0x%p\n",
			m->origmp, h, pt);
	}
	addr = m->origmp;
	dasp = 0;
	DNP("\tvar\t@mp, size %d\n", dsize);
	for(;;) {
		sm = *istream++;
		if(sm == 0)
			break;
		n = DLEN(sm);
		if(n == 0)
			n = operand(isp);
		v = operand(isp);
		si = addr + v;
		switch(DTYPE(sm)) {
		default:
			kwerrstr("bad data item");
			goto bad;
		case DEFS:
			s = c2string((char*)istream, n);
			asmstring(v, si, s, n, istream);
			istream += n;
			*(String**)si = s;
			break;
		case DEFB:
			DNP("\tbyte\t@mp+%d", v);
			for(i = 0; i < n; i++){
				DNP(",%d", *istream & 0xff);
				*si++ = *istream++;
			}
			DNP(" n=%d\n", n);
			break;
		case DEFW:
			DNP("\tword\t@mp+%d len %d:", v, n);
			for(i = 0; i < n; i++) {
				*(WORD*)si = disw(isp);
				DNP(" 0x%zx", *(WORD*)si);
				si += sizeof(WORD);
			}
			DNP("\n");
			break;
		case DEFL:
			DNP("\tlong\t@mp+%d", v);
			for(i = 0; i < n; i++) {
				hi = disw(isp);
				lo = disw(isp);
				*(LONG*)si = (LONG)hi << 32 | (LONG)(u32)lo;
				DNP(",%lld 0x%zx", *(LONG*)si, *(LONG*)si);
				si += sizeof(LONG);
			}
			DNP("\n");
			break;
		case DEFF:
			DNP("\treal\t@mp+%d", v);
			for(i = 0; i < n; i++) {
				DNP(" raw: ");
				for(int j = 0; j<8; j++){
					DNP(" 0x%x", ((u8*)isp)[j]);
				}
				ul[0] = disw(isp);
				ul[1] = disw(isp);
				/*print("canontod ul[0] 0x%x ul[1] 0x%x ", ul[0], ul[1]);*/
				*(REAL*)si = canontod(ul);
				/*DNP("__");
				DNP(",%g", *(REAL*)si);
				DNP("--");*/
				si += sizeof(REAL);
			}
			DNP("\n");
			break;
		case DEFA:			/* Array */
			DNP("\tarray\t@mp+%d", v);
			v = disw(isp);
			if(v < 0 || v > m->ntype) {
				kwerrstr("bad array type");
				goto bad;
			}
			DNP(",$%d", v);
			pt = m->type[v];
			v = disw(isp);
			DNP(",%d", v);
			h = nheap(sizeof(Array)+(pt->size*v));
			h->t = &Tarray;
			h->t->ref++;
			ary = H2D(Array*, h);
			ary->t = pt;
			ary->len = v;
			ary->root = H;
			ary->data = (uchar*)ary+sizeof(Array);
			memset((void*)ary->data, 0, pt->size*v);
			for(i=(intptr)ary->data;
				i < v;
				i++){
				DNP(",%d",*(uchar*)(i+ary));
			}
			DNP("\n");
			initarray(pt, ary);
			A(si) = ary;
			break;			
		case DIND:			/* Set index */
			ary = A(si);
			if(ary == H || D2H(ary)->t != &Tarray) {
				kwerrstr("ind not array");
				goto bad;
			}
			DNP("\tindir\t@mp+%d", v);
			v = disw(isp);
			if(v > ary->len || v < 0 || dasp >= DADEPTH) {
				kwerrstr("array init range");
				goto bad;
			}
			dastack[dasp++] = addr;
			addr = ary->data+v*ary->t->size;
			DNP(",%d,%zd 0x%zx\n",
				v, (intptr)ary->data+v*ary->t->size,
				(intptr)ary->data+v*ary->t->size);
			break;
		case DAPOP:
			if(dasp == 0) {
				kwerrstr("pop range");
				goto bad;
			}
			DNP("\tapop\n");
			addr = dastack[--dasp];
			break;
		}
	}
	/*DNP("		Initialized origmp\n");
	for(int i = 0; i < m->type[0]->size/(sizeof(intptr)); i++){
		DNP("\t\t0x%p\t%zx\n", (intptr*)m->origmp+i, *((intptr*) m->origmp+i));
	}*/
	mod = istream;
	if(memchr(mod, 0, 128) == 0) {
		kwerrstr("bad module name");
		goto bad;
	}
	m->name = strdup((char*)mod);
	if(m->name == nil) {
		kwerrstr(exNomem);
		goto bad;
	}
	DNP("\tmodule\t%s\n", m->name);
	while(*istream++)
		;

	l = m->ext = (Link*)malloc((lsize+1)*sizeof(Link));
	if(l == nil){
		kwerrstr(exNomem);
		goto bad;
	}
	for(i = 0; i < lsize; i++, l++) {
		pc = operand(isp);
		de = operand(isp);
		v  = disw(isp);
		pt = nil;
		if(de != -1)
			pt = m->type[de];
		mlink(m, l, istream, v, pc, pt);
		if(de != -1){
			DNP("\tlink\tidx %d, type %d size %d np %d ",
				i, de, pt->size, pt->np);
			if(pt->np > 0){
				DNP("map");
				for(b = pt->map; b < pt->map+pt->np; b++)
					DNP(" %.2x", *b);
				DNP(" ");
			}
			DNP(", pc %zd, sig 0x%ux,\"%s\"\n",
				pc, v, (char*)istream);
		}else
			DNP("\tlink\tidx %d type %d, pc %zd, sig 0x%ux,\"%s\"\n",
				i, de, pc, v, (char*)istream);
		while(*istream++)
			;
	}
	l->name = nil;

	if(m->rt & HASLDT0){
		kwerrstr("obsolete dis");
		goto bad;
	}

	if(m->rt & HASLDT){
		int j, nl;
		Import *i1, **i2;

		nl = operand(isp);
		i2 = m->ldt = (Import**)malloc((nl+1)*sizeof(Import*));
		if(i2 == nil){
			kwerrstr(exNomem);
			goto bad;
		}
		DNP("\tldts\t@ldt,%d\n", nl);
		for(i = 0; i < nl; i++, i2++){
			n = operand(isp);
			DNP("\text\t@ldts+%d,%d,%zd\n",
				i, n, (intptr)i2-(intptr)m->ldt);
			i1 = *i2 = (Import*)malloc((n+1)*sizeof(Import));
			if(i1 == nil){
				kwerrstr(exNomem);
				goto bad;
			}
			for(j = 0; j < n; j++, i1++){
				i1->sig = disw(isp);
				i1->name = strdup((char*)istream);
				if(i1->name == nil){
					kwerrstr(exNomem);
					goto bad;
				}
				DNP("\text\t@ldt+%zd,idx %d, sig 0x%ux,\"%s\"\n",
					(intptr)i1-(intptr)m->ldt,
					j, i1->sig, (char*)istream);
				while(*istream++)
					;
			}
		}
		istream++;
	}

	if(m->rt & HASEXCEPT){
		s32 j, nh, descid;
		Handler *h;
		Except *e;

		nh = operand(isp);
		m->htab = malloc((nh+1)*sizeof(Handler));
		if(m->htab == nil){
			kwerrstr(exNomem);
			goto bad;
		}
		DNP("\texceptions\t%d\n", nh);
		h = m->htab;
		for(i = 0; i < nh; i++, h++){
			h->eoff = operand(isp);
			h->pc1 = operand(isp);
			h->pc2 = operand(isp);
			descid = operand(isp);
			if(n != -1)
				h->t = m->type[descid];
			n = operand(isp); /* no of labels */
			h->ne = n>>16;
			n &= 0xffff;
			h->etab = malloc((n+1)*sizeof(Except));
			if(h->etab == nil){
				kwerrstr(exNomem);
				goto bad;
			}
			e = h->etab;
			DNP("\texception\t%d: offset %zd pc1 %zd pc2 %zd"
				" desc %d nlab %d ne %zd\n",
				i, h->eoff, h->pc1, h->pc2,
				descid, n, h->ne);
			for(j = 0; j < n; j++, e++){
				e->s = strdup((char*)istream);
				if(e->s == nil){
					kwerrstr(exNomem);
					goto bad;
				}
				while(*istream++)
					;
				e->pc = operand(isp);
				DNP("\texctab\t\"%s\", %zd\n", e->s, e->pc);
			}
			e->s = nil;
			e->pc = operand(isp);
			DNP("\texctab\t*, %zd\n", e->pc);
		}
		istream++;
	}

	m->entryt = nil;
	m->entry = m->prog;
	if(entry < isize && entryt < hsize) {
		m->entry = &m->prog[entry];
		m->entryt = m->type[entryt];
	}

	if(cflag) {
		if((m->rt&DONTCOMPILE) == 0 && !dontcompile)
			compile(m, isize, nil);
	}
	else
	if(m->rt & MUSTCOMPILE && !dontcompile) {
		if(compile(m, isize, nil) == 0) {
			kwerrstr("compiler required");
			goto bad;
		}
	}

	m->path = strdup(path);
	if(m->path == nil) {
		kwerrstr(exNomem);
		goto bad;
	}
	DNP("\tsource\t\"%s\"\n", m->path);
	m->link = modules;
	modules = m;

	return m;
bad:
	destroy(m->origmp);
	freemod(m);
	return nil;
}

Module*
newmod(char *s)
{
	Module *m;

	m = malloc(sizeof(Module));
	if(m == nil)
		error(exNomem);
	m->ref = 1;
	m->path = s;
	m->origmp = H;
	m->name = strdup(s);
	if(m->name == nil) {
		free(m);
		error(exNomem);
	}
	m->link = modules;
	modules = m;
	m->pctab = nil;
	return m;
}

Module*
lookmod(char *s)
{
	Module *m;

	for(m = modules; m != nil; m = m->link)
		if(strcmp(s, m->path) == 0) {
			m->ref++;
			return m;
		}
	return nil;
}

void
freemod(Module *m)
{
	int i;
	Handler *h;
	Except *e;
	Import *i1, **i2;

	if(m->type != nil) {
		for(i = 0; i < m->ntype; i++)
			freetype(m->type[i]);
		free(m->type);
	}
	free(m->name);
	free(m->prog);
	free(m->path);
	free(m->pctab);
	if(m->ldt != nil){
		for(i2 = m->ldt; *i2 != nil; i2++){
			for(i1 = *i2; i1->name != nil; i1++)
				free(i1->name);
			free(*i2);
		}
		free(m->ldt);
	}
	if(m->htab != nil){
		for(h = m->htab; h->etab != nil; h++){
			for(e = h->etab; e->s != nil; e++)
				free(e->s);
			free(h->etab);
		}
		free(m->htab);
	}
	free(m);
}

void
unload(Module *m)
{
	Module **last, *mm;

	m->ref--;
	if(m->ref > 0)
		return;
	if(m->ref == -1)
		abort();

	last = &modules;
	for(mm = modules; mm != nil; mm = mm->link) {
		if(mm == m) {
			*last = m->link;
			break;
		}
		last = &mm->link;
	}

	if(m->rt == DYNMOD)
		freedyncode(m);
	else
		destroy(m->origmp);

	destroylinks(m);

	freemod(m);
}
