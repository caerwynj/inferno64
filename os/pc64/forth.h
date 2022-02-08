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
	M_mmap = 112,
	M_terminate = 136,
	M_fthdump = 160,
	M_clear = 184,
	M_reset = 208,
	M_exitcolon = 232,
	M_literal = 264,
	M_sliteral = 296,
	M_doinit = 320,
	M_doloop = 344,
	M_doploop = 368,
	M_rfetch = 392,
	M_rpop = 416,
	M_rpush = 440,
	M_i = 464,
	M_j = 488,
	M_plus = 512,
	M_minus = 536,
	M_multiply = 560,
	M_cjump = 584,
	M_jump = 608,
	M_slashmod = 632,
	M_uslashmod = 656,
	M_binand = 680,
	M_binor = 704,
	M_binxor = 728,
	M_xswap = 752,
	M_drop = 776,
	M_dup = 800,
	M_over = 824,
	M_equal = 848,
	M_greater = 872,
	M_less = 896,
	M_lshift = 920,
	M_rshift = 944,
	M_rshifta = 968,
	M_execute = 992,
	M_unloop = 1016,
	M_cmove = 1040,
	M_cmoveb = 1064,
	M_variable = 1096,
	M_constant = 1128,
	M_colon = 1152,
	M_dodoes = 1176,
	M_cas = 1200,
	M_deferred = 1232,
	M_sysbind = 1256,
	M_sysclose = 1288,
	M_syscreate = 1320,
	M_sysmount = 1352,
	M_sysopen = 1376,
	M_sysread = 1400,
	M_sysseek = 1424,
	M_syswrite = 1456,
	MC_STDIN = 1480,
	MC_STDOUT = 1512,
	MC_STDERR = 1544,
	MV_Iobuf = 1576,
	MV_Sourcebuf = 1616,
	MV_Wordbuf = 1648,
	MV_toIn = 1680,
	MV_toLimit = 1712,
	MV_Findadr = 1744,
	MV_Acceptvec = 1784,
	MV_Searchlen = 1824,
	MV_Base = 1856,
	MV_toNum = 1888,
	MV_State = 1920,
	MV_Abortvec = 1960,
	MV_Infd = 1992,
	MV_Outfd = 2024,
	MV_Errfd = 2056,
	MV_Eof = 2088,
	MV_Ninputs = 2120,
	MV_H0 = 2152,
	M_Dp = 2184,
	M_Dtop = 2208,
	M_Vp = 2232,
	M_S0 = 2256,
	M_stackptr = 2280,
	M_Wordb = 2304,
	M_Tib = 2328,
	M_Fthargs = 2352,
	C_false = 2376,
	C_true = 2424,
	C_bl = 2472,
	C_on = 2520,
	C_off = 2584,
	C_tobody = 2648,
	C_aligned = 2704,
	C_cells = 2784,
	C_cellplus = 2840,
	C_depth = 2904,
	C_nip = 3008,
	C_rot = 3056,
	C_2drop = 3120,
	C_2dup = 3168,
	C_2nip = 3216,
	C_2swap = 3264,
	C_qdup = 3328,
	L20 = 3400,
	C_pick = 3424,
	L22 = 3528,
	L23 = 3536,
	C_tuck = 3560,
	C_divides = 3624,
	C_plusstore = 3672,
	C_invert = 3752,
	C_mod = 3808,
	C_1plus = 3856,
	C_1minus = 3912,
	C_negate = 3968,
	C_2multiplies = 4032,
	C_2divides = 4088,
	C_0eq = 4144,
	C_0lt = 4200,
	C_0gt = 4256,
	C_neq = 4312,
	C_0neq = 4360,
	C_max = 4416,
	L40 = 4480,
	L41 = 4488,
	C_min = 4512,
	L43 = 4576,
	L44 = 4584,
	C_signum = 4608,
	L46 = 4688,
	L48 = 4744,
	L49 = 4760,
	L47 = 4760,
	C_within = 4784,
	C_abs = 4888,
	L52 = 4936,
	C_key = 4960,
	L78 = 5088,
	L79 = 5104,
	C_emit = 5128,
	C_type = 5232,
	C_cr = 5328,
	C_space = 5384,
	C_emits = 5432,
	L85 = 5440,
	L86 = 5504,
	C_spaces = 5536,
	C_count = 5592,
	C_compare = 5736,
	L55 = 5808,
	L56 = 5944,
	C_erase = 6024,
	L58 = 6056,
	C_fill = 6144,
	L60 = 6184,
	C_blank = 6272,
	C_search = 6320,
	L64 = 6424,
	L65 = 6608,
	C_here = 6672,
	C_vhere = 6720,
	C_comma = 6768,
	C_c = 6848,
	C_allot = 6928,
	C_vallot = 6976,
	C_pad = 7024,
	C_align = 7088,
	C_unused = 7152,
	C_fromhash = 7216,
	C_hash = 7296,
	L92 = 7448,
	L93 = 7472,
	C_hashs = 7552,
	L95 = 7560,
	L96 = 7608,
	C_hashfrom = 7632,
	C_hold = 7744,
	C_sign = 7848,
	L100 = 7904,
	C_dot = 7928,
	C_dotr = 8032,
	C_hex = 8192,
	C_decimal = 8256,
	C_digit = 8320,
	L106 = 8432,
	L108 = 8536,
	L110 = 8640,
	L111 = 8664,
	L109 = 8664,
	L107 = 8664,
	L112 = 8736,
	L113 = 8752,
	C_number = 8776,
	L115 = 8912,
	L116 = 8944,
	L117 = 9008,
	L118 = 9112,
	L119 = 9168,
	C_abort = 9256,
	C_source = 9312,
	C_current_input = 9368,
	C_save_input = 9448,
	C_default_input = 9584,
	C_restore_input = 9736,
	L132 = 9960,
	C_qrestore_input = 10008,
	L136 = 10136,
	C_next_input = 10168,
	L139 = 10264,
	L140 = 10288,
	C_parse = 10312,
	L142 = 10352,
	L143 = 10480,
	C_word = 10624,
	L145 = 10640,
	L146 = 10736,
	C_accept = 10776,
	L300 = 10840,
	C_accept_line = 10912,
	L303 = 11120,
	L301 = 11136,
	L302 = 11192,
	C_accept_key = 11240,
	L148 = 11280,
	L150 = 11440,
	L149 = 11504,
	C_query = 11552,
	L152 = 11696,
	L153 = 11728,
	C_refill = 11752,
	L155 = 11808,
	C_findname = 11856,
	L158 = 11896,
	L160 = 12008,
	L162 = 12136,
	L161 = 12144,
	L159 = 12160,
	C_find = 12208,
	L165 = 12400,
	L166 = 12416,
	L164 = 12440,
	L167 = 12448,
	C_single_quote = 12472,
	L169 = 12608,
	C_qstack = 12632,
	L172 = 12736,
	C_interpret = 12808,
	L175 = 12816,
	L177 = 12928,
	L179 = 13040,
	L178 = 13040,
	L176 = 13056,
	C_create = 13088,
	C_variable = 13336,
	C_constant = 13432,
	C_immediate = 13560,
	C_tocfa = 13672,
	C_compile = 13752,
	L189 = 13880,
	L190 = 13896,
	L188 = 13912,
	L192 = 14040,
	L194 = 14072,
	L191 = 14072,
	C_close_bracket = 14096,
	L196 = 14120,
	L197 = 14208,
	L198 = 14232,
	L199 = 14264,
	CI_open_bracket = 14288,
	C_smudge = 14336,
	C_reveal = 14448,
	C_colon = 14568,
	CI_semicolon = 14696,
	CI_recurse = 14776,
	C_char = 14848,
	C_literal = 14912,
	C_sliteral = 14984,
	C_string = 15152,
	CI_char_brackets = 15264,
	CI_quote_brackets = 15336,
	CI_openparen = 15384,
	CI_backslash = 15448,
	L214 = 15528,
	C_qabort_parens = 15592,
	L217 = 15672,
	L218 = 15680,
	CI_abort_double_quote = 15704,
	C_double_quote = 15768,
	C_cdouble_quote = 15896,
	CI_sdouble_quote = 16032,
	CI_dotstr = 16072,
	CI_if = 16136,
	CI_else = 16224,
	CI_then = 16352,
	CI_begin = 16408,
	CI_again = 16448,
	CI_until = 16512,
	CI_while = 16576,
	CI_repeat = 16664,
	CI_do = 16760,
	CI_loop = 16840,
	L234 = 16928,
	CI_ploop = 16952,
	L236 = 17040,
	C_wo = 17064,
	C_ro = 17160,
	C_rw = 17208,
	C_cstring = 17256,
	C_cstring0 = 17440,
	C_cstring1 = 17504,
	C_open_file = 17568,
	C_close_file = 17672,
	C_read_file = 17728,
	C_write_file = 17824,
	C_reposition_file = 17912,
	C_qfcheck = 17992,
	L246 = 18088,
	C_create_file = 18120,
	C_bye = 18392,
	C_include = 18448,
	L248 = 18544,
	C_crash = 18672,
	C_quit = 18760,
	L253 = 18784,
	C_parenabort = 18840,
	C_oldboot = 18976,
	C_do_args = 19424,
	C_boot = 19576,
	L260 = 19824,
	L137 = 19840,
	L170 = 19864,
	L173 = 19868,
	L180 = 19885,
	L193 = 19889,
	L247 = 19893,
	L251 = 19903,
	L255 = 19934,
	L304 = 19938,
	L305 = 19975,
};
extern void *sliteral(void);
extern void *syscreate(void);
extern void *cjump(void);
extern void *syswrite(void);
extern void *i(void);
extern void *equal(void);
extern void *j(void);
extern void *drop(void);
extern void *rpop(void);
extern void *stackptr(void);
extern void *sysseek(void);
extern void *deferred(void);
extern void *cas(void);
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
extern void *sysbind(void);
extern void *cfetch(void);
extern void *sysmount(void);
extern void *constant(void);
extern void *variable(void);
extern void *fetch(void);
extern void *doloop(void);
extern void *mmap(void);
extern void *binxor(void);
extern void *sysread(void);
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
	{.type Header, {.hdr { 1, "@", /* M_fetch = 16 */ fetch }}}, /* MENTRY "@" fetch 1 h 24 */
	{.type Header, {.hdr { 1, "!", /* M_store = 40 */ store }}}, /* MENTRY "!" store 1 h 48 */
	{.type Header, {.hdr { 2, "c@", /* M_cfetch = 64 */ cfetch }}}, /* MENTRY "c@" cfetch 2 h 72 */
	{.type Header, {.hdr { 2, "c!", /* M_cstore = 88 */ cstore }}}, /* MENTRY "c!" cstore 2 h 96 */
	{.type Header, {.hdr { 4, "mmap", /* M_mmap = 112 */ mmap }}}, /* MENTRY "mmap" mmap 4 h 120 */
	{.type Header, {.hdr { 4, "halt", /* M_terminate = 136 */ terminate }}}, /* MENTRY "halt" terminate 4 h 144 */
	{.type Header, {.hdr { 4, "dump", /* M_fthdump = 160 */ fthdump }}}, /* MENTRY "dump" fthdump 4 h 168 */
	{.type Header, {.hdr { 5, "clear", /* M_clear = 184 */ clear }}}, /* MENTRY "clear" clear 5 h 192 */
	{.type Header, {.hdr { 5, "reset", /* M_reset = 208 */ reset }}}, /* MENTRY "reset" reset 5 h 216 */
	{.type Header, {.hdr { 4, "exit", /* M_exitcolon = 232 */ exitcolon }}}, /* MENTRY "exit" exitcolon 4 h 240 */
	{.type Header, {.hdr { 9, "(literal)", /* M_literal = 264 */ literal }}}, /* MENTRY "(literal)" literal 9 h 272 */
	{.type Header, {.hdr { 10, "(sliteral)", /* M_sliteral = 296 */ sliteral }}}, /* MENTRY "(sliteral)" sliteral 10 h 304 */
	{.type Header, {.hdr { 4, "(do)", /* M_doinit = 320 */ doinit }}}, /* MENTRY "(do)" doinit 4 h 328 */
	{.type Header, {.hdr { 6, "(loop)", /* M_doloop = 344 */ doloop }}}, /* MENTRY "(loop)" doloop 6 h 352 */
	{.type Header, {.hdr { 7, "(+loop)", /* M_doploop = 368 */ doploop }}}, /* MENTRY "(+loop)" doploop 7 h 376 */
	{.type Header, {.hdr { 2, "r@", /* M_rfetch = 392 */ rfetch }}}, /* MENTRY "r@" rfetch 2 h 400 */
	{.type Header, {.hdr { 2, "r>", /* M_rpop = 416 */ rpop }}}, /* MENTRY "r>" rpop 2 h 424 */
	{.type Header, {.hdr { 2, ">r", /* M_rpush = 440 */ rpush }}}, /* MENTRY ">r" rpush 2 h 448 */
	{.type Header, {.hdr { 1, "i", /* M_i = 464 */ i }}}, /* MENTRY "i" i 1 h 472 */
	{.type Header, {.hdr { 1, "j", /* M_j = 488 */ j }}}, /* MENTRY "j" j 1 h 496 */
	{.type Header, {.hdr { 1, "+", /* M_plus = 512 */ plus }}}, /* MENTRY "+" plus 1 h 520 */
	{.type Header, {.hdr { 1, "-", /* M_minus = 536 */ minus }}}, /* MENTRY "-" minus 1 h 544 */
	{.type Header, {.hdr { 1, "*", /* M_multiply = 560 */ multiply }}}, /* MENTRY "*" multiply 1 h 568 */
	{.type Header, {.hdr { 4, "(if)", /* M_cjump = 584 */ cjump }}}, /* MENTRY "(if)" cjump 4 h 592 */
	{.type Header, {.hdr { 6, "(else)", /* M_jump = 608 */ jump }}}, /* MENTRY "(else)" jump 6 h 616 */
	{.type Header, {.hdr { 4, "/mod", /* M_slashmod = 632 */ slashmod }}}, /* MENTRY "/mod" slashmod 4 h 640 */
	{.type Header, {.hdr { 5, "u/mod", /* M_uslashmod = 656 */ uslashmod }}}, /* MENTRY "u/mod" uslashmod 5 h 664 */
	{.type Header, {.hdr { 3, "and", /* M_binand = 680 */ binand }}}, /* MENTRY "and" binand 3 h 688 */
	{.type Header, {.hdr { 2, "or", /* M_binor = 704 */ binor }}}, /* MENTRY "or" binor 2 h 712 */
	{.type Header, {.hdr { 3, "xor", /* M_binxor = 728 */ binxor }}}, /* MENTRY "xor" binxor 3 h 736 */
	{.type Header, {.hdr { 4, "swap", /* M_xswap = 752 */ xswap }}}, /* MENTRY "swap" xswap 4 h 760 */
	{.type Header, {.hdr { 4, "drop", /* M_drop = 776 */ drop }}}, /* MENTRY "drop" drop 4 h 784 */
	{.type Header, {.hdr { 3, "dup", /* M_dup = 800 */ dup }}}, /* MENTRY "dup" dup 3 h 808 */
	{.type Header, {.hdr { 4, "over", /* M_over = 824 */ over }}}, /* MENTRY "over" over 4 h 832 */
	{.type Header, {.hdr { 1, "=", /* M_equal = 848 */ equal }}}, /* MENTRY "=" equal 1 h 856 */
	{.type Header, {.hdr { 1, ">", /* M_greater = 872 */ greater }}}, /* MENTRY ">" greater 1 h 880 */
	{.type Header, {.hdr { 1, "<", /* M_less = 896 */ less }}}, /* MENTRY "<" less 1 h 904 */
	{.type Header, {.hdr { 6, "lshift", /* M_lshift = 920 */ lshift }}}, /* MENTRY "lshift" lshift 6 h 928 */
	{.type Header, {.hdr { 6, "rshift", /* M_rshift = 944 */ rshift }}}, /* MENTRY "rshift" rshift 6 h 952 */
	{.type Header, {.hdr { 7, "rshifta", /* M_rshifta = 968 */ rshifta }}}, /* MENTRY "rshifta" rshifta 7 h 976 */
	{.type Header, {.hdr { 7, "execute", /* M_execute = 992 */ execute }}}, /* MENTRY "execute" execute 7 h 1000 */
	{.type Header, {.hdr { 6, "unloop", /* M_unloop = 1016 */ unloop }}}, /* MENTRY "unloop" unloop 6 h 1024 */
	{.type Header, {.hdr { 5, "cmove", /* M_cmove = 1040 */ cmove }}}, /* MENTRY "cmove" cmove 5 h 1048 */
	{.type Header, {.hdr { 6, "cmove>", /* M_cmoveb = 1064 */ cmoveb }}}, /* MENTRY "cmove>" cmoveb 6 h 1072 */
	{.type Header, {.hdr { 10, "(variable)", /* M_variable = 1096 */ variable }}}, /* MENTRY "(variable)" variable 10 h 1104 */
	{.type Header, {.hdr { 10, "(constant)", /* M_constant = 1128 */ constant }}}, /* MENTRY "(constant)" constant 10 h 1136 */
	{.type Header, {.hdr { 3, "(:)", /* M_colon = 1152 */ colon }}}, /* MENTRY "(:)" colon 3 h 1160 */
	{.type Header, {.hdr { 6, "(does)", /* M_dodoes = 1176 */ dodoes }}}, /* MENTRY "(does)" dodoes 6 h 1184 */
	{.type Header, {.hdr { 3, "cas", /* M_cas = 1200 */ cas }}}, /* MENTRY "cas" cas 3 h 1208 */
	{.type Header, {.hdr { 10, "(deferred)", /* M_deferred = 1232 */ deferred }}}, /* MENTRY "(deferred)" deferred 10 h 1240 */
	{.type Header, {.hdr { 7, "sysbind", /* M_sysbind = 1256 */ sysbind }}}, /* MENTRY "sysbind" sysbind 7 h 1264 */
	{.type Header, {.hdr { 8, "sysclose", /* M_sysclose = 1288 */ sysclose }}}, /* MENTRY "sysclose" sysclose 8 h 1296 */
	{.type Header, {.hdr { 9, "syscreate", /* M_syscreate = 1320 */ syscreate }}}, /* MENTRY "syscreate" syscreate 9 h 1328 */
	{.type Header, {.hdr { 8, "sysmount", /* M_sysmount = 1352 */ sysmount }}}, /* MENTRY "sysmount" sysmount 8 h 1360 */
	{.type Header, {.hdr { 7, "sysopen", /* M_sysopen = 1376 */ sysopen }}}, /* MENTRY "sysopen" sysopen 7 h 1384 */
	{.type Header, {.hdr { 7, "sysread", /* M_sysread = 1400 */ sysread }}}, /* MENTRY "sysread" sysread 7 h 1408 */
	{.type Header, {.hdr { 7, "sysseek", /* M_sysseek = 1424 */ sysseek }}}, /* MENTRY "sysseek" sysseek 7 h 1432 */
	{.type Header, {.hdr { 8, "syswrite", /* M_syswrite = 1456 */ syswrite }}}, /* MENTRY "syswrite" syswrite 8 h 1464 */
	{.type Header, {.hdr { 5, "STDIN", /* MC_STDIN = 1480 */ constant }}}, /* MCENTRY "STDIN" STDIN 0 5		; 3 constants from here CAPITALS h 1488 */
	{.type Absolute, {.p 0}},		/* 1496 */
	{.type Header, {.hdr { 6, "STDOUT", /* MC_STDOUT = 1512 */ constant }}}, /* MCENTRY "STDOUT" STDOUT 1 6 h 1520 */
	{.type Absolute, {.p 1}},		/* 1528 */
	{.type Header, {.hdr { 6, "STDERR", /* MC_STDERR = 1544 */ constant }}}, /* MCENTRY "STDERR" STDERR 2 6 h 1552 */
	{.type Absolute, {.p 2}},		/* 1560 */
	{.type Header, {.hdr { 5, "Iobuf", /* MV_Iobuf = 1576 */ variable }}}, /* MVENTRY "Iobuf" Iobuf 0 5			; the values are not being used from the definition. All are initialized to 0. h 1584 */
	{.type FromV0, {.p 0 }},	/* 1592 0 */
	{.type Header, {.hdr { 9, "Sourcebuf", /* MV_Sourcebuf = 1616 */ variable }}}, /* MVENTRY "Sourcebuf" Sourcebuf 0 9	; is there a need for this? h 1624 */
	{.type FromV0, {.p 8 }},	/* 1632 8 */
	{.type Header, {.hdr { 7, "Wordbuf", /* MV_Wordbuf = 1648 */ variable }}}, /* MVENTRY "Wordbuf" Wordbuf 0 7		; is there a need for this? h 1656 */
	{.type FromV0, {.p 16 }},	/* 1664 16 */
	{.type Header, {.hdr { 3, ">In", /* MV_toIn = 1680 */ variable }}}, /* MVENTRY ">In" toIn 0 3 h 1688 */
	{.type FromV0, {.p 24 }},	/* 1696 24 */
	{.type Header, {.hdr { 6, ">Limit", /* MV_toLimit = 1712 */ variable }}}, /* MVENTRY ">Limit" toLimit 0 6 h 1720 */
	{.type FromV0, {.p 32 }},	/* 1728 32 */
	{.type Header, {.hdr { 7, "Findadr", /* MV_Findadr = 1744 */ variable }}}, /* MVENTRY "Findadr" Findadr 0 7 h 1752 */
	{.type FromV0, {.p 40 }},	/* 1760 40 */
	{.type Header, {.hdr { 9, "Acceptvec", /* MV_Acceptvec = 1784 */ variable }}}, /* MVENTRY "Acceptvec" Acceptvec 0 9 h 1792 */
	{.type FromV0, {.p 48 }},	/* 1800 48 */
	{.type Header, {.hdr { 9, "Searchlen", /* MV_Searchlen = 1824 */ variable }}}, /* MVENTRY "Searchlen" Searchlen 0 9 h 1832 */
	{.type FromV0, {.p 56 }},	/* 1840 56 */
	{.type Header, {.hdr { 4, "Base", /* MV_Base = 1856 */ variable }}}, /* MVENTRY "Base" Base 0 4 h 1864 */
	{.type FromV0, {.p 64 }},	/* 1872 64 */
	{.type Header, {.hdr { 4, ">Num", /* MV_toNum = 1888 */ variable }}}, /* MVENTRY ">Num" toNum 0 4 h 1896 */
	{.type FromV0, {.p 72 }},	/* 1904 72 */
	{.type Header, {.hdr { 5, "State", /* MV_State = 1920 */ variable }}}, /* MVENTRY "State" State 0 5 h 1928 */
	{.type FromV0, {.p 80 }},	/* 1936 80 */
	{.type Header, {.hdr { 8, "Abortvec", /* MV_Abortvec = 1960 */ variable }}}, /* MVENTRY "Abortvec" Abortvec 0 8	; not sure if these 3 can be constants instead? h 1968 */
	{.type FromV0, {.p 88 }},	/* 1976 88 */
	{.type Header, {.hdr { 4, "Infd", /* MV_Infd = 1992 */ variable }}}, /* MVENTRY "Infd" Infd 0 4 h 2000 */
	{.type FromV0, {.p 96 }},	/* 2008 96 */
	{.type Header, {.hdr { 5, "Outfd", /* MV_Outfd = 2024 */ variable }}}, /* MVENTRY "Outfd" Outfd 0 5 h 2032 */
	{.type FromV0, {.p 104 }},	/* 2040 104 */
	{.type Header, {.hdr { 5, "Errfd", /* MV_Errfd = 2056 */ variable }}}, /* MVENTRY "Errfd" Errfd 0 5 h 2064 */
	{.type FromV0, {.p 112 }},	/* 2072 112 */
	{.type Header, {.hdr { 3, "Eof", /* MV_Eof = 2088 */ variable }}}, /* MVENTRY "Eof" Eof 0 3 h 2096 */
	{.type FromV0, {.p 120 }},	/* 2104 120 */
	{.type Header, {.hdr { 7, "Ninputs", /* MV_Ninputs = 2120 */ variable }}}, /* MVENTRY "Ninputs" Ninputs 0 7 h 2128 */
	{.type FromV0, {.p 128 }},	/* 2136 128 */
	{.type Header, {.hdr { 2, "H0", /* MV_H0 = 2152 */ variable }}}, /* MVENTRY "H0" H0 0 2		; here at startup h 2160 */
	{.type FromV0, {.p 136 }},	/* 2168 136 */
