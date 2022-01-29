/*
 * Forth dictionary
 */
enum {
	Header,
	IHeader,	/* Immediate dictionary definition */
	Absolute,
	FromH0,
	FromV0,
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
	char src[128];
};
enum {
	M_fetch = 16,
	M_store = 40,
	M_cfetch = 64,
	M_cstore = 88,
	M_sysread = 112,
	M_syswrite = 144,
	M_sysseek = 168,
	M_sysopen = 192,
	M_sysclose = 224,
	M_syscreate = 256,
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
	M_variable = 1264,
	M_constant = 1296,
	M_colon = 1320,
	M_dodoes = 1344,
	M_cas = 1368,
	M_deferred = 1400,
	MC_STDIN = 1424,
	MC_STDOUT = 1456,
	MC_STDERR = 1488,
	MV_Iobuf = 1520,
	MV_Sourcebuf = 1560,
	MV_Wordbuf = 1592,
	MV_toIn = 1624,
	MV_toLimit = 1656,
	MV_Findadr = 1688,
	MV_Blk = 1720,
	MV_Searchlen = 1760,
	MV_Base = 1792,
	MV_toNum = 1824,
	MV_State = 1856,
	MV_Abortvec = 1896,
	MV_Infd = 1928,
	MV_Outfd = 1960,
	MV_Errfd = 1992,
	MV_Eof = 2024,
	MV_Ninputs = 2056,
	MV_H0 = 2088,
	M_Dp = 2120,
	M_Dtop = 2144,
	M_Vp = 2168,
	M_S0 = 2192,
	M_stackptr = 2216,
	M_Wordb = 2240,
	M_Tib = 2264,
	M_Args = 2288,
	C_false = 2312,
	C_true = 2360,
	C_bl = 2408,
	C_on = 2456,
	C_off = 2520,
	C_tobody = 2584,
	C_aligned = 2640,
	C_cells = 2720,
	C_cellplus = 2776,
	C_depth = 2840,
	C_nip = 2944,
	C_rot = 2992,
	C_2drop = 3056,
	C_2dup = 3104,
	C_2nip = 3152,
	C_2swap = 3200,
	C_qdup = 3264,
	L20 = 3336,
	C_pick = 3360,
	L22 = 3464,
	L23 = 3472,
	C_tuck = 3496,
	C_divides = 3560,
	C_plusstore = 3608,
	C_invert = 3688,
	C_mod = 3744,
	C_1plus = 3792,
	C_1minus = 3848,
	C_negate = 3904,
	C_2multiplies = 3968,
	C_2divides = 4024,
	C_0eq = 4080,
	C_0lt = 4136,
	C_0gt = 4192,
	C_neq = 4248,
	C_0neq = 4296,
	C_max = 4352,
	L40 = 4416,
	L41 = 4424,
	C_min = 4448,
	L43 = 4512,
	L44 = 4520,
	C_signum = 4544,
	L46 = 4624,
	L48 = 4680,
	L49 = 4696,
	L47 = 4696,
	C_within = 4720,
	C_abs = 4824,
	L52 = 4872,
	C_key = 4896,
	L78 = 5024,
	L79 = 5040,
	C_emit = 5064,
	C_type = 5168,
	C_cr = 5264,
	C_space = 5320,
	C_emits = 5368,
	L85 = 5376,
	L86 = 5440,
	C_spaces = 5472,
	C_count = 5528,
	C_compare = 5672,
	L55 = 5744,
	L56 = 5880,
	C_erase = 5960,
	L58 = 5992,
	C_fill = 6080,
	L60 = 6120,
	C_blank = 6208,
	C_search = 6256,
	L64 = 6360,
	L65 = 6544,
	C_here = 6608,
	C_vhere = 6656,
	C_comma = 6704,
	C_c = 6784,
	C_allot = 6864,
	C_vallot = 6912,
	C_pad = 6960,
	C_align = 7024,
	C_unused = 7088,
	C_fromhash = 7152,
	C_hash = 7232,
	L92 = 7384,
	L93 = 7408,
	C_hashs = 7488,
	L95 = 7496,
	L96 = 7544,
	C_hashfrom = 7568,
	C_hold = 7680,
	C_sign = 7784,
	L100 = 7840,
	C_dot = 7864,
	C_dotr = 7968,
	C_hex = 8128,
	C_decimal = 8192,
	C_digit = 8256,
	L106 = 8368,
	L108 = 8472,
	L110 = 8576,
	L111 = 8600,
	L109 = 8600,
	L107 = 8600,
	L112 = 8672,
	L113 = 8688,
	C_number = 8712,
	L115 = 8848,
	L116 = 8880,
	L117 = 8944,
	L118 = 9048,
	L119 = 9104,
	C_abort = 9192,
	C_source = 9248,
	C_current_input = 9304,
	C_save_input = 9384,
	C_default_input = 9528,
	C_restore_input = 9648,
	L300 = 9752,
	L301 = 9768,
	L133 = 9856,
	L134 = 9944,
	C_qrestore_input = 9976,
	L136 = 10104,
	C_next_input = 10136,
	L139 = 10232,
	L140 = 10256,
	C_parse = 10280,
	L142 = 10320,
	L143 = 10448,
	C_word = 10592,
	L145 = 10608,
	L146 = 10704,
	C_accept = 10744,
	L148 = 10784,
	L150 = 10944,
	L149 = 11008,
	C_query = 11056,
	L152 = 11200,
	L153 = 11232,
	C_refill = 11256,
	L155 = 11320,
	L156 = 11336,
	C_findname = 11368,
	L158 = 11408,
	L160 = 11520,
	L162 = 11648,
	L161 = 11656,
	L159 = 11672,
	C_find = 11720,
	L165 = 11912,
	L166 = 11928,
	L164 = 11952,
	L167 = 11960,
	C_single_quote = 11984,
	L169 = 12120,
	C_qstack = 12144,
	L172 = 12248,
	C_interpret = 12320,
	L175 = 12328,
	L177 = 12440,
	L179 = 12552,
	L178 = 12552,
	L176 = 12568,
	C_create = 12600,
	C_variable = 12848,
	C_constant = 12944,
	C_immediate = 13072,
	C_tocfa = 13184,
	C_compile = 13264,
	L189 = 13392,
	L190 = 13408,
	L188 = 13424,
	L192 = 13552,
	L194 = 13584,
	L191 = 13584,
	C_close_bracket = 13608,
	L196 = 13632,
	L197 = 13720,
	L198 = 13744,
	L199 = 13776,
	CI_open_bracket = 13800,
	C_smudge = 13848,
	C_reveal = 13960,
	C_colon = 14080,
	CI_semicolon = 14208,
	CI_recurse = 14288,
	C_char = 14360,
	C_literal = 14424,
	C_sliteral = 14496,
	C_string = 14664,
	CI_char_brackets = 14776,
	CI_quote_brackets = 14848,
	CI_openparen = 14896,
	CI_backslash = 14960,
	L214 = 15104,
	L215 = 15136,
	C_qabort_parens = 15168,
	L217 = 15248,
	L218 = 15256,
	CI_abort_double_quote = 15280,
	C_double_quote = 15344,
	C_cdouble_quote = 15472,
	CI_sdouble_quote = 15608,
	CI_dotstr = 15648,
	CI_if = 15712,
	CI_else = 15800,
	CI_then = 15928,
	CI_begin = 15984,
	CI_again = 16024,
	CI_until = 16088,
	CI_while = 16152,
	CI_repeat = 16240,
	CI_do = 16336,
	CI_loop = 16416,
	L234 = 16504,
	CI_ploop = 16528,
	L236 = 16616,
	C_wo = 16640,
	C_ro = 16736,
	C_rw = 16784,
	C_open_file = 16840,
	C_close_file = 17104,
	C_read_file = 17160,
	C_write_file = 17256,
	C_reposition_file = 17344,
	C_qfcheck = 17424,
	L246 = 17520,
	C_create_file = 17552,
	C_bye = 17824,
	C_include = 17880,
	C_crash = 18032,
	C_quit = 18120,
	L253 = 18144,
	C_parenabort = 18200,
	C_oldboot = 18368,
	C_boot = 18816,
	L137 = 19056,
	L170 = 19080,
	L173 = 19084,
	L180 = 19101,
	L193 = 19105,
	L247 = 19109,
	L251 = 19119,
	L255 = 19150,
};
extern void *sliteral(void);
extern void *cjump(void);
extern void *syscreate(void);
extern void *syswrite(void);
extern void *i(void);
extern void *equal(void);
extern void *j(void);
extern void *drop(void);
extern void *rpop(void);
extern void *stackptr(void);
extern void *deferred(void);
extern void *cas(void);
extern void *sysseek(void);
extern void *xswap(void);
extern void *terminate(void);
extern void *greater(void);
extern void *slashmod(void);
extern void *cmoveb(void);
extern void *Dtop(void);
extern void *doinit(void);
extern void *multiply(void);
extern void *colon(void);
extern void *less(void);
extern void *Dp(void);
extern void *lshift(void);
extern void *S0(void);
extern void *sysopen(void);
extern void *plus(void);
extern void *sysclose(void);
extern void *jump(void);
extern void *fthdump(void);
extern void *rshift(void);
extern void *cstore(void);
extern void *Args(void);
extern void *Tib(void);
extern void *store(void);
extern void *Vp(void);
extern void *cmove(void);
extern void *binor(void);
extern void *unloop(void);
extern void *Wordb(void);
extern void *cfetch(void);
extern void *constant(void);
extern void *variable(void);
extern void *fetch(void);
extern void *doloop(void);
extern void *mmap(void);
extern void *binxor(void);
extern void *dup(void);
extern void *exitcolon(void);
extern void *clear(void);
extern void *sysread(void);
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
	{.type Header, {.hdr { 1, "@", /* M_fetch = 16 */ fetch }}}, /* MENTRY "@" fetch 1 h 24 */
	{.type Header, {.hdr { 1, "!", /* M_store = 40 */ store }}}, /* MENTRY "!" store 1 h 48 */
	{.type Header, {.hdr { 2, "c@", /* M_cfetch = 64 */ cfetch }}}, /* MENTRY "c@" cfetch 2 h 72 */
	{.type Header, {.hdr { 2, "c!", /* M_cstore = 88 */ cstore }}}, /* MENTRY "c!" cstore 2 h 96 */
	{.type Header, {.hdr { 7, "sysread", /* M_sysread = 112 */ sysread }}}, /* MENTRY "sysread" sysread 7 h 120 */
	{.type Header, {.hdr { 8, "syswrite", /* M_syswrite = 144 */ syswrite }}}, /* MENTRY "syswrite" syswrite 8 h 152 */
	{.type Header, {.hdr { 7, "sysseek", /* M_sysseek = 168 */ sysseek }}}, /* MENTRY "sysseek" sysseek 7 h 176 */
	{.type Header, {.hdr { 7, "sysopen", /* M_sysopen = 192 */ sysopen }}}, /* MENTRY "sysopen" sysopen 7 h 200 */
	{.type Header, {.hdr { 8, "sysclose", /* M_sysclose = 224 */ sysclose }}}, /* MENTRY "sysclose" sysclose 8 h 232 */
	{.type Header, {.hdr { 9, "syscreate", /* M_syscreate = 256 */ syscreate }}}, /* MENTRY "syscreate" syscreate 9 h 264 */
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
	{.type Header, {.hdr { 10, "(variable)", /* M_variable = 1264 */ variable }}}, /* MENTRY "(variable)" variable 10 h 1272 */
	{.type Header, {.hdr { 10, "(constant)", /* M_constant = 1296 */ constant }}}, /* MENTRY "(constant)" constant 10 h 1304 */
	{.type Header, {.hdr { 3, "(:)", /* M_colon = 1320 */ colon }}}, /* MENTRY "(:)" colon 3 h 1328 */
	{.type Header, {.hdr { 6, "(does)", /* M_dodoes = 1344 */ dodoes }}}, /* MENTRY "(does)" dodoes 6 h 1352 */
	{.type Header, {.hdr { 3, "cas", /* M_cas = 1368 */ cas }}}, /* MENTRY "cas" cas 3 h 1376 */
	{.type Header, {.hdr { 10, "(deferred)", /* M_deferred = 1400 */ deferred }}}, /* MENTRY "(deferred)" deferred 10 h 1408 */
	{.type Header, {.hdr { 5, "STDIN", /* MC_STDIN = 1424 */ constant }}}, /* MCENTRY "STDIN" STDIN 0 5		; 3 constants from here CAPITALS h 1432 */
	{.type Absolute, {.p 0}},		/* 1440 */
	{.type Header, {.hdr { 6, "STDOUT", /* MC_STDOUT = 1456 */ constant }}}, /* MCENTRY "STDOUT" STDOUT 1 6 h 1464 */
	{.type Absolute, {.p 1}},		/* 1472 */
	{.type Header, {.hdr { 6, "STDERR", /* MC_STDERR = 1488 */ constant }}}, /* MCENTRY "STDERR" STDERR 2 6 h 1496 */
	{.type Absolute, {.p 2}},		/* 1504 */
	{.type Header, {.hdr { 5, "Iobuf", /* MV_Iobuf = 1520 */ variable }}}, /* MVENTRY "Iobuf" Iobuf 0 5			; the values are not being used from the definition. All are initialized to 0. h 1528 */
	{.type FromV0, {.p 0 }},	/* 1536 0 */
	{.type Header, {.hdr { 9, "Sourcebuf", /* MV_Sourcebuf = 1560 */ variable }}}, /* MVENTRY "Sourcebuf" Sourcebuf 0 9	; is there a need for this? h 1568 */
	{.type FromV0, {.p 8 }},	/* 1576 8 */
	{.type Header, {.hdr { 7, "Wordbuf", /* MV_Wordbuf = 1592 */ variable }}}, /* MVENTRY "Wordbuf" Wordbuf 0 7		; is there a need for this? h 1600 */
	{.type FromV0, {.p 16 }},	/* 1608 16 */
	{.type Header, {.hdr { 3, ">In", /* MV_toIn = 1624 */ variable }}}, /* MVENTRY ">In" toIn 0 3 h 1632 */
	{.type FromV0, {.p 24 }},	/* 1640 24 */
	{.type Header, {.hdr { 6, ">Limit", /* MV_toLimit = 1656 */ variable }}}, /* MVENTRY ">Limit" toLimit 0 6 h 1664 */
	{.type FromV0, {.p 32 }},	/* 1672 32 */
	{.type Header, {.hdr { 7, "Findadr", /* MV_Findadr = 1688 */ variable }}}, /* MVENTRY "Findadr" Findadr 0 7 h 1696 */
	{.type FromV0, {.p 40 }},	/* 1704 40 */
	{.type Header, {.hdr { 3, "Blk", /* MV_Blk = 1720 */ variable }}}, /* MVENTRY "Blk" Blk 0 3 h 1728 */
	{.type FromV0, {.p 48 }},	/* 1736 48 */
	{.type Header, {.hdr { 9, "Searchlen", /* MV_Searchlen = 1760 */ variable }}}, /* MVENTRY "Searchlen" Searchlen 0 9 h 1768 */
	{.type FromV0, {.p 56 }},	/* 1776 56 */
	{.type Header, {.hdr { 4, "Base", /* MV_Base = 1792 */ variable }}}, /* MVENTRY "Base" Base 0 4 h 1800 */
	{.type FromV0, {.p 64 }},	/* 1808 64 */
	{.type Header, {.hdr { 4, ">Num", /* MV_toNum = 1824 */ variable }}}, /* MVENTRY ">Num" toNum 0 4 h 1832 */
	{.type FromV0, {.p 72 }},	/* 1840 72 */
	{.type Header, {.hdr { 5, "State", /* MV_State = 1856 */ variable }}}, /* MVENTRY "State" State 0 5 h 1864 */
	{.type FromV0, {.p 80 }},	/* 1872 80 */
	{.type Header, {.hdr { 8, "Abortvec", /* MV_Abortvec = 1896 */ variable }}}, /* MVENTRY "Abortvec" Abortvec 0 8	; not sure if these 3 can be constants instead? h 1904 */
	{.type FromV0, {.p 88 }},	/* 1912 88 */
	{.type Header, {.hdr { 4, "Infd", /* MV_Infd = 1928 */ variable }}}, /* MVENTRY "Infd" Infd 0 4 h 1936 */
	{.type FromV0, {.p 96 }},	/* 1944 96 */
	{.type Header, {.hdr { 5, "Outfd", /* MV_Outfd = 1960 */ variable }}}, /* MVENTRY "Outfd" Outfd 0 5 h 1968 */
	{.type FromV0, {.p 104 }},	/* 1976 104 */
	{.type Header, {.hdr { 5, "Errfd", /* MV_Errfd = 1992 */ variable }}}, /* MVENTRY "Errfd" Errfd 0 5 h 2000 */
	{.type FromV0, {.p 112 }},	/* 2008 112 */
	{.type Header, {.hdr { 3, "Eof", /* MV_Eof = 2024 */ variable }}}, /* MVENTRY "Eof" Eof 0 3 h 2032 */
	{.type FromV0, {.p 120 }},	/* 2040 120 */
	{.type Header, {.hdr { 7, "Ninputs", /* MV_Ninputs = 2056 */ variable }}}, /* MVENTRY "Ninputs" Ninputs 0 7 h 2064 */
	{.type FromV0, {.p 128 }},	/* 2072 128 */
	{.type Header, {.hdr { 2, "H0", /* MV_H0 = 2088 */ variable }}}, /* MVENTRY "H0" H0 0 2		; here at startup h 2096 */
	{.type FromV0, {.p 136 }},	/* 2104 136 */
