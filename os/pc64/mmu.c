#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"io.h"

/*
mmu.c: differs between pc and pc64
	- on 9front:
	pmap() - setup up page table entries for the physical address in virtual memory
			the virtual memory address is a parameter
			the flags are included in the physical address
			used by memory.c:^mapkzero for setting the page tables of the kernel
	vmap() - setup page tables for device memory
			virtual memory address = device memory address
			used by almost all the device drivers accessing registers
				as memory addresses (unbacked physical address)
	kmap() - setup kernel page tables
			virtual memory address = page address + KMAP
	A process's virtual memory usage is maintained in the PMMU data structure
		on inferno:
	1. there is no separate virtual memory address - linear mapping
	2. As all memory is linear and global, there is no need to maintain
		a per-process list of page tables
	3. pmap() without the parameter for the virtual memory address handles the
		above needs
	3. vmap() is  a wrapper around pmap() specialized for unbacked physical
		addresses
	4. kmap() is obsolete
 */
#define DP	if(1){}else print
/*
 * Simple segment descriptors with no translation.
 */
#define	EXECSEGM(p) 	{ 0, SEGL|SEGP|SEGPL(p)|SEGEXEC }
#define	DATASEGM(p) 	{ 0, SEGB|SEGG|SEGP|SEGPL(p)|SEGDATA|SEGW }

Segdesc gdt[NGDT] =
{
[NULLSEG]	{ 0, 0},		/* null descriptor */
[KESEG]		EXECSEGM(0),		/* code - kernel privilege for all */
[KDSEG]		DATASEGM(0),		/* data - kernel privilege for all */
};

enum {
	/* level */
	PML4E	= 3,
	PDPE	= 2,
	PDE	= 1,
	PTE	= 0,
};

static void
loadptr(u16int lim, uintptr off, void (*load)(void*))
{
	u64int b[2], *o;
	u16int *s;

	o = &b[1];
	s = ((u16int*)o)-1;

	*s = lim;
	*o = off;

	(*load)(s);
}

static void
taskswitch(uintptr stack)
{
	Tss *tss;

	tss = m->tss;
	tss->rsp0[0] = (u32)stack;
	tss->rsp0[1] = stack >> 32;
	tss->rsp1[0] = (u32)stack;
	tss->rsp1[1] = stack >> 32;
	tss->rsp2[0] = (u32)stack;
	tss->rsp2[1] = stack >> 32;
	mmuflushtlb();
}

void
mmuinit(void)
{
	uintptr x;
	int i;

	/* move kernelro here to mimic 9front? */

	m->tss = mallocz(sizeof(Tss), 1);
	if(m->tss == nil){
		print("mmuinit: no memory for Tss");
		panic("mmuinit: no memory for Tss");
	}
	m->tss->iomap = 0xDFFF;
	/* the IST is not used by the interrupt descriptors.
	 * Putting the existing stack address instead of
	 * leaving the fields empty.
	 */
	for(i=0; i<14; i+=2){
		x = (uintptr)m + MACHSIZE;
		m->tss->ist[i] = x;
		m->tss->ist[i+1] = x>>32;
	}

	/*
	 * We used to keep the GDT in the Mach structure, but it
	 * turns out that that slows down access to the rest of the
	 * page.  Since the Mach structure is accessed quite often,
	 * it pays off anywhere from a factor of 1.25 to 2 on real
	 * hardware to separate them (the AMDs are more sensitive
	 * than Intels in this regard).  Under VMware it pays off
	 * a factor of about 10 to 100.
	 */
	memmove(m->gdt, gdt, sizeof gdt);

	x = (uintptr)m->tss;
	m->gdt[TSSSEG+0].d0 = (x<<16)|(sizeof(Tss)-1);
	m->gdt[TSSSEG+0].d1 = (x&0xFF000000)|((x>>16)&0xFF)|SEGTSS|SEGPL(0)|SEGP;
	m->gdt[TSSSEG+1].d0 = x>>32;
	m->gdt[TSSSEG+1].d1 = 0;

	loadptr(sizeof(gdt)-1, (uintptr)m->gdt, lgdt);
	loadptr(sizeof(Segdesc)*512-1, (uintptr)IDTADDR, lidt);
	taskswitch((uintptr)m + MACHSIZE);
	ltr(TSSSEL);

	wrmsr(FSbase, 0ull);
	wrmsr(GSbase, (u64)&machp[m->machno]);
	/* SWAPGS is not needed for inferno.
	 * leaving it the same as GSbase if unintentional SWAPGS's are used
	 */
	wrmsr(KernelGSbase, (u64)&machp[m->machno]);

	/* pre allocate pages */
	Confmem *cm;
	ulong np, nt;

	np = 0;
	for(i=0; i<nelem(conf.mem); i++){
		cm = &conf.mem[i];
		if(cm->npage == 0)
			continue;
		DP("i %d base 0x%p npage 0x%d\n", i, cm->base, cm->npage);
		pmap(cm->base, PTEGLOBAL|PTEWRITE|PTENOEXEC|PTEVALID, cm->npage*BY2PG);

	}
}

