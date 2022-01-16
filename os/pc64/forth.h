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
	M_fsread = 112,
	M_fswrite = 136,
	M_fsseek = 160,
	M_fsopen = 184,
	M_fsclose = 208,
	M_fscreate = 232,
	M_mmap = 256,
	M_terminate = 280,
	M_fthdump = 304,
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
	M_variable = 1240,
	M_constant = 1272,
	M_colon = 1296,
	M_dodoes = 1320,
	M_cas = 1344,
	M_deferred = 1376,
	MC_STDIN = 1400,
	MC_STDOUT = 1432,
	MC_STDERR = 1464,
	MV_Iobuf = 1496,
	MV_Sourcebuf = 1536,
	MV_Wordbuf = 1568,
	MV_toIn = 1600,
	MV_toLimit = 1632,
	MV_Findadr = 1664,
	MV_Blk = 1696,
	MV_Searchlen = 1736,
	MV_Base = 1768,
	MV_toNum = 1800,
	MV_State = 1832,
	MV_Abortvec = 1872,
	MV_Infd = 1904,
	MV_Outfd = 1936,
	MV_Errfd = 1968,
	MV_Eof = 2000,
	MV_Ninputs = 2032,
	MV_H0 = 2064,
	M_Dp = 2096,
	M_Dtop = 2120,
	M_Vp = 2144,
	M_S0 = 2168,
	M_stackptr = 2192,
	M_Wordb = 2216,
	M_Tib = 2240,
	M_Args = 2264,
	C_false = 2288,
	C_true = 2336,
	C_bl = 2384,
	C_on = 2432,
	C_off = 2496,
	C_tobody = 2560,
	C_aligned = 2616,
	C_cells = 2696,
	C_cellplus = 2752,
	C_depth = 2816,
	C_nip = 2920,
	C_rot = 2968,
	C_2drop = 3032,
	C_2dup = 3080,
	C_2nip = 3128,
	C_2swap = 3176,
	C_qdup = 3240,
	L20 = 3312,
	C_pick = 3336,
	L22 = 3440,
	L23 = 3448,
	C_tuck = 3472,
	C_divides = 3536,
	C_plusstore = 3584,
	C_invert = 3664,
	C_mod = 3720,
	C_1plus = 3768,
	C_1minus = 3824,
	C_negate = 3880,
	C_2multiplies = 3944,
	C_2divides = 4000,
	C_0eq = 4056,
	C_0lt = 4112,
	C_0gt = 4168,
	C_neq = 4224,
	C_0neq = 4272,
	C_max = 4328,
	L40 = 4392,
	L41 = 4400,
	C_min = 4424,
	L43 = 4488,
	L44 = 4496,
	C_signum = 4520,
	L46 = 4600,
	L48 = 4656,
	L49 = 4672,
	L47 = 4672,
	C_within = 4696,
	C_abs = 4800,
	L52 = 4848,
	C_key = 4872,
	L78 = 5000,
	L79 = 5016,
	C_emit = 5040,
	C_type = 5152,
	C_cr = 5224,
	C_space = 5280,
	C_emits = 5328,
	L85 = 5336,
	L86 = 5400,
	C_spaces = 5432,
	C_count = 5488,
	C_compare = 5632,
	L55 = 5704,
	L56 = 5840,
	C_erase = 5920,
	L58 = 5952,
	C_fill = 6040,
	L60 = 6080,
	C_blank = 6168,
	C_search = 6216,
	L64 = 6320,
	L65 = 6504,
	C_here = 6568,
	C_vhere = 6616,
	C_comma = 6664,
	C_c = 6744,
	C_allot = 6824,
	C_vallot = 6872,
	C_pad = 6920,
	C_align = 6984,
	C_unused = 7048,
	C_fromhash = 7112,
	C_hash = 7192,
	L92 = 7344,
	L93 = 7368,
	C_hashs = 7448,
	L95 = 7456,
	L96 = 7504,
	C_hashfrom = 7528,
	C_hold = 7640,
	C_sign = 7744,
	L100 = 7800,
	C_dot = 7824,
	C_dotr = 7928,
	C_hex = 8088,
	C_decimal = 8152,
	C_digit = 8216,
	L106 = 8328,
	L108 = 8432,
	L110 = 8536,
	L111 = 8560,
	L109 = 8560,
	L107 = 8560,
	L112 = 8632,
	L113 = 8648,
	C_number = 8672,
	L115 = 8808,
	L116 = 8840,
	L117 = 8904,
	L118 = 9008,
	L119 = 9064,
	C_abort = 9152,
	C_source = 9208,
	C_current_input = 9264,
	C_save_input = 9344,
	C_default_input = 9488,
	C_restore_input = 9608,
	L300 = 9712,
	L301 = 9728,
	L133 = 9816,
	L134 = 9904,
	C_qrestore_input = 9936,
	L136 = 10064,
	C_next_input = 10096,
	L139 = 10192,
	L140 = 10216,
	C_parse = 10240,
	L142 = 10280,
	L143 = 10408,
	C_word = 10552,
	L145 = 10568,
	L146 = 10664,
	C_accept = 10704,
	L148 = 10744,
	L150 = 10904,
	L149 = 10968,
	C_query = 11016,
	L152 = 11160,
	L153 = 11192,
	C_refill = 11216,
	L155 = 11280,
	L156 = 11296,
	C_findname = 11328,
	L158 = 11368,
	L160 = 11480,
	L162 = 11608,
	L161 = 11616,
	L159 = 11632,
	C_find = 11680,
	L165 = 11872,
	L166 = 11888,
	L164 = 11912,
	L167 = 11920,
	C_single_quote = 11944,
	L169 = 12080,
	C_qstack = 12104,
	L172 = 12208,
	C_interpret = 12288,
	L175 = 12296,
	L177 = 12408,
	L179 = 12520,
	L178 = 12520,
	L176 = 12536,
	C_create = 12568,
	C_variable = 12816,
	C_constant = 12912,
	C_immediate = 13040,
	C_tocfa = 13152,
	C_compile = 13232,
	L189 = 13360,
	L190 = 13376,
	L188 = 13392,
	L192 = 13520,
	L194 = 13552,
	L191 = 13552,
	C_close_bracket = 13576,
	L196 = 13600,
	L197 = 13688,
	L198 = 13712,
	L199 = 13744,
	CI_open_bracket = 13768,
	C_smudge = 13816,
	C_reveal = 13928,
	C_colon = 14048,
	CI_semicolon = 14176,
	CI_recurse = 14256,
	C_char = 14328,
	C_literal = 14392,
	C_sliteral = 14464,
	C_string = 14632,
	CI_char_brackets = 14744,
	CI_quote_brackets = 14816,
	CI_openparen = 14864,
	CI_backslash = 14928,
	L214 = 15072,
	L215 = 15104,
	C_qabort_parens = 15136,
	L217 = 15216,
	L218 = 15224,
	CI_abort_double_quote = 15248,
	C_double_quote = 15312,
	C_cdouble_quote = 15440,
	CI_sdouble_quote = 15576,
	CI_dotstr = 15616,
	CI_if = 15680,
	CI_else = 15768,
	CI_then = 15896,
	CI_begin = 15952,
	CI_again = 15992,
	CI_until = 16056,
	CI_while = 16120,
	CI_repeat = 16208,
	CI_do = 16304,
	CI_loop = 16384,
	L234 = 16472,
	CI_ploop = 16496,
	L236 = 16584,
	C_wo = 16608,
	C_ro = 16704,
	C_rw = 16752,
	C_open_file = 16808,
	C_close_file = 17080,
	C_read_file = 17136,
	C_write_file = 17240,
	C_reposition_file = 17336,
	C_qfcheck = 17400,
	L246 = 17496,
	C_create_file = 17528,
	C_bye = 17816,
	C_include = 17872,
	C_crash = 18024,
	C_quit = 18112,
	L253 = 18136,
	C_parenabort = 18192,
	C_oldboot = 18360,
	C_boot = 18808,
	L137 = 19048,
	L170 = 19072,
	L173 = 19076,
	L180 = 19093,
	L193 = 19097,
	L247 = 19101,
	L251 = 19111,
	L255 = 19142,
};
extern void *sliteral(void);
extern void *cjump(void);
extern void *i(void);
extern void *fsclose(void);
extern void *equal(void);
extern void *j(void);
extern void *drop(void);
extern void *rpop(void);
extern void *fsread(void);
extern void *stackptr(void);
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
extern void *colon(void);
extern void *less(void);
extern void *Dp(void);
extern void *lshift(void);
extern void *S0(void);
extern void *plus(void);
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
extern void *fsseek(void);
extern void *cfetch(void);
extern void *constant(void);
extern void *variable(void);
extern void *fetch(void);
extern void *doloop(void);
extern void *fswrite(void);
extern void *mmap(void);
extern void *binxor(void);
extern void *dup(void);
extern void *exitcolon(void);
extern void *clear(void);
extern void *binand(void);
extern void *literal(void);
extern void *fsopen(void);
extern void *rpush(void);
extern void *fscreate(void);
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
	{.type Header, {.hdr { 4, "read", /* M_fsread = 112 */ fsread }}}, /* MENTRY "read" fsread 4 h 120 */
	{.type Header, {.hdr { 5, "write", /* M_fswrite = 136 */ fswrite }}}, /* MENTRY "write" fswrite 5 h 144 */
	{.type Header, {.hdr { 4, "seek", /* M_fsseek = 160 */ fsseek }}}, /* MENTRY "seek" fsseek 4 h 168 */
	{.type Header, {.hdr { 4, "open", /* M_fsopen = 184 */ fsopen }}}, /* MENTRY "open" fsopen 4 h 192 */
	{.type Header, {.hdr { 5, "close", /* M_fsclose = 208 */ fsclose }}}, /* MENTRY "close" fsclose 5 h 216 */
	{.type Header, {.hdr { 6, "create", /* M_fscreate = 232 */ fscreate }}}, /* MENTRY "create" fscreate 6 h 240 */
	{.type Header, {.hdr { 4, "mmap", /* M_mmap = 256 */ mmap }}}, /* MENTRY "mmap" mmap 4 h 264 */
	{.type Header, {.hdr { 4, "halt", /* M_terminate = 280 */ terminate }}}, /* MENTRY "halt" terminate 4 h 288 */
	{.type Header, {.hdr { 4, "dump", /* M_fthdump = 304 */ fthdump }}}, /* MENTRY "dump" fthdump 4 h 312 */
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
	{.type Header, {.hdr { 10, "(variable)", /* M_variable = 1240 */ variable }}}, /* MENTRY "(variable)" variable 10 h 1248 */
	{.type Header, {.hdr { 10, "(constant)", /* M_constant = 1272 */ constant }}}, /* MENTRY "(constant)" constant 10 h 1280 */
	{.type Header, {.hdr { 3, "(:)", /* M_colon = 1296 */ colon }}}, /* MENTRY "(:)" colon 3 h 1304 */
	{.type Header, {.hdr { 6, "(does)", /* M_dodoes = 1320 */ dodoes }}}, /* MENTRY "(does)" dodoes 6 h 1328 */
	{.type Header, {.hdr { 3, "cas", /* M_cas = 1344 */ cas }}}, /* MENTRY "cas" cas 3 h 1352 */
	{.type Header, {.hdr { 10, "(deferred)", /* M_deferred = 1376 */ deferred }}}, /* MENTRY "(deferred)" deferred 10 h 1384 */
	{.type Header, {.hdr { 5, "STDIN", /* MC_STDIN = 1400 */ constant }}}, /* MCENTRY "STDIN" STDIN 0 5		; 3 constants from here CAPITALS h 1408 */
	{.type Absolute, {.p 0}},		/* 1416 */
	{.type Header, {.hdr { 6, "STDOUT", /* MC_STDOUT = 1432 */ constant }}}, /* MCENTRY "STDOUT" STDOUT 1 6 h 1440 */
	{.type Absolute, {.p 1}},		/* 1448 */
	{.type Header, {.hdr { 6, "STDERR", /* MC_STDERR = 1464 */ constant }}}, /* MCENTRY "STDERR" STDERR 2 6 h 1472 */
	{.type Absolute, {.p 2}},		/* 1480 */
	{.type Header, {.hdr { 5, "Iobuf", /* MV_Iobuf = 1496 */ variable }}}, /* MVENTRY "Iobuf" Iobuf 0 5			; the values are not being used from the definition. All are initialized to 0. h 1504 */
	{.type FromV0, {.p 0 }},	/* 1512 0 */
	{.type Header, {.hdr { 9, "Sourcebuf", /* MV_Sourcebuf = 1536 */ variable }}}, /* MVENTRY "Sourcebuf" Sourcebuf 0 9	; is there a need for this? h 1544 */
	{.type FromV0, {.p 8 }},	/* 1552 8 */
	{.type Header, {.hdr { 7, "Wordbuf", /* MV_Wordbuf = 1568 */ variable }}}, /* MVENTRY "Wordbuf" Wordbuf 0 7		; is there a need for this? h 1576 */
	{.type FromV0, {.p 16 }},	/* 1584 16 */
	{.type Header, {.hdr { 3, ">In", /* MV_toIn = 1600 */ variable }}}, /* MVENTRY ">In" toIn 0 3 h 1608 */
	{.type FromV0, {.p 24 }},	/* 1616 24 */
	{.type Header, {.hdr { 6, ">Limit", /* MV_toLimit = 1632 */ variable }}}, /* MVENTRY ">Limit" toLimit 0 6 h 1640 */
	{.type FromV0, {.p 32 }},	/* 1648 32 */
	{.type Header, {.hdr { 7, "Findadr", /* MV_Findadr = 1664 */ variable }}}, /* MVENTRY "Findadr" Findadr 0 7 h 1672 */
	{.type FromV0, {.p 40 }},	/* 1680 40 */
	{.type Header, {.hdr { 3, "Blk", /* MV_Blk = 1696 */ variable }}}, /* MVENTRY "Blk" Blk 0 3 h 1704 */
	{.type FromV0, {.p 48 }},	/* 1712 48 */
	{.type Header, {.hdr { 9, "Searchlen", /* MV_Searchlen = 1736 */ variable }}}, /* MVENTRY "Searchlen" Searchlen 0 9 h 1744 */
	{.type FromV0, {.p 56 }},	/* 1752 56 */
	{.type Header, {.hdr { 4, "Base", /* MV_Base = 1768 */ variable }}}, /* MVENTRY "Base" Base 0 4 h 1776 */
	{.type FromV0, {.p 64 }},	/* 1784 64 */
	{.type Header, {.hdr { 4, ">Num", /* MV_toNum = 1800 */ variable }}}, /* MVENTRY ">Num" toNum 0 4 h 1808 */
	{.type FromV0, {.p 72 }},	/* 1816 72 */
	{.type Header, {.hdr { 5, "State", /* MV_State = 1832 */ variable }}}, /* MVENTRY "State" State 0 5 h 1840 */
	{.type FromV0, {.p 80 }},	/* 1848 80 */
	{.type Header, {.hdr { 8, "Abortvec", /* MV_Abortvec = 1872 */ variable }}}, /* MVENTRY "Abortvec" Abortvec 0 8	; not sure if these 3 can be constants instead? h 1880 */
	{.type FromV0, {.p 88 }},	/* 1888 88 */
	{.type Header, {.hdr { 4, "Infd", /* MV_Infd = 1904 */ variable }}}, /* MVENTRY "Infd" Infd 0 4 h 1912 */
	{.type FromV0, {.p 96 }},	/* 1920 96 */
	{.type Header, {.hdr { 5, "Outfd", /* MV_Outfd = 1936 */ variable }}}, /* MVENTRY "Outfd" Outfd 0 5 h 1944 */
	{.type FromV0, {.p 104 }},	/* 1952 104 */
	{.type Header, {.hdr { 5, "Errfd", /* MV_Errfd = 1968 */ variable }}}, /* MVENTRY "Errfd" Errfd 0 5 h 1976 */
	{.type FromV0, {.p 112 }},	/* 1984 112 */
	{.type Header, {.hdr { 3, "Eof", /* MV_Eof = 2000 */ variable }}}, /* MVENTRY "Eof" Eof 0 3 h 2008 */
	{.type FromV0, {.p 120 }},	/* 2016 120 */
	{.type Header, {.hdr { 7, "Ninputs", /* MV_Ninputs = 2032 */ variable }}}, /* MVENTRY "Ninputs" Ninputs 0 7 h 2040 */
	{.type FromV0, {.p 128 }},	/* 2048 128 */
	{.type Header, {.hdr { 2, "H0", /* MV_H0 = 2064 */ variable }}}, /* MVENTRY "H0" H0 0 2		; here at startup h 2072 */
	{.type FromV0, {.p 136 }},	/* 2080 136 */
