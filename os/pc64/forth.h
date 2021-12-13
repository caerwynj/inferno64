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
	MV_Abortvec = 1600,
	MV_Infd = 1632,
	MV_Outfd = 1664,
	MV_Errfd = 1696,
	MV_Eof = 1728,
	MC_STDIN = 1760,
	MC_STDOUT = 1792,
	MC_STDERR = 1824,
	MC_WORDB = 1856,
	MC_TIB = 1888,
	M_S0 = 1920,
	M_stackptr = 1944,
	M_H0 = 1968,
	M_Args = 1992,
	M_variable = 2024,
	M_constant = 2056,
	M_colon = 2080,
	M_dodoes = 2104,
	M_cas = 2128,
	M_deferred = 2160,
	C_false = 2184,
	C_true = 2232,
	C_bl = 2280,
	C_on = 2328,
	C_off = 2392,
	C_tobody = 2456,
	C_aligned = 2512,
	C_cells = 2592,
	C_cellplus = 2648,
	C_depth = 2712,
	C_nip = 2816,
	C_rot = 2864,
	C_2drop = 2928,
	C_2dup = 2976,
	C_2nip = 3024,
	C_2swap = 3072,
	C_qdup = 3136,
	L20 = 3208,
	C_pick = 3232,
	L22 = 3336,
	L23 = 3344,
	C_tuck = 3368,
	C_divides = 3432,
	C_plusstore = 3480,
	C_invert = 3560,
	C_mod = 3616,
	C_1plus = 3664,
	C_1minus = 3720,
	C_negate = 3776,
	C_2multiplies = 3840,
	C_2divides = 3896,
	C_0eq = 3952,
	C_0lt = 4008,
	C_0gt = 4064,
	C_neq = 4120,
	C_0neq = 4168,
	C_max = 4224,
	L40 = 4288,
	L41 = 4296,
	C_min = 4320,
	L43 = 4384,
	L44 = 4392,
	C_signum = 4416,
	L46 = 4496,
	L48 = 4552,
	L49 = 4568,
	L47 = 4568,
	C_within = 4592,
	C_abs = 4696,
	L52 = 4744,
	C_key = 4768,
	L78 = 4896,
	L79 = 4912,
	C_emit = 4936,
	C_type = 5040,
	C_cr = 5104,
	C_space = 5160,
	C_emits = 5208,
	L85 = 5216,
	L86 = 5280,
	C_spaces = 5312,
	C_count = 5368,
	C_compare = 5432,
	L55 = 5504,
	L56 = 5640,
	C_erase = 5720,
	L58 = 5752,
	C_fill = 5840,
	L60 = 5880,
	C_blank = 5968,
	C_search = 6016,
	L64 = 6120,
	L65 = 6304,
	C_here = 6368,
	C_comma = 6416,
	C_c = 6496,
	C_allot = 6576,
	C_pad = 6624,
	C_align = 6688,
	C_unused = 6752,
	C_fromhash = 6816,
	C_hash = 6896,
	L92 = 7048,
	L93 = 7072,
	C_hashs = 7152,
	L95 = 7160,
	L96 = 7208,
	C_hashfrom = 7232,
	C_hold = 7344,
	C_sign = 7448,
	L100 = 7504,
	C_dot = 7528,
	C_dotr = 7632,
	C_hex = 7792,
	C_decimal = 7856,
	C_digit = 7920,
	L106 = 8032,
	L108 = 8136,
	L110 = 8240,
	L111 = 8264,
	L109 = 8264,
	L107 = 8264,
	L112 = 8336,
	L113 = 8352,
	C_number = 8376,
	L115 = 8512,
	L116 = 8544,
	L117 = 8608,
	L118 = 8712,
	L119 = 8768,
	C_abort = 8856,
	C_source = 8912,
	C_current_input = 8968,
	C_save_input = 9048,
	C_default_input = 9176,
	C_restore_input = 9296,
	L133 = 9392,
	L134 = 9480,
	C_qrestore_input = 9512,
	L136 = 9616,
	C_next_input = 9648,
	L139 = 9744,
	L140 = 9768,
	C_parse = 9792,
	L142 = 9832,
	L143 = 9960,
	C_word = 10104,
	L145 = 10120,
	L146 = 10216,
	C_accept = 10256,
	L148 = 10296,
	L150 = 10456,
	L149 = 10520,
	C_query = 10568,
	L152 = 10712,
	L153 = 10744,
	C_refill = 10768,
	L155 = 10832,
	L156 = 10848,
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
	C_variable = 12304,
	C_constant = 12368,
	C_immediate = 12496,
	C_tocfa = 12608,
	C_compile = 12688,
	L189 = 12816,
	L190 = 12832,
	L188 = 12848,
	L192 = 12976,
	L194 = 13008,
	L191 = 13008,
	C_close_bracket = 13032,
	L196 = 13056,
	L197 = 13144,
	L198 = 13168,
	L199 = 13200,
	C_smudge = 13248,
	C_reveal = 13360,
	C_colon = 13480,
	C_L206 = 13712,
	C_literal = 13776,
	C_sliteral = 13840,
	C_string = 14008,
	L214 = 14352,
	L215 = 14384,
	C_qabort_parens = 14408,
	L217 = 14488,
	L218 = 14496,
	C_double_quote = 14560,
	C_cdouble_quote = 14688,
	L234 = 15432,
	L236 = 15520,
	C_wo = 15544,
	C_ro = 15640,
	C_rw = 15688,
	C_open_file = 15744,
	C_close_file = 16024,
	C_read_file = 16080,
	C_write_file = 16160,
	C_reposition_file = 16232,
	C_qfcheck = 16296,
	L246 = 16392,
	C_bye = 16416,
	C_include = 16472,
	C_crash = 16624,
	C_quit = 16712,
	L253 = 16736,
	C_parenabort = 16792,
	C_oldboot = 16960,
	C_boot = 17280,
	L137 = 17608,
	L170 = 17632,
	L173 = 17636,
	L180 = 17653,
	L193 = 17657,
	L247 = 17661,
	L251 = 17671,
	L255 = 17702,
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
extern void *store(void);
extern void *cmove(void);
extern void *binor(void);
extern void *fthclose(void);
extern void *unloop(void);
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
	{.type Header, {.hdr { 8, "Abortvec", /* MV_Abortvec = 1600 */ variable }}}, /* MVENTRY "Abortvec" Abortvec 0 8	; not sure if these 3 can be constants instead? h 1608 */
	{.type Absolute, {.p 0}},		/* 1616 */
	{.type Header, {.hdr { 5, "Infd", /* MV_Infd = 1632 */ variable }}}, /* MVENTRY "Infd" Infd 0 5 h 1640 */
	{.type Absolute, {.p 0}},		/* 1648 */
	{.type Header, {.hdr { 6, "Outfd", /* MV_Outfd = 1664 */ variable }}}, /* MVENTRY "Outfd" Outfd 0 6 h 1672 */
	{.type Absolute, {.p 0}},		/* 1680 */
	{.type Header, {.hdr { 4, "Errfd", /* MV_Errfd = 1696 */ variable }}}, /* MVENTRY "Errfd" Errfd 0 4 h 1704 */
	{.type Absolute, {.p 0}},		/* 1712 */
	{.type Header, {.hdr { 3, "Eof", /* MV_Eof = 1728 */ variable }}}, /* MVENTRY "Eof" Eof 0 3 h 1736 */
	{.type Absolute, {.p 0}},		/* 1744 */
	{.type Header, {.hdr { 5, "STDIN", /* MC_STDIN = 1760 */ constant }}}, /* MCENTRY "STDIN" STDIN 0 5		; 3 constants from here CAPITALS h 1768 */
	{.type Absolute, {.p 0}},		/* 1776 */
	{.type Header, {.hdr { 6, "STDOUT", /* MC_STDOUT = 1792 */ constant }}}, /* MCENTRY "STDOUT" STDOUT 1 6 h 1800 */
	{.type Absolute, {.p 1}},		/* 1808 */
	{.type Header, {.hdr { 6, "STDERR", /* MC_STDERR = 1824 */ constant }}}, /* MCENTRY "STDERR" STDERR 2 6 h 1832 */
	{.type Absolute, {.p 2}},		/* 1840 */
	{.type Header, {.hdr { 5, "WORDB", /* MC_WORDB = 1856 */ constant }}}, /* MCENTRY "WORDB" WORDB WORDB 5 h 1864 */
	{.type Absolute, {.p WORDB}},		/* 1872 */
	{.type Header, {.hdr { 3, "TIB", /* MC_TIB = 1888 */ constant }}}, /* MCENTRY "TIB" TIB TIB 3 h 1896 */
	{.type Absolute, {.p TIB}},		/* 1904 */
	{.type Header, {.hdr { 2, "S0", /* M_S0 = 1920 */ S0 }}}, /* MENTRY "S0" S0 2 h 1928 */
	{.type Header, {.hdr { 2, "s@", /* M_stackptr = 1944 */ stackptr }}}, /* MENTRY "s@" stackptr 2		; puts PSP on stack h 1952 */
	{.type Header, {.hdr { 2, "H0", /* M_H0 = 1968 */ H0 }}}, /* MENTRY "H0" H0 2 h 1976 */
	{.type Header, {.hdr { 3, "Args", /* M_Args = 1992 */ Args }}}, /* MENTRY "Args" Args 3 h 2000 */
	{.type Header, {.hdr { 10, "(variable)", /* M_variable = 2024 */ variable }}}, /* MENTRY "(variable)" variable 10 h 2032 */
	{.type Header, {.hdr { 10, "(constant)", /* M_constant = 2056 */ constant }}}, /* MENTRY "(constant)" constant 10 h 2064 */
	{.type Header, {.hdr { 3, "(:)", /* M_colon = 2080 */ colon }}}, /* MENTRY "(:)" colon 3 h 2088 */
	{.type Header, {.hdr { 6, "(does)", /* M_dodoes = 2104 */ dodoes }}}, /* MENTRY "(does)" dodoes 6 h 2112 */
	{.type Header, {.hdr { 3, "cas", /* M_cas = 2128 */ cas }}}, /* MENTRY "cas" cas 3 h 2136 */
	{.type Header, {.hdr { 10, "(deferred)", /* M_deferred = 2160 */ deferred }}}, /* MENTRY "(deferred)" deferred 10 h 2168 */
	{.type Header, {.hdr { 5, "false", /* C_false = 2184 */ colon }}}, /* CENTRY "false" false 5 h 2192 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2200 */
	{.type Absolute, {.p 0}},		/* dd 0 2208 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2216 */
	{.type Header, {.hdr { 4, "true", /* C_true = 2232 */ colon }}}, /* CENTRY "true" true 4 h 2240 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2248 */
	{.type Absolute, {.p -1}},		/* dd -1 2256 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2264 */
	{.type Header, {.hdr { 2, "bl", /* C_bl = 2280 */ colon }}}, /* CENTRY "bl" bl 2 h 2288 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2296 */
	{.type Absolute, {.p 32}},		/* dd 32 2304 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2312 */
	{.type Header, {.hdr { 2, "on", /* C_on = 2328 */ colon }}}, /* CENTRY "on" on 2 ; ( a -- ) (G stores -1 at a ) h 2336 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2344 */
	{.type Absolute, {.p -1}},		/* dd -1 2352 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2360 */
	{.type FromH0, {.p M_store}},		/* dd M_store 2368 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2376 */
	{.type Header, {.hdr { 3, "off", /* C_off = 2392 */ colon }}}, /* CENTRY "off" off 3 ; ( a -- ) (G stores 0 at a ) h 2400 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2408 */
	{.type Absolute, {.p 0}},		/* dd 0 2416 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2424 */
	{.type FromH0, {.p M_store}},		/* dd M_store 2432 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2440 */
	{.type Header, {.hdr { 5, ">body", /* C_tobody = 2456 */ colon }}}, /* CENTRY ">body" tobody 5 h 2464 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2472 */
	{.type Absolute, {.p 8}},		/* dd 8 2480 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 2488 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2496 */
	{.type Header, {.hdr { 7, "aligned", /* C_aligned = 2512 */ colon }}}, /* CENTRY "aligned" aligned 7 h 2520 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2528 */
	{.type Absolute, {.p 7}},		/* dd 7 2536 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 2544 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2552 */
	{.type Absolute, {.p -8}},		/* dd -8 2560 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 2568 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2576 */
	{.type Header, {.hdr { 5, "cells", /* C_cells = 2592 */ colon }}}, /* CENTRY "cells" cells 5 h 2600 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2608 */
	{.type Absolute, {.p 3}},		/* dd 3			; (index << 2) -> (index << 3)for amd64 2616 */
	{.type FromH0, {.p M_lshift}},		/* dd M_lshift 2624 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2632 */
	{.type Header, {.hdr { 5, "cell+", /* C_cellplus = 2648 */ colon }}}, /* CENTRY "cell+" cellplus 5 h 2656 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2664 */
	{.type Absolute, {.p 1}},		/* dd 1 2672 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 2680 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 2688 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2696 */
	{.type Header, {.hdr { 5, "depth", /* C_depth = 2712 */ colon }}}, /* CENTRY "depth" depth 5 h 2720 */
	{.type FromH0, {.p M_S0}},		/* dd M_S0 2728 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr 2736 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 2744 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2752 */
	{.type Absolute, {.p 3}},		/* dd 3 2760 */
	{.type FromH0, {.p M_rshift}},		/* dd M_rshift 2768 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2776 */
	{.type Absolute, {.p 1}},		/* dd 1 2784 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 2792 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2800 */
	{.type Header, {.hdr { 3, "nip", /* C_nip = 2816 */ colon }}}, /* CENTRY "nip" nip 3 h 2824 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2832 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 2840 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2848 */
	{.type Header, {.hdr { 3, "rot", /* C_rot = 2864 */ colon }}}, /* CENTRY "rot" rot 3 h 2872 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 2880 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2888 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 2896 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2904 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2912 */
	{.type Header, {.hdr { 5, "2drop", /* C_2drop = 2928 */ colon }}}, /* CENTRY "2drop" 2drop 5 h 2936 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 2944 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 2952 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2960 */
	{.type Header, {.hdr { 4, "2dup", /* C_2dup = 2976 */ colon }}}, /* CENTRY "2dup" 2dup 4 h 2984 */
	{.type FromH0, {.p M_over}},		/* dd M_over 2992 */
	{.type FromH0, {.p M_over}},		/* dd M_over 3000 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3008 */
	{.type Header, {.hdr { 4, "2nip", /* C_2nip = 3024 */ colon }}}, /* CENTRY "2nip" 2nip 4 h 3032 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 3040 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 3048 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3056 */
	{.type Header, {.hdr { 5, "2swap", /* C_2swap = 3072 */ colon }}}, /* CENTRY "2swap" 2swap 5 h 3080 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot 3088 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 3096 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot 3104 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 3112 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3120 */
	{.type Header, {.hdr { 4, "?dup", /* C_qdup = 3136 */ colon }}}, /* CENTRY "?dup" qdup 4 ; if (tos != 0) dup ( n -- ) TODO correct stack notations h 3144 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n n -- ) 3152 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n n n -- ) 3160 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3168 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( n n n 0 -- ) 3176 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( n n f -- ) 3184 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump	; ( n n -- ) 3192 */
	{.type FromH0, {.p L20}},		/* dd L20 3200 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop	; tos == 0 ( n -- ) 3208 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3216 */
	{.type Header, {.hdr { 4, "pick", /* C_pick = 3232 */ colon }}}, /* CENTRY "pick" pick 4 h 3240 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 3248 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 3256 */
	{.type FromH0, {.p L22}},		/* dd L22 3264 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3272 */
	{.type Absolute, {.p 1}},		/* dd 1 3280 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3288 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 3296 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr 3304 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3312 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 3320 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 3328 */
	{.type FromH0, {.p L23}},		/* dd L23 3336 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 3344 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3352 */
	{.type Header, {.hdr { 4, "tuck", /* C_tuck = 3368 */ colon }}}, /* CENTRY "tuck" tuck 4 h 3376 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 3384 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 3392 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 3400 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 3408 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3416 */
	{.type Header, {.hdr { 1, "/", /* C_divides = 3432 */ colon }}}, /* CENTRY "/" divides 1 h 3440 */
	{.type FromH0, {.p M_slashmod}},		/* dd M_slashmod 3448 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 3456 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3464 */
	{.type Header, {.hdr { 2, "+!", /* C_plusstore = 3480 */ colon }}}, /* CENTRY "+!" plusstore 2 h 3488 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 3496 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 3504 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot 3512 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3520 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 3528 */
	{.type FromH0, {.p M_store}},		/* dd M_store 3536 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3544 */
	{.type Header, {.hdr { 6, "invert", /* C_invert = 3560 */ colon }}}, /* CENTRY "invert" invert 6 h 3568 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3576 */
	{.type Absolute, {.p -1}},		/* dd -1 3584 */
	{.type FromH0, {.p M_binxor}},		/* dd M_binxor 3592 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3600 */
	{.type Header, {.hdr { 3, "mod", /* C_mod = 3616 */ colon }}}, /* CENTRY "mod" mod 3 h 3624 */
	{.type FromH0, {.p M_slashmod}},		/* dd M_slashmod 3632 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 3640 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3648 */
	{.type Header, {.hdr { 2, "1+", /* C_1plus = 3664 */ colon }}}, /* CENTRY "1+" 1plus 2 h 3672 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3680 */
	{.type Absolute, {.p 1}},		/* dd 1 3688 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3696 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3704 */
	{.type Header, {.hdr { 2, "1-", /* C_1minus = 3720 */ colon }}}, /* CENTRY "1-" 1minus 2 h 3728 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3736 */
	{.type Absolute, {.p 1}},		/* dd 1 3744 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 3752 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3760 */
	{.type Header, {.hdr { 6, "negate", /* C_negate = 3776 */ colon }}}, /* CENTRY "negate" negate 6 h 3784 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3792 */
	{.type Absolute, {.p 0}},		/* dd 0 3800 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 3808 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 3816 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3824 */
	{.type Header, {.hdr { 2, "2*", /* C_2multiplies = 3840 */ colon }}}, /* CENTRY "2*" 2multiplies 2 h 3848 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3856 */
	{.type Absolute, {.p 1}},		/* dd 1 3864 */
	{.type FromH0, {.p M_lshift}},		/* dd M_lshift 3872 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3880 */
	{.type Header, {.hdr { 2, "2/", /* C_2divides = 3896 */ colon }}}, /* CENTRY "2/" 2divides 2 h 3904 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3912 */
	{.type Absolute, {.p 1}},		/* dd 1 3920 */
	{.type FromH0, {.p M_rshifta}},		/* dd M_rshifta 3928 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3936 */
	{.type Header, {.hdr { 2, "0=", /* C_0eq = 3952 */ colon }}}, /* CENTRY "0=" 0eq 2 h 3960 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3968 */
	{.type Absolute, {.p 0}},		/* dd 0 3976 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal 3984 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3992 */
	{.type Header, {.hdr { 2, "0<", /* C_0lt = 4008 */ colon }}}, /* CENTRY "0<" 0lt 2 h 4016 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4024 */
	{.type Absolute, {.p 0}},		/* dd 0 4032 */
	{.type FromH0, {.p M_less}},		/* dd M_less 4040 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4048 */
	{.type Header, {.hdr { 2, "0>", /* C_0gt = 4064 */ colon }}}, /* CENTRY "0>" 0gt 2 h 4072 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4080 */
	{.type Absolute, {.p 0}},		/* dd 0 4088 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4096 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4104 */
	{.type Header, {.hdr { 2, "<>", /* C_neq = 4120 */ colon }}}, /* CENTRY "<>" neq 2 h 4128 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal 4136 */
	{.type FromH0, {.p C_invert}},		/* dd C_invert 4144 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4152 */
	{.type Header, {.hdr { 3, "0<>", /* C_0neq = 4168 */ colon }}}, /* CENTRY "0<>" 0neq 3 h 4176 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4184 */
	{.type Absolute, {.p 0}},		/* dd 0 4192 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 4200 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4208 */
	{.type Header, {.hdr { 3, "max", /* C_max = 4224 */ colon }}}, /* CENTRY "max" max 3 h 4232 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 4240 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4248 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4256 */
	{.type FromH0, {.p L40}},		/* dd L40 4264 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 4272 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4280 */
	{.type FromH0, {.p L41}},		/* dd L41 4288 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 4296 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4304 */
	{.type Header, {.hdr { 3, "min", /* C_min = 4320 */ colon }}}, /* CENTRY "min" min 3 h 4328 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 4336 */
	{.type FromH0, {.p M_less}},		/* dd M_less 4344 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4352 */
	{.type FromH0, {.p L43}},		/* dd L43 4360 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 4368 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4376 */
	{.type FromH0, {.p L44}},		/* dd L44 4384 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 4392 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4400 */
	{.type Header, {.hdr { 6, "signum", /* C_signum = 4416 */ colon }}}, /* CENTRY "signum" signum 6 h 4424 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 4432 */
	{.type FromH0, {.p C_0gt}},		/* dd C_0gt 4440 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4448 */
	{.type FromH0, {.p L46}},		/* dd L46 4456 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 4464 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4472 */
	{.type Absolute, {.p 1}},		/* dd 1 4480 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4488 */
	{.type FromH0, {.p L47}},		/* dd L47 4496 */
	{.type FromH0, {.p C_0lt}},		/* dd C_0lt 4504 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4512 */
	{.type FromH0, {.p L48}},		/* dd L48 4520 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4528 */
	{.type Absolute, {.p -1}},		/* dd -1 4536 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4544 */
	{.type FromH0, {.p L49}},		/* dd L49 4552 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4560 */
	{.type Absolute, {.p 0}},		/* dd 0 4568 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4576 */
	{.type Header, {.hdr { 6, "within", /* C_within = 4592 */ colon }}}, /* CENTRY "within" within 6 h 4600 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 4608 */
	{.type FromH0, {.p M_over}},		/* dd M_over 4616 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4624 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 4632 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 4640 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 4648 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4656 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 4664 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 4672 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4680 */
	{.type Header, {.hdr { 3, "abs", /* C_abs = 4696 */ colon }}}, /* CENTRY "abs" abs 3 h 4704 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 4712 */
	{.type FromH0, {.p C_0lt}},		/* dd C_0lt 4720 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4728 */
	{.type FromH0, {.p L52}},		/* dd L52 4736 */
	{.type FromH0, {.p C_negate}},		/* dd C_negate 4744 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4752 */
	{.type Header, {.hdr { 3, "key", /* C_key = 4768 */ colon }}}, /* CENTRY "key" key 3 ; ( -- c ) (G read a single character from the input onto the stack ) h 4776 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4784 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( 1 -- ) 4792 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf to store the character read 4800 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 4808 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; ( 1 Iobuf -- 1 Iobuf infd ) 4816 */
	{.type FromH0, {.p M_fthread}},		/* dd M_fthread	; ( 1 Iobuf infd -- n ) 4824 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 4832 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump		; if 0 characters read 4840 */
	{.type FromH0, {.p L78}},		/* dd L78			; if qread n != 0 jump to L78. If n == 0 jump over 4848 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 4856 */
	{.type FromH0, {.p C_on}},		/* dd C_on		; EOF 4864 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4872 */
	{.type Absolute, {.p -1}},		/* dd -1			; return -1 when EOF 4880 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4888 */
	{.type FromH0, {.p L79}},		/* dd L79 4896 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; get the character from Iobuf to stack 4904 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch	; ( -- c ) return the character read if not EOF 4912 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4920 */
	{.type Header, {.hdr { 4, "emit", /* C_emit = 4936 */ colon }}}, /* CENTRY "emit" emit 4 ; ( character -- ) h 4944 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf address 4952 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; variable iobuf has character 4960 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf address 4968 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4976 */
	{.type Absolute, {.p 1}},		/* dd 1 4984 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap		; ( iobuf 1 --  1 iobuf ) 4992 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 5000 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; outfd 5008 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite	; ( 1 iobuf outfd --  ) 5016 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5024 */
	{.type Header, {.hdr { 4, "type", /* C_type = 5040 */ colon }}}, /* CENTRY "type" type 4 ; ( addr n -- ) h 5048 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap			; ( addr n --  n addr ) 5056 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5064 */
	{.type Absolute, {.p 1}},		/* dd 1				; stdout 5072 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite			; ( n addr 1 --  ) 5080 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5088 */
	{.type Header, {.hdr { 2, "cr", /* C_cr = 5104 */ colon }}}, /* CENTRY "cr" cr 2 h 5112 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5120 */
	{.type Absolute, {.p 10}},		/* dd 10			; ascii value of carriage return 5128 */
	{.type FromH0, {.p C_emit}},		/* dd C_emit			; emit 5136 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5144 */
	{.type Header, {.hdr { 5, "space", /* C_space = 5160 */ colon }}}, /* CENTRY "space" space 5 h 5168 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 5176 */
	{.type FromH0, {.p C_emit}},		/* dd C_emit 5184 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5192 */
	{.type Header, {.hdr { 5, "emits", /* C_emits = 5208 */ colon }}}, /* CENTRY "emits" emits 5 h 5216 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 5224 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 5232 */
	{.type FromH0, {.p L86}},		/* dd L86 5240 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5248 */
	{.type FromH0, {.p C_emit}},		/* dd C_emit 5256 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 5264 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 5272 */
	{.type FromH0, {.p L85}},		/* dd L85 5280 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 5288 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5296 */
	{.type Header, {.hdr { 6, "spaces", /* C_spaces = 5312 */ colon }}}, /* CENTRY "spaces" spaces 6 h 5320 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 5328 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 5336 */
	{.type FromH0, {.p C_emits}},		/* dd C_emits 5344 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5352 */
	{.type Header, {.hdr { 5, "count", /* C_count = 5368 */ colon }}}, /* CENTRY "count" count 5 ; ( a -- a+1 n ) a = counted string h 5376 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 5384 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 5392 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 5400 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 5408 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5416 */
	{.type Header, {.hdr { 7, "compare", /* C_compare = 5432 */ colon }}}, /* CENTRY "compare" compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search h 5440 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 5448 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 ) 5456 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- ) 5464 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- ) 5472 */
	{.type FromH0, {.p C_min}},		/* dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- ) 5480 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5488 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- ) 5496 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- ) 5504 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5512 */
	{.type FromH0, {.p M_i}},		/* dd M_i 5520 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 5528 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 5536 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5544 */
	{.type FromH0, {.p M_i}},		/* dd M_i 5552 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 5560 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 5568 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 5576 */
	{.type FromH0, {.p C_signum}},		/* dd C_signum 5584 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 5592 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 5600 */
	{.type FromH0, {.p L56}},		/* dd L56 5608 */
	{.type FromH0, {.p C_2nip}},		/* dd C_2nip 5616 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop 5624 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop 5632 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5640 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 5648 */
	{.type FromH0, {.p L55}},		/* dd L55 5656 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- ) 5664 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 5672 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( n2 n1 -- ) (R -- ) 5680 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( -- n1-n2 ) 5688 */
	{.type FromH0, {.p C_signum}},		/* dd C_signum 5696 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5704 */
	{.type Header, {.hdr { 5, "erase", /* C_erase = 5720 */ colon }}}, /* CENTRY "erase" erase 5 h 5728 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5736 */
	{.type Absolute, {.p 0}},		/* dd 0 5744 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 5752 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5760 */
	{.type Absolute, {.p 0}},		/* dd 0 5768 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5776 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 5784 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 5792 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 5800 */
	{.type FromH0, {.p L58}},		/* dd L58 5808 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 5816 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5824 */
	{.type Header, {.hdr { 4, "fill", /* C_fill = 5840 */ colon }}}, /* CENTRY "fill" fill 4 h 5848 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 5856 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5864 */
	{.type Absolute, {.p 0}},		/* dd 0 5872 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 5880 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 5888 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 5896 */
	{.type FromH0, {.p M_i}},		/* dd M_i 5904 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 5912 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 5920 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 5928 */
	{.type FromH0, {.p L60}},		/* dd L60 5936 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop 5944 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5952 */
	{.type Header, {.hdr { 5, "blank", /* C_blank = 5968 */ colon }}}, /* CENTRY "blank" blank 5 h 5976 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 5984 */
	{.type FromH0, {.p C_fill}},		/* dd C_fill 5992 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6000 */
	{.type Header, {.hdr { 6, "search", /* C_search = 6016 */ colon }}}, /* CENTRY "search" search 6 h 6024 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6032 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6040 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6048 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 6056 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 6064 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6072 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6080 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 6088 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 6096 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6104 */
	{.type Absolute, {.p 0}},		/* dd 0 6112 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 6120 */
	{.type FromH0, {.p M_over}},		/* dd M_over 6128 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6136 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6144 */
	{.type FromH0, {.p M_over}},		/* dd M_over 6152 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6160 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6168 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6176 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6184 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6192 */
	{.type FromH0, {.p C_compare}},		/* dd C_compare 6200 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 6208 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 6216 */
	{.type FromH0, {.p L65}},		/* dd L65 6224 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 6232 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6240 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6248 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6256 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop 6264 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 6272 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6280 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 6288 */
	{.type FromH0, {.p C_true}},		/* dd C_true 6296 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6304 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 6312 */
	{.type FromH0, {.p L64}},		/* dd L64 6320 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 6328 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 6336 */
	{.type FromH0, {.p C_false}},		/* dd C_false 6344 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6352 */
	{.type Header, {.hdr { 4, "here", /* C_here = 6368 */ colon }}}, /* CENTRY "here" here 4 h 6376 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6384 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6392 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6400 */
	{.type Header, {.hdr { 1, ",", /* C_comma = 6416 */ colon }}}, /* CENTRY "," comma 1 h 6424 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6432 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6440 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6448 */
	{.type Absolute, {.p 8}},		/* dd 8 6456 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6464 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore 6472 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6480 */
	{.type Header, {.hdr { 2, "c", /* C_c = 6496 */ colon }}}, /* CENTRY "c" c 2 h 6504 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6512 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 6520 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6528 */
	{.type Absolute, {.p 1}},		/* dd 1 6536 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6544 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore 6552 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6560 */
	{.type Header, {.hdr { 5, "allot", /* C_allot = 6576 */ colon }}}, /* CENTRY "allot" allot 5 h 6584 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6592 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore 6600 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6608 */
	{.type Header, {.hdr { 3, "pad", /* C_pad = 6624 */ colon }}}, /* CENTRY "pad" pad 3 h 6632 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6640 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6648 */
	{.type Absolute, {.p 256}},		/* dd 256 6656 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6664 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6672 */
	{.type Header, {.hdr { 5, "align", /* C_align = 6688 */ colon }}}, /* CENTRY "align" align 5 h 6696 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6704 */
	{.type FromH0, {.p C_aligned}},		/* dd C_aligned 6712 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6720 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6728 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6736 */
	{.type Header, {.hdr { 6, "unused", /* C_unused = 6752 */ colon }}}, /* CENTRY "unused" unused 6 h 6760 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6768 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6776 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6784 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 6792 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6800 */
	{.type Header, {.hdr { 2, "<#", /* C_fromhash = 6816 */ colon }}}, /* CENTRY "<#" fromhash 2 h 6824 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 6832 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6840 */
	{.type Absolute, {.p 1024}},		/* dd 1024 6848 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6856 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 6864 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6872 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6880 */
	{.type Header, {.hdr { 1, "#", /* C_hash = 6896 */ colon }}}, /* CENTRY "#" hash 1 h 6904 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 6912 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6920 */
	{.type FromH0, {.p M_uslashmod}},		/* dd M_uslashmod 6928 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6936 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 6944 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6952 */
	{.type Absolute, {.p 9}},		/* dd 9 6960 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 6968 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 6976 */
	{.type FromH0, {.p L92}},		/* dd L92 6984 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6992 */
	{.type Absolute, {.p 97}},		/* dd 97 7000 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7008 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7016 */
	{.type Absolute, {.p 10}},		/* dd 10 7024 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 7032 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 7040 */
	{.type FromH0, {.p L93}},		/* dd L93 7048 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7056 */
	{.type Absolute, {.p 48}},		/* dd 48 7064 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7072 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7080 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7088 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 7096 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7104 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7112 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7120 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 7128 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7136 */
	{.type Header, {.hdr { 2, "#s", /* C_hashs = 7152 */ colon }}}, /* CENTRY "#s" hashs 2 h 7160 */
	{.type FromH0, {.p C_hash}},		/* dd C_hash 7168 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7176 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 7184 */
	{.type FromH0, {.p L96}},		/* dd L96 7192 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 7200 */
	{.type FromH0, {.p L95}},		/* dd L95 7208 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7216 */
	{.type Header, {.hdr { 2, "#>", /* C_hashfrom = 7232 */ colon }}}, /* CENTRY "#>" hashfrom 2 h 7240 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 7248 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7256 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7264 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7272 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 7280 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7288 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7296 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7304 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7312 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 7320 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7328 */
	{.type Header, {.hdr { 4, "hold", /* C_hold = 7344 */ colon }}}, /* CENTRY "hold" hold 4 h 7352 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7360 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7368 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 7376 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7384 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 7392 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 7400 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 7408 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7416 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7424 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7432 */
	{.type Header, {.hdr { 4, "sign", /* C_sign = 7448 */ colon }}}, /* CENTRY "sign" sign 4 h 7456 */
	{.type FromH0, {.p C_0lt}},		/* dd C_0lt 7464 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 7472 */
	{.type FromH0, {.p L100}},		/* dd L100 7480 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7488 */
	{.type Absolute, {.p 45}},		/* dd 45 7496 */
	{.type FromH0, {.p C_hold}},		/* dd C_hold 7504 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7512 */
	{.type Header, {.hdr { 1, ".", /* C_dot = 7528 */ colon }}}, /* CENTRY "." dot 1 h 7536 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7544 */
	{.type FromH0, {.p C_abs}},		/* dd C_abs 7552 */
	{.type FromH0, {.p C_fromhash}},		/* dd C_fromhash 7560 */
	{.type FromH0, {.p C_hashs}},		/* dd C_hashs 7568 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7576 */
	{.type FromH0, {.p C_sign}},		/* dd C_sign 7584 */
	{.type FromH0, {.p C_hashfrom}},		/* dd C_hashfrom 7592 */
	{.type FromH0, {.p C_type}},		/* dd C_type 7600 */
	{.type FromH0, {.p C_space}},		/* dd C_space 7608 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7616 */
	{.type Header, {.hdr { 2, ".r", /* C_dotr = 7632 */ colon }}}, /* CENTRY ".r" dotr 2 h 7640 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 7648 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7656 */
	{.type FromH0, {.p C_abs}},		/* dd C_abs 7664 */
	{.type FromH0, {.p C_fromhash}},		/* dd C_fromhash 7672 */
	{.type FromH0, {.p C_hashs}},		/* dd C_hashs 7680 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7688 */
	{.type FromH0, {.p C_sign}},		/* dd C_sign 7696 */
	{.type FromH0, {.p C_hashfrom}},		/* dd C_hashfrom 7704 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 7712 */
	{.type FromH0, {.p M_over}},		/* dd M_over 7720 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 7728 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7736 */
	{.type Absolute, {.p 0}},		/* dd 0 7744 */
	{.type FromH0, {.p C_max}},		/* dd C_max 7752 */
	{.type FromH0, {.p C_spaces}},		/* dd C_spaces 7760 */
	{.type FromH0, {.p C_type}},		/* dd C_type 7768 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7776 */
	{.type Header, {.hdr { 3, "hex", /* C_hex = 7792 */ colon }}}, /* CENTRY "hex" hex 3 h 7800 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7808 */
	{.type Absolute, {.p 16}},		/* dd 16 7816 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 7824 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7832 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7840 */
	{.type Header, {.hdr { 7, "decimal", /* C_decimal = 7856 */ colon }}}, /* CENTRY "decimal" decimal 7 h 7864 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7872 */
	{.type Absolute, {.p 10}},		/* dd 10 7880 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 7888 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7896 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7904 */
	{.type Header, {.hdr { 5, "digit", /* C_digit = 7920 */ colon }}}, /* CENTRY "digit" digit 5 h 7928 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7936 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7944 */
	{.type Absolute, {.p 65}},		/* dd 65 7952 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7960 */
	{.type Absolute, {.p 91}},		/* dd 91 7968 */
	{.type FromH0, {.p C_within}},		/* dd C_within 7976 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 7984 */
	{.type FromH0, {.p L106}},		/* dd L106 7992 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8000 */
	{.type Absolute, {.p 55}},		/* dd 55 8008 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 8016 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8024 */
	{.type FromH0, {.p L107}},		/* dd L107 8032 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8040 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8048 */
	{.type Absolute, {.p 97}},		/* dd 97 8056 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8064 */
	{.type Absolute, {.p 123}},		/* dd 123 8072 */
	{.type FromH0, {.p C_within}},		/* dd C_within 8080 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8088 */
	{.type FromH0, {.p L108}},		/* dd L108 8096 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8104 */
	{.type Absolute, {.p 87}},		/* dd 87 8112 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 8120 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8128 */
	{.type FromH0, {.p L109}},		/* dd L109 8136 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8144 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8152 */
	{.type Absolute, {.p 48}},		/* dd 48 8160 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8168 */
	{.type Absolute, {.p 58}},		/* dd 58 8176 */
	{.type FromH0, {.p C_within}},		/* dd C_within 8184 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8192 */
	{.type FromH0, {.p L110}},		/* dd L110 8200 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8208 */
	{.type Absolute, {.p 48}},		/* dd 48 8216 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 8224 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8232 */
	{.type FromH0, {.p L111}},		/* dd L111 8240 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8248 */
	{.type FromH0, {.p C_false}},		/* dd C_false 8256 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8264 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8272 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 8280 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8288 */
	{.type FromH0, {.p M_less}},		/* dd M_less 8296 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8304 */
	{.type FromH0, {.p L112}},		/* dd L112 8312 */
	{.type FromH0, {.p C_true}},		/* dd C_true 8320 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8328 */
	{.type FromH0, {.p L113}},		/* dd L113 8336 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8344 */
	{.type FromH0, {.p C_false}},		/* dd C_false 8352 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8360 */
	{.type Header, {.hdr { 6, "number", /* C_number = 8376 */ colon }}}, /* CENTRY "number" number 6 h 8384 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 8392 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8400 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 8408 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8416 */
	{.type Absolute, {.p 45}},		/* dd 45 8424 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal 8432 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8440 */
	{.type FromH0, {.p L115}},		/* dd L115 8448 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 8456 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 8464 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 8472 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8480 */
	{.type Absolute, {.p -1}},		/* dd -1 8488 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 8496 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8504 */
	{.type FromH0, {.p L116}},		/* dd L116 8512 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 8520 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8528 */
	{.type Absolute, {.p 1}},		/* dd 1 8536 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 8544 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8552 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 8560 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8568 */
	{.type Absolute, {.p 0}},		/* dd 0 8576 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 8584 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8592 */
	{.type Absolute, {.p 0}},		/* dd 0 8600 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 8608 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 8616 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8624 */
	{.type FromH0, {.p M_multiply}},		/* dd M_multiply 8632 */
	{.type FromH0, {.p M_over}},		/* dd M_over 8640 */
	{.type FromH0, {.p M_i}},		/* dd M_i 8648 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 8656 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 8664 */
	{.type FromH0, {.p C_digit}},		/* dd C_digit 8672 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8680 */
	{.type FromH0, {.p L118}},		/* dd L118 8688 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 8696 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8704 */
	{.type FromH0, {.p L119}},		/* dd L119 8712 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8720 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop 8728 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8736 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8744 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8752 */
	{.type FromH0, {.p C_false}},		/* dd C_false 8760 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8768 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 8776 */
	{.type FromH0, {.p L117}},		/* dd L117 8784 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8792 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8800 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 8808 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8816 */
	{.type FromH0, {.p M_multiply}},		/* dd M_multiply 8824 */
	{.type FromH0, {.p C_true}},		/* dd C_true 8832 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8840 */
	{.type Header, {.hdr { 5, "abort", /* C_abort = 8856 */ colon }}}, /* CENTRY "abort" abort 5 h 8864 */
	{.type FromH0, {.p MV_Abortvec}},		/* dd MV_Abortvec 8872 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8880 */
	{.type FromH0, {.p M_execute}},		/* dd M_execute 8888 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8896 */
	{.type Header, {.hdr { 6, "source", /* C_source = 8912 */ colon }}}, /* CENTRY "source" source 6 h 8920 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 8928 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8936 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8944 */
	{.type Header, {.hdr { 13, "current-input", /* C_current_input = 8968 */ colon }}}, /* CENTRY "current-input" current_input 13 ; ( -- c ) read the next character from the location in Sourcebuf h 8976 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 8984 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8992 */
	{.type FromH0, {.p C_source}},		/* dd C_source 9000 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus		; Sourcebuf + >In 9008 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 9016 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9024 */
	{.type Header, {.hdr { 10, "save-input", /* C_save_input = 9048 */ colon }}}, /* CENTRY "save-input" save_input 10 h 9056 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 9064 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9072 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9080 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9088 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9096 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9104 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9112 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 9120 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9128 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9136 */
	{.type Absolute, {.p 5}},		/* dd 5 9144 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9152 */
	{.type Header, {.hdr { 13, "default-input", /* C_default_input = 9176 */ colon }}}, /* CENTRY "default-input" default_input 13 h 9184 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 9192 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9200 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9208 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9216 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9224 */
	{.type FromH0, {.p MC_TIB}},		/* dd MC_TIB 9232 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9240 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9248 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 9256 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9264 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9272 */
	{.type Header, {.hdr { 13, "restore-input", /* C_restore_input = 9296 */ colon }}}, /* CENTRY "restore-input" restore_input 13 h 9304 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 9312 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9320 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9328 */
	{.type Absolute, {.p 5}},		/* dd 5 9336 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 9344 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9352 */
	{.type FromH0, {.p L133}},		/* dd L133 9360 */
	{.type FromH0, {.p C_default_input}},		/* dd C_default_input 9368 */
	{.type FromH0, {.p C_false}},		/* dd C_false 9376 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 9384 */
	{.type FromH0, {.p L134}},		/* dd L134 9392 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 9400 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9408 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9416 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9424 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9432 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9440 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9448 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9456 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 9464 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9472 */
	{.type FromH0, {.p C_true}},		/* dd C_true 9480 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9488 */
	{.type Header, {.hdr { 14, "?restore-input", /* C_qrestore_input = 9512 */ colon }}}, /* CENTRY "?restore-input" qrestore_input 14 h 9520 */
	{.type FromH0, {.p C_restore_input}},		/* dd C_restore_input 9528 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 9536 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9544 */
	{.type FromH0, {.p L136}},		/* dd L136 9552 */
	{.type FromH0, {.p C_space}},		/* dd C_space 9560 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9568 */
	{.type FromH0, {.p L137}},		/* dd L137 9576 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9584 */
	{.type Absolute, {.p 23}},		/* dd 23 9592 */
	{.type FromH0, {.p C_type}},		/* dd C_type 9600 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 9608 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 9616 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9624 */
	{.type Header, {.hdr { 10, "next-input", /* C_next_input = 9648 */ colon }}}, /* CENTRY "next-input" next_input 10 ; when >In < >Limit ( -- true c ). ( -- 0 false ) otherwise h 9656 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9664 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9672 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9680 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9688 */
	{.type FromH0, {.p M_less}},		/* dd M_less 9696 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9704 */
	{.type FromH0, {.p L139}},		/* dd L139	; >In >= >Limit 9712 */
	{.type FromH0, {.p C_true}},		/* dd C_true	; >In < >Limit 9720 */
	{.type FromH0, {.p C_current_input}},		/* dd C_current_input	; ( -- c ) 9728 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 9736 */
	{.type FromH0, {.p L140}},		/* dd L140 9744 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9752 */
	{.type Absolute, {.p 0}},		/* dd 0 9760 */
	{.type FromH0, {.p C_false}},		/* dd C_false 9768 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9776 */
	{.type Header, {.hdr { 5, "parse", /* C_parse = 9792 */ colon }}}, /* CENTRY "parse" parse 5 ; ( c -- a ) Place the counted string in the address in Wordbuf and return that address. c = word delimiter. h 9800 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush		; ( c -- ) (R -- c ) 9808 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf 9816 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; ( -- Wordb ) 9824 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus		; ( Wordb -- Wordb+1 ) 9832 */
	{.type FromH0, {.p C_next_input}},		/* dd C_next_input ; ( Wordb+1 -- Wordb+1 f c ) 9840 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c ) 9848 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) ) 9856 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 9864 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9872 */
	{.type FromH0, {.p L143}},		/* dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew 9880 */
	{.type FromH0, {.p C_current_input}},		/* dd C_current_input	; ( Wordb+1 -- Wordb+1 c ) 9888 */
	{.type FromH0, {.p M_over}},		/* dd M_over 9896 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1 9904 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus		; ( Wordb+1 -- Wordb+2 ) 9912 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9920 */
	{.type Absolute, {.p 1}},		/* dd 1 9928 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9936 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; >In++ 9944 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 9952 */
	{.type FromH0, {.p L142}},		/* dd L142		; ( Wordb+2 ) repeat 9960 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9968 */
	{.type Absolute, {.p 1}},		/* dd 1 9976 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9984 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; >In++ 9992 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- ) 10000 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; (Wordb+1 c -- Wordb+1) 10008 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf 10016 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb) 10024 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb) 10032 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb) 10040 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb) 10048 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb) 10056 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb) 10064 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now. 10072 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop		; ( -- Wordb) (R Wordb -- ) 10080 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10088 */
	{.type Header, {.hdr { 4, "word", /* C_word = 10104 */ colon }}}, /* CENTRY "word" word 4 ; ( c -- a ) skip the c"s. Placed the counted string in a (as in Wordbuf) h 10112 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( -- ) (R -- c ) 10120 */
	{.type FromH0, {.p C_next_input}},		/* dd C_next_input ; ( -- f c2 ) (R c1 -- ) 10128 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial ) 10136 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial ) 10144 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial ) 10152 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10160 */
	{.type FromH0, {.p L146}},		/* dd L146		; >In >= >Limit || cinitial != cnew 10168 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal	; >In < >Limit && cinitial == cnew 10176 */
	{.type Absolute, {.p 1}},		/* dd 1 10184 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 10192 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; >In++ 10200 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump		; repeat 10208 */
	{.type FromH0, {.p L145}},		/* dd L145 10216 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character 10224 */
	{.type FromH0, {.p C_parse}},		/* dd C_parse 10232 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10240 */
	{.type Header, {.hdr { 6, "accept", /* C_accept = 10256 */ colon }}}, /* CENTRY "accept" accept 6 ; ( a n -- n ) get line or n chars or EOF from input and store at a h 10264 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap	; ( n a -- ) 10272 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n a a -- ) 10280 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 10288 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( n -- ) (R a a -- ) 10296 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup	; ( n n -- ) (R a a -- ) 10304 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump	; (if) 10312 */
	{.type FromH0, {.p L149}},		/* dd L149	; n == 0 10320 */
	{.type FromH0, {.p C_key}},		/* dd C_key	; n > 0 ( n -- n c ) 10328 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( -- n c c ) 10336 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10344 */
	{.type Absolute, {.p 10}},		/* dd 10		; ( -- n c c 10 ) 10352 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( n c c 10 -- n c f ) checking for newline 10360 */
	{.type FromH0, {.p M_over}},		/* dd M_over	; ( -- n c f c ) 10368 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10376 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( -- n c f c -1 ) 10384 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( -- n c f1 f2 ) 10392 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor	; ( -- n c f ) 10400 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10408 */
	{.type FromH0, {.p L150}},		/* dd L150 10416 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop	; n == -1 || n == 10 (	-- ) 10424 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 10432 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 10440 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( -- a2-a1 ) 10448 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon	; ( -- n ) (R -- ) 10456 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch	; ( n c a -- ) (R a a -- ) 10464 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; store the character at a 10472 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( n a -- ) (R a -- ) 10480 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 10488 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address 10496 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus	; ( n -- n-1 ) 10504 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10512 */
	{.type FromH0, {.p L148}},		/* dd L148	; loop again for the next character 10520 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 ) 10528 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( a2 a1 -- ) (R a1 -- ) 10536 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( a2 a1 -- a2-a1 ) 10544 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10552 */
	{.type Header, {.hdr { 5, "query", /* C_query = 10568 */ colon }}}, /* CENTRY "query" query 5 ; read from input stream into the Text Input Buffer h 10576 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 10584 */
	{.type FromH0, {.p C_off}},		/* dd C_off		; clear EOF flag 10592 */
	{.type FromH0, {.p MC_TIB}},		/* dd MC_TIB	; constant puts address of tibuffer on the top 10600 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10608 */
	{.type Absolute, {.p 4096}},		/* dd 4096	; ( tibuffer -- tibuffer 4096 ) 10616 */
	{.type FromH0, {.p C_accept}},		/* dd C_accept ; ( tibuffer 4096 -- n ) 10624 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n -- n n ) 10632 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq	; ( n n -- n f ) 10640 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 10648 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 10656 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; n == 0 && EOF 10664 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10672 */
	{.type FromH0, {.p L152}},		/* dd L152		; false condition 10680 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; n == 0 && EOF ( n -- ) 10688 */
	{.type FromH0, {.p C_qrestore_input}},		/* dd C_qrestore_input 10696 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10704 */
	{.type FromH0, {.p L153}},		/* dd L153 10712 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 10720 */
	{.type FromH0, {.p M_store}},		/* dd M_store		; number of characters to read >Limit = n 10728 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 10736 */
	{.type FromH0, {.p C_off}},		/* dd C_off		; start from 0 >In = 0 10744 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10752 */
	{.type Header, {.hdr { 6, "refill", /* C_refill = 10768 */ colon }}}, /* CENTRY "refill" refill 6 h 10776 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 10784 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 10792 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10800 */
	{.type FromH0, {.p L155}},		/* dd L155 10808 */
	{.type FromH0, {.p C_false}},		/* dd C_false 10816 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10824 */
	{.type FromH0, {.p L156}},		/* dd L156 10832 */
	{.type FromH0, {.p C_query}},		/* dd C_query 10840 */
	{.type FromH0, {.p C_true}},		/* dd C_true 10848 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10856 */
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
	{.type Header, {.hdr { 8, "variable", /* C_variable = 12304 */ colon }}}, /* CENTRY "variable" variable 8 h 12312 */
	{.type FromH0, {.p C_create}},		/* dd C_create 12320 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12328 */
	{.type Absolute, {.p 0}},		/* dd 0 12336 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12344 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12352 */
	{.type Header, {.hdr { 8, "constant", /* C_constant = 12368 */ colon }}}, /* CENTRY "constant" constant 8 h 12376 */
	{.type FromH0, {.p C_create}},		/* dd C_create 12384 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12392 */
	{.type FromH0, {.p M_constant}},		/* dd M_constant 12400 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12408 */
	{.type FromH0, {.p C_here}},		/* dd C_here 12416 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12424 */
	{.type Absolute, {.p 1}},		/* dd 1 12432 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 12440 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 12448 */
	{.type FromH0, {.p M_store}},		/* dd M_store 12456 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12464 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12472 */
	{.type Header, {.hdr { 9, "immediate", /* C_immediate = 12496 */ colon }}}, /* CENTRY "immediate" immediate 9 h 12504 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 12512 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12520 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 12528 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12536 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 12544 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12552 */
	{.type Absolute, {.p 128}},		/* dd 128 12560 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 12568 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 12576 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 12584 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12592 */
	{.type Header, {.hdr { 4, ">cfa", /* C_tocfa = 12608 */ colon }}}, /* CENTRY ">cfa" tocfa 4 h 12616 */
	{.type FromH0, {.p C_count}},		/* dd C_count 12624 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12632 */
	{.type Absolute, {.p 63}},		/* dd 63 12640 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 12648 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 12656 */
	{.type FromH0, {.p C_aligned}},		/* dd C_aligned 12664 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12672 */
	{.type Header, {.hdr { 7, "compile", /* C_compile = 12688 */ colon }}}, /* CENTRY "compile" compile 7 h 12696 */
	{.type FromH0, {.p C_findname}},		/* dd C_findname 12704 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12712 */
	{.type FromH0, {.p L188}},		/* dd L188 12720 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12728 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 12736 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12744 */
	{.type Absolute, {.p 128}},		/* dd 128 12752 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 12760 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12768 */
	{.type FromH0, {.p L189}},		/* dd L189 12776 */
	{.type FromH0, {.p C_tocfa}},		/* dd C_tocfa	; immediate 12784 */
	{.type FromH0, {.p M_execute}},		/* dd M_execute 12792 */
	{.type FromH0, {.p C_qstack}},		/* dd C_qstack 12800 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 12808 */
	{.type FromH0, {.p L190}},		/* dd L190 12816 */
	{.type FromH0, {.p C_tocfa}},		/* dd C_tocfa 12824 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12832 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 12840 */
	{.type FromH0, {.p L191}},		/* dd L191 12848 */
	{.type FromH0, {.p C_count}},		/* dd C_count 12856 */
	{.type FromH0, {.p C_number}},		/* dd C_number 12864 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 12872 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12880 */
	{.type FromH0, {.p L192}},		/* dd L192 12888 */
	{.type FromH0, {.p C_space}},		/* dd C_space 12896 */
	{.type FromH0, {.p C_type}},		/* dd C_type 12904 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12912 */
	{.type FromH0, {.p L193}},		/* dd L193 12920 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12928 */
	{.type Absolute, {.p 3}},		/* dd 3 12936 */
	{.type FromH0, {.p C_type}},		/* dd C_type 12944 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 12952 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 12960 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 12968 */
	{.type FromH0, {.p L194}},		/* dd L194 12976 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12984 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12992 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13000 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13008 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13016 */
	{.type Header, {.hdr { 1, "]", /* C_close_bracket = 13032 */ colon }}}, /* CENTRY "]" close_bracket 1 h 13040 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13048 */
	{.type FromH0, {.p C_on}},		/* dd C_on 13056 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 13064 */
	{.type FromH0, {.p C_word}},		/* dd C_word 13072 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13080 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13088 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 13096 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 13104 */
	{.type FromH0, {.p L197}},		/* dd L197 13112 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 13120 */
	{.type FromH0, {.p C_refill}},		/* dd C_refill 13128 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13136 */
	{.type FromH0, {.p L198}},		/* dd L198 13144 */
	{.type FromH0, {.p C_compile}},		/* dd C_compile 13152 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13160 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13168 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 13176 */
	{.type FromH0, {.p L199}},		/* dd L199 13184 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13192 */
	{.type FromH0, {.p L196}},		/* dd L196 13200 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13208 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13216 */
	{.type FromH0, {.p C_off}},		/* dd C_off 13224 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13232 */
	{.type Header, {.hdr { 6, "smudge", /* C_smudge = 13248 */ colon }}}, /* CENTRY "smudge" smudge 6 h 13256 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 13264 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13272 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 13280 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13288 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13296 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13304 */
	{.type Absolute, {.p 64}},		/* dd 64 13312 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 13320 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 13328 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 13336 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13344 */
	{.type Header, {.hdr { 6, "reveal", /* C_reveal = 13360 */ colon }}}, /* CENTRY "reveal" reveal 6 h 13368 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 13376 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13384 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 13392 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13400 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13408 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13416 */
	{.type Absolute, {.p 64}},		/* dd 64 13424 */
	{.type FromH0, {.p C_invert}},		/* dd C_invert 13432 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 13440 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 13448 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 13456 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13464 */
	{.type Header, {.hdr { 1, ":", /* C_colon = 13480 */ colon }}}, /* CENTRY ":" colon 1 h 13488 */
	{.type FromH0, {.p C_create}},		/* dd C_create 13496 */
	{.type FromH0, {.p C_smudge}},		/* dd C_smudge 13504 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13512 */
	{.type FromH0, {.p M_colon}},		/* dd M_colon 13520 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13528 */
	{.type FromH0, {.p C_here}},		/* dd C_here 13536 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13544 */
	{.type Absolute, {.p 1}},		/* dd 1 13552 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 13560 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 13568 */
	{.type FromH0, {.p M_store}},		/* dd M_store 13576 */
	{.type FromH0, {.p C_close_bracket}},		/* dd C_close_bracket 13584 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13592 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13600 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13608 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13616 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13624 */
	{.type FromH0, {.p C_off}},		/* dd C_off 13632 */
	{.type FromH0, {.p C_reveal}},		/* dd C_reveal 13640 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13648 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 13656 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13664 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 13672 */
	{.type FromH0, {.p C_tocfa}},		/* dd C_tocfa 13680 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13688 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13696 */
	{.type Header, {.hdr { 4, "char", /* C_L206 = 13712 */ colon }}}, /* CENTRY "char" L206 4 h 13720 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 13728 */
	{.type FromH0, {.p C_word}},		/* dd C_word 13736 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 13744 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13752 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13760 */
	{.type Header, {.hdr { 7, "literal", /* C_literal = 13776 */ colon }}}, /* CENTRY "literal" literal 7 h 13784 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13792 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13800 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13808 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13816 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13824 */
	{.type Header, {.hdr { 8, "sliteral", /* C_sliteral = 13840 */ colon }}}, /* CENTRY "sliteral" sliteral 8 h 13848 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13856 */
	{.type FromH0, {.p M_sliteral}},		/* dd M_sliteral 13864 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13872 */
	{.type FromH0, {.p C_here}},		/* dd C_here 13880 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13888 */
	{.type Absolute, {.p 34}},		/* dd 34 13896 */
	{.type FromH0, {.p C_parse}},		/* dd C_parse 13904 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13912 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13920 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 13928 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 13936 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 13944 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 13952 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 13960 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 13968 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 13976 */
	{.type FromH0, {.p C_align}},		/* dd C_align 13984 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13992 */
	{.type Header, {.hdr { 6, "string", /* C_string = 14008 */ colon }}}, /* CENTRY "string" string 6 h 14016 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14024 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 14032 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14040 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14048 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 14056 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14064 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 14072 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 14080 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 14088 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 14096 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14104 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 14112 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14120 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14128 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14136 */
	{.type FromH0, {.p C_literal}},		/* dd C_literal 14144 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14152 */
	{.type FromH0, {.p C_single_quote}},		/* dd C_single_quote 14160 */
	{.type FromH0, {.p C_literal}},		/* dd C_literal 14168 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14176 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14184 */
	{.type Absolute, {.p 41}},		/* dd 41 14192 */
	{.type FromH0, {.p C_parse}},		/* dd C_parse 14200 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 14208 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14216 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 14224 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14232 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 14240 */
	{.type FromH0, {.p L214}},		/* dd L214 14248 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 14256 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14264 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14272 */
	{.type Absolute, {.p 63}},		/* dd 63 14280 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 14288 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14296 */
	{.type Absolute, {.p 63}},		/* dd 63 14304 */
	{.type FromH0, {.p C_invert}},		/* dd C_invert 14312 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 14320 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 14328 */
	{.type FromH0, {.p M_store}},		/* dd M_store 14336 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 14344 */
	{.type FromH0, {.p L215}},		/* dd L215 14352 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 14360 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14368 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 14376 */
	{.type FromH0, {.p M_store}},		/* dd M_store 14384 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14392 */
	{.type Header, {.hdr { 8, "(?abort)", /* C_qabort_parens = 14408 */ colon }}}, /* CENTRY "(?abort)" qabort_parens 8 h 14416 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 14424 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 14432 */
	{.type FromH0, {.p L217}},		/* dd L217 14440 */
	{.type FromH0, {.p C_space}},		/* dd C_space 14448 */
	{.type FromH0, {.p C_type}},		/* dd C_type 14456 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 14464 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 14472 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 14480 */
	{.type FromH0, {.p L218}},		/* dd L218 14488 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop 14496 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14504 */
	{.type FromH0, {.p C_sliteral}},		/* dd C_sliteral 14512 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14520 */
	{.type FromH0, {.p C_qabort_parens}},		/* dd C_qabort_parens 14528 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14536 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14544 */
	{.type Header, {.hdr { 1, "\"", /* C_double_quote = 14560 */ colon }}}, /* CENTRY "\"" double_quote 1 h 14568 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14576 */
	{.type Absolute, {.p 34}},		/* dd 34 14584 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14592 */
	{.type FromH0, {.p C_count}},		/* dd C_count 14600 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 14608 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14616 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 14624 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 14632 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14640 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 14648 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 14656 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 14664 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14672 */
	{.type Header, {.hdr { 2, "c\"", /* C_cdouble_quote = 14688 */ colon }}}, /* CENTRY "c\"" cdouble_quote 2 h 14696 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14704 */
	{.type Absolute, {.p 34}},		/* dd 34 14712 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14720 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 14728 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14736 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14744 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 14752 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14760 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 14768 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 14776 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14784 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 14792 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 14800 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14808 */
	{.type FromH0, {.p C_sliteral}},		/* dd C_sliteral 14816 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14824 */
	{.type FromH0, {.p C_sliteral}},		/* dd C_sliteral 14832 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14840 */
	{.type FromH0, {.p C_type}},		/* dd C_type 14848 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14856 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14864 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14872 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 14880 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14888 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14896 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14904 */
	{.type Absolute, {.p 0}},		/* dd 0 14912 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14920 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14928 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14936 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 14944 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14952 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14960 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 14968 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14976 */
	{.type Absolute, {.p 0}},		/* dd 0 14984 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14992 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15000 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15008 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15016 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 15024 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15032 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15040 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15048 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15056 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15064 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15072 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15080 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15088 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 15096 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15104 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15112 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15120 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15128 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15136 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15144 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15152 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15160 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15168 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15176 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15184 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15192 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15200 */
	{.type Absolute, {.p 0}},		/* dd 0 15208 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15216 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15224 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15232 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 15240 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15248 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15256 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15264 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15272 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15280 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15288 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15296 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15304 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 15312 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15320 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15328 */
	{.type Absolute, {.p 0}},		/* dd 0 15336 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15344 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15352 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15360 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 15368 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15376 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15384 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 15392 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15400 */
	{.type FromH0, {.p L234}},		/* dd L234 15408 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15416 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15424 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15432 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15440 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15448 */
	{.type FromH0, {.p M_doploop}},		/* dd M_doploop 15456 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15464 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15472 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 15480 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15488 */
	{.type FromH0, {.p L236}},		/* dd L236 15496 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15504 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15512 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15520 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15528 */
	{.type Header, {.hdr { 3, "w/o", /* C_wo = 15544 */ colon }}}, /* CENTRY "w/o" wo 3 h 15552 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15560 */
	{.type Absolute, {.p 1}},		/* dd 1 15568 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15576 */
	{.type Absolute, {.p 512}},		/* dd 512 15584 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 15592 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15600 */
	{.type Absolute, {.p 64}},		/* dd 64 15608 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 15616 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15624 */
	{.type Header, {.hdr { 3, "r/o", /* C_ro = 15640 */ colon }}}, /* CENTRY "r/o" ro 3 h 15648 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15656 */
	{.type Absolute, {.p 0}},		/* dd 0 15664 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15672 */
	{.type Header, {.hdr { 3, "r/w", /* C_rw = 15688 */ colon }}}, /* CENTRY "r/w" rw 3 h 15696 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15704 */
	{.type Absolute, {.p 2}},		/* dd 2 15712 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15720 */
	{.type Header, {.hdr { 9, "open-file", /* C_open_file = 15744 */ colon }}}, /* CENTRY "open-file" open_file 9 h 15752 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 15760 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 15768 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15776 */
	{.type Absolute, {.p 1024}},		/* dd 1024 15784 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 15792 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15800 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 15808 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 15816 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 15824 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15832 */
	{.type Absolute, {.p 0}},		/* dd 0 15840 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 15848 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 15856 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 15864 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15872 */
	{.type Absolute, {.p 1024}},		/* dd 1024 15880 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 15888 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 15896 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 15904 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15912 */
	{.type Absolute, {.p 1024}},		/* dd 1024 15920 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 15928 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 15936 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15944 */
	{.type Absolute, {.p 420}},		/* dd 420 15952 */
	{.type FromH0, {.p M_fthopen}},		/* dd M_fthopen 15960 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 15968 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15976 */
	{.type Absolute, {.p -1}},		/* dd -1 15984 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 15992 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16000 */
	{.type Header, {.hdr { 10, "close-file", /* C_close_file = 16024 */ colon }}}, /* CENTRY "close-file" close_file 10 h 16032 */
	{.type FromH0, {.p M_fthclose}},		/* dd M_fthclose 16040 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 16048 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16056 */
	{.type Header, {.hdr { 9, "read-file", /* C_read_file = 16080 */ colon }}}, /* CENTRY "read-file" read_file 9 h 16088 */
	{.type FromH0, {.p M_fthread}},		/* dd M_fthread 16096 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 16104 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16112 */
	{.type Absolute, {.p -1}},		/* dd -1 16120 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 16128 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16136 */
	{.type Header, {.hdr { 10, "write-file", /* C_write_file = 16160 */ colon }}}, /* CENTRY "write-file" write_file 10 h 16168 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite 16176 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16184 */
	{.type Absolute, {.p -1}},		/* dd -1 16192 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 16200 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16208 */
	{.type Header, {.hdr { 15, "reposition-file", /* C_reposition_file = 16232 */ colon }}}, /* CENTRY "reposition-file" reposition_file 15 h 16240 */
	{.type FromH0, {.p M_fthseek}},		/* dd M_fthseek 16248 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16256 */
	{.type Absolute, {.p -1}},		/* dd -1 16264 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 16272 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16280 */
	{.type Header, {.hdr { 7, "?fcheck", /* C_qfcheck = 16296 */ colon }}}, /* CENTRY "?fcheck" qfcheck 7 h 16304 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 16312 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 16320 */
	{.type FromH0, {.p L246}},		/* dd L246 16328 */
	{.type FromH0, {.p C_space}},		/* dd C_space 16336 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16344 */
	{.type FromH0, {.p L247}},		/* dd L247 16352 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16360 */
	{.type Absolute, {.p 9}},		/* dd 9 16368 */
	{.type FromH0, {.p C_type}},		/* dd C_type 16376 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 16384 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 16392 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16400 */
	{.type Header, {.hdr { 3, "bye", /* C_bye = 16416 */ colon }}}, /* CENTRY "bye" bye 3 h 16424 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16432 */
	{.type Absolute, {.p 0}},		/* dd 0 16440 */
	{.type FromH0, {.p M_terminate}},		/* dd M_terminate 16448 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16456 */
	{.type Header, {.hdr { 7, "include", /* C_include = 16472 */ colon }}}, /* CENTRY "include" include 7 h 16480 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 16488 */
	{.type FromH0, {.p C_word}},		/* dd C_word 16496 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 16504 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 16512 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 16520 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 16528 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16536 */
	{.type FromH0, {.p C_save_input}},		/* dd C_save_input 16544 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 16552 */
	{.type FromH0, {.p C_count}},		/* dd C_count 16560 */
	{.type FromH0, {.p C_ro}},		/* dd C_ro 16568 */
	{.type FromH0, {.p C_open_file}},		/* dd C_open_file 16576 */
	{.type FromH0, {.p C_qfcheck}},		/* dd C_qfcheck 16584 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 16592 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16600 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16608 */
	{.type Header, {.hdr { 5, "crash", /* C_crash = 16624 */ colon }}}, /* CENTRY "crash" crash 5 h 16632 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16640 */
	{.type FromH0, {.p L251}},		/* dd L251 16648 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16656 */
	{.type Absolute, {.p 30}},		/* dd 30 16664 */
	{.type FromH0, {.p C_type}},		/* dd C_type 16672 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 16680 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 16688 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16696 */
	{.type Header, {.hdr { 4, "quit", /* C_quit = 16712 */ colon }}}, /* CENTRY "quit" quit 4 ; interpreter loop h 16720 */
	{.type FromH0, {.p M_reset}},		/* dd M_reset ; initialize return stack 16728 */
	{.type FromH0, {.p M_clear}},		/* dd M_clear	; SP = sstack_end initialize data stack 16736 */
	{.type FromH0, {.p C_query}},		/* dd C_query 16744 */
	{.type FromH0, {.p C_interpret}},		/* dd C_interpret 16752 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 16760 */
	{.type FromH0, {.p L253}},		/* dd L253 16768 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon	; why is this needed? 16776 */
	{.type Header, {.hdr { 7, "(abort)", /* C_parenabort = 16792 */ colon }}}, /* CENTRY "(abort)" parenabort 7 ; TODO correct below stack notations h 16800 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State	; ( mv_State -- ) 16808 */
	{.type FromH0, {.p C_off}},		/* dd C_off		; off sets variable state = 0 16816 */
	{.type FromH0, {.p MC_TIB}},		/* dd MC_TIB	; constant puts address of tibuffer on the top of stack 16824 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 16832 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 16840 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk	; variable blk 16848 */
	{.type FromH0, {.p C_off}},		/* dd C_off	; off variable blk = 0 16856 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 16864 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 16872 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16880 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 16888 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 16896 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16904 */
	{.type FromH0, {.p MC_STDERR}},		/* dd MC_STDERR 16912 */
	{.type FromH0, {.p MV_Errfd}},		/* dd MV_Errfd 16920 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16928 */
	{.type FromH0, {.p C_quit}},		/* dd C_quit	; quit resets stacks and is the interpreter loop 16936 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon	; why is this needed? quit does not return unless it breaks 16944 */
	{.type Header, {.hdr { 7, "oldboot", /* C_oldboot = 16960 */ colon }}}, /* CENTRY "oldboot" oldboot 7 ; TODO correct below stack notations and this is obsolete. leaving it here for reference until it all works well h 16968 */
	{.type FromH0, {.p M_reset}},		/* dd M_reset 16976 */
	{.type FromH0, {.p M_clear}},		/* dd M_clear	; SP = sstack_end 16984 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr	; (D -- FFEND) 16992 */
	{.type FromH0, {.p M_S0}},		/* dd M_S0 17000 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; s0 = FFEND 17008 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0	; heaptop = heapend 17016 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; ( heapend -- ) 17024 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17032 */
	{.type Absolute, {.p 1}},		/* dd 1		; ( heapend 1 -- ) 17040 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells	; cells ( heapend 8 -- ) 17048 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( heapend-8 -- ) 17056 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; ( contents_from_heapend-8 -- ) 17064 */
	{.type FromH0, {.p M_Args}},		/* dd M_Args	; variable args 17072 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; args = contents_from_heapend-8 17080 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17088 */
	{.type FromH0, {.p C_parenabort}},		/* dd C_parenabort ; ( (abort) -- ) 17096 */
	{.type FromH0, {.p MV_Abortvec}},		/* dd MV_Abortvec	; variable abortvec 17104 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable abortvec = (abort) code address 17112 */
	{.type FromH0, {.p MC_WORDB}},		/* dd MC_WORDB	; constant puts address of wordbuffer on the top of stack 17120 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf	; variable wordbuf 17128 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable wordbuf = address of wordbuffer 17136 */
	{.type FromH0, {.p MC_TIB}},		/* dd MC_TIB	; constant puts address of tibuffer on the top of stack 17144 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 17152 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 17160 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17168 */
	{.type Absolute, {.p 0}},		/* dd 0 17176 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 17184 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; stdin = 0 17192 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17200 */
	{.type Absolute, {.p 1}},		/* dd 1 17208 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 17216 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; stdout = 1 17224 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 17232 */
	{.type FromH0, {.p C_off}},		/* dd C_off	; off stores 0 at state 17240 */
	{.type FromH0, {.p C_decimal}},		/* dd C_decimal	; decimal setting base = 0 17248 */
	{.type FromH0, {.p C_quit}},		/* dd C_quit	; quit 17256 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17264 */
	{.type Header, {.hdr { 4, "boot", /* C_boot = 17280 */ colon }}}, /* CENTRY "boot" boot 4 h 17288 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal	; this is not working TEST 17296 */
	{.type Absolute, {.p 66}},		/* dd 66 17304 */
	{.type FromH0, {.p MC_WORDB}},		/* dd MC_WORDB 17312 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17320 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17328 */
	{.type Absolute, {.p 1}},		/* dd 1 17336 */
	{.type FromH0, {.p MC_WORDB}},		/* dd MC_WORDB 17344 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 17352 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite 17360 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17368 */
	{.type Absolute, {.p 1}},		/* dd 1 17376 */
	{.type FromH0, {.p MC_WORDB}},		/* dd MC_WORDB 17384 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 17392 */
	{.type FromH0, {.p M_fthread}},		/* dd M_fthread	; this is not working TODO 17400 */
	{.type FromH0, {.p M_reset}},		/* dd M_reset ; initialize return stack 17408 */
	{.type FromH0, {.p M_clear}},		/* dd M_clear	; SP = sstack_end initialize data stack 17416 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17424 */
	{.type FromH0, {.p C_parenabort}},		/* dd C_parenabort ; ( (abort) -- ) 17432 */
	{.type FromH0, {.p MV_Abortvec}},		/* dd MV_Abortvec	; variable that puts (abort) code address on the stack 17440 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable abortvec = (abort) code address 17448 */
	{.type FromH0, {.p MC_WORDB}},		/* dd MC_WORDB	; variable puts address of wordbuffer on the top of stack 17456 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf ; variable wordbuf 17464 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable wordbuf = address of wordbuffer 17472 */
	{.type FromH0, {.p MC_TIB}},		/* dd MC_TIB	; constant puts address of tibuffer on the top of stack 17480 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 17488 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 17496 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 17504 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 17512 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; stdin = 0 17520 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 17528 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 17536 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17544 */
	{.type FromH0, {.p MC_STDERR}},		/* dd MC_STDERR 17552 */
	{.type FromH0, {.p MV_Errfd}},		/* dd MV_Errfd 17560 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17568 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 17576 */
	{.type FromH0, {.p C_off}},		/* dd C_off	; off stores 0 at state 17584 */
	{.type FromH0, {.p C_decimal}},		/* dd C_decimal	; decimal setting base = 0 17592 */
	{.type FromH0, {.p C_quit}},		/* dd C_quit	; quit 17600 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17608 */
	{.type Chars, {.str "unable to restore input"}},		/* 17632 */
	{.type Chars, {.str " Q?"}},		/* 17636 */
	{.type Chars, {.str " stack underflow"}},		/* 17653 */
	{.type Chars, {.str " I?"}},		/* 17657 */
	{.type Chars, {.str " C?"}},		/* 17661 */
	{.type Chars, {.str "I/O error"}},		/* 17671 */
	{.type Chars, {.str "uninitialized execution vector"}},		/* 17702 */
	{.type Chars, {.str " ok"}},		/* 17706 */
};

