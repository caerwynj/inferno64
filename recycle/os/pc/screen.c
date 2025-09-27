#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"
#include "io.h"
#include "ureg.h"
#include "../port/pci.h"
#include "../port/error.h"

#include <draw.h>
#include <memdraw.h>
#include <cursor.h>
#include "screen.h"

#define RGB2K(r,g,b)	((156763*(r)+307758*(g)+59769*(b))>>19)

extern VGAcur vgasoftcur;

Point ZP = {0, 0};

Rectangle physgscreenr;
Cursorinfo cursor;	/* TO DO */

Memdata gscreendata;
Memimage *gscreen;

VGAscr vgascreen[1];

char *tiltstr[4] = {
	"none",
	"left",
	"inverted",
	"right",
};

Cursor	arrow = {
	{ -1, -1 },
	{ 0xFF, 0xFF, 0x80, 0x01, 0x80, 0x02, 0x80, 0x0C, 
	  0x80, 0x10, 0x80, 0x10, 0x80, 0x08, 0x80, 0x04, 
	  0x80, 0x02, 0x80, 0x01, 0x80, 0x02, 0x8C, 0x04, 
	  0x92, 0x08, 0x91, 0x10, 0xA0, 0xA0, 0xC0, 0x40, 
	},
	{ 0x00, 0x00, 0x7F, 0xFE, 0x7F, 0xFC, 0x7F, 0xF0, 
	  0x7F, 0xE0, 0x7F, 0xE0, 0x7F, 0xF0, 0x7F, 0xF8, 
	  0x7F, 0xFC, 0x7F, 0xFE, 0x7F, 0xFC, 0x73, 0xF8, 
	  0x61, 0xF0, 0x60, 0xE0, 0x40, 0x40, 0x00, 0x00, 
	},
};

static Point
tiltpt(int tilt, Point dim, Point p)
{
	switch(tilt&3){
	case 1:	return Pt(dim.y-p.y-1, p.x);
	case 2:	return Pt(dim.x-p.x-1, dim.y-p.y-1);
	case 3:	return Pt(p.y, dim.x-p.x-1);
	}
	return p;
}

static Rectangle
tiltrect(int tilt, Point dim, Rectangle r)
{
	switch(tilt&3){
	case 1:	return Rect(dim.y-r.max.y, r.min.x, dim.y-r.min.y, r.max.x);
	case 2:	return Rect(dim.x-r.max.x, dim.y-r.max.y, dim.x-r.min.x, dim.y-r.min.y);
	case 3:	return Rect(r.min.y, dim.x-r.max.x, r.max.y, dim.x-r.min.x);
	}
	return r;
}

static Point
tiltsize(int tilt, Point dim)
{
	return (tilt & 1) != 0 ? Pt(dim.y, dim.x) : dim;
}

Rectangle
actualscreensize(VGAscr *scr)
{
	return Rpt(ZP, tiltsize(-scr->tilt, scr->gscreen->clipr.max));
}

void
setactualsize(VGAscr *scr, Rectangle r)
{
	qlock(&drawlock);

	r.min = ZP;
	r.max = tiltsize(scr->tilt, r.max);
	if(rectclip(&r, scr->gscreen->r) == 0){
		qunlock(&drawlock);
		return;
	}
	scr->gscreen->clipr = r;

	qunlock(&drawlock);
}

static char*
setscreensize0(VGAscr *scr, int width, int height, int depth, ulong chan, int tilt)
{
	int bpp, pitch;

	scr->gscreendata = nil;
	scr->gscreen = nil;
	if(gscreen != nil){
		freememimage(gscreen);
		gscreen = nil;
	}
	if(scr->paddr == 0){
		if(scr->dev && scr->dev->page){
			scr->vaddr = KADDR(VGAMEM());
			scr->apsize = 1<<16;
		}
		scr->softscreen = 1;
	}

	depth = chantodepth(chan);
	bpp = (depth+7) / 8;
	pitch = ((width * depth+31) & ~31) / 8;

	if(tilt)
		scr->softscreen = 1;
	if(scr->softscreen){
		gscreen = allocmemimage(Rpt(ZP, tiltsize(tilt, Pt(width, height))), chan);
		scr->useflush = 1;
	}else{
		static Memdata md;

		md.ref = 1;
		if((md.bdata = scr->vaddr) == 0)
			error("framebuffer not maped");
		gscreen = allocmemimaged(Rpt(ZP, Pt(width, height)), chan, &md);
		scr->useflush = scr->dev && scr->dev->flush;
	}
	if(gscreen == nil)
		return "no memory for vga memimage";

	scr->bpp = bpp;
	scr->pitch = pitch;
	scr->width = width;
	scr->height = height;
	scr->tilt = tilt & 3;

	scr->palettedepth = 6;	/* default */
	scr->memdefont = getmemdefont();
	scr->gscreen = gscreen;
	scr->gscreendata = gscreen->data;

	return nil;
}

