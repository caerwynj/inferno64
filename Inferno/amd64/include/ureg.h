struct Ureg {
	u64	ax;
	u64	bx;
	u64	cx;
	u64	dx;
	u64	si;
	u64	di;
	u64	bp;
	u64	r8;
	u64	r9;
	u64	r10;
	u64	r11;
	u64	r12;
	u64	r13;
	u64	r14;	/* up-> */
	u64	r15;	/* m-> */

	u16	ds;
	u16	es;
	u16	fs;
	u16	gs;

	union {
		u64	trap;	/* trap type */
		u64 type;
	};
	union {
		u64	ecode;	/* error code (or zero) */
		u64 error;
	};
	u64	pc;		/* pc */
	u64	cs;		/* old context */
	u64	flags;	/* old flags */
	union {		/* sp */
		u64	usp;
		u64	sp;
	};
	u64	ss;		/* old stack segment */
};