int
mmukmapsync(uintptr va)
{
return 0;
}

uintptr
mmukmap(uintptr pa, uintptr va, int size)
{
return 0;
}

/*
 * Add a device mapping to the vmap range.
 * note that the VMAP and KZERO PDPs are shared
 * between processors (see mpstartap) so no
 * synchronization is being done.
 *
 * < cinap_lenrek> joe7: pmap() is kind of generic function,
 *  allowing to pass the protection flags too
 * < cinap_lenrek> vmap() and kmap() are all built ontop of it
 */
void*
vmap(uintptr pa, int size)
{
        int o;

        if(pa < BY2PG || size <= 0 || -pa < size || pa+size > VMAPSIZE){
                print("vmap pa=%llux size=%d pc=%#p\n", pa, size, getcallerpc(&pa));
                return nil;
        }

        /*
         * might be asking for less than a page.
         */
        o = pa & (BY2PG-1);
        pa -= o;
        size += o;
        pmap(pa, PTEUNCACHED|PTEWRITE|PTENOEXEC|PTEVALID, size);
        return (void*)(pa+o);
}

void
vunmap(void *va, int size)
{
/* nothing to do */
}

int
segflush(void*, ulong)
{
	return 0;
}

static uintptr*
mmucreate(uintptr *table, uintptr pa, int level, int index)
{
	uintptr *page, flags;
	MMU *p;
	
	DP("mmucreate table 0x%p pa 0x%p level %d index %d\n",
		table, pa, level, index);
	flags = PTEWRITE|PTEVALID;
	page = (uintptr*)rampage();
	DP("mmucreate new page 0x%p PTSZ 0x%x %d BY2PG 0x%zx %zd\n",
		page, PTSZ, PTSZ, BY2PG, BY2PG);
	memset(page, 0, PTSZ);
	table[index] = PADDR(page) | flags;
	return page;
}

/* not bothering with 1GiB or 2MiB pages yet */
uintptr*
mmuwalk(uintptr* table, uintptr pa, int level, int create)
{
	uintptr pte, flags;
	int i, x;

	DP("mmuwalk table 0x%p pa 0x%p level %d create %d\n",
		table, pa, level, create);
	flags = PTEWRITE | PTEVALID;
	x = PTLX(pa, 3);
	DP("\tpml4 index %d\n", x);
	for(i = 2; i >= level; i--){
		pte = table[x];
		if(pte & PTEVALID){
			pte = PPN(pte);
			table = (void*)pte;
		} else {
			if(!create)
				return 0;
			table = mmucreate(table, pa, i, x);
		}
		x = PTLX(pa, i);
		DP("\tlevel %d index %d\n", i, x);
	}
	return &table[x];
}