/* ; cannot use H as it is nil in inferno, address where here (next available dictionary cell location) is stored *//* ; here = Dp @ */	{.type Header, {.hdr { 2, "Dp", /* M_Dp = 2184 */ Dp }}}, /* MENTRY "Dp" Dp 2		; here h 2192 */
	{.type Header, {.hdr { 4, "Dtop", /* M_Dtop = 2208 */ Dtop }}}, /* MENTRY "Dtop" Dtop 4	; last defined header h 2216 */
	{.type Header, {.hdr { 2, "Vp", /* M_Vp = 2232 */ Vp }}}, /* MENTRY "Vp" Vp 2		; here of the variables space h 2240 */
	{.type Header, {.hdr { 2, "S0", /* M_S0 = 2256 */ S0 }}}, /* MENTRY "S0" S0 2 h 2264 */
	{.type Header, {.hdr { 2, "s@", /* M_stackptr = 2280 */ stackptr }}}, /* MENTRY "s@" stackptr 2	; puts PSP on stack. Not a variable hence lower case. h 2288 */
	{.type Header, {.hdr { 5, "Wordb", /* M_Wordb = 2304 */ Wordb }}}, /* MENTRY "Wordb" Wordb 5 h 2312 */
	{.type Header, {.hdr { 3, "Tib", /* M_Tib = 2328 */ Tib }}}, /* MENTRY "Tib" Tib 3 h 2336 */
	{.type Header, {.hdr { 7, "Fthargs", /* M_Fthargs = 2352 */ Fthargs }}}, /* MENTRY "Fthargs" Fthargs 7 h 2360 */
	{.type Header, {.hdr { 5, "false", /* C_false = 2376 */ colon }}}, /* CENTRY "false" false 5 h 2384 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2392 */
	{.type Absolute, {.p 0}},		/* dd 0 2400 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2408 */
	{.type Header, {.hdr { 4, "true", /* C_true = 2424 */ colon }}}, /* CENTRY "true" true 4 h 2432 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2440 */
	{.type Absolute, {.p -1}},		/* dd -1 2448 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2456 */
	{.type Header, {.hdr { 2, "bl", /* C_bl = 2472 */ colon }}}, /* CENTRY "bl" bl 2 h 2480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2488 */
	{.type Absolute, {.p 32}},		/* dd 32 2496 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2504 */
	{.type Header, {.hdr { 2, "on", /* C_on = 2520 */ colon }}}, /* CENTRY "on" on 2 ; ( a -- ) (G stores -1 at a ) h 2528 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2536 */
	{.type Absolute, {.p -1}},		/* dd -1 2544 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2552 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2560 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2568 */
	{.type Header, {.hdr { 3, "off", /* C_off = 2584 */ colon }}}, /* CENTRY "off" off 3 ; ( a -- ) (G stores 0 at a ) h 2592 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2600 */
	{.type Absolute, {.p 0}},		/* dd 0 2608 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2616 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2624 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2632 */
	{.type Header, {.hdr { 5, ">body", /* C_tobody = 2648 */ colon }}}, /* CENTRY ">body" tobody 5 h 2656 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2664 */
	{.type Absolute, {.p 8}},		/* dd 8 2672 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2680 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2688 */
	{.type Header, {.hdr { 7, "aligned", /* C_aligned = 2704 */ colon }}}, /* CENTRY "aligned" aligned 7 ; align a number to a multiple of 8 h 2712 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2720 */
	{.type Absolute, {.p 7}},		/* dd 7 2728 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2736 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2744 */
	{.type Absolute, {.p -8}},		/* dd -8 2752 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 2760 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2768 */
	{.type Header, {.hdr { 5, "cells", /* C_cells = 2784 */ colon }}}, /* CENTRY "cells" cells 5 h 2792 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2800 */
	{.type Absolute, {.p 3}},		/* dd 3			; (index << 2) -> (index << 3) for amd64 2808 */
	{.type FromH0, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 2816 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2824 */
	{.type Header, {.hdr { 5, "cell+", /* C_cellplus = 2840 */ colon }}}, /* CENTRY "cell+" cellplus 5 h 2848 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2856 */
	{.type Absolute, {.p 1}},		/* dd 1 2864 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 2872 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2880 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2888 */
	{.type Header, {.hdr { 5, "depth", /* C_depth = 2904 */ colon }}}, /* CENTRY "depth" depth 5 h 2912 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 2920 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 2928 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 2936 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2944 */
	{.type Absolute, {.p 3}},		/* dd 3 2952 */
	{.type FromH0, {.p M_rshift}, .src = "dd M_rshift"},		/* dd M_rshift 2960 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2968 */
	{.type Absolute, {.p 1}},		/* dd 1 2976 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 2984 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2992 */
	{.type Header, {.hdr { 3, "nip", /* C_nip = 3008 */ colon }}}, /* CENTRY "nip" nip 3 h 3016 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3024 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3032 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3040 */
	{.type Header, {.hdr { 3, "rot", /* C_rot = 3056 */ colon }}}, /* CENTRY "rot" rot 3 h 3064 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3072 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3080 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3088 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3096 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3104 */
	{.type Header, {.hdr { 5, "2drop", /* C_2drop = 3120 */ colon }}}, /* CENTRY "2drop" 2drop 5 h 3128 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3136 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3144 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3152 */
	{.type Header, {.hdr { 4, "2dup", /* C_2dup = 3168 */ colon }}}, /* CENTRY "2dup" 2dup 4 h 3176 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3184 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3192 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3200 */
	{.type Header, {.hdr { 4, "2nip", /* C_2nip = 3216 */ colon }}}, /* CENTRY "2nip" 2nip 4 h 3224 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3232 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3240 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3248 */
	{.type Header, {.hdr { 5, "2swap", /* C_2swap = 3264 */ colon }}}, /* CENTRY "2swap" 2swap 5 h 3272 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3280 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3288 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3296 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3304 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3312 */
	{.type Header, {.hdr { 4, "?dup", /* C_qdup = 3328 */ colon }}}, /* CENTRY "?dup" qdup 4 ; if (n != 0) ( n -- n n) else ( n -- n ) h 3336 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n -- n n )"},		/* dd M_dup	; ( n -- n n ) 3344 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n n -- n n n )"},		/* dd M_dup	; ( n n -- n n n ) 3352 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3360 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( n n n -- n n n 0 ) 3368 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n n n 0 -- n n f )"},		/* dd M_equal	; ( n n n 0 -- n n f ) 3376 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; ( n n f -- n n )"},		/* dd M_cjump	; ( n n f -- n n ) 3384 */
	{.type FromH0, {.p L20}, .src = "dd L20		; when n != 0, go to L20"},		/* dd L20		; when n != 0, go to L20 3392 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; when n == 0 ( n n -- n)"},		/* dd M_drop	; when n == 0 ( n n -- n) 3400 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3408 */
	{.type Header, {.hdr { 4, "pick", /* C_pick = 3424 */ colon }}}, /* CENTRY "pick" pick 4 h 3432 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 3440 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 3448 */
	{.type FromH0, {.p L22}, .src = "dd L22"},		/* dd L22 3456 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3464 */
	{.type Absolute, {.p 1}},		/* dd 1 3472 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3480 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 3488 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 3496 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3504 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3512 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 3520 */
	{.type FromH0, {.p L23}, .src = "dd L23"},		/* dd L23 3528 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3536 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3544 */
	{.type Header, {.hdr { 4, "tuck", /* C_tuck = 3560 */ colon }}}, /* CENTRY "tuck" tuck 4 h 3568 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3576 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3584 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3592 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3600 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3608 */
	{.type Header, {.hdr { 1, "/", /* C_divides = 3624 */ colon }}}, /* CENTRY "/" divides 1 h 3632 */
	{.type FromH0, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 3640 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3648 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3656 */
	{.type Header, {.hdr { 2, "+!", /* C_plusstore = 3672 */ colon }}}, /* CENTRY "+!" plusstore 2 h 3680 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3688 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3696 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3704 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3712 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3720 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 3728 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3736 */
	{.type Header, {.hdr { 6, "invert", /* C_invert = 3752 */ colon }}}, /* CENTRY "invert" invert 6 h 3760 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3768 */
	{.type Absolute, {.p -1}},		/* dd -1 3776 */
	{.type FromH0, {.p M_binxor}, .src = "dd M_binxor"},		/* dd M_binxor 3784 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3792 */
	{.type Header, {.hdr { 3, "mod", /* C_mod = 3808 */ colon }}}, /* CENTRY "mod" mod 3 h 3816 */
	{.type FromH0, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 3824 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3832 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3840 */
	{.type Header, {.hdr { 2, "1+", /* C_1plus = 3856 */ colon }}}, /* CENTRY "1+" 1plus 2 h 3864 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3872 */
	{.type Absolute, {.p 1}},		/* dd 1 3880 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3888 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3896 */
	{.type Header, {.hdr { 2, "1-", /* C_1minus = 3912 */ colon }}}, /* CENTRY "1-" 1minus 2 h 3920 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3928 */
	{.type Absolute, {.p 1}},		/* dd 1 3936 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3944 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3952 */
	{.type Header, {.hdr { 6, "negate", /* C_negate = 3968 */ colon }}}, /* CENTRY "negate" negate 6 h 3976 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3984 */
	{.type Absolute, {.p 0}},		/* dd 0 3992 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 4000 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 4008 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4016 */
	{.type Header, {.hdr { 2, "2*", /* C_2multiplies = 4032 */ colon }}}, /* CENTRY "2*" 2multiplies 2 h 4040 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4048 */
	{.type Absolute, {.p 1}},		/* dd 1 4056 */
	{.type FromH0, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 4064 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4072 */
	{.type Header, {.hdr { 2, "2/", /* C_2divides = 4088 */ colon }}}, /* CENTRY "2/" 2divides 2 h 4096 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4104 */
	{.type Absolute, {.p 1}},		/* dd 1 4112 */
	{.type FromH0, {.p M_rshifta}, .src = "dd M_rshifta"},		/* dd M_rshifta 4120 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4128 */
	{.type Header, {.hdr { 2, "0=", /* C_0eq = 4144 */ colon }}}, /* CENTRY "0=" 0eq 2 h 4152 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4160 */
	{.type Absolute, {.p 0}},		/* dd 0 4168 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4176 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4184 */
	{.type Header, {.hdr { 2, "0<", /* C_0lt = 4200 */ colon }}}, /* CENTRY "0<" 0lt 2 h 4208 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4216 */
	{.type Absolute, {.p 0}},		/* dd 0 4224 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4240 */
	{.type Header, {.hdr { 2, "0>", /* C_0gt = 4256 */ colon }}}, /* CENTRY "0>" 0gt 2 h 4264 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4272 */
	{.type Absolute, {.p 0}},		/* dd 0 4280 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4288 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4296 */
	{.type Header, {.hdr { 2, "<>", /* C_neq = 4312 */ colon }}}, /* CENTRY "<>" neq 2 h 4320 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4328 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 4336 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4344 */
	{.type Header, {.hdr { 3, "0<>", /* C_0neq = 4360 */ colon }}}, /* CENTRY "0<>" 0neq 3 h 4368 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4376 */
	{.type Absolute, {.p 0}},		/* dd 0 4384 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 4392 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4400 */
	{.type Header, {.hdr { 3, "max", /* C_max = 4416 */ colon }}}, /* CENTRY "max" max 3 h 4424 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4432 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4440 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4448 */
	{.type FromH0, {.p L40}, .src = "dd L40"},		/* dd L40 4456 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4464 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4472 */
	{.type FromH0, {.p L41}, .src = "dd L41"},		/* dd L41 4480 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4488 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4496 */
	{.type Header, {.hdr { 3, "min", /* C_min = 4512 */ colon }}}, /* CENTRY "min" min 3 h 4520 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4528 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4536 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4544 */
	{.type FromH0, {.p L43}, .src = "dd L43"},		/* dd L43 4552 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4560 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4568 */
	{.type FromH0, {.p L44}, .src = "dd L44"},		/* dd L44 4576 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4584 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4592 */
	{.type Header, {.hdr { 6, "signum", /* C_signum = 4608 */ colon }}}, /* CENTRY "signum" signum 6 h 4616 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4624 */
	{.type FromH0, {.p C_0gt}, .src = "dd C_0gt"},		/* dd C_0gt 4632 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4640 */
	{.type FromH0, {.p L46}, .src = "dd L46"},		/* dd L46 4648 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4656 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4664 */
	{.type Absolute, {.p 1}},		/* dd 1 4672 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4680 */
	{.type FromH0, {.p L47}, .src = "dd L47"},		/* dd L47 4688 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 4696 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4704 */
	{.type FromH0, {.p L48}, .src = "dd L48"},		/* dd L48 4712 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4720 */
	{.type Absolute, {.p -1}},		/* dd -1 4728 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4736 */
	{.type FromH0, {.p L49}, .src = "dd L49"},		/* dd L49 4744 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4752 */
	{.type Absolute, {.p 0}},		/* dd 0 4760 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4768 */
	{.type Header, {.hdr { 6, "within", /* C_within = 4784 */ colon }}}, /* CENTRY "within" within 6 h 4792 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 4800 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 4808 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4816 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4824 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 4832 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 4840 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4848 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4856 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 4864 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4872 */
	{.type Header, {.hdr { 3, "abs", /* C_abs = 4888 */ colon }}}, /* CENTRY "abs" abs 3 h 4896 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4904 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 4912 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4920 */
	{.type FromH0, {.p L52}, .src = "dd L52"},		/* dd L52 4928 */
	{.type FromH0, {.p C_negate}, .src = "dd C_negate"},		/* dd C_negate 4936 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4944 */
	{.type Header, {.hdr { 3, "key", /* C_key = 4960 */ colon }}}, /* CENTRY "key" key 3 ; ( -- c ) (G read a single character from the input onto the stack ) h 4968 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 4976 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( infd )"},		/* dd M_fetch		; ( infd ) 4984 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf to store the character read"},		/* dd MV_Iobuf		; variable iobuf to store the character read 4992 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5000 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( infd Iobuf 1 ) 5008 */
	{.type FromH0, {.p M_sysread}, .src = "dd M_sysread	; ( infd Iobuf 1 -- n )"},		/* dd M_sysread	; ( infd Iobuf 1 -- n ) 5016 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 5024 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump		; if 0 characters read"},		/* dd M_cjump		; if 0 characters read 5032 */
	{.type FromH0, {.p L78}, .src = "dd L78			; if qread n != 0 jump to L78. If n == 0 jump over"},		/* dd L78			; if qread n != 0 jump to L78. If n == 0 jump over 5040 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 5048 */
	{.type FromH0, {.p C_on}, .src = "dd C_on		; EOF"},		/* dd C_on		; EOF 5056 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5064 */
	{.type Absolute, {.p -1}},		/* dd -1			; return -1 when EOF 5072 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5080 */
	{.type FromH0, {.p L79}, .src = "dd L79"},		/* dd L79 5088 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; get the character from Iobuf to stack"},		/* dd MV_Iobuf		; get the character from Iobuf to stack 5096 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( -- c ) return the character read if not EOF"},		/* dd M_cfetch	; ( -- c ) return the character read if not EOF 5104 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5112 */
	{.type Header, {.hdr { 4, "emit", /* C_emit = 5128 */ colon }}}, /* CENTRY "emit" emit 4 ; ( character -- ) h 5136 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5144 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; variable iobuf has character"},		/* dd M_cstore	; variable iobuf has character 5152 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 5160 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; outfd"},		/* dd M_fetch		; outfd 5168 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5176 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5184 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( outfd iobuf 1 ) 5192 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite	; ( 1 iobuf outfd --  )"},		/* dd M_syswrite	; ( 1 iobuf outfd --  ) 5200 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5208 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5216 */
	{.type Header, {.hdr { 4, "type", /* C_type = 5232 */ colon }}}, /* CENTRY "type" type 4 ; ( addr n -- ) h 5240 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; ( addr ) (R n )"},		/* dd M_rpush		; ( addr ) (R n ) 5248 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; ( ) (R n addr )"},		/* dd M_rpush		; ( ) (R n addr ) 5256 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 5264 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( outfd )"},		/* dd M_fetch		; ( outfd ) 5272 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( outfd addr ) (R n )"},		/* dd M_rpop		; ( outfd addr ) (R n ) 5280 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( outfd addr n ) (R )"},		/* dd M_rpop		; ( outfd addr n ) (R ) 5288 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite	; ( 1 addr n --  )"},		/* dd M_syswrite	; ( 1 addr n --  ) 5296 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5304 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5312 */
	{.type Header, {.hdr { 2, "cr", /* C_cr = 5328 */ colon }}}, /* CENTRY "cr" cr 2 h 5336 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5344 */
	{.type Absolute, {.p 10}},		/* dd 10			; ascii value of carriage return 5352 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit			; emit"},		/* dd C_emit			; emit 5360 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5368 */
	{.type Header, {.hdr { 5, "space", /* C_space = 5384 */ colon }}}, /* CENTRY "space" space 5 h 5392 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5400 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5408 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5416 */
	{.type Header, {.hdr { 5, "emits", /* C_emits = 5432 */ colon }}}, /* CENTRY "emits" emits 5 h 5440 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5448 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5456 */
	{.type FromH0, {.p L86}, .src = "dd L86"},		/* dd L86 5464 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5472 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5480 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5488 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5496 */
	{.type FromH0, {.p L85}, .src = "dd L85"},		/* dd L85 5504 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 5512 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5520 */
	{.type Header, {.hdr { 6, "spaces", /* C_spaces = 5536 */ colon }}}, /* CENTRY "spaces" spaces 6 h 5544 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5552 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 5560 */
	{.type FromH0, {.p C_emits}, .src = "dd C_emits"},		/* dd C_emits 5568 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5576 */
	{.type Header, {.hdr { 5, "count", /* C_count = 5592 */ colon }}}, /* CENTRY "count" count 5 ; ( 'counted-string -- 'text count ) a = address of counted string ( a - a+1 a[0]) h 5600 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 5608 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 5616 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5624 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5632 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5640 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup ; debug show the word name to search"},		/* dd C_2dup ; debug show the word name to search 5648 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5656 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 5664 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush ; debug show the dictionary entry"},		/* dd M_rpush ; debug show the dictionary entry 5672 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 5680 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 5688 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5696 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5704 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5712 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 5720 */
	{.type Header, {.hdr { 7, "compare", /* C_compare = 5736 */ colon }}}, /* CENTRY "compare" compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search h 5744 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 )"},		/* dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 5752 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 )"},		/* dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 ) 5760 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- ) 5768 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- ) 5776 */
	{.type FromH0, {.p C_min}, .src = "dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- )"},		/* dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- ) 5784 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5792 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- ) 5800 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- )"},		/* dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- ) 5808 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5816 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 5824 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 5832 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5840 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5848 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 5856 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 5864 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5872 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 5880 */
	{.type FromH0, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 5888 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5896 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5904 */
	{.type FromH0, {.p L56}, .src = "dd L56		; matches"},		/* dd L56		; matches 5912 */
	{.type FromH0, {.p C_2nip}, .src = "dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- )"},		/* dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- ) 5920 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2)"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2) 5928 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 -- )"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 -- ) 5936 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5944 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 5952 */
	{.type FromH0, {.p L55}, .src = "dd L55"},		/* dd L55 5960 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- )"},		/* dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- ) 5968 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5976 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( n2 n1 -- ) (R -- )"},		/* dd M_rpop	; ( n2 n1 -- ) (R -- ) 5984 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( -- n1-n2 )"},		/* dd M_minus	; ( -- n1-n2 ) 5992 */
	{.type FromH0, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 6000 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6008 */
	{.type Header, {.hdr { 5, "erase", /* C_erase = 6024 */ colon }}}, /* CENTRY "erase" erase 5 h 6032 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6040 */
	{.type Absolute, {.p 0}},		/* dd 0 6048 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6056 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6064 */
	{.type Absolute, {.p 0}},		/* dd 0 6072 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6080 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6088 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 6096 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6104 */
	{.type FromH0, {.p L58}, .src = "dd L58"},		/* dd L58 6112 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6120 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6128 */
	{.type Header, {.hdr { 4, "fill", /* C_fill = 6144 */ colon }}}, /* CENTRY "fill" fill 4 h 6152 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6160 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6168 */
	{.type Absolute, {.p 0}},		/* dd 0 6176 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6184 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 6192 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6200 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6208 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6216 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6224 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6232 */
	{.type FromH0, {.p L60}, .src = "dd L60"},		/* dd L60 6240 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 6248 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6256 */
	{.type Header, {.hdr { 5, "blank", /* C_blank = 6272 */ colon }}}, /* CENTRY "blank" blank 5 h 6280 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 6288 */
	{.type FromH0, {.p C_fill}, .src = "dd C_fill"},		/* dd C_fill 6296 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6304 */
	{.type Header, {.hdr { 6, "search", /* C_search = 6320 */ colon }}}, /* CENTRY "search" search 6 h 6328 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6336 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6344 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6352 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 6360 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 6368 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6376 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6384 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6392 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 6400 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6408 */
	{.type Absolute, {.p 0}},		/* dd 0 6416 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6424 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6432 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6440 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6448 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6456 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6464 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6472 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6480 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6488 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6496 */
	{.type FromH0, {.p C_compare}, .src = "dd C_compare"},		/* dd C_compare 6504 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 6512 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 6520 */
	{.type FromH0, {.p L65}, .src = "dd L65"},		/* dd L65 6528 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6536 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6544 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6552 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6560 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 6568 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6576 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6584 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6592 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 6600 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6608 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6616 */
	{.type FromH0, {.p L64}, .src = "dd L64"},		/* dd L64 6624 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6632 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6640 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 6648 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6656 */
	{.type Header, {.hdr { 4, "here", /* C_here = 6672 */ colon }}}, /* CENTRY "here" here 4 h 6680 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6688 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6696 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6704 */
	{.type Header, {.hdr { 4, "vhere", /* C_vhere = 6720 */ colon }}}, /* CENTRY "vhere" vhere 4 h 6728 */
	{.type FromH0, {.p M_Vp}, .src = "dd M_Vp"},		/* dd M_Vp 6736 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6744 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6752 */
	{.type Header, {.hdr { 1, ",", /* C_comma = 6768 */ colon }}}, /* CENTRY "," comma 1 h 6776 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6784 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6792 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6800 */
	{.type Absolute, {.p 8}},		/* dd 8 6808 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6816 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6824 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6832 */
	{.type Header, {.hdr { 2, "c,", /* C_c = 6848 */ colon }}}, /* CENTRY "c," c 2 h 6856 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6864 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6872 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6880 */
	{.type Absolute, {.p 1}},		/* dd 1 6888 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6896 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6904 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6912 */
	{.type Header, {.hdr { 5, "allot", /* C_allot = 6928 */ colon }}}, /* CENTRY "allot" allot 5 ; ( n -- ) here = here+n h 6936 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6944 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6952 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6960 */
	{.type Header, {.hdr { 6, "vallot", /* C_vallot = 6976 */ colon }}}, /* CENTRY "vallot" vallot 6 ; allot on the variable space ( n -- ) vhere = vhere+n h 6984 */
	{.type FromH0, {.p M_Vp}, .src = "dd M_Vp"},		/* dd M_Vp 6992 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 7000 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7008 */
	{.type Header, {.hdr { 3, "pad", /* C_pad = 7024 */ colon }}}, /* CENTRY "pad" pad 3 h 7032 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 7040 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7048 */
	{.type Absolute, {.p 256}},		/* dd 256 7056 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7064 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7072 */
	{.type Header, {.hdr { 5, "align", /* C_align = 7088 */ colon }}}, /* CENTRY "align" align 5 ; ( -- ) align here to a cell boundary h 7096 */
	{.type FromH0, {.p C_here}, .src = "dd C_here		; Dp @"},		/* dd C_here		; Dp @ 7104 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned	; here is aligned to a multiple of 8"},		/* dd C_aligned	; here is aligned to a multiple of 8 7112 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp			; store the aligned here at Dp"},		/* dd M_Dp			; store the aligned here at Dp 7120 */
	{.type FromH0, {.p M_store}, .src = "dd M_store		; Dp contains aligned_here"},		/* dd M_store		; Dp contains aligned_here 7128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7136 */
	{.type Header, {.hdr { 6, "unused", /* C_unused = 7152 */ colon }}}, /* CENTRY "unused" unused 6 h 7160 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 7168 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7176 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 7184 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7192 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7200 */
	{.type Header, {.hdr { 2, "<#", /* C_fromhash = 7216 */ colon }}}, /* CENTRY "<#" fromhash 2 h 7224 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7232 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7240 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7248 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7256 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7264 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7272 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7280 */
	{.type Header, {.hdr { 1, "#", /* C_hash = 7296 */ colon }}}, /* CENTRY "#" hash 1 h 7304 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 7312 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7320 */
	{.type FromH0, {.p M_uslashmod}, .src = "dd M_uslashmod"},		/* dd M_uslashmod 7328 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7336 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7344 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7352 */
	{.type Absolute, {.p 9}},		/* dd 9 7360 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 7368 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7376 */
	{.type FromH0, {.p L92}, .src = "dd L92"},		/* dd L92 7384 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7392 */
	{.type Absolute, {.p 97}},		/* dd 97 7400 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7408 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7416 */
	{.type Absolute, {.p 10}},		/* dd 10 7424 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7432 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7440 */
	{.type FromH0, {.p L93}, .src = "dd L93"},		/* dd L93 7448 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7456 */
	{.type Absolute, {.p 48}},		/* dd 48 7464 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7472 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7480 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7488 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7496 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7504 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7512 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7520 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7528 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7536 */
	{.type Header, {.hdr { 2, "#s", /* C_hashs = 7552 */ colon }}}, /* CENTRY "#s" hashs 2 h 7560 */
	{.type FromH0, {.p C_hash}, .src = "dd C_hash"},		/* dd C_hash 7568 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7576 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7584 */
	{.type FromH0, {.p L96}, .src = "dd L96"},		/* dd L96 7592 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7600 */
	{.type FromH0, {.p L95}, .src = "dd L95"},		/* dd L95 7608 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7616 */
	{.type Header, {.hdr { 2, "#>", /* C_hashfrom = 7632 */ colon }}}, /* CENTRY "#>" hashfrom 2 h 7640 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 7648 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7656 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7664 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7672 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7680 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7688 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7696 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7704 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7712 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7720 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7728 */
	{.type Header, {.hdr { 4, "hold", /* C_hold = 7744 */ colon }}}, /* CENTRY "hold" hold 4 h 7752 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7760 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7768 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7776 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7784 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 7792 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7800 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 7808 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7816 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7824 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7832 */
	{.type Header, {.hdr { 4, "sign", /* C_sign = 7848 */ colon }}}, /* CENTRY "sign" sign 4 h 7856 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 7864 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7872 */
	{.type FromH0, {.p L100}, .src = "dd L100"},		/* dd L100 7880 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7888 */
	{.type Absolute, {.p 45}},		/* dd 45 7896 */
	{.type FromH0, {.p C_hold}, .src = "dd C_hold"},		/* dd C_hold 7904 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7912 */
	{.type Header, {.hdr { 1, ".", /* C_dot = 7928 */ colon }}}, /* CENTRY "." dot 1 ; print the top of stack ( n -- ) h 7936 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; ( n -- n n )"},		/* dd M_dup		; ( n -- n n ) 7944 */
	{.type FromH0, {.p C_abs}, .src = "dd C_abs		; ( n n -- n u )"},		/* dd C_abs		; ( n n -- n u ) 7952 */
	{.type FromH0, {.p C_fromhash}, .src = "dd C_fromhash	; pad = h+256; >num = pad+1024"},		/* dd C_fromhash	; pad = h+256; >num = pad+1024 7960 */
	{.type FromH0, {.p C_hashs}, .src = "dd C_hashs		; ( n u1 -- n n2 )"},		/* dd C_hashs		; ( n u1 -- n n2 ) 7968 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap		; ( n n2 -- n2 n )"},		/* dd M_xswap		; ( n n2 -- n2 n ) 7976 */
	{.type FromH0, {.p C_sign}, .src = "dd C_sign		; ( n2 n -- n2 )"},		/* dd C_sign		; ( n2 n -- n2 ) 7984 */
	{.type FromH0, {.p C_hashfrom}, .src = "dd C_hashfrom	; ( u1 -- a n )"},		/* dd C_hashfrom	; ( u1 -- a n ) 7992 */
	{.type FromH0, {.p C_type}, .src = "dd C_type		; ( a n -- )"},		/* dd C_type		; ( a n -- ) 8000 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 8008 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8016 */
	{.type Header, {.hdr { 2, ".r", /* C_dotr = 8032 */ colon }}}, /* CENTRY ".r" dotr 2 h 8040 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 8048 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8056 */
	{.type FromH0, {.p C_abs}, .src = "dd C_abs"},		/* dd C_abs 8064 */
	{.type FromH0, {.p C_fromhash}, .src = "dd C_fromhash"},		/* dd C_fromhash 8072 */
	{.type FromH0, {.p C_hashs}, .src = "dd C_hashs"},		/* dd C_hashs 8080 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 8088 */
	{.type FromH0, {.p C_sign}, .src = "dd C_sign"},		/* dd C_sign 8096 */
	{.type FromH0, {.p C_hashfrom}, .src = "dd C_hashfrom"},		/* dd C_hashfrom 8104 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 8112 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 8120 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8128 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8136 */
	{.type Absolute, {.p 0}},		/* dd 0 8144 */
	{.type FromH0, {.p C_max}, .src = "dd C_max"},		/* dd C_max 8152 */
	{.type FromH0, {.p C_spaces}, .src = "dd C_spaces"},		/* dd C_spaces 8160 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 8168 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8176 */
	{.type Header, {.hdr { 3, "hex", /* C_hex = 8192 */ colon }}}, /* CENTRY "hex" hex 3 h 8200 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8208 */
	{.type Absolute, {.p 16}},		/* dd 16 8216 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8224 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8240 */
	{.type Header, {.hdr { 7, "decimal", /* C_decimal = 8256 */ colon }}}, /* CENTRY "decimal" decimal 7 h 8264 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8272 */
	{.type Absolute, {.p 10}},		/* dd 10 8280 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8288 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8296 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8304 */
	{.type Header, {.hdr { 5, "digit", /* C_digit = 8320 */ colon }}}, /* CENTRY "digit" digit 5 ; ( c -- ) h 8328 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8336 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8344 */
	{.type Absolute, {.p 65}},		/* dd 65 8352 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8360 */
	{.type Absolute, {.p 91}},		/* dd 91 8368 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8376 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8384 */
	{.type FromH0, {.p L106}, .src = "dd L106"},		/* dd L106 8392 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8400 */
	{.type Absolute, {.p 55}},		/* dd 55 8408 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8416 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8424 */
	{.type FromH0, {.p L107}, .src = "dd L107"},		/* dd L107 8432 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8440 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8448 */
	{.type Absolute, {.p 97}},		/* dd 97 8456 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8464 */
	{.type Absolute, {.p 123}},		/* dd 123 8472 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8480 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8488 */
	{.type FromH0, {.p L108}, .src = "dd L108"},		/* dd L108 8496 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8504 */
	{.type Absolute, {.p 87}},		/* dd 87 8512 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8520 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8528 */
	{.type FromH0, {.p L109}, .src = "dd L109"},		/* dd L109 8536 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8544 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8552 */
	{.type Absolute, {.p 48}},		/* dd 48 8560 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8568 */
	{.type Absolute, {.p 58}},		/* dd 58 8576 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8584 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8592 */
	{.type FromH0, {.p L110}, .src = "dd L110"},		/* dd L110 8600 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8608 */
	{.type Absolute, {.p 48}},		/* dd 48 8616 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8624 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8632 */
	{.type FromH0, {.p L111}, .src = "dd L111"},		/* dd L111 8640 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8648 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8656 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8664 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8672 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8680 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 8688 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 8696 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8704 */
	{.type FromH0, {.p L112}, .src = "dd L112"},		/* dd L112 8712 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 8720 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8728 */
	{.type FromH0, {.p L113}, .src = "dd L113"},		/* dd L113 8736 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8744 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8752 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8760 */
	{.type Header, {.hdr { 6, "number", /* C_number = 8776 */ colon }}}, /* CENTRY "number" number 6 ; ( a n1 -- n2 -1 | a n1 0 ) h 8784 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 -- n1 a )"},		/* dd M_xswap	; ( a n1 -- n1 a ) 8792 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n1 a -- n1 a a )"},		/* dd M_dup	; ( n1 a -- n1 a a ) 8800 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( n1 a a -- n1 a c )"},		/* dd M_cfetch	; ( n1 a a -- n1 a c ) 8808 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8816 */
	{.type Absolute, {.p 45}},		/* dd 45		; ( n1 a c -- n1 a c - ) 8824 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n1 a c -- n1 a f )"},		/* dd M_equal	; ( n1 a c -- n1 a f ) 8832 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; ( n1 a c -- n1 a )"},		/* dd M_cjump	; ( n1 a c -- n1 a ) 8840 */
	{.type FromH0, {.p L115}, .src = "dd L115		; c != -"},		/* dd L115		; c != - 8848 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; c == - ( n1 a -- n1 a+1 )"},		/* dd C_1plus	; c == - ( n1 a -- n1 a+1 ) 8856 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 8864 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 )"},		/* dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 ) 8872 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8880 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( a+1 n1-1 -- a+1 n1-1 -1 ) 8888 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1)"},		/* dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1) 8896 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8904 */
	{.type FromH0, {.p L116}, .src = "dd L116"},		/* dd L116 8912 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( n1 a -- a n1)"},		/* dd M_xswap	; ( n1 a -- a n1) 8920 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8928 */
	{.type Absolute, {.p 1}},		/* dd 1 8936 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1)"},		/* dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1) 8944 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a n1 -- a n1 n1 ) (R nr)"},		/* dd M_dup	; ( a n1 -- a n1 n1 ) (R nr) 8952 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1)"},		/* dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1) 8960 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8968 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a n1 -- a n1 0) (R nr n1) 8976 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1)"},		/* dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1) 8984 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8992 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a 0 n1 -- a 0 n1 0) (R nr n1) 9000 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1) 9008 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 9016 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1) 9024 */
	{.type FromH0, {.p M_multiply}, .src = "dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1) 9032 */
	{.type FromH0, {.p M_over}, .src = "dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1)"},		/* dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1) 9040 */
	{.type FromH0, {.p M_i}, .src = "dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1) 9048 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1) 9056 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1)"},		/* dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1) 9064 */
	{.type FromH0, {.p C_digit}, .src = "dd C_digit"},		/* dd C_digit 9072 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9080 */
	{.type FromH0, {.p L118}, .src = "dd L118"},		/* dd L118 9088 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 9096 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9104 */
	{.type FromH0, {.p L119}, .src = "dd L119"},		/* dd L119 9112 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9120 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 9128 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9136 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9144 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9152 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 9160 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9168 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 9176 */
	{.type FromH0, {.p L117}, .src = "dd L117"},		/* dd L117 9184 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9192 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9200 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 9208 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9216 */
	{.type FromH0, {.p M_multiply}, .src = "dd M_multiply"},		/* dd M_multiply 9224 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 9232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9240 */
	{.type Header, {.hdr { 5, "abort", /* C_abort = 9256 */ colon }}}, /* CENTRY "abort" abort 5 h 9264 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec"},		/* dd MV_Abortvec 9272 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9280 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 9288 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9296 */
	{.type Header, {.hdr { 6, "source", /* C_source = 9312 */ colon }}}, /* CENTRY "source" source 6 h 9320 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9328 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9336 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9344 */
/* ; current-input-char */	{.type Header, {.hdr { 13, "current-input", /* C_current_input = 9368 */ colon }}}, /* CENTRY "current-input" current_input 13 ; ( -- c ) read the next character from the location in Sourcebuf h 9376 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9384 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9392 */
	{.type FromH0, {.p C_source}, .src = "dd C_source"},		/* dd C_source 9400 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus		; Sourcebuf + >In"},		/* dd M_plus		; Sourcebuf + >In 9408 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 9416 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9424 */
	{.type Header, {.hdr { 10, "save-input", /* C_save_input = 9448 */ colon }}}, /* CENTRY "save-input" save_input 10 ; ( -- infd >in >limit sourcebuf 'Acceptvec 5 ) save input stream onto the stack h 9456 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 9464 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9472 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9480 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9488 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9496 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9504 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9512 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9520 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 9528 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9536 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9544 */
	{.type Absolute, {.p 5}},		/* dd 5 9552 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9560 */
	{.type Header, {.hdr { 13, "default-input", /* C_default_input = 9584 */ colon }}}, /* CENTRY "default-input" default_input 13 ; stream input from stdin into Text input buffer h 9592 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 9600 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 9608 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9616 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9624 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9632 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9640 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9648 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib"},		/* dd M_Tib 9656 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9664 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9672 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9680 */
	{.type FromH0, {.p C_accept_line}, .src = "dd C_accept_line	; could use C_accept_key too"},		/* dd C_accept_line	; could use C_accept_key too 9688 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 9696 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9704 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9712 */
	{.type Header, {.hdr { 13, "restore-input", /* C_restore_input = 9736 */ colon }}}, /* CENTRY "restore-input" restore_input 13 ; ( <input>|empty -- f ) ; restore input stream from the stack or set the default-input as the input stream h 9744 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 9752 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; reset Eof back to 0"},		/* dd C_off		; reset Eof back to 0 9760 */
	{.type FromH0, {.p C_depth}, .src = "dd C_depth"},		/* dd C_depth 9768 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9776 */
	{.type Absolute, {.p 6}},		/* dd 6			; is the input stream on the stack, depth == 6? 9784 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 9792 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9800 */
	{.type FromH0, {.p L132}, .src = "dd L132			; depth <> 6, there is no input stream on the stack, get out"},		/* dd L132			; depth <> 6, there is no input stream on the stack, get out 9808 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; depth == 6, now check if there is a 5 on the top of stack"},		/* dd M_dup		; depth == 6, now check if there is a 5 on the top of stack 9816 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9824 */
	{.type Absolute, {.p 5}},		/* dd 5			; is 5 on the top of stack? 9832 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 9840 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9848 */
	{.type FromH0, {.p L132}, .src = "dd L132			; top of stack <> 5, there is no input stream on the stack, get out"},		/* dd L132			; top of stack <> 5, there is no input stream on the stack, get out 9856 */
/* ; ( infd >in >limit sourcebuf 'accept 5 ) */	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; ( infd >in >limit sourcebuf 'accept )"},		/* dd M_drop		; ( infd >in >limit sourcebuf 'accept ) 9864 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 9872 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9880 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9888 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9896 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9904 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9912 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9920 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9928 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 9936 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9944 */
	{.type FromH0, {.p C_true}, .src = "dd C_true			; ( true )"},		/* dd C_true			; ( true ) 9952 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9960 */
	{.type FromH0, {.p C_default_input}, .src = "dd C_default_input	; no input stream on the stack, use default input from now"},		/* dd C_default_input	; no input stream on the stack, use default input from now 9968 */
	{.type FromH0, {.p C_false}, .src = "dd C_false			; ( 0 )"},		/* dd C_false			; ( 0 ) 9976 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9984 */
	{.type Header, {.hdr { 14, "?restore-input", /* C_qrestore_input = 10008 */ colon }}}, /* CENTRY "?restore-input" qrestore_input 14 ; ( <input> -- ) ; use the input stream on the stack or abort h 10016 */
	{.type FromH0, {.p C_restore_input}, .src = "dd C_restore_input"},		/* dd C_restore_input 10024 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 10032 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10040 */
	{.type FromH0, {.p L136}, .src = "dd L136		; input stream restored"},		/* dd L136		; input stream restored 10048 */
/* ; no input stream on the stack to restore, show error and abort */	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 10056 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10064 */
	{.type FromH0, {.p L137}, .src = "dd L137"},		/* dd L137 10072 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10080 */
	{.type Absolute, {.p 23}},		/* dd 23 10088 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 10096 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 10104 */
	{.type FromH0, {.p C_depth}, .src = "dd C_depth"},		/* dd C_depth 10112 */
	{.type FromH0, {.p C_dot}, .src = "dd C_dot"},		/* dd C_dot 10120 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 10128 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 10136 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10144 */
/* ; next-input-char */	{.type Header, {.hdr { 10, "next-input", /* C_next_input = 10168 */ colon }}}, /* CENTRY "next-input" next_input 10 ; when >In < >Limit ( -- true c ). ( -- 0 false ) otherwise h 10176 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10184 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10192 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 10200 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10208 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 10216 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10224 */
	{.type FromH0, {.p L139}, .src = "dd L139	; >In >= >Limit"},		/* dd L139	; >In >= >Limit 10232 */
	{.type FromH0, {.p C_true}, .src = "dd C_true	; >In < >Limit"},		/* dd C_true	; >In < >Limit 10240 */
	{.type FromH0, {.p C_current_input}, .src = "dd C_current_input	; ( -- c )"},		/* dd C_current_input	; ( -- c ) 10248 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 10256 */
	{.type FromH0, {.p L140}, .src = "dd L140"},		/* dd L140 10264 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10272 */
	{.type Absolute, {.p 0}},		/* dd 0 10280 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 10288 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10296 */
/* ; replace current-input and next-input with an asm function that does cmove until it meets a certain character or limit? */	{.type Header, {.hdr { 5, "parse", /* C_parse = 10312 */ colon }}}, /* CENTRY "parse" parse 5 ; ( c -- a ) Place the counted string in Wordbuf and return that address. c = word delimiter. h 10320 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; ( c -- ) (R -- c )"},		/* dd M_rpush		; ( c -- ) (R -- c ) 10328 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf"},		/* dd MV_Wordbuf 10336 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( -- Wordb )"},		/* dd M_fetch		; ( -- Wordb ) 10344 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus		; ( Wordb -- Wordb+1 )"},		/* dd C_1plus		; ( Wordb -- Wordb+1 ) 10352 */
	{.type FromH0, {.p C_next_input}, .src = "dd C_next_input ; ( Wordb+1 -- Wordb+1 f c )"},		/* dd C_next_input ; ( Wordb+1 -- Wordb+1 f c ) 10360 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c )"},		/* dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c ) 10368 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) )"},		/* dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) ) 10376 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand		; ( Wordb+1 f&(c!=cinitial) )"},		/* dd M_binand		; ( Wordb+1 f&(c!=cinitial) ) 10384 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10392 */
	{.type FromH0, {.p L143}, .src = "dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew"},		/* dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew 10400 */
	{.type FromH0, {.p C_current_input}, .src = "dd C_current_input	; ( Wordb+1 -- Wordb+1 c )"},		/* dd C_current_input	; ( Wordb+1 -- Wordb+1 c ) 10408 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 10416 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1"},		/* dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1 10424 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus		; ( Wordb+1 -- Wordb+2 )"},		/* dd C_1plus		; ( Wordb+1 -- Wordb+2 ) 10432 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10440 */
	{.type Absolute, {.p 1}},		/* dd 1 10448 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10456 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10464 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 10472 */
	{.type FromH0, {.p L142}, .src = "dd L142		; ( Wordb+2 ) repeat"},		/* dd L142		; ( Wordb+2 ) repeat 10480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10488 */
	{.type Absolute, {.p 1}},		/* dd 1 10496 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10504 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10512 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- )"},		/* dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- ) 10520 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; (Wordb+1 c -- Wordb+1)"},		/* dd M_drop		; (Wordb+1 c -- Wordb+1) 10528 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf"},		/* dd MV_Wordbuf 10536 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb)"},		/* dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb) 10544 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb)"},		/* dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb) 10552 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb)"},		/* dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb) 10560 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb)"},		/* dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb) 10568 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb)"},		/* dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb) 10576 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb)"},		/* dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb) 10584 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now."},		/* dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now. 10592 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( -- Wordb) (R Wordb -- )"},		/* dd M_rpop		; ( -- Wordb) (R Wordb -- ) 10600 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10608 */
	{.type Header, {.hdr { 4, "word", /* C_word = 10624 */ colon }}}, /* CENTRY "word" word 4 ; ( c -- a ) skip the c"s. Placed the counted string in a (as in Wordbuf) h 10632 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- ) (R -- c )"},		/* dd M_rpush	; ( -- ) (R -- c ) 10640 */
	{.type FromH0, {.p C_next_input}, .src = "dd C_next_input ; ( -- f c2 ) (R c1 -- )"},		/* dd C_next_input ; ( -- f c2 ) (R c1 -- ) 10648 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial )"},		/* dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial ) 10656 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial )"},		/* dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial ) 10664 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial )"},		/* dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial ) 10672 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10680 */
	{.type FromH0, {.p L146}, .src = "dd L146		; >In >= >Limit || cinitial != cnew"},		/* dd L146		; >In >= >Limit || cinitial != cnew 10688 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal	; >In < >Limit && cinitial == cnew"},		/* dd M_literal	; >In < >Limit && cinitial == cnew 10696 */
	{.type Absolute, {.p 1}},		/* dd 1 10704 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10712 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10720 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump		; repeat"},		/* dd M_jump		; repeat 10728 */
	{.type FromH0, {.p L145}, .src = "dd L145"},		/* dd L145 10736 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( cinitial ) Sourcebuf+>In = location of first non-matching character"},		/* dd M_rpop		; ( cinitial ) Sourcebuf+>In = location of first non-matching character 10744 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 10752 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10760 */
/* ; accept is the Brdline of bio *//* ; if Acceptvec == 0, set Eof on and get out *//* ;	else execute it */	{.type Header, {.hdr { 6, "accept", /* C_accept = 10776 */ colon }}}, /* CENTRY "accept" accept 6 ; ( a n -- n ) get line or n chars or EOF from input and store at a h 10784 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 10792 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10800 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 10808 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10816 */
	{.type FromH0, {.p L300}, .src = "dd L300	; Acceptvec == 0, set Eof on and get out"},		/* dd L300	; Acceptvec == 0, set Eof on and get out 10824 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 10832 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10840 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop	; ( )"},		/* dd C_2drop	; ( ) 10848 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10856 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( 0 ) 10864 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 10872 */
	{.type FromH0, {.p C_on}, .src = "dd C_on"},		/* dd C_on 10880 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10888 */
	{.type Header, {.hdr { 11, "accept-line", /* C_accept_line = 10912 */ colon }}}, /* CENTRY "accept-line" accept_line 11 ; ( a n -- n1 ) get line or n chars or EOF from input and store at a using key h 10920 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 10928 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( a n infd )"},		/* dd M_fetch		; ( a n infd ) 10936 */
	{.type FromH0, {.p C_read_file}, .src = "dd C_read_file	; ( n ioresult )"},		/* dd C_read_file	; ( n ioresult ) 10944 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10952 */
	{.type FromH0, {.p L301}, .src = "dd L301			; ioresult == false as n = -1"},		/* dd L301			; ioresult == false as n = -1 10960 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; ( n n )"},		/* dd M_dup		; ( n n ) 10968 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10976 */
	{.type FromH0, {.p L302}, .src = "dd L302			; ( 0 )"},		/* dd L302			; ( 0 ) 10984 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; n > 0. if n == 4096, error out. ( n n )"},		/* dd M_dup		; n > 0. if n == 4096, error out. ( n n ) 10992 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11000 */
	{.type Absolute, {.p 4096}},		/* dd 4096			; ( n n 4096 ) 11008 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal		; ( n n==4096 )"},		/* dd M_equal		; ( n n==4096 ) 11016 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump		; ( n )"},		/* dd M_cjump		; ( n ) 11024 */
	{.type FromH0, {.p L303}, .src = "dd L303			; n < 4096 ( n )"},		/* dd L303			; n < 4096 ( n ) 11032 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; n == 4096 ( n )"},		/* dd MV_Sourcebuf	; n == 4096 ( n ) 11040 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( n tib )"},		/* dd M_fetch		; ( n tib ) 11048 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap		; ( tib n )"},		/* dd M_xswap		; ( tib n ) 11056 */
	{.type FromH0, {.p C_type}, .src = "dd C_type		; show the long line and an error message"},		/* dd C_type		; show the long line and an error message 11064 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11072 */
	{.type FromH0, {.p L304}, .src = "dd L304"},		/* dd L304 11080 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11088 */
	{.type Absolute, {.p 37}},		/* dd 37 11096 */
	{.type FromH0, {.p C_type}, .src = "dd C_type		; show the error message"},		/* dd C_type		; show the error message 11104 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 11112 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 11120 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus		; n-- to avoid parsing the newline character"},		/* dd C_1minus		; n-- to avoid parsing the newline character 11128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; ( n ) n = number of bytes read"},		/* dd M_exitcolon	; ( n ) n = number of bytes read 11136 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11144 */
	{.type FromH0, {.p L305}, .src = "dd L305"},		/* dd L305 11152 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11160 */
	{.type Absolute, {.p 12}},		/* dd 12 11168 */
	{.type FromH0, {.p C_type}, .src = "dd C_type		; show the error message"},		/* dd C_type		; show the error message 11176 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 11184 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 11192 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof	; n == 0, set Eof"},		/* dd MV_Eof	; n == 0, set Eof 11200 */
	{.type FromH0, {.p C_on}, .src = "dd C_on		; EOF"},		/* dd C_on		; EOF 11208 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; ( 0 )"},		/* dd M_exitcolon	; ( 0 ) 11216 */
/* ; loops through 1 character at a time until a newline unlike accept-line which gets the line in one call. */	{.type Header, {.hdr { 10, "accept-key", /* C_accept_key = 11240 */ colon }}}, /* CENTRY "accept-key" accept_key 10 ; ( a n -- n ) get line or n chars or EOF from input and store at a using key h 11248 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( n a -- )"},		/* dd M_xswap	; ( n a -- ) 11256 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n a a -- )"},		/* dd M_dup	; ( n a a -- ) 11264 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 11272 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( n -- ) (R a a -- )"},		/* dd M_rpush	; ( n -- ) (R a a -- ) 11280 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup	; ( n n -- ) (R a a -- )"},		/* dd C_qdup	; ( n n -- ) (R a a -- ) 11288 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; (if)"},		/* dd M_cjump	; (if) 11296 */
	{.type FromH0, {.p L149}, .src = "dd L149		; n == 0"},		/* dd L149		; n == 0 11304 */
	{.type FromH0, {.p C_key}, .src = "dd C_key	; n > 0 ( n -- n c )"},		/* dd C_key	; n > 0 ( n -- n c ) 11312 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( -- n c c )"},		/* dd M_dup	; ( -- n c c ) 11320 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11328 */
	{.type Absolute, {.p 10}},		/* dd 10		; ( -- n c c 10 ) 11336 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n c c 10 -- n c f ) checking for newline"},		/* dd M_equal	; ( n c c 10 -- n c f ) checking for newline 11344 */
	{.type FromH0, {.p M_over}, .src = "dd M_over	; ( -- n c f c )"},		/* dd M_over	; ( -- n c f c ) 11352 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11360 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( -- n c f c -1 ) 11368 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( -- n c f1 f2 )"},		/* dd M_equal	; ( -- n c f1 f2 ) 11376 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor	; ( -- n c f )"},		/* dd M_binor	; ( -- n c f ) 11384 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11392 */
	{.type FromH0, {.p L150}, .src = "dd L150"},		/* dd L150 11400 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop	; n == -1 || n == 10 (	-- )"},		/* dd C_2drop	; n == -1 || n == 10 (	-- ) 11408 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 11416 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 11424 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( -- a2-a1 )"},		/* dd M_minus	; ( -- a2-a1 ) 11432 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; ( -- n ) (R -- )"},		/* dd M_exitcolon	; ( -- n ) (R -- ) 11440 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( n c a -- ) (R a a -- )"},		/* dd M_rfetch	; ( n c a -- ) (R a a -- ) 11448 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; store the character at a"},		/* dd M_cstore	; store the character at a 11456 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( n a -- ) (R a -- )"},		/* dd M_rpop	; ( n a -- ) (R a -- ) 11464 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 11472 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address"},		/* dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address 11480 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; ( n -- n-1 )"},		/* dd C_1minus	; ( n -- n-1 ) 11488 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11496 */
	{.type FromH0, {.p L148}, .src = "dd L148	; loop again for the next character"},		/* dd L148	; loop again for the next character 11504 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 )"},		/* dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 ) 11512 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( a2 a1 -- ) (R a1 -- )"},		/* dd M_rpop	; ( a2 a1 -- ) (R a1 -- ) 11520 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( a2 a1 -- a2-a1 )"},		/* dd M_minus	; ( a2 a1 -- a2-a1 ) 11528 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11536 */
	{.type Header, {.hdr { 5, "query", /* C_query = 11552 */ colon }}}, /* CENTRY "query" query 5 ; read from input stream into the Text Input Buffer h 11560 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 11568 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; clear EOF flag"},		/* dd C_off	; clear EOF flag 11576 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top"},		/* dd M_Tib	; constant puts address of tibuffer on the top 11584 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11592 */
	{.type Absolute, {.p 4096}},		/* dd 4096	; ( tibuffer -- tibuffer 4096 ) 11600 */
	{.type FromH0, {.p C_accept}, .src = "dd C_accept ; ( tibuffer 4096 -- n )"},		/* dd C_accept ; ( tibuffer 4096 -- n ) 11608 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n -- n n )"},		/* dd M_dup	; ( n -- n n ) 11616 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq	; ( n n -- n f )"},		/* dd C_0eq	; ( n n -- n f ) 11624 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 11632 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11640 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; n == 0 && EOF"},		/* dd M_binand	; n == 0 && EOF 11648 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11656 */
	{.type FromH0, {.p L152}, .src = "dd L152		; false condition"},		/* dd L152		; false condition 11664 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; n == 0 && EOF ( n -- )"},		/* dd M_drop	; n == 0 && EOF ( n -- ) 11672 */
	{.type FromH0, {.p C_qrestore_input}, .src = "dd C_qrestore_input"},		/* dd C_qrestore_input 11680 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11688 */
	{.type FromH0, {.p L153}, .src = "dd L153"},		/* dd L153 11696 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 11704 */
	{.type FromH0, {.p M_store}, .src = "dd M_store		; number of characters to read >Limit = n"},		/* dd M_store		; number of characters to read >Limit = n 11712 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 11720 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; start from 0 >In = 0"},		/* dd C_off		; start from 0 >In = 0 11728 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11736 */
	{.type Header, {.hdr { 6, "refill", /* C_refill = 11752 */ colon }}}, /* CENTRY "refill" refill 6 ; no more refills when there is no 'Acceptvec h 11760 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 11768 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11776 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11784 */
	{.type FromH0, {.p L155}, .src = "dd L155"},		/* dd L155 11792 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 11800 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11808 */
	{.type FromH0, {.p C_query}, .src = "dd C_query"},		/* dd C_query 11816 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 11824 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11832 */
	{.type Header, {.hdr { 8, "findname", /* C_findname = 11856 */ colon }}}, /* CENTRY "findname" findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names h 11864 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 11872 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11880 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop"},		/* dd M_Dtop 11888 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; get latest dictionary link"},		/* dd M_fetch	; get latest dictionary link 11896 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 11904 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11912 */
	{.type FromH0, {.p L159}, .src = "dd L159	; seached until the first dictionary entry get out"},		/* dd L159	; seached until the first dictionary entry get out 11920 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a )"},		/* dd M_dup	; ( a -- a a ) 11928 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; ( a a -- a a+8) lenth + initial name address"},		/* dd C_cellplus	; ( a a -- a a+8) lenth + initial name address 11936 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name"},		/* dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name 11944 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11952 */
	{.type Absolute, {.p 64}},		/* dd 64		; check the reveal'ed flag 1=hidden, 0=reveal 11960 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; if hidden, goto L161 else L160"},		/* dd M_binand	; if hidden, goto L161 else L160 11968 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11976 */
	{.type FromH0, {.p L160}, .src = "dd L160"},		/* dd L160 11984 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; smudge'd dictionary entry, get the previous entry"},		/* dd M_fetch	; smudge'd dictionary entry, get the previous entry 11992 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12000 */
	{.type FromH0, {.p L161}, .src = "dd L161"},		/* dd L161 12008 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a1 -- a1 a1)"},		/* dd M_dup	; ( a1 -- a1 a1) 12016 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; ( a1 a1 -- a1 a1+8)"},		/* dd C_cellplus	; ( a1 a1 -- a1 a1+8) 12024 */
	{.type FromH0, {.p C_count}, .src = "dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n )"},		/* dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n ) 12032 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12040 */
	{.type Absolute, {.p 63}},		/* dd 63 12048 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len )"},		/* dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len ) 12056 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 12064 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 12072 */
	{.type FromH0, {.p C_count}, .src = "dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 )"},		/* dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 ) 12080 */
	{.type FromH0, {.p C_compare}, .src = "dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name"},		/* dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name 12088 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq	; found a match?"},		/* dd C_0eq	; found a match? 12096 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12104 */
	{.type FromH0, {.p L162}, .src = "dd L162		; no match"},		/* dd L162		; no match 12112 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; match found"},		/* dd C_cellplus	; match found 12120 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 12128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12136 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 12144 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12152 */
	{.type FromH0, {.p L158}, .src = "dd L158"},		/* dd L158 12160 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 12168 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 12176 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 12184 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12192 */
	{.type Header, {.hdr { 4, "find", /* C_find = 12208 */ colon }}}, /* CENTRY "find" find 4 ; ( a1 -- a2 f )? h 12216 */
	{.type FromH0, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 12224 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12232 */
	{.type FromH0, {.p L164}, .src = "dd L164"},		/* dd L164 12240 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12248 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 12256 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 12264 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 12272 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12280 */
	{.type Absolute, {.p 63}},		/* dd 63 12288 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 12296 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 12304 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 12312 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 12320 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 12328 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12336 */
	{.type Absolute, {.p 128}},		/* dd 128 12344 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 12352 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12360 */
	{.type FromH0, {.p L165}, .src = "dd L165"},		/* dd L165 12368 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12376 */
	{.type Absolute, {.p 1}},		/* dd 1 12384 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12392 */
	{.type FromH0, {.p L166}, .src = "dd L166"},		/* dd L166 12400 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12408 */
	{.type Absolute, {.p -1}},		/* dd -1 12416 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12424 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12432 */
	{.type FromH0, {.p L167}, .src = "dd L167"},		/* dd L167 12440 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 12448 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12456 */
	{.type Header, {.hdr { 1, "'", /* C_single_quote = 12472 */ colon }}}, /* CENTRY "'" single_quote 1 h 12480 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 12488 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 12496 */
	{.type FromH0, {.p C_find}, .src = "dd C_find"},		/* dd C_find 12504 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 12512 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12520 */
	{.type FromH0, {.p L169}, .src = "dd L169"},		/* dd L169 12528 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 12536 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 12544 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12552 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12560 */
	{.type FromH0, {.p L170}, .src = "dd L170"},		/* dd L170 12568 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12576 */
	{.type Absolute, {.p 3}},		/* dd 3 12584 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12592 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12600 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12608 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12616 */
	{.type Header, {.hdr { 6, "?stack", /* C_qstack = 12632 */ colon }}}, /* CENTRY "?stack" qstack 6 h 12640 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 12648 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 12656 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 12664 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12672 */
	{.type FromH0, {.p L172}, .src = "dd L172"},		/* dd L172 12680 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12688 */
	{.type FromH0, {.p L173}, .src = "dd L173"},		/* dd L173 12696 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12704 */
	{.type Absolute, {.p 16}},		/* dd 16 12712 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12720 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12728 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12736 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12744 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT	; ( str -- str 1) ; debug code to show the word found"},		/* dd MC_STDOUT	; ( str -- str 1) ; debug code to show the word found 12752 */
	{.type FromH0, {.p M_over}, .src = "dd M_over		; ( str 1 str )"},		/* dd M_over		; ( str 1 str ) 12760 */
	{.type FromH0, {.p C_count}, .src = "dd C_count 		; ( str 1 a n)"},		/* dd C_count 		; ( str 1 a n) 12768 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 12776 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 12784 */
	{.type Header, {.hdr { 9, "interpret", /* C_interpret = 12808 */ colon }}}, /* CENTRY "interpret" interpret 9 ; there is stuff in TIB to be interpreted >In and >Limit are set h 12816 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 12824 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( bl -- a ) a = address of counted string"},		/* dd C_word	; ( bl -- a ) a = address of counted string 12832 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12840 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 12848 */
	{.type FromH0, {.p C_0neq}, .src = "dd C_0neq"},		/* dd C_0neq 12856 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12864 */
	{.type FromH0, {.p L176}, .src = "dd L176	; count at a = 0, drop a and exit"},		/* dd L176	; count at a = 0, drop a and exit 12872 */
	{.type FromH0, {.p C_find}, .src = "dd C_find	; ( a -- a1 f ) a = address of counted string"},		/* dd C_find	; ( a -- a1 f ) a = address of counted string 12880 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12888 */
	{.type FromH0, {.p L177}, .src = "dd L177"},		/* dd L177 12896 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute	; found in dictionary, execute"},		/* dd M_execute	; found in dictionary, execute 12904 */
	{.type FromH0, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 12912 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12920 */
	{.type FromH0, {.p L178}, .src = "dd L178"},		/* dd L178 12928 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 12936 */
	{.type FromH0, {.p C_number}, .src = "dd C_number"},		/* dd C_number 12944 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 12952 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12960 */
	{.type FromH0, {.p L179}, .src = "dd L179"},		/* dd L179 12968 */
	{.type FromH0, {.p C_space}, .src = "dd C_space	; the word is neither in the dictionary nor a number"},		/* dd C_space	; the word is neither in the dictionary nor a number 12976 */
	{.type FromH0, {.p C_type}, .src = "dd C_type	; show the word"},		/* dd C_type	; show the word 12984 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12992 */
	{.type FromH0, {.p L180}, .src = "dd L180	; error I?"},		/* dd L180	; error I? 13000 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13008 */
	{.type Absolute, {.p 3}},		/* dd 3 13016 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13024 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 13032 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 13040 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13048 */
	{.type FromH0, {.p L175}, .src = "dd L175"},		/* dd L175 13056 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; count at a = 0 ( a -- )"},		/* dd M_drop	; count at a = 0 ( a -- ) 13064 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13072 */
	{.type Header, {.hdr { 6, "create", /* C_create = 13088 */ colon }}}, /* CENTRY "create" create 6 ; compiles dictionary header until the pfa (link, len, name, cfa) h 13096 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 13104 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here )"},		/* dd C_here	; ( -- here ) 13112 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- ) (R -- linkaddr )"},		/* dd M_rpush	; ( -- ) (R -- linkaddr ) 13120 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop	; ( -- Dtop ) (R -- linkaddr )"},		/* dd M_Dtop	; ( -- Dtop ) (R -- linkaddr ) 13128 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr )"},		/* dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr ) 13136 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; ( dtop -- ) (R -- linkaddr )"},		/* dd C_comma	; ( dtop -- ) (R -- linkaddr ) 13144 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 13152 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; get the word from the input stream ( c -- a ) skip any c. Placed the counted string in a (as in Wordbuf)"},		/* dd C_word	; get the word from the input stream ( c -- a ) skip any c. Placed the counted string in a (as in Wordbuf) 13160 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a ) (R -- linkaddr )"},		/* dd M_dup	; ( a -- a a ) (R -- linkaddr ) 13168 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a -- a len ) (R -- linkaddr )"},		/* dd M_cfetch	; ( a a -- a len ) (R -- linkaddr ) 13176 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( a len -- a len here ) (R -- linkaddr )"},		/* dd C_here	; ( a len -- a len here ) (R -- linkaddr ) 13184 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr )"},		/* dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr ) 13192 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte"},		/* dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte 13200 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr )"},		/* dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr ) 13208 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 )"},		/* dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 ) 13216 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 )"},		/* dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 ) 13224 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- len+1 ) (R -- linkaddr )"},		/* dd M_rpop	; ( -- len+1 ) (R -- linkaddr ) 13232 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1"},		/* dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1 13240 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 13248 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13256 */
	{.type FromH0, {.p M_variable}, .src = "dd M_variable"},		/* dd M_variable 13264 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( -- variablecfa) (R -- linkaddr )"},		/* dd M_fetch	; ( -- variablecfa) (R -- linkaddr ) 13272 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; ( -- ) put the variablecfa into the cfa"},		/* dd C_comma	; ( -- ) put the variablecfa into the cfa 13280 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- linkaddr) (R -- )"},		/* dd M_rpop	; ( -- linkaddr) (R -- ) 13288 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop"},		/* dd M_Dtop 13296 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; Dtop = just created link address"},		/* dd M_store	; Dtop = just created link address 13304 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13312 */
	{.type Header, {.hdr { 8, "variable", /* C_variable = 13336 */ colon }}}, /* CENTRY "variable" variable 8 ; compile to put the vhere then on the stack h 13344 */
	{.type FromH0, {.p C_create}, .src = "dd C_create"},		/* dd C_create 13352 */
	{.type FromH0, {.p C_vhere}, .src = "dd C_vhere"},		/* dd C_vhere 13360 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; put the next available variable location in pfa"},		/* dd C_comma	; put the next available variable location in pfa 13368 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13376 */
	{.type Absolute, {.p 1}},		/* dd 1 13384 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 13392 */
	{.type FromH0, {.p C_vallot}, .src = "dd C_vallot	; vhere = vhere+8, stored at Vp"},		/* dd C_vallot	; vhere = vhere+8, stored at Vp 13400 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13408 */
	{.type Header, {.hdr { 8, "constant", /* C_constant = 13432 */ colon }}}, /* CENTRY "constant" constant 8 ; ( n -- ) do the same as variable but change the cfa to (constant) h 13440 */
	{.type FromH0, {.p C_create}, .src = "dd C_create	; create dictionary header upto the cfa"},		/* dd C_create	; create dictionary header upto the cfa 13448 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13456 */
	{.type FromH0, {.p M_constant}, .src = "dd M_constant"},		/* dd M_constant 13464 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Contstantcfa -- (constant) )"},		/* dd M_fetch	; ( Contstantcfa -- (constant) ) 13472 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( (constant) -- (constant) here )"},		/* dd C_here	; ( (constant) -- (constant) here ) 13480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13488 */
	{.type Absolute, {.p 1}},		/* dd 1 13496 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells	; ( (constant) here -- (constant) here 8 )"},		/* dd C_cells	; ( (constant) here -- (constant) here 8 ) 13504 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( (constant) here 8 -- (constant) here-8 )"},		/* dd M_minus	; ( (constant) here 8 -- (constant) here-8 ) 13512 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant) "},		/* dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant)  13520 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; store n into the dictionary"},		/* dd C_comma	; store n into the dictionary 13528 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13536 */
	{.type Header, {.hdr { 9, "immediate", /* C_immediate = 13560 */ colon }}}, /* CENTRY "immediate" immediate 9 h 13568 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 13576 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13584 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 13592 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13600 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13608 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13616 */
	{.type Absolute, {.p 128}},		/* dd 128 13624 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 13632 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 13640 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 13648 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13656 */
	{.type Header, {.hdr { 4, ">cfa", /* C_tocfa = 13672 */ colon }}}, /* CENTRY ">cfa" tocfa 4 h 13680 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13688 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13696 */
	{.type Absolute, {.p 63}},		/* dd 63 13704 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 13712 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 13720 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 13728 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13736 */
	{.type Header, {.hdr { 7, "compile", /* C_compile = 13752 */ colon }}}, /* CENTRY "compile" compile 7 h 13760 */
	{.type FromH0, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 13768 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13776 */
	{.type FromH0, {.p L188}, .src = "dd L188"},		/* dd L188 13784 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13792 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13800 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13808 */
	{.type Absolute, {.p 128}},		/* dd 128 13816 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 13824 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13832 */
	{.type FromH0, {.p L189}, .src = "dd L189"},		/* dd L189 13840 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa	; immediate"},		/* dd C_tocfa	; immediate 13848 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 13856 */
	{.type FromH0, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 13864 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13872 */
	{.type FromH0, {.p L190}, .src = "dd L190"},		/* dd L190 13880 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 13888 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 13896 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13904 */
	{.type FromH0, {.p L191}, .src = "dd L191"},		/* dd L191 13912 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13920 */
	{.type FromH0, {.p C_number}, .src = "dd C_number"},		/* dd C_number 13928 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 13936 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13944 */
	{.type FromH0, {.p L192}, .src = "dd L192"},		/* dd L192 13952 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 13960 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13968 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13976 */
	{.type FromH0, {.p L193}, .src = "dd L193"},		/* dd L193 13984 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13992 */
	{.type Absolute, {.p 3}},		/* dd 3 14000 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 14008 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 14016 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 14024 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14032 */
	{.type FromH0, {.p L194}, .src = "dd L194"},		/* dd L194 14040 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14048 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14056 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14064 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14072 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14080 */
	{.type Header, {.hdr { 1, "]", /* C_close_bracket = 14096 */ colon }}}, /* CENTRY "]" close_bracket 1 h 14104 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 14112 */
	{.type FromH0, {.p C_on}, .src = "dd C_on"},		/* dd C_on 14120 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 14128 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 14136 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14144 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14152 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 14160 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14168 */
	{.type FromH0, {.p L197}, .src = "dd L197"},		/* dd L197 14176 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 14184 */
	{.type FromH0, {.p C_refill}, .src = "dd C_refill	; no more refills when there is no Acceptvec. Is it a problem? did not dig through to figure out"},		/* dd C_refill	; no more refills when there is no Acceptvec. Is it a problem? did not dig through to figure out 14192 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14200 */
	{.type FromH0, {.p L198}, .src = "dd L198"},		/* dd L198 14208 */
	{.type FromH0, {.p C_compile}, .src = "dd C_compile"},		/* dd C_compile 14216 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 14224 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14232 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14240 */
	{.type FromH0, {.p L199}, .src = "dd L199"},		/* dd L199 14248 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14256 */
	{.type FromH0, {.p L196}, .src = "dd L196"},		/* dd L196 14264 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14272 */
	{.type IHeader, {.hdr { 1, "[", /* CI_open_bracket = 14288 */ colon }}}, /* CIENTRY "[" open_bracket 1 h 14296 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 14304 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 14312 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14320 */
	{.type Header, {.hdr { 6, "smudge", /* C_smudge = 14336 */ colon }}}, /* CENTRY "smudge" smudge 6 h 14344 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 14352 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14360 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 14368 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14376 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14384 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14392 */
	{.type Absolute, {.p 64}},		/* dd 64 14400 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 14408 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 14416 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 14424 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14432 */
	{.type Header, {.hdr { 6, "reveal", /* C_reveal = 14448 */ colon }}}, /* CENTRY "reveal" reveal 6 h 14456 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 14464 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14472 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 14480 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14488 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14496 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14504 */
	{.type Absolute, {.p 64}},		/* dd 64 14512 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 14520 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 14528 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 14536 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 14544 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14552 */
	{.type Header, {.hdr { 1, ":", /* C_colon = 14568 */ colon }}}, /* CENTRY ":" colon 1 h 14576 */
	{.type FromH0, {.p C_create}, .src = "dd C_create	; create a dictionary header with (variable) at cfa"},		/* dd C_create	; create a dictionary header with (variable) at cfa 14584 */
	{.type FromH0, {.p C_smudge}, .src = "dd C_smudge"},		/* dd C_smudge 14592 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14600 */
	{.type FromH0, {.p M_colon}, .src = "dd M_colon"},		/* dd M_colon 14608 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon"},		/* dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon 14616 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( (colon) -- (colon) here )"},		/* dd C_here	; ( (colon) -- (colon) here ) 14624 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14632 */
	{.type Absolute, {.p 1}},		/* dd 1 14640 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 14648 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( (colon) here -- (colon) here-8 )"},		/* dd M_minus	; ( (colon) here -- (colon) here-8 ) 14656 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon"},		/* dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon 14664 */
	{.type FromH0, {.p C_close_bracket}, .src = "dd C_close_bracket"},		/* dd C_close_bracket 14672 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14680 */
	{.type IHeader, {.hdr { 1, ";", /* CI_semicolon = 14696 */ colon }}}, /* CIENTRY ";" semicolon 1 h 14704 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14712 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14720 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14728 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 14736 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 14744 */
	{.type FromH0, {.p C_reveal}, .src = "dd C_reveal"},		/* dd C_reveal 14752 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14760 */
	{.type IHeader, {.hdr { 7, "recurse", /* CI_recurse = 14776 */ colon }}}, /* CIENTRY "recurse" recurse 7 h 14784 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 14792 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14800 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 14808 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 14816 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14824 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14832 */
	{.type Header, {.hdr { 4, "char", /* C_char = 14848 */ colon }}}, /* CENTRY "char" char 4 ; ( -- c ) fetch the first character of the next word from input h 14856 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 14864 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( c -- a ) puts the address of the counted string from the input on the stack"},		/* dd C_word	; ( c -- a ) puts the address of the counted string from the input on the stack 14872 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; skip the count"},		/* dd C_1plus	; skip the count 14880 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; fetch the first character"},		/* dd M_cfetch	; fetch the first character 14888 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14896 */
	{.type Header, {.hdr { 7, "literal", /* C_literal = 14912 */ colon }}}, /* CENTRY "literal" literal 7 ; ( n -- ) adds (literal) n to the dictionary h 14920 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14928 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14936 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14944 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14952 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14960 */
	{.type Header, {.hdr { 8, "sliteral", /* C_sliteral = 14984 */ colon }}}, /* CENTRY "sliteral" sliteral 8 ; ( -- ) adds (sliteral) a n to the dictionary h 14992 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15000 */
	{.type FromH0, {.p M_sliteral}, .src = "dd M_sliteral"},		/* dd M_sliteral 15008 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; adds (sliteral) to the dictionary"},		/* dd C_comma	; adds (sliteral) to the dictionary 15016 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here)"},		/* dd C_here	; ( -- here) 15024 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15032 */
	{.type Absolute, {.p 34}},		/* dd 34		; ascii value of " 15040 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse	; ( here \" -- here a ) \" = word delimiter. a = address of counted string (in Wordbuf)."},		/* dd C_parse	; ( here \" -- here a ) \" = word delimiter. a = address of counted string (in Wordbuf). 15048 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( here a -- here a a )"},		/* dd M_dup	; ( here a -- here a a ) 15056 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( here a a -- here a n )"},		/* dd M_cfetch	; ( here a a -- here a n ) 15064 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( here a n -- here a n+1 ) n+1 as 1 for the count and n for the length of the string"},		/* dd C_1plus	; ( here a n -- here a n+1 ) n+1 as 1 for the count and n for the length of the string 15072 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( here a n+1 -- here a ) (R -- n+1)"},		/* dd M_rpush	; ( here a n+1 -- here a ) (R -- n+1) 15080 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( here a -- a here ) (R -- n+1)"},		/* dd M_xswap	; ( here a -- a here ) (R -- n+1) 15088 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( a here -- a here n+1 ) (R -- n+1 )"},		/* dd M_rfetch	; ( a here -- a here n+1 ) (R -- n+1 ) 15096 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; ( a here n+1 -- ) moves n+1 from a to here"},		/* dd M_cmove	; ( a here n+1 -- ) moves n+1 from a to here 15104 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- n+1 ) (R -- )"},		/* dd M_rpop	; ( -- n+1 ) (R -- ) 15112 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( n+1 -- ) here = here+n+1"},		/* dd C_allot	; ( n+1 -- ) here = here+n+1 15120 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; align here"},		/* dd C_align	; align here 15128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15136 */
	{.type Header, {.hdr { 6, "string", /* C_string = 15152 */ colon }}}, /* CENTRY "string" string 6 ; ( c -- ) h 15160 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 15168 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15176 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 15184 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 15192 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 15200 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15208 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 15216 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 15224 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 15232 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 15240 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15248 */
	{.type IHeader, {.hdr { 6, "[char]", /* CI_char_brackets = 15264 */ colon }}}, /* CIENTRY "[char]" char_brackets 6 ; take the next character from the input stream during compilation h 15272 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 15280 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 15288 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 15296 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 15304 */
	{.type FromH0, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 15312 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15320 */
	{.type IHeader, {.hdr { 3, "[']", /* CI_quote_brackets = 15336 */ colon }}}, /* CIENTRY "[']" quote_brackets 3 ; take the address of next token from the input stream during compilation h 15344 */
	{.type FromH0, {.p C_single_quote}, .src = "dd C_single_quote"},		/* dd C_single_quote 15352 */
	{.type FromH0, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 15360 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15368 */
	{.type IHeader, {.hdr { 1, "(", /* CI_openparen = 15384 */ colon }}}, /* CIENTRY "(" openparen 1 ; ignore until ) from the input stream during compilation h 15392 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15400 */
	{.type Absolute, {.p 41}},		/* dd 41 15408 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 15416 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 15424 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15432 */
/* ; if the line is longer than Tib, then skipping this line is not good enough. hence, throwing an error when >Limit == Tib length */	{.type IHeader, {.hdr { 1, "\\", /* CI_backslash = 15448 */ colon }}}, /* CIENTRY "\\" backslash 1 ; when there is no Acceptvec, find a newline in the buffer and skip until that h 15456 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 15464 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 15472 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15480 */
	{.type FromH0, {.p L214}, .src = "dd L214		; there is no Acceptvec, we are processing a buffer"},		/* dd L214		; there is no Acceptvec, we are processing a buffer 15488 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit	; there is an Acceptvec, skip the rest of this line"},		/* dd MV_toLimit	; there is an Acceptvec, skip the rest of this line 15496 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 15504 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 15512 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15520 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15528 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15536 */
	{.type Absolute, {.p 10}},		/* dd 10 15544 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse	; find the next 10 = LF character"},		/* dd C_parse	; find the next 10 = LF character 15552 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; skip all characters not equal to 10"},		/* dd M_drop	; skip all characters not equal to 10 15560 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15568 */
	{.type Header, {.hdr { 8, "(?abort)", /* C_qabort_parens = 15592 */ colon }}}, /* CENTRY "(?abort)" qabort_parens 8 h 15600 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 15608 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15616 */
	{.type FromH0, {.p L217}, .src = "dd L217"},		/* dd L217 15624 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 15632 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 15640 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 15648 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 15656 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15664 */
	{.type FromH0, {.p L218}, .src = "dd L218"},		/* dd L218 15672 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 15680 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15688 */
	{.type IHeader, {.hdr { 6, "abort\"", /* CI_abort_double_quote = 15704 */ colon }}}, /* CIENTRY "abort\"" abort_double_quote 6 h 15712 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 15720 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15728 */
	{.type FromH0, {.p C_qabort_parens}, .src = "dd C_qabort_parens"},		/* dd C_qabort_parens 15736 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15744 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15752 */
	{.type Header, {.hdr { 1, "\"", /* C_double_quote = 15768 */ colon }}}, /* CENTRY "\"" double_quote 1 ; ( | .. " -- 'text count ) stores counted string in the dictionary and also leaves the address and count of the string on the stack - to use strings at the interpreter prompt h 15776 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15784 */
	{.type Absolute, {.p 34}},		/* dd 34 15792 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 15800 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 15808 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 15816 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15824 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 15832 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 15840 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15848 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 15856 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15864 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 15872 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15880 */
	{.type Header, {.hdr { 2, "c\"", /* C_cdouble_quote = 15896 */ colon }}}, /* CENTRY "c\"" cdouble_quote 2 ; ( | ..." -- 'counted-string ) stores counted string in the dictionary and also leaves the address of the counted string on the stack. For use in interpretive mode. shouldn't this be using pad? h 15904 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15912 */
	{.type Absolute, {.p 34}},		/* dd 34		; ( -- \" ) 15920 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( \" -- a ) a = counted string address. a will be in Wordbuf"},		/* dd C_word	; ( \" -- a ) a = counted string address. a will be in Wordbuf 15928 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a)"},		/* dd M_dup	; ( a -- a a) 15936 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a -- a n )"},		/* dd M_cfetch	; ( a a -- a n ) 15944 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( a n -- a n+1 )"},		/* dd C_1plus	; ( a n -- a n+1 ) 15952 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n -- a ) (R -- n+1)"},		/* dd M_rpush	; ( a n -- a ) (R -- n+1) 15960 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( a -- a here ) (R -- n+1)"},		/* dd C_here	; ( a -- a here ) (R -- n+1) 15968 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( a here -- a here n+1) (R -- n+1)"},		/* dd M_rfetch	; ( a here -- a here n+1) (R -- n+1) 15976 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; move counted string from a to here"},		/* dd M_cmove	; move counted string from a to here 15984 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here )"},		/* dd C_here	; ( -- here ) 15992 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( here -- here n+1 )(R -- )"},		/* dd M_rpop	; ( here -- here n+1 )(R -- ) 16000 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( here n+1 -- here) here += n+1"},		/* dd C_allot	; ( here n+1 -- here) here += n+1 16008 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16016 */
	{.type IHeader, {.hdr { 2, "s\"", /* CI_sdouble_quote = 16032 */ colon }}}, /* CIENTRY "s\"" sdouble_quote 2 ; ( | ..." -- 'text count ) add the string from the input stream to the dictionary as (sliteral) count string - at run-time puts the ( -- addr n) of the counted string on the stack. h 16040 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 16048 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16056 */
	{.type IHeader, {.hdr { 2, ".\"", /* CI_dotstr = 16072 */ colon }}}, /* CIENTRY ".\"" dotstr 2 ; ( | ..." -- ) do what s" does and then add a type word to the dictionary to print that string h 16080 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 16088 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16096 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 16104 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16112 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16120 */
	{.type IHeader, {.hdr { 2, "if", /* CI_if = 16136 */ colon }}}, /* CIENTRY "if" if 2 h 16144 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16152 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16160 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16168 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16176 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16184 */
	{.type Absolute, {.p 0}},		/* dd 0 16192 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16200 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16208 */
	{.type IHeader, {.hdr { 4, "else", /* CI_else = 16224 */ colon }}}, /* CIENTRY "else" else 4 h 16232 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16240 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16248 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16256 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16264 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 16272 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16280 */
	{.type Absolute, {.p 0}},		/* dd 0 16288 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16296 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16304 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16312 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16320 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 16328 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16336 */
	{.type IHeader, {.hdr { 4, "then", /* CI_then = 16352 */ colon }}}, /* CIENTRY "then" then 4 h 16360 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16368 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16376 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16384 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16392 */
	{.type IHeader, {.hdr { 5, "begin", /* CI_begin = 16408 */ colon }}}, /* CIENTRY "begin" begin 5 h 16416 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16424 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16432 */
	{.type IHeader, {.hdr { 5, "again", /* CI_again = 16448 */ colon }}}, /* CIENTRY "again" again 5 h 16456 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16464 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16472 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16480 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16488 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16496 */
	{.type IHeader, {.hdr { 5, "until", /* CI_until = 16512 */ colon }}}, /* CIENTRY "until" until 5 h 16520 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16528 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16536 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16544 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16552 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16560 */
	{.type IHeader, {.hdr { 5, "while", /* CI_while = 16576 */ colon }}}, /* CIENTRY "while" while 5 h 16584 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16592 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16600 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16608 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16616 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16624 */
	{.type Absolute, {.p 0}},		/* dd 0 16632 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16640 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16648 */
	{.type IHeader, {.hdr { 6, "repeat", /* CI_repeat = 16664 */ colon }}}, /* CIENTRY "repeat" repeat 6 h 16672 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16680 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16688 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16696 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16704 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16712 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16720 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16728 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16736 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16744 */
	{.type IHeader, {.hdr { 2, "do", /* CI_do = 16760 */ colon }}}, /* CIENTRY "do" do 2 h 16768 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16776 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time"},		/* dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time 16784 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; puts (do) into the dictionary"},		/* dd C_comma		; puts (do) into the dictionary 16792 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16800 */
	{.type Absolute, {.p 0}},		/* dd 0			; ( -- 0 ) 16808 */
	{.type FromH0, {.p C_here}, .src = "dd C_here		; ( 0 -- 0 here1 )"},		/* dd C_here		; ( 0 -- 0 here1 ) 16816 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16824 */
	{.type IHeader, {.hdr { 4, "loop", /* CI_loop = 16840 */ colon }}}, /* CIENTRY "loop" loop 4 ; ( 0 here1 -- ) h 16848 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16856 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop		; ( 0 here1 -- 0 here1 (loop) )"},		/* dd M_doloop		; ( 0 here1 -- 0 here1 (loop) ) 16864 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 )"},		/* dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 ) 16872 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 )"},		/* dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 ) 16880 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 16888 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16896 */
	{.type FromH0, {.p L234}, .src = "dd L234"},		/* dd L234 16904 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16912 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16920 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16928 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16936 */
	{.type IHeader, {.hdr { 5, "+loop", /* CI_ploop = 16952 */ colon }}}, /* CIENTRY "+loop" ploop 5 h 16960 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16968 */
	{.type FromH0, {.p M_doploop}, .src = "dd M_doploop"},		/* dd M_doploop 16976 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16984 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16992 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 17000 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 17008 */
	{.type FromH0, {.p L236}, .src = "dd L236"},		/* dd L236 17016 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 17024 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 17032 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 17040 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17048 */
	{.type Header, {.hdr { 3, "w/o", /* C_wo = 17064 */ colon }}}, /* CENTRY "w/o" wo 3 h 17072 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17080 */
	{.type Absolute, {.p 1}},		/* dd 1 17088 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17096 */
	{.type Absolute, {.p 512}},		/* dd 512 17104 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 17112 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17120 */
	{.type Absolute, {.p 64}},		/* dd 64 17128 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 17136 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17144 */
	{.type Header, {.hdr { 3, "r/o", /* C_ro = 17160 */ colon }}}, /* CENTRY "r/o" ro 3 h 17168 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17176 */
	{.type Absolute, {.p 0}},		/* dd 0 17184 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17192 */
	{.type Header, {.hdr { 3, "r/w", /* C_rw = 17208 */ colon }}}, /* CENTRY "r/w" rw 3 h 17216 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17224 */
	{.type Absolute, {.p 2}},		/* dd 2 17232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17240 */
	{.type Header, {.hdr { 7, "cstring", /* C_cstring = 17256 */ colon }}}, /* CENTRY "cstring" cstring 7 ; ( 'text count o -- o+'pad+1024 ) \ copy string to pad+o and add a null byte at the end h 17264 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( 'text count o 'pad )"},		/* dd C_pad	; ( 'text count o 'pad ) 17272 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17280 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( 'text count o 'pad 1024 ) 17288 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 'text count o 'pad+1024 )"},		/* dd M_plus	; ( 'text count o 'pad+1024 ) 17296 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 'text count o+'pad+1024 ) o=padoffset"},		/* dd M_plus	; ( 'text count o+'pad+1024 ) o=padoffset 17304 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17312 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( 'text count o+'pad+1024 ) (R o+'pad+1024 )"},		/* dd M_rpush	; ( 'text count o+'pad+1024 ) (R o+'pad+1024 ) 17320 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( 'text o+'pad+1024 count ) (R o+'pad+1024 )"},		/* dd M_xswap	; ( 'text o+'pad+1024 count ) (R o+'pad+1024 ) 17328 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( 'text o+'pad+1024 count count ) (R o+'pad+1024 )"},		/* dd M_dup	; ( 'text o+'pad+1024 count count ) (R o+'pad+1024 ) 17336 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( 'text o+'pad+1024 count ) (R o+'pad+1024  count )"},		/* dd M_rpush	; ( 'text o+'pad+1024 count ) (R o+'pad+1024  count ) 17344 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; moves the filename from 'text to o+'pad+1024"},		/* dd M_cmove	; moves the filename from 'text to o+'pad+1024 17352 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17360 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( 0 ) (R o+'pad+1024  count ) 17368 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( 0 count ) (R o+'pad+1024 )"},		/* dd M_rpop	; ( 0 count ) (R o+'pad+1024 ) 17376 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( 0 count o+'pad+1024 ) (R o+'pad+1024 )"},		/* dd M_rfetch	; ( 0 count o+'pad+1024 ) (R o+'pad+1024 ) 17384 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 count+o+'pad+1024 ) (R o+'pad+1024 )"},		/* dd M_plus	; ( 0 count+o+'pad+1024 ) (R o+'pad+1024 ) 17392 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; makes the filename to a null terminated string"},		/* dd M_cstore	; makes the filename to a null terminated string 17400 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop ;  ( o+'pad+1024 )"},		/* dd M_rpop ;  ( o+'pad+1024 ) 17408 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17416 */
	{.type Header, {.hdr { 8, "cstring0", /* C_cstring0 = 17440 */ colon }}}, /* CENTRY "cstring0" cstring0 8 ; ( 'text count -- 'text ) \ copy string to pad+1024 and add a null byte at the end h 17448 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17456 */
	{.type Absolute, {.p 0}},		/* dd 0 17464 */
	{.type FromH0, {.p C_cstring}, .src = "dd C_cstring"},		/* dd C_cstring 17472 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17480 */
	{.type Header, {.hdr { 8, "cstring1", /* C_cstring1 = 17504 */ colon }}}, /* CENTRY "cstring1" cstring1 8 ; ( 'text count -- 'text ) \ copy string to pad+1536 and add a null byte at the end h 17512 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17520 */
	{.type Absolute, {.p 512}},		/* dd 512 17528 */
	{.type FromH0, {.p C_cstring}, .src = "dd C_cstring"},		/* dd C_cstring 17536 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17544 */
	{.type Header, {.hdr { 9, "open-file", /* C_open_file = 17568 */ colon }}}, /* CENTRY "open-file" open_file 9 ; ( 'text count mode -- fd ioresult ) h 17576 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( 'text count ) (R mode)"},		/* dd M_rpush	; ( 'text count ) (R mode) 17584 */
	{.type FromH0, {.p C_cstring0}, .src = "dd C_cstring0 ; ( 'padtext ) (R mode )"},		/* dd C_cstring0 ; ( 'padtext ) (R mode ) 17592 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( 'padtext mode ) (R )"},		/* dd M_rpop	; ( 'padtext mode ) (R ) 17600 */
	{.type FromH0, {.p M_sysopen}, .src = "dd M_sysopen"},		/* dd M_sysopen 17608 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17616 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17624 */
	{.type Absolute, {.p -1}},		/* dd -1 17632 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 17640 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17648 */
	{.type Header, {.hdr { 10, "close-file", /* C_close_file = 17672 */ colon }}}, /* CENTRY "close-file" close_file 10 ; ( fd -- ioresult ) h 17680 */
	{.type FromH0, {.p M_sysclose}, .src = "dd M_sysclose"},		/* dd M_sysclose 17688 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 17696 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17704 */
	{.type Header, {.hdr { 9, "read-file", /* C_read_file = 17728 */ colon }}}, /* CENTRY "read-file" read_file 9 ; ( a n fd -- n2 ioresult ) h 17736 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( n fd a )"},		/* dd C_rot	; ( n fd a ) 17744 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( fd a n )"},		/* dd C_rot	; ( fd a n ) 17752 */
	{.type FromH0, {.p M_sysread}, .src = "dd M_sysread"},		/* dd M_sysread 17760 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17768 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17776 */
	{.type Absolute, {.p -1}},		/* dd -1 17784 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17792 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17800 */
	{.type Header, {.hdr { 10, "write-file", /* C_write_file = 17824 */ colon }}}, /* CENTRY "write-file" write_file 10 ; ( a n fd -- ioresult ) h 17832 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( n fd a )"},		/* dd C_rot	; ( n fd a ) 17840 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( fd a n )"},		/* dd C_rot	; ( fd a n ) 17848 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 17856 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17864 */
	{.type Absolute, {.p -1}},		/* dd -1 17872 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17880 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17888 */
	{.type Header, {.hdr { 15, "reposition-file", /* C_reposition_file = 17912 */ colon }}}, /* CENTRY "reposition-file" reposition_file 15 ; ( type n fd -- ioresult ) h 17920 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap		; ( type fd n )"},		/* dd M_xswap		; ( type fd n ) 17928 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot		; ( fd n type )"},		/* dd C_rot		; ( fd n type ) 17936 */
	{.type FromH0, {.p M_sysseek}, .src = "dd M_sysseek"},		/* dd M_sysseek 17944 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17952 */
	{.type Absolute, {.p -1}},		/* dd -1 17960 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17968 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17976 */
	{.type Header, {.hdr { 7, "?fcheck", /* C_qfcheck = 17992 */ colon }}}, /* CENTRY "?fcheck" qfcheck 7 h 18000 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 18008 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 18016 */
	{.type FromH0, {.p L246}, .src = "dd L246"},		/* dd L246 18024 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 18032 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18040 */
	{.type FromH0, {.p L247}, .src = "dd L247"},		/* dd L247 18048 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18056 */
	{.type Absolute, {.p 9}},		/* dd 9 18064 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 18072 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 18080 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 18088 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18096 */
	{.type Header, {.hdr { 11, "create-file", /* C_create_file = 18120 */ colon }}}, /* CENTRY "create-file" create_file 11 ; ( a n mode perm -- fd ioresult ) not part of the original ff. could move this to a forth file. h 18128 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n mode ) (R perm)"},		/* dd M_rpush	; ( a n mode ) (R perm) 18136 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n ) (R perm mode)"},		/* dd M_rpush	; ( a n ) (R perm mode) 18144 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( a n padaddr)"},		/* dd C_pad	; ( a n padaddr) 18152 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18160 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( a n padaddr 1024 ) 18168 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( a n padaddr+1024 )"},		/* dd M_plus	; ( a n padaddr+1024 ) 18176 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a padaddr+1024 n )"},		/* dd M_xswap	; ( a padaddr+1024 n ) 18184 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a padaddr+1024 n n )"},		/* dd M_dup	; ( a padaddr+1024 n n ) 18192 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n )"},		/* dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n ) 18200 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; moves the filename from a to paddaddr+1024"},		/* dd M_cmove	; moves the filename from a to paddaddr+1024 18208 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18216 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( 0 ) 18224 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( 0 n ) (R perm mode)"},		/* dd M_rpop	; ( 0 n ) (R perm mode) 18232 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( 0 n padaddr)"},		/* dd C_pad	; ( 0 n padaddr) 18240 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n )"},		/* dd M_plus	; ( 0 padaddr+n ) 18248 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18256 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( 0 padaddr+n 1024 ) 18264 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n+1024 )"},		/* dd M_plus	; ( 0 padaddr+n+1024 ) 18272 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; ( ) makes the filename to a null terminated string"},		/* dd M_cstore	; ( ) makes the filename to a null terminated string 18280 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 18288 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18296 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( padaddr 1024 ) 18304 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( padaddr+1024 )"},		/* dd M_plus	; ( padaddr+1024 ) 18312 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 mode) (R perm )"},		/* dd M_rpop	; ( padaddr+1024 mode) (R perm ) 18320 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 mode perm ) (R )"},		/* dd M_rpop	; ( padaddr+1024 mode perm ) (R ) 18328 */
	{.type FromH0, {.p M_syscreate}, .src = "dd M_syscreate"},		/* dd M_syscreate 18336 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 18344 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18352 */
	{.type Absolute, {.p -1}},		/* dd -1 18360 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 18368 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18376 */
	{.type Header, {.hdr { 3, "bye", /* C_bye = 18392 */ colon }}}, /* CENTRY "bye" bye 3 h 18400 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18408 */
	{.type Absolute, {.p 0}},		/* dd 0 18416 */
	{.type FromH0, {.p M_terminate}, .src = "dd M_terminate"},		/* dd M_terminate 18424 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18432 */
	{.type Header, {.hdr { 7, "include", /* C_include = 18448 */ colon }}}, /* CENTRY "include" include 7 ; this does not work h 18456 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 18464 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 18472 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 18480 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 18488 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 18496 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 18504 */
	{.type FromH0, {.p L248}, .src = "dd L248			; when Acceptvec == 0"},		/* dd L248			; when Acceptvec == 0 18512 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit	; include ends any further reading from the current input line"},		/* dd MV_toLimit	; include ends any further reading from the current input line 18520 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 18528 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 18536 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18544 */
	{.type FromH0, {.p C_save_input}, .src = "dd C_save_input"},		/* dd C_save_input 18552 */
	{.type FromH0, {.p C_default_input}, .src = "dd C_default_input"},		/* dd C_default_input 18560 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18568 */
	{.type FromH0, {.p C_accept_key}, .src = "dd C_accept_key	; as C_accept_line will not get a line per read from non-cons files"},		/* dd C_accept_key	; as C_accept_line will not get a line per read from non-cons files 18576 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec"},		/* dd MV_Acceptvec 18584 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18592 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 18600 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 18608 */
	{.type FromH0, {.p C_ro}, .src = "dd C_ro"},		/* dd C_ro 18616 */
	{.type FromH0, {.p C_open_file}, .src = "dd C_open_file"},		/* dd C_open_file 18624 */
	{.type FromH0, {.p C_qfcheck}, .src = "dd C_qfcheck"},		/* dd C_qfcheck 18632 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18640 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18648 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18656 */
	{.type Header, {.hdr { 5, "crash", /* C_crash = 18672 */ colon }}}, /* CENTRY "crash" crash 5 h 18680 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18688 */
	{.type FromH0, {.p L251}, .src = "dd L251"},		/* dd L251 18696 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18704 */
	{.type Absolute, {.p 30}},		/* dd 30 18712 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 18720 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 18728 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 18736 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18744 */
	{.type Header, {.hdr { 4, "quit", /* C_quit = 18760 */ colon }}}, /* CENTRY "quit" quit 4 ; interpreter loop h 18768 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 18776 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 18784 */
	{.type FromH0, {.p C_query}, .src = "dd C_query"},		/* dd C_query 18792 */
/* ; dd MV_toLimit	; show the line read, for debugging *//* ; dd M_fetch *//* ; dd M_Tib *//* ; dd MC_STDOUT *//* ; dd M_fswrite *//* ; dd M_drop		; drop the return value of write *//* ; dd C_cr *//* ; dd C_space */	{.type FromH0, {.p C_interpret}, .src = "dd C_interpret"},		/* dd C_interpret 18800 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 18808 */
	{.type FromH0, {.p L253}, .src = "dd L253"},		/* dd L253 18816 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed?"},		/* dd M_exitcolon	; why is this needed? 18824 */
	{.type Header, {.hdr { 7, "(abort)", /* C_parenabort = 18840 */ colon }}}, /* CENTRY "(abort)" parenabort 7 ; TODO correct below stack notations h 18848 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State	; ( mv_State -- )"},		/* dd MV_State	; ( mv_State -- ) 18856 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off sets variable state = 0"},		/* dd C_off	; off sets variable state = 0 18864 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 18872 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18880 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18888 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 18896 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 18904 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18912 */
	{.type FromH0, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 18920 */
	{.type FromH0, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 18928 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18936 */
	{.type FromH0, {.p C_default_input}, .src = "dd C_default_input"},		/* dd C_default_input 18944 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit resets stacks and is the interpreter loop"},		/* dd C_quit	; quit resets stacks and is the interpreter loop 18952 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed? quit does not return unless it breaks"},		/* dd M_exitcolon	; why is this needed? quit does not return unless it breaks 18960 */
	{.type Header, {.hdr { 7, "oldboot", /* C_oldboot = 18976 */ colon }}}, /* CENTRY "oldboot" oldboot 7 ; TODO correct below stack notations and this is obsolete. leaving it here for reference until it all works well h 18984 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset"},		/* dd M_reset 18992 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end"},		/* dd M_clear	; SP = sstack_end 19000 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr	; (D -- FFEND)"},		/* dd M_stackptr	; (D -- FFEND) 19008 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 19016 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; s0 = FFEND"},		/* dd M_store	; s0 = FFEND 19024 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp	; heaptop = heapend"},		/* dd M_Dp	; heaptop = heapend 19032 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( heapend -- )"},		/* dd M_fetch	; ( heapend -- ) 19040 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19048 */
	{.type Absolute, {.p 1}},		/* dd 1		; ( heapend 1 -- ) 19056 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells	; cells ( heapend 8 -- )"},		/* dd C_cells	; cells ( heapend 8 -- ) 19064 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( heapend-8 -- )"},		/* dd M_minus	; ( heapend-8 -- ) 19072 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( contents_from_heapend-8 -- )"},		/* dd M_fetch	; ( contents_from_heapend-8 -- ) 19080 */
	{.type FromH0, {.p M_Fthargs}, .src = "dd M_Fthargs	; variable args"},		/* dd M_Fthargs	; variable args 19088 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; args = contents_from_heapend-8"},		/* dd M_store	; args = contents_from_heapend-8 19096 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19104 */
	{.type FromH0, {.p C_parenabort}, .src = "dd C_parenabort ; ( (abort) -- )"},		/* dd C_parenabort ; ( (abort) -- ) 19112 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec	; variable abortvec"},		/* dd MV_Abortvec	; variable abortvec 19120 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable abortvec = (abort) code address"},		/* dd M_store	; variable abortvec = (abort) code address 19128 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb	; constant puts address of wordbuffer on the top of stack"},		/* dd M_Wordb	; constant puts address of wordbuffer on the top of stack 19136 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf	; variable wordbuf"},		/* dd MV_Wordbuf	; variable wordbuf 19144 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable wordbuf = address of wordbuffer"},		/* dd M_store	; variable wordbuf = address of wordbuffer 19152 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top of stack"},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 19160 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; variable sourcebuf"},		/* dd MV_Sourcebuf	; variable sourcebuf 19168 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable sourcebuf = address of tibuffer"},		/* dd M_store	; variable sourcebuf = address of tibuffer 19176 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19184 */
	{.type Absolute, {.p 0}},		/* dd 0 19192 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 19200 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdin = 0"},		/* dd M_store	; stdin = 0 19208 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19216 */
	{.type Absolute, {.p 1}},		/* dd 1 19224 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 19232 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdout = 1"},		/* dd M_store	; stdout = 1 19240 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 19248 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off stores 0 at state"},		/* dd C_off	; off stores 0 at state 19256 */
	{.type FromH0, {.p C_decimal}, .src = "dd C_decimal	; decimal setting base = 0"},		/* dd C_decimal	; decimal setting base = 0 19264 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit"},		/* dd C_quit	; quit 19272 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19280 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal	; test code"},		/* dd M_literal	; test code 19288 */
	{.type Absolute, {.p 66}},		/* dd 66 19296 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 19304 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 19312 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 19320 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 19328 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19336 */
	{.type Absolute, {.p 1}},		/* dd 1 19344 */
	{.type FromH0, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 19352 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 19360 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 19368 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 19376 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19384 */
	{.type Absolute, {.p 1}},		/* dd 1 19392 */
	{.type FromH0, {.p M_sysread}, .src = "dd M_sysread"},		/* dd M_sysread 19400 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of read"},		/* dd M_drop		; drop the return value of read 19408 */
	{.type Header, {.hdr { 7, "do-args", /* C_do_args = 19424 */ colon }}}, /* CENTRY "do-args" do_args 7 h 19432 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19440 */
	{.type Absolute, {.p 0}},		/* dd 0 19448 */
	{.type FromH0, {.p MV_Acceptvec}, .src = "dd MV_Acceptvec	; no more refills"},		/* dd MV_Acceptvec	; no more refills 19456 */
	{.type FromH0, {.p M_store}, .src = "dd M_store 	; C_off	; Acceptvec == 0, reading from a buffer. no more refills."},		/* dd M_store 	; C_off	; Acceptvec == 0, reading from a buffer. no more refills. 19464 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19472 */
	{.type Absolute, {.p 0}},		/* dd 0 19480 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 19488 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; >in = 0"},		/* dd M_store	; >in = 0 19496 */
	{.type FromH0, {.p M_Fthargs}, .src = "dd M_Fthargs	; ( a )"},		/* dd M_Fthargs	; ( a ) 19504 */
	{.type FromH0, {.p C_count}, .src = "dd C_count	; ( a+1 n )"},		/* dd C_count	; ( a+1 n ) 19512 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 19520 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; ( a+1 ) >limit = n"},		/* dd M_store	; ( a+1 ) >limit = n 19528 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 19536 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; sourcebuf = a+1"},		/* dd M_store	; sourcebuf = a+1 19544 */
	{.type FromH0, {.p C_interpret}, .src = "dd C_interpret"},		/* dd C_interpret 19552 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19560 */
	{.type Header, {.hdr { 4, "boot", /* C_boot = 19576 */ colon }}}, /* CENTRY "boot" boot 4 h 19584 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 19592 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 19600 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19608 */
	{.type FromH0, {.p C_parenabort}, .src = "dd C_parenabort ; ( (abort) -- )"},		/* dd C_parenabort ; ( (abort) -- ) 19616 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec	; variable that puts (abort) code address on the stack"},		/* dd MV_Abortvec	; variable that puts (abort) code address on the stack 19624 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable abortvec = (abort) code address"},		/* dd M_store	; variable abortvec = (abort) code address 19632 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb	; variable puts address of wordbuffer on the top of stack"},		/* dd M_Wordb	; variable puts address of wordbuffer on the top of stack 19640 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf ; variable wordbuf"},		/* dd MV_Wordbuf ; variable wordbuf 19648 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable wordbuf = address of wordbuffer"},		/* dd M_store	; variable wordbuf = address of wordbuffer 19656 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 19664 */
	{.type FromH0, {.p MV_H0}, .src = "dd MV_H0	; H0 = here at startup"},		/* dd MV_H0	; H0 = here at startup 19672 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 19680 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 19688 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 19696 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdin = 0"},		/* dd M_store	; stdin = 0 19704 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 19712 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 19720 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 19728 */
	{.type FromH0, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 19736 */
	{.type FromH0, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 19744 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 19752 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 19760 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off stores 0 at state"},		/* dd C_off	; off stores 0 at state 19768 */
	{.type FromH0, {.p C_decimal}, .src = "dd C_decimal	; decimal sets base = 10"},		/* dd C_decimal	; decimal sets base = 10 19776 */
	{.type FromH0, {.p C_default_input}, .src = "dd C_default_input	; read lines from stdin, if args do not set one up"},		/* dd C_default_input	; read lines from stdin, if args do not set one up 19784 */
	{.type FromH0, {.p M_Fthargs}, .src = "dd M_Fthargs"},		/* dd M_Fthargs 19792 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 19800 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 19808 */
	{.type FromH0, {.p L260}, .src = "dd L260	; fetched 0, no args, go to the interpreter loop"},		/* dd L260	; fetched 0, no args, go to the interpreter loop 19816 */
	{.type FromH0, {.p C_do_args}, .src = "dd C_do_args	; process args"},		/* dd C_do_args	; process args 19824 */
/* ; dd C_default_input	; do not do this as it will override any input streams set up by the args */	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; interpreter loop when there are no args or fall through after processing args"},		/* dd C_quit	; interpreter loop when there are no args or fall through after processing args 19832 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19840 */
	{.type Chars, {.str "unable to restore input"}},		/* 19864 */
	{.type Chars, {.str " Q?"}},		/* 19868 */
	{.type Chars, {.str " stack underflow"}},		/* 19885 */
	{.type Chars, {.str " I?"}},		/* 19889 */
	{.type Chars, {.str " C?"}},		/* 19893 */
	{.type Chars, {.str "I/O error"}},		/* 19903 */
	{.type Chars, {.str "uninitialized execution vector"}},		/* 19934 */
	{.type Chars, {.str " ok"}},		/* 19938 */
	{.type Chars, {.str "input line is longer than 4096 bytes"}},		/* 19975 */
	{.type Chars, {.str "read error"}},		/* 19986 */
};