/* ; cannot use H as it is nil in inferno, address where here (next available dictionary cell location) is stored *//* ; here = Dp @ */	{.type Header, {.hdr { 2, "Dp", /* M_Dp = 2120 */ Dp }}}, /* MENTRY "Dp" Dp 2		; here h 2128 */
	{.type Header, {.hdr { 4, "Dtop", /* M_Dtop = 2144 */ Dtop }}}, /* MENTRY "Dtop" Dtop 4	; last defined header h 2152 */
	{.type Header, {.hdr { 2, "Vp", /* M_Vp = 2168 */ Vp }}}, /* MENTRY "Vp" Vp 2		; here of the variables space h 2176 */
	{.type Header, {.hdr { 2, "S0", /* M_S0 = 2192 */ S0 }}}, /* MENTRY "S0" S0 2 h 2200 */
	{.type Header, {.hdr { 2, "s@", /* M_stackptr = 2216 */ stackptr }}}, /* MENTRY "s@" stackptr 2	; puts PSP on stack. Not a variable hence lower case. h 2224 */
	{.type Header, {.hdr { 5, "Wordb", /* M_Wordb = 2240 */ Wordb }}}, /* MENTRY "Wordb" Wordb 5 h 2248 */
	{.type Header, {.hdr { 3, "Tib", /* M_Tib = 2264 */ Tib }}}, /* MENTRY "Tib" Tib 3 h 2272 */
	{.type Header, {.hdr { 4, "Args", /* M_Args = 2288 */ Args }}}, /* MENTRY "Args" Args 4 h 2296 */
	{.type Header, {.hdr { 5, "false", /* C_false = 2312 */ colon }}}, /* CENTRY "false" false 5 h 2320 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2328 */
	{.type Absolute, {.p 0}},		/* dd 0 2336 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2344 */
	{.type Header, {.hdr { 4, "true", /* C_true = 2360 */ colon }}}, /* CENTRY "true" true 4 h 2368 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2376 */
	{.type Absolute, {.p -1}},		/* dd -1 2384 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2392 */
	{.type Header, {.hdr { 2, "bl", /* C_bl = 2408 */ colon }}}, /* CENTRY "bl" bl 2 h 2416 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2424 */
	{.type Absolute, {.p 32}},		/* dd 32 2432 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2440 */
	{.type Header, {.hdr { 2, "on", /* C_on = 2456 */ colon }}}, /* CENTRY "on" on 2 ; ( a -- ) (G stores -1 at a ) h 2464 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2472 */
	{.type Absolute, {.p -1}},		/* dd -1 2480 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2488 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2496 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2504 */
	{.type Header, {.hdr { 3, "off", /* C_off = 2520 */ colon }}}, /* CENTRY "off" off 3 ; ( a -- ) (G stores 0 at a ) h 2528 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2536 */
	{.type Absolute, {.p 0}},		/* dd 0 2544 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2552 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2560 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2568 */
	{.type Header, {.hdr { 5, ">body", /* C_tobody = 2584 */ colon }}}, /* CENTRY ">body" tobody 5 h 2592 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2600 */
	{.type Absolute, {.p 8}},		/* dd 8 2608 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2616 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2624 */
	{.type Header, {.hdr { 7, "aligned", /* C_aligned = 2640 */ colon }}}, /* CENTRY "aligned" aligned 7 ; align a number to a multiple of 8 h 2648 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2656 */
	{.type Absolute, {.p 7}},		/* dd 7 2664 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2672 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2680 */
	{.type Absolute, {.p -8}},		/* dd -8 2688 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 2696 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2704 */
	{.type Header, {.hdr { 5, "cells", /* C_cells = 2720 */ colon }}}, /* CENTRY "cells" cells 5 h 2728 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2736 */
	{.type Absolute, {.p 3}},		/* dd 3			; (index << 2) -> (index << 3) for amd64 2744 */
	{.type FromH0, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 2752 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2760 */
	{.type Header, {.hdr { 5, "cell+", /* C_cellplus = 2776 */ colon }}}, /* CENTRY "cell+" cellplus 5 h 2784 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2792 */
	{.type Absolute, {.p 1}},		/* dd 1 2800 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 2808 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2816 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2824 */
	{.type Header, {.hdr { 5, "depth", /* C_depth = 2840 */ colon }}}, /* CENTRY "depth" depth 5 h 2848 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 2856 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 2864 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 2872 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2880 */
	{.type Absolute, {.p 3}},		/* dd 3 2888 */
	{.type FromH0, {.p M_rshift}, .src = "dd M_rshift"},		/* dd M_rshift 2896 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2904 */
	{.type Absolute, {.p 1}},		/* dd 1 2912 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 2920 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2928 */
	{.type Header, {.hdr { 3, "nip", /* C_nip = 2944 */ colon }}}, /* CENTRY "nip" nip 3 h 2952 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2960 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 2968 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2976 */
	{.type Header, {.hdr { 3, "rot", /* C_rot = 2992 */ colon }}}, /* CENTRY "rot" rot 3 h 3000 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3008 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3016 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3024 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3032 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3040 */
	{.type Header, {.hdr { 5, "2drop", /* C_2drop = 3056 */ colon }}}, /* CENTRY "2drop" 2drop 5 h 3064 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3072 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3080 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3088 */
	{.type Header, {.hdr { 4, "2dup", /* C_2dup = 3104 */ colon }}}, /* CENTRY "2dup" 2dup 4 h 3112 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3120 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3136 */
	{.type Header, {.hdr { 4, "2nip", /* C_2nip = 3152 */ colon }}}, /* CENTRY "2nip" 2nip 4 h 3160 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3168 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3176 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3184 */
	{.type Header, {.hdr { 5, "2swap", /* C_2swap = 3200 */ colon }}}, /* CENTRY "2swap" 2swap 5 h 3208 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3216 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3224 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3232 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3240 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3248 */
	{.type Header, {.hdr { 4, "?dup", /* C_qdup = 3264 */ colon }}}, /* CENTRY "?dup" qdup 4 ; if (n != 0) ( n -- n n) else ( n -- n ) h 3272 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n -- n n )"},		/* dd M_dup	; ( n -- n n ) 3280 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n n -- n n n )"},		/* dd M_dup	; ( n n -- n n n ) 3288 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3296 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( n n n -- n n n 0 ) 3304 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n n n 0 -- n n f )"},		/* dd M_equal	; ( n n n 0 -- n n f ) 3312 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; ( n n f -- n n )"},		/* dd M_cjump	; ( n n f -- n n ) 3320 */
	{.type FromH0, {.p L20}, .src = "dd L20		; when n != 0, go to L20"},		/* dd L20		; when n != 0, go to L20 3328 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; when n == 0 ( n n -- n)"},		/* dd M_drop	; when n == 0 ( n n -- n) 3336 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3344 */
	{.type Header, {.hdr { 4, "pick", /* C_pick = 3360 */ colon }}}, /* CENTRY "pick" pick 4 h 3368 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 3376 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 3384 */
	{.type FromH0, {.p L22}, .src = "dd L22"},		/* dd L22 3392 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3400 */
	{.type Absolute, {.p 1}},		/* dd 1 3408 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3416 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 3424 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 3432 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3440 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3448 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 3456 */
	{.type FromH0, {.p L23}, .src = "dd L23"},		/* dd L23 3464 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3472 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3480 */
	{.type Header, {.hdr { 4, "tuck", /* C_tuck = 3496 */ colon }}}, /* CENTRY "tuck" tuck 4 h 3504 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3512 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3520 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3528 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3536 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3544 */
	{.type Header, {.hdr { 1, "/", /* C_divides = 3560 */ colon }}}, /* CENTRY "/" divides 1 h 3568 */
	{.type FromH0, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 3576 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3584 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3592 */
	{.type Header, {.hdr { 2, "+!", /* C_plusstore = 3608 */ colon }}}, /* CENTRY "+!" plusstore 2 h 3616 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3624 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3632 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3640 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3648 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3656 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 3664 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3672 */
	{.type Header, {.hdr { 6, "invert", /* C_invert = 3688 */ colon }}}, /* CENTRY "invert" invert 6 h 3696 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3704 */
	{.type Absolute, {.p -1}},		/* dd -1 3712 */
	{.type FromH0, {.p M_binxor}, .src = "dd M_binxor"},		/* dd M_binxor 3720 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3728 */
	{.type Header, {.hdr { 3, "mod", /* C_mod = 3744 */ colon }}}, /* CENTRY "mod" mod 3 h 3752 */
	{.type FromH0, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 3760 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3768 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3776 */
	{.type Header, {.hdr { 2, "1+", /* C_1plus = 3792 */ colon }}}, /* CENTRY "1+" 1plus 2 h 3800 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3808 */
	{.type Absolute, {.p 1}},		/* dd 1 3816 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3824 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3832 */
	{.type Header, {.hdr { 2, "1-", /* C_1minus = 3848 */ colon }}}, /* CENTRY "1-" 1minus 2 h 3856 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3864 */
	{.type Absolute, {.p 1}},		/* dd 1 3872 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3880 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3888 */
	{.type Header, {.hdr { 6, "negate", /* C_negate = 3904 */ colon }}}, /* CENTRY "negate" negate 6 h 3912 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3920 */
	{.type Absolute, {.p 0}},		/* dd 0 3928 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3936 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3944 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3952 */
	{.type Header, {.hdr { 2, "2*", /* C_2multiplies = 3968 */ colon }}}, /* CENTRY "2*" 2multiplies 2 h 3976 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3984 */
	{.type Absolute, {.p 1}},		/* dd 1 3992 */
	{.type FromH0, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 4000 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4008 */
	{.type Header, {.hdr { 2, "2/", /* C_2divides = 4024 */ colon }}}, /* CENTRY "2/" 2divides 2 h 4032 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4040 */
	{.type Absolute, {.p 1}},		/* dd 1 4048 */
	{.type FromH0, {.p M_rshifta}, .src = "dd M_rshifta"},		/* dd M_rshifta 4056 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4064 */
	{.type Header, {.hdr { 2, "0=", /* C_0eq = 4080 */ colon }}}, /* CENTRY "0=" 0eq 2 h 4088 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4096 */
	{.type Absolute, {.p 0}},		/* dd 0 4104 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4112 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4120 */
	{.type Header, {.hdr { 2, "0<", /* C_0lt = 4136 */ colon }}}, /* CENTRY "0<" 0lt 2 h 4144 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4152 */
	{.type Absolute, {.p 0}},		/* dd 0 4160 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4168 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4176 */
	{.type Header, {.hdr { 2, "0>", /* C_0gt = 4192 */ colon }}}, /* CENTRY "0>" 0gt 2 h 4200 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4208 */
	{.type Absolute, {.p 0}},		/* dd 0 4216 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4224 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4232 */
	{.type Header, {.hdr { 2, "<>", /* C_neq = 4248 */ colon }}}, /* CENTRY "<>" neq 2 h 4256 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4264 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 4272 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4280 */
	{.type Header, {.hdr { 3, "0<>", /* C_0neq = 4296 */ colon }}}, /* CENTRY "0<>" 0neq 3 h 4304 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4312 */
	{.type Absolute, {.p 0}},		/* dd 0 4320 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 4328 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4336 */
	{.type Header, {.hdr { 3, "max", /* C_max = 4352 */ colon }}}, /* CENTRY "max" max 3 h 4360 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4368 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4376 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4384 */
	{.type FromH0, {.p L40}, .src = "dd L40"},		/* dd L40 4392 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4400 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4408 */
	{.type FromH0, {.p L41}, .src = "dd L41"},		/* dd L41 4416 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4424 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4432 */
	{.type Header, {.hdr { 3, "min", /* C_min = 4448 */ colon }}}, /* CENTRY "min" min 3 h 4456 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4464 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4472 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4480 */
	{.type FromH0, {.p L43}, .src = "dd L43"},		/* dd L43 4488 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4496 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4504 */
	{.type FromH0, {.p L44}, .src = "dd L44"},		/* dd L44 4512 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4520 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4528 */
	{.type Header, {.hdr { 6, "signum", /* C_signum = 4544 */ colon }}}, /* CENTRY "signum" signum 6 h 4552 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4560 */
	{.type FromH0, {.p C_0gt}, .src = "dd C_0gt"},		/* dd C_0gt 4568 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4576 */
	{.type FromH0, {.p L46}, .src = "dd L46"},		/* dd L46 4584 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4592 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4600 */
	{.type Absolute, {.p 1}},		/* dd 1 4608 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4616 */
	{.type FromH0, {.p L47}, .src = "dd L47"},		/* dd L47 4624 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 4632 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4640 */
	{.type FromH0, {.p L48}, .src = "dd L48"},		/* dd L48 4648 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4656 */
	{.type Absolute, {.p -1}},		/* dd -1 4664 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4672 */
	{.type FromH0, {.p L49}, .src = "dd L49"},		/* dd L49 4680 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4688 */
	{.type Absolute, {.p 0}},		/* dd 0 4696 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4704 */
	{.type Header, {.hdr { 6, "within", /* C_within = 4720 */ colon }}}, /* CENTRY "within" within 6 h 4728 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 4736 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 4744 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4752 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4760 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 4768 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 4776 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4784 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4792 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 4800 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4808 */
	{.type Header, {.hdr { 3, "abs", /* C_abs = 4824 */ colon }}}, /* CENTRY "abs" abs 3 h 4832 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4840 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 4848 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4856 */
	{.type FromH0, {.p L52}, .src = "dd L52"},		/* dd L52 4864 */
	{.type FromH0, {.p C_negate}, .src = "dd C_negate"},		/* dd C_negate 4872 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4880 */
	{.type Header, {.hdr { 3, "key", /* C_key = 4896 */ colon }}}, /* CENTRY "key" key 3 ; ( -- c ) (G read a single character from the input onto the stack ) h 4904 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 4912 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( infd )"},		/* dd M_fetch		; ( infd ) 4920 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf to store the character read"},		/* dd MV_Iobuf		; variable iobuf to store the character read 4928 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4936 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( infd Iobuf 1 ) 4944 */
	{.type FromH0, {.p M_sysread}, .src = "dd M_sysread	; ( infd Iobuf 1 -- n )"},		/* dd M_sysread	; ( infd Iobuf 1 -- n ) 4952 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4960 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump		; if 0 characters read"},		/* dd M_cjump		; if 0 characters read 4968 */
	{.type FromH0, {.p L78}, .src = "dd L78			; if qread n != 0 jump to L78. If n == 0 jump over"},		/* dd L78			; if qread n != 0 jump to L78. If n == 0 jump over 4976 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 4984 */
	{.type FromH0, {.p C_on}, .src = "dd C_on		; EOF"},		/* dd C_on		; EOF 4992 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5000 */
	{.type Absolute, {.p -1}},		/* dd -1			; return -1 when EOF 5008 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5016 */
	{.type FromH0, {.p L79}, .src = "dd L79"},		/* dd L79 5024 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; get the character from Iobuf to stack"},		/* dd MV_Iobuf		; get the character from Iobuf to stack 5032 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( -- c ) return the character read if not EOF"},		/* dd M_cfetch	; ( -- c ) return the character read if not EOF 5040 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5048 */
	{.type Header, {.hdr { 4, "emit", /* C_emit = 5064 */ colon }}}, /* CENTRY "emit" emit 4 ; ( character -- ) h 5072 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5080 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; variable iobuf has character"},		/* dd M_cstore	; variable iobuf has character 5088 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 5096 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; outfd"},		/* dd M_fetch		; outfd 5104 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5112 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5120 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( outfd iobuf 1 ) 5128 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite	; ( 1 iobuf outfd --  )"},		/* dd M_syswrite	; ( 1 iobuf outfd --  ) 5136 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5144 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5152 */
	{.type Header, {.hdr { 4, "type", /* C_type = 5168 */ colon }}}, /* CENTRY "type" type 4 ; ( addr n -- ) h 5176 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush			; ( addr ) (R n )"},		/* dd M_rpush			; ( addr ) (R n ) 5184 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush			; ( ) (R n addr )"},		/* dd M_rpush			; ( ) (R n addr ) 5192 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5200 */
	{.type Absolute, {.p 1}},		/* dd 1				; stdout 5208 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop			; ( stdout addr ) (R n )"},		/* dd M_rpop			; ( stdout addr ) (R n ) 5216 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop			; ( stdout addr n ) (R )"},		/* dd M_rpop			; ( stdout addr n ) (R ) 5224 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite		; ( 1 addr n --  )"},		/* dd M_syswrite		; ( 1 addr n --  ) 5232 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5240 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5248 */
	{.type Header, {.hdr { 2, "cr", /* C_cr = 5264 */ colon }}}, /* CENTRY "cr" cr 2 h 5272 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5280 */
	{.type Absolute, {.p 10}},		/* dd 10			; ascii value of carriage return 5288 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit			; emit"},		/* dd C_emit			; emit 5296 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5304 */
	{.type Header, {.hdr { 5, "space", /* C_space = 5320 */ colon }}}, /* CENTRY "space" space 5 h 5328 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5336 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5344 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5352 */
	{.type Header, {.hdr { 5, "emits", /* C_emits = 5368 */ colon }}}, /* CENTRY "emits" emits 5 h 5376 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5384 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5392 */
	{.type FromH0, {.p L86}, .src = "dd L86"},		/* dd L86 5400 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5408 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5416 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5424 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5432 */
	{.type FromH0, {.p L85}, .src = "dd L85"},		/* dd L85 5440 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 5448 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5456 */
	{.type Header, {.hdr { 6, "spaces", /* C_spaces = 5472 */ colon }}}, /* CENTRY "spaces" spaces 6 h 5480 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5488 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 5496 */
	{.type FromH0, {.p C_emits}, .src = "dd C_emits"},		/* dd C_emits 5504 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5512 */
	{.type Header, {.hdr { 5, "count", /* C_count = 5528 */ colon }}}, /* CENTRY "count" count 5 ; ( a -- a+1 n ) a = address of counted string ( a - a+1 a[0]) h 5536 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 5544 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 5552 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5560 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5568 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5576 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup ; debug show the word name to search"},		/* dd C_2dup ; debug show the word name to search 5584 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5592 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 5600 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush ; debug show the dictionary entry"},		/* dd M_rpush ; debug show the dictionary entry 5608 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 5616 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 5624 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5632 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5640 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5648 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 5656 */
	{.type Header, {.hdr { 7, "compare", /* C_compare = 5672 */ colon }}}, /* CENTRY "compare" compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search h 5680 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 )"},		/* dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 5688 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 )"},		/* dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 ) 5696 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- ) 5704 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- ) 5712 */
	{.type FromH0, {.p C_min}, .src = "dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- )"},		/* dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- ) 5720 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5728 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- ) 5736 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- )"},		/* dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- ) 5744 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5752 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 5760 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 5768 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5776 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5784 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 5792 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 5800 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5808 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 5816 */
	{.type FromH0, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 5824 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5832 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5840 */
	{.type FromH0, {.p L56}, .src = "dd L56		; matches"},		/* dd L56		; matches 5848 */
	{.type FromH0, {.p C_2nip}, .src = "dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- )"},		/* dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- ) 5856 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2)"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2) 5864 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 -- )"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 -- ) 5872 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5880 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 5888 */
	{.type FromH0, {.p L55}, .src = "dd L55"},		/* dd L55 5896 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- )"},		/* dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- ) 5904 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5912 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( n2 n1 -- ) (R -- )"},		/* dd M_rpop	; ( n2 n1 -- ) (R -- ) 5920 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( -- n1-n2 )"},		/* dd M_minus	; ( -- n1-n2 ) 5928 */
	{.type FromH0, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 5936 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5944 */
	{.type Header, {.hdr { 5, "erase", /* C_erase = 5960 */ colon }}}, /* CENTRY "erase" erase 5 h 5968 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5976 */
	{.type Absolute, {.p 0}},		/* dd 0 5984 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 5992 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6000 */
	{.type Absolute, {.p 0}},		/* dd 0 6008 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6016 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6024 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 6032 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6040 */
	{.type FromH0, {.p L58}, .src = "dd L58"},		/* dd L58 6048 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6056 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6064 */
	{.type Header, {.hdr { 4, "fill", /* C_fill = 6080 */ colon }}}, /* CENTRY "fill" fill 4 h 6088 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6096 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6104 */
	{.type Absolute, {.p 0}},		/* dd 0 6112 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6120 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 6128 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6136 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6144 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6152 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6160 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6168 */
	{.type FromH0, {.p L60}, .src = "dd L60"},		/* dd L60 6176 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 6184 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6192 */
	{.type Header, {.hdr { 5, "blank", /* C_blank = 6208 */ colon }}}, /* CENTRY "blank" blank 5 h 6216 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 6224 */
	{.type FromH0, {.p C_fill}, .src = "dd C_fill"},		/* dd C_fill 6232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6240 */
	{.type Header, {.hdr { 6, "search", /* C_search = 6256 */ colon }}}, /* CENTRY "search" search 6 h 6264 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6272 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6280 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6288 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 6296 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 6304 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6312 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6320 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6328 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 6336 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6344 */
	{.type Absolute, {.p 0}},		/* dd 0 6352 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6360 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6368 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6376 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6384 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6392 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6400 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6408 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6416 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6424 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6432 */
	{.type FromH0, {.p C_compare}, .src = "dd C_compare"},		/* dd C_compare 6440 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 6448 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 6456 */
	{.type FromH0, {.p L65}, .src = "dd L65"},		/* dd L65 6464 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6472 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6480 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6488 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6496 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 6504 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6512 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6520 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6528 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 6536 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6544 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6552 */
	{.type FromH0, {.p L64}, .src = "dd L64"},		/* dd L64 6560 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6568 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6576 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 6584 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6592 */
	{.type Header, {.hdr { 4, "here", /* C_here = 6608 */ colon }}}, /* CENTRY "here" here 4 h 6616 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6624 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6632 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6640 */
	{.type Header, {.hdr { 4, "vhere", /* C_vhere = 6656 */ colon }}}, /* CENTRY "vhere" vhere 4 h 6664 */
	{.type FromH0, {.p M_Vp}, .src = "dd M_Vp"},		/* dd M_Vp 6672 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6680 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6688 */
	{.type Header, {.hdr { 1, ",", /* C_comma = 6704 */ colon }}}, /* CENTRY "," comma 1 h 6712 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6720 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6728 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6736 */
	{.type Absolute, {.p 8}},		/* dd 8 6744 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6752 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6760 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6768 */
	{.type Header, {.hdr { 2, "c,", /* C_c = 6784 */ colon }}}, /* CENTRY "c," c 2 h 6792 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6800 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6808 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6816 */
	{.type Absolute, {.p 1}},		/* dd 1 6824 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6832 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6840 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6848 */
	{.type Header, {.hdr { 5, "allot", /* C_allot = 6864 */ colon }}}, /* CENTRY "allot" allot 5 ; ( n -- ) here = here+n h 6872 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6880 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6888 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6896 */
	{.type Header, {.hdr { 6, "vallot", /* C_vallot = 6912 */ colon }}}, /* CENTRY "vallot" vallot 6 ; allot on the variable space ( n -- ) vhere = vhere+n h 6920 */
	{.type FromH0, {.p M_Vp}, .src = "dd M_Vp"},		/* dd M_Vp 6928 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6936 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6944 */
	{.type Header, {.hdr { 3, "pad", /* C_pad = 6960 */ colon }}}, /* CENTRY "pad" pad 3 h 6968 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6976 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6984 */
	{.type Absolute, {.p 256}},		/* dd 256 6992 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7000 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7008 */
	{.type Header, {.hdr { 5, "align", /* C_align = 7024 */ colon }}}, /* CENTRY "align" align 5 ; ( -- ) align here to a cell boundary h 7032 */
	{.type FromH0, {.p C_here}, .src = "dd C_here		; Dp @"},		/* dd C_here		; Dp @ 7040 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned	; here is aligned to a multiple of 8"},		/* dd C_aligned	; here is aligned to a multiple of 8 7048 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp			; store the aligned here at Dp"},		/* dd M_Dp			; store the aligned here at Dp 7056 */
	{.type FromH0, {.p M_store}, .src = "dd M_store		; Dp contains aligned_here"},		/* dd M_store		; Dp contains aligned_here 7064 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7072 */
	{.type Header, {.hdr { 6, "unused", /* C_unused = 7088 */ colon }}}, /* CENTRY "unused" unused 6 h 7096 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 7104 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7112 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 7120 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7136 */
	{.type Header, {.hdr { 2, "<#", /* C_fromhash = 7152 */ colon }}}, /* CENTRY "<#" fromhash 2 h 7160 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7168 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7176 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7184 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7192 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7200 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7208 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7216 */
	{.type Header, {.hdr { 1, "#", /* C_hash = 7232 */ colon }}}, /* CENTRY "#" hash 1 h 7240 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 7248 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7256 */
	{.type FromH0, {.p M_uslashmod}, .src = "dd M_uslashmod"},		/* dd M_uslashmod 7264 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7272 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7280 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7288 */
	{.type Absolute, {.p 9}},		/* dd 9 7296 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 7304 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7312 */
	{.type FromH0, {.p L92}, .src = "dd L92"},		/* dd L92 7320 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7328 */
	{.type Absolute, {.p 97}},		/* dd 97 7336 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7344 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7352 */
	{.type Absolute, {.p 10}},		/* dd 10 7360 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7368 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7376 */
	{.type FromH0, {.p L93}, .src = "dd L93"},		/* dd L93 7384 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7392 */
	{.type Absolute, {.p 48}},		/* dd 48 7400 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7408 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7416 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7424 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7432 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7440 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7448 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7456 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7464 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7472 */
	{.type Header, {.hdr { 2, "#s", /* C_hashs = 7488 */ colon }}}, /* CENTRY "#s" hashs 2 h 7496 */
	{.type FromH0, {.p C_hash}, .src = "dd C_hash"},		/* dd C_hash 7504 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7512 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7520 */
	{.type FromH0, {.p L96}, .src = "dd L96"},		/* dd L96 7528 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7536 */
	{.type FromH0, {.p L95}, .src = "dd L95"},		/* dd L95 7544 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7552 */
	{.type Header, {.hdr { 2, "#>", /* C_hashfrom = 7568 */ colon }}}, /* CENTRY "#>" hashfrom 2 h 7576 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 7584 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7592 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7600 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7608 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7616 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7624 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7632 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7640 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7648 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7656 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7664 */
	{.type Header, {.hdr { 4, "hold", /* C_hold = 7680 */ colon }}}, /* CENTRY "hold" hold 4 h 7688 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7696 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7704 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7712 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7720 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 7728 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7736 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 7744 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7752 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7760 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7768 */
	{.type Header, {.hdr { 4, "sign", /* C_sign = 7784 */ colon }}}, /* CENTRY "sign" sign 4 h 7792 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 7800 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7808 */
	{.type FromH0, {.p L100}, .src = "dd L100"},		/* dd L100 7816 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7824 */
	{.type Absolute, {.p 45}},		/* dd 45 7832 */
	{.type FromH0, {.p C_hold}, .src = "dd C_hold"},		/* dd C_hold 7840 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7848 */
	{.type Header, {.hdr { 1, ".", /* C_dot = 7864 */ colon }}}, /* CENTRY "." dot 1 ; print the top of stack ( n -- ) h 7872 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; ( n -- n n )"},		/* dd M_dup		; ( n -- n n ) 7880 */
	{.type FromH0, {.p C_abs}, .src = "dd C_abs		; ( n n -- n u )"},		/* dd C_abs		; ( n n -- n u ) 7888 */
	{.type FromH0, {.p C_fromhash}, .src = "dd C_fromhash	; pad = h+256; >num = pad+1024"},		/* dd C_fromhash	; pad = h+256; >num = pad+1024 7896 */
	{.type FromH0, {.p C_hashs}, .src = "dd C_hashs		; ( n u1 -- n n2 )"},		/* dd C_hashs		; ( n u1 -- n n2 ) 7904 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap		; ( n n2 -- n2 n )"},		/* dd M_xswap		; ( n n2 -- n2 n ) 7912 */
	{.type FromH0, {.p C_sign}, .src = "dd C_sign		; ( n2 n -- n2 )"},		/* dd C_sign		; ( n2 n -- n2 ) 7920 */
	{.type FromH0, {.p C_hashfrom}, .src = "dd C_hashfrom	; ( u1 -- a n )"},		/* dd C_hashfrom	; ( u1 -- a n ) 7928 */
	{.type FromH0, {.p C_type}, .src = "dd C_type		; ( a n -- )"},		/* dd C_type		; ( a n -- ) 7936 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 7944 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7952 */
	{.type Header, {.hdr { 2, ".r", /* C_dotr = 7968 */ colon }}}, /* CENTRY ".r" dotr 2 h 7976 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 7984 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7992 */
	{.type FromH0, {.p C_abs}, .src = "dd C_abs"},		/* dd C_abs 8000 */
	{.type FromH0, {.p C_fromhash}, .src = "dd C_fromhash"},		/* dd C_fromhash 8008 */
	{.type FromH0, {.p C_hashs}, .src = "dd C_hashs"},		/* dd C_hashs 8016 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 8024 */
	{.type FromH0, {.p C_sign}, .src = "dd C_sign"},		/* dd C_sign 8032 */
	{.type FromH0, {.p C_hashfrom}, .src = "dd C_hashfrom"},		/* dd C_hashfrom 8040 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 8048 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 8056 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8064 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8072 */
	{.type Absolute, {.p 0}},		/* dd 0 8080 */
	{.type FromH0, {.p C_max}, .src = "dd C_max"},		/* dd C_max 8088 */
	{.type FromH0, {.p C_spaces}, .src = "dd C_spaces"},		/* dd C_spaces 8096 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 8104 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8112 */
	{.type Header, {.hdr { 3, "hex", /* C_hex = 8128 */ colon }}}, /* CENTRY "hex" hex 3 h 8136 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8144 */
	{.type Absolute, {.p 16}},		/* dd 16 8152 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8160 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8168 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8176 */
	{.type Header, {.hdr { 7, "decimal", /* C_decimal = 8192 */ colon }}}, /* CENTRY "decimal" decimal 7 h 8200 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8208 */
	{.type Absolute, {.p 10}},		/* dd 10 8216 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8224 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8240 */
	{.type Header, {.hdr { 5, "digit", /* C_digit = 8256 */ colon }}}, /* CENTRY "digit" digit 5 ; ( c -- ) h 8264 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8272 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8280 */
	{.type Absolute, {.p 65}},		/* dd 65 8288 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8296 */
	{.type Absolute, {.p 91}},		/* dd 91 8304 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8312 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8320 */
	{.type FromH0, {.p L106}, .src = "dd L106"},		/* dd L106 8328 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8336 */
	{.type Absolute, {.p 55}},		/* dd 55 8344 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8352 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8360 */
	{.type FromH0, {.p L107}, .src = "dd L107"},		/* dd L107 8368 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8376 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8384 */
	{.type Absolute, {.p 97}},		/* dd 97 8392 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8400 */
	{.type Absolute, {.p 123}},		/* dd 123 8408 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8416 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8424 */
	{.type FromH0, {.p L108}, .src = "dd L108"},		/* dd L108 8432 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8440 */
	{.type Absolute, {.p 87}},		/* dd 87 8448 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8456 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8464 */
	{.type FromH0, {.p L109}, .src = "dd L109"},		/* dd L109 8472 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8488 */
	{.type Absolute, {.p 48}},		/* dd 48 8496 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8504 */
	{.type Absolute, {.p 58}},		/* dd 58 8512 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8520 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8528 */
	{.type FromH0, {.p L110}, .src = "dd L110"},		/* dd L110 8536 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8544 */
	{.type Absolute, {.p 48}},		/* dd 48 8552 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8560 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8568 */
	{.type FromH0, {.p L111}, .src = "dd L111"},		/* dd L111 8576 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8584 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8592 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8600 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8608 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8616 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 8624 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 8632 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8640 */
	{.type FromH0, {.p L112}, .src = "dd L112"},		/* dd L112 8648 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 8656 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8664 */
	{.type FromH0, {.p L113}, .src = "dd L113"},		/* dd L113 8672 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8680 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8688 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8696 */
	{.type Header, {.hdr { 6, "number", /* C_number = 8712 */ colon }}}, /* CENTRY "number" number 6 ; ( a n1 -- n2 -1 | a n1 0 ) h 8720 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 -- n1 a )"},		/* dd M_xswap	; ( a n1 -- n1 a ) 8728 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n1 a -- n1 a a )"},		/* dd M_dup	; ( n1 a -- n1 a a ) 8736 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( n1 a a -- n1 a c )"},		/* dd M_cfetch	; ( n1 a a -- n1 a c ) 8744 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8752 */
	{.type Absolute, {.p 45}},		/* dd 45		; ( n1 a c -- n1 a c - ) 8760 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n1 a c -- n1 a f )"},		/* dd M_equal	; ( n1 a c -- n1 a f ) 8768 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; ( n1 a c -- n1 a )"},		/* dd M_cjump	; ( n1 a c -- n1 a ) 8776 */
	{.type FromH0, {.p L115}, .src = "dd L115		; c != -"},		/* dd L115		; c != - 8784 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; c == - ( n1 a -- n1 a+1 )"},		/* dd C_1plus	; c == - ( n1 a -- n1 a+1 ) 8792 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 8800 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 )"},		/* dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 ) 8808 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8816 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( a+1 n1-1 -- a+1 n1-1 -1 ) 8824 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1)"},		/* dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1) 8832 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8840 */
	{.type FromH0, {.p L116}, .src = "dd L116"},		/* dd L116 8848 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( n1 a -- a n1)"},		/* dd M_xswap	; ( n1 a -- a n1) 8856 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8864 */
	{.type Absolute, {.p 1}},		/* dd 1 8872 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1)"},		/* dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1) 8880 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a n1 -- a n1 n1 ) (R nr)"},		/* dd M_dup	; ( a n1 -- a n1 n1 ) (R nr) 8888 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1)"},		/* dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1) 8896 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8904 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a n1 -- a n1 0) (R nr n1) 8912 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1)"},		/* dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1) 8920 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8928 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a 0 n1 -- a 0 n1 0) (R nr n1) 8936 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1) 8944 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8952 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1) 8960 */
	{.type FromH0, {.p M_multiply}, .src = "dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1) 8968 */
	{.type FromH0, {.p M_over}, .src = "dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1)"},		/* dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1) 8976 */
	{.type FromH0, {.p M_i}, .src = "dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1) 8984 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1) 8992 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1)"},		/* dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1) 9000 */
	{.type FromH0, {.p C_digit}, .src = "dd C_digit"},		/* dd C_digit 9008 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9016 */
	{.type FromH0, {.p L118}, .src = "dd L118"},		/* dd L118 9024 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 9032 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9040 */
	{.type FromH0, {.p L119}, .src = "dd L119"},		/* dd L119 9048 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9056 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 9064 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9072 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9080 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9088 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 9096 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9104 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 9112 */
	{.type FromH0, {.p L117}, .src = "dd L117"},		/* dd L117 9120 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9128 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9136 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 9144 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9152 */
	{.type FromH0, {.p M_multiply}, .src = "dd M_multiply"},		/* dd M_multiply 9160 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 9168 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9176 */
	{.type Header, {.hdr { 5, "abort", /* C_abort = 9192 */ colon }}}, /* CENTRY "abort" abort 5 h 9200 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec"},		/* dd MV_Abortvec 9208 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9216 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 9224 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9232 */
	{.type Header, {.hdr { 6, "source", /* C_source = 9248 */ colon }}}, /* CENTRY "source" source 6 h 9256 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9264 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9272 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9280 */
	{.type Header, {.hdr { 13, "current-input", /* C_current_input = 9304 */ colon }}}, /* CENTRY "current-input" current_input 13 ; ( -- c ) read the next character from the location in Sourcebuf h 9312 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9320 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9328 */
	{.type FromH0, {.p C_source}, .src = "dd C_source"},		/* dd C_source 9336 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus		; Sourcebuf + >In"},		/* dd M_plus		; Sourcebuf + >In 9344 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 9352 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9360 */
	{.type Header, {.hdr { 10, "save-input", /* C_save_input = 9384 */ colon }}}, /* CENTRY "save-input" save_input 10 h 9392 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 9400 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9408 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9416 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9424 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9432 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9440 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9448 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 9456 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9464 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9472 */
	{.type Absolute, {.p 5}},		/* dd 5 9480 */
	{.type FromH0, {.p MV_Ninputs}, .src = "dd MV_Ninputs"},		/* dd MV_Ninputs 9488 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; Ninputs++"},		/* dd C_plusstore	; Ninputs++ 9496 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9504 */
	{.type Header, {.hdr { 13, "default-input", /* C_default_input = 9528 */ colon }}}, /* CENTRY "default-input" default_input 13 h 9536 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 9544 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9552 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9560 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9568 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9576 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib"},		/* dd M_Tib 9584 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9592 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9600 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 9608 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9616 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9624 */
	{.type Header, {.hdr { 13, "restore-input", /* C_restore_input = 9648 */ colon }}}, /* CENTRY "restore-input" restore_input 13 ; ( <input>|empty -- f ) h 9656 */
	{.type FromH0, {.p MV_Ninputs}, .src = "dd MV_Ninputs	; if Ninputs == 0, leave 0 on the stack. Or, Ninputs--"},		/* dd MV_Ninputs	; if Ninputs == 0, leave 0 on the stack. Or, Ninputs-- 9664 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9672 */
	{.type FromH0, {.p C_0neq}, .src = "dd C_0neq"},		/* dd C_0neq 9680 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9688 */
	{.type FromH0, {.p L300}, .src = "dd L300"},		/* dd L300 9696 */
	{.type FromH0, {.p MV_Ninputs}, .src = "dd MV_Ninputs	; there are <input>'s pending on the stack"},		/* dd MV_Ninputs	; there are <input>'s pending on the stack 9704 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9712 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 9720 */
	{.type FromH0, {.p MV_Ninputs}, .src = "dd MV_Ninputs"},		/* dd MV_Ninputs 9728 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9736 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9744 */
	{.type FromH0, {.p L301}, .src = "dd L301		; ( <input> -- <input>)"},		/* dd L301		; ( <input> -- <input>) 9752 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9760 */
	{.type Absolute, {.p 0}},		/* dd 0 9768 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 9776 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9784 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9792 */
	{.type Absolute, {.p 5}},		/* dd 5 9800 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 9808 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9816 */
	{.type FromH0, {.p L133}, .src = "dd L133"},		/* dd L133 9824 */
	{.type FromH0, {.p C_default_input}, .src = "dd C_default_input"},		/* dd C_default_input 9832 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 9840 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9848 */
	{.type FromH0, {.p L134}, .src = "dd L134"},		/* dd L134 9856 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 9864 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9872 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9880 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9888 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9896 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9904 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9912 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9920 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 9928 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9936 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 9944 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9952 */
	{.type Header, {.hdr { 14, "?restore-input", /* C_qrestore_input = 9976 */ colon }}}, /* CENTRY "?restore-input" qrestore_input 14 ; ( <input> -- f ) h 9984 */
	{.type FromH0, {.p C_restore_input}, .src = "dd C_restore_input"},		/* dd C_restore_input 9992 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 10000 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10008 */
	{.type FromH0, {.p L136}, .src = "dd L136"},		/* dd L136 10016 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 10024 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10032 */
	{.type FromH0, {.p L137}, .src = "dd L137"},		/* dd L137 10040 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10048 */
	{.type Absolute, {.p 23}},		/* dd 23 10056 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 10064 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 10072 */
	{.type FromH0, {.p C_depth}, .src = "dd C_depth"},		/* dd C_depth 10080 */
	{.type FromH0, {.p C_dot}, .src = "dd C_dot"},		/* dd C_dot 10088 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 10096 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 10104 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10112 */
	{.type Header, {.hdr { 10, "next-input", /* C_next_input = 10136 */ colon }}}, /* CENTRY "next-input" next_input 10 ; when >In < >Limit ( -- true c ). ( -- 0 false ) otherwise h 10144 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10152 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10160 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 10168 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10176 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 10184 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10192 */
	{.type FromH0, {.p L139}, .src = "dd L139	; >In >= >Limit"},		/* dd L139	; >In >= >Limit 10200 */
	{.type FromH0, {.p C_true}, .src = "dd C_true	; >In < >Limit"},		/* dd C_true	; >In < >Limit 10208 */
	{.type FromH0, {.p C_current_input}, .src = "dd C_current_input	; ( -- c )"},		/* dd C_current_input	; ( -- c ) 10216 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 10224 */
	{.type FromH0, {.p L140}, .src = "dd L140"},		/* dd L140 10232 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10240 */
	{.type Absolute, {.p 0}},		/* dd 0 10248 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 10256 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10264 */
	{.type Header, {.hdr { 5, "parse", /* C_parse = 10280 */ colon }}}, /* CENTRY "parse" parse 5 ; ( c -- a ) Place the counted string in the address in Wordbuf and return that address. c = word delimiter. h 10288 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; ( c -- ) (R -- c )"},		/* dd M_rpush		; ( c -- ) (R -- c ) 10296 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf"},		/* dd MV_Wordbuf 10304 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( -- Wordb )"},		/* dd M_fetch		; ( -- Wordb ) 10312 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus		; ( Wordb -- Wordb+1 )"},		/* dd C_1plus		; ( Wordb -- Wordb+1 ) 10320 */
	{.type FromH0, {.p C_next_input}, .src = "dd C_next_input ; ( Wordb+1 -- Wordb+1 f c )"},		/* dd C_next_input ; ( Wordb+1 -- Wordb+1 f c ) 10328 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c )"},		/* dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c ) 10336 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) )"},		/* dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) ) 10344 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 10352 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10360 */
	{.type FromH0, {.p L143}, .src = "dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew"},		/* dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew 10368 */
	{.type FromH0, {.p C_current_input}, .src = "dd C_current_input	; ( Wordb+1 -- Wordb+1 c )"},		/* dd C_current_input	; ( Wordb+1 -- Wordb+1 c ) 10376 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 10384 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1"},		/* dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1 10392 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus		; ( Wordb+1 -- Wordb+2 )"},		/* dd C_1plus		; ( Wordb+1 -- Wordb+2 ) 10400 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10408 */
	{.type Absolute, {.p 1}},		/* dd 1 10416 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10424 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10432 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 10440 */
	{.type FromH0, {.p L142}, .src = "dd L142		; ( Wordb+2 ) repeat"},		/* dd L142		; ( Wordb+2 ) repeat 10448 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10456 */
	{.type Absolute, {.p 1}},		/* dd 1 10464 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10472 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10480 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- )"},		/* dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- ) 10488 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; (Wordb+1 c -- Wordb+1)"},		/* dd M_drop		; (Wordb+1 c -- Wordb+1) 10496 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf"},		/* dd MV_Wordbuf 10504 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb)"},		/* dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb) 10512 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb)"},		/* dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb) 10520 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb)"},		/* dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb) 10528 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb)"},		/* dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb) 10536 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb)"},		/* dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb) 10544 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb)"},		/* dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb) 10552 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now."},		/* dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now. 10560 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( -- Wordb) (R Wordb -- )"},		/* dd M_rpop		; ( -- Wordb) (R Wordb -- ) 10568 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10576 */
	{.type Header, {.hdr { 4, "word", /* C_word = 10592 */ colon }}}, /* CENTRY "word" word 4 ; ( c -- a ) skip the c"s. Placed the counted string in a (as in Wordbuf) h 10600 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- ) (R -- c )"},		/* dd M_rpush	; ( -- ) (R -- c ) 10608 */
	{.type FromH0, {.p C_next_input}, .src = "dd C_next_input ; ( -- f c2 ) (R c1 -- )"},		/* dd C_next_input ; ( -- f c2 ) (R c1 -- ) 10616 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial )"},		/* dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial ) 10624 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial )"},		/* dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial ) 10632 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial )"},		/* dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial ) 10640 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10648 */
	{.type FromH0, {.p L146}, .src = "dd L146		; >In >= >Limit || cinitial != cnew"},		/* dd L146		; >In >= >Limit || cinitial != cnew 10656 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal	; >In < >Limit && cinitial == cnew"},		/* dd M_literal	; >In < >Limit && cinitial == cnew 10664 */
	{.type Absolute, {.p 1}},		/* dd 1 10672 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10680 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10688 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump		; repeat"},		/* dd M_jump		; repeat 10696 */
	{.type FromH0, {.p L145}, .src = "dd L145"},		/* dd L145 10704 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character"},		/* dd M_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character 10712 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 10720 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10728 */
	{.type Header, {.hdr { 6, "accept", /* C_accept = 10744 */ colon }}}, /* CENTRY "accept" accept 6 ; ( a n -- n ) get line or n chars or EOF from input and store at a h 10752 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( n a -- )"},		/* dd M_xswap	; ( n a -- ) 10760 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n a a -- )"},		/* dd M_dup	; ( n a a -- ) 10768 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 10776 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( n -- ) (R a a -- )"},		/* dd M_rpush	; ( n -- ) (R a a -- ) 10784 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup	; ( n n -- ) (R a a -- )"},		/* dd C_qdup	; ( n n -- ) (R a a -- ) 10792 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; (if)"},		/* dd M_cjump	; (if) 10800 */
	{.type FromH0, {.p L149}, .src = "dd L149	; n == 0"},		/* dd L149	; n == 0 10808 */
	{.type FromH0, {.p C_key}, .src = "dd C_key	; n > 0 ( n -- n c )"},		/* dd C_key	; n > 0 ( n -- n c ) 10816 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( -- n c c )"},		/* dd M_dup	; ( -- n c c ) 10824 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10832 */
	{.type Absolute, {.p 10}},		/* dd 10		; ( -- n c c 10 ) 10840 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n c c 10 -- n c f ) checking for newline"},		/* dd M_equal	; ( n c c 10 -- n c f ) checking for newline 10848 */
	{.type FromH0, {.p M_over}, .src = "dd M_over	; ( -- n c f c )"},		/* dd M_over	; ( -- n c f c ) 10856 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10864 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( -- n c f c -1 ) 10872 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( -- n c f1 f2 )"},		/* dd M_equal	; ( -- n c f1 f2 ) 10880 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor	; ( -- n c f )"},		/* dd M_binor	; ( -- n c f ) 10888 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10896 */
	{.type FromH0, {.p L150}, .src = "dd L150"},		/* dd L150 10904 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop	; n == -1 || n == 10 (	-- )"},		/* dd C_2drop	; n == -1 || n == 10 (	-- ) 10912 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 10920 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 10928 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( -- a2-a1 )"},		/* dd M_minus	; ( -- a2-a1 ) 10936 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; ( -- n ) (R -- )"},		/* dd M_exitcolon	; ( -- n ) (R -- ) 10944 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( n c a -- ) (R a a -- )"},		/* dd M_rfetch	; ( n c a -- ) (R a a -- ) 10952 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; store the character at a"},		/* dd M_cstore	; store the character at a 10960 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( n a -- ) (R a -- )"},		/* dd M_rpop	; ( n a -- ) (R a -- ) 10968 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 10976 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address"},		/* dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address 10984 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; ( n -- n-1 )"},		/* dd C_1minus	; ( n -- n-1 ) 10992 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11000 */
	{.type FromH0, {.p L148}, .src = "dd L148	; loop again for the next character"},		/* dd L148	; loop again for the next character 11008 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 )"},		/* dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 ) 11016 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( a2 a1 -- ) (R a1 -- )"},		/* dd M_rpop	; ( a2 a1 -- ) (R a1 -- ) 11024 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( a2 a1 -- a2-a1 )"},		/* dd M_minus	; ( a2 a1 -- a2-a1 ) 11032 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11040 */
	{.type Header, {.hdr { 5, "query", /* C_query = 11056 */ colon }}}, /* CENTRY "query" query 5 ; read from input stream into the Text Input Buffer h 11064 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 11072 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; clear EOF flag"},		/* dd C_off		; clear EOF flag 11080 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top"},		/* dd M_Tib	; constant puts address of tibuffer on the top 11088 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11096 */
	{.type Absolute, {.p 4096}},		/* dd 4096	; ( tibuffer -- tibuffer 4096 ) 11104 */
	{.type FromH0, {.p C_accept}, .src = "dd C_accept ; ( tibuffer 4096 -- n )"},		/* dd C_accept ; ( tibuffer 4096 -- n ) 11112 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n -- n n )"},		/* dd M_dup	; ( n -- n n ) 11120 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq	; ( n n -- n f )"},		/* dd C_0eq	; ( n n -- n f ) 11128 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 11136 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11144 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; n == 0 && EOF"},		/* dd M_binand	; n == 0 && EOF 11152 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11160 */
	{.type FromH0, {.p L152}, .src = "dd L152		; false condition"},		/* dd L152		; false condition 11168 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; n == 0 && EOF ( n -- )"},		/* dd M_drop	; n == 0 && EOF ( n -- ) 11176 */
	{.type FromH0, {.p C_qrestore_input}, .src = "dd C_qrestore_input"},		/* dd C_qrestore_input 11184 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11192 */
	{.type FromH0, {.p L153}, .src = "dd L153"},		/* dd L153 11200 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 11208 */
	{.type FromH0, {.p M_store}, .src = "dd M_store		; number of characters to read >Limit = n"},		/* dd M_store		; number of characters to read >Limit = n 11216 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 11224 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; start from 0 >In = 0"},		/* dd C_off		; start from 0 >In = 0 11232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11240 */
	{.type Header, {.hdr { 6, "refill", /* C_refill = 11256 */ colon }}}, /* CENTRY "refill" refill 6 h 11264 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 11272 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11280 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11288 */
	{.type FromH0, {.p L155}, .src = "dd L155"},		/* dd L155 11296 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 11304 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11312 */
	{.type FromH0, {.p L156}, .src = "dd L156"},		/* dd L156 11320 */
	{.type FromH0, {.p C_query}, .src = "dd C_query"},		/* dd C_query 11328 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 11336 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11344 */
	{.type Header, {.hdr { 8, "findname", /* C_findname = 11368 */ colon }}}, /* CENTRY "findname" findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names h 11376 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 11384 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11392 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop"},		/* dd M_Dtop 11400 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; get latest dictionary link"},		/* dd M_fetch	; get latest dictionary link 11408 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 11416 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11424 */
	{.type FromH0, {.p L159}, .src = "dd L159	; seached until the first dictionary entry get out"},		/* dd L159	; seached until the first dictionary entry get out 11432 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a )"},		/* dd M_dup	; ( a -- a a ) 11440 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; ( a a -- a a+8) lenth + initial name address"},		/* dd C_cellplus	; ( a a -- a a+8) lenth + initial name address 11448 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name"},		/* dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name 11456 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11464 */
	{.type Absolute, {.p 64}},		/* dd 64		; check the reveal'ed flag 1=hidden, 0=reveal 11472 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; if hidden, goto L161 else L160"},		/* dd M_binand	; if hidden, goto L161 else L160 11480 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11488 */
	{.type FromH0, {.p L160}, .src = "dd L160"},		/* dd L160 11496 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; smudge'd dictionary entry, get the previous entry"},		/* dd M_fetch	; smudge'd dictionary entry, get the previous entry 11504 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11512 */
	{.type FromH0, {.p L161}, .src = "dd L161"},		/* dd L161 11520 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a1 -- a1 a1)"},		/* dd M_dup	; ( a1 -- a1 a1) 11528 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; ( a1 a1 -- a1 a1+8)"},		/* dd C_cellplus	; ( a1 a1 -- a1 a1+8) 11536 */
	{.type FromH0, {.p C_count}, .src = "dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n )"},		/* dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n ) 11544 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11552 */
	{.type Absolute, {.p 63}},		/* dd 63 11560 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len )"},		/* dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len ) 11568 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 11576 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11584 */
	{.type FromH0, {.p C_count}, .src = "dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 )"},		/* dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 ) 11592 */
	{.type FromH0, {.p C_compare}, .src = "dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name"},		/* dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name 11600 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq	; found a match?"},		/* dd C_0eq	; found a match? 11608 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11616 */
	{.type FromH0, {.p L162}, .src = "dd L162		; no match"},		/* dd L162		; no match 11624 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; match found"},		/* dd C_cellplus	; match found 11632 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 11640 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11648 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11656 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11664 */
	{.type FromH0, {.p L158}, .src = "dd L158"},		/* dd L158 11672 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 11680 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11688 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 11696 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11704 */
	{.type Header, {.hdr { 4, "find", /* C_find = 11720 */ colon }}}, /* CENTRY "find" find 4 ; ( a1 -- a2 f )? h 11728 */
	{.type FromH0, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 11736 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11744 */
	{.type FromH0, {.p L164}, .src = "dd L164"},		/* dd L164 11752 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 11760 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 11768 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 11776 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 11784 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11792 */
	{.type Absolute, {.p 63}},		/* dd 63 11800 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 11808 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11816 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 11824 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 11832 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 11840 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11848 */
	{.type Absolute, {.p 128}},		/* dd 128 11856 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 11864 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11872 */
	{.type FromH0, {.p L165}, .src = "dd L165"},		/* dd L165 11880 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11888 */
	{.type Absolute, {.p 1}},		/* dd 1 11896 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11904 */
	{.type FromH0, {.p L166}, .src = "dd L166"},		/* dd L166 11912 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11920 */
	{.type Absolute, {.p -1}},		/* dd -1 11928 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11936 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11944 */
	{.type FromH0, {.p L167}, .src = "dd L167"},		/* dd L167 11952 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 11960 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11968 */
	{.type Header, {.hdr { 1, "'", /* C_single_quote = 11984 */ colon }}}, /* CENTRY "'" single_quote 1 h 11992 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 12000 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 12008 */
	{.type FromH0, {.p C_find}, .src = "dd C_find"},		/* dd C_find 12016 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 12024 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12032 */
	{.type FromH0, {.p L169}, .src = "dd L169"},		/* dd L169 12040 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 12048 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 12056 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12064 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12072 */
	{.type FromH0, {.p L170}, .src = "dd L170"},		/* dd L170 12080 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12088 */
	{.type Absolute, {.p 3}},		/* dd 3 12096 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12104 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12112 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12120 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12128 */
	{.type Header, {.hdr { 6, "?stack", /* C_qstack = 12144 */ colon }}}, /* CENTRY "?stack" qstack 6 h 12152 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 12160 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 12168 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 12176 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12184 */
	{.type FromH0, {.p L172}, .src = "dd L172"},		/* dd L172 12192 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12200 */
	{.type FromH0, {.p L173}, .src = "dd L173"},		/* dd L173 12208 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12216 */
	{.type Absolute, {.p 16}},		/* dd 16 12224 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12232 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12240 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12248 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12256 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT	; ( str -- str 1) ; debug code to show the word found"},		/* dd MC_STDOUT	; ( str -- str 1) ; debug code to show the word found 12264 */
	{.type FromH0, {.p M_over}, .src = "dd M_over		; ( str 1 str )"},		/* dd M_over		; ( str 1 str ) 12272 */
	{.type FromH0, {.p C_count}, .src = "dd C_count 		; ( str 1 a n)"},		/* dd C_count 		; ( str 1 a n) 12280 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 12288 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 12296 */
	{.type Header, {.hdr { 9, "interpret", /* C_interpret = 12320 */ colon }}}, /* CENTRY "interpret" interpret 9 ; there is stuff in TIB to be interpreted >In and >Limit are set h 12328 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 12336 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( bl -- a ) a = address of counted string"},		/* dd C_word	; ( bl -- a ) a = address of counted string 12344 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12352 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 12360 */
	{.type FromH0, {.p C_0neq}, .src = "dd C_0neq"},		/* dd C_0neq 12368 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12376 */
	{.type FromH0, {.p L176}, .src = "dd L176	; count at a = 0"},		/* dd L176	; count at a = 0 12384 */
	{.type FromH0, {.p C_find}, .src = "dd C_find	; ( a -- a1 f ) a = address of counted string"},		/* dd C_find	; ( a -- a1 f ) a = address of counted string 12392 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12400 */
	{.type FromH0, {.p L177}, .src = "dd L177"},		/* dd L177 12408 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute	; found in dictionary, execute"},		/* dd M_execute	; found in dictionary, execute 12416 */
	{.type FromH0, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 12424 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12432 */
	{.type FromH0, {.p L178}, .src = "dd L178"},		/* dd L178 12440 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 12448 */
	{.type FromH0, {.p C_number}, .src = "dd C_number"},		/* dd C_number 12456 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 12464 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12472 */
	{.type FromH0, {.p L179}, .src = "dd L179"},		/* dd L179 12480 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 12488 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12496 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12504 */
	{.type FromH0, {.p L180}, .src = "dd L180	; error I?"},		/* dd L180	; error I? 12512 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12520 */
	{.type Absolute, {.p 3}},		/* dd 3 12528 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12536 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12544 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12552 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12560 */
	{.type FromH0, {.p L175}, .src = "dd L175"},		/* dd L175 12568 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; count at a = 0 ( a -- )"},		/* dd M_drop	; count at a = 0 ( a -- ) 12576 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12584 */
	{.type Header, {.hdr { 6, "create", /* C_create = 12600 */ colon }}}, /* CENTRY "create" create 6 ; compiles dictionary header until the pfa (link, len, name, cfa) h 12608 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 12616 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here )"},		/* dd C_here	; ( -- here ) 12624 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- ) (R -- linkaddr )"},		/* dd M_rpush	; ( -- ) (R -- linkaddr ) 12632 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop	; ( -- Dtop ) (R -- linkaddr )"},		/* dd M_Dtop	; ( -- Dtop ) (R -- linkaddr ) 12640 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr )"},		/* dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr ) 12648 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; ( dtop -- ) (R -- linkaddr )"},		/* dd C_comma	; ( dtop -- ) (R -- linkaddr ) 12656 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 12664 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; get the word from the input stream ( c -- a ) skip any c. Placed the counted string in a (as in Wordbuf)"},		/* dd C_word	; get the word from the input stream ( c -- a ) skip any c. Placed the counted string in a (as in Wordbuf) 12672 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a ) (R -- linkaddr )"},		/* dd M_dup	; ( a -- a a ) (R -- linkaddr ) 12680 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a -- a len ) (R -- linkaddr )"},		/* dd M_cfetch	; ( a a -- a len ) (R -- linkaddr ) 12688 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( a len -- a len here ) (R -- linkaddr )"},		/* dd C_here	; ( a len -- a len here ) (R -- linkaddr ) 12696 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr )"},		/* dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr ) 12704 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte"},		/* dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte 12712 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr )"},		/* dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr ) 12720 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 )"},		/* dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 ) 12728 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 )"},		/* dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 ) 12736 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- len+1 ) (R -- linkaddr )"},		/* dd M_rpop	; ( -- len+1 ) (R -- linkaddr ) 12744 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1"},		/* dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1 12752 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 12760 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12768 */
	{.type FromH0, {.p M_variable}, .src = "dd M_variable"},		/* dd M_variable 12776 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( -- variablecfa) (R -- linkaddr )"},		/* dd M_fetch	; ( -- variablecfa) (R -- linkaddr ) 12784 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; ( -- ) put the variablecfa into the cfa"},		/* dd C_comma	; ( -- ) put the variablecfa into the cfa 12792 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- linkaddr) (R -- )"},		/* dd M_rpop	; ( -- linkaddr) (R -- ) 12800 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop"},		/* dd M_Dtop 12808 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; Dtop = just created link address"},		/* dd M_store	; Dtop = just created link address 12816 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12824 */
	{.type Header, {.hdr { 8, "variable", /* C_variable = 12848 */ colon }}}, /* CENTRY "variable" variable 8 ; compile to put the vhere then on the stack h 12856 */
	{.type FromH0, {.p C_create}, .src = "dd C_create"},		/* dd C_create 12864 */
	{.type FromH0, {.p C_vhere}, .src = "dd C_vhere"},		/* dd C_vhere 12872 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; put the next available variable location in pfa"},		/* dd C_comma	; put the next available variable location in pfa 12880 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12888 */
	{.type Absolute, {.p 1}},		/* dd 1 12896 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 12904 */
	{.type FromH0, {.p C_vallot}, .src = "dd C_vallot	; vhere = vhere+8, stored at Vp"},		/* dd C_vallot	; vhere = vhere+8, stored at Vp 12912 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12920 */
	{.type Header, {.hdr { 8, "constant", /* C_constant = 12944 */ colon }}}, /* CENTRY "constant" constant 8 ; ( n -- ) do the same as variable but change the cfa to (constant) h 12952 */
	{.type FromH0, {.p C_create}, .src = "dd C_create	; create dictionary header upto the cfa"},		/* dd C_create	; create dictionary header upto the cfa 12960 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12968 */
	{.type FromH0, {.p M_constant}, .src = "dd M_constant"},		/* dd M_constant 12976 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Contstantcfa -- (constant) )"},		/* dd M_fetch	; ( Contstantcfa -- (constant) ) 12984 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( (constant) -- (constant) here )"},		/* dd C_here	; ( (constant) -- (constant) here ) 12992 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13000 */
	{.type Absolute, {.p 1}},		/* dd 1 13008 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells	; ( (constant) here -- (constant) here 8 )"},		/* dd C_cells	; ( (constant) here -- (constant) here 8 ) 13016 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( (constant) here 8 -- (constant) here-8 )"},		/* dd M_minus	; ( (constant) here 8 -- (constant) here-8 ) 13024 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant) "},		/* dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant)  13032 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; store n into the dictionary"},		/* dd C_comma	; store n into the dictionary 13040 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13048 */
	{.type Header, {.hdr { 9, "immediate", /* C_immediate = 13072 */ colon }}}, /* CENTRY "immediate" immediate 9 h 13080 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 13088 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13096 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 13104 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13112 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13120 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13128 */
	{.type Absolute, {.p 128}},		/* dd 128 13136 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 13144 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 13152 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 13160 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13168 */
	{.type Header, {.hdr { 4, ">cfa", /* C_tocfa = 13184 */ colon }}}, /* CENTRY ">cfa" tocfa 4 h 13192 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13200 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13208 */
	{.type Absolute, {.p 63}},		/* dd 63 13216 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 13224 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 13232 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 13240 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13248 */
	{.type Header, {.hdr { 7, "compile", /* C_compile = 13264 */ colon }}}, /* CENTRY "compile" compile 7 h 13272 */
	{.type FromH0, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 13280 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13288 */
	{.type FromH0, {.p L188}, .src = "dd L188"},		/* dd L188 13296 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13304 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13312 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13320 */
	{.type Absolute, {.p 128}},		/* dd 128 13328 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 13336 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13344 */
	{.type FromH0, {.p L189}, .src = "dd L189"},		/* dd L189 13352 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa	; immediate"},		/* dd C_tocfa	; immediate 13360 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 13368 */
	{.type FromH0, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 13376 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13384 */
	{.type FromH0, {.p L190}, .src = "dd L190"},		/* dd L190 13392 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 13400 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 13408 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13416 */
	{.type FromH0, {.p L191}, .src = "dd L191"},		/* dd L191 13424 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13432 */
	{.type FromH0, {.p C_number}, .src = "dd C_number"},		/* dd C_number 13440 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 13448 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13456 */
	{.type FromH0, {.p L192}, .src = "dd L192"},		/* dd L192 13464 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 13472 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13488 */
	{.type FromH0, {.p L193}, .src = "dd L193"},		/* dd L193 13496 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13504 */
	{.type Absolute, {.p 3}},		/* dd 3 13512 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13520 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 13528 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 13536 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13544 */
	{.type FromH0, {.p L194}, .src = "dd L194"},		/* dd L194 13552 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13560 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13568 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 13576 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 13584 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13592 */
	{.type Header, {.hdr { 1, "]", /* C_close_bracket = 13608 */ colon }}}, /* CENTRY "]" close_bracket 1 h 13616 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 13624 */
	{.type FromH0, {.p C_on}, .src = "dd C_on"},		/* dd C_on 13632 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 13640 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 13648 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13656 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13664 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 13672 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13680 */
	{.type FromH0, {.p L197}, .src = "dd L197"},		/* dd L197 13688 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 13696 */
	{.type FromH0, {.p C_refill}, .src = "dd C_refill"},		/* dd C_refill 13704 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13712 */
	{.type FromH0, {.p L198}, .src = "dd L198"},		/* dd L198 13720 */
	{.type FromH0, {.p C_compile}, .src = "dd C_compile"},		/* dd C_compile 13728 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 13736 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13744 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13752 */
	{.type FromH0, {.p L199}, .src = "dd L199"},		/* dd L199 13760 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13768 */
	{.type FromH0, {.p L196}, .src = "dd L196"},		/* dd L196 13776 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13784 */
	{.type IHeader, {.hdr { 1, "[", /* CI_open_bracket = 13800 */ colon }}}, /* CIENTRY "[" open_bracket 1 h 13808 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 13816 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 13824 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13832 */
	{.type Header, {.hdr { 6, "smudge", /* C_smudge = 13848 */ colon }}}, /* CENTRY "smudge" smudge 6 h 13856 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 13864 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13872 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 13880 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13888 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13896 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13904 */
	{.type Absolute, {.p 64}},		/* dd 64 13912 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 13920 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 13928 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 13936 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13944 */
	{.type Header, {.hdr { 6, "reveal", /* C_reveal = 13960 */ colon }}}, /* CENTRY "reveal" reveal 6 h 13968 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 13976 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13984 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 13992 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14000 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14008 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14016 */
	{.type Absolute, {.p 64}},		/* dd 64 14024 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 14032 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 14040 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 14048 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 14056 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14064 */
	{.type Header, {.hdr { 1, ":", /* C_colon = 14080 */ colon }}}, /* CENTRY ":" colon 1 h 14088 */
	{.type FromH0, {.p C_create}, .src = "dd C_create	; create a dictionary header with (variable) at cfa"},		/* dd C_create	; create a dictionary header with (variable) at cfa 14096 */
	{.type FromH0, {.p C_smudge}, .src = "dd C_smudge"},		/* dd C_smudge 14104 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14112 */
	{.type FromH0, {.p M_colon}, .src = "dd M_colon"},		/* dd M_colon 14120 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon"},		/* dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon 14128 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( (colon) -- (colon) here )"},		/* dd C_here	; ( (colon) -- (colon) here ) 14136 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14144 */
	{.type Absolute, {.p 1}},		/* dd 1 14152 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 14160 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( (colon) here -- (colon) here-8 )"},		/* dd M_minus	; ( (colon) here -- (colon) here-8 ) 14168 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon"},		/* dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon 14176 */
	{.type FromH0, {.p C_close_bracket}, .src = "dd C_close_bracket"},		/* dd C_close_bracket 14184 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14192 */
	{.type IHeader, {.hdr { 1, ";", /* CI_semicolon = 14208 */ colon }}}, /* CIENTRY ";" semicolon 1 h 14216 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14224 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14232 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14240 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 14248 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 14256 */
	{.type FromH0, {.p C_reveal}, .src = "dd C_reveal"},		/* dd C_reveal 14264 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14272 */
	{.type IHeader, {.hdr { 7, "recurse", /* CI_recurse = 14288 */ colon }}}, /* CIENTRY "recurse" recurse 7 h 14296 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 14304 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14312 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 14320 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 14328 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14336 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14344 */
	{.type Header, {.hdr { 4, "char", /* C_char = 14360 */ colon }}}, /* CENTRY "char" char 4 ; ( -- c ) fetch the first character of the next word from input h 14368 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 14376 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( c -- a ) puts the address of the counted string from the input on the stack"},		/* dd C_word	; ( c -- a ) puts the address of the counted string from the input on the stack 14384 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; skip the count"},		/* dd C_1plus	; skip the count 14392 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; fetch the first character"},		/* dd M_cfetch	; fetch the first character 14400 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14408 */
	{.type Header, {.hdr { 7, "literal", /* C_literal = 14424 */ colon }}}, /* CENTRY "literal" literal 7 ; ( n -- ) adds (literal) n to the dictionary h 14432 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14440 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14448 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14456 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14464 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14472 */
	{.type Header, {.hdr { 8, "sliteral", /* C_sliteral = 14496 */ colon }}}, /* CENTRY "sliteral" sliteral 8 ; ( -- ) adds (sliteral) a n to the dictionary h 14504 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14512 */
	{.type FromH0, {.p M_sliteral}, .src = "dd M_sliteral"},		/* dd M_sliteral 14520 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; adds (sliteral) to the dictionary"},		/* dd C_comma	; adds (sliteral) to the dictionary 14528 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here)"},		/* dd C_here	; ( -- here) 14536 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14544 */
	{.type Absolute, {.p 34}},		/* dd 34		; ascii value of " 14552 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse	; ( here \" -- here a ) \" = word delimiter. a = address of counted string (in Wordbuf)."},		/* dd C_parse	; ( here \" -- here a ) \" = word delimiter. a = address of counted string (in Wordbuf). 14560 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( here a -- here a a )"},		/* dd M_dup	; ( here a -- here a a ) 14568 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( here a a -- here a n )"},		/* dd M_cfetch	; ( here a a -- here a n ) 14576 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( here a n -- here a n+1 ) n+1 as 1 for the count and n for the length of the string"},		/* dd C_1plus	; ( here a n -- here a n+1 ) n+1 as 1 for the count and n for the length of the string 14584 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( here a n+1 -- here a ) (R -- n+1)"},		/* dd M_rpush	; ( here a n+1 -- here a ) (R -- n+1) 14592 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( here a -- a here ) (R -- n+1)"},		/* dd M_xswap	; ( here a -- a here ) (R -- n+1) 14600 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( a here -- a here n+1 ) (R -- n+1 )"},		/* dd M_rfetch	; ( a here -- a here n+1 ) (R -- n+1 ) 14608 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; ( a here n+1 -- ) moves n+1 from a to here"},		/* dd M_cmove	; ( a here n+1 -- ) moves n+1 from a to here 14616 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- n+1 ) (R -- )"},		/* dd M_rpop	; ( -- n+1 ) (R -- ) 14624 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( n+1 -- ) here = here+n+1"},		/* dd C_allot	; ( n+1 -- ) here = here+n+1 14632 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; align here"},		/* dd C_align	; align here 14640 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14648 */
	{.type Header, {.hdr { 6, "string", /* C_string = 14664 */ colon }}}, /* CENTRY "string" string 6 ; ( c -- ) h 14672 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 14680 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14688 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14696 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 14704 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 14712 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 14720 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 14728 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 14736 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 14744 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 14752 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14760 */
	{.type IHeader, {.hdr { 6, "[char]", /* CI_char_brackets = 14776 */ colon }}}, /* CIENTRY "[char]" char_brackets 6 ; take the next character from the input stream during compilation h 14784 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 14792 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 14800 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 14808 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14816 */
	{.type FromH0, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 14824 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14832 */
	{.type IHeader, {.hdr { 3, "[']", /* CI_quote_brackets = 14848 */ colon }}}, /* CIENTRY "[']" quote_brackets 3 ; take the address of next token from the input stream during compilation h 14856 */
	{.type FromH0, {.p C_single_quote}, .src = "dd C_single_quote"},		/* dd C_single_quote 14864 */
	{.type FromH0, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 14872 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14880 */
	{.type IHeader, {.hdr { 1, "(", /* CI_openparen = 14896 */ colon }}}, /* CIENTRY "(" openparen 1 ; ignore until ) from the input stream during compilation h 14904 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14912 */
	{.type Absolute, {.p 41}},		/* dd 41 14920 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 14928 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 14936 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14944 */
	{.type IHeader, {.hdr { 1, "\\", /* CI_backslash = 14960 */ colon }}}, /* CIENTRY "\\" backslash 1 h 14968 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 14976 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14984 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14992 */
	{.type FromH0, {.p L214}, .src = "dd L214"},		/* dd L214 15000 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 15008 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 15016 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15024 */
	{.type Absolute, {.p 63}},		/* dd 63 15032 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 15040 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15048 */
	{.type Absolute, {.p 63}},		/* dd 63 15056 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 15064 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 15072 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 15080 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15088 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15096 */
	{.type FromH0, {.p L215}, .src = "dd L215"},		/* dd L215 15104 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 15112 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 15120 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 15128 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15136 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15144 */
	{.type Header, {.hdr { 8, "(?abort)", /* C_qabort_parens = 15168 */ colon }}}, /* CENTRY "(?abort)" qabort_parens 8 h 15176 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 15184 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15192 */
	{.type FromH0, {.p L217}, .src = "dd L217"},		/* dd L217 15200 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 15208 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 15216 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 15224 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 15232 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15240 */
	{.type FromH0, {.p L218}, .src = "dd L218"},		/* dd L218 15248 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 15256 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15264 */
	{.type IHeader, {.hdr { 6, "abort\"", /* CI_abort_double_quote = 15280 */ colon }}}, /* CIENTRY "abort\"" abort_double_quote 6 h 15288 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 15296 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15304 */
	{.type FromH0, {.p C_qabort_parens}, .src = "dd C_qabort_parens"},		/* dd C_qabort_parens 15312 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15320 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15328 */
	{.type Header, {.hdr { 1, "\"", /* C_double_quote = 15344 */ colon }}}, /* CENTRY "\"" double_quote 1 ; stores counted string in the dictionary and also leaves the address count of the string on the stack - used to use strings at the interpreter prompt h 15352 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15360 */
	{.type Absolute, {.p 34}},		/* dd 34 15368 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 15376 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 15384 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 15392 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15400 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 15408 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 15416 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15424 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 15432 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15440 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 15448 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15456 */
	{.type Header, {.hdr { 2, "c\"", /* C_cdouble_quote = 15472 */ colon }}}, /* CENTRY "c\"" cdouble_quote 2 ; stores counted string in the dictionary and also leaves the address of the counted string on the stack h 15480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15488 */
	{.type Absolute, {.p 34}},		/* dd 34		; ( -- \" ) 15496 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( \" -- a ) a = counted string address. a will be in Wordbuf"},		/* dd C_word	; ( \" -- a ) a = counted string address. a will be in Wordbuf 15504 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a)"},		/* dd M_dup	; ( a -- a a) 15512 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a -- a n )"},		/* dd M_cfetch	; ( a a -- a n ) 15520 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( a n -- a n+1 )"},		/* dd C_1plus	; ( a n -- a n+1 ) 15528 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n -- a ) (R -- n+1)"},		/* dd M_rpush	; ( a n -- a ) (R -- n+1) 15536 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( a -- a here ) (R -- n+1)"},		/* dd C_here	; ( a -- a here ) (R -- n+1) 15544 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( a here -- a here n+1) (R -- n+1)"},		/* dd M_rfetch	; ( a here -- a here n+1) (R -- n+1) 15552 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; move counted string from a to here"},		/* dd M_cmove	; move counted string from a to here 15560 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here )"},		/* dd C_here	; ( -- here ) 15568 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( here -- here n+1 )(R -- )"},		/* dd M_rpop	; ( here -- here n+1 )(R -- ) 15576 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( here n+1 -- here) here += n+1"},		/* dd C_allot	; ( here n+1 -- here) here += n+1 15584 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15592 */
	{.type IHeader, {.hdr { 2, "s\"", /* CI_sdouble_quote = 15608 */ colon }}}, /* CIENTRY "s\"" sdouble_quote 2 ; add the string from the input stream to the dictionary as (sliteral) count string - at run-time puts the ( -- addr n) of the counted string on the stack. h 15616 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 15624 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15632 */
	{.type IHeader, {.hdr { 2, ".\"", /* CI_dotstr = 15648 */ colon }}}, /* CIENTRY ".\"" dotstr 2 ; do what s" does and then add a type word to the dictionary to print that string h 15656 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 15664 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15672 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 15680 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15688 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15696 */
	{.type IHeader, {.hdr { 2, "if", /* CI_if = 15712 */ colon }}}, /* CIENTRY "if" if 2 h 15720 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15728 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15736 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15744 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15752 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15760 */
	{.type Absolute, {.p 0}},		/* dd 0 15768 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15776 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15784 */
	{.type IHeader, {.hdr { 4, "else", /* CI_else = 15800 */ colon }}}, /* CIENTRY "else" else 4 h 15808 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15816 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15824 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15832 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15840 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 15848 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15856 */
	{.type Absolute, {.p 0}},		/* dd 0 15864 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15872 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15880 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 15888 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15896 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 15904 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15912 */
	{.type IHeader, {.hdr { 4, "then", /* CI_then = 15928 */ colon }}}, /* CIENTRY "then" then 4 h 15936 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15944 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 15952 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15960 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15968 */
	{.type IHeader, {.hdr { 5, "begin", /* CI_begin = 15984 */ colon }}}, /* CIENTRY "begin" begin 5 h 15992 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16000 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16008 */
	{.type IHeader, {.hdr { 5, "again", /* CI_again = 16024 */ colon }}}, /* CIENTRY "again" again 5 h 16032 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16040 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16048 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16056 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16064 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16072 */
	{.type IHeader, {.hdr { 5, "until", /* CI_until = 16088 */ colon }}}, /* CIENTRY "until" until 5 h 16096 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16104 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16112 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16120 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16136 */
	{.type IHeader, {.hdr { 5, "while", /* CI_while = 16152 */ colon }}}, /* CIENTRY "while" while 5 h 16160 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16168 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16176 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16184 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16192 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16200 */
	{.type Absolute, {.p 0}},		/* dd 0 16208 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16216 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16224 */
	{.type IHeader, {.hdr { 6, "repeat", /* CI_repeat = 16240 */ colon }}}, /* CIENTRY "repeat" repeat 6 h 16248 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16256 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16264 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16272 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16280 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16288 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16296 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16304 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16312 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16320 */
	{.type IHeader, {.hdr { 2, "do", /* CI_do = 16336 */ colon }}}, /* CIENTRY "do" do 2 h 16344 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16352 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time"},		/* dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time 16360 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; puts (do) into the dictionary"},		/* dd C_comma		; puts (do) into the dictionary 16368 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16376 */
	{.type Absolute, {.p 0}},		/* dd 0			; ( -- 0 ) 16384 */
	{.type FromH0, {.p C_here}, .src = "dd C_here		; ( 0 -- 0 here1 )"},		/* dd C_here		; ( 0 -- 0 here1 ) 16392 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16400 */
	{.type IHeader, {.hdr { 4, "loop", /* CI_loop = 16416 */ colon }}}, /* CIENTRY "loop" loop 4 ; ( 0 here1 -- ) h 16424 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16432 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop		; ( 0 here1 -- 0 here1 (loop) )"},		/* dd M_doloop		; ( 0 here1 -- 0 here1 (loop) ) 16440 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 )"},		/* dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 ) 16448 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 )"},		/* dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 ) 16456 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 16464 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16472 */
	{.type FromH0, {.p L234}, .src = "dd L234"},		/* dd L234 16480 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16488 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16496 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16504 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16512 */
	{.type IHeader, {.hdr { 5, "+loop", /* CI_ploop = 16528 */ colon }}}, /* CIENTRY "+loop" ploop 5 h 16536 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16544 */
	{.type FromH0, {.p M_doploop}, .src = "dd M_doploop"},		/* dd M_doploop 16552 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16560 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16568 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 16576 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16584 */
	{.type FromH0, {.p L236}, .src = "dd L236"},		/* dd L236 16592 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16600 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16608 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16616 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16624 */
	{.type Header, {.hdr { 3, "w/o", /* C_wo = 16640 */ colon }}}, /* CENTRY "w/o" wo 3 h 16648 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16656 */
	{.type Absolute, {.p 1}},		/* dd 1 16664 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16672 */
	{.type Absolute, {.p 512}},		/* dd 512 16680 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 16688 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16696 */
	{.type Absolute, {.p 64}},		/* dd 64 16704 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 16712 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16720 */
	{.type Header, {.hdr { 3, "r/o", /* C_ro = 16736 */ colon }}}, /* CENTRY "r/o" ro 3 h 16744 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16752 */
	{.type Absolute, {.p 0}},		/* dd 0 16760 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16768 */
	{.type Header, {.hdr { 3, "r/w", /* C_rw = 16784 */ colon }}}, /* CENTRY "r/w" rw 3 h 16792 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16800 */
	{.type Absolute, {.p 2}},		/* dd 2 16808 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16816 */
	{.type Header, {.hdr { 9, "open-file", /* C_open_file = 16840 */ colon }}}, /* CENTRY "open-file" open_file 9 ; ( a n mode -- fd ioresult ) h 16848 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n mode -- a n ) (R -- mode)"},		/* dd M_rpush	; ( a n mode -- a n ) (R -- mode) 16856 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( a n -- a n padaddr)"},		/* dd C_pad	; ( a n -- a n padaddr) 16864 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16872 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( a n padaddr --  a n padaddr 1024 ) 16880 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( a n padaddr+1024 --  a n padaddr+1024 )"},		/* dd M_plus	; ( a n padaddr+1024 --  a n padaddr+1024 ) 16888 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n padaddr+1024 --  a padaddr+1024 n )"},		/* dd M_xswap	; ( a n padaddr+1024 --  a padaddr+1024 n ) 16896 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a padaddr+1024 n --  a padaddr+1024 n n )"},		/* dd M_dup	; ( a padaddr+1024 n --  a padaddr+1024 n n ) 16904 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a padaddr+1024 n n --  a padaddr+1024 n ) (R mode -- mode n )"},		/* dd M_rpush	; ( a padaddr+1024 n n --  a padaddr+1024 n ) (R mode -- mode n ) 16912 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; moves the filename from a to paddaddr+1024"},		/* dd M_cmove	; moves the filename from a to paddaddr+1024 16920 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16928 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- 0 ) 16936 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( 0 -- 0 n ) (R mode n -- mode)"},		/* dd M_rpop	; ( 0 -- 0 n ) (R mode n -- mode) 16944 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( 0 n -- 0 n padaddr)"},		/* dd C_pad	; ( 0 n -- 0 n padaddr) 16952 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 n padaddr -- 0 padaddr+n )"},		/* dd M_plus	; ( 0 n padaddr -- 0 padaddr+n ) 16960 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16968 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( 0 padaddr+n --  0 padaddr+n 1024 ) 16976 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n 1024 --  0 padaddr+n+1024 )"},		/* dd M_plus	; ( 0 padaddr+n 1024 --  0 padaddr+n+1024 ) 16984 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; ( 0 padaddr+n 1024 --   ) makes the filename to a null terminated string"},		/* dd M_cstore	; ( 0 padaddr+n 1024 --   ) makes the filename to a null terminated string 16992 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 17000 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17008 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( -- padaddr 1024 ) 17016 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( padaddr 1024 -- padaddr+1024 )"},		/* dd M_plus	; ( padaddr 1024 -- padaddr+1024 ) 17024 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 -- padaddr+1024 mode) (R mode -- )"},		/* dd M_rpop	; ( padaddr+1024 -- padaddr+1024 mode) (R mode -- ) 17032 */
	{.type FromH0, {.p M_sysopen}, .src = "dd M_sysopen"},		/* dd M_sysopen 17040 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17048 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17056 */
	{.type Absolute, {.p -1}},		/* dd -1 17064 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 17072 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17080 */
	{.type Header, {.hdr { 10, "close-file", /* C_close_file = 17104 */ colon }}}, /* CENTRY "close-file" close_file 10 ; ( fd -- ioresult ) h 17112 */
	{.type FromH0, {.p M_sysclose}, .src = "dd M_sysclose"},		/* dd M_sysclose 17120 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 17128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17136 */
	{.type Header, {.hdr { 9, "read-file", /* C_read_file = 17160 */ colon }}}, /* CENTRY "read-file" read_file 9 ; ( a n fd -- n2 ioresult ) h 17168 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( n fd a )"},		/* dd C_rot	; ( n fd a ) 17176 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( fd a n )"},		/* dd C_rot	; ( fd a n ) 17184 */
	{.type FromH0, {.p M_sysread}, .src = "dd M_sysread"},		/* dd M_sysread 17192 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17200 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17208 */
	{.type Absolute, {.p -1}},		/* dd -1 17216 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17224 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17232 */
	{.type Header, {.hdr { 10, "write-file", /* C_write_file = 17256 */ colon }}}, /* CENTRY "write-file" write_file 10 ; ( a n fd -- ioresult ) h 17264 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( n fd a )"},		/* dd C_rot	; ( n fd a ) 17272 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( fd a n )"},		/* dd C_rot	; ( fd a n ) 17280 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 17288 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17296 */
	{.type Absolute, {.p -1}},		/* dd -1 17304 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17312 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17320 */
	{.type Header, {.hdr { 15, "reposition-file", /* C_reposition_file = 17344 */ colon }}}, /* CENTRY "reposition-file" reposition_file 15 ; ( type n fd -- ioresult ) h 17352 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap		; ( type fd n )"},		/* dd M_xswap		; ( type fd n ) 17360 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot		; ( fd n type )"},		/* dd C_rot		; ( fd n type ) 17368 */
	{.type FromH0, {.p M_sysseek}, .src = "dd M_sysseek"},		/* dd M_sysseek 17376 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17384 */
	{.type Absolute, {.p -1}},		/* dd -1 17392 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17400 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17408 */
	{.type Header, {.hdr { 7, "?fcheck", /* C_qfcheck = 17424 */ colon }}}, /* CENTRY "?fcheck" qfcheck 7 h 17432 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 17440 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 17448 */
	{.type FromH0, {.p L246}, .src = "dd L246"},		/* dd L246 17456 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 17464 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17472 */
	{.type FromH0, {.p L247}, .src = "dd L247"},		/* dd L247 17480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17488 */
	{.type Absolute, {.p 9}},		/* dd 9 17496 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 17504 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 17512 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 17520 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17528 */
	{.type Header, {.hdr { 11, "create-file", /* C_create_file = 17552 */ colon }}}, /* CENTRY "create-file" create_file 11 ; ( a n mode perm -- fd ioresult ) not part of the original ff. could move this to a forth file. h 17560 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n mode ) (R perm)"},		/* dd M_rpush	; ( a n mode ) (R perm) 17568 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n ) (R perm mode)"},		/* dd M_rpush	; ( a n ) (R perm mode) 17576 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( a n padaddr)"},		/* dd C_pad	; ( a n padaddr) 17584 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17592 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( a n padaddr 1024 ) 17600 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( a n padaddr+1024 )"},		/* dd M_plus	; ( a n padaddr+1024 ) 17608 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a padaddr+1024 n )"},		/* dd M_xswap	; ( a padaddr+1024 n ) 17616 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a padaddr+1024 n n )"},		/* dd M_dup	; ( a padaddr+1024 n n ) 17624 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n )"},		/* dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n ) 17632 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; moves the filename from a to paddaddr+1024"},		/* dd M_cmove	; moves the filename from a to paddaddr+1024 17640 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17648 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( 0 ) 17656 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( 0 n ) (R perm mode)"},		/* dd M_rpop	; ( 0 n ) (R perm mode) 17664 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( 0 n padaddr)"},		/* dd C_pad	; ( 0 n padaddr) 17672 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n )"},		/* dd M_plus	; ( 0 padaddr+n ) 17680 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17688 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( 0 padaddr+n 1024 ) 17696 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n+1024 )"},		/* dd M_plus	; ( 0 padaddr+n+1024 ) 17704 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; ( ) makes the filename to a null terminated string"},		/* dd M_cstore	; ( ) makes the filename to a null terminated string 17712 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 17720 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17728 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( padaddr 1024 ) 17736 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( padaddr+1024 )"},		/* dd M_plus	; ( padaddr+1024 ) 17744 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 mode) (R perm )"},		/* dd M_rpop	; ( padaddr+1024 mode) (R perm ) 17752 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 mode perm ) (R )"},		/* dd M_rpop	; ( padaddr+1024 mode perm ) (R ) 17760 */
	{.type FromH0, {.p M_syscreate}, .src = "dd M_syscreate"},		/* dd M_syscreate 17768 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17776 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17784 */
	{.type Absolute, {.p -1}},		/* dd -1 17792 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 17800 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17808 */
	{.type Header, {.hdr { 3, "bye", /* C_bye = 17824 */ colon }}}, /* CENTRY "bye" bye 3 h 17832 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17840 */
	{.type Absolute, {.p 0}},		/* dd 0 17848 */
	{.type FromH0, {.p M_terminate}, .src = "dd M_terminate"},		/* dd M_terminate 17856 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17864 */
	{.type Header, {.hdr { 7, "include", /* C_include = 17880 */ colon }}}, /* CENTRY "include" include 7 h 17888 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 17896 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 17904 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 17912 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 17920 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 17928 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 17936 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 17944 */
	{.type FromH0, {.p C_save_input}, .src = "dd C_save_input"},		/* dd C_save_input 17952 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 17960 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 17968 */
	{.type FromH0, {.p C_ro}, .src = "dd C_ro"},		/* dd C_ro 17976 */
	{.type FromH0, {.p C_open_file}, .src = "dd C_open_file"},		/* dd C_open_file 17984 */
	{.type FromH0, {.p C_qfcheck}, .src = "dd C_qfcheck"},		/* dd C_qfcheck 17992 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18000 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18008 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18016 */
	{.type Header, {.hdr { 5, "crash", /* C_crash = 18032 */ colon }}}, /* CENTRY "crash" crash 5 h 18040 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18048 */
	{.type FromH0, {.p L251}, .src = "dd L251"},		/* dd L251 18056 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18064 */
	{.type Absolute, {.p 30}},		/* dd 30 18072 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 18080 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 18088 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 18096 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18104 */
	{.type Header, {.hdr { 4, "quit", /* C_quit = 18120 */ colon }}}, /* CENTRY "quit" quit 4 ; interpreter loop h 18128 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 18136 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 18144 */
	{.type FromH0, {.p C_query}, .src = "dd C_query"},		/* dd C_query 18152 */
/* ; dd MV_toLimit	; show the line read, for debugging *//* ; dd M_fetch *//* ; dd M_Tib *//* ; dd MC_STDOUT *//* ; dd M_fswrite *//* ; dd M_drop		; drop the return value of write *//* ; dd C_cr *//* ; dd C_space */	{.type FromH0, {.p C_interpret}, .src = "dd C_interpret"},		/* dd C_interpret 18160 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 18168 */
	{.type FromH0, {.p L253}, .src = "dd L253"},		/* dd L253 18176 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed?"},		/* dd M_exitcolon	; why is this needed? 18184 */
	{.type Header, {.hdr { 7, "(abort)", /* C_parenabort = 18200 */ colon }}}, /* CENTRY "(abort)" parenabort 7 ; TODO correct below stack notations h 18208 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State	; ( mv_State -- )"},		/* dd MV_State	; ( mv_State -- ) 18216 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; off sets variable state = 0"},		/* dd C_off		; off sets variable state = 0 18224 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top of stack"},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 18232 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; variable sourcebuf"},		/* dd MV_Sourcebuf	; variable sourcebuf 18240 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable sourcebuf = address of tibuffer"},		/* dd M_store	; variable sourcebuf = address of tibuffer 18248 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk	; variable blk"},		/* dd MV_Blk	; variable blk 18256 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off variable blk = 0"},		/* dd C_off	; off variable blk = 0 18264 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 18272 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18280 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18288 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 18296 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 18304 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18312 */
	{.type FromH0, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 18320 */
	{.type FromH0, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 18328 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18336 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit resets stacks and is the interpreter loop"},		/* dd C_quit	; quit resets stacks and is the interpreter loop 18344 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed? quit does not return unless it breaks"},		/* dd M_exitcolon	; why is this needed? quit does not return unless it breaks 18352 */
	{.type Header, {.hdr { 7, "oldboot", /* C_oldboot = 18368 */ colon }}}, /* CENTRY "oldboot" oldboot 7 ; TODO correct below stack notations and this is obsolete. leaving it here for reference until it all works well h 18376 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset"},		/* dd M_reset 18384 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end"},		/* dd M_clear	; SP = sstack_end 18392 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr	; (D -- FFEND)"},		/* dd M_stackptr	; (D -- FFEND) 18400 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 18408 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; s0 = FFEND"},		/* dd M_store	; s0 = FFEND 18416 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp	; heaptop = heapend"},		/* dd M_Dp	; heaptop = heapend 18424 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( heapend -- )"},		/* dd M_fetch	; ( heapend -- ) 18432 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18440 */
	{.type Absolute, {.p 1}},		/* dd 1		; ( heapend 1 -- ) 18448 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells	; cells ( heapend 8 -- )"},		/* dd C_cells	; cells ( heapend 8 -- ) 18456 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( heapend-8 -- )"},		/* dd M_minus	; ( heapend-8 -- ) 18464 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( contents_from_heapend-8 -- )"},		/* dd M_fetch	; ( contents_from_heapend-8 -- ) 18472 */
	{.type FromH0, {.p M_Args}, .src = "dd M_Args	; variable args"},		/* dd M_Args	; variable args 18480 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; args = contents_from_heapend-8"},		/* dd M_store	; args = contents_from_heapend-8 18488 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18496 */
	{.type FromH0, {.p C_parenabort}, .src = "dd C_parenabort ; ( (abort) -- )"},		/* dd C_parenabort ; ( (abort) -- ) 18504 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec	; variable abortvec"},		/* dd MV_Abortvec	; variable abortvec 18512 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable abortvec = (abort) code address"},		/* dd M_store	; variable abortvec = (abort) code address 18520 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb	; constant puts address of wordbuffer on the top of stack"},		/* dd M_Wordb	; constant puts address of wordbuffer on the top of stack 18528 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf	; variable wordbuf"},		/* dd MV_Wordbuf	; variable wordbuf 18536 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable wordbuf = address of wordbuffer"},		/* dd M_store	; variable wordbuf = address of wordbuffer 18544 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top of stack"},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 18552 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; variable sourcebuf"},		/* dd MV_Sourcebuf	; variable sourcebuf 18560 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable sourcebuf = address of tibuffer"},		/* dd M_store	; variable sourcebuf = address of tibuffer 18568 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18576 */
	{.type Absolute, {.p 0}},		/* dd 0 18584 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18592 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdin = 0"},		/* dd M_store	; stdin = 0 18600 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18608 */
	{.type Absolute, {.p 1}},		/* dd 1 18616 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 18624 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdout = 1"},		/* dd M_store	; stdout = 1 18632 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 18640 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off stores 0 at state"},		/* dd C_off	; off stores 0 at state 18648 */
	{.type FromH0, {.p C_decimal}, .src = "dd C_decimal	; decimal setting base = 0"},		/* dd C_decimal	; decimal setting base = 0 18656 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit"},		/* dd C_quit	; quit 18664 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18672 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal	; test code"},		/* dd M_literal	; test code 18680 */
	{.type Absolute, {.p 66}},		/* dd 66 18688 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 18696 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18704 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 18712 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 18720 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18728 */
	{.type Absolute, {.p 1}},		/* dd 1 18736 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 18744 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 18752 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 18760 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 18768 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18776 */
	{.type Absolute, {.p 1}},		/* dd 1 18784 */
	{.type FromH0, {.p M_sysread}, .src = "dd M_sysread"},		/* dd M_sysread 18792 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of read"},		/* dd M_drop		; drop the return value of read 18800 */
	{.type Header, {.hdr { 4, "boot", /* C_boot = 18816 */ colon }}}, /* CENTRY "boot" boot 4 h 18824 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 18832 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 18840 */
/* 			; s0 puts FFEND on the stack *//* 			; no args */	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18848 */
	{.type FromH0, {.p C_parenabort}, .src = "dd C_parenabort ; ( (abort) -- )"},		/* dd C_parenabort ; ( (abort) -- ) 18856 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec	; variable that puts (abort) code address on the stack"},		/* dd MV_Abortvec	; variable that puts (abort) code address on the stack 18864 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable abortvec = (abort) code address"},		/* dd M_store	; variable abortvec = (abort) code address 18872 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb	; variable puts address of wordbuffer on the top of stack"},		/* dd M_Wordb	; variable puts address of wordbuffer on the top of stack 18880 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf ; variable wordbuf"},		/* dd MV_Wordbuf ; variable wordbuf 18888 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable wordbuf = address of wordbuffer"},		/* dd M_store	; variable wordbuf = address of wordbuffer 18896 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top of stack"},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 18904 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; variable sourcebuf"},		/* dd MV_Sourcebuf	; variable sourcebuf 18912 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable sourcebuf = address of tibuffer"},		/* dd M_store	; variable sourcebuf = address of tibuffer 18920 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 18928 */
	{.type FromH0, {.p MV_H0}, .src = "dd MV_H0	; H0 = here at startup"},		/* dd MV_H0	; H0 = here at startup 18936 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18944 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 18952 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18960 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdin = 0"},		/* dd M_store	; stdin = 0 18968 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 18976 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 18984 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18992 */
	{.type FromH0, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 19000 */
	{.type FromH0, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 19008 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 19016 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 19024 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off stores 0 at state"},		/* dd C_off	; off stores 0 at state 19032 */
	{.type FromH0, {.p C_decimal}, .src = "dd C_decimal	; decimal sets base = 10"},		/* dd C_decimal	; decimal sets base = 10 19040 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit"},		/* dd C_quit	; quit 19048 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19056 */
	{.type Chars, {.str "unable to restore input"}},		/* 19080 */
	{.type Chars, {.str " Q?"}},		/* 19084 */
	{.type Chars, {.str " stack underflow"}},		/* 19101 */
	{.type Chars, {.str " I?"}},		/* 19105 */
	{.type Chars, {.str " C?"}},		/* 19109 */
	{.type Chars, {.str "I/O error"}},		/* 19119 */
	{.type Chars, {.str "uninitialized execution vector"}},		/* 19150 */
	{.type Chars, {.str " ok"}},		/* 19154 */
};