static int
ptecount(uintptr pa, s32 level)
{
	return (1<<PTSHIFT) - (pa & PGLSZ(level+1)-1) / PGLSZ(level);
}

/* splits a 2 MiB page table entry into a table of 4096 pages
 * probably not useful for inferno
 */
static void
ptesplit(uintptr* table, uintptr va)
{
	uintptr *pte, pa, off;

	pte = mmuwalk(table, va, 1, 0);
	if(pte == nil || (*pte & PTESIZE) == 0 || (va & PGLSZ(1)-1) == 0)
		return;
	table = (uintptr*)rampage();
	va &= -PGLSZ(1);
	pa = *pte & ~PTESIZE;
	for(off = 0; off < PGLSZ(1); off += PGLSZ(0))
		table[PTLX(va + off, 0)] = pa + off;
	*pte = PADDR(table) | PTEVALID|PTEWRITE;
	invlpg(va);
}

void
pmap(uintptr pa, u64 flags, s64 size)
{
	uintptr *pte, *ptee;
	s32 z, l;

	if(size <= 0)
		panic("pmap: pa=%#p size=%lld", pa, size);
	DP("pmap pa 0x%p-0x%zux flags 0x%llux size %llud 0x%llux\n",
		pa, (uintptr)pa+size, flags, size, size);
	pa = PPN(pa);
	DP("\tpa 0x%p\n", pa);
	while(size > 0){
		/* reducing complexity, use 4096 byte pages all through */
		l = 0;
		z = PGLSZ(0);
		pte = mmuwalk((uintptr*)PML4ADDR, pa, l, 1);
		if(pte == nil){
			panic("pmap: pa=%#p size=%lld", pa, size);
		}
		ptee = pte + ptecount(pa, l);
		while(size > 0 && pte < ptee){
			*pte++ = pa | flags;
			pa += z;
			size -= z;
		}
	}
}

void
punmap(uintptr pa, vlong size)
{
	uintptr *pte;
	int l;

	pa = PPN(pa);
	while(size > 0){
		if((pa % PGLSZ(1)) != 0 || size < PGLSZ(1))
			ptesplit((uintptr*)PML4ADDR, pa);
		l = 0;
		pte = mmuwalk((uintptr*)PML4ADDR,pa, l, 0);
		if(pte == nil && (pa % PGLSZ(1)) == 0 && size >= PGLSZ(1))
			pte = mmuwalk((uintptr*)PML4ADDR, pa, ++l, 0);
		if(pte){
			*pte = 0;
			invlpg(pa);
		}
		pa += PGLSZ(l);
		size -= PGLSZ(l);
	}
}

/*
 * mark pages as write combining (used for framebuffer)
 */
void
patwc(void *a, int n)
{
	uintptr *pte, mask, attr, pa;
	int z, l;
	vlong v;

	/* check if pat is usable */
	if((MACHP(0)->cpuiddx & Pat) == 0
	|| rdmsr(0x277, &v) == -1
	|| ((v >> PATWC*8) & 7) != 1)
		return;

	/* set the bits for all pages in range */
	for(pa = (uintptr)a; n > 0; n -= z, pa += z){
		l = 0;
		pte = mmuwalk((uintptr*)PML4ADDR, pa, l, 0);
		if(pte == 0)
			pte = mmuwalk((uintptr*)PML4ADDR, pa, ++l, 0);
		if(pte == 0 || (*pte & PTEVALID) == 0)
			panic("patwc: pa=%#p", pa);
		z = PGLSZ(l);
		z -= pa & (z-1);
		mask = l == 0 ? 3<<3 | 1<<7 : 3<<3 | 1<<12;
		attr = (((PATWC&3)<<3) | ((PATWC&4)<<5) | ((PATWC&4)<<10));
		*pte = (*pte & ~mask) | (attr & mask);
	}
}
