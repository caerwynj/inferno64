#include <lib9.h>

typedef struct	Instr	Instr;
struct	Instr
{
	ulong	w;
	ulong	addr;
	uchar	op;			/* super opcode */

	uchar	cond;			
	uchar	store;			

	uchar	rd;			
	uchar	rn;			
	uchar	rs;			

	long	imm;			/* rotated imm */
	char*	curr;			/* fill point in buffer */
	char*	end;			/* end of buffer */
	char*	err;			/* error message */
};

typedef struct Opcode Opcode;
struct Opcode
{
	char*	o;
	void	(*f)(Opcode*, Instr*);
	char*	a;
};

static	void	format(char*, Instr*, char*);
static	int	arminst(ulong, char, char*, int);
static	int	armdas(ulong, char*, int);

static
char*	cond[16] =
{
	"EQ",	"NE",	"CS",	"CC",
	"MI",	"PL",	"VS",	"VC",
	"HI",	"LS",	"GE",	"LT",
	"GT",	"LE",	0,	"NV"
};

static
char*	shtype[4] =
{
	"<<",	">>",	"->",	"@>"
};

static int
get4(ulong addr, uint *v)
{
	*v = *(uint*)addr;
	return 1;	
}

static char *
_hexify(char *buf, ulong p, int zeros)
{
	ulong d;

	d = p/16;
	if(d)
		buf = _hexify(buf, d, zeros-1);
	else
		while(zeros--)
			*buf++ = '0';
	*buf++ = "0123456789abcdef"[p&0x0f];
	return buf;
}

int
armclass(ulong w)
{
	uint op;

	op = (w >> 24) & 0x1f;
	switch(op) {
	case 0b01010:
		/* AND,ORR,EOR */
		op = (w>>29) & 0x3;
		break;
	case 0b01011:
		/* ADD,SUB,CMN,CMP */
		op = 4 + ((w>>29) & 0x3);
		break;
	case 0b11010:
		/* ADC,SUBC */
		op = 8 + ((w>>30) & 1);
		break;
	case 0b10010:
		/* MOVZ MOVK */	
		op = 10 + ((w>>29) & 0x3) - 2;
		break;
	case 0b10001:
		/* ADDI,SUBI,CMNI,CMPI */
		op = 12 + ((w>>29) & 0x3);
		break;
	case 0b10000:
		/* ADR,ADRP */
		op = 16 + ((w>>31) & 0x1);
		break;
	case 0b11011:
		/* MUL, MADD */
		op = 18;
		break;
	case 0b10100:
		/* B.c */
		op = 20;
		if(w>>31 == 0)
			break;
		/* else fall through */
	case 0b10101:
	case 0b10110:
	case 0b10111:
		/* RET, BL, BLR, BR*/
		if(w>>26 == 0x25)
			op = 21; //BL
		else 
			op = 22 + ((w >> 21) & 3); 
		break;
	case 0b11001:
		/* LDRI, STRI */
		op = 25 + ((w>>22) & 0x1) + ((w>>31) & 1)*2;
		break;
	case 0b11000:
		/* LDR, STR */
		op = 29 + ((w>>22) & 0x1) + ((w>>31) & 1)*2;
		break;
	default:
		op = 33;
		break;
	}
	return op;
}

static int
decode(ulong pc, Instr *i)
{
	uint w;

	get4(pc, &w);
	i->w = w;
	i->addr = pc;
	i->cond = (w >> 28) & 0xF;
	i->op = armclass(w);
	return 1;
}

static void
bprint(Instr *i, char *fmt, ...)
{
	va_list arg;

	va_start(arg, fmt);
	i->curr = vseprint(i->curr, i->end, fmt, arg);
	va_end(arg);
}

static void
armdps(Opcode *o, Instr *i)
{
	i->store = (i->w >> 29) & 1;
	i->rn = (i->w >> 5) & 0x1f;
	i->rd = (i->w >> 0) & 0x1f;
	i->rs = (i->w >> 16) & 0x1f;
	format(o->o, i, o->a);
}

static void
armdpi(Opcode *o, Instr *i)
{
	ulong v;

	v = (i->w>>10) & 0xfff;
	i->imm = v;
	i->store = (i->w >> 29) & 1;
	i->rn = (i->w >> 5) & 0x1f;
	i->rd = (i->w >> 0) & 0x1f;

	format(o->o, i, o->a);
}

