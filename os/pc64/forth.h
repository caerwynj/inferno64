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
	M_fthread = 112,
	M_fthwrite = 136,
	M_fthseek = 160,
	M_fthopen = 184,
	M_fthclose = 208,
	M_mmap = 232,
	M_terminate = 256,
	M_fthdump = 280,
	M_clear = 304,
	M_reset = 328,
	M_exitcolon = 352,
	M_literal = 384,
	M_sliteral = 416,
	M_doinit = 440,
	M_doloop = 464,
	M_doploop = 488,
	M_rfetch = 512,
	M_rpop = 536,
	M_rpush = 560,
	M_i = 584,
	M_j = 608,
	M_plus = 632,
	M_minus = 656,
	M_multiply = 680,
	M_cjump = 704,
	M_jump = 728,
	M_slashmod = 752,
	M_uslashmod = 776,
	M_binand = 800,
	M_binor = 824,
	M_binxor = 848,
	M_xswap = 872,
	M_drop = 896,
	M_dup = 920,
	M_over = 944,
	M_equal = 968,
	M_greater = 992,
	M_less = 1016,
	M_lshift = 1040,
	M_rshift = 1064,
	M_rshifta = 1088,
	M_execute = 1112,
	M_unloop = 1136,
	M_cmove = 1160,
	M_cmoveb = 1184,
	M_variable = 1216,
	M_constant = 1248,
	M_colon = 1272,
	M_dodoes = 1296,
	M_cas = 1320,
	M_deferred = 1352,
	MC_STDIN = 1376,
	MC_STDOUT = 1408,
	MC_STDERR = 1440,
	MV_Iobuf = 1472,
	MV_Sourcebuf = 1512,
	MV_Wordbuf = 1544,
	MV_toIn = 1576,
	MV_toLimit = 1608,
	MV_Findadr = 1640,
	MV_Blk = 1672,
	MV_Searchlen = 1712,
	MV_Base = 1744,
	MV_toNum = 1776,
	MV_State = 1808,
	MV_Abortvec = 1848,
	MV_Infd = 1880,
	MV_Outfd = 1912,
	MV_Errfd = 1944,
	MV_Eof = 1976,
	MV_Ninputs = 2008,
	MV_H0 = 2040,
	M_Dp = 2072,
	M_Dtop = 2096,
	M_Vp = 2120,
	M_S0 = 2144,
	M_stackptr = 2168,
	M_Wordb = 2192,
	M_Tib = 2216,
	M_Args = 2240,
	C_false = 2264,
	C_true = 2312,
	C_bl = 2360,
	C_on = 2408,
	C_off = 2472,
	C_tobody = 2536,
	C_aligned = 2592,
	C_cells = 2672,
	C_cellplus = 2728,
	C_depth = 2792,
	C_nip = 2896,
	C_rot = 2944,
	C_2drop = 3008,
	C_2dup = 3056,
	C_2nip = 3104,
	C_2swap = 3152,
	C_qdup = 3216,
	L20 = 3288,
	C_pick = 3312,
	L22 = 3416,
	L23 = 3424,
	C_tuck = 3448,
	C_divides = 3512,
	C_plusstore = 3560,
	C_invert = 3640,
	C_mod = 3696,
	C_1plus = 3744,
	C_1minus = 3800,
	C_negate = 3856,
	C_2multiplies = 3920,
	C_2divides = 3976,
	C_0eq = 4032,
	C_0lt = 4088,
	C_0gt = 4144,
	C_neq = 4200,
	C_0neq = 4248,
	C_max = 4304,
	L40 = 4368,
	L41 = 4376,
	C_min = 4400,
	L43 = 4464,
	L44 = 4472,
	C_signum = 4496,
	L46 = 4576,
	L48 = 4632,
	L49 = 4648,
	L47 = 4648,
	C_within = 4672,
	C_abs = 4776,
	L52 = 4824,
	C_key = 4848,
	L78 = 4976,
	L79 = 4992,
	C_emit = 5016,
	C_type = 5128,
	C_cr = 5200,
	C_space = 5256,
	C_emits = 5304,
	L85 = 5312,
	L86 = 5376,
	C_spaces = 5408,
	C_count = 5464,
	C_compare = 5608,
	L55 = 5680,
	L56 = 5816,
	C_erase = 5896,
	L58 = 5928,
	C_fill = 6016,
	L60 = 6056,
	C_blank = 6144,
	C_search = 6192,
	L64 = 6296,
	L65 = 6480,
	C_here = 6544,
	C_vhere = 6592,
	C_comma = 6640,
	C_c = 6720,
	C_allot = 6800,
	C_vallot = 6848,
	C_pad = 6896,
	C_align = 6960,
	C_unused = 7024,
	C_fromhash = 7088,
	C_hash = 7168,
	L92 = 7320,
	L93 = 7344,
	C_hashs = 7424,
	L95 = 7432,
	L96 = 7480,
	C_hashfrom = 7504,
	C_hold = 7616,
	C_sign = 7720,
	L100 = 7776,
	C_dot = 7800,
	C_dotr = 7904,
	C_hex = 8064,
	C_decimal = 8128,
	C_digit = 8192,
	L106 = 8304,
	L108 = 8408,
	L110 = 8512,
	L111 = 8536,
	L109 = 8536,
	L107 = 8536,
	L112 = 8608,
	L113 = 8624,
	C_number = 8648,
	L115 = 8784,
	L116 = 8816,
	L117 = 8880,
	L118 = 8984,
	L119 = 9040,
	C_abort = 9128,
	C_source = 9184,
	C_current_input = 9240,
	C_save_input = 9320,
	C_default_input = 9464,
	C_restore_input = 9584,
	L300 = 9688,
	L301 = 9704,
	L133 = 9792,
	L134 = 9880,
	C_qrestore_input = 9912,
	L136 = 10040,
	C_next_input = 10072,
	L139 = 10168,
	L140 = 10192,
	C_parse = 10216,
	L142 = 10256,
	L143 = 10384,
	C_word = 10528,
	L145 = 10544,
	L146 = 10640,
	C_accept = 10680,
	L148 = 10720,
	L150 = 10880,
	L149 = 10944,
	C_query = 10992,
	L152 = 11136,
	L153 = 11168,
	C_refill = 11192,
	L155 = 11256,
	L156 = 11272,
	C_findname = 11304,
	L158 = 11344,
	L160 = 11456,
	L162 = 11584,
	L161 = 11592,
	L159 = 11608,
	C_find = 11656,
	L165 = 11848,
	L166 = 11864,
	L164 = 11888,
	L167 = 11896,
	C_single_quote = 11920,
	L169 = 12056,
	C_qstack = 12080,
	L172 = 12184,
	C_interpret = 12264,
	L175 = 12272,
	L177 = 12384,
	L179 = 12496,
	L178 = 12496,
	L176 = 12512,
	C_create = 12544,
	C_variable = 12792,
	C_constant = 12888,
	C_immediate = 13016,
	C_tocfa = 13128,
	C_compile = 13208,
	L189 = 13336,
	L190 = 13352,
	L188 = 13368,
	L192 = 13496,
	L194 = 13528,
	L191 = 13528,
	C_close_bracket = 13552,
	L196 = 13576,
	L197 = 13664,
	L198 = 13688,
	L199 = 13720,
	CI_open_bracket = 13744,
	C_smudge = 13792,
	C_reveal = 13904,
	C_colon = 14024,
	CI_semicolon = 14152,
	CI_recurse = 14232,
	C_L206 = 14304,
	C_literal = 14368,
	C_sliteral = 14440,
	C_string = 14608,
	CI_char_brackets = 14720,
	CI_quote_brackets = 14792,
	CI_openparen = 14840,
	CI_backslash = 14904,
	L214 = 15048,
	L215 = 15080,
	C_qabort_parens = 15112,
	L217 = 15192,
	L218 = 15200,
	CI_abort_double_quote = 15224,
	C_double_quote = 15288,
	C_cdouble_quote = 15416,
	CI_sdouble_quote = 15552,
	CI_dotstr = 15592,
	CI_if = 15656,
	CI_else = 15744,
	CI_then = 15872,
	CI_begin = 15928,
	CI_again = 15968,
	CI_until = 16032,
	CI_while = 16096,
	CI_repeat = 16184,
	CI_do = 16280,
	CI_loop = 16360,
	L234 = 16448,
	CI_ploop = 16472,
	L236 = 16560,
	C_wo = 16584,
	C_ro = 16680,
	C_rw = 16728,
	C_open_file = 16784,
	C_close_file = 17064,
	C_read_file = 17120,
	C_write_file = 17200,
	C_reposition_file = 17272,
	C_qfcheck = 17336,
	L246 = 17432,
	C_bye = 17456,
	C_include = 17512,
	C_crash = 17664,
	C_quit = 17752,
	L253 = 17776,
	C_parenabort = 17832,
	C_oldboot = 18000,
	C_boot = 18448,
	L137 = 18688,
	L170 = 18712,
	L173 = 18716,
	L180 = 18733,
	L193 = 18737,
	L247 = 18741,
	L251 = 18751,
	L255 = 18782,
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
extern void *Dtop(void);
extern void *doinit(void);
extern void *multiply(void);
extern void *colon(void);
extern void *less(void);
extern void *Dp(void);
extern void *lshift(void);
extern void *fthopen(void);
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
extern void *fthclose(void);
extern void *unloop(void);
extern void *Wordb(void);
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
	{.type Header, {.hdr { 1, "@", /* M_fetch = 16 */ fetch }}}, /* MENTRY "@" fetch 1 h 24 */
	{.type Header, {.hdr { 1, "!", /* M_store = 40 */ store }}}, /* MENTRY "!" store 1 h 48 */
	{.type Header, {.hdr { 2, "c@", /* M_cfetch = 64 */ cfetch }}}, /* MENTRY "c@" cfetch 2 h 72 */
	{.type Header, {.hdr { 2, "c!", /* M_cstore = 88 */ cstore }}}, /* MENTRY "c!" cstore 2 h 96 */
	{.type Header, {.hdr { 4, "read", /* M_fthread = 112 */ fthread }}}, /* MENTRY "read" fthread 4 h 120 */
	{.type Header, {.hdr { 5, "write", /* M_fthwrite = 136 */ fthwrite }}}, /* MENTRY "write" fthwrite 5 h 144 */
	{.type Header, {.hdr { 4, "seek", /* M_fthseek = 160 */ fthseek }}}, /* MENTRY "seek" fthseek 4 h 168 */
	{.type Header, {.hdr { 4, "open", /* M_fthopen = 184 */ fthopen }}}, /* MENTRY "open" fthopen 4 h 192 */
	{.type Header, {.hdr { 5, "close", /* M_fthclose = 208 */ fthclose }}}, /* MENTRY "close" fthclose 5 h 216 */
	{.type Header, {.hdr { 4, "mmap", /* M_mmap = 232 */ mmap }}}, /* MENTRY "mmap" mmap 4 h 240 */
	{.type Header, {.hdr { 4, "halt", /* M_terminate = 256 */ terminate }}}, /* MENTRY "halt" terminate 4 h 264 */
	{.type Header, {.hdr { 4, "dump", /* M_fthdump = 280 */ fthdump }}}, /* MENTRY "dump" fthdump 4 h 288 */
	{.type Header, {.hdr { 5, "clear", /* M_clear = 304 */ clear }}}, /* MENTRY "clear" clear 5 h 312 */
	{.type Header, {.hdr { 5, "reset", /* M_reset = 328 */ reset }}}, /* MENTRY "reset" reset 5 h 336 */
	{.type Header, {.hdr { 4, "exitcolon", /* M_exitcolon = 352 */ exitcolon }}}, /* MENTRY "exitcolon" exitcolon 4 h 360 */
	{.type Header, {.hdr { 9, "(literal)", /* M_literal = 384 */ literal }}}, /* MENTRY "(literal)" literal 9 h 392 */
	{.type Header, {.hdr { 10, "(sliteral)", /* M_sliteral = 416 */ sliteral }}}, /* MENTRY "(sliteral)" sliteral 10 h 424 */
	{.type Header, {.hdr { 4, "(do)", /* M_doinit = 440 */ doinit }}}, /* MENTRY "(do)" doinit 4 h 448 */
	{.type Header, {.hdr { 6, "(loop)", /* M_doloop = 464 */ doloop }}}, /* MENTRY "(loop)" doloop 6 h 472 */
	{.type Header, {.hdr { 7, "(+loop)", /* M_doploop = 488 */ doploop }}}, /* MENTRY "(+loop)" doploop 7 h 496 */
	{.type Header, {.hdr { 2, "r@", /* M_rfetch = 512 */ rfetch }}}, /* MENTRY "r@" rfetch 2 h 520 */
	{.type Header, {.hdr { 2, "r>", /* M_rpop = 536 */ rpop }}}, /* MENTRY "r>" rpop 2 h 544 */
	{.type Header, {.hdr { 2, ">r", /* M_rpush = 560 */ rpush }}}, /* MENTRY ">r" rpush 2 h 568 */
	{.type Header, {.hdr { 1, "i", /* M_i = 584 */ i }}}, /* MENTRY "i" i 1 h 592 */
	{.type Header, {.hdr { 1, "j", /* M_j = 608 */ j }}}, /* MENTRY "j" j 1 h 616 */
	{.type Header, {.hdr { 1, "+", /* M_plus = 632 */ plus }}}, /* MENTRY "+" plus 1 h 640 */
	{.type Header, {.hdr { 1, "-", /* M_minus = 656 */ minus }}}, /* MENTRY "-" minus 1 h 664 */
	{.type Header, {.hdr { 1, "*", /* M_multiply = 680 */ multiply }}}, /* MENTRY "*" multiply 1 h 688 */
	{.type Header, {.hdr { 4, "(if)", /* M_cjump = 704 */ cjump }}}, /* MENTRY "(if)" cjump 4 h 712 */
	{.type Header, {.hdr { 6, "(else)", /* M_jump = 728 */ jump }}}, /* MENTRY "(else)" jump 6 h 736 */
	{.type Header, {.hdr { 4, "/mod", /* M_slashmod = 752 */ slashmod }}}, /* MENTRY "/mod" slashmod 4 h 760 */
	{.type Header, {.hdr { 5, "u/mod", /* M_uslashmod = 776 */ uslashmod }}}, /* MENTRY "u/mod" uslashmod 5 h 784 */
	{.type Header, {.hdr { 3, "and", /* M_binand = 800 */ binand }}}, /* MENTRY "and" binand 3 h 808 */
	{.type Header, {.hdr { 2, "or", /* M_binor = 824 */ binor }}}, /* MENTRY "or" binor 2 h 832 */
	{.type Header, {.hdr { 3, "xor", /* M_binxor = 848 */ binxor }}}, /* MENTRY "xor" binxor 3 h 856 */
	{.type Header, {.hdr { 4, "swap", /* M_xswap = 872 */ xswap }}}, /* MENTRY "swap" xswap 4 h 880 */
	{.type Header, {.hdr { 4, "drop", /* M_drop = 896 */ drop }}}, /* MENTRY "drop" drop 4 h 904 */
	{.type Header, {.hdr { 3, "dup", /* M_dup = 920 */ dup }}}, /* MENTRY "dup" dup 3 h 928 */
	{.type Header, {.hdr { 4, "over", /* M_over = 944 */ over }}}, /* MENTRY "over" over 4 h 952 */
	{.type Header, {.hdr { 1, "=", /* M_equal = 968 */ equal }}}, /* MENTRY "=" equal 1 h 976 */
	{.type Header, {.hdr { 1, ">", /* M_greater = 992 */ greater }}}, /* MENTRY ">" greater 1 h 1000 */
	{.type Header, {.hdr { 1, "<", /* M_less = 1016 */ less }}}, /* MENTRY "<" less 1 h 1024 */
	{.type Header, {.hdr { 6, "lshift", /* M_lshift = 1040 */ lshift }}}, /* MENTRY "lshift" lshift 6 h 1048 */
	{.type Header, {.hdr { 6, "rshift", /* M_rshift = 1064 */ rshift }}}, /* MENTRY "rshift" rshift 6 h 1072 */
	{.type Header, {.hdr { 7, "rshifta", /* M_rshifta = 1088 */ rshifta }}}, /* MENTRY "rshifta" rshifta 7 h 1096 */
	{.type Header, {.hdr { 7, "execute", /* M_execute = 1112 */ execute }}}, /* MENTRY "execute" execute 7 h 1120 */
	{.type Header, {.hdr { 6, "unloop", /* M_unloop = 1136 */ unloop }}}, /* MENTRY "unloop" unloop 6 h 1144 */
	{.type Header, {.hdr { 5, "cmove", /* M_cmove = 1160 */ cmove }}}, /* MENTRY "cmove" cmove 5 h 1168 */
	{.type Header, {.hdr { 6, "cmove>", /* M_cmoveb = 1184 */ cmoveb }}}, /* MENTRY "cmove>" cmoveb 6 h 1192 */
	{.type Header, {.hdr { 10, "(variable)", /* M_variable = 1216 */ variable }}}, /* MENTRY "(variable)" variable 10 h 1224 */
	{.type Header, {.hdr { 10, "(constant)", /* M_constant = 1248 */ constant }}}, /* MENTRY "(constant)" constant 10 h 1256 */
	{.type Header, {.hdr { 3, "(:)", /* M_colon = 1272 */ colon }}}, /* MENTRY "(:)" colon 3 h 1280 */
	{.type Header, {.hdr { 6, "(does)", /* M_dodoes = 1296 */ dodoes }}}, /* MENTRY "(does)" dodoes 6 h 1304 */
	{.type Header, {.hdr { 3, "cas", /* M_cas = 1320 */ cas }}}, /* MENTRY "cas" cas 3 h 1328 */
	{.type Header, {.hdr { 10, "(deferred)", /* M_deferred = 1352 */ deferred }}}, /* MENTRY "(deferred)" deferred 10 h 1360 */
	{.type Header, {.hdr { 5, "STDIN", /* MC_STDIN = 1376 */ constant }}}, /* MCENTRY "STDIN" STDIN 0 5		; 3 constants from here CAPITALS h 1384 */
	{.type Absolute, {.p 0}},		/* 1392 */
	{.type Header, {.hdr { 6, "STDOUT", /* MC_STDOUT = 1408 */ constant }}}, /* MCENTRY "STDOUT" STDOUT 1 6 h 1416 */
	{.type Absolute, {.p 1}},		/* 1424 */
	{.type Header, {.hdr { 6, "STDERR", /* MC_STDERR = 1440 */ constant }}}, /* MCENTRY "STDERR" STDERR 2 6 h 1448 */
	{.type Absolute, {.p 2}},		/* 1456 */
	{.type Header, {.hdr { 5, "Iobuf", /* MV_Iobuf = 1472 */ variable }}}, /* MVENTRY "Iobuf" Iobuf 0 5			; the values are not being used from the definition. All are initialized to 0. h 1480 */
	{.type FromV0, {.p 0 }},	/* 1488 0 */
	{.type Header, {.hdr { 9, "Sourcebuf", /* MV_Sourcebuf = 1512 */ variable }}}, /* MVENTRY "Sourcebuf" Sourcebuf 0 9	; is there a need for this? h 1520 */
	{.type FromV0, {.p 8 }},	/* 1528 8 */
	{.type Header, {.hdr { 7, "Wordbuf", /* MV_Wordbuf = 1544 */ variable }}}, /* MVENTRY "Wordbuf" Wordbuf 0 7		; is there a need for this? h 1552 */
	{.type FromV0, {.p 16 }},	/* 1560 16 */
	{.type Header, {.hdr { 3, ">In", /* MV_toIn = 1576 */ variable }}}, /* MVENTRY ">In" toIn 0 3 h 1584 */
	{.type FromV0, {.p 24 }},	/* 1592 24 */
	{.type Header, {.hdr { 6, ">Limit", /* MV_toLimit = 1608 */ variable }}}, /* MVENTRY ">Limit" toLimit 0 6 h 1616 */
	{.type FromV0, {.p 32 }},	/* 1624 32 */
	{.type Header, {.hdr { 7, "Findadr", /* MV_Findadr = 1640 */ variable }}}, /* MVENTRY "Findadr" Findadr 0 7 h 1648 */
	{.type FromV0, {.p 40 }},	/* 1656 40 */
	{.type Header, {.hdr { 3, "Blk", /* MV_Blk = 1672 */ variable }}}, /* MVENTRY "Blk" Blk 0 3 h 1680 */
	{.type FromV0, {.p 48 }},	/* 1688 48 */
	{.type Header, {.hdr { 9, "Searchlen", /* MV_Searchlen = 1712 */ variable }}}, /* MVENTRY "Searchlen" Searchlen 0 9 h 1720 */
	{.type FromV0, {.p 56 }},	/* 1728 56 */
	{.type Header, {.hdr { 4, "Base", /* MV_Base = 1744 */ variable }}}, /* MVENTRY "Base" Base 0 4 h 1752 */
	{.type FromV0, {.p 64 }},	/* 1760 64 */
	{.type Header, {.hdr { 4, ">Num", /* MV_toNum = 1776 */ variable }}}, /* MVENTRY ">Num" toNum 0 4 h 1784 */
	{.type FromV0, {.p 72 }},	/* 1792 72 */
	{.type Header, {.hdr { 5, "State", /* MV_State = 1808 */ variable }}}, /* MVENTRY "State" State 0 5 h 1816 */
	{.type FromV0, {.p 80 }},	/* 1824 80 */
	{.type Header, {.hdr { 8, "Abortvec", /* MV_Abortvec = 1848 */ variable }}}, /* MVENTRY "Abortvec" Abortvec 0 8	; not sure if these 3 can be constants instead? h 1856 */
	{.type FromV0, {.p 88 }},	/* 1864 88 */
	{.type Header, {.hdr { 4, "Infd", /* MV_Infd = 1880 */ variable }}}, /* MVENTRY "Infd" Infd 0 4 h 1888 */
	{.type FromV0, {.p 96 }},	/* 1896 96 */
	{.type Header, {.hdr { 5, "Outfd", /* MV_Outfd = 1912 */ variable }}}, /* MVENTRY "Outfd" Outfd 0 5 h 1920 */
	{.type FromV0, {.p 104 }},	/* 1928 104 */
	{.type Header, {.hdr { 5, "Errfd", /* MV_Errfd = 1944 */ variable }}}, /* MVENTRY "Errfd" Errfd 0 5 h 1952 */
	{.type FromV0, {.p 112 }},	/* 1960 112 */
	{.type Header, {.hdr { 3, "Eof", /* MV_Eof = 1976 */ variable }}}, /* MVENTRY "Eof" Eof 0 3 h 1984 */
	{.type FromV0, {.p 120 }},	/* 1992 120 */
	{.type Header, {.hdr { 7, "Ninputs", /* MV_Ninputs = 2008 */ variable }}}, /* MVENTRY "Ninputs" Ninputs 0 7 h 2016 */
	{.type FromV0, {.p 128 }},	/* 2024 128 */
	{.type Header, {.hdr { 2, "H0", /* MV_H0 = 2040 */ variable }}}, /* MVENTRY "H0" H0 0 2		; here at startup h 2048 */
	{.type FromV0, {.p 136 }},	/* 2056 136 */