void
setscreensize(VGAscr *scr, int x, int y, int z, ulong chan, int tilt)
{
	char *err;

	qlock(&drawlock);
	if(waserror()){
		qunlock(&drawlock);
		nexterror();
	}

	if(memimageinit() < 0)
		error("memimageinit failed");

	lock(&vgascreenlock);
	if(waserror()){
		unlock(&vgascreenlock);
		nexterror();
	}

	err = setscreensize0(scr, x, y, z, chan, tilt);
	if(err != nil)
		error(err);

	vgaimageinit(chan);
	bootscreenconf(scr);

	unlock(&vgascreenlock);
	poperror();

	drawcmap();

	if(scr->cur && scr->cur != &vgasoftcur){
		cursoroff();
		setcursor(&cursor);
		cursoron(0);
	}

	qunlock(&drawlock);
	poperror();
}

int
screensize(int x, int y, int z, ulong chan)
{
	VGAscr *scr;

	memimageinit();
	scr = &vgascreen[0];

	/*
	 * BUG: need to check if any xalloc'ed memory needs to
	 * be given back if aperture is set.
	 */
	if(scr->aperture == 0){
		int width = (x*z)/BI2WD;

		gscreendata.bdata = xalloc(width*BY2WD*y);
		if(gscreendata.bdata == 0)
			error("screensize: vga soft memory");
/*		memset(gscreendata.bdata, 0x72, width*BY2WD*y);	 not really black */
		scr->useflush = 1;
		scr->aperture = VGAMEM();
		scr->apsize = 1<<16;
	}
	else
		gscreendata.bdata = KADDR(scr->aperture);

	if(gscreen)
		freememimage(gscreen);

	gscreen = allocmemimaged(Rect(0,0,x,y), chan, &gscreendata);
	vgaimageinit(chan);
	if(gscreen == nil)
		return -1;

	if(scr->dev && scr->dev->flush)
		scr->useflush = 1;

	scr->palettedepth = 6;	/* default */
	scr->gscreendata = &gscreendata;
	scr->memdefont = getmemdefont();
	scr->gscreen = gscreen;

	physgscreenr = gscreen->r;

	drawcmap();
	return 0;
}

int
screenaperture(int size, int align)
{
	VGAscr *scr;
	ulong aperture;

	scr = &vgascreen[0];

	if(size == 0){
		if(scr->aperture && scr->isupamem)
			upafree(scr->aperture, scr->apsize);
		scr->aperture = 0;
		scr->isupamem = 0;
		return 0;
	}
	if(scr->dev && scr->dev->linear){
		aperture = scr->dev->linear(scr, &size, &align);
		if(aperture == 0)
			return 1;
	}else{
		aperture = upamalloc(0, size, align);
		if(aperture == 0)
			return 1;

		if(scr->aperture && scr->isupamem)
			upafree(scr->aperture, scr->apsize);
		scr->isupamem = 1;
	}

	scr->aperture = aperture;
	scr->apsize = size;

	return 0;
}

uchar*
attachscreen(Rectangle* r, ulong* chan, int* d, int* width, int *softscreen)
{
	VGAscr *scr;

	scr = &vgascreen[0];
	if(scr->gscreen == nil || scr->gscreendata == nil)
		return nil;

	*r = scr->gscreen->clipr;
	*chan = scr->gscreen->chan;
	*d = scr->gscreen->depth;
	*width = scr->gscreen->width;
	*softscreen = scr->useflush;

	return scr->gscreendata->bdata;
}

/*
 * It would be fair to say that this doesn't work for >8-bit screens.
 */