static void
armdpi16(Opcode *o, Instr *i)
{
	ulong v;

	v = (i->w>>5) & 0xffff;
	i->imm = v;
	i->rd = (i->w >> 0) & 0x1f;

	format(o->o, i, o->a);
}

static void
armsdti(Opcode *o, Instr *i)
{
	ulong v;

	v = (i->w >> 10) & 0xfff;
	i->store = 0;
	i->imm = v*8;
	i->rn = (i->w >> 5) & 0x1f;
	i->rd = (i->w >> 0) & 0x1f;
	format(o->o, i, o->a);
}

static void
armsdts(Opcode *o, Instr *i)
{
	i->store = 0;
	i->rs = (i->w >> 16) & 0x1f;
	i->rn = (i->w >> 5) & 0x1f;
	i->rd = (i->w >> 0) & 0x1f;
	format(o->o, i, o->a);
}

static void
armbdt(Opcode *o, Instr *i)
{
	i->store = (i->w >> 21) & 0x3;		/* S & W bits */
	i->rn = (i->w >> 16) & 0xf;
	i->imm = i->w & 0xffff;
	if(i->w == 0xe8fd8000)
		format("RFE", i, "");
	else
		format(o->o, i, o->a);
}

static void
armbadr(Opcode *o, Instr *i)
{
	i->rd = i->w & 0x1f;
	i->imm = (((i->w >> 5) & 0x7ffff)<<2) | ((i->w >> 29) & 0x3);
	format(o->o, i, o->a);
}


static void
armund(Opcode *o, Instr *i)
{
	format(o->o, i, o->a);
}

static void
armcdt(Opcode *o, Instr *i)
{
	format(o->o, i, o->a);
}

static void
armunk(Opcode *o, Instr *i)
{
	format(o->o, i, o->a);
}

static void
armb(Opcode *o, Instr *i)
{
	ulong v;

	v = i->w & 0xffffff;
	if(v & 0x800000)
		v |= ~0xffffff;
	i->cond = i->w & 0xF;
	i->imm = (v<<2) + i->addr + 8;
	format(o->o, i, o->a);
}

static void
armco(Opcode *o, Instr *i)		/* coprocessor instructions */
{
	int op, p, cp;

	char buf[1024];

	i->rn = (i->w >> 16) & 0xf;
	i->rd = (i->w >> 12) & 0xf;
	i->rs = i->w&0xf;
	cp = (i->w >> 8) & 0xf;
	p = (i->w >> 5) & 0x7;
	if(i->w&0x10) {
		op = (i->w >> 20) & 0x0f;
		snprint(buf, sizeof(buf), "#%x, #%x, R%d, C(%d), C(%d), #%x\n", cp, op, i->rd, i->rn, i->rs, p);
	} else {
		op = (i->w >> 21) & 0x07;
		snprint(buf, sizeof(buf), "#%x, #%x, C(%d), C(%d), C(%d), #%x\n", cp, op, i->rd, i->rn, i->rs, p);
	}
	format(o->o, i, buf);
}

static Opcode opcodes[] =
{
	"AND%S",	armdps,	"(R%s%h#%m),R%n,R%d",
	"ORR%S",	armdps,	"(R%s%h#%m),R%n,R%d",
	"EOR%S",	armdps,	"(R%s%h#%m),R%n,R%d",
	"ORN",		armdps,	"(R%s%h#%m),R%n,R%d",

	"ADD%S",	armdps,	"(R%s%h#%m),R%n,R%d",
	"CMN%S",	armdps,	"(R%s%h#%m),R%n,",
	"SUB%S",	armdps,	"(R%s%h#%m),R%n,R%d",
	"CMP%S",	armdps,	"(R%s%h#%m),R%n,",

	"ADC%S",	armdps,	"(R%s%h#%m),R%n,R%d",
	"SBC%S",	armdps,	"(R%s%h#%m),R%n,R%d",

	"MOVZ",		armdpi16,"$#%i,lsl %q,R%d",
	"MOVK",		armdpi16,"$#%i,lsl %q,R%d",

	"ADD%S",	armdpi,	"$#%i,R%n,R%d",
	"CMN%S",	armdpi,	"$#%i,R%n,",
	"SUB%S",	armdpi,	"$#%i,R%n,R%d",
	"CMP%S",	armdpi,	"$#%i,R%n,",

	/* TODO instructions with bitmask immediate encoding 
	"AND%S",	armdpi,	"$#%i,R%n,R%d",
	"ORR%S",	armdpi,	"$#%i,R%n,R%d",
	*/

	"ADR",		armbadr,"%b,R%d",
	"ADRP",		armbadr,"%b,R%d",

	"MUL%S",	armdpi,	"R%s,R%m,R%n",
	"MADD", 	armdpi, "R%s,R%m,R%n",

	"B%C",		armb,	"%b",
	"BL",		armb,	"%b",
	"BR",		armsdts, "R%n",
	"BLR",		armsdts, "R%n",
	"RET",		armunk, "",

	"STRB",	armsdti,"R%d,#%i(R%n)",
	"LDRB",	armsdti,"#%i(R%n),R%d",
	"STR",	armsdti,"R%d,#%i(R%n)",
	"LDR",	armsdti,"#%i(R%n),R%d",

	"STRB",	armsdts,"R%d,%D(R%s%h#%m)(R%n)",
	"LDRB",	armsdts,"%D(R%s%h#%m)(R%n),R%d",
	"STR",	armsdts,"R%d,%D(R%s%h#%m)(R%n)",
	"LDR",	armsdts,"%D(R%s%h#%m)(R%n),R%d",

	"UNK",		armunk,	"",
};

