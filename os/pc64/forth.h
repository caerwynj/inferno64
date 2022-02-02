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
	MV_Acceptvec = 1728,
	MV_Searchlen = 1768,
	MV_Base = 1800,
	MV_toNum = 1832,
	MV_State = 1864,
	MV_Abortvec = 1904,
	MV_Infd = 1936,
	MV_Outfd = 1968,
	MV_Errfd = 2000,
	MV_Eof = 2032,
	MV_Ninputs = 2064,
	MV_H0 = 2096,
	M_Dp = 2128,
	M_Dtop = 2152,
	M_Vp = 2176,
	M_S0 = 2200,
	M_stackptr = 2224,
	M_Wordb = 2248,
	M_Tib = 2272,
	M_Fthargs = 2296,
	C_false = 2320,
	C_true = 2368,
	C_bl = 2416,
	C_on = 2464,
	C_off = 2528,
	C_tobody = 2592,
	C_aligned = 2648,
	C_cells = 2728,
	C_cellplus = 2784,
	C_depth = 2848,
	C_nip = 2952,
	C_rot = 3000,
	C_2drop = 3064,
	C_2dup = 3112,
	C_2nip = 3160,
	C_2swap = 3208,
	C_qdup = 3272,
	L20 = 3344,
	C_pick = 3368,
	L22 = 3472,
	L23 = 3480,
	C_tuck = 3504,
	C_divides = 3568,
	C_plusstore = 3616,
	C_invert = 3696,
	C_mod = 3752,
	C_1plus = 3800,
	C_1minus = 3856,
	C_negate = 3912,
	C_2multiplies = 3976,
	C_2divides = 4032,
	C_0eq = 4088,
	C_0lt = 4144,
	C_0gt = 4200,
	C_neq = 4256,
	C_0neq = 4304,
	C_max = 4360,
	L40 = 4424,
	L41 = 4432,
	C_min = 4456,
	L43 = 4520,
	L44 = 4528,
	C_signum = 4552,
	L46 = 4632,
	L48 = 4688,
	L49 = 4704,
	L47 = 4704,
	C_within = 4728,
	C_abs = 4832,
	L52 = 4880,
	C_key = 4904,
	L78 = 5032,
	L79 = 5048,
	C_emit = 5072,
	C_type = 5176,
	C_cr = 5272,
	C_space = 5328,
	C_emits = 5376,
	L85 = 5384,
	L86 = 5448,
	C_spaces = 5480,
	C_count = 5536,
	C_compare = 5680,
	L55 = 5752,
	L56 = 5888,
	C_erase = 5968,
	L58 = 6000,
	C_fill = 6088,
	L60 = 6128,
	C_blank = 6216,
	C_search = 6264,
	L64 = 6368,
	L65 = 6552,
	C_here = 6616,
	C_vhere = 6664,
	C_comma = 6712,
	C_c = 6792,
	C_allot = 6872,
	C_vallot = 6920,
	C_pad = 6968,
	C_align = 7032,
	C_unused = 7096,
	C_fromhash = 7160,
	C_hash = 7240,
	L92 = 7392,
	L93 = 7416,
	C_hashs = 7496,
	L95 = 7504,
	L96 = 7552,
	C_hashfrom = 7576,
	C_hold = 7688,
	C_sign = 7792,
	L100 = 7848,
	C_dot = 7872,
	C_dotr = 7976,
	C_hex = 8136,
	C_decimal = 8200,
	C_digit = 8264,
	L106 = 8376,
	L108 = 8480,
	L110 = 8584,
	L111 = 8608,
	L109 = 8608,
	L107 = 8608,
	L112 = 8680,
	L113 = 8696,
	C_number = 8720,
	L115 = 8856,
	L116 = 8888,
	L117 = 8952,
	L118 = 9056,
	L119 = 9112,
	C_abort = 9200,
	C_source = 9256,
	C_current_input = 9312,
	C_save_input = 9392,
	C_default_input = 9528,
	C_restore_input = 9680,
	L132 = 9904,
	C_qrestore_input = 9952,
	L136 = 10080,
	C_next_input = 10112,
	L139 = 10208,
	L140 = 10232,
	C_parse = 10256,
	L142 = 10296,
	L143 = 10424,
	C_word = 10568,
	L145 = 10584,
	L146 = 10680,
	C_accept = 10720,
	L300 = 10784,
	C_accept_line = 10856,
	L303 = 11064,
	L301 = 11080,
	L302 = 11136,
	C_accept_key = 11184,
	L148 = 11224,
	L150 = 11384,
	L149 = 11448,
	C_query = 11496,
	L152 = 11640,
	L153 = 11672,
	C_refill = 11696,
	L155 = 11752,
	C_findname = 11800,
	L158 = 11840,
	L160 = 11952,
	L162 = 12080,
	L161 = 12088,
	L159 = 12104,
	C_find = 12152,
	L165 = 12344,
	L166 = 12360,
	L164 = 12384,
	L167 = 12392,
	C_single_quote = 12416,
	L169 = 12552,
	C_qstack = 12576,
	L172 = 12680,
	C_interpret = 12752,
	L175 = 12760,
	L177 = 12872,
	L179 = 12984,
	L178 = 12984,
	L176 = 13000,
	C_create = 13032,
	C_variable = 13280,
	C_constant = 13376,
	C_immediate = 13504,
	C_tocfa = 13616,
	C_compile = 13696,
	L189 = 13824,
	L190 = 13840,
	L188 = 13856,
	L192 = 13984,
	L194 = 14016,
	L191 = 14016,
	C_close_bracket = 14040,
	L196 = 14064,
	L197 = 14152,
	L198 = 14176,
	L199 = 14208,
	CI_open_bracket = 14232,
	C_smudge = 14280,
	C_reveal = 14392,
	C_colon = 14512,
	CI_semicolon = 14640,
	CI_recurse = 14720,
	C_char = 14792,
	C_literal = 14856,
	C_sliteral = 14928,
	C_string = 15096,
	CI_char_brackets = 15208,
	CI_quote_brackets = 15280,
	CI_openparen = 15328,
	CI_backslash = 15392,
	L214 = 15472,
	C_qabort_parens = 15536,
	L217 = 15616,
	L218 = 15624,
	CI_abort_double_quote = 15648,
	C_double_quote = 15712,
	C_cdouble_quote = 15840,
	CI_sdouble_quote = 15976,
	CI_dotstr = 16016,
	CI_if = 16080,
	CI_else = 16168,
	CI_then = 16296,
	CI_begin = 16352,
	CI_again = 16392,
	CI_until = 16456,
	CI_while = 16520,
	CI_repeat = 16608,
	CI_do = 16704,
	CI_loop = 16784,
	L234 = 16872,
	CI_ploop = 16896,
	L236 = 16984,
	C_wo = 17008,
	C_ro = 17104,
	C_rw = 17152,
	C_open_file = 17208,
	C_close_file = 17472,
	C_read_file = 17528,
	C_write_file = 17624,
	C_reposition_file = 17712,
	C_qfcheck = 17792,
	L246 = 17888,
	C_create_file = 17920,
	C_bye = 18192,
	C_include = 18248,
	C_crash = 18400,
	C_quit = 18488,
	L253 = 18512,
	C_parenabort = 18568,
	C_oldboot = 18704,
	C_do_args = 19152,
	C_boot = 19304,
	L260 = 19552,
	L137 = 19568,
	L170 = 19592,
	L173 = 19596,
	L180 = 19613,
	L193 = 19617,
	L247 = 19621,
	L251 = 19631,
	L255 = 19662,
	L304 = 19666,
	L305 = 19703,
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
extern void *Fthargs(void);
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
	{.type Header, {.hdr { 4, "exit", /* M_exitcolon = 400 */ exitcolon }}}, /* MENTRY "exit" exitcolon 4 h 408 */
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
	{.type Header, {.hdr { 9, "Acceptvec", /* MV_Acceptvec = 1728 */ variable }}}, /* MVENTRY "Acceptvec" Acceptvec 0 9 h 1736 */
	{.type FromV0, {.p 48 }},	/* 1744 48 */
	{.type Header, {.hdr { 9, "Searchlen", /* MV_Searchlen = 1768 */ variable }}}, /* MVENTRY "Searchlen" Searchlen 0 9 h 1776 */
	{.type FromV0, {.p 56 }},	/* 1784 56 */
	{.type Header, {.hdr { 4, "Base", /* MV_Base = 1800 */ variable }}}, /* MVENTRY "Base" Base 0 4 h 1808 */
	{.type FromV0, {.p 64 }},	/* 1816 64 */
	{.type Header, {.hdr { 4, ">Num", /* MV_toNum = 1832 */ variable }}}, /* MVENTRY ">Num" toNum 0 4 h 1840 */
	{.type FromV0, {.p 72 }},	/* 1848 72 */
	{.type Header, {.hdr { 5, "State", /* MV_State = 1864 */ variable }}}, /* MVENTRY "State" State 0 5 h 1872 */
	{.type FromV0, {.p 80 }},	/* 1880 80 */
	{.type Header, {.hdr { 8, "Abortvec", /* MV_Abortvec = 1904 */ variable }}}, /* MVENTRY "Abortvec" Abortvec 0 8	; not sure if these 3 can be constants instead? h 1912 */
	{.type FromV0, {.p 88 }},	/* 1920 88 */
	{.type Header, {.hdr { 4, "Infd", /* MV_Infd = 1936 */ variable }}}, /* MVENTRY "Infd" Infd 0 4 h 1944 */
	{.type FromV0, {.p 96 }},	/* 1952 96 */
	{.type Header, {.hdr { 5, "Outfd", /* MV_Outfd = 1968 */ variable }}}, /* MVENTRY "Outfd" Outfd 0 5 h 1976 */
	{.type FromV0, {.p 104 }},	/* 1984 104 */
	{.type Header, {.hdr { 5, "Errfd", /* MV_Errfd = 2000 */ variable }}}, /* MVENTRY "Errfd" Errfd 0 5 h 2008 */
	{.type FromV0, {.p 112 }},	/* 2016 112 */
	{.type Header, {.hdr { 3, "Eof", /* MV_Eof = 2032 */ variable }}}, /* MVENTRY "Eof" Eof 0 3 h 2040 */
	{.type FromV0, {.p 120 }},	/* 2048 120 */
	{.type Header, {.hdr { 7, "Ninputs", /* MV_Ninputs = 2064 */ variable }}}, /* MVENTRY "Ninputs" Ninputs 0 7 h 2072 */
	{.type FromV0, {.p 128 }},	/* 2080 128 */
	{.type Header, {.hdr { 2, "H0", /* MV_H0 = 2096 */ variable }}}, /* MVENTRY "H0" H0 0 2		; here at startup h 2104 */
	{.type FromV0, {.p 136 }},	/* 2112 136 */
