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
	M_fthdump = 328,
	M_clear = 352,
	M_reset = 376,
	M_exitcolon = 400,
	M_literal = 432,
	M_sliteral = 464,
	M_doinit = 488,
	M_doloop = 512,
	M_doploop = 536,
	M_rfetch = 560,
	M_rpop = 584,
	M_rpush = 608,
	M_i = 632,
	M_j = 656,
	M_plus = 680,
	M_minus = 704,
	M_multiply = 728,
	M_cjump = 752,
	M_jump = 776,
	M_slashmod = 800,
	M_uslashmod = 824,
	M_binand = 848,
	M_binor = 872,
	M_binxor = 896,
	M_xswap = 920,
	M_drop = 944,
	M_dup = 968,
	M_over = 992,
	M_equal = 1016,
	M_greater = 1040,
	M_less = 1064,
	M_lshift = 1088,
	M_rshift = 1112,
	M_rshifta = 1136,
	M_execute = 1160,
	M_unloop = 1184,
	M_cmove = 1208,
	M_cmoveb = 1232,
	MV_Iobuf = 1256,
	MV_Sourcebuf = 1296,
	MV_Wordbuf = 1328,
	MV_toIn = 1360,
	MV_toLimit = 1392,
	MV_Findadr = 1424,
	MV_Blk = 1456,
	MV_Searchlen = 1496,
	MV_Base = 1528,
	MV_toNum = 1560,
	MV_State = 1592,
	MV_Abortvec = 1632,
	MV_Infd = 1664,
	MV_Outfd = 1696,
	MV_Errfd = 1728,
	MV_Eof = 1760,
	MC_STDIN = 1792,
	MC_STDOUT = 1824,
	MC_STDERR = 1856,
	M_S0 = 1888,
	M_stackptr = 1912,
	M_H0 = 1936,
	M_Wordb = 1960,
	M_Tib = 1984,
	M_Args = 2008,
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
	C_type = 5064,
	C_cr = 5136,
	C_space = 5192,
	C_emits = 5240,
	L85 = 5248,
	L86 = 5312,
	C_spaces = 5344,
	C_count = 5400,
	C_compare = 5528,
	L55 = 5600,
	L56 = 5736,
	C_erase = 5816,
	L58 = 5848,
	C_fill = 5936,
	L60 = 5976,
	C_blank = 6064,
	C_search = 6112,
	L64 = 6216,
	L65 = 6400,
	C_here = 6464,
	C_comma = 6512,
	C_c = 6592,
	C_allot = 6672,
	C_pad = 6720,
	C_align = 6784,
	C_unused = 6848,
	C_fromhash = 6912,
	C_hash = 6992,
	L92 = 7144,
	L93 = 7168,
	C_hashs = 7248,
	L95 = 7256,
	L96 = 7304,
	C_hashfrom = 7328,
	C_hold = 7440,
	C_sign = 7544,
	L100 = 7600,
	C_dot = 7624,
	C_dotr = 7728,
	C_hex = 7888,
	C_decimal = 7952,
	C_digit = 8016,
	L106 = 8128,
	L108 = 8232,
	L110 = 8336,
	L111 = 8360,
	L109 = 8360,
	L107 = 8360,
	L112 = 8432,
	L113 = 8448,
	C_number = 8472,
	L115 = 8608,
	L116 = 8640,
	L117 = 8704,
	L118 = 8808,
	L119 = 8864,
	C_abort = 8952,
	C_source = 9008,
	C_current_input = 9064,
	C_save_input = 9144,
	C_default_input = 9272,
	C_restore_input = 9392,
	L133 = 9488,
	L134 = 9576,
	C_qrestore_input = 9608,
	L136 = 9712,
	C_next_input = 9744,
	L139 = 9840,
	L140 = 9864,
	C_parse = 9888,
	L142 = 9928,
	L143 = 10056,
	C_word = 10200,
	L145 = 10216,
	L146 = 10312,
	C_accept = 10352,
	L148 = 10392,
	L150 = 10552,
	L149 = 10616,
	C_query = 10664,
	L152 = 10808,
	L153 = 10840,
	C_refill = 10864,
	L155 = 10928,
	L156 = 10944,
	C_findname = 10976,
	L158 = 11016,
	L160 = 11128,
	L162 = 11256,
	L161 = 11264,
	L159 = 11280,
	C_find = 11328,
	L165 = 11520,
	L166 = 11536,
	L164 = 11560,
	L167 = 11568,
	C_single_quote = 11592,
	L169 = 11728,
	C_qstack = 11752,
	L172 = 11856,
	C_interpret = 11936,
	L175 = 11944,
	L177 = 12048,
	L179 = 12160,
	L178 = 12160,
	L176 = 12176,
	C_create = 12208,
	C_variable = 12456,
	C_constant = 12528,
	C_immediate = 12656,
	C_tocfa = 12768,
	C_compile = 12848,
	L189 = 12976,
	L190 = 12992,
	L188 = 13008,
	L192 = 13136,
	L194 = 13168,
	L191 = 13168,
	C_close_bracket = 13192,
	L196 = 13216,
	L197 = 13304,
	L198 = 13328,
	L199 = 13360,
	CI_open_bracket = 13384,
	C_smudge = 13432,
	C_reveal = 13544,
	C_colon = 13664,
	CI_semicolon = 13792,
	CI_recurse = 13872,
	C_L206 = 13944,
	C_literal = 14008,
	C_sliteral = 14080,
	C_string = 14248,
	CI_char_brackets = 14360,
	CI_quote_brackets = 14432,
	CI_openparen = 14480,
	CI_backslash = 14544,
	L214 = 14688,
	L215 = 14720,
	C_qabort_parens = 14752,
	L217 = 14832,
	L218 = 14840,
	CI_abort_double_quote = 14864,
	C_double_quote = 14928,
	C_cdouble_quote = 15056,
	CI_sdouble_quote = 15192,
	CI_dotstr = 15232,
	CI_if = 15296,
	CI_else = 15384,
	CI_then = 15512,
	CI_begin = 15568,
	CI_again = 15608,
	CI_until = 15672,
	CI_while = 15736,
	CI_repeat = 15824,
	CI_do = 15920,
	CI_loop = 16000,
	L234 = 16088,
	CI_ploop = 16112,
	L236 = 16200,
	C_wo = 16224,
	C_ro = 16320,
	C_rw = 16368,
	C_open_file = 16424,
	C_close_file = 16704,
	C_read_file = 16760,
	C_write_file = 16840,
	C_reposition_file = 16912,
	C_qfcheck = 16976,
	L246 = 17072,
	C_bye = 17096,
	C_include = 17152,
	C_crash = 17304,
	C_quit = 17392,
	L253 = 17416,
	C_parenabort = 17520,
	C_oldboot = 17688,
	C_boot = 18136,
	L137 = 18352,
	L170 = 18376,
	L173 = 18380,
	L180 = 18397,
	L193 = 18401,
	L247 = 18405,
	L251 = 18415,
	L255 = 18446,
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
extern void *fthdump(void);
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
	{.type Header, {.hdr { 4, "dump", /* M_fthdump = 328 */ fthdump }}}, /* MENTRY "dump" fthdump 4 h 336 */
	{.type Header, {.hdr { 5, "clear", /* M_clear = 352 */ clear }}}, /* MENTRY "clear" clear 5 h 360 */
	{.type Header, {.hdr { 5, "reset", /* M_reset = 376 */ reset }}}, /* MENTRY "reset" reset 5 h 384 */
	{.type Header, {.hdr { 4, "exitcolon", /* M_exitcolon = 400 */ exitcolon }}}, /* MENTRY "exitcolon" exitcolon 4 h 408 */
	{.type Header, {.hdr { 9, "(literal)", /* M_literal = 432 */ literal }}}, /* MENTRY "(literal)" literal 9 h 440 */
	{.type Header, {.hdr { 10, "(sliteral)", /* M_sliteral = 464 */ sliteral }}}, /* MENTRY "(sliteral)" sliteral 10 h 472 */
	{.type Header, {.hdr { 4, "(do)", /* M_doinit = 488 */ doinit }}}, /* MENTRY "(do)" doinit 4 h 496 */
	{.type Header, {.hdr { 6, "(loop)", /* M_doloop = 512 */ doloop }}}, /* MENTRY "(loop)" doloop 6 h 520 */
	{.type Header, {.hdr { 7, "(+loop)", /* M_doploop = 536 */ doploop }}}, /* MENTRY "(+loop)" doploop 7 h 544 */
	{.type Header, {.hdr { 2, "r@", /* M_rfetch = 560 */ rfetch }}}, /* MENTRY "r@" rfetch 2 h 568 */
	{.type Header, {.hdr { 2, "r>", /* M_rpop = 584 */ rpop }}}, /* MENTRY "r>" rpop 2 h 592 */
	{.type Header, {.hdr { 2, ">r", /* M_rpush = 608 */ rpush }}}, /* MENTRY ">r" rpush 2 h 616 */
	{.type Header, {.hdr { 1, "i", /* M_i = 632 */ i }}}, /* MENTRY "i" i 1 h 640 */
	{.type Header, {.hdr { 1, "j", /* M_j = 656 */ j }}}, /* MENTRY "j" j 1 h 664 */
	{.type Header, {.hdr { 1, "+", /* M_plus = 680 */ plus }}}, /* MENTRY "+" plus 1 h 688 */
	{.type Header, {.hdr { 1, "-", /* M_minus = 704 */ minus }}}, /* MENTRY "-" minus 1 h 712 */
	{.type Header, {.hdr { 1, "*", /* M_multiply = 728 */ multiply }}}, /* MENTRY "*" multiply 1 h 736 */
	{.type Header, {.hdr { 4, "(if)", /* M_cjump = 752 */ cjump }}}, /* MENTRY "(if)" cjump 4 h 760 */
	{.type Header, {.hdr { 6, "(else)", /* M_jump = 776 */ jump }}}, /* MENTRY "(else)" jump 6 h 784 */
	{.type Header, {.hdr { 4, "/mod", /* M_slashmod = 800 */ slashmod }}}, /* MENTRY "/mod" slashmod 4 h 808 */
	{.type Header, {.hdr { 5, "u/mod", /* M_uslashmod = 824 */ uslashmod }}}, /* MENTRY "u/mod" uslashmod 5 h 832 */
	{.type Header, {.hdr { 3, "and", /* M_binand = 848 */ binand }}}, /* MENTRY "and" binand 3 h 856 */
	{.type Header, {.hdr { 2, "or", /* M_binor = 872 */ binor }}}, /* MENTRY "or" binor 2 h 880 */
	{.type Header, {.hdr { 3, "xor", /* M_binxor = 896 */ binxor }}}, /* MENTRY "xor" binxor 3 h 904 */
	{.type Header, {.hdr { 4, "swap", /* M_xswap = 920 */ xswap }}}, /* MENTRY "swap" xswap 4 h 928 */
	{.type Header, {.hdr { 4, "drop", /* M_drop = 944 */ drop }}}, /* MENTRY "drop" drop 4 h 952 */
	{.type Header, {.hdr { 3, "dup", /* M_dup = 968 */ dup }}}, /* MENTRY "dup" dup 3 h 976 */
	{.type Header, {.hdr { 4, "over", /* M_over = 992 */ over }}}, /* MENTRY "over" over 4 h 1000 */
	{.type Header, {.hdr { 1, "=", /* M_equal = 1016 */ equal }}}, /* MENTRY "=" equal 1 h 1024 */
	{.type Header, {.hdr { 1, ">", /* M_greater = 1040 */ greater }}}, /* MENTRY ">" greater 1 h 1048 */
	{.type Header, {.hdr { 1, "<", /* M_less = 1064 */ less }}}, /* MENTRY "<" less 1 h 1072 */
	{.type Header, {.hdr { 6, "lshift", /* M_lshift = 1088 */ lshift }}}, /* MENTRY "lshift" lshift 6 h 1096 */
	{.type Header, {.hdr { 6, "rshift", /* M_rshift = 1112 */ rshift }}}, /* MENTRY "rshift" rshift 6 h 1120 */
	{.type Header, {.hdr { 7, "rshifta", /* M_rshifta = 1136 */ rshifta }}}, /* MENTRY "rshifta" rshifta 7 h 1144 */
	{.type Header, {.hdr { 7, "execute", /* M_execute = 1160 */ execute }}}, /* MENTRY "execute" execute 7 h 1168 */
	{.type Header, {.hdr { 6, "unloop", /* M_unloop = 1184 */ unloop }}}, /* MENTRY "unloop" unloop 6 h 1192 */
	{.type Header, {.hdr { 5, "cmove", /* M_cmove = 1208 */ cmove }}}, /* MENTRY "cmove" cmove 5 h 1216 */
	{.type Header, {.hdr { 6, "cmove>", /* M_cmoveb = 1232 */ cmoveb }}}, /* MENTRY "cmove>" cmoveb 6 h 1240 */
	{.type Header, {.hdr { 5, "Iobuf", /* MV_Iobuf = 1256 */ variable }}}, /* MVENTRY "Iobuf" Iobuf 0 5 h 1264 */
	{.type Absolute, {.p 0}},		/* 1272 */
	{.type Header, {.hdr { 9, "Sourcebuf", /* MV_Sourcebuf = 1296 */ variable }}}, /* MVENTRY "Sourcebuf" Sourcebuf 0 9	; is there a need for this? h 1304 */
	{.type Absolute, {.p 0}},		/* 1312 */
	{.type Header, {.hdr { 7, "Wordbuf", /* MV_Wordbuf = 1328 */ variable }}}, /* MVENTRY "Wordbuf" Wordbuf 0 7		; is there a need for this? h 1336 */
	{.type Absolute, {.p 0}},		/* 1344 */
	{.type Header, {.hdr { 3, ">In", /* MV_toIn = 1360 */ variable }}}, /* MVENTRY ">In" toIn 0 3 h 1368 */
	{.type Absolute, {.p 0}},		/* 1376 */
	{.type Header, {.hdr { 6, ">Limit", /* MV_toLimit = 1392 */ variable }}}, /* MVENTRY ">Limit" toLimit 0 6 h 1400 */
	{.type Absolute, {.p 0}},		/* 1408 */
	{.type Header, {.hdr { 7, "Findadr", /* MV_Findadr = 1424 */ variable }}}, /* MVENTRY "Findadr" Findadr 0 7 h 1432 */
	{.type Absolute, {.p 0}},		/* 1440 */
	{.type Header, {.hdr { 3, "Blk", /* MV_Blk = 1456 */ variable }}}, /* MVENTRY "Blk" Blk 0 3 h 1464 */
	{.type Absolute, {.p 0}},		/* 1472 */
	{.type Header, {.hdr { 9, "Searchlen", /* MV_Searchlen = 1496 */ variable }}}, /* MVENTRY "Searchlen" Searchlen 0 9 h 1504 */
	{.type Absolute, {.p 0}},		/* 1512 */
	{.type Header, {.hdr { 4, "Base", /* MV_Base = 1528 */ variable }}}, /* MVENTRY "Base" Base 0 4 h 1536 */
	{.type Absolute, {.p 0}},		/* 1544 */
	{.type Header, {.hdr { 4, ">Num", /* MV_toNum = 1560 */ variable }}}, /* MVENTRY ">Num" toNum 0 4 h 1568 */
	{.type Absolute, {.p 0}},		/* 1576 */
	{.type Header, {.hdr { 5, "State", /* MV_State = 1592 */ variable }}}, /* MVENTRY "State" State 0 5 h 1600 */
	{.type Absolute, {.p 0}},		/* 1608 */
	{.type Header, {.hdr { 8, "Abortvec", /* MV_Abortvec = 1632 */ variable }}}, /* MVENTRY "Abortvec" Abortvec 0 8	; not sure if these 3 can be constants instead? h 1640 */
	{.type Absolute, {.p 0}},		/* 1648 */
	{.type Header, {.hdr { 4, "Infd", /* MV_Infd = 1664 */ variable }}}, /* MVENTRY "Infd" Infd 0 4 h 1672 */
	{.type Absolute, {.p 0}},		/* 1680 */
	{.type Header, {.hdr { 5, "Outfd", /* MV_Outfd = 1696 */ variable }}}, /* MVENTRY "Outfd" Outfd 0 5 h 1704 */
	{.type Absolute, {.p 0}},		/* 1712 */
	{.type Header, {.hdr { 5, "Errfd", /* MV_Errfd = 1728 */ variable }}}, /* MVENTRY "Errfd" Errfd 0 5 h 1736 */
	{.type Absolute, {.p 0}},		/* 1744 */
	{.type Header, {.hdr { 3, "Eof", /* MV_Eof = 1760 */ variable }}}, /* MVENTRY "Eof" Eof 0 3 h 1768 */
	{.type Absolute, {.p 0}},		/* 1776 */
	{.type Header, {.hdr { 5, "STDIN", /* MC_STDIN = 1792 */ constant }}}, /* MCENTRY "STDIN" STDIN 0 5		; 3 constants from here CAPITALS h 1800 */
	{.type Absolute, {.p 0}},		/* 1808 */
	{.type Header, {.hdr { 6, "STDOUT", /* MC_STDOUT = 1824 */ constant }}}, /* MCENTRY "STDOUT" STDOUT 1 6 h 1832 */
	{.type Absolute, {.p 1}},		/* 1840 */
	{.type Header, {.hdr { 6, "STDERR", /* MC_STDERR = 1856 */ constant }}}, /* MCENTRY "STDERR" STDERR 2 6 h 1864 */
	{.type Absolute, {.p 2}},		/* 1872 */
	{.type Header, {.hdr { 2, "S0", /* M_S0 = 1888 */ S0 }}}, /* MENTRY "S0" S0 2 h 1896 */
	{.type Header, {.hdr { 2, "s@", /* M_stackptr = 1912 */ stackptr }}}, /* MENTRY "s@" stackptr 2		; puts PSP on stack h 1920 */
	{.type Header, {.hdr { 2, "H0", /* M_H0 = 1936 */ H0 }}}, /* MENTRY "H0" H0 2 h 1944 */
	{.type Header, {.hdr { 5, "Wordb", /* M_Wordb = 1960 */ Wordb }}}, /* MENTRY "Wordb" Wordb 5 h 1968 */
	{.type Header, {.hdr { 3, "Tib", /* M_Tib = 1984 */ Tib }}}, /* MENTRY "Tib" Tib 3 h 1992 */
	{.type Header, {.hdr { 3, "Args", /* M_Args = 2008 */ Args }}}, /* MENTRY "Args" Args 3 h 2016 */
	{.type Header, {.hdr { 10, "(variable)", /* M_variable = 2040 */ variable }}}, /* MENTRY "(variable)" variable 10 h 2048 */
	{.type Header, {.hdr { 10, "(constant)", /* M_constant = 2072 */ constant }}}, /* MENTRY "(constant)" constant 10 h 2080 */
	{.type Header, {.hdr { 3, "(:)", /* M_colon = 2096 */ colon }}}, /* MENTRY "(:)" colon 3 h 2104 */
	{.type Header, {.hdr { 6, "(does)", /* M_dodoes = 2120 */ dodoes }}}, /* MENTRY "(does)" dodoes 6 h 2128 */
	{.type Header, {.hdr { 3, "cas", /* M_cas = 2144 */ cas }}}, /* MENTRY "cas" cas 3 h 2152 */
	{.type Header, {.hdr { 10, "(deferred)", /* M_deferred = 2176 */ deferred }}}, /* MENTRY "(deferred)" deferred 10 h 2184 */
	{.type Header, {.hdr { 5, "false", /* C_false = 2200 */ colon }}}, /* CENTRY "false" false 5 h 2208 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2216 */
	{.type Absolute, {.p 0}},		/* dd 0 2224 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2232 */
	{.type Header, {.hdr { 4, "true", /* C_true = 2248 */ colon }}}, /* CENTRY "true" true 4 h 2256 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2264 */
	{.type Absolute, {.p -1}},		/* dd -1 2272 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2280 */
	{.type Header, {.hdr { 2, "bl", /* C_bl = 2296 */ colon }}}, /* CENTRY "bl" bl 2 h 2304 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2312 */
	{.type Absolute, {.p 32}},		/* dd 32 2320 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2328 */
	{.type Header, {.hdr { 2, "on", /* C_on = 2344 */ colon }}}, /* CENTRY "on" on 2 ; ( a -- ) (G stores -1 at a ) h 2352 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2360 */
	{.type Absolute, {.p -1}},		/* dd -1 2368 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2376 */
	{.type FromH0, {.p M_store}},		/* dd M_store 2384 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2392 */
	{.type Header, {.hdr { 3, "off", /* C_off = 2408 */ colon }}}, /* CENTRY "off" off 3 ; ( a -- ) (G stores 0 at a ) h 2416 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2424 */
	{.type Absolute, {.p 0}},		/* dd 0 2432 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2440 */
	{.type FromH0, {.p M_store}},		/* dd M_store 2448 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2456 */
	{.type Header, {.hdr { 5, ">body", /* C_tobody = 2472 */ colon }}}, /* CENTRY ">body" tobody 5 h 2480 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2488 */
	{.type Absolute, {.p 8}},		/* dd 8 2496 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 2504 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2512 */
	{.type Header, {.hdr { 7, "aligned", /* C_aligned = 2528 */ colon }}}, /* CENTRY "aligned" aligned 7 h 2536 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2544 */
	{.type Absolute, {.p 7}},		/* dd 7 2552 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 2560 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2568 */
	{.type Absolute, {.p -8}},		/* dd -8 2576 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 2584 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2592 */
	{.type Header, {.hdr { 5, "cells", /* C_cells = 2608 */ colon }}}, /* CENTRY "cells" cells 5 h 2616 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2624 */
	{.type Absolute, {.p 3}},		/* dd 3			; (index << 2) -> (index << 3)for amd64 2632 */
	{.type FromH0, {.p M_lshift}},		/* dd M_lshift 2640 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2648 */
	{.type Header, {.hdr { 5, "cell+", /* C_cellplus = 2664 */ colon }}}, /* CENTRY "cell+" cellplus 5 h 2672 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2680 */
	{.type Absolute, {.p 1}},		/* dd 1 2688 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 2696 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 2704 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2712 */
	{.type Header, {.hdr { 5, "depth", /* C_depth = 2728 */ colon }}}, /* CENTRY "depth" depth 5 h 2736 */
	{.type FromH0, {.p M_S0}},		/* dd M_S0 2744 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr 2752 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 2760 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2768 */
	{.type Absolute, {.p 3}},		/* dd 3 2776 */
	{.type FromH0, {.p M_rshift}},		/* dd M_rshift 2784 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2792 */
	{.type Absolute, {.p 1}},		/* dd 1 2800 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 2808 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2816 */
	{.type Header, {.hdr { 3, "nip", /* C_nip = 2832 */ colon }}}, /* CENTRY "nip" nip 3 h 2840 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2848 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 2856 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2864 */
	{.type Header, {.hdr { 3, "rot", /* C_rot = 2880 */ colon }}}, /* CENTRY "rot" rot 3 h 2888 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 2896 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2904 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 2912 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2920 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2928 */
	{.type Header, {.hdr { 5, "2drop", /* C_2drop = 2944 */ colon }}}, /* CENTRY "2drop" 2drop 5 h 2952 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 2960 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 2968 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2976 */
	{.type Header, {.hdr { 4, "2dup", /* C_2dup = 2992 */ colon }}}, /* CENTRY "2dup" 2dup 4 h 3000 */
	{.type FromH0, {.p M_over}},		/* dd M_over 3008 */
	{.type FromH0, {.p M_over}},		/* dd M_over 3016 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3024 */
	{.type Header, {.hdr { 4, "2nip", /* C_2nip = 3040 */ colon }}}, /* CENTRY "2nip" 2nip 4 h 3048 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 3056 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 3064 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3072 */
	{.type Header, {.hdr { 5, "2swap", /* C_2swap = 3088 */ colon }}}, /* CENTRY "2swap" 2swap 5 h 3096 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot 3104 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 3112 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot 3120 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 3128 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3136 */
	{.type Header, {.hdr { 4, "?dup", /* C_qdup = 3152 */ colon }}}, /* CENTRY "?dup" qdup 4 ; if (tos != 0) dup ( n -- ) TODO correct stack notations h 3160 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n n -- ) 3168 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n n n -- ) 3176 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3184 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( n n n 0 -- ) 3192 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( n n f -- ) 3200 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump	; ( n n -- ) 3208 */
	{.type FromH0, {.p L20}},		/* dd L20 3216 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop	; tos == 0 ( n -- ) 3224 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3232 */
	{.type Header, {.hdr { 4, "pick", /* C_pick = 3248 */ colon }}}, /* CENTRY "pick" pick 4 h 3256 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 3264 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 3272 */
	{.type FromH0, {.p L22}},		/* dd L22 3280 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3288 */
	{.type Absolute, {.p 1}},		/* dd 1 3296 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3304 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 3312 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr 3320 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3328 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 3336 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 3344 */
	{.type FromH0, {.p L23}},		/* dd L23 3352 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 3360 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3368 */
	{.type Header, {.hdr { 4, "tuck", /* C_tuck = 3384 */ colon }}}, /* CENTRY "tuck" tuck 4 h 3392 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 3400 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 3408 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 3416 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 3424 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3432 */
	{.type Header, {.hdr { 1, "/", /* C_divides = 3448 */ colon }}}, /* CENTRY "/" divides 1 h 3456 */
	{.type FromH0, {.p M_slashmod}},		/* dd M_slashmod 3464 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 3472 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3480 */
	{.type Header, {.hdr { 2, "+!", /* C_plusstore = 3496 */ colon }}}, /* CENTRY "+!" plusstore 2 h 3504 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 3512 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 3520 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot 3528 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3536 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 3544 */
	{.type FromH0, {.p M_store}},		/* dd M_store 3552 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3560 */
	{.type Header, {.hdr { 6, "invert", /* C_invert = 3576 */ colon }}}, /* CENTRY "invert" invert 6 h 3584 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3592 */
	{.type Absolute, {.p -1}},		/* dd -1 3600 */
	{.type FromH0, {.p M_binxor}},		/* dd M_binxor 3608 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3616 */
	{.type Header, {.hdr { 3, "mod", /* C_mod = 3632 */ colon }}}, /* CENTRY "mod" mod 3 h 3640 */
	{.type FromH0, {.p M_slashmod}},		/* dd M_slashmod 3648 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 3656 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3664 */
	{.type Header, {.hdr { 2, "1+", /* C_1plus = 3680 */ colon }}}, /* CENTRY "1+" 1plus 2 h 3688 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3696 */
	{.type Absolute, {.p 1}},		/* dd 1 3704 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3712 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3720 */
	{.type Header, {.hdr { 2, "1-", /* C_1minus = 3736 */ colon }}}, /* CENTRY "1-" 1minus 2 h 3744 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3752 */
	{.type Absolute, {.p 1}},		/* dd 1 3760 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 3768 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3776 */
	{.type Header, {.hdr { 6, "negate", /* C_negate = 3792 */ colon }}}, /* CENTRY "negate" negate 6 h 3800 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3808 */
	{.type Absolute, {.p 0}},		/* dd 0 3816 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 3824 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 3832 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3840 */
	{.type Header, {.hdr { 2, "2*", /* C_2multiplies = 3856 */ colon }}}, /* CENTRY "2*" 2multiplies 2 h 3864 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3872 */
	{.type Absolute, {.p 1}},		/* dd 1 3880 */
	{.type FromH0, {.p M_lshift}},		/* dd M_lshift 3888 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3896 */
	{.type Header, {.hdr { 2, "2/", /* C_2divides = 3912 */ colon }}}, /* CENTRY "2/" 2divides 2 h 3920 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3928 */
	{.type Absolute, {.p 1}},		/* dd 1 3936 */
	{.type FromH0, {.p M_rshifta}},		/* dd M_rshifta 3944 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3952 */
	{.type Header, {.hdr { 2, "0=", /* C_0eq = 3968 */ colon }}}, /* CENTRY "0=" 0eq 2 h 3976 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3984 */
	{.type Absolute, {.p 0}},		/* dd 0 3992 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal 4000 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4008 */
	{.type Header, {.hdr { 2, "0<", /* C_0lt = 4024 */ colon }}}, /* CENTRY "0<" 0lt 2 h 4032 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4040 */
	{.type Absolute, {.p 0}},		/* dd 0 4048 */
	{.type FromH0, {.p M_less}},		/* dd M_less 4056 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4064 */
	{.type Header, {.hdr { 2, "0>", /* C_0gt = 4080 */ colon }}}, /* CENTRY "0>" 0gt 2 h 4088 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4096 */
	{.type Absolute, {.p 0}},		/* dd 0 4104 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4112 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4120 */
	{.type Header, {.hdr { 2, "<>", /* C_neq = 4136 */ colon }}}, /* CENTRY "<>" neq 2 h 4144 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal 4152 */
	{.type FromH0, {.p C_invert}},		/* dd C_invert 4160 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4168 */
	{.type Header, {.hdr { 3, "0<>", /* C_0neq = 4184 */ colon }}}, /* CENTRY "0<>" 0neq 3 h 4192 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4200 */
	{.type Absolute, {.p 0}},		/* dd 0 4208 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 4216 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4224 */
	{.type Header, {.hdr { 3, "max", /* C_max = 4240 */ colon }}}, /* CENTRY "max" max 3 h 4248 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 4256 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4264 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4272 */
	{.type FromH0, {.p L40}},		/* dd L40 4280 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 4288 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4296 */
	{.type FromH0, {.p L41}},		/* dd L41 4304 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 4312 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4320 */
	{.type Header, {.hdr { 3, "min", /* C_min = 4336 */ colon }}}, /* CENTRY "min" min 3 h 4344 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 4352 */
	{.type FromH0, {.p M_less}},		/* dd M_less 4360 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4368 */
	{.type FromH0, {.p L43}},		/* dd L43 4376 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 4384 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4392 */
	{.type FromH0, {.p L44}},		/* dd L44 4400 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 4408 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4416 */
	{.type Header, {.hdr { 6, "signum", /* C_signum = 4432 */ colon }}}, /* CENTRY "signum" signum 6 h 4440 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 4448 */
	{.type FromH0, {.p C_0gt}},		/* dd C_0gt 4456 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4464 */
	{.type FromH0, {.p L46}},		/* dd L46 4472 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 4480 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4488 */
	{.type Absolute, {.p 1}},		/* dd 1 4496 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4504 */
	{.type FromH0, {.p L47}},		/* dd L47 4512 */
	{.type FromH0, {.p C_0lt}},		/* dd C_0lt 4520 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4528 */
	{.type FromH0, {.p L48}},		/* dd L48 4536 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4544 */
	{.type Absolute, {.p -1}},		/* dd -1 4552 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4560 */
	{.type FromH0, {.p L49}},		/* dd L49 4568 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4576 */
	{.type Absolute, {.p 0}},		/* dd 0 4584 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4592 */
	{.type Header, {.hdr { 6, "within", /* C_within = 4608 */ colon }}}, /* CENTRY "within" within 6 h 4616 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 4624 */
	{.type FromH0, {.p M_over}},		/* dd M_over 4632 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4640 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 4648 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 4656 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 4664 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4672 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 4680 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 4688 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4696 */
	{.type Header, {.hdr { 3, "abs", /* C_abs = 4712 */ colon }}}, /* CENTRY "abs" abs 3 h 4720 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 4728 */
	{.type FromH0, {.p C_0lt}},		/* dd C_0lt 4736 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4744 */
	{.type FromH0, {.p L52}},		/* dd L52 4752 */
	{.type FromH0, {.p C_negate}},		/* dd C_negate 4760 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4768 */
	{.type Header, {.hdr { 3, "key", /* C_key = 4784 */ colon }}}, /* CENTRY "key" key 3 ; ( -- c ) (G read a single character from the input onto the stack ) h 4792 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4800 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( 1 -- ) 4808 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf to store the character read 4816 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 4824 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; ( 1 Iobuf -- 1 Iobuf infd ) 4832 */
	{.type FromH0, {.p M_fthread}},		/* dd M_fthread	; ( 1 Iobuf infd -- n ) 4840 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 4848 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump		; if 0 characters read 4856 */
	{.type FromH0, {.p L78}},		/* dd L78			; if qread n != 0 jump to L78. If n == 0 jump over 4864 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 4872 */
	{.type FromH0, {.p C_on}},		/* dd C_on		; EOF 4880 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4888 */
	{.type Absolute, {.p -1}},		/* dd -1			; return -1 when EOF 4896 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4904 */
	{.type FromH0, {.p L79}},		/* dd L79 4912 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; get the character from Iobuf to stack 4920 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch	; ( -- c ) return the character read if not EOF 4928 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4936 */
	{.type Header, {.hdr { 4, "emit", /* C_emit = 4952 */ colon }}}, /* CENTRY "emit" emit 4 ; ( character -- ) h 4960 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf address 4968 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; variable iobuf has character 4976 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf address 4984 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4992 */
	{.type Absolute, {.p 1}},		/* dd 1 5000 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap		; ( iobuf 1 --  1 iobuf ) 5008 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 5016 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; outfd 5024 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite	; ( 1 iobuf outfd --  ) 5032 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; drop the return value of write 5040 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5048 */
	{.type Header, {.hdr { 4, "type", /* C_type = 5064 */ colon }}}, /* CENTRY "type" type 4 ; ( addr n -- ) h 5072 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap			; ( addr n --  n addr ) 5080 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5088 */
	{.type Absolute, {.p 1}},		/* dd 1				; stdout 5096 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite			; ( n addr 1 --  ) 5104 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; drop the return value of write 5112 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5120 */
	{.type Header, {.hdr { 2, "cr", /* C_cr = 5136 */ colon }}}, /* CENTRY "cr" cr 2 h 5144 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5152 */
	{.type Absolute, {.p 10}},		/* dd 10			; ascii value of carriage return 5160 */
	{.type FromH0, {.p C_emit}},		/* dd C_emit			; emit 5168 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5176 */
	{.type Header, {.hdr { 5, "space", /* C_space = 5192 */ colon }}}, /* CENTRY "space" space 5 h 5200 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 5208 */
	{.type FromH0, {.p C_emit}},		/* dd C_emit 5216 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5224 */
	{.type Header, {.hdr { 5, "emits", /* C_emits = 5240 */ colon }}}, /* CENTRY "emits" emits 5 h 5248 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 5256 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 5264 */
	{.type FromH0, {.p L86}},		/* dd L86 5272 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5280 */
	{.type FromH0, {.p C_emit}},		/* dd C_emit 5288 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 5296 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 5304 */
	{.type FromH0, {.p L85}},		/* dd L85 5312 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 5320 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5328 */
	{.type Header, {.hdr { 6, "spaces", /* C_spaces = 5344 */ colon }}}, /* CENTRY "spaces" spaces 6 h 5352 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 5360 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 5368 */
	{.type FromH0, {.p C_emits}},		/* dd C_emits 5376 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5384 */
	{.type Header, {.hdr { 5, "count", /* C_count = 5400 */ colon }}}, /* CENTRY "count" count 5 ; ( a -- a+1 n ) a = counted string h 5408 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 5416 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 5424 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 5432 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 5440 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5448 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup ; debug show the word name to search 5456 */
	{.type FromH0, {.p C_type}},		/* dd C_type 5464 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush ; debug show the dictionary entry 5472 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 5480 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 5488 */
	{.type FromH0, {.p C_type}},		/* dd C_type 5496 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 5504 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 5512 */
	{.type Header, {.hdr { 7, "compare", /* C_compare = 5528 */ colon }}}, /* CENTRY "compare" compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search h 5536 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 5544 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 ) 5552 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- ) 5560 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- ) 5568 */
	{.type FromH0, {.p C_min}},		/* dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- ) 5576 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5584 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- ) 5592 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- ) 5600 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5608 */
	{.type FromH0, {.p M_i}},		/* dd M_i 5616 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 5624 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 5632 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5640 */
	{.type FromH0, {.p M_i}},		/* dd M_i 5648 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 5656 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 5664 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 5672 */
	{.type FromH0, {.p C_signum}},		/* dd C_signum 5680 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 5688 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 5696 */
	{.type FromH0, {.p L56}},		/* dd L56		; matches 5704 */
	{.type FromH0, {.p C_2nip}},		/* dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- ) 5712 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2) 5720 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop	; ( f -- f ) (R n1 n2 -- ) 5728 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5736 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 5744 */
	{.type FromH0, {.p L55}},		/* dd L55 5752 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- ) 5760 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 5768 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( n2 n1 -- ) (R -- ) 5776 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( -- n1-n2 ) 5784 */
	{.type FromH0, {.p C_signum}},		/* dd C_signum 5792 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5800 */
	{.type Header, {.hdr { 5, "erase", /* C_erase = 5816 */ colon }}}, /* CENTRY "erase" erase 5 h 5824 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5832 */
	{.type Absolute, {.p 0}},		/* dd 0 5840 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 5848 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5856 */
	{.type Absolute, {.p 0}},		/* dd 0 5864 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5872 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 5880 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 5888 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 5896 */
	{.type FromH0, {.p L58}},		/* dd L58 5904 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 5912 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5920 */
	{.type Header, {.hdr { 4, "fill", /* C_fill = 5936 */ colon }}}, /* CENTRY "fill" fill 4 h 5944 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 5952 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5960 */
	{.type Absolute, {.p 0}},		/* dd 0 5968 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 5976 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 5984 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 5992 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6000 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6008 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 6016 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 6024 */
	{.type FromH0, {.p L60}},		/* dd L60 6032 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop 6040 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6048 */
	{.type Header, {.hdr { 5, "blank", /* C_blank = 6064 */ colon }}}, /* CENTRY "blank" blank 5 h 6072 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 6080 */
	{.type FromH0, {.p C_fill}},		/* dd C_fill 6088 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6096 */
	{.type Header, {.hdr { 6, "search", /* C_search = 6112 */ colon }}}, /* CENTRY "search" search 6 h 6120 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6128 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6136 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6144 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 6152 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 6160 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6168 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6176 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 6184 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 6192 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6200 */
	{.type Absolute, {.p 0}},		/* dd 0 6208 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 6216 */
	{.type FromH0, {.p M_over}},		/* dd M_over 6224 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6232 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6240 */
	{.type FromH0, {.p M_over}},		/* dd M_over 6248 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6256 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6264 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6272 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6280 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6288 */
	{.type FromH0, {.p C_compare}},		/* dd C_compare 6296 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 6304 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 6312 */
	{.type FromH0, {.p L65}},		/* dd L65 6320 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 6328 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6336 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6344 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6352 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop 6360 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 6368 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6376 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 6384 */
	{.type FromH0, {.p C_true}},		/* dd C_true 6392 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6400 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 6408 */
	{.type FromH0, {.p L64}},		/* dd L64 6416 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 6424 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 6432 */
	{.type FromH0, {.p C_false}},		/* dd C_false 6440 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6448 */
	{.type Header, {.hdr { 4, "here", /* C_here = 6464 */ colon }}}, /* CENTRY "here" here 4 h 6472 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6480 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6488 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6496 */
	{.type Header, {.hdr { 1, ",", /* C_comma = 6512 */ colon }}}, /* CENTRY "," comma 1 h 6520 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6528 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6536 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6544 */
	{.type Absolute, {.p 8}},		/* dd 8 6552 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6560 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore 6568 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6576 */
	{.type Header, {.hdr { 2, "c,", /* C_c = 6592 */ colon }}}, /* CENTRY "c," c 2 h 6600 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6608 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 6616 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6624 */
	{.type Absolute, {.p 1}},		/* dd 1 6632 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6640 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore 6648 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6656 */
	{.type Header, {.hdr { 5, "allot", /* C_allot = 6672 */ colon }}}, /* CENTRY "allot" allot 5 h 6680 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6688 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore 6696 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6704 */
	{.type Header, {.hdr { 3, "pad", /* C_pad = 6720 */ colon }}}, /* CENTRY "pad" pad 3 h 6728 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6736 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6744 */
	{.type Absolute, {.p 256}},		/* dd 256 6752 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6760 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6768 */
	{.type Header, {.hdr { 5, "align", /* C_align = 6784 */ colon }}}, /* CENTRY "align" align 5 h 6792 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6800 */
	{.type FromH0, {.p C_aligned}},		/* dd C_aligned 6808 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6816 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6824 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6832 */
	{.type Header, {.hdr { 6, "unused", /* C_unused = 6848 */ colon }}}, /* CENTRY "unused" unused 6 h 6856 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6864 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6872 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6880 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 6888 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6896 */
	{.type Header, {.hdr { 2, "<#", /* C_fromhash = 6912 */ colon }}}, /* CENTRY "<#" fromhash 2 h 6920 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 6928 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6936 */
	{.type Absolute, {.p 1024}},		/* dd 1024 6944 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6952 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 6960 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6968 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6976 */
	{.type Header, {.hdr { 1, "#", /* C_hash = 6992 */ colon }}}, /* CENTRY "#" hash 1 h 7000 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 7008 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7016 */
	{.type FromH0, {.p M_uslashmod}},		/* dd M_uslashmod 7024 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7032 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7040 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7048 */
	{.type Absolute, {.p 9}},		/* dd 9 7056 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 7064 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 7072 */
	{.type FromH0, {.p L92}},		/* dd L92 7080 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7088 */
	{.type Absolute, {.p 97}},		/* dd 97 7096 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7104 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7112 */
	{.type Absolute, {.p 10}},		/* dd 10 7120 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 7128 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 7136 */
	{.type FromH0, {.p L93}},		/* dd L93 7144 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7152 */
	{.type Absolute, {.p 48}},		/* dd 48 7160 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7168 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7176 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7184 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 7192 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7200 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7208 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7216 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 7224 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7232 */
	{.type Header, {.hdr { 2, "#s", /* C_hashs = 7248 */ colon }}}, /* CENTRY "#s" hashs 2 h 7256 */
	{.type FromH0, {.p C_hash}},		/* dd C_hash 7264 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7272 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 7280 */
	{.type FromH0, {.p L96}},		/* dd L96 7288 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 7296 */
	{.type FromH0, {.p L95}},		/* dd L95 7304 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7312 */
	{.type Header, {.hdr { 2, "#>", /* C_hashfrom = 7328 */ colon }}}, /* CENTRY "#>" hashfrom 2 h 7336 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 7344 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7352 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7360 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7368 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 7376 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7384 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7392 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7400 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7408 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 7416 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7424 */
	{.type Header, {.hdr { 4, "hold", /* C_hold = 7440 */ colon }}}, /* CENTRY "hold" hold 4 h 7448 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7456 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7464 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 7472 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7480 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 7488 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 7496 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 7504 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7512 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7520 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7528 */
	{.type Header, {.hdr { 4, "sign", /* C_sign = 7544 */ colon }}}, /* CENTRY "sign" sign 4 h 7552 */
	{.type FromH0, {.p C_0lt}},		/* dd C_0lt 7560 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 7568 */
	{.type FromH0, {.p L100}},		/* dd L100 7576 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7584 */
	{.type Absolute, {.p 45}},		/* dd 45 7592 */
	{.type FromH0, {.p C_hold}},		/* dd C_hold 7600 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7608 */
	{.type Header, {.hdr { 1, ".", /* C_dot = 7624 */ colon }}}, /* CENTRY "." dot 1 h 7632 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7640 */
	{.type FromH0, {.p C_abs}},		/* dd C_abs 7648 */
	{.type FromH0, {.p C_fromhash}},		/* dd C_fromhash 7656 */
	{.type FromH0, {.p C_hashs}},		/* dd C_hashs 7664 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7672 */
	{.type FromH0, {.p C_sign}},		/* dd C_sign 7680 */
	{.type FromH0, {.p C_hashfrom}},		/* dd C_hashfrom 7688 */
	{.type FromH0, {.p C_type}},		/* dd C_type 7696 */
	{.type FromH0, {.p C_space}},		/* dd C_space 7704 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7712 */
	{.type Header, {.hdr { 2, ".r", /* C_dotr = 7728 */ colon }}}, /* CENTRY ".r" dotr 2 h 7736 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 7744 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7752 */
	{.type FromH0, {.p C_abs}},		/* dd C_abs 7760 */
	{.type FromH0, {.p C_fromhash}},		/* dd C_fromhash 7768 */
	{.type FromH0, {.p C_hashs}},		/* dd C_hashs 7776 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7784 */
	{.type FromH0, {.p C_sign}},		/* dd C_sign 7792 */
	{.type FromH0, {.p C_hashfrom}},		/* dd C_hashfrom 7800 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 7808 */
	{.type FromH0, {.p M_over}},		/* dd M_over 7816 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 7824 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7832 */
	{.type Absolute, {.p 0}},		/* dd 0 7840 */
	{.type FromH0, {.p C_max}},		/* dd C_max 7848 */
	{.type FromH0, {.p C_spaces}},		/* dd C_spaces 7856 */
	{.type FromH0, {.p C_type}},		/* dd C_type 7864 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7872 */
	{.type Header, {.hdr { 3, "hex", /* C_hex = 7888 */ colon }}}, /* CENTRY "hex" hex 3 h 7896 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7904 */
	{.type Absolute, {.p 16}},		/* dd 16 7912 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 7920 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7928 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7936 */
	{.type Header, {.hdr { 7, "decimal", /* C_decimal = 7952 */ colon }}}, /* CENTRY "decimal" decimal 7 h 7960 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7968 */
	{.type Absolute, {.p 10}},		/* dd 10 7976 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 7984 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7992 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8000 */
	{.type Header, {.hdr { 5, "digit", /* C_digit = 8016 */ colon }}}, /* CENTRY "digit" digit 5 ; c -- h 8024 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8032 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8040 */
	{.type Absolute, {.p 65}},		/* dd 65 8048 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8056 */
	{.type Absolute, {.p 91}},		/* dd 91 8064 */
	{.type FromH0, {.p C_within}},		/* dd C_within 8072 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8080 */
	{.type FromH0, {.p L106}},		/* dd L106 8088 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8096 */
	{.type Absolute, {.p 55}},		/* dd 55 8104 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 8112 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8120 */
	{.type FromH0, {.p L107}},		/* dd L107 8128 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8136 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8144 */
	{.type Absolute, {.p 97}},		/* dd 97 8152 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8160 */
	{.type Absolute, {.p 123}},		/* dd 123 8168 */
	{.type FromH0, {.p C_within}},		/* dd C_within 8176 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8184 */
	{.type FromH0, {.p L108}},		/* dd L108 8192 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8200 */
	{.type Absolute, {.p 87}},		/* dd 87 8208 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 8216 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8224 */
	{.type FromH0, {.p L109}},		/* dd L109 8232 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8240 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8248 */
	{.type Absolute, {.p 48}},		/* dd 48 8256 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8264 */
	{.type Absolute, {.p 58}},		/* dd 58 8272 */
	{.type FromH0, {.p C_within}},		/* dd C_within 8280 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8288 */
	{.type FromH0, {.p L110}},		/* dd L110 8296 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8304 */
	{.type Absolute, {.p 48}},		/* dd 48 8312 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 8320 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8328 */
	{.type FromH0, {.p L111}},		/* dd L111 8336 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8344 */
	{.type FromH0, {.p C_false}},		/* dd C_false 8352 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8360 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8368 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 8376 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8384 */
	{.type FromH0, {.p M_less}},		/* dd M_less 8392 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8400 */
	{.type FromH0, {.p L112}},		/* dd L112 8408 */
	{.type FromH0, {.p C_true}},		/* dd C_true 8416 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8424 */
	{.type FromH0, {.p L113}},		/* dd L113 8432 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8440 */
	{.type FromH0, {.p C_false}},		/* dd C_false 8448 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8456 */
	{.type Header, {.hdr { 6, "number", /* C_number = 8472 */ colon }}}, /* CENTRY "number" number 6 ; ( a n1 -- n2 -1 | a n1 0 ) h 8480 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap	; ( a n1 -- n1 a ) 8488 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n1 a -- n1 a a ) 8496 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch	; ( n1 a a -- n1 a c ) 8504 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8512 */
	{.type Absolute, {.p 45}},		/* dd 45		; ( n1 a c -- n1 a c - ) 8520 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( n1 a c -- n1 a f ) 8528 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump	; ( n1 a c -- n1 a ) 8536 */
	{.type FromH0, {.p L115}},		/* dd L115		; c != - 8544 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus	; c == - ( n1 a -- n1 a+1 ) 8552 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 8560 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 ) 8568 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8576 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( a+1 n1-1 -- a+1 n1-1 -1 ) 8584 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1) 8592 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8600 */
	{.type FromH0, {.p L116}},		/* dd L116 8608 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap	; ( n1 a -- a n1) 8616 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8624 */
	{.type Absolute, {.p 1}},		/* dd 1 8632 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1) 8640 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( a n1 -- a n1 n1 ) (R nr) 8648 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1) 8656 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8664 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a n1 -- a n1 0) (R nr n1) 8672 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1) 8680 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8688 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a 0 n1 -- a 0 n1 0) (R nr n1) 8696 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1) 8704 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 8712 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1) 8720 */
	{.type FromH0, {.p M_multiply}},		/* dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1) 8728 */
	{.type FromH0, {.p M_over}},		/* dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1) 8736 */
	{.type FromH0, {.p M_i}},		/* dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1) 8744 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1) 8752 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1) 8760 */
	{.type FromH0, {.p C_digit}},		/* dd C_digit 8768 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8776 */
	{.type FromH0, {.p L118}},		/* dd L118 8784 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 8792 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8800 */
	{.type FromH0, {.p L119}},		/* dd L119 8808 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8816 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop 8824 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8832 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8840 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8848 */
	{.type FromH0, {.p C_false}},		/* dd C_false 8856 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8864 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 8872 */
	{.type FromH0, {.p L117}},		/* dd L117 8880 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8888 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8896 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 8904 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8912 */
	{.type FromH0, {.p M_multiply}},		/* dd M_multiply 8920 */
	{.type FromH0, {.p C_true}},		/* dd C_true 8928 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8936 */
	{.type Header, {.hdr { 5, "abort", /* C_abort = 8952 */ colon }}}, /* CENTRY "abort" abort 5 h 8960 */
	{.type FromH0, {.p MV_Abortvec}},		/* dd MV_Abortvec 8968 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8976 */
	{.type FromH0, {.p M_execute}},		/* dd M_execute 8984 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8992 */
	{.type Header, {.hdr { 6, "source", /* C_source = 9008 */ colon }}}, /* CENTRY "source" source 6 h 9016 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9024 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9032 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9040 */
	{.type Header, {.hdr { 13, "current-input", /* C_current_input = 9064 */ colon }}}, /* CENTRY "current-input" current_input 13 ; ( -- c ) read the next character from the location in Sourcebuf h 9072 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9080 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9088 */
	{.type FromH0, {.p C_source}},		/* dd C_source 9096 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus		; Sourcebuf + >In 9104 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 9112 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9120 */
	{.type Header, {.hdr { 10, "save-input", /* C_save_input = 9144 */ colon }}}, /* CENTRY "save-input" save_input 10 h 9152 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 9160 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9168 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9176 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9184 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9192 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9200 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9208 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 9216 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9224 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9232 */
	{.type Absolute, {.p 5}},		/* dd 5 9240 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9248 */
	{.type Header, {.hdr { 13, "default-input", /* C_default_input = 9272 */ colon }}}, /* CENTRY "default-input" default_input 13 h 9280 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 9288 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9296 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9304 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9312 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9320 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib 9328 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9336 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9344 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 9352 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9360 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9368 */
	{.type Header, {.hdr { 13, "restore-input", /* C_restore_input = 9392 */ colon }}}, /* CENTRY "restore-input" restore_input 13 ; ( -- f ) h 9400 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 9408 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9416 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9424 */
	{.type Absolute, {.p 5}},		/* dd 5 9432 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 9440 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9448 */
	{.type FromH0, {.p L133}},		/* dd L133 9456 */
	{.type FromH0, {.p C_default_input}},		/* dd C_default_input 9464 */
	{.type FromH0, {.p C_false}},		/* dd C_false 9472 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 9480 */
	{.type FromH0, {.p L134}},		/* dd L134 9488 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 9496 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9504 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9512 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9520 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9528 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9536 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9544 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9552 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 9560 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9568 */
	{.type FromH0, {.p C_true}},		/* dd C_true 9576 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9584 */
	{.type Header, {.hdr { 14, "?restore-input", /* C_qrestore_input = 9608 */ colon }}}, /* CENTRY "?restore-input" qrestore_input 14 ; ( -- ) h 9616 */
	{.type FromH0, {.p C_restore_input}},		/* dd C_restore_input 9624 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 9632 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9640 */
	{.type FromH0, {.p L136}},		/* dd L136 9648 */
	{.type FromH0, {.p C_space}},		/* dd C_space 9656 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9664 */
	{.type FromH0, {.p L137}},		/* dd L137 9672 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9680 */
	{.type Absolute, {.p 23}},		/* dd 23 9688 */
	{.type FromH0, {.p C_type}},		/* dd C_type 9696 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 9704 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 9712 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9720 */
	{.type Header, {.hdr { 10, "next-input", /* C_next_input = 9744 */ colon }}}, /* CENTRY "next-input" next_input 10 ; when >In < >Limit ( -- true c ). ( -- 0 false ) otherwise h 9752 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9760 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9768 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9776 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9784 */
	{.type FromH0, {.p M_less}},		/* dd M_less 9792 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9800 */
	{.type FromH0, {.p L139}},		/* dd L139	; >In >= >Limit 9808 */
	{.type FromH0, {.p C_true}},		/* dd C_true	; >In < >Limit 9816 */
	{.type FromH0, {.p C_current_input}},		/* dd C_current_input	; ( -- c ) 9824 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 9832 */
	{.type FromH0, {.p L140}},		/* dd L140 9840 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9848 */
	{.type Absolute, {.p 0}},		/* dd 0 9856 */
	{.type FromH0, {.p C_false}},		/* dd C_false 9864 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9872 */
	{.type Header, {.hdr { 5, "parse", /* C_parse = 9888 */ colon }}}, /* CENTRY "parse" parse 5 ; ( c -- a ) Place the counted string in the address in Wordbuf and return that address. c = word delimiter. h 9896 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush		; ( c -- ) (R -- c ) 9904 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf 9912 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; ( -- Wordb ) 9920 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus		; ( Wordb -- Wordb+1 ) 9928 */
	{.type FromH0, {.p C_next_input}},		/* dd C_next_input ; ( Wordb+1 -- Wordb+1 f c ) 9936 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c ) 9944 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) ) 9952 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 9960 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9968 */
	{.type FromH0, {.p L143}},		/* dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew 9976 */
	{.type FromH0, {.p C_current_input}},		/* dd C_current_input	; ( Wordb+1 -- Wordb+1 c ) 9984 */
	{.type FromH0, {.p M_over}},		/* dd M_over 9992 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1 10000 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus		; ( Wordb+1 -- Wordb+2 ) 10008 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10016 */
	{.type Absolute, {.p 1}},		/* dd 1 10024 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 10032 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; >In++ 10040 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10048 */
	{.type FromH0, {.p L142}},		/* dd L142		; ( Wordb+2 ) repeat 10056 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10064 */
	{.type Absolute, {.p 1}},		/* dd 1 10072 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 10080 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; >In++ 10088 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- ) 10096 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; (Wordb+1 c -- Wordb+1) 10104 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf 10112 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb) 10120 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb) 10128 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb) 10136 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb) 10144 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb) 10152 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb) 10160 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now. 10168 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop		; ( -- Wordb) (R Wordb -- ) 10176 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10184 */
	{.type Header, {.hdr { 4, "word", /* C_word = 10200 */ colon }}}, /* CENTRY "word" word 4 ; ( c -- a ) skip the c"s. Placed the counted string in a (as in Wordbuf) h 10208 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( -- ) (R -- c ) 10216 */
	{.type FromH0, {.p C_next_input}},		/* dd C_next_input ; ( -- f c2 ) (R c1 -- ) 10224 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial ) 10232 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial ) 10240 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial ) 10248 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10256 */
	{.type FromH0, {.p L146}},		/* dd L146		; >In >= >Limit || cinitial != cnew 10264 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal	; >In < >Limit && cinitial == cnew 10272 */
	{.type Absolute, {.p 1}},		/* dd 1 10280 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 10288 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; >In++ 10296 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump		; repeat 10304 */
	{.type FromH0, {.p L145}},		/* dd L145 10312 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character 10320 */
	{.type FromH0, {.p C_parse}},		/* dd C_parse 10328 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10336 */
	{.type Header, {.hdr { 6, "accept", /* C_accept = 10352 */ colon }}}, /* CENTRY "accept" accept 6 ; ( a n -- n ) get line or n chars or EOF from input and store at a h 10360 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap	; ( n a -- ) 10368 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n a a -- ) 10376 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 10384 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( n -- ) (R a a -- ) 10392 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup	; ( n n -- ) (R a a -- ) 10400 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump	; (if) 10408 */
	{.type FromH0, {.p L149}},		/* dd L149	; n == 0 10416 */
	{.type FromH0, {.p C_key}},		/* dd C_key	; n > 0 ( n -- n c ) 10424 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( -- n c c ) 10432 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10440 */
	{.type Absolute, {.p 10}},		/* dd 10		; ( -- n c c 10 ) 10448 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( n c c 10 -- n c f ) checking for newline 10456 */
	{.type FromH0, {.p M_over}},		/* dd M_over	; ( -- n c f c ) 10464 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10472 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( -- n c f c -1 ) 10480 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( -- n c f1 f2 ) 10488 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor	; ( -- n c f ) 10496 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10504 */
	{.type FromH0, {.p L150}},		/* dd L150 10512 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop	; n == -1 || n == 10 (	-- ) 10520 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 10528 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 10536 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( -- a2-a1 ) 10544 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon	; ( -- n ) (R -- ) 10552 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch	; ( n c a -- ) (R a a -- ) 10560 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; store the character at a 10568 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( n a -- ) (R a -- ) 10576 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 10584 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address 10592 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus	; ( n -- n-1 ) 10600 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10608 */
	{.type FromH0, {.p L148}},		/* dd L148	; loop again for the next character 10616 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 ) 10624 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( a2 a1 -- ) (R a1 -- ) 10632 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( a2 a1 -- a2-a1 ) 10640 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10648 */
	{.type Header, {.hdr { 5, "query", /* C_query = 10664 */ colon }}}, /* CENTRY "query" query 5 ; read from input stream into the Text Input Buffer h 10672 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 10680 */
	{.type FromH0, {.p C_off}},		/* dd C_off		; clear EOF flag 10688 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib	; constant puts address of tibuffer on the top 10696 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10704 */
	{.type Absolute, {.p 4096}},		/* dd 4096	; ( tibuffer -- tibuffer 4096 ) 10712 */
	{.type FromH0, {.p C_accept}},		/* dd C_accept ; ( tibuffer 4096 -- n ) 10720 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n -- n n ) 10728 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq	; ( n n -- n f ) 10736 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 10744 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 10752 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; n == 0 && EOF 10760 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10768 */
	{.type FromH0, {.p L152}},		/* dd L152		; false condition 10776 */