static	char *mode[] = { 0, "IA", "DB", "IB" };
static	char *pw[] = { "P", "PW", 0, "W" };
static	char *sw[] = { 0, "W", "S", "SW" };

static void
format(char *mnemonic, Instr *i, char *f)
{
	int j, k, m, n;

	if(mnemonic)
		format(0, i, mnemonic);
	if(f == 0)
		return;
	if(mnemonic)
		if(i->curr < i->end)
			*i->curr++ = '\t';
	for ( ; *f && i->curr < i->end; f++) {
		if(*f != '%') {
			*i->curr++ = *f;
			continue;
		}
		switch (*++f) {

		case 'C':	/* .CONDITION */
			if(cond[i->cond])
				bprint(i, ".%s", cond[i->cond]);
			break;

		case 'S':	/* .STORE */
			if(i->store)
				bprint(i, ".S");
			break;

		case 'P':	/* P & U bits for block move */
			n = (i->w >>23) & 0x3;
			if (mode[n])
				bprint(i, ".%s", mode[n]);
			break;

		case 'D':	/* ~U bit for single data xfer */
			if((i->w & (1<<23)) == 0)
				bprint(i, "-");
			break;

		case 'p':	/* P & W bits for single data xfer*/
			if (pw[i->store])
				bprint(i, ".%s", pw[i->store]);
			break;

		case 'a':	/* S & W bits for single data xfer*/
			if (sw[i->store])
				bprint(i, ".%s", sw[i->store]);
			break;

		case 's':
			bprint(i, "%d", i->rs & 0xf);
			break;
				
		case 'm':
			bprint(i, "%d", (i->w>>10) & 0x3f);
			break;

		case 'q':
			bprint(i, "%d", ((i->w>>21) & 0x3)*16);
			break;

		case 'h':
			bprint(i, "%s", shtype[(i->w>>22) & 0x3]);
			break;

		case 'n':
			bprint(i, "%d", i->rn);
			break;

		case 'd':
			bprint(i, "%d", i->rd);
			break;

		case 'i':
			bprint(i, "%lux", i->imm);
			break;

		case 'b':
			bprint(i, "%lux", i->imm);
			break;

		case 'r':
			n = i->imm&0xffff;
			j = 0;
			k = 0;
			while(n) {
				m = j;
				while(n&0x1) {
					j++;
					n >>= 1;
				}
				if(j != m) {
					if(k)
						bprint(i, ",");
					if(j == m+1)
						bprint(i, "R%d", m);
					else
						bprint(i, "R%d-R%d", m, j-1);
					k = 1;
				}
				j++;
				n >>= 1;
			}
			break;

		case '\0':
			*i->curr++ = '%';
			return;

		default:
			bprint(i, "%%%c", *f);
			break;
		}
	}
	*i->curr = 0;
}

void
das(ulong *x, int n)
{
	ulong pc;
	Instr i;
	char buf[128];

	pc = (ulong)x;
	while(n > 0) {
		i.curr = buf;
		i.end = buf+sizeof(buf)-1;

		if(decode(pc, &i) < 0)
			sprint(buf, "???");
		else
			(*opcodes[i.op].f)(&opcodes[i.op], &i);

		print("%.8lux %.8lux\t%s\n", pc, i.w, buf);
		pc += 4;
		n--;
	}
}
