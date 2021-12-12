/*
 * Forth dictionary
 */
#define WORDB		(BY2WD*144)	/* word buffer */
#define TIB			(7*BY2PG)	/* text input buffer */
enum {
	Header,
	IHeader,	/* Immediate dictionary definition */
	Absolute,
	FromH0,
	Chars,
};

typedef struct Hdr Hdr;
		struct Hdr {
			int len;
			char *name;
			void *cfa;
		};
typedef struct Fentry Fentry;
struct Fentry
{
	int type;
	union {
		Hdr hdr;
		intptr p;
		char *str;
	} u;
};
enum {
	M_fetch = 16,
	M_store = 40,
	M_cfetch = 64,
	M_cstore = 88,
	M_fthread = 112,
	M_fthwrite = 136,
	M_fthseek = 160,
	M_fthopen = 184,
	M_fthclose = 208,
	M_mmap = 232,
	M_terminate = 256,
	M_clear = 280,
	M_reset = 304,
	M_exitcolon = 328,
	M_literal = 360,
	M_sliteral = 392,
	M_doinit = 416,
	M_doloop = 440,
	M_doploop = 464,
	M_rfetch = 488,
	M_rpop = 512,
	M_rpush = 536,
	M_i = 560,
	M_j = 584,
	M_plus = 608,
	M_minus = 632,
	M_multiply = 656,
	M_cjump = 680,
	M_jump = 704,
	M_slashmod = 728,
	M_uslashmod = 752,
	M_binand = 776,
	M_binor = 800,
	M_binxor = 824,
	M_xswap = 848,
	M_drop = 872,
	M_dup = 896,
	M_over = 920,
	M_equal = 944,
	M_greater = 968,
	M_less = 992,
	M_lshift = 1016,
	M_rshift = 1040,
	M_rshifta = 1064,
	M_execute = 1088,
	M_unloop = 1112,
	M_cmove = 1136,
	M_cmoveb = 1160,
	MV_Dp = 1184,
	MV_Dtop = 1216,
	MV_Iobuf = 1248,
	MV_Sourcebuf = 1288,
	MV_Wordbuf = 1320,
	MV_toIn = 1352,
	MV_toLimit = 1384,
	MV_Findadr = 1416,
	MV_Blk = 1448,
	MV_Searchlen = 1488,
	MV_Base = 1520,
	MV_toNum = 1552,
	MV_State = 1584,
	MV_Abortvec = 1616,
	MV_Infd = 1648,
	MV_Outfd = 1680,
	MV_Errfd = 1712,
	MV_Eof = 1744,
	MC_STDIN = 1776,
	MC_STDOUT = 1808,
	MC_STDERR = 1840,
	MC_WORDB = 1872,
	MC_TIB = 1904,
	M_s0 = 1936,
	M_stackptr = 1960,
	M_h0 = 1984,
	M_args = 2008,
	M_variable = 2040,
	M_constant = 2072,
	M_colon = 2096,
	M_dodoes = 2120,
	M_cas = 2144,
	M_deferred = 2176,
	C_false = 2200,
	C_true = 2248,
	C_bl = 2296,
	C_on = 2344,
	C_off = 2408,
	C_tobody = 2472,
	C_aligned = 2528,
	C_cells = 2608,
	C_cellplus = 2664,
	C_depth = 2728,
	C_nip = 2832,
	C_rot = 2880,
	C_2drop = 2944,
	C_2dup = 2992,
	C_2nip = 3040,
	C_2swap = 3088,
	C_qdup = 3152,
	L20 = 3224,
	C_pick = 3248,
	L22 = 3352,
	L23 = 3360,
	C_tuck = 3384,
	C_divides = 3448,
	C_plusstore = 3496,
	C_invert = 3576,
	C_mod = 3632,
	C_1plus = 3680,
	C_1minus = 3736,
	C_negate = 3792,
	C_2multiplies = 3856,
	C_2divides = 3912,
	C_0eq = 3968,
	C_0lt = 4024,
	C_0gt = 4080,
	C_neq = 4136,
	C_0neq = 4184,
	C_max = 4240,
	L40 = 4304,
	L41 = 4312,
	C_min = 4336,
	L43 = 4400,
	L44 = 4408,
	C_signum = 4432,
	L46 = 4512,
	L48 = 4568,
	L49 = 4584,
	L47 = 4584,
	C_within = 4608,
	C_abs = 4712,
	L52 = 4760,
	C_key = 4784,
	L78 = 4912,
	L79 = 4928,
	C_emit = 4952,
	C_type = 5056,
	C_cr = 5120,
	C_space = 5176,
	C_emits = 5224,
	L85 = 5232,
	L86 = 5296,
	C_spaces = 5328,
	C_count = 5384,
	C_compare = 5448,
	L55 = 5520,
	L56 = 5656,
	C_erase = 5736,
	L58 = 5768,
	C_fill = 5856,
	L60 = 5896,
	C_blank = 5984,
	C_search = 6032,
	L64 = 6136,
	L65 = 6320,
	C_here = 6384,
	C_comma = 6432,
	C_c = 6512,
	C_allot = 6592,
	C_pad = 6640,
	C_align = 6704,
	C_unused = 6768,
	C_fromhash = 6832,
	C_hash = 6912,
	L92 = 7064,
	L93 = 7088,
	C_hashs = 7168,
	L95 = 7176,
	L96 = 7224,
	C_hashfrom = 7248,
	C_hold = 7360,
	C_sign = 7464,
	L100 = 7520,
	C_dot = 7544,
	C_dotr = 7648,
	C_hex = 7808,
	C_decimal = 7872,
	C_digit = 7936,
	L106 = 8048,
	L108 = 8152,
	L110 = 8256,
	L111 = 8280,
	L109 = 8280,
	L107 = 8280,
	L112 = 8352,
	L113 = 8368,
	C_number = 8392,
	L115 = 8528,
	L116 = 8560,
	L117 = 8624,
	L118 = 8728,
	L119 = 8784,
	C_abort = 8872,
	C_source = 8928,
	C_current_input = 8984,
	C_save_input = 9064,
	C_default_input = 9192,
	C_restore_input = 9312,
	L133 = 9408,
	L134 = 9496,
	C_qrestore_input = 9528,
	L136 = 9632,
	C_next_input = 9664,
	L139 = 9760,
	L140 = 9784,
	C_parse = 9808,
	L142 = 9848,
	L143 = 9976,
	C_word = 10120,
	L145 = 10136,
	L146 = 10232,
	C_accept = 10272,
	L148 = 10312,
	L150 = 10472,
	L149 = 10536,
	C_query = 10584,
	L152 = 10728,
	L153 = 10760,
	C_refill = 10784,
	L155 = 10848,
	L156 = 10864,
	C_findname = 10888,
	L158 = 10928,
	L160 = 11040,
	L162 = 11168,
	L161 = 11176,
	L159 = 11192,
	C_find = 11240,
	L165 = 11432,
	L166 = 11448,
	L164 = 11472,
	L167 = 11480,
	C_single_quote = 11504,
	L169 = 11640,
	C_qstack = 11664,
	L172 = 11768,
	C_interpret = 11800,
	L175 = 11808,
	L177 = 11920,
	L179 = 12032,
	L178 = 12032,
	L176 = 12048,
	C_create = 12080,
	C_variable = 12320,
	C_constant = 12384,
	C_immediate = 12512,
	C_tocfa = 12624,
	C_compile = 12704,
	L189 = 12832,
	L190 = 12848,
	L188 = 12864,
	L192 = 12992,
	L194 = 13024,
	L191 = 13024,
	C_close_bracket = 13048,
	L196 = 13072,
	L197 = 13160,
	L198 = 13184,
	L199 = 13216,
	C_smudge = 13264,
	C_reveal = 13376,
	C_colon = 13496,
	C_L206 = 13728,
	C_literal = 13792,
	C_sliteral = 13856,
	C_string = 14024,
	L214 = 14368,
	L215 = 14400,
	C_qabort_parens = 14424,
	L217 = 14504,
	L218 = 14512,
	C_double_quote = 14576,
	C_cdouble_quote = 14704,
	L234 = 15448,
	L236 = 15536,
	C_wo = 15560,
	C_ro = 15656,
	C_rw = 15704,
	C_open_file = 15760,
	C_close_file = 16040,
	C_read_file = 16096,
	C_write_file = 16176,
	C_reposition_file = 16248,
	C_qfcheck = 16312,
	L246 = 16408,
	C_bye = 16432,
	C_include = 16488,
	C_crash = 16640,
	C_quit = 16728,
	L253 = 16752,
	C_parenabort = 16808,
	C_oldboot = 16976,
	C_boot = 17296,
	L137 = 17624,
	L170 = 17648,
	L173 = 17652,
	L180 = 17669,
	L193 = 17673,
	L247 = 17677,
	L251 = 17687,
	L255 = 17718,
};
extern void *sliteral(void);
extern void *cjump(void);
extern void *i(void);
extern void *equal(void);
extern void *j(void);
extern void *drop(void);
extern void *rpop(void);
extern void *fthwrite(void);
extern void *stackptr(void);
extern void *fthseek(void);
extern void *deferred(void);
extern void *cas(void);
extern void *s0(void);
extern void *xswap(void);
extern void *terminate(void);
extern void *greater(void);
extern void *slashmod(void);
extern void *cmoveb(void);
extern void *doinit(void);
extern void *multiply(void);
extern void *colon(void);
extern void *less(void);
extern void *lshift(void);
extern void *fthopen(void);
extern void *h0(void);
extern void *plus(void);
extern void *jump(void);
extern void *rshift(void);
extern void *cstore(void);
extern void *store(void);
extern void *cmove(void);
extern void *binor(void);
extern void *fthclose(void);
extern void *unloop(void);
extern void *cfetch(void);
extern void *constant(void);
extern void *variable(void);
extern void *fetch(void);
extern void *doloop(void);
extern void *mmap(void);
extern void *binxor(void);
extern void *fthread(void);
extern void *args(void);
extern void *dup(void);
extern void *exitcolon(void);
extern void *clear(void);
extern void *binand(void);
extern void *literal(void);
extern void *rpush(void);
extern void *over(void);
extern void *minus(void);
extern void *rfetch(void);
extern void *reset(void);
extern void *dodoes(void);
extern void *uslashmod(void);
extern void *execute(void);
extern void *rshifta(void);
extern void *doploop(void);
Fentry fentries[] = {
	{.type Header, .u {.hdr { 1, "@", /* M_fetch = 16 */ fetch }}}, /* MENTRY "@" fetch 1 h 24 */
	{.type Header, .u {.hdr { 1, "!", /* M_store = 40 */ store }}}, /* MENTRY "!" store 1 h 48 */
	{.type Header, .u {.hdr { 2, "c@", /* M_cfetch = 64 */ cfetch }}}, /* MENTRY "c@" cfetch 2 h 72 */
	{.type Header, .u {.hdr { 2, "c!", /* M_cstore = 88 */ cstore }}}, /* MENTRY "c!" cstore 2 h 96 */
	{.type Header, .u {.hdr { 4, "read", /* M_fthread = 112 */ fthread }}}, /* MENTRY "read" fthread 4 h 120 */
	{.type Header, .u {.hdr { 5, "write", /* M_fthwrite = 136 */ fthwrite }}}, /* MENTRY "write" fthwrite 5 h 144 */
	{.type Header, .u {.hdr { 4, "seek", /* M_fthseek = 160 */ fthseek }}}, /* MENTRY "seek" fthseek 4 h 168 */
	{.type Header, .u {.hdr { 4, "open", /* M_fthopen = 184 */ fthopen }}}, /* MENTRY "open" fthopen 4 h 192 */
	{.type Header, .u {.hdr { 5, "close", /* M_fthclose = 208 */ fthclose }}}, /* MENTRY "close" fthclose 5 h 216 */
	{.type Header, .u {.hdr { 4, "mmap", /* M_mmap = 232 */ mmap }}}, /* MENTRY "mmap" mmap 4 h 240 */
	{.type Header, .u {.hdr { 4, "halt", /* M_terminate = 256 */ terminate }}}, /* MENTRY "halt" terminate 4 h 264 */
	{.type Header, .u {.hdr { 5, "clear", /* M_clear = 280 */ clear }}}, /* MENTRY "clear" clear 5 h 288 */
	{.type Header, .u {.hdr { 5, "reset", /* M_reset = 304 */ reset }}}, /* MENTRY "reset" reset 5 h 312 */
	{.type Header, .u {.hdr { 4, "exitcolon", /* M_exitcolon = 328 */ exitcolon }}}, /* MENTRY "exitcolon" exitcolon 4 h 336 */
	{.type Header, .u {.hdr { 9, "(literal)", /* M_literal = 360 */ literal }}}, /* MENTRY "(literal)" literal 9 h 368 */
	{.type Header, .u {.hdr { 10, "(sliteral)", /* M_sliteral = 392 */ sliteral }}}, /* MENTRY "(sliteral)" sliteral 10 h 400 */
	{.type Header, .u {.hdr { 4, "(do)", /* M_doinit = 416 */ doinit }}}, /* MENTRY "(do)" doinit 4 h 424 */
	{.type Header, .u {.hdr { 6, "(loop)", /* M_doloop = 440 */ doloop }}}, /* MENTRY "(loop)" doloop 6 h 448 */
	{.type Header, .u {.hdr { 7, "(+loop)", /* M_doploop = 464 */ doploop }}}, /* MENTRY "(+loop)" doploop 7 h 472 */
	{.type Header, .u {.hdr { 2, "r@", /* M_rfetch = 488 */ rfetch }}}, /* MENTRY "r@" rfetch 2 h 496 */
	{.type Header, .u {.hdr { 2, "r>", /* M_rpop = 512 */ rpop }}}, /* MENTRY "r>" rpop 2 h 520 */
	{.type Header, .u {.hdr { 2, ">r", /* M_rpush = 536 */ rpush }}}, /* MENTRY ">r" rpush 2 h 544 */
	{.type Header, .u {.hdr { 1, "i", /* M_i = 560 */ i }}}, /* MENTRY "i" i 1 h 568 */
	{.type Header, .u {.hdr { 1, "j", /* M_j = 584 */ j }}}, /* MENTRY "j" j 1 h 592 */
	{.type Header, .u {.hdr { 1, "+", /* M_plus = 608 */ plus }}}, /* MENTRY "+" plus 1 h 616 */
	{.type Header, .u {.hdr { 1, "-", /* M_minus = 632 */ minus }}}, /* MENTRY "-" minus 1 h 640 */
	{.type Header, .u {.hdr { 1, "*", /* M_multiply = 656 */ multiply }}}, /* MENTRY "*" multiply 1 h 664 */
	{.type Header, .u {.hdr { 4, "(if)", /* M_cjump = 680 */ cjump }}}, /* MENTRY "(if)" cjump 4 h 688 */
	{.type Header, .u {.hdr { 6, "(else)", /* M_jump = 704 */ jump }}}, /* MENTRY "(else)" jump 6 h 712 */
	{.type Header, .u {.hdr { 4, "/mod", /* M_slashmod = 728 */ slashmod }}}, /* MENTRY "/mod" slashmod 4 h 736 */
	{.type Header, .u {.hdr { 5, "u/mod", /* M_uslashmod = 752 */ uslashmod }}}, /* MENTRY "u/mod" uslashmod 5 h 760 */
	{.type Header, .u {.hdr { 3, "and", /* M_binand = 776 */ binand }}}, /* MENTRY "and" binand 3 h 784 */
	{.type Header, .u {.hdr { 2, "or", /* M_binor = 800 */ binor }}}, /* MENTRY "or" binor 2 h 808 */
	{.type Header, .u {.hdr { 3, "xor", /* M_binxor = 824 */ binxor }}}, /* MENTRY "xor" binxor 3 h 832 */
	{.type Header, .u {.hdr { 4, "swap", /* M_xswap = 848 */ xswap }}}, /* MENTRY "swap" xswap 4 h 856 */
	{.type Header, .u {.hdr { 4, "drop", /* M_drop = 872 */ drop }}}, /* MENTRY "drop" drop 4 h 880 */
	{.type Header, .u {.hdr { 3, "dup", /* M_dup = 896 */ dup }}}, /* MENTRY "dup" dup 3 h 904 */
	{.type Header, .u {.hdr { 4, "over", /* M_over = 920 */ over }}}, /* MENTRY "over" over 4 h 928 */
	{.type Header, .u {.hdr { 1, "=", /* M_equal = 944 */ equal }}}, /* MENTRY "=" equal 1 h 952 */
	{.type Header, .u {.hdr { 1, ">", /* M_greater = 968 */ greater }}}, /* MENTRY ">" greater 1 h 976 */
	{.type Header, .u {.hdr { 1, "<", /* M_less = 992 */ less }}}, /* MENTRY "<" less 1 h 1000 */
	{.type Header, .u {.hdr { 6, "lshift", /* M_lshift = 1016 */ lshift }}}, /* MENTRY "lshift" lshift 6 h 1024 */
	{.type Header, .u {.hdr { 6, "rshift", /* M_rshift = 1040 */ rshift }}}, /* MENTRY "rshift" rshift 6 h 1048 */
	{.type Header, .u {.hdr { 7, "rshifta", /* M_rshifta = 1064 */ rshifta }}}, /* MENTRY "rshifta" rshifta 7 h 1072 */
	{.type Header, .u {.hdr { 7, "execute", /* M_execute = 1088 */ execute }}}, /* MENTRY "execute" execute 7 h 1096 */
	{.type Header, .u {.hdr { 6, "unloop", /* M_unloop = 1112 */ unloop }}}, /* MENTRY "unloop" unloop 6 h 1120 */
	{.type Header, .u {.hdr { 5, "cmove", /* M_cmove = 1136 */ cmove }}}, /* MENTRY "cmove" cmove 5 h 1144 */
	{.type Header, .u {.hdr { 6, "cmove>", /* M_cmoveb = 1160 */ cmoveb }}}, /* MENTRY "cmove>" cmoveb 6 h 1168 */
	{.type Header, .u {.hdr { 2, "Dp", /* MV_Dp = 1184 */ variable }}}, /* MVENTRY "Dp" Dp 0 2			; cannot use H as it is nil in inferno next available cell for the dictionary h 1192 */
	{.type Absolute, .u {.p 0}},		/* 1200 */
	{.type Header, .u {.hdr { 4, "Dtop", /* MV_Dtop = 1216 */ variable }}}, /* MVENTRY "Dtop" Dtop 0 4	; TODO put centry_c_boot here. cannot use H as it is nil in inferno next available cell for the dictionary h 1224 */
	{.type Absolute, .u {.p 0}},		/* 1232 */
	{.type Header, .u {.hdr { 5, "Iobuf", /* MV_Iobuf = 1248 */ variable }}}, /* MVENTRY "Iobuf" Iobuf 0 5 h 1256 */
	{.type Absolute, .u {.p 0}},		/* 1264 */
	{.type Header, .u {.hdr { 9, "Sourcebuf", /* MV_Sourcebuf = 1288 */ variable }}}, /* MVENTRY "Sourcebuf" Sourcebuf 0 9	; is there a need for this? h 1296 */
	{.type Absolute, .u {.p 0}},		/* 1304 */
	{.type Header, .u {.hdr { 7, "Wordbuf", /* MV_Wordbuf = 1320 */ variable }}}, /* MVENTRY "Wordbuf" Wordbuf 0 7		; is there a need for this? h 1328 */
	{.type Absolute, .u {.p 0}},		/* 1336 */
	{.type Header, .u {.hdr { 3, ">In", /* MV_toIn = 1352 */ variable }}}, /* MVENTRY ">In" toIn 0 3 h 1360 */
	{.type Absolute, .u {.p 0}},		/* 1368 */
	{.type Header, .u {.hdr { 6, ">Limit", /* MV_toLimit = 1384 */ variable }}}, /* MVENTRY ">Limit" toLimit 0 6 h 1392 */
	{.type Absolute, .u {.p 0}},		/* 1400 */
	{.type Header, .u {.hdr { 7, "Findadr", /* MV_Findadr = 1416 */ variable }}}, /* MVENTRY "Findadr" Findadr 0 7 h 1424 */
	{.type Absolute, .u {.p 0}},		/* 1432 */
	{.type Header, .u {.hdr { 3, "Blk", /* MV_Blk = 1448 */ variable }}}, /* MVENTRY "Blk" Blk 0 3 h 1456 */
	{.type Absolute, .u {.p 0}},		/* 1464 */
	{.type Header, .u {.hdr { 9, "Searchlen", /* MV_Searchlen = 1488 */ variable }}}, /* MVENTRY "Searchlen" Searchlen 0 9 h 1496 */
	{.type Absolute, .u {.p 0}},		/* 1504 */
	{.type Header, .u {.hdr { 4, "Base", /* MV_Base = 1520 */ variable }}}, /* MVENTRY "Base" Base 0 4 h 1528 */
	{.type Absolute, .u {.p 0}},		/* 1536 */
	{.type Header, .u {.hdr { 4, ">Num", /* MV_toNum = 1552 */ variable }}}, /* MVENTRY ">Num" toNum 0 4 h 1560 */
	{.type Absolute, .u {.p 0}},		/* 1568 */
	{.type Header, .u {.hdr { 5, "State", /* MV_State = 1584 */ variable }}}, /* MVENTRY "State" State 0 5 h 1592 */
	{.type Absolute, .u {.p 0}},		/* 1600 */
	{.type Header, .u {.hdr { 8, "Abortvec", /* MV_Abortvec = 1616 */ variable }}}, /* MVENTRY "Abortvec" Abortvec 0 8	; not sure if these 3 can be constants instead? h 1624 */
	{.type Absolute, .u {.p 0}},		/* 1632 */
	{.type Header, .u {.hdr { 5, "Infd", /* MV_Infd = 1648 */ variable }}}, /* MVENTRY "Infd" Infd 0 5 h 1656 */
	{.type Absolute, .u {.p 0}},		/* 1664 */
	{.type Header, .u {.hdr { 6, "Outfd", /* MV_Outfd = 1680 */ variable }}}, /* MVENTRY "Outfd" Outfd 0 6 h 1688 */
	{.type Absolute, .u {.p 0}},		/* 1696 */
	{.type Header, .u {.hdr { 4, "Errfd", /* MV_Errfd = 1712 */ variable }}}, /* MVENTRY "Errfd" Errfd 0 4 h 1720 */
	{.type Absolute, .u {.p 0}},		/* 1728 */
	{.type Header, .u {.hdr { 3, "Eof", /* MV_Eof = 1744 */ variable }}}, /* MVENTRY "Eof" Eof 0 3 h 1752 */
	{.type Absolute, .u {.p 0}},		/* 1760 */
	{.type Header, .u {.hdr { 5, "STDIN", /* MC_STDIN = 1776 */ constant }}}, /* MCENTRY "STDIN" STDIN 0 5		; 3 constants from here CAPITALS h 1784 */
	{.type Absolute, .u {.p 0}},		/* 1792 */
	{.type Header, .u {.hdr { 6, "STDOUT", /* MC_STDOUT = 1808 */ constant }}}, /* MCENTRY "STDOUT" STDOUT 1 6 h 1816 */
	{.type Absolute, .u {.p 1}},		/* 1824 */
	{.type Header, .u {.hdr { 6, "STDERR", /* MC_STDERR = 1840 */ constant }}}, /* MCENTRY "STDERR" STDERR 2 6 h 1848 */
	{.type Absolute, .u {.p 2}},		/* 1856 */
	{.type Header, .u {.hdr { 5, "WORDB", /* MC_WORDB = 1872 */ constant }}}, /* MCENTRY "WORDB" WORDB WORDB 5 h 1880 */
	{.type Absolute, .u {.p WORDB}},		/* 1888 */
	{.type Header, .u {.hdr { 3, "TIB", /* MC_TIB = 1904 */ constant }}}, /* MCENTRY "TIB" TIB TIB 3 h 1912 */
	{.type Absolute, .u {.p TIB}},		/* 1920 */
	{.type Header, .u {.hdr { 2, "s0", /* M_s0 = 1936 */ s0 }}}, /* MENTRY "s0" s0 2 h 1944 */
	{.type Header, .u {.hdr { 2, "s@", /* M_stackptr = 1960 */ stackptr }}}, /* MENTRY "s@" stackptr 2		; puts PSP on stack h 1968 */
	{.type Header, .u {.hdr { 2, "h0", /* M_h0 = 1984 */ h0 }}}, /* MENTRY "h0" h0 2 h 1992 */
	{.type Header, .u {.hdr { 3, "args", /* M_args = 2008 */ args }}}, /* MENTRY "args" args 3 h 2016 */
	{.type Header, .u {.hdr { 10, "(variable)", /* M_variable = 2040 */ variable }}}, /* MENTRY "(variable)" variable 10 h 2048 */
	{.type Header, .u {.hdr { 10, "(constant)", /* M_constant = 2072 */ constant }}}, /* MENTRY "(constant)" constant 10 h 2080 */
	{.type Header, .u {.hdr { 3, "(:)", /* M_colon = 2096 */ colon }}}, /* MENTRY "(:)" colon 3 h 2104 */
	{.type Header, .u {.hdr { 6, "(does)", /* M_dodoes = 2120 */ dodoes }}}, /* MENTRY "(does)" dodoes 6 h 2128 */
	{.type Header, .u {.hdr { 3, "cas", /* M_cas = 2144 */ cas }}}, /* MENTRY "cas" cas 3 h 2152 */
	{.type Header, .u {.hdr { 10, "(deferred)", /* M_deferred = 2176 */ deferred }}}, /* MENTRY "(deferred)" deferred 10 h 2184 */
	{.type Header, .u {.hdr { 5, "false", /* C_false = 2200 */ colon }}}, /* CENTRY "false" false 5 h 2208 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 2216 */
	{.type Absolute, .u {.p 0}},		/* dd 0 2224 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2232 */
	{.type Header, .u {.hdr { 4, "true", /* C_true = 2248 */ colon }}}, /* CENTRY "true" true 4 h 2256 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 2264 */
	{.type Absolute, .u {.p -1}},		/* dd -1 2272 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2280 */
	{.type Header, .u {.hdr { 2, "bl", /* C_bl = 2296 */ colon }}}, /* CENTRY "bl" bl 2 h 2304 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 2312 */
	{.type Absolute, .u {.p 32}},		/* dd 32 2320 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2328 */
	{.type Header, .u {.hdr { 2, "on", /* C_on = 2344 */ colon }}}, /* CENTRY "on" on 2 ; ( a -- ) (G stores -1 at a ) h 2352 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 2360 */
	{.type Absolute, .u {.p -1}},		/* dd -1 2368 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 2376 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 2384 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2392 */
	{.type Header, .u {.hdr { 3, "off", /* C_off = 2408 */ colon }}}, /* CENTRY "off" off 3 ; ( a -- ) (G stores 0 at a ) h 2416 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 2424 */
	{.type Absolute, .u {.p 0}},		/* dd 0 2432 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 2440 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 2448 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2456 */
	{.type Header, .u {.hdr { 5, ">body", /* C_tobody = 2472 */ colon }}}, /* CENTRY ">body" tobody 5 h 2480 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 2488 */
	{.type Absolute, .u {.p 8}},		/* dd 8 2496 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 2504 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2512 */
	{.type Header, .u {.hdr { 7, "aligned", /* C_aligned = 2528 */ colon }}}, /* CENTRY "aligned" aligned 7 h 2536 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 2544 */
	{.type Absolute, .u {.p 7}},		/* dd 7 2552 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 2560 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 2568 */
	{.type Absolute, .u {.p -8}},		/* dd -8 2576 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand 2584 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2592 */
	{.type Header, .u {.hdr { 5, "cells", /* C_cells = 2608 */ colon }}}, /* CENTRY "cells" cells 5 h 2616 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 2624 */
	{.type Absolute, .u {.p 3}},		/* dd 3			; (index << 2) -> (index << 3)for amd64 2632 */
	{.type FromH0, .u {.p M_lshift}},		/* dd M_lshift 2640 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2648 */
	{.type Header, .u {.hdr { 5, "cell+", /* C_cellplus = 2664 */ colon }}}, /* CENTRY "cell+" cellplus 5 h 2672 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 2680 */
	{.type Absolute, .u {.p 1}},		/* dd 1 2688 */
	{.type FromH0, .u {.p C_cells}},		/* dd C_cells 2696 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 2704 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2712 */
	{.type Header, .u {.hdr { 5, "depth", /* C_depth = 2728 */ colon }}}, /* CENTRY "depth" depth 5 h 2736 */
	{.type FromH0, .u {.p M_s0}},		/* dd M_s0 2744 */
	{.type FromH0, .u {.p M_stackptr}},		/* dd M_stackptr 2752 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 2760 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 2768 */
	{.type Absolute, .u {.p 3}},		/* dd 3 2776 */
	{.type FromH0, .u {.p M_rshift}},		/* dd M_rshift 2784 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 2792 */
	{.type Absolute, .u {.p 1}},		/* dd 1 2800 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 2808 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2816 */
	{.type Header, .u {.hdr { 3, "nip", /* C_nip = 2832 */ colon }}}, /* CENTRY "nip" nip 3 h 2840 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 2848 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 2856 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2864 */
	{.type Header, .u {.hdr { 3, "rot", /* C_rot = 2880 */ colon }}}, /* CENTRY "rot" rot 3 h 2888 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 2896 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 2904 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 2912 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 2920 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2928 */
	{.type Header, .u {.hdr { 5, "2drop", /* C_2drop = 2944 */ colon }}}, /* CENTRY "2drop" 2drop 5 h 2952 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 2960 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 2968 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 2976 */
	{.type Header, .u {.hdr { 4, "2dup", /* C_2dup = 2992 */ colon }}}, /* CENTRY "2dup" 2dup 4 h 3000 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 3008 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 3016 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3024 */
	{.type Header, .u {.hdr { 4, "2nip", /* C_2nip = 3040 */ colon }}}, /* CENTRY "2nip" 2nip 4 h 3048 */
	{.type FromH0, .u {.p C_nip}},		/* dd C_nip 3056 */
	{.type FromH0, .u {.p C_nip}},		/* dd C_nip 3064 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3072 */
	{.type Header, .u {.hdr { 5, "2swap", /* C_2swap = 3088 */ colon }}}, /* CENTRY "2swap" 2swap 5 h 3096 */
	{.type FromH0, .u {.p C_rot}},		/* dd C_rot 3104 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 3112 */
	{.type FromH0, .u {.p C_rot}},		/* dd C_rot 3120 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 3128 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3136 */
	{.type Header, .u {.hdr { 4, "?dup", /* C_qdup = 3152 */ colon }}}, /* CENTRY "?dup" qdup 4 ; if (tos != 0) dup ( n -- ) TODO correct stack notations h 3160 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup	; ( n n -- ) 3168 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup	; ( n n n -- ) 3176 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 3184 */
	{.type Absolute, .u {.p 0}},		/* dd 0		; ( n n n 0 -- ) 3192 */
	{.type FromH0, .u {.p M_equal}},		/* dd M_equal	; ( n n f -- ) 3200 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump	; ( n n -- ) 3208 */
	{.type FromH0, .u {.p L20}},		/* dd L20 3216 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop	; tos == 0 ( n -- ) 3224 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3232 */
	{.type Header, .u {.hdr { 4, "pick", /* C_pick = 3248 */ colon }}}, /* CENTRY "pick" pick 4 h 3256 */
	{.type FromH0, .u {.p C_qdup}},		/* dd C_qdup 3264 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 3272 */
	{.type FromH0, .u {.p L22}},		/* dd L22 3280 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 3288 */
	{.type Absolute, .u {.p 1}},		/* dd 1 3296 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 3304 */
	{.type FromH0, .u {.p C_cells}},		/* dd C_cells 3312 */
	{.type FromH0, .u {.p M_stackptr}},		/* dd M_stackptr 3320 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 3328 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 3336 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 3344 */
	{.type FromH0, .u {.p L23}},		/* dd L23 3352 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 3360 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3368 */
	{.type Header, .u {.hdr { 4, "tuck", /* C_tuck = 3384 */ colon }}}, /* CENTRY "tuck" tuck 4 h 3392 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 3400 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 3408 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 3416 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 3424 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3432 */
	{.type Header, .u {.hdr { 1, "/", /* C_divides = 3448 */ colon }}}, /* CENTRY "/" divides 1 h 3456 */
	{.type FromH0, .u {.p M_slashmod}},		/* dd M_slashmod 3464 */
	{.type FromH0, .u {.p C_nip}},		/* dd C_nip 3472 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3480 */
	{.type Header, .u {.hdr { 2, "+!", /* C_plusstore = 3496 */ colon }}}, /* CENTRY "+!" plusstore 2 h 3504 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 3512 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 3520 */
	{.type FromH0, .u {.p C_rot}},		/* dd C_rot 3528 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 3536 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 3544 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 3552 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3560 */
	{.type Header, .u {.hdr { 6, "invert", /* C_invert = 3576 */ colon }}}, /* CENTRY "invert" invert 6 h 3584 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 3592 */
	{.type Absolute, .u {.p -1}},		/* dd -1 3600 */
	{.type FromH0, .u {.p M_binxor}},		/* dd M_binxor 3608 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3616 */
	{.type Header, .u {.hdr { 3, "mod", /* C_mod = 3632 */ colon }}}, /* CENTRY "mod" mod 3 h 3640 */
	{.type FromH0, .u {.p M_slashmod}},		/* dd M_slashmod 3648 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 3656 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3664 */
	{.type Header, .u {.hdr { 2, "1+", /* C_1plus = 3680 */ colon }}}, /* CENTRY "1+" 1plus 2 h 3688 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 3696 */
	{.type Absolute, .u {.p 1}},		/* dd 1 3704 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 3712 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3720 */
	{.type Header, .u {.hdr { 2, "1-", /* C_1minus = 3736 */ colon }}}, /* CENTRY "1-" 1minus 2 h 3744 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 3752 */
	{.type Absolute, .u {.p 1}},		/* dd 1 3760 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 3768 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3776 */
	{.type Header, .u {.hdr { 6, "negate", /* C_negate = 3792 */ colon }}}, /* CENTRY "negate" negate 6 h 3800 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 3808 */
	{.type Absolute, .u {.p 0}},		/* dd 0 3816 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 3824 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 3832 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3840 */
	{.type Header, .u {.hdr { 2, "2*", /* C_2multiplies = 3856 */ colon }}}, /* CENTRY "2*" 2multiplies 2 h 3864 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 3872 */
	{.type Absolute, .u {.p 1}},		/* dd 1 3880 */
	{.type FromH0, .u {.p M_lshift}},		/* dd M_lshift 3888 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3896 */
	{.type Header, .u {.hdr { 2, "2/", /* C_2divides = 3912 */ colon }}}, /* CENTRY "2/" 2divides 2 h 3920 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 3928 */
	{.type Absolute, .u {.p 1}},		/* dd 1 3936 */
	{.type FromH0, .u {.p M_rshifta}},		/* dd M_rshifta 3944 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 3952 */
	{.type Header, .u {.hdr { 2, "0=", /* C_0eq = 3968 */ colon }}}, /* CENTRY "0=" 0eq 2 h 3976 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 3984 */
	{.type Absolute, .u {.p 0}},		/* dd 0 3992 */
	{.type FromH0, .u {.p M_equal}},		/* dd M_equal 4000 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 4008 */
	{.type Header, .u {.hdr { 2, "0<", /* C_0lt = 4024 */ colon }}}, /* CENTRY "0<" 0lt 2 h 4032 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 4040 */
	{.type Absolute, .u {.p 0}},		/* dd 0 4048 */
	{.type FromH0, .u {.p M_less}},		/* dd M_less 4056 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 4064 */
	{.type Header, .u {.hdr { 2, "0>", /* C_0gt = 4080 */ colon }}}, /* CENTRY "0>" 0gt 2 h 4088 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 4096 */
	{.type Absolute, .u {.p 0}},		/* dd 0 4104 */
	{.type FromH0, .u {.p M_greater}},		/* dd M_greater 4112 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 4120 */
	{.type Header, .u {.hdr { 2, "<>", /* C_neq = 4136 */ colon }}}, /* CENTRY "<>" neq 2 h 4144 */
	{.type FromH0, .u {.p M_equal}},		/* dd M_equal 4152 */
	{.type FromH0, .u {.p C_invert}},		/* dd C_invert 4160 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 4168 */
	{.type Header, .u {.hdr { 3, "0<>", /* C_0neq = 4184 */ colon }}}, /* CENTRY "0<>" 0neq 3 h 4192 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 4200 */
	{.type Absolute, .u {.p 0}},		/* dd 0 4208 */
	{.type FromH0, .u {.p C_neq}},		/* dd C_neq 4216 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 4224 */
	{.type Header, .u {.hdr { 3, "max", /* C_max = 4240 */ colon }}}, /* CENTRY "max" max 3 h 4248 */
	{.type FromH0, .u {.p C_2dup}},		/* dd C_2dup 4256 */
	{.type FromH0, .u {.p M_greater}},		/* dd M_greater 4264 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 4272 */
	{.type FromH0, .u {.p L40}},		/* dd L40 4280 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 4288 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 4296 */
	{.type FromH0, .u {.p L41}},		/* dd L41 4304 */
	{.type FromH0, .u {.p C_nip}},		/* dd C_nip 4312 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 4320 */
	{.type Header, .u {.hdr { 3, "min", /* C_min = 4336 */ colon }}}, /* CENTRY "min" min 3 h 4344 */
	{.type FromH0, .u {.p C_2dup}},		/* dd C_2dup 4352 */
	{.type FromH0, .u {.p M_less}},		/* dd M_less 4360 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 4368 */
	{.type FromH0, .u {.p L43}},		/* dd L43 4376 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 4384 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 4392 */
	{.type FromH0, .u {.p L44}},		/* dd L44 4400 */
	{.type FromH0, .u {.p C_nip}},		/* dd C_nip 4408 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 4416 */
	{.type Header, .u {.hdr { 6, "signum", /* C_signum = 4432 */ colon }}}, /* CENTRY "signum" signum 6 h 4440 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 4448 */
	{.type FromH0, .u {.p C_0gt}},		/* dd C_0gt 4456 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 4464 */
	{.type FromH0, .u {.p L46}},		/* dd L46 4472 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 4480 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 4488 */
	{.type Absolute, .u {.p 1}},		/* dd 1 4496 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 4504 */
	{.type FromH0, .u {.p L47}},		/* dd L47 4512 */
	{.type FromH0, .u {.p C_0lt}},		/* dd C_0lt 4520 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 4528 */
	{.type FromH0, .u {.p L48}},		/* dd L48 4536 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 4544 */
	{.type Absolute, .u {.p -1}},		/* dd -1 4552 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 4560 */
	{.type FromH0, .u {.p L49}},		/* dd L49 4568 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 4576 */
	{.type Absolute, .u {.p 0}},		/* dd 0 4584 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 4592 */
	{.type Header, .u {.hdr { 6, "within", /* C_within = 4608 */ colon }}}, /* CENTRY "within" within 6 h 4616 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 4624 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 4632 */
	{.type FromH0, .u {.p M_greater}},		/* dd M_greater 4640 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq 4648 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 4656 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 4664 */
	{.type FromH0, .u {.p M_greater}},		/* dd M_greater 4672 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq 4680 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand 4688 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 4696 */
	{.type Header, .u {.hdr { 3, "abs", /* C_abs = 4712 */ colon }}}, /* CENTRY "abs" abs 3 h 4720 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 4728 */
	{.type FromH0, .u {.p C_0lt}},		/* dd C_0lt 4736 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 4744 */
	{.type FromH0, .u {.p L52}},		/* dd L52 4752 */
	{.type FromH0, .u {.p C_negate}},		/* dd C_negate 4760 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 4768 */
	{.type Header, .u {.hdr { 3, "key", /* C_key = 4784 */ colon }}}, /* CENTRY "key" key 3 ; ( -- c ) (G read a single character from the input onto the stack ) h 4792 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 4800 */
	{.type Absolute, .u {.p 1}},		/* dd 1			; ( 1 -- ) 4808 */
	{.type FromH0, .u {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf to store the character read 4816 */
	{.type FromH0, .u {.p MV_Infd}},		/* dd MV_Infd 4824 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch		; ( 1 Iobuf -- 1 Iobuf infd ) 4832 */
	{.type FromH0, .u {.p M_fthread}},		/* dd M_fthread	; ( 1 Iobuf infd -- n ) 4840 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq 4848 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump		; if 0 characters read 4856 */
	{.type FromH0, .u {.p L78}},		/* dd L78			; if qread n != 0 jump to L78. If n == 0 jump over 4864 */
	{.type FromH0, .u {.p MV_Eof}},		/* dd MV_Eof 4872 */
	{.type FromH0, .u {.p C_on}},		/* dd C_on		; EOF 4880 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 4888 */
	{.type Absolute, .u {.p -1}},		/* dd -1			; return -1 when EOF 4896 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 4904 */
	{.type FromH0, .u {.p L79}},		/* dd L79 4912 */
	{.type FromH0, .u {.p MV_Iobuf}},		/* dd MV_Iobuf		; get the character from Iobuf to stack 4920 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch	; ( -- c ) return the character read if not EOF 4928 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 4936 */
	{.type Header, .u {.hdr { 4, "emit", /* C_emit = 4952 */ colon }}}, /* CENTRY "emit" emit 4 ; ( character -- ) h 4960 */
	{.type FromH0, .u {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf address 4968 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore	; variable iobuf has character 4976 */
	{.type FromH0, .u {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf address 4984 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 4992 */
	{.type Absolute, .u {.p 1}},		/* dd 1 5000 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap		; ( iobuf 1 --  1 iobuf ) 5008 */
	{.type FromH0, .u {.p MV_Outfd}},		/* dd MV_Outfd 5016 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch		; outfd 5024 */
	{.type FromH0, .u {.p M_fthwrite}},		/* dd M_fthwrite	; ( 1 iobuf outfd --  ) 5032 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 5040 */
	{.type Header, .u {.hdr { 4, "type", /* C_type = 5056 */ colon }}}, /* CENTRY "type" type 4 ; ( addr n -- ) h 5064 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap			; ( addr n --  n addr ) 5072 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 5080 */
	{.type Absolute, .u {.p 1}},		/* dd 1				; stdout 5088 */
	{.type FromH0, .u {.p M_fthwrite}},		/* dd M_fthwrite			; ( n addr 1 --  ) 5096 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 5104 */
	{.type Header, .u {.hdr { 2, "cr", /* C_cr = 5120 */ colon }}}, /* CENTRY "cr" cr 2 h 5128 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 5136 */
	{.type Absolute, .u {.p 10}},		/* dd 10			; ascii value of carriage return 5144 */
	{.type FromH0, .u {.p C_emit}},		/* dd C_emit			; emit 5152 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 5160 */
	{.type Header, .u {.hdr { 5, "space", /* C_space = 5176 */ colon }}}, /* CENTRY "space" space 5 h 5184 */
	{.type FromH0, .u {.p C_bl}},		/* dd C_bl 5192 */
	{.type FromH0, .u {.p C_emit}},		/* dd C_emit 5200 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 5208 */
	{.type Header, .u {.hdr { 5, "emits", /* C_emits = 5224 */ colon }}}, /* CENTRY "emits" emits 5 h 5232 */
	{.type FromH0, .u {.p C_qdup}},		/* dd C_qdup 5240 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 5248 */
	{.type FromH0, .u {.p L86}},		/* dd L86 5256 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 5264 */
	{.type FromH0, .u {.p C_emit}},		/* dd C_emit 5272 */
	{.type FromH0, .u {.p C_1minus}},		/* dd C_1minus 5280 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 5288 */
	{.type FromH0, .u {.p L85}},		/* dd L85 5296 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 5304 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 5312 */
	{.type Header, .u {.hdr { 6, "spaces", /* C_spaces = 5328 */ colon }}}, /* CENTRY "spaces" spaces 6 h 5336 */
	{.type FromH0, .u {.p C_bl}},		/* dd C_bl 5344 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 5352 */
	{.type FromH0, .u {.p C_emits}},		/* dd C_emits 5360 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 5368 */
	{.type Header, .u {.hdr { 5, "count", /* C_count = 5384 */ colon }}}, /* CENTRY "count" count 5 ; ( a -- a+1 n ) a = counted string h 5392 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus 5400 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 5408 */
	{.type FromH0, .u {.p C_1minus}},		/* dd C_1minus 5416 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 5424 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 5432 */
	{.type Header, .u {.hdr { 7, "compare", /* C_compare = 5448 */ colon }}}, /* CENTRY "compare" compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search h 5456 */
	{.type FromH0, .u {.p C_rot}},		/* dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 5464 */
	{.type FromH0, .u {.p C_2dup}},		/* dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 ) 5472 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- ) 5480 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- ) 5488 */
	{.type FromH0, .u {.p C_min}},		/* dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- ) 5496 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 5504 */
	{.type Absolute, .u {.p 0}},		/* dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- ) 5512 */
	{.type FromH0, .u {.p M_doinit}},		/* dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- ) 5520 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 5528 */
	{.type FromH0, .u {.p M_i}},		/* dd M_i 5536 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 5544 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 5552 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 5560 */
	{.type FromH0, .u {.p M_i}},		/* dd M_i 5568 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 5576 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 5584 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 5592 */
	{.type FromH0, .u {.p C_signum}},		/* dd C_signum 5600 */
	{.type FromH0, .u {.p C_qdup}},		/* dd C_qdup 5608 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 5616 */
	{.type FromH0, .u {.p L56}},		/* dd L56 5624 */
	{.type FromH0, .u {.p C_2nip}},		/* dd C_2nip 5632 */
	{.type FromH0, .u {.p M_unloop}},		/* dd M_unloop 5640 */
	{.type FromH0, .u {.p M_unloop}},		/* dd M_unloop 5648 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 5656 */
	{.type FromH0, .u {.p M_doloop}},		/* dd M_doloop 5664 */
	{.type FromH0, .u {.p L55}},		/* dd L55 5672 */
	{.type FromH0, .u {.p C_2drop}},		/* dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- ) 5680 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 5688 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop	; ( n2 n1 -- ) (R -- ) 5696 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus	; ( -- n1-n2 ) 5704 */
	{.type FromH0, .u {.p C_signum}},		/* dd C_signum 5712 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 5720 */
	{.type Header, .u {.hdr { 5, "erase", /* C_erase = 5736 */ colon }}}, /* CENTRY "erase" erase 5 h 5744 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 5752 */
	{.type Absolute, .u {.p 0}},		/* dd 0 5760 */
	{.type FromH0, .u {.p M_doinit}},		/* dd M_doinit 5768 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 5776 */
	{.type Absolute, .u {.p 0}},		/* dd 0 5784 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 5792 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore 5800 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus 5808 */
	{.type FromH0, .u {.p M_doloop}},		/* dd M_doloop 5816 */
	{.type FromH0, .u {.p L58}},		/* dd L58 5824 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 5832 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 5840 */
	{.type Header, .u {.hdr { 4, "fill", /* C_fill = 5856 */ colon }}}, /* CENTRY "fill" fill 4 h 5864 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 5872 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 5880 */
	{.type Absolute, .u {.p 0}},		/* dd 0 5888 */
	{.type FromH0, .u {.p M_doinit}},		/* dd M_doinit 5896 */
	{.type FromH0, .u {.p C_2dup}},		/* dd C_2dup 5904 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 5912 */
	{.type FromH0, .u {.p M_i}},		/* dd M_i 5920 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 5928 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore 5936 */
	{.type FromH0, .u {.p M_doloop}},		/* dd M_doloop 5944 */
	{.type FromH0, .u {.p L60}},		/* dd L60 5952 */
	{.type FromH0, .u {.p C_2drop}},		/* dd C_2drop 5960 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 5968 */
	{.type Header, .u {.hdr { 5, "blank", /* C_blank = 5984 */ colon }}}, /* CENTRY "blank" blank 5 h 5992 */
	{.type FromH0, .u {.p C_bl}},		/* dd C_bl 6000 */
	{.type FromH0, .u {.p C_fill}},		/* dd C_fill 6008 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 6016 */
	{.type Header, .u {.hdr { 6, "search", /* C_search = 6032 */ colon }}}, /* CENTRY "search" search 6 h 6040 */
	{.type FromH0, .u {.p MV_Searchlen}},		/* dd MV_Searchlen 6048 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 6056 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 6064 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 6072 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 6080 */
	{.type FromH0, .u {.p MV_Searchlen}},		/* dd MV_Searchlen 6088 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 6096 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 6104 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus 6112 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 6120 */
	{.type Absolute, .u {.p 0}},		/* dd 0 6128 */
	{.type FromH0, .u {.p M_doinit}},		/* dd M_doinit 6136 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 6144 */
	{.type FromH0, .u {.p M_i}},		/* dd M_i 6152 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 6160 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 6168 */
	{.type FromH0, .u {.p MV_Searchlen}},		/* dd MV_Searchlen 6176 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 6184 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 6192 */
	{.type FromH0, .u {.p MV_Searchlen}},		/* dd MV_Searchlen 6200 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 6208 */
	{.type FromH0, .u {.p C_compare}},		/* dd C_compare 6216 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq 6224 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 6232 */
	{.type FromH0, .u {.p L65}},		/* dd L65 6240 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 6248 */
	{.type FromH0, .u {.p M_i}},		/* dd M_i 6256 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 6264 */
	{.type FromH0, .u {.p M_i}},		/* dd M_i 6272 */
	{.type FromH0, .u {.p M_unloop}},		/* dd M_unloop 6280 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 6288 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 6296 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 6304 */
	{.type FromH0, .u {.p C_true}},		/* dd C_true 6312 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 6320 */
	{.type FromH0, .u {.p M_doloop}},		/* dd M_doloop 6328 */
	{.type FromH0, .u {.p L64}},		/* dd L64 6336 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 6344 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 6352 */
	{.type FromH0, .u {.p C_false}},		/* dd C_false 6360 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 6368 */
	{.type Header, .u {.hdr { 4, "here", /* C_here = 6384 */ colon }}}, /* CENTRY "here" here 4 h 6392 */
	{.type FromH0, .u {.p M_h0}},		/* dd M_h0 6400 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 6408 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 6416 */
	{.type Header, .u {.hdr { 1, ",", /* C_comma = 6432 */ colon }}}, /* CENTRY "," comma 1 h 6440 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 6448 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 6456 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 6464 */
	{.type Absolute, .u {.p 8}},		/* dd 8 6472 */
	{.type FromH0, .u {.p M_h0}},		/* dd M_h0 6480 */
	{.type FromH0, .u {.p C_plusstore}},		/* dd C_plusstore 6488 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 6496 */
	{.type Header, .u {.hdr { 2, "c", /* C_c = 6512 */ colon }}}, /* CENTRY "c" c 2 h 6520 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 6528 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore 6536 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 6544 */
	{.type Absolute, .u {.p 1}},		/* dd 1 6552 */
	{.type FromH0, .u {.p M_h0}},		/* dd M_h0 6560 */
	{.type FromH0, .u {.p C_plusstore}},		/* dd C_plusstore 6568 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 6576 */
	{.type Header, .u {.hdr { 5, "allot", /* C_allot = 6592 */ colon }}}, /* CENTRY "allot" allot 5 h 6600 */
	{.type FromH0, .u {.p M_h0}},		/* dd M_h0 6608 */
	{.type FromH0, .u {.p C_plusstore}},		/* dd C_plusstore 6616 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 6624 */
	{.type Header, .u {.hdr { 3, "pad", /* C_pad = 6640 */ colon }}}, /* CENTRY "pad" pad 3 h 6648 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 6656 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 6664 */
	{.type Absolute, .u {.p 256}},		/* dd 256 6672 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 6680 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 6688 */
	{.type Header, .u {.hdr { 5, "align", /* C_align = 6704 */ colon }}}, /* CENTRY "align" align 5 h 6712 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 6720 */
	{.type FromH0, .u {.p C_aligned}},		/* dd C_aligned 6728 */
	{.type FromH0, .u {.p M_h0}},		/* dd M_h0 6736 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 6744 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 6752 */
	{.type Header, .u {.hdr { 6, "unused", /* C_unused = 6768 */ colon }}}, /* CENTRY "unused" unused 6 h 6776 */
	{.type FromH0, .u {.p M_h0}},		/* dd M_h0 6784 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 6792 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 6800 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 6808 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 6816 */
	{.type Header, .u {.hdr { 2, "<#", /* C_fromhash = 6832 */ colon }}}, /* CENTRY "<#" fromhash 2 h 6840 */
	{.type FromH0, .u {.p C_pad}},		/* dd C_pad 6848 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 6856 */
	{.type Absolute, .u {.p 1024}},		/* dd 1024 6864 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 6872 */
	{.type FromH0, .u {.p MV_toNum}},		/* dd MV_toNum 6880 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 6888 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 6896 */
	{.type Header, .u {.hdr { 1, "#", /* C_hash = 6912 */ colon }}}, /* CENTRY "#" hash 1 h 6920 */
	{.type FromH0, .u {.p MV_Base}},		/* dd MV_Base 6928 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 6936 */
	{.type FromH0, .u {.p M_uslashmod}},		/* dd M_uslashmod 6944 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 6952 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 6960 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 6968 */
	{.type Absolute, .u {.p 9}},		/* dd 9 6976 */
	{.type FromH0, .u {.p M_greater}},		/* dd M_greater 6984 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 6992 */
	{.type FromH0, .u {.p L92}},		/* dd L92 7000 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 7008 */
	{.type Absolute, .u {.p 97}},		/* dd 97 7016 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 7024 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 7032 */
	{.type Absolute, .u {.p 10}},		/* dd 10 7040 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 7048 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 7056 */
	{.type FromH0, .u {.p L93}},		/* dd L93 7064 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 7072 */
	{.type Absolute, .u {.p 48}},		/* dd 48 7080 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 7088 */
	{.type FromH0, .u {.p MV_toNum}},		/* dd MV_toNum 7096 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 7104 */
	{.type FromH0, .u {.p C_1minus}},		/* dd C_1minus 7112 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 7120 */
	{.type FromH0, .u {.p MV_toNum}},		/* dd MV_toNum 7128 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 7136 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore 7144 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 7152 */
	{.type Header, .u {.hdr { 2, "#s", /* C_hashs = 7168 */ colon }}}, /* CENTRY "#s" hashs 2 h 7176 */
	{.type FromH0, .u {.p C_hash}},		/* dd C_hash 7184 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 7192 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 7200 */
	{.type FromH0, .u {.p L96}},		/* dd L96 7208 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 7216 */
	{.type FromH0, .u {.p L95}},		/* dd L95 7224 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 7232 */
	{.type Header, .u {.hdr { 2, "#>", /* C_hashfrom = 7248 */ colon }}}, /* CENTRY "#>" hashfrom 2 h 7256 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 7264 */
	{.type FromH0, .u {.p MV_toNum}},		/* dd MV_toNum 7272 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 7280 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 7288 */
	{.type FromH0, .u {.p C_pad}},		/* dd C_pad 7296 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 7304 */
	{.type Absolute, .u {.p 1024}},		/* dd 1024 7312 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 7320 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 7328 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 7336 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 7344 */
	{.type Header, .u {.hdr { 4, "hold", /* C_hold = 7360 */ colon }}}, /* CENTRY "hold" hold 4 h 7368 */
	{.type FromH0, .u {.p MV_toNum}},		/* dd MV_toNum 7376 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 7384 */
	{.type FromH0, .u {.p C_1minus}},		/* dd C_1minus 7392 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 7400 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 7408 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore 7416 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 7424 */
	{.type FromH0, .u {.p MV_toNum}},		/* dd MV_toNum 7432 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 7440 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 7448 */
	{.type Header, .u {.hdr { 4, "sign", /* C_sign = 7464 */ colon }}}, /* CENTRY "sign" sign 4 h 7472 */
	{.type FromH0, .u {.p C_0lt}},		/* dd C_0lt 7480 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 7488 */
	{.type FromH0, .u {.p L100}},		/* dd L100 7496 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 7504 */
	{.type Absolute, .u {.p 45}},		/* dd 45 7512 */
	{.type FromH0, .u {.p C_hold}},		/* dd C_hold 7520 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 7528 */
	{.type Header, .u {.hdr { 1, ".", /* C_dot = 7544 */ colon }}}, /* CENTRY "." dot 1 h 7552 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 7560 */
	{.type FromH0, .u {.p C_abs}},		/* dd C_abs 7568 */
	{.type FromH0, .u {.p C_fromhash}},		/* dd C_fromhash 7576 */
	{.type FromH0, .u {.p C_hashs}},		/* dd C_hashs 7584 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 7592 */
	{.type FromH0, .u {.p C_sign}},		/* dd C_sign 7600 */
	{.type FromH0, .u {.p C_hashfrom}},		/* dd C_hashfrom 7608 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 7616 */
	{.type FromH0, .u {.p C_space}},		/* dd C_space 7624 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 7632 */
	{.type Header, .u {.hdr { 2, ".r", /* C_dotr = 7648 */ colon }}}, /* CENTRY ".r" dotr 2 h 7656 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 7664 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 7672 */
	{.type FromH0, .u {.p C_abs}},		/* dd C_abs 7680 */
	{.type FromH0, .u {.p C_fromhash}},		/* dd C_fromhash 7688 */
	{.type FromH0, .u {.p C_hashs}},		/* dd C_hashs 7696 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 7704 */
	{.type FromH0, .u {.p C_sign}},		/* dd C_sign 7712 */
	{.type FromH0, .u {.p C_hashfrom}},		/* dd C_hashfrom 7720 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 7728 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 7736 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 7744 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 7752 */
	{.type Absolute, .u {.p 0}},		/* dd 0 7760 */
	{.type FromH0, .u {.p C_max}},		/* dd C_max 7768 */
	{.type FromH0, .u {.p C_spaces}},		/* dd C_spaces 7776 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 7784 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 7792 */
	{.type Header, .u {.hdr { 3, "hex", /* C_hex = 7808 */ colon }}}, /* CENTRY "hex" hex 3 h 7816 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 7824 */
	{.type Absolute, .u {.p 16}},		/* dd 16 7832 */
	{.type FromH0, .u {.p MV_Base}},		/* dd MV_Base 7840 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 7848 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 7856 */
	{.type Header, .u {.hdr { 7, "decimal", /* C_decimal = 7872 */ colon }}}, /* CENTRY "decimal" decimal 7 h 7880 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 7888 */
	{.type Absolute, .u {.p 10}},		/* dd 10 7896 */
	{.type FromH0, .u {.p MV_Base}},		/* dd MV_Base 7904 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 7912 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 7920 */
	{.type Header, .u {.hdr { 5, "digit", /* C_digit = 7936 */ colon }}}, /* CENTRY "digit" digit 5 h 7944 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 7952 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 7960 */
	{.type Absolute, .u {.p 65}},		/* dd 65 7968 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 7976 */
	{.type Absolute, .u {.p 91}},		/* dd 91 7984 */
	{.type FromH0, .u {.p C_within}},		/* dd C_within 7992 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 8000 */
	{.type FromH0, .u {.p L106}},		/* dd L106 8008 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 8016 */
	{.type Absolute, .u {.p 55}},		/* dd 55 8024 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 8032 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 8040 */
	{.type FromH0, .u {.p L107}},		/* dd L107 8048 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 8056 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 8064 */
	{.type Absolute, .u {.p 97}},		/* dd 97 8072 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 8080 */
	{.type Absolute, .u {.p 123}},		/* dd 123 8088 */
	{.type FromH0, .u {.p C_within}},		/* dd C_within 8096 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 8104 */
	{.type FromH0, .u {.p L108}},		/* dd L108 8112 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 8120 */
	{.type Absolute, .u {.p 87}},		/* dd 87 8128 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 8136 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 8144 */
	{.type FromH0, .u {.p L109}},		/* dd L109 8152 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 8160 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 8168 */
	{.type Absolute, .u {.p 48}},		/* dd 48 8176 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 8184 */
	{.type Absolute, .u {.p 58}},		/* dd 58 8192 */
	{.type FromH0, .u {.p C_within}},		/* dd C_within 8200 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 8208 */
	{.type FromH0, .u {.p L110}},		/* dd L110 8216 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 8224 */
	{.type Absolute, .u {.p 48}},		/* dd 48 8232 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 8240 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 8248 */
	{.type FromH0, .u {.p L111}},		/* dd L111 8256 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 8264 */
	{.type FromH0, .u {.p C_false}},		/* dd C_false 8272 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 8280 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 8288 */
	{.type FromH0, .u {.p MV_Base}},		/* dd MV_Base 8296 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 8304 */
	{.type FromH0, .u {.p M_less}},		/* dd M_less 8312 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 8320 */
	{.type FromH0, .u {.p L112}},		/* dd L112 8328 */
	{.type FromH0, .u {.p C_true}},		/* dd C_true 8336 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 8344 */
	{.type FromH0, .u {.p L113}},		/* dd L113 8352 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 8360 */
	{.type FromH0, .u {.p C_false}},		/* dd C_false 8368 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 8376 */
	{.type Header, .u {.hdr { 6, "number", /* C_number = 8392 */ colon }}}, /* CENTRY "number" number 6 h 8400 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 8408 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 8416 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 8424 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 8432 */
	{.type Absolute, .u {.p 45}},		/* dd 45 8440 */
	{.type FromH0, .u {.p M_equal}},		/* dd M_equal 8448 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 8456 */
	{.type FromH0, .u {.p L115}},		/* dd L115 8464 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus 8472 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 8480 */
	{.type FromH0, .u {.p C_1minus}},		/* dd C_1minus 8488 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 8496 */
	{.type Absolute, .u {.p -1}},		/* dd -1 8504 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 8512 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 8520 */
	{.type FromH0, .u {.p L116}},		/* dd L116 8528 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 8536 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 8544 */
	{.type Absolute, .u {.p 1}},		/* dd 1 8552 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 8560 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 8568 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 8576 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 8584 */
	{.type Absolute, .u {.p 0}},		/* dd 0 8592 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 8600 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 8608 */
	{.type Absolute, .u {.p 0}},		/* dd 0 8616 */
	{.type FromH0, .u {.p M_doinit}},		/* dd M_doinit 8624 */
	{.type FromH0, .u {.p MV_Base}},		/* dd MV_Base 8632 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 8640 */
	{.type FromH0, .u {.p M_multiply}},		/* dd M_multiply 8648 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 8656 */
	{.type FromH0, .u {.p M_i}},		/* dd M_i 8664 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 8672 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 8680 */
	{.type FromH0, .u {.p C_digit}},		/* dd C_digit 8688 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 8696 */
	{.type FromH0, .u {.p L118}},		/* dd L118 8704 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 8712 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 8720 */
	{.type FromH0, .u {.p L119}},		/* dd L119 8728 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 8736 */
	{.type FromH0, .u {.p M_unloop}},		/* dd M_unloop 8744 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 8752 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 8760 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 8768 */
	{.type FromH0, .u {.p C_false}},		/* dd C_false 8776 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 8784 */
	{.type FromH0, .u {.p M_doloop}},		/* dd M_doloop 8792 */
	{.type FromH0, .u {.p L117}},		/* dd L117 8800 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 8808 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 8816 */
	{.type FromH0, .u {.p C_nip}},		/* dd C_nip 8824 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 8832 */
	{.type FromH0, .u {.p M_multiply}},		/* dd M_multiply 8840 */
	{.type FromH0, .u {.p C_true}},		/* dd C_true 8848 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 8856 */
	{.type Header, .u {.hdr { 5, "abort", /* C_abort = 8872 */ colon }}}, /* CENTRY "abort" abort 5 h 8880 */
	{.type FromH0, .u {.p MV_Abortvec}},		/* dd MV_Abortvec 8888 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 8896 */
	{.type FromH0, .u {.p M_execute}},		/* dd M_execute 8904 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 8912 */
	{.type Header, .u {.hdr { 6, "source", /* C_source = 8928 */ colon }}}, /* CENTRY "source" source 6 h 8936 */
	{.type FromH0, .u {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 8944 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 8952 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 8960 */
	{.type Header, .u {.hdr { 13, "current-input", /* C_current_input = 8984 */ colon }}}, /* CENTRY "current-input" current_input 13 ; ( -- c ) read the next character from the location in Sourcebuf h 8992 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 9000 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 9008 */
	{.type FromH0, .u {.p C_source}},		/* dd C_source 9016 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus		; Sourcebuf + >In 9024 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 9032 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 9040 */
	{.type Header, .u {.hdr { 10, "save-input", /* C_save_input = 9064 */ colon }}}, /* CENTRY "save-input" save_input 10 h 9072 */
	{.type FromH0, .u {.p MV_Infd}},		/* dd MV_Infd 9080 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 9088 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 9096 */
	{.type FromH0, .u {.p MV_toLimit}},		/* dd MV_toLimit 9104 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 9112 */
	{.type FromH0, .u {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9120 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 9128 */
	{.type FromH0, .u {.p MV_Blk}},		/* dd MV_Blk 9136 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 9144 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 9152 */
	{.type Absolute, .u {.p 5}},		/* dd 5 9160 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 9168 */
	{.type Header, .u {.hdr { 13, "default-input", /* C_default_input = 9192 */ colon }}}, /* CENTRY "default-input" default_input 13 h 9200 */
	{.type FromH0, .u {.p MC_STDIN}},		/* dd MC_STDIN 9208 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 9216 */
	{.type FromH0, .u {.p C_off}},		/* dd C_off 9224 */
	{.type FromH0, .u {.p MV_toLimit}},		/* dd MV_toLimit 9232 */
	{.type FromH0, .u {.p C_off}},		/* dd C_off 9240 */
	{.type FromH0, .u {.p MC_TIB}},		/* dd MC_TIB 9248 */
	{.type FromH0, .u {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9256 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 9264 */
	{.type FromH0, .u {.p MV_Blk}},		/* dd MV_Blk 9272 */
	{.type FromH0, .u {.p C_off}},		/* dd C_off 9280 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 9288 */
	{.type Header, .u {.hdr { 13, "restore-input", /* C_restore_input = 9312 */ colon }}}, /* CENTRY "restore-input" restore_input 13 h 9320 */
	{.type FromH0, .u {.p MV_Eof}},		/* dd MV_Eof 9328 */
	{.type FromH0, .u {.p C_off}},		/* dd C_off 9336 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 9344 */
	{.type Absolute, .u {.p 5}},		/* dd 5 9352 */
	{.type FromH0, .u {.p C_neq}},		/* dd C_neq 9360 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 9368 */
	{.type FromH0, .u {.p L133}},		/* dd L133 9376 */
	{.type FromH0, .u {.p C_default_input}},		/* dd C_default_input 9384 */
	{.type FromH0, .u {.p C_false}},		/* dd C_false 9392 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 9400 */
	{.type FromH0, .u {.p L134}},		/* dd L134 9408 */
	{.type FromH0, .u {.p MV_Blk}},		/* dd MV_Blk 9416 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 9424 */
	{.type FromH0, .u {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9432 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 9440 */
	{.type FromH0, .u {.p MV_toLimit}},		/* dd MV_toLimit 9448 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 9456 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 9464 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 9472 */
	{.type FromH0, .u {.p MV_Infd}},		/* dd MV_Infd 9480 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 9488 */
	{.type FromH0, .u {.p C_true}},		/* dd C_true 9496 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 9504 */
	{.type Header, .u {.hdr { 14, "?restore-input", /* C_qrestore_input = 9528 */ colon }}}, /* CENTRY "?restore-input" qrestore_input 14 h 9536 */
	{.type FromH0, .u {.p C_restore_input}},		/* dd C_restore_input 9544 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq 9552 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 9560 */
	{.type FromH0, .u {.p L136}},		/* dd L136 9568 */
	{.type FromH0, .u {.p C_space}},		/* dd C_space 9576 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 9584 */
	{.type FromH0, .u {.p L137}},		/* dd L137 9592 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 9600 */
	{.type Absolute, .u {.p 23}},		/* dd 23 9608 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 9616 */
	{.type FromH0, .u {.p C_cr}},		/* dd C_cr 9624 */
	{.type FromH0, .u {.p C_abort}},		/* dd C_abort 9632 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 9640 */
	{.type Header, .u {.hdr { 10, "next-input", /* C_next_input = 9664 */ colon }}}, /* CENTRY "next-input" next_input 10 ; when >In < >Limit ( -- true c ). ( -- 0 false ) otherwise h 9672 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 9680 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 9688 */
	{.type FromH0, .u {.p MV_toLimit}},		/* dd MV_toLimit 9696 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 9704 */
	{.type FromH0, .u {.p M_less}},		/* dd M_less 9712 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 9720 */
	{.type FromH0, .u {.p L139}},		/* dd L139	; >In >= >Limit 9728 */
	{.type FromH0, .u {.p C_true}},		/* dd C_true	; >In < >Limit 9736 */
	{.type FromH0, .u {.p C_current_input}},		/* dd C_current_input	; ( -- c ) 9744 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 9752 */
	{.type FromH0, .u {.p L140}},		/* dd L140 9760 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 9768 */
	{.type Absolute, .u {.p 0}},		/* dd 0 9776 */
	{.type FromH0, .u {.p C_false}},		/* dd C_false 9784 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 9792 */
	{.type Header, .u {.hdr { 5, "parse", /* C_parse = 9808 */ colon }}}, /* CENTRY "parse" parse 5 ; ( c -- a ) Place the counted string in the address in Wordbuf and return that address. c = word delimiter. h 9816 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush		; ( c -- ) (R -- c ) 9824 */
	{.type FromH0, .u {.p MV_Wordbuf}},		/* dd MV_Wordbuf 9832 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch		; ( -- Wordb ) 9840 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus		; ( Wordb -- Wordb+1 ) 9848 */
	{.type FromH0, .u {.p C_next_input}},		/* dd C_next_input ; ( Wordb+1 -- Wordb+1 f c ) 9856 */
	{.type FromH0, .u {.p M_rfetch}},		/* dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c ) 9864 */
	{.type FromH0, .u {.p C_neq}},		/* dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) ) 9872 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand 9880 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 9888 */
	{.type FromH0, .u {.p L143}},		/* dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew 9896 */
	{.type FromH0, .u {.p C_current_input}},		/* dd C_current_input	; ( Wordb+1 -- Wordb+1 c ) 9904 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 9912 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1 9920 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus		; ( Wordb+1 -- Wordb+2 ) 9928 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 9936 */
	{.type Absolute, .u {.p 1}},		/* dd 1 9944 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 9952 */
	{.type FromH0, .u {.p C_plusstore}},		/* dd C_plusstore	; >In++ 9960 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 9968 */
	{.type FromH0, .u {.p L142}},		/* dd L142		; ( Wordb+2 ) repeat 9976 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 9984 */
	{.type Absolute, .u {.p 1}},		/* dd 1 9992 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 10000 */
	{.type FromH0, .u {.p C_plusstore}},		/* dd C_plusstore	; >In++ 10008 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- ) 10016 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop		; (Wordb+1 c -- Wordb+1) 10024 */
	{.type FromH0, .u {.p MV_Wordbuf}},		/* dd MV_Wordbuf 10032 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb) 10040 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb) 10048 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb) 10056 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb) 10064 */
	{.type FromH0, .u {.p C_1minus}},		/* dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb) 10072 */
	{.type FromH0, .u {.p M_rfetch}},		/* dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb) 10080 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now. 10088 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop		; ( -- Wordb) (R Wordb -- ) 10096 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 10104 */
	{.type Header, .u {.hdr { 4, "word", /* C_word = 10120 */ colon }}}, /* CENTRY "word" word 4 ; ( c -- a ) skip the c"s. Placed the counted string in a (as in Wordbuf) h 10128 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush	; ( -- ) (R -- c ) 10136 */
	{.type FromH0, .u {.p C_next_input}},		/* dd C_next_input ; ( -- f c2 ) (R c1 -- ) 10144 */
	{.type FromH0, .u {.p M_rfetch}},		/* dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial ) 10152 */
	{.type FromH0, .u {.p M_equal}},		/* dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial ) 10160 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial ) 10168 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 10176 */
	{.type FromH0, .u {.p L146}},		/* dd L146		; >In >= >Limit || cinitial != cnew 10184 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal	; >In < >Limit && cinitial == cnew 10192 */
	{.type Absolute, .u {.p 1}},		/* dd 1 10200 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 10208 */
	{.type FromH0, .u {.p C_plusstore}},		/* dd C_plusstore	; >In++ 10216 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump		; repeat 10224 */
	{.type FromH0, .u {.p L145}},		/* dd L145 10232 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character 10240 */
	{.type FromH0, .u {.p C_parse}},		/* dd C_parse 10248 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 10256 */
	{.type Header, .u {.hdr { 6, "accept", /* C_accept = 10272 */ colon }}}, /* CENTRY "accept" accept 6 ; ( a n -- n ) get line or n chars or EOF from input and store at a h 10280 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap	; ( n a -- ) 10288 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup	; ( n a a -- ) 10296 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 10304 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush	; ( n -- ) (R a a -- ) 10312 */
	{.type FromH0, .u {.p C_qdup}},		/* dd C_qdup	; ( n n -- ) (R a a -- ) 10320 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump	; (if) 10328 */
	{.type FromH0, .u {.p L149}},		/* dd L149	; n == 0 10336 */
	{.type FromH0, .u {.p C_key}},		/* dd C_key	; n > 0 ( n -- n c ) 10344 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup	; ( -- n c c ) 10352 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 10360 */
	{.type Absolute, .u {.p 10}},		/* dd 10		; ( -- n c c 10 ) 10368 */
	{.type FromH0, .u {.p M_equal}},		/* dd M_equal	; ( n c c 10 -- n c f ) checking for newline 10376 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over	; ( -- n c f c ) 10384 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 10392 */
	{.type Absolute, .u {.p -1}},		/* dd -1		; ( -- n c f c -1 ) 10400 */
	{.type FromH0, .u {.p M_equal}},		/* dd M_equal	; ( -- n c f1 f2 ) 10408 */
	{.type FromH0, .u {.p M_binor}},		/* dd M_binor	; ( -- n c f ) 10416 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 10424 */
	{.type FromH0, .u {.p L150}},		/* dd L150 10432 */
	{.type FromH0, .u {.p C_2drop}},		/* dd C_2drop	; n == -1 || n == 10 (	-- ) 10440 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 10448 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 10456 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus	; ( -- a2-a1 ) 10464 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon	; ( -- n ) (R -- ) 10472 */
	{.type FromH0, .u {.p M_rfetch}},		/* dd M_rfetch	; ( n c a -- ) (R a a -- ) 10480 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore	; store the character at a 10488 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop	; ( n a -- ) (R a -- ) 10496 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus 10504 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address 10512 */
	{.type FromH0, .u {.p C_1minus}},		/* dd C_1minus	; ( n -- n-1 ) 10520 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 10528 */
	{.type FromH0, .u {.p L148}},		/* dd L148	; loop again for the next character 10536 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 ) 10544 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop	; ( a2 a1 -- ) (R a1 -- ) 10552 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus	; ( a2 a1 -- a2-a1 ) 10560 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 10568 */
	{.type Header, .u {.hdr { 5, "query", /* C_query = 10584 */ colon }}}, /* CENTRY "query" query 5 ; read from input stream into the Text Input Buffer h 10592 */
	{.type FromH0, .u {.p MV_Eof}},		/* dd MV_Eof 10600 */
	{.type FromH0, .u {.p C_off}},		/* dd C_off		; clear EOF flag 10608 */
	{.type FromH0, .u {.p MC_TIB}},		/* dd MC_TIB	; constant puts address of tibuffer on the top 10616 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 10624 */
	{.type Absolute, .u {.p 4096}},		/* dd 4096	; ( tibuffer -- tibuffer 4096 ) 10632 */
	{.type FromH0, .u {.p C_accept}},		/* dd C_accept ; ( tibuffer 4096 -- n ) 10640 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup	; ( n -- n n ) 10648 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq	; ( n n -- n f ) 10656 */
	{.type FromH0, .u {.p MV_Eof}},		/* dd MV_Eof 10664 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 10672 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand	; n == 0 && EOF 10680 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 10688 */
	{.type FromH0, .u {.p L152}},		/* dd L152		; false condition 10696 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop		; n == 0 && EOF ( n -- ) 10704 */
	{.type FromH0, .u {.p C_qrestore_input}},		/* dd C_qrestore_input 10712 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 10720 */
	{.type FromH0, .u {.p L153}},		/* dd L153 10728 */
	{.type FromH0, .u {.p MV_toLimit}},		/* dd MV_toLimit 10736 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store		; number of characters to read >Limit = n 10744 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 10752 */
	{.type FromH0, .u {.p C_off}},		/* dd C_off		; start from 0 >In = 0 10760 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 10768 */
	{.type Header, .u {.hdr { 6, "refill", /* C_refill = 10784 */ colon }}}, /* CENTRY "refill" refill 6 h 10792 */
	{.type FromH0, .u {.p MV_Blk}},		/* dd MV_Blk 10800 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 10808 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 10816 */
	{.type FromH0, .u {.p L155}},		/* dd L155 10824 */
	{.type FromH0, .u {.p C_false}},		/* dd C_false 10832 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 10840 */
	{.type FromH0, .u {.p L156}},		/* dd L156 10848 */
	{.type FromH0, .u {.p C_query}},		/* dd C_query 10856 */
	{.type FromH0, .u {.p C_true}},		/* dd C_true 10864 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 10872 */
	{.type Header, .u {.hdr { 8, "findname", /* C_findname = 10888 */ colon }}}, /* CENTRY "findname" findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names h 10896 */
	{.type FromH0, .u {.p MV_Findadr}},		/* dd MV_Findadr 10904 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 10912 */
	{.type FromH0, .u {.p MV_Dp}},		/* dd MV_Dp 10920 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch	; get dictionary link 10928 */
	{.type FromH0, .u {.p C_qdup}},		/* dd C_qdup 10936 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 10944 */
	{.type FromH0, .u {.p L159}},		/* dd L159	; seached until the first dictionary entry get out 10952 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup	; ( a -- a a ) 10960 */
	{.type FromH0, .u {.p C_cellplus}},		/* dd C_cellplus	; lenth + initial name address 10968 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch	; length + initial name 10976 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 10984 */
	{.type Absolute, .u {.p 64}},		/* dd 64		; max name length? 10992 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand	; keep only the length 11000 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 11008 */
	{.type FromH0, .u {.p L160}},		/* dd L160 11016 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 11024 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 11032 */
	{.type FromH0, .u {.p L161}},		/* dd L161 11040 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 11048 */
	{.type FromH0, .u {.p C_cellplus}},		/* dd C_cellplus 11056 */
	{.type FromH0, .u {.p C_count}},		/* dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n ) 11064 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 11072 */
	{.type Absolute, .u {.p 63}},		/* dd 63 11080 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63 ) 11088 */
	{.type FromH0, .u {.p MV_Findadr}},		/* dd MV_Findadr 11096 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 11104 */
	{.type FromH0, .u {.p C_count}},		/* dd C_count	; ( a1 a1+8+1 n&63 a2 n2 -- a1 a1+8+1 n&63 a2+1 n2 ) 11112 */
	{.type FromH0, .u {.p C_compare}},		/* dd C_compare	; ( -- a1 n ) compare dictionary entry with name 11120 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq	; found a match? 11128 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 11136 */
	{.type FromH0, .u {.p L162}},		/* dd L162 11144 */
	{.type FromH0, .u {.p C_cellplus}},		/* dd C_cellplus 11152 */
	{.type FromH0, .u {.p C_true}},		/* dd C_true 11160 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 11168 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 11176 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 11184 */
	{.type FromH0, .u {.p L158}},		/* dd L158 11192 */
	{.type FromH0, .u {.p MV_Findadr}},		/* dd MV_Findadr 11200 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 11208 */
	{.type FromH0, .u {.p C_false}},		/* dd C_false 11216 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 11224 */
	{.type Header, .u {.hdr { 4, "find", /* C_find = 11240 */ colon }}}, /* CENTRY "find" find 4 ; ( a1 -- a2 f )? h 11248 */
	{.type FromH0, .u {.p C_findname}},		/* dd C_findname 11256 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 11264 */
	{.type FromH0, .u {.p L164}},		/* dd L164 11272 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 11280 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 11288 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 11296 */
	{.type FromH0, .u {.p M_over}},		/* dd M_over 11304 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 11312 */
	{.type Absolute, .u {.p 63}},		/* dd 63 11320 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand 11328 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 11336 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus 11344 */
	{.type FromH0, .u {.p C_aligned}},		/* dd C_aligned 11352 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 11360 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 11368 */
	{.type Absolute, .u {.p 128}},		/* dd 128 11376 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand 11384 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 11392 */
	{.type FromH0, .u {.p L165}},		/* dd L165 11400 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 11408 */
	{.type Absolute, .u {.p 1}},		/* dd 1 11416 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 11424 */
	{.type FromH0, .u {.p L166}},		/* dd L166 11432 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 11440 */
	{.type Absolute, .u {.p -1}},		/* dd -1 11448 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 11456 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 11464 */
	{.type FromH0, .u {.p L167}},		/* dd L167 11472 */
	{.type FromH0, .u {.p C_false}},		/* dd C_false 11480 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 11488 */
	{.type Header, .u {.hdr { 1, "'", /* C_single_quote = 11504 */ colon }}}, /* CENTRY "'" single_quote 1 h 11512 */
	{.type FromH0, .u {.p C_bl}},		/* dd C_bl 11520 */
	{.type FromH0, .u {.p C_word}},		/* dd C_word 11528 */
	{.type FromH0, .u {.p C_find}},		/* dd C_find 11536 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq 11544 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 11552 */
	{.type FromH0, .u {.p L169}},		/* dd L169 11560 */
	{.type FromH0, .u {.p C_space}},		/* dd C_space 11568 */
	{.type FromH0, .u {.p C_count}},		/* dd C_count 11576 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 11584 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 11592 */
	{.type FromH0, .u {.p L170}},		/* dd L170 11600 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 11608 */
	{.type Absolute, .u {.p 3}},		/* dd 3 11616 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 11624 */
	{.type FromH0, .u {.p C_cr}},		/* dd C_cr 11632 */
	{.type FromH0, .u {.p C_abort}},		/* dd C_abort 11640 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 11648 */
	{.type Header, .u {.hdr { 6, "?stack", /* C_qstack = 11664 */ colon }}}, /* CENTRY "?stack" qstack 6 h 11672 */
	{.type FromH0, .u {.p M_stackptr}},		/* dd M_stackptr 11680 */
	{.type FromH0, .u {.p M_s0}},		/* dd M_s0 11688 */
	{.type FromH0, .u {.p M_greater}},		/* dd M_greater 11696 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 11704 */
	{.type FromH0, .u {.p L172}},		/* dd L172 11712 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 11720 */
	{.type FromH0, .u {.p L173}},		/* dd L173 11728 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 11736 */
	{.type Absolute, .u {.p 16}},		/* dd 16 11744 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 11752 */
	{.type FromH0, .u {.p C_cr}},		/* dd C_cr 11760 */
	{.type FromH0, .u {.p C_abort}},		/* dd C_abort 11768 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 11776 */
	{.type Header, .u {.hdr { 9, "interpret", /* C_interpret = 11800 */ colon }}}, /* CENTRY "interpret" interpret 9 ; there is stuff in TIB to be interpreted >In and >Limit are set h 11808 */
	{.type FromH0, .u {.p C_bl}},		/* dd C_bl 11816 */
	{.type FromH0, .u {.p C_word}},		/* dd C_word	; ( bl -- a ) 11824 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 11832 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 11840 */
	{.type FromH0, .u {.p C_0neq}},		/* dd C_0neq 11848 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 11856 */
	{.type FromH0, .u {.p L176}},		/* dd L176	; count at a = 0 11864 */
	{.type FromH0, .u {.p C_find}},		/* dd C_find	; ( a -- ) a = address of counted string 11872 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 11880 */
	{.type FromH0, .u {.p L177}},		/* dd L177 11888 */
	{.type FromH0, .u {.p M_execute}},		/* dd M_execute 11896 */
	{.type FromH0, .u {.p C_qstack}},		/* dd C_qstack 11904 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 11912 */
	{.type FromH0, .u {.p L178}},		/* dd L178 11920 */
	{.type FromH0, .u {.p C_count}},		/* dd C_count 11928 */
	{.type FromH0, .u {.p C_number}},		/* dd C_number 11936 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq 11944 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 11952 */
	{.type FromH0, .u {.p L179}},		/* dd L179 11960 */
	{.type FromH0, .u {.p C_space}},		/* dd C_space 11968 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 11976 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 11984 */
	{.type FromH0, .u {.p L180}},		/* dd L180	; error I? 11992 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 12000 */
	{.type Absolute, .u {.p 3}},		/* dd 3 12008 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 12016 */
	{.type FromH0, .u {.p C_cr}},		/* dd C_cr 12024 */
	{.type FromH0, .u {.p C_abort}},		/* dd C_abort 12032 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 12040 */
	{.type FromH0, .u {.p L175}},		/* dd L175 12048 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop	; count at a = 0 ( a -- ) 12056 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 12064 */
	{.type Header, .u {.hdr { 6, "create", /* C_create = 12080 */ colon }}}, /* CENTRY "create" create 6 h 12088 */
	{.type FromH0, .u {.p C_align}},		/* dd C_align 12096 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 12104 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 12112 */
	{.type FromH0, .u {.p MV_Dp}},		/* dd MV_Dp 12120 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 12128 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 12136 */
	{.type FromH0, .u {.p C_bl}},		/* dd C_bl 12144 */
	{.type FromH0, .u {.p C_word}},		/* dd C_word 12152 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 12160 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 12168 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 12176 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 12184 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus 12192 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 12200 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 12208 */
	{.type FromH0, .u {.p M_cmove}},		/* dd M_cmove 12216 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 12224 */
	{.type FromH0, .u {.p C_allot}},		/* dd C_allot 12232 */
	{.type FromH0, .u {.p C_align}},		/* dd C_align 12240 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 12248 */
	{.type FromH0, .u {.p M_variable}},		/* dd M_variable 12256 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 12264 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 12272 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 12280 */
	{.type FromH0, .u {.p MV_Dp}},		/* dd MV_Dp 12288 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 12296 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 12304 */
	{.type Header, .u {.hdr { 8, "variable", /* C_variable = 12320 */ colon }}}, /* CENTRY "variable" variable 8 h 12328 */
	{.type FromH0, .u {.p C_create}},		/* dd C_create 12336 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 12344 */
	{.type Absolute, .u {.p 0}},		/* dd 0 12352 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 12360 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 12368 */
	{.type Header, .u {.hdr { 8, "constant", /* C_constant = 12384 */ colon }}}, /* CENTRY "constant" constant 8 h 12392 */
	{.type FromH0, .u {.p C_create}},		/* dd C_create 12400 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 12408 */
	{.type FromH0, .u {.p M_constant}},		/* dd M_constant 12416 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 12424 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 12432 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 12440 */
	{.type Absolute, .u {.p 1}},		/* dd 1 12448 */
	{.type FromH0, .u {.p C_cells}},		/* dd C_cells 12456 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 12464 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 12472 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 12480 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 12488 */
	{.type Header, .u {.hdr { 9, "immediate", /* C_immediate = 12512 */ colon }}}, /* CENTRY "immediate" immediate 9 h 12520 */
	{.type FromH0, .u {.p MV_Dp}},		/* dd MV_Dp 12528 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 12536 */
	{.type FromH0, .u {.p C_cellplus}},		/* dd C_cellplus 12544 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 12552 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 12560 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 12568 */
	{.type Absolute, .u {.p 128}},		/* dd 128 12576 */
	{.type FromH0, .u {.p M_binor}},		/* dd M_binor 12584 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 12592 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore 12600 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 12608 */
	{.type Header, .u {.hdr { 4, ">cfa", /* C_tocfa = 12624 */ colon }}}, /* CENTRY ">cfa" tocfa 4 h 12632 */
	{.type FromH0, .u {.p C_count}},		/* dd C_count 12640 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 12648 */
	{.type Absolute, .u {.p 63}},		/* dd 63 12656 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand 12664 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 12672 */
	{.type FromH0, .u {.p C_aligned}},		/* dd C_aligned 12680 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 12688 */
	{.type Header, .u {.hdr { 7, "compile", /* C_compile = 12704 */ colon }}}, /* CENTRY "compile" compile 7 h 12712 */
	{.type FromH0, .u {.p C_findname}},		/* dd C_findname 12720 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 12728 */
	{.type FromH0, .u {.p L188}},		/* dd L188 12736 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 12744 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 12752 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 12760 */
	{.type Absolute, .u {.p 128}},		/* dd 128 12768 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand 12776 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 12784 */
	{.type FromH0, .u {.p L189}},		/* dd L189 12792 */
	{.type FromH0, .u {.p C_tocfa}},		/* dd C_tocfa	; immediate 12800 */
	{.type FromH0, .u {.p M_execute}},		/* dd M_execute 12808 */
	{.type FromH0, .u {.p C_qstack}},		/* dd C_qstack 12816 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 12824 */
	{.type FromH0, .u {.p L190}},		/* dd L190 12832 */
	{.type FromH0, .u {.p C_tocfa}},		/* dd C_tocfa 12840 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 12848 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 12856 */
	{.type FromH0, .u {.p L191}},		/* dd L191 12864 */
	{.type FromH0, .u {.p C_count}},		/* dd C_count 12872 */
	{.type FromH0, .u {.p C_number}},		/* dd C_number 12880 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq 12888 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 12896 */
	{.type FromH0, .u {.p L192}},		/* dd L192 12904 */
	{.type FromH0, .u {.p C_space}},		/* dd C_space 12912 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 12920 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 12928 */
	{.type FromH0, .u {.p L193}},		/* dd L193 12936 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 12944 */
	{.type Absolute, .u {.p 3}},		/* dd 3 12952 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 12960 */
	{.type FromH0, .u {.p C_cr}},		/* dd C_cr 12968 */
	{.type FromH0, .u {.p C_abort}},		/* dd C_abort 12976 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 12984 */
	{.type FromH0, .u {.p L194}},		/* dd L194 12992 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 13000 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 13008 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 13016 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 13024 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 13032 */
	{.type Header, .u {.hdr { 1, "]", /* C_close_bracket = 13048 */ colon }}}, /* CENTRY "]" close_bracket 1 h 13056 */
	{.type FromH0, .u {.p MV_State}},		/* dd MV_State 13064 */
	{.type FromH0, .u {.p C_on}},		/* dd C_on 13072 */
	{.type FromH0, .u {.p C_bl}},		/* dd C_bl 13080 */
	{.type FromH0, .u {.p C_word}},		/* dd C_word 13088 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 13096 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 13104 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq 13112 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 13120 */
	{.type FromH0, .u {.p L197}},		/* dd L197 13128 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 13136 */
	{.type FromH0, .u {.p C_refill}},		/* dd C_refill 13144 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 13152 */
	{.type FromH0, .u {.p L198}},		/* dd L198 13160 */
	{.type FromH0, .u {.p C_compile}},		/* dd C_compile 13168 */
	{.type FromH0, .u {.p MV_State}},		/* dd MV_State 13176 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 13184 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 13192 */
	{.type FromH0, .u {.p L199}},		/* dd L199 13200 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 13208 */
	{.type FromH0, .u {.p L196}},		/* dd L196 13216 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 13224 */
	{.type FromH0, .u {.p MV_State}},		/* dd MV_State 13232 */
	{.type FromH0, .u {.p C_off}},		/* dd C_off 13240 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 13248 */
	{.type Header, .u {.hdr { 6, "smudge", /* C_smudge = 13264 */ colon }}}, /* CENTRY "smudge" smudge 6 h 13272 */
	{.type FromH0, .u {.p MV_Dp}},		/* dd MV_Dp 13280 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 13288 */
	{.type FromH0, .u {.p C_cellplus}},		/* dd C_cellplus 13296 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 13304 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 13312 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 13320 */
	{.type Absolute, .u {.p 64}},		/* dd 64 13328 */
	{.type FromH0, .u {.p M_binor}},		/* dd M_binor 13336 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 13344 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore 13352 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 13360 */
	{.type Header, .u {.hdr { 6, "reveal", /* C_reveal = 13376 */ colon }}}, /* CENTRY "reveal" reveal 6 h 13384 */
	{.type FromH0, .u {.p MV_Dp}},		/* dd MV_Dp 13392 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 13400 */
	{.type FromH0, .u {.p C_cellplus}},		/* dd C_cellplus 13408 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 13416 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 13424 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 13432 */
	{.type Absolute, .u {.p 64}},		/* dd 64 13440 */
	{.type FromH0, .u {.p C_invert}},		/* dd C_invert 13448 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand 13456 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 13464 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore 13472 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 13480 */
	{.type Header, .u {.hdr { 1, ":", /* C_colon = 13496 */ colon }}}, /* CENTRY ":" colon 1 h 13504 */
	{.type FromH0, .u {.p C_create}},		/* dd C_create 13512 */
	{.type FromH0, .u {.p C_smudge}},		/* dd C_smudge 13520 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 13528 */
	{.type FromH0, .u {.p M_colon}},		/* dd M_colon 13536 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 13544 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 13552 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 13560 */
	{.type Absolute, .u {.p 1}},		/* dd 1 13568 */
	{.type FromH0, .u {.p C_cells}},		/* dd C_cells 13576 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus 13584 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 13592 */
	{.type FromH0, .u {.p C_close_bracket}},		/* dd C_close_bracket 13600 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 13608 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 13616 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 13624 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 13632 */
	{.type FromH0, .u {.p MV_State}},		/* dd MV_State 13640 */
	{.type FromH0, .u {.p C_off}},		/* dd C_off 13648 */
	{.type FromH0, .u {.p C_reveal}},		/* dd C_reveal 13656 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 13664 */
	{.type FromH0, .u {.p MV_Dp}},		/* dd MV_Dp 13672 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 13680 */
	{.type FromH0, .u {.p C_cellplus}},		/* dd C_cellplus 13688 */
	{.type FromH0, .u {.p C_tocfa}},		/* dd C_tocfa 13696 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 13704 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 13712 */
	{.type Header, .u {.hdr { 4, "char", /* C_L206 = 13728 */ colon }}}, /* CENTRY "char" L206 4 h 13736 */
	{.type FromH0, .u {.p C_bl}},		/* dd C_bl 13744 */
	{.type FromH0, .u {.p C_word}},		/* dd C_word 13752 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus 13760 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 13768 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 13776 */
	{.type Header, .u {.hdr { 7, "literal", /* C_literal = 13792 */ colon }}}, /* CENTRY "literal" literal 7 h 13800 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 13808 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 13816 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 13824 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 13832 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 13840 */
	{.type Header, .u {.hdr { 8, "sliteral", /* C_sliteral = 13856 */ colon }}}, /* CENTRY "sliteral" sliteral 8 h 13864 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 13872 */
	{.type FromH0, .u {.p M_sliteral}},		/* dd M_sliteral 13880 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 13888 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 13896 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 13904 */
	{.type Absolute, .u {.p 34}},		/* dd 34 13912 */
	{.type FromH0, .u {.p C_parse}},		/* dd C_parse 13920 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 13928 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 13936 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus 13944 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 13952 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 13960 */
	{.type FromH0, .u {.p M_rfetch}},		/* dd M_rfetch 13968 */
	{.type FromH0, .u {.p M_cmove}},		/* dd M_cmove 13976 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 13984 */
	{.type FromH0, .u {.p C_allot}},		/* dd C_allot 13992 */
	{.type FromH0, .u {.p C_align}},		/* dd C_align 14000 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14008 */
	{.type Header, .u {.hdr { 6, "string", /* C_string = 14024 */ colon }}}, /* CENTRY "string" string 6 h 14032 */
	{.type FromH0, .u {.p C_word}},		/* dd C_word 14040 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 14048 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 14056 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus 14064 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 14072 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 14080 */
	{.type FromH0, .u {.p M_rfetch}},		/* dd M_rfetch 14088 */
	{.type FromH0, .u {.p M_cmove}},		/* dd M_cmove 14096 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 14104 */
	{.type FromH0, .u {.p C_allot}},		/* dd C_allot 14112 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14120 */
	{.type FromH0, .u {.p C_bl}},		/* dd C_bl 14128 */
	{.type FromH0, .u {.p C_word}},		/* dd C_word 14136 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus 14144 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 14152 */
	{.type FromH0, .u {.p C_literal}},		/* dd C_literal 14160 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14168 */
	{.type FromH0, .u {.p C_single_quote}},		/* dd C_single_quote 14176 */
	{.type FromH0, .u {.p C_literal}},		/* dd C_literal 14184 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14192 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 14200 */
	{.type Absolute, .u {.p 41}},		/* dd 41 14208 */
	{.type FromH0, .u {.p C_parse}},		/* dd C_parse 14216 */
	{.type FromH0, .u {.p M_drop}},		/* dd M_drop 14224 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14232 */
	{.type FromH0, .u {.p MV_Blk}},		/* dd MV_Blk 14240 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 14248 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 14256 */
	{.type FromH0, .u {.p L214}},		/* dd L214 14264 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 14272 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 14280 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 14288 */
	{.type Absolute, .u {.p 63}},		/* dd 63 14296 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 14304 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 14312 */
	{.type Absolute, .u {.p 63}},		/* dd 63 14320 */
	{.type FromH0, .u {.p C_invert}},		/* dd C_invert 14328 */
	{.type FromH0, .u {.p M_binand}},		/* dd M_binand 14336 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 14344 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 14352 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 14360 */
	{.type FromH0, .u {.p L215}},		/* dd L215 14368 */
	{.type FromH0, .u {.p MV_toLimit}},		/* dd MV_toLimit 14376 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 14384 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 14392 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 14400 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14408 */
	{.type Header, .u {.hdr { 8, "(?abort)", /* C_qabort_parens = 14424 */ colon }}}, /* CENTRY "(?abort)" qabort_parens 8 h 14432 */
	{.type FromH0, .u {.p MV_State}},		/* dd MV_State 14440 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 14448 */
	{.type FromH0, .u {.p L217}},		/* dd L217 14456 */
	{.type FromH0, .u {.p C_space}},		/* dd C_space 14464 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 14472 */
	{.type FromH0, .u {.p C_cr}},		/* dd C_cr 14480 */
	{.type FromH0, .u {.p C_abort}},		/* dd C_abort 14488 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 14496 */
	{.type FromH0, .u {.p L218}},		/* dd L218 14504 */
	{.type FromH0, .u {.p C_2drop}},		/* dd C_2drop 14512 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14520 */
	{.type FromH0, .u {.p C_sliteral}},		/* dd C_sliteral 14528 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 14536 */
	{.type FromH0, .u {.p C_qabort_parens}},		/* dd C_qabort_parens 14544 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 14552 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14560 */
	{.type Header, .u {.hdr { 1, "\"", /* C_double_quote = 14576 */ colon }}}, /* CENTRY "\"" double_quote 1 h 14584 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 14592 */
	{.type Absolute, .u {.p 34}},		/* dd 34 14600 */
	{.type FromH0, .u {.p C_word}},		/* dd C_word 14608 */
	{.type FromH0, .u {.p C_count}},		/* dd C_count 14616 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 14624 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 14632 */
	{.type FromH0, .u {.p M_rfetch}},		/* dd M_rfetch 14640 */
	{.type FromH0, .u {.p M_cmove}},		/* dd M_cmove 14648 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 14656 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 14664 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 14672 */
	{.type FromH0, .u {.p C_allot}},		/* dd C_allot 14680 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14688 */
	{.type Header, .u {.hdr { 2, "c\"", /* C_cdouble_quote = 14704 */ colon }}}, /* CENTRY "c\"" cdouble_quote 2 h 14712 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 14720 */
	{.type Absolute, .u {.p 34}},		/* dd 34 14728 */
	{.type FromH0, .u {.p C_word}},		/* dd C_word 14736 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 14744 */
	{.type FromH0, .u {.p M_cfetch}},		/* dd M_cfetch 14752 */
	{.type FromH0, .u {.p C_1plus}},		/* dd C_1plus 14760 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 14768 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 14776 */
	{.type FromH0, .u {.p M_rfetch}},		/* dd M_rfetch 14784 */
	{.type FromH0, .u {.p M_cmove}},		/* dd M_cmove 14792 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 14800 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 14808 */
	{.type FromH0, .u {.p C_allot}},		/* dd C_allot 14816 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14824 */
	{.type FromH0, .u {.p C_sliteral}},		/* dd C_sliteral 14832 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14840 */
	{.type FromH0, .u {.p C_sliteral}},		/* dd C_sliteral 14848 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 14856 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 14864 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 14872 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14880 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 14888 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 14896 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 14904 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 14912 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 14920 */
	{.type Absolute, .u {.p 0}},		/* dd 0 14928 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 14936 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 14944 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 14952 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 14960 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 14968 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 14976 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 14984 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 14992 */
	{.type Absolute, .u {.p 0}},		/* dd 0 15000 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15008 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 15016 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 15024 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 15032 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 15040 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15048 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 15056 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 15064 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 15072 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15080 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 15088 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15096 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15104 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 15112 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15120 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15128 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15136 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15144 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 15152 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15160 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15168 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15176 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15184 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 15192 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15200 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 15208 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15216 */
	{.type Absolute, .u {.p 0}},		/* dd 0 15224 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15232 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15240 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15248 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 15256 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15264 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 15272 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15280 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 15288 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 15296 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 15304 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15312 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15320 */
	{.type FromH0, .u {.p M_doinit}},		/* dd M_doinit 15328 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15336 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15344 */
	{.type Absolute, .u {.p 0}},		/* dd 0 15352 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 15360 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15368 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15376 */
	{.type FromH0, .u {.p M_doloop}},		/* dd M_doloop 15384 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15392 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15400 */
	{.type FromH0, .u {.p C_qdup}},		/* dd C_qdup 15408 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 15416 */
	{.type FromH0, .u {.p L234}},		/* dd L234 15424 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 15432 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 15440 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 15448 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15456 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15464 */
	{.type FromH0, .u {.p M_doploop}},		/* dd M_doploop 15472 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15480 */
	{.type FromH0, .u {.p C_comma}},		/* dd C_comma 15488 */
	{.type FromH0, .u {.p C_qdup}},		/* dd C_qdup 15496 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 15504 */
	{.type FromH0, .u {.p L236}},		/* dd L236 15512 */
	{.type FromH0, .u {.p C_here}},		/* dd C_here 15520 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 15528 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 15536 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15544 */
	{.type Header, .u {.hdr { 3, "w/o", /* C_wo = 15560 */ colon }}}, /* CENTRY "w/o" wo 3 h 15568 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15576 */
	{.type Absolute, .u {.p 1}},		/* dd 1 15584 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15592 */
	{.type Absolute, .u {.p 512}},		/* dd 512 15600 */
	{.type FromH0, .u {.p M_binor}},		/* dd M_binor 15608 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15616 */
	{.type Absolute, .u {.p 64}},		/* dd 64 15624 */
	{.type FromH0, .u {.p M_binor}},		/* dd M_binor 15632 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15640 */
	{.type Header, .u {.hdr { 3, "r/o", /* C_ro = 15656 */ colon }}}, /* CENTRY "r/o" ro 3 h 15664 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15672 */
	{.type Absolute, .u {.p 0}},		/* dd 0 15680 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15688 */
	{.type Header, .u {.hdr { 3, "r/w", /* C_rw = 15704 */ colon }}}, /* CENTRY "r/w" rw 3 h 15712 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15720 */
	{.type Absolute, .u {.p 2}},		/* dd 2 15728 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 15736 */
	{.type Header, .u {.hdr { 9, "open-file", /* C_open_file = 15760 */ colon }}}, /* CENTRY "open-file" open_file 9 h 15768 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 15776 */
	{.type FromH0, .u {.p C_pad}},		/* dd C_pad 15784 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15792 */
	{.type Absolute, .u {.p 1024}},		/* dd 1024 15800 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 15808 */
	{.type FromH0, .u {.p M_xswap}},		/* dd M_xswap 15816 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 15824 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 15832 */
	{.type FromH0, .u {.p M_cmove}},		/* dd M_cmove 15840 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15848 */
	{.type Absolute, .u {.p 0}},		/* dd 0 15856 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 15864 */
	{.type FromH0, .u {.p C_pad}},		/* dd C_pad 15872 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 15880 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15888 */
	{.type Absolute, .u {.p 1024}},		/* dd 1024 15896 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 15904 */
	{.type FromH0, .u {.p M_cstore}},		/* dd M_cstore 15912 */
	{.type FromH0, .u {.p C_pad}},		/* dd C_pad 15920 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15928 */
	{.type Absolute, .u {.p 1024}},		/* dd 1024 15936 */
	{.type FromH0, .u {.p M_plus}},		/* dd M_plus 15944 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 15952 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15960 */
	{.type Absolute, .u {.p 420}},		/* dd 420 15968 */
	{.type FromH0, .u {.p M_fthopen}},		/* dd M_fthopen 15976 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 15984 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 15992 */
	{.type Absolute, .u {.p -1}},		/* dd -1 16000 */
	{.type FromH0, .u {.p M_greater}},		/* dd M_greater 16008 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 16016 */
	{.type Header, .u {.hdr { 10, "close-file", /* C_close_file = 16040 */ colon }}}, /* CENTRY "close-file" close_file 10 h 16048 */
	{.type FromH0, .u {.p M_fthclose}},		/* dd M_fthclose 16056 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq 16064 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 16072 */
	{.type Header, .u {.hdr { 9, "read-file", /* C_read_file = 16096 */ colon }}}, /* CENTRY "read-file" read_file 9 h 16104 */
	{.type FromH0, .u {.p M_fthread}},		/* dd M_fthread 16112 */
	{.type FromH0, .u {.p M_dup}},		/* dd M_dup 16120 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 16128 */
	{.type Absolute, .u {.p -1}},		/* dd -1 16136 */
	{.type FromH0, .u {.p C_neq}},		/* dd C_neq 16144 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 16152 */
	{.type Header, .u {.hdr { 10, "write-file", /* C_write_file = 16176 */ colon }}}, /* CENTRY "write-file" write_file 10 h 16184 */
	{.type FromH0, .u {.p M_fthwrite}},		/* dd M_fthwrite 16192 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 16200 */
	{.type Absolute, .u {.p -1}},		/* dd -1 16208 */
	{.type FromH0, .u {.p C_neq}},		/* dd C_neq 16216 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 16224 */
	{.type Header, .u {.hdr { 15, "reposition-file", /* C_reposition_file = 16248 */ colon }}}, /* CENTRY "reposition-file" reposition_file 15 h 16256 */
	{.type FromH0, .u {.p M_fthseek}},		/* dd M_fthseek 16264 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 16272 */
	{.type Absolute, .u {.p -1}},		/* dd -1 16280 */
	{.type FromH0, .u {.p C_neq}},		/* dd C_neq 16288 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 16296 */
	{.type Header, .u {.hdr { 7, "?fcheck", /* C_qfcheck = 16312 */ colon }}}, /* CENTRY "?fcheck" qfcheck 7 h 16320 */
	{.type FromH0, .u {.p C_0eq}},		/* dd C_0eq 16328 */
	{.type FromH0, .u {.p M_cjump}},		/* dd M_cjump 16336 */
	{.type FromH0, .u {.p L246}},		/* dd L246 16344 */
	{.type FromH0, .u {.p C_space}},		/* dd C_space 16352 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 16360 */
	{.type FromH0, .u {.p L247}},		/* dd L247 16368 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 16376 */
	{.type Absolute, .u {.p 9}},		/* dd 9 16384 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 16392 */
	{.type FromH0, .u {.p C_cr}},		/* dd C_cr 16400 */
	{.type FromH0, .u {.p C_abort}},		/* dd C_abort 16408 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 16416 */
	{.type Header, .u {.hdr { 3, "bye", /* C_bye = 16432 */ colon }}}, /* CENTRY "bye" bye 3 h 16440 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 16448 */
	{.type Absolute, .u {.p 0}},		/* dd 0 16456 */
	{.type FromH0, .u {.p M_terminate}},		/* dd M_terminate 16464 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 16472 */
	{.type Header, .u {.hdr { 7, "include", /* C_include = 16488 */ colon }}}, /* CENTRY "include" include 7 h 16496 */
	{.type FromH0, .u {.p C_bl}},		/* dd C_bl 16504 */
	{.type FromH0, .u {.p C_word}},		/* dd C_word 16512 */
	{.type FromH0, .u {.p M_rpush}},		/* dd M_rpush 16520 */
	{.type FromH0, .u {.p MV_toLimit}},		/* dd MV_toLimit 16528 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch 16536 */
	{.type FromH0, .u {.p MV_toIn}},		/* dd MV_toIn 16544 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 16552 */
	{.type FromH0, .u {.p C_save_input}},		/* dd C_save_input 16560 */
	{.type FromH0, .u {.p M_rpop}},		/* dd M_rpop 16568 */
	{.type FromH0, .u {.p C_count}},		/* dd C_count 16576 */
	{.type FromH0, .u {.p C_ro}},		/* dd C_ro 16584 */
	{.type FromH0, .u {.p C_open_file}},		/* dd C_open_file 16592 */
	{.type FromH0, .u {.p C_qfcheck}},		/* dd C_qfcheck 16600 */
	{.type FromH0, .u {.p MV_Infd}},		/* dd MV_Infd 16608 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 16616 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 16624 */
	{.type Header, .u {.hdr { 5, "crash", /* C_crash = 16640 */ colon }}}, /* CENTRY "crash" crash 5 h 16648 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 16656 */
	{.type FromH0, .u {.p L251}},		/* dd L251 16664 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 16672 */
	{.type Absolute, .u {.p 30}},		/* dd 30 16680 */
	{.type FromH0, .u {.p C_type}},		/* dd C_type 16688 */
	{.type FromH0, .u {.p C_cr}},		/* dd C_cr 16696 */
	{.type FromH0, .u {.p C_abort}},		/* dd C_abort 16704 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 16712 */
	{.type Header, .u {.hdr { 4, "quit", /* C_quit = 16728 */ colon }}}, /* CENTRY "quit" quit 4 ; interpreter loop h 16736 */
	{.type FromH0, .u {.p M_reset}},		/* dd M_reset ; initialize return stack 16744 */
	{.type FromH0, .u {.p M_clear}},		/* dd M_clear	; SP = sstack_end initialize data stack 16752 */
	{.type FromH0, .u {.p C_query}},		/* dd C_query 16760 */
	{.type FromH0, .u {.p C_interpret}},		/* dd C_interpret 16768 */
	{.type FromH0, .u {.p M_jump}},		/* dd M_jump 16776 */
	{.type FromH0, .u {.p L253}},		/* dd L253 16784 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon	; why is this needed? 16792 */
	{.type Header, .u {.hdr { 7, "(abort)", /* C_parenabort = 16808 */ colon }}}, /* CENTRY "(abort)" parenabort 7 ; TODO correct below stack notations h 16816 */
	{.type FromH0, .u {.p MV_State}},		/* dd MV_State	; ( mv_State -- ) 16824 */
	{.type FromH0, .u {.p C_off}},		/* dd C_off		; off sets variable state = 0 16832 */
	{.type FromH0, .u {.p MC_TIB}},		/* dd MC_TIB	; constant puts address of tibuffer on the top of stack 16840 */
	{.type FromH0, .u {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 16848 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 16856 */
	{.type FromH0, .u {.p MV_Blk}},		/* dd MV_Blk	; variable blk 16864 */
	{.type FromH0, .u {.p C_off}},		/* dd C_off	; off variable blk = 0 16872 */
	{.type FromH0, .u {.p MC_STDIN}},		/* dd MC_STDIN 16880 */
	{.type FromH0, .u {.p MV_Infd}},		/* dd MV_Infd 16888 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 16896 */
	{.type FromH0, .u {.p MC_STDOUT}},		/* dd MC_STDOUT 16904 */
	{.type FromH0, .u {.p MV_Outfd}},		/* dd MV_Outfd 16912 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 16920 */
	{.type FromH0, .u {.p MC_STDERR}},		/* dd MC_STDERR 16928 */
	{.type FromH0, .u {.p MV_Errfd}},		/* dd MV_Errfd 16936 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 16944 */
	{.type FromH0, .u {.p C_quit}},		/* dd C_quit	; quit resets stacks and is the interpreter loop 16952 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon	; why is this needed? quit does not return unless it breaks 16960 */
	{.type Header, .u {.hdr { 7, "oldboot", /* C_oldboot = 16976 */ colon }}}, /* CENTRY "oldboot" oldboot 7 ; TODO correct below stack notations and this is obsolete. leaving it here for reference until it all works well h 16984 */
	{.type FromH0, .u {.p M_reset}},		/* dd M_reset 16992 */
	{.type FromH0, .u {.p M_clear}},		/* dd M_clear	; SP = sstack_end 17000 */
	{.type FromH0, .u {.p M_stackptr}},		/* dd M_stackptr	; (D -- FFEND) 17008 */
	{.type FromH0, .u {.p M_s0}},		/* dd M_s0 17016 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store	; s0 = FFEND 17024 */
	{.type FromH0, .u {.p M_h0}},		/* dd M_h0	; heaptop = heapend 17032 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch	; ( heapend -- ) 17040 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 17048 */
	{.type Absolute, .u {.p 1}},		/* dd 1		; ( heapend 1 -- ) 17056 */
	{.type FromH0, .u {.p C_cells}},		/* dd C_cells	; cells ( heapend 8 -- ) 17064 */
	{.type FromH0, .u {.p M_minus}},		/* dd M_minus	; ( heapend-8 -- ) 17072 */
	{.type FromH0, .u {.p M_fetch}},		/* dd M_fetch	; ( contents_from_heapend-8 -- ) 17080 */
	{.type FromH0, .u {.p M_args}},		/* dd M_args	; variable args 17088 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store	; args = contents_from_heapend-8 17096 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 17104 */
	{.type FromH0, .u {.p C_parenabort}},		/* dd C_parenabort ; ( (abort) -- ) 17112 */
	{.type FromH0, .u {.p MV_Abortvec}},		/* dd MV_Abortvec	; variable abortvec 17120 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store	; variable abortvec = (abort) code address 17128 */
	{.type FromH0, .u {.p MC_WORDB}},		/* dd MC_WORDB	; constant puts address of wordbuffer on the top of stack 17136 */
	{.type FromH0, .u {.p MV_Wordbuf}},		/* dd MV_Wordbuf	; variable wordbuf 17144 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store	; variable wordbuf = address of wordbuffer 17152 */
	{.type FromH0, .u {.p MC_TIB}},		/* dd MC_TIB	; constant puts address of tibuffer on the top of stack 17160 */
	{.type FromH0, .u {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 17168 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 17176 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 17184 */
	{.type Absolute, .u {.p 0}},		/* dd 0 17192 */
	{.type FromH0, .u {.p MV_Infd}},		/* dd MV_Infd 17200 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store	; stdin = 0 17208 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 17216 */
	{.type Absolute, .u {.p 1}},		/* dd 1 17224 */
	{.type FromH0, .u {.p MV_Outfd}},		/* dd MV_Outfd 17232 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store	; stdout = 1 17240 */
	{.type FromH0, .u {.p MV_State}},		/* dd MV_State 17248 */
	{.type FromH0, .u {.p C_off}},		/* dd C_off	; off stores 0 at state 17256 */
	{.type FromH0, .u {.p C_decimal}},		/* dd C_decimal	; decimal setting base = 0 17264 */
	{.type FromH0, .u {.p C_quit}},		/* dd C_quit	; quit 17272 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 17280 */
	{.type Header, .u {.hdr { 4, "boot", /* C_boot = 17296 */ colon }}}, /* CENTRY "boot" boot 4 h 17304 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal	; this is not working TEST 17312 */
	{.type Absolute, .u {.p 66}},		/* dd 66 17320 */
	{.type FromH0, .u {.p MC_WORDB}},		/* dd MC_WORDB 17328 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 17336 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 17344 */
	{.type Absolute, .u {.p 1}},		/* dd 1 17352 */
	{.type FromH0, .u {.p MC_WORDB}},		/* dd MC_WORDB 17360 */
	{.type FromH0, .u {.p MC_STDOUT}},		/* dd MC_STDOUT 17368 */
	{.type FromH0, .u {.p M_fthwrite}},		/* dd M_fthwrite 17376 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 17384 */
	{.type Absolute, .u {.p 1}},		/* dd 1 17392 */
	{.type FromH0, .u {.p MC_WORDB}},		/* dd MC_WORDB 17400 */
	{.type FromH0, .u {.p MC_STDIN}},		/* dd MC_STDIN 17408 */
	{.type FromH0, .u {.p M_fthread}},		/* dd M_fthread	; this is not working TODO 17416 */
	{.type FromH0, .u {.p M_reset}},		/* dd M_reset ; initialize return stack 17424 */
	{.type FromH0, .u {.p M_clear}},		/* dd M_clear	; SP = sstack_end initialize data stack 17432 */
	{.type FromH0, .u {.p M_literal}},		/* dd M_literal 17440 */
	{.type FromH0, .u {.p C_parenabort}},		/* dd C_parenabort ; ( (abort) -- ) 17448 */
	{.type FromH0, .u {.p MV_Abortvec}},		/* dd MV_Abortvec	; variable that puts (abort) code address on the stack 17456 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store	; variable abortvec = (abort) code address 17464 */
	{.type FromH0, .u {.p MC_WORDB}},		/* dd MC_WORDB	; variable puts address of wordbuffer on the top of stack 17472 */
	{.type FromH0, .u {.p MV_Wordbuf}},		/* dd MV_Wordbuf ; variable wordbuf 17480 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store	; variable wordbuf = address of wordbuffer 17488 */
	{.type FromH0, .u {.p MC_TIB}},		/* dd MC_TIB	; constant puts address of tibuffer on the top of stack 17496 */
	{.type FromH0, .u {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 17504 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 17512 */
	{.type FromH0, .u {.p MC_STDIN}},		/* dd MC_STDIN 17520 */
	{.type FromH0, .u {.p MV_Infd}},		/* dd MV_Infd 17528 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store	; stdin = 0 17536 */
	{.type FromH0, .u {.p MC_STDOUT}},		/* dd MC_STDOUT 17544 */
	{.type FromH0, .u {.p MV_Outfd}},		/* dd MV_Outfd 17552 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 17560 */
	{.type FromH0, .u {.p MC_STDERR}},		/* dd MC_STDERR 17568 */
	{.type FromH0, .u {.p MV_Errfd}},		/* dd MV_Errfd 17576 */
	{.type FromH0, .u {.p M_store}},		/* dd M_store 17584 */
	{.type FromH0, .u {.p MV_State}},		/* dd MV_State 17592 */
	{.type FromH0, .u {.p C_off}},		/* dd C_off	; off stores 0 at state 17600 */
	{.type FromH0, .u {.p C_decimal}},		/* dd C_decimal	; decimal setting base = 0 17608 */
	{.type FromH0, .u {.p C_quit}},		/* dd C_quit	; quit 17616 */
	{.type FromH0, .u {.p M_exitcolon}},		/* dd M_exitcolon 17624 */
	{.type Chars, .u {.str "unable to restore input"}},		/* 17648 */
	{.type Chars, .u {.str " Q?"}},		/* 17652 */
	{.type Chars, .u {.str " stack underflow"}},		/* 17669 */
	{.type Chars, .u {.str " I?"}},		/* 17673 */
	{.type Chars, .u {.str " C?"}},		/* 17677 */
	{.type Chars, .u {.str "I/O error"}},		/* 17687 */
	{.type Chars, .u {.str "uninitialized execution vector"}},		/* 17718 */
	{.type Chars, .u {.str " ok"}},		/* 17722 */
};

