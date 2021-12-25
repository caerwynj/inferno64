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
	MV_Ninputs = 1792,
	MC_STDIN = 1824,
	MC_STDOUT = 1856,
	MC_STDERR = 1888,
	M_S0 = 1920,
	M_stackptr = 1944,
	M_H0 = 1968,
	M_Wordb = 1992,
	M_Tib = 2016,
	M_Args = 2040,
	M_variable = 2072,
	M_constant = 2104,
	M_colon = 2128,
	M_dodoes = 2152,
	M_cas = 2176,
	M_deferred = 2208,
	C_false = 2232,
	C_true = 2280,
	C_bl = 2328,
	C_on = 2376,
	C_off = 2440,
	C_tobody = 2504,
	C_aligned = 2560,
	C_cells = 2640,
	C_cellplus = 2696,
	C_depth = 2760,
	C_nip = 2864,
	C_rot = 2912,
	C_2drop = 2976,
	C_2dup = 3024,
	C_2nip = 3072,
	C_2swap = 3120,
	C_qdup = 3184,
	L20 = 3256,
	C_pick = 3280,
	L22 = 3384,
	L23 = 3392,
	C_tuck = 3416,
	C_divides = 3480,
	C_plusstore = 3528,
	C_invert = 3608,
	C_mod = 3664,
	C_1plus = 3712,
	C_1minus = 3768,
	C_negate = 3824,
	C_2multiplies = 3888,
	C_2divides = 3944,
	C_0eq = 4000,
	C_0lt = 4056,
	C_0gt = 4112,
	C_neq = 4168,
	C_0neq = 4216,
	C_max = 4272,
	L40 = 4336,
	L41 = 4344,
	C_min = 4368,
	L43 = 4432,
	L44 = 4440,
	C_signum = 4464,
	L46 = 4544,
	L48 = 4600,
	L49 = 4616,
	L47 = 4616,
	C_within = 4640,
	C_abs = 4744,
	L52 = 4792,
	C_key = 4816,
	L78 = 4944,
	L79 = 4960,
	C_emit = 4984,
	C_type = 5096,
	C_cr = 5168,
	C_space = 5224,
	C_emits = 5272,
	L85 = 5280,
	L86 = 5344,
	C_spaces = 5376,
	C_count = 5432,
	C_compare = 5576,
	L55 = 5648,
	L56 = 5784,
	C_erase = 5864,
	L58 = 5896,
	C_fill = 5984,
	L60 = 6024,
	C_blank = 6112,
	C_search = 6160,
	L64 = 6264,
	L65 = 6448,
	C_here = 6512,
	C_comma = 6560,
	C_c = 6640,
	C_allot = 6720,
	C_pad = 6768,
	C_align = 6832,
	C_unused = 6896,
	C_fromhash = 6960,
	C_hash = 7040,
	L92 = 7192,
	L93 = 7216,
	C_hashs = 7296,
	L95 = 7304,
	L96 = 7352,
	C_hashfrom = 7376,
	C_hold = 7488,
	C_sign = 7592,
	L100 = 7648,
	C_dot = 7672,
	C_dotr = 7776,
	C_hex = 7936,
	C_decimal = 8000,
	C_digit = 8064,
	L106 = 8176,
	L108 = 8280,
	L110 = 8384,
	L111 = 8408,
	L109 = 8408,
	L107 = 8408,
	L112 = 8480,
	L113 = 8496,
	C_number = 8520,
	L115 = 8656,
	L116 = 8688,
	L117 = 8752,
	L118 = 8856,
	L119 = 8912,
	C_abort = 9000,
	C_source = 9056,
	C_current_input = 9112,
	C_save_input = 9192,
	C_default_input = 9336,
	C_restore_input = 9456,
	L300 = 9560,
	L301 = 9576,
	L133 = 9664,
	L134 = 9752,
	C_qrestore_input = 9784,
	L136 = 9912,
	C_next_input = 9944,
	L139 = 10040,
	L140 = 10064,
	C_parse = 10088,
	L142 = 10128,
	L143 = 10256,
	C_word = 10400,
	L145 = 10416,
	L146 = 10512,
	C_accept = 10552,
	L148 = 10592,
	L150 = 10752,
	L149 = 10816,
	C_query = 10864,
	L152 = 11008,
	L153 = 11040,
	C_refill = 11064,
	L155 = 11128,
	L156 = 11144,
	C_findname = 11176,
	L158 = 11216,
	L160 = 11328,
	L162 = 11456,
	L161 = 11464,
	L159 = 11480,
	C_find = 11528,
	L165 = 11720,
	L166 = 11736,
	L164 = 11760,
	L167 = 11768,
	C_single_quote = 11792,
	L169 = 11928,
	C_qstack = 11952,
	L172 = 12056,
	C_interpret = 12136,
	L175 = 12144,
	L177 = 12256,
	L179 = 12368,
	L178 = 12368,
	L176 = 12384,
	C_create = 12416,
	C_variable = 12664,
	C_constant = 12736,
	C_immediate = 12864,
	C_tocfa = 12976,
	C_compile = 13056,
	L189 = 13184,
	L190 = 13200,
	L188 = 13216,
	L192 = 13344,
	L194 = 13376,
	L191 = 13376,
	C_close_bracket = 13400,
	L196 = 13424,
	L197 = 13512,
	L198 = 13536,
	L199 = 13568,
	CI_open_bracket = 13592,
	C_smudge = 13640,
	C_reveal = 13752,
	C_colon = 13872,
	CI_semicolon = 14000,
	CI_recurse = 14080,
	C_L206 = 14152,
	C_literal = 14216,
	C_sliteral = 14288,
	C_string = 14456,
	CI_char_brackets = 14568,
	CI_quote_brackets = 14640,
	CI_openparen = 14688,
	CI_backslash = 14752,
	L214 = 14896,
	L215 = 14928,
	C_qabort_parens = 14960,
	L217 = 15040,
	L218 = 15048,
	CI_abort_double_quote = 15072,
	C_double_quote = 15136,
	C_cdouble_quote = 15264,
	CI_sdouble_quote = 15400,
	CI_dotstr = 15440,
	CI_if = 15504,
	CI_else = 15592,
	CI_then = 15720,
	CI_begin = 15776,
	CI_again = 15816,
	CI_until = 15880,
	CI_while = 15944,
	CI_repeat = 16032,
	CI_do = 16128,
	CI_loop = 16208,
	L234 = 16296,
	CI_ploop = 16320,
	L236 = 16408,
	C_wo = 16432,
	C_ro = 16528,
	C_rw = 16576,
	C_open_file = 16632,
	C_close_file = 16912,
	C_read_file = 16968,
	C_write_file = 17048,
	C_reposition_file = 17120,
	C_qfcheck = 17184,
	L246 = 17280,
	C_bye = 17304,
	C_include = 17360,
	C_crash = 17512,
	C_quit = 17600,
	L253 = 17624,
	C_parenabort = 17752,
	C_oldboot = 17920,
	C_boot = 18368,
	L137 = 18584,
	L170 = 18608,
	L173 = 18612,
	L180 = 18629,
	L193 = 18633,
	L247 = 18637,
	L251 = 18647,
	L255 = 18678,
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
	{.type Header, {.hdr { 7, "Ninputs", /* MV_Ninputs = 1792 */ variable }}}, /* MVENTRY "Ninputs" Ninputs 0 7 h 1800 */
	{.type Absolute, {.p 0}},		/* 1808 */
	{.type Header, {.hdr { 5, "STDIN", /* MC_STDIN = 1824 */ constant }}}, /* MCENTRY "STDIN" STDIN 0 5		; 3 constants from here CAPITALS h 1832 */
	{.type Absolute, {.p 0}},		/* 1840 */
	{.type Header, {.hdr { 6, "STDOUT", /* MC_STDOUT = 1856 */ constant }}}, /* MCENTRY "STDOUT" STDOUT 1 6 h 1864 */
	{.type Absolute, {.p 1}},		/* 1872 */
	{.type Header, {.hdr { 6, "STDERR", /* MC_STDERR = 1888 */ constant }}}, /* MCENTRY "STDERR" STDERR 2 6 h 1896 */
	{.type Absolute, {.p 2}},		/* 1904 */
	{.type Header, {.hdr { 2, "S0", /* M_S0 = 1920 */ S0 }}}, /* MENTRY "S0" S0 2 h 1928 */
	{.type Header, {.hdr { 2, "s@", /* M_stackptr = 1944 */ stackptr }}}, /* MENTRY "s@" stackptr 2		; puts PSP on stack h 1952 */
	{.type Header, {.hdr { 2, "H0", /* M_H0 = 1968 */ H0 }}}, /* MENTRY "H0" H0 2 h 1976 */
	{.type Header, {.hdr { 5, "Wordb", /* M_Wordb = 1992 */ Wordb }}}, /* MENTRY "Wordb" Wordb 5 h 2000 */
	{.type Header, {.hdr { 3, "Tib", /* M_Tib = 2016 */ Tib }}}, /* MENTRY "Tib" Tib 3 h 2024 */
	{.type Header, {.hdr { 3, "Args", /* M_Args = 2040 */ Args }}}, /* MENTRY "Args" Args 3 h 2048 */
	{.type Header, {.hdr { 10, "(variable)", /* M_variable = 2072 */ variable }}}, /* MENTRY "(variable)" variable 10 h 2080 */
	{.type Header, {.hdr { 10, "(constant)", /* M_constant = 2104 */ constant }}}, /* MENTRY "(constant)" constant 10 h 2112 */
	{.type Header, {.hdr { 3, "(:)", /* M_colon = 2128 */ colon }}}, /* MENTRY "(:)" colon 3 h 2136 */
	{.type Header, {.hdr { 6, "(does)", /* M_dodoes = 2152 */ dodoes }}}, /* MENTRY "(does)" dodoes 6 h 2160 */
	{.type Header, {.hdr { 3, "cas", /* M_cas = 2176 */ cas }}}, /* MENTRY "cas" cas 3 h 2184 */
	{.type Header, {.hdr { 10, "(deferred)", /* M_deferred = 2208 */ deferred }}}, /* MENTRY "(deferred)" deferred 10 h 2216 */
	{.type Header, {.hdr { 5, "false", /* C_false = 2232 */ colon }}}, /* CENTRY "false" false 5 h 2240 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2248 */
	{.type Absolute, {.p 0}},		/* dd 0 2256 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2264 */
	{.type Header, {.hdr { 4, "true", /* C_true = 2280 */ colon }}}, /* CENTRY "true" true 4 h 2288 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2296 */
	{.type Absolute, {.p -1}},		/* dd -1 2304 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2312 */
	{.type Header, {.hdr { 2, "bl", /* C_bl = 2328 */ colon }}}, /* CENTRY "bl" bl 2 h 2336 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2344 */
	{.type Absolute, {.p 32}},		/* dd 32 2352 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2360 */
	{.type Header, {.hdr { 2, "on", /* C_on = 2376 */ colon }}}, /* CENTRY "on" on 2 ; ( a -- ) (G stores -1 at a ) h 2384 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2392 */
	{.type Absolute, {.p -1}},		/* dd -1 2400 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2408 */
	{.type FromH0, {.p M_store}},		/* dd M_store 2416 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2424 */
	{.type Header, {.hdr { 3, "off", /* C_off = 2440 */ colon }}}, /* CENTRY "off" off 3 ; ( a -- ) (G stores 0 at a ) h 2448 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2456 */
	{.type Absolute, {.p 0}},		/* dd 0 2464 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2472 */
	{.type FromH0, {.p M_store}},		/* dd M_store 2480 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2488 */
	{.type Header, {.hdr { 5, ">body", /* C_tobody = 2504 */ colon }}}, /* CENTRY ">body" tobody 5 h 2512 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2520 */
	{.type Absolute, {.p 8}},		/* dd 8 2528 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 2536 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2544 */
	{.type Header, {.hdr { 7, "aligned", /* C_aligned = 2560 */ colon }}}, /* CENTRY "aligned" aligned 7 h 2568 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2576 */
	{.type Absolute, {.p 7}},		/* dd 7 2584 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 2592 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2600 */
	{.type Absolute, {.p -8}},		/* dd -8 2608 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 2616 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2624 */
	{.type Header, {.hdr { 5, "cells", /* C_cells = 2640 */ colon }}}, /* CENTRY "cells" cells 5 h 2648 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2656 */
	{.type Absolute, {.p 3}},		/* dd 3			; (index << 2) -> (index << 3)for amd64 2664 */
	{.type FromH0, {.p M_lshift}},		/* dd M_lshift 2672 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2680 */
	{.type Header, {.hdr { 5, "cell+", /* C_cellplus = 2696 */ colon }}}, /* CENTRY "cell+" cellplus 5 h 2704 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2712 */
	{.type Absolute, {.p 1}},		/* dd 1 2720 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 2728 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 2736 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2744 */
	{.type Header, {.hdr { 5, "depth", /* C_depth = 2760 */ colon }}}, /* CENTRY "depth" depth 5 h 2768 */
	{.type FromH0, {.p M_S0}},		/* dd M_S0 2776 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr 2784 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 2792 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2800 */
	{.type Absolute, {.p 3}},		/* dd 3 2808 */
	{.type FromH0, {.p M_rshift}},		/* dd M_rshift 2816 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 2824 */
	{.type Absolute, {.p 1}},		/* dd 1 2832 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 2840 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2848 */
	{.type Header, {.hdr { 3, "nip", /* C_nip = 2864 */ colon }}}, /* CENTRY "nip" nip 3 h 2872 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2880 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 2888 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2896 */
	{.type Header, {.hdr { 3, "rot", /* C_rot = 2912 */ colon }}}, /* CENTRY "rot" rot 3 h 2920 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 2928 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2936 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 2944 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 2952 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 2960 */
	{.type Header, {.hdr { 5, "2drop", /* C_2drop = 2976 */ colon }}}, /* CENTRY "2drop" 2drop 5 h 2984 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 2992 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 3000 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3008 */
	{.type Header, {.hdr { 4, "2dup", /* C_2dup = 3024 */ colon }}}, /* CENTRY "2dup" 2dup 4 h 3032 */
	{.type FromH0, {.p M_over}},		/* dd M_over 3040 */
	{.type FromH0, {.p M_over}},		/* dd M_over 3048 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3056 */
	{.type Header, {.hdr { 4, "2nip", /* C_2nip = 3072 */ colon }}}, /* CENTRY "2nip" 2nip 4 h 3080 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 3088 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 3096 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3104 */
	{.type Header, {.hdr { 5, "2swap", /* C_2swap = 3120 */ colon }}}, /* CENTRY "2swap" 2swap 5 h 3128 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot 3136 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 3144 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot 3152 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 3160 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3168 */
	{.type Header, {.hdr { 4, "?dup", /* C_qdup = 3184 */ colon }}}, /* CENTRY "?dup" qdup 4 ; if (n != 0) ( n -- n n) else ( n -- n ) h 3192 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n -- n n ) 3200 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n n -- n n n ) 3208 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3216 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( n n n -- n n n 0 ) 3224 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( n n n 0 -- n n f ) 3232 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump	; ( n n f -- n n ) 3240 */
	{.type FromH0, {.p L20}},		/* dd L20		; when n != 0, go to L20 3248 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop	; when n == 0 ( n n -- n) 3256 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3264 */
	{.type Header, {.hdr { 4, "pick", /* C_pick = 3280 */ colon }}}, /* CENTRY "pick" pick 4 h 3288 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 3296 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 3304 */
	{.type FromH0, {.p L22}},		/* dd L22 3312 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3320 */
	{.type Absolute, {.p 1}},		/* dd 1 3328 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3336 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 3344 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr 3352 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3360 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 3368 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 3376 */
	{.type FromH0, {.p L23}},		/* dd L23 3384 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 3392 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3400 */
	{.type Header, {.hdr { 4, "tuck", /* C_tuck = 3416 */ colon }}}, /* CENTRY "tuck" tuck 4 h 3424 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 3432 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 3440 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 3448 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 3456 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3464 */
	{.type Header, {.hdr { 1, "/", /* C_divides = 3480 */ colon }}}, /* CENTRY "/" divides 1 h 3488 */
	{.type FromH0, {.p M_slashmod}},		/* dd M_slashmod 3496 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 3504 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3512 */
	{.type Header, {.hdr { 2, "+!", /* C_plusstore = 3528 */ colon }}}, /* CENTRY "+!" plusstore 2 h 3536 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 3544 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 3552 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot 3560 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3568 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 3576 */
	{.type FromH0, {.p M_store}},		/* dd M_store 3584 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3592 */
	{.type Header, {.hdr { 6, "invert", /* C_invert = 3608 */ colon }}}, /* CENTRY "invert" invert 6 h 3616 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3624 */
	{.type Absolute, {.p -1}},		/* dd -1 3632 */
	{.type FromH0, {.p M_binxor}},		/* dd M_binxor 3640 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3648 */
	{.type Header, {.hdr { 3, "mod", /* C_mod = 3664 */ colon }}}, /* CENTRY "mod" mod 3 h 3672 */
	{.type FromH0, {.p M_slashmod}},		/* dd M_slashmod 3680 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 3688 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3696 */
	{.type Header, {.hdr { 2, "1+", /* C_1plus = 3712 */ colon }}}, /* CENTRY "1+" 1plus 2 h 3720 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3728 */
	{.type Absolute, {.p 1}},		/* dd 1 3736 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 3744 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3752 */
	{.type Header, {.hdr { 2, "1-", /* C_1minus = 3768 */ colon }}}, /* CENTRY "1-" 1minus 2 h 3776 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3784 */
	{.type Absolute, {.p 1}},		/* dd 1 3792 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 3800 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3808 */
	{.type Header, {.hdr { 6, "negate", /* C_negate = 3824 */ colon }}}, /* CENTRY "negate" negate 6 h 3832 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3840 */
	{.type Absolute, {.p 0}},		/* dd 0 3848 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 3856 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 3864 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3872 */
	{.type Header, {.hdr { 2, "2*", /* C_2multiplies = 3888 */ colon }}}, /* CENTRY "2*" 2multiplies 2 h 3896 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3904 */
	{.type Absolute, {.p 1}},		/* dd 1 3912 */
	{.type FromH0, {.p M_lshift}},		/* dd M_lshift 3920 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3928 */
	{.type Header, {.hdr { 2, "2/", /* C_2divides = 3944 */ colon }}}, /* CENTRY "2/" 2divides 2 h 3952 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 3960 */
	{.type Absolute, {.p 1}},		/* dd 1 3968 */
	{.type FromH0, {.p M_rshifta}},		/* dd M_rshifta 3976 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 3984 */
	{.type Header, {.hdr { 2, "0=", /* C_0eq = 4000 */ colon }}}, /* CENTRY "0=" 0eq 2 h 4008 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4016 */
	{.type Absolute, {.p 0}},		/* dd 0 4024 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal 4032 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4040 */
	{.type Header, {.hdr { 2, "0<", /* C_0lt = 4056 */ colon }}}, /* CENTRY "0<" 0lt 2 h 4064 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4072 */
	{.type Absolute, {.p 0}},		/* dd 0 4080 */
	{.type FromH0, {.p M_less}},		/* dd M_less 4088 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4096 */
	{.type Header, {.hdr { 2, "0>", /* C_0gt = 4112 */ colon }}}, /* CENTRY "0>" 0gt 2 h 4120 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4128 */
	{.type Absolute, {.p 0}},		/* dd 0 4136 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4144 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4152 */
	{.type Header, {.hdr { 2, "<>", /* C_neq = 4168 */ colon }}}, /* CENTRY "<>" neq 2 h 4176 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal 4184 */
	{.type FromH0, {.p C_invert}},		/* dd C_invert 4192 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4200 */
	{.type Header, {.hdr { 3, "0<>", /* C_0neq = 4216 */ colon }}}, /* CENTRY "0<>" 0neq 3 h 4224 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4232 */
	{.type Absolute, {.p 0}},		/* dd 0 4240 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 4248 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4256 */
	{.type Header, {.hdr { 3, "max", /* C_max = 4272 */ colon }}}, /* CENTRY "max" max 3 h 4280 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 4288 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4296 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4304 */
	{.type FromH0, {.p L40}},		/* dd L40 4312 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 4320 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4328 */
	{.type FromH0, {.p L41}},		/* dd L41 4336 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 4344 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4352 */
	{.type Header, {.hdr { 3, "min", /* C_min = 4368 */ colon }}}, /* CENTRY "min" min 3 h 4376 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 4384 */
	{.type FromH0, {.p M_less}},		/* dd M_less 4392 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4400 */
	{.type FromH0, {.p L43}},		/* dd L43 4408 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 4416 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4424 */
	{.type FromH0, {.p L44}},		/* dd L44 4432 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 4440 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4448 */
	{.type Header, {.hdr { 6, "signum", /* C_signum = 4464 */ colon }}}, /* CENTRY "signum" signum 6 h 4472 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 4480 */
	{.type FromH0, {.p C_0gt}},		/* dd C_0gt 4488 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4496 */
	{.type FromH0, {.p L46}},		/* dd L46 4504 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 4512 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4520 */
	{.type Absolute, {.p 1}},		/* dd 1 4528 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4536 */
	{.type FromH0, {.p L47}},		/* dd L47 4544 */
	{.type FromH0, {.p C_0lt}},		/* dd C_0lt 4552 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4560 */
	{.type FromH0, {.p L48}},		/* dd L48 4568 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4576 */
	{.type Absolute, {.p -1}},		/* dd -1 4584 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4592 */
	{.type FromH0, {.p L49}},		/* dd L49 4600 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4608 */
	{.type Absolute, {.p 0}},		/* dd 0 4616 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4624 */
	{.type Header, {.hdr { 6, "within", /* C_within = 4640 */ colon }}}, /* CENTRY "within" within 6 h 4648 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 4656 */
	{.type FromH0, {.p M_over}},		/* dd M_over 4664 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4672 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 4680 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 4688 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 4696 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 4704 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 4712 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 4720 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4728 */
	{.type Header, {.hdr { 3, "abs", /* C_abs = 4744 */ colon }}}, /* CENTRY "abs" abs 3 h 4752 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 4760 */
	{.type FromH0, {.p C_0lt}},		/* dd C_0lt 4768 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 4776 */
	{.type FromH0, {.p L52}},		/* dd L52 4784 */
	{.type FromH0, {.p C_negate}},		/* dd C_negate 4792 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4800 */
	{.type Header, {.hdr { 3, "key", /* C_key = 4816 */ colon }}}, /* CENTRY "key" key 3 ; ( -- c ) (G read a single character from the input onto the stack ) h 4824 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4832 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( 1 -- ) 4840 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf to store the character read 4848 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 4856 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; ( 1 Iobuf -- 1 Iobuf infd ) 4864 */
	{.type FromH0, {.p M_fthread}},		/* dd M_fthread	; ( 1 Iobuf infd -- n ) 4872 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 4880 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump		; if 0 characters read 4888 */
	{.type FromH0, {.p L78}},		/* dd L78			; if qread n != 0 jump to L78. If n == 0 jump over 4896 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 4904 */
	{.type FromH0, {.p C_on}},		/* dd C_on		; EOF 4912 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 4920 */
	{.type Absolute, {.p -1}},		/* dd -1			; return -1 when EOF 4928 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 4936 */
	{.type FromH0, {.p L79}},		/* dd L79 4944 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; get the character from Iobuf to stack 4952 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch	; ( -- c ) return the character read if not EOF 4960 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 4968 */
	{.type Header, {.hdr { 4, "emit", /* C_emit = 4984 */ colon }}}, /* CENTRY "emit" emit 4 ; ( character -- ) h 4992 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf address 5000 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; variable iobuf has character 5008 */
	{.type FromH0, {.p MV_Iobuf}},		/* dd MV_Iobuf		; variable iobuf address 5016 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5024 */
	{.type Absolute, {.p 1}},		/* dd 1 5032 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap		; ( iobuf 1 --  1 iobuf ) 5040 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 5048 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; outfd 5056 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite	; ( 1 iobuf outfd --  ) 5064 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; drop the return value of write 5072 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5080 */
	{.type Header, {.hdr { 4, "type", /* C_type = 5096 */ colon }}}, /* CENTRY "type" type 4 ; ( addr n -- ) h 5104 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap			; ( addr n --  n addr ) 5112 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5120 */
	{.type Absolute, {.p 1}},		/* dd 1				; stdout 5128 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite			; ( n addr 1 --  ) 5136 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; drop the return value of write 5144 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5152 */
	{.type Header, {.hdr { 2, "cr", /* C_cr = 5168 */ colon }}}, /* CENTRY "cr" cr 2 h 5176 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5184 */
	{.type Absolute, {.p 10}},		/* dd 10			; ascii value of carriage return 5192 */
	{.type FromH0, {.p C_emit}},		/* dd C_emit			; emit 5200 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5208 */
	{.type Header, {.hdr { 5, "space", /* C_space = 5224 */ colon }}}, /* CENTRY "space" space 5 h 5232 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 5240 */
	{.type FromH0, {.p C_emit}},		/* dd C_emit 5248 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5256 */
	{.type Header, {.hdr { 5, "emits", /* C_emits = 5272 */ colon }}}, /* CENTRY "emits" emits 5 h 5280 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 5288 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 5296 */
	{.type FromH0, {.p L86}},		/* dd L86 5304 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5312 */
	{.type FromH0, {.p C_emit}},		/* dd C_emit 5320 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 5328 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 5336 */
	{.type FromH0, {.p L85}},		/* dd L85 5344 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 5352 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5360 */
	{.type Header, {.hdr { 6, "spaces", /* C_spaces = 5376 */ colon }}}, /* CENTRY "spaces" spaces 6 h 5384 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 5392 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 5400 */
	{.type FromH0, {.p C_emits}},		/* dd C_emits 5408 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5416 */
	{.type Header, {.hdr { 5, "count", /* C_count = 5432 */ colon }}}, /* CENTRY "count" count 5 ; ( a -- a+1 n ) a = counted string h 5440 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 5448 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 5456 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 5464 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 5472 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5480 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup ; debug show the word name to search 5488 */
	{.type FromH0, {.p C_type}},		/* dd C_type 5496 */
	{.type FromH0, {.p C_space}},		/* dd C_space 5504 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush ; debug show the dictionary entry 5512 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 5520 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 5528 */
	{.type FromH0, {.p C_type}},		/* dd C_type 5536 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 5544 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 5552 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 5560 */
	{.type Header, {.hdr { 7, "compare", /* C_compare = 5576 */ colon }}}, /* CENTRY "compare" compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search h 5584 */
	{.type FromH0, {.p C_rot}},		/* dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 5592 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 ) 5600 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- ) 5608 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- ) 5616 */
	{.type FromH0, {.p C_min}},		/* dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- ) 5624 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5632 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- ) 5640 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- ) 5648 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5656 */
	{.type FromH0, {.p M_i}},		/* dd M_i 5664 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 5672 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 5680 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5688 */
	{.type FromH0, {.p M_i}},		/* dd M_i 5696 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 5704 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 5712 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 5720 */
	{.type FromH0, {.p C_signum}},		/* dd C_signum 5728 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 5736 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 5744 */
	{.type FromH0, {.p L56}},		/* dd L56		; matches 5752 */
	{.type FromH0, {.p C_2nip}},		/* dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- ) 5760 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2) 5768 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop	; ( f -- f ) (R n1 n2 -- ) 5776 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5784 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 5792 */
	{.type FromH0, {.p L55}},		/* dd L55 5800 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- ) 5808 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 5816 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( n2 n1 -- ) (R -- ) 5824 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( -- n1-n2 ) 5832 */
	{.type FromH0, {.p C_signum}},		/* dd C_signum 5840 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5848 */
	{.type Header, {.hdr { 5, "erase", /* C_erase = 5864 */ colon }}}, /* CENTRY "erase" erase 5 h 5872 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5880 */
	{.type Absolute, {.p 0}},		/* dd 0 5888 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 5896 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 5904 */
	{.type Absolute, {.p 0}},		/* dd 0 5912 */
	{.type FromH0, {.p M_over}},		/* dd M_over 5920 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 5928 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 5936 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 5944 */
	{.type FromH0, {.p L58}},		/* dd L58 5952 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 5960 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 5968 */
	{.type Header, {.hdr { 4, "fill", /* C_fill = 5984 */ colon }}}, /* CENTRY "fill" fill 4 h 5992 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6000 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6008 */
	{.type Absolute, {.p 0}},		/* dd 0 6016 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 6024 */
	{.type FromH0, {.p C_2dup}},		/* dd C_2dup 6032 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6040 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6048 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6056 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 6064 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 6072 */
	{.type FromH0, {.p L60}},		/* dd L60 6080 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop 6088 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6096 */
	{.type Header, {.hdr { 5, "blank", /* C_blank = 6112 */ colon }}}, /* CENTRY "blank" blank 5 h 6120 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 6128 */
	{.type FromH0, {.p C_fill}},		/* dd C_fill 6136 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6144 */
	{.type Header, {.hdr { 6, "search", /* C_search = 6160 */ colon }}}, /* CENTRY "search" search 6 h 6168 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6176 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6184 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6192 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 6200 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 6208 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6216 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6224 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 6232 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 6240 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6248 */
	{.type Absolute, {.p 0}},		/* dd 0 6256 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 6264 */
	{.type FromH0, {.p M_over}},		/* dd M_over 6272 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6280 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6288 */
	{.type FromH0, {.p M_over}},		/* dd M_over 6296 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6304 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6312 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6320 */
	{.type FromH0, {.p MV_Searchlen}},		/* dd MV_Searchlen 6328 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6336 */
	{.type FromH0, {.p C_compare}},		/* dd C_compare 6344 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 6352 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 6360 */
	{.type FromH0, {.p L65}},		/* dd L65 6368 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 6376 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6384 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6392 */
	{.type FromH0, {.p M_i}},		/* dd M_i 6400 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop 6408 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 6416 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 6424 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 6432 */
	{.type FromH0, {.p C_true}},		/* dd C_true 6440 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6448 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 6456 */
	{.type FromH0, {.p L64}},		/* dd L64 6464 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 6472 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 6480 */
	{.type FromH0, {.p C_false}},		/* dd C_false 6488 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6496 */
	{.type Header, {.hdr { 4, "here", /* C_here = 6512 */ colon }}}, /* CENTRY "here" here 4 h 6520 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6528 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6536 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6544 */
	{.type Header, {.hdr { 1, ",", /* C_comma = 6560 */ colon }}}, /* CENTRY "," comma 1 h 6568 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6576 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6584 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6592 */
	{.type Absolute, {.p 8}},		/* dd 8 6600 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6608 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore 6616 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6624 */
	{.type Header, {.hdr { 2, "c,", /* C_c = 6640 */ colon }}}, /* CENTRY "c," c 2 h 6648 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6656 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 6664 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6672 */
	{.type Absolute, {.p 1}},		/* dd 1 6680 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6688 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore 6696 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6704 */
	{.type Header, {.hdr { 5, "allot", /* C_allot = 6720 */ colon }}}, /* CENTRY "allot" allot 5 h 6728 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6736 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore 6744 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6752 */
	{.type Header, {.hdr { 3, "pad", /* C_pad = 6768 */ colon }}}, /* CENTRY "pad" pad 3 h 6776 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6784 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6792 */
	{.type Absolute, {.p 256}},		/* dd 256 6800 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 6808 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6816 */
	{.type Header, {.hdr { 5, "align", /* C_align = 6832 */ colon }}}, /* CENTRY "align" align 5 h 6840 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6848 */
	{.type FromH0, {.p C_aligned}},		/* dd C_aligned 6856 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6864 */
	{.type FromH0, {.p M_store}},		/* dd M_store 6872 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6880 */
	{.type Header, {.hdr { 6, "unused", /* C_unused = 6896 */ colon }}}, /* CENTRY "unused" unused 6 h 6904 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0 6912 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 6920 */
	{.type FromH0, {.p C_here}},		/* dd C_here 6928 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 6936 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 6944 */
	{.type Header, {.hdr { 2, "<#", /* C_fromhash = 6960 */ colon }}}, /* CENTRY "<#" fromhash 2 h 6968 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 6976 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 6984 */
	{.type Absolute, {.p 1024}},		/* dd 1024 6992 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7000 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7008 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7016 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7024 */
	{.type Header, {.hdr { 1, "#", /* C_hash = 7040 */ colon }}}, /* CENTRY "#" hash 1 h 7048 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 7056 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7064 */
	{.type FromH0, {.p M_uslashmod}},		/* dd M_uslashmod 7072 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7080 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7088 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7096 */
	{.type Absolute, {.p 9}},		/* dd 9 7104 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 7112 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 7120 */
	{.type FromH0, {.p L92}},		/* dd L92 7128 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7136 */
	{.type Absolute, {.p 97}},		/* dd 97 7144 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7152 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7160 */
	{.type Absolute, {.p 10}},		/* dd 10 7168 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 7176 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 7184 */
	{.type FromH0, {.p L93}},		/* dd L93 7192 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7200 */
	{.type Absolute, {.p 48}},		/* dd 48 7208 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7216 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7224 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7232 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 7240 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7248 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7256 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7264 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 7272 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7280 */
	{.type Header, {.hdr { 2, "#s", /* C_hashs = 7296 */ colon }}}, /* CENTRY "#s" hashs 2 h 7304 */
	{.type FromH0, {.p C_hash}},		/* dd C_hash 7312 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7320 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 7328 */
	{.type FromH0, {.p L96}},		/* dd L96 7336 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 7344 */
	{.type FromH0, {.p L95}},		/* dd L95 7352 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7360 */
	{.type Header, {.hdr { 2, "#>", /* C_hashfrom = 7376 */ colon }}}, /* CENTRY "#>" hashfrom 2 h 7384 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 7392 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7400 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7408 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7416 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 7424 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7432 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7440 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 7448 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7456 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 7464 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7472 */
	{.type Header, {.hdr { 4, "hold", /* C_hold = 7488 */ colon }}}, /* CENTRY "hold" hold 4 h 7496 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7504 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 7512 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 7520 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7528 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 7536 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 7544 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 7552 */
	{.type FromH0, {.p MV_toNum}},		/* dd MV_toNum 7560 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7568 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7576 */
	{.type Header, {.hdr { 4, "sign", /* C_sign = 7592 */ colon }}}, /* CENTRY "sign" sign 4 h 7600 */
	{.type FromH0, {.p C_0lt}},		/* dd C_0lt 7608 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 7616 */
	{.type FromH0, {.p L100}},		/* dd L100 7624 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7632 */
	{.type Absolute, {.p 45}},		/* dd 45 7640 */
	{.type FromH0, {.p C_hold}},		/* dd C_hold 7648 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7656 */
	{.type Header, {.hdr { 1, ".", /* C_dot = 7672 */ colon }}}, /* CENTRY "." dot 1 h 7680 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7688 */
	{.type FromH0, {.p C_abs}},		/* dd C_abs 7696 */
	{.type FromH0, {.p C_fromhash}},		/* dd C_fromhash 7704 */
	{.type FromH0, {.p C_hashs}},		/* dd C_hashs 7712 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7720 */
	{.type FromH0, {.p C_sign}},		/* dd C_sign 7728 */
	{.type FromH0, {.p C_hashfrom}},		/* dd C_hashfrom 7736 */
	{.type FromH0, {.p C_type}},		/* dd C_type 7744 */
	{.type FromH0, {.p C_space}},		/* dd C_space 7752 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7760 */
	{.type Header, {.hdr { 2, ".r", /* C_dotr = 7776 */ colon }}}, /* CENTRY ".r" dotr 2 h 7784 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 7792 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 7800 */
	{.type FromH0, {.p C_abs}},		/* dd C_abs 7808 */
	{.type FromH0, {.p C_fromhash}},		/* dd C_fromhash 7816 */
	{.type FromH0, {.p C_hashs}},		/* dd C_hashs 7824 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 7832 */
	{.type FromH0, {.p C_sign}},		/* dd C_sign 7840 */
	{.type FromH0, {.p C_hashfrom}},		/* dd C_hashfrom 7848 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 7856 */
	{.type FromH0, {.p M_over}},		/* dd M_over 7864 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 7872 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7880 */
	{.type Absolute, {.p 0}},		/* dd 0 7888 */
	{.type FromH0, {.p C_max}},		/* dd C_max 7896 */
	{.type FromH0, {.p C_spaces}},		/* dd C_spaces 7904 */
	{.type FromH0, {.p C_type}},		/* dd C_type 7912 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7920 */
	{.type Header, {.hdr { 3, "hex", /* C_hex = 7936 */ colon }}}, /* CENTRY "hex" hex 3 h 7944 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 7952 */
	{.type Absolute, {.p 16}},		/* dd 16 7960 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 7968 */
	{.type FromH0, {.p M_store}},		/* dd M_store 7976 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 7984 */
	{.type Header, {.hdr { 7, "decimal", /* C_decimal = 8000 */ colon }}}, /* CENTRY "decimal" decimal 7 h 8008 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8016 */
	{.type Absolute, {.p 10}},		/* dd 10 8024 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 8032 */
	{.type FromH0, {.p M_store}},		/* dd M_store 8040 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8048 */
	{.type Header, {.hdr { 5, "digit", /* C_digit = 8064 */ colon }}}, /* CENTRY "digit" digit 5 ; c -- h 8072 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8080 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8088 */
	{.type Absolute, {.p 65}},		/* dd 65 8096 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8104 */
	{.type Absolute, {.p 91}},		/* dd 91 8112 */
	{.type FromH0, {.p C_within}},		/* dd C_within 8120 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8128 */
	{.type FromH0, {.p L106}},		/* dd L106 8136 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8144 */
	{.type Absolute, {.p 55}},		/* dd 55 8152 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 8160 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8168 */
	{.type FromH0, {.p L107}},		/* dd L107 8176 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8184 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8192 */
	{.type Absolute, {.p 97}},		/* dd 97 8200 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8208 */
	{.type Absolute, {.p 123}},		/* dd 123 8216 */
	{.type FromH0, {.p C_within}},		/* dd C_within 8224 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8232 */
	{.type FromH0, {.p L108}},		/* dd L108 8240 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8248 */
	{.type Absolute, {.p 87}},		/* dd 87 8256 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 8264 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8272 */
	{.type FromH0, {.p L109}},		/* dd L109 8280 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8288 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8296 */
	{.type Absolute, {.p 48}},		/* dd 48 8304 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8312 */
	{.type Absolute, {.p 58}},		/* dd 58 8320 */
	{.type FromH0, {.p C_within}},		/* dd C_within 8328 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8336 */
	{.type FromH0, {.p L110}},		/* dd L110 8344 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8352 */
	{.type Absolute, {.p 48}},		/* dd 48 8360 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 8368 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8376 */
	{.type FromH0, {.p L111}},		/* dd L111 8384 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8392 */
	{.type FromH0, {.p C_false}},		/* dd C_false 8400 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8408 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 8416 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 8424 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 8432 */
	{.type FromH0, {.p M_less}},		/* dd M_less 8440 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8448 */
	{.type FromH0, {.p L112}},		/* dd L112 8456 */
	{.type FromH0, {.p C_true}},		/* dd C_true 8464 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8472 */
	{.type FromH0, {.p L113}},		/* dd L113 8480 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8488 */
	{.type FromH0, {.p C_false}},		/* dd C_false 8496 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8504 */
	{.type Header, {.hdr { 6, "number", /* C_number = 8520 */ colon }}}, /* CENTRY "number" number 6 ; ( a n1 -- n2 -1 | a n1 0 ) h 8528 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap	; ( a n1 -- n1 a ) 8536 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n1 a -- n1 a a ) 8544 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch	; ( n1 a a -- n1 a c ) 8552 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8560 */
	{.type Absolute, {.p 45}},		/* dd 45		; ( n1 a c -- n1 a c - ) 8568 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( n1 a c -- n1 a f ) 8576 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump	; ( n1 a c -- n1 a ) 8584 */
	{.type FromH0, {.p L115}},		/* dd L115		; c != - 8592 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus	; c == - ( n1 a -- n1 a+1 ) 8600 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 8608 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 ) 8616 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8624 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( a+1 n1-1 -- a+1 n1-1 -1 ) 8632 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1) 8640 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8648 */
	{.type FromH0, {.p L116}},		/* dd L116 8656 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap	; ( n1 a -- a n1) 8664 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8672 */
	{.type Absolute, {.p 1}},		/* dd 1 8680 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1) 8688 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( a n1 -- a n1 n1 ) (R nr) 8696 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1) 8704 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8712 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a n1 -- a n1 0) (R nr n1) 8720 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1) 8728 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 8736 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a 0 n1 -- a 0 n1 0) (R nr n1) 8744 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1) 8752 */
	{.type FromH0, {.p MV_Base}},		/* dd MV_Base 8760 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1) 8768 */
	{.type FromH0, {.p M_multiply}},		/* dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1) 8776 */
	{.type FromH0, {.p M_over}},		/* dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1) 8784 */
	{.type FromH0, {.p M_i}},		/* dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1) 8792 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1) 8800 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1) 8808 */
	{.type FromH0, {.p C_digit}},		/* dd C_digit 8816 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 8824 */
	{.type FromH0, {.p L118}},		/* dd L118 8832 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 8840 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 8848 */
	{.type FromH0, {.p L119}},		/* dd L119 8856 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8864 */
	{.type FromH0, {.p M_unloop}},		/* dd M_unloop 8872 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8880 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8888 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8896 */
	{.type FromH0, {.p C_false}},		/* dd C_false 8904 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8912 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 8920 */
	{.type FromH0, {.p L117}},		/* dd L117 8928 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8936 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 8944 */
	{.type FromH0, {.p C_nip}},		/* dd C_nip 8952 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 8960 */
	{.type FromH0, {.p M_multiply}},		/* dd M_multiply 8968 */
	{.type FromH0, {.p C_true}},		/* dd C_true 8976 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 8984 */
	{.type Header, {.hdr { 5, "abort", /* C_abort = 9000 */ colon }}}, /* CENTRY "abort" abort 5 h 9008 */
	{.type FromH0, {.p MV_Abortvec}},		/* dd MV_Abortvec 9016 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9024 */
	{.type FromH0, {.p M_execute}},		/* dd M_execute 9032 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9040 */
	{.type Header, {.hdr { 6, "source", /* C_source = 9056 */ colon }}}, /* CENTRY "source" source 6 h 9064 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9072 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9080 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9088 */
	{.type Header, {.hdr { 13, "current-input", /* C_current_input = 9112 */ colon }}}, /* CENTRY "current-input" current_input 13 ; ( -- c ) read the next character from the location in Sourcebuf h 9120 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9128 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9136 */
	{.type FromH0, {.p C_source}},		/* dd C_source 9144 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus		; Sourcebuf + >In 9152 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 9160 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9168 */
	{.type Header, {.hdr { 10, "save-input", /* C_save_input = 9192 */ colon }}}, /* CENTRY "save-input" save_input 10 h 9200 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 9208 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9216 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9224 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9232 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9240 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9248 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9256 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 9264 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9272 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9280 */
	{.type Absolute, {.p 5}},		/* dd 5 9288 */
	{.type FromH0, {.p MV_Ninputs}},		/* dd MV_Ninputs 9296 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; Ninputs++ 9304 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9312 */
	{.type Header, {.hdr { 13, "default-input", /* C_default_input = 9336 */ colon }}}, /* CENTRY "default-input" default_input 13 h 9344 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 9352 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9360 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9368 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9376 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9384 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib 9392 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9400 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9408 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 9416 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9424 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9432 */
	{.type Header, {.hdr { 13, "restore-input", /* C_restore_input = 9456 */ colon }}}, /* CENTRY "restore-input" restore_input 13 ; ( <input>|empty -- f ) h 9464 */
	{.type FromH0, {.p MV_Ninputs}},		/* dd MV_Ninputs	; if Ninputs == 0, leave 0 on the stack. Or, Ninputs-- 9472 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9480 */
	{.type FromH0, {.p C_0neq}},		/* dd C_0neq 9488 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9496 */
	{.type FromH0, {.p L300}},		/* dd L300 9504 */
	{.type FromH0, {.p MV_Ninputs}},		/* dd MV_Ninputs	; there are <input>'s pending on the stack 9512 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9520 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus 9528 */
	{.type FromH0, {.p MV_Ninputs}},		/* dd MV_Ninputs 9536 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9544 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 9552 */
	{.type FromH0, {.p L301}},		/* dd L301		; ( <input> -- <input>) 9560 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9568 */
	{.type Absolute, {.p 0}},		/* dd 0 9576 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 9584 */
	{.type FromH0, {.p C_off}},		/* dd C_off 9592 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9600 */
	{.type Absolute, {.p 5}},		/* dd 5 9608 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 9616 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9624 */
	{.type FromH0, {.p L133}},		/* dd L133 9632 */
	{.type FromH0, {.p C_default_input}},		/* dd C_default_input 9640 */
	{.type FromH0, {.p C_false}},		/* dd C_false 9648 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 9656 */
	{.type FromH0, {.p L134}},		/* dd L134 9664 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 9672 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9680 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf 9688 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9696 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9704 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9712 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9720 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9728 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 9736 */
	{.type FromH0, {.p M_store}},		/* dd M_store 9744 */
	{.type FromH0, {.p C_true}},		/* dd C_true 9752 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9760 */
	{.type Header, {.hdr { 14, "?restore-input", /* C_qrestore_input = 9784 */ colon }}}, /* CENTRY "?restore-input" qrestore_input 14 ; ( <input> -- f ) h 9792 */
	{.type FromH0, {.p C_restore_input}},		/* dd C_restore_input 9800 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 9808 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 9816 */
	{.type FromH0, {.p L136}},		/* dd L136 9824 */
	{.type FromH0, {.p C_space}},		/* dd C_space 9832 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9840 */
	{.type FromH0, {.p L137}},		/* dd L137 9848 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 9856 */
	{.type Absolute, {.p 23}},		/* dd 23 9864 */
	{.type FromH0, {.p C_type}},		/* dd C_type 9872 */
	{.type FromH0, {.p C_space}},		/* dd C_space 9880 */
	{.type FromH0, {.p C_depth}},		/* dd C_depth 9888 */
	{.type FromH0, {.p C_dot}},		/* dd C_dot 9896 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 9904 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 9912 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 9920 */
	{.type Header, {.hdr { 10, "next-input", /* C_next_input = 9944 */ colon }}}, /* CENTRY "next-input" next_input 10 ; when >In < >Limit ( -- true c ). ( -- 0 false ) otherwise h 9952 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 9960 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9968 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 9976 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 9984 */
	{.type FromH0, {.p M_less}},		/* dd M_less 9992 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10000 */
	{.type FromH0, {.p L139}},		/* dd L139	; >In >= >Limit 10008 */
	{.type FromH0, {.p C_true}},		/* dd C_true	; >In < >Limit 10016 */
	{.type FromH0, {.p C_current_input}},		/* dd C_current_input	; ( -- c ) 10024 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10032 */
	{.type FromH0, {.p L140}},		/* dd L140 10040 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10048 */
	{.type Absolute, {.p 0}},		/* dd 0 10056 */
	{.type FromH0, {.p C_false}},		/* dd C_false 10064 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10072 */
	{.type Header, {.hdr { 5, "parse", /* C_parse = 10088 */ colon }}}, /* CENTRY "parse" parse 5 ; ( c -- a ) Place the counted string in the address in Wordbuf and return that address. c = word delimiter. h 10096 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush		; ( c -- ) (R -- c ) 10104 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf 10112 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; ( -- Wordb ) 10120 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus		; ( Wordb -- Wordb+1 ) 10128 */
	{.type FromH0, {.p C_next_input}},		/* dd C_next_input ; ( Wordb+1 -- Wordb+1 f c ) 10136 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c ) 10144 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) ) 10152 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 10160 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10168 */
	{.type FromH0, {.p L143}},		/* dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew 10176 */
	{.type FromH0, {.p C_current_input}},		/* dd C_current_input	; ( Wordb+1 -- Wordb+1 c ) 10184 */
	{.type FromH0, {.p M_over}},		/* dd M_over 10192 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1 10200 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus		; ( Wordb+1 -- Wordb+2 ) 10208 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10216 */
	{.type Absolute, {.p 1}},		/* dd 1 10224 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 10232 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; >In++ 10240 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10248 */
	{.type FromH0, {.p L142}},		/* dd L142		; ( Wordb+2 ) repeat 10256 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10264 */
	{.type Absolute, {.p 1}},		/* dd 1 10272 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 10280 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; >In++ 10288 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- ) 10296 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; (Wordb+1 c -- Wordb+1) 10304 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf 10312 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb) 10320 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb) 10328 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb) 10336 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb) 10344 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb) 10352 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb) 10360 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now. 10368 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop		; ( -- Wordb) (R Wordb -- ) 10376 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10384 */
	{.type Header, {.hdr { 4, "word", /* C_word = 10400 */ colon }}}, /* CENTRY "word" word 4 ; ( c -- a ) skip the c"s. Placed the counted string in a (as in Wordbuf) h 10408 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( -- ) (R -- c ) 10416 */
	{.type FromH0, {.p C_next_input}},		/* dd C_next_input ; ( -- f c2 ) (R c1 -- ) 10424 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial ) 10432 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial ) 10440 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial ) 10448 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10456 */
	{.type FromH0, {.p L146}},		/* dd L146		; >In >= >Limit || cinitial != cnew 10464 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal	; >In < >Limit && cinitial == cnew 10472 */
	{.type Absolute, {.p 1}},		/* dd 1 10480 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 10488 */
	{.type FromH0, {.p C_plusstore}},		/* dd C_plusstore	; >In++ 10496 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump		; repeat 10504 */
	{.type FromH0, {.p L145}},		/* dd L145 10512 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character 10520 */
	{.type FromH0, {.p C_parse}},		/* dd C_parse 10528 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10536 */
	{.type Header, {.hdr { 6, "accept", /* C_accept = 10552 */ colon }}}, /* CENTRY "accept" accept 6 ; ( a n -- n ) get line or n chars or EOF from input and store at a h 10560 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap	; ( n a -- ) 10568 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n a a -- ) 10576 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 10584 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( n -- ) (R a a -- ) 10592 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup	; ( n n -- ) (R a a -- ) 10600 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump	; (if) 10608 */
	{.type FromH0, {.p L149}},		/* dd L149	; n == 0 10616 */
	{.type FromH0, {.p C_key}},		/* dd C_key	; n > 0 ( n -- n c ) 10624 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( -- n c c ) 10632 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10640 */
	{.type Absolute, {.p 10}},		/* dd 10		; ( -- n c c 10 ) 10648 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( n c c 10 -- n c f ) checking for newline 10656 */
	{.type FromH0, {.p M_over}},		/* dd M_over	; ( -- n c f c ) 10664 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10672 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( -- n c f c -1 ) 10680 */
	{.type FromH0, {.p M_equal}},		/* dd M_equal	; ( -- n c f1 f2 ) 10688 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor	; ( -- n c f ) 10696 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10704 */
	{.type FromH0, {.p L150}},		/* dd L150 10712 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop	; n == -1 || n == 10 (	-- ) 10720 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 10728 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 10736 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( -- a2-a1 ) 10744 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon	; ( -- n ) (R -- ) 10752 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch	; ( n c a -- ) (R a a -- ) 10760 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore	; store the character at a 10768 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( n a -- ) (R a -- ) 10776 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 10784 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address 10792 */
	{.type FromH0, {.p C_1minus}},		/* dd C_1minus	; ( n -- n-1 ) 10800 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 10808 */
	{.type FromH0, {.p L148}},		/* dd L148	; loop again for the next character 10816 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 ) 10824 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop	; ( a2 a1 -- ) (R a1 -- ) 10832 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( a2 a1 -- a2-a1 ) 10840 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 10848 */
	{.type Header, {.hdr { 5, "query", /* C_query = 10864 */ colon }}}, /* CENTRY "query" query 5 ; read from input stream into the Text Input Buffer h 10872 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 10880 */
	{.type FromH0, {.p C_off}},		/* dd C_off		; clear EOF flag 10888 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib	; constant puts address of tibuffer on the top 10896 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 10904 */
	{.type Absolute, {.p 4096}},		/* dd 4096	; ( tibuffer -- tibuffer 4096 ) 10912 */
	{.type FromH0, {.p C_accept}},		/* dd C_accept ; ( tibuffer 4096 -- n ) 10920 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( n -- n n ) 10928 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq	; ( n n -- n f ) 10936 */
	{.type FromH0, {.p MV_Eof}},		/* dd MV_Eof 10944 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 10952 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; n == 0 && EOF 10960 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 10968 */
	{.type FromH0, {.p L152}},		/* dd L152		; false condition 10976 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop	; n == 0 && EOF ( n -- ) 10984 */
	{.type FromH0, {.p C_qrestore_input}},		/* dd C_qrestore_input 10992 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11000 */
	{.type FromH0, {.p L153}},		/* dd L153 11008 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 11016 */
	{.type FromH0, {.p M_store}},		/* dd M_store		; number of characters to read >Limit = n 11024 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 11032 */
	{.type FromH0, {.p C_off}},		/* dd C_off		; start from 0 >In = 0 11040 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11048 */
	{.type Header, {.hdr { 6, "refill", /* C_refill = 11064 */ colon }}}, /* CENTRY "refill" refill 6 h 11072 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 11080 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 11088 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11096 */
	{.type FromH0, {.p L155}},		/* dd L155 11104 */
	{.type FromH0, {.p C_false}},		/* dd C_false 11112 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11120 */
	{.type FromH0, {.p L156}},		/* dd L156 11128 */
	{.type FromH0, {.p C_query}},		/* dd C_query 11136 */
	{.type FromH0, {.p C_true}},		/* dd C_true 11144 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11152 */
	{.type Header, {.hdr { 8, "findname", /* C_findname = 11176 */ colon }}}, /* CENTRY "findname" findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names h 11184 */
	{.type FromH0, {.p MV_Findadr}},		/* dd MV_Findadr 11192 */
	{.type FromH0, {.p M_store}},		/* dd M_store 11200 */
	{.type FromH0, {.p M_Dtop}},		/* dd M_Dtop 11208 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; get latest dictionary link 11216 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 11224 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11232 */
	{.type FromH0, {.p L159}},		/* dd L159	; seached until the first dictionary entry get out 11240 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( a -- a a ) 11248 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus	; ( a a -- a a+8) lenth + initial name address 11256 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name 11264 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11272 */
	{.type Absolute, {.p 64}},		/* dd 64		; check the reveal'ed flag 1=hidden, 0=reveal 11280 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; if hidden, goto L161 else L160 11288 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11296 */
	{.type FromH0, {.p L160}},		/* dd L160 11304 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; smudge'd dictionary entry, get the previous entry 11312 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11320 */
	{.type FromH0, {.p L161}},		/* dd L161 11328 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup	; ( a1 -- a1 a1) 11336 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus	; ( a1 a1 -- a1 a1+8) 11344 */
	{.type FromH0, {.p C_count}},		/* dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n ) 11352 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11360 */
	{.type Absolute, {.p 63}},		/* dd 63 11368 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len ) 11376 */
	{.type FromH0, {.p MV_Findadr}},		/* dd MV_Findadr 11384 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 11392 */
	{.type FromH0, {.p C_count}},		/* dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 ) 11400 */
	{.type FromH0, {.p C_compare}},		/* dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name 11408 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq	; found a match? 11416 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11424 */
	{.type FromH0, {.p L162}},		/* dd L162		; no match 11432 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus	; match found 11440 */
	{.type FromH0, {.p C_true}},		/* dd C_true 11448 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11456 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 11464 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11472 */
	{.type FromH0, {.p L158}},		/* dd L158 11480 */
	{.type FromH0, {.p MV_Findadr}},		/* dd MV_Findadr 11488 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 11496 */
	{.type FromH0, {.p C_false}},		/* dd C_false 11504 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11512 */
	{.type Header, {.hdr { 4, "find", /* C_find = 11528 */ colon }}}, /* CENTRY "find" find 4 ; ( a1 -- a2 f )? h 11536 */
	{.type FromH0, {.p C_findname}},		/* dd C_findname 11544 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11552 */
	{.type FromH0, {.p L164}},		/* dd L164 11560 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 11568 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 11576 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 11584 */
	{.type FromH0, {.p M_over}},		/* dd M_over 11592 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11600 */
	{.type Absolute, {.p 63}},		/* dd 63 11608 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 11616 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 11624 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 11632 */
	{.type FromH0, {.p C_aligned}},		/* dd C_aligned 11640 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 11648 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11656 */
	{.type Absolute, {.p 128}},		/* dd 128 11664 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 11672 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11680 */
	{.type FromH0, {.p L165}},		/* dd L165 11688 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11696 */
	{.type Absolute, {.p 1}},		/* dd 1 11704 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11712 */
	{.type FromH0, {.p L166}},		/* dd L166 11720 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11728 */
	{.type Absolute, {.p -1}},		/* dd -1 11736 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11744 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 11752 */
	{.type FromH0, {.p L167}},		/* dd L167 11760 */
	{.type FromH0, {.p C_false}},		/* dd C_false 11768 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11776 */
	{.type Header, {.hdr { 1, "'", /* C_single_quote = 11792 */ colon }}}, /* CENTRY "'" single_quote 1 h 11800 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 11808 */
	{.type FromH0, {.p C_word}},		/* dd C_word 11816 */
	{.type FromH0, {.p C_find}},		/* dd C_find 11824 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 11832 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11840 */
	{.type FromH0, {.p L169}},		/* dd L169 11848 */
	{.type FromH0, {.p C_space}},		/* dd C_space 11856 */
	{.type FromH0, {.p C_count}},		/* dd C_count 11864 */
	{.type FromH0, {.p C_type}},		/* dd C_type 11872 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11880 */
	{.type FromH0, {.p L170}},		/* dd L170 11888 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 11896 */
	{.type Absolute, {.p 3}},		/* dd 3 11904 */
	{.type FromH0, {.p C_type}},		/* dd C_type 11912 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 11920 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 11928 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 11936 */
	{.type Header, {.hdr { 6, "?stack", /* C_qstack = 11952 */ colon }}}, /* CENTRY "?stack" qstack 6 h 11960 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr 11968 */
	{.type FromH0, {.p M_S0}},		/* dd M_S0 11976 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 11984 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 11992 */
	{.type FromH0, {.p L172}},		/* dd L172 12000 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12008 */
	{.type FromH0, {.p L173}},		/* dd L173 12016 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12024 */
	{.type Absolute, {.p 16}},		/* dd 16 12032 */
	{.type FromH0, {.p C_type}},		/* dd C_type 12040 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 12048 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 12056 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12064 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup ; debug code to show the word found 12072 */
	{.type FromH0, {.p C_count}},		/* dd C_count ; ( -- a n) 12080 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap ; ( -- n a) 12088 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 12096 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite 12104 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; drop the return value of write 12112 */
	{.type Header, {.hdr { 9, "interpret", /* C_interpret = 12136 */ colon }}}, /* CENTRY "interpret" interpret 9 ; there is stuff in TIB to be interpreted >In and >Limit are set h 12144 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 12152 */
	{.type FromH0, {.p C_word}},		/* dd C_word	; ( bl -- a ) a = address of counted string 12160 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12168 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 12176 */
	{.type FromH0, {.p C_0neq}},		/* dd C_0neq 12184 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12192 */
	{.type FromH0, {.p L176}},		/* dd L176	; count at a = 0 12200 */
	{.type FromH0, {.p C_find}},		/* dd C_find	; ( a -- a1 f ) a = address of counted string 12208 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12216 */
	{.type FromH0, {.p L177}},		/* dd L177 12224 */
	{.type FromH0, {.p M_execute}},		/* dd M_execute	; found in dictionary, execute 12232 */
	{.type FromH0, {.p C_qstack}},		/* dd C_qstack 12240 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 12248 */
	{.type FromH0, {.p L178}},		/* dd L178 12256 */
	{.type FromH0, {.p C_count}},		/* dd C_count 12264 */
	{.type FromH0, {.p C_number}},		/* dd C_number 12272 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 12280 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 12288 */
	{.type FromH0, {.p L179}},		/* dd L179 12296 */
	{.type FromH0, {.p C_space}},		/* dd C_space 12304 */
	{.type FromH0, {.p C_type}},		/* dd C_type 12312 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12320 */
	{.type FromH0, {.p L180}},		/* dd L180	; error I? 12328 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12336 */
	{.type Absolute, {.p 3}},		/* dd 3 12344 */
	{.type FromH0, {.p C_type}},		/* dd C_type 12352 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 12360 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 12368 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 12376 */
	{.type FromH0, {.p L175}},		/* dd L175 12384 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop	; count at a = 0 ( a -- ) 12392 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12400 */
	{.type Header, {.hdr { 6, "create", /* C_create = 12416 */ colon }}}, /* CENTRY "create" create 6 h 12424 */
	{.type FromH0, {.p C_align}},		/* dd C_align 12432 */
	{.type FromH0, {.p C_here}},		/* dd C_here 12440 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 12448 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 12456 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12464 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12472 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 12480 */
	{.type FromH0, {.p C_word}},		/* dd C_word 12488 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12496 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 12504 */
	{.type FromH0, {.p C_here}},		/* dd C_here 12512 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 12520 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 12528 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12536 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 12544 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 12552 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 12560 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 12568 */
	{.type FromH0, {.p C_align}},		/* dd C_align 12576 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12584 */
	{.type FromH0, {.p M_variable}},		/* dd M_variable 12592 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12600 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12608 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 12616 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 12624 */
	{.type FromH0, {.p M_store}},		/* dd M_store 12632 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12640 */
	{.type Header, {.hdr { 8, "variable", /* C_variable = 12664 */ colon }}}, /* CENTRY "variable" variable 8 h 12672 */
	{.type FromH0, {.p C_create}},		/* dd C_create 12680 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12688 */
	{.type Absolute, {.p 0}},		/* dd 0 12696 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12704 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12712 */
	{.type Header, {.hdr { 8, "constant", /* C_constant = 12736 */ colon }}}, /* CENTRY "constant" constant 8 h 12744 */
	{.type FromH0, {.p C_create}},		/* dd C_create 12752 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12760 */
	{.type FromH0, {.p M_constant}},		/* dd M_constant 12768 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12776 */
	{.type FromH0, {.p C_here}},		/* dd C_here 12784 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12792 */
	{.type Absolute, {.p 1}},		/* dd 1 12800 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 12808 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 12816 */
	{.type FromH0, {.p M_store}},		/* dd M_store 12824 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 12832 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12840 */
	{.type Header, {.hdr { 9, "immediate", /* C_immediate = 12864 */ colon }}}, /* CENTRY "immediate" immediate 9 h 12872 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 12880 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 12888 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 12896 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 12904 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 12912 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 12920 */
	{.type Absolute, {.p 128}},		/* dd 128 12928 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 12936 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 12944 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 12952 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 12960 */
	{.type Header, {.hdr { 4, ">cfa", /* C_tocfa = 12976 */ colon }}}, /* CENTRY ">cfa" tocfa 4 h 12984 */
	{.type FromH0, {.p C_count}},		/* dd C_count 12992 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13000 */
	{.type Absolute, {.p 63}},		/* dd 63 13008 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 13016 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 13024 */
	{.type FromH0, {.p C_aligned}},		/* dd C_aligned 13032 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13040 */
	{.type Header, {.hdr { 7, "compile", /* C_compile = 13056 */ colon }}}, /* CENTRY "compile" compile 7 h 13064 */
	{.type FromH0, {.p C_findname}},		/* dd C_findname 13072 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 13080 */
	{.type FromH0, {.p L188}},		/* dd L188 13088 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13096 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13104 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13112 */
	{.type Absolute, {.p 128}},		/* dd 128 13120 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 13128 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 13136 */
	{.type FromH0, {.p L189}},		/* dd L189 13144 */
	{.type FromH0, {.p C_tocfa}},		/* dd C_tocfa	; immediate 13152 */
	{.type FromH0, {.p M_execute}},		/* dd M_execute 13160 */
	{.type FromH0, {.p C_qstack}},		/* dd C_qstack 13168 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13176 */
	{.type FromH0, {.p L190}},		/* dd L190 13184 */
	{.type FromH0, {.p C_tocfa}},		/* dd C_tocfa 13192 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13200 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13208 */
	{.type FromH0, {.p L191}},		/* dd L191 13216 */
	{.type FromH0, {.p C_count}},		/* dd C_count 13224 */
	{.type FromH0, {.p C_number}},		/* dd C_number 13232 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 13240 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 13248 */
	{.type FromH0, {.p L192}},		/* dd L192 13256 */
	{.type FromH0, {.p C_space}},		/* dd C_space 13264 */
	{.type FromH0, {.p C_type}},		/* dd C_type 13272 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13280 */
	{.type FromH0, {.p L193}},		/* dd L193 13288 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13296 */
	{.type Absolute, {.p 3}},		/* dd 3 13304 */
	{.type FromH0, {.p C_type}},		/* dd C_type 13312 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 13320 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 13328 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13336 */
	{.type FromH0, {.p L194}},		/* dd L194 13344 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13352 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13360 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13368 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 13376 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13384 */
	{.type Header, {.hdr { 1, "]", /* C_close_bracket = 13400 */ colon }}}, /* CENTRY "]" close_bracket 1 h 13408 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13416 */
	{.type FromH0, {.p C_on}},		/* dd C_on 13424 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 13432 */
	{.type FromH0, {.p C_word}},		/* dd C_word 13440 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13448 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13456 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 13464 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 13472 */
	{.type FromH0, {.p L197}},		/* dd L197 13480 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 13488 */
	{.type FromH0, {.p C_refill}},		/* dd C_refill 13496 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13504 */
	{.type FromH0, {.p L198}},		/* dd L198 13512 */
	{.type FromH0, {.p C_compile}},		/* dd C_compile 13520 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13528 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13536 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 13544 */
	{.type FromH0, {.p L199}},		/* dd L199 13552 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 13560 */
	{.type FromH0, {.p L196}},		/* dd L196 13568 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13576 */
	{.type IHeader, {.hdr { 1, "[", /* CI_open_bracket = 13592 */ colon }}}, /* CIENTRY "[" open_bracket 1 h 13600 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 13608 */
	{.type FromH0, {.p C_off}},		/* dd C_off 13616 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13624 */
	{.type Header, {.hdr { 6, "smudge", /* C_smudge = 13640 */ colon }}}, /* CENTRY "smudge" smudge 6 h 13648 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 13656 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13664 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 13672 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13680 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13688 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13696 */
	{.type Absolute, {.p 64}},		/* dd 64 13704 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 13712 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 13720 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 13728 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13736 */
	{.type Header, {.hdr { 6, "reveal", /* C_reveal = 13752 */ colon }}}, /* CENTRY "reveal" reveal 6 h 13760 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 13768 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13776 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 13784 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 13792 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 13800 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13808 */
	{.type Absolute, {.p 64}},		/* dd 64 13816 */
	{.type FromH0, {.p C_invert}},		/* dd C_invert 13824 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 13832 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 13840 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 13848 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13856 */
	{.type Header, {.hdr { 1, ":", /* C_colon = 13872 */ colon }}}, /* CENTRY ":" colon 1 h 13880 */
	{.type FromH0, {.p C_create}},		/* dd C_create 13888 */
	{.type FromH0, {.p C_smudge}},		/* dd C_smudge 13896 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13904 */
	{.type FromH0, {.p M_colon}},		/* dd M_colon 13912 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 13920 */
	{.type FromH0, {.p C_here}},		/* dd C_here 13928 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 13936 */
	{.type Absolute, {.p 1}},		/* dd 1 13944 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells 13952 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus 13960 */
	{.type FromH0, {.p M_store}},		/* dd M_store 13968 */
	{.type FromH0, {.p C_close_bracket}},		/* dd C_close_bracket 13976 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 13984 */
	{.type IHeader, {.hdr { 1, ";", /* CI_semicolon = 14000 */ colon }}}, /* CIENTRY ";" semicolon 1 h 14008 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14016 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14024 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14032 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 14040 */
	{.type FromH0, {.p C_off}},		/* dd C_off 14048 */
	{.type FromH0, {.p C_reveal}},		/* dd C_reveal 14056 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14064 */
	{.type IHeader, {.hdr { 7, "recurse", /* CI_recurse = 14080 */ colon }}}, /* CIENTRY "recurse" recurse 7 h 14088 */
	{.type FromH0, {.p M_Dp}},		/* dd M_Dp 14096 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14104 */
	{.type FromH0, {.p C_cellplus}},		/* dd C_cellplus 14112 */
	{.type FromH0, {.p C_tocfa}},		/* dd C_tocfa 14120 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14128 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14136 */
	{.type Header, {.hdr { 4, "char", /* C_L206 = 14152 */ colon }}}, /* CENTRY "char" L206 4 h 14160 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 14168 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14176 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14184 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14192 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14200 */
	{.type Header, {.hdr { 7, "literal", /* C_literal = 14216 */ colon }}}, /* CENTRY "literal" literal 7 h 14224 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14232 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14240 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14248 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14256 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14264 */
	{.type Header, {.hdr { 8, "sliteral", /* C_sliteral = 14288 */ colon }}}, /* CENTRY "sliteral" sliteral 8 h 14296 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14304 */
	{.type FromH0, {.p M_sliteral}},		/* dd M_sliteral 14312 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 14320 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14328 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14336 */
	{.type Absolute, {.p 34}},		/* dd 34 14344 */
	{.type FromH0, {.p C_parse}},		/* dd C_parse 14352 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 14360 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14368 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14376 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 14384 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 14392 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 14400 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 14408 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 14416 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 14424 */
	{.type FromH0, {.p C_align}},		/* dd C_align 14432 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14440 */
	{.type Header, {.hdr { 6, "string", /* C_string = 14456 */ colon }}}, /* CENTRY "string" string 6 h 14464 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14472 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 14480 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14488 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14496 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 14504 */
	{.type FromH0, {.p C_here}},		/* dd C_here 14512 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 14520 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 14528 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 14536 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 14544 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14552 */
	{.type IHeader, {.hdr { 6, "[char]", /* CI_char_brackets = 14568 */ colon }}}, /* CIENTRY "[char]" char_brackets 6 h 14576 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 14584 */
	{.type FromH0, {.p C_word}},		/* dd C_word 14592 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 14600 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 14608 */
	{.type FromH0, {.p C_literal}},		/* dd C_literal 14616 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14624 */
	{.type IHeader, {.hdr { 3, "[']", /* CI_quote_brackets = 14640 */ colon }}}, /* CIENTRY "[']" quote_brackets 3 h 14648 */
	{.type FromH0, {.p C_single_quote}},		/* dd C_single_quote 14656 */
	{.type FromH0, {.p C_literal}},		/* dd C_literal 14664 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14672 */
	{.type IHeader, {.hdr { 1, "(", /* CI_openparen = 14688 */ colon }}}, /* CIENTRY "(" openparen 1 h 14696 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14704 */
	{.type Absolute, {.p 41}},		/* dd 41 14712 */
	{.type FromH0, {.p C_parse}},		/* dd C_parse 14720 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop 14728 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14736 */
	{.type IHeader, {.hdr { 1, "\\", /* CI_backslash = 14752 */ colon }}}, /* CIENTRY "\\" backslash 1 h 14760 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk 14768 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14776 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 14784 */
	{.type FromH0, {.p L214}},		/* dd L214 14792 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 14800 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14808 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14816 */
	{.type Absolute, {.p 63}},		/* dd 63 14824 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 14832 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 14840 */
	{.type Absolute, {.p 63}},		/* dd 63 14848 */
	{.type FromH0, {.p C_invert}},		/* dd C_invert 14856 */
	{.type FromH0, {.p M_binand}},		/* dd M_binand 14864 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 14872 */
	{.type FromH0, {.p M_store}},		/* dd M_store 14880 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 14888 */
	{.type FromH0, {.p L215}},		/* dd L215 14896 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 14904 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 14912 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 14920 */
	{.type FromH0, {.p M_store}},		/* dd M_store 14928 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 14936 */
	{.type Header, {.hdr { 8, "(?abort)", /* C_qabort_parens = 14960 */ colon }}}, /* CENTRY "(?abort)" qabort_parens 8 h 14968 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 14976 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 14984 */
	{.type FromH0, {.p L217}},		/* dd L217 14992 */
	{.type FromH0, {.p C_space}},		/* dd C_space 15000 */
	{.type FromH0, {.p C_type}},		/* dd C_type 15008 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 15016 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 15024 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 15032 */
	{.type FromH0, {.p L218}},		/* dd L218 15040 */
	{.type FromH0, {.p C_2drop}},		/* dd C_2drop 15048 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15056 */
	{.type IHeader, {.hdr { 6, "abort\"", /* CI_abort_double_quote = 15072 */ colon }}}, /* CIENTRY "abort\"" abort_double_quote 6 h 15080 */
	{.type FromH0, {.p C_sliteral}},		/* dd C_sliteral 15088 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15096 */
	{.type FromH0, {.p C_qabort_parens}},		/* dd C_qabort_parens 15104 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15112 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15120 */
	{.type Header, {.hdr { 1, "\"", /* C_double_quote = 15136 */ colon }}}, /* CENTRY "\"" double_quote 1 h 15144 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15152 */
	{.type Absolute, {.p 34}},		/* dd 34 15160 */
	{.type FromH0, {.p C_word}},		/* dd C_word 15168 */
	{.type FromH0, {.p C_count}},		/* dd C_count 15176 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 15184 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15192 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 15200 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 15208 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15216 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 15224 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 15232 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 15240 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15248 */
	{.type Header, {.hdr { 2, "c\"", /* C_cdouble_quote = 15264 */ colon }}}, /* CENTRY "c\"" cdouble_quote 2 h 15272 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15280 */
	{.type Absolute, {.p 34}},		/* dd 34 15288 */
	{.type FromH0, {.p C_word}},		/* dd C_word 15296 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 15304 */
	{.type FromH0, {.p M_cfetch}},		/* dd M_cfetch 15312 */
	{.type FromH0, {.p C_1plus}},		/* dd C_1plus 15320 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 15328 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15336 */
	{.type FromH0, {.p M_rfetch}},		/* dd M_rfetch 15344 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 15352 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15360 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 15368 */
	{.type FromH0, {.p C_allot}},		/* dd C_allot 15376 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15384 */
	{.type IHeader, {.hdr { 2, "s\"", /* CI_sdouble_quote = 15400 */ colon }}}, /* CIENTRY "s\"" sdouble_quote 2 h 15408 */
	{.type FromH0, {.p C_sliteral}},		/* dd C_sliteral 15416 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15424 */
	{.type IHeader, {.hdr { 2, ".\"", /* CI_dotstr = 15440 */ colon }}}, /* CIENTRY ".\"" dotstr 2 h 15448 */
	{.type FromH0, {.p C_sliteral}},		/* dd C_sliteral 15456 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15464 */
	{.type FromH0, {.p C_type}},		/* dd C_type 15472 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15480 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15488 */
	{.type IHeader, {.hdr { 2, "if", /* CI_if = 15504 */ colon }}}, /* CIENTRY "if" if 2 h 15512 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15520 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15528 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15536 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15544 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15552 */
	{.type Absolute, {.p 0}},		/* dd 0 15560 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15568 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15576 */
	{.type IHeader, {.hdr { 4, "else", /* CI_else = 15592 */ colon }}}, /* CIENTRY "else" else 4 h 15600 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15608 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 15616 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15624 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15632 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 15640 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15648 */
	{.type Absolute, {.p 0}},		/* dd 0 15656 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15664 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15672 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15680 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15688 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 15696 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15704 */
	{.type IHeader, {.hdr { 4, "then", /* CI_then = 15720 */ colon }}}, /* CIENTRY "then" then 4 h 15728 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15736 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 15744 */
	{.type FromH0, {.p M_store}},		/* dd M_store 15752 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15760 */
	{.type IHeader, {.hdr { 5, "begin", /* CI_begin = 15776 */ colon }}}, /* CIENTRY "begin" begin 5 h 15784 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15792 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15800 */
	{.type IHeader, {.hdr { 5, "again", /* CI_again = 15816 */ colon }}}, /* CIENTRY "again" again 5 h 15824 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15832 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 15840 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15848 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15856 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15864 */
	{.type IHeader, {.hdr { 5, "until", /* CI_until = 15880 */ colon }}}, /* CIENTRY "until" until 5 h 15888 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15896 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15904 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15912 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15920 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 15928 */
	{.type IHeader, {.hdr { 5, "while", /* CI_while = 15944 */ colon }}}, /* CIENTRY "while" while 5 h 15952 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15960 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 15968 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 15976 */
	{.type FromH0, {.p C_here}},		/* dd C_here 15984 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 15992 */
	{.type Absolute, {.p 0}},		/* dd 0 16000 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 16008 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16016 */
	{.type IHeader, {.hdr { 6, "repeat", /* CI_repeat = 16032 */ colon }}}, /* CIENTRY "repeat" repeat 6 h 16040 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16048 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 16056 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 16064 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 16072 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 16080 */
	{.type FromH0, {.p C_here}},		/* dd C_here 16088 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 16096 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16104 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16112 */
	{.type IHeader, {.hdr { 2, "do", /* CI_do = 16128 */ colon }}}, /* CIENTRY "do" do 2 h 16136 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16144 */
	{.type FromH0, {.p M_doinit}},		/* dd M_doinit 16152 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 16160 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16168 */
	{.type Absolute, {.p 0}},		/* dd 0 16176 */
	{.type FromH0, {.p C_here}},		/* dd C_here 16184 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16192 */
	{.type IHeader, {.hdr { 4, "loop", /* CI_loop = 16208 */ colon }}}, /* CIENTRY "loop" loop 4 h 16216 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16224 */
	{.type FromH0, {.p M_doloop}},		/* dd M_doloop 16232 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 16240 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 16248 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 16256 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 16264 */
	{.type FromH0, {.p L234}},		/* dd L234 16272 */
	{.type FromH0, {.p C_here}},		/* dd C_here 16280 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 16288 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16296 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16304 */
	{.type IHeader, {.hdr { 5, "+loop", /* CI_ploop = 16320 */ colon }}}, /* CIENTRY "+loop" ploop 5 h 16328 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16336 */
	{.type FromH0, {.p M_doploop}},		/* dd M_doploop 16344 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 16352 */
	{.type FromH0, {.p C_comma}},		/* dd C_comma 16360 */
	{.type FromH0, {.p C_qdup}},		/* dd C_qdup 16368 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 16376 */
	{.type FromH0, {.p L236}},		/* dd L236 16384 */
	{.type FromH0, {.p C_here}},		/* dd C_here 16392 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 16400 */
	{.type FromH0, {.p M_store}},		/* dd M_store 16408 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16416 */
	{.type Header, {.hdr { 3, "w/o", /* C_wo = 16432 */ colon }}}, /* CENTRY "w/o" wo 3 h 16440 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16448 */
	{.type Absolute, {.p 1}},		/* dd 1 16456 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16464 */
	{.type Absolute, {.p 512}},		/* dd 512 16472 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 16480 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16488 */
	{.type Absolute, {.p 64}},		/* dd 64 16496 */
	{.type FromH0, {.p M_binor}},		/* dd M_binor 16504 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16512 */
	{.type Header, {.hdr { 3, "r/o", /* C_ro = 16528 */ colon }}}, /* CENTRY "r/o" ro 3 h 16536 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16544 */
	{.type Absolute, {.p 0}},		/* dd 0 16552 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16560 */
	{.type Header, {.hdr { 3, "r/w", /* C_rw = 16576 */ colon }}}, /* CENTRY "r/w" rw 3 h 16584 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16592 */
	{.type Absolute, {.p 2}},		/* dd 2 16600 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16608 */
	{.type Header, {.hdr { 9, "open-file", /* C_open_file = 16632 */ colon }}}, /* CENTRY "open-file" open_file 9 h 16640 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 16648 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 16656 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16664 */
	{.type Absolute, {.p 1024}},		/* dd 1024 16672 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 16680 */
	{.type FromH0, {.p M_xswap}},		/* dd M_xswap 16688 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 16696 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 16704 */
	{.type FromH0, {.p M_cmove}},		/* dd M_cmove 16712 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16720 */
	{.type Absolute, {.p 0}},		/* dd 0 16728 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 16736 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 16744 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 16752 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16760 */
	{.type Absolute, {.p 1024}},		/* dd 1024 16768 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 16776 */
	{.type FromH0, {.p M_cstore}},		/* dd M_cstore 16784 */
	{.type FromH0, {.p C_pad}},		/* dd C_pad 16792 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16800 */
	{.type Absolute, {.p 1024}},		/* dd 1024 16808 */
	{.type FromH0, {.p M_plus}},		/* dd M_plus 16816 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 16824 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16832 */
	{.type Absolute, {.p 420}},		/* dd 420 16840 */
	{.type FromH0, {.p M_fthopen}},		/* dd M_fthopen 16848 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 16856 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 16864 */
	{.type Absolute, {.p -1}},		/* dd -1 16872 */
	{.type FromH0, {.p M_greater}},		/* dd M_greater 16880 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16888 */
	{.type Header, {.hdr { 10, "close-file", /* C_close_file = 16912 */ colon }}}, /* CENTRY "close-file" close_file 10 h 16920 */
	{.type FromH0, {.p M_fthclose}},		/* dd M_fthclose 16928 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 16936 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 16944 */
	{.type Header, {.hdr { 9, "read-file", /* C_read_file = 16968 */ colon }}}, /* CENTRY "read-file" read_file 9 h 16976 */
	{.type FromH0, {.p M_fthread}},		/* dd M_fthread 16984 */
	{.type FromH0, {.p M_dup}},		/* dd M_dup 16992 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17000 */
	{.type Absolute, {.p -1}},		/* dd -1 17008 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 17016 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17024 */
	{.type Header, {.hdr { 10, "write-file", /* C_write_file = 17048 */ colon }}}, /* CENTRY "write-file" write_file 10 h 17056 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite 17064 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17072 */
	{.type Absolute, {.p -1}},		/* dd -1 17080 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 17088 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17096 */
	{.type Header, {.hdr { 15, "reposition-file", /* C_reposition_file = 17120 */ colon }}}, /* CENTRY "reposition-file" reposition_file 15 h 17128 */
	{.type FromH0, {.p M_fthseek}},		/* dd M_fthseek 17136 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17144 */
	{.type Absolute, {.p -1}},		/* dd -1 17152 */
	{.type FromH0, {.p C_neq}},		/* dd C_neq 17160 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17168 */
	{.type Header, {.hdr { 7, "?fcheck", /* C_qfcheck = 17184 */ colon }}}, /* CENTRY "?fcheck" qfcheck 7 h 17192 */
	{.type FromH0, {.p C_0eq}},		/* dd C_0eq 17200 */
	{.type FromH0, {.p M_cjump}},		/* dd M_cjump 17208 */
	{.type FromH0, {.p L246}},		/* dd L246 17216 */
	{.type FromH0, {.p C_space}},		/* dd C_space 17224 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17232 */
	{.type FromH0, {.p L247}},		/* dd L247 17240 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17248 */
	{.type Absolute, {.p 9}},		/* dd 9 17256 */
	{.type FromH0, {.p C_type}},		/* dd C_type 17264 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 17272 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 17280 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17288 */
	{.type Header, {.hdr { 3, "bye", /* C_bye = 17304 */ colon }}}, /* CENTRY "bye" bye 3 h 17312 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17320 */
	{.type Absolute, {.p 0}},		/* dd 0 17328 */
	{.type FromH0, {.p M_terminate}},		/* dd M_terminate 17336 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17344 */
	{.type Header, {.hdr { 7, "include", /* C_include = 17360 */ colon }}}, /* CENTRY "include" include 7 h 17368 */
	{.type FromH0, {.p C_bl}},		/* dd C_bl 17376 */
	{.type FromH0, {.p C_word}},		/* dd C_word 17384 */
	{.type FromH0, {.p M_rpush}},		/* dd M_rpush 17392 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit 17400 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 17408 */
	{.type FromH0, {.p MV_toIn}},		/* dd MV_toIn 17416 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17424 */
	{.type FromH0, {.p C_save_input}},		/* dd C_save_input 17432 */
	{.type FromH0, {.p M_rpop}},		/* dd M_rpop 17440 */
	{.type FromH0, {.p C_count}},		/* dd C_count 17448 */
	{.type FromH0, {.p C_ro}},		/* dd C_ro 17456 */
	{.type FromH0, {.p C_open_file}},		/* dd C_open_file 17464 */
	{.type FromH0, {.p C_qfcheck}},		/* dd C_qfcheck 17472 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 17480 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17488 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17496 */
	{.type Header, {.hdr { 5, "crash", /* C_crash = 17512 */ colon }}}, /* CENTRY "crash" crash 5 h 17520 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17528 */
	{.type FromH0, {.p L251}},		/* dd L251 17536 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17544 */
	{.type Absolute, {.p 30}},		/* dd 30 17552 */
	{.type FromH0, {.p C_type}},		/* dd C_type 17560 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 17568 */
	{.type FromH0, {.p C_abort}},		/* dd C_abort 17576 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 17584 */
	{.type Header, {.hdr { 4, "quit", /* C_quit = 17600 */ colon }}}, /* CENTRY "quit" quit 4 ; interpreter loop h 17608 */
	{.type FromH0, {.p M_reset}},		/* dd M_reset ; initialize return stack 17616 */
	{.type FromH0, {.p M_clear}},		/* dd M_clear	; SP = sstack_end initialize data stack 17624 */
	{.type FromH0, {.p C_query}},		/* dd C_query 17632 */
	{.type FromH0, {.p MV_toLimit}},		/* dd MV_toLimit	; show the line read, for debugging 17640 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch 17648 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib 17656 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 17664 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite 17672 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; drop the return value of write 17680 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 17688 */
	{.type FromH0, {.p C_space}},		/* dd C_space 17696 */
	{.type FromH0, {.p C_interpret}},		/* dd C_interpret 17704 */
	{.type FromH0, {.p C_cr}},		/* dd C_cr 17712 */
	{.type FromH0, {.p M_jump}},		/* dd M_jump 17720 */
	{.type FromH0, {.p L253}},		/* dd L253 17728 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon	; why is this needed? 17736 */
	{.type Header, {.hdr { 7, "(abort)", /* C_parenabort = 17752 */ colon }}}, /* CENTRY "(abort)" parenabort 7 ; TODO correct below stack notations h 17760 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State	; ( mv_State -- ) 17768 */
	{.type FromH0, {.p C_off}},		/* dd C_off		; off sets variable state = 0 17776 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 17784 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 17792 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 17800 */
	{.type FromH0, {.p MV_Blk}},		/* dd MV_Blk	; variable blk 17808 */
	{.type FromH0, {.p C_off}},		/* dd C_off	; off variable blk = 0 17816 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 17824 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 17832 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17840 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 17848 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 17856 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17864 */
	{.type FromH0, {.p MC_STDERR}},		/* dd MC_STDERR 17872 */
	{.type FromH0, {.p MV_Errfd}},		/* dd MV_Errfd 17880 */
	{.type FromH0, {.p M_store}},		/* dd M_store 17888 */
	{.type FromH0, {.p C_quit}},		/* dd C_quit	; quit resets stacks and is the interpreter loop 17896 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon	; why is this needed? quit does not return unless it breaks 17904 */
	{.type Header, {.hdr { 7, "oldboot", /* C_oldboot = 17920 */ colon }}}, /* CENTRY "oldboot" oldboot 7 ; TODO correct below stack notations and this is obsolete. leaving it here for reference until it all works well h 17928 */
	{.type FromH0, {.p M_reset}},		/* dd M_reset 17936 */
	{.type FromH0, {.p M_clear}},		/* dd M_clear	; SP = sstack_end 17944 */
	{.type FromH0, {.p M_stackptr}},		/* dd M_stackptr	; (D -- FFEND) 17952 */
	{.type FromH0, {.p M_S0}},		/* dd M_S0 17960 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; s0 = FFEND 17968 */
	{.type FromH0, {.p M_H0}},		/* dd M_H0	; heaptop = heapend 17976 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; ( heapend -- ) 17984 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 17992 */
	{.type Absolute, {.p 1}},		/* dd 1		; ( heapend 1 -- ) 18000 */
	{.type FromH0, {.p C_cells}},		/* dd C_cells	; cells ( heapend 8 -- ) 18008 */
	{.type FromH0, {.p M_minus}},		/* dd M_minus	; ( heapend-8 -- ) 18016 */
	{.type FromH0, {.p M_fetch}},		/* dd M_fetch	; ( contents_from_heapend-8 -- ) 18024 */
	{.type FromH0, {.p M_Args}},		/* dd M_Args	; variable args 18032 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; args = contents_from_heapend-8 18040 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 18048 */
	{.type FromH0, {.p C_parenabort}},		/* dd C_parenabort ; ( (abort) -- ) 18056 */
	{.type FromH0, {.p MV_Abortvec}},		/* dd MV_Abortvec	; variable abortvec 18064 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable abortvec = (abort) code address 18072 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb	; constant puts address of wordbuffer on the top of stack 18080 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf	; variable wordbuf 18088 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable wordbuf = address of wordbuffer 18096 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 18104 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 18112 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 18120 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 18128 */
	{.type Absolute, {.p 0}},		/* dd 0 18136 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 18144 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; stdin = 0 18152 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 18160 */
	{.type Absolute, {.p 1}},		/* dd 1 18168 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 18176 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; stdout = 1 18184 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 18192 */
	{.type FromH0, {.p C_off}},		/* dd C_off	; off stores 0 at state 18200 */
	{.type FromH0, {.p C_decimal}},		/* dd C_decimal	; decimal setting base = 0 18208 */
	{.type FromH0, {.p C_quit}},		/* dd C_quit	; quit 18216 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 18224 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal	; test code 18232 */
	{.type Absolute, {.p 66}},		/* dd 66 18240 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb 18248 */
	{.type FromH0, {.p M_store}},		/* dd M_store 18256 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 18264 */
	{.type Absolute, {.p 1}},		/* dd 1 18272 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb 18280 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 18288 */
	{.type FromH0, {.p M_fthwrite}},		/* dd M_fthwrite 18296 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; drop the return value of write 18304 */
	{.type FromH0, {.p M_literal}},		/* dd M_literal 18312 */
	{.type Absolute, {.p 1}},		/* dd 1 18320 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb 18328 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 18336 */
	{.type FromH0, {.p M_fthread}},		/* dd M_fthread 18344 */
	{.type FromH0, {.p M_drop}},		/* dd M_drop		; drop the return value of read 18352 */
	{.type Header, {.hdr { 4, "boot", /* C_boot = 18368 */ colon }}}, /* CENTRY "boot" boot 4 h 18376 */
	{.type FromH0, {.p M_reset}},		/* dd M_reset ; initialize return stack 18384 */
	{.type FromH0, {.p M_clear}},		/* dd M_clear	; SP = sstack_end initialize data stack 18392 */