/* ; cannot use H as it is nil in inferno, address where here (next available dictionary cell location) is stored *//* ; here = Dp @ */	{.type Header, {.hdr { 2, "Dp", /* M_Dp = 2128 */ Dp }}}, /* MENTRY "Dp" Dp 2		; here h 2136 */
	{.type Header, {.hdr { 4, "Dtop", /* M_Dtop = 2152 */ Dtop }}}, /* MENTRY "Dtop" Dtop 4	; last defined header h 2160 */
	{.type Header, {.hdr { 2, "Vp", /* M_Vp = 2176 */ Vp }}}, /* MENTRY "Vp" Vp 2		; here of the variables space h 2184 */
	{.type Header, {.hdr { 2, "S0", /* M_S0 = 2200 */ S0 }}}, /* MENTRY "S0" S0 2 h 2208 */
	{.type Header, {.hdr { 2, "s@", /* M_stackptr = 2224 */ stackptr }}}, /* MENTRY "s@" stackptr 2	; puts PSP on stack. Not a variable hence lower case. h 2232 */
	{.type Header, {.hdr { 5, "Wordb", /* M_Wordb = 2248 */ Wordb }}}, /* MENTRY "Wordb" Wordb 5 h 2256 */
	{.type Header, {.hdr { 3, "Tib", /* M_Tib = 2272 */ Tib }}}, /* MENTRY "Tib" Tib 3 h 2280 */
	{.type Header, {.hdr { 7, "Fthargs", /* M_Fthargs = 2296 */ Fthargs }}}, /* MENTRY "Fthargs" Fthargs 7 h 2304 */
	{.type Header, {.hdr { 5, "false", /* C_false = 2320 */ colon }}}, /* CENTRY "false" false 5 h 2328 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2336 */
	{.type Absolute, {.p 0}},		/* dd 0 2344 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2352 */
	{.type Header, {.hdr { 4, "true", /* C_true = 2368 */ colon }}}, /* CENTRY "true" true 4 h 2376 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2384 */
	{.type Absolute, {.p -1}},		/* dd -1 2392 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2400 */
	{.type Header, {.hdr { 2, "bl", /* C_bl = 2416 */ colon }}}, /* CENTRY "bl" bl 2 h 2424 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2432 */
	{.type Absolute, {.p 32}},		/* dd 32 2440 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2448 */
	{.type Header, {.hdr { 2, "on", /* C_on = 2464 */ colon }}}, /* CENTRY "on" on 2 ; ( a -- ) (G stores -1 at a ) h 2472 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2480 */
	{.type Absolute, {.p -1}},		/* dd -1 2488 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2496 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2504 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2512 */
	{.type Header, {.hdr { 3, "off", /* C_off = 2528 */ colon }}}, /* CENTRY "off" off 3 ; ( a -- ) (G stores 0 at a ) h 2536 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2544 */
	{.type Absolute, {.p 0}},		/* dd 0 2552 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2560 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2568 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2576 */
	{.type Header, {.hdr { 5, ">body", /* C_tobody = 2592 */ colon }}}, /* CENTRY ">body" tobody 5 h 2600 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2608 */
	{.type Absolute, {.p 8}},		/* dd 8 2616 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2624 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2632 */
	{.type Header, {.hdr { 7, "aligned", /* C_aligned = 2648 */ colon }}}, /* CENTRY "aligned" aligned 7 ; align a number to a multiple of 8 h 2656 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2664 */
	{.type Absolute, {.p 7}},		/* dd 7 2672 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2680 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2688 */
	{.type Absolute, {.p -8}},		/* dd -8 2696 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 2704 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2712 */
	{.type Header, {.hdr { 5, "cells", /* C_cells = 2728 */ colon }}}, /* CENTRY "cells" cells 5 h 2736 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2744 */
	{.type Absolute, {.p 3}},		/* dd 3			; (index << 2) -> (index << 3) for amd64 2752 */
	{.type FromH0, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 2760 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2768 */
	{.type Header, {.hdr { 5, "cell+", /* C_cellplus = 2784 */ colon }}}, /* CENTRY "cell+" cellplus 5 h 2792 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2800 */
	{.type Absolute, {.p 1}},		/* dd 1 2808 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 2816 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2824 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2832 */
	{.type Header, {.hdr { 5, "depth", /* C_depth = 2848 */ colon }}}, /* CENTRY "depth" depth 5 h 2856 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 2864 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 2872 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 2880 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2888 */
	{.type Absolute, {.p 3}},		/* dd 3 2896 */
	{.type FromH0, {.p M_rshift}, .src = "dd M_rshift"},		/* dd M_rshift 2904 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2912 */
	{.type Absolute, {.p 1}},		/* dd 1 2920 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 2928 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2936 */
	{.type Header, {.hdr { 3, "nip", /* C_nip = 2952 */ colon }}}, /* CENTRY "nip" nip 3 h 2960 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2968 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 2976 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2984 */
	{.type Header, {.hdr { 3, "rot", /* C_rot = 3000 */ colon }}}, /* CENTRY "rot" rot 3 h 3008 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3016 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3024 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3032 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3040 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3048 */
	{.type Header, {.hdr { 5, "2drop", /* C_2drop = 3064 */ colon }}}, /* CENTRY "2drop" 2drop 5 h 3072 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3080 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3088 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3096 */
	{.type Header, {.hdr { 4, "2dup", /* C_2dup = 3112 */ colon }}}, /* CENTRY "2dup" 2dup 4 h 3120 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3128 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3136 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3144 */
	{.type Header, {.hdr { 4, "2nip", /* C_2nip = 3160 */ colon }}}, /* CENTRY "2nip" 2nip 4 h 3168 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3176 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3184 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3192 */
	{.type Header, {.hdr { 5, "2swap", /* C_2swap = 3208 */ colon }}}, /* CENTRY "2swap" 2swap 5 h 3216 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3224 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3232 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3240 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3248 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3256 */
	{.type Header, {.hdr { 4, "?dup", /* C_qdup = 3272 */ colon }}}, /* CENTRY "?dup" qdup 4 ; if (n != 0) ( n -- n n) else ( n -- n ) h 3280 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n -- n n )"},		/* dd M_dup	; ( n -- n n ) 3288 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n n -- n n n )"},		/* dd M_dup	; ( n n -- n n n ) 3296 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3304 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( n n n -- n n n 0 ) 3312 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n n n 0 -- n n f )"},		/* dd M_equal	; ( n n n 0 -- n n f ) 3320 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; ( n n f -- n n )"},		/* dd M_cjump	; ( n n f -- n n ) 3328 */
	{.type FromH0, {.p L20}, .src = "dd L20		; when n != 0, go to L20"},		/* dd L20		; when n != 0, go to L20 3336 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; when n == 0 ( n n -- n)"},		/* dd M_drop	; when n == 0 ( n n -- n) 3344 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3352 */
	{.type Header, {.hdr { 4, "pick", /* C_pick = 3368 */ colon }}}, /* CENTRY "pick" pick 4 h 3376 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 3384 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 3392 */
	{.type FromH0, {.p L22}, .src = "dd L22"},		/* dd L22 3400 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3408 */
	{.type Absolute, {.p 1}},		/* dd 1 3416 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3424 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 3432 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 3440 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3448 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3456 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 3464 */
	{.type FromH0, {.p L23}, .src = "dd L23"},		/* dd L23 3472 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3480 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3488 */
	{.type Header, {.hdr { 4, "tuck", /* C_tuck = 3504 */ colon }}}, /* CENTRY "tuck" tuck 4 h 3512 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3520 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3528 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3536 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3544 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3552 */
	{.type Header, {.hdr { 1, "/", /* C_divides = 3568 */ colon }}}, /* CENTRY "/" divides 1 h 3576 */
	{.type FromH0, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 3584 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3592 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3600 */
	{.type Header, {.hdr { 2, "+!", /* C_plusstore = 3616 */ colon }}}, /* CENTRY "+!" plusstore 2 h 3624 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3632 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3640 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3648 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3656 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3664 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 3672 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3680 */
	{.type Header, {.hdr { 6, "invert", /* C_invert = 3696 */ colon }}}, /* CENTRY "invert" invert 6 h 3704 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3712 */
	{.type Absolute, {.p -1}},		/* dd -1 3720 */
	{.type FromH0, {.p M_binxor}, .src = "dd M_binxor"},		/* dd M_binxor 3728 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3736 */
	{.type Header, {.hdr { 3, "mod", /* C_mod = 3752 */ colon }}}, /* CENTRY "mod" mod 3 h 3760 */
	{.type FromH0, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 3768 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3776 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3784 */
	{.type Header, {.hdr { 2, "1+", /* C_1plus = 3800 */ colon }}}, /* CENTRY "1+" 1plus 2 h 3808 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3816 */
	{.type Absolute, {.p 1}},		/* dd 1 3824 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3832 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3840 */
	{.type Header, {.hdr { 2, "1-", /* C_1minus = 3856 */ colon }}}, /* CENTRY "1-" 1minus 2 h 3864 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3872 */
	{.type Absolute, {.p 1}},		/* dd 1 3880 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3888 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3896 */
	{.type Header, {.hdr { 6, "negate", /* C_negate = 3912 */ colon }}}, /* CENTRY "negate" negate 6 h 3920 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3928 */
	{.type Absolute, {.p 0}},		/* dd 0 3936 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3944 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3952 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3960 */
	{.type Header, {.hdr { 2, "2*", /* C_2multiplies = 3976 */ colon }}}, /* CENTRY "2*" 2multiplies 2 h 3984 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3992 */
	{.type Absolute, {.p 1}},		/* dd 1 4000 */
	{.type FromH0, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 4008 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4016 */
	{.type Header, {.hdr { 2, "2/", /* C_2divides = 4032 */ colon }}}, /* CENTRY "2/" 2divides 2 h 4040 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4048 */
	{.type Absolute, {.p 1}},		/* dd 1 4056 */
	{.type FromH0, {.p M_rshifta}, .src = "dd M_rshifta"},		/* dd M_rshifta 4064 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4072 */
	{.type Header, {.hdr { 2, "0=", /* C_0eq = 4088 */ colon }}}, /* CENTRY "0=" 0eq 2 h 4096 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4104 */
	{.type Absolute, {.p 0}},		/* dd 0 4112 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4120 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4128 */
	{.type Header, {.hdr { 2, "0<", /* C_0lt = 4144 */ colon }}}, /* CENTRY "0<" 0lt 2 h 4152 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4160 */
	{.type Absolute, {.p 0}},		/* dd 0 4168 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4176 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4184 */
	{.type Header, {.hdr { 2, "0>", /* C_0gt = 4200 */ colon }}}, /* CENTRY "0>" 0gt 2 h 4208 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4216 */
	{.type Absolute, {.p 0}},		/* dd 0 4224 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4240 */
	{.type Header, {.hdr { 2, "<>", /* C_neq = 4256 */ colon }}}, /* CENTRY "<>" neq 2 h 4264 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4272 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 4280 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4288 */
	{.type Header, {.hdr { 3, "0<>", /* C_0neq = 4304 */ colon }}}, /* CENTRY "0<>" 0neq 3 h 4312 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4320 */
	{.type Absolute, {.p 0}},		/* dd 0 4328 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 4336 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4344 */
	{.type Header, {.hdr { 3, "max", /* C_max = 4360 */ colon }}}, /* CENTRY "max" max 3 h 4368 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4376 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4384 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4392 */
	{.type FromH0, {.p L40}, .src = "dd L40"},		/* dd L40 4400 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4408 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4416 */
	{.type FromH0, {.p L41}, .src = "dd L41"},		/* dd L41 4424 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4432 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4440 */
	{.type Header, {.hdr { 3, "min", /* C_min = 4456 */ colon }}}, /* CENTRY "min" min 3 h 4464 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4472 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4480 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4488 */
	{.type FromH0, {.p L43}, .src = "dd L43"},		/* dd L43 4496 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4504 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4512 */
	{.type FromH0, {.p L44}, .src = "dd L44"},		/* dd L44 4520 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4528 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4536 */
	{.type Header, {.hdr { 6, "signum", /* C_signum = 4552 */ colon }}}, /* CENTRY "signum" signum 6 h 4560 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4568 */
	{.type FromH0, {.p C_0gt}, .src = "dd C_0gt"},		/* dd C_0gt 4576 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4584 */
	{.type FromH0, {.p L46}, .src = "dd L46"},		/* dd L46 4592 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4600 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4608 */
	{.type Absolute, {.p 1}},		/* dd 1 4616 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4624 */
	{.type FromH0, {.p L47}, .src = "dd L47"},		/* dd L47 4632 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 4640 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4648 */
	{.type FromH0, {.p L48}, .src = "dd L48"},		/* dd L48 4656 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4664 */
	{.type Absolute, {.p -1}},		/* dd -1 4672 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4680 */
	{.type FromH0, {.p L49}, .src = "dd L49"},		/* dd L49 4688 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4696 */
	{.type Absolute, {.p 0}},		/* dd 0 4704 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4712 */
	{.type Header, {.hdr { 6, "within", /* C_within = 4728 */ colon }}}, /* CENTRY "within" within 6 h 4736 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 4744 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 4752 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4760 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4768 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 4776 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 4784 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4792 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4800 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 4808 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4816 */
	{.type Header, {.hdr { 3, "abs", /* C_abs = 4832 */ colon }}}, /* CENTRY "abs" abs 3 h 4840 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4848 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 4856 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4864 */
	{.type FromH0, {.p L52}, .src = "dd L52"},		/* dd L52 4872 */
	{.type FromH0, {.p C_negate}, .src = "dd C_negate"},		/* dd C_negate 4880 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4888 */
	{.type Header, {.hdr { 3, "key", /* C_key = 4904 */ colon }}}, /* CENTRY "key" key 3 ; ( -- c ) (G read a single character from the input onto the stack ) h 4912 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 4920 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( infd )"},		/* dd M_fetch		; ( infd ) 4928 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf to store the character read"},		/* dd MV_Iobuf		; variable iobuf to store the character read 4936 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4944 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( infd Iobuf 1 ) 4952 */
	{.type FromH0, {.p M_sysread}, .src = "dd M_sysread	; ( infd Iobuf 1 -- n )"},		/* dd M_sysread	; ( infd Iobuf 1 -- n ) 4960 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4968 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump		; if 0 characters read"},		/* dd M_cjump		; if 0 characters read 4976 */
	{.type FromH0, {.p L78}, .src = "dd L78			; if qread n != 0 jump to L78. If n == 0 jump over"},		/* dd L78			; if qread n != 0 jump to L78. If n == 0 jump over 4984 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 4992 */
	{.type FromH0, {.p C_on}, .src = "dd C_on		; EOF"},		/* dd C_on		; EOF 5000 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5008 */
	{.type Absolute, {.p -1}},		/* dd -1			; return -1 when EOF 5016 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5024 */
	{.type FromH0, {.p L79}, .src = "dd L79"},		/* dd L79 5032 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; get the character from Iobuf to stack"},		/* dd MV_Iobuf		; get the character from Iobuf to stack 5040 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( -- c ) return the character read if not EOF"},		/* dd M_cfetch	; ( -- c ) return the character read if not EOF 5048 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5056 */
	{.type Header, {.hdr { 4, "emit", /* C_emit = 5072 */ colon }}}, /* CENTRY "emit" emit 4 ; ( character -- ) h 5080 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5088 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; variable iobuf has character"},		/* dd M_cstore	; variable iobuf has character 5096 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 5104 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; outfd"},		/* dd M_fetch		; outfd 5112 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5120 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5128 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( outfd iobuf 1 ) 5136 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite	; ( 1 iobuf outfd --  )"},		/* dd M_syswrite	; ( 1 iobuf outfd --  ) 5144 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5152 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5160 */
	{.type Header, {.hdr { 4, "type", /* C_type = 5176 */ colon }}}, /* CENTRY "type" type 4 ; ( addr n -- ) h 5184 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; ( addr ) (R n )"},		/* dd M_rpush		; ( addr ) (R n ) 5192 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; ( ) (R n addr )"},		/* dd M_rpush		; ( ) (R n addr ) 5200 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 5208 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( outfd )"},		/* dd M_fetch		; ( outfd ) 5216 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( outfd addr ) (R n )"},		/* dd M_rpop		; ( outfd addr ) (R n ) 5224 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( outfd addr n ) (R )"},		/* dd M_rpop		; ( outfd addr n ) (R ) 5232 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite	; ( 1 addr n --  )"},		/* dd M_syswrite	; ( 1 addr n --  ) 5240 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5248 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5256 */
	{.type Header, {.hdr { 2, "cr", /* C_cr = 5272 */ colon }}}, /* CENTRY "cr" cr 2 h 5280 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5288 */
	{.type Absolute, {.p 10}},		/* dd 10			; ascii value of carriage return 5296 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit			; emit"},		/* dd C_emit			; emit 5304 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5312 */
	{.type Header, {.hdr { 5, "space", /* C_space = 5328 */ colon }}}, /* CENTRY "space" space 5 h 5336 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5344 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5352 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5360 */
	{.type Header, {.hdr { 5, "emits", /* C_emits = 5376 */ colon }}}, /* CENTRY "emits" emits 5 h 5384 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5392 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5400 */
	{.type FromH0, {.p L86}, .src = "dd L86"},		/* dd L86 5408 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5416 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5424 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5432 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5440 */
	{.type FromH0, {.p L85}, .src = "dd L85"},		/* dd L85 5448 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 5456 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5464 */
	{.type Header, {.hdr { 6, "spaces", /* C_spaces = 5480 */ colon }}}, /* CENTRY "spaces" spaces 6 h 5488 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5496 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 5504 */
	{.type FromH0, {.p C_emits}, .src = "dd C_emits"},		/* dd C_emits 5512 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5520 */
	{.type Header, {.hdr { 5, "count", /* C_count = 5536 */ colon }}}, /* CENTRY "count" count 5 ; ( a -- a+1 n ) a = address of counted string ( a - a+1 a[0]) h 5544 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 5552 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 5560 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5568 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5576 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5584 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup ; debug show the word name to search"},		/* dd C_2dup ; debug show the word name to search 5592 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5600 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 5608 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush ; debug show the dictionary entry"},		/* dd M_rpush ; debug show the dictionary entry 5616 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 5624 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 5632 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5640 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5648 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5656 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 5664 */
	{.type Header, {.hdr { 7, "compare", /* C_compare = 5680 */ colon }}}, /* CENTRY "compare" compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search h 5688 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 )"},		/* dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 5696 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 )"},		/* dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 ) 5704 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- ) 5712 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- ) 5720 */
	{.type FromH0, {.p C_min}, .src = "dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- )"},		/* dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- ) 5728 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5736 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- ) 5744 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- )"},		/* dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- ) 5752 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5760 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 5768 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 5776 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5784 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5792 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 5800 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 5808 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5816 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 5824 */
	{.type FromH0, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 5832 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5840 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5848 */
	{.type FromH0, {.p L56}, .src = "dd L56		; matches"},		/* dd L56		; matches 5856 */
	{.type FromH0, {.p C_2nip}, .src = "dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- )"},		/* dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- ) 5864 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2)"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2) 5872 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 -- )"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 -- ) 5880 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5888 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 5896 */
	{.type FromH0, {.p L55}, .src = "dd L55"},		/* dd L55 5904 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- )"},		/* dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- ) 5912 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5920 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( n2 n1 -- ) (R -- )"},		/* dd M_rpop	; ( n2 n1 -- ) (R -- ) 5928 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( -- n1-n2 )"},		/* dd M_minus	; ( -- n1-n2 ) 5936 */
	{.type FromH0, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 5944 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5952 */
	{.type Header, {.hdr { 5, "erase", /* C_erase = 5968 */ colon }}}, /* CENTRY "erase" erase 5 h 5976 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5984 */
	{.type Absolute, {.p 0}},		/* dd 0 5992 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6000 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6008 */
	{.type Absolute, {.p 0}},		/* dd 0 6016 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6024 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6032 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 6040 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6048 */
	{.type FromH0, {.p L58}, .src = "dd L58"},		/* dd L58 6056 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6064 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6072 */
	{.type Header, {.hdr { 4, "fill", /* C_fill = 6088 */ colon }}}, /* CENTRY "fill" fill 4 h 6096 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6104 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6112 */
	{.type Absolute, {.p 0}},		/* dd 0 6120 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6128 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 6136 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6144 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6152 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6160 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6168 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6176 */
	{.type FromH0, {.p L60}, .src = "dd L60"},		/* dd L60 6184 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 6192 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6200 */
	{.type Header, {.hdr { 5, "blank", /* C_blank = 6216 */ colon }}}, /* CENTRY "blank" blank 5 h 6224 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 6232 */
	{.type FromH0, {.p C_fill}, .src = "dd C_fill"},		/* dd C_fill 6240 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6248 */
	{.type Header, {.hdr { 6, "search", /* C_search = 6264 */ colon }}}, /* CENTRY "search" search 6 h 6272 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6280 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6288 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6296 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 6304 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 6312 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6320 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6328 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6336 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 6344 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6352 */
	{.type Absolute, {.p 0}},		/* dd 0 6360 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6368 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6376 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6384 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6392 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6400 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6408 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6416 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6424 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6432 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6440 */
	{.type FromH0, {.p C_compare}, .src = "dd C_compare"},		/* dd C_compare 6448 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 6456 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 6464 */
	{.type FromH0, {.p L65}, .src = "dd L65"},		/* dd L65 6472 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6480 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6488 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6496 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6504 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 6512 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6520 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6528 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6536 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 6544 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6552 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6560 */
	{.type FromH0, {.p L64}, .src = "dd L64"},		/* dd L64 6568 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6576 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6584 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 6592 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6600 */
	{.type Header, {.hdr { 4, "here", /* C_here = 6616 */ colon }}}, /* CENTRY "here" here 4 h 6624 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6632 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6640 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6648 */
	{.type Header, {.hdr { 4, "vhere", /* C_vhere = 6664 */ colon }}}, /* CENTRY "vhere" vhere 4 h 6672 */
	{.type FromH0, {.p M_Vp}, .src = "dd M_Vp"},		/* dd M_Vp 6680 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6688 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6696 */
	{.type Header, {.hdr { 1, ",", /* C_comma = 6712 */ colon }}}, /* CENTRY "," comma 1 h 6720 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6728 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6736 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6744 */
	{.type Absolute, {.p 8}},		/* dd 8 6752 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6760 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6768 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6776 */
	{.type Header, {.hdr { 2, "c,", /* C_c = 6792 */ colon }}}, /* CENTRY "c," c 2 h 6800 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6808 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6816 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6824 */
	{.type Absolute, {.p 1}},		/* dd 1 6832 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6840 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6848 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6856 */
	{.type Header, {.hdr { 5, "allot", /* C_allot = 6872 */ colon }}}, /* CENTRY "allot" allot 5 ; ( n -- ) here = here+n h 6880 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6888 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6896 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6904 */
	{.type Header, {.hdr { 6, "vallot", /* C_vallot = 6920 */ colon }}}, /* CENTRY "vallot" vallot 6 ; allot on the variable space ( n -- ) vhere = vhere+n h 6928 */
	{.type FromH0, {.p M_Vp}, .src = "dd M_Vp"},		/* dd M_Vp 6936 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6944 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6952 */
	{.type Header, {.hdr { 3, "pad", /* C_pad = 6968 */ colon }}}, /* CENTRY "pad" pad 3 h 6976 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6984 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6992 */
	{.type Absolute, {.p 256}},		/* dd 256 7000 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7008 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7016 */
	{.type Header, {.hdr { 5, "align", /* C_align = 7032 */ colon }}}, /* CENTRY "align" align 5 ; ( -- ) align here to a cell boundary h 7040 */
	{.type FromH0, {.p C_here}, .src = "dd C_here		; Dp @"},		/* dd C_here		; Dp @ 7048 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned	; here is aligned to a multiple of 8"},		/* dd C_aligned	; here is aligned to a multiple of 8 7056 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp			; store the aligned here at Dp"},		/* dd M_Dp			; store the aligned here at Dp 7064 */
	{.type FromH0, {.p M_store}, .src = "dd M_store		; Dp contains aligned_here"},		/* dd M_store		; Dp contains aligned_here 7072 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7080 */
	{.type Header, {.hdr { 6, "unused", /* C_unused = 7096 */ colon }}}, /* CENTRY "unused" unused 6 h 7104 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 7112 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7120 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 7128 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7136 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7144 */
	{.type Header, {.hdr { 2, "<#", /* C_fromhash = 7160 */ colon }}}, /* CENTRY "<#" fromhash 2 h 7168 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7176 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7184 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7192 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7200 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7208 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7216 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7224 */
	{.type Header, {.hdr { 1, "#", /* C_hash = 7240 */ colon }}}, /* CENTRY "#" hash 1 h 7248 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 7256 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7264 */
	{.type FromH0, {.p M_uslashmod}, .src = "dd M_uslashmod"},		/* dd M_uslashmod 7272 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7280 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7288 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7296 */
	{.type Absolute, {.p 9}},		/* dd 9 7304 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 7312 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7320 */
	{.type FromH0, {.p L92}, .src = "dd L92"},		/* dd L92 7328 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7336 */
	{.type Absolute, {.p 97}},		/* dd 97 7344 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7352 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7360 */
	{.type Absolute, {.p 10}},		/* dd 10 7368 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7376 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7384 */
	{.type FromH0, {.p L93}, .src = "dd L93"},		/* dd L93 7392 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7400 */
	{.type Absolute, {.p 48}},		/* dd 48 7408 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7416 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7424 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7432 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7440 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7448 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7456 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7464 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7472 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7480 */
	{.type Header, {.hdr { 2, "#s", /* C_hashs = 7496 */ colon }}}, /* CENTRY "#s" hashs 2 h 7504 */
	{.type FromH0, {.p C_hash}, .src = "dd C_hash"},		/* dd C_hash 7512 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7520 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7528 */
	{.type FromH0, {.p L96}, .src = "dd L96"},		/* dd L96 7536 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7544 */
	{.type FromH0, {.p L95}, .src = "dd L95"},		/* dd L95 7552 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7560 */
	{.type Header, {.hdr { 2, "#>", /* C_hashfrom = 7576 */ colon }}}, /* CENTRY "#>" hashfrom 2 h 7584 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 7592 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7600 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7608 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7616 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7624 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7632 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7640 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7648 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7656 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7664 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7672 */
	{.type Header, {.hdr { 4, "hold", /* C_hold = 7688 */ colon }}}, /* CENTRY "hold" hold 4 h 7696 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7704 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7712 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7720 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7728 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 7736 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7744 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 7752 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7760 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7768 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7776 */
	{.type Header, {.hdr { 4, "sign", /* C_sign = 7792 */ colon }}}, /* CENTRY "sign" sign 4 h 7800 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 7808 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7816 */
	{.type FromH0, {.p L100}, .src = "dd L100"},		/* dd L100 7824 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7832 */
	{.type Absolute, {.p 45}},		/* dd 45 7840 */
	{.type FromH0, {.p C_hold}, .src = "dd C_hold"},		/* dd C_hold 7848 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7856 */
	{.type Header, {.hdr { 1, ".", /* C_dot = 7872 */ colon }}}, /* CENTRY "." dot 1 ; print the top of stack ( n -- ) h 7880 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; ( n -- n n )"},		/* dd M_dup		; ( n -- n n ) 7888 */
	{.type FromH0, {.p C_abs}, .src = "dd C_abs		; ( n n -- n u )"},		/* dd C_abs		; ( n n -- n u ) 7896 */
	{.type FromH0, {.p C_fromhash}, .src = "dd C_fromhash	; pad = h+256; >num = pad+1024"},		/* dd C_fromhash	; pad = h+256; >num = pad+1024 7904 */
	{.type FromH0, {.p C_hashs}, .src = "dd C_hashs		; ( n u1 -- n n2 )"},		/* dd C_hashs		; ( n u1 -- n n2 ) 7912 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap		; ( n n2 -- n2 n )"},		/* dd M_xswap		; ( n n2 -- n2 n ) 7920 */
	{.type FromH0, {.p C_sign}, .src = "dd C_sign		; ( n2 n -- n2 )"},		/* dd C_sign		; ( n2 n -- n2 ) 7928 */
	{.type FromH0, {.p C_hashfrom}, .src = "dd C_hashfrom	; ( u1 -- a n )"},		/* dd C_hashfrom	; ( u1 -- a n ) 7936 */
	{.type FromH0, {.p C_type}, .src = "dd C_type		; ( a n -- )"},		/* dd C_type		; ( a n -- ) 7944 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 7952 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7960 */
	{.type Header, {.hdr { 2, ".r", /* C_dotr = 7976 */ colon }}}, /* CENTRY ".r" dotr 2 h 7984 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 7992 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8000 */
	{.type FromH0, {.p C_abs}, .src = "dd C_abs"},		/* dd C_abs 8008 */
	{.type FromH0, {.p C_fromhash}, .src = "dd C_fromhash"},		/* dd C_fromhash 8016 */
	{.type FromH0, {.p C_hashs}, .src = "dd C_hashs"},		/* dd C_hashs 8024 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 8032 */
	{.type FromH0, {.p C_sign}, .src = "dd C_sign"},		/* dd C_sign 8040 */
	{.type FromH0, {.p C_hashfrom}, .src = "dd C_hashfrom"},		/* dd C_hashfrom 8048 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 8056 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 8064 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8072 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8080 */
	{.type Absolute, {.p 0}},		/* dd 0 8088 */
	{.type FromH0, {.p C_max}, .src = "dd C_max"},		/* dd C_max 8096 */
	{.type FromH0, {.p C_spaces}, .src = "dd C_spaces"},		/* dd C_spaces 8104 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 8112 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8120 */
	{.type Header, {.hdr { 3, "hex", /* C_hex = 8136 */ colon }}}, /* CENTRY "hex" hex 3 h 8144 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8152 */
	{.type Absolute, {.p 16}},		/* dd 16 8160 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8168 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8176 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8184 */
	{.type Header, {.hdr { 7, "decimal", /* C_decimal = 8200 */ colon }}}, /* CENTRY "decimal" decimal 7 h 8208 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8216 */
	{.type Absolute, {.p 10}},		/* dd 10 8224 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8232 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8240 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8248 */
	{.type Header, {.hdr { 5, "digit", /* C_digit = 8264 */ colon }}}, /* CENTRY "digit" digit 5 ; ( c -- ) h 8272 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8280 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8288 */
	{.type Absolute, {.p 65}},		/* dd 65 8296 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8304 */
	{.type Absolute, {.p 91}},		/* dd 91 8312 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8320 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8328 */
	{.type FromH0, {.p L106}, .src = "dd L106"},		/* dd L106 8336 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8344 */
	{.type Absolute, {.p 55}},		/* dd 55 8352 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8360 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8368 */
	{.type FromH0, {.p L107}, .src = "dd L107"},		/* dd L107 8376 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8384 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8392 */
	{.type Absolute, {.p 97}},		/* dd 97 8400 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8408 */
	{.type Absolute, {.p 123}},		/* dd 123 8416 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8424 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8432 */
	{.type FromH0, {.p L108}, .src = "dd L108"},		/* dd L108 8440 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8448 */
	{.type Absolute, {.p 87}},		/* dd 87 8456 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8464 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8472 */
	{.type FromH0, {.p L109}, .src = "dd L109"},		/* dd L109 8480 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8488 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8496 */
	{.type Absolute, {.p 48}},		/* dd 48 8504 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8512 */
	{.type Absolute, {.p 58}},		/* dd 58 8520 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8528 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8536 */
	{.type FromH0, {.p L110}, .src = "dd L110"},		/* dd L110 8544 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8552 */
	{.type Absolute, {.p 48}},		/* dd 48 8560 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8568 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8576 */
	{.type FromH0, {.p L111}, .src = "dd L111"},		/* dd L111 8584 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8592 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8600 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8608 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8616 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8624 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 8632 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 8640 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8648 */
	{.type FromH0, {.p L112}, .src = "dd L112"},		/* dd L112 8656 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 8664 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8672 */
	{.type FromH0, {.p L113}, .src = "dd L113"},		/* dd L113 8680 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8688 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8696 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8704 */
	{.type Header, {.hdr { 6, "number", /* C_number = 8720 */ colon }}}, /* CENTRY "number" number 6 ; ( a n1 -- n2 -1 | a n1 0 ) h 8728 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 -- n1 a )"},		/* dd M_xswap	; ( a n1 -- n1 a ) 8736 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n1 a -- n1 a a )"},		/* dd M_dup	; ( n1 a -- n1 a a ) 8744 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( n1 a a -- n1 a c )"},		/* dd M_cfetch	; ( n1 a a -- n1 a c ) 8752 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8760 */
	{.type Absolute, {.p 45}},		/* dd 45		; ( n1 a c -- n1 a c - ) 8768 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n1 a c -- n1 a f )"},		/* dd M_equal	; ( n1 a c -- n1 a f ) 8776 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; ( n1 a c -- n1 a )"},		/* dd M_cjump	; ( n1 a c -- n1 a ) 8784 */
	{.type FromH0, {.p L115}, .src = "dd L115		; c != -"},		/* dd L115		; c != - 8792 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; c == - ( n1 a -- n1 a+1 )"},		/* dd C_1plus	; c == - ( n1 a -- n1 a+1 ) 8800 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 8808 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 )"},		/* dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 ) 8816 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8824 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( a+1 n1-1 -- a+1 n1-1 -1 ) 8832 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1)"},		/* dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1) 8840 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8848 */
	{.type FromH0, {.p L116}, .src = "dd L116"},		/* dd L116 8856 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( n1 a -- a n1)"},		/* dd M_xswap	; ( n1 a -- a n1) 8864 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8872 */
	{.type Absolute, {.p 1}},		/* dd 1 8880 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1)"},		/* dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1) 8888 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a n1 -- a n1 n1 ) (R nr)"},		/* dd M_dup	; ( a n1 -- a n1 n1 ) (R nr) 8896 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1)"},		/* dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1) 8904 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8912 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a n1 -- a n1 0) (R nr n1) 8920 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1)"},		/* dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1) 8928 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8936 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a 0 n1 -- a 0 n1 0) (R nr n1) 8944 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1) 8952 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8960 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1) 8968 */
	{.type FromH0, {.p M_multiply}, .src = "dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1) 8976 */
	{.type FromH0, {.p M_over}, .src = "dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1)"},		/* dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1) 8984 */
	{.type FromH0, {.p M_i}, .src = "dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1) 8992 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1) 9000 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1)"},		/* dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1) 9008 */
	{.type FromH0, {.p C_digit}, .src = "dd C_digit"},		/* dd C_digit 9016 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9024 */
	{.type FromH0, {.p L118}, .src = "dd L118"},		/* dd L118 9032 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 9040 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9048 */
	{.type FromH0, {.p L119}, .src = "dd L119"},		/* dd L119 9056 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9064 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 9072 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9080 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9088 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9096 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 9104 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9112 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 9120 */
	{.type FromH0, {.p L117}, .src = "dd L117"},		/* dd L117 9128 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9136 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9144 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 9152 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9160 */
	{.type FromH0, {.p M_multiply}, .src = "dd M_multiply"},		/* dd M_multiply 9168 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 9176 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9184 */
	{.type Header, {.hdr { 5, "abort", /* C_abort = 9200 */ colon }}}, /* CENTRY "abort" abort 5 h 9208 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec"},		/* dd MV_Abortvec 9216 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9224 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 9232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9240 */
	{.type Header, {.hdr { 6, "source", /* C_source = 9256 */ colon }}}, /* CENTRY "source" source 6 h 9264 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9272 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9280 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9288 */
/* ; current-input-char */	{.type Header, {.hdr { 13, "current-input", /* C_current_input = 9312 */ colon }}}, /* CENTRY "current-input" current_input 13 ; ( -- c ) read the next character from the location in Sourcebuf h 9320 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9328 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9336 */
	{.type FromH0, {.p C_source}, .src = "dd C_source"},		/* dd C_source 9344 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus		; Sourcebuf + >In"},		/* dd M_plus		; Sourcebuf + >In 9352 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 9360 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9368 */
	{.type Header, {.hdr { 10, "save-input", /* C_save_input = 9392 */ colon }}}, /* CENTRY "save-input" save_input 10 ; ( -- infd >in >limit sourcebuf 'Acceptvec 5 ) save input stream onto the stack h 9400 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 9408 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9416 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9424 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9432 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9440 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9448 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9456 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9464 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 9472 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9488 */
	{.type Absolute, {.p 5}},		/* dd 5 9496 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9504 */
	{.type Header, {.hdr { 13, "default-input", /* C_default_input = 9528 */ colon }}}, /* CENTRY "default-input" default_input 13 ; stream input from stdin into Text input buffer h 9536 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 9544 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 9552 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9560 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9568 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9576 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9584 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9592 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib"},		/* dd M_Tib 9600 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9608 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9616 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9624 */
	{.type FromH0, {.p C_accept_line}, .src = "dd C_accept_line	; could use C_accept_key too"},		/* dd C_accept_line	; could use C_accept_key too 9632 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 9640 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9648 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9656 */
	{.type Header, {.hdr { 13, "restore-input", /* C_restore_input = 9680 */ colon }}}, /* CENTRY "restore-input" restore_input 13 ; ( <input>|empty -- f ) ; restore input stream from the stack or set the default-input as the input stream h 9688 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 9696 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; reset Eof back to 0"},		/* dd C_off		; reset Eof back to 0 9704 */
	{.type FromH0, {.p C_depth}, .src = "dd C_depth"},		/* dd C_depth 9712 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9720 */
	{.type Absolute, {.p 6}},		/* dd 6			; is the input stream on the stack, depth == 6? 9728 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 9736 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9744 */
	{.type FromH0, {.p L132}, .src = "dd L132			; depth <> 6, there is no input stream on the stack, get out"},		/* dd L132			; depth <> 6, there is no input stream on the stack, get out 9752 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; depth == 6, now check if there is a 5 on the top of stack"},		/* dd M_dup		; depth == 6, now check if there is a 5 on the top of stack 9760 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9768 */
	{.type Absolute, {.p 5}},		/* dd 5			; is 5 on the top of stack? 9776 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 9784 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9792 */
	{.type FromH0, {.p L132}, .src = "dd L132			; top of stack <> 5, there is no input stream on the stack, get out"},		/* dd L132			; top of stack <> 5, there is no input stream on the stack, get out 9800 */
/* ; ( infd >in >limit sourcebuf 'accept 5 ) */	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; ( infd >in >limit sourcebuf 'accept )"},		/* dd M_drop		; ( infd >in >limit sourcebuf 'accept ) 9808 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 9816 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9824 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9832 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9840 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9848 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9856 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9864 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9872 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 9880 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9888 */
	{.type FromH0, {.p C_true}, .src = "dd C_true			; ( true )"},		/* dd C_true			; ( true ) 9896 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9904 */
	{.type FromH0, {.p C_default_input}, .src = "dd C_default_input	; no input stream on the stack, use default input from now"},		/* dd C_default_input	; no input stream on the stack, use default input from now 9912 */
	{.type FromH0, {.p C_false}, .src = "dd C_false			; ( 0 )"},		/* dd C_false			; ( 0 ) 9920 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9928 */
	{.type Header, {.hdr { 14, "?restore-input", /* C_qrestore_input = 9952 */ colon }}}, /* CENTRY "?restore-input" qrestore_input 14 ; ( <input> -- ) ; use the input stream on the stack or abort h 9960 */
	{.type FromH0, {.p C_restore_input}, .src = "dd C_restore_input"},		/* dd C_restore_input 9968 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 9976 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9984 */
	{.type FromH0, {.p L136}, .src = "dd L136		; input stream restored"},		/* dd L136		; input stream restored 9992 */
/* ; no input stream on the stack to restore, show error and abort */	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 10000 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10008 */
	{.type FromH0, {.p L137}, .src = "dd L137"},		/* dd L137 10016 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10024 */
	{.type Absolute, {.p 23}},		/* dd 23 10032 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 10040 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 10048 */
	{.type FromH0, {.p C_depth}, .src = "dd C_depth"},		/* dd C_depth 10056 */
	{.type FromH0, {.p C_dot}, .src = "dd C_dot"},		/* dd C_dot 10064 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 10072 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 10080 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10088 */
/* ; next-input-char */	{.type Header, {.hdr { 10, "next-input", /* C_next_input = 10112 */ colon }}}, /* CENTRY "next-input" next_input 10 ; when >In < >Limit ( -- true c ). ( -- 0 false ) otherwise h 10120 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10128 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10136 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 10144 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10152 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 10160 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10168 */
	{.type FromH0, {.p L139}, .src = "dd L139	; >In >= >Limit"},		/* dd L139	; >In >= >Limit 10176 */
	{.type FromH0, {.p C_true}, .src = "dd C_true	; >In < >Limit"},		/* dd C_true	; >In < >Limit 10184 */
	{.type FromH0, {.p C_current_input}, .src = "dd C_current_input	; ( -- c )"},		/* dd C_current_input	; ( -- c ) 10192 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 10200 */
	{.type FromH0, {.p L140}, .src = "dd L140"},		/* dd L140 10208 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10216 */
	{.type Absolute, {.p 0}},		/* dd 0 10224 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 10232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10240 */
/* ; replace current-input and next-input with an asm function that does cmove until it meets a certain character or limit? */	{.type Header, {.hdr { 5, "parse", /* C_parse = 10256 */ colon }}}, /* CENTRY "parse" parse 5 ; ( c -- a ) Place the counted string in Wordbuf and return that address. c = word delimiter. h 10264 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; ( c -- ) (R -- c )"},		/* dd M_rpush		; ( c -- ) (R -- c ) 10272 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf"},		/* dd MV_Wordbuf 10280 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( -- Wordb )"},		/* dd M_fetch		; ( -- Wordb ) 10288 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus		; ( Wordb -- Wordb+1 )"},		/* dd C_1plus		; ( Wordb -- Wordb+1 ) 10296 */
	{.type FromH0, {.p C_next_input}, .src = "dd C_next_input ; ( Wordb+1 -- Wordb+1 f c )"},		/* dd C_next_input ; ( Wordb+1 -- Wordb+1 f c ) 10304 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c )"},		/* dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c ) 10312 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) )"},		/* dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) ) 10320 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand		; ( Wordb+1 f&(c!=cinitial) )"},		/* dd M_binand		; ( Wordb+1 f&(c!=cinitial) ) 10328 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10336 */
	{.type FromH0, {.p L143}, .src = "dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew"},		/* dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew 10344 */
	{.type FromH0, {.p C_current_input}, .src = "dd C_current_input	; ( Wordb+1 -- Wordb+1 c )"},		/* dd C_current_input	; ( Wordb+1 -- Wordb+1 c ) 10352 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 10360 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1"},		/* dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1 10368 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus		; ( Wordb+1 -- Wordb+2 )"},		/* dd C_1plus		; ( Wordb+1 -- Wordb+2 ) 10376 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10384 */
	{.type Absolute, {.p 1}},		/* dd 1 10392 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10400 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10408 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 10416 */
	{.type FromH0, {.p L142}, .src = "dd L142		; ( Wordb+2 ) repeat"},		/* dd L142		; ( Wordb+2 ) repeat 10424 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10432 */
	{.type Absolute, {.p 1}},		/* dd 1 10440 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10448 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10456 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- )"},		/* dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- ) 10464 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; (Wordb+1 c -- Wordb+1)"},		/* dd M_drop		; (Wordb+1 c -- Wordb+1) 10472 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf"},		/* dd MV_Wordbuf 10480 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb)"},		/* dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb) 10488 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb)"},		/* dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb) 10496 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb)"},		/* dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb) 10504 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb)"},		/* dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb) 10512 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb)"},		/* dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb) 10520 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb)"},		/* dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb) 10528 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now."},		/* dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now. 10536 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( -- Wordb) (R Wordb -- )"},		/* dd M_rpop		; ( -- Wordb) (R Wordb -- ) 10544 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10552 */
	{.type Header, {.hdr { 4, "word", /* C_word = 10568 */ colon }}}, /* CENTRY "word" word 4 ; ( c -- a ) skip the c"s. Placed the counted string in a (as in Wordbuf) h 10576 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- ) (R -- c )"},		/* dd M_rpush	; ( -- ) (R -- c ) 10584 */
	{.type FromH0, {.p C_next_input}, .src = "dd C_next_input ; ( -- f c2 ) (R c1 -- )"},		/* dd C_next_input ; ( -- f c2 ) (R c1 -- ) 10592 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial )"},		/* dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial ) 10600 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial )"},		/* dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial ) 10608 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial )"},		/* dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial ) 10616 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10624 */
	{.type FromH0, {.p L146}, .src = "dd L146		; >In >= >Limit || cinitial != cnew"},		/* dd L146		; >In >= >Limit || cinitial != cnew 10632 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal	; >In < >Limit && cinitial == cnew"},		/* dd M_literal	; >In < >Limit && cinitial == cnew 10640 */
	{.type Absolute, {.p 1}},		/* dd 1 10648 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10656 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10664 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump		; repeat"},		/* dd M_jump		; repeat 10672 */
	{.type FromH0, {.p L145}, .src = "dd L145"},		/* dd L145 10680 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( cinitial ) Sourcebuf+>In = location of first non-matching character"},		/* dd M_rpop		; ( cinitial ) Sourcebuf+>In = location of first non-matching character 10688 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 10696 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10704 */
/* ; accept is the Brdline of bio *//* ; if Acceptvec == 0, set Eof on and get out *//* ;	else execute it */	{.type Header, {.hdr { 6, "accept", /* C_accept = 10720 */ colon }}}, /* CENTRY "accept" accept 6 ; ( a n -- n ) get line or n chars or EOF from input and store at a h 10728 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 10736 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10744 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 10752 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10760 */
	{.type FromH0, {.p L300}, .src = "dd L300	; Acceptvec == 0, set Eof on and get out"},		/* dd L300	; Acceptvec == 0, set Eof on and get out 10768 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 10776 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10784 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop	; ( )"},		/* dd C_2drop	; ( ) 10792 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10800 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( 0 ) 10808 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 10816 */
	{.type FromH0, {.p C_on}, .src = "dd C_on"},		/* dd C_on 10824 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10832 */
	{.type Header, {.hdr { 11, "accept-line", /* C_accept_line = 10856 */ colon }}}, /* CENTRY "accept-line" accept_line 11 ; ( a n -- n1 ) get line or n chars or EOF from input and store at a using key h 10864 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 10872 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( a n infd )"},		/* dd M_fetch		; ( a n infd ) 10880 */
	{.type FromH0, {.p C_read_file}, .src = "dd C_read_file	; ( n ioresult )"},		/* dd C_read_file	; ( n ioresult ) 10888 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10896 */
	{.type FromH0, {.p L301}, .src = "dd L301			; ioresult == false as n = -1"},		/* dd L301			; ioresult == false as n = -1 10904 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; ( n n )"},		/* dd M_dup		; ( n n ) 10912 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10920 */
	{.type FromH0, {.p L302}, .src = "dd L302			; ( 0 )"},		/* dd L302			; ( 0 ) 10928 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; n > 0. if n == 4096, error out. ( n n )"},		/* dd M_dup		; n > 0. if n == 4096, error out. ( n n ) 10936 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10944 */
	{.type Absolute, {.p 4096}},		/* dd 4096			; ( n n 4096 ) 10952 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal		; ( n n==4096 )"},		/* dd M_equal		; ( n n==4096 ) 10960 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump		; ( n )"},		/* dd M_cjump		; ( n ) 10968 */
	{.type FromH0, {.p L303}, .src = "dd L303			; n < 4096 ( n )"},		/* dd L303			; n < 4096 ( n ) 10976 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; n == 4096 ( n )"},		/* dd MV_Sourcebuf	; n == 4096 ( n ) 10984 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( n tib )"},		/* dd M_fetch		; ( n tib ) 10992 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap		; ( tib n )"},		/* dd M_xswap		; ( tib n ) 11000 */
	{.type FromH0, {.p C_type}, .src = "dd C_type		; show the long line and an error message"},		/* dd C_type		; show the long line and an error message 11008 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11016 */
	{.type FromH0, {.p L304}, .src = "dd L304"},		/* dd L304 11024 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11032 */
	{.type Absolute, {.p 37}},		/* dd 37 11040 */
	{.type FromH0, {.p C_type}, .src = "dd C_type		; show the error message"},		/* dd C_type		; show the error message 11048 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 11056 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 11064 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus		; n-- to avoid parsing the newline character"},		/* dd C_1minus		; n-- to avoid parsing the newline character 11072 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; ( n ) n = number of bytes read"},		/* dd M_exitcolon	; ( n ) n = number of bytes read 11080 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11088 */
	{.type FromH0, {.p L305}, .src = "dd L305"},		/* dd L305 11096 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11104 */
	{.type Absolute, {.p 12}},		/* dd 12 11112 */
	{.type FromH0, {.p C_type}, .src = "dd C_type		; show the error message"},		/* dd C_type		; show the error message 11120 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 11128 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 11136 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof	; n == 0, set Eof"},		/* dd MV_Eof	; n == 0, set Eof 11144 */
	{.type FromH0, {.p C_on}, .src = "dd C_on		; EOF"},		/* dd C_on		; EOF 11152 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; ( 0 )"},		/* dd M_exitcolon	; ( 0 ) 11160 */
/* ; loops through 1 character at a time until a newline unlike accept-line which gets the line in one call. */	{.type Header, {.hdr { 10, "accept-key", /* C_accept_key = 11184 */ colon }}}, /* CENTRY "accept-key" accept_key 10 ; ( a n -- n ) get line or n chars or EOF from input and store at a using key h 11192 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( n a -- )"},		/* dd M_xswap	; ( n a -- ) 11200 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n a a -- )"},		/* dd M_dup	; ( n a a -- ) 11208 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 11216 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( n -- ) (R a a -- )"},		/* dd M_rpush	; ( n -- ) (R a a -- ) 11224 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup	; ( n n -- ) (R a a -- )"},		/* dd C_qdup	; ( n n -- ) (R a a -- ) 11232 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; (if)"},		/* dd M_cjump	; (if) 11240 */
	{.type FromH0, {.p L149}, .src = "dd L149		; n == 0"},		/* dd L149		; n == 0 11248 */
	{.type FromH0, {.p C_key}, .src = "dd C_key	; n > 0 ( n -- n c )"},		/* dd C_key	; n > 0 ( n -- n c ) 11256 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( -- n c c )"},		/* dd M_dup	; ( -- n c c ) 11264 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11272 */
	{.type Absolute, {.p 10}},		/* dd 10		; ( -- n c c 10 ) 11280 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n c c 10 -- n c f ) checking for newline"},		/* dd M_equal	; ( n c c 10 -- n c f ) checking for newline 11288 */
	{.type FromH0, {.p M_over}, .src = "dd M_over	; ( -- n c f c )"},		/* dd M_over	; ( -- n c f c ) 11296 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11304 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( -- n c f c -1 ) 11312 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( -- n c f1 f2 )"},		/* dd M_equal	; ( -- n c f1 f2 ) 11320 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor	; ( -- n c f )"},		/* dd M_binor	; ( -- n c f ) 11328 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11336 */
	{.type FromH0, {.p L150}, .src = "dd L150"},		/* dd L150 11344 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop	; n == -1 || n == 10 (	-- )"},		/* dd C_2drop	; n == -1 || n == 10 (	-- ) 11352 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 11360 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 11368 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( -- a2-a1 )"},		/* dd M_minus	; ( -- a2-a1 ) 11376 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; ( -- n ) (R -- )"},		/* dd M_exitcolon	; ( -- n ) (R -- ) 11384 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( n c a -- ) (R a a -- )"},		/* dd M_rfetch	; ( n c a -- ) (R a a -- ) 11392 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; store the character at a"},		/* dd M_cstore	; store the character at a 11400 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( n a -- ) (R a -- )"},		/* dd M_rpop	; ( n a -- ) (R a -- ) 11408 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 11416 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address"},		/* dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address 11424 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; ( n -- n-1 )"},		/* dd C_1minus	; ( n -- n-1 ) 11432 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11440 */
	{.type FromH0, {.p L148}, .src = "dd L148	; loop again for the next character"},		/* dd L148	; loop again for the next character 11448 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 )"},		/* dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 ) 11456 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( a2 a1 -- ) (R a1 -- )"},		/* dd M_rpop	; ( a2 a1 -- ) (R a1 -- ) 11464 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( a2 a1 -- a2-a1 )"},		/* dd M_minus	; ( a2 a1 -- a2-a1 ) 11472 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11480 */
	{.type Header, {.hdr { 5, "query", /* C_query = 11496 */ colon }}}, /* CENTRY "query" query 5 ; read from input stream into the Text Input Buffer h 11504 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 11512 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; clear EOF flag"},		/* dd C_off	; clear EOF flag 11520 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top"},		/* dd M_Tib	; constant puts address of tibuffer on the top 11528 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11536 */
	{.type Absolute, {.p 4096}},		/* dd 4096	; ( tibuffer -- tibuffer 4096 ) 11544 */
	{.type FromH0, {.p C_accept}, .src = "dd C_accept ; ( tibuffer 4096 -- n )"},		/* dd C_accept ; ( tibuffer 4096 -- n ) 11552 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n -- n n )"},		/* dd M_dup	; ( n -- n n ) 11560 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq	; ( n n -- n f )"},		/* dd C_0eq	; ( n n -- n f ) 11568 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 11576 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11584 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; n == 0 && EOF"},		/* dd M_binand	; n == 0 && EOF 11592 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11600 */
	{.type FromH0, {.p L152}, .src = "dd L152		; false condition"},		/* dd L152		; false condition 11608 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; n == 0 && EOF ( n -- )"},		/* dd M_drop	; n == 0 && EOF ( n -- ) 11616 */
	{.type FromH0, {.p C_qrestore_input}, .src = "dd C_qrestore_input"},		/* dd C_qrestore_input 11624 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11632 */
	{.type FromH0, {.p L153}, .src = "dd L153"},		/* dd L153 11640 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 11648 */
	{.type FromH0, {.p M_store}, .src = "dd M_store		; number of characters to read >Limit = n"},		/* dd M_store		; number of characters to read >Limit = n 11656 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 11664 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; start from 0 >In = 0"},		/* dd C_off		; start from 0 >In = 0 11672 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11680 */
	{.type Header, {.hdr { 6, "refill", /* C_refill = 11696 */ colon }}}, /* CENTRY "refill" refill 6 ; no more refills when there is no 'Acceptvec h 11704 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 11712 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11720 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11728 */
	{.type FromH0, {.p L155}, .src = "dd L155"},		/* dd L155 11736 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 11744 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11752 */
	{.type FromH0, {.p C_query}, .src = "dd C_query"},		/* dd C_query 11760 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 11768 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11776 */
	{.type Header, {.hdr { 8, "findname", /* C_findname = 11800 */ colon }}}, /* CENTRY "findname" findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names h 11808 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 11816 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11824 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop"},		/* dd M_Dtop 11832 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; get latest dictionary link"},		/* dd M_fetch	; get latest dictionary link 11840 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 11848 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11856 */
	{.type FromH0, {.p L159}, .src = "dd L159	; seached until the first dictionary entry get out"},		/* dd L159	; seached until the first dictionary entry get out 11864 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a )"},		/* dd M_dup	; ( a -- a a ) 11872 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; ( a a -- a a+8) lenth + initial name address"},		/* dd C_cellplus	; ( a a -- a a+8) lenth + initial name address 11880 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name"},		/* dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name 11888 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11896 */
	{.type Absolute, {.p 64}},		/* dd 64		; check the reveal'ed flag 1=hidden, 0=reveal 11904 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; if hidden, goto L161 else L160"},		/* dd M_binand	; if hidden, goto L161 else L160 11912 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11920 */
	{.type FromH0, {.p L160}, .src = "dd L160"},		/* dd L160 11928 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; smudge'd dictionary entry, get the previous entry"},		/* dd M_fetch	; smudge'd dictionary entry, get the previous entry 11936 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11944 */
	{.type FromH0, {.p L161}, .src = "dd L161"},		/* dd L161 11952 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a1 -- a1 a1)"},		/* dd M_dup	; ( a1 -- a1 a1) 11960 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; ( a1 a1 -- a1 a1+8)"},		/* dd C_cellplus	; ( a1 a1 -- a1 a1+8) 11968 */
	{.type FromH0, {.p C_count}, .src = "dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n )"},		/* dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n ) 11976 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11984 */
	{.type Absolute, {.p 63}},		/* dd 63 11992 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len )"},		/* dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len ) 12000 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 12008 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 12016 */
	{.type FromH0, {.p C_count}, .src = "dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 )"},		/* dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 ) 12024 */
	{.type FromH0, {.p C_compare}, .src = "dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name"},		/* dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name 12032 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq	; found a match?"},		/* dd C_0eq	; found a match? 12040 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12048 */
	{.type FromH0, {.p L162}, .src = "dd L162		; no match"},		/* dd L162		; no match 12056 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; match found"},		/* dd C_cellplus	; match found 12064 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 12072 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12080 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 12088 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12096 */
	{.type FromH0, {.p L158}, .src = "dd L158"},		/* dd L158 12104 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 12112 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 12120 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 12128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12136 */
	{.type Header, {.hdr { 4, "find", /* C_find = 12152 */ colon }}}, /* CENTRY "find" find 4 ; ( a1 -- a2 f )? h 12160 */
	{.type FromH0, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 12168 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12176 */
	{.type FromH0, {.p L164}, .src = "dd L164"},		/* dd L164 12184 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12192 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 12200 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 12208 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 12216 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12224 */
	{.type Absolute, {.p 63}},		/* dd 63 12232 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 12240 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 12248 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 12256 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 12264 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 12272 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12280 */
	{.type Absolute, {.p 128}},		/* dd 128 12288 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 12296 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12304 */
	{.type FromH0, {.p L165}, .src = "dd L165"},		/* dd L165 12312 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12320 */
	{.type Absolute, {.p 1}},		/* dd 1 12328 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12336 */
	{.type FromH0, {.p L166}, .src = "dd L166"},		/* dd L166 12344 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12352 */
	{.type Absolute, {.p -1}},		/* dd -1 12360 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12368 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12376 */
	{.type FromH0, {.p L167}, .src = "dd L167"},		/* dd L167 12384 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 12392 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12400 */
	{.type Header, {.hdr { 1, "'", /* C_single_quote = 12416 */ colon }}}, /* CENTRY "'" single_quote 1 h 12424 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 12432 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 12440 */
	{.type FromH0, {.p C_find}, .src = "dd C_find"},		/* dd C_find 12448 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 12456 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12464 */
	{.type FromH0, {.p L169}, .src = "dd L169"},		/* dd L169 12472 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 12480 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 12488 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12496 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12504 */
	{.type FromH0, {.p L170}, .src = "dd L170"},		/* dd L170 12512 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12520 */
	{.type Absolute, {.p 3}},		/* dd 3 12528 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12536 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12544 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12552 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12560 */
	{.type Header, {.hdr { 6, "?stack", /* C_qstack = 12576 */ colon }}}, /* CENTRY "?stack" qstack 6 h 12584 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 12592 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 12600 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 12608 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12616 */
	{.type FromH0, {.p L172}, .src = "dd L172"},		/* dd L172 12624 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12632 */
	{.type FromH0, {.p L173}, .src = "dd L173"},		/* dd L173 12640 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12648 */
	{.type Absolute, {.p 16}},		/* dd 16 12656 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12664 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12672 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12680 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12688 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT	; ( str -- str 1) ; debug code to show the word found"},		/* dd MC_STDOUT	; ( str -- str 1) ; debug code to show the word found 12696 */
	{.type FromH0, {.p M_over}, .src = "dd M_over		; ( str 1 str )"},		/* dd M_over		; ( str 1 str ) 12704 */
	{.type FromH0, {.p C_count}, .src = "dd C_count 		; ( str 1 a n)"},		/* dd C_count 		; ( str 1 a n) 12712 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 12720 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 12728 */
	{.type Header, {.hdr { 9, "interpret", /* C_interpret = 12752 */ colon }}}, /* CENTRY "interpret" interpret 9 ; there is stuff in TIB to be interpreted >In and >Limit are set h 12760 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 12768 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( bl -- a ) a = address of counted string"},		/* dd C_word	; ( bl -- a ) a = address of counted string 12776 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12784 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 12792 */
	{.type FromH0, {.p C_0neq}, .src = "dd C_0neq"},		/* dd C_0neq 12800 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12808 */
	{.type FromH0, {.p L176}, .src = "dd L176	; count at a = 0, drop a and exit"},		/* dd L176	; count at a = 0, drop a and exit 12816 */
	{.type FromH0, {.p C_find}, .src = "dd C_find	; ( a -- a1 f ) a = address of counted string"},		/* dd C_find	; ( a -- a1 f ) a = address of counted string 12824 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12832 */
	{.type FromH0, {.p L177}, .src = "dd L177"},		/* dd L177 12840 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute	; found in dictionary, execute"},		/* dd M_execute	; found in dictionary, execute 12848 */
	{.type FromH0, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 12856 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12864 */
	{.type FromH0, {.p L178}, .src = "dd L178"},		/* dd L178 12872 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 12880 */
	{.type FromH0, {.p C_number}, .src = "dd C_number"},		/* dd C_number 12888 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 12896 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12904 */
	{.type FromH0, {.p L179}, .src = "dd L179"},		/* dd L179 12912 */
	{.type FromH0, {.p C_space}, .src = "dd C_space	; the word is neither in the dictionary nor a number"},		/* dd C_space	; the word is neither in the dictionary nor a number 12920 */
	{.type FromH0, {.p C_type}, .src = "dd C_type	; show the word"},		/* dd C_type	; show the word 12928 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12936 */
	{.type FromH0, {.p L180}, .src = "dd L180	; error I?"},		/* dd L180	; error I? 12944 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12952 */
	{.type Absolute, {.p 3}},		/* dd 3 12960 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12968 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12976 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12984 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12992 */
	{.type FromH0, {.p L175}, .src = "dd L175"},		/* dd L175 13000 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; count at a = 0 ( a -- )"},		/* dd M_drop	; count at a = 0 ( a -- ) 13008 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13016 */
	{.type Header, {.hdr { 6, "create", /* C_create = 13032 */ colon }}}, /* CENTRY "create" create 6 ; compiles dictionary header until the pfa (link, len, name, cfa) h 13040 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 13048 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here )"},		/* dd C_here	; ( -- here ) 13056 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- ) (R -- linkaddr )"},		/* dd M_rpush	; ( -- ) (R -- linkaddr ) 13064 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop	; ( -- Dtop ) (R -- linkaddr )"},		/* dd M_Dtop	; ( -- Dtop ) (R -- linkaddr ) 13072 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr )"},		/* dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr ) 13080 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; ( dtop -- ) (R -- linkaddr )"},		/* dd C_comma	; ( dtop -- ) (R -- linkaddr ) 13088 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 13096 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; get the word from the input stream ( c -- a ) skip any c. Placed the counted string in a (as in Wordbuf)"},		/* dd C_word	; get the word from the input stream ( c -- a ) skip any c. Placed the counted string in a (as in Wordbuf) 13104 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a ) (R -- linkaddr )"},		/* dd M_dup	; ( a -- a a ) (R -- linkaddr ) 13112 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a -- a len ) (R -- linkaddr )"},		/* dd M_cfetch	; ( a a -- a len ) (R -- linkaddr ) 13120 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( a len -- a len here ) (R -- linkaddr )"},		/* dd C_here	; ( a len -- a len here ) (R -- linkaddr ) 13128 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr )"},		/* dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr ) 13136 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte"},		/* dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte 13144 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr )"},		/* dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr ) 13152 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 )"},		/* dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 ) 13160 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 )"},		/* dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 ) 13168 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- len+1 ) (R -- linkaddr )"},		/* dd M_rpop	; ( -- len+1 ) (R -- linkaddr ) 13176 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1"},		/* dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1 13184 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 13192 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13200 */
	{.type FromH0, {.p M_variable}, .src = "dd M_variable"},		/* dd M_variable 13208 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( -- variablecfa) (R -- linkaddr )"},		/* dd M_fetch	; ( -- variablecfa) (R -- linkaddr ) 13216 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; ( -- ) put the variablecfa into the cfa"},		/* dd C_comma	; ( -- ) put the variablecfa into the cfa 13224 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- linkaddr) (R -- )"},		/* dd M_rpop	; ( -- linkaddr) (R -- ) 13232 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop"},		/* dd M_Dtop 13240 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; Dtop = just created link address"},		/* dd M_store	; Dtop = just created link address 13248 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13256 */
	{.type Header, {.hdr { 8, "variable", /* C_variable = 13280 */ colon }}}, /* CENTRY "variable" variable 8 ; compile to put the vhere then on the stack h 13288 */
	{.type FromH0, {.p C_create}, .src = "dd C_create"},		/* dd C_create 13296 */
	{.type FromH0, {.p C_vhere}, .src = "dd C_vhere"},		/* dd C_vhere 13304 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; put the next available variable location in pfa"},		/* dd C_comma	; put the next available variable location in pfa 13312 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13320 */
	{.type Absolute, {.p 1}},		/* dd 1 13328 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 13336 */
	{.type FromH0, {.p C_vallot}, .src = "dd C_vallot	; vhere = vhere+8, stored at Vp"},		/* dd C_vallot	; vhere = vhere+8, stored at Vp 13344 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13352 */
	{.type Header, {.hdr { 8, "constant", /* C_constant = 13376 */ colon }}}, /* CENTRY "constant" constant 8 ; ( n -- ) do the same as variable but change the cfa to (constant) h 13384 */
	{.type FromH0, {.p C_create}, .src = "dd C_create	; create dictionary header upto the cfa"},		/* dd C_create	; create dictionary header upto the cfa 13392 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13400 */
	{.type FromH0, {.p M_constant}, .src = "dd M_constant"},		/* dd M_constant 13408 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Contstantcfa -- (constant) )"},		/* dd M_fetch	; ( Contstantcfa -- (constant) ) 13416 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( (constant) -- (constant) here )"},		/* dd C_here	; ( (constant) -- (constant) here ) 13424 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13432 */
	{.type Absolute, {.p 1}},		/* dd 1 13440 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells	; ( (constant) here -- (constant) here 8 )"},		/* dd C_cells	; ( (constant) here -- (constant) here 8 ) 13448 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( (constant) here 8 -- (constant) here-8 )"},		/* dd M_minus	; ( (constant) here 8 -- (constant) here-8 ) 13456 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant) "},		/* dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant)  13464 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; store n into the dictionary"},		/* dd C_comma	; store n into the dictionary 13472 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13480 */
	{.type Header, {.hdr { 9, "immediate", /* C_immediate = 13504 */ colon }}}, /* CENTRY "immediate" immediate 9 h 13512 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 13520 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13528 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 13536 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13544 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13552 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13560 */
	{.type Absolute, {.p 128}},		/* dd 128 13568 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 13576 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 13584 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 13592 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13600 */
	{.type Header, {.hdr { 4, ">cfa", /* C_tocfa = 13616 */ colon }}}, /* CENTRY ">cfa" tocfa 4 h 13624 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13632 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13640 */
	{.type Absolute, {.p 63}},		/* dd 63 13648 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 13656 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 13664 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 13672 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13680 */
	{.type Header, {.hdr { 7, "compile", /* C_compile = 13696 */ colon }}}, /* CENTRY "compile" compile 7 h 13704 */
	{.type FromH0, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 13712 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13720 */
	{.type FromH0, {.p L188}, .src = "dd L188"},		/* dd L188 13728 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13736 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13744 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13752 */
	{.type Absolute, {.p 128}},		/* dd 128 13760 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 13768 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13776 */
	{.type FromH0, {.p L189}, .src = "dd L189"},		/* dd L189 13784 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa	; immediate"},		/* dd C_tocfa	; immediate 13792 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 13800 */
	{.type FromH0, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 13808 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13816 */
	{.type FromH0, {.p L190}, .src = "dd L190"},		/* dd L190 13824 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 13832 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 13840 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13848 */
	{.type FromH0, {.p L191}, .src = "dd L191"},		/* dd L191 13856 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13864 */
	{.type FromH0, {.p C_number}, .src = "dd C_number"},		/* dd C_number 13872 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 13880 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13888 */
	{.type FromH0, {.p L192}, .src = "dd L192"},		/* dd L192 13896 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 13904 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13912 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13920 */
	{.type FromH0, {.p L193}, .src = "dd L193"},		/* dd L193 13928 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13936 */
	{.type Absolute, {.p 3}},		/* dd 3 13944 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13952 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 13960 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 13968 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13976 */
	{.type FromH0, {.p L194}, .src = "dd L194"},		/* dd L194 13984 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13992 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14000 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14008 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14016 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14024 */
	{.type Header, {.hdr { 1, "]", /* C_close_bracket = 14040 */ colon }}}, /* CENTRY "]" close_bracket 1 h 14048 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 14056 */
	{.type FromH0, {.p C_on}, .src = "dd C_on"},		/* dd C_on 14064 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 14072 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 14080 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14088 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14096 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 14104 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14112 */
	{.type FromH0, {.p L197}, .src = "dd L197"},		/* dd L197 14120 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 14128 */
	{.type FromH0, {.p C_refill}, .src = "dd C_refill	; no more refills when there is no Acceptvec. Is it a problem? did not dig through to figure out"},		/* dd C_refill	; no more refills when there is no Acceptvec. Is it a problem? did not dig through to figure out 14136 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14144 */
	{.type FromH0, {.p L198}, .src = "dd L198"},		/* dd L198 14152 */
	{.type FromH0, {.p C_compile}, .src = "dd C_compile"},		/* dd C_compile 14160 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 14168 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14176 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14184 */
	{.type FromH0, {.p L199}, .src = "dd L199"},		/* dd L199 14192 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14200 */
	{.type FromH0, {.p L196}, .src = "dd L196"},		/* dd L196 14208 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14216 */
	{.type IHeader, {.hdr { 1, "[", /* CI_open_bracket = 14232 */ colon }}}, /* CIENTRY "[" open_bracket 1 h 14240 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 14248 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 14256 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14264 */
	{.type Header, {.hdr { 6, "smudge", /* C_smudge = 14280 */ colon }}}, /* CENTRY "smudge" smudge 6 h 14288 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 14296 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14304 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 14312 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14320 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14328 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14336 */
	{.type Absolute, {.p 64}},		/* dd 64 14344 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 14352 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 14360 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 14368 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14376 */
	{.type Header, {.hdr { 6, "reveal", /* C_reveal = 14392 */ colon }}}, /* CENTRY "reveal" reveal 6 h 14400 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 14408 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14416 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 14424 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14432 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14440 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14448 */
	{.type Absolute, {.p 64}},		/* dd 64 14456 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 14464 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 14472 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 14480 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 14488 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14496 */
	{.type Header, {.hdr { 1, ":", /* C_colon = 14512 */ colon }}}, /* CENTRY ":" colon 1 h 14520 */
	{.type FromH0, {.p C_create}, .src = "dd C_create	; create a dictionary header with (variable) at cfa"},		/* dd C_create	; create a dictionary header with (variable) at cfa 14528 */
	{.type FromH0, {.p C_smudge}, .src = "dd C_smudge"},		/* dd C_smudge 14536 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14544 */
	{.type FromH0, {.p M_colon}, .src = "dd M_colon"},		/* dd M_colon 14552 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon"},		/* dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon 14560 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( (colon) -- (colon) here )"},		/* dd C_here	; ( (colon) -- (colon) here ) 14568 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14576 */
	{.type Absolute, {.p 1}},		/* dd 1 14584 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 14592 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( (colon) here -- (colon) here-8 )"},		/* dd M_minus	; ( (colon) here -- (colon) here-8 ) 14600 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon"},		/* dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon 14608 */
	{.type FromH0, {.p C_close_bracket}, .src = "dd C_close_bracket"},		/* dd C_close_bracket 14616 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14624 */
	{.type IHeader, {.hdr { 1, ";", /* CI_semicolon = 14640 */ colon }}}, /* CIENTRY ";" semicolon 1 h 14648 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14656 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14664 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14672 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 14680 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 14688 */
	{.type FromH0, {.p C_reveal}, .src = "dd C_reveal"},		/* dd C_reveal 14696 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14704 */
	{.type IHeader, {.hdr { 7, "recurse", /* CI_recurse = 14720 */ colon }}}, /* CIENTRY "recurse" recurse 7 h 14728 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 14736 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14744 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 14752 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 14760 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14768 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14776 */
	{.type Header, {.hdr { 4, "char", /* C_char = 14792 */ colon }}}, /* CENTRY "char" char 4 ; ( -- c ) fetch the first character of the next word from input h 14800 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 14808 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( c -- a ) puts the address of the counted string from the input on the stack"},		/* dd C_word	; ( c -- a ) puts the address of the counted string from the input on the stack 14816 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; skip the count"},		/* dd C_1plus	; skip the count 14824 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; fetch the first character"},		/* dd M_cfetch	; fetch the first character 14832 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14840 */
	{.type Header, {.hdr { 7, "literal", /* C_literal = 14856 */ colon }}}, /* CENTRY "literal" literal 7 ; ( n -- ) adds (literal) n to the dictionary h 14864 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14872 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14880 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14888 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14896 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14904 */
	{.type Header, {.hdr { 8, "sliteral", /* C_sliteral = 14928 */ colon }}}, /* CENTRY "sliteral" sliteral 8 ; ( -- ) adds (sliteral) a n to the dictionary h 14936 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14944 */
	{.type FromH0, {.p M_sliteral}, .src = "dd M_sliteral"},		/* dd M_sliteral 14952 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; adds (sliteral) to the dictionary"},		/* dd C_comma	; adds (sliteral) to the dictionary 14960 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here)"},		/* dd C_here	; ( -- here) 14968 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14976 */
	{.type Absolute, {.p 34}},		/* dd 34		; ascii value of " 14984 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse	; ( here \" -- here a ) \" = word delimiter. a = address of counted string (in Wordbuf)."},		/* dd C_parse	; ( here \" -- here a ) \" = word delimiter. a = address of counted string (in Wordbuf). 14992 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( here a -- here a a )"},		/* dd M_dup	; ( here a -- here a a ) 15000 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( here a a -- here a n )"},		/* dd M_cfetch	; ( here a a -- here a n ) 15008 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( here a n -- here a n+1 ) n+1 as 1 for the count and n for the length of the string"},		/* dd C_1plus	; ( here a n -- here a n+1 ) n+1 as 1 for the count and n for the length of the string 15016 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( here a n+1 -- here a ) (R -- n+1)"},		/* dd M_rpush	; ( here a n+1 -- here a ) (R -- n+1) 15024 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( here a -- a here ) (R -- n+1)"},		/* dd M_xswap	; ( here a -- a here ) (R -- n+1) 15032 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( a here -- a here n+1 ) (R -- n+1 )"},		/* dd M_rfetch	; ( a here -- a here n+1 ) (R -- n+1 ) 15040 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; ( a here n+1 -- ) moves n+1 from a to here"},		/* dd M_cmove	; ( a here n+1 -- ) moves n+1 from a to here 15048 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- n+1 ) (R -- )"},		/* dd M_rpop	; ( -- n+1 ) (R -- ) 15056 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( n+1 -- ) here = here+n+1"},		/* dd C_allot	; ( n+1 -- ) here = here+n+1 15064 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; align here"},		/* dd C_align	; align here 15072 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15080 */
	{.type Header, {.hdr { 6, "string", /* C_string = 15096 */ colon }}}, /* CENTRY "string" string 6 ; ( c -- ) h 15104 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 15112 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15120 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 15128 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 15136 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 15144 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15152 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 15160 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 15168 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 15176 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 15184 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15192 */
	{.type IHeader, {.hdr { 6, "[char]", /* CI_char_brackets = 15208 */ colon }}}, /* CIENTRY "[char]" char_brackets 6 ; take the next character from the input stream during compilation h 15216 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 15224 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 15232 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 15240 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 15248 */
	{.type FromH0, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 15256 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15264 */
	{.type IHeader, {.hdr { 3, "[']", /* CI_quote_brackets = 15280 */ colon }}}, /* CIENTRY "[']" quote_brackets 3 ; take the address of next token from the input stream during compilation h 15288 */
	{.type FromH0, {.p C_single_quote}, .src = "dd C_single_quote"},		/* dd C_single_quote 15296 */
	{.type FromH0, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 15304 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15312 */
	{.type IHeader, {.hdr { 1, "(", /* CI_openparen = 15328 */ colon }}}, /* CIENTRY "(" openparen 1 ; ignore until ) from the input stream during compilation h 15336 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15344 */
	{.type Absolute, {.p 41}},		/* dd 41 15352 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 15360 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 15368 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15376 */
/* ; if the line is longer than Tib, then skipping this line is not good enough. hence, throwing an error when >Limit == Tib length */	{.type IHeader, {.hdr { 1, "\\", /* CI_backslash = 15392 */ colon }}}, /* CIENTRY "\\" backslash 1 ; when there is no Acceptvec, find a newline in the buffer and skip until that h 15400 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 15408 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 15416 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15424 */
	{.type FromH0, {.p L214}, .src = "dd L214		; there is no Acceptvec, we are processing a buffer"},		/* dd L214		; there is no Acceptvec, we are processing a buffer 15432 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit	; there is an Acceptvec, skip the rest of this line"},		/* dd MV_toLimit	; there is an Acceptvec, skip the rest of this line 15440 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 15448 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 15456 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15464 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15472 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15480 */
	{.type Absolute, {.p 10}},		/* dd 10 15488 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse	; find the next 10 = LF character"},		/* dd C_parse	; find the next 10 = LF character 15496 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; skip all characters not equal to 10"},		/* dd M_drop	; skip all characters not equal to 10 15504 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15512 */
	{.type Header, {.hdr { 8, "(?abort)", /* C_qabort_parens = 15536 */ colon }}}, /* CENTRY "(?abort)" qabort_parens 8 h 15544 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 15552 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15560 */
	{.type FromH0, {.p L217}, .src = "dd L217"},		/* dd L217 15568 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 15576 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 15584 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 15592 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 15600 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15608 */
	{.type FromH0, {.p L218}, .src = "dd L218"},		/* dd L218 15616 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 15624 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15632 */
	{.type IHeader, {.hdr { 6, "abort\"", /* CI_abort_double_quote = 15648 */ colon }}}, /* CIENTRY "abort\"" abort_double_quote 6 h 15656 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 15664 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15672 */
	{.type FromH0, {.p C_qabort_parens}, .src = "dd C_qabort_parens"},		/* dd C_qabort_parens 15680 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15688 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15696 */
	{.type Header, {.hdr { 1, "\"", /* C_double_quote = 15712 */ colon }}}, /* CENTRY "\"" double_quote 1 ; stores counted string in the dictionary and also leaves the address count of the string on the stack - used to use strings at the interpreter prompt h 15720 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15728 */
	{.type Absolute, {.p 34}},		/* dd 34 15736 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 15744 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 15752 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 15760 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15768 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 15776 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 15784 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15792 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 15800 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15808 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 15816 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15824 */
	{.type Header, {.hdr { 2, "c\"", /* C_cdouble_quote = 15840 */ colon }}}, /* CENTRY "c\"" cdouble_quote 2 ; stores counted string in the dictionary and also leaves the address of the counted string on the stack h 15848 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15856 */
	{.type Absolute, {.p 34}},		/* dd 34		; ( -- \" ) 15864 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( \" -- a ) a = counted string address. a will be in Wordbuf"},		/* dd C_word	; ( \" -- a ) a = counted string address. a will be in Wordbuf 15872 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a)"},		/* dd M_dup	; ( a -- a a) 15880 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a -- a n )"},		/* dd M_cfetch	; ( a a -- a n ) 15888 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( a n -- a n+1 )"},		/* dd C_1plus	; ( a n -- a n+1 ) 15896 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n -- a ) (R -- n+1)"},		/* dd M_rpush	; ( a n -- a ) (R -- n+1) 15904 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( a -- a here ) (R -- n+1)"},		/* dd C_here	; ( a -- a here ) (R -- n+1) 15912 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( a here -- a here n+1) (R -- n+1)"},		/* dd M_rfetch	; ( a here -- a here n+1) (R -- n+1) 15920 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; move counted string from a to here"},		/* dd M_cmove	; move counted string from a to here 15928 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here )"},		/* dd C_here	; ( -- here ) 15936 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( here -- here n+1 )(R -- )"},		/* dd M_rpop	; ( here -- here n+1 )(R -- ) 15944 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( here n+1 -- here) here += n+1"},		/* dd C_allot	; ( here n+1 -- here) here += n+1 15952 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15960 */
	{.type IHeader, {.hdr { 2, "s\"", /* CI_sdouble_quote = 15976 */ colon }}}, /* CIENTRY "s\"" sdouble_quote 2 ; add the string from the input stream to the dictionary as (sliteral) count string - at run-time puts the ( -- addr n) of the counted string on the stack. h 15984 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 15992 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16000 */
	{.type IHeader, {.hdr { 2, ".\"", /* CI_dotstr = 16016 */ colon }}}, /* CIENTRY ".\"" dotstr 2 ; do what s" does and then add a type word to the dictionary to print that string h 16024 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 16032 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16040 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 16048 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16056 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16064 */
	{.type IHeader, {.hdr { 2, "if", /* CI_if = 16080 */ colon }}}, /* CIENTRY "if" if 2 h 16088 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16096 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16104 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16112 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16120 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16128 */
	{.type Absolute, {.p 0}},		/* dd 0 16136 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16144 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16152 */
	{.type IHeader, {.hdr { 4, "else", /* CI_else = 16168 */ colon }}}, /* CIENTRY "else" else 4 h 16176 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16184 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16192 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16200 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16208 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 16216 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16224 */
	{.type Absolute, {.p 0}},		/* dd 0 16232 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16240 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16248 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16256 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16264 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 16272 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16280 */
	{.type IHeader, {.hdr { 4, "then", /* CI_then = 16296 */ colon }}}, /* CIENTRY "then" then 4 h 16304 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16312 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16320 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16328 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16336 */
	{.type IHeader, {.hdr { 5, "begin", /* CI_begin = 16352 */ colon }}}, /* CIENTRY "begin" begin 5 h 16360 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16368 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16376 */
	{.type IHeader, {.hdr { 5, "again", /* CI_again = 16392 */ colon }}}, /* CIENTRY "again" again 5 h 16400 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16408 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16416 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16424 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16432 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16440 */
	{.type IHeader, {.hdr { 5, "until", /* CI_until = 16456 */ colon }}}, /* CIENTRY "until" until 5 h 16464 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16472 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16480 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16488 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16496 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16504 */
	{.type IHeader, {.hdr { 5, "while", /* CI_while = 16520 */ colon }}}, /* CIENTRY "while" while 5 h 16528 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16536 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16544 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16552 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16560 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16568 */
	{.type Absolute, {.p 0}},		/* dd 0 16576 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16584 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16592 */
	{.type IHeader, {.hdr { 6, "repeat", /* CI_repeat = 16608 */ colon }}}, /* CIENTRY "repeat" repeat 6 h 16616 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16624 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16632 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16640 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16648 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16656 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16664 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16672 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16680 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16688 */
	{.type IHeader, {.hdr { 2, "do", /* CI_do = 16704 */ colon }}}, /* CIENTRY "do" do 2 h 16712 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16720 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time"},		/* dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time 16728 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; puts (do) into the dictionary"},		/* dd C_comma		; puts (do) into the dictionary 16736 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16744 */
	{.type Absolute, {.p 0}},		/* dd 0			; ( -- 0 ) 16752 */
	{.type FromH0, {.p C_here}, .src = "dd C_here		; ( 0 -- 0 here1 )"},		/* dd C_here		; ( 0 -- 0 here1 ) 16760 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16768 */
	{.type IHeader, {.hdr { 4, "loop", /* CI_loop = 16784 */ colon }}}, /* CIENTRY "loop" loop 4 ; ( 0 here1 -- ) h 16792 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16800 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop		; ( 0 here1 -- 0 here1 (loop) )"},		/* dd M_doloop		; ( 0 here1 -- 0 here1 (loop) ) 16808 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 )"},		/* dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 ) 16816 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 )"},		/* dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 ) 16824 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 16832 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16840 */
	{.type FromH0, {.p L234}, .src = "dd L234"},		/* dd L234 16848 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16856 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16864 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16872 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16880 */
	{.type IHeader, {.hdr { 5, "+loop", /* CI_ploop = 16896 */ colon }}}, /* CIENTRY "+loop" ploop 5 h 16904 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16912 */
	{.type FromH0, {.p M_doploop}, .src = "dd M_doploop"},		/* dd M_doploop 16920 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16928 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16936 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 16944 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16952 */
	{.type FromH0, {.p L236}, .src = "dd L236"},		/* dd L236 16960 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16968 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16976 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16984 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16992 */
	{.type Header, {.hdr { 3, "w/o", /* C_wo = 17008 */ colon }}}, /* CENTRY "w/o" wo 3 h 17016 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17024 */
	{.type Absolute, {.p 1}},		/* dd 1 17032 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17040 */
	{.type Absolute, {.p 512}},		/* dd 512 17048 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 17056 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17064 */
	{.type Absolute, {.p 64}},		/* dd 64 17072 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 17080 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17088 */
	{.type Header, {.hdr { 3, "r/o", /* C_ro = 17104 */ colon }}}, /* CENTRY "r/o" ro 3 h 17112 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17120 */
	{.type Absolute, {.p 0}},		/* dd 0 17128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17136 */
	{.type Header, {.hdr { 3, "r/w", /* C_rw = 17152 */ colon }}}, /* CENTRY "r/w" rw 3 h 17160 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17168 */
	{.type Absolute, {.p 2}},		/* dd 2 17176 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17184 */
	{.type Header, {.hdr { 9, "open-file", /* C_open_file = 17208 */ colon }}}, /* CENTRY "open-file" open_file 9 ; ( a n mode -- fd ioresult ) h 17216 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n mode -- a n ) (R -- mode)"},		/* dd M_rpush	; ( a n mode -- a n ) (R -- mode) 17224 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( a n -- a n padaddr)"},		/* dd C_pad	; ( a n -- a n padaddr) 17232 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17240 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( a n padaddr --  a n padaddr 1024 ) 17248 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( a n padaddr+1024 --  a n padaddr+1024 )"},		/* dd M_plus	; ( a n padaddr+1024 --  a n padaddr+1024 ) 17256 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n padaddr+1024 --  a padaddr+1024 n )"},		/* dd M_xswap	; ( a n padaddr+1024 --  a padaddr+1024 n ) 17264 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a padaddr+1024 n --  a padaddr+1024 n n )"},		/* dd M_dup	; ( a padaddr+1024 n --  a padaddr+1024 n n ) 17272 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a padaddr+1024 n n --  a padaddr+1024 n ) (R mode -- mode n )"},		/* dd M_rpush	; ( a padaddr+1024 n n --  a padaddr+1024 n ) (R mode -- mode n ) 17280 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; moves the filename from a to paddaddr+1024"},		/* dd M_cmove	; moves the filename from a to paddaddr+1024 17288 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17296 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- 0 ) 17304 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( 0 -- 0 n ) (R mode n -- mode)"},		/* dd M_rpop	; ( 0 -- 0 n ) (R mode n -- mode) 17312 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( 0 n -- 0 n padaddr)"},		/* dd C_pad	; ( 0 n -- 0 n padaddr) 17320 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 n padaddr -- 0 padaddr+n )"},		/* dd M_plus	; ( 0 n padaddr -- 0 padaddr+n ) 17328 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17336 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( 0 padaddr+n --  0 padaddr+n 1024 ) 17344 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n 1024 --  0 padaddr+n+1024 )"},		/* dd M_plus	; ( 0 padaddr+n 1024 --  0 padaddr+n+1024 ) 17352 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; ( 0 padaddr+n 1024 --   ) makes the filename to a null terminated string"},		/* dd M_cstore	; ( 0 padaddr+n 1024 --   ) makes the filename to a null terminated string 17360 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 17368 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17376 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( -- padaddr 1024 ) 17384 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( padaddr 1024 -- padaddr+1024 )"},		/* dd M_plus	; ( padaddr 1024 -- padaddr+1024 ) 17392 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 -- padaddr+1024 mode) (R mode -- )"},		/* dd M_rpop	; ( padaddr+1024 -- padaddr+1024 mode) (R mode -- ) 17400 */
	{.type FromH0, {.p M_sysopen}, .src = "dd M_sysopen"},		/* dd M_sysopen 17408 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17416 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17424 */
	{.type Absolute, {.p -1}},		/* dd -1 17432 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 17440 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17448 */
	{.type Header, {.hdr { 10, "close-file", /* C_close_file = 17472 */ colon }}}, /* CENTRY "close-file" close_file 10 ; ( fd -- ioresult ) h 17480 */
	{.type FromH0, {.p M_sysclose}, .src = "dd M_sysclose"},		/* dd M_sysclose 17488 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 17496 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17504 */
	{.type Header, {.hdr { 9, "read-file", /* C_read_file = 17528 */ colon }}}, /* CENTRY "read-file" read_file 9 ; ( a n fd -- n2 ioresult ) h 17536 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( n fd a )"},		/* dd C_rot	; ( n fd a ) 17544 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( fd a n )"},		/* dd C_rot	; ( fd a n ) 17552 */
	{.type FromH0, {.p M_sysread}, .src = "dd M_sysread"},		/* dd M_sysread 17560 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17568 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17576 */
	{.type Absolute, {.p -1}},		/* dd -1 17584 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17592 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17600 */
	{.type Header, {.hdr { 10, "write-file", /* C_write_file = 17624 */ colon }}}, /* CENTRY "write-file" write_file 10 ; ( a n fd -- ioresult ) h 17632 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( n fd a )"},		/* dd C_rot	; ( n fd a ) 17640 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( fd a n )"},		/* dd C_rot	; ( fd a n ) 17648 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 17656 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17664 */
	{.type Absolute, {.p -1}},		/* dd -1 17672 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17680 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17688 */
	{.type Header, {.hdr { 15, "reposition-file", /* C_reposition_file = 17712 */ colon }}}, /* CENTRY "reposition-file" reposition_file 15 ; ( type n fd -- ioresult ) h 17720 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap		; ( type fd n )"},		/* dd M_xswap		; ( type fd n ) 17728 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot		; ( fd n type )"},		/* dd C_rot		; ( fd n type ) 17736 */
	{.type FromH0, {.p M_sysseek}, .src = "dd M_sysseek"},		/* dd M_sysseek 17744 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17752 */
	{.type Absolute, {.p -1}},		/* dd -1 17760 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17768 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17776 */
	{.type Header, {.hdr { 7, "?fcheck", /* C_qfcheck = 17792 */ colon }}}, /* CENTRY "?fcheck" qfcheck 7 h 17800 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 17808 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 17816 */
	{.type FromH0, {.p L246}, .src = "dd L246"},		/* dd L246 17824 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 17832 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17840 */
	{.type FromH0, {.p L247}, .src = "dd L247"},		/* dd L247 17848 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17856 */
	{.type Absolute, {.p 9}},		/* dd 9 17864 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 17872 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 17880 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 17888 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17896 */
	{.type Header, {.hdr { 11, "create-file", /* C_create_file = 17920 */ colon }}}, /* CENTRY "create-file" create_file 11 ; ( a n mode perm -- fd ioresult ) not part of the original ff. could move this to a forth file. h 17928 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n mode ) (R perm)"},		/* dd M_rpush	; ( a n mode ) (R perm) 17936 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n ) (R perm mode)"},		/* dd M_rpush	; ( a n ) (R perm mode) 17944 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( a n padaddr)"},		/* dd C_pad	; ( a n padaddr) 17952 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17960 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( a n padaddr 1024 ) 17968 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( a n padaddr+1024 )"},		/* dd M_plus	; ( a n padaddr+1024 ) 17976 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a padaddr+1024 n )"},		/* dd M_xswap	; ( a padaddr+1024 n ) 17984 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a padaddr+1024 n n )"},		/* dd M_dup	; ( a padaddr+1024 n n ) 17992 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n )"},		/* dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n ) 18000 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; moves the filename from a to paddaddr+1024"},		/* dd M_cmove	; moves the filename from a to paddaddr+1024 18008 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18016 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( 0 ) 18024 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( 0 n ) (R perm mode)"},		/* dd M_rpop	; ( 0 n ) (R perm mode) 18032 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( 0 n padaddr)"},		/* dd C_pad	; ( 0 n padaddr) 18040 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n )"},		/* dd M_plus	; ( 0 padaddr+n ) 18048 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18056 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( 0 padaddr+n 1024 ) 18064 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n+1024 )"},		/* dd M_plus	; ( 0 padaddr+n+1024 ) 18072 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; ( ) makes the filename to a null terminated string"},		/* dd M_cstore	; ( ) makes the filename to a null terminated string 18080 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 18088 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18096 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( padaddr 1024 ) 18104 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( padaddr+1024 )"},		/* dd M_plus	; ( padaddr+1024 ) 18112 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 mode) (R perm )"},		/* dd M_rpop	; ( padaddr+1024 mode) (R perm ) 18120 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 mode perm ) (R )"},		/* dd M_rpop	; ( padaddr+1024 mode perm ) (R ) 18128 */
	{.type FromH0, {.p M_syscreate}, .src = "dd M_syscreate"},		/* dd M_syscreate 18136 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 18144 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18152 */
	{.type Absolute, {.p -1}},		/* dd -1 18160 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 18168 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18176 */
	{.type Header, {.hdr { 3, "bye", /* C_bye = 18192 */ colon }}}, /* CENTRY "bye" bye 3 h 18200 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18208 */
	{.type Absolute, {.p 0}},		/* dd 0 18216 */
	{.type FromH0, {.p M_terminate}, .src = "dd M_terminate"},		/* dd M_terminate 18224 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18232 */
	{.type Header, {.hdr { 7, "include", /* C_include = 18248 */ colon }}}, /* CENTRY "include" include 7 h 18256 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 18264 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 18272 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 18280 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 18288 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 18296 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 18304 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18312 */
	{.type FromH0, {.p C_save_input}, .src = "dd C_save_input"},		/* dd C_save_input 18320 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 18328 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 18336 */
	{.type FromH0, {.p C_ro}, .src = "dd C_ro"},		/* dd C_ro 18344 */
	{.type FromH0, {.p C_open_file}, .src = "dd C_open_file"},		/* dd C_open_file 18352 */
	{.type FromH0, {.p C_qfcheck}, .src = "dd C_qfcheck"},		/* dd C_qfcheck 18360 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18368 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18376 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18384 */
	{.type Header, {.hdr { 5, "crash", /* C_crash = 18400 */ colon }}}, /* CENTRY "crash" crash 5 h 18408 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18416 */
	{.type FromH0, {.p L251}, .src = "dd L251"},		/* dd L251 18424 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18432 */
	{.type Absolute, {.p 30}},		/* dd 30 18440 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 18448 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 18456 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 18464 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18472 */
	{.type Header, {.hdr { 4, "quit", /* C_quit = 18488 */ colon }}}, /* CENTRY "quit" quit 4 ; interpreter loop h 18496 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 18504 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 18512 */
	{.type FromH0, {.p C_query}, .src = "dd C_query"},		/* dd C_query 18520 */
/* ; dd MV_toLimit	; show the line read, for debugging *//* ; dd M_fetch *//* ; dd M_Tib *//* ; dd MC_STDOUT *//* ; dd M_fswrite *//* ; dd M_drop		; drop the return value of write *//* ; dd C_cr *//* ; dd C_space */	{.type FromH0, {.p C_interpret}, .src = "dd C_interpret"},		/* dd C_interpret 18528 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 18536 */
	{.type FromH0, {.p L253}, .src = "dd L253"},		/* dd L253 18544 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed?"},		/* dd M_exitcolon	; why is this needed? 18552 */
	{.type Header, {.hdr { 7, "(abort)", /* C_parenabort = 18568 */ colon }}}, /* CENTRY "(abort)" parenabort 7 ; TODO correct below stack notations h 18576 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State	; ( mv_State -- )"},		/* dd MV_State	; ( mv_State -- ) 18584 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off sets variable state = 0"},		/* dd C_off	; off sets variable state = 0 18592 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 18600 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18608 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18616 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 18624 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 18632 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18640 */
	{.type FromH0, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 18648 */
	{.type FromH0, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 18656 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18664 */
	{.type FromH0, {.p C_default_input}, .src = "dd C_default_input"},		/* dd C_default_input 18672 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit resets stacks and is the interpreter loop"},		/* dd C_quit	; quit resets stacks and is the interpreter loop 18680 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed? quit does not return unless it breaks"},		/* dd M_exitcolon	; why is this needed? quit does not return unless it breaks 18688 */
	{.type Header, {.hdr { 7, "oldboot", /* C_oldboot = 18704 */ colon }}}, /* CENTRY "oldboot" oldboot 7 ; TODO correct below stack notations and this is obsolete. leaving it here for reference until it all works well h 18712 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset"},		/* dd M_reset 18720 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end"},		/* dd M_clear	; SP = sstack_end 18728 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr	; (D -- FFEND)"},		/* dd M_stackptr	; (D -- FFEND) 18736 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 18744 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; s0 = FFEND"},		/* dd M_store	; s0 = FFEND 18752 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp	; heaptop = heapend"},		/* dd M_Dp	; heaptop = heapend 18760 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( heapend -- )"},		/* dd M_fetch	; ( heapend -- ) 18768 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18776 */
	{.type Absolute, {.p 1}},		/* dd 1		; ( heapend 1 -- ) 18784 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells	; cells ( heapend 8 -- )"},		/* dd C_cells	; cells ( heapend 8 -- ) 18792 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( heapend-8 -- )"},		/* dd M_minus	; ( heapend-8 -- ) 18800 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( contents_from_heapend-8 -- )"},		/* dd M_fetch	; ( contents_from_heapend-8 -- ) 18808 */
	{.type FromH0, {.p M_Fthargs}, .src = "dd M_Fthargs	; variable args"},		/* dd M_Fthargs	; variable args 18816 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; args = contents_from_heapend-8"},		/* dd M_store	; args = contents_from_heapend-8 18824 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18832 */
	{.type FromH0, {.p C_parenabort}, .src = "dd C_parenabort ; ( (abort) -- )"},		/* dd C_parenabort ; ( (abort) -- ) 18840 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec	; variable abortvec"},		/* dd MV_Abortvec	; variable abortvec 18848 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable abortvec = (abort) code address"},		/* dd M_store	; variable abortvec = (abort) code address 18856 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb	; constant puts address of wordbuffer on the top of stack"},		/* dd M_Wordb	; constant puts address of wordbuffer on the top of stack 18864 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf	; variable wordbuf"},		/* dd MV_Wordbuf	; variable wordbuf 18872 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable wordbuf = address of wordbuffer"},		/* dd M_store	; variable wordbuf = address of wordbuffer 18880 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top of stack"},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 18888 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; variable sourcebuf"},		/* dd MV_Sourcebuf	; variable sourcebuf 18896 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable sourcebuf = address of tibuffer"},		/* dd M_store	; variable sourcebuf = address of tibuffer 18904 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18912 */
	{.type Absolute, {.p 0}},		/* dd 0 18920 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18928 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdin = 0"},		/* dd M_store	; stdin = 0 18936 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18944 */
	{.type Absolute, {.p 1}},		/* dd 1 18952 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 18960 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdout = 1"},		/* dd M_store	; stdout = 1 18968 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 18976 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off stores 0 at state"},		/* dd C_off	; off stores 0 at state 18984 */
	{.type FromH0, {.p C_decimal}, .src = "dd C_decimal	; decimal setting base = 0"},		/* dd C_decimal	; decimal setting base = 0 18992 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit"},		/* dd C_quit	; quit 19000 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19008 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal	; test code"},		/* dd M_literal	; test code 19016 */
	{.type Absolute, {.p 66}},		/* dd 66 19024 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 19032 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 19040 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 19048 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 19056 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19064 */
	{.type Absolute, {.p 1}},		/* dd 1 19072 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 19080 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 19088 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 19096 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 19104 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19112 */
	{.type Absolute, {.p 1}},		/* dd 1 19120 */
	{.type FromH0, {.p M_sysread}, .src = "dd M_sysread"},		/* dd M_sysread 19128 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of read"},		/* dd M_drop		; drop the return value of read 19136 */
	{.type Header, {.hdr { 7, "do-args", /* C_do_args = 19152 */ colon }}}, /* CENTRY "do-args" do_args 7 h 19160 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19168 */
	{.type Absolute, {.p 0}},		/* dd 0 19176 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec	; no more refills"},		/* dd MV_Acceptvec	; no more refills 19184 */
	{.type FromH0, {.p M_store}, .src = "dd M_store 	; C_off	; Acceptvec == 0, reading from a buffer. no more refills."},		/* dd M_store 	; C_off	; Acceptvec == 0, reading from a buffer. no more refills. 19192 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19200 */
	{.type Absolute, {.p 0}},		/* dd 0 19208 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 19216 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; >in = 0"},		/* dd M_store	; >in = 0 19224 */
	{.type FromH0, {.p M_Fthargs}, .src = "dd M_Fthargs	; ( a )"},		/* dd M_Fthargs	; ( a ) 19232 */
	{.type FromH0, {.p C_count}, .src = "dd C_count	; ( a+1 n )"},		/* dd C_count	; ( a+1 n ) 19240 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 19248 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; ( a+1 ) >limit = n"},		/* dd M_store	; ( a+1 ) >limit = n 19256 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 19264 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; sourcebuf = a+1"},		/* dd M_store	; sourcebuf = a+1 19272 */
	{.type FromH0, {.p C_interpret}, .src = "dd C_interpret"},		/* dd C_interpret 19280 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19288 */
	{.type Header, {.hdr { 4, "boot", /* C_boot = 19304 */ colon }}}, /* CENTRY "boot" boot 4 h 19312 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 19320 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 19328 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19336 */
	{.type FromH0, {.p C_parenabort}, .src = "dd C_parenabort ; ( (abort) -- )"},		/* dd C_parenabort ; ( (abort) -- ) 19344 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec	; variable that puts (abort) code address on the stack"},		/* dd MV_Abortvec	; variable that puts (abort) code address on the stack 19352 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable abortvec = (abort) code address"},		/* dd M_store	; variable abortvec = (abort) code address 19360 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb	; variable puts address of wordbuffer on the top of stack"},		/* dd M_Wordb	; variable puts address of wordbuffer on the top of stack 19368 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf ; variable wordbuf"},		/* dd MV_Wordbuf ; variable wordbuf 19376 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable wordbuf = address of wordbuffer"},		/* dd M_store	; variable wordbuf = address of wordbuffer 19384 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 19392 */
	{.type FromH0, {.p MV_H0}, .src = "dd MV_H0	; H0 = here at startup"},		/* dd MV_H0	; H0 = here at startup 19400 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 19408 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 19416 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 19424 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdin = 0"},		/* dd M_store	; stdin = 0 19432 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 19440 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 19448 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 19456 */
	{.type FromH0, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 19464 */
	{.type FromH0, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 19472 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 19480 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 19488 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off stores 0 at state"},		/* dd C_off	; off stores 0 at state 19496 */
	{.type FromH0, {.p C_decimal}, .src = "dd C_decimal	; decimal sets base = 10"},		/* dd C_decimal	; decimal sets base = 10 19504 */
	{.type FromH0, {.p C_default_input}, .src = "dd C_default_input	; read lines from stdin, if args do not set one up"},		/* dd C_default_input	; read lines from stdin, if args do not set one up 19512 */
	{.type FromH0, {.p M_Fthargs}, .src = "dd M_Fthargs"},		/* dd M_Fthargs 19520 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 19528 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 19536 */
	{.type FromH0, {.p L260}, .src = "dd L260	; fetched 0, no args, go to the interpreter loop"},		/* dd L260	; fetched 0, no args, go to the interpreter loop 19544 */
	{.type FromH0, {.p C_do_args}, .src = "dd C_do_args	; process args"},		/* dd C_do_args	; process args 19552 */
/* ; dd C_default_input	; do not do this as it will override any input streams set up by the args */	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; interpreter loop when there are no args or fall through after processing args"},		/* dd C_quit	; interpreter loop when there are no args or fall through after processing args 19560 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19568 */
	{.type Chars, {.str "unable to restore input"}},		/* 19592 */
	{.type Chars, {.str " Q?"}},		/* 19596 */
	{.type Chars, {.str " stack underflow"}},		/* 19613 */
	{.type Chars, {.str " I?"}},		/* 19617 */
	{.type Chars, {.str " C?"}},		/* 19621 */
	{.type Chars, {.str "I/O error"}},		/* 19631 */
	{.type Chars, {.str "uninitialized execution vector"}},		/* 19662 */
	{.type Chars, {.str " ok"}},		/* 19666 */
	{.type Chars, {.str "input line is longer than 4096 bytes"}},		/* 19703 */
	{.type Chars, {.str "read error"}},		/* 19714 */
};