/* ; cannot use H as it is nil in inferno, address where here (next available dictionary cell location) is stored *//* ; here = Dp @ */	{.type Header, {.hdr { 2, "Dp", /* M_Dp = 2096 */ Dp }}}, /* MENTRY "Dp" Dp 2		; here h 2104 */
	{.type Header, {.hdr { 4, "Dtop", /* M_Dtop = 2120 */ Dtop }}}, /* MENTRY "Dtop" Dtop 4	; last defined header h 2128 */
	{.type Header, {.hdr { 2, "Vp", /* M_Vp = 2144 */ Vp }}}, /* MENTRY "Vp" Vp 2		; here of the variables space h 2152 */
	{.type Header, {.hdr { 2, "S0", /* M_S0 = 2168 */ S0 }}}, /* MENTRY "S0" S0 2 h 2176 */
	{.type Header, {.hdr { 2, "s@", /* M_stackptr = 2192 */ stackptr }}}, /* MENTRY "s@" stackptr 2	; puts PSP on stack. Not a variable hence lower case. h 2200 */
	{.type Header, {.hdr { 5, "Wordb", /* M_Wordb = 2216 */ Wordb }}}, /* MENTRY "Wordb" Wordb 5 h 2224 */
	{.type Header, {.hdr { 3, "Tib", /* M_Tib = 2240 */ Tib }}}, /* MENTRY "Tib" Tib 3 h 2248 */
	{.type Header, {.hdr { 4, "Args", /* M_Args = 2264 */ Args }}}, /* MENTRY "Args" Args 4 h 2272 */
	{.type Header, {.hdr { 5, "false", /* C_false = 2288 */ colon }}}, /* CENTRY "false" false 5 h 2296 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2304 */
	{.type Absolute, {.p 0}},		/* dd 0 2312 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2320 */
	{.type Header, {.hdr { 4, "true", /* C_true = 2336 */ colon }}}, /* CENTRY "true" true 4 h 2344 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2352 */
	{.type Absolute, {.p -1}},		/* dd -1 2360 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2368 */
	{.type Header, {.hdr { 2, "bl", /* C_bl = 2384 */ colon }}}, /* CENTRY "bl" bl 2 h 2392 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2400 */
	{.type Absolute, {.p 32}},		/* dd 32 2408 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2416 */
	{.type Header, {.hdr { 2, "on", /* C_on = 2432 */ colon }}}, /* CENTRY "on" on 2 ; ( a -- ) (G stores -1 at a ) h 2440 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2448 */
	{.type Absolute, {.p -1}},		/* dd -1 2456 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2464 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2472 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2480 */
	{.type Header, {.hdr { 3, "off", /* C_off = 2496 */ colon }}}, /* CENTRY "off" off 3 ; ( a -- ) (G stores 0 at a ) h 2504 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2512 */
	{.type Absolute, {.p 0}},		/* dd 0 2520 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2528 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2536 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2544 */
	{.type Header, {.hdr { 5, ">body", /* C_tobody = 2560 */ colon }}}, /* CENTRY ">body" tobody 5 h 2568 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2576 */
	{.type Absolute, {.p 8}},		/* dd 8 2584 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2592 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2600 */
	{.type Header, {.hdr { 7, "aligned", /* C_aligned = 2616 */ colon }}}, /* CENTRY "aligned" aligned 7 ; align a number to a multiple of 8 h 2624 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2632 */
	{.type Absolute, {.p 7}},		/* dd 7 2640 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2648 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2656 */
	{.type Absolute, {.p -8}},		/* dd -8 2664 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 2672 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2680 */
	{.type Header, {.hdr { 5, "cells", /* C_cells = 2696 */ colon }}}, /* CENTRY "cells" cells 5 h 2704 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2712 */
	{.type Absolute, {.p 3}},		/* dd 3			; (index << 2) -> (index << 3) for amd64 2720 */
	{.type FromH0, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 2728 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2736 */
	{.type Header, {.hdr { 5, "cell+", /* C_cellplus = 2752 */ colon }}}, /* CENTRY "cell+" cellplus 5 h 2760 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2768 */
	{.type Absolute, {.p 1}},		/* dd 1 2776 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 2784 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2792 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2800 */
	{.type Header, {.hdr { 5, "depth", /* C_depth = 2816 */ colon }}}, /* CENTRY "depth" depth 5 h 2824 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 2832 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 2840 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 2848 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2856 */
	{.type Absolute, {.p 3}},		/* dd 3 2864 */
	{.type FromH0, {.p M_rshift}, .src = "dd M_rshift"},		/* dd M_rshift 2872 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2880 */
	{.type Absolute, {.p 1}},		/* dd 1 2888 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 2896 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2904 */
	{.type Header, {.hdr { 3, "nip", /* C_nip = 2920 */ colon }}}, /* CENTRY "nip" nip 3 h 2928 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2936 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 2944 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2952 */
	{.type Header, {.hdr { 3, "rot", /* C_rot = 2968 */ colon }}}, /* CENTRY "rot" rot 3 h 2976 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 2984 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2992 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3000 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3008 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3016 */
	{.type Header, {.hdr { 5, "2drop", /* C_2drop = 3032 */ colon }}}, /* CENTRY "2drop" 2drop 5 h 3040 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3048 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3056 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3064 */
	{.type Header, {.hdr { 4, "2dup", /* C_2dup = 3080 */ colon }}}, /* CENTRY "2dup" 2dup 4 h 3088 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3096 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3104 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3112 */
	{.type Header, {.hdr { 4, "2nip", /* C_2nip = 3128 */ colon }}}, /* CENTRY "2nip" 2nip 4 h 3136 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3144 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3152 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3160 */
	{.type Header, {.hdr { 5, "2swap", /* C_2swap = 3176 */ colon }}}, /* CENTRY "2swap" 2swap 5 h 3184 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3192 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3200 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3208 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3216 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3224 */
	{.type Header, {.hdr { 4, "?dup", /* C_qdup = 3240 */ colon }}}, /* CENTRY "?dup" qdup 4 ; if (n != 0) ( n -- n n) else ( n -- n ) h 3248 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n -- n n )"},		/* dd M_dup	; ( n -- n n ) 3256 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n n -- n n n )"},		/* dd M_dup	; ( n n -- n n n ) 3264 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3272 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( n n n -- n n n 0 ) 3280 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n n n 0 -- n n f )"},		/* dd M_equal	; ( n n n 0 -- n n f ) 3288 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; ( n n f -- n n )"},		/* dd M_cjump	; ( n n f -- n n ) 3296 */
	{.type FromH0, {.p L20}, .src = "dd L20		; when n != 0, go to L20"},		/* dd L20		; when n != 0, go to L20 3304 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; when n == 0 ( n n -- n)"},		/* dd M_drop	; when n == 0 ( n n -- n) 3312 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3320 */
	{.type Header, {.hdr { 4, "pick", /* C_pick = 3336 */ colon }}}, /* CENTRY "pick" pick 4 h 3344 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 3352 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 3360 */
	{.type FromH0, {.p L22}, .src = "dd L22"},		/* dd L22 3368 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3376 */
	{.type Absolute, {.p 1}},		/* dd 1 3384 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3392 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 3400 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 3408 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3416 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3424 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 3432 */
	{.type FromH0, {.p L23}, .src = "dd L23"},		/* dd L23 3440 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3448 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3456 */
	{.type Header, {.hdr { 4, "tuck", /* C_tuck = 3472 */ colon }}}, /* CENTRY "tuck" tuck 4 h 3480 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3488 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3496 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3504 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3512 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3520 */
	{.type Header, {.hdr { 1, "/", /* C_divides = 3536 */ colon }}}, /* CENTRY "/" divides 1 h 3544 */
	{.type FromH0, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 3552 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3560 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3568 */
	{.type Header, {.hdr { 2, "+!", /* C_plusstore = 3584 */ colon }}}, /* CENTRY "+!" plusstore 2 h 3592 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3600 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3608 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3616 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3624 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3632 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 3640 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3648 */
	{.type Header, {.hdr { 6, "invert", /* C_invert = 3664 */ colon }}}, /* CENTRY "invert" invert 6 h 3672 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3680 */
	{.type Absolute, {.p -1}},		/* dd -1 3688 */
	{.type FromH0, {.p M_binxor}, .src = "dd M_binxor"},		/* dd M_binxor 3696 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3704 */
	{.type Header, {.hdr { 3, "mod", /* C_mod = 3720 */ colon }}}, /* CENTRY "mod" mod 3 h 3728 */
	{.type FromH0, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 3736 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3744 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3752 */
	{.type Header, {.hdr { 2, "1+", /* C_1plus = 3768 */ colon }}}, /* CENTRY "1+" 1plus 2 h 3776 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3784 */
	{.type Absolute, {.p 1}},		/* dd 1 3792 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3800 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3808 */
	{.type Header, {.hdr { 2, "1-", /* C_1minus = 3824 */ colon }}}, /* CENTRY "1-" 1minus 2 h 3832 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3840 */
	{.type Absolute, {.p 1}},		/* dd 1 3848 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3856 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3864 */
	{.type Header, {.hdr { 6, "negate", /* C_negate = 3880 */ colon }}}, /* CENTRY "negate" negate 6 h 3888 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3896 */
	{.type Absolute, {.p 0}},		/* dd 0 3904 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3912 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3920 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3928 */
	{.type Header, {.hdr { 2, "2*", /* C_2multiplies = 3944 */ colon }}}, /* CENTRY "2*" 2multiplies 2 h 3952 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3960 */
	{.type Absolute, {.p 1}},		/* dd 1 3968 */
	{.type FromH0, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 3976 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3984 */
	{.type Header, {.hdr { 2, "2/", /* C_2divides = 4000 */ colon }}}, /* CENTRY "2/" 2divides 2 h 4008 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4016 */
	{.type Absolute, {.p 1}},		/* dd 1 4024 */
	{.type FromH0, {.p M_rshifta}, .src = "dd M_rshifta"},		/* dd M_rshifta 4032 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4040 */
	{.type Header, {.hdr { 2, "0=", /* C_0eq = 4056 */ colon }}}, /* CENTRY "0=" 0eq 2 h 4064 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4072 */
	{.type Absolute, {.p 0}},		/* dd 0 4080 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4088 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4096 */
	{.type Header, {.hdr { 2, "0<", /* C_0lt = 4112 */ colon }}}, /* CENTRY "0<" 0lt 2 h 4120 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4128 */
	{.type Absolute, {.p 0}},		/* dd 0 4136 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4144 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4152 */
	{.type Header, {.hdr { 2, "0>", /* C_0gt = 4168 */ colon }}}, /* CENTRY "0>" 0gt 2 h 4176 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4184 */
	{.type Absolute, {.p 0}},		/* dd 0 4192 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4200 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4208 */
	{.type Header, {.hdr { 2, "<>", /* C_neq = 4224 */ colon }}}, /* CENTRY "<>" neq 2 h 4232 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4240 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 4248 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4256 */
	{.type Header, {.hdr { 3, "0<>", /* C_0neq = 4272 */ colon }}}, /* CENTRY "0<>" 0neq 3 h 4280 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4288 */
	{.type Absolute, {.p 0}},		/* dd 0 4296 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 4304 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4312 */
	{.type Header, {.hdr { 3, "max", /* C_max = 4328 */ colon }}}, /* CENTRY "max" max 3 h 4336 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4344 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4352 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4360 */
	{.type FromH0, {.p L40}, .src = "dd L40"},		/* dd L40 4368 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4376 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4384 */
	{.type FromH0, {.p L41}, .src = "dd L41"},		/* dd L41 4392 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4400 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4408 */
	{.type Header, {.hdr { 3, "min", /* C_min = 4424 */ colon }}}, /* CENTRY "min" min 3 h 4432 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4440 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4448 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4456 */
	{.type FromH0, {.p L43}, .src = "dd L43"},		/* dd L43 4464 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4472 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4480 */
	{.type FromH0, {.p L44}, .src = "dd L44"},		/* dd L44 4488 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4496 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4504 */
	{.type Header, {.hdr { 6, "signum", /* C_signum = 4520 */ colon }}}, /* CENTRY "signum" signum 6 h 4528 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4536 */
	{.type FromH0, {.p C_0gt}, .src = "dd C_0gt"},		/* dd C_0gt 4544 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4552 */
	{.type FromH0, {.p L46}, .src = "dd L46"},		/* dd L46 4560 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4568 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4576 */
	{.type Absolute, {.p 1}},		/* dd 1 4584 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4592 */
	{.type FromH0, {.p L47}, .src = "dd L47"},		/* dd L47 4600 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 4608 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4616 */
	{.type FromH0, {.p L48}, .src = "dd L48"},		/* dd L48 4624 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4632 */
	{.type Absolute, {.p -1}},		/* dd -1 4640 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4648 */
	{.type FromH0, {.p L49}, .src = "dd L49"},		/* dd L49 4656 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4664 */
	{.type Absolute, {.p 0}},		/* dd 0 4672 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4680 */
	{.type Header, {.hdr { 6, "within", /* C_within = 4696 */ colon }}}, /* CENTRY "within" within 6 h 4704 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 4712 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 4720 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4728 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4736 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 4744 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 4752 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4760 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4768 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 4776 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4784 */
	{.type Header, {.hdr { 3, "abs", /* C_abs = 4800 */ colon }}}, /* CENTRY "abs" abs 3 h 4808 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4816 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 4824 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4832 */
	{.type FromH0, {.p L52}, .src = "dd L52"},		/* dd L52 4840 */
	{.type FromH0, {.p C_negate}, .src = "dd C_negate"},		/* dd C_negate 4848 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4856 */
	{.type Header, {.hdr { 3, "key", /* C_key = 4872 */ colon }}}, /* CENTRY "key" key 3 ; ( -- c ) (G read a single character from the input onto the stack ) h 4880 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4888 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( 1 -- ) 4896 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf to store the character read"},		/* dd MV_Iobuf		; variable iobuf to store the character read 4904 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 4912 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( 1 Iobuf -- 1 Iobuf infd )"},		/* dd M_fetch		; ( 1 Iobuf -- 1 Iobuf infd ) 4920 */
	{.type FromH0, {.p M_fsread}, .src = "dd M_fsread	; ( 1 Iobuf infd -- n )"},		/* dd M_fsread	; ( 1 Iobuf infd -- n ) 4928 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4936 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump		; if 0 characters read"},		/* dd M_cjump		; if 0 characters read 4944 */
	{.type FromH0, {.p L78}, .src = "dd L78			; if qread n != 0 jump to L78. If n == 0 jump over"},		/* dd L78			; if qread n != 0 jump to L78. If n == 0 jump over 4952 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 4960 */
	{.type FromH0, {.p C_on}, .src = "dd C_on		; EOF"},		/* dd C_on		; EOF 4968 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4976 */
	{.type Absolute, {.p -1}},		/* dd -1			; return -1 when EOF 4984 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4992 */
	{.type FromH0, {.p L79}, .src = "dd L79"},		/* dd L79 5000 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; get the character from Iobuf to stack"},		/* dd MV_Iobuf		; get the character from Iobuf to stack 5008 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( -- c ) return the character read if not EOF"},		/* dd M_cfetch	; ( -- c ) return the character read if not EOF 5016 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5024 */
	{.type Header, {.hdr { 4, "emit", /* C_emit = 5040 */ colon }}}, /* CENTRY "emit" emit 4 ; ( character -- ) h 5048 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5056 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; variable iobuf has character"},		/* dd M_cstore	; variable iobuf has character 5064 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5072 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5080 */
	{.type Absolute, {.p 1}},		/* dd 1 5088 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap		; ( iobuf 1 --  1 iobuf )"},		/* dd M_xswap		; ( iobuf 1 --  1 iobuf ) 5096 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 5104 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; outfd"},		/* dd M_fetch		; outfd 5112 */
	{.type FromH0, {.p M_fswrite}, .src = "dd M_fswrite	; ( 1 iobuf outfd --  )"},		/* dd M_fswrite	; ( 1 iobuf outfd --  ) 5120 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5136 */
	{.type Header, {.hdr { 4, "type", /* C_type = 5152 */ colon }}}, /* CENTRY "type" type 4 ; ( addr n -- ) h 5160 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap			; ( addr n --  n addr )"},		/* dd M_xswap			; ( addr n --  n addr ) 5168 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5176 */
	{.type Absolute, {.p 1}},		/* dd 1				; stdout 5184 */
	{.type FromH0, {.p M_fswrite}, .src = "dd M_fswrite		; ( n addr 1 --  )"},		/* dd M_fswrite		; ( n addr 1 --  ) 5192 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5200 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5208 */
	{.type Header, {.hdr { 2, "cr", /* C_cr = 5224 */ colon }}}, /* CENTRY "cr" cr 2 h 5232 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5240 */
	{.type Absolute, {.p 10}},		/* dd 10			; ascii value of carriage return 5248 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit			; emit"},		/* dd C_emit			; emit 5256 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5264 */
	{.type Header, {.hdr { 5, "space", /* C_space = 5280 */ colon }}}, /* CENTRY "space" space 5 h 5288 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5296 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5304 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5312 */
	{.type Header, {.hdr { 5, "emits", /* C_emits = 5328 */ colon }}}, /* CENTRY "emits" emits 5 h 5336 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5344 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5352 */
	{.type FromH0, {.p L86}, .src = "dd L86"},		/* dd L86 5360 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5368 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5376 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5384 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5392 */
	{.type FromH0, {.p L85}, .src = "dd L85"},		/* dd L85 5400 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 5408 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5416 */
	{.type Header, {.hdr { 6, "spaces", /* C_spaces = 5432 */ colon }}}, /* CENTRY "spaces" spaces 6 h 5440 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5448 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 5456 */
	{.type FromH0, {.p C_emits}, .src = "dd C_emits"},		/* dd C_emits 5464 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5472 */
	{.type Header, {.hdr { 5, "count", /* C_count = 5488 */ colon }}}, /* CENTRY "count" count 5 ; ( a -- a+1 n ) a = address of counted string ( a - a+1 a[0]) h 5496 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 5504 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 5512 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5520 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5528 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5536 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup ; debug show the word name to search"},		/* dd C_2dup ; debug show the word name to search 5544 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5552 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 5560 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush ; debug show the dictionary entry"},		/* dd M_rpush ; debug show the dictionary entry 5568 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 5576 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 5584 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5592 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5600 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5608 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 5616 */
	{.type Header, {.hdr { 7, "compare", /* C_compare = 5632 */ colon }}}, /* CENTRY "compare" compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search h 5640 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 )"},		/* dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 5648 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 )"},		/* dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 ) 5656 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- ) 5664 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- ) 5672 */
	{.type FromH0, {.p C_min}, .src = "dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- )"},		/* dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- ) 5680 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5688 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- ) 5696 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- )"},		/* dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- ) 5704 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5712 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 5720 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 5728 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5736 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5744 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 5752 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 5760 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5768 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 5776 */
	{.type FromH0, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 5784 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5792 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5800 */
	{.type FromH0, {.p L56}, .src = "dd L56		; matches"},		/* dd L56		; matches 5808 */
	{.type FromH0, {.p C_2nip}, .src = "dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- )"},		/* dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- ) 5816 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2)"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2) 5824 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 -- )"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 -- ) 5832 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5840 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 5848 */
	{.type FromH0, {.p L55}, .src = "dd L55"},		/* dd L55 5856 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- )"},		/* dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- ) 5864 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5872 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( n2 n1 -- ) (R -- )"},		/* dd M_rpop	; ( n2 n1 -- ) (R -- ) 5880 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( -- n1-n2 )"},		/* dd M_minus	; ( -- n1-n2 ) 5888 */
	{.type FromH0, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 5896 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5904 */
	{.type Header, {.hdr { 5, "erase", /* C_erase = 5920 */ colon }}}, /* CENTRY "erase" erase 5 h 5928 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5936 */
	{.type Absolute, {.p 0}},		/* dd 0 5944 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 5952 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5960 */
	{.type Absolute, {.p 0}},		/* dd 0 5968 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5976 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 5984 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 5992 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6000 */
	{.type FromH0, {.p L58}, .src = "dd L58"},		/* dd L58 6008 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6016 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6024 */
	{.type Header, {.hdr { 4, "fill", /* C_fill = 6040 */ colon }}}, /* CENTRY "fill" fill 4 h 6048 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6056 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6064 */
	{.type Absolute, {.p 0}},		/* dd 0 6072 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6080 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 6088 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6096 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6104 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6112 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6120 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6128 */
	{.type FromH0, {.p L60}, .src = "dd L60"},		/* dd L60 6136 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 6144 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6152 */
	{.type Header, {.hdr { 5, "blank", /* C_blank = 6168 */ colon }}}, /* CENTRY "blank" blank 5 h 6176 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 6184 */
	{.type FromH0, {.p C_fill}, .src = "dd C_fill"},		/* dd C_fill 6192 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6200 */
	{.type Header, {.hdr { 6, "search", /* C_search = 6216 */ colon }}}, /* CENTRY "search" search 6 h 6224 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6232 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6240 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6248 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 6256 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 6264 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6272 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6280 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6288 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 6296 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6304 */
	{.type Absolute, {.p 0}},		/* dd 0 6312 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6320 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6328 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6336 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6344 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6352 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6360 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6368 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6376 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6384 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6392 */
	{.type FromH0, {.p C_compare}, .src = "dd C_compare"},		/* dd C_compare 6400 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 6408 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 6416 */
	{.type FromH0, {.p L65}, .src = "dd L65"},		/* dd L65 6424 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6432 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6440 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6448 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6456 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 6464 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6472 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6480 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6488 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 6496 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6504 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6512 */
	{.type FromH0, {.p L64}, .src = "dd L64"},		/* dd L64 6520 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6528 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6536 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 6544 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6552 */
	{.type Header, {.hdr { 4, "here", /* C_here = 6568 */ colon }}}, /* CENTRY "here" here 4 h 6576 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6584 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6592 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6600 */
	{.type Header, {.hdr { 4, "vhere", /* C_vhere = 6616 */ colon }}}, /* CENTRY "vhere" vhere 4 h 6624 */
	{.type FromH0, {.p M_Vp}, .src = "dd M_Vp"},		/* dd M_Vp 6632 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6640 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6648 */
	{.type Header, {.hdr { 1, ",", /* C_comma = 6664 */ colon }}}, /* CENTRY "," comma 1 h 6672 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6680 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6688 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6696 */
	{.type Absolute, {.p 8}},		/* dd 8 6704 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6712 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6720 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6728 */
	{.type Header, {.hdr { 2, "c,", /* C_c = 6744 */ colon }}}, /* CENTRY "c," c 2 h 6752 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6760 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6768 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6776 */
	{.type Absolute, {.p 1}},		/* dd 1 6784 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6792 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6800 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6808 */
	{.type Header, {.hdr { 5, "allot", /* C_allot = 6824 */ colon }}}, /* CENTRY "allot" allot 5 ; ( n -- ) here = here+n h 6832 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6840 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6848 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6856 */
	{.type Header, {.hdr { 5, "vallot", /* C_vallot = 6872 */ colon }}}, /* CENTRY "vallot" vallot 5 ; allot on the variable space ( n -- ) vhere = vhere+n h 6880 */
	{.type FromH0, {.p M_Vp}, .src = "dd M_Vp"},		/* dd M_Vp 6888 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6896 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6904 */
	{.type Header, {.hdr { 3, "pad", /* C_pad = 6920 */ colon }}}, /* CENTRY "pad" pad 3 h 6928 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6936 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6944 */
	{.type Absolute, {.p 256}},		/* dd 256 6952 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6960 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6968 */
	{.type Header, {.hdr { 5, "align", /* C_align = 6984 */ colon }}}, /* CENTRY "align" align 5 ; ( -- ) align here to a cell boundary h 6992 */
	{.type FromH0, {.p C_here}, .src = "dd C_here		; Dp @"},		/* dd C_here		; Dp @ 7000 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned	; here is aligned to a multiple of 8"},		/* dd C_aligned	; here is aligned to a multiple of 8 7008 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp			; store the aligned here at Dp"},		/* dd M_Dp			; store the aligned here at Dp 7016 */
	{.type FromH0, {.p M_store}, .src = "dd M_store		; Dp contains aligned_here"},		/* dd M_store		; Dp contains aligned_here 7024 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7032 */
	{.type Header, {.hdr { 6, "unused", /* C_unused = 7048 */ colon }}}, /* CENTRY "unused" unused 6 h 7056 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 7064 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7072 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 7080 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7088 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7096 */
	{.type Header, {.hdr { 2, "<#", /* C_fromhash = 7112 */ colon }}}, /* CENTRY "<#" fromhash 2 h 7120 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7128 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7136 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7144 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7152 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7160 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7168 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7176 */
	{.type Header, {.hdr { 1, "#", /* C_hash = 7192 */ colon }}}, /* CENTRY "#" hash 1 h 7200 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 7208 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7216 */
	{.type FromH0, {.p M_uslashmod}, .src = "dd M_uslashmod"},		/* dd M_uslashmod 7224 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7232 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7240 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7248 */
	{.type Absolute, {.p 9}},		/* dd 9 7256 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 7264 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7272 */
	{.type FromH0, {.p L92}, .src = "dd L92"},		/* dd L92 7280 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7288 */
	{.type Absolute, {.p 97}},		/* dd 97 7296 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7304 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7312 */
	{.type Absolute, {.p 10}},		/* dd 10 7320 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7328 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7336 */
	{.type FromH0, {.p L93}, .src = "dd L93"},		/* dd L93 7344 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7352 */
	{.type Absolute, {.p 48}},		/* dd 48 7360 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7368 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7376 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7384 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7392 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7400 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7408 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7416 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7424 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7432 */
	{.type Header, {.hdr { 2, "#s", /* C_hashs = 7448 */ colon }}}, /* CENTRY "#s" hashs 2 h 7456 */
	{.type FromH0, {.p C_hash}, .src = "dd C_hash"},		/* dd C_hash 7464 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7472 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7480 */
	{.type FromH0, {.p L96}, .src = "dd L96"},		/* dd L96 7488 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7496 */
	{.type FromH0, {.p L95}, .src = "dd L95"},		/* dd L95 7504 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7512 */
	{.type Header, {.hdr { 2, "#>", /* C_hashfrom = 7528 */ colon }}}, /* CENTRY "#>" hashfrom 2 h 7536 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 7544 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7552 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7560 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7568 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7576 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7584 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7592 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7600 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7608 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7616 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7624 */
	{.type Header, {.hdr { 4, "hold", /* C_hold = 7640 */ colon }}}, /* CENTRY "hold" hold 4 h 7648 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7656 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7664 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7672 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7680 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 7688 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7696 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 7704 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7712 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7720 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7728 */
	{.type Header, {.hdr { 4, "sign", /* C_sign = 7744 */ colon }}}, /* CENTRY "sign" sign 4 h 7752 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 7760 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7768 */
	{.type FromH0, {.p L100}, .src = "dd L100"},		/* dd L100 7776 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7784 */
	{.type Absolute, {.p 45}},		/* dd 45 7792 */
	{.type FromH0, {.p C_hold}, .src = "dd C_hold"},		/* dd C_hold 7800 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7808 */
	{.type Header, {.hdr { 1, ".", /* C_dot = 7824 */ colon }}}, /* CENTRY "." dot 1 ; print the top of stack ( n -- ) h 7832 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; ( n -- n n )"},		/* dd M_dup		; ( n -- n n ) 7840 */
	{.type FromH0, {.p C_abs}, .src = "dd C_abs		; ( n n -- n u )"},		/* dd C_abs		; ( n n -- n u ) 7848 */
	{.type FromH0, {.p C_fromhash}, .src = "dd C_fromhash	; pad = h+256; >num = pad+1024"},		/* dd C_fromhash	; pad = h+256; >num = pad+1024 7856 */
	{.type FromH0, {.p C_hashs}, .src = "dd C_hashs		; ( n u1 -- n n2 )"},		/* dd C_hashs		; ( n u1 -- n n2 ) 7864 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap		; ( n n2 -- n2 n )"},		/* dd M_xswap		; ( n n2 -- n2 n ) 7872 */
	{.type FromH0, {.p C_sign}, .src = "dd C_sign		; ( n2 n -- n2 )"},		/* dd C_sign		; ( n2 n -- n2 ) 7880 */
	{.type FromH0, {.p C_hashfrom}, .src = "dd C_hashfrom	; ( u1 -- a n )"},		/* dd C_hashfrom	; ( u1 -- a n ) 7888 */
	{.type FromH0, {.p C_type}, .src = "dd C_type		; ( a n -- )"},		/* dd C_type		; ( a n -- ) 7896 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 7904 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7912 */
	{.type Header, {.hdr { 2, ".r", /* C_dotr = 7928 */ colon }}}, /* CENTRY ".r" dotr 2 h 7936 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 7944 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7952 */
	{.type FromH0, {.p C_abs}, .src = "dd C_abs"},		/* dd C_abs 7960 */
	{.type FromH0, {.p C_fromhash}, .src = "dd C_fromhash"},		/* dd C_fromhash 7968 */
	{.type FromH0, {.p C_hashs}, .src = "dd C_hashs"},		/* dd C_hashs 7976 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7984 */
	{.type FromH0, {.p C_sign}, .src = "dd C_sign"},		/* dd C_sign 7992 */
	{.type FromH0, {.p C_hashfrom}, .src = "dd C_hashfrom"},		/* dd C_hashfrom 8000 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 8008 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 8016 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8024 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8032 */
	{.type Absolute, {.p 0}},		/* dd 0 8040 */
	{.type FromH0, {.p C_max}, .src = "dd C_max"},		/* dd C_max 8048 */
	{.type FromH0, {.p C_spaces}, .src = "dd C_spaces"},		/* dd C_spaces 8056 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 8064 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8072 */
	{.type Header, {.hdr { 3, "hex", /* C_hex = 8088 */ colon }}}, /* CENTRY "hex" hex 3 h 8096 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8104 */
	{.type Absolute, {.p 16}},		/* dd 16 8112 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8120 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8136 */
	{.type Header, {.hdr { 7, "decimal", /* C_decimal = 8152 */ colon }}}, /* CENTRY "decimal" decimal 7 h 8160 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8168 */
	{.type Absolute, {.p 10}},		/* dd 10 8176 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8184 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8192 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8200 */
	{.type Header, {.hdr { 5, "digit", /* C_digit = 8216 */ colon }}}, /* CENTRY "digit" digit 5 ; ( c -- ) h 8224 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8232 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8240 */
	{.type Absolute, {.p 65}},		/* dd 65 8248 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8256 */
	{.type Absolute, {.p 91}},		/* dd 91 8264 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8272 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8280 */
	{.type FromH0, {.p L106}, .src = "dd L106"},		/* dd L106 8288 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8296 */
	{.type Absolute, {.p 55}},		/* dd 55 8304 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8312 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8320 */
	{.type FromH0, {.p L107}, .src = "dd L107"},		/* dd L107 8328 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8336 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8344 */
	{.type Absolute, {.p 97}},		/* dd 97 8352 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8360 */
	{.type Absolute, {.p 123}},		/* dd 123 8368 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8376 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8384 */
	{.type FromH0, {.p L108}, .src = "dd L108"},		/* dd L108 8392 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8400 */
	{.type Absolute, {.p 87}},		/* dd 87 8408 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8416 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8424 */
	{.type FromH0, {.p L109}, .src = "dd L109"},		/* dd L109 8432 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8440 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8448 */
	{.type Absolute, {.p 48}},		/* dd 48 8456 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8464 */
	{.type Absolute, {.p 58}},		/* dd 58 8472 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8480 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8488 */
	{.type FromH0, {.p L110}, .src = "dd L110"},		/* dd L110 8496 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8504 */
	{.type Absolute, {.p 48}},		/* dd 48 8512 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8520 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8528 */
	{.type FromH0, {.p L111}, .src = "dd L111"},		/* dd L111 8536 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8544 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8552 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8560 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8568 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8576 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 8584 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 8592 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8600 */
	{.type FromH0, {.p L112}, .src = "dd L112"},		/* dd L112 8608 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 8616 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8624 */
	{.type FromH0, {.p L113}, .src = "dd L113"},		/* dd L113 8632 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8640 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8648 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8656 */
	{.type Header, {.hdr { 6, "number", /* C_number = 8672 */ colon }}}, /* CENTRY "number" number 6 ; ( a n1 -- n2 -1 | a n1 0 ) h 8680 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 -- n1 a )"},		/* dd M_xswap	; ( a n1 -- n1 a ) 8688 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n1 a -- n1 a a )"},		/* dd M_dup	; ( n1 a -- n1 a a ) 8696 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( n1 a a -- n1 a c )"},		/* dd M_cfetch	; ( n1 a a -- n1 a c ) 8704 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8712 */
	{.type Absolute, {.p 45}},		/* dd 45		; ( n1 a c -- n1 a c - ) 8720 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n1 a c -- n1 a f )"},		/* dd M_equal	; ( n1 a c -- n1 a f ) 8728 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; ( n1 a c -- n1 a )"},		/* dd M_cjump	; ( n1 a c -- n1 a ) 8736 */
	{.type FromH0, {.p L115}, .src = "dd L115		; c != -"},		/* dd L115		; c != - 8744 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; c == - ( n1 a -- n1 a+1 )"},		/* dd C_1plus	; c == - ( n1 a -- n1 a+1 ) 8752 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 8760 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 )"},		/* dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 ) 8768 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8776 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( a+1 n1-1 -- a+1 n1-1 -1 ) 8784 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1)"},		/* dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1) 8792 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8800 */
	{.type FromH0, {.p L116}, .src = "dd L116"},		/* dd L116 8808 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( n1 a -- a n1)"},		/* dd M_xswap	; ( n1 a -- a n1) 8816 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8824 */
	{.type Absolute, {.p 1}},		/* dd 1 8832 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1)"},		/* dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1) 8840 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a n1 -- a n1 n1 ) (R nr)"},		/* dd M_dup	; ( a n1 -- a n1 n1 ) (R nr) 8848 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1)"},		/* dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1) 8856 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8864 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a n1 -- a n1 0) (R nr n1) 8872 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1)"},		/* dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1) 8880 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8888 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a 0 n1 -- a 0 n1 0) (R nr n1) 8896 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1) 8904 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8912 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1) 8920 */
	{.type FromH0, {.p M_multiply}, .src = "dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1) 8928 */
	{.type FromH0, {.p M_over}, .src = "dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1)"},		/* dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1) 8936 */
	{.type FromH0, {.p M_i}, .src = "dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1) 8944 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1) 8952 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1)"},		/* dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1) 8960 */
	{.type FromH0, {.p C_digit}, .src = "dd C_digit"},		/* dd C_digit 8968 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8976 */
	{.type FromH0, {.p L118}, .src = "dd L118"},		/* dd L118 8984 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 8992 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9000 */
	{.type FromH0, {.p L119}, .src = "dd L119"},		/* dd L119 9008 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9016 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 9024 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9032 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9040 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9048 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 9056 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9064 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 9072 */
	{.type FromH0, {.p L117}, .src = "dd L117"},		/* dd L117 9080 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9088 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9096 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 9104 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9112 */
	{.type FromH0, {.p M_multiply}, .src = "dd M_multiply"},		/* dd M_multiply 9120 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 9128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9136 */
	{.type Header, {.hdr { 5, "abort", /* C_abort = 9152 */ colon }}}, /* CENTRY "abort" abort 5 h 9160 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec"},		/* dd MV_Abortvec 9168 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9176 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 9184 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9192 */
	{.type Header, {.hdr { 6, "source", /* C_source = 9208 */ colon }}}, /* CENTRY "source" source 6 h 9216 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9224 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9240 */
	{.type Header, {.hdr { 13, "current-input", /* C_current_input = 9264 */ colon }}}, /* CENTRY "current-input" current_input 13 ; ( -- c ) read the next character from the location in Sourcebuf h 9272 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9280 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9288 */
	{.type FromH0, {.p C_source}, .src = "dd C_source"},		/* dd C_source 9296 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus		; Sourcebuf + >In"},		/* dd M_plus		; Sourcebuf + >In 9304 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 9312 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9320 */
	{.type Header, {.hdr { 10, "save-input", /* C_save_input = 9344 */ colon }}}, /* CENTRY "save-input" save_input 10 h 9352 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 9360 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9368 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9376 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9384 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9392 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9400 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9408 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 9416 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9424 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9432 */
	{.type Absolute, {.p 5}},		/* dd 5 9440 */
	{.type FromH0, {.p MV_Ninputs}, .src = "dd MV_Ninputs"},		/* dd MV_Ninputs 9448 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; Ninputs++"},		/* dd C_plusstore	; Ninputs++ 9456 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9464 */
	{.type Header, {.hdr { 13, "default-input", /* C_default_input = 9488 */ colon }}}, /* CENTRY "default-input" default_input 13 h 9496 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 9504 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9512 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9520 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9528 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9536 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib"},		/* dd M_Tib 9544 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9552 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9560 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 9568 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9576 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9584 */
	{.type Header, {.hdr { 13, "restore-input", /* C_restore_input = 9608 */ colon }}}, /* CENTRY "restore-input" restore_input 13 ; ( <input>|empty -- f ) h 9616 */
	{.type FromH0, {.p MV_Ninputs}, .src = "dd MV_Ninputs	; if Ninputs == 0, leave 0 on the stack. Or, Ninputs--"},		/* dd MV_Ninputs	; if Ninputs == 0, leave 0 on the stack. Or, Ninputs-- 9624 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9632 */
	{.type FromH0, {.p C_0neq}, .src = "dd C_0neq"},		/* dd C_0neq 9640 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9648 */
	{.type FromH0, {.p L300}, .src = "dd L300"},		/* dd L300 9656 */
	{.type FromH0, {.p MV_Ninputs}, .src = "dd MV_Ninputs	; there are <input>'s pending on the stack"},		/* dd MV_Ninputs	; there are <input>'s pending on the stack 9664 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9672 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 9680 */
	{.type FromH0, {.p MV_Ninputs}, .src = "dd MV_Ninputs"},		/* dd MV_Ninputs 9688 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9696 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9704 */
	{.type FromH0, {.p L301}, .src = "dd L301		; ( <input> -- <input>)"},		/* dd L301		; ( <input> -- <input>) 9712 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9720 */
	{.type Absolute, {.p 0}},		/* dd 0 9728 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 9736 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9744 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9752 */
	{.type Absolute, {.p 5}},		/* dd 5 9760 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 9768 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9776 */
	{.type FromH0, {.p L133}, .src = "dd L133"},		/* dd L133 9784 */
	{.type FromH0, {.p C_default_input}, .src = "dd C_default_input"},		/* dd C_default_input 9792 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 9800 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9808 */
	{.type FromH0, {.p L134}, .src = "dd L134"},		/* dd L134 9816 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 9824 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9832 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9840 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9848 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9856 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9864 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9872 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9880 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 9888 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9896 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 9904 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9912 */
	{.type Header, {.hdr { 14, "?restore-input", /* C_qrestore_input = 9936 */ colon }}}, /* CENTRY "?restore-input" qrestore_input 14 ; ( <input> -- f ) h 9944 */
	{.type FromH0, {.p C_restore_input}, .src = "dd C_restore_input"},		/* dd C_restore_input 9952 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 9960 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9968 */
	{.type FromH0, {.p L136}, .src = "dd L136"},		/* dd L136 9976 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 9984 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9992 */
	{.type FromH0, {.p L137}, .src = "dd L137"},		/* dd L137 10000 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10008 */
	{.type Absolute, {.p 23}},		/* dd 23 10016 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 10024 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 10032 */
	{.type FromH0, {.p C_depth}, .src = "dd C_depth"},		/* dd C_depth 10040 */
	{.type FromH0, {.p C_dot}, .src = "dd C_dot"},		/* dd C_dot 10048 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 10056 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 10064 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10072 */
	{.type Header, {.hdr { 10, "next-input", /* C_next_input = 10096 */ colon }}}, /* CENTRY "next-input" next_input 10 ; when >In < >Limit ( -- true c ). ( -- 0 false ) otherwise h 10104 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10112 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10120 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 10128 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10136 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 10144 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10152 */
	{.type FromH0, {.p L139}, .src = "dd L139	; >In >= >Limit"},		/* dd L139	; >In >= >Limit 10160 */
	{.type FromH0, {.p C_true}, .src = "dd C_true	; >In < >Limit"},		/* dd C_true	; >In < >Limit 10168 */
	{.type FromH0, {.p C_current_input}, .src = "dd C_current_input	; ( -- c )"},		/* dd C_current_input	; ( -- c ) 10176 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 10184 */
	{.type FromH0, {.p L140}, .src = "dd L140"},		/* dd L140 10192 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10200 */
	{.type Absolute, {.p 0}},		/* dd 0 10208 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 10216 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10224 */
	{.type Header, {.hdr { 5, "parse", /* C_parse = 10240 */ colon }}}, /* CENTRY "parse" parse 5 ; ( c -- a ) Place the counted string in the address in Wordbuf and return that address. c = word delimiter. h 10248 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; ( c -- ) (R -- c )"},		/* dd M_rpush		; ( c -- ) (R -- c ) 10256 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf"},		/* dd MV_Wordbuf 10264 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( -- Wordb )"},		/* dd M_fetch		; ( -- Wordb ) 10272 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus		; ( Wordb -- Wordb+1 )"},		/* dd C_1plus		; ( Wordb -- Wordb+1 ) 10280 */
	{.type FromH0, {.p C_next_input}, .src = "dd C_next_input ; ( Wordb+1 -- Wordb+1 f c )"},		/* dd C_next_input ; ( Wordb+1 -- Wordb+1 f c ) 10288 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c )"},		/* dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c ) 10296 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) )"},		/* dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) ) 10304 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 10312 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10320 */
	{.type FromH0, {.p L143}, .src = "dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew"},		/* dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew 10328 */
	{.type FromH0, {.p C_current_input}, .src = "dd C_current_input	; ( Wordb+1 -- Wordb+1 c )"},		/* dd C_current_input	; ( Wordb+1 -- Wordb+1 c ) 10336 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 10344 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1"},		/* dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1 10352 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus		; ( Wordb+1 -- Wordb+2 )"},		/* dd C_1plus		; ( Wordb+1 -- Wordb+2 ) 10360 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10368 */
	{.type Absolute, {.p 1}},		/* dd 1 10376 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10384 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10392 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 10400 */
	{.type FromH0, {.p L142}, .src = "dd L142		; ( Wordb+2 ) repeat"},		/* dd L142		; ( Wordb+2 ) repeat 10408 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10416 */
	{.type Absolute, {.p 1}},		/* dd 1 10424 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10432 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10440 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- )"},		/* dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- ) 10448 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; (Wordb+1 c -- Wordb+1)"},		/* dd M_drop		; (Wordb+1 c -- Wordb+1) 10456 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf"},		/* dd MV_Wordbuf 10464 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb)"},		/* dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb) 10472 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb)"},		/* dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb) 10480 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb)"},		/* dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb) 10488 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb)"},		/* dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb) 10496 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb)"},		/* dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb) 10504 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb)"},		/* dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb) 10512 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now."},		/* dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now. 10520 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( -- Wordb) (R Wordb -- )"},		/* dd M_rpop		; ( -- Wordb) (R Wordb -- ) 10528 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10536 */
	{.type Header, {.hdr { 4, "word", /* C_word = 10552 */ colon }}}, /* CENTRY "word" word 4 ; ( c -- a ) skip the c"s. Placed the counted string in a (as in Wordbuf) h 10560 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- ) (R -- c )"},		/* dd M_rpush	; ( -- ) (R -- c ) 10568 */
	{.type FromH0, {.p C_next_input}, .src = "dd C_next_input ; ( -- f c2 ) (R c1 -- )"},		/* dd C_next_input ; ( -- f c2 ) (R c1 -- ) 10576 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial )"},		/* dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial ) 10584 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial )"},		/* dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial ) 10592 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial )"},		/* dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial ) 10600 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10608 */
	{.type FromH0, {.p L146}, .src = "dd L146		; >In >= >Limit || cinitial != cnew"},		/* dd L146		; >In >= >Limit || cinitial != cnew 10616 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal	; >In < >Limit && cinitial == cnew"},		/* dd M_literal	; >In < >Limit && cinitial == cnew 10624 */
	{.type Absolute, {.p 1}},		/* dd 1 10632 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10640 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10648 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump		; repeat"},		/* dd M_jump		; repeat 10656 */
	{.type FromH0, {.p L145}, .src = "dd L145"},		/* dd L145 10664 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character"},		/* dd M_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character 10672 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 10680 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10688 */
	{.type Header, {.hdr { 6, "accept", /* C_accept = 10704 */ colon }}}, /* CENTRY "accept" accept 6 ; ( a n -- n ) get line or n chars or EOF from input and store at a h 10712 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( n a -- )"},		/* dd M_xswap	; ( n a -- ) 10720 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n a a -- )"},		/* dd M_dup	; ( n a a -- ) 10728 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 10736 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( n -- ) (R a a -- )"},		/* dd M_rpush	; ( n -- ) (R a a -- ) 10744 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup	; ( n n -- ) (R a a -- )"},		/* dd C_qdup	; ( n n -- ) (R a a -- ) 10752 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; (if)"},		/* dd M_cjump	; (if) 10760 */
	{.type FromH0, {.p L149}, .src = "dd L149	; n == 0"},		/* dd L149	; n == 0 10768 */
	{.type FromH0, {.p C_key}, .src = "dd C_key	; n > 0 ( n -- n c )"},		/* dd C_key	; n > 0 ( n -- n c ) 10776 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( -- n c c )"},		/* dd M_dup	; ( -- n c c ) 10784 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10792 */
	{.type Absolute, {.p 10}},		/* dd 10		; ( -- n c c 10 ) 10800 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n c c 10 -- n c f ) checking for newline"},		/* dd M_equal	; ( n c c 10 -- n c f ) checking for newline 10808 */
	{.type FromH0, {.p M_over}, .src = "dd M_over	; ( -- n c f c )"},		/* dd M_over	; ( -- n c f c ) 10816 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10824 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( -- n c f c -1 ) 10832 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( -- n c f1 f2 )"},		/* dd M_equal	; ( -- n c f1 f2 ) 10840 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor	; ( -- n c f )"},		/* dd M_binor	; ( -- n c f ) 10848 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10856 */
	{.type FromH0, {.p L150}, .src = "dd L150"},		/* dd L150 10864 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop	; n == -1 || n == 10 (	-- )"},		/* dd C_2drop	; n == -1 || n == 10 (	-- ) 10872 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 10880 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 10888 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( -- a2-a1 )"},		/* dd M_minus	; ( -- a2-a1 ) 10896 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; ( -- n ) (R -- )"},		/* dd M_exitcolon	; ( -- n ) (R -- ) 10904 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( n c a -- ) (R a a -- )"},		/* dd M_rfetch	; ( n c a -- ) (R a a -- ) 10912 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; store the character at a"},		/* dd M_cstore	; store the character at a 10920 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( n a -- ) (R a -- )"},		/* dd M_rpop	; ( n a -- ) (R a -- ) 10928 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 10936 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address"},		/* dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address 10944 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; ( n -- n-1 )"},		/* dd C_1minus	; ( n -- n-1 ) 10952 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 10960 */
	{.type FromH0, {.p L148}, .src = "dd L148	; loop again for the next character"},		/* dd L148	; loop again for the next character 10968 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 )"},		/* dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 ) 10976 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( a2 a1 -- ) (R a1 -- )"},		/* dd M_rpop	; ( a2 a1 -- ) (R a1 -- ) 10984 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( a2 a1 -- a2-a1 )"},		/* dd M_minus	; ( a2 a1 -- a2-a1 ) 10992 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11000 */
	{.type Header, {.hdr { 5, "query", /* C_query = 11016 */ colon }}}, /* CENTRY "query" query 5 ; read from input stream into the Text Input Buffer h 11024 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 11032 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; clear EOF flag"},		/* dd C_off		; clear EOF flag 11040 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top"},		/* dd M_Tib	; constant puts address of tibuffer on the top 11048 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11056 */
	{.type Absolute, {.p 4096}},		/* dd 4096	; ( tibuffer -- tibuffer 4096 ) 11064 */
	{.type FromH0, {.p C_accept}, .src = "dd C_accept ; ( tibuffer 4096 -- n )"},		/* dd C_accept ; ( tibuffer 4096 -- n ) 11072 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n -- n n )"},		/* dd M_dup	; ( n -- n n ) 11080 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq	; ( n n -- n f )"},		/* dd C_0eq	; ( n n -- n f ) 11088 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 11096 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11104 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; n == 0 && EOF"},		/* dd M_binand	; n == 0 && EOF 11112 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11120 */
	{.type FromH0, {.p L152}, .src = "dd L152		; false condition"},		/* dd L152		; false condition 11128 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; n == 0 && EOF ( n -- )"},		/* dd M_drop	; n == 0 && EOF ( n -- ) 11136 */
	{.type FromH0, {.p C_qrestore_input}, .src = "dd C_qrestore_input"},		/* dd C_qrestore_input 11144 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11152 */
	{.type FromH0, {.p L153}, .src = "dd L153"},		/* dd L153 11160 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 11168 */
	{.type FromH0, {.p M_store}, .src = "dd M_store		; number of characters to read >Limit = n"},		/* dd M_store		; number of characters to read >Limit = n 11176 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 11184 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; start from 0 >In = 0"},		/* dd C_off		; start from 0 >In = 0 11192 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11200 */
	{.type Header, {.hdr { 6, "refill", /* C_refill = 11216 */ colon }}}, /* CENTRY "refill" refill 6 h 11224 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 11232 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11240 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11248 */
	{.type FromH0, {.p L155}, .src = "dd L155"},		/* dd L155 11256 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 11264 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11272 */
	{.type FromH0, {.p L156}, .src = "dd L156"},		/* dd L156 11280 */
	{.type FromH0, {.p C_query}, .src = "dd C_query"},		/* dd C_query 11288 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 11296 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11304 */
	{.type Header, {.hdr { 8, "findname", /* C_findname = 11328 */ colon }}}, /* CENTRY "findname" findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names h 11336 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 11344 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11352 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop"},		/* dd M_Dtop 11360 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; get latest dictionary link"},		/* dd M_fetch	; get latest dictionary link 11368 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 11376 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11384 */
	{.type FromH0, {.p L159}, .src = "dd L159	; seached until the first dictionary entry get out"},		/* dd L159	; seached until the first dictionary entry get out 11392 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a )"},		/* dd M_dup	; ( a -- a a ) 11400 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; ( a a -- a a+8) lenth + initial name address"},		/* dd C_cellplus	; ( a a -- a a+8) lenth + initial name address 11408 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name"},		/* dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name 11416 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11424 */
	{.type Absolute, {.p 64}},		/* dd 64		; check the reveal'ed flag 1=hidden, 0=reveal 11432 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; if hidden, goto L161 else L160"},		/* dd M_binand	; if hidden, goto L161 else L160 11440 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11448 */
	{.type FromH0, {.p L160}, .src = "dd L160"},		/* dd L160 11456 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; smudge'd dictionary entry, get the previous entry"},		/* dd M_fetch	; smudge'd dictionary entry, get the previous entry 11464 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11472 */
	{.type FromH0, {.p L161}, .src = "dd L161"},		/* dd L161 11480 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a1 -- a1 a1)"},		/* dd M_dup	; ( a1 -- a1 a1) 11488 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; ( a1 a1 -- a1 a1+8)"},		/* dd C_cellplus	; ( a1 a1 -- a1 a1+8) 11496 */
	{.type FromH0, {.p C_count}, .src = "dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n )"},		/* dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n ) 11504 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11512 */
	{.type Absolute, {.p 63}},		/* dd 63 11520 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len )"},		/* dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len ) 11528 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 11536 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11544 */
	{.type FromH0, {.p C_count}, .src = "dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 )"},		/* dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 ) 11552 */
	{.type FromH0, {.p C_compare}, .src = "dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name"},		/* dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name 11560 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq	; found a match?"},		/* dd C_0eq	; found a match? 11568 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11576 */
	{.type FromH0, {.p L162}, .src = "dd L162		; no match"},		/* dd L162		; no match 11584 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; match found"},		/* dd C_cellplus	; match found 11592 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 11600 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11608 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11616 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11624 */
	{.type FromH0, {.p L158}, .src = "dd L158"},		/* dd L158 11632 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 11640 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11648 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 11656 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11664 */
	{.type Header, {.hdr { 4, "find", /* C_find = 11680 */ colon }}}, /* CENTRY "find" find 4 ; ( a1 -- a2 f )? h 11688 */
	{.type FromH0, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 11696 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11704 */
	{.type FromH0, {.p L164}, .src = "dd L164"},		/* dd L164 11712 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 11720 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 11728 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 11736 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 11744 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11752 */
	{.type Absolute, {.p 63}},		/* dd 63 11760 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 11768 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11776 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 11784 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 11792 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 11800 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11808 */
	{.type Absolute, {.p 128}},		/* dd 128 11816 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 11824 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11832 */
	{.type FromH0, {.p L165}, .src = "dd L165"},		/* dd L165 11840 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11848 */
	{.type Absolute, {.p 1}},		/* dd 1 11856 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11864 */
	{.type FromH0, {.p L166}, .src = "dd L166"},		/* dd L166 11872 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11880 */
	{.type Absolute, {.p -1}},		/* dd -1 11888 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11896 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11904 */
	{.type FromH0, {.p L167}, .src = "dd L167"},		/* dd L167 11912 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 11920 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11928 */
	{.type Header, {.hdr { 1, "'", /* C_single_quote = 11944 */ colon }}}, /* CENTRY "'" single_quote 1 h 11952 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 11960 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 11968 */
	{.type FromH0, {.p C_find}, .src = "dd C_find"},		/* dd C_find 11976 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 11984 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11992 */
	{.type FromH0, {.p L169}, .src = "dd L169"},		/* dd L169 12000 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 12008 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 12016 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12024 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12032 */
	{.type FromH0, {.p L170}, .src = "dd L170"},		/* dd L170 12040 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12048 */
	{.type Absolute, {.p 3}},		/* dd 3 12056 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12064 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12072 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12080 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12088 */
	{.type Header, {.hdr { 6, "?stack", /* C_qstack = 12104 */ colon }}}, /* CENTRY "?stack" qstack 6 h 12112 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 12120 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 12128 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 12136 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12144 */
	{.type FromH0, {.p L172}, .src = "dd L172"},		/* dd L172 12152 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12160 */
	{.type FromH0, {.p L173}, .src = "dd L173"},		/* dd L173 12168 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12176 */
	{.type Absolute, {.p 16}},		/* dd 16 12184 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12192 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12200 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12208 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12216 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup ; debug code to show the word found"},		/* dd M_dup ; debug code to show the word found 12224 */
	{.type FromH0, {.p C_count}, .src = "dd C_count ; ( -- a n)"},		/* dd C_count ; ( -- a n) 12232 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap ; ( -- n a)"},		/* dd M_xswap ; ( -- n a) 12240 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 12248 */
	{.type FromH0, {.p M_fswrite}, .src = "dd M_fswrite"},		/* dd M_fswrite 12256 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 12264 */
	{.type Header, {.hdr { 9, "interpret", /* C_interpret = 12288 */ colon }}}, /* CENTRY "interpret" interpret 9 ; there is stuff in TIB to be interpreted >In and >Limit are set h 12296 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 12304 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( bl -- a ) a = address of counted string"},		/* dd C_word	; ( bl -- a ) a = address of counted string 12312 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12320 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 12328 */
	{.type FromH0, {.p C_0neq}, .src = "dd C_0neq"},		/* dd C_0neq 12336 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12344 */
	{.type FromH0, {.p L176}, .src = "dd L176	; count at a = 0"},		/* dd L176	; count at a = 0 12352 */
	{.type FromH0, {.p C_find}, .src = "dd C_find	; ( a -- a1 f ) a = address of counted string"},		/* dd C_find	; ( a -- a1 f ) a = address of counted string 12360 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12368 */
	{.type FromH0, {.p L177}, .src = "dd L177"},		/* dd L177 12376 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute	; found in dictionary, execute"},		/* dd M_execute	; found in dictionary, execute 12384 */
	{.type FromH0, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 12392 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12400 */
	{.type FromH0, {.p L178}, .src = "dd L178"},		/* dd L178 12408 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 12416 */
	{.type FromH0, {.p C_number}, .src = "dd C_number"},		/* dd C_number 12424 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 12432 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12440 */
	{.type FromH0, {.p L179}, .src = "dd L179"},		/* dd L179 12448 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 12456 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12464 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12472 */
	{.type FromH0, {.p L180}, .src = "dd L180	; error I?"},		/* dd L180	; error I? 12480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12488 */
	{.type Absolute, {.p 3}},		/* dd 3 12496 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12504 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12512 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12520 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12528 */
	{.type FromH0, {.p L175}, .src = "dd L175"},		/* dd L175 12536 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; count at a = 0 ( a -- )"},		/* dd M_drop	; count at a = 0 ( a -- ) 12544 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12552 */
	{.type Header, {.hdr { 6, "create", /* C_create = 12568 */ colon }}}, /* CENTRY "create" create 6 ; compiles dictionary header until the pfa (link, len, name, cfa) h 12576 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 12584 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here )"},		/* dd C_here	; ( -- here ) 12592 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- ) (R -- linkaddr )"},		/* dd M_rpush	; ( -- ) (R -- linkaddr ) 12600 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop	; ( -- Dtop ) (R -- linkaddr )"},		/* dd M_Dtop	; ( -- Dtop ) (R -- linkaddr ) 12608 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr )"},		/* dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr ) 12616 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; ( dtop -- ) (R -- linkaddr )"},		/* dd C_comma	; ( dtop -- ) (R -- linkaddr ) 12624 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 12632 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; get the word from the input stream ( c -- a ) skip any c. Placed the counted string in a (as in Wordbuf)"},		/* dd C_word	; get the word from the input stream ( c -- a ) skip any c. Placed the counted string in a (as in Wordbuf) 12640 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a ) (R -- linkaddr )"},		/* dd M_dup	; ( a -- a a ) (R -- linkaddr ) 12648 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a -- a len ) (R -- linkaddr )"},		/* dd M_cfetch	; ( a a -- a len ) (R -- linkaddr ) 12656 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( a len -- a len here ) (R -- linkaddr )"},		/* dd C_here	; ( a len -- a len here ) (R -- linkaddr ) 12664 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr )"},		/* dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr ) 12672 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte"},		/* dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte 12680 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr )"},		/* dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr ) 12688 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 )"},		/* dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 ) 12696 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 )"},		/* dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 ) 12704 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- len+1 ) (R -- linkaddr )"},		/* dd M_rpop	; ( -- len+1 ) (R -- linkaddr ) 12712 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1"},		/* dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1 12720 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 12728 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12736 */
	{.type FromH0, {.p M_variable}, .src = "dd M_variable"},		/* dd M_variable 12744 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( -- variablecfa) (R -- linkaddr )"},		/* dd M_fetch	; ( -- variablecfa) (R -- linkaddr ) 12752 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; ( -- ) put the variablecfa into the cfa"},		/* dd C_comma	; ( -- ) put the variablecfa into the cfa 12760 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- linkaddr) (R -- )"},		/* dd M_rpop	; ( -- linkaddr) (R -- ) 12768 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop"},		/* dd M_Dtop 12776 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; Dtop = just created link address"},		/* dd M_store	; Dtop = just created link address 12784 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12792 */
	{.type Header, {.hdr { 8, "variable", /* C_variable = 12816 */ colon }}}, /* CENTRY "variable" variable 8 ; compile to put the vhere then on the stack h 12824 */
	{.type FromH0, {.p C_create}, .src = "dd C_create"},		/* dd C_create 12832 */
	{.type FromH0, {.p C_vhere}, .src = "dd C_vhere"},		/* dd C_vhere 12840 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; put the next available variable location in pfa"},		/* dd C_comma	; put the next available variable location in pfa 12848 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12856 */
	{.type Absolute, {.p 1}},		/* dd 1 12864 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 12872 */
	{.type FromH0, {.p C_vallot}, .src = "dd C_vallot	; vhere = vhere+8, stored at Vp"},		/* dd C_vallot	; vhere = vhere+8, stored at Vp 12880 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12888 */
	{.type Header, {.hdr { 8, "constant", /* C_constant = 12912 */ colon }}}, /* CENTRY "constant" constant 8 ; ( n -- ) do the same as variable but change the cfa to (constant) h 12920 */
	{.type FromH0, {.p C_create}, .src = "dd C_create	; create dictionary header upto the cfa"},		/* dd C_create	; create dictionary header upto the cfa 12928 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12936 */
	{.type FromH0, {.p M_constant}, .src = "dd M_constant"},		/* dd M_constant 12944 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Contstantcfa -- (constant) )"},		/* dd M_fetch	; ( Contstantcfa -- (constant) ) 12952 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( (constant) -- (constant) here )"},		/* dd C_here	; ( (constant) -- (constant) here ) 12960 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12968 */
	{.type Absolute, {.p 1}},		/* dd 1 12976 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells	; ( (constant) here -- (constant) here 8 )"},		/* dd C_cells	; ( (constant) here -- (constant) here 8 ) 12984 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( (constant) here 8 -- (constant) here-8 )"},		/* dd M_minus	; ( (constant) here 8 -- (constant) here-8 ) 12992 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant) "},		/* dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant)  13000 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; store n into the dictionary"},		/* dd C_comma	; store n into the dictionary 13008 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13016 */
	{.type Header, {.hdr { 9, "immediate", /* C_immediate = 13040 */ colon }}}, /* CENTRY "immediate" immediate 9 h 13048 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 13056 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13064 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 13072 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13080 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13088 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13096 */
	{.type Absolute, {.p 128}},		/* dd 128 13104 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 13112 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 13120 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 13128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13136 */
	{.type Header, {.hdr { 4, ">cfa", /* C_tocfa = 13152 */ colon }}}, /* CENTRY ">cfa" tocfa 4 h 13160 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13168 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13176 */
	{.type Absolute, {.p 63}},		/* dd 63 13184 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 13192 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 13200 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 13208 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13216 */
	{.type Header, {.hdr { 7, "compile", /* C_compile = 13232 */ colon }}}, /* CENTRY "compile" compile 7 h 13240 */
	{.type FromH0, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 13248 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13256 */
	{.type FromH0, {.p L188}, .src = "dd L188"},		/* dd L188 13264 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13272 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13280 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13288 */
	{.type Absolute, {.p 128}},		/* dd 128 13296 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 13304 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13312 */
	{.type FromH0, {.p L189}, .src = "dd L189"},		/* dd L189 13320 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa	; immediate"},		/* dd C_tocfa	; immediate 13328 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 13336 */
	{.type FromH0, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 13344 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13352 */
	{.type FromH0, {.p L190}, .src = "dd L190"},		/* dd L190 13360 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 13368 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 13376 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13384 */
	{.type FromH0, {.p L191}, .src = "dd L191"},		/* dd L191 13392 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13400 */
	{.type FromH0, {.p C_number}, .src = "dd C_number"},		/* dd C_number 13408 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 13416 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13424 */
	{.type FromH0, {.p L192}, .src = "dd L192"},		/* dd L192 13432 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 13440 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13448 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13456 */
	{.type FromH0, {.p L193}, .src = "dd L193"},		/* dd L193 13464 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13472 */
	{.type Absolute, {.p 3}},		/* dd 3 13480 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13488 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 13496 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 13504 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13512 */
	{.type FromH0, {.p L194}, .src = "dd L194"},		/* dd L194 13520 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13528 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13536 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 13544 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 13552 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13560 */
	{.type Header, {.hdr { 1, "]", /* C_close_bracket = 13576 */ colon }}}, /* CENTRY "]" close_bracket 1 h 13584 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 13592 */
	{.type FromH0, {.p C_on}, .src = "dd C_on"},		/* dd C_on 13600 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 13608 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 13616 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13624 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13632 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 13640 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13648 */
	{.type FromH0, {.p L197}, .src = "dd L197"},		/* dd L197 13656 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 13664 */
	{.type FromH0, {.p C_refill}, .src = "dd C_refill"},		/* dd C_refill 13672 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13680 */
	{.type FromH0, {.p L198}, .src = "dd L198"},		/* dd L198 13688 */
	{.type FromH0, {.p C_compile}, .src = "dd C_compile"},		/* dd C_compile 13696 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 13704 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13712 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13720 */
	{.type FromH0, {.p L199}, .src = "dd L199"},		/* dd L199 13728 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13736 */
	{.type FromH0, {.p L196}, .src = "dd L196"},		/* dd L196 13744 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13752 */
	{.type IHeader, {.hdr { 1, "[", /* CI_open_bracket = 13768 */ colon }}}, /* CIENTRY "[" open_bracket 1 h 13776 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 13784 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 13792 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13800 */
	{.type Header, {.hdr { 6, "smudge", /* C_smudge = 13816 */ colon }}}, /* CENTRY "smudge" smudge 6 h 13824 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 13832 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13840 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 13848 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13856 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13864 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13872 */
	{.type Absolute, {.p 64}},		/* dd 64 13880 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 13888 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 13896 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 13904 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13912 */
	{.type Header, {.hdr { 6, "reveal", /* C_reveal = 13928 */ colon }}}, /* CENTRY "reveal" reveal 6 h 13936 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 13944 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13952 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 13960 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13968 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13976 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13984 */
	{.type Absolute, {.p 64}},		/* dd 64 13992 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 14000 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 14008 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 14016 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 14024 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14032 */
	{.type Header, {.hdr { 1, ":", /* C_colon = 14048 */ colon }}}, /* CENTRY ":" colon 1 h 14056 */
	{.type FromH0, {.p C_create}, .src = "dd C_create	; create a dictionary header with (variable) at cfa"},		/* dd C_create	; create a dictionary header with (variable) at cfa 14064 */
	{.type FromH0, {.p C_smudge}, .src = "dd C_smudge"},		/* dd C_smudge 14072 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14080 */
	{.type FromH0, {.p M_colon}, .src = "dd M_colon"},		/* dd M_colon 14088 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon"},		/* dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon 14096 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( (colon) -- (colon) here )"},		/* dd C_here	; ( (colon) -- (colon) here ) 14104 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14112 */
	{.type Absolute, {.p 1}},		/* dd 1 14120 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 14128 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( (colon) here -- (colon) here-8 )"},		/* dd M_minus	; ( (colon) here -- (colon) here-8 ) 14136 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon"},		/* dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon 14144 */
	{.type FromH0, {.p C_close_bracket}, .src = "dd C_close_bracket"},		/* dd C_close_bracket 14152 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14160 */
	{.type IHeader, {.hdr { 1, ";", /* CI_semicolon = 14176 */ colon }}}, /* CIENTRY ";" semicolon 1 h 14184 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14192 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14200 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14208 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 14216 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 14224 */
	{.type FromH0, {.p C_reveal}, .src = "dd C_reveal"},		/* dd C_reveal 14232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14240 */
	{.type IHeader, {.hdr { 7, "recurse", /* CI_recurse = 14256 */ colon }}}, /* CIENTRY "recurse" recurse 7 h 14264 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 14272 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14280 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 14288 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 14296 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14304 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14312 */
	{.type Header, {.hdr { 4, "char", /* C_char = 14328 */ colon }}}, /* CENTRY "char" char 4 ; ( -- c ) fetch the first character of the next word from input h 14336 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 14344 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( c -- a ) puts the address of the counted string from the input on the stack"},		/* dd C_word	; ( c -- a ) puts the address of the counted string from the input on the stack 14352 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; skip the count"},		/* dd C_1plus	; skip the count 14360 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; fetch the first character"},		/* dd M_cfetch	; fetch the first character 14368 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14376 */
	{.type Header, {.hdr { 7, "literal", /* C_literal = 14392 */ colon }}}, /* CENTRY "literal" literal 7 ; ( n -- ) adds (literal) n to the dictionary h 14400 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14408 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14416 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14424 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14432 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14440 */
	{.type Header, {.hdr { 8, "sliteral", /* C_sliteral = 14464 */ colon }}}, /* CENTRY "sliteral" sliteral 8 ; ( -- ) adds (sliteral) a n to the dictionary h 14472 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14480 */
	{.type FromH0, {.p M_sliteral}, .src = "dd M_sliteral"},		/* dd M_sliteral 14488 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; adds (sliteral) to the dictionary"},		/* dd C_comma	; adds (sliteral) to the dictionary 14496 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here)"},		/* dd C_here	; ( -- here) 14504 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14512 */
	{.type Absolute, {.p 34}},		/* dd 34		; ascii value of " 14520 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse	; ( here \" -- here a ) \" = word delimiter. a = address of counted string (in Wordbuf)."},		/* dd C_parse	; ( here \" -- here a ) \" = word delimiter. a = address of counted string (in Wordbuf). 14528 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( here a -- here a a )"},		/* dd M_dup	; ( here a -- here a a ) 14536 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( here a a -- here a n )"},		/* dd M_cfetch	; ( here a a -- here a n ) 14544 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( here a n -- here a n+1 ) n+1 as 1 for the count and n for the length of the string"},		/* dd C_1plus	; ( here a n -- here a n+1 ) n+1 as 1 for the count and n for the length of the string 14552 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( here a n+1 -- here a ) (R -- n+1)"},		/* dd M_rpush	; ( here a n+1 -- here a ) (R -- n+1) 14560 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( here a -- a here ) (R -- n+1)"},		/* dd M_xswap	; ( here a -- a here ) (R -- n+1) 14568 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( a here -- a here n+1 ) (R -- n+1 )"},		/* dd M_rfetch	; ( a here -- a here n+1 ) (R -- n+1 ) 14576 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; ( a here n+1 -- ) moves n+1 from a to here"},		/* dd M_cmove	; ( a here n+1 -- ) moves n+1 from a to here 14584 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- n+1 ) (R -- )"},		/* dd M_rpop	; ( -- n+1 ) (R -- ) 14592 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( n+1 -- ) here = here+n+1"},		/* dd C_allot	; ( n+1 -- ) here = here+n+1 14600 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; align here"},		/* dd C_align	; align here 14608 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14616 */
	{.type Header, {.hdr { 6, "string", /* C_string = 14632 */ colon }}}, /* CENTRY "string" string 6 ; ( c -- ) h 14640 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 14648 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14656 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14664 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 14672 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 14680 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 14688 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 14696 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 14704 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 14712 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 14720 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14728 */
	{.type IHeader, {.hdr { 6, "[char]", /* CI_char_brackets = 14744 */ colon }}}, /* CIENTRY "[char]" char_brackets 6 ; take the next character from the input stream during compilation h 14752 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 14760 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 14768 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 14776 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14784 */
	{.type FromH0, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 14792 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14800 */
	{.type IHeader, {.hdr { 3, "[']", /* CI_quote_brackets = 14816 */ colon }}}, /* CIENTRY "[']" quote_brackets 3 ; take the address of next token from the input stream during compilation h 14824 */
	{.type FromH0, {.p C_single_quote}, .src = "dd C_single_quote"},		/* dd C_single_quote 14832 */
	{.type FromH0, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 14840 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14848 */
	{.type IHeader, {.hdr { 1, "(", /* CI_openparen = 14864 */ colon }}}, /* CIENTRY "(" openparen 1 ; ignore until ) from the input stream during compilation h 14872 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14880 */
	{.type Absolute, {.p 41}},		/* dd 41 14888 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 14896 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 14904 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14912 */
	{.type IHeader, {.hdr { 1, "\\", /* CI_backslash = 14928 */ colon }}}, /* CIENTRY "\\" backslash 1 h 14936 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 14944 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14952 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14960 */
	{.type FromH0, {.p L214}, .src = "dd L214"},		/* dd L214 14968 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 14976 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14984 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14992 */
	{.type Absolute, {.p 63}},		/* dd 63 15000 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 15008 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15016 */
	{.type Absolute, {.p 63}},		/* dd 63 15024 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 15032 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 15040 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 15048 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15056 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15064 */
	{.type FromH0, {.p L215}, .src = "dd L215"},		/* dd L215 15072 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 15080 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 15088 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 15096 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15104 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15112 */
	{.type Header, {.hdr { 8, "(?abort)", /* C_qabort_parens = 15136 */ colon }}}, /* CENTRY "(?abort)" qabort_parens 8 h 15144 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 15152 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15160 */
	{.type FromH0, {.p L217}, .src = "dd L217"},		/* dd L217 15168 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 15176 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 15184 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 15192 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 15200 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15208 */
	{.type FromH0, {.p L218}, .src = "dd L218"},		/* dd L218 15216 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 15224 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15232 */
	{.type IHeader, {.hdr { 6, "abort\"", /* CI_abort_double_quote = 15248 */ colon }}}, /* CIENTRY "abort\"" abort_double_quote 6 h 15256 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 15264 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15272 */
	{.type FromH0, {.p C_qabort_parens}, .src = "dd C_qabort_parens"},		/* dd C_qabort_parens 15280 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15288 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15296 */
	{.type Header, {.hdr { 1, "\"", /* C_double_quote = 15312 */ colon }}}, /* CENTRY "\"" double_quote 1 ; stores counted string in the dictionary and also leaves the address count of the string on the stack - used to use strings at the interpreter prompt h 15320 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15328 */
	{.type Absolute, {.p 34}},		/* dd 34 15336 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 15344 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 15352 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 15360 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15368 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 15376 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 15384 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15392 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 15400 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15408 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 15416 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15424 */
	{.type Header, {.hdr { 2, "c\"", /* C_cdouble_quote = 15440 */ colon }}}, /* CENTRY "c\"" cdouble_quote 2 ; stores counted string in the dictionary and also leaves the address of the counted string on the stack h 15448 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15456 */
	{.type Absolute, {.p 34}},		/* dd 34		; ( -- \" ) 15464 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( \" -- a ) a = counted string address. a will be in Wordbuf"},		/* dd C_word	; ( \" -- a ) a = counted string address. a will be in Wordbuf 15472 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a)"},		/* dd M_dup	; ( a -- a a) 15480 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a -- a n )"},		/* dd M_cfetch	; ( a a -- a n ) 15488 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( a n -- a n+1 )"},		/* dd C_1plus	; ( a n -- a n+1 ) 15496 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n -- a ) (R -- n+1)"},		/* dd M_rpush	; ( a n -- a ) (R -- n+1) 15504 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( a -- a here ) (R -- n+1)"},		/* dd C_here	; ( a -- a here ) (R -- n+1) 15512 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( a here -- a here n+1) (R -- n+1)"},		/* dd M_rfetch	; ( a here -- a here n+1) (R -- n+1) 15520 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; move counted string from a to here"},		/* dd M_cmove	; move counted string from a to here 15528 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here )"},		/* dd C_here	; ( -- here ) 15536 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( here -- here n+1 )(R -- )"},		/* dd M_rpop	; ( here -- here n+1 )(R -- ) 15544 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( here n+1 -- here) here += n+1"},		/* dd C_allot	; ( here n+1 -- here) here += n+1 15552 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15560 */
	{.type IHeader, {.hdr { 2, "s\"", /* CI_sdouble_quote = 15576 */ colon }}}, /* CIENTRY "s\"" sdouble_quote 2 ; add the string from the input stream to the dictionary as (sliteral) count string - at run-time puts the ( -- addr n) of the counted string on the stack. h 15584 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 15592 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15600 */
	{.type IHeader, {.hdr { 2, ".\"", /* CI_dotstr = 15616 */ colon }}}, /* CIENTRY ".\"" dotstr 2 ; do what s" does and then add a type word to the dictionary to print that string h 15624 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 15632 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15640 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 15648 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15656 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15664 */
	{.type IHeader, {.hdr { 2, "if", /* CI_if = 15680 */ colon }}}, /* CIENTRY "if" if 2 h 15688 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15696 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15704 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15712 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15720 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15728 */
	{.type Absolute, {.p 0}},		/* dd 0 15736 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15744 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15752 */
	{.type IHeader, {.hdr { 4, "else", /* CI_else = 15768 */ colon }}}, /* CIENTRY "else" else 4 h 15776 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15784 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15792 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15800 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15808 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 15816 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15824 */
	{.type Absolute, {.p 0}},		/* dd 0 15832 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15840 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15848 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 15856 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15864 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 15872 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15880 */
	{.type IHeader, {.hdr { 4, "then", /* CI_then = 15896 */ colon }}}, /* CIENTRY "then" then 4 h 15904 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15912 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 15920 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15928 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15936 */
	{.type IHeader, {.hdr { 5, "begin", /* CI_begin = 15952 */ colon }}}, /* CIENTRY "begin" begin 5 h 15960 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15968 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15976 */
	{.type IHeader, {.hdr { 5, "again", /* CI_again = 15992 */ colon }}}, /* CIENTRY "again" again 5 h 16000 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16008 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16016 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16024 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16032 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16040 */
	{.type IHeader, {.hdr { 5, "until", /* CI_until = 16056 */ colon }}}, /* CIENTRY "until" until 5 h 16064 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16072 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16080 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16088 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16096 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16104 */
	{.type IHeader, {.hdr { 5, "while", /* CI_while = 16120 */ colon }}}, /* CIENTRY "while" while 5 h 16128 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16136 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16144 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16152 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16160 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16168 */
	{.type Absolute, {.p 0}},		/* dd 0 16176 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16184 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16192 */
	{.type IHeader, {.hdr { 6, "repeat", /* CI_repeat = 16208 */ colon }}}, /* CIENTRY "repeat" repeat 6 h 16216 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16224 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16232 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16240 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16248 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16256 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16264 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16272 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16280 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16288 */
	{.type IHeader, {.hdr { 2, "do", /* CI_do = 16304 */ colon }}}, /* CIENTRY "do" do 2 h 16312 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16320 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time"},		/* dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time 16328 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; puts (do) into the dictionary"},		/* dd C_comma		; puts (do) into the dictionary 16336 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16344 */
	{.type Absolute, {.p 0}},		/* dd 0			; ( -- 0 ) 16352 */
	{.type FromH0, {.p C_here}, .src = "dd C_here		; ( 0 -- 0 here1 )"},		/* dd C_here		; ( 0 -- 0 here1 ) 16360 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16368 */
	{.type IHeader, {.hdr { 4, "loop", /* CI_loop = 16384 */ colon }}}, /* CIENTRY "loop" loop 4 ; ( 0 here1 -- ) h 16392 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16400 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop		; ( 0 here1 -- 0 here1 (loop) )"},		/* dd M_doloop		; ( 0 here1 -- 0 here1 (loop) ) 16408 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 )"},		/* dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 ) 16416 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 )"},		/* dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 ) 16424 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 16432 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16440 */
	{.type FromH0, {.p L234}, .src = "dd L234"},		/* dd L234 16448 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16456 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16464 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16472 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16480 */
	{.type IHeader, {.hdr { 5, "+loop", /* CI_ploop = 16496 */ colon }}}, /* CIENTRY "+loop" ploop 5 h 16504 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16512 */
	{.type FromH0, {.p M_doploop}, .src = "dd M_doploop"},		/* dd M_doploop 16520 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16528 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16536 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 16544 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16552 */
	{.type FromH0, {.p L236}, .src = "dd L236"},		/* dd L236 16560 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16568 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16576 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16584 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16592 */
	{.type Header, {.hdr { 3, "w/o", /* C_wo = 16608 */ colon }}}, /* CENTRY "w/o" wo 3 h 16616 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16624 */
	{.type Absolute, {.p 1}},		/* dd 1 16632 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16640 */
	{.type Absolute, {.p 512}},		/* dd 512 16648 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 16656 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16664 */
	{.type Absolute, {.p 64}},		/* dd 64 16672 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 16680 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16688 */
	{.type Header, {.hdr { 3, "r/o", /* C_ro = 16704 */ colon }}}, /* CENTRY "r/o" ro 3 h 16712 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16720 */
	{.type Absolute, {.p 0}},		/* dd 0 16728 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16736 */
	{.type Header, {.hdr { 3, "r/w", /* C_rw = 16752 */ colon }}}, /* CENTRY "r/w" rw 3 h 16760 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16768 */
	{.type Absolute, {.p 2}},		/* dd 2 16776 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16784 */
	{.type Header, {.hdr { 9, "open-file", /* C_open_file = 16808 */ colon }}}, /* CENTRY "open-file" open_file 9 ; ( a n mode -- fd ioresult ) h 16816 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n mode -- a n ) (R -- mode)"},		/* dd M_rpush	; ( a n mode -- a n ) (R -- mode) 16824 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( a n -- a n padaddr)"},		/* dd C_pad	; ( a n -- a n padaddr) 16832 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16840 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( a n padaddr --  a n padaddr 1024 ) 16848 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( a n padaddr+1024 --  a n padaddr+1024 )"},		/* dd M_plus	; ( a n padaddr+1024 --  a n padaddr+1024 ) 16856 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n padaddr+1024 --  a padaddr+1024 n )"},		/* dd M_xswap	; ( a n padaddr+1024 --  a padaddr+1024 n ) 16864 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a padaddr+1024 n --  a padaddr+1024 n n )"},		/* dd M_dup	; ( a padaddr+1024 n --  a padaddr+1024 n n ) 16872 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a padaddr+1024 n n --  a padaddr+1024 n ) (R mode -- mode n )"},		/* dd M_rpush	; ( a padaddr+1024 n n --  a padaddr+1024 n ) (R mode -- mode n ) 16880 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; moves the filename from a to paddaddr+1024"},		/* dd M_cmove	; moves the filename from a to paddaddr+1024 16888 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16896 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- 0 ) 16904 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( 0 -- 0 n ) (R mode n -- mode)"},		/* dd M_rpop	; ( 0 -- 0 n ) (R mode n -- mode) 16912 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( 0 n -- 0 n padaddr)"},		/* dd C_pad	; ( 0 n -- 0 n padaddr) 16920 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 n padaddr -- 0 padaddr+n )"},		/* dd M_plus	; ( 0 n padaddr -- 0 padaddr+n ) 16928 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16936 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( 0 padaddr+n --  0 padaddr+n 1024 ) 16944 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n 1024 --  0 padaddr+n+1024 )"},		/* dd M_plus	; ( 0 padaddr+n 1024 --  0 padaddr+n+1024 ) 16952 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; ( 0 padaddr+n 1024 --   ) makes the filename to a null terminated string"},		/* dd M_cstore	; ( 0 padaddr+n 1024 --   ) makes the filename to a null terminated string 16960 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 16968 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16976 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( -- padaddr 1024 ) 16984 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( padaddr 1024 -- padaddr+1024 )"},		/* dd M_plus	; ( padaddr 1024 -- padaddr+1024 ) 16992 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 -- padaddr+1024 mode) (R mode -- )"},		/* dd M_rpop	; ( padaddr+1024 -- padaddr+1024 mode) (R mode -- ) 17000 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; M_literal dd 420		; ( padaddr+1024 mode 420 ) 420 for hardcoded mode?"},		/* dd M_xswap	; M_literal dd 420		; ( padaddr+1024 mode 420 ) 420 for hardcoded mode? 17008 */
	{.type FromH0, {.p M_fsopen}, .src = "dd M_fsopen"},		/* dd M_fsopen 17016 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17024 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17032 */
	{.type Absolute, {.p -1}},		/* dd -1 17040 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 17048 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17056 */
	{.type Header, {.hdr { 10, "close-file", /* C_close_file = 17080 */ colon }}}, /* CENTRY "close-file" close_file 10 ; ( fd -- ioresult ) h 17088 */
	{.type FromH0, {.p M_fsclose}, .src = "dd M_fsclose"},		/* dd M_fsclose 17096 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 17104 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17112 */
	{.type Header, {.hdr { 9, "read-file", /* C_read_file = 17136 */ colon }}}, /* CENTRY "read-file" read_file 9 ; ( a n fd -- n2 ioresult ) h 17144 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 17152 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 17160 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( n a fd )"},		/* dd M_rpop	; ( n a fd ) 17168 */
	{.type FromH0, {.p M_fsread}, .src = "dd M_fsread"},		/* dd M_fsread 17176 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17184 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17192 */
	{.type Absolute, {.p -1}},		/* dd -1 17200 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17208 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17216 */
	{.type Header, {.hdr { 10, "write-file", /* C_write_file = 17240 */ colon }}}, /* CENTRY "write-file" write_file 10 ; ( a n fd -- ioresult ) h 17248 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 17256 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 17264 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( n a fd )"},		/* dd M_rpop	; ( n a fd ) 17272 */
	{.type FromH0, {.p M_fswrite}, .src = "dd M_fswrite"},		/* dd M_fswrite 17280 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17288 */
	{.type Absolute, {.p -1}},		/* dd -1 17296 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17304 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17312 */
	{.type Header, {.hdr { 15, "reposition-file", /* C_reposition_file = 17336 */ colon }}}, /* CENTRY "reposition-file" reposition_file 15 ; ( type n fd -- ioresult ) h 17344 */
	{.type FromH0, {.p M_fsseek}, .src = "dd M_fsseek"},		/* dd M_fsseek 17352 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17360 */
	{.type Absolute, {.p -1}},		/* dd -1 17368 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17376 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17384 */
	{.type Header, {.hdr { 7, "?fcheck", /* C_qfcheck = 17400 */ colon }}}, /* CENTRY "?fcheck" qfcheck 7 h 17408 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 17416 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 17424 */
	{.type FromH0, {.p L246}, .src = "dd L246"},		/* dd L246 17432 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 17440 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17448 */
	{.type FromH0, {.p L247}, .src = "dd L247"},		/* dd L247 17456 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17464 */
	{.type Absolute, {.p 9}},		/* dd 9 17472 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 17480 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 17488 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 17496 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17504 */
	{.type Header, {.hdr { 11, "create-file", /* C_create_file = 17528 */ colon }}}, /* CENTRY "create-file" create_file 11 ; ( a n mode perm -- fd ioresult ) not part of the original ff. could move this to a forth file. h 17536 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n mode ) (R perm)"},		/* dd M_rpush	; ( a n mode ) (R perm) 17544 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n ) (R perm mode)"},		/* dd M_rpush	; ( a n ) (R perm mode) 17552 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( a n padaddr)"},		/* dd C_pad	; ( a n padaddr) 17560 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17568 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( a n padaddr 1024 ) 17576 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( a n padaddr+1024 )"},		/* dd M_plus	; ( a n padaddr+1024 ) 17584 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a padaddr+1024 n )"},		/* dd M_xswap	; ( a padaddr+1024 n ) 17592 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a padaddr+1024 n n )"},		/* dd M_dup	; ( a padaddr+1024 n n ) 17600 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n )"},		/* dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n ) 17608 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; moves the filename from a to paddaddr+1024"},		/* dd M_cmove	; moves the filename from a to paddaddr+1024 17616 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17624 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( 0 ) 17632 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( 0 n ) (R perm mode)"},		/* dd M_rpop	; ( 0 n ) (R perm mode) 17640 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad	; ( 0 n padaddr)"},		/* dd C_pad	; ( 0 n padaddr) 17648 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n )"},		/* dd M_plus	; ( 0 padaddr+n ) 17656 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17664 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( 0 padaddr+n 1024 ) 17672 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n+1024 )"},		/* dd M_plus	; ( 0 padaddr+n+1024 ) 17680 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; ( ) makes the filename to a null terminated string"},		/* dd M_cstore	; ( ) makes the filename to a null terminated string 17688 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 17696 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17704 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( padaddr 1024 ) 17712 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( padaddr+1024 )"},		/* dd M_plus	; ( padaddr+1024 ) 17720 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 mode) (R perm )"},		/* dd M_rpop	; ( padaddr+1024 mode) (R perm ) 17728 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 mode perm ) (R )"},		/* dd M_rpop	; ( padaddr+1024 mode perm ) (R ) 17736 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( padaddr+1024 perm mode )"},		/* dd M_xswap	; ( padaddr+1024 perm mode ) 17744 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( perm mode padaddr+1024 )"},		/* dd C_rot	; ( perm mode padaddr+1024 ) 17752 */
	{.type FromH0, {.p M_fscreate}, .src = "dd M_fscreate"},		/* dd M_fscreate 17760 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17768 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17776 */
	{.type Absolute, {.p -1}},		/* dd -1 17784 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 17792 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17800 */
	{.type Header, {.hdr { 3, "bye", /* C_bye = 17816 */ colon }}}, /* CENTRY "bye" bye 3 h 17824 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17832 */
	{.type Absolute, {.p 0}},		/* dd 0 17840 */
	{.type FromH0, {.p M_terminate}, .src = "dd M_terminate"},		/* dd M_terminate 17848 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17856 */
	{.type Header, {.hdr { 7, "include", /* C_include = 17872 */ colon }}}, /* CENTRY "include" include 7 h 17880 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 17888 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 17896 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 17904 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 17912 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 17920 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 17928 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 17936 */
	{.type FromH0, {.p C_save_input}, .src = "dd C_save_input"},		/* dd C_save_input 17944 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 17952 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 17960 */
	{.type FromH0, {.p C_ro}, .src = "dd C_ro"},		/* dd C_ro 17968 */
	{.type FromH0, {.p C_open_file}, .src = "dd C_open_file"},		/* dd C_open_file 17976 */
	{.type FromH0, {.p C_qfcheck}, .src = "dd C_qfcheck"},		/* dd C_qfcheck 17984 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 17992 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18000 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18008 */
	{.type Header, {.hdr { 5, "crash", /* C_crash = 18024 */ colon }}}, /* CENTRY "crash" crash 5 h 18032 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18040 */
	{.type FromH0, {.p L251}, .src = "dd L251"},		/* dd L251 18048 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18056 */
	{.type Absolute, {.p 30}},		/* dd 30 18064 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 18072 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 18080 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 18088 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18096 */
	{.type Header, {.hdr { 4, "quit", /* C_quit = 18112 */ colon }}}, /* CENTRY "quit" quit 4 ; interpreter loop h 18120 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 18128 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 18136 */
	{.type FromH0, {.p C_query}, .src = "dd C_query"},		/* dd C_query 18144 */
/* ; dd MV_toLimit	; show the line read, for debugging *//* ; dd M_fetch *//* ; dd M_Tib *//* ; dd MC_STDOUT *//* ; dd M_fswrite *//* ; dd M_drop		; drop the return value of write *//* ; dd C_cr *//* ; dd C_space */	{.type FromH0, {.p C_interpret}, .src = "dd C_interpret"},		/* dd C_interpret 18152 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 18160 */
	{.type FromH0, {.p L253}, .src = "dd L253"},		/* dd L253 18168 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed?"},		/* dd M_exitcolon	; why is this needed? 18176 */
	{.type Header, {.hdr { 7, "(abort)", /* C_parenabort = 18192 */ colon }}}, /* CENTRY "(abort)" parenabort 7 ; TODO correct below stack notations h 18200 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State	; ( mv_State -- )"},		/* dd MV_State	; ( mv_State -- ) 18208 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; off sets variable state = 0"},		/* dd C_off		; off sets variable state = 0 18216 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top of stack"},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 18224 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; variable sourcebuf"},		/* dd MV_Sourcebuf	; variable sourcebuf 18232 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable sourcebuf = address of tibuffer"},		/* dd M_store	; variable sourcebuf = address of tibuffer 18240 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk	; variable blk"},		/* dd MV_Blk	; variable blk 18248 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off variable blk = 0"},		/* dd C_off	; off variable blk = 0 18256 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 18264 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18272 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18280 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 18288 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 18296 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18304 */
	{.type FromH0, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 18312 */
	{.type FromH0, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 18320 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18328 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit resets stacks and is the interpreter loop"},		/* dd C_quit	; quit resets stacks and is the interpreter loop 18336 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed? quit does not return unless it breaks"},		/* dd M_exitcolon	; why is this needed? quit does not return unless it breaks 18344 */
	{.type Header, {.hdr { 7, "oldboot", /* C_oldboot = 18360 */ colon }}}, /* CENTRY "oldboot" oldboot 7 ; TODO correct below stack notations and this is obsolete. leaving it here for reference until it all works well h 18368 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset"},		/* dd M_reset 18376 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end"},		/* dd M_clear	; SP = sstack_end 18384 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr	; (D -- FFEND)"},		/* dd M_stackptr	; (D -- FFEND) 18392 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 18400 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; s0 = FFEND"},		/* dd M_store	; s0 = FFEND 18408 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp	; heaptop = heapend"},		/* dd M_Dp	; heaptop = heapend 18416 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( heapend -- )"},		/* dd M_fetch	; ( heapend -- ) 18424 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18432 */
	{.type Absolute, {.p 1}},		/* dd 1		; ( heapend 1 -- ) 18440 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells	; cells ( heapend 8 -- )"},		/* dd C_cells	; cells ( heapend 8 -- ) 18448 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( heapend-8 -- )"},		/* dd M_minus	; ( heapend-8 -- ) 18456 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( contents_from_heapend-8 -- )"},		/* dd M_fetch	; ( contents_from_heapend-8 -- ) 18464 */
	{.type FromH0, {.p M_Args}, .src = "dd M_Args	; variable args"},		/* dd M_Args	; variable args 18472 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; args = contents_from_heapend-8"},		/* dd M_store	; args = contents_from_heapend-8 18480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18488 */
	{.type FromH0, {.p C_parenabort}, .src = "dd C_parenabort ; ( (abort) -- )"},		/* dd C_parenabort ; ( (abort) -- ) 18496 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec	; variable abortvec"},		/* dd MV_Abortvec	; variable abortvec 18504 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable abortvec = (abort) code address"},		/* dd M_store	; variable abortvec = (abort) code address 18512 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb	; constant puts address of wordbuffer on the top of stack"},		/* dd M_Wordb	; constant puts address of wordbuffer on the top of stack 18520 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf	; variable wordbuf"},		/* dd MV_Wordbuf	; variable wordbuf 18528 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable wordbuf = address of wordbuffer"},		/* dd M_store	; variable wordbuf = address of wordbuffer 18536 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top of stack"},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 18544 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; variable sourcebuf"},		/* dd MV_Sourcebuf	; variable sourcebuf 18552 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable sourcebuf = address of tibuffer"},		/* dd M_store	; variable sourcebuf = address of tibuffer 18560 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18568 */
	{.type Absolute, {.p 0}},		/* dd 0 18576 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18584 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdin = 0"},		/* dd M_store	; stdin = 0 18592 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18600 */
	{.type Absolute, {.p 1}},		/* dd 1 18608 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 18616 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdout = 1"},		/* dd M_store	; stdout = 1 18624 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 18632 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off stores 0 at state"},		/* dd C_off	; off stores 0 at state 18640 */
	{.type FromH0, {.p C_decimal}, .src = "dd C_decimal	; decimal setting base = 0"},		/* dd C_decimal	; decimal setting base = 0 18648 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit"},		/* dd C_quit	; quit 18656 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18664 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal	; test code"},		/* dd M_literal	; test code 18672 */
	{.type Absolute, {.p 66}},		/* dd 66 18680 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 18688 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18696 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18704 */
	{.type Absolute, {.p 1}},		/* dd 1 18712 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 18720 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 18728 */
	{.type FromH0, {.p M_fswrite}, .src = "dd M_fswrite"},		/* dd M_fswrite 18736 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 18744 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18752 */
	{.type Absolute, {.p 1}},		/* dd 1 18760 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 18768 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 18776 */
	{.type FromH0, {.p M_fsread}, .src = "dd M_fsread"},		/* dd M_fsread 18784 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of read"},		/* dd M_drop		; drop the return value of read 18792 */
	{.type Header, {.hdr { 4, "boot", /* C_boot = 18808 */ colon }}}, /* CENTRY "boot" boot 4 h 18816 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 18824 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 18832 */
/* 			; s0 puts FFEND on the stack *//* 			; no args */	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18840 */
	{.type FromH0, {.p C_parenabort}, .src = "dd C_parenabort ; ( (abort) -- )"},		/* dd C_parenabort ; ( (abort) -- ) 18848 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec	; variable that puts (abort) code address on the stack"},		/* dd MV_Abortvec	; variable that puts (abort) code address on the stack 18856 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable abortvec = (abort) code address"},		/* dd M_store	; variable abortvec = (abort) code address 18864 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb	; variable puts address of wordbuffer on the top of stack"},		/* dd M_Wordb	; variable puts address of wordbuffer on the top of stack 18872 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf ; variable wordbuf"},		/* dd MV_Wordbuf ; variable wordbuf 18880 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable wordbuf = address of wordbuffer"},		/* dd M_store	; variable wordbuf = address of wordbuffer 18888 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top of stack"},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 18896 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; variable sourcebuf"},		/* dd MV_Sourcebuf	; variable sourcebuf 18904 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable sourcebuf = address of tibuffer"},		/* dd M_store	; variable sourcebuf = address of tibuffer 18912 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 18920 */
	{.type FromH0, {.p MV_H0}, .src = "dd MV_H0	; H0 = here at startup"},		/* dd MV_H0	; H0 = here at startup 18928 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18936 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 18944 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18952 */
	{.type FromH0, {.p M_store}, .src = "dd M_store     ; stdin = 0"},		/* dd M_store     ; stdin = 0 18960 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 18968 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 18976 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18984 */
	{.type FromH0, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 18992 */
	{.type FromH0, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 19000 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 19008 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 19016 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off stores 0 at state"},		/* dd C_off	; off stores 0 at state 19024 */
	{.type FromH0, {.p C_decimal}, .src = "dd C_decimal	; decimal sets base = 10"},		/* dd C_decimal	; decimal sets base = 10 19032 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit"},		/* dd C_quit	; quit 19040 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19048 */
	{.type Chars, {.str "unable to restore input"}},		/* 19072 */
	{.type Chars, {.str " Q?"}},		/* 19076 */
	{.type Chars, {.str " stack underflow"}},		/* 19093 */
	{.type Chars, {.str " I?"}},		/* 19097 */
	{.type Chars, {.str " C?"}},		/* 19101 */
	{.type Chars, {.str "I/O error"}},		/* 19111 */
	{.type Chars, {.str "uninitialized execution vector"}},		/* 19142 */
	{.type Chars, {.str " ok"}},		/* 19146 */
};