/* 			; s0 puts FFEND on the stack *//* 			; no args */	{.type FromH0, {.p M_literal}},		/* dd M_literal 18400 */
	{.type FromH0, {.p C_parenabort}},		/* dd C_parenabort ; ( (abort) -- ) 18408 */
	{.type FromH0, {.p MV_Abortvec}},		/* dd MV_Abortvec	; variable that puts (abort) code address on the stack 18416 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable abortvec = (abort) code address 18424 */
	{.type FromH0, {.p M_Wordb}},		/* dd M_Wordb	; variable puts address of wordbuffer on the top of stack 18432 */
	{.type FromH0, {.p MV_Wordbuf}},		/* dd MV_Wordbuf ; variable wordbuf 18440 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable wordbuf = address of wordbuffer 18448 */
	{.type FromH0, {.p M_Tib}},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 18456 */
	{.type FromH0, {.p MV_Sourcebuf}},		/* dd MV_Sourcebuf	; variable sourcebuf 18464 */
	{.type FromH0, {.p M_store}},		/* dd M_store	; variable sourcebuf = address of tibuffer 18472 */
	{.type FromH0, {.p MC_STDIN}},		/* dd MC_STDIN 18480 */
	{.type FromH0, {.p MV_Infd}},		/* dd MV_Infd 18488 */
	{.type FromH0, {.p M_store}},		/* dd M_store     ; stdin = 0 18496 */
	{.type FromH0, {.p MC_STDOUT}},		/* dd MC_STDOUT 18504 */
	{.type FromH0, {.p MV_Outfd}},		/* dd MV_Outfd 18512 */
	{.type FromH0, {.p M_store}},		/* dd M_store 18520 */
	{.type FromH0, {.p MC_STDERR}},		/* dd MC_STDERR 18528 */
	{.type FromH0, {.p MV_Errfd}},		/* dd MV_Errfd 18536 */
	{.type FromH0, {.p M_store}},		/* dd M_store 18544 */
	{.type FromH0, {.p MV_State}},		/* dd MV_State 18552 */
	{.type FromH0, {.p C_off}},		/* dd C_off	; off stores 0 at state 18560 */
	{.type FromH0, {.p C_decimal}},		/* dd C_decimal	; decimal sets base = 10 18568 */
	{.type FromH0, {.p C_quit}},		/* dd C_quit	; quit 18576 */
	{.type FromH0, {.p M_exitcolon}},		/* dd M_exitcolon 18584 */
	{.type Chars, {.str "unable to restore input"}},		/* 18608 */
	{.type Chars, {.str " Q?"}},		/* 18612 */
	{.type Chars, {.str " stack underflow"}},		/* 18629 */
	{.type Chars, {.str " I?"}},		/* 18633 */
	{.type Chars, {.str " C?"}},		/* 18637 */
	{.type Chars, {.str "I/O error"}},		/* 18647 */
	{.type Chars, {.str "uninitialized execution vector"}},		/* 18678 */
	{.type Chars, {.str " ok"}},		/* 18682 */
};

