#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"
#include "io.h"
#include "ureg.h"

#define DP if(1){}else print

enum {
	MemUPA		= 0,	/* unbacked physical address */
	MemUMB		= 1,	/* upper memory block (<16MB) */
	MemRAM		= 2,	/* physical memory */
	MemACPI		= 3,	/* ACPI tables */
	MemReserved	= 4,	/* don't allocate */

	KB = 1024,
};

u64	MemMin;		/* set by l.s */

/* TODO just use xspanalloc. I do not know what the memmapalloc() does. It does not seem to work anyway. inferno pc does not use it either? can refactor all this code.
 */
void*
rampage(void)
{
	uintptr pa;

	if(conf.mem[0].npage != 0)
		return xspanalloc(BY2PG, BY2PG, 0);

	/*
	 * Allocate from the map directly to make page tables.
	 */
	print("before calling rampage\n");
	memmapdump();
	pa = memmapalloc(-1, BY2PG, BY2PG, MemRAM);
	if(pa == -1)
		panic("rampage: out of memory\n");
	print("rampage returned 0x%p\n", pa);
	return (void*)pa;
}

static void
mapkzero(uintptr base, u64 len, int type)
{
	uintptr flags, n;

	DP("mapkzero base 0x%p len %llud 0x%llux type 0x%x\n",
		base, len, len, type);
	if(base < MemMin && base+len > MemMin){
		mapkzero(base, MemMin-base, type);
		len = base+len-MemMin;
		base = MemMin;
	}

	switch(type){
	default:
		return;
	case MemRAM:
		if(base < MemMin)
			return;
		flags = PTEWRITE|PTEVALID;
		break;
	case MemUMB:
		flags = PTEWRITE|PTEUNCACHED|PTEVALID;
		break;
	}
	pmap(base, flags, len);
}

/*
 * map kernel text segment readonly
 * and everything else no-execute.
 */
static void
kernelro(void)
{
	uintptr *pte, psz, va;

	for(va = KTZERO; va <= (uintptr)etext; va += psz){
		psz = PGLSZ(0);
		pte = mmuwalk((uintptr*)PML4ADDR, va, 0, 0);
		if(pte == nil){
			print("kernelro va 0x%p\n", va);
			panic("kernelro");
		}
		if((*pte & PTEVALID) == 0){
			print("kernelro invalid page va 0x%p pte 0x%p *pte 0x%zux\n",
				va, pte, *pte);
			panic("kernelro invalid page\n");
		}
		if(va >= KTZERO && va < (uintptr)etext){
			*pte &= ~PTEWRITE;
			*pte |= PTEGLOBAL;
		}
	}
	mmuflushtlb();
}

static uintptr
ebdaseg(void)
{
	uchar *bda;

	if(memcmp(KADDR(0xfffd9), "EISA", 4) != 0)
		return 0;
	bda = KADDR(0x400);
	return ((bda[0x0f]<<8)|bda[0x0e]) << 4;
}

static uintptr
convmemsize(void)
{
	uintptr top;
	uchar *bda;

	bda = KADDR(0x400);
	top = ((bda[0x14]<<8) | bda[0x13])*KB;

	if(top < 64*KB || top > 640*KB)
		top = 640*KB;	/* sanity */

	/* Reserved for BIOS tables */
	top -= 1*KB;

	return top;
}

static void
lowraminit(void)
{
	uintptr base, pa, len;
	uchar *p;

	/*
	 * Discover the memory bank information for conventional memory
	 * (i.e. less than 640KB). The base is the first location after the
	 * bootstrap processor MMU information and the limit is obtained from
	 * the BIOS data area.
	 */
	base = PADDR(CPU0END);
	pa = convmemsize();
	if(base < pa)
		memmapadd(base, pa-base, MemRAM);

	/* Reserve BIOS tables */
	memmapadd(pa, 1*KB, MemReserved);

	/* Reserve EBDA */
	if((pa = ebdaseg()) != 0)
		memmapadd(pa, 1*KB, MemReserved);
	memmapadd(0xA0000-1*KB, 1*KB, MemReserved);

	/* Reserve the VGA frame buffer */
	umballoc(0xA0000, 128*KB, 0);

	/* Reserve VGA ROM */
	memmapadd(0xC0000, 64*KB, MemReserved);

	/*
	 * Scan the Upper Memory Blocks (0xD0000->0xF0000) for device BIOS ROMs.
	 * This should start with a two-byte header of 0x55 0xAA, followed by a
	 * byte giving the size of the ROM in 512-byte chunks.
	 * These ROM's must start on a 2KB boundary.
	 */
	for(p = (uchar*)KADDR(0xD0000); p < (uchar*)KADDR(0xF0000); p += len){
		len = 2*KB;
		if(p[0] == 0x55 && p[1] == 0xAA){
			if(p[2] != 0)
				len = p[2]*512;
			memmapadd(PADDR(p), len, MemReserved);
			len = ROUND(len, 2*KB);
		}
	}

	/* Reserve BIOS ROM */
	memmapadd(0xF0000, 64*KB, MemReserved);
}