void
flushmemscreen(Rectangle r)
{
	VGAscr *scr;
	uchar *sp, *disp, *sdisp, *edisp;
	int y, len, incs, off, page;

	scr = &vgascreen[0];
	if(scr->dev && scr->dev->flush){
		scr->dev->flush(scr, r);
		return;
	}
	if(scr->gscreen == nil || scr->useflush == 0)
		return;
	if(scr->dev == nil || scr->dev->page == nil)
		return;

	if(rectclip(&r, scr->gscreen->r) == 0)
		return;

	incs = scr->gscreen->width * BY2WD;

	switch(scr->gscreen->depth){
	default:
		len = 0;
		panic("flushmemscreen: depth\n");
		break;
	case 8:
		len = Dx(r);
		break;
	}
	if(len < 1)
		return;

	off = r.min.y*scr->gscreen->width*BY2WD+(r.min.x*scr->gscreen->depth)/8;
	page = off/scr->apsize;
	off %= scr->apsize;
	disp = KADDR(scr->aperture);
	sdisp = disp+off;
	edisp = disp+scr->apsize;

	off = r.min.y*scr->gscreen->width*BY2WD+(r.min.x*scr->gscreen->depth)/8;

	sp = scr->gscreendata->bdata + off;

	scr->dev->page(scr, page);
	for(y = r.min.y; y < r.max.y; y++) {
		if(sdisp + incs < edisp) {
			memmove(sdisp, sp, len);
			sp += incs;
			sdisp += incs;
		}
		else {
			off = edisp - sdisp;
			page++;
			if(off <= len){
				if(off > 0)
					memmove(sdisp, sp, off);
				scr->dev->page(scr, page);
				if(len - off > 0)
					memmove(disp, sp+off, len - off);
			}
			else {
				memmove(sdisp, sp, len);
				scr->dev->page(scr, page);
			}
			sp += incs;
			sdisp += incs - scr->apsize;
		}
	}
}

void
getcolor(u32 p, u32* pr, u32* pg, u32* pb)
{
	VGAscr *scr;
	ulong x;

	scr = &vgascreen[0];
	if(scr->gscreen == nil)
		return;

	switch(scr->gscreen->depth){
	default:
		x = 0x0F;
		break;
	case 8:
		x = 0xFF;
		break;
	}
	p &= x;

	lock(&cursor);
	*pr = scr->colormap[p][0];
	*pg = scr->colormap[p][1];
	*pb = scr->colormap[p][2];
	unlock(&cursor);
}

int
setpalette(u32 p, u32 r, u32 g, u32 b)
{
	VGAscr *scr;
	int d;

	scr = &vgascreen[0];
	d = scr->palettedepth;

	lock(&cursor);
	scr->colormap[p][0] = r;
	scr->colormap[p][1] = g;
	scr->colormap[p][2] = b;
	vgao(PaddrW, p);
	vgao(Pdata, r>>(32-d));
	vgao(Pdata, g>>(32-d));
	vgao(Pdata, b>>(32-d));
	unlock(&cursor);

	return ~0;
}

/*
 * On some video cards (e.g. Mach64), the palette is used as the 
 * DAC registers for >8-bit modes.  We don't want to set them when the user
 * is trying to set a colormap and the card is in one of these modes.
 */
int
setcolor(u32 p, u32 r, u32 g, u32 b)
{
	VGAscr *scr;
	int x;

	scr = &vgascreen[0];
	if(scr->gscreen == nil)
		return 0;

	switch(scr->gscreen->depth){
	case 1:
	case 2:
	case 4:
		x = 0x0F;
		break;
	case 8:
		x = 0xFF;
		break;
	default:
		return 0;
	}
	p &= x;

	return setpalette(p, r, g, b);
}

int
cursoron(int dolock)
{
	VGAscr *scr;
	int v;

	scr = &vgascreen[0];
	if(scr->cur == nil || scr->cur->move == nil)
		return 0;

	if(dolock)
		lock(&cursor);
	v = scr->cur->move(scr, mousexy());
	if(dolock)
		unlock(&cursor);

	return v;
}

void
cursoroff(void)
{
}

void
setcursor(Cursor* curs)
{
	VGAscr *scr;

	scr = &vgascreen[0];
	if(scr->cur == nil || scr->cur->load == nil)
		return;

	scr->cur->load(scr, curs);
}

int hwaccel = 1;
int hwblank = 0;	/* turned on by drivers that are known good */
int panning = 0;