/* ; cannot use H as it is nil in inferno, address where here (next available dictionary cell location) is stored *//* ; here = Dp @ */	{.type Header, {.hdr { 2, "Dp", /* M_Dp = 2072 */ Dp }}}, /* MENTRY "Dp" Dp 2		; here h 2080 */
	{.type Header, {.hdr { 4, "Dtop", /* M_Dtop = 2096 */ Dtop }}}, /* MENTRY "Dtop" Dtop 4	; last defined header h 2104 */
	{.type Header, {.hdr { 2, "Vp", /* M_Vp = 2120 */ Vp }}}, /* MENTRY "Vp" Vp 2		; here of the variables space h 2128 */
	{.type Header, {.hdr { 2, "S0", /* M_S0 = 2144 */ S0 }}}, /* MENTRY "S0" S0 2 h 2152 */
	{.type Header, {.hdr { 2, "s@", /* M_stackptr = 2168 */ stackptr }}}, /* MENTRY "s@" stackptr 2	; puts PSP on stack. Not a variable hence lower case. h 2176 */
	{.type Header, {.hdr { 5, "Wordb", /* M_Wordb = 2192 */ Wordb }}}, /* MENTRY "Wordb" Wordb 5 h 2200 */
	{.type Header, {.hdr { 3, "Tib", /* M_Tib = 2216 */ Tib }}}, /* MENTRY "Tib" Tib 3 h 2224 */
	{.type Header, {.hdr { 4, "Args", /* M_Args = 2240 */ Args }}}, /* MENTRY "Args" Args 4 h 2248 */
	{.type Header, {.hdr { 5, "false", /* C_false = 2264 */ colon }}}, /* CENTRY "false" false 5 h 2272 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2280 */
	{.type Absolute, {.p 0}},		/* dd 0 2288 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2296 */
	{.type Header, {.hdr { 4, "true", /* C_true = 2312 */ colon }}}, /* CENTRY "true" true 4 h 2320 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2328 */
	{.type Absolute, {.p -1}},		/* dd -1 2336 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2344 */
	{.type Header, {.hdr { 2, "bl", /* C_bl = 2360 */ colon }}}, /* CENTRY "bl" bl 2 h 2368 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2376 */
	{.type Absolute, {.p 32}},		/* dd 32 2384 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2392 */
	{.type Header, {.hdr { 2, "on", /* C_on = 2408 */ colon }}}, /* CENTRY "on" on 2 ; ( a -- ) (G stores -1 at a ) h 2416 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2424 */
	{.type Absolute, {.p -1}},		/* dd -1 2432 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2440 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2448 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2456 */
	{.type Header, {.hdr { 3, "off", /* C_off = 2472 */ colon }}}, /* CENTRY "off" off 3 ; ( a -- ) (G stores 0 at a ) h 2480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2488 */
	{.type Absolute, {.p 0}},		/* dd 0 2496 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2504 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2512 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2520 */
	{.type Header, {.hdr { 5, ">body", /* C_tobody = 2536 */ colon }}}, /* CENTRY ">body" tobody 5 h 2544 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2552 */
	{.type Absolute, {.p 8}},		/* dd 8 2560 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2568 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2576 */
	{.type Header, {.hdr { 7, "aligned", /* C_aligned = 2592 */ colon }}}, /* CENTRY "aligned" aligned 7 ; align a number to a multiple of 8 h 2600 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2608 */
	{.type Absolute, {.p 7}},		/* dd 7 2616 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2624 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2632 */
	{.type Absolute, {.p -8}},		/* dd -8 2640 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 2648 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2656 */
	{.type Header, {.hdr { 5, "cells", /* C_cells = 2672 */ colon }}}, /* CENTRY "cells" cells 5 h 2680 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2688 */
	{.type Absolute, {.p 3}},		/* dd 3			; (index << 2) -> (index << 3)for amd64 2696 */
	{.type FromH0, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 2704 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2712 */
	{.type Header, {.hdr { 5, "cell+", /* C_cellplus = 2728 */ colon }}}, /* CENTRY "cell+" cellplus 5 h 2736 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2744 */
	{.type Absolute, {.p 1}},		/* dd 1 2752 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 2760 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2768 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2776 */
	{.type Header, {.hdr { 5, "depth", /* C_depth = 2792 */ colon }}}, /* CENTRY "depth" depth 5 h 2800 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 2808 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 2816 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 2824 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2832 */
	{.type Absolute, {.p 3}},		/* dd 3 2840 */
	{.type FromH0, {.p M_rshift}, .src = "dd M_rshift"},		/* dd M_rshift 2848 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2856 */
	{.type Absolute, {.p 1}},		/* dd 1 2864 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 2872 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2880 */
	{.type Header, {.hdr { 3, "nip", /* C_nip = 2896 */ colon }}}, /* CENTRY "nip" nip 3 h 2904 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2912 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 2920 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2928 */
	{.type Header, {.hdr { 3, "rot", /* C_rot = 2944 */ colon }}}, /* CENTRY "rot" rot 3 h 2952 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 2960 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2968 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 2976 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2984 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2992 */
	{.type Header, {.hdr { 5, "2drop", /* C_2drop = 3008 */ colon }}}, /* CENTRY "2drop" 2drop 5 h 3016 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3024 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3032 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3040 */
	{.type Header, {.hdr { 4, "2dup", /* C_2dup = 3056 */ colon }}}, /* CENTRY "2dup" 2dup 4 h 3064 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3072 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3080 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3088 */
	{.type Header, {.hdr { 4, "2nip", /* C_2nip = 3104 */ colon }}}, /* CENTRY "2nip" 2nip 4 h 3112 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3120 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3136 */
	{.type Header, {.hdr { 5, "2swap", /* C_2swap = 3152 */ colon }}}, /* CENTRY "2swap" 2swap 5 h 3160 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3168 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3176 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3184 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3192 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3200 */
	{.type Header, {.hdr { 4, "?dup", /* C_qdup = 3216 */ colon }}}, /* CENTRY "?dup" qdup 4 ; if (n != 0) ( n -- n n) else ( n -- n ) h 3224 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n -- n n )"},		/* dd M_dup	; ( n -- n n ) 3232 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n n -- n n n )"},		/* dd M_dup	; ( n n -- n n n ) 3240 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3248 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( n n n -- n n n 0 ) 3256 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n n n 0 -- n n f )"},		/* dd M_equal	; ( n n n 0 -- n n f ) 3264 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; ( n n f -- n n )"},		/* dd M_cjump	; ( n n f -- n n ) 3272 */
	{.type FromH0, {.p L20}, .src = "dd L20		; when n != 0, go to L20"},		/* dd L20		; when n != 0, go to L20 3280 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; when n == 0 ( n n -- n)"},		/* dd M_drop	; when n == 0 ( n n -- n) 3288 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3296 */
	{.type Header, {.hdr { 4, "pick", /* C_pick = 3312 */ colon }}}, /* CENTRY "pick" pick 4 h 3320 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 3328 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 3336 */
	{.type FromH0, {.p L22}, .src = "dd L22"},		/* dd L22 3344 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3352 */
	{.type Absolute, {.p 1}},		/* dd 1 3360 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3368 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 3376 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 3384 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3392 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3400 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 3408 */
	{.type FromH0, {.p L23}, .src = "dd L23"},		/* dd L23 3416 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3424 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3432 */
	{.type Header, {.hdr { 4, "tuck", /* C_tuck = 3448 */ colon }}}, /* CENTRY "tuck" tuck 4 h 3456 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3464 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3472 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3480 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3488 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3496 */
	{.type Header, {.hdr { 1, "/", /* C_divides = 3512 */ colon }}}, /* CENTRY "/" divides 1 h 3520 */
	{.type FromH0, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 3528 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3536 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3544 */
	{.type Header, {.hdr { 2, "+!", /* C_plusstore = 3560 */ colon }}}, /* CENTRY "+!" plusstore 2 h 3568 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3576 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3584 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3592 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3600 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3608 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 3616 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3624 */
	{.type Header, {.hdr { 6, "invert", /* C_invert = 3640 */ colon }}}, /* CENTRY "invert" invert 6 h 3648 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3656 */
	{.type Absolute, {.p -1}},		/* dd -1 3664 */
	{.type FromH0, {.p M_binxor}, .src = "dd M_binxor"},		/* dd M_binxor 3672 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3680 */
	{.type Header, {.hdr { 3, "mod", /* C_mod = 3696 */ colon }}}, /* CENTRY "mod" mod 3 h 3704 */
	{.type FromH0, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 3712 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3720 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3728 */
	{.type Header, {.hdr { 2, "1+", /* C_1plus = 3744 */ colon }}}, /* CENTRY "1+" 1plus 2 h 3752 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3760 */
	{.type Absolute, {.p 1}},		/* dd 1 3768 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3776 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3784 */
	{.type Header, {.hdr { 2, "1-", /* C_1minus = 3800 */ colon }}}, /* CENTRY "1-" 1minus 2 h 3808 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3816 */
	{.type Absolute, {.p 1}},		/* dd 1 3824 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3832 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3840 */
	{.type Header, {.hdr { 6, "negate", /* C_negate = 3856 */ colon }}}, /* CENTRY "negate" negate 6 h 3864 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3872 */
	{.type Absolute, {.p 0}},		/* dd 0 3880 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3888 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3896 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3904 */
	{.type Header, {.hdr { 2, "2*", /* C_2multiplies = 3920 */ colon }}}, /* CENTRY "2*" 2multiplies 2 h 3928 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3936 */
	{.type Absolute, {.p 1}},		/* dd 1 3944 */
	{.type FromH0, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 3952 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3960 */
	{.type Header, {.hdr { 2, "2/", /* C_2divides = 3976 */ colon }}}, /* CENTRY "2/" 2divides 2 h 3984 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3992 */
	{.type Absolute, {.p 1}},		/* dd 1 4000 */
	{.type FromH0, {.p M_rshifta}, .src = "dd M_rshifta"},		/* dd M_rshifta 4008 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4016 */
	{.type Header, {.hdr { 2, "0=", /* C_0eq = 4032 */ colon }}}, /* CENTRY "0=" 0eq 2 h 4040 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4048 */
	{.type Absolute, {.p 0}},		/* dd 0 4056 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4064 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4072 */
	{.type Header, {.hdr { 2, "0<", /* C_0lt = 4088 */ colon }}}, /* CENTRY "0<" 0lt 2 h 4096 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4104 */
	{.type Absolute, {.p 0}},		/* dd 0 4112 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4120 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4128 */
	{.type Header, {.hdr { 2, "0>", /* C_0gt = 4144 */ colon }}}, /* CENTRY "0>" 0gt 2 h 4152 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4160 */
	{.type Absolute, {.p 0}},		/* dd 0 4168 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4176 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4184 */
	{.type Header, {.hdr { 2, "<>", /* C_neq = 4200 */ colon }}}, /* CENTRY "<>" neq 2 h 4208 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4216 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 4224 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4232 */
	{.type Header, {.hdr { 3, "0<>", /* C_0neq = 4248 */ colon }}}, /* CENTRY "0<>" 0neq 3 h 4256 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4264 */
	{.type Absolute, {.p 0}},		/* dd 0 4272 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 4280 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4288 */
	{.type Header, {.hdr { 3, "max", /* C_max = 4304 */ colon }}}, /* CENTRY "max" max 3 h 4312 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4320 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4328 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4336 */
	{.type FromH0, {.p L40}, .src = "dd L40"},		/* dd L40 4344 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4352 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4360 */
	{.type FromH0, {.p L41}, .src = "dd L41"},		/* dd L41 4368 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4376 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4384 */
	{.type Header, {.hdr { 3, "min", /* C_min = 4400 */ colon }}}, /* CENTRY "min" min 3 h 4408 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4416 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4424 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4432 */
	{.type FromH0, {.p L43}, .src = "dd L43"},		/* dd L43 4440 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4448 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4456 */
	{.type FromH0, {.p L44}, .src = "dd L44"},		/* dd L44 4464 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4472 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4480 */
	{.type Header, {.hdr { 6, "signum", /* C_signum = 4496 */ colon }}}, /* CENTRY "signum" signum 6 h 4504 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4512 */
	{.type FromH0, {.p C_0gt}, .src = "dd C_0gt"},		/* dd C_0gt 4520 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4528 */
	{.type FromH0, {.p L46}, .src = "dd L46"},		/* dd L46 4536 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4544 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4552 */
	{.type Absolute, {.p 1}},		/* dd 1 4560 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4568 */
	{.type FromH0, {.p L47}, .src = "dd L47"},		/* dd L47 4576 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 4584 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4592 */
	{.type FromH0, {.p L48}, .src = "dd L48"},		/* dd L48 4600 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4608 */
	{.type Absolute, {.p -1}},		/* dd -1 4616 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4624 */
	{.type FromH0, {.p L49}, .src = "dd L49"},		/* dd L49 4632 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4640 */
	{.type Absolute, {.p 0}},		/* dd 0 4648 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4656 */
	{.type Header, {.hdr { 6, "within", /* C_within = 4672 */ colon }}}, /* CENTRY "within" within 6 h 4680 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 4688 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 4696 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4704 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4712 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 4720 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 4728 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4736 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4744 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 4752 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4760 */
	{.type Header, {.hdr { 3, "abs", /* C_abs = 4776 */ colon }}}, /* CENTRY "abs" abs 3 h 4784 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4792 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 4800 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4808 */
	{.type FromH0, {.p L52}, .src = "dd L52"},		/* dd L52 4816 */
	{.type FromH0, {.p C_negate}, .src = "dd C_negate"},		/* dd C_negate 4824 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4832 */
	{.type Header, {.hdr { 3, "key", /* C_key = 4848 */ colon }}}, /* CENTRY "key" key 3 ; ( -- c ) (G read a single character from the input onto the stack ) h 4856 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4864 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( 1 -- ) 4872 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf to store the character read"},		/* dd MV_Iobuf		; variable iobuf to store the character read 4880 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 4888 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( 1 Iobuf -- 1 Iobuf infd )"},		/* dd M_fetch		; ( 1 Iobuf -- 1 Iobuf infd ) 4896 */
	{.type FromH0, {.p M_fthread}, .src = "dd M_fthread	; ( 1 Iobuf infd -- n )"},		/* dd M_fthread	; ( 1 Iobuf infd -- n ) 4904 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 4912 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump		; if 0 characters read"},		/* dd M_cjump		; if 0 characters read 4920 */
	{.type FromH0, {.p L78}, .src = "dd L78			; if qread n != 0 jump to L78. If n == 0 jump over"},		/* dd L78			; if qread n != 0 jump to L78. If n == 0 jump over 4928 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 4936 */
	{.type FromH0, {.p C_on}, .src = "dd C_on		; EOF"},		/* dd C_on		; EOF 4944 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4952 */
	{.type Absolute, {.p -1}},		/* dd -1			; return -1 when EOF 4960 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4968 */
	{.type FromH0, {.p L79}, .src = "dd L79"},		/* dd L79 4976 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; get the character from Iobuf to stack"},		/* dd MV_Iobuf		; get the character from Iobuf to stack 4984 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( -- c ) return the character read if not EOF"},		/* dd M_cfetch	; ( -- c ) return the character read if not EOF 4992 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5000 */
	{.type Header, {.hdr { 4, "emit", /* C_emit = 5016 */ colon }}}, /* CENTRY "emit" emit 4 ; ( character -- ) h 5024 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5032 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; variable iobuf has character"},		/* dd M_cstore	; variable iobuf has character 5040 */
	{.type FromH0, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5048 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5056 */
	{.type Absolute, {.p 1}},		/* dd 1 5064 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap		; ( iobuf 1 --  1 iobuf )"},		/* dd M_xswap		; ( iobuf 1 --  1 iobuf ) 5072 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 5080 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; outfd"},		/* dd M_fetch		; outfd 5088 */
	{.type FromH0, {.p M_fthwrite}, .src = "dd M_fthwrite	; ( 1 iobuf outfd --  )"},		/* dd M_fthwrite	; ( 1 iobuf outfd --  ) 5096 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5104 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5112 */
	{.type Header, {.hdr { 4, "type", /* C_type = 5128 */ colon }}}, /* CENTRY "type" type 4 ; ( addr n -- ) h 5136 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap			; ( addr n --  n addr )"},		/* dd M_xswap			; ( addr n --  n addr ) 5144 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5152 */
	{.type Absolute, {.p 1}},		/* dd 1				; stdout 5160 */
	{.type FromH0, {.p M_fthwrite}, .src = "dd M_fthwrite		; ( n addr 1 --  )"},		/* dd M_fthwrite		; ( n addr 1 --  ) 5168 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5176 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5184 */
	{.type Header, {.hdr { 2, "cr", /* C_cr = 5200 */ colon }}}, /* CENTRY "cr" cr 2 h 5208 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5216 */
	{.type Absolute, {.p 10}},		/* dd 10			; ascii value of carriage return 5224 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit			; emit"},		/* dd C_emit			; emit 5232 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5240 */
	{.type Header, {.hdr { 5, "space", /* C_space = 5256 */ colon }}}, /* CENTRY "space" space 5 h 5264 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5272 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5280 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5288 */
	{.type Header, {.hdr { 5, "emits", /* C_emits = 5304 */ colon }}}, /* CENTRY "emits" emits 5 h 5312 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5320 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5328 */
	{.type FromH0, {.p L86}, .src = "dd L86"},		/* dd L86 5336 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5344 */
	{.type FromH0, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5352 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5360 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5368 */
	{.type FromH0, {.p L85}, .src = "dd L85"},		/* dd L85 5376 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 5384 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5392 */
	{.type Header, {.hdr { 6, "spaces", /* C_spaces = 5408 */ colon }}}, /* CENTRY "spaces" spaces 6 h 5416 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5424 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 5432 */
	{.type FromH0, {.p C_emits}, .src = "dd C_emits"},		/* dd C_emits 5440 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5448 */
	{.type Header, {.hdr { 5, "count", /* C_count = 5464 */ colon }}}, /* CENTRY "count" count 5 ; ( a -- a+1 n ) a = counted string h 5472 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 5480 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 5488 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5496 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5504 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5512 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup ; debug show the word name to search"},		/* dd C_2dup ; debug show the word name to search 5520 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5528 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 5536 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush ; debug show the dictionary entry"},		/* dd M_rpush ; debug show the dictionary entry 5544 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 5552 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 5560 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5568 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5576 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5584 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 5592 */
	{.type Header, {.hdr { 7, "compare", /* C_compare = 5608 */ colon }}}, /* CENTRY "compare" compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search h 5616 */
	{.type FromH0, {.p C_rot}, .src = "dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 )"},		/* dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 5624 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 )"},		/* dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 ) 5632 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- ) 5640 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- ) 5648 */
	{.type FromH0, {.p C_min}, .src = "dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- )"},		/* dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- ) 5656 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5664 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- ) 5672 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- )"},		/* dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- ) 5680 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5688 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 5696 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 5704 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5712 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5720 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 5728 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 5736 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5744 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 5752 */
	{.type FromH0, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 5760 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5768 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5776 */
	{.type FromH0, {.p L56}, .src = "dd L56		; matches"},		/* dd L56		; matches 5784 */
	{.type FromH0, {.p C_2nip}, .src = "dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- )"},		/* dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- ) 5792 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2)"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2) 5800 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 -- )"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 -- ) 5808 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5816 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 5824 */
	{.type FromH0, {.p L55}, .src = "dd L55"},		/* dd L55 5832 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- )"},		/* dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- ) 5840 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5848 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( n2 n1 -- ) (R -- )"},		/* dd M_rpop	; ( n2 n1 -- ) (R -- ) 5856 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( -- n1-n2 )"},		/* dd M_minus	; ( -- n1-n2 ) 5864 */
	{.type FromH0, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 5872 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5880 */
	{.type Header, {.hdr { 5, "erase", /* C_erase = 5896 */ colon }}}, /* CENTRY "erase" erase 5 h 5904 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5912 */
	{.type Absolute, {.p 0}},		/* dd 0 5920 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 5928 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5936 */
	{.type Absolute, {.p 0}},		/* dd 0 5944 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5952 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 5960 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 5968 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 5976 */
	{.type FromH0, {.p L58}, .src = "dd L58"},		/* dd L58 5984 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 5992 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6000 */
	{.type Header, {.hdr { 4, "fill", /* C_fill = 6016 */ colon }}}, /* CENTRY "fill" fill 4 h 6024 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6032 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6040 */
	{.type Absolute, {.p 0}},		/* dd 0 6048 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6056 */
	{.type FromH0, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 6064 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6072 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6080 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6088 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6096 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6104 */
	{.type FromH0, {.p L60}, .src = "dd L60"},		/* dd L60 6112 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 6120 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6128 */
	{.type Header, {.hdr { 5, "blank", /* C_blank = 6144 */ colon }}}, /* CENTRY "blank" blank 5 h 6152 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 6160 */
	{.type FromH0, {.p C_fill}, .src = "dd C_fill"},		/* dd C_fill 6168 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6176 */
	{.type Header, {.hdr { 6, "search", /* C_search = 6192 */ colon }}}, /* CENTRY "search" search 6 h 6200 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6208 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6216 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6224 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 6232 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 6240 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6248 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6256 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6264 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 6272 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6280 */
	{.type Absolute, {.p 0}},		/* dd 0 6288 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6296 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6304 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6312 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6320 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6328 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6336 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6344 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6352 */
	{.type FromH0, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6360 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6368 */
	{.type FromH0, {.p C_compare}, .src = "dd C_compare"},		/* dd C_compare 6376 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 6384 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 6392 */
	{.type FromH0, {.p L65}, .src = "dd L65"},		/* dd L65 6400 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6408 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6416 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6424 */
	{.type FromH0, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6432 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 6440 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6448 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6456 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6464 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 6472 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6480 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6488 */
	{.type FromH0, {.p L64}, .src = "dd L64"},		/* dd L64 6496 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6504 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6512 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 6520 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6528 */
	{.type Header, {.hdr { 4, "here", /* C_here = 6544 */ colon }}}, /* CENTRY "here" here 4 h 6552 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6560 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6568 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6576 */
	{.type Header, {.hdr { 4, "vhere", /* C_vhere = 6592 */ colon }}}, /* CENTRY "vhere" vhere 4 h 6600 */
	{.type FromH0, {.p M_Vp}, .src = "dd M_Vp"},		/* dd M_Vp 6608 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6616 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6624 */
	{.type Header, {.hdr { 1, ",", /* C_comma = 6640 */ colon }}}, /* CENTRY "," comma 1 h 6648 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6656 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6664 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6672 */
	{.type Absolute, {.p 8}},		/* dd 8 6680 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6688 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6696 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6704 */
	{.type Header, {.hdr { 2, "c,", /* C_c = 6720 */ colon }}}, /* CENTRY "c," c 2 h 6728 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6736 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6744 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6752 */
	{.type Absolute, {.p 1}},		/* dd 1 6760 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6768 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6776 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6784 */
	{.type Header, {.hdr { 5, "allot", /* C_allot = 6800 */ colon }}}, /* CENTRY "allot" allot 5 ; ( n -- ) here = here+n h 6808 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 6816 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6824 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6832 */
	{.type Header, {.hdr { 5, "vallot", /* C_vallot = 6848 */ colon }}}, /* CENTRY "vallot" vallot 5 ; allot on the variable space ( n -- ) vhere = vhere+n h 6856 */
	{.type FromH0, {.p M_Vp}, .src = "dd M_Vp"},		/* dd M_Vp 6864 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6872 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6880 */
	{.type Header, {.hdr { 3, "pad", /* C_pad = 6896 */ colon }}}, /* CENTRY "pad" pad 3 h 6904 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6912 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6920 */
	{.type Absolute, {.p 256}},		/* dd 256 6928 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6936 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6944 */
	{.type Header, {.hdr { 5, "align", /* C_align = 6960 */ colon }}}, /* CENTRY "align" align 5 h 6968 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6976 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned	; here is aligned to a multiple of 8"},		/* dd C_aligned	; here is aligned to a multiple of 8 6984 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp			; store the aligned here at Dp"},		/* dd M_Dp			; store the aligned here at Dp 6992 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7000 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7008 */
	{.type Header, {.hdr { 6, "unused", /* C_unused = 7024 */ colon }}}, /* CENTRY "unused" unused 6 h 7032 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 7040 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7048 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 7056 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7064 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7072 */
	{.type Header, {.hdr { 2, "<#", /* C_fromhash = 7088 */ colon }}}, /* CENTRY "<#" fromhash 2 h 7096 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7104 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7112 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7120 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7128 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7136 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7144 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7152 */
	{.type Header, {.hdr { 1, "#", /* C_hash = 7168 */ colon }}}, /* CENTRY "#" hash 1 h 7176 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 7184 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7192 */
	{.type FromH0, {.p M_uslashmod}, .src = "dd M_uslashmod"},		/* dd M_uslashmod 7200 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7208 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7216 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7224 */
	{.type Absolute, {.p 9}},		/* dd 9 7232 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 7240 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7248 */
	{.type FromH0, {.p L92}, .src = "dd L92"},		/* dd L92 7256 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7264 */
	{.type Absolute, {.p 97}},		/* dd 97 7272 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7280 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7288 */
	{.type Absolute, {.p 10}},		/* dd 10 7296 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7304 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7312 */
	{.type FromH0, {.p L93}, .src = "dd L93"},		/* dd L93 7320 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7328 */
	{.type Absolute, {.p 48}},		/* dd 48 7336 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7344 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7352 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7360 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7368 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7376 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7384 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7392 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7400 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7408 */
	{.type Header, {.hdr { 2, "#s", /* C_hashs = 7424 */ colon }}}, /* CENTRY "#s" hashs 2 h 7432 */
	{.type FromH0, {.p C_hash}, .src = "dd C_hash"},		/* dd C_hash 7440 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7448 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7456 */
	{.type FromH0, {.p L96}, .src = "dd L96"},		/* dd L96 7464 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7472 */
	{.type FromH0, {.p L95}, .src = "dd L95"},		/* dd L95 7480 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7488 */
	{.type Header, {.hdr { 2, "#>", /* C_hashfrom = 7504 */ colon }}}, /* CENTRY "#>" hashfrom 2 h 7512 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 7520 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7528 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7536 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7544 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7552 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7560 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7568 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7576 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7584 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7592 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7600 */
	{.type Header, {.hdr { 4, "hold", /* C_hold = 7616 */ colon }}}, /* CENTRY "hold" hold 4 h 7624 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7632 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7640 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7648 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7656 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 7664 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7672 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 7680 */
	{.type FromH0, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7688 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7696 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7704 */
	{.type Header, {.hdr { 4, "sign", /* C_sign = 7720 */ colon }}}, /* CENTRY "sign" sign 4 h 7728 */
	{.type FromH0, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 7736 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7744 */
	{.type FromH0, {.p L100}, .src = "dd L100"},		/* dd L100 7752 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7760 */
	{.type Absolute, {.p 45}},		/* dd 45 7768 */
	{.type FromH0, {.p C_hold}, .src = "dd C_hold"},		/* dd C_hold 7776 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7784 */
	{.type Header, {.hdr { 1, ".", /* C_dot = 7800 */ colon }}}, /* CENTRY "." dot 1 ; print the top of stack ( n -- ) h 7808 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; ( n -- n n )"},		/* dd M_dup		; ( n -- n n ) 7816 */
	{.type FromH0, {.p C_abs}, .src = "dd C_abs		; ( n n -- n u )"},		/* dd C_abs		; ( n n -- n u ) 7824 */
	{.type FromH0, {.p C_fromhash}, .src = "dd C_fromhash	; pad = h+256; >num = pad+1024"},		/* dd C_fromhash	; pad = h+256; >num = pad+1024 7832 */
	{.type FromH0, {.p C_hashs}, .src = "dd C_hashs		; ( n u1 -- n n2 )"},		/* dd C_hashs		; ( n u1 -- n n2 ) 7840 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap		; ( n n2 -- n2 n )"},		/* dd M_xswap		; ( n n2 -- n2 n ) 7848 */
	{.type FromH0, {.p C_sign}, .src = "dd C_sign		; ( n2 n -- n2 )"},		/* dd C_sign		; ( n2 n -- n2 ) 7856 */
	{.type FromH0, {.p C_hashfrom}, .src = "dd C_hashfrom	; ( u1 -- a n )"},		/* dd C_hashfrom	; ( u1 -- a n ) 7864 */
	{.type FromH0, {.p C_type}, .src = "dd C_type		; ( a n -- )"},		/* dd C_type		; ( a n -- ) 7872 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 7880 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7888 */
	{.type Header, {.hdr { 2, ".r", /* C_dotr = 7904 */ colon }}}, /* CENTRY ".r" dotr 2 h 7912 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 7920 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7928 */
	{.type FromH0, {.p C_abs}, .src = "dd C_abs"},		/* dd C_abs 7936 */
	{.type FromH0, {.p C_fromhash}, .src = "dd C_fromhash"},		/* dd C_fromhash 7944 */
	{.type FromH0, {.p C_hashs}, .src = "dd C_hashs"},		/* dd C_hashs 7952 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7960 */
	{.type FromH0, {.p C_sign}, .src = "dd C_sign"},		/* dd C_sign 7968 */
	{.type FromH0, {.p C_hashfrom}, .src = "dd C_hashfrom"},		/* dd C_hashfrom 7976 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 7984 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 7992 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8000 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8008 */
	{.type Absolute, {.p 0}},		/* dd 0 8016 */
	{.type FromH0, {.p C_max}, .src = "dd C_max"},		/* dd C_max 8024 */
	{.type FromH0, {.p C_spaces}, .src = "dd C_spaces"},		/* dd C_spaces 8032 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 8040 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8048 */
	{.type Header, {.hdr { 3, "hex", /* C_hex = 8064 */ colon }}}, /* CENTRY "hex" hex 3 h 8072 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8080 */
	{.type Absolute, {.p 16}},		/* dd 16 8088 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8096 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8104 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8112 */
	{.type Header, {.hdr { 7, "decimal", /* C_decimal = 8128 */ colon }}}, /* CENTRY "decimal" decimal 7 h 8136 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8144 */
	{.type Absolute, {.p 10}},		/* dd 10 8152 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8160 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8168 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8176 */
	{.type Header, {.hdr { 5, "digit", /* C_digit = 8192 */ colon }}}, /* CENTRY "digit" digit 5 ; ( c -- ) h 8200 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8208 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8216 */
	{.type Absolute, {.p 65}},		/* dd 65 8224 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8232 */
	{.type Absolute, {.p 91}},		/* dd 91 8240 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8248 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8256 */
	{.type FromH0, {.p L106}, .src = "dd L106"},		/* dd L106 8264 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8272 */
	{.type Absolute, {.p 55}},		/* dd 55 8280 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8288 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8296 */
	{.type FromH0, {.p L107}, .src = "dd L107"},		/* dd L107 8304 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8312 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8320 */
	{.type Absolute, {.p 97}},		/* dd 97 8328 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8336 */
	{.type Absolute, {.p 123}},		/* dd 123 8344 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8352 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8360 */
	{.type FromH0, {.p L108}, .src = "dd L108"},		/* dd L108 8368 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8376 */
	{.type Absolute, {.p 87}},		/* dd 87 8384 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8392 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8400 */
	{.type FromH0, {.p L109}, .src = "dd L109"},		/* dd L109 8408 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8416 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8424 */
	{.type Absolute, {.p 48}},		/* dd 48 8432 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8440 */
	{.type Absolute, {.p 58}},		/* dd 58 8448 */
	{.type FromH0, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8456 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8464 */
	{.type FromH0, {.p L110}, .src = "dd L110"},		/* dd L110 8472 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8480 */
	{.type Absolute, {.p 48}},		/* dd 48 8488 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8496 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8504 */
	{.type FromH0, {.p L111}, .src = "dd L111"},		/* dd L111 8512 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8520 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8528 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8536 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8544 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8552 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 8560 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 8568 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8576 */
	{.type FromH0, {.p L112}, .src = "dd L112"},		/* dd L112 8584 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 8592 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8600 */
	{.type FromH0, {.p L113}, .src = "dd L113"},		/* dd L113 8608 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8616 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8624 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8632 */
	{.type Header, {.hdr { 6, "number", /* C_number = 8648 */ colon }}}, /* CENTRY "number" number 6 ; ( a n1 -- n2 -1 | a n1 0 ) h 8656 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 -- n1 a )"},		/* dd M_xswap	; ( a n1 -- n1 a ) 8664 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n1 a -- n1 a a )"},		/* dd M_dup	; ( n1 a -- n1 a a ) 8672 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( n1 a a -- n1 a c )"},		/* dd M_cfetch	; ( n1 a a -- n1 a c ) 8680 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8688 */
	{.type Absolute, {.p 45}},		/* dd 45		; ( n1 a c -- n1 a c - ) 8696 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n1 a c -- n1 a f )"},		/* dd M_equal	; ( n1 a c -- n1 a f ) 8704 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; ( n1 a c -- n1 a )"},		/* dd M_cjump	; ( n1 a c -- n1 a ) 8712 */
	{.type FromH0, {.p L115}, .src = "dd L115		; c != -"},		/* dd L115		; c != - 8720 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; c == - ( n1 a -- n1 a+1 )"},		/* dd C_1plus	; c == - ( n1 a -- n1 a+1 ) 8728 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 8736 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 )"},		/* dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 ) 8744 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8752 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( a+1 n1-1 -- a+1 n1-1 -1 ) 8760 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1)"},		/* dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1) 8768 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8776 */
	{.type FromH0, {.p L116}, .src = "dd L116"},		/* dd L116 8784 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( n1 a -- a n1)"},		/* dd M_xswap	; ( n1 a -- a n1) 8792 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8800 */
	{.type Absolute, {.p 1}},		/* dd 1 8808 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1)"},		/* dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1) 8816 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a n1 -- a n1 n1 ) (R nr)"},		/* dd M_dup	; ( a n1 -- a n1 n1 ) (R nr) 8824 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1)"},		/* dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1) 8832 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8840 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a n1 -- a n1 0) (R nr n1) 8848 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1)"},		/* dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1) 8856 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8864 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a 0 n1 -- a 0 n1 0) (R nr n1) 8872 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1) 8880 */
	{.type FromH0, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8888 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1) 8896 */
	{.type FromH0, {.p M_multiply}, .src = "dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1) 8904 */
	{.type FromH0, {.p M_over}, .src = "dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1)"},		/* dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1) 8912 */
	{.type FromH0, {.p M_i}, .src = "dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1) 8920 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1) 8928 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1)"},		/* dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1) 8936 */
	{.type FromH0, {.p C_digit}, .src = "dd C_digit"},		/* dd C_digit 8944 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8952 */
	{.type FromH0, {.p L118}, .src = "dd L118"},		/* dd L118 8960 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 8968 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8976 */
	{.type FromH0, {.p L119}, .src = "dd L119"},		/* dd L119 8984 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8992 */
	{.type FromH0, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 9000 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9008 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9016 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9024 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 9032 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9040 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 9048 */
	{.type FromH0, {.p L117}, .src = "dd L117"},		/* dd L117 9056 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9064 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9072 */
	{.type FromH0, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 9080 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9088 */
	{.type FromH0, {.p M_multiply}, .src = "dd M_multiply"},		/* dd M_multiply 9096 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 9104 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9112 */
	{.type Header, {.hdr { 5, "abort", /* C_abort = 9128 */ colon }}}, /* CENTRY "abort" abort 5 h 9136 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec"},		/* dd MV_Abortvec 9144 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9152 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 9160 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9168 */
	{.type Header, {.hdr { 6, "source", /* C_source = 9184 */ colon }}}, /* CENTRY "source" source 6 h 9192 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9200 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9208 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9216 */
	{.type Header, {.hdr { 13, "current-input", /* C_current_input = 9240 */ colon }}}, /* CENTRY "current-input" current_input 13 ; ( -- c ) read the next character from the location in Sourcebuf h 9248 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9256 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9264 */
	{.type FromH0, {.p C_source}, .src = "dd C_source"},		/* dd C_source 9272 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus		; Sourcebuf + >In"},		/* dd M_plus		; Sourcebuf + >In 9280 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 9288 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9296 */
	{.type Header, {.hdr { 10, "save-input", /* C_save_input = 9320 */ colon }}}, /* CENTRY "save-input" save_input 10 h 9328 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 9336 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9344 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9352 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9360 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9368 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9376 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9384 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 9392 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9400 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9408 */
	{.type Absolute, {.p 5}},		/* dd 5 9416 */
	{.type FromH0, {.p MV_Ninputs}, .src = "dd MV_Ninputs"},		/* dd MV_Ninputs 9424 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; Ninputs++"},		/* dd C_plusstore	; Ninputs++ 9432 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9440 */
	{.type Header, {.hdr { 13, "default-input", /* C_default_input = 9464 */ colon }}}, /* CENTRY "default-input" default_input 13 h 9472 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 9480 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9488 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9496 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9504 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9512 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib"},		/* dd M_Tib 9520 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9528 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9536 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 9544 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9552 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9560 */
	{.type Header, {.hdr { 13, "restore-input", /* C_restore_input = 9584 */ colon }}}, /* CENTRY "restore-input" restore_input 13 ; ( <input>|empty -- f ) h 9592 */
	{.type FromH0, {.p MV_Ninputs}, .src = "dd MV_Ninputs	; if Ninputs == 0, leave 0 on the stack. Or, Ninputs--"},		/* dd MV_Ninputs	; if Ninputs == 0, leave 0 on the stack. Or, Ninputs-- 9600 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9608 */
	{.type FromH0, {.p C_0neq}, .src = "dd C_0neq"},		/* dd C_0neq 9616 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9624 */
	{.type FromH0, {.p L300}, .src = "dd L300"},		/* dd L300 9632 */
	{.type FromH0, {.p MV_Ninputs}, .src = "dd MV_Ninputs	; there are <input>'s pending on the stack"},		/* dd MV_Ninputs	; there are <input>'s pending on the stack 9640 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9648 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 9656 */
	{.type FromH0, {.p MV_Ninputs}, .src = "dd MV_Ninputs"},		/* dd MV_Ninputs 9664 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9672 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9680 */
	{.type FromH0, {.p L301}, .src = "dd L301		; ( <input> -- <input>)"},		/* dd L301		; ( <input> -- <input>) 9688 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9696 */
	{.type Absolute, {.p 0}},		/* dd 0 9704 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 9712 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 9720 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9728 */
	{.type Absolute, {.p 5}},		/* dd 5 9736 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 9744 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9752 */
	{.type FromH0, {.p L133}, .src = "dd L133"},		/* dd L133 9760 */
	{.type FromH0, {.p C_default_input}, .src = "dd C_default_input"},		/* dd C_default_input 9768 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 9776 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9784 */
	{.type FromH0, {.p L134}, .src = "dd L134"},		/* dd L134 9792 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 9800 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9808 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9816 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9824 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 9832 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9840 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 9848 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9856 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 9864 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9872 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 9880 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9888 */
	{.type Header, {.hdr { 14, "?restore-input", /* C_qrestore_input = 9912 */ colon }}}, /* CENTRY "?restore-input" qrestore_input 14 ; ( <input> -- f ) h 9920 */
	{.type FromH0, {.p C_restore_input}, .src = "dd C_restore_input"},		/* dd C_restore_input 9928 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 9936 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9944 */
	{.type FromH0, {.p L136}, .src = "dd L136"},		/* dd L136 9952 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 9960 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9968 */
	{.type FromH0, {.p L137}, .src = "dd L137"},		/* dd L137 9976 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9984 */
	{.type Absolute, {.p 23}},		/* dd 23 9992 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 10000 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 10008 */
	{.type FromH0, {.p C_depth}, .src = "dd C_depth"},		/* dd C_depth 10016 */
	{.type FromH0, {.p C_dot}, .src = "dd C_dot"},		/* dd C_dot 10024 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 10032 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 10040 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10048 */
	{.type Header, {.hdr { 10, "next-input", /* C_next_input = 10072 */ colon }}}, /* CENTRY "next-input" next_input 10 ; when >In < >Limit ( -- true c ). ( -- 0 false ) otherwise h 10080 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10088 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10096 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 10104 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10112 */
	{.type FromH0, {.p M_less}, .src = "dd M_less"},		/* dd M_less 10120 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10128 */
	{.type FromH0, {.p L139}, .src = "dd L139	; >In >= >Limit"},		/* dd L139	; >In >= >Limit 10136 */
	{.type FromH0, {.p C_true}, .src = "dd C_true	; >In < >Limit"},		/* dd C_true	; >In < >Limit 10144 */
	{.type FromH0, {.p C_current_input}, .src = "dd C_current_input	; ( -- c )"},		/* dd C_current_input	; ( -- c ) 10152 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 10160 */
	{.type FromH0, {.p L140}, .src = "dd L140"},		/* dd L140 10168 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10176 */
	{.type Absolute, {.p 0}},		/* dd 0 10184 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 10192 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10200 */
	{.type Header, {.hdr { 5, "parse", /* C_parse = 10216 */ colon }}}, /* CENTRY "parse" parse 5 ; ( c -- a ) Place the counted string in the address in Wordbuf and return that address. c = word delimiter. h 10224 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; ( c -- ) (R -- c )"},		/* dd M_rpush		; ( c -- ) (R -- c ) 10232 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf"},		/* dd MV_Wordbuf 10240 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; ( -- Wordb )"},		/* dd M_fetch		; ( -- Wordb ) 10248 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus		; ( Wordb -- Wordb+1 )"},		/* dd C_1plus		; ( Wordb -- Wordb+1 ) 10256 */
	{.type FromH0, {.p C_next_input}, .src = "dd C_next_input ; ( Wordb+1 -- Wordb+1 f c )"},		/* dd C_next_input ; ( Wordb+1 -- Wordb+1 f c ) 10264 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c )"},		/* dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c ) 10272 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) )"},		/* dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) ) 10280 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 10288 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10296 */
	{.type FromH0, {.p L143}, .src = "dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew"},		/* dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew 10304 */
	{.type FromH0, {.p C_current_input}, .src = "dd C_current_input	; ( Wordb+1 -- Wordb+1 c )"},		/* dd C_current_input	; ( Wordb+1 -- Wordb+1 c ) 10312 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 10320 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1"},		/* dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1 10328 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus		; ( Wordb+1 -- Wordb+2 )"},		/* dd C_1plus		; ( Wordb+1 -- Wordb+2 ) 10336 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10344 */
	{.type Absolute, {.p 1}},		/* dd 1 10352 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10360 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10368 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 10376 */
	{.type FromH0, {.p L142}, .src = "dd L142		; ( Wordb+2 ) repeat"},		/* dd L142		; ( Wordb+2 ) repeat 10384 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10392 */
	{.type Absolute, {.p 1}},		/* dd 1 10400 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10408 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10416 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- )"},		/* dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- ) 10424 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; (Wordb+1 c -- Wordb+1)"},		/* dd M_drop		; (Wordb+1 c -- Wordb+1) 10432 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf"},		/* dd MV_Wordbuf 10440 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb)"},		/* dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb) 10448 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb)"},		/* dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb) 10456 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb)"},		/* dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb) 10464 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb)"},		/* dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb) 10472 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb)"},		/* dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb) 10480 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb)"},		/* dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb) 10488 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now."},		/* dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now. 10496 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( -- Wordb) (R Wordb -- )"},		/* dd M_rpop		; ( -- Wordb) (R Wordb -- ) 10504 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10512 */
	{.type Header, {.hdr { 4, "word", /* C_word = 10528 */ colon }}}, /* CENTRY "word" word 4 ; ( c -- a ) skip the c"s. Placed the counted string in a (as in Wordbuf) h 10536 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- ) (R -- c )"},		/* dd M_rpush	; ( -- ) (R -- c ) 10544 */
	{.type FromH0, {.p C_next_input}, .src = "dd C_next_input ; ( -- f c2 ) (R c1 -- )"},		/* dd C_next_input ; ( -- f c2 ) (R c1 -- ) 10552 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial )"},		/* dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial ) 10560 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial )"},		/* dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial ) 10568 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial )"},		/* dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial ) 10576 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10584 */
	{.type FromH0, {.p L146}, .src = "dd L146		; >In >= >Limit || cinitial != cnew"},		/* dd L146		; >In >= >Limit || cinitial != cnew 10592 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal	; >In < >Limit && cinitial == cnew"},		/* dd M_literal	; >In < >Limit && cinitial == cnew 10600 */
	{.type Absolute, {.p 1}},		/* dd 1 10608 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 10616 */
	{.type FromH0, {.p C_plusstore}, .src = "dd C_plusstore	; >In++"},		/* dd C_plusstore	; >In++ 10624 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump		; repeat"},		/* dd M_jump		; repeat 10632 */
	{.type FromH0, {.p L145}, .src = "dd L145"},		/* dd L145 10640 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character"},		/* dd M_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character 10648 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 10656 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10664 */
	{.type Header, {.hdr { 6, "accept", /* C_accept = 10680 */ colon }}}, /* CENTRY "accept" accept 6 ; ( a n -- n ) get line or n chars or EOF from input and store at a h 10688 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( n a -- )"},		/* dd M_xswap	; ( n a -- ) 10696 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n a a -- )"},		/* dd M_dup	; ( n a a -- ) 10704 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 10712 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( n -- ) (R a a -- )"},		/* dd M_rpush	; ( n -- ) (R a a -- ) 10720 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup	; ( n n -- ) (R a a -- )"},		/* dd C_qdup	; ( n n -- ) (R a a -- ) 10728 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump	; (if)"},		/* dd M_cjump	; (if) 10736 */
	{.type FromH0, {.p L149}, .src = "dd L149	; n == 0"},		/* dd L149	; n == 0 10744 */
	{.type FromH0, {.p C_key}, .src = "dd C_key	; n > 0 ( n -- n c )"},		/* dd C_key	; n > 0 ( n -- n c ) 10752 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( -- n c c )"},		/* dd M_dup	; ( -- n c c ) 10760 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10768 */
	{.type Absolute, {.p 10}},		/* dd 10		; ( -- n c c 10 ) 10776 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( n c c 10 -- n c f ) checking for newline"},		/* dd M_equal	; ( n c c 10 -- n c f ) checking for newline 10784 */
	{.type FromH0, {.p M_over}, .src = "dd M_over	; ( -- n c f c )"},		/* dd M_over	; ( -- n c f c ) 10792 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10800 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( -- n c f c -1 ) 10808 */
	{.type FromH0, {.p M_equal}, .src = "dd M_equal	; ( -- n c f1 f2 )"},		/* dd M_equal	; ( -- n c f1 f2 ) 10816 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor	; ( -- n c f )"},		/* dd M_binor	; ( -- n c f ) 10824 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 10832 */
	{.type FromH0, {.p L150}, .src = "dd L150"},		/* dd L150 10840 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop	; n == -1 || n == 10 (	-- )"},		/* dd C_2drop	; n == -1 || n == 10 (	-- ) 10848 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 10856 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 10864 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( -- a2-a1 )"},		/* dd M_minus	; ( -- a2-a1 ) 10872 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; ( -- n ) (R -- )"},		/* dd M_exitcolon	; ( -- n ) (R -- ) 10880 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch	; ( n c a -- ) (R a a -- )"},		/* dd M_rfetch	; ( n c a -- ) (R a a -- ) 10888 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore	; store the character at a"},		/* dd M_cstore	; store the character at a 10896 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( n a -- ) (R a -- )"},		/* dd M_rpop	; ( n a -- ) (R a -- ) 10904 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 10912 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address"},		/* dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address 10920 */
	{.type FromH0, {.p C_1minus}, .src = "dd C_1minus	; ( n -- n-1 )"},		/* dd C_1minus	; ( n -- n-1 ) 10928 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 10936 */
	{.type FromH0, {.p L148}, .src = "dd L148	; loop again for the next character"},		/* dd L148	; loop again for the next character 10944 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 )"},		/* dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 ) 10952 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( a2 a1 -- ) (R a1 -- )"},		/* dd M_rpop	; ( a2 a1 -- ) (R a1 -- ) 10960 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( a2 a1 -- a2-a1 )"},		/* dd M_minus	; ( a2 a1 -- a2-a1 ) 10968 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10976 */
	{.type Header, {.hdr { 5, "query", /* C_query = 10992 */ colon }}}, /* CENTRY "query" query 5 ; read from input stream into the Text Input Buffer h 11000 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 11008 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; clear EOF flag"},		/* dd C_off		; clear EOF flag 11016 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top"},		/* dd M_Tib	; constant puts address of tibuffer on the top 11024 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11032 */
	{.type Absolute, {.p 4096}},		/* dd 4096	; ( tibuffer -- tibuffer 4096 ) 11040 */
	{.type FromH0, {.p C_accept}, .src = "dd C_accept ; ( tibuffer 4096 -- n )"},		/* dd C_accept ; ( tibuffer 4096 -- n ) 11048 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( n -- n n )"},		/* dd M_dup	; ( n -- n n ) 11056 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq	; ( n n -- n f )"},		/* dd C_0eq	; ( n n -- n f ) 11064 */
	{.type FromH0, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 11072 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11080 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; n == 0 && EOF"},		/* dd M_binand	; n == 0 && EOF 11088 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11096 */
	{.type FromH0, {.p L152}, .src = "dd L152		; false condition"},		/* dd L152		; false condition 11104 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; n == 0 && EOF ( n -- )"},		/* dd M_drop	; n == 0 && EOF ( n -- ) 11112 */
	{.type FromH0, {.p C_qrestore_input}, .src = "dd C_qrestore_input"},		/* dd C_qrestore_input 11120 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11128 */
	{.type FromH0, {.p L153}, .src = "dd L153"},		/* dd L153 11136 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 11144 */
	{.type FromH0, {.p M_store}, .src = "dd M_store		; number of characters to read >Limit = n"},		/* dd M_store		; number of characters to read >Limit = n 11152 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 11160 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; start from 0 >In = 0"},		/* dd C_off		; start from 0 >In = 0 11168 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11176 */
	{.type Header, {.hdr { 6, "refill", /* C_refill = 11192 */ colon }}}, /* CENTRY "refill" refill 6 h 11200 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 11208 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11216 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11224 */
	{.type FromH0, {.p L155}, .src = "dd L155"},		/* dd L155 11232 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 11240 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11248 */
	{.type FromH0, {.p L156}, .src = "dd L156"},		/* dd L156 11256 */
	{.type FromH0, {.p C_query}, .src = "dd C_query"},		/* dd C_query 11264 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 11272 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11280 */
	{.type Header, {.hdr { 8, "findname", /* C_findname = 11304 */ colon }}}, /* CENTRY "findname" findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names h 11312 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 11320 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11328 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop"},		/* dd M_Dtop 11336 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; get latest dictionary link"},		/* dd M_fetch	; get latest dictionary link 11344 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 11352 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11360 */
	{.type FromH0, {.p L159}, .src = "dd L159	; seached until the first dictionary entry get out"},		/* dd L159	; seached until the first dictionary entry get out 11368 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a )"},		/* dd M_dup	; ( a -- a a ) 11376 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; ( a a -- a a+8) lenth + initial name address"},		/* dd C_cellplus	; ( a a -- a a+8) lenth + initial name address 11384 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name"},		/* dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name 11392 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11400 */
	{.type Absolute, {.p 64}},		/* dd 64		; check the reveal'ed flag 1=hidden, 0=reveal 11408 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; if hidden, goto L161 else L160"},		/* dd M_binand	; if hidden, goto L161 else L160 11416 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11424 */
	{.type FromH0, {.p L160}, .src = "dd L160"},		/* dd L160 11432 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; smudge'd dictionary entry, get the previous entry"},		/* dd M_fetch	; smudge'd dictionary entry, get the previous entry 11440 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11448 */
	{.type FromH0, {.p L161}, .src = "dd L161"},		/* dd L161 11456 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a1 -- a1 a1)"},		/* dd M_dup	; ( a1 -- a1 a1) 11464 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; ( a1 a1 -- a1 a1+8)"},		/* dd C_cellplus	; ( a1 a1 -- a1 a1+8) 11472 */
	{.type FromH0, {.p C_count}, .src = "dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n )"},		/* dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n ) 11480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11488 */
	{.type Absolute, {.p 63}},		/* dd 63 11496 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len )"},		/* dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len ) 11504 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 11512 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11520 */
	{.type FromH0, {.p C_count}, .src = "dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 )"},		/* dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 ) 11528 */
	{.type FromH0, {.p C_compare}, .src = "dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name"},		/* dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name 11536 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq	; found a match?"},		/* dd C_0eq	; found a match? 11544 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11552 */
	{.type FromH0, {.p L162}, .src = "dd L162		; no match"},		/* dd L162		; no match 11560 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus	; match found"},		/* dd C_cellplus	; match found 11568 */
	{.type FromH0, {.p C_true}, .src = "dd C_true"},		/* dd C_true 11576 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11584 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11592 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11600 */
	{.type FromH0, {.p L158}, .src = "dd L158"},		/* dd L158 11608 */
	{.type FromH0, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 11616 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11624 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 11632 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11640 */
	{.type Header, {.hdr { 4, "find", /* C_find = 11656 */ colon }}}, /* CENTRY "find" find 4 ; ( a1 -- a2 f )? h 11664 */
	{.type FromH0, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 11672 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11680 */
	{.type FromH0, {.p L164}, .src = "dd L164"},		/* dd L164 11688 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 11696 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 11704 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 11712 */
	{.type FromH0, {.p M_over}, .src = "dd M_over"},		/* dd M_over 11720 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11728 */
	{.type Absolute, {.p 63}},		/* dd 63 11736 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 11744 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11752 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 11760 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 11768 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 11776 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11784 */
	{.type Absolute, {.p 128}},		/* dd 128 11792 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 11800 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11808 */
	{.type FromH0, {.p L165}, .src = "dd L165"},		/* dd L165 11816 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11824 */
	{.type Absolute, {.p 1}},		/* dd 1 11832 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11840 */
	{.type FromH0, {.p L166}, .src = "dd L166"},		/* dd L166 11848 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11856 */
	{.type Absolute, {.p -1}},		/* dd -1 11864 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11872 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 11880 */
	{.type FromH0, {.p L167}, .src = "dd L167"},		/* dd L167 11888 */
	{.type FromH0, {.p C_false}, .src = "dd C_false"},		/* dd C_false 11896 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11904 */
	{.type Header, {.hdr { 1, "'", /* C_single_quote = 11920 */ colon }}}, /* CENTRY "'" single_quote 1 h 11928 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 11936 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 11944 */
	{.type FromH0, {.p C_find}, .src = "dd C_find"},		/* dd C_find 11952 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 11960 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11968 */
	{.type FromH0, {.p L169}, .src = "dd L169"},		/* dd L169 11976 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 11984 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 11992 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12000 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12008 */
	{.type FromH0, {.p L170}, .src = "dd L170"},		/* dd L170 12016 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12024 */
	{.type Absolute, {.p 3}},		/* dd 3 12032 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12040 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12048 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12056 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12064 */
	{.type Header, {.hdr { 6, "?stack", /* C_qstack = 12080 */ colon }}}, /* CENTRY "?stack" qstack 6 h 12088 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 12096 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 12104 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 12112 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12120 */
	{.type FromH0, {.p L172}, .src = "dd L172"},		/* dd L172 12128 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12136 */
	{.type FromH0, {.p L173}, .src = "dd L173"},		/* dd L173 12144 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12152 */
	{.type Absolute, {.p 16}},		/* dd 16 12160 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12168 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12176 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12184 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12192 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup ; debug code to show the word found"},		/* dd M_dup ; debug code to show the word found 12200 */
	{.type FromH0, {.p C_count}, .src = "dd C_count ; ( -- a n)"},		/* dd C_count ; ( -- a n) 12208 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap ; ( -- n a)"},		/* dd M_xswap ; ( -- n a) 12216 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 12224 */
	{.type FromH0, {.p M_fthwrite}, .src = "dd M_fthwrite"},		/* dd M_fthwrite 12232 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 12240 */
	{.type Header, {.hdr { 9, "interpret", /* C_interpret = 12264 */ colon }}}, /* CENTRY "interpret" interpret 9 ; there is stuff in TIB to be interpreted >In and >Limit are set h 12272 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 12280 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; ( bl -- a ) a = address of counted string"},		/* dd C_word	; ( bl -- a ) a = address of counted string 12288 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12296 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 12304 */
	{.type FromH0, {.p C_0neq}, .src = "dd C_0neq"},		/* dd C_0neq 12312 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12320 */
	{.type FromH0, {.p L176}, .src = "dd L176	; count at a = 0"},		/* dd L176	; count at a = 0 12328 */
	{.type FromH0, {.p C_find}, .src = "dd C_find	; ( a -- a1 f ) a = address of counted string"},		/* dd C_find	; ( a -- a1 f ) a = address of counted string 12336 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12344 */
	{.type FromH0, {.p L177}, .src = "dd L177"},		/* dd L177 12352 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute	; found in dictionary, execute"},		/* dd M_execute	; found in dictionary, execute 12360 */
	{.type FromH0, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 12368 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12376 */
	{.type FromH0, {.p L178}, .src = "dd L178"},		/* dd L178 12384 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 12392 */
	{.type FromH0, {.p C_number}, .src = "dd C_number"},		/* dd C_number 12400 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 12408 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12416 */
	{.type FromH0, {.p L179}, .src = "dd L179"},		/* dd L179 12424 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 12432 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12440 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12448 */
	{.type FromH0, {.p L180}, .src = "dd L180	; error I?"},		/* dd L180	; error I? 12456 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12464 */
	{.type Absolute, {.p 3}},		/* dd 3 12472 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12480 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12488 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12496 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 12504 */
	{.type FromH0, {.p L175}, .src = "dd L175"},		/* dd L175 12512 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop	; count at a = 0 ( a -- )"},		/* dd M_drop	; count at a = 0 ( a -- ) 12520 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12528 */
	{.type Header, {.hdr { 6, "create", /* C_create = 12544 */ colon }}}, /* CENTRY "create" create 6 ; compiles dictionary header until the pfa (link, len, name, cfa) h 12552 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 12560 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( -- here )"},		/* dd C_here	; ( -- here ) 12568 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( -- ) (R -- linkaddr )"},		/* dd M_rpush	; ( -- ) (R -- linkaddr ) 12576 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop	; ( -- Dtop ) (R -- linkaddr )"},		/* dd M_Dtop	; ( -- Dtop ) (R -- linkaddr ) 12584 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr )"},		/* dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr ) 12592 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; ( dtop -- ) (R -- linkaddr )"},		/* dd C_comma	; ( dtop -- ) (R -- linkaddr ) 12600 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 12608 */
	{.type FromH0, {.p C_word}, .src = "dd C_word	; get the word from the input stream ( c -- a ) skip any c. Placed the counted string in a (as in Wordbuf)"},		/* dd C_word	; get the word from the input stream ( c -- a ) skip any c. Placed the counted string in a (as in Wordbuf) 12616 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a -- a a ) (R -- linkaddr )"},		/* dd M_dup	; ( a -- a a ) (R -- linkaddr ) 12624 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a -- a len ) (R -- linkaddr )"},		/* dd M_cfetch	; ( a a -- a len ) (R -- linkaddr ) 12632 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( a len -- a len here ) (R -- linkaddr )"},		/* dd C_here	; ( a len -- a len here ) (R -- linkaddr ) 12640 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr )"},		/* dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr ) 12648 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte"},		/* dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte 12656 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr )"},		/* dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr ) 12664 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 )"},		/* dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 ) 12672 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 )"},		/* dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 ) 12680 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- len+1 ) (R -- linkaddr )"},		/* dd M_rpop	; ( -- len+1 ) (R -- linkaddr ) 12688 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1"},		/* dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1 12696 */
	{.type FromH0, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 12704 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12712 */
	{.type FromH0, {.p M_variable}, .src = "dd M_variable"},		/* dd M_variable 12720 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( -- variablecfa) (R -- linkaddr )"},		/* dd M_fetch	; ( -- variablecfa) (R -- linkaddr ) 12728 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; ( -- ) put the variablecfa into the cfa"},		/* dd C_comma	; ( -- ) put the variablecfa into the cfa 12736 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop	; ( -- linkaddr) (R -- )"},		/* dd M_rpop	; ( -- linkaddr) (R -- ) 12744 */
	{.type FromH0, {.p M_Dtop}, .src = "dd M_Dtop"},		/* dd M_Dtop 12752 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; Dtop = just created link address"},		/* dd M_store	; Dtop = just created link address 12760 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12768 */
	{.type Header, {.hdr { 8, "variable", /* C_variable = 12792 */ colon }}}, /* CENTRY "variable" variable 8 h 12800 */
	{.type FromH0, {.p C_create}, .src = "dd C_create"},		/* dd C_create 12808 */
	{.type FromH0, {.p C_vhere}, .src = "dd C_vhere"},		/* dd C_vhere 12816 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; put the next available variable location in pfa"},		/* dd C_comma	; put the next available variable location in pfa 12824 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12832 */
	{.type Absolute, {.p 1}},		/* dd 1 12840 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 12848 */
	{.type FromH0, {.p C_vallot}, .src = "dd C_vallot	; vhere = vhere+8, stored at Vp"},		/* dd C_vallot	; vhere = vhere+8, stored at Vp 12856 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12864 */
	{.type Header, {.hdr { 8, "constant", /* C_constant = 12888 */ colon }}}, /* CENTRY "constant" constant 8 ; ( n -- ) do the same as variable but change the cfa to (constant) h 12896 */
	{.type FromH0, {.p C_create}, .src = "dd C_create	; create dictionary header upto the cfa"},		/* dd C_create	; create dictionary header upto the cfa 12904 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12912 */
	{.type FromH0, {.p M_constant}, .src = "dd M_constant"},		/* dd M_constant 12920 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Contstantcfa -- (constant) )"},		/* dd M_fetch	; ( Contstantcfa -- (constant) ) 12928 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( (constant) -- (constant) here )"},		/* dd C_here	; ( (constant) -- (constant) here ) 12936 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12944 */
	{.type Absolute, {.p 1}},		/* dd 1 12952 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells	; ( (constant) here -- (constant) here 8 )"},		/* dd C_cells	; ( (constant) here -- (constant) here 8 ) 12960 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( (constant) here 8 -- (constant) here-8 )"},		/* dd M_minus	; ( (constant) here 8 -- (constant) here-8 ) 12968 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant) "},		/* dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant)  12976 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma	; store n into the dictionary"},		/* dd C_comma	; store n into the dictionary 12984 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12992 */
	{.type Header, {.hdr { 9, "immediate", /* C_immediate = 13016 */ colon }}}, /* CENTRY "immediate" immediate 9 h 13024 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 13032 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13040 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 13048 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13056 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13064 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13072 */
	{.type Absolute, {.p 128}},		/* dd 128 13080 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 13088 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 13096 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 13104 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13112 */
	{.type Header, {.hdr { 4, ">cfa", /* C_tocfa = 13128 */ colon }}}, /* CENTRY ">cfa" tocfa 4 h 13136 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13144 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13152 */
	{.type Absolute, {.p 63}},		/* dd 63 13160 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 13168 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 13176 */
	{.type FromH0, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 13184 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13192 */
	{.type Header, {.hdr { 7, "compile", /* C_compile = 13208 */ colon }}}, /* CENTRY "compile" compile 7 h 13216 */
	{.type FromH0, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 13224 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13232 */
	{.type FromH0, {.p L188}, .src = "dd L188"},		/* dd L188 13240 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13248 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13256 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13264 */
	{.type Absolute, {.p 128}},		/* dd 128 13272 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 13280 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13288 */
	{.type FromH0, {.p L189}, .src = "dd L189"},		/* dd L189 13296 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa	; immediate"},		/* dd C_tocfa	; immediate 13304 */
	{.type FromH0, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 13312 */
	{.type FromH0, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 13320 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13328 */
	{.type FromH0, {.p L190}, .src = "dd L190"},		/* dd L190 13336 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 13344 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 13352 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13360 */
	{.type FromH0, {.p L191}, .src = "dd L191"},		/* dd L191 13368 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13376 */
	{.type FromH0, {.p C_number}, .src = "dd C_number"},		/* dd C_number 13384 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 13392 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13400 */
	{.type FromH0, {.p L192}, .src = "dd L192"},		/* dd L192 13408 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 13416 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13424 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13432 */
	{.type FromH0, {.p L193}, .src = "dd L193"},		/* dd L193 13440 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13448 */
	{.type Absolute, {.p 3}},		/* dd 3 13456 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13464 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 13472 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 13480 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13488 */
	{.type FromH0, {.p L194}, .src = "dd L194"},		/* dd L194 13496 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13504 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13512 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 13520 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 13528 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13536 */
	{.type Header, {.hdr { 1, "]", /* C_close_bracket = 13552 */ colon }}}, /* CENTRY "]" close_bracket 1 h 13560 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 13568 */
	{.type FromH0, {.p C_on}, .src = "dd C_on"},		/* dd C_on 13576 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 13584 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 13592 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13600 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13608 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 13616 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13624 */
	{.type FromH0, {.p L197}, .src = "dd L197"},		/* dd L197 13632 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 13640 */
	{.type FromH0, {.p C_refill}, .src = "dd C_refill"},		/* dd C_refill 13648 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13656 */
	{.type FromH0, {.p L198}, .src = "dd L198"},		/* dd L198 13664 */
	{.type FromH0, {.p C_compile}, .src = "dd C_compile"},		/* dd C_compile 13672 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 13680 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13688 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13696 */
	{.type FromH0, {.p L199}, .src = "dd L199"},		/* dd L199 13704 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13712 */
	{.type FromH0, {.p L196}, .src = "dd L196"},		/* dd L196 13720 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13728 */
	{.type IHeader, {.hdr { 1, "[", /* CI_open_bracket = 13744 */ colon }}}, /* CIENTRY "[" open_bracket 1 h 13752 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 13760 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 13768 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13776 */
	{.type Header, {.hdr { 6, "smudge", /* C_smudge = 13792 */ colon }}}, /* CENTRY "smudge" smudge 6 h 13800 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 13808 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13816 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 13824 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13832 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13840 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13848 */
	{.type Absolute, {.p 64}},		/* dd 64 13856 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 13864 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 13872 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 13880 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13888 */
	{.type Header, {.hdr { 6, "reveal", /* C_reveal = 13904 */ colon }}}, /* CENTRY "reveal" reveal 6 h 13912 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 13920 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13928 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 13936 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13944 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 13952 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13960 */
	{.type Absolute, {.p 64}},		/* dd 64 13968 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 13976 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 13984 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 13992 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 14000 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14008 */
	{.type Header, {.hdr { 1, ":", /* C_colon = 14024 */ colon }}}, /* CENTRY ":" colon 1 h 14032 */
	{.type FromH0, {.p C_create}, .src = "dd C_create	; create a dictionary header with (variable) at cfa"},		/* dd C_create	; create a dictionary header with (variable) at cfa 14040 */
	{.type FromH0, {.p C_smudge}, .src = "dd C_smudge"},		/* dd C_smudge 14048 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14056 */
	{.type FromH0, {.p M_colon}, .src = "dd M_colon"},		/* dd M_colon 14064 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon"},		/* dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon 14072 */
	{.type FromH0, {.p C_here}, .src = "dd C_here	; ( (colon) -- (colon) here )"},		/* dd C_here	; ( (colon) -- (colon) here ) 14080 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14088 */
	{.type Absolute, {.p 1}},		/* dd 1 14096 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 14104 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( (colon) here -- (colon) here-8 )"},		/* dd M_minus	; ( (colon) here -- (colon) here-8 ) 14112 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon"},		/* dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon 14120 */
	{.type FromH0, {.p C_close_bracket}, .src = "dd C_close_bracket"},		/* dd C_close_bracket 14128 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14136 */
	{.type IHeader, {.hdr { 1, ";", /* CI_semicolon = 14152 */ colon }}}, /* CIENTRY ";" semicolon 1 h 14160 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14168 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14176 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14184 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 14192 */
	{.type FromH0, {.p C_off}, .src = "dd C_off"},		/* dd C_off 14200 */
	{.type FromH0, {.p C_reveal}, .src = "dd C_reveal"},		/* dd C_reveal 14208 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14216 */
	{.type IHeader, {.hdr { 7, "recurse", /* CI_recurse = 14232 */ colon }}}, /* CIENTRY "recurse" recurse 7 h 14240 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 14248 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14256 */
	{.type FromH0, {.p C_cellplus}, .src = "dd C_cellplus"},		/* dd C_cellplus 14264 */
	{.type FromH0, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 14272 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14280 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14288 */
	{.type Header, {.hdr { 4, "char", /* C_L206 = 14304 */ colon }}}, /* CENTRY "char" L206 4 h 14312 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 14320 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 14328 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 14336 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14344 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14352 */
	{.type Header, {.hdr { 7, "literal", /* C_literal = 14368 */ colon }}}, /* CENTRY "literal" literal 7 h 14376 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14384 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14392 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14400 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14408 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14416 */
	{.type Header, {.hdr { 8, "sliteral", /* C_sliteral = 14440 */ colon }}}, /* CENTRY "sliteral" sliteral 8 h 14448 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14456 */
	{.type FromH0, {.p M_sliteral}, .src = "dd M_sliteral"},		/* dd M_sliteral 14464 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 14472 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 14480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14488 */
	{.type Absolute, {.p 34}},		/* dd 34 14496 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 14504 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14512 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14520 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 14528 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 14536 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 14544 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 14552 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 14560 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 14568 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 14576 */
	{.type FromH0, {.p C_align}, .src = "dd C_align"},		/* dd C_align 14584 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14592 */
	{.type Header, {.hdr { 6, "string", /* C_string = 14608 */ colon }}}, /* CENTRY "string" string 6 h 14616 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 14624 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14632 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14640 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 14648 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 14656 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 14664 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 14672 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 14680 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 14688 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 14696 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14704 */
	{.type IHeader, {.hdr { 6, "[char]", /* CI_char_brackets = 14720 */ colon }}}, /* CIENTRY "[char]" char_brackets 6 h 14728 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 14736 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 14744 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 14752 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14760 */
	{.type FromH0, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 14768 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14776 */
	{.type IHeader, {.hdr { 3, "[']", /* CI_quote_brackets = 14792 */ colon }}}, /* CIENTRY "[']" quote_brackets 3 h 14800 */
	{.type FromH0, {.p C_single_quote}, .src = "dd C_single_quote"},		/* dd C_single_quote 14808 */
	{.type FromH0, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 14816 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14824 */
	{.type IHeader, {.hdr { 1, "(", /* CI_openparen = 14840 */ colon }}}, /* CIENTRY "(" openparen 1 h 14848 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14856 */
	{.type Absolute, {.p 41}},		/* dd 41 14864 */
	{.type FromH0, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 14872 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 14880 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14888 */
	{.type IHeader, {.hdr { 1, "\\", /* CI_backslash = 14904 */ colon }}}, /* CIENTRY "\\" backslash 1 h 14912 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk"},		/* dd MV_Blk 14920 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14928 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14936 */
	{.type FromH0, {.p L214}, .src = "dd L214"},		/* dd L214 14944 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 14952 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14960 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14968 */
	{.type Absolute, {.p 63}},		/* dd 63 14976 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 14984 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14992 */
	{.type Absolute, {.p 63}},		/* dd 63 15000 */
	{.type FromH0, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 15008 */
	{.type FromH0, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 15016 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 15024 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15032 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15040 */
	{.type FromH0, {.p L215}, .src = "dd L215"},		/* dd L215 15048 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 15056 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 15064 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 15072 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15080 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15088 */
	{.type Header, {.hdr { 8, "(?abort)", /* C_qabort_parens = 15112 */ colon }}}, /* CENTRY "(?abort)" qabort_parens 8 h 15120 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 15128 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15136 */
	{.type FromH0, {.p L217}, .src = "dd L217"},		/* dd L217 15144 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 15152 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 15160 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 15168 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 15176 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15184 */
	{.type FromH0, {.p L218}, .src = "dd L218"},		/* dd L218 15192 */
	{.type FromH0, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 15200 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15208 */
	{.type IHeader, {.hdr { 6, "abort\"", /* CI_abort_double_quote = 15224 */ colon }}}, /* CIENTRY "abort\"" abort_double_quote 6 h 15232 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 15240 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15248 */
	{.type FromH0, {.p C_qabort_parens}, .src = "dd C_qabort_parens"},		/* dd C_qabort_parens 15256 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15264 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15272 */
	{.type Header, {.hdr { 1, "\"", /* C_double_quote = 15288 */ colon }}}, /* CENTRY "\"" double_quote 1 h 15296 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15304 */
	{.type Absolute, {.p 34}},		/* dd 34 15312 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 15320 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 15328 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 15336 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15344 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 15352 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 15360 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15368 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 15376 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15384 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 15392 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15400 */
	{.type Header, {.hdr { 2, "c\"", /* C_cdouble_quote = 15416 */ colon }}}, /* CENTRY "c\"" cdouble_quote 2 h 15424 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15432 */
	{.type Absolute, {.p 34}},		/* dd 34 15440 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 15448 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15456 */
	{.type FromH0, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 15464 */
	{.type FromH0, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 15472 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 15480 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15488 */
	{.type FromH0, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 15496 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 15504 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15512 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 15520 */
	{.type FromH0, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 15528 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15536 */
	{.type IHeader, {.hdr { 2, "s\"", /* CI_sdouble_quote = 15552 */ colon }}}, /* CIENTRY "s\"" sdouble_quote 2 h 15560 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 15568 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15576 */
	{.type IHeader, {.hdr { 2, ".\"", /* CI_dotstr = 15592 */ colon }}}, /* CIENTRY ".\"" dotstr 2 h 15600 */
	{.type FromH0, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 15608 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15616 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 15624 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15632 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15640 */
	{.type IHeader, {.hdr { 2, "if", /* CI_if = 15656 */ colon }}}, /* CIENTRY "if" if 2 h 15664 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15672 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15680 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15688 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15696 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15704 */
	{.type Absolute, {.p 0}},		/* dd 0 15712 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15720 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15728 */
	{.type IHeader, {.hdr { 4, "else", /* CI_else = 15744 */ colon }}}, /* CIENTRY "else" else 4 h 15752 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15760 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15768 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15776 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15784 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 15792 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15800 */
	{.type Absolute, {.p 0}},		/* dd 0 15808 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15816 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15824 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 15832 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15840 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 15848 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15856 */
	{.type IHeader, {.hdr { 4, "then", /* CI_then = 15872 */ colon }}}, /* CIENTRY "then" then 4 h 15880 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15888 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 15896 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 15904 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15912 */
	{.type IHeader, {.hdr { 5, "begin", /* CI_begin = 15928 */ colon }}}, /* CIENTRY "begin" begin 5 h 15936 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 15944 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15952 */
	{.type IHeader, {.hdr { 5, "again", /* CI_again = 15968 */ colon }}}, /* CIENTRY "again" again 5 h 15976 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15984 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15992 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16000 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16008 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16016 */
	{.type IHeader, {.hdr { 5, "until", /* CI_until = 16032 */ colon }}}, /* CIENTRY "until" until 5 h 16040 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16048 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16056 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16064 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16072 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16080 */
	{.type IHeader, {.hdr { 5, "while", /* CI_while = 16096 */ colon }}}, /* CIENTRY "while" while 5 h 16104 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16112 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16120 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16128 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16136 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16144 */
	{.type Absolute, {.p 0}},		/* dd 0 16152 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16160 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16168 */
	{.type IHeader, {.hdr { 6, "repeat", /* CI_repeat = 16184 */ colon }}}, /* CIENTRY "repeat" repeat 6 h 16192 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16200 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16208 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16216 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16224 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16232 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16240 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16248 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16256 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16264 */
	{.type IHeader, {.hdr { 2, "do", /* CI_do = 16280 */ colon }}}, /* CIENTRY "do" do 2 h 16288 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16296 */
	{.type FromH0, {.p M_doinit}, .src = "dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time"},		/* dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time 16304 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; puts (do) into the dictionary"},		/* dd C_comma		; puts (do) into the dictionary 16312 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16320 */
	{.type Absolute, {.p 0}},		/* dd 0			; ( -- 0 ) 16328 */
	{.type FromH0, {.p C_here}, .src = "dd C_here		; ( 0 -- 0 here1 )"},		/* dd C_here		; ( 0 -- 0 here1 ) 16336 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16344 */
	{.type IHeader, {.hdr { 4, "loop", /* CI_loop = 16360 */ colon }}}, /* CIENTRY "loop" loop 4 ; ( 0 here1 -- ) h 16368 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16376 */
	{.type FromH0, {.p M_doloop}, .src = "dd M_doloop		; ( 0 here1 -- 0 here1 (loop) )"},		/* dd M_doloop		; ( 0 here1 -- 0 here1 (loop) ) 16384 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 )"},		/* dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 ) 16392 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 )"},		/* dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 ) 16400 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 16408 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16416 */
	{.type FromH0, {.p L234}, .src = "dd L234"},		/* dd L234 16424 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16432 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16440 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16448 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16456 */
	{.type IHeader, {.hdr { 5, "+loop", /* CI_ploop = 16472 */ colon }}}, /* CIENTRY "+loop" ploop 5 h 16480 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16488 */
	{.type FromH0, {.p M_doploop}, .src = "dd M_doploop"},		/* dd M_doploop 16496 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16504 */
	{.type FromH0, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16512 */
	{.type FromH0, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 16520 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16528 */
	{.type FromH0, {.p L236}, .src = "dd L236"},		/* dd L236 16536 */
	{.type FromH0, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16544 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16552 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 16560 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16568 */
	{.type Header, {.hdr { 3, "w/o", /* C_wo = 16584 */ colon }}}, /* CENTRY "w/o" wo 3 h 16592 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16600 */
	{.type Absolute, {.p 1}},		/* dd 1 16608 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16616 */
	{.type Absolute, {.p 512}},		/* dd 512 16624 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 16632 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16640 */
	{.type Absolute, {.p 64}},		/* dd 64 16648 */
	{.type FromH0, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 16656 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16664 */
	{.type Header, {.hdr { 3, "r/o", /* C_ro = 16680 */ colon }}}, /* CENTRY "r/o" ro 3 h 16688 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16696 */
	{.type Absolute, {.p 0}},		/* dd 0 16704 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16712 */
	{.type Header, {.hdr { 3, "r/w", /* C_rw = 16728 */ colon }}}, /* CENTRY "r/w" rw 3 h 16736 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16744 */
	{.type Absolute, {.p 2}},		/* dd 2 16752 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16760 */
	{.type Header, {.hdr { 9, "open-file", /* C_open_file = 16784 */ colon }}}, /* CENTRY "open-file" open_file 9 h 16792 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 16800 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 16808 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16816 */
	{.type Absolute, {.p 1024}},		/* dd 1024 16824 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 16832 */
	{.type FromH0, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16840 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 16848 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 16856 */
	{.type FromH0, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 16864 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16872 */
	{.type Absolute, {.p 0}},		/* dd 0 16880 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 16888 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 16896 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 16904 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16912 */
	{.type Absolute, {.p 1024}},		/* dd 1024 16920 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 16928 */
	{.type FromH0, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 16936 */
	{.type FromH0, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 16944 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16952 */
	{.type Absolute, {.p 1024}},		/* dd 1024 16960 */
	{.type FromH0, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 16968 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 16976 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16984 */
	{.type Absolute, {.p 420}},		/* dd 420 16992 */
	{.type FromH0, {.p M_fthopen}, .src = "dd M_fthopen"},		/* dd M_fthopen 17000 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17008 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17016 */
	{.type Absolute, {.p -1}},		/* dd -1 17024 */
	{.type FromH0, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 17032 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17040 */
	{.type Header, {.hdr { 10, "close-file", /* C_close_file = 17064 */ colon }}}, /* CENTRY "close-file" close_file 10 h 17072 */
	{.type FromH0, {.p M_fthclose}, .src = "dd M_fthclose"},		/* dd M_fthclose 17080 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 17088 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17096 */
	{.type Header, {.hdr { 9, "read-file", /* C_read_file = 17120 */ colon }}}, /* CENTRY "read-file" read_file 9 h 17128 */
	{.type FromH0, {.p M_fthread}, .src = "dd M_fthread"},		/* dd M_fthread 17136 */
	{.type FromH0, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17144 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17152 */
	{.type Absolute, {.p -1}},		/* dd -1 17160 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17168 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17176 */
	{.type Header, {.hdr { 10, "write-file", /* C_write_file = 17200 */ colon }}}, /* CENTRY "write-file" write_file 10 h 17208 */
	{.type FromH0, {.p M_fthwrite}, .src = "dd M_fthwrite"},		/* dd M_fthwrite 17216 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17224 */
	{.type Absolute, {.p -1}},		/* dd -1 17232 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17240 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17248 */
	{.type Header, {.hdr { 15, "reposition-file", /* C_reposition_file = 17272 */ colon }}}, /* CENTRY "reposition-file" reposition_file 15 h 17280 */
	{.type FromH0, {.p M_fthseek}, .src = "dd M_fthseek"},		/* dd M_fthseek 17288 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17296 */
	{.type Absolute, {.p -1}},		/* dd -1 17304 */
	{.type FromH0, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 17312 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17320 */
	{.type Header, {.hdr { 7, "?fcheck", /* C_qfcheck = 17336 */ colon }}}, /* CENTRY "?fcheck" qfcheck 7 h 17344 */
	{.type FromH0, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 17352 */
	{.type FromH0, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 17360 */
	{.type FromH0, {.p L246}, .src = "dd L246"},		/* dd L246 17368 */
	{.type FromH0, {.p C_space}, .src = "dd C_space"},		/* dd C_space 17376 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17384 */
	{.type FromH0, {.p L247}, .src = "dd L247"},		/* dd L247 17392 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17400 */
	{.type Absolute, {.p 9}},		/* dd 9 17408 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 17416 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 17424 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 17432 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17440 */
	{.type Header, {.hdr { 3, "bye", /* C_bye = 17456 */ colon }}}, /* CENTRY "bye" bye 3 h 17464 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17472 */
	{.type Absolute, {.p 0}},		/* dd 0 17480 */
	{.type FromH0, {.p M_terminate}, .src = "dd M_terminate"},		/* dd M_terminate 17488 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17496 */
	{.type Header, {.hdr { 7, "include", /* C_include = 17512 */ colon }}}, /* CENTRY "include" include 7 h 17520 */
	{.type FromH0, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 17528 */
	{.type FromH0, {.p C_word}, .src = "dd C_word"},		/* dd C_word 17536 */
	{.type FromH0, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 17544 */
	{.type FromH0, {.p MV_toLimit}, .src = "dd MV_toLimit"},		/* dd MV_toLimit 17552 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 17560 */
	{.type FromH0, {.p MV_toIn}, .src = "dd MV_toIn"},		/* dd MV_toIn 17568 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 17576 */
	{.type FromH0, {.p C_save_input}, .src = "dd C_save_input"},		/* dd C_save_input 17584 */
	{.type FromH0, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 17592 */
	{.type FromH0, {.p C_count}, .src = "dd C_count"},		/* dd C_count 17600 */
	{.type FromH0, {.p C_ro}, .src = "dd C_ro"},		/* dd C_ro 17608 */
	{.type FromH0, {.p C_open_file}, .src = "dd C_open_file"},		/* dd C_open_file 17616 */
	{.type FromH0, {.p C_qfcheck}, .src = "dd C_qfcheck"},		/* dd C_qfcheck 17624 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 17632 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 17640 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17648 */
	{.type Header, {.hdr { 5, "crash", /* C_crash = 17664 */ colon }}}, /* CENTRY "crash" crash 5 h 17672 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17680 */
	{.type FromH0, {.p L251}, .src = "dd L251"},		/* dd L251 17688 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17696 */
	{.type Absolute, {.p 30}},		/* dd 30 17704 */
	{.type FromH0, {.p C_type}, .src = "dd C_type"},		/* dd C_type 17712 */
	{.type FromH0, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 17720 */
	{.type FromH0, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 17728 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17736 */
	{.type Header, {.hdr { 4, "quit", /* C_quit = 17752 */ colon }}}, /* CENTRY "quit" quit 4 ; interpreter loop h 17760 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 17768 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 17776 */
	{.type FromH0, {.p C_query}, .src = "dd C_query"},		/* dd C_query 17784 */
/* ; dd MV_toLimit	; show the line read, for debugging *//* ; dd M_fetch *//* ; dd M_Tib *//* ; dd MC_STDOUT *//* ; dd M_fthwrite *//* ; dd M_drop		; drop the return value of write *//* ; dd C_cr *//* ; dd C_space */	{.type FromH0, {.p C_interpret}, .src = "dd C_interpret"},		/* dd C_interpret 17792 */
	{.type FromH0, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 17800 */
	{.type FromH0, {.p L253}, .src = "dd L253"},		/* dd L253 17808 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed?"},		/* dd M_exitcolon	; why is this needed? 17816 */
	{.type Header, {.hdr { 7, "(abort)", /* C_parenabort = 17832 */ colon }}}, /* CENTRY "(abort)" parenabort 7 ; TODO correct below stack notations h 17840 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State	; ( mv_State -- )"},		/* dd MV_State	; ( mv_State -- ) 17848 */
	{.type FromH0, {.p C_off}, .src = "dd C_off		; off sets variable state = 0"},		/* dd C_off		; off sets variable state = 0 17856 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top of stack"},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 17864 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; variable sourcebuf"},		/* dd MV_Sourcebuf	; variable sourcebuf 17872 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable sourcebuf = address of tibuffer"},		/* dd M_store	; variable sourcebuf = address of tibuffer 17880 */
	{.type FromH0, {.p MV_Blk}, .src = "dd MV_Blk	; variable blk"},		/* dd MV_Blk	; variable blk 17888 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off variable blk = 0"},		/* dd C_off	; off variable blk = 0 17896 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 17904 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 17912 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 17920 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 17928 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 17936 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 17944 */
	{.type FromH0, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 17952 */
	{.type FromH0, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 17960 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 17968 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit resets stacks and is the interpreter loop"},		/* dd C_quit	; quit resets stacks and is the interpreter loop 17976 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed? quit does not return unless it breaks"},		/* dd M_exitcolon	; why is this needed? quit does not return unless it breaks 17984 */
	{.type Header, {.hdr { 7, "oldboot", /* C_oldboot = 18000 */ colon }}}, /* CENTRY "oldboot" oldboot 7 ; TODO correct below stack notations and this is obsolete. leaving it here for reference until it all works well h 18008 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset"},		/* dd M_reset 18016 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end"},		/* dd M_clear	; SP = sstack_end 18024 */
	{.type FromH0, {.p M_stackptr}, .src = "dd M_stackptr	; (D -- FFEND)"},		/* dd M_stackptr	; (D -- FFEND) 18032 */
	{.type FromH0, {.p M_S0}, .src = "dd M_S0"},		/* dd M_S0 18040 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; s0 = FFEND"},		/* dd M_store	; s0 = FFEND 18048 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp	; heaptop = heapend"},		/* dd M_Dp	; heaptop = heapend 18056 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( heapend -- )"},		/* dd M_fetch	; ( heapend -- ) 18064 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18072 */
	{.type Absolute, {.p 1}},		/* dd 1		; ( heapend 1 -- ) 18080 */
	{.type FromH0, {.p C_cells}, .src = "dd C_cells	; cells ( heapend 8 -- )"},		/* dd C_cells	; cells ( heapend 8 -- ) 18088 */
	{.type FromH0, {.p M_minus}, .src = "dd M_minus	; ( heapend-8 -- )"},		/* dd M_minus	; ( heapend-8 -- ) 18096 */
	{.type FromH0, {.p M_fetch}, .src = "dd M_fetch	; ( contents_from_heapend-8 -- )"},		/* dd M_fetch	; ( contents_from_heapend-8 -- ) 18104 */
	{.type FromH0, {.p M_Args}, .src = "dd M_Args	; variable args"},		/* dd M_Args	; variable args 18112 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; args = contents_from_heapend-8"},		/* dd M_store	; args = contents_from_heapend-8 18120 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18128 */
	{.type FromH0, {.p C_parenabort}, .src = "dd C_parenabort ; ( (abort) -- )"},		/* dd C_parenabort ; ( (abort) -- ) 18136 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec	; variable abortvec"},		/* dd MV_Abortvec	; variable abortvec 18144 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable abortvec = (abort) code address"},		/* dd M_store	; variable abortvec = (abort) code address 18152 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb	; constant puts address of wordbuffer on the top of stack"},		/* dd M_Wordb	; constant puts address of wordbuffer on the top of stack 18160 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf	; variable wordbuf"},		/* dd MV_Wordbuf	; variable wordbuf 18168 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable wordbuf = address of wordbuffer"},		/* dd M_store	; variable wordbuf = address of wordbuffer 18176 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top of stack"},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 18184 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; variable sourcebuf"},		/* dd MV_Sourcebuf	; variable sourcebuf 18192 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable sourcebuf = address of tibuffer"},		/* dd M_store	; variable sourcebuf = address of tibuffer 18200 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18208 */
	{.type Absolute, {.p 0}},		/* dd 0 18216 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18224 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdin = 0"},		/* dd M_store	; stdin = 0 18232 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18240 */
	{.type Absolute, {.p 1}},		/* dd 1 18248 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 18256 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; stdout = 1"},		/* dd M_store	; stdout = 1 18264 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 18272 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off stores 0 at state"},		/* dd C_off	; off stores 0 at state 18280 */
	{.type FromH0, {.p C_decimal}, .src = "dd C_decimal	; decimal setting base = 0"},		/* dd C_decimal	; decimal setting base = 0 18288 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit"},		/* dd C_quit	; quit 18296 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18304 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal	; test code"},		/* dd M_literal	; test code 18312 */
	{.type Absolute, {.p 66}},		/* dd 66 18320 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 18328 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18336 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18344 */
	{.type Absolute, {.p 1}},		/* dd 1 18352 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 18360 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 18368 */
	{.type FromH0, {.p M_fthwrite}, .src = "dd M_fthwrite"},		/* dd M_fthwrite 18376 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 18384 */
	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18392 */
	{.type Absolute, {.p 1}},		/* dd 1 18400 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb"},		/* dd M_Wordb 18408 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 18416 */
	{.type FromH0, {.p M_fthread}, .src = "dd M_fthread"},		/* dd M_fthread 18424 */
	{.type FromH0, {.p M_drop}, .src = "dd M_drop		; drop the return value of read"},		/* dd M_drop		; drop the return value of read 18432 */
	{.type Header, {.hdr { 4, "boot", /* C_boot = 18448 */ colon }}}, /* CENTRY "boot" boot 4 h 18456 */
	{.type FromH0, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 18464 */
	{.type FromH0, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 18472 */
/* 			; s0 puts FFEND on the stack *//* 			; no args */	{.type FromH0, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18480 */
	{.type FromH0, {.p C_parenabort}, .src = "dd C_parenabort ; ( (abort) -- )"},		/* dd C_parenabort ; ( (abort) -- ) 18488 */
	{.type FromH0, {.p MV_Abortvec}, .src = "dd MV_Abortvec	; variable that puts (abort) code address on the stack"},		/* dd MV_Abortvec	; variable that puts (abort) code address on the stack 18496 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable abortvec = (abort) code address"},		/* dd M_store	; variable abortvec = (abort) code address 18504 */
	{.type FromH0, {.p M_Wordb}, .src = "dd M_Wordb	; variable puts address of wordbuffer on the top of stack"},		/* dd M_Wordb	; variable puts address of wordbuffer on the top of stack 18512 */
	{.type FromH0, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf ; variable wordbuf"},		/* dd MV_Wordbuf ; variable wordbuf 18520 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable wordbuf = address of wordbuffer"},		/* dd M_store	; variable wordbuf = address of wordbuffer 18528 */
	{.type FromH0, {.p M_Tib}, .src = "dd M_Tib	; constant puts address of tibuffer on the top of stack"},		/* dd M_Tib	; constant puts address of tibuffer on the top of stack 18536 */
	{.type FromH0, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf	; variable sourcebuf"},		/* dd MV_Sourcebuf	; variable sourcebuf 18544 */
	{.type FromH0, {.p M_store}, .src = "dd M_store	; variable sourcebuf = address of tibuffer"},		/* dd M_store	; variable sourcebuf = address of tibuffer 18552 */
	{.type FromH0, {.p M_Dp}, .src = "dd M_Dp"},		/* dd M_Dp 18560 */
	{.type FromH0, {.p MV_H0}, .src = "dd MV_H0	; H0 = here at startup"},		/* dd MV_H0	; H0 = here at startup 18568 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18576 */
	{.type FromH0, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 18584 */
	{.type FromH0, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 18592 */
	{.type FromH0, {.p M_store}, .src = "dd M_store     ; stdin = 0"},		/* dd M_store     ; stdin = 0 18600 */
	{.type FromH0, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 18608 */
	{.type FromH0, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 18616 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18624 */
	{.type FromH0, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 18632 */
	{.type FromH0, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 18640 */
	{.type FromH0, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18648 */
	{.type FromH0, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 18656 */
	{.type FromH0, {.p C_off}, .src = "dd C_off	; off stores 0 at state"},		/* dd C_off	; off stores 0 at state 18664 */
	{.type FromH0, {.p C_decimal}, .src = "dd C_decimal	; decimal sets base = 10"},		/* dd C_decimal	; decimal sets base = 10 18672 */
	{.type FromH0, {.p C_quit}, .src = "dd C_quit	; quit"},		/* dd C_quit	; quit 18680 */
	{.type FromH0, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18688 */
	{.type Chars, {.str "unable to restore input"}},		/* 18712 */
	{.type Chars, {.str " Q?"}},		/* 18716 */
	{.type Chars, {.str " stack underflow"}},		/* 18733 */
	{.type Chars, {.str " I?"}},		/* 18737 */
	{.type Chars, {.str " C?"}},		/* 18741 */
	{.type Chars, {.str "I/O error"}},		/* 18751 */
	{.type Chars, {.str "uninitialized execution vector"}},		/* 18782 */
	{.type Chars, {.str " ok"}},		/* 18786 */
};