/* ; get out instead of M_drop and then C_qrestore_input */	{.type FromH0, {.p M_terminate}},		/* dd M_terminate ;	dd M_drop	; n == 0 && EOF ( n -- ) 10784 */
	{.type FromH0, {.p C_qrestore_input}},		/* dd C_qrestore_input 10792 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10800 */
	{.type FromH0, {.p L153}},		/* dd L153 10808 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 10816 */
	{.type FromH0, {.p M_store}},		/* dd M_store		; number of characters to read >Limit = n 10824 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 10832 */
	{.type FromH0, {.p C_off}},		/* dd C_off		; start from 0 >In = 0 10840 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10848 */
	{.type Header, {.hdr { 6, "refill", /* C_refill = 10864 */ colon }}}, /* CENTRY "refill" refill 6 h 10872 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 10880 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 10888 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10896 */
	{.type FromH0, {.p L155}},		/* dd L155 10904 */
	{.type FromH0, {.p C_false}},		/* dd C_false 10912 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10920 */
	{.type FromH0, {.p L156}},		/* dd L156 10928 */
	{.type FromH0, {.p C_query}},		/* dd C_query 10936 */
	{.type FromH0, {.p C_true}},		/* dd C_true 10944 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10952 */
	{.type Header, {.hdr { 8, "findname", /* C_findname = 10976 */ colon }}}, /* CENTRY "findname" findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names h 10984 */
	{.type FromH0, {.p MV_Findadr}},		/* dd MV_Findadr 10992 */
	{.type FromH0, {.p M_store}},		/* dd M_store 11000 */
	{.type FromH0, {.p M_Dtop}},		/* dd M_Dtop 11008 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; get latest dictionary link 11016 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 11024 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11032 */
	{.type FromH0, {.p L159}},		/* dd L159	; seached until the first dictionary entry get out 11040 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( a -- a a ) 11048 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus	; ( a a -- a a+8) lenth + initial name address 11056 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name 11064 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11072 */
	{.type Absolute, {.p 64}},		/* dd 64		; check the reveal'ed flag 1=hidden, 0=reveal 11080 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; if hidden, goto L161 else L160 11088 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11096 */
	{.type FromH0, {.p L160}},		/* dd L160 11104 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; smudge'd dictionary entry, get the previous entry 11112 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11120 */
	{.type FromH0, {.p L161}},		/* dd L161 11128 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( a1 -- a1 a1) 11136 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus	; ( a1 a1 -- a1 a1+8) 11144 */
	{.type FromH0, {.p C_count}},		/* dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n ) 11152 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11160 */
	{.type Absolute, {.p 63}},		/* dd 63 11168 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len ) 11176 */
	{.type FromH0, {.p MV_Findadr}},		/* dd MV_Findadr 11184 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 11192 */
	{.type FromH0, {.p C_count}},		/* dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 ) 11200 */
	{.type FromH0, {.p C_compare}},		/* dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name 11208 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq	; found a match? 11216 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11224 */
	{.type FromH0, {.p L162}},		/* dd L162		; no match 11232 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus	; match found 11240 */
	{.type FromH0, {.p C_true}},		/* dd C_true 11248 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11256 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 11264 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11272 */
	{.type FromH0, {.p L158}},		/* dd L158 11280 */
	{.type FromH0, {.p MV_Findadr}},		/* dd MV_Findadr 11288 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 11296 */
	{.type FromH0, {.p C_false}},		/* dd C_false 11304 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11312 */
	{.type Header, {.hdr { 4, "find", /* C_find = 11328 */ colon }}}, /* CENTRY "find" find 4 ; ( a1 -- a2 f )? h 11336 */
	{.type FromH0, {.p C_findname}},		/* dd C_findname 11344 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11352 */
	{.type FromH0, {.p L164}},		/* dd L164 11360 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 11368 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 11376 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 11384 */
	{.type FromH0, {.p M_over}},		/* dd M_over 11392 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11400 */
	{.type Absolute, {.p 63}},		/* dd 63 11408 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 11416 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 11424 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 11432 */
	{.type FromH0, {.p C_aligned}},		/* dd C_aligned 11440 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 11448 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11456 */
	{.type Absolute, {.p 128}},		/* dd 128 11464 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 11472 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11480 */
	{.type FromH0, {.p L165}},		/* dd L165 11488 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11496 */
	{.type Absolute, {.p 1}},		/* dd 1 11504 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11512 */
	{.type FromH0, {.p L166}},		/* dd L166 11520 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11528 */
	{.type Absolute, {.p -1}},		/* dd -1 11536 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11544 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11552 */
	{.type FromH0, {.p L167}},		/* dd L167 11560 */
	{.type FromH0, {.p C_false}},		/* dd C_false 11568 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11576 */
	{.type Header, {.hdr { 1, "'", /* C_single_quote = 11592 */ colon }}}, /* CENTRY "'" single_quote 1 h 11600 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 11608 */
	{.type FromH0, {.p C_word}},		/* dd C_word 11616 */
	{.type FromH0, {.p C_find}},		/* dd C_find 11624 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 11632 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11640 */
	{.type FromH0, {.p L169}},		/* dd L169 11648 */
	{.type FromH0, {.p C_space}},		/* dd C_space 11656 */
	{.type FromH0, {.p C_count}},		/* dd C_count 11664 */
	{.type FromH0, {.p C_type}},		/* dd C_type 11672 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11680 */
	{.type FromH0, {.p L170}},		/* dd L170 11688 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11696 */
	{.type Absolute, {.p 3}},		/* dd 3 11704 */
	{.type FromH0, {.p C_type}},		/* dd C_type 11712 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 11720 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 11728 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11736 */
	{.type Header, {.hdr { 6, "?stack", /* C_qstack = 11752 */ colon }}}, /* CENTRY "?stack" qstack 6 h 11760 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr 11768 */
	{.type FromH0, {.p M_S0}},		/* dd M_S0 11776 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 11784 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11792 */
	{.type FromH0, {.p L172}},		/* dd L172 11800 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11808 */
	{.type FromH0, {.p L173}},		/* dd L173 11816 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11824 */
	{.type Absolute, {.p 16}},		/* dd 16 11832 */
	{.type FromH0, {.p C_type}},		/* dd C_type 11840 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 11848 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 11856 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11864 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup ; debug code to show the word found 11872 */
	{.type FromH0, {.p C_count}},		/* dd C_count ; ( -- a n) 11880 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap ; ( -- n a) 11888 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 11896 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite 11904 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; drop the return value of write 11912 */
	{.type Header, {.hdr { 9, "interpret", /* C_interpret = 11936 */ colon }}}, /* CENTRY "interpret" interpret 9 ; there is stuff in TIB to be interpreted >In and >Limit are set h 11944 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 11952 */
	{.type FromH0, {.p C_word}},		/* dd C_word	; ( bl -- a ) a = address of counted string 11960 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 11968 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 11976 */
	{.type FromH0, {.p C_0neq}},		/* dd C_0neq 11984 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11992 */
	{.type FromH0, {.p L176}},		/* dd L176	; count at a = 0 12000 */
	{.type FromH0, {.p C_find}},		/* dd C_find	; ( a -- a1 f ) a = address of counted string 12008 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12016 */
	{.type FromH0, {.p L177}},		/* dd L177 12024 */
	{.type FromH0, {.p C_qstack}},		/* dd C_qstack 12032 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 12040 */
	{.type FromH0, {.p L178}},		/* dd L178 12048 */
	{.type FromH0, {.p C_count}},		/* dd C_count 12056 */
	{.type FromH0, {.p C_number}},		/* dd C_number 12064 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 12072 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12080 */
	{.type FromH0, {.p L179}},		/* dd L179 12088 */
	{.type FromH0, {.p C_space}},		/* dd C_space 12096 */
	{.type FromH0, {.p C_type}},		/* dd C_type 12104 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12112 */
	{.type FromH0, {.p L180}},		/* dd L180	; error I? 12120 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12128 */
	{.type Absolute, {.p 3}},		/* dd 3 12136 */
	{.type FromH0, {.p C_type}},		/* dd C_type 12144 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 12152 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 12160 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 12168 */
	{.type FromH0, {.p L175}},		/* dd L175 12176 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop	; count at a = 0 ( a -- ) 12184 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12192 */
	{.type Header, {.hdr { 6, "create", /* C_create = 12208 */ colon }}}, /* CENTRY "create" create 6 h 12216 */
	{.type FromH0, {.p C_align}},		/* dd C_align 12224 */
	{.type FromH0, {.p C_here}},		/* dd C_here 12232 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 12240 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 12248 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12256 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12264 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 12272 */
	{.type FromH0, {.p C_word}},		/* dd C_word 12280 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12288 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 12296 */
	{.type FromH0, {.p C_here}},		/* dd C_here 12304 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 12312 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 12320 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12328 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 12336 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 12344 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 12352 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 12360 */
	{.type FromH0, {.p C_align}},		/* dd C_align 12368 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12376 */
	{.type FromH0, {.p M_variable}},		/* dd M_variable 12384 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12392 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12400 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 12408 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 12416 */
	{.type FromH0, {.p M_store}},		/* dd M_store 12424 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12432 */
	{.type Header, {.hdr { 8, "variable", /* C_variable = 12456 */ colon }}}, /* CENTRY "variable" variable 8 h 12464 */
	{.type FromH0, {.p C_create}},		/* dd C_create 12472 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12480 */
	{.type Absolute, {.p 0}},		/* dd 0 12488 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12496 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12504 */
	{.type Header, {.hdr { 8, "constant", /* C_constant = 12528 */ colon }}}, /* CENTRY "constant" constant 8 h 12536 */
	{.type FromH0, {.p C_create}},		/* dd C_create 12544 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12552 */
	{.type FromH0, {.p M_constant}},		/* dd M_constant 12560 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12568 */
	{.type FromH0, {.p C_here}},		/* dd C_here 12576 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12584 */
	{.type Absolute, {.p 1}},		/* dd 1 12592 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 12600 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 12608 */
	{.type FromH0, {.p M_store}},		/* dd M_store 12616 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12624 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12632 */
	{.type Header, {.hdr { 9, "immediate", /* C_immediate = 12656 */ colon }}}, /* CENTRY "immediate" immediate 9 h 12664 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 12672 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12680 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 12688 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12696 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 12704 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12712 */
	{.type Absolute, {.p 128}},		/* dd 128 12720 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 12728 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 12736 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 12744 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12752 */
	{.type Header, {.hdr { 4, ">cfa", /* C_tocfa = 12768 */ colon }}}, /* CENTRY ">cfa" tocfa 4 h 12776 */
	{.type FromH0, {.p C_count}},		/* dd C_count 12784 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12792 */
	{.type Absolute, {.p 63}},		/* dd 63 12800 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 12808 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 12816 */
	{.type FromH0, {.p C_aligned}},		/* dd C_aligned 12824 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12832 */
	{.type Header, {.hdr { 7, "compile", /* C_compile = 12848 */ colon }}}, /* CENTRY "compile" compile 7 h 12856 */
	{.type FromH0, {.p C_findname}},		/* dd C_findname 12864 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12872 */
	{.type FromH0, {.p L188}},		/* dd L188 12880 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12888 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 12896 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12904 */
	{.type Absolute, {.p 128}},		/* dd 128 12912 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 12920 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12928 */
	{.type FromH0, {.p L189}},		/* dd L189 12936 */
	{.type FromH0, {.p C_tocfa}},		/* dd C_tocfa	; immediate 12944 */
	{.type FromH0, {.p M_execute}},		/* dd M_execute 12952 */
	{.type FromH0, {.p C_qstack}},		/* dd C_qstack 12960 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 12968 */
	{.type FromH0, {.p L190}},		/* dd L190 12976 */
	{.type FromH0, {.p C_tocfa}},		/* dd C_tocfa 12984 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12992 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13000 */
	{.type FromH0, {.p L191}},		/* dd L191 13008 */
	{.type FromH0, {.p C_count}},		/* dd C_count 13016 */
	{.type FromH0, {.p C_number}},		/* dd C_number 13024 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 13032 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 13040 */
	{.type FromH0, {.p L192}},		/* dd L192 13048 */
	{.type FromH0, {.p C_space}},		/* dd C_space 13056 */
	{.type FromH0, {.p C_type}},		/* dd C_type 13064 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13072 */
	{.type FromH0, {.p L193}},		/* dd L193 13080 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13088 */
	{.type Absolute, {.p 3}},		/* dd 3 13096 */
	{.type FromH0, {.p C_type}},		/* dd C_type 13104 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 13112 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 13120 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13128 */
	{.type FromH0, {.p L194}},		/* dd L194 13136 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13144 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13152 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13160 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13168 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13176 */
	{.type Header, {.hdr { 1, "]", /* C_close_bracket = 13192 */ colon }}}, /* CENTRY "]" close_bracket 1 h 13200 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13208 */
	{.type FromH0, {.p C_on}},		/* dd C_on 13216 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 13224 */
	{.type FromH0, {.p C_word}},		/* dd C_word 13232 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13240 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13248 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 13256 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 13264 */
	{.type FromH0, {.p L197}},		/* dd L197 13272 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 13280 */
	{.type FromH0, {.p C_refill}},		/* dd C_refill 13288 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13296 */
	{.type FromH0, {.p L198}},		/* dd L198 13304 */
	{.type FromH0, {.p C_compile}},		/* dd C_compile 13312 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13320 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13328 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 13336 */
	{.type FromH0, {.p L199}},		/* dd L199 13344 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13352 */
	{.type FromH0, {.p L196}},		/* dd L196 13360 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13368 */
	{.type IHeader, {.hdr { 1, "[", /* CI_open_bracket = 13384 */ colon }}}, /* CIENTRY "[" open_bracket 1 h 13392 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13400 */
	{.type FromH0, {.p C_off}},		/* dd C_off 13408 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13416 */
	{.type Header, {.hdr { 6, "smudge", /* C_smudge = 13432 */ colon }}}, /* CENTRY "smudge" smudge 6 h 13440 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 13448 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13456 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 13464 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13472 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13480 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13488 */
	{.type Absolute, {.p 64}},		/* dd 64 13496 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 13504 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 13512 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 13520 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13528 */
	{.type Header, {.hdr { 6, "reveal", /* C_reveal = 13544 */ colon }}}, /* CENTRY "reveal" reveal 6 h 13552 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 13560 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13568 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 13576 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13584 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13592 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13600 */
	{.type Absolute, {.p 64}},		/* dd 64 13608 */
	{.type FromH0, {.p C_invert}},		/* dd C_invert 13616 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 13624 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 13632 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 13640 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13648 */
	{.type Header, {.hdr { 1, ":", /* C_colon = 13664 */ colon }}}, /* CENTRY ":" colon 1 h 13672 */
	{.type FromH0, {.p C_create}},		/* dd C_create 13680 */
	{.type FromH0, {.p C_smudge}},		/* dd C_smudge 13688 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13696 */
	{.type FromH0, {.p M_colon}},		/* dd M_colon 13704 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13712 */
	{.type FromH0, {.p C_here}},		/* dd C_here 13720 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13728 */
	{.type Absolute, {.p 1}},		/* dd 1 13736 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 13744 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 13752 */
	{.type FromH0, {.p M_store}},		/* dd M_store 13760 */
	{.type FromH0, {.p C_close_bracket}},		/* dd C_close_bracket 13768 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13776 */
	{.type IHeader, {.hdr { 1, ";", /* CI_semicolon = 13792 */ colon }}}, /* CIENTRY ";" semicolon 1 h 13800 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13808 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13816 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13824 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13832 */
	{.type FromH0, {.p C_off}},		/* dd C_off 13840 */
	{.type FromH0, {.p C_reveal}},		/* dd C_reveal 13848 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13856 */
	{.type IHeader, {.hdr { 7, "recurse", /* CI_recurse = 13872 */ colon }}}, /* CIENTRY "recurse" recurse 7 h 13880 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 13888 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13896 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 13904 */
	{.type FromH0, {.p C_tocfa}},		/* dd C_tocfa 13912 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13920 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13928 */
	{.type Header, {.hdr { 4, "char", /* C_L206 = 13944 */ colon }}}, /* CENTRY "char" L206 4 h 13952 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 13960 */
	{.type FromH0, {.p C_word}},		/* dd C_word 13968 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 13976 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13984 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13992 */
	{.type Header, {.hdr { 7, "literal", /* C_literal = 14008 */ colon }}}, /* CENTRY "literal" literal 7 h 14016 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14024 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14032 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14040 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14048 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14056 */
	{.type Header, {.hdr { 8, "sliteral", /* C_sliteral = 14080 */ colon }}}, /* CENTRY "sliteral" sliteral 8 h 14088 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14096 */
	{.type FromH0, {.p M_sliteral}},		/* dd M_sliteral 14104 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14112 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14120 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14128 */
	{.type Absolute, {.p 34}},		/* dd 34 14136 */
	{.type FromH0, {.p C_parse}},		/* dd C_parse 14144 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 14152 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14160 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14168 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 14176 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 14184 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 14192 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 14200 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 14208 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 14216 */
	{.type FromH0, {.p C_align}},		/* dd C_align 14224 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14232 */
	{.type Header, {.hdr { 6, "string", /* C_string = 14248 */ colon }}}, /* CENTRY "string" string 6 h 14256 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14264 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 14272 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14280 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14288 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 14296 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14304 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 14312 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 14320 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 14328 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 14336 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14344 */
	{.type IHeader, {.hdr { 6, "[char]", /* CI_char_brackets = 14360 */ colon }}}, /* CIENTRY "[char]" char_brackets 6 h 14368 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 14376 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14384 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14392 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14400 */
	{.type FromH0, {.p C_literal}},		/* dd C_literal 14408 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14416 */
	{.type IHeader, {.hdr { 3, "[']", /* CI_quote_brackets = 14432 */ colon }}}, /* CIENTRY "[']" quote_brackets 3 h 14440 */
	{.type FromH0, {.p C_single_quote}},		/* dd C_single_quote 14448 */
	{.type FromH0, {.p C_literal}},		/* dd C_literal 14456 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14464 */
	{.type IHeader, {.hdr { 1, "(", /* CI_openparen = 14480 */ colon }}}, /* CIENTRY "(" openparen 1 h 14488 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14496 */
	{.type Absolute, {.p 41}},		/* dd 41 14504 */
	{.type FromH0, {.p C_parse}},		/* dd C_parse 14512 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 14520 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14528 */
	{.type IHeader, {.hdr { 1, "\\", /* CI_backslash = 14544 */ colon }}}, /* CIENTRY "\\" backslash 1 h 14552 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 14560 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14568 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 14576 */
	{.type FromH0, {.p L214}},		/* dd L214 14584 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 14592 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14600 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14608 */
	{.type Absolute, {.p 63}},		/* dd 63 14616 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 14624 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14632 */
	{.type Absolute, {.p 63}},		/* dd 63 14640 */
	{.type FromH0, {.p C_invert}},		/* dd C_invert 14648 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 14656 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 14664 */
	{.type FromH0, {.p M_store}},		/* dd M_store 14672 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 14680 */
	{.type FromH0, {.p L215}},		/* dd L215 14688 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 14696 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14704 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 14712 */
	{.type FromH0, {.p M_store}},		/* dd M_store 14720 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14728 */
	{.type Header, {.hdr { 8, "(?abort)", /* C_qabort_parens = 14752 */ colon }}}, /* CENTRY "(?abort)" qabort_parens 8 h 14760 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 14768 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 14776 */
	{.type FromH0, {.p L217}},		/* dd L217 14784 */
	{.type FromH0, {.p C_space}},		/* dd C_space 14792 */
	{.type FromH0, {.p C_type}},		/* dd C_type 14800 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 14808 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 14816 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 14824 */
	{.type FromH0, {.p L218}},		/* dd L218 14832 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop 14840 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14848 */
	{.type IHeader, {.hdr { 6, "abort\"", /* CI_abort_double_quote = 14864 */ colon }}}, /* CIENTRY "abort\"" abort_double_quote 6 h 14872 */
	{.type FromH0, {.p C_sliteral}},		/* dd C_sliteral 14880 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14888 */
	{.type FromH0, {.p C_qabort_parens}},		/* dd C_qabort_parens 14896 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14904 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14912 */
	{.type Header, {.hdr { 1, "\"", /* C_double_quote = 14928 */ colon }}}, /* CENTRY "\"" double_quote 1 h 14936 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14944 */
	{.type Absolute, {.p 34}},		/* dd 34 14952 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14960 */
	{.type FromH0, {.p C_count}},		/* dd C_count 14968 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 14976 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14984 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 14992 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 15000 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15008 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 15016 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 15024 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 15032 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15040 */
	{.type Header, {.hdr { 2, "c\"", /* C_cdouble_quote = 15056 */ colon }}}, /* CENTRY "c\"" cdouble_quote 2 h 15064 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15072 */
	{.type Absolute, {.p 34}},		/* dd 34 15080 */
	{.type FromH0, {.p C_word}},		/* dd C_word 15088 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 15096 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 15104 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 15112 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 15120 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15128 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 15136 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 15144 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15152 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 15160 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 15168 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15176 */
	{.type IHeader, {.hdr { 2, "s\"", /* CI_sdouble_quote = 15192 */ colon }}}, /* CIENTRY "s\"" sdouble_quote 2 h 15200 */
	{.type FromH0, {.p C_sliteral}},		/* dd C_sliteral 15208 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15216 */
	{.type IHeader, {.hdr { 2, ".\"", /* CI_dotstr = 15232 */ colon }}}, /* CIENTRY ".\"" dotstr 2 h 15240 */
	{.type FromH0, {.p C_sliteral}},		/* dd C_sliteral 15248 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15256 */
	{.type FromH0, {.p C_type}},		/* dd C_type 15264 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15272 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15280 */
	{.type IHeader, {.hdr { 2, "if", /* CI_if = 15296 */ colon }}}, /* CIENTRY "if" if 2 h 15304 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15312 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15320 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15328 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15336 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15344 */
	{.type Absolute, {.p 0}},		/* dd 0 15352 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15360 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15368 */
	{.type IHeader, {.hdr { 4, "else", /* CI_else = 15384 */ colon }}}, /* CIENTRY "else" else 4 h 15392 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15400 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 15408 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15416 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15424 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 15432 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15440 */
	{.type Absolute, {.p 0}},		/* dd 0 15448 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15456 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15464 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15472 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15480 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 15488 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15496 */
	{.type IHeader, {.hdr { 4, "then", /* CI_then = 15512 */ colon }}}, /* CIENTRY "then" then 4 h 15520 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15528 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15536 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15544 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15552 */
	{.type IHeader, {.hdr { 5, "begin", /* CI_begin = 15568 */ colon }}}, /* CIENTRY "begin" begin 5 h 15576 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15584 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15592 */
	{.type IHeader, {.hdr { 5, "again", /* CI_again = 15608 */ colon }}}, /* CIENTRY "again" again 5 h 15616 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15624 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 15632 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15640 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15648 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15656 */
	{.type IHeader, {.hdr { 5, "until", /* CI_until = 15672 */ colon }}}, /* CIENTRY "until" until 5 h 15680 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15688 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15696 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15704 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15712 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15720 */
	{.type IHeader, {.hdr { 5, "while", /* CI_while = 15736 */ colon }}}, /* CIENTRY "while" while 5 h 15744 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15752 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15760 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15768 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15776 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15784 */
	{.type Absolute, {.p 0}},		/* dd 0 15792 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15800 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15808 */
	{.type IHeader, {.hdr { 6, "repeat", /* CI_repeat = 15824 */ colon }}}, /* CIENTRY "repeat" repeat 6 h 15832 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15840 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 15848 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15856 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15864 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15872 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15880 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15888 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15896 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15904 */
	{.type IHeader, {.hdr { 2, "do", /* CI_do = 15920 */ colon }}}, /* CIENTRY "do" do 2 h 15928 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15936 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 15944 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15952 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15960 */
	{.type Absolute, {.p 0}},		/* dd 0 15968 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15976 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15984 */
	{.type IHeader, {.hdr { 4, "loop", /* CI_loop = 16000 */ colon }}}, /* CIENTRY "loop" loop 4 h 16008 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16016 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 16024 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 16032 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 16040 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 16048 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 16056 */
	{.type FromH0, {.p L234}},		/* dd L234 16064 */
	{.type FromH0, {.p C_here}},		/* dd C_here 16072 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 16080 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16088 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16096 */
	{.type IHeader, {.hdr { 5, "+loop", /* CI_ploop = 16112 */ colon }}}, /* CIENTRY "+loop" ploop 5 h 16120 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16128 */
	{.type FromH0, {.p M_doploop}},		/* dd M_doploop 16136 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 16144 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 16152 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 16160 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 16168 */
	{.type FromH0, {.p L236}},		/* dd L236 16176 */
	{.type FromH0, {.p C_here}},		/* dd C_here 16184 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 16192 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16200 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16208 */
	{.type Header, {.hdr { 3, "w/o", /* C_wo = 16224 */ colon }}}, /* CENTRY "w/o" wo 3 h 16232 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16240 */
	{.type Absolute, {.p 1}},		/* dd 1 16248 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16256 */
	{.type Absolute, {.p 512}},		/* dd 512 16264 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 16272 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16280 */
	{.type Absolute, {.p 64}},		/* dd 64 16288 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 16296 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16304 */
	{.type Header, {.hdr { 3, "r/o", /* C_ro = 16320 */ colon }}}, /* CENTRY "r/o" ro 3 h 16328 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16336 */
	{.type Absolute, {.p 0}},		/* dd 0 16344 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16352 */
	{.type Header, {.hdr { 3, "r/w", /* C_rw = 16368 */ colon }}}, /* CENTRY "r/w" rw 3 h 16376 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16384 */
	{.type Absolute, {.p 2}},		/* dd 2 16392 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16400 */
	{.type Header, {.hdr { 9, "open-file", /* C_open_file = 16424 */ colon }}}, /* CENTRY "open-file" open_file 9 h 16432 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 16440 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 16448 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16456 */
	{.type Absolute, {.p 1024}},		/* dd 1024 16464 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 16472 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 16480 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 16488 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 16496 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 16504 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16512 */
	{.type Absolute, {.p 0}},		/* dd 0 16520 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 16528 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 16536 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 16544 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16552 */
	{.type Absolute, {.p 1024}},		/* dd 1024 16560 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 16568 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 16576 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 16584 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16592 */
	{.type Absolute, {.p 1024}},		/* dd 1024 16600 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 16608 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 16616 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16624 */
	{.type Absolute, {.p 420}},		/* dd 420 16632 */
	{.type FromH0, {.p M_fthopen}},		/* dd M_fthopen 16640 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 16648 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16656 */
	{.type Absolute, {.p -1}},		/* dd -1 16664 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 16672 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16680 */
	{.type Header, {.hdr { 10, "close-file", /* C_close_file = 16704 */ colon }}}, /* CENTRY "close-file" close_file 10 h 16712 */
	{.type FromH0, {.p M_fthclose}},		/* dd M_fthclose 16720 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 16728 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16736 */
	{.type Header, {.hdr { 9, "read-file", /* C_read_file = 16760 */ colon }}}, /* CENTRY "read-file" read_file 9 h 16768 */
	{.type FromH0, {.p M_fthread}},		/* dd M_fthread 16776 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 16784 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16792 */
	{.type Absolute, {.p -1}},		/* dd -1 16800 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 16808 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16816 */
	{.type Header, {.hdr { 10, "write-file", /* C_write_file = 16840 */ colon }}}, /* CENTRY "write-file" write_file 10 h 16848 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite 16856 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16864 */
	{.type Absolute, {.p -1}},		/* dd -1 16872 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 16880 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16888 */
	{.type Header, {.hdr { 15, "reposition-file", /* C_reposition_file = 16912 */ colon }}}, /* CENTRY "reposition-file" reposition_file 15 h 16920 */
	{.type FromH0, {.p M_fthseek}},		/* dd M_fthseek 16928 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16936 */
	{.type Absolute, {.p -1}},		/* dd -1 16944 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 16952 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16960 */
	{.type Header, {.hdr { 7, "?fcheck", /* C_qfcheck = 16976 */ colon }}}, /* CENTRY "?fcheck" qfcheck 7 h 16984 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 16992 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 17000 */
	{.type FromH0, {.p L246}},		/* dd L246 17008 */
	{.type FromH0, {.p C_space}},		/* dd C_space 17016 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17024 */
	{.type FromH0, {.p L247}},		/* dd L247 17032 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17040 */
	{.type Absolute, {.p 9}},		/* dd 9 17048 */
	{.type FromH0, {.p C_type}},		/* dd C_type 17056 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 17064 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 17072 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17080 */
	{.type Header, {.hdr { 3, "bye", /* C_bye = 17096 */ colon }}}, /* CENTRY "bye" bye 3 h 17104 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17112 */
	{.type Absolute, {.p 0}},		/* dd 0 17120 */
	{.type FromH0, {.p M_terminate}},		/* dd M_terminate 17128 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17136 */
	{.type Header, {.hdr { 7, "include", /* C_include = 17152 */ colon }}}, /* CENTRY "include" include 7 h 17160 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 17168 */
	{.type FromH0, {.p C_word}},		/* dd C_word 17176 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 17184 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 17192 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 17200 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 17208 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17216 */
	{.type FromH0, {.p C_save_input}},		/* dd C_save_input 17224 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 17232 */
	{.type FromH0, {.p C_count}},		/* dd C_count 17240 */
	{.type FromH0, {.p C_ro}},		/* dd C_ro 17248 */
	{.type FromH0, {.p C_open_file}},		/* dd C_open_file 17256 */
	{.type FromH0, {.p C_qfcheck}},		/* dd C_qfcheck 17264 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 17272 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17280 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17288 */
	{.type Header, {.hdr { 5, "crash", /* C_crash = 17304 */ colon }}}, /* CENTRY "crash" crash 5 h 17312 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17320 */
	{.type FromH0, {.p L251}},		/* dd L251 17328 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17336 */
	{.type Absolute, {.p 30}},		/* dd 30 17344 */
	{.type FromH0, {.p C_type}},		/* dd C_type 17352 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 17360 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 17368 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17376 */
	{.type Header, {.hdr { 4, "quit", /* C_quit = 17392 */ colon }}}, /* CENTRY "quit" quit 4 ; interpreter loop h 17400 */
	{.type FromH0, {.p M_reset}},		/* dd M_reset ; initialize return stack 17408 */
	{.type FromH0, {.p M_clear}},		/* dd M_clear	; SP = sstack_end initialize data stack 17416 */
	{.type FromH0, {.p C_query}},		/* dd C_query 17424 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit	; show the line read, for debugging 17432 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 17440 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib 17448 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 17456 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite 17464 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; drop the return value of write 17472 */
	{.type FromH0, {.p C_interpret}},		/* dd C_interpret 17480 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 17488 */
	{.type FromH0, {.p L253}},		/* dd L253 17496 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon	; why is this needed? 17504 */
	{.type Header, {.hdr { 7, "(abort)", /* C_parenabort = 17520 */ colon }}}, /* CENTRY "(abort)" parenabort 7 ; TODO correct below stack notations h 17528 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State	; ( mv_State -- ) 17536 */
	{.type FromH0, {.p C_off}},		/* dd C_off		; off sets variable state = 0 17544 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 17552 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 17560 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 17568 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk	; variable blk 17576 */
	{.type FromH0, {.p C_off}},		/* dd C_off	; off variable blk = 0 17584 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 17592 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 17600 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17608 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 17616 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 17624 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17632 */
	{.type FromH0, {.p MC_STDERR}},		/* dd MC_STDERR 17640 */
	{.type FromH0, {.p MV_Errfd}},		/* dd MV_Errfd 17648 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17656 */
	{.type FromH0, {.p C_quit}},		/* dd C_quit	; quit resets stacks and is the interpreter loop 17664 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon	; why is this needed? quit does not return unless it breaks 17672 */
	{.type Header, {.hdr { 7, "oldboot", /* C_oldboot = 17688 */ colon }}}, /* CENTRY "oldboot" oldboot 7 ; TODO correct below stack notations and this is obsolete. leaving it here for reference until it all works well h 17696 */
	{.type FromH0, {.p M_reset}},		/* dd M_reset 17704 */
	{.type FromH0, {.p M_clear}},		/* dd M_clear	; SP = sstack_end 17712 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr	; (D -- FFEND) 17720 */
	{.type FromH0, {.p M_S0}},		/* dd M_S0 17728 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; s0 = FFEND 17736 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0	; heaptop = heapend 17744 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; ( heapend -- ) 17752 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17760 */
	{.type Absolute, {.p 1}},		/* dd 1		; ( heapend 1 -- ) 17768 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells	; cells ( heapend 8 -- ) 17776 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( heapend-8 -- ) 17784 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; ( contents_from_heapend-8 -- ) 17792 */
	{.type FromH0, {.p M_Args}},		/* dd M_Args	; variable args 17800 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; args = contents_from_heapend-8 17808 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17816 */
	{.type FromH0, {.p C_parenabort}},		/* dd C_parenabort ; ( (abort) -- ) 17824 */
	{.type FromH0, {.p MV_Abortvec}},		/* dd MV_Abortvec	; variable abortvec 17832 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable abortvec = (abort) code address 17840 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb	; constant puts address of wordbuffer on the top of stack 17848 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf	; variable wordbuf 17856 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable wordbuf = address of wordbuffer 17864 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 17872 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 17880 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 17888 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17896 */
	{.type Absolute, {.p 0}},		/* dd 0 17904 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 17912 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; stdin = 0 17920 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17928 */
	{.type Absolute, {.p 1}},		/* dd 1 17936 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 17944 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; stdout = 1 17952 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 17960 */
	{.type FromH0, {.p C_off}},		/* dd C_off	; off stores 0 at state 17968 */
	{.type FromH0, {.p C_decimal}},		/* dd C_decimal	; decimal setting base = 0 17976 */
	{.type FromH0, {.p C_quit}},		/* dd C_quit	; quit 17984 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17992 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal	; test code 18000 */
	{.type Absolute, {.p 66}},		/* dd 66 18008 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb 18016 */
	{.type FromH0, {.p M_store}},		/* dd M_store 18024 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 18032 */
	{.type Absolute, {.p 1}},		/* dd 1 18040 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb 18048 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 18056 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite 18064 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; drop the return value of write 18072 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 18080 */
	{.type Absolute, {.p 1}},		/* dd 1 18088 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb 18096 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 18104 */
	{.type FromH0, {.p M_fthread}},		/* dd M_fthread 18112 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; drop the return value of read 18120 */
	{.type Header, {.hdr { 4, "boot", /* C_boot = 18136 */ colon }}}, /* CENTRY "boot" boot 4 h 18144 */
	{.type FromH0, {.p M_reset}},		/* dd M_reset ; initialize return stack 18152 */
	{.type FromH0, {.p M_clear}},		/* dd M_clear	; SP = sstack_end initialize data stack 18160 */