int
hwdraw(Memdrawparam *par)
{
	VGAscr *scr;
	Memimage *dst, *src;
	int m;

	if(hwaccel == 0)
		return 0;

	dst = par->dst;
	scr = &vgascreen[0];
	if(dst == nil || dst->data == nil)
		return 0;

	if(dst->data->bdata != gscreendata.bdata)
		return 0;

	if(scr->fill==nil && scr->scroll==nil)
		return 0;

	/*
	 * If we have an opaque mask and source is one opaque
	 * pixel we can convert to the destination format and just
	 * replicate with memset.
	 */
	m = Simplesrc|Simplemask|Fullmask;
	if(scr->fill
	&& (par->state&m)==m
	&& ((par->srgba&0xFF) == 0xFF)
	&& (par->op&S) == S)
		return scr->fill(scr, par->r, par->sdval);

	/*
	 * If no source alpha, an opaque mask, we can just copy the
	 * source onto the destination.  If the channels are the same and
	 * the source is not replicated, memmove suffices.
	 */
	m = Simplemask|Fullmask;
	src = par->src;
	if(scr->scroll
	&& src->data->bdata==dst->data->bdata
	&& !(src->flags&Falpha)
	&& (par->state&m)==m
	&& (par->op&S) == S)
		return scr->scroll(scr, par->r, par->sr);

	return 0;	
}

void
blankscreen(int blank)
{
	VGAscr *scr;

	scr = &vgascreen[0];
	if(hwblank){
		if(scr->blank)
			scr->blank(scr, blank);
		else
			vgablank(scr, blank);
	}
}

void
cursorenable(void)
{
}

void
cursordisable(void)
{
}

static char*
vgalinearaddr0(VGAscr *scr, uvlong paddr, int size)
{
	int x, nsize;
	uvlong npaddr;

	/*
	 * new approach.  instead of trying to resize this
	 * later, let's assume that we can just allocate the
	 * entire window to start with.
	 */
	if(scr->paddr == paddr && size <= scr->apsize)
		return nil;

	if(scr->paddr){
		/*
		 * could call vunmap and vmap,
		 * but worried about dangling pointers in devdraw
		 */
		return "cannot grow vga frame buffer";
	}

	/* round to page boundary, just in case */
	x = paddr&(BY2PG-1);
	npaddr = paddr-x;
	nsize = PGROUND(size+x);

	/*
	 * Don't bother trying to map more than 4000x4000x32 = 64MB.
	 * We only have a 256MB window.
	 */
	if(nsize > 64*MB)
		nsize = 64*MB;
	scr->vaddr = vmap(npaddr, nsize);
	if(scr->vaddr == nil)
		return "cannot map vga frame buffer";

	patwc(scr->vaddr, nsize);

	scr->vaddr = (char*)scr->vaddr+x;
	scr->paddr = paddr;
	scr->apsize = nsize;

	mtrr(npaddr, nsize, "wc");

	return nil;
}

static char*
vgalinearpci0(VGAscr *scr)
{
	int i, size, best;
	uvlong paddr;
	Pcidev *p;
	
	p = scr->pci;
	if(p == nil)
		return "no pci card";

	/*
	 * Scan for largest memory region on card.
	 * Some S3 cards (e.g. Savage) have enormous
	 * mmio regions (but even larger frame buffers).
	 * Some 3dfx cards (e.g., Voodoo3) have mmio
	 * buffers the same size as the frame buffer,
	 * but only the frame buffer is marked as
	 * prefetchable (bar&8).  If a card doesn't fit
	 * into these heuristics, its driver will have to
	 * call vgalinearaddr directly.
	 */
	best = -1;
	for(i=0; i<nelem(p->mem); i++){
		if(p->mem[i].bar&1)	/* not memory */
			continue;
		if(p->mem[i].size < 640*480)	/* not big enough */
			continue;
		if(best==-1 
		|| p->mem[i].size > p->mem[best].size 
		|| (p->mem[i].size == p->mem[best].size 
		  && (p->mem[i].bar&8)
		  && !(p->mem[best].bar&8)))
			best = i;
	}
	if(best >= 0){
		paddr = p->mem[best].bar & ~0x0F;
		size = p->mem[best].size;
		return vgalinearaddr0(scr, paddr, size);
	}
	return "no video memory found on pci card";
}

void
vgalinearpci(VGAscr *scr)
{
	char *err;

	if(scr->pci == nil)
		return;
	if((err = vgalinearpci0(scr)) != nil)
		error(err);
}

void
vgalinearaddr(VGAscr *scr, uvlong paddr, int size)
{
	char *err;

	if((err = vgalinearaddr0(scr, paddr, size)) != nil)
		error(err);
}