int
checksum(void *v, int n)
{
	uchar *p, s;

	s = 0;
	p = v;
	while(n-- > 0)
		s += *p++;
	return s;
}

static void*
sigscan(uchar *addr, int len, char *sig, int size, int step)
{
	uchar *e, *p;
	int sl;

	sl = strlen(sig);
	e = addr+len-(size > sl ? size : sl);
	for(p = addr; p <= e; p += step){
		if(memcmp(p, sig, sl) != 0)
			continue;
		if(size && checksum(p, size) != 0)
			continue;
		return p;
	}
	return nil;
}

void*
sigsearch(char* signature, int size)
{
	uintptr p;
	void *r;

	/*
	 * Search for the data structure:
	 * 1) within the first KiB of the Extended BIOS Data Area (EBDA), or
	 * 2) within the last KiB of system base memory if the EBDA segment
	 *    is undefined, or
	 * 3) within the BIOS ROM address space between 0xf0000 and 0xfffff
	 *    (but will actually check 0xe0000 to 0xfffff).
	 */
	if((p = ebdaseg()) != 0){
		if((r = sigscan(KADDR(p), 1*KB, signature, size, 16)) != nil)
			return r;
	}
	if((r = sigscan(KADDR(convmemsize()), 1*KB, signature, size, 16)) != nil)
		return r;

	/* hack for virtualbox: look in KiB below 0xa0000 */
	if((r = sigscan(KADDR(0xA0000-1*KB), 1*KB, signature, size, 16)) != nil)
		return r;

	return sigscan(KADDR(0xE0000), 128*KB, signature, size, 16);
}

void*
rsdsearch(void)
{
	static char signature[] = "RSD PTR ";
	uintptr base, size;
	uchar *v, *p;

	if((p = sigsearch(signature, 36)) != nil)
		return p;
	if((p = sigsearch(signature, 20)) != nil)
		return p;

	for(base = memmapnext(-1, MemACPI); base != -1; base = memmapnext(base, MemACPI)){
		size = memmapsize(base, 0);
		if(size == 0 || size > 0x7fffffff)
			continue;
		if((v = vmap(base, size)) != nil){
			p = sigscan(v, size, signature, 36, 4);
			if(p == nil)
				p = sigscan(v, size, signature, 20, 4);
			vunmap(v, size);
			if(p != nil)
				return vmap(base + (p - v), 64);
		}
	}
	return nil;
}

/*
 * Give out otherwise-unused physical address space
 * for use in configuring devices.  Note that upaalloc
 * does not map the physical address into virtual memory.
 * Call vmap to do that.
 */
u64
upaalloc(u64 pa, u32 size, u32 align)
{
	print("before memmapalloc pa 0x%p size 0x%x %d\n",
		pa, size, size);
	// memmapdump();
	return memmapalloc(pa, size, align, MemUPA);
}

u64
upamalloc(u64 pa, u32 size, u32 align)
{
	return memmapalloc(pa, size, align, MemUPA);
}

u64
upaallocwin(u64 pa, u32 win, u32 size, u32 align)
{
	uvlong a, base, top = pa + win;

	for(base = memmapnext(-1, MemUPA); base != -1 && base < top; base = memmapnext(base, MemUPA)){
		if(base < pa){
			if(pa >= base + memmapsize(base, 0))
				continue;
			base = pa;
		}
		a = upaalloc(base, size, align);
		if(a != -1)
			return a;
	}
	return -1ULL;
}

void
upafree(u64 pa, u32 size)
{
	memmapfree(pa, size, MemUPA);
}

/*
 * Allocate memory from the upper memory blocks.
 */