/* 			; s0 puts FFEND on the stack *//* 			; no args */	{.type FromH0, {.p M_literal}},		/* dd M_literal 18168 */
	{.type FromH0, {.p C_parenabort}},		/* dd C_parenabort ; ( (abort) -- ) 18176 */
	{.type FromH0, {.p MV_Abortvec}},		/* dd MV_Abortvec	; variable that puts (abort) code address on the stack 18184 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable abortvec = (abort) code address 18192 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb	; variable puts address of wordbuffer on the top of stack 18200 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf ; variable wordbuf 18208 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable wordbuf = address of wordbuffer 18216 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 18224 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 18232 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 18240 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 18248 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 18256 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; stdin = 0 18264 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 18272 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 18280 */
	{.type FromH0, {.p M_store}},		/* dd M_store 18288 */
	{.type FromH0, {.p MC_STDERR}},		/* dd MC_STDERR 18296 */
	{.type FromH0, {.p MV_Errfd}},		/* dd MV_Errfd 18304 */
	{.type FromH0, {.p M_store}},		/* dd M_store 18312 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 18320 */
	{.type FromH0, {.p C_off}},		/* dd C_off	; off stores 0 at state 18328 */
	{.type FromH0, {.p C_decimal}},		/* dd C_decimal	; decimal sets base = 10 18336 */
	{.type FromH0, {.p C_quit}},		/* dd C_quit	; quit 18344 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 18352 */
	{.type Chars, {.str "unable to restore input"}},		/* 18376 */
	{.type Chars, {.str " Q?"}},		/* 18380 */
	{.type Chars, {.str " stack underflow"}},		/* 18397 */
	{.type Chars, {.str " I?"}},		/* 18401 */
	{.type Chars, {.str " C?"}},		/* 18405 */
	{.type Chars, {.str "I/O error"}},		/* 18415 */
	{.type Chars, {.str "uninitialized execution vector"}},		/* 18446 */
	{.type Chars, {.str " ok"}},		/* 18450 */
};