static char*
bootmapfb(VGAscr *scr, uvlong pa, ulong sz)
{
	uvlong start, end;
	Pcidev *p;
	int i;

	for(p = pcimatch(nil, 0, 0); p != nil; p = pcimatch(p, 0, 0)){
		for(i=0; i<nelem(p->mem); i++){
			if(p->mem[i].size == 0 || (p->mem[i].bar & 1) != 0)
				continue;
			start = p->mem[i].bar & ~0xF;
			end = start + p->mem[i].size;
			if(pa == start && (pa + sz) <= end){
				scr->pci = p;
				return vgalinearpci0(scr);
			}
		}
	}
	upaalloc(pa, sz, 0);
	return vgalinearaddr0(scr, pa, sz);
}

char*
rgbmask2chan(char *buf, int depth, u32int rm, u32int gm, u32int bm)
{
	u32int m[4], dm;	/* r,g,b,x */
	char tmp[32];
	int c, n;

	dm = 1<<depth-1;
	dm |= dm-1;

	m[0] = rm & dm;
	m[1] = gm & dm;
	m[2] = bm & dm;
	m[3] = (~(m[0] | m[1] | m[2])) & dm;

	buf[0] = 0;
Next:
	for(c=0; c<4; c++){
		for(n = 0; m[c] & (1<<n); n++)
			;
		if(n){
			m[0] >>= n, m[1] >>= n, m[2] >>= n, m[3] >>= n;
			snprint(tmp, sizeof tmp, "%c%d%s", "rgbx"[c], n, buf);
			strcpy(buf, tmp);
			goto Next;
		}
	}
	return buf;
}

/*
 * called early on boot to attach to framebuffer
 * setup by bootloader/firmware or plan9.
 */
void
bootscreeninit(void)
{
	VGAscr *scr;
	int x, y, z, tilt;
	uvlong pa;
	ulong chan, sz;
	char *s, *p, *err;

	print("pc bootscreeninit\n");
	/* *bootscreen=WIDTHxHEIGHTxDEPTH CHAN PA [SZ] */
	s = getconf("*bootscreen");
	if(s == nil){
		print("bootscreen == nil\n");
		return;
	}

	x = strtoul(s, &s, 0);
	if(x == 0 || *s++ != 'x')
		return;

	y = strtoul(s, &s, 0);
	if(y == 0 || *s++ != 'x')
		return;

	z = strtoul(s, &s, 0);
	if(*s != ' ')
		return;
	if((p = strchr(++s, ' ')) == nil)
		return;
	*p = 0;
	chan = strtochan(s);
	*p = ' ';
	if(chan == 0 || chantodepth(chan) != z)
		return;

	sz = 0;
	pa = strtoull(p+1, &s, 0);
	if(pa == 0)
		return;
	if(*s == ' ')
		sz = strtoul(s+1, nil, 0);
	if(sz < x * y * (z+7)/8)
		sz = x * y * (z+7)/8;

	tilt = 0;
	if((p = getconf("tiltscreen")) != nil){
		for(; tilt < nelem(tiltstr); tilt++)
			if(strcmp(p, tiltstr[tilt]) == 0)
				break;
		tilt &= 3;
	}

	scr = &vgascreen[0];
	scr->dev = nil;
	scr->softscreen = 1;

	if((err = bootmapfb(scr, pa, sz)) != nil){
		print("bootmapfb: %s\n", err);
		return;
	}

	if(memimageinit() < 0){
		print("memimageinit failed\n");
		return;
	}
	if((err = setscreensize0(scr, x, y, z, chan, tilt)) != nil){
		print("setscreensize0: %s\n", err);
		return;
	}

	vgaimageinit(chan);
	vgascreenwin(scr);

	drawcmap();

	scr->cur = &vgasoftcur;
	scr->cur->enable(scr);

	conf.monitor = 1;
}

/*
 * called from devvga when the framebuffer is setup
 * to set *bootscreen= that can be passed on to a
 * new kernel on reboot.
 */
void
bootscreenconf(VGAscr *scr)
{
	char conf[100], chan[30];

	conf[0] = '\0';
	if(scr != nil && scr->paddr != 0 && scr->gscreen != nil){
		snprint(conf, sizeof(conf), "%dx%dx%d %s 0x%.8llux %d\n",
			scr->width, scr->height, scr->gscreen->depth, chantostr(chan, scr->gscreen->chan),
			scr->paddr, scr->apsize);
		ksetenv("tiltscreen", tiltstr[scr->tilt], 1);
	}
	ksetenv("*bootscreen", conf, 1);
}