uintptr
umballoc(uintptr pa, u32 size, u32 align)
{
	return (uintptr)memmapalloc(pa == -1UL ? -1ULL : (uvlong)pa, size, align, MemUMB);
}

void
umbfree(uintptr pa, u32 size)
{
	memmapfree(pa, size, MemUMB);
}

static void
umbexclude(void)
{
	uintptr pa, size;
	char *op, *p, *rptr;

	if((p = getconf("umbexclude")) == nil)
		return;

	while(p && *p != '\0' && *p != '\n'){
		op = p;
		pa = strtoul(p, &rptr, 0);
		if(rptr == nil || rptr == p || *rptr != '-'){
			print("umbexclude: invalid argument <%s>\n", op);
			break;
		}
		p = rptr+1;

		size = strtoul(p, &rptr, 0) - pa + 1;
		if(size <= 0){
			print("umbexclude: bad range <%s>\n", op);
			break;
		}
		if(rptr != nil && *rptr == ',')
			*rptr++ = '\0';
		p = rptr;

		memmapalloc(pa, size, 0, MemUMB);
	}
}

static void
mtrrexclude(int type, char *expect)
{
	uintptr base, top, next, pa;
	char *attr;

	for(base = memmapnext(-1, type); base != -1; base = memmapnext(base, type)){
		top = base + memmapsize(base, 0);
		for(pa = base; pa < top; pa = next){
			next = top;
			attr = mtrrattr(pa, &next);
			if(attr != nil && strcmp(attr, expect) != 0){
				if(next > top)
					next = top;
				memmapadd(pa, next - pa, MemReserved);
			}
			base = pa;
		}
	}
}

static int
e820scan(void)
{
	uintptr base, top, size;
	int type;
	char *s;

	/* passed by bootloader */
	if((s = getconf("*e820")) == nil)
		if((s = getconf("e820")) == nil)
			return -1;

	print("e820scan %s\n", s);
	for(;;){
		while(*s == ' ')
			s++;
		if(*s == 0)
			break;
		type = 1;
		if(s[1] == ' '){	/* new format */
			type = s[0] - '0';
			s += 2;
		}
		base = strtoull(s, &s, 16);
		if(*s != ' ')
			break;
		top  = strtoull(s, &s, 16);
		if(*s != ' ' && *s != 0)
			break;
		if(base >= top)
			continue;
		switch(type){
		case 1:
			memmapadd(base, top - base, MemRAM);
			break;
		case 3:
			memmapadd(base, top - base, MemACPI);
			break;
		default:
			memmapadd(base, top - base, MemReserved);
		}
	}

	/* RAM needs to be writeback */
	mtrrexclude(MemRAM, "wb");

	return 0;
}

/*
21:00 < joe7> ori, you around? I am trying to figure out how ramscan() works. When writing the pattern, why does it do this: *k0 = ~pat; ?
21:01 < joe7> that value is not used anywhere else again in that subroutine.
21:06 < joe7> nemo's kernel book on page 51 asks the same question too.
21:06 < joe7> It says, "the author is saving the value actually stored at address KZERO, can you guess why?"
0:36 < cinap_lenrek> joe7: it is to detect aliases
00:36 < cinap_lenrek> joe7: it is a RAM tester basically
00:36 < cinap_lenrek> joe7: you should not use this at all
00:37 < cinap_lenrek> in modern machines, this approach is impossible
00:37 < cinap_lenrek> because ram now contains life firmware for devices and megabytes of persistent firmware code
00:40 < cinap_lenrek> if you write to that or damage that info the whole machine will just lock up or brick itself
04:38 < joe7> cinap_lenrek: joe7: you should not use this at all -- which one? the ramscan() or *k = pat?
04:39 < joe7> I see ramscan in 9front 9/pc/memory.c too
04:39 < joe7> Iif(e820scan() < 0)
04:39 < joe7> IIramscan(MemMin, -((uintptr)MemMin), 4*MB);
04:39 < joe7> that is how the ram is being discovered
04:46 < cinap_lenrek> e820scan() just reads the *e820= plan9.ini parameter
04:46 < cinap_lenrek> ramscan() is a fallback
04:46 < cinap_lenrek> when theres no memory map
04:46 < cinap_lenrek> like on reeeeeally old machines
04:46 < cinap_lenrek> or when bios is totally broken
04:47 < cinap_lenrek> dont worry about it
04:47 < cinap_lenrek> theres not really a point in supporting it anymore
04:47 < cinap_lenrek> as i said
04:47 < cinap_lenrek> it is a destructive memory test
04:47 < joe7> oh, ok. I must have screwed up something as it is going to ramscan() each time.
04:47 < joe7> I will fix it. Thanks.
 */
