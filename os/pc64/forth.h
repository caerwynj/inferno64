/*
 * Forth dictionary
 */
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
	char name[64];
	void *cfa;
};
typedef struct Fentry Fentry;
struct Fentry
{
	int type;
	union {
		Hdr hdr;
		intptr p;
		char str[128];
	};
};
enum {
	M_Dp = 16,
	M_Dtop = 40,
	M_fetch = 64,
	M_store = 88,
	M_cfetch = 112,
	M_cstore = 136,
	M_fthread = 160,
	M_fthwrite = 184,
	M_fthseek = 208,
	M_fthopen = 232,
	M_fthclose = 256,
	M_mmap = 280,
	M_terminate = 304,
	M_clear = 328,
	M_reset = 352,
	M_exitcolon = 376,
	M_literal = 408,
	M_sliteral = 440,
	M_doinit = 464,
	M_doloop = 488,
	M_doploop = 512,
	M_rfetch = 536,
	M_rpop = 560,
	M_rpush = 584,
	M_i = 608,
	M_j = 632,
	M_plus = 656,
	M_minus = 680,
	M_multiply = 704,
	M_cjump = 728,
	M_jump = 752,
	M_slashmod = 776,
	M_uslashmod = 800,
	M_binand = 824,
	M_binor = 848,
	M_binxor = 872,
	M_xswap = 896,
	M_drop = 920,
	M_dup = 944,
	M_over = 968,
	M_equal = 992,
	M_greater = 1016,
	M_less = 1040,
	M_lshift = 1064,
	M_rshift = 1088,
	M_rshifta = 1112,
	M_execute = 1136,
	M_unloop = 1160,
	M_cmove = 1184,
	M_cmoveb = 1208,
	MV_Iobuf = 1232,
	MV_Sourcebuf = 1272,
	MV_Wordbuf = 1304,
	MV_toIn = 1336,
	MV_toLimit = 1368,
	MV_Findadr = 1400,
	MV_Blk = 1432,
	MV_Searchlen = 1472,
	MV_Base = 1504,
	MV_toNum = 1536,
	MV_State = 1568,
	MV_Abortvec = 1608,
	MV_Infd = 1640,
	MV_Outfd = 1672,
	MV_Errfd = 1704,
	MV_Eof = 1736,
	MC_STDIN = 1768,
	MC_STDOUT = 1800,
	MC_STDERR = 1832,
	M_S0 = 1864,
	M_stackptr = 1888,
	M_H0 = 1912,
	M_Wordb = 1936,
	M_Tib = 1960,
	M_Args = 1984,
	M_variable = 2016,
	M_constant = 2048,
	M_colon = 2072,
	M_dodoes = 2096,
	M_cas = 2120,
	M_deferred = 2152,
	C_false = 2176,
	C_true = 2224,
	C_bl = 2272,
	C_on = 2320,
	C_off = 2384,
	C_tobody = 2448,
	C_aligned = 2504,
	C_cells = 2584,
	C_cellplus = 2640,
	C_depth = 2704,
	C_nip = 2808,
	C_rot = 2856,
	C_2drop = 2920,
	C_2dup = 2968,
	C_2nip = 3016,
	C_2swap = 3064,
	C_qdup = 3128,
	L20 = 3200,
	C_pick = 3224,
	L22 = 3328,
	L23 = 3336,
	C_tuck = 3360,
	C_divides = 3424,
	C_plusstore = 3472,
	C_invert = 3552,
	C_mod = 3608,
	C_1plus = 3656,
	C_1minus = 3712,
	C_negate = 3768,
	C_2multiplies = 3832,
	C_2divides = 3888,
	C_0eq = 3944,
	C_0lt = 4000,
	C_0gt = 4056,
	C_neq = 4112,
	C_0neq = 4160,
	C_max = 4216,
	L40 = 4280,
	L41 = 4288,
	C_min = 4312,
	L43 = 4376,
	L44 = 4384,
	C_signum = 4408,
	L46 = 4488,
	L48 = 4544,
	L49 = 4560,
	L47 = 4560,
	C_within = 4584,
	C_abs = 4688,
	L52 = 4736,
	C_key = 4760,
	L78 = 4888,
	L79 = 4904,
	C_emit = 4928,
	C_type = 5032,
	C_cr = 5096,
	C_space = 5152,
	C_emits = 5200,
	L85 = 5208,
	L86 = 5272,
	C_spaces = 5304,
	C_count = 5360,
	C_compare = 5424,
	L55 = 5496,
	L56 = 5632,
	C_erase = 5712,
	L58 = 5744,
	C_fill = 5832,
	L60 = 5872,
	C_blank = 5960,
	C_search = 6008,
	L64 = 6112,
	L65 = 6296,
	C_here = 6360,
	C_comma = 6408,
	C_c = 6488,
	C_allot = 6568,
	C_pad = 6616,
	C_align = 6680,
	C_unused = 6744,
	C_fromhash = 6808,
	C_hash = 6888,
	L92 = 7040,
	L93 = 7064,
	C_hashs = 7144,
	L95 = 7152,
	L96 = 7200,
	C_hashfrom = 7224,
	C_hold = 7336,
	C_sign = 7440,
	L100 = 7496,
	C_dot = 7520,
	C_dotr = 7624,
	C_hex = 7784,
	C_decimal = 7848,
	C_digit = 7912,
	L106 = 8024,
	L108 = 8128,
	L110 = 8232,
	L111 = 8256,
	L109 = 8256,
	L107 = 8256,
	L112 = 8328,
	L113 = 8344,
	C_number = 8368,
	L115 = 8504,
	L116 = 8536,
	L117 = 8600,
	L118 = 8704,
	L119 = 8760,
	C_abort = 8848,
	C_source = 8904,
	C_current_input = 8960,
	C_save_input = 9040,
	C_default_input = 9168,
	C_restore_input = 9288,
	L133 = 9384,
	L134 = 9472,
	C_qrestore_input = 9504,
	L136 = 9608,
	C_next_input = 9640,
	L139 = 9736,
	L140 = 9760,
	C_parse = 9784,
	L142 = 9824,
	L143 = 9952,
	C_word = 10096,
	L145 = 10112,
	L146 = 10208,
	C_accept = 10248,
	L148 = 10288,
	L150 = 10448,
	L149 = 10512,
	C_query = 10560,
	L152 = 10704,
	L153 = 10736,
	C_refill = 10760,
	L155 = 10824,
	L156 = 10840,
	C_findname = 10872,
	L158 = 10912,
	L160 = 11024,
	L162 = 11152,
	L161 = 11160,
	L159 = 11176,
	C_find = 11224,
	L165 = 11416,
	L166 = 11432,
	L164 = 11456,
	L167 = 11464,
	C_single_quote = 11488,
	L169 = 11624,
	C_qstack = 11648,
	L172 = 11752,
	C_interpret = 11784,
	L175 = 11792,
	L177 = 11904,
	L179 = 12016,
	L178 = 12016,
	L176 = 12032,
	C_create = 12064,
	C_variable = 12312,
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
	C_sliteral = 13864,
	C_string = 14032,
	L214 = 14376,
	L215 = 14408,
	C_qabort_parens = 14440,
	L217 = 14520,
	L218 = 14528,
	C_double_quote = 14592,
	C_cdouble_quote = 14720,
	L234 = 15464,
	L236 = 15552,
	C_wo = 15576,
	C_ro = 15672,
	C_rw = 15720,
	C_open_file = 15776,
	C_close_file = 16056,
	C_read_file = 16112,
	C_write_file = 16192,
	C_reposition_file = 16264,
	C_qfcheck = 16328,
	L246 = 16424,
	C_bye = 16448,
	C_include = 16504,
	C_crash = 16656,
	C_quit = 16744,
	L253 = 16768,
	C_parenabort = 16824,
	C_oldboot = 16992,
	C_boot = 17312,
	L137 = 17640,
	L170 = 17664,
	L173 = 17668,
	L180 = 17685,
	L193 = 17689,
	L247 = 17693,
	L251 = 17703,
	L255 = 17734,
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
extern void *xswap(void);
extern void *terminate(void);
extern void *greater(void);
extern void *slashmod(void);
extern void *cmoveb(void);
extern void *doinit(void);
extern void *Dtop(void);
extern void *multiply(void);
extern void *colon(void);
extern void *less(void);
extern void *lshift(void);
extern void *fthopen(void);
extern void *Dp(void);
extern void *S0(void);
extern void *plus(void);
extern void *jump(void);
extern void *rshift(void);
extern void *cstore(void);
extern void *Args(void);
extern void *Tib(void);
extern void *store(void);
extern void *cmove(void);
extern void *binor(void);
extern void *fthclose(void);
extern void *unloop(void);
extern void *Wordb(void);
extern void *H0(void);
extern void *cfetch(void);
extern void *constant(void);
extern void *variable(void);
extern void *fetch(void);
extern void *doloop(void);
extern void *mmap(void);
extern void *binxor(void);
extern void *fthread(void);
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
	{.type Header, {.hdr { 2, "Dp", /* M_Dp = 16 */ Dp }}}, /* MENTRY "Dp" Dp 2		; cannot use H as it is nil in inferno, next available cell for the dictionary h 24 */
	{.type Header, {.hdr { 4, "Dtop", /* M_Dtop = 40 */ Dtop }}}, /* MENTRY "Dtop" Dtop 4	; last defined header h 48 */
	{.type Header, {.hdr { 1, "@", /* M_fetch = 64 */ fetch }}}, /* MENTRY "@" fetch 1 h 72 */
	{.type Header, {.hdr { 1, "!", /* M_store = 88 */ store }}}, /* MENTRY "!" store 1 h 96 */
	{.type Header, {.hdr { 2, "c@", /* M_cfetch = 112 */ cfetch }}}, /* MENTRY "c@" cfetch 2 h 120 */
	{.type Header, {.hdr { 2, "c!", /* M_cstore = 136 */ cstore }}}, /* MENTRY "c!" cstore 2 h 144 */
	{.type Header, {.hdr { 4, "read", /* M_fthread = 160 */ fthread }}}, /* MENTRY "read" fthread 4 h 168 */
	{.type Header, {.hdr { 5, "write", /* M_fthwrite = 184 */ fthwrite }}}, /* MENTRY "write" fthwrite 5 h 192 */
	{.type Header, {.hdr { 4, "seek", /* M_fthseek = 208 */ fthseek }}}, /* MENTRY "seek" fthseek 4 h 216 */
	{.type Header, {.hdr { 4, "open", /* M_fthopen = 232 */ fthopen }}}, /* MENTRY "open" fthopen 4 h 240 */
	{.type Header, {.hdr { 5, "close", /* M_fthclose = 256 */ fthclose }}}, /* MENTRY "close" fthclose 5 h 264 */
	{.type Header, {.hdr { 4, "mmap", /* M_mmap = 280 */ mmap }}}, /* MENTRY "mmap" mmap 4 h 288 */
	{.type Header, {.hdr { 4, "halt", /* M_terminate = 304 */ terminate }}}, /* MENTRY "halt" terminate 4 h 312 */
	{.type Header, {.hdr { 5, "clear", /* M_clear = 328 */ clear }}}, /* MENTRY "clear" clear 5 h 336 */
	{.type Header, {.hdr { 5, "reset", /* M_reset = 352 */ reset }}}, /* MENTRY "reset" reset 5 h 360 */
	{.type Header, {.hdr { 4, "exitcolon", /* M_exitcolon = 376 */ exitcolon }}}, /* MENTRY "exitcolon" exitcolon 4 h 384 */
	{.type Header, {.hdr { 9, "(literal)", /* M_literal = 408 */ literal }}}, /* MENTRY "(literal)" literal 9 h 416 */
	{.type Header, {.hdr { 10, "(sliteral)", /* M_sliteral = 440 */ sliteral }}}, /* MENTRY "(sliteral)" sliteral 10 h 448 */
	{.type Header, {.hdr { 4, "(do)", /* M_doinit = 464 */ doinit }}}, /* MENTRY "(do)" doinit 4 h 472 */
	{.type Header, {.hdr { 6, "(loop)", /* M_doloop = 488 */ doloop }}}, /* MENTRY "(loop)" doloop 6 h 496 */
	{.type Header, {.hdr { 7, "(+loop)", /* M_doploop = 512 */ doploop }}}, /* MENTRY "(+loop)" doploop 7 h 520 */
	{.type Header, {.hdr { 2, "r@", /* M_rfetch = 536 */ rfetch }}}, /* MENTRY "r@" rfetch 2 h 544 */
	{.type Header, {.hdr { 2, "r>", /* M_rpop = 560 */ rpop }}}, /* MENTRY "r>" rpop 2 h 568 */
	{.type Header, {.hdr { 2, ">r", /* M_rpush = 584 */ rpush }}}, /* MENTRY ">r" rpush 2 h 592 */
	{.type Header, {.hdr { 1, "i", /* M_i = 608 */ i }}}, /* MENTRY "i" i 1 h 616 */
	{.type Header, {.hdr { 1, "j", /* M_j = 632 */ j }}}, /* MENTRY "j" j 1 h 640 */
	{.type Header, {.hdr { 1, "+", /* M_plus = 656 */ plus }}}, /* MENTRY "+" plus 1 h 664 */
	{.type Header, {.hdr { 1, "-", /* M_minus = 680 */ minus }}}, /* MENTRY "-" minus 1 h 688 */
	{.type Header, {.hdr { 1, "*", /* M_multiply = 704 */ multiply }}}, /* MENTRY "*" multiply 1 h 712 */
	{.type Header, {.hdr { 4, "(if)", /* M_cjump = 728 */ cjump }}}, /* MENTRY "(if)" cjump 4 h 736 */
	{.type Header, {.hdr { 6, "(else)", /* M_jump = 752 */ jump }}}, /* MENTRY "(else)" jump 6 h 760 */
	{.type Header, {.hdr { 4, "/mod", /* M_slashmod = 776 */ slashmod }}}, /* MENTRY "/mod" slashmod 4 h 784 */
	{.type Header, {.hdr { 5, "u/mod", /* M_uslashmod = 800 */ uslashmod }}}, /* MENTRY "u/mod" uslashmod 5 h 808 */
	{.type Header, {.hdr { 3, "and", /* M_binand = 824 */ binand }}}, /* MENTRY "and" binand 3 h 832 */
	{.type Header, {.hdr { 2, "or", /* M_binor = 848 */ binor }}}, /* MENTRY "or" binor 2 h 856 */
	{.type Header, {.hdr { 3, "xor", /* M_binxor = 872 */ binxor }}}, /* MENTRY "xor" binxor 3 h 880 */
	{.type Header, {.hdr { 4, "swap", /* M_xswap = 896 */ xswap }}}, /* MENTRY "swap" xswap 4 h 904 */
	{.type Header, {.hdr { 4, "drop", /* M_drop = 920 */ drop }}}, /* MENTRY "drop" drop 4 h 928 */
	{.type Header, {.hdr { 3, "dup", /* M_dup = 944 */ dup }}}, /* MENTRY "dup" dup 3 h 952 */
	{.type Header, {.hdr { 4, "over", /* M_over = 968 */ over }}}, /* MENTRY "over" over 4 h 976 */
	{.type Header, {.hdr { 1, "=", /* M_equal = 992 */ equal }}}, /* MENTRY "=" equal 1 h 1000 */
	{.type Header, {.hdr { 1, ">", /* M_greater = 1016 */ greater }}}, /* MENTRY ">" greater 1 h 1024 */
	{.type Header, {.hdr { 1, "<", /* M_less = 1040 */ less }}}, /* MENTRY "<" less 1 h 1048 */
	{.type Header, {.hdr { 6, "lshift", /* M_lshift = 1064 */ lshift }}}, /* MENTRY "lshift" lshift 6 h 1072 */
	{.type Header, {.hdr { 6, "rshift", /* M_rshift = 1088 */ rshift }}}, /* MENTRY "rshift" rshift 6 h 1096 */
	{.type Header, {.hdr { 7, "rshifta", /* M_rshifta = 1112 */ rshifta }}}, /* MENTRY "rshifta" rshifta 7 h 1120 */
	{.type Header, {.hdr { 7, "execute", /* M_execute = 1136 */ execute }}}, /* MENTRY "execute" execute 7 h 1144 */
	{.type Header, {.hdr { 6, "unloop", /* M_unloop = 1160 */ unloop }}}, /* MENTRY "unloop" unloop 6 h 1168 */
	{.type Header, {.hdr { 5, "cmove", /* M_cmove = 1184 */ cmove }}}, /* MENTRY "cmove" cmove 5 h 1192 */
	{.type Header, {.hdr { 6, "cmove>", /* M_cmoveb = 1208 */ cmoveb }}}, /* MENTRY "cmove>" cmoveb 6 h 1216 */
	{.type Header, {.hdr { 5, "Iobuf", /* MV_Iobuf = 1232 */ variable }}}, /* MVENTRY "Iobuf" Iobuf 0 5 h 1240 */
	{.type Absolute, {.p 0}},		/* 1248 */
	{.type Header, {.hdr { 9, "Sourcebuf", /* MV_Sourcebuf = 1272 */ variable }}}, /* MVENTRY "Sourcebuf" Sourcebuf 0 9	; is there a need for this? h 1280 */
	{.type Absolute, {.p 0}},		/* 1288 */
	{.type Header, {.hdr { 7, "Wordbuf", /* MV_Wordbuf = 1304 */ variable }}}, /* MVENTRY "Wordbuf" Wordbuf 0 7		; is there a need for this? h 1312 */
	{.type Absolute, {.p 0}},		/* 1320 */
	{.type Header, {.hdr { 3, ">In", /* MV_toIn = 1336 */ variable }}}, /* MVENTRY ">In" toIn 0 3 h 1344 */
	{.type Absolute, {.p 0}},		/* 1352 */
	{.type Header, {.hdr { 6, ">Limit", /* MV_toLimit = 1368 */ variable }}}, /* MVENTRY ">Limit" toLimit 0 6 h 1376 */
	{.type Absolute, {.p 0}},		/* 1384 */
	{.type Header, {.hdr { 7, "Findadr", /* MV_Findadr = 1400 */ variable }}}, /* MVENTRY "Findadr" Findadr 0 7 h 1408 */
	{.type Absolute, {.p 0}},		/* 1416 */
	{.type Header, {.hdr { 3, "Blk", /* MV_Blk = 1432 */ variable }}}, /* MVENTRY "Blk" Blk 0 3 h 1440 */
	{.type Absolute, {.p 0}},		/* 1448 */
	{.type Header, {.hdr { 9, "Searchlen", /* MV_Searchlen = 1472 */ variable }}}, /* MVENTRY "Searchlen" Searchlen 0 9 h 1480 */
	{.type Absolute, {.p 0}},		/* 1488 */
	{.type Header, {.hdr { 4, "Base", /* MV_Base = 1504 */ variable }}}, /* MVENTRY "Base" Base 0 4 h 1512 */
	{.type Absolute, {.p 0}},		/* 1520 */
	{.type Header, {.hdr { 4, ">Num", /* MV_toNum = 1536 */ variable }}}, /* MVENTRY ">Num" toNum 0 4 h 1544 */
	{.type Absolute, {.p 0}},		/* 1552 */
	{.type Header, {.hdr { 5, "State", /* MV_State = 1568 */ variable }}}, /* MVENTRY "State" State 0 5 h 1576 */
	{.type Absolute, {.p 0}},		/* 1584 */
	{.type Header, {.hdr { 8, "Abortvec", /* MV_Abortvec = 1608 */ variable }}}, /* MVENTRY "Abortvec" Abortvec 0 8	; not sure if these 3 can be constants instead? h 1616 */
	{.type Absolute, {.p 0}},		/* 1624 */
	{.type Header, {.hdr { 4, "Infd", /* MV_Infd = 1640 */ variable }}}, /* MVENTRY "Infd" Infd 0 4 h 1648 */
	{.type Absolute, {.p 0}},		/* 1656 */
	{.type Header, {.hdr { 5, "Outfd", /* MV_Outfd = 1672 */ variable }}}, /* MVENTRY "Outfd" Outfd 0 5 h 1680 */
	{.type Absolute, {.p 0}},		/* 1688 */
	{.type Header, {.hdr { 5, "Errfd", /* MV_Errfd = 1704 */ variable }}}, /* MVENTRY "Errfd" Errfd 0 5 h 1712 */
	{.type Absolute, {.p 0}},		/* 1720 */
	{.type Header, {.hdr { 3, "Eof", /* MV_Eof = 1736 */ variable }}}, /* MVENTRY "Eof" Eof 0 3 h 1744 */
	{.type Absolute, {.p 0}},		/* 1752 */
	{.type Header, {.hdr { 5, "STDIN", /* MC_STDIN = 1768 */ constant }}}, /* MCENTRY "STDIN" STDIN 0 5		; 3 constants from here CAPITALS h 1776 */
	{.type Absolute, {.p 0}},		/* 1784 */
	{.type Header, {.hdr { 6, "STDOUT", /* MC_STDOUT = 1800 */ constant }}}, /* MCENTRY "STDOUT" STDOUT 1 6 h 1808 */
	{.type Absolute, {.p 1}},		/* 1816 */
	{.type Header, {.hdr { 6, "STDERR", /* MC_STDERR = 1832 */ constant }}}, /* MCENTRY "STDERR" STDERR 2 6 h 1840 */
	{.type Absolute, {.p 2}},		/* 1848 */
	{.type Header, {.hdr { 2, "S0", /* M_S0 = 1864 */ S0 }}}, /* MENTRY "S0" S0 2 h 1872 */
	{.type Header, {.hdr { 2, "s@", /* M_stackptr = 1888 */ stackptr }}}, /* MENTRY "s@" stackptr 2		; puts PSP on stack h 1896 */
	{.type Header, {.hdr { 2, "H0", /* M_H0 = 1912 */ H0 }}}, /* MENTRY "H0" H0 2 h 1920 */
	{.type Header, {.hdr { 5, "Wordb", /* M_Wordb = 1936 */ Wordb }}}, /* MENTRY "Wordb" Wordb 5 h 1944 */
	{.type Header, {.hdr { 3, "Tib", /* M_Tib = 1960 */ Tib }}}, /* MENTRY "Tib" Tib 3 h 1968 */
	{.type Header, {.hdr { 3, "Args", /* M_Args = 1984 */ Args }}}, /* MENTRY "Args" Args 3 h 1992 */
	{.type Header, {.hdr { 10, "(variable)", /* M_variable = 2016 */ variable }}}, /* MENTRY "(variable)" variable 10 h 2024 */
	{.type Header, {.hdr { 10, "(constant)", /* M_constant = 2048 */ constant }}}, /* MENTRY "(constant)" constant 10 h 2056 */
	{.type Header, {.hdr { 3, "(:)", /* M_colon = 2072 */ colon }}}, /* MENTRY "(:)" colon 3 h 2080 */
	{.type Header, {.hdr { 6, "(does)", /* M_dodoes = 2096 */ dodoes }}}, /* MENTRY "(does)" dodoes 6 h 2104 */
	{.type Header, {.hdr { 3, "cas", /* M_cas = 2120 */ cas }}}, /* MENTRY "cas" cas 3 h 2128 */
	{.type Header, {.hdr { 10, "(deferred)", /* M_deferred = 2152 */ deferred }}}, /* MENTRY "(deferred)" deferred 10 h 2160 */
	{.type Header, {.hdr { 5, "false", /* C_false = 2176 */ colon }}}, /* CENTRY "false" false 5 h 2184 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2192 */
	{.type Absolute, {.p 0}},		/* dd 0 2200 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2208 */
	{.type Header, {.hdr { 4, "true", /* C_true = 2224 */ colon }}}, /* CENTRY "true" true 4 h 2232 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2240 */
	{.type Absolute, {.p -1}},		/* dd -1 2248 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2256 */
	{.type Header, {.hdr { 2, "bl", /* C_bl = 2272 */ colon }}}, /* CENTRY "bl" bl 2 h 2280 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2288 */
	{.type Absolute, {.p 32}},		/* dd 32 2296 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2304 */
	{.type Header, {.hdr { 2, "on", /* C_on = 2320 */ colon }}}, /* CENTRY "on" on 2 ; ( a -- ) (G stores -1 at a ) h 2328 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2336 */
	{.type Absolute, {.p -1}},		/* dd -1 2344 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2352 */
	{.type FromH0, {.p M_store}},		/* dd M_store 2360 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2368 */
	{.type Header, {.hdr { 3, "off", /* C_off = 2384 */ colon }}}, /* CENTRY "off" off 3 ; ( a -- ) (G stores 0 at a ) h 2392 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2400 */
	{.type Absolute, {.p 0}},		/* dd 0 2408 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2416 */
	{.type FromH0, {.p M_store}},		/* dd M_store 2424 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2432 */
	{.type Header, {.hdr { 5, ">body", /* C_tobody = 2448 */ colon }}}, /* CENTRY ">body" tobody 5 h 2456 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2464 */
	{.type Absolute, {.p 8}},		/* dd 8 2472 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 2480 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2488 */
	{.type Header, {.hdr { 7, "aligned", /* C_aligned = 2504 */ colon }}}, /* CENTRY "aligned" aligned 7 h 2512 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2520 */
	{.type Absolute, {.p 7}},		/* dd 7 2528 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 2536 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2544 */
	{.type Absolute, {.p -8}},		/* dd -8 2552 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 2560 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2568 */
	{.type Header, {.hdr { 5, "cells", /* C_cells = 2584 */ colon }}}, /* CENTRY "cells" cells 5 h 2592 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2600 */
	{.type Absolute, {.p 3}},		/* dd 3			; (index << 2) -> (index << 3)for amd64 2608 */
	{.type FromH0, {.p M_lshift}},		/* dd M_lshift 2616 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2624 */
	{.type Header, {.hdr { 5, "cell+", /* C_cellplus = 2640 */ colon }}}, /* CENTRY "cell+" cellplus 5 h 2648 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2656 */
	{.type Absolute, {.p 1}},		/* dd 1 2664 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 2672 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 2680 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2688 */
	{.type Header, {.hdr { 5, "depth", /* C_depth = 2704 */ colon }}}, /* CENTRY "depth" depth 5 h 2712 */
	{.type FromH0, {.p M_S0}},		/* dd M_S0 2720 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr 2728 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 2736 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2744 */
	{.type Absolute, {.p 3}},		/* dd 3 2752 */
	{.type FromH0, {.p M_rshift}},		/* dd M_rshift 2760 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2768 */
	{.type Absolute, {.p 1}},		/* dd 1 2776 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 2784 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2792 */
	{.type Header, {.hdr { 3, "nip", /* C_nip = 2808 */ colon }}}, /* CENTRY "nip" nip 3 h 2816 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2824 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 2832 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2840 */
	{.type Header, {.hdr { 3, "rot", /* C_rot = 2856 */ colon }}}, /* CENTRY "rot" rot 3 h 2864 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 2872 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2880 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 2888 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2896 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2904 */
	{.type Header, {.hdr { 5, "2drop", /* C_2drop = 2920 */ colon }}}, /* CENTRY "2drop" 2drop 5 h 2928 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 2936 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 2944 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2952 */
	{.type Header, {.hdr { 4, "2dup", /* C_2dup = 2968 */ colon }}}, /* CENTRY "2dup" 2dup 4 h 2976 */
	{.type FromH0, {.p M_over}},		/* dd M_over 2984 */
	{.type FromH0, {.p M_over}},		/* dd M_over 2992 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3000 */
	{.type Header, {.hdr { 4, "2nip", /* C_2nip = 3016 */ colon }}}, /* CENTRY "2nip" 2nip 4 h 3024 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 3032 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 3040 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3048 */
	{.type Header, {.hdr { 5, "2swap", /* C_2swap = 3064 */ colon }}}, /* CENTRY "2swap" 2swap 5 h 3072 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot 3080 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 3088 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot 3096 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 3104 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3112 */
	{.type Header, {.hdr { 4, "?dup", /* C_qdup = 3128 */ colon }}}, /* CENTRY "?dup" qdup 4 ; if (tos != 0) dup ( n -- ) TODO correct stack notations h 3136 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n n -- ) 3144 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n n n -- ) 3152 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3160 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( n n n 0 -- ) 3168 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( n n f -- ) 3176 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump	; ( n n -- ) 3184 */
	{.type FromH0, {.p L20}},		/* dd L20 3192 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop	; tos == 0 ( n -- ) 3200 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3208 */
	{.type Header, {.hdr { 4, "pick", /* C_pick = 3224 */ colon }}}, /* CENTRY "pick" pick 4 h 3232 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 3240 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 3248 */
	{.type FromH0, {.p L22}},		/* dd L22 3256 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3264 */
	{.type Absolute, {.p 1}},		/* dd 1 3272 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3280 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 3288 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr 3296 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3304 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 3312 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 3320 */
	{.type FromH0, {.p L23}},		/* dd L23 3328 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 3336 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3344 */
	{.type Header, {.hdr { 4, "tuck", /* C_tuck = 3360 */ colon }}}, /* CENTRY "tuck" tuck 4 h 3368 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 3376 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 3384 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 3392 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 3400 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3408 */
	{.type Header, {.hdr { 1, "/", /* C_divides = 3424 */ colon }}}, /* CENTRY "/" divides 1 h 3432 */
	{.type FromH0, {.p M_slashmod}},		/* dd M_slashmod 3440 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 3448 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3456 */
	{.type Header, {.hdr { 2, "+!", /* C_plusstore = 3472 */ colon }}}, /* CENTRY "+!" plusstore 2 h 3480 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 3488 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 3496 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot 3504 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3512 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 3520 */
	{.type FromH0, {.p M_store}},		/* dd M_store 3528 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3536 */
	{.type Header, {.hdr { 6, "invert", /* C_invert = 3552 */ colon }}}, /* CENTRY "invert" invert 6 h 3560 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3568 */
	{.type Absolute, {.p -1}},		/* dd -1 3576 */
	{.type FromH0, {.p M_binxor}},		/* dd M_binxor 3584 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3592 */
	{.type Header, {.hdr { 3, "mod", /* C_mod = 3608 */ colon }}}, /* CENTRY "mod" mod 3 h 3616 */
	{.type FromH0, {.p M_slashmod}},		/* dd M_slashmod 3624 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 3632 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3640 */
	{.type Header, {.hdr { 2, "1+", /* C_1plus = 3656 */ colon }}}, /* CENTRY "1+" 1plus 2 h 3664 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3672 */
	{.type Absolute, {.p 1}},		/* dd 1 3680 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3688 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3696 */
	{.type Header, {.hdr { 2, "1-", /* C_1minus = 3712 */ colon }}}, /* CENTRY "1-" 1minus 2 h 3720 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3728 */
	{.type Absolute, {.p 1}},		/* dd 1 3736 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 3744 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3752 */
	{.type Header, {.hdr { 6, "negate", /* C_negate = 3768 */ colon }}}, /* CENTRY "negate" negate 6 h 3776 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3784 */
	{.type Absolute, {.p 0}},		/* dd 0 3792 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 3800 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 3808 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3816 */
	{.type Header, {.hdr { 2, "2*", /* C_2multiplies = 3832 */ colon }}}, /* CENTRY "2*" 2multiplies 2 h 3840 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3848 */
	{.type Absolute, {.p 1}},		/* dd 1 3856 */
	{.type FromH0, {.p M_lshift}},		/* dd M_lshift 3864 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3872 */
	{.type Header, {.hdr { 2, "2/", /* C_2divides = 3888 */ colon }}}, /* CENTRY "2/" 2divides 2 h 3896 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3904 */
	{.type Absolute, {.p 1}},		/* dd 1 3912 */
	{.type FromH0, {.p M_rshifta}},		/* dd M_rshifta 3920 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3928 */
	{.type Header, {.hdr { 2, "0=", /* C_0eq = 3944 */ colon }}}, /* CENTRY "0=" 0eq 2 h 3952 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3960 */
	{.type Absolute, {.p 0}},		/* dd 0 3968 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal 3976 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3984 */
	{.type Header, {.hdr { 2, "0<", /* C_0lt = 4000 */ colon }}}, /* CENTRY "0<" 0lt 2 h 4008 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4016 */
	{.type Absolute, {.p 0}},		/* dd 0 4024 */
	{.type FromH0, {.p M_less}},		/* dd M_less 4032 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4040 */
	{.type Header, {.hdr { 2, "0>", /* C_0gt = 4056 */ colon }}}, /* CENTRY "0>" 0gt 2 h 4064 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4072 */
	{.type Absolute, {.p 0}},		/* dd 0 4080 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4088 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4096 */
	{.type Header, {.hdr { 2, "<>", /* C_neq = 4112 */ colon }}}, /* CENTRY "<>" neq 2 h 4120 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal 4128 */
	{.type FromH0, {.p C_invert}},		/* dd C_invert 4136 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4144 */
	{.type Header, {.hdr { 3, "0<>", /* C_0neq = 4160 */ colon }}}, /* CENTRY "0<>" 0neq 3 h 4168 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4176 */
	{.type Absolute, {.p 0}},		/* dd 0 4184 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 4192 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4200 */
	{.type Header, {.hdr { 3, "max", /* C_max = 4216 */ colon }}}, /* CENTRY "max" max 3 h 4224 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 4232 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4240 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4248 */
	{.type FromH0, {.p L40}},		/* dd L40 4256 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 4264 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4272 */
	{.type FromH0, {.p L41}},		/* dd L41 4280 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 4288 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4296 */
	{.type Header, {.hdr { 3, "min", /* C_min = 4312 */ colon }}}, /* CENTRY "min" min 3 h 4320 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 4328 */
	{.type FromH0, {.p M_less}},		/* dd M_less 4336 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4344 */
	{.type FromH0, {.p L43}},		/* dd L43 4352 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 4360 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4368 */
	{.type FromH0, {.p L44}},		/* dd L44 4376 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 4384 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4392 */
	{.type Header, {.hdr { 6, "signum", /* C_signum = 4408 */ colon }}}, /* CENTRY "signum" signum 6 h 4416 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 4424 */
	{.type FromH0, {.p C_0gt}},		/* dd C_0gt 4432 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4440 */
	{.type FromH0, {.p L46}},		/* dd L46 4448 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 4456 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4464 */
	{.type Absolute, {.p 1}},		/* dd 1 4472 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4480 */
	{.type FromH0, {.p L47}},		/* dd L47 4488 */
	{.type FromH0, {.p C_0lt}},		/* dd C_0lt 4496 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4504 */
	{.type FromH0, {.p L48}},		/* dd L48 4512 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4520 */
	{.type Absolute, {.p -1}},		/* dd -1 4528 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4536 */
	{.type FromH0, {.p L49}},		/* dd L49 4544 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4552 */
	{.type Absolute, {.p 0}},		/* dd 0 4560 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4568 */
	{.type Header, {.hdr { 6, "within", /* C_within = 4584 */ colon }}}, /* CENTRY "within" within 6 h 4592 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 4600 */
	{.type FromH0, {.p M_over}},		/* dd M_over 4608 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4616 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 4624 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 4632 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 4640 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4648 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 4656 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 4664 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4672 */
	{.type Header, {.hdr { 3, "abs", /* C_abs = 4688 */ colon }}}, /* CENTRY "abs" abs 3 h 4696 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 4704 */
	{.type FromH0, {.p C_0lt}},		/* dd C_0lt 4712 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4720 */
	{.type FromH0, {.p L52}},		/* dd L52 4728 */
	{.type FromH0, {.p C_negate}},		/* dd C_negate 4736 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4744 */
	{.type Header, {.hdr { 3, "key", /* C_key = 4760 */ colon }}}, /* CENTRY "key" key 3 ; ( -- c ) (G read a single character from the input onto the stack ) h 4768 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4776 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( 1 -- ) 4784 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf to store the character read 4792 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 4800 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; ( 1 Iobuf -- 1 Iobuf infd ) 4808 */
	{.type FromH0, {.p M_fthread}},		/* dd M_fthread	; ( 1 Iobuf infd -- n ) 4816 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 4824 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump		; if 0 characters read 4832 */
	{.type FromH0, {.p L78}},		/* dd L78			; if qread n != 0 jump to L78. If n == 0 jump over 4840 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 4848 */
	{.type FromH0, {.p C_on}},		/* dd C_on		; EOF 4856 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4864 */
	{.type Absolute, {.p -1}},		/* dd -1			; return -1 when EOF 4872 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4880 */
	{.type FromH0, {.p L79}},		/* dd L79 4888 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; get the character from Iobuf to stack 4896 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch	; ( -- c ) return the character read if not EOF 4904 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4912 */
	{.type Header, {.hdr { 4, "emit", /* C_emit = 4928 */ colon }}}, /* CENTRY "emit" emit 4 ; ( character -- ) h 4936 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf address 4944 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; variable iobuf has character 4952 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf address 4960 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4968 */
	{.type Absolute, {.p 1}},		/* dd 1 4976 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap		; ( iobuf 1 --  1 iobuf ) 4984 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 4992 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; outfd 5000 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite	; ( 1 iobuf outfd --  ) 5008 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5016 */
	{.type Header, {.hdr { 4, "type", /* C_type = 5032 */ colon }}}, /* CENTRY "type" type 4 ; ( addr n -- ) h 5040 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap			; ( addr n --  n addr ) 5048 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5056 */
	{.type Absolute, {.p 1}},		/* dd 1				; stdout 5064 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite			; ( n addr 1 --  ) 5072 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5080 */
	{.type Header, {.hdr { 2, "cr", /* C_cr = 5096 */ colon }}}, /* CENTRY "cr" cr 2 h 5104 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5112 */
	{.type Absolute, {.p 10}},		/* dd 10			; ascii value of carriage return 5120 */
	{.type FromH0, {.p C_emit}},		/* dd C_emit			; emit 5128 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5136 */
	{.type Header, {.hdr { 5, "space", /* C_space = 5152 */ colon }}}, /* CENTRY "space" space 5 h 5160 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 5168 */
	{.type FromH0, {.p C_emit}},		/* dd C_emit 5176 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5184 */
	{.type Header, {.hdr { 5, "emits", /* C_emits = 5200 */ colon }}}, /* CENTRY "emits" emits 5 h 5208 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 5216 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 5224 */
	{.type FromH0, {.p L86}},		/* dd L86 5232 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5240 */
	{.type FromH0, {.p C_emit}},		/* dd C_emit 5248 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 5256 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 5264 */
	{.type FromH0, {.p L85}},		/* dd L85 5272 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 5280 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5288 */
	{.type Header, {.hdr { 6, "spaces", /* C_spaces = 5304 */ colon }}}, /* CENTRY "spaces" spaces 6 h 5312 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 5320 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 5328 */
	{.type FromH0, {.p C_emits}},		/* dd C_emits 5336 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5344 */
	{.type Header, {.hdr { 5, "count", /* C_count = 5360 */ colon }}}, /* CENTRY "count" count 5 ; ( a -- a+1 n ) a = counted string h 5368 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 5376 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 5384 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 5392 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 5400 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5408 */
	{.type Header, {.hdr { 7, "compare", /* C_compare = 5424 */ colon }}}, /* CENTRY "compare" compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search h 5432 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 5440 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 ) 5448 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- ) 5456 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- ) 5464 */
	{.type FromH0, {.p C_min}},		/* dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- ) 5472 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5480 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- ) 5488 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- ) 5496 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5504 */
	{.type FromH0, {.p M_i}},		/* dd M_i 5512 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 5520 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 5528 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5536 */
	{.type FromH0, {.p M_i}},		/* dd M_i 5544 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 5552 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 5560 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 5568 */
	{.type FromH0, {.p C_signum}},		/* dd C_signum 5576 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 5584 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 5592 */
	{.type FromH0, {.p L56}},		/* dd L56 5600 */
	{.type FromH0, {.p C_2nip}},		/* dd C_2nip 5608 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop 5616 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop 5624 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5632 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 5640 */
	{.type FromH0, {.p L55}},		/* dd L55 5648 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- ) 5656 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 5664 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( n2 n1 -- ) (R -- ) 5672 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( -- n1-n2 ) 5680 */
	{.type FromH0, {.p C_signum}},		/* dd C_signum 5688 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5696 */
	{.type Header, {.hdr { 5, "erase", /* C_erase = 5712 */ colon }}}, /* CENTRY "erase" erase 5 h 5720 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5728 */
	{.type Absolute, {.p 0}},		/* dd 0 5736 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 5744 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5752 */
	{.type Absolute, {.p 0}},		/* dd 0 5760 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5768 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 5776 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 5784 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 5792 */
	{.type FromH0, {.p L58}},		/* dd L58 5800 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 5808 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5816 */
	{.type Header, {.hdr { 4, "fill", /* C_fill = 5832 */ colon }}}, /* CENTRY "fill" fill 4 h 5840 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 5848 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5856 */
	{.type Absolute, {.p 0}},		/* dd 0 5864 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 5872 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 5880 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 5888 */
	{.type FromH0, {.p M_i}},		/* dd M_i 5896 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 5904 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 5912 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 5920 */
	{.type FromH0, {.p L60}},		/* dd L60 5928 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop 5936 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5944 */
	{.type Header, {.hdr { 5, "blank", /* C_blank = 5960 */ colon }}}, /* CENTRY "blank" blank 5 h 5968 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 5976 */
	{.type FromH0, {.p C_fill}},		/* dd C_fill 5984 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5992 */
	{.type Header, {.hdr { 6, "search", /* C_search = 6008 */ colon }}}, /* CENTRY "search" search 6 h 6016 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6024 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6032 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6040 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 6048 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 6056 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6064 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6072 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 6080 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 6088 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6096 */
	{.type Absolute, {.p 0}},		/* dd 0 6104 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 6112 */
	{.type FromH0, {.p M_over}},		/* dd M_over 6120 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6128 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6136 */
	{.type FromH0, {.p M_over}},		/* dd M_over 6144 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6152 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6160 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6168 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6176 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6184 */
	{.type FromH0, {.p C_compare}},		/* dd C_compare 6192 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 6200 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 6208 */
	{.type FromH0, {.p L65}},		/* dd L65 6216 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 6224 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6232 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6240 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6248 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop 6256 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 6264 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6272 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 6280 */
	{.type FromH0, {.p C_true}},		/* dd C_true 6288 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6296 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 6304 */
	{.type FromH0, {.p L64}},		/* dd L64 6312 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 6320 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 6328 */
	{.type FromH0, {.p C_false}},		/* dd C_false 6336 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6344 */
	{.type Header, {.hdr { 4, "here", /* C_here = 6360 */ colon }}}, /* CENTRY "here" here 4 h 6368 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6376 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6384 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6392 */
	{.type Header, {.hdr { 1, ",", /* C_comma = 6408 */ colon }}}, /* CENTRY "," comma 1 h 6416 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6424 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6432 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6440 */
	{.type Absolute, {.p 8}},		/* dd 8 6448 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6456 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore 6464 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6472 */
	{.type Header, {.hdr { 2, "c,", /* C_c = 6488 */ colon }}}, /* CENTRY "c," c 2 h 6496 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6504 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 6512 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6520 */
	{.type Absolute, {.p 1}},		/* dd 1 6528 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6536 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore 6544 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6552 */
	{.type Header, {.hdr { 5, "allot", /* C_allot = 6568 */ colon }}}, /* CENTRY "allot" allot 5 h 6576 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6584 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore 6592 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6600 */
	{.type Header, {.hdr { 3, "pad", /* C_pad = 6616 */ colon }}}, /* CENTRY "pad" pad 3 h 6624 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6632 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6640 */
	{.type Absolute, {.p 256}},		/* dd 256 6648 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6656 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6664 */
	{.type Header, {.hdr { 5, "align", /* C_align = 6680 */ colon }}}, /* CENTRY "align" align 5 h 6688 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6696 */
	{.type FromH0, {.p C_aligned}},		/* dd C_aligned 6704 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6712 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6720 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6728 */
	{.type Header, {.hdr { 6, "unused", /* C_unused = 6744 */ colon }}}, /* CENTRY "unused" unused 6 h 6752 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6760 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6768 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6776 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 6784 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6792 */
	{.type Header, {.hdr { 2, "<#", /* C_fromhash = 6808 */ colon }}}, /* CENTRY "<#" fromhash 2 h 6816 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 6824 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6832 */
	{.type Absolute, {.p 1024}},		/* dd 1024 6840 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6848 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 6856 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6864 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6872 */
	{.type Header, {.hdr { 1, "#", /* C_hash = 6888 */ colon }}}, /* CENTRY "#" hash 1 h 6896 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 6904 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6912 */
	{.type FromH0, {.p M_uslashmod}},		/* dd M_uslashmod 6920 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6928 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 6936 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6944 */
	{.type Absolute, {.p 9}},		/* dd 9 6952 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 6960 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 6968 */
	{.type FromH0, {.p L92}},		/* dd L92 6976 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6984 */
	{.type Absolute, {.p 97}},		/* dd 97 6992 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7000 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7008 */
	{.type Absolute, {.p 10}},		/* dd 10 7016 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 7024 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 7032 */
	{.type FromH0, {.p L93}},		/* dd L93 7040 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7048 */
	{.type Absolute, {.p 48}},		/* dd 48 7056 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7064 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7072 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7080 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 7088 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7096 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7104 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7112 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 7120 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7128 */
	{.type Header, {.hdr { 2, "#s", /* C_hashs = 7144 */ colon }}}, /* CENTRY "#s" hashs 2 h 7152 */
	{.type FromH0, {.p C_hash}},		/* dd C_hash 7160 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7168 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 7176 */
	{.type FromH0, {.p L96}},		/* dd L96 7184 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 7192 */
	{.type FromH0, {.p L95}},		/* dd L95 7200 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7208 */
	{.type Header, {.hdr { 2, "#>", /* C_hashfrom = 7224 */ colon }}}, /* CENTRY "#>" hashfrom 2 h 7232 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 7240 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7248 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7256 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7264 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 7272 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7280 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7288 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7296 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7304 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 7312 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7320 */
	{.type Header, {.hdr { 4, "hold", /* C_hold = 7336 */ colon }}}, /* CENTRY "hold" hold 4 h 7344 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7352 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7360 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 7368 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7376 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 7384 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 7392 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 7400 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7408 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7416 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7424 */
	{.type Header, {.hdr { 4, "sign", /* C_sign = 7440 */ colon }}}, /* CENTRY "sign" sign 4 h 7448 */
	{.type FromH0, {.p C_0lt}},		/* dd C_0lt 7456 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 7464 */
	{.type FromH0, {.p L100}},		/* dd L100 7472 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7480 */
	{.type Absolute, {.p 45}},		/* dd 45 7488 */
	{.type FromH0, {.p C_hold}},		/* dd C_hold 7496 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7504 */
	{.type Header, {.hdr { 1, ".", /* C_dot = 7520 */ colon }}}, /* CENTRY "." dot 1 h 7528 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7536 */
	{.type FromH0, {.p C_abs}},		/* dd C_abs 7544 */
	{.type FromH0, {.p C_fromhash}},		/* dd C_fromhash 7552 */
	{.type FromH0, {.p C_hashs}},		/* dd C_hashs 7560 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7568 */
	{.type FromH0, {.p C_sign}},		/* dd C_sign 7576 */
	{.type FromH0, {.p C_hashfrom}},		/* dd C_hashfrom 7584 */
	{.type FromH0, {.p C_type}},		/* dd C_type 7592 */
	{.type FromH0, {.p C_space}},		/* dd C_space 7600 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7608 */
	{.type Header, {.hdr { 2, ".r", /* C_dotr = 7624 */ colon }}}, /* CENTRY ".r" dotr 2 h 7632 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 7640 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7648 */
	{.type FromH0, {.p C_abs}},		/* dd C_abs 7656 */
	{.type FromH0, {.p C_fromhash}},		/* dd C_fromhash 7664 */
	{.type FromH0, {.p C_hashs}},		/* dd C_hashs 7672 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7680 */
	{.type FromH0, {.p C_sign}},		/* dd C_sign 7688 */
	{.type FromH0, {.p C_hashfrom}},		/* dd C_hashfrom 7696 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 7704 */
	{.type FromH0, {.p M_over}},		/* dd M_over 7712 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 7720 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7728 */
	{.type Absolute, {.p 0}},		/* dd 0 7736 */
	{.type FromH0, {.p C_max}},		/* dd C_max 7744 */
	{.type FromH0, {.p C_spaces}},		/* dd C_spaces 7752 */
	{.type FromH0, {.p C_type}},		/* dd C_type 7760 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7768 */
	{.type Header, {.hdr { 3, "hex", /* C_hex = 7784 */ colon }}}, /* CENTRY "hex" hex 3 h 7792 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7800 */
	{.type Absolute, {.p 16}},		/* dd 16 7808 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 7816 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7824 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7832 */
	{.type Header, {.hdr { 7, "decimal", /* C_decimal = 7848 */ colon }}}, /* CENTRY "decimal" decimal 7 h 7856 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7864 */
	{.type Absolute, {.p 10}},		/* dd 10 7872 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 7880 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7888 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7896 */
	{.type Header, {.hdr { 5, "digit", /* C_digit = 7912 */ colon }}}, /* CENTRY "digit" digit 5 h 7920 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7928 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7936 */
	{.type Absolute, {.p 65}},		/* dd 65 7944 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7952 */
	{.type Absolute, {.p 91}},		/* dd 91 7960 */
	{.type FromH0, {.p C_within}},		/* dd C_within 7968 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 7976 */
	{.type FromH0, {.p L106}},		/* dd L106 7984 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7992 */
	{.type Absolute, {.p 55}},		/* dd 55 8000 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 8008 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8016 */
	{.type FromH0, {.p L107}},		/* dd L107 8024 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8032 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8040 */
	{.type Absolute, {.p 97}},		/* dd 97 8048 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8056 */
	{.type Absolute, {.p 123}},		/* dd 123 8064 */
	{.type FromH0, {.p C_within}},		/* dd C_within 8072 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8080 */
	{.type FromH0, {.p L108}},		/* dd L108 8088 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8096 */
	{.type Absolute, {.p 87}},		/* dd 87 8104 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 8112 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8120 */
	{.type FromH0, {.p L109}},		/* dd L109 8128 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8136 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8144 */
	{.type Absolute, {.p 48}},		/* dd 48 8152 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8160 */
	{.type Absolute, {.p 58}},		/* dd 58 8168 */
	{.type FromH0, {.p C_within}},		/* dd C_within 8176 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8184 */
	{.type FromH0, {.p L110}},		/* dd L110 8192 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8200 */
	{.type Absolute, {.p 48}},		/* dd 48 8208 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 8216 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8224 */
	{.type FromH0, {.p L111}},		/* dd L111 8232 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8240 */
	{.type FromH0, {.p C_false}},		/* dd C_false 8248 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8256 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8264 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 8272 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8280 */
	{.type FromH0, {.p M_less}},		/* dd M_less 8288 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8296 */
	{.type FromH0, {.p L112}},		/* dd L112 8304 */
	{.type FromH0, {.p C_true}},		/* dd C_true 8312 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8320 */
	{.type FromH0, {.p L113}},		/* dd L113 8328 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8336 */
	{.type FromH0, {.p C_false}},		/* dd C_false 8344 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8352 */
	{.type Header, {.hdr { 6, "number", /* C_number = 8368 */ colon }}}, /* CENTRY "number" number 6 h 8376 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 8384 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8392 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 8400 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8408 */
	{.type Absolute, {.p 45}},		/* dd 45 8416 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal 8424 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8432 */
	{.type FromH0, {.p L115}},		/* dd L115 8440 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 8448 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 8456 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 8464 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8472 */
	{.type Absolute, {.p -1}},		/* dd -1 8480 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 8488 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8496 */
	{.type FromH0, {.p L116}},		/* dd L116 8504 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 8512 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8520 */
	{.type Absolute, {.p 1}},		/* dd 1 8528 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 8536 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8544 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 8552 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8560 */
	{.type Absolute, {.p 0}},		/* dd 0 8568 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 8576 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8584 */
	{.type Absolute, {.p 0}},		/* dd 0 8592 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 8600 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 8608 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8616 */
	{.type FromH0, {.p M_multiply}},		/* dd M_multiply 8624 */
	{.type FromH0, {.p M_over}},		/* dd M_over 8632 */
	{.type FromH0, {.p M_i}},		/* dd M_i 8640 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 8648 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 8656 */
	{.type FromH0, {.p C_digit}},		/* dd C_digit 8664 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8672 */
	{.type FromH0, {.p L118}},		/* dd L118 8680 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 8688 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8696 */
	{.type FromH0, {.p L119}},		/* dd L119 8704 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8712 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop 8720 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8728 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8736 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8744 */
	{.type FromH0, {.p C_false}},		/* dd C_false 8752 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8760 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 8768 */
	{.type FromH0, {.p L117}},		/* dd L117 8776 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8784 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8792 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 8800 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8808 */
	{.type FromH0, {.p M_multiply}},		/* dd M_multiply 8816 */
	{.type FromH0, {.p C_true}},		/* dd C_true 8824 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8832 */
	{.type Header, {.hdr { 5, "abort", /* C_abort = 8848 */ colon }}}, /* CENTRY "abort" abort 5 h 8856 */
	{.type FromH0, {.p MV_Abortvec}},		/* dd MV_Abortvec 8864 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8872 */
	{.type FromH0, {.p M_execute}},		/* dd M_execute 8880 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8888 */
	{.type Header, {.hdr { 6, "source", /* C_source = 8904 */ colon }}}, /* CENTRY "source" source 6 h 8912 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 8920 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8928 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8936 */
	{.type Header, {.hdr { 13, "current-input", /* C_current_input = 8960 */ colon }}}, /* CENTRY "current-input" current_input 13 ; ( -- c ) read the next character from the location in Sourcebuf h 8968 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 8976 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8984 */
	{.type FromH0, {.p C_source}},		/* dd C_source 8992 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus		; Sourcebuf + >In 9000 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 9008 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9016 */
	{.type Header, {.hdr { 10, "save-input", /* C_save_input = 9040 */ colon }}}, /* CENTRY "save-input" save_input 10 h 9048 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 9056 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9064 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9072 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9080 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9088 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9096 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9104 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 9112 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9120 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9128 */
	{.type Absolute, {.p 5}},		/* dd 5 9136 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9144 */
	{.type Header, {.hdr { 13, "default-input", /* C_default_input = 9168 */ colon }}}, /* CENTRY "default-input" default_input 13 h 9176 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 9184 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9192 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9200 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9208 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9216 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib 9224 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9232 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9240 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 9248 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9256 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9264 */
	{.type Header, {.hdr { 13, "restore-input", /* C_restore_input = 9288 */ colon }}}, /* CENTRY "restore-input" restore_input 13 h 9296 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 9304 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9312 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9320 */
	{.type Absolute, {.p 5}},		/* dd 5 9328 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 9336 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9344 */
	{.type FromH0, {.p L133}},		/* dd L133 9352 */
	{.type FromH0, {.p C_default_input}},		/* dd C_default_input 9360 */
	{.type FromH0, {.p C_false}},		/* dd C_false 9368 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 9376 */
	{.type FromH0, {.p L134}},		/* dd L134 9384 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 9392 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9400 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9408 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9416 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9424 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9432 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9440 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9448 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 9456 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9464 */
	{.type FromH0, {.p C_true}},		/* dd C_true 9472 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9480 */
	{.type Header, {.hdr { 14, "?restore-input", /* C_qrestore_input = 9504 */ colon }}}, /* CENTRY "?restore-input" qrestore_input 14 h 9512 */
	{.type FromH0, {.p C_restore_input}},		/* dd C_restore_input 9520 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 9528 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9536 */
	{.type FromH0, {.p L136}},		/* dd L136 9544 */
	{.type FromH0, {.p C_space}},		/* dd C_space 9552 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9560 */
	{.type FromH0, {.p L137}},		/* dd L137 9568 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9576 */
	{.type Absolute, {.p 23}},		/* dd 23 9584 */
	{.type FromH0, {.p C_type}},		/* dd C_type 9592 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 9600 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 9608 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9616 */
	{.type Header, {.hdr { 10, "next-input", /* C_next_input = 9640 */ colon }}}, /* CENTRY "next-input" next_input 10 ; when >In < >Limit ( -- true c ). ( -- 0 false ) otherwise h 9648 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9656 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9664 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9672 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9680 */
	{.type FromH0, {.p M_less}},		/* dd M_less 9688 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9696 */
	{.type FromH0, {.p L139}},		/* dd L139	; >In >= >Limit 9704 */
	{.type FromH0, {.p C_true}},		/* dd C_true	; >In < >Limit 9712 */
	{.type FromH0, {.p C_current_input}},		/* dd C_current_input	; ( -- c ) 9720 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 9728 */
	{.type FromH0, {.p L140}},		/* dd L140 9736 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9744 */
	{.type Absolute, {.p 0}},		/* dd 0 9752 */
	{.type FromH0, {.p C_false}},		/* dd C_false 9760 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9768 */
	{.type Header, {.hdr { 5, "parse", /* C_parse = 9784 */ colon }}}, /* CENTRY "parse" parse 5 ; ( c -- a ) Place the counted string in the address in Wordbuf and return that address. c = word delimiter. h 9792 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush		; ( c -- ) (R -- c ) 9800 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf 9808 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; ( -- Wordb ) 9816 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus		; ( Wordb -- Wordb+1 ) 9824 */
	{.type FromH0, {.p C_next_input}},		/* dd C_next_input ; ( Wordb+1 -- Wordb+1 f c ) 9832 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c ) 9840 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) ) 9848 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 9856 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9864 */
	{.type FromH0, {.p L143}},		/* dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew 9872 */
	{.type FromH0, {.p C_current_input}},		/* dd C_current_input	; ( Wordb+1 -- Wordb+1 c ) 9880 */
	{.type FromH0, {.p M_over}},		/* dd M_over 9888 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1 9896 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus		; ( Wordb+1 -- Wordb+2 ) 9904 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9912 */
	{.type Absolute, {.p 1}},		/* dd 1 9920 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9928 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; >In++ 9936 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 9944 */
	{.type FromH0, {.p L142}},		/* dd L142		; ( Wordb+2 ) repeat 9952 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9960 */
	{.type Absolute, {.p 1}},		/* dd 1 9968 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9976 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; >In++ 9984 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- ) 9992 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; (Wordb+1 c -- Wordb+1) 10000 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf 10008 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb) 10016 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb) 10024 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb) 10032 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb) 10040 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb) 10048 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb) 10056 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now. 10064 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop		; ( -- Wordb) (R Wordb -- ) 10072 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10080 */
	{.type Header, {.hdr { 4, "word", /* C_word = 10096 */ colon }}}, /* CENTRY "word" word 4 ; ( c -- a ) skip the c"s. Placed the counted string in a (as in Wordbuf) h 10104 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( -- ) (R -- c ) 10112 */
	{.type FromH0, {.p C_next_input}},		/* dd C_next_input ; ( -- f c2 ) (R c1 -- ) 10120 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial ) 10128 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial ) 10136 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial ) 10144 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10152 */
	{.type FromH0, {.p L146}},		/* dd L146		; >In >= >Limit || cinitial != cnew 10160 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal	; >In < >Limit && cinitial == cnew 10168 */
	{.type Absolute, {.p 1}},		/* dd 1 10176 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 10184 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; >In++ 10192 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump		; repeat 10200 */
	{.type FromH0, {.p L145}},		/* dd L145 10208 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character 10216 */
	{.type FromH0, {.p C_parse}},		/* dd C_parse 10224 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10232 */
	{.type Header, {.hdr { 6, "accept", /* C_accept = 10248 */ colon }}}, /* CENTRY "accept" accept 6 ; ( a n -- n ) get line or n chars or EOF from input and store at a h 10256 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap	; ( n a -- ) 10264 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n a a -- ) 10272 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 10280 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( n -- ) (R a a -- ) 10288 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup	; ( n n -- ) (R a a -- ) 10296 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump	; (if) 10304 */
	{.type FromH0, {.p L149}},		/* dd L149	; n == 0 10312 */
	{.type FromH0, {.p C_key}},		/* dd C_key	; n > 0 ( n -- n c ) 10320 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( -- n c c ) 10328 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10336 */
	{.type Absolute, {.p 10}},		/* dd 10		; ( -- n c c 10 ) 10344 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( n c c 10 -- n c f ) checking for newline 10352 */
	{.type FromH0, {.p M_over}},		/* dd M_over	; ( -- n c f c ) 10360 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10368 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( -- n c f c -1 ) 10376 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( -- n c f1 f2 ) 10384 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor	; ( -- n c f ) 10392 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10400 */
	{.type FromH0, {.p L150}},		/* dd L150 10408 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop	; n == -1 || n == 10 (	-- ) 10416 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 10424 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 10432 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( -- a2-a1 ) 10440 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon	; ( -- n ) (R -- ) 10448 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch	; ( n c a -- ) (R a a -- ) 10456 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; store the character at a 10464 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( n a -- ) (R a -- ) 10472 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 10480 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address 10488 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus	; ( n -- n-1 ) 10496 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10504 */
	{.type FromH0, {.p L148}},		/* dd L148	; loop again for the next character 10512 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 ) 10520 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( a2 a1 -- ) (R a1 -- ) 10528 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( a2 a1 -- a2-a1 ) 10536 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10544 */
	{.type Header, {.hdr { 5, "query", /* C_query = 10560 */ colon }}}, /* CENTRY "query" query 5 ; read from input stream into the Text Input Buffer h 10568 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 10576 */
	{.type FromH0, {.p C_off}},		/* dd C_off		; clear EOF flag 10584 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib	; constant puts address of tibuffer on the top 10592 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10600 */
	{.type Absolute, {.p 4096}},		/* dd 4096	; ( tibuffer -- tibuffer 4096 ) 10608 */
	{.type FromH0, {.p C_accept}},		/* dd C_accept ; ( tibuffer 4096 -- n ) 10616 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n -- n n ) 10624 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq	; ( n n -- n f ) 10632 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 10640 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 10648 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; n == 0 && EOF 10656 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10664 */
	{.type FromH0, {.p L152}},		/* dd L152		; false condition 10672 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; n == 0 && EOF ( n -- ) 10680 */
	{.type FromH0, {.p C_qrestore_input}},		/* dd C_qrestore_input 10688 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10696 */
	{.type FromH0, {.p L153}},		/* dd L153 10704 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 10712 */
	{.type FromH0, {.p M_store}},		/* dd M_store		; number of characters to read >Limit = n 10720 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 10728 */
	{.type FromH0, {.p C_off}},		/* dd C_off		; start from 0 >In = 0 10736 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10744 */
	{.type Header, {.hdr { 6, "refill", /* C_refill = 10760 */ colon }}}, /* CENTRY "refill" refill 6 h 10768 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 10776 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 10784 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10792 */
	{.type FromH0, {.p L155}},		/* dd L155 10800 */
	{.type FromH0, {.p C_false}},		/* dd C_false 10808 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10816 */
	{.type FromH0, {.p L156}},		/* dd L156 10824 */
	{.type FromH0, {.p C_query}},		/* dd C_query 10832 */
	{.type FromH0, {.p C_true}},		/* dd C_true 10840 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10848 */
	{.type Header, {.hdr { 8, "findname", /* C_findname = 10872 */ colon }}}, /* CENTRY "findname" findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names h 10880 */
	{.type FromH0, {.p MV_Findadr}},		/* dd MV_Findadr 10888 */
	{.type FromH0, {.p M_store}},		/* dd M_store 10896 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 10904 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; get dictionary link 10912 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 10920 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10928 */
	{.type FromH0, {.p L159}},		/* dd L159	; seached until the first dictionary entry get out 10936 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( a -- a a ) 10944 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus	; lenth + initial name address 10952 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch	; length + initial name 10960 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10968 */
	{.type Absolute, {.p 64}},		/* dd 64		; max name length? 10976 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; keep only the length 10984 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10992 */
	{.type FromH0, {.p L160}},		/* dd L160 11000 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 11008 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11016 */
	{.type FromH0, {.p L161}},		/* dd L161 11024 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 11032 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 11040 */
	{.type FromH0, {.p C_count}},		/* dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n ) 11048 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11056 */
	{.type Absolute, {.p 63}},		/* dd 63 11064 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63 ) 11072 */
	{.type FromH0, {.p MV_Findadr}},		/* dd MV_Findadr 11080 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 11088 */
	{.type FromH0, {.p C_count}},		/* dd C_count	; ( a1 a1+8+1 n&63 a2 n2 -- a1 a1+8+1 n&63 a2+1 n2 ) 11096 */
	{.type FromH0, {.p C_compare}},		/* dd C_compare	; ( -- a1 n ) compare dictionary entry with name 11104 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq	; found a match? 11112 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11120 */
	{.type FromH0, {.p L162}},		/* dd L162 11128 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 11136 */
	{.type FromH0, {.p C_true}},		/* dd C_true 11144 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11152 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 11160 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11168 */
	{.type FromH0, {.p L158}},		/* dd L158 11176 */
	{.type FromH0, {.p MV_Findadr}},		/* dd MV_Findadr 11184 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 11192 */
	{.type FromH0, {.p C_false}},		/* dd C_false 11200 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11208 */
	{.type Header, {.hdr { 4, "find", /* C_find = 11224 */ colon }}}, /* CENTRY "find" find 4 ; ( a1 -- a2 f )? h 11232 */
	{.type FromH0, {.p C_findname}},		/* dd C_findname 11240 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11248 */
	{.type FromH0, {.p L164}},		/* dd L164 11256 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 11264 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 11272 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 11280 */
	{.type FromH0, {.p M_over}},		/* dd M_over 11288 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11296 */
	{.type Absolute, {.p 63}},		/* dd 63 11304 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 11312 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 11320 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 11328 */
	{.type FromH0, {.p C_aligned}},		/* dd C_aligned 11336 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 11344 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11352 */
	{.type Absolute, {.p 128}},		/* dd 128 11360 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 11368 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11376 */
	{.type FromH0, {.p L165}},		/* dd L165 11384 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11392 */
	{.type Absolute, {.p 1}},		/* dd 1 11400 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11408 */
	{.type FromH0, {.p L166}},		/* dd L166 11416 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11424 */
	{.type Absolute, {.p -1}},		/* dd -1 11432 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11440 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11448 */
	{.type FromH0, {.p L167}},		/* dd L167 11456 */
	{.type FromH0, {.p C_false}},		/* dd C_false 11464 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11472 */
	{.type Header, {.hdr { 1, "'", /* C_single_quote = 11488 */ colon }}}, /* CENTRY "'" single_quote 1 h 11496 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 11504 */
	{.type FromH0, {.p C_word}},		/* dd C_word 11512 */
	{.type FromH0, {.p C_find}},		/* dd C_find 11520 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 11528 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11536 */
	{.type FromH0, {.p L169}},		/* dd L169 11544 */
	{.type FromH0, {.p C_space}},		/* dd C_space 11552 */
	{.type FromH0, {.p C_count}},		/* dd C_count 11560 */
	{.type FromH0, {.p C_type}},		/* dd C_type 11568 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11576 */
	{.type FromH0, {.p L170}},		/* dd L170 11584 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11592 */
	{.type Absolute, {.p 3}},		/* dd 3 11600 */
	{.type FromH0, {.p C_type}},		/* dd C_type 11608 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 11616 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 11624 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11632 */
	{.type Header, {.hdr { 6, "?stack", /* C_qstack = 11648 */ colon }}}, /* CENTRY "?stack" qstack 6 h 11656 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr 11664 */
	{.type FromH0, {.p M_S0}},		/* dd M_S0 11672 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 11680 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11688 */
	{.type FromH0, {.p L172}},		/* dd L172 11696 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11704 */
	{.type FromH0, {.p L173}},		/* dd L173 11712 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11720 */
	{.type Absolute, {.p 16}},		/* dd 16 11728 */
	{.type FromH0, {.p C_type}},		/* dd C_type 11736 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 11744 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 11752 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11760 */
	{.type Header, {.hdr { 9, "interpret", /* C_interpret = 11784 */ colon }}}, /* CENTRY "interpret" interpret 9 ; there is stuff in TIB to be interpreted >In and >Limit are set h 11792 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 11800 */
	{.type FromH0, {.p C_word}},		/* dd C_word	; ( bl -- a ) 11808 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 11816 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 11824 */
	{.type FromH0, {.p C_0neq}},		/* dd C_0neq 11832 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11840 */
	{.type FromH0, {.p L176}},		/* dd L176	; count at a = 0 11848 */
	{.type FromH0, {.p C_find}},		/* dd C_find	; ( a -- ) a = address of counted string 11856 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11864 */
	{.type FromH0, {.p L177}},		/* dd L177 11872 */
	{.type FromH0, {.p M_execute}},		/* dd M_execute 11880 */
	{.type FromH0, {.p C_qstack}},		/* dd C_qstack 11888 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11896 */
	{.type FromH0, {.p L178}},		/* dd L178 11904 */
	{.type FromH0, {.p C_count}},		/* dd C_count 11912 */
	{.type FromH0, {.p C_number}},		/* dd C_number 11920 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 11928 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11936 */
	{.type FromH0, {.p L179}},		/* dd L179 11944 */
	{.type FromH0, {.p C_space}},		/* dd C_space 11952 */
	{.type FromH0, {.p C_type}},		/* dd C_type 11960 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11968 */
	{.type FromH0, {.p L180}},		/* dd L180	; error I? 11976 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11984 */
	{.type Absolute, {.p 3}},		/* dd 3 11992 */
	{.type FromH0, {.p C_type}},		/* dd C_type 12000 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 12008 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 12016 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 12024 */
	{.type FromH0, {.p L175}},		/* dd L175 12032 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop	; count at a = 0 ( a -- ) 12040 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12048 */
	{.type Header, {.hdr { 6, "create", /* C_create = 12064 */ colon }}}, /* CENTRY "create" create 6 h 12072 */
	{.type FromH0, {.p C_align}},		/* dd C_align 12080 */
	{.type FromH0, {.p C_here}},		/* dd C_here 12088 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 12096 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 12104 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12112 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12120 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 12128 */
	{.type FromH0, {.p C_word}},		/* dd C_word 12136 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12144 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 12152 */
	{.type FromH0, {.p C_here}},		/* dd C_here 12160 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 12168 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 12176 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12184 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 12192 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 12200 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 12208 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 12216 */
	{.type FromH0, {.p C_align}},		/* dd C_align 12224 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12232 */
	{.type FromH0, {.p M_variable}},		/* dd M_variable 12240 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12248 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12256 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 12264 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 12272 */
	{.type FromH0, {.p M_store}},		/* dd M_store 12280 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12288 */
	{.type Header, {.hdr { 8, "variable", /* C_variable = 12312 */ colon }}}, /* CENTRY "variable" variable 8 h 12320 */
	{.type FromH0, {.p C_create}},		/* dd C_create 12328 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12336 */
	{.type Absolute, {.p 0}},		/* dd 0 12344 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12352 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12360 */
	{.type Header, {.hdr { 8, "constant", /* C_constant = 12384 */ colon }}}, /* CENTRY "constant" constant 8 h 12392 */
	{.type FromH0, {.p C_create}},		/* dd C_create 12400 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12408 */
	{.type FromH0, {.p M_constant}},		/* dd M_constant 12416 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12424 */
	{.type FromH0, {.p C_here}},		/* dd C_here 12432 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12440 */
	{.type Absolute, {.p 1}},		/* dd 1 12448 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 12456 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 12464 */
	{.type FromH0, {.p M_store}},		/* dd M_store 12472 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12480 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12488 */
	{.type Header, {.hdr { 9, "immediate", /* C_immediate = 12512 */ colon }}}, /* CENTRY "immediate" immediate 9 h 12520 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 12528 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12536 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 12544 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12552 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 12560 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12568 */
	{.type Absolute, {.p 128}},		/* dd 128 12576 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 12584 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 12592 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 12600 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12608 */
	{.type Header, {.hdr { 4, ">cfa", /* C_tocfa = 12624 */ colon }}}, /* CENTRY ">cfa" tocfa 4 h 12632 */
	{.type FromH0, {.p C_count}},		/* dd C_count 12640 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12648 */
	{.type Absolute, {.p 63}},		/* dd 63 12656 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 12664 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 12672 */
	{.type FromH0, {.p C_aligned}},		/* dd C_aligned 12680 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12688 */
	{.type Header, {.hdr { 7, "compile", /* C_compile = 12704 */ colon }}}, /* CENTRY "compile" compile 7 h 12712 */
	{.type FromH0, {.p C_findname}},		/* dd C_findname 12720 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12728 */
	{.type FromH0, {.p L188}},		/* dd L188 12736 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12744 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 12752 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12760 */
	{.type Absolute, {.p 128}},		/* dd 128 12768 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 12776 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12784 */
	{.type FromH0, {.p L189}},		/* dd L189 12792 */
	{.type FromH0, {.p C_tocfa}},		/* dd C_tocfa	; immediate 12800 */
	{.type FromH0, {.p M_execute}},		/* dd M_execute 12808 */
	{.type FromH0, {.p C_qstack}},		/* dd C_qstack 12816 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 12824 */
	{.type FromH0, {.p L190}},		/* dd L190 12832 */
	{.type FromH0, {.p C_tocfa}},		/* dd C_tocfa 12840 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12848 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 12856 */
	{.type FromH0, {.p L191}},		/* dd L191 12864 */
	{.type FromH0, {.p C_count}},		/* dd C_count 12872 */
	{.type FromH0, {.p C_number}},		/* dd C_number 12880 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 12888 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12896 */
	{.type FromH0, {.p L192}},		/* dd L192 12904 */
	{.type FromH0, {.p C_space}},		/* dd C_space 12912 */
	{.type FromH0, {.p C_type}},		/* dd C_type 12920 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12928 */
	{.type FromH0, {.p L193}},		/* dd L193 12936 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12944 */
	{.type Absolute, {.p 3}},		/* dd 3 12952 */
	{.type FromH0, {.p C_type}},		/* dd C_type 12960 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 12968 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 12976 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 12984 */
	{.type FromH0, {.p L194}},		/* dd L194 12992 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13000 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13008 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13016 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13024 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13032 */
	{.type Header, {.hdr { 1, "]", /* C_close_bracket = 13048 */ colon }}}, /* CENTRY "]" close_bracket 1 h 13056 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13064 */
	{.type FromH0, {.p C_on}},		/* dd C_on 13072 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 13080 */
	{.type FromH0, {.p C_word}},		/* dd C_word 13088 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13096 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13104 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 13112 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 13120 */
	{.type FromH0, {.p L197}},		/* dd L197 13128 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 13136 */
	{.type FromH0, {.p C_refill}},		/* dd C_refill 13144 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13152 */
	{.type FromH0, {.p L198}},		/* dd L198 13160 */
	{.type FromH0, {.p C_compile}},		/* dd C_compile 13168 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13176 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13184 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 13192 */
	{.type FromH0, {.p L199}},		/* dd L199 13200 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13208 */
	{.type FromH0, {.p L196}},		/* dd L196 13216 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13224 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13232 */
	{.type FromH0, {.p C_off}},		/* dd C_off 13240 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13248 */
	{.type Header, {.hdr { 6, "smudge", /* C_smudge = 13264 */ colon }}}, /* CENTRY "smudge" smudge 6 h 13272 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 13280 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13288 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 13296 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13304 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13312 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13320 */
	{.type Absolute, {.p 64}},		/* dd 64 13328 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 13336 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 13344 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 13352 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13360 */
	{.type Header, {.hdr { 6, "reveal", /* C_reveal = 13376 */ colon }}}, /* CENTRY "reveal" reveal 6 h 13384 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 13392 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13400 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 13408 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13416 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13424 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13432 */
	{.type Absolute, {.p 64}},		/* dd 64 13440 */
	{.type FromH0, {.p C_invert}},		/* dd C_invert 13448 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 13456 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 13464 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 13472 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13480 */
	{.type Header, {.hdr { 1, ":", /* C_colon = 13496 */ colon }}}, /* CENTRY ":" colon 1 h 13504 */
	{.type FromH0, {.p C_create}},		/* dd C_create 13512 */
	{.type FromH0, {.p C_smudge}},		/* dd C_smudge 13520 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13528 */
	{.type FromH0, {.p M_colon}},		/* dd M_colon 13536 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13544 */
	{.type FromH0, {.p C_here}},		/* dd C_here 13552 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13560 */
	{.type Absolute, {.p 1}},		/* dd 1 13568 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 13576 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 13584 */
	{.type FromH0, {.p M_store}},		/* dd M_store 13592 */
	{.type FromH0, {.p C_close_bracket}},		/* dd C_close_bracket 13600 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13608 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13616 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13624 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13632 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13640 */
	{.type FromH0, {.p C_off}},		/* dd C_off 13648 */
	{.type FromH0, {.p C_reveal}},		/* dd C_reveal 13656 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13664 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 13672 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13680 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 13688 */
	{.type FromH0, {.p C_tocfa}},		/* dd C_tocfa 13696 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13704 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13712 */
	{.type Header, {.hdr { 4, "char", /* C_L206 = 13728 */ colon }}}, /* CENTRY "char" L206 4 h 13736 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 13744 */
	{.type FromH0, {.p C_word}},		/* dd C_word 13752 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 13760 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13768 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13776 */
	{.type Header, {.hdr { 7, "literal", /* C_literal = 13792 */ colon }}}, /* CENTRY "literal" literal 7 h 13800 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13808 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13816 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13824 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13832 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13840 */
	{.type Header, {.hdr { 8, "sliteral", /* C_sliteral = 13864 */ colon }}}, /* CENTRY "sliteral" sliteral 8 h 13872 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13880 */
	{.type FromH0, {.p M_sliteral}},		/* dd M_sliteral 13888 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13896 */
	{.type FromH0, {.p C_here}},		/* dd C_here 13904 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13912 */
	{.type Absolute, {.p 34}},		/* dd 34 13920 */
	{.type FromH0, {.p C_parse}},		/* dd C_parse 13928 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13936 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13944 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 13952 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 13960 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 13968 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 13976 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 13984 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 13992 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 14000 */
	{.type FromH0, {.p C_align}},		/* dd C_align 14008 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14016 */
	{.type Header, {.hdr { 6, "string", /* C_string = 14032 */ colon }}}, /* CENTRY "string" string 6 h 14040 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14048 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 14056 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14064 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14072 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 14080 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14088 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 14096 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 14104 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 14112 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 14120 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14128 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 14136 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14144 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14152 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14160 */
	{.type FromH0, {.p C_literal}},		/* dd C_literal 14168 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14176 */
	{.type FromH0, {.p C_single_quote}},		/* dd C_single_quote 14184 */
	{.type FromH0, {.p C_literal}},		/* dd C_literal 14192 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14200 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14208 */
	{.type Absolute, {.p 41}},		/* dd 41 14216 */
	{.type FromH0, {.p C_parse}},		/* dd C_parse 14224 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 14232 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14240 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 14248 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14256 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 14264 */
	{.type FromH0, {.p L214}},		/* dd L214 14272 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 14280 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14288 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14296 */
	{.type Absolute, {.p 63}},		/* dd 63 14304 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 14312 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14320 */
	{.type Absolute, {.p 63}},		/* dd 63 14328 */
	{.type FromH0, {.p C_invert}},		/* dd C_invert 14336 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 14344 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 14352 */
	{.type FromH0, {.p M_store}},		/* dd M_store 14360 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 14368 */
	{.type FromH0, {.p L215}},		/* dd L215 14376 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 14384 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14392 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 14400 */
	{.type FromH0, {.p M_store}},		/* dd M_store 14408 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14416 */
	{.type Header, {.hdr { 8, "(?abort)", /* C_qabort_parens = 14440 */ colon }}}, /* CENTRY "(?abort)" qabort_parens 8 h 14448 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 14456 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 14464 */
	{.type FromH0, {.p L217}},		/* dd L217 14472 */
	{.type FromH0, {.p C_space}},		/* dd C_space 14480 */
	{.type FromH0, {.p C_type}},		/* dd C_type 14488 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 14496 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 14504 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 14512 */
	{.type FromH0, {.p L218}},		/* dd L218 14520 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop 14528 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14536 */
	{.type FromH0, {.p C_sliteral}},		/* dd C_sliteral 14544 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14552 */
	{.type FromH0, {.p C_qabort_parens}},		/* dd C_qabort_parens 14560 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14568 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14576 */
	{.type Header, {.hdr { 1, "\"", /* C_double_quote = 14592 */ colon }}}, /* CENTRY "\"" double_quote 1 h 14600 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14608 */
	{.type Absolute, {.p 34}},		/* dd 34 14616 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14624 */
	{.type FromH0, {.p C_count}},		/* dd C_count 14632 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 14640 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14648 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 14656 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 14664 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14672 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 14680 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 14688 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 14696 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14704 */
	{.type Header, {.hdr { 2, "c\"", /* C_cdouble_quote = 14720 */ colon }}}, /* CENTRY "c\"" cdouble_quote 2 h 14728 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14736 */
	{.type Absolute, {.p 34}},		/* dd 34 14744 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14752 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 14760 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14768 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14776 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 14784 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14792 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 14800 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 14808 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14816 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 14824 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 14832 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14840 */
	{.type FromH0, {.p C_sliteral}},		/* dd C_sliteral 14848 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14856 */
	{.type FromH0, {.p C_sliteral}},		/* dd C_sliteral 14864 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14872 */
	{.type FromH0, {.p C_type}},		/* dd C_type 14880 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14888 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14896 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14904 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 14912 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14920 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14928 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14936 */
	{.type Absolute, {.p 0}},		/* dd 0 14944 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14952 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14960 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14968 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 14976 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14984 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14992 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 15000 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15008 */
	{.type Absolute, {.p 0}},		/* dd 0 15016 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15024 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15032 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15040 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15048 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 15056 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15064 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15072 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15080 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15088 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15096 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15104 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15112 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15120 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 15128 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15136 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15144 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15152 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15160 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15168 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15176 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15184 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15192 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15200 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15208 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15216 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15224 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15232 */
	{.type Absolute, {.p 0}},		/* dd 0 15240 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15248 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15256 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15264 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 15272 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15280 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15288 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15296 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15304 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15312 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15320 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15328 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15336 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 15344 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15352 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15360 */
	{.type Absolute, {.p 0}},		/* dd 0 15368 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15376 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15384 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15392 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 15400 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15408 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15416 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 15424 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15432 */
	{.type FromH0, {.p L234}},		/* dd L234 15440 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15448 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15456 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15464 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15472 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15480 */
	{.type FromH0, {.p M_doploop}},		/* dd M_doploop 15488 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15496 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15504 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 15512 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15520 */
	{.type FromH0, {.p L236}},		/* dd L236 15528 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15536 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15544 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15552 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15560 */
	{.type Header, {.hdr { 3, "w/o", /* C_wo = 15576 */ colon }}}, /* CENTRY "w/o" wo 3 h 15584 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15592 */
	{.type Absolute, {.p 1}},		/* dd 1 15600 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15608 */
	{.type Absolute, {.p 512}},		/* dd 512 15616 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 15624 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15632 */
	{.type Absolute, {.p 64}},		/* dd 64 15640 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 15648 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15656 */
	{.type Header, {.hdr { 3, "r/o", /* C_ro = 15672 */ colon }}}, /* CENTRY "r/o" ro 3 h 15680 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15688 */
	{.type Absolute, {.p 0}},		/* dd 0 15696 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15704 */
	{.type Header, {.hdr { 3, "r/w", /* C_rw = 15720 */ colon }}}, /* CENTRY "r/w" rw 3 h 15728 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15736 */
	{.type Absolute, {.p 2}},		/* dd 2 15744 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15752 */
	{.type Header, {.hdr { 9, "open-file", /* C_open_file = 15776 */ colon }}}, /* CENTRY "open-file" open_file 9 h 15784 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 15792 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 15800 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15808 */
	{.type Absolute, {.p 1024}},		/* dd 1024 15816 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 15824 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15832 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 15840 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 15848 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 15856 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15864 */
	{.type Absolute, {.p 0}},		/* dd 0 15872 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 15880 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 15888 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 15896 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15904 */
	{.type Absolute, {.p 1024}},		/* dd 1024 15912 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 15920 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 15928 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 15936 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15944 */
	{.type Absolute, {.p 1024}},		/* dd 1024 15952 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 15960 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 15968 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15976 */
	{.type Absolute, {.p 420}},		/* dd 420 15984 */
	{.type FromH0, {.p M_fthopen}},		/* dd M_fthopen 15992 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 16000 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16008 */
	{.type Absolute, {.p -1}},		/* dd -1 16016 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 16024 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16032 */
	{.type Header, {.hdr { 10, "close-file", /* C_close_file = 16056 */ colon }}}, /* CENTRY "close-file" close_file 10 h 16064 */
	{.type FromH0, {.p M_fthclose}},		/* dd M_fthclose 16072 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 16080 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16088 */
	{.type Header, {.hdr { 9, "read-file", /* C_read_file = 16112 */ colon }}}, /* CENTRY "read-file" read_file 9 h 16120 */
	{.type FromH0, {.p M_fthread}},		/* dd M_fthread 16128 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 16136 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16144 */
	{.type Absolute, {.p -1}},		/* dd -1 16152 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 16160 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16168 */
	{.type Header, {.hdr { 10, "write-file", /* C_write_file = 16192 */ colon }}}, /* CENTRY "write-file" write_file 10 h 16200 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite 16208 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16216 */
	{.type Absolute, {.p -1}},		/* dd -1 16224 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 16232 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16240 */
	{.type Header, {.hdr { 15, "reposition-file", /* C_reposition_file = 16264 */ colon }}}, /* CENTRY "reposition-file" reposition_file 15 h 16272 */
	{.type FromH0, {.p M_fthseek}},		/* dd M_fthseek 16280 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16288 */
	{.type Absolute, {.p -1}},		/* dd -1 16296 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 16304 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16312 */
	{.type Header, {.hdr { 7, "?fcheck", /* C_qfcheck = 16328 */ colon }}}, /* CENTRY "?fcheck" qfcheck 7 h 16336 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 16344 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 16352 */
	{.type FromH0, {.p L246}},		/* dd L246 16360 */
	{.type FromH0, {.p C_space}},		/* dd C_space 16368 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16376 */
	{.type FromH0, {.p L247}},		/* dd L247 16384 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16392 */
	{.type Absolute, {.p 9}},		/* dd 9 16400 */
	{.type FromH0, {.p C_type}},		/* dd C_type 16408 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 16416 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 16424 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16432 */
	{.type Header, {.hdr { 3, "bye", /* C_bye = 16448 */ colon }}}, /* CENTRY "bye" bye 3 h 16456 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16464 */
	{.type Absolute, {.p 0}},		/* dd 0 16472 */
	{.type FromH0, {.p M_terminate}},		/* dd M_terminate 16480 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16488 */
	{.type Header, {.hdr { 7, "include", /* C_include = 16504 */ colon }}}, /* CENTRY "include" include 7 h 16512 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 16520 */
	{.type FromH0, {.p C_word}},		/* dd C_word 16528 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 16536 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 16544 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 16552 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 16560 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16568 */
	{.type FromH0, {.p C_save_input}},		/* dd C_save_input 16576 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 16584 */
	{.type FromH0, {.p C_count}},		/* dd C_count 16592 */
	{.type FromH0, {.p C_ro}},		/* dd C_ro 16600 */
	{.type FromH0, {.p C_open_file}},		/* dd C_open_file 16608 */
	{.type FromH0, {.p C_qfcheck}},		/* dd C_qfcheck 16616 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 16624 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16632 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16640 */
	{.type Header, {.hdr { 5, "crash", /* C_crash = 16656 */ colon }}}, /* CENTRY "crash" crash 5 h 16664 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16672 */
	{.type FromH0, {.p L251}},		/* dd L251 16680 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16688 */
	{.type Absolute, {.p 30}},		/* dd 30 16696 */
	{.type FromH0, {.p C_type}},		/* dd C_type 16704 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 16712 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 16720 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16728 */
	{.type Header, {.hdr { 4, "quit", /* C_quit = 16744 */ colon }}}, /* CENTRY "quit" quit 4 ; interpreter loop h 16752 */
	{.type FromH0, {.p M_reset}},		/* dd M_reset ; initialize return stack 16760 */
	{.type FromH0, {.p M_clear}},		/* dd M_clear	; SP = sstack_end initialize data stack 16768 */
	{.type FromH0, {.p C_query}},		/* dd C_query 16776 */
	{.type FromH0, {.p C_interpret}},		/* dd C_interpret 16784 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 16792 */
	{.type FromH0, {.p L253}},		/* dd L253 16800 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon	; why is this needed? 16808 */
	{.type Header, {.hdr { 7, "(abort)", /* C_parenabort = 16824 */ colon }}}, /* CENTRY "(abort)" parenabort 7 ; TODO correct below stack notations h 16832 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State	; ( mv_State -- ) 16840 */
	{.type FromH0, {.p C_off}},		/* dd C_off		; off sets variable state = 0 16848 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 16856 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 16864 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 16872 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk	; variable blk 16880 */
	{.type FromH0, {.p C_off}},		/* dd C_off	; off variable blk = 0 16888 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 16896 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 16904 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16912 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 16920 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 16928 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16936 */
	{.type FromH0, {.p MC_STDERR}},		/* dd MC_STDERR 16944 */
	{.type FromH0, {.p MV_Errfd}},		/* dd MV_Errfd 16952 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16960 */
	{.type FromH0, {.p C_quit}},		/* dd C_quit	; quit resets stacks and is the interpreter loop 16968 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon	; why is this needed? quit does not return unless it breaks 16976 */
	{.type Header, {.hdr { 7, "oldboot", /* C_oldboot = 16992 */ colon }}}, /* CENTRY "oldboot" oldboot 7 ; TODO correct below stack notations and this is obsolete. leaving it here for reference until it all works well h 17000 */
	{.type FromH0, {.p M_reset}},		/* dd M_reset 17008 */
	{.type FromH0, {.p M_clear}},		/* dd M_clear	; SP = sstack_end 17016 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr	; (D -- FFEND) 17024 */
	{.type FromH0, {.p M_S0}},		/* dd M_S0 17032 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; s0 = FFEND 17040 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0	; heaptop = heapend 17048 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; ( heapend -- ) 17056 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17064 */
	{.type Absolute, {.p 1}},		/* dd 1		; ( heapend 1 -- ) 17072 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells	; cells ( heapend 8 -- ) 17080 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( heapend-8 -- ) 17088 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; ( contents_from_heapend-8 -- ) 17096 */
	{.type FromH0, {.p M_Args}},		/* dd M_Args	; variable args 17104 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; args = contents_from_heapend-8 17112 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17120 */
	{.type FromH0, {.p C_parenabort}},		/* dd C_parenabort ; ( (abort) -- ) 17128 */
	{.type FromH0, {.p MV_Abortvec}},		/* dd MV_Abortvec	; variable abortvec 17136 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable abortvec = (abort) code address 17144 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb	; constant puts address of wordbuffer on the top of stack 17152 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf	; variable wordbuf 17160 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable wordbuf = address of wordbuffer 17168 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 17176 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 17184 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 17192 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17200 */
	{.type Absolute, {.p 0}},		/* dd 0 17208 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 17216 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; stdin = 0 17224 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17232 */
	{.type Absolute, {.p 1}},		/* dd 1 17240 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 17248 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; stdout = 1 17256 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 17264 */
	{.type FromH0, {.p C_off}},		/* dd C_off	; off stores 0 at state 17272 */
	{.type FromH0, {.p C_decimal}},		/* dd C_decimal	; decimal setting base = 0 17280 */
	{.type FromH0, {.p C_quit}},		/* dd C_quit	; quit 17288 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17296 */
	{.type Header, {.hdr { 4, "boot", /* C_boot = 17312 */ colon }}}, /* CENTRY "boot" boot 4 h 17320 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal	; this is not working TEST 17328 */
	{.type Absolute, {.p 66}},		/* dd 66 17336 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb 17344 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17352 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17360 */
	{.type Absolute, {.p 1}},		/* dd 1 17368 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb 17376 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 17384 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite 17392 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17400 */
	{.type Absolute, {.p 1}},		/* dd 1 17408 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb 17416 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 17424 */
	{.type FromH0, {.p M_fthread}},		/* dd M_fthread	; this is not working TODO 17432 */
	{.type FromH0, {.p M_reset}},		/* dd M_reset ; initialize return stack 17440 */
	{.type FromH0, {.p M_clear}},		/* dd M_clear	; SP = sstack_end initialize data stack 17448 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17456 */
	{.type FromH0, {.p C_parenabort}},		/* dd C_parenabort ; ( (abort) -- ) 17464 */
	{.type FromH0, {.p MV_Abortvec}},		/* dd MV_Abortvec	; variable that puts (abort) code address on the stack 17472 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable abortvec = (abort) code address 17480 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb	; variable puts address of wordbuffer on the top of stack 17488 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf ; variable wordbuf 17496 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable wordbuf = address of wordbuffer 17504 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 17512 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 17520 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 17528 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 17536 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 17544 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; stdin = 0 17552 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 17560 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 17568 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17576 */
	{.type FromH0, {.p MC_STDERR}},		/* dd MC_STDERR 17584 */
	{.type FromH0, {.p MV_Errfd}},		/* dd MV_Errfd 17592 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17600 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 17608 */
	{.type FromH0, {.p C_off}},		/* dd C_off	; off stores 0 at state 17616 */
	{.type FromH0, {.p C_decimal}},		/* dd C_decimal	; decimal setting base = 0 17624 */
	{.type FromH0, {.p C_quit}},		/* dd C_quit	; quit 17632 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17640 */
	{.type Chars, {.str "unable to restore input"}},		/* 17664 */
	{.type Chars, {.str " Q?"}},		/* 17668 */
	{.type Chars, {.str " stack underflow"}},		/* 17685 */
	{.type Chars, {.str " I?"}},		/* 17689 */
	{.type Chars, {.str " C?"}},		/* 17693 */
	{.type Chars, {.str "I/O error"}},		/* 17703 */
	{.type Chars, {.str "uninitialized execution vector"}},		/* 17734 */
	{.type Chars, {.str " ok"}},		/* 17738 */
};