static void
ramscan(uintptr pa, uintptr top)
{
	uintptr save, pat, seed, *v, *k0, *pte;
	uintptr i, n, w;
	char *attr;
	uintptr chunk;

	chunk = PGLSZ(0);
	pa += chunk-1;
	pa &= ~(chunk-1);
	top &= ~(chunk-1);

	n = chunk/sizeof(*v);
	w = BY2PG/sizeof(*v);

	k0 = KADDR(0);
	save = *k0;

	DP("ramscan\n");
	pat = 0x12345678UL;
	for(; pa < top; pa += chunk){
		DP("ramscan pa 0x%p\n", pa);
		v = (uintptr*)pa;
		attr = mtrrattr(pa, nil);
		if(attr != nil && strcmp(attr, "wb") != 0)
			goto Skip;

		/* write pattern */
		seed = pat;
		if((pte = mmuwalk((uintptr*)PML4ADDR, pa, 0, 1)) == nil)
			continue;
		*pte = pa|PTEWRITE|PTEVALID;
		for(i = 0; i < n; i += w){
			pat += 0x3141526UL;
			v[i] = pat;
			*k0 = ~pat;
			if(v[i] != pat)
				goto Bad;
		}

		/* verify pattern */
		pat = seed;
		for(i = 0; i < n; i += w){
			pat += 0x3141526UL;
			if(v[i] != pat)
				goto Bad;
		}

		memmapadd(pa, chunk, MemRAM);
		mapkzero(pa, chunk, MemRAM);
		continue;

	Bad:
		*pte = 0;

	Skip:
		if(pa+chunk <= 16*MB)
			memmapadd(pa, chunk, MemUMB);

		/*
		 * If we encounter a chunk of missing memory
		 * at a sufficiently high offset, call it the end of
		 * memory.  Otherwise we run the risk of thinking
		 * that video memory is real RAM.
		 */
		if(pa >= 32*MB)
			break;
	}

	*k0 = save;
}

void
showpagetables(uintptr *pml4)
{
	uintptr *epml4, pml4e, *pdp, *epdp, pdpe, *pd, *epd, pde, *pt, *ept, pte, cr3, pa;

	cr3 = getcr3();
	print("CR3 0x%zux cpu0pml4 0x%p\n"
		"\tpml4 base address 0x%zux\n"
		"\tpage-level writethrough bit 0x%zux"
		" page-level cache disable bit 0x%zux\n",
		cr3, PML4ADDR, cr3&(~0xFFF),
		cr3&(1<<4)>>4,
		cr3&(1<<3)>>3);
	epml4 = pml4+512;
	for(; pml4 != epml4; pml4++){
		if(*pml4 == 0)
			continue;
		pml4e = *pml4;
		pdp = (uintptr*)(pml4e&(~0xFFF));
		print("pml4 0x%p has 0x%zx pdp base address 0x%p\n", pml4, pml4e, pdp);
		epdp = pdp + 512;
		for(; pdp != epdp; pdp++){
			if(*pdp == 0)
				continue;
			pdpe = *pdp;
			pd = (uintptr*)(pdpe&(~0xFFF));
			epd = pd + 512;
			print("\tpdp 0x%p has 0x%zx pd base address 0x%p\n",
				pdp, pdpe, pd);
			for(; pd != epd; pd++){
				if(*pd == 0)
					continue;
				pde = *pd;
				pt = (uintptr*)(pde&(~0xFFF));
				print("\t\tpd 0x%p has 0x%zx page base address 0x%p\n",
					pd, pde, pt);
				ept = pt + 512;
				for(; pt != ept; pt++){
					if(*pt == 0)
						continue;
					pte = *pt;
					pa = (uintptr)(pte&(~0xFFF));
					print("\t\t\tpt 0x%p has 0x%zx address 0x%zx\n",
						pt, pte, pa);
				}
			}
		}
	}
}

/*
 * Sort out initial memory map and discover RAM.
 */
void
meminit0(void)
{
	uintptr prevbase = 0, base, size = 0;

	print("MemMin 0x%llux end 0x%p KZERO 0x%x KDZERO 0x%x\n"
		"\tKTZERO 0x%x etext 0x%p\n\tCPU0END 0x%llux\n"
		"\tPADDR(PGROUND((uintptr)end)) 0x%zux MemMin-PADDR(PGROUND((uintptr)end)) 0x%zux\n",
		MemMin, end, KZERO, KDZERO, KTZERO, etext, (uintptr)CPU0END,
		PADDR(PGROUND((uintptr)end)), MemMin-PADDR(PGROUND((uintptr)end)));
	/*
	 * Add the already mapped memory after the kernel.
	 */
	if(MemMin < PADDR(PGROUND((uintptr)end)))
		panic("kernel too big");
	memmapadd(PADDR(PGROUND((uintptr)end)), MemMin-PADDR(PGROUND((uintptr)end)), MemRAM);

	/*
	 * Memory below MemMin is reserved for the kernel.
	 * Also, set the kernel text pages read only
	 */
	memreserve(PADDR(KDZERO), PADDR(PGROUND((uintptr)MemMin))-PADDR(KDZERO));
	kernelro();

	/*
	 * Addresses below 16MB default to be upper
	 * memory blocks usable for ISA devices.
	 */
	memmapadd(0, 16*MB, MemUMB);

	/*
	 * Everything between 16MB and 4GB defaults
	 * to unbacked physical addresses usable for
	 * device mappings.
	 */
	memmapadd(16*MB, (u32)-16*MB, MemUPA);

		print("------before lowraminit -----\n");
		memmapdump();
		print("-----------\n");
	/*
	 * Discover conventional RAM, ROMs and UMBs.
	 */
	lowraminit();

		print("------after lowraminit -----\n");
		memmapdump();
		print("-----------\n");
	/*
	 * Discover more RAM and map to KZERO.
	 */
	if(e820scan() < 0)
		ramscan(MemMin, -((uintptr)MemMin));

	/*
	 * Exclude UMB's and UPA's with unusual cache attributes.
	 */
	mtrrexclude(MemUMB, "uc");
	mtrrexclude(MemUPA, "uc");
}

/*
 * Until the memory map is finalized by meminit(),
 * archinit() should reserve memory of discovered BIOS
 * and ACPI tables by calling memreserve() to prevent
 * them from getting allocated and trashed.
 * This is due to the UEFI and BIOS memory map being
 * unreliable and sometimes marking these ranges as RAM.
 */
void
memreserve(uintptr pa, uintptr size)
{
	assert(conf.mem[0].npage == 0);

	size += (pa & BY2PG-1);
	size &= ~(BY2PG-1);
	pa &= ~(BY2PG-1);
	memmapadd(pa, size, MemReserved);
}

/*
 * Finalize the memory map:
 *  (re-)map the upper memory blocks
 *  allocate all usable ram to the conf.mem[] banks
 *  memory is allocated to memory maps -> conf.mem[] -> xlists.hole
 */
void
meminit(void)
{
	uintptr base, size;
	Confmem *cm;

		print("------ before umbexclude -----\n");
		memmapdump();
		print("-----------\n");
	umbexclude();
		print("------ after umbexclude -----\n");
		memmapdump();
		print("-----------\n");
	for(base = memmapnext(-1, MemUMB); base != -1; base = memmapnext(base, MemUMB)){
		size = memmapsize(base, BY2PG) & ~(BY2PG-1);
		if(size != 0)
			mapkzero(PGROUND(base), size, MemUMB);
	}

	cm = &conf.mem[0];
	for(base = memmapnext(-1, MemRAM); base != -1; base = memmapnext(base, MemRAM)){
		size = memmapsize(base, BY2PG) & ~(BY2PG-1);
		if(size == 0)
			continue;
		if(cm >= &conf.mem[nelem(conf.mem)]){
			print("meminit: out of entries, loosing: %#p (%llud)\n", base, (uvlong)size);
			continue;
		}
		if(base < MemMin){
			print("meminit: ignoring RAM below MemMin base 0x%p size 0x%zd\n", base, size);
			continue;
		}
		cm->base = memmapalloc(base, size, BY2PG, MemRAM);
		if(cm->base == -1)
			continue;
		base = cm->base;
		cm->npage = size/BY2PG;
		cm++;
	}

	print("-----------\n");
	if(1) memmapdump();
	print("-----------\n");
	// showpagetables((uintptr*)PML4ADDR);
	//showpagetables((uintptr*)PML4ADDR);
}
