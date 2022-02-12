/*
 * Forth dictionary
 */
enum {
	Header,
	IHeader,	/* Immediate dictionary definition */
	Absolute,
	FromDictionary,
	FromH0,
	FromV0,
	Byte,	/* obsolete, all are counted strings now */
	Chars,
	Here,
	There,
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
		s8 b;
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
	M_stackptr = 1256,
	M_sysbind = 1280,
	M_sysclose = 1312,
	M_syscreate = 1344,
	M_sysmount = 1376,
	M_sysopen = 1400,
	M_sysread = 1424,
	M_sysseek = 1448,
	M_syswrite = 1480,
	MC_STDIN = 1504,
	MC_STDOUT = 1536,
	MC_STDERR = 1568,
	MC_WORDNUM = 1600,
	MC_LINENUM = 1632,
	MC_DOUBLEQUOTENUM = 1672,
	MC_CLOSEPARENNUM = 1712,
	MC_NBUFFERS = 1752,
	MV_Dp = 1784,
	MV_Dtop = 1816,
	MV_Vp = 1848,
	MV_Pid = 1880,
	MV_Parentpid = 1912,
	MV_S0 = 1944,
	MV_Wordb = 1976,
	MV_Tib = 2008,
	MV_Argsfilename = 2048,
	MV_Iobuf = 2080,
	MV_Findadr = 2112,
	MV_Searchlen = 2152,
	MV_Base = 2184,
	MV_toNum = 2216,
	MV_State = 2248,
	MV_Abortvec = 2288,
	MV_Infd = 2320,
	MV_Outfd = 2352,
	MV_Errfd = 2384,
	MV_Eof = 2416,
	MV_Ninputs = 2448,
	MV_H0 = 2480,
	MV_Bufferfds = 2520,
	MV_Bufferfilenames = 2560,
	C_false = 2592,
	C_true = 2640,
	C_bl = 2688,
	C_on = 2736,
	C_off = 2800,
	C_tobody = 2864,
	C_aligned = 2920,
	C_cells = 3000,
	C_cells_plus = 3056,
	C_cell_plus = 3104,
	C_depth = 3160,
	C_nip = 3264,
	C_rot = 3312,
	C_2drop = 3376,
	C_2dup = 3424,
	C_2nip = 3472,
	C_2swap = 3520,
	C_qdup = 3584,
	L_C_qdup = 3656,
	C_pick = 3680,
	L_C_pick = 3784,
	L_C_pick_1 = 3792,
	C_tuck = 3816,
	C_divides = 3880,
	C_plusstore = 3928,
	C_invert = 4008,
	C_mod = 4064,
	C_1plus = 4112,
	C_1minus = 4168,
	C_negate = 4224,
	C_2multiplies = 4288,
	C_2divides = 4344,
	C_0eq = 4400,
	C_0lt = 4456,
	C_0gt = 4512,
	C_neq = 4568,
	C_0neq = 4616,
	C_max = 4672,
	L_C_max = 4736,
	L_C_max_1 = 4744,
	C_min = 4768,
	L_C_min = 4832,
	L_C_min_1 = 4840,
	C_signum = 4864,
	L_C_signum = 4944,
	L_C_signum_2 = 5000,
	L_C_signum_3 = 5016,
	L_C_signum_1 = 5016,
	C_within = 5040,
	C_abs = 5144,
	L_C_abs = 5192,
	C_emit = 5216,
	C_type = 5320,
	C_cr = 5416,
	C_space = 5472,
	C_emits = 5520,
	L_C_emits = 5528,
	L_C_emits_1 = 5592,
	C_spaces = 5624,
	C_count = 5680,
	C_compare = 5824,
	L_C_compare = 5896,
	L_C_compare_1 = 6032,
	C_erase = 6112,
	L_C_erase = 6144,
	C_fill = 6232,
	L_C_fill = 6272,
	C_blank = 6360,
	C_search = 6408,
	L_C_search = 6512,
	L_C_search_1 = 6696,
	C_here = 6760,
	C_there = 6808,
	C_comma = 6856,
	C_c = 6936,
	C_allot = 7016,
	C_vallot = 7064,
	C_pad = 7112,
	C_align = 7176,
	C_unused = 7240,
	C_fromhash = 7304,
	C_hash = 7384,
	L_C_hash = 7536,
	L_C_hash_1 = 7560,
	C_hashs = 7640,
	L_C_hashs = 7648,
	L_C_hashs_1 = 7696,
	C_hashfrom = 7720,
	C_hold = 7832,
	C_sign = 7936,
	L_C_sign = 7992,
	C_paren_dot_paren = 8016,
	C_dot = 8104,
	C_dotr = 8160,
	C_hex = 8320,
	C_decimal = 8384,
	C_digit = 8448,
	L_C_digit = 8560,
	L_C_digit_2 = 8664,
	L_C_digit_4 = 8768,
	L_C_digit_5 = 8792,
	L_C_digit_3 = 8792,
	L_C_digit_1 = 8792,
	L_C_digit_6 = 8864,
	L_C_digit_7 = 8880,
	C_number = 8904,
	L_C_number = 9040,
	L_C_number_1 = 9072,
	L_C_number_2 = 9136,
	L_C_number_3 = 9240,
	L_C_number_4 = 9296,
	C_abort = 9384,
	C_bufferfilename_store = 9448,
	C_toword = 9512,
	C_wordfd_fetch = 9568,
	C_wordfd_store = 9624,
	C_wordfilename_fetch = 9688,
	C_wordfilename_store = 9752,
	C_toline = 9808,
	C_linefd_fetch = 9864,
	C_linefd_store = 9920,
	C_linefilename_fetch = 9984,
	C_linefilename_store = 10048,
	C_todoublequote = 10112,
	C_doublequotefd_fetch = 10176,
	C_doublequotefd_store = 10240,
	C_doublequotefilename_fetch = 10312,
	C_doublequotefilename_store = 10384,
	C_tocloseparen = 10448,
	C_closeparenfd_fetch = 10512,
	C_closeparenfd_store = 10576,
	C_closeparenfilename_fetch = 10648,
	C_closeparenfilename_store = 10720,
	C_stdinput = 10784,
	L_C_stdinput = 10856,
	C_args = 10976,
	L_C_args_read = 11048,
	C_input_fetch = 11136,
	L_C_input_fetch = 11184,
	C_input_store = 11368,
	L_C_input_store = 11496,
	L_C_input_store_1 = 11584,
	C_close_input = 11624,
	L_C_close_input = 11672,
	C_restore_input = 11904,
	L_restore_input = 12032,
	C_buffername = 12064,
	C_get = 12416,
	L_C_get_store = 12672,
	L_C_get = 12720,
	L_C_get_1 = 12856,
	L_C_get_2 = 12952,
	L_C_get_3 = 13056,
	C_parse = 13080,
	L_C_parse_1 = 13240,
	C_word = 13312,
	C_line = 13368,
	C_doublequote = 13424,
	C_counted_doublequote = 13480,
	C_closeparen = 13544,
	C_findname = 13600,
	L_C_findname = 13640,
	L_C_findname_2 = 13752,
	L_C_findname_4 = 13880,
	L_C_findname_3 = 13888,
	L_C_findname_1 = 13904,
	C_find = 13952,
	L_C_find_1 = 14144,
	L_C_find_2 = 14160,
	L_C_find = 14184,
	L_C_find_3 = 14192,
	C_single_quote = 14216,
	L_C_single_quote = 14336,
	C_qstack = 14360,
	L_C_qstack = 14456,
	C_interpret = 14528,
	L_C_interpret = 14536,
	L_C_interpret_2 = 14600,
	L_C_interpret_4 = 14704,
	L_C_interpret_3 = 14704,
	C_create = 14744,
	C_variable = 14984,
	C_constant = 15080,
	C_immediate = 15208,
	C_tocfa = 15320,
	C_compile = 15400,
	L_C_compile_1 = 15528,
	L_C_compile_2 = 15544,
	L_C_compile = 15560,
	L_C_compile_4 = 15680,
	L_C_compile_6 = 15712,
	L_C_compile_3 = 15712,
	C_close_bracket = 15736,
	L_C_close_bracket = 15760,
	L_C_close_bracket_1 = 15840,
	L_C_close_bracket_2 = 15864,
	L_C_close_bracket_3 = 15896,
	CI_open_bracket = 15920,
	C_smudge = 15968,
	C_reveal = 16080,
	C_colon = 16200,
	CI_semicolon = 16328,
	CI_recurse = 16408,
	C_char = 16480,
	C_literal = 16536,
	C_sliteral = 16608,
	C_string = 16760,
	CI_char_brackets = 16872,
	CI_quote_brackets = 16936,
	CI_openparen = 16984,
	CI_backslash = 17032,
	C_qabort_parens = 17080,
	L_C_qabort_parens = 17160,
	L_C_qabort_parens_1 = 17168,
	CI_abort_double_quote = 17192,
	C_double_quote = 17256,
	C_cdouble_quote = 17368,
	CI_sdouble_quote = 17488,
	CI_dotstr = 17528,
	CI_if = 17592,
	CI_else = 17680,
	CI_then = 17808,
	CI_begin = 17864,
	CI_again = 17904,
	CI_until = 17968,
	CI_while = 18032,
	CI_repeat = 18120,
	CI_do = 18216,
	CI_loop = 18296,
	L234 = 18384,
	CI_ploop = 18408,
	L236 = 18496,
	C_wo = 18520,
	C_ro = 18616,
	C_rw = 18664,
	C_cstring = 18712,
	C_cstring0 = 18896,
	C_cstring1 = 18960,
	C_open_file = 19024,
	C_close_file = 19128,
	C_read_file = 19184,
	C_write_file = 19280,
	C_reposition_file = 19368,
	C_qfcheck = 19448,
	L246 = 19536,
	C_create_file = 19568,
	C_bye = 19840,
	C_include = 19896,
	C_crash = 20008,
	C_quit = 20088,
	L_C_quit = 20112,
	C_parenabort = 20168,
	C_initialize = 20440,
	L_C_initialize = 20488,
	L_C_initialize_1 = 20624,
	C_boot = 20840,
	L120 = 21064,
	L121 = 21072,
	L122 = 21080,
	L123 = 21088,
	L124 = 21104,
	L137 = 21120,
	L140 = 21144,
	L141 = 21168,
	L170 = 21192,
	L173 = 21200,
	L180 = 21224,
	L_C_compile_5 = 21232,
	L247 = 21240,
	L251 = 21256,
	L255 = 21288,
	L_C_get_too_long = 21296,
	L305 = 21352,
	L_C_long_word = 21368,
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
extern void *doinit(void);
extern void *multiply(void);
extern void *colon(void);
extern void *less(void);
extern void *lshift(void);
extern void *sysopen(void);
extern void *plus(void);
extern void *sysclose(void);
extern void *jump(void);
extern void *fthdump(void);
extern void *rshift(void);
extern void *cstore(void);
extern void *store(void);
extern void *cmove(void);
extern void *binor(void);
extern void *unloop(void);
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
	{.type Here, {.p 24 }},	/* 24 0 */
	{.type There, {.p 0 }},	/* 24 0 */
	{.type Here, {.p 24 }},	/* 24 0 */
	{.type There, {.p 0 }},	/* 24 0 */
	{.type Header, {.hdr { 1, "!", /* M_store = 40 */ store }}}, /* MENTRY "!" store 1 h 48 */
	{.type Here, {.p 48 }},	/* 48 0 */
	{.type There, {.p 0 }},	/* 48 0 */
	{.type Here, {.p 48 }},	/* 48 0 */
	{.type There, {.p 0 }},	/* 48 0 */
	{.type Header, {.hdr { 2, "c@", /* M_cfetch = 64 */ cfetch }}}, /* MENTRY "c@" cfetch 2 h 72 */
	{.type Here, {.p 72 }},	/* 72 0 */
	{.type There, {.p 0 }},	/* 72 0 */
	{.type Here, {.p 72 }},	/* 72 0 */
	{.type There, {.p 0 }},	/* 72 0 */
	{.type Header, {.hdr { 2, "c!", /* M_cstore = 88 */ cstore }}}, /* MENTRY "c!" cstore 2 h 96 */
	{.type Here, {.p 96 }},	/* 96 0 */
	{.type There, {.p 0 }},	/* 96 0 */
	{.type Here, {.p 96 }},	/* 96 0 */
	{.type There, {.p 0 }},	/* 96 0 */
	{.type Header, {.hdr { 4, "mmap", /* M_mmap = 112 */ mmap }}}, /* MENTRY "mmap" mmap 4 h 120 */
	{.type Here, {.p 120 }},	/* 120 0 */
	{.type There, {.p 0 }},	/* 120 0 */
	{.type Here, {.p 120 }},	/* 120 0 */
	{.type There, {.p 0 }},	/* 120 0 */
	{.type Header, {.hdr { 4, "halt", /* M_terminate = 136 */ terminate }}}, /* MENTRY "halt" terminate 4 h 144 */
	{.type Here, {.p 144 }},	/* 144 0 */
	{.type There, {.p 0 }},	/* 144 0 */
	{.type Here, {.p 144 }},	/* 144 0 */
	{.type There, {.p 0 }},	/* 144 0 */
	{.type Header, {.hdr { 4, "dump", /* M_fthdump = 160 */ fthdump }}}, /* MENTRY "dump" fthdump 4 h 168 */
	{.type Here, {.p 168 }},	/* 168 0 */
	{.type There, {.p 0 }},	/* 168 0 */
	{.type Here, {.p 168 }},	/* 168 0 */
	{.type There, {.p 0 }},	/* 168 0 */
	{.type Header, {.hdr { 5, "clear", /* M_clear = 184 */ clear }}}, /* MENTRY "clear" clear 5 h 192 */
	{.type Here, {.p 192 }},	/* 192 0 */
	{.type There, {.p 0 }},	/* 192 0 */
	{.type Here, {.p 192 }},	/* 192 0 */
	{.type There, {.p 0 }},	/* 192 0 */
	{.type Header, {.hdr { 5, "reset", /* M_reset = 208 */ reset }}}, /* MENTRY "reset" reset 5 h 216 */
	{.type Here, {.p 216 }},	/* 216 0 */
	{.type There, {.p 0 }},	/* 216 0 */
	{.type Here, {.p 216 }},	/* 216 0 */
	{.type There, {.p 0 }},	/* 216 0 */
	{.type Header, {.hdr { 4, "exit", /* M_exitcolon = 232 */ exitcolon }}}, /* MENTRY "exit" exitcolon 4 h 240 */
	{.type Here, {.p 240 }},	/* 240 0 */
	{.type There, {.p 0 }},	/* 240 0 */
	{.type Here, {.p 240 }},	/* 240 0 */
	{.type There, {.p 0 }},	/* 240 0 */
	{.type Header, {.hdr { 9, "(literal)", /* M_literal = 264 */ literal }}}, /* MENTRY "(literal)" literal 9 h 272 */
	{.type Here, {.p 272 }},	/* 272 0 */
	{.type There, {.p 0 }},	/* 272 0 */
	{.type Here, {.p 272 }},	/* 272 0 */
	{.type There, {.p 0 }},	/* 272 0 */
	{.type Header, {.hdr { 10, "(sliteral)", /* M_sliteral = 296 */ sliteral }}}, /* MENTRY "(sliteral)" sliteral 10 h 304 */
	{.type Here, {.p 304 }},	/* 304 0 */
	{.type There, {.p 0 }},	/* 304 0 */
	{.type Here, {.p 304 }},	/* 304 0 */
	{.type There, {.p 0 }},	/* 304 0 */
	{.type Header, {.hdr { 4, "(do)", /* M_doinit = 320 */ doinit }}}, /* MENTRY "(do)" doinit 4 h 328 */
	{.type Here, {.p 328 }},	/* 328 0 */
	{.type There, {.p 0 }},	/* 328 0 */
	{.type Here, {.p 328 }},	/* 328 0 */
	{.type There, {.p 0 }},	/* 328 0 */
	{.type Header, {.hdr { 6, "(loop)", /* M_doloop = 344 */ doloop }}}, /* MENTRY "(loop)" doloop 6 h 352 */
	{.type Here, {.p 352 }},	/* 352 0 */
	{.type There, {.p 0 }},	/* 352 0 */
	{.type Here, {.p 352 }},	/* 352 0 */
	{.type There, {.p 0 }},	/* 352 0 */
	{.type Header, {.hdr { 7, "(+loop)", /* M_doploop = 368 */ doploop }}}, /* MENTRY "(+loop)" doploop 7 h 376 */
	{.type Here, {.p 376 }},	/* 376 0 */
	{.type There, {.p 0 }},	/* 376 0 */
	{.type Here, {.p 376 }},	/* 376 0 */
	{.type There, {.p 0 }},	/* 376 0 */
	{.type Header, {.hdr { 2, "r@", /* M_rfetch = 392 */ rfetch }}}, /* MENTRY "r@" rfetch 2 h 400 */
	{.type Here, {.p 400 }},	/* 400 0 */
	{.type There, {.p 0 }},	/* 400 0 */
	{.type Here, {.p 400 }},	/* 400 0 */
	{.type There, {.p 0 }},	/* 400 0 */
	{.type Header, {.hdr { 2, "r>", /* M_rpop = 416 */ rpop }}}, /* MENTRY "r>" rpop 2 h 424 */
	{.type Here, {.p 424 }},	/* 424 0 */
	{.type There, {.p 0 }},	/* 424 0 */
	{.type Here, {.p 424 }},	/* 424 0 */
	{.type There, {.p 0 }},	/* 424 0 */
	{.type Header, {.hdr { 2, ">r", /* M_rpush = 440 */ rpush }}}, /* MENTRY ">r" rpush 2 h 448 */
	{.type Here, {.p 448 }},	/* 448 0 */
	{.type There, {.p 0 }},	/* 448 0 */
	{.type Here, {.p 448 }},	/* 448 0 */
	{.type There, {.p 0 }},	/* 448 0 */
	{.type Header, {.hdr { 1, "i", /* M_i = 464 */ i }}}, /* MENTRY "i" i 1 h 472 */
	{.type Here, {.p 472 }},	/* 472 0 */
	{.type There, {.p 0 }},	/* 472 0 */
	{.type Here, {.p 472 }},	/* 472 0 */
	{.type There, {.p 0 }},	/* 472 0 */
	{.type Header, {.hdr { 1, "j", /* M_j = 488 */ j }}}, /* MENTRY "j" j 1 h 496 */
	{.type Here, {.p 496 }},	/* 496 0 */
	{.type There, {.p 0 }},	/* 496 0 */
	{.type Here, {.p 496 }},	/* 496 0 */
	{.type There, {.p 0 }},	/* 496 0 */
	{.type Header, {.hdr { 1, "+", /* M_plus = 512 */ plus }}}, /* MENTRY "+" plus 1 h 520 */
	{.type Here, {.p 520 }},	/* 520 0 */
	{.type There, {.p 0 }},	/* 520 0 */
	{.type Here, {.p 520 }},	/* 520 0 */
	{.type There, {.p 0 }},	/* 520 0 */
	{.type Header, {.hdr { 1, "-", /* M_minus = 536 */ minus }}}, /* MENTRY "-" minus 1 h 544 */
	{.type Here, {.p 544 }},	/* 544 0 */
	{.type There, {.p 0 }},	/* 544 0 */
	{.type Here, {.p 544 }},	/* 544 0 */
	{.type There, {.p 0 }},	/* 544 0 */
	{.type Header, {.hdr { 1, "*", /* M_multiply = 560 */ multiply }}}, /* MENTRY "*" multiply 1 h 568 */
	{.type Here, {.p 568 }},	/* 568 0 */
	{.type There, {.p 0 }},	/* 568 0 */
	{.type Here, {.p 568 }},	/* 568 0 */
	{.type There, {.p 0 }},	/* 568 0 */
	{.type Header, {.hdr { 4, "(if)", /* M_cjump = 584 */ cjump }}}, /* MENTRY "(if)" cjump 4 h 592 */
	{.type Here, {.p 592 }},	/* 592 0 */
	{.type There, {.p 0 }},	/* 592 0 */
	{.type Here, {.p 592 }},	/* 592 0 */
	{.type There, {.p 0 }},	/* 592 0 */
	{.type Header, {.hdr { 6, "(else)", /* M_jump = 608 */ jump }}}, /* MENTRY "(else)" jump 6 h 616 */
	{.type Here, {.p 616 }},	/* 616 0 */
	{.type There, {.p 0 }},	/* 616 0 */
	{.type Here, {.p 616 }},	/* 616 0 */
	{.type There, {.p 0 }},	/* 616 0 */
	{.type Header, {.hdr { 4, "/mod", /* M_slashmod = 632 */ slashmod }}}, /* MENTRY "/mod" slashmod 4 h 640 */
	{.type Here, {.p 640 }},	/* 640 0 */
	{.type There, {.p 0 }},	/* 640 0 */
	{.type Here, {.p 640 }},	/* 640 0 */
	{.type There, {.p 0 }},	/* 640 0 */
	{.type Header, {.hdr { 5, "u/mod", /* M_uslashmod = 656 */ uslashmod }}}, /* MENTRY "u/mod" uslashmod 5 h 664 */
	{.type Here, {.p 664 }},	/* 664 0 */
	{.type There, {.p 0 }},	/* 664 0 */
	{.type Here, {.p 664 }},	/* 664 0 */
	{.type There, {.p 0 }},	/* 664 0 */
	{.type Header, {.hdr { 3, "and", /* M_binand = 680 */ binand }}}, /* MENTRY "and" binand 3 h 688 */
	{.type Here, {.p 688 }},	/* 688 0 */
	{.type There, {.p 0 }},	/* 688 0 */
	{.type Here, {.p 688 }},	/* 688 0 */
	{.type There, {.p 0 }},	/* 688 0 */
	{.type Header, {.hdr { 2, "or", /* M_binor = 704 */ binor }}}, /* MENTRY "or" binor 2 h 712 */
	{.type Here, {.p 712 }},	/* 712 0 */
	{.type There, {.p 0 }},	/* 712 0 */
	{.type Here, {.p 712 }},	/* 712 0 */
	{.type There, {.p 0 }},	/* 712 0 */
	{.type Header, {.hdr { 3, "xor", /* M_binxor = 728 */ binxor }}}, /* MENTRY "xor" binxor 3 h 736 */
	{.type Here, {.p 736 }},	/* 736 0 */
	{.type There, {.p 0 }},	/* 736 0 */
	{.type Here, {.p 736 }},	/* 736 0 */
	{.type There, {.p 0 }},	/* 736 0 */
	{.type Header, {.hdr { 4, "swap", /* M_xswap = 752 */ xswap }}}, /* MENTRY "swap" xswap 4 h 760 */
	{.type Here, {.p 760 }},	/* 760 0 */
	{.type There, {.p 0 }},	/* 760 0 */
	{.type Here, {.p 760 }},	/* 760 0 */
	{.type There, {.p 0 }},	/* 760 0 */
	{.type Header, {.hdr { 4, "drop", /* M_drop = 776 */ drop }}}, /* MENTRY "drop" drop 4 h 784 */
	{.type Here, {.p 784 }},	/* 784 0 */
	{.type There, {.p 0 }},	/* 784 0 */
	{.type Here, {.p 784 }},	/* 784 0 */
	{.type There, {.p 0 }},	/* 784 0 */
	{.type Header, {.hdr { 3, "dup", /* M_dup = 800 */ dup }}}, /* MENTRY "dup" dup 3 h 808 */
	{.type Here, {.p 808 }},	/* 808 0 */
	{.type There, {.p 0 }},	/* 808 0 */
	{.type Here, {.p 808 }},	/* 808 0 */
	{.type There, {.p 0 }},	/* 808 0 */
	{.type Header, {.hdr { 4, "over", /* M_over = 824 */ over }}}, /* MENTRY "over" over 4 h 832 */
	{.type Here, {.p 832 }},	/* 832 0 */
	{.type There, {.p 0 }},	/* 832 0 */
	{.type Here, {.p 832 }},	/* 832 0 */
	{.type There, {.p 0 }},	/* 832 0 */
	{.type Header, {.hdr { 1, "=", /* M_equal = 848 */ equal }}}, /* MENTRY "=" equal 1 h 856 */
	{.type Here, {.p 856 }},	/* 856 0 */
	{.type There, {.p 0 }},	/* 856 0 */
	{.type Here, {.p 856 }},	/* 856 0 */
	{.type There, {.p 0 }},	/* 856 0 */
	{.type Header, {.hdr { 1, ">", /* M_greater = 872 */ greater }}}, /* MENTRY ">" greater 1 h 880 */
	{.type Here, {.p 880 }},	/* 880 0 */
	{.type There, {.p 0 }},	/* 880 0 */
	{.type Here, {.p 880 }},	/* 880 0 */
	{.type There, {.p 0 }},	/* 880 0 */
	{.type Header, {.hdr { 1, "<", /* M_less = 896 */ less }}}, /* MENTRY "<" less 1 h 904 */
	{.type Here, {.p 904 }},	/* 904 0 */
	{.type There, {.p 0 }},	/* 904 0 */
	{.type Here, {.p 904 }},	/* 904 0 */
	{.type There, {.p 0 }},	/* 904 0 */
	{.type Header, {.hdr { 6, "lshift", /* M_lshift = 920 */ lshift }}}, /* MENTRY "lshift" lshift 6 h 928 */
	{.type Here, {.p 928 }},	/* 928 0 */
	{.type There, {.p 0 }},	/* 928 0 */
	{.type Here, {.p 928 }},	/* 928 0 */
	{.type There, {.p 0 }},	/* 928 0 */
	{.type Header, {.hdr { 6, "rshift", /* M_rshift = 944 */ rshift }}}, /* MENTRY "rshift" rshift 6 h 952 */
	{.type Here, {.p 952 }},	/* 952 0 */
	{.type There, {.p 0 }},	/* 952 0 */
	{.type Here, {.p 952 }},	/* 952 0 */
	{.type There, {.p 0 }},	/* 952 0 */
	{.type Header, {.hdr { 7, "rshifta", /* M_rshifta = 968 */ rshifta }}}, /* MENTRY "rshifta" rshifta 7 h 976 */
	{.type Here, {.p 976 }},	/* 976 0 */
	{.type There, {.p 0 }},	/* 976 0 */
	{.type Here, {.p 976 }},	/* 976 0 */
	{.type There, {.p 0 }},	/* 976 0 */
	{.type Header, {.hdr { 7, "execute", /* M_execute = 992 */ execute }}}, /* MENTRY "execute" execute 7 h 1000 */
	{.type Here, {.p 1000 }},	/* 1000 0 */
	{.type There, {.p 0 }},	/* 1000 0 */
	{.type Here, {.p 1000 }},	/* 1000 0 */
	{.type There, {.p 0 }},	/* 1000 0 */
	{.type Header, {.hdr { 6, "unloop", /* M_unloop = 1016 */ unloop }}}, /* MENTRY "unloop" unloop 6 h 1024 */
	{.type Here, {.p 1024 }},	/* 1024 0 */
	{.type There, {.p 0 }},	/* 1024 0 */
	{.type Here, {.p 1024 }},	/* 1024 0 */
	{.type There, {.p 0 }},	/* 1024 0 */
	{.type Header, {.hdr { 5, "cmove", /* M_cmove = 1040 */ cmove }}}, /* MENTRY "cmove" cmove 5 h 1048 */
	{.type Here, {.p 1048 }},	/* 1048 0 */
	{.type There, {.p 0 }},	/* 1048 0 */
	{.type Here, {.p 1048 }},	/* 1048 0 */
	{.type There, {.p 0 }},	/* 1048 0 */
	{.type Header, {.hdr { 6, "cmove>", /* M_cmoveb = 1064 */ cmoveb }}}, /* MENTRY "cmove>" cmoveb 6 h 1072 */
	{.type Here, {.p 1072 }},	/* 1072 0 */
	{.type There, {.p 0 }},	/* 1072 0 */
	{.type Here, {.p 1072 }},	/* 1072 0 */
	{.type There, {.p 0 }},	/* 1072 0 */
	{.type Header, {.hdr { 10, "(variable)", /* M_variable = 1096 */ variable }}}, /* MENTRY "(variable)" variable 10 h 1104 */
	{.type Here, {.p 1104 }},	/* 1104 0 */
	{.type There, {.p 0 }},	/* 1104 0 */
	{.type Here, {.p 1104 }},	/* 1104 0 */
	{.type There, {.p 0 }},	/* 1104 0 */
	{.type Header, {.hdr { 10, "(constant)", /* M_constant = 1128 */ constant }}}, /* MENTRY "(constant)" constant 10 h 1136 */
	{.type Here, {.p 1136 }},	/* 1136 0 */
	{.type There, {.p 0 }},	/* 1136 0 */
	{.type Here, {.p 1136 }},	/* 1136 0 */
	{.type There, {.p 0 }},	/* 1136 0 */
	{.type Header, {.hdr { 3, "(:)", /* M_colon = 1152 */ colon }}}, /* MENTRY "(:)" colon 3 h 1160 */
	{.type Here, {.p 1160 }},	/* 1160 0 */
	{.type There, {.p 0 }},	/* 1160 0 */
	{.type Here, {.p 1160 }},	/* 1160 0 */
	{.type There, {.p 0 }},	/* 1160 0 */
	{.type Header, {.hdr { 6, "(does)", /* M_dodoes = 1176 */ dodoes }}}, /* MENTRY "(does)" dodoes 6 h 1184 */
	{.type Here, {.p 1184 }},	/* 1184 0 */
	{.type There, {.p 0 }},	/* 1184 0 */
	{.type Here, {.p 1184 }},	/* 1184 0 */
	{.type There, {.p 0 }},	/* 1184 0 */
	{.type Header, {.hdr { 3, "cas", /* M_cas = 1200 */ cas }}}, /* MENTRY "cas" cas 3 h 1208 */
	{.type Here, {.p 1208 }},	/* 1208 0 */
	{.type There, {.p 0 }},	/* 1208 0 */
	{.type Here, {.p 1208 }},	/* 1208 0 */
	{.type There, {.p 0 }},	/* 1208 0 */
	{.type Header, {.hdr { 10, "(deferred)", /* M_deferred = 1232 */ deferred }}}, /* MENTRY "(deferred)" deferred 10 h 1240 */
	{.type Here, {.p 1240 }},	/* 1240 0 */
	{.type There, {.p 0 }},	/* 1240 0 */
	{.type Here, {.p 1240 }},	/* 1240 0 */
	{.type There, {.p 0 }},	/* 1240 0 */
	{.type Header, {.hdr { 2, "s@", /* M_stackptr = 1256 */ stackptr }}}, /* MENTRY "s@" stackptr 2	; puts PSP on stack. Not a variable hence lower case. h 1264 */
	{.type Here, {.p 1264 }},	/* 1264 0 */
	{.type There, {.p 0 }},	/* 1264 0 */
	{.type Here, {.p 1264 }},	/* 1264 0 */
	{.type There, {.p 0 }},	/* 1264 0 */
	{.type Here, {.p 1264 }},	/* 1264 0 */
	{.type There, {.p 0 }},	/* 1264 0 */
	{.type Header, {.hdr { 7, "sysbind", /* M_sysbind = 1280 */ sysbind }}}, /* MENTRY "sysbind" sysbind 7 h 1288 */
	{.type Here, {.p 1288 }},	/* 1288 0 */
	{.type There, {.p 0 }},	/* 1288 0 */
	{.type Here, {.p 1288 }},	/* 1288 0 */
	{.type There, {.p 0 }},	/* 1288 0 */
	{.type Header, {.hdr { 8, "sysclose", /* M_sysclose = 1312 */ sysclose }}}, /* MENTRY "sysclose" sysclose 8 h 1320 */
	{.type Here, {.p 1320 }},	/* 1320 0 */
	{.type There, {.p 0 }},	/* 1320 0 */
	{.type Here, {.p 1320 }},	/* 1320 0 */
	{.type There, {.p 0 }},	/* 1320 0 */
	{.type Header, {.hdr { 9, "syscreate", /* M_syscreate = 1344 */ syscreate }}}, /* MENTRY "syscreate" syscreate 9 h 1352 */
	{.type Here, {.p 1352 }},	/* 1352 0 */
	{.type There, {.p 0 }},	/* 1352 0 */
	{.type Here, {.p 1352 }},	/* 1352 0 */
	{.type There, {.p 0 }},	/* 1352 0 */
	{.type Header, {.hdr { 8, "sysmount", /* M_sysmount = 1376 */ sysmount }}}, /* MENTRY "sysmount" sysmount 8 h 1384 */
	{.type Here, {.p 1384 }},	/* 1384 0 */
	{.type There, {.p 0 }},	/* 1384 0 */
	{.type Here, {.p 1384 }},	/* 1384 0 */
	{.type There, {.p 0 }},	/* 1384 0 */
	{.type Header, {.hdr { 7, "sysopen", /* M_sysopen = 1400 */ sysopen }}}, /* MENTRY "sysopen" sysopen 7 h 1408 */
	{.type Here, {.p 1408 }},	/* 1408 0 */
	{.type There, {.p 0 }},	/* 1408 0 */
	{.type Here, {.p 1408 }},	/* 1408 0 */
	{.type There, {.p 0 }},	/* 1408 0 */
	{.type Header, {.hdr { 7, "sysread", /* M_sysread = 1424 */ sysread }}}, /* MENTRY "sysread" sysread 7 h 1432 */
	{.type Here, {.p 1432 }},	/* 1432 0 */
	{.type There, {.p 0 }},	/* 1432 0 */
	{.type Here, {.p 1432 }},	/* 1432 0 */
	{.type There, {.p 0 }},	/* 1432 0 */
	{.type Header, {.hdr { 7, "sysseek", /* M_sysseek = 1448 */ sysseek }}}, /* MENTRY "sysseek" sysseek 7 h 1456 */
	{.type Here, {.p 1456 }},	/* 1456 0 */
	{.type There, {.p 0 }},	/* 1456 0 */
	{.type Here, {.p 1456 }},	/* 1456 0 */
	{.type There, {.p 0 }},	/* 1456 0 */
	{.type Header, {.hdr { 8, "syswrite", /* M_syswrite = 1480 */ syswrite }}}, /* MENTRY "syswrite" syswrite 8 h 1488 */
	{.type Here, {.p 1488 }},	/* 1488 0 */
	{.type There, {.p 0 }},	/* 1488 0 */
	{.type Here, {.p 1488 }},	/* 1488 0 */
	{.type There, {.p 0 }},	/* 1488 0 */
	{.type Here, {.p 1488 }},	/* 1488 0 */
	{.type There, {.p 0 }},	/* 1488 0 */
	{.type Header, {.hdr { 5, "STDIN", /* MC_STDIN = 1504 */ constant }}}, /* MCENTRY "STDIN" STDIN 5	0 ; 3 constants from here CAPITALS h 1512 */
	{.type Here, {.p 1512 }},	/* 1512 0 */
	{.type There, {.p 0 }},	/* 1512 0 */
	{.type Absolute, {.p 0}},		/* 1520 */
	{.type Here, {.p 1520 }},	/* 1520 0 */
	{.type There, {.p 0 }},	/* 1520 0 */
	{.type Header, {.hdr { 6, "STDOUT", /* MC_STDOUT = 1536 */ constant }}}, /* MCENTRY "STDOUT" STDOUT 6 1 h 1544 */
	{.type Here, {.p 1544 }},	/* 1544 0 */
	{.type There, {.p 0 }},	/* 1544 0 */
	{.type Absolute, {.p 1}},		/* 1552 */
	{.type Here, {.p 1552 }},	/* 1552 0 */
	{.type There, {.p 0 }},	/* 1552 0 */
	{.type Header, {.hdr { 6, "STDERR", /* MC_STDERR = 1568 */ constant }}}, /* MCENTRY "STDERR" STDERR 6 2 h 1576 */
	{.type Here, {.p 1576 }},	/* 1576 0 */
	{.type There, {.p 0 }},	/* 1576 0 */
	{.type Absolute, {.p 2}},		/* 1584 */
	{.type Here, {.p 1584 }},	/* 1584 0 */
	{.type There, {.p 0 }},	/* 1584 0 */
	{.type Here, {.p 1584 }},	/* 1584 0 */
	{.type There, {.p 0 }},	/* 1584 0 */
	{.type Header, {.hdr { 5, "WORD#", /* MC_WORDNUM = 1600 */ constant }}}, /* MCENTRY	"WORD#" WORDNUM 5 0 h 1608 */
	{.type Here, {.p 1608 }},	/* 1608 0 */
	{.type There, {.p 0 }},	/* 1608 0 */
	{.type Absolute, {.p 0}},		/* 1616 */
	{.type Here, {.p 1616 }},	/* 1616 0 */
	{.type There, {.p 0 }},	/* 1616 0 */
	{.type Header, {.hdr { 5, "LINE#", /* MC_LINENUM = 1632 */ constant }}}, /* MCENTRY	"LINE#" LINENUM 5 1 h 1640 */
	{.type Here, {.p 1640 }},	/* 1640 0 */
	{.type There, {.p 0 }},	/* 1640 0 */
	{.type Absolute, {.p 1}},		/* 1648 */
	{.type Here, {.p 1648 }},	/* 1648 0 */
	{.type There, {.p 0 }},	/* 1648 0 */
	{.type Header, {.hdr { 12, "DOUBLEQUOTE#", /* MC_DOUBLEQUOTENUM = 1672 */ constant }}}, /* MCENTRY	"DOUBLEQUOTE#" DOUBLEQUOTENUM 12 2 h 1680 */
	{.type Here, {.p 1680 }},	/* 1680 0 */
	{.type There, {.p 0 }},	/* 1680 0 */
	{.type Absolute, {.p 2}},		/* 1688 */
	{.type Here, {.p 1688 }},	/* 1688 0 */
	{.type There, {.p 0 }},	/* 1688 0 */
	{.type Header, {.hdr { 11, "CLOSEPAREN#", /* MC_CLOSEPARENNUM = 1712 */ constant }}}, /* MCENTRY	"CLOSEPAREN#" CLOSEPARENNUM 11 3 h 1720 */
	{.type Here, {.p 1720 }},	/* 1720 0 */
	{.type There, {.p 0 }},	/* 1720 0 */
	{.type Absolute, {.p 3}},		/* 1728 */
	{.type Here, {.p 1728 }},	/* 1728 0 */
	{.type There, {.p 0 }},	/* 1728 0 */
	{.type Header, {.hdr { 8, "#BUFFERS", /* MC_NBUFFERS = 1752 */ constant }}}, /* MCENTRY "#BUFFERS" NBUFFERS 8 16 h 1760 */
	{.type Here, {.p 1760 }},	/* 1760 0 */
	{.type There, {.p 0 }},	/* 1760 0 */
	{.type Absolute, {.p 16}},		/* 1768 */
	{.type Here, {.p 1768 }},	/* 1768 0 */
	{.type There, {.p 0 }},	/* 1768 0 */
	{.type Here, {.p 1768 }},	/* 1768 0 */
	{.type There, {.p 0 }},	/* 1768 0 */
/* ; put address of the defined location on the top of stack */	{.type Here, {.p 1768 }},	/* 1768 0 */
	{.type There, {.p 0 }},	/* 1768 0 */
/* ; cannot use H as it is nil in inferno, address where here (next available dictionary cell location) is stored */	{.type Here, {.p 1768 }},	/* 1768 0 */
	{.type There, {.p 0 }},	/* 1768 0 */
/* ; here = Dp @ */	{.type Here, {.p 1768 }},	/* 1768 0 */
	{.type There, {.p 0 }},	/* 1768 0 */
/* ; these memory locations (HERE, DTOP, etc.) are populated with values by the forth initializer */	{.type Here, {.p 1768 }},	/* 1768 0 */
	{.type There, {.p 0 }},	/* 1768 0 */
	{.type Header, {.hdr { 2, "Dp", /* MV_Dp = 1784 */ variable }}}, /* MVDENTRY "Dp" Dp 2 HERE		; here h 1792 */
	{.type Here, {.p 1792 }},	/* 1792 0 */
	{.type There, {.p 0 }},	/* 1792 0 */
	{.type FromH0, {.p HERE }},	/* 1800 0 */
	{.type Here, {.p 1800 }},	/* 1800 0 */
	{.type There, {.p 0 }},	/* 1800 0 */
	{.type Header, {.hdr { 4, "Dtop", /* MV_Dtop = 1816 */ variable }}}, /* MVDENTRY "Dtop" Dtop 4 DTOP	; last defined header h 1824 */
	{.type Here, {.p 1824 }},	/* 1824 0 */
	{.type There, {.p 0 }},	/* 1824 0 */
	{.type FromH0, {.p DTOP }},	/* 1832 0 */
	{.type Here, {.p 1832 }},	/* 1832 0 */
	{.type There, {.p 0 }},	/* 1832 0 */
	{.type Header, {.hdr { 2, "Vp", /* MV_Vp = 1848 */ variable }}}, /* MVDENTRY "Vp" Vp 2 THERE	; here of the variables space h 1856 */
	{.type Here, {.p 1856 }},	/* 1856 0 */
	{.type There, {.p 0 }},	/* 1856 0 */
	{.type FromH0, {.p THERE }},	/* 1864 0 */
	{.type Here, {.p 1864 }},	/* 1864 0 */
	{.type There, {.p 0 }},	/* 1864 0 */
	{.type Header, {.hdr { 3, "Pid", /* MV_Pid = 1880 */ variable }}}, /* MVDENTRY "Pid" Pid 3 FTHPID h 1888 */
	{.type Here, {.p 1888 }},	/* 1888 0 */
	{.type There, {.p 0 }},	/* 1888 0 */
	{.type FromH0, {.p FTHPID }},	/* 1896 0 */
	{.type Here, {.p 1896 }},	/* 1896 0 */
	{.type There, {.p 0 }},	/* 1896 0 */
	{.type Header, {.hdr { 4, "Parentpid", /* MV_Parentpid = 1912 */ variable }}}, /* MVDENTRY "Parentpid" Parentpid 4 FTHPARENTPID h 1920 */
	{.type Here, {.p 1920 }},	/* 1920 0 */
	{.type There, {.p 0 }},	/* 1920 0 */
	{.type FromH0, {.p FTHPARENTPID }},	/* 1928 0 */
	{.type Here, {.p 1928 }},	/* 1928 0 */
	{.type There, {.p 0 }},	/* 1928 0 */
/* ; the below memory locations are left alone as zeros by the initializer */	{.type Here, {.p 1928 }},	/* 1928 0 */
	{.type There, {.p 0 }},	/* 1928 0 */
	{.type Header, {.hdr { 2, "S0", /* MV_S0 = 1944 */ variable }}}, /* MVDENTRY "S0" S0 2 PSTACK h 1952 */
	{.type Here, {.p 1952 }},	/* 1952 0 */
	{.type There, {.p 0 }},	/* 1952 0 */
	{.type FromH0, {.p PSTACK }},	/* 1960 0 */
	{.type Here, {.p 1960 }},	/* 1960 0 */
	{.type There, {.p 0 }},	/* 1960 0 */
	{.type Header, {.hdr { 5, "Wordb", /* MV_Wordb = 1976 */ variable }}}, /* MVDENTRY "Wordb" Wordb 5 WORDB h 1984 */
	{.type Here, {.p 1984 }},	/* 1984 0 */
	{.type There, {.p 0 }},	/* 1984 0 */
	{.type FromH0, {.p WORDB }},	/* 1992 0 */
	{.type Here, {.p 1992 }},	/* 1992 0 */
	{.type There, {.p 0 }},	/* 1992 0 */
	{.type Header, {.hdr { 3, "Tib", /* MV_Tib = 2008 */ variable }}}, /* MVDENTRY "Tib" Tib 3 TIB h 2016 */
	{.type Here, {.p 2016 }},	/* 2016 0 */
	{.type There, {.p 0 }},	/* 2016 0 */
	{.type FromH0, {.p TIB }},	/* 2024 0 */
	{.type Here, {.p 2024 }},	/* 2024 0 */
	{.type There, {.p 0 }},	/* 2024 0 */
	{.type Header, {.hdr { 12, "Argsfilename", /* MV_Argsfilename = 2048 */ variable }}}, /* MVDENTRY "Argsfilename" Argsfilename 12 ARGSFILENAME ; counted string populated by forth starter from params h 2056 */
	{.type Here, {.p 2056 }},	/* 2056 0 */
	{.type There, {.p 0 }},	/* 2056 0 */
	{.type FromH0, {.p ARGSFILENAME }},	/* 2064 0 */
	{.type Here, {.p 2064 }},	/* 2064 0 */
	{.type There, {.p 0 }},	/* 2064 0 */
	{.type Here, {.p 2064 }},	/* 2064 0 */
	{.type There, {.p 0 }},	/* 2064 0 */
	{.type Header, {.hdr { 5, "Iobuf", /* MV_Iobuf = 2080 */ variable }}}, /* MVENTRY "Iobuf" Iobuf 5		; the values are not being used from the definition. All are initialized to 0. h 2088 */
	{.type Here, {.p 2088 }},	/* 2088 0 */
	{.type There, {.p 0 }},	/* 2088 0 */
	{.type FromV0, {.p 0 }},	/* 2096 0 */
	{.type Here, {.p 2096 }},	/* 2096 8 */
	{.type There, {.p 8 }},	/* 2096 8 */
	{.type Header, {.hdr { 7, "Findadr", /* MV_Findadr = 2112 */ variable }}}, /* MVENTRY "Findadr" Findadr 7 h 2120 */
	{.type Here, {.p 2120 }},	/* 2120 8 */
	{.type There, {.p 8 }},	/* 2120 8 */
	{.type FromV0, {.p 8 }},	/* 2128 8 */
	{.type Here, {.p 2128 }},	/* 2128 16 */
	{.type There, {.p 16 }},	/* 2128 16 */
	{.type Header, {.hdr { 9, "Searchlen", /* MV_Searchlen = 2152 */ variable }}}, /* MVENTRY "Searchlen" Searchlen 9 h 2160 */
	{.type Here, {.p 2160 }},	/* 2160 16 */
	{.type There, {.p 16 }},	/* 2160 16 */
	{.type FromV0, {.p 16 }},	/* 2168 16 */
	{.type Here, {.p 2168 }},	/* 2168 24 */
	{.type There, {.p 24 }},	/* 2168 24 */
	{.type Header, {.hdr { 4, "Base", /* MV_Base = 2184 */ variable }}}, /* MVENTRY "Base" Base 4 h 2192 */
	{.type Here, {.p 2192 }},	/* 2192 24 */
	{.type There, {.p 24 }},	/* 2192 24 */
	{.type FromV0, {.p 24 }},	/* 2200 24 */
	{.type Here, {.p 2200 }},	/* 2200 32 */
	{.type There, {.p 32 }},	/* 2200 32 */
	{.type Header, {.hdr { 4, ">Num", /* MV_toNum = 2216 */ variable }}}, /* MVENTRY ">Num" toNum 4 h 2224 */
	{.type Here, {.p 2224 }},	/* 2224 32 */
	{.type There, {.p 32 }},	/* 2224 32 */
	{.type FromV0, {.p 32 }},	/* 2232 32 */
	{.type Here, {.p 2232 }},	/* 2232 40 */
	{.type There, {.p 40 }},	/* 2232 40 */
	{.type Header, {.hdr { 5, "State", /* MV_State = 2248 */ variable }}}, /* MVENTRY "State" State 5 h 2256 */
	{.type Here, {.p 2256 }},	/* 2256 40 */
	{.type There, {.p 40 }},	/* 2256 40 */
	{.type FromV0, {.p 40 }},	/* 2264 40 */
	{.type Here, {.p 2264 }},	/* 2264 48 */
	{.type There, {.p 48 }},	/* 2264 48 */
	{.type Header, {.hdr { 8, "Abortvec", /* MV_Abortvec = 2288 */ variable }}}, /* MVENTRY "Abortvec" Abortvec 8	; not sure if these 3 can be constants instead? h 2296 */
	{.type Here, {.p 2296 }},	/* 2296 48 */
	{.type There, {.p 48 }},	/* 2296 48 */
	{.type FromV0, {.p 48 }},	/* 2304 48 */
	{.type Here, {.p 2304 }},	/* 2304 56 */
	{.type There, {.p 56 }},	/* 2304 56 */
	{.type Header, {.hdr { 4, "Infd", /* MV_Infd = 2320 */ variable }}}, /* MVENTRY "Infd" Infd 4 h 2328 */
	{.type Here, {.p 2328 }},	/* 2328 56 */
	{.type There, {.p 56 }},	/* 2328 56 */
	{.type FromV0, {.p 56 }},	/* 2336 56 */
	{.type Here, {.p 2336 }},	/* 2336 64 */
	{.type There, {.p 64 }},	/* 2336 64 */
	{.type Header, {.hdr { 5, "Outfd", /* MV_Outfd = 2352 */ variable }}}, /* MVENTRY "Outfd" Outfd 5 h 2360 */
	{.type Here, {.p 2360 }},	/* 2360 64 */
	{.type There, {.p 64 }},	/* 2360 64 */
	{.type FromV0, {.p 64 }},	/* 2368 64 */
	{.type Here, {.p 2368 }},	/* 2368 72 */
	{.type There, {.p 72 }},	/* 2368 72 */
	{.type Header, {.hdr { 5, "Errfd", /* MV_Errfd = 2384 */ variable }}}, /* MVENTRY "Errfd" Errfd 5 h 2392 */
	{.type Here, {.p 2392 }},	/* 2392 72 */
	{.type There, {.p 72 }},	/* 2392 72 */
	{.type FromV0, {.p 72 }},	/* 2400 72 */
	{.type Here, {.p 2400 }},	/* 2400 80 */
	{.type There, {.p 80 }},	/* 2400 80 */
	{.type Header, {.hdr { 3, "Eof", /* MV_Eof = 2416 */ variable }}}, /* MVENTRY "Eof" Eof 3 h 2424 */
	{.type Here, {.p 2424 }},	/* 2424 80 */
	{.type There, {.p 80 }},	/* 2424 80 */
	{.type FromV0, {.p 80 }},	/* 2432 80 */
	{.type Here, {.p 2432 }},	/* 2432 88 */
	{.type There, {.p 88 }},	/* 2432 88 */
	{.type Header, {.hdr { 7, "Ninputs", /* MV_Ninputs = 2448 */ variable }}}, /* MVENTRY "Ninputs" Ninputs 7 h 2456 */
	{.type Here, {.p 2456 }},	/* 2456 88 */
	{.type There, {.p 88 }},	/* 2456 88 */
	{.type FromV0, {.p 88 }},	/* 2464 88 */
	{.type Here, {.p 2464 }},	/* 2464 96 */
	{.type There, {.p 96 }},	/* 2464 96 */
	{.type Header, {.hdr { 2, "H0", /* MV_H0 = 2480 */ variable }}}, /* MVENTRY "H0" H0 2		; here at startup h 2488 */
	{.type Here, {.p 2488 }},	/* 2488 96 */
	{.type There, {.p 96 }},	/* 2488 96 */
	{.type FromV0, {.p 96 }},	/* 2496 96 */
	{.type Here, {.p 2496 }},	/* 2496 104 */
	{.type There, {.p 104 }},	/* 2496 104 */
	{.type Here, {.p 2496 }},	/* 2496 104 */
	{.type There, {.p 104 }},	/* 2496 104 */
	{.type Header, {.hdr { 9, "Bufferfds", /* MV_Bufferfds = 2520 */ variable }}}, /* MVENTRY "Bufferfds" Bufferfds 9 16 h 2528 */
	{.type Here, {.p 2528 }},	/* 2528 104 */
	{.type There, {.p 104 }},	/* 2528 104 */
	{.type FromV0, {.p 104 }},	/* 2536 104 */
	{.type Here, {.p 2536 }},	/* 2536 232 */
	{.type There, {.p 232 }},	/* 2536 232 */
	{.type Header, {.hdr { 15, "Bufferfilenames", /* MV_Bufferfilenames = 2560 */ variable }}}, /* MVENTRY "Bufferfilenames" Bufferfilenames 15 16 ; counted string labels of the searchers populated by boot h 2568 */
	{.type Here, {.p 2568 }},	/* 2568 232 */
	{.type There, {.p 232 }},	/* 2568 232 */
	{.type FromV0, {.p 232 }},	/* 2576 232 */
	{.type Here, {.p 2576 }},	/* 2576 360 */
	{.type There, {.p 360 }},	/* 2576 360 */
	{.type Here, {.p 2576 }},	/* 2576 360 */
	{.type There, {.p 360 }},	/* 2576 360 */
	{.type Header, {.hdr { 5, "false", /* C_false = 2592 */ colon }}}, /* CENTRY "false" false 5 h 2600 */
	{.type Here, {.p 2600 }},	/* 2600 360 */
	{.type There, {.p 360 }},	/* 2600 360 */
	{.type Here, {.p 2600 }},	/* 2600 360 */
	{.type There, {.p 360 }},	/* 2600 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2608 */
	{.type Here, {.p 2608 }},	/* 2608 360 */
	{.type There, {.p 360 }},	/* 2608 360 */
	{.type Absolute, {.p 0}},		/* dd 0 2616 */
	{.type Here, {.p 2616 }},	/* 2616 360 */
	{.type There, {.p 360 }},	/* 2616 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2624 */
	{.type Here, {.p 2624 }},	/* 2624 360 */
	{.type There, {.p 360 }},	/* 2624 360 */
	{.type Header, {.hdr { 4, "true", /* C_true = 2640 */ colon }}}, /* CENTRY "true" true 4 h 2648 */
	{.type Here, {.p 2648 }},	/* 2648 360 */
	{.type There, {.p 360 }},	/* 2648 360 */
	{.type Here, {.p 2648 }},	/* 2648 360 */
	{.type There, {.p 360 }},	/* 2648 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2656 */
	{.type Here, {.p 2656 }},	/* 2656 360 */
	{.type There, {.p 360 }},	/* 2656 360 */
	{.type Absolute, {.p -1}},		/* dd -1 2664 */
	{.type Here, {.p 2664 }},	/* 2664 360 */
	{.type There, {.p 360 }},	/* 2664 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2672 */
	{.type Here, {.p 2672 }},	/* 2672 360 */
	{.type There, {.p 360 }},	/* 2672 360 */
	{.type Header, {.hdr { 2, "bl", /* C_bl = 2688 */ colon }}}, /* CENTRY "bl" bl 2 h 2696 */
	{.type Here, {.p 2696 }},	/* 2696 360 */
	{.type There, {.p 360 }},	/* 2696 360 */
	{.type Here, {.p 2696 }},	/* 2696 360 */
	{.type There, {.p 360 }},	/* 2696 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2704 */
	{.type Here, {.p 2704 }},	/* 2704 360 */
	{.type There, {.p 360 }},	/* 2704 360 */
	{.type Absolute, {.p 32}},		/* dd 32 2712 */
	{.type Here, {.p 2712 }},	/* 2712 360 */
	{.type There, {.p 360 }},	/* 2712 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2720 */
	{.type Here, {.p 2720 }},	/* 2720 360 */
	{.type There, {.p 360 }},	/* 2720 360 */
	{.type Header, {.hdr { 2, "on", /* C_on = 2736 */ colon }}}, /* CENTRY "on" on 2 ; ( a -- ) (G stores -1 at a ) h 2744 */
	{.type Here, {.p 2744 }},	/* 2744 360 */
	{.type There, {.p 360 }},	/* 2744 360 */
	{.type Here, {.p 2744 }},	/* 2744 360 */
	{.type There, {.p 360 }},	/* 2744 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2752 */
	{.type Here, {.p 2752 }},	/* 2752 360 */
	{.type There, {.p 360 }},	/* 2752 360 */
	{.type Absolute, {.p -1}},		/* dd -1 2760 */
	{.type Here, {.p 2760 }},	/* 2760 360 */
	{.type There, {.p 360 }},	/* 2760 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2768 */
	{.type Here, {.p 2768 }},	/* 2768 360 */
	{.type There, {.p 360 }},	/* 2768 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2776 */
	{.type Here, {.p 2776 }},	/* 2776 360 */
	{.type There, {.p 360 }},	/* 2776 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2784 */
	{.type Here, {.p 2784 }},	/* 2784 360 */
	{.type There, {.p 360 }},	/* 2784 360 */
	{.type Header, {.hdr { 3, "off", /* C_off = 2800 */ colon }}}, /* CENTRY "off" off 3 ; ( a -- ) (G stores 0 at a ) h 2808 */
	{.type Here, {.p 2808 }},	/* 2808 360 */
	{.type There, {.p 360 }},	/* 2808 360 */
	{.type Here, {.p 2808 }},	/* 2808 360 */
	{.type There, {.p 360 }},	/* 2808 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2816 */
	{.type Here, {.p 2816 }},	/* 2816 360 */
	{.type There, {.p 360 }},	/* 2816 360 */
	{.type Absolute, {.p 0}},		/* dd 0 2824 */
	{.type Here, {.p 2824 }},	/* 2824 360 */
	{.type There, {.p 360 }},	/* 2824 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2832 */
	{.type Here, {.p 2832 }},	/* 2832 360 */
	{.type There, {.p 360 }},	/* 2832 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2840 */
	{.type Here, {.p 2840 }},	/* 2840 360 */
	{.type There, {.p 360 }},	/* 2840 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2848 */
	{.type Here, {.p 2848 }},	/* 2848 360 */
	{.type There, {.p 360 }},	/* 2848 360 */
	{.type Header, {.hdr { 5, ">body", /* C_tobody = 2864 */ colon }}}, /* CENTRY ">body" tobody 5 h 2872 */
	{.type Here, {.p 2872 }},	/* 2872 360 */
	{.type There, {.p 360 }},	/* 2872 360 */
	{.type Here, {.p 2872 }},	/* 2872 360 */
	{.type There, {.p 360 }},	/* 2872 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2880 */
	{.type Here, {.p 2880 }},	/* 2880 360 */
	{.type There, {.p 360 }},	/* 2880 360 */
	{.type Absolute, {.p 8}},		/* dd 8 2888 */
	{.type Here, {.p 2888 }},	/* 2888 360 */
	{.type There, {.p 360 }},	/* 2888 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2896 */
	{.type Here, {.p 2896 }},	/* 2896 360 */
	{.type There, {.p 360 }},	/* 2896 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2904 */
	{.type Here, {.p 2904 }},	/* 2904 360 */
	{.type There, {.p 360 }},	/* 2904 360 */
	{.type Header, {.hdr { 7, "aligned", /* C_aligned = 2920 */ colon }}}, /* CENTRY "aligned" aligned 7 ; align a number to a multiple of 8 h 2928 */
	{.type Here, {.p 2928 }},	/* 2928 360 */
	{.type There, {.p 360 }},	/* 2928 360 */
	{.type Here, {.p 2928 }},	/* 2928 360 */
	{.type There, {.p 360 }},	/* 2928 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2936 */
	{.type Here, {.p 2936 }},	/* 2936 360 */
	{.type There, {.p 360 }},	/* 2936 360 */
	{.type Absolute, {.p 7}},		/* dd 7 2944 */
	{.type Here, {.p 2944 }},	/* 2944 360 */
	{.type There, {.p 360 }},	/* 2944 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 2952 */
	{.type Here, {.p 2952 }},	/* 2952 360 */
	{.type There, {.p 360 }},	/* 2952 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2960 */
	{.type Here, {.p 2960 }},	/* 2960 360 */
	{.type There, {.p 360 }},	/* 2960 360 */
	{.type Absolute, {.p -8}},		/* dd -8 2968 */
	{.type Here, {.p 2968 }},	/* 2968 360 */
	{.type There, {.p 360 }},	/* 2968 360 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 2976 */
	{.type Here, {.p 2976 }},	/* 2976 360 */
	{.type There, {.p 360 }},	/* 2976 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2984 */
	{.type Here, {.p 2984 }},	/* 2984 360 */
	{.type There, {.p 360 }},	/* 2984 360 */
	{.type Header, {.hdr { 5, "cells", /* C_cells = 3000 */ colon }}}, /* CENTRY "cells" cells 5 h 3008 */
	{.type Here, {.p 3008 }},	/* 3008 360 */
	{.type There, {.p 360 }},	/* 3008 360 */
	{.type Here, {.p 3008 }},	/* 3008 360 */
	{.type There, {.p 360 }},	/* 3008 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3016 */
	{.type Here, {.p 3016 }},	/* 3016 360 */
	{.type There, {.p 360 }},	/* 3016 360 */
	{.type Absolute, {.p 3}},		/* dd 3			; (index << 2) -> (index << 3) for amd64 3024 */
	{.type Here, {.p 3024 }},	/* 3024 360 */
	{.type There, {.p 360 }},	/* 3024 360 */
	{.type FromDictionary, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 3032 */
	{.type Here, {.p 3032 }},	/* 3032 360 */
	{.type There, {.p 360 }},	/* 3032 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3040 */
	{.type Here, {.p 3040 }},	/* 3040 360 */
	{.type There, {.p 360 }},	/* 3040 360 */
	{.type Header, {.hdr { 6, "cells+", /* C_cells_plus = 3056 */ colon }}}, /* CENTRY "cells+" cells_plus 6 ; ( n1 n2 -- n1+(n2*cellsize) ) h 3064 */
	{.type Here, {.p 3064 }},	/* 3064 360 */
	{.type There, {.p 360 }},	/* 3064 360 */
	{.type Here, {.p 3064 }},	/* 3064 360 */
	{.type There, {.p 360 }},	/* 3064 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 3072 */
	{.type Here, {.p 3072 }},	/* 3072 360 */
	{.type There, {.p 360 }},	/* 3072 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3080 */
	{.type Here, {.p 3080 }},	/* 3080 360 */
	{.type There, {.p 360 }},	/* 3080 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3088 */
	{.type Here, {.p 3088 }},	/* 3088 360 */
	{.type There, {.p 360 }},	/* 3088 360 */
	{.type Header, {.hdr { 5, "cell+", /* C_cell_plus = 3104 */ colon }}}, /* CENTRY "cell+" cell_plus 5 h 3112 */
	{.type Here, {.p 3112 }},	/* 3112 360 */
	{.type There, {.p 360 }},	/* 3112 360 */
	{.type Here, {.p 3112 }},	/* 3112 360 */
	{.type There, {.p 360 }},	/* 3112 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3120 */
	{.type Here, {.p 3120 }},	/* 3120 360 */
	{.type There, {.p 360 }},	/* 3120 360 */
	{.type Absolute, {.p 1}},		/* dd 1 3128 */
	{.type Here, {.p 3128 }},	/* 3128 360 */
	{.type There, {.p 360 }},	/* 3128 360 */
	{.type FromDictionary, {.p C_cells_plus}, .src = "dd C_cells_plus"},		/* dd C_cells_plus 3136 */
	{.type Here, {.p 3136 }},	/* 3136 360 */
	{.type There, {.p 360 }},	/* 3136 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3144 */
	{.type Here, {.p 3144 }},	/* 3144 360 */
	{.type There, {.p 360 }},	/* 3144 360 */
	{.type Here, {.p 3144 }},	/* 3144 360 */
	{.type There, {.p 360 }},	/* 3144 360 */
	{.type Header, {.hdr { 5, "depth", /* C_depth = 3160 */ colon }}}, /* CENTRY "depth" depth 5 h 3168 */
	{.type Here, {.p 3168 }},	/* 3168 360 */
	{.type There, {.p 360 }},	/* 3168 360 */
	{.type Here, {.p 3168 }},	/* 3168 360 */
	{.type There, {.p 360 }},	/* 3168 360 */
	{.type FromDictionary, {.p MV_S0}, .src = "dd MV_S0"},		/* dd MV_S0 3176 */
	{.type Here, {.p 3176 }},	/* 3176 360 */
	{.type There, {.p 360 }},	/* 3176 360 */
	{.type FromDictionary, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 3184 */
	{.type Here, {.p 3184 }},	/* 3184 360 */
	{.type There, {.p 360 }},	/* 3184 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3192 */
	{.type Here, {.p 3192 }},	/* 3192 360 */
	{.type There, {.p 360 }},	/* 3192 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3200 */
	{.type Here, {.p 3200 }},	/* 3200 360 */
	{.type There, {.p 360 }},	/* 3200 360 */
	{.type Absolute, {.p 3}},		/* dd 3 3208 */
	{.type Here, {.p 3208 }},	/* 3208 360 */
	{.type There, {.p 360 }},	/* 3208 360 */
	{.type FromDictionary, {.p M_rshift}, .src = "dd M_rshift"},		/* dd M_rshift 3216 */
	{.type Here, {.p 3216 }},	/* 3216 360 */
	{.type There, {.p 360 }},	/* 3216 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3224 */
	{.type Here, {.p 3224 }},	/* 3224 360 */
	{.type There, {.p 360 }},	/* 3224 360 */
	{.type Absolute, {.p 1}},		/* dd 1 3232 */
	{.type Here, {.p 3232 }},	/* 3232 360 */
	{.type There, {.p 360 }},	/* 3232 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3240 */
	{.type Here, {.p 3240 }},	/* 3240 360 */
	{.type There, {.p 360 }},	/* 3240 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3248 */
	{.type Here, {.p 3248 }},	/* 3248 360 */
	{.type There, {.p 360 }},	/* 3248 360 */
	{.type Header, {.hdr { 3, "nip", /* C_nip = 3264 */ colon }}}, /* CENTRY "nip" nip 3 h 3272 */
	{.type Here, {.p 3272 }},	/* 3272 360 */
	{.type There, {.p 360 }},	/* 3272 360 */
	{.type Here, {.p 3272 }},	/* 3272 360 */
	{.type There, {.p 360 }},	/* 3272 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3280 */
	{.type Here, {.p 3280 }},	/* 3280 360 */
	{.type There, {.p 360 }},	/* 3280 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3288 */
	{.type Here, {.p 3288 }},	/* 3288 360 */
	{.type There, {.p 360 }},	/* 3288 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3296 */
	{.type Here, {.p 3296 }},	/* 3296 360 */
	{.type There, {.p 360 }},	/* 3296 360 */
	{.type Header, {.hdr { 3, "rot", /* C_rot = 3312 */ colon }}}, /* CENTRY "rot" rot 3 h 3320 */
	{.type Here, {.p 3320 }},	/* 3320 360 */
	{.type There, {.p 360 }},	/* 3320 360 */
	{.type Here, {.p 3320 }},	/* 3320 360 */
	{.type There, {.p 360 }},	/* 3320 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3328 */
	{.type Here, {.p 3328 }},	/* 3328 360 */
	{.type There, {.p 360 }},	/* 3328 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3336 */
	{.type Here, {.p 3336 }},	/* 3336 360 */
	{.type There, {.p 360 }},	/* 3336 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3344 */
	{.type Here, {.p 3344 }},	/* 3344 360 */
	{.type There, {.p 360 }},	/* 3344 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3352 */
	{.type Here, {.p 3352 }},	/* 3352 360 */
	{.type There, {.p 360 }},	/* 3352 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3360 */
	{.type Here, {.p 3360 }},	/* 3360 360 */
	{.type There, {.p 360 }},	/* 3360 360 */
	{.type Header, {.hdr { 5, "2drop", /* C_2drop = 3376 */ colon }}}, /* CENTRY "2drop" 2drop 5 h 3384 */
	{.type Here, {.p 3384 }},	/* 3384 360 */
	{.type There, {.p 360 }},	/* 3384 360 */
	{.type Here, {.p 3384 }},	/* 3384 360 */
	{.type There, {.p 360 }},	/* 3384 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3392 */
	{.type Here, {.p 3392 }},	/* 3392 360 */
	{.type There, {.p 360 }},	/* 3392 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3400 */
	{.type Here, {.p 3400 }},	/* 3400 360 */
	{.type There, {.p 360 }},	/* 3400 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3408 */
	{.type Here, {.p 3408 }},	/* 3408 360 */
	{.type There, {.p 360 }},	/* 3408 360 */
	{.type Header, {.hdr { 4, "2dup", /* C_2dup = 3424 */ colon }}}, /* CENTRY "2dup" 2dup 4 h 3432 */
	{.type Here, {.p 3432 }},	/* 3432 360 */
	{.type There, {.p 360 }},	/* 3432 360 */
	{.type Here, {.p 3432 }},	/* 3432 360 */
	{.type There, {.p 360 }},	/* 3432 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3440 */
	{.type Here, {.p 3440 }},	/* 3440 360 */
	{.type There, {.p 360 }},	/* 3440 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3448 */
	{.type Here, {.p 3448 }},	/* 3448 360 */
	{.type There, {.p 360 }},	/* 3448 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3456 */
	{.type Here, {.p 3456 }},	/* 3456 360 */
	{.type There, {.p 360 }},	/* 3456 360 */
	{.type Header, {.hdr { 4, "2nip", /* C_2nip = 3472 */ colon }}}, /* CENTRY "2nip" 2nip 4 h 3480 */
	{.type Here, {.p 3480 }},	/* 3480 360 */
	{.type There, {.p 360 }},	/* 3480 360 */
	{.type Here, {.p 3480 }},	/* 3480 360 */
	{.type There, {.p 360 }},	/* 3480 360 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3488 */
	{.type Here, {.p 3488 }},	/* 3488 360 */
	{.type There, {.p 360 }},	/* 3488 360 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3496 */
	{.type Here, {.p 3496 }},	/* 3496 360 */
	{.type There, {.p 360 }},	/* 3496 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3504 */
	{.type Here, {.p 3504 }},	/* 3504 360 */
	{.type There, {.p 360 }},	/* 3504 360 */
	{.type Header, {.hdr { 5, "2swap", /* C_2swap = 3520 */ colon }}}, /* CENTRY "2swap" 2swap 5 h 3528 */
	{.type Here, {.p 3528 }},	/* 3528 360 */
	{.type There, {.p 360 }},	/* 3528 360 */
	{.type Here, {.p 3528 }},	/* 3528 360 */
	{.type There, {.p 360 }},	/* 3528 360 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3536 */
	{.type Here, {.p 3536 }},	/* 3536 360 */
	{.type There, {.p 360 }},	/* 3536 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3544 */
	{.type Here, {.p 3544 }},	/* 3544 360 */
	{.type There, {.p 360 }},	/* 3544 360 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3552 */
	{.type Here, {.p 3552 }},	/* 3552 360 */
	{.type There, {.p 360 }},	/* 3552 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3560 */
	{.type Here, {.p 3560 }},	/* 3560 360 */
	{.type There, {.p 360 }},	/* 3560 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3568 */
	{.type Here, {.p 3568 }},	/* 3568 360 */
	{.type There, {.p 360 }},	/* 3568 360 */
	{.type Header, {.hdr { 4, "?dup", /* C_qdup = 3584 */ colon }}}, /* CENTRY "?dup" qdup 4 ; if (n != 0) ( n -- n n) else ( n -- n ) h 3592 */
	{.type Here, {.p 3592 }},	/* 3592 360 */
	{.type There, {.p 360 }},	/* 3592 360 */
	{.type Here, {.p 3592 }},	/* 3592 360 */
	{.type There, {.p 360 }},	/* 3592 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( n -- n n )"},		/* dd M_dup	; ( n -- n n ) 3600 */
	{.type Here, {.p 3600 }},	/* 3600 360 */
	{.type There, {.p 360 }},	/* 3600 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( n n -- n n n )"},		/* dd M_dup	; ( n n -- n n n ) 3608 */
	{.type Here, {.p 3608 }},	/* 3608 360 */
	{.type There, {.p 360 }},	/* 3608 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3616 */
	{.type Here, {.p 3616 }},	/* 3616 360 */
	{.type There, {.p 360 }},	/* 3616 360 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( n n n -- n n n 0 ) 3624 */
	{.type Here, {.p 3624 }},	/* 3624 360 */
	{.type There, {.p 360 }},	/* 3624 360 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal	; ( n n n 0 -- n n f )"},		/* dd M_equal	; ( n n n 0 -- n n f ) 3632 */
	{.type Here, {.p 3632 }},	/* 3632 360 */
	{.type There, {.p 360 }},	/* 3632 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump	; ( n n f -- n n )"},		/* dd M_cjump	; ( n n f -- n n ) 3640 */
	{.type Here, {.p 3640 }},	/* 3640 360 */
	{.type There, {.p 360 }},	/* 3640 360 */
	{.type FromDictionary, {.p L_C_qdup}, .src = "dd L_C_qdup	; when n != 0, go to L20"},		/* dd L_C_qdup	; when n != 0, go to L20 3648 */
	{.type Here, {.p 3648 }},	/* 3648 360 */
	{.type There, {.p 360 }},	/* 3648 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; when n == 0 ( n n -- n)"},		/* dd M_drop	; when n == 0 ( n n -- n) 3656 */
	{.type Here, {.p 3656 }},	/* 3656 360 */
	{.type There, {.p 360 }},	/* 3656 360 */
	{.type Here, {.p 3656 }},	/* 3656 360 */
	{.type There, {.p 360 }},	/* 3656 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3664 */
	{.type Here, {.p 3664 }},	/* 3664 360 */
	{.type There, {.p 360 }},	/* 3664 360 */
	{.type Here, {.p 3664 }},	/* 3664 360 */
	{.type There, {.p 360 }},	/* 3664 360 */
	{.type Header, {.hdr { 4, "pick", /* C_pick = 3680 */ colon }}}, /* CENTRY "pick" pick 4 h 3688 */
	{.type Here, {.p 3688 }},	/* 3688 360 */
	{.type There, {.p 360 }},	/* 3688 360 */
	{.type Here, {.p 3688 }},	/* 3688 360 */
	{.type There, {.p 360 }},	/* 3688 360 */
	{.type FromDictionary, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 3696 */
	{.type Here, {.p 3696 }},	/* 3696 360 */
	{.type There, {.p 360 }},	/* 3696 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 3704 */
	{.type Here, {.p 3704 }},	/* 3704 360 */
	{.type There, {.p 360 }},	/* 3704 360 */
	{.type FromDictionary, {.p L_C_pick}, .src = "dd L_C_pick"},		/* dd L_C_pick 3712 */
	{.type Here, {.p 3712 }},	/* 3712 360 */
	{.type There, {.p 360 }},	/* 3712 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3720 */
	{.type Here, {.p 3720 }},	/* 3720 360 */
	{.type There, {.p 360 }},	/* 3720 360 */
	{.type Absolute, {.p 1}},		/* dd 1 3728 */
	{.type Here, {.p 3728 }},	/* 3728 360 */
	{.type There, {.p 360 }},	/* 3728 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3736 */
	{.type Here, {.p 3736 }},	/* 3736 360 */
	{.type There, {.p 360 }},	/* 3736 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 3744 */
	{.type Here, {.p 3744 }},	/* 3744 360 */
	{.type There, {.p 360 }},	/* 3744 360 */
	{.type FromDictionary, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 3752 */
	{.type Here, {.p 3752 }},	/* 3752 360 */
	{.type There, {.p 360 }},	/* 3752 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3760 */
	{.type Here, {.p 3760 }},	/* 3760 360 */
	{.type There, {.p 360 }},	/* 3760 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3768 */
	{.type Here, {.p 3768 }},	/* 3768 360 */
	{.type There, {.p 360 }},	/* 3768 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 3776 */
	{.type Here, {.p 3776 }},	/* 3776 360 */
	{.type There, {.p 360 }},	/* 3776 360 */
	{.type FromDictionary, {.p L_C_pick_1}, .src = "dd L_C_pick_1"},		/* dd L_C_pick_1 3784 */
	{.type Here, {.p 3784 }},	/* 3784 360 */
	{.type There, {.p 360 }},	/* 3784 360 */
	{.type Here, {.p 3784 }},	/* 3784 360 */
	{.type There, {.p 360 }},	/* 3784 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3792 */
	{.type Here, {.p 3792 }},	/* 3792 360 */
	{.type There, {.p 360 }},	/* 3792 360 */
	{.type Here, {.p 3792 }},	/* 3792 360 */
	{.type There, {.p 360 }},	/* 3792 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3800 */
	{.type Here, {.p 3800 }},	/* 3800 360 */
	{.type There, {.p 360 }},	/* 3800 360 */
	{.type Here, {.p 3800 }},	/* 3800 360 */
	{.type There, {.p 360 }},	/* 3800 360 */
	{.type Header, {.hdr { 4, "tuck", /* C_tuck = 3816 */ colon }}}, /* CENTRY "tuck" tuck 4 h 3824 */
	{.type Here, {.p 3824 }},	/* 3824 360 */
	{.type There, {.p 360 }},	/* 3824 360 */
	{.type Here, {.p 3824 }},	/* 3824 360 */
	{.type There, {.p 360 }},	/* 3824 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3832 */
	{.type Here, {.p 3832 }},	/* 3832 360 */
	{.type There, {.p 360 }},	/* 3832 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3840 */
	{.type Here, {.p 3840 }},	/* 3840 360 */
	{.type There, {.p 360 }},	/* 3840 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3848 */
	{.type Here, {.p 3848 }},	/* 3848 360 */
	{.type There, {.p 360 }},	/* 3848 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3856 */
	{.type Here, {.p 3856 }},	/* 3856 360 */
	{.type There, {.p 360 }},	/* 3856 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3864 */
	{.type Here, {.p 3864 }},	/* 3864 360 */
	{.type There, {.p 360 }},	/* 3864 360 */
	{.type Header, {.hdr { 1, "/", /* C_divides = 3880 */ colon }}}, /* CENTRY "/" divides 1 h 3888 */
	{.type Here, {.p 3888 }},	/* 3888 360 */
	{.type There, {.p 360 }},	/* 3888 360 */
	{.type Here, {.p 3888 }},	/* 3888 360 */
	{.type There, {.p 360 }},	/* 3888 360 */
	{.type FromDictionary, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 3896 */
	{.type Here, {.p 3896 }},	/* 3896 360 */
	{.type There, {.p 360 }},	/* 3896 360 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3904 */
	{.type Here, {.p 3904 }},	/* 3904 360 */
	{.type There, {.p 360 }},	/* 3904 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3912 */
	{.type Here, {.p 3912 }},	/* 3912 360 */
	{.type There, {.p 360 }},	/* 3912 360 */
	{.type Here, {.p 3912 }},	/* 3912 360 */
	{.type There, {.p 360 }},	/* 3912 360 */
	{.type Header, {.hdr { 2, "+!", /* C_plusstore = 3928 */ colon }}}, /* CENTRY "+!" plusstore 2 ; ( n 'a -- ) a@ = a@+n h 3936 */
	{.type Here, {.p 3936 }},	/* 3936 360 */
	{.type There, {.p 360 }},	/* 3936 360 */
	{.type Here, {.p 3936 }},	/* 3936 360 */
	{.type There, {.p 360 }},	/* 3936 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3944 */
	{.type Here, {.p 3944 }},	/* 3944 360 */
	{.type There, {.p 360 }},	/* 3944 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3952 */
	{.type Here, {.p 3952 }},	/* 3952 360 */
	{.type There, {.p 360 }},	/* 3952 360 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3960 */
	{.type Here, {.p 3960 }},	/* 3960 360 */
	{.type There, {.p 360 }},	/* 3960 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3968 */
	{.type Here, {.p 3968 }},	/* 3968 360 */
	{.type There, {.p 360 }},	/* 3968 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3976 */
	{.type Here, {.p 3976 }},	/* 3976 360 */
	{.type There, {.p 360 }},	/* 3976 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 3984 */
	{.type Here, {.p 3984 }},	/* 3984 360 */
	{.type There, {.p 360 }},	/* 3984 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3992 */
	{.type Here, {.p 3992 }},	/* 3992 360 */
	{.type There, {.p 360 }},	/* 3992 360 */
	{.type Here, {.p 3992 }},	/* 3992 360 */
	{.type There, {.p 360 }},	/* 3992 360 */
	{.type Header, {.hdr { 6, "invert", /* C_invert = 4008 */ colon }}}, /* CENTRY "invert" invert 6 h 4016 */
	{.type Here, {.p 4016 }},	/* 4016 360 */
	{.type There, {.p 360 }},	/* 4016 360 */
	{.type Here, {.p 4016 }},	/* 4016 360 */
	{.type There, {.p 360 }},	/* 4016 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4024 */
	{.type Here, {.p 4024 }},	/* 4024 360 */
	{.type There, {.p 360 }},	/* 4024 360 */
	{.type Absolute, {.p -1}},		/* dd -1 4032 */
	{.type Here, {.p 4032 }},	/* 4032 360 */
	{.type There, {.p 360 }},	/* 4032 360 */
	{.type FromDictionary, {.p M_binxor}, .src = "dd M_binxor"},		/* dd M_binxor 4040 */
	{.type Here, {.p 4040 }},	/* 4040 360 */
	{.type There, {.p 360 }},	/* 4040 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4048 */
	{.type Here, {.p 4048 }},	/* 4048 360 */
	{.type There, {.p 360 }},	/* 4048 360 */
	{.type Header, {.hdr { 3, "mod", /* C_mod = 4064 */ colon }}}, /* CENTRY "mod" mod 3 h 4072 */
	{.type Here, {.p 4072 }},	/* 4072 360 */
	{.type There, {.p 360 }},	/* 4072 360 */
	{.type Here, {.p 4072 }},	/* 4072 360 */
	{.type There, {.p 360 }},	/* 4072 360 */
	{.type FromDictionary, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 4080 */
	{.type Here, {.p 4080 }},	/* 4080 360 */
	{.type There, {.p 360 }},	/* 4080 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4088 */
	{.type Here, {.p 4088 }},	/* 4088 360 */
	{.type There, {.p 360 }},	/* 4088 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4096 */
	{.type Here, {.p 4096 }},	/* 4096 360 */
	{.type There, {.p 360 }},	/* 4096 360 */
	{.type Header, {.hdr { 2, "1+", /* C_1plus = 4112 */ colon }}}, /* CENTRY "1+" 1plus 2 h 4120 */
	{.type Here, {.p 4120 }},	/* 4120 360 */
	{.type There, {.p 360 }},	/* 4120 360 */
	{.type Here, {.p 4120 }},	/* 4120 360 */
	{.type There, {.p 360 }},	/* 4120 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4128 */
	{.type Here, {.p 4128 }},	/* 4128 360 */
	{.type There, {.p 360 }},	/* 4128 360 */
	{.type Absolute, {.p 1}},		/* dd 1 4136 */
	{.type Here, {.p 4136 }},	/* 4136 360 */
	{.type There, {.p 360 }},	/* 4136 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 4144 */
	{.type Here, {.p 4144 }},	/* 4144 360 */
	{.type There, {.p 360 }},	/* 4144 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4152 */
	{.type Here, {.p 4152 }},	/* 4152 360 */
	{.type There, {.p 360 }},	/* 4152 360 */
	{.type Header, {.hdr { 2, "1-", /* C_1minus = 4168 */ colon }}}, /* CENTRY "1-" 1minus 2 h 4176 */
	{.type Here, {.p 4176 }},	/* 4176 360 */
	{.type There, {.p 360 }},	/* 4176 360 */
	{.type Here, {.p 4176 }},	/* 4176 360 */
	{.type There, {.p 360 }},	/* 4176 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4184 */
	{.type Here, {.p 4184 }},	/* 4184 360 */
	{.type There, {.p 360 }},	/* 4184 360 */
	{.type Absolute, {.p 1}},		/* dd 1 4192 */
	{.type Here, {.p 4192 }},	/* 4192 360 */
	{.type There, {.p 360 }},	/* 4192 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 4200 */
	{.type Here, {.p 4200 }},	/* 4200 360 */
	{.type There, {.p 360 }},	/* 4200 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4208 */
	{.type Here, {.p 4208 }},	/* 4208 360 */
	{.type There, {.p 360 }},	/* 4208 360 */
	{.type Header, {.hdr { 6, "negate", /* C_negate = 4224 */ colon }}}, /* CENTRY "negate" negate 6 h 4232 */
	{.type Here, {.p 4232 }},	/* 4232 360 */
	{.type There, {.p 360 }},	/* 4232 360 */
	{.type Here, {.p 4232 }},	/* 4232 360 */
	{.type There, {.p 360 }},	/* 4232 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4240 */
	{.type Here, {.p 4240 }},	/* 4240 360 */
	{.type There, {.p 360 }},	/* 4240 360 */
	{.type Absolute, {.p 0}},		/* dd 0 4248 */
	{.type Here, {.p 4248 }},	/* 4248 360 */
	{.type There, {.p 360 }},	/* 4248 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 4256 */
	{.type Here, {.p 4256 }},	/* 4256 360 */
	{.type There, {.p 360 }},	/* 4256 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 4264 */
	{.type Here, {.p 4264 }},	/* 4264 360 */
	{.type There, {.p 360 }},	/* 4264 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4272 */
	{.type Here, {.p 4272 }},	/* 4272 360 */
	{.type There, {.p 360 }},	/* 4272 360 */
	{.type Header, {.hdr { 2, "2*", /* C_2multiplies = 4288 */ colon }}}, /* CENTRY "2*" 2multiplies 2 h 4296 */
	{.type Here, {.p 4296 }},	/* 4296 360 */
	{.type There, {.p 360 }},	/* 4296 360 */
	{.type Here, {.p 4296 }},	/* 4296 360 */
	{.type There, {.p 360 }},	/* 4296 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4304 */
	{.type Here, {.p 4304 }},	/* 4304 360 */
	{.type There, {.p 360 }},	/* 4304 360 */
	{.type Absolute, {.p 1}},		/* dd 1 4312 */
	{.type Here, {.p 4312 }},	/* 4312 360 */
	{.type There, {.p 360 }},	/* 4312 360 */
	{.type FromDictionary, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 4320 */
	{.type Here, {.p 4320 }},	/* 4320 360 */
	{.type There, {.p 360 }},	/* 4320 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4328 */
	{.type Here, {.p 4328 }},	/* 4328 360 */
	{.type There, {.p 360 }},	/* 4328 360 */
	{.type Header, {.hdr { 2, "2/", /* C_2divides = 4344 */ colon }}}, /* CENTRY "2/" 2divides 2 h 4352 */
	{.type Here, {.p 4352 }},	/* 4352 360 */
	{.type There, {.p 360 }},	/* 4352 360 */
	{.type Here, {.p 4352 }},	/* 4352 360 */
	{.type There, {.p 360 }},	/* 4352 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4360 */
	{.type Here, {.p 4360 }},	/* 4360 360 */
	{.type There, {.p 360 }},	/* 4360 360 */
	{.type Absolute, {.p 1}},		/* dd 1 4368 */
	{.type Here, {.p 4368 }},	/* 4368 360 */
	{.type There, {.p 360 }},	/* 4368 360 */
	{.type FromDictionary, {.p M_rshifta}, .src = "dd M_rshifta"},		/* dd M_rshifta 4376 */
	{.type Here, {.p 4376 }},	/* 4376 360 */
	{.type There, {.p 360 }},	/* 4376 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4384 */
	{.type Here, {.p 4384 }},	/* 4384 360 */
	{.type There, {.p 360 }},	/* 4384 360 */
	{.type Header, {.hdr { 2, "0=", /* C_0eq = 4400 */ colon }}}, /* CENTRY "0=" 0eq 2 h 4408 */
	{.type Here, {.p 4408 }},	/* 4408 360 */
	{.type There, {.p 360 }},	/* 4408 360 */
	{.type Here, {.p 4408 }},	/* 4408 360 */
	{.type There, {.p 360 }},	/* 4408 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4416 */
	{.type Here, {.p 4416 }},	/* 4416 360 */
	{.type There, {.p 360 }},	/* 4416 360 */
	{.type Absolute, {.p 0}},		/* dd 0 4424 */
	{.type Here, {.p 4424 }},	/* 4424 360 */
	{.type There, {.p 360 }},	/* 4424 360 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4432 */
	{.type Here, {.p 4432 }},	/* 4432 360 */
	{.type There, {.p 360 }},	/* 4432 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4440 */
	{.type Here, {.p 4440 }},	/* 4440 360 */
	{.type There, {.p 360 }},	/* 4440 360 */
	{.type Header, {.hdr { 2, "0<", /* C_0lt = 4456 */ colon }}}, /* CENTRY "0<" 0lt 2 h 4464 */
	{.type Here, {.p 4464 }},	/* 4464 360 */
	{.type There, {.p 360 }},	/* 4464 360 */
	{.type Here, {.p 4464 }},	/* 4464 360 */
	{.type There, {.p 360 }},	/* 4464 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4472 */
	{.type Here, {.p 4472 }},	/* 4472 360 */
	{.type There, {.p 360 }},	/* 4472 360 */
	{.type Absolute, {.p 0}},		/* dd 0 4480 */
	{.type Here, {.p 4480 }},	/* 4480 360 */
	{.type There, {.p 360 }},	/* 4480 360 */
	{.type FromDictionary, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4488 */
	{.type Here, {.p 4488 }},	/* 4488 360 */
	{.type There, {.p 360 }},	/* 4488 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4496 */
	{.type Here, {.p 4496 }},	/* 4496 360 */
	{.type There, {.p 360 }},	/* 4496 360 */
	{.type Header, {.hdr { 2, "0>", /* C_0gt = 4512 */ colon }}}, /* CENTRY "0>" 0gt 2 h 4520 */
	{.type Here, {.p 4520 }},	/* 4520 360 */
	{.type There, {.p 360 }},	/* 4520 360 */
	{.type Here, {.p 4520 }},	/* 4520 360 */
	{.type There, {.p 360 }},	/* 4520 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4528 */
	{.type Here, {.p 4528 }},	/* 4528 360 */
	{.type There, {.p 360 }},	/* 4528 360 */
	{.type Absolute, {.p 0}},		/* dd 0 4536 */
	{.type Here, {.p 4536 }},	/* 4536 360 */
	{.type There, {.p 360 }},	/* 4536 360 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4544 */
	{.type Here, {.p 4544 }},	/* 4544 360 */
	{.type There, {.p 360 }},	/* 4544 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4552 */
	{.type Here, {.p 4552 }},	/* 4552 360 */
	{.type There, {.p 360 }},	/* 4552 360 */
	{.type Header, {.hdr { 2, "<>", /* C_neq = 4568 */ colon }}}, /* CENTRY "<>" neq 2 h 4576 */
	{.type Here, {.p 4576 }},	/* 4576 360 */
	{.type There, {.p 360 }},	/* 4576 360 */
	{.type Here, {.p 4576 }},	/* 4576 360 */
	{.type There, {.p 360 }},	/* 4576 360 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4584 */
	{.type Here, {.p 4584 }},	/* 4584 360 */
	{.type There, {.p 360 }},	/* 4584 360 */
	{.type FromDictionary, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 4592 */
	{.type Here, {.p 4592 }},	/* 4592 360 */
	{.type There, {.p 360 }},	/* 4592 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4600 */
	{.type Here, {.p 4600 }},	/* 4600 360 */
	{.type There, {.p 360 }},	/* 4600 360 */
	{.type Header, {.hdr { 3, "0<>", /* C_0neq = 4616 */ colon }}}, /* CENTRY "0<>" 0neq 3 h 4624 */
	{.type Here, {.p 4624 }},	/* 4624 360 */
	{.type There, {.p 360 }},	/* 4624 360 */
	{.type Here, {.p 4624 }},	/* 4624 360 */
	{.type There, {.p 360 }},	/* 4624 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4632 */
	{.type Here, {.p 4632 }},	/* 4632 360 */
	{.type There, {.p 360 }},	/* 4632 360 */
	{.type Absolute, {.p 0}},		/* dd 0 4640 */
	{.type Here, {.p 4640 }},	/* 4640 360 */
	{.type There, {.p 360 }},	/* 4640 360 */
	{.type FromDictionary, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 4648 */
	{.type Here, {.p 4648 }},	/* 4648 360 */
	{.type There, {.p 360 }},	/* 4648 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4656 */
	{.type Here, {.p 4656 }},	/* 4656 360 */
	{.type There, {.p 360 }},	/* 4656 360 */
	{.type Here, {.p 4656 }},	/* 4656 360 */
	{.type There, {.p 360 }},	/* 4656 360 */
	{.type Header, {.hdr { 3, "max", /* C_max = 4672 */ colon }}}, /* CENTRY "max" max 3 h 4680 */
	{.type Here, {.p 4680 }},	/* 4680 360 */
	{.type There, {.p 360 }},	/* 4680 360 */
	{.type Here, {.p 4680 }},	/* 4680 360 */
	{.type There, {.p 360 }},	/* 4680 360 */
	{.type FromDictionary, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4688 */
	{.type Here, {.p 4688 }},	/* 4688 360 */
	{.type There, {.p 360 }},	/* 4688 360 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4696 */
	{.type Here, {.p 4696 }},	/* 4696 360 */
	{.type There, {.p 360 }},	/* 4696 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4704 */
	{.type Here, {.p 4704 }},	/* 4704 360 */
	{.type There, {.p 360 }},	/* 4704 360 */
	{.type FromDictionary, {.p L_C_max}, .src = "dd L_C_max"},		/* dd L_C_max 4712 */
	{.type Here, {.p 4712 }},	/* 4712 360 */
	{.type There, {.p 360 }},	/* 4712 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4720 */
	{.type Here, {.p 4720 }},	/* 4720 360 */
	{.type There, {.p 360 }},	/* 4720 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4728 */
	{.type Here, {.p 4728 }},	/* 4728 360 */
	{.type There, {.p 360 }},	/* 4728 360 */
	{.type FromDictionary, {.p L_C_max_1}, .src = "dd L_C_max_1"},		/* dd L_C_max_1 4736 */
	{.type Here, {.p 4736 }},	/* 4736 360 */
	{.type There, {.p 360 }},	/* 4736 360 */
	{.type Here, {.p 4736 }},	/* 4736 360 */
	{.type There, {.p 360 }},	/* 4736 360 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4744 */
	{.type Here, {.p 4744 }},	/* 4744 360 */
	{.type There, {.p 360 }},	/* 4744 360 */
	{.type Here, {.p 4744 }},	/* 4744 360 */
	{.type There, {.p 360 }},	/* 4744 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4752 */
	{.type Here, {.p 4752 }},	/* 4752 360 */
	{.type There, {.p 360 }},	/* 4752 360 */
	{.type Here, {.p 4752 }},	/* 4752 360 */
	{.type There, {.p 360 }},	/* 4752 360 */
	{.type Header, {.hdr { 3, "min", /* C_min = 4768 */ colon }}}, /* CENTRY "min" min 3 h 4776 */
	{.type Here, {.p 4776 }},	/* 4776 360 */
	{.type There, {.p 360 }},	/* 4776 360 */
	{.type Here, {.p 4776 }},	/* 4776 360 */
	{.type There, {.p 360 }},	/* 4776 360 */
	{.type FromDictionary, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4784 */
	{.type Here, {.p 4784 }},	/* 4784 360 */
	{.type There, {.p 360 }},	/* 4784 360 */
	{.type FromDictionary, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4792 */
	{.type Here, {.p 4792 }},	/* 4792 360 */
	{.type There, {.p 360 }},	/* 4792 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4800 */
	{.type Here, {.p 4800 }},	/* 4800 360 */
	{.type There, {.p 360 }},	/* 4800 360 */
	{.type FromDictionary, {.p L_C_min}, .src = "dd L_C_min"},		/* dd L_C_min 4808 */
	{.type Here, {.p 4808 }},	/* 4808 360 */
	{.type There, {.p 360 }},	/* 4808 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4816 */
	{.type Here, {.p 4816 }},	/* 4816 360 */
	{.type There, {.p 360 }},	/* 4816 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4824 */
	{.type Here, {.p 4824 }},	/* 4824 360 */
	{.type There, {.p 360 }},	/* 4824 360 */
	{.type FromDictionary, {.p L_C_min_1}, .src = "dd L_C_min_1"},		/* dd L_C_min_1 4832 */
	{.type Here, {.p 4832 }},	/* 4832 360 */
	{.type There, {.p 360 }},	/* 4832 360 */
	{.type Here, {.p 4832 }},	/* 4832 360 */
	{.type There, {.p 360 }},	/* 4832 360 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4840 */
	{.type Here, {.p 4840 }},	/* 4840 360 */
	{.type There, {.p 360 }},	/* 4840 360 */
	{.type Here, {.p 4840 }},	/* 4840 360 */
	{.type There, {.p 360 }},	/* 4840 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4848 */
	{.type Here, {.p 4848 }},	/* 4848 360 */
	{.type There, {.p 360 }},	/* 4848 360 */
	{.type Here, {.p 4848 }},	/* 4848 360 */
	{.type There, {.p 360 }},	/* 4848 360 */
	{.type Header, {.hdr { 6, "signum", /* C_signum = 4864 */ colon }}}, /* CENTRY "signum" signum 6 h 4872 */
	{.type Here, {.p 4872 }},	/* 4872 360 */
	{.type There, {.p 360 }},	/* 4872 360 */
	{.type Here, {.p 4872 }},	/* 4872 360 */
	{.type There, {.p 360 }},	/* 4872 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4880 */
	{.type Here, {.p 4880 }},	/* 4880 360 */
	{.type There, {.p 360 }},	/* 4880 360 */
	{.type FromDictionary, {.p C_0gt}, .src = "dd C_0gt"},		/* dd C_0gt 4888 */
	{.type Here, {.p 4888 }},	/* 4888 360 */
	{.type There, {.p 360 }},	/* 4888 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4896 */
	{.type Here, {.p 4896 }},	/* 4896 360 */
	{.type There, {.p 360 }},	/* 4896 360 */
	{.type FromDictionary, {.p L_C_signum}, .src = "dd L_C_signum"},		/* dd L_C_signum 4904 */
	{.type Here, {.p 4904 }},	/* 4904 360 */
	{.type There, {.p 360 }},	/* 4904 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4912 */
	{.type Here, {.p 4912 }},	/* 4912 360 */
	{.type There, {.p 360 }},	/* 4912 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4920 */
	{.type Here, {.p 4920 }},	/* 4920 360 */
	{.type There, {.p 360 }},	/* 4920 360 */
	{.type Absolute, {.p 1}},		/* dd 1 4928 */
	{.type Here, {.p 4928 }},	/* 4928 360 */
	{.type There, {.p 360 }},	/* 4928 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4936 */
	{.type Here, {.p 4936 }},	/* 4936 360 */
	{.type There, {.p 360 }},	/* 4936 360 */
	{.type FromDictionary, {.p L_C_signum_1}, .src = "dd L_C_signum_1"},		/* dd L_C_signum_1 4944 */
	{.type Here, {.p 4944 }},	/* 4944 360 */
	{.type There, {.p 360 }},	/* 4944 360 */
	{.type Here, {.p 4944 }},	/* 4944 360 */
	{.type There, {.p 360 }},	/* 4944 360 */
	{.type FromDictionary, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 4952 */
	{.type Here, {.p 4952 }},	/* 4952 360 */
	{.type There, {.p 360 }},	/* 4952 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4960 */
	{.type Here, {.p 4960 }},	/* 4960 360 */
	{.type There, {.p 360 }},	/* 4960 360 */
	{.type FromDictionary, {.p L_C_signum_2}, .src = "dd L_C_signum_2"},		/* dd L_C_signum_2 4968 */
	{.type Here, {.p 4968 }},	/* 4968 360 */
	{.type There, {.p 360 }},	/* 4968 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4976 */
	{.type Here, {.p 4976 }},	/* 4976 360 */
	{.type There, {.p 360 }},	/* 4976 360 */
	{.type Absolute, {.p -1}},		/* dd -1 4984 */
	{.type Here, {.p 4984 }},	/* 4984 360 */
	{.type There, {.p 360 }},	/* 4984 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4992 */
	{.type Here, {.p 4992 }},	/* 4992 360 */
	{.type There, {.p 360 }},	/* 4992 360 */
	{.type FromDictionary, {.p L_C_signum_3}, .src = "dd L_C_signum_3"},		/* dd L_C_signum_3 5000 */
	{.type Here, {.p 5000 }},	/* 5000 360 */
	{.type There, {.p 360 }},	/* 5000 360 */
	{.type Here, {.p 5000 }},	/* 5000 360 */
	{.type There, {.p 360 }},	/* 5000 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5008 */
	{.type Here, {.p 5008 }},	/* 5008 360 */
	{.type There, {.p 360 }},	/* 5008 360 */
	{.type Absolute, {.p 0}},		/* dd 0 5016 */
	{.type Here, {.p 5016 }},	/* 5016 360 */
	{.type There, {.p 360 }},	/* 5016 360 */
	{.type Here, {.p 5016 }},	/* 5016 360 */
	{.type There, {.p 360 }},	/* 5016 360 */
	{.type Here, {.p 5016 }},	/* 5016 360 */
	{.type There, {.p 360 }},	/* 5016 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5024 */
	{.type Here, {.p 5024 }},	/* 5024 360 */
	{.type There, {.p 360 }},	/* 5024 360 */
	{.type Here, {.p 5024 }},	/* 5024 360 */
	{.type There, {.p 360 }},	/* 5024 360 */
	{.type Header, {.hdr { 6, "within", /* C_within = 5040 */ colon }}}, /* CENTRY "within" within 6 h 5048 */
	{.type Here, {.p 5048 }},	/* 5048 360 */
	{.type There, {.p 360 }},	/* 5048 360 */
	{.type Here, {.p 5048 }},	/* 5048 360 */
	{.type There, {.p 360 }},	/* 5048 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 5056 */
	{.type Here, {.p 5056 }},	/* 5056 360 */
	{.type There, {.p 360 }},	/* 5056 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5064 */
	{.type Here, {.p 5064 }},	/* 5064 360 */
	{.type There, {.p 360 }},	/* 5064 360 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 5072 */
	{.type Here, {.p 5072 }},	/* 5072 360 */
	{.type There, {.p 360 }},	/* 5072 360 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 5080 */
	{.type Here, {.p 5080 }},	/* 5080 360 */
	{.type There, {.p 360 }},	/* 5080 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 5088 */
	{.type Here, {.p 5088 }},	/* 5088 360 */
	{.type There, {.p 360 }},	/* 5088 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5096 */
	{.type Here, {.p 5096 }},	/* 5096 360 */
	{.type There, {.p 360 }},	/* 5096 360 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 5104 */
	{.type Here, {.p 5104 }},	/* 5104 360 */
	{.type There, {.p 360 }},	/* 5104 360 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 5112 */
	{.type Here, {.p 5112 }},	/* 5112 360 */
	{.type There, {.p 360 }},	/* 5112 360 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 5120 */
	{.type Here, {.p 5120 }},	/* 5120 360 */
	{.type There, {.p 360 }},	/* 5120 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5128 */
	{.type Here, {.p 5128 }},	/* 5128 360 */
	{.type There, {.p 360 }},	/* 5128 360 */
	{.type Header, {.hdr { 3, "abs", /* C_abs = 5144 */ colon }}}, /* CENTRY "abs" abs 3 h 5152 */
	{.type Here, {.p 5152 }},	/* 5152 360 */
	{.type There, {.p 360 }},	/* 5152 360 */
	{.type Here, {.p 5152 }},	/* 5152 360 */
	{.type There, {.p 360 }},	/* 5152 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 5160 */
	{.type Here, {.p 5160 }},	/* 5160 360 */
	{.type There, {.p 360 }},	/* 5160 360 */
	{.type FromDictionary, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 5168 */
	{.type Here, {.p 5168 }},	/* 5168 360 */
	{.type There, {.p 360 }},	/* 5168 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5176 */
	{.type Here, {.p 5176 }},	/* 5176 360 */
	{.type There, {.p 360 }},	/* 5176 360 */
	{.type FromDictionary, {.p L_C_abs}, .src = "dd L_C_abs"},		/* dd L_C_abs 5184 */
	{.type Here, {.p 5184 }},	/* 5184 360 */
	{.type There, {.p 360 }},	/* 5184 360 */
	{.type FromDictionary, {.p C_negate}, .src = "dd C_negate"},		/* dd C_negate 5192 */
	{.type Here, {.p 5192 }},	/* 5192 360 */
	{.type There, {.p 360 }},	/* 5192 360 */
	{.type Here, {.p 5192 }},	/* 5192 360 */
	{.type There, {.p 360 }},	/* 5192 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5200 */
	{.type Here, {.p 5200 }},	/* 5200 360 */
	{.type There, {.p 360 }},	/* 5200 360 */
	{.type Here, {.p 5200 }},	/* 5200 360 */
	{.type There, {.p 360 }},	/* 5200 360 */
	{.type Header, {.hdr { 4, "emit", /* C_emit = 5216 */ colon }}}, /* CENTRY "emit" emit 4 ; ( character -- ) h 5224 */
	{.type Here, {.p 5224 }},	/* 5224 360 */
	{.type There, {.p 360 }},	/* 5224 360 */
	{.type Here, {.p 5224 }},	/* 5224 360 */
	{.type There, {.p 360 }},	/* 5224 360 */
	{.type FromDictionary, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5232 */
	{.type Here, {.p 5232 }},	/* 5232 360 */
	{.type There, {.p 360 }},	/* 5232 360 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore	; variable iobuf has character"},		/* dd M_cstore	; variable iobuf has character 5240 */
	{.type Here, {.p 5240 }},	/* 5240 360 */
	{.type There, {.p 360 }},	/* 5240 360 */
	{.type FromDictionary, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 5248 */
	{.type Here, {.p 5248 }},	/* 5248 360 */
	{.type There, {.p 360 }},	/* 5248 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch		; outfd"},		/* dd M_fetch		; outfd 5256 */
	{.type Here, {.p 5256 }},	/* 5256 360 */
	{.type There, {.p 360 }},	/* 5256 360 */
	{.type FromDictionary, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5264 */
	{.type Here, {.p 5264 }},	/* 5264 360 */
	{.type There, {.p 360 }},	/* 5264 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5272 */
	{.type Here, {.p 5272 }},	/* 5272 360 */
	{.type There, {.p 360 }},	/* 5272 360 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( outfd iobuf 1 ) 5280 */
	{.type Here, {.p 5280 }},	/* 5280 360 */
	{.type There, {.p 360 }},	/* 5280 360 */
	{.type FromDictionary, {.p M_syswrite}, .src = "dd M_syswrite	; ( 1 iobuf outfd --  )"},		/* dd M_syswrite	; ( 1 iobuf outfd --  ) 5288 */
	{.type Here, {.p 5288 }},	/* 5288 360 */
	{.type There, {.p 360 }},	/* 5288 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5296 */
	{.type Here, {.p 5296 }},	/* 5296 360 */
	{.type There, {.p 360 }},	/* 5296 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5304 */
	{.type Here, {.p 5304 }},	/* 5304 360 */
	{.type There, {.p 360 }},	/* 5304 360 */
	{.type Here, {.p 5304 }},	/* 5304 360 */
	{.type There, {.p 360 }},	/* 5304 360 */
	{.type Header, {.hdr { 4, "type", /* C_type = 5320 */ colon }}}, /* CENTRY "type" type 4 ; ( addr n -- ) h 5328 */
	{.type Here, {.p 5328 }},	/* 5328 360 */
	{.type There, {.p 360 }},	/* 5328 360 */
	{.type Here, {.p 5328 }},	/* 5328 360 */
	{.type There, {.p 360 }},	/* 5328 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush		; ( addr ) (R n )"},		/* dd M_rpush		; ( addr ) (R n ) 5336 */
	{.type Here, {.p 5336 }},	/* 5336 360 */
	{.type There, {.p 360 }},	/* 5336 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush		; ( ) (R n addr )"},		/* dd M_rpush		; ( ) (R n addr ) 5344 */
	{.type Here, {.p 5344 }},	/* 5344 360 */
	{.type There, {.p 360 }},	/* 5344 360 */
	{.type FromDictionary, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 5352 */
	{.type Here, {.p 5352 }},	/* 5352 360 */
	{.type There, {.p 360 }},	/* 5352 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch		; ( outfd )"},		/* dd M_fetch		; ( outfd ) 5360 */
	{.type Here, {.p 5360 }},	/* 5360 360 */
	{.type There, {.p 360 }},	/* 5360 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop		; ( outfd addr ) (R n )"},		/* dd M_rpop		; ( outfd addr ) (R n ) 5368 */
	{.type Here, {.p 5368 }},	/* 5368 360 */
	{.type There, {.p 360 }},	/* 5368 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop		; ( outfd addr n ) (R )"},		/* dd M_rpop		; ( outfd addr n ) (R ) 5376 */
	{.type Here, {.p 5376 }},	/* 5376 360 */
	{.type There, {.p 360 }},	/* 5376 360 */
	{.type FromDictionary, {.p M_syswrite}, .src = "dd M_syswrite	; ( 1 addr n --  )"},		/* dd M_syswrite	; ( 1 addr n --  ) 5384 */
	{.type Here, {.p 5384 }},	/* 5384 360 */
	{.type There, {.p 360 }},	/* 5384 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5392 */
	{.type Here, {.p 5392 }},	/* 5392 360 */
	{.type There, {.p 360 }},	/* 5392 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5400 */
	{.type Here, {.p 5400 }},	/* 5400 360 */
	{.type There, {.p 360 }},	/* 5400 360 */
	{.type Here, {.p 5400 }},	/* 5400 360 */
	{.type There, {.p 360 }},	/* 5400 360 */
	{.type Header, {.hdr { 2, "cr", /* C_cr = 5416 */ colon }}}, /* CENTRY "cr" cr 2 h 5424 */
	{.type Here, {.p 5424 }},	/* 5424 360 */
	{.type There, {.p 360 }},	/* 5424 360 */
	{.type Here, {.p 5424 }},	/* 5424 360 */
	{.type There, {.p 360 }},	/* 5424 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5432 */
	{.type Here, {.p 5432 }},	/* 5432 360 */
	{.type There, {.p 360 }},	/* 5432 360 */
	{.type Absolute, {.p 10}},		/* dd 10			; ascii value of carriage return 5440 */
	{.type Here, {.p 5440 }},	/* 5440 360 */
	{.type There, {.p 360 }},	/* 5440 360 */
	{.type FromDictionary, {.p C_emit}, .src = "dd C_emit			; emit"},		/* dd C_emit			; emit 5448 */
	{.type Here, {.p 5448 }},	/* 5448 360 */
	{.type There, {.p 360 }},	/* 5448 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5456 */
	{.type Here, {.p 5456 }},	/* 5456 360 */
	{.type There, {.p 360 }},	/* 5456 360 */
	{.type Here, {.p 5456 }},	/* 5456 360 */
	{.type There, {.p 360 }},	/* 5456 360 */
	{.type Header, {.hdr { 5, "space", /* C_space = 5472 */ colon }}}, /* CENTRY "space" space 5 h 5480 */
	{.type Here, {.p 5480 }},	/* 5480 360 */
	{.type There, {.p 360 }},	/* 5480 360 */
	{.type Here, {.p 5480 }},	/* 5480 360 */
	{.type There, {.p 360 }},	/* 5480 360 */
	{.type FromDictionary, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5488 */
	{.type Here, {.p 5488 }},	/* 5488 360 */
	{.type There, {.p 360 }},	/* 5488 360 */
	{.type FromDictionary, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5496 */
	{.type Here, {.p 5496 }},	/* 5496 360 */
	{.type There, {.p 360 }},	/* 5496 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5504 */
	{.type Here, {.p 5504 }},	/* 5504 360 */
	{.type There, {.p 360 }},	/* 5504 360 */
	{.type Here, {.p 5504 }},	/* 5504 360 */
	{.type There, {.p 360 }},	/* 5504 360 */
	{.type Header, {.hdr { 5, "emits", /* C_emits = 5520 */ colon }}}, /* CENTRY "emits" emits 5 h 5528 */
	{.type Here, {.p 5528 }},	/* 5528 360 */
	{.type There, {.p 360 }},	/* 5528 360 */
	{.type Here, {.p 5528 }},	/* 5528 360 */
	{.type There, {.p 360 }},	/* 5528 360 */
	{.type Here, {.p 5528 }},	/* 5528 360 */
	{.type There, {.p 360 }},	/* 5528 360 */
	{.type FromDictionary, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5536 */
	{.type Here, {.p 5536 }},	/* 5536 360 */
	{.type There, {.p 360 }},	/* 5536 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5544 */
	{.type Here, {.p 5544 }},	/* 5544 360 */
	{.type There, {.p 360 }},	/* 5544 360 */
	{.type FromDictionary, {.p L_C_emits_1}, .src = "dd L_C_emits_1"},		/* dd L_C_emits_1 5552 */
	{.type Here, {.p 5552 }},	/* 5552 360 */
	{.type There, {.p 360 }},	/* 5552 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5560 */
	{.type Here, {.p 5560 }},	/* 5560 360 */
	{.type There, {.p 360 }},	/* 5560 360 */
	{.type FromDictionary, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5568 */
	{.type Here, {.p 5568 }},	/* 5568 360 */
	{.type There, {.p 360 }},	/* 5568 360 */
	{.type FromDictionary, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5576 */
	{.type Here, {.p 5576 }},	/* 5576 360 */
	{.type There, {.p 360 }},	/* 5576 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5584 */
	{.type Here, {.p 5584 }},	/* 5584 360 */
	{.type There, {.p 360 }},	/* 5584 360 */
	{.type FromDictionary, {.p L_C_emits}, .src = "dd L_C_emits"},		/* dd L_C_emits 5592 */
	{.type Here, {.p 5592 }},	/* 5592 360 */
	{.type There, {.p 360 }},	/* 5592 360 */
	{.type Here, {.p 5592 }},	/* 5592 360 */
	{.type There, {.p 360 }},	/* 5592 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 5600 */
	{.type Here, {.p 5600 }},	/* 5600 360 */
	{.type There, {.p 360 }},	/* 5600 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5608 */
	{.type Here, {.p 5608 }},	/* 5608 360 */
	{.type There, {.p 360 }},	/* 5608 360 */
	{.type Here, {.p 5608 }},	/* 5608 360 */
	{.type There, {.p 360 }},	/* 5608 360 */
	{.type Header, {.hdr { 6, "spaces", /* C_spaces = 5624 */ colon }}}, /* CENTRY "spaces" spaces 6 h 5632 */
	{.type Here, {.p 5632 }},	/* 5632 360 */
	{.type There, {.p 360 }},	/* 5632 360 */
	{.type Here, {.p 5632 }},	/* 5632 360 */
	{.type There, {.p 360 }},	/* 5632 360 */
	{.type FromDictionary, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5640 */
	{.type Here, {.p 5640 }},	/* 5640 360 */
	{.type There, {.p 360 }},	/* 5640 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 5648 */
	{.type Here, {.p 5648 }},	/* 5648 360 */
	{.type There, {.p 360 }},	/* 5648 360 */
	{.type FromDictionary, {.p C_emits}, .src = "dd C_emits"},		/* dd C_emits 5656 */
	{.type Here, {.p 5656 }},	/* 5656 360 */
	{.type There, {.p 360 }},	/* 5656 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5664 */
	{.type Here, {.p 5664 }},	/* 5664 360 */
	{.type There, {.p 360 }},	/* 5664 360 */
	{.type Here, {.p 5664 }},	/* 5664 360 */
	{.type There, {.p 360 }},	/* 5664 360 */
	{.type Header, {.hdr { 5, "count", /* C_count = 5680 */ colon }}}, /* CENTRY "count" count 5 ; ( 'counted-string -- 'text count ) a = address of counted string ( a - a+1 a[0]) h 5688 */
	{.type Here, {.p 5688 }},	/* 5688 360 */
	{.type There, {.p 360 }},	/* 5688 360 */
	{.type Here, {.p 5688 }},	/* 5688 360 */
	{.type There, {.p 360 }},	/* 5688 360 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 5696 */
	{.type Here, {.p 5696 }},	/* 5696 360 */
	{.type There, {.p 360 }},	/* 5696 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 5704 */
	{.type Here, {.p 5704 }},	/* 5704 360 */
	{.type There, {.p 360 }},	/* 5704 360 */
	{.type FromDictionary, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5712 */
	{.type Here, {.p 5712 }},	/* 5712 360 */
	{.type There, {.p 360 }},	/* 5712 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5720 */
	{.type Here, {.p 5720 }},	/* 5720 360 */
	{.type There, {.p 360 }},	/* 5720 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5728 */
	{.type Here, {.p 5728 }},	/* 5728 360 */
	{.type There, {.p 360 }},	/* 5728 360 */
	{.type Here, {.p 5728 }},	/* 5728 360 */
	{.type There, {.p 360 }},	/* 5728 360 */
	{.type FromDictionary, {.p C_2dup}, .src = "dd C_2dup ; debug show the word name to search"},		/* dd C_2dup ; debug show the word name to search 5736 */
	{.type Here, {.p 5736 }},	/* 5736 360 */
	{.type There, {.p 360 }},	/* 5736 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5744 */
	{.type Here, {.p 5744 }},	/* 5744 360 */
	{.type There, {.p 360 }},	/* 5744 360 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 5752 */
	{.type Here, {.p 5752 }},	/* 5752 360 */
	{.type There, {.p 360 }},	/* 5752 360 */
	{.type Here, {.p 5752 }},	/* 5752 360 */
	{.type There, {.p 360 }},	/* 5752 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush ; debug show the dictionary entry"},		/* dd M_rpush ; debug show the dictionary entry 5760 */
	{.type Here, {.p 5760 }},	/* 5760 360 */
	{.type There, {.p 360 }},	/* 5760 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 5768 */
	{.type Here, {.p 5768 }},	/* 5768 360 */
	{.type There, {.p 360 }},	/* 5768 360 */
	{.type FromDictionary, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 5776 */
	{.type Here, {.p 5776 }},	/* 5776 360 */
	{.type There, {.p 360 }},	/* 5776 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5784 */
	{.type Here, {.p 5784 }},	/* 5784 360 */
	{.type There, {.p 360 }},	/* 5784 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5792 */
	{.type Here, {.p 5792 }},	/* 5792 360 */
	{.type There, {.p 360 }},	/* 5792 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5800 */
	{.type Here, {.p 5800 }},	/* 5800 360 */
	{.type There, {.p 360 }},	/* 5800 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 5808 */
	{.type Here, {.p 5808 }},	/* 5808 360 */
	{.type There, {.p 360 }},	/* 5808 360 */
	{.type Here, {.p 5808 }},	/* 5808 360 */
	{.type There, {.p 360 }},	/* 5808 360 */
	{.type Header, {.hdr { 7, "compare", /* C_compare = 5824 */ colon }}}, /* CENTRY "compare" compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search h 5832 */
	{.type Here, {.p 5832 }},	/* 5832 360 */
	{.type There, {.p 360 }},	/* 5832 360 */
	{.type Here, {.p 5832 }},	/* 5832 360 */
	{.type There, {.p 360 }},	/* 5832 360 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 )"},		/* dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 5840 */
	{.type Here, {.p 5840 }},	/* 5840 360 */
	{.type There, {.p 360 }},	/* 5840 360 */
	{.type FromDictionary, {.p C_2dup}, .src = "dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 )"},		/* dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 ) 5848 */
	{.type Here, {.p 5848 }},	/* 5848 360 */
	{.type There, {.p 360 }},	/* 5848 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- ) 5856 */
	{.type Here, {.p 5856 }},	/* 5856 360 */
	{.type There, {.p 360 }},	/* 5856 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- ) 5864 */
	{.type Here, {.p 5864 }},	/* 5864 360 */
	{.type There, {.p 360 }},	/* 5864 360 */
	{.type FromDictionary, {.p C_min}, .src = "dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- )"},		/* dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- ) 5872 */
	{.type Here, {.p 5872 }},	/* 5872 360 */
	{.type There, {.p 360 }},	/* 5872 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5880 */
	{.type Here, {.p 5880 }},	/* 5880 360 */
	{.type There, {.p 360 }},	/* 5880 360 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- ) 5888 */
	{.type Here, {.p 5888 }},	/* 5888 360 */
	{.type There, {.p 360 }},	/* 5888 360 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- )"},		/* dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- ) 5896 */
	{.type Here, {.p 5896 }},	/* 5896 360 */
	{.type There, {.p 360 }},	/* 5896 360 */
	{.type Here, {.p 5896 }},	/* 5896 360 */
	{.type There, {.p 360 }},	/* 5896 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5904 */
	{.type Here, {.p 5904 }},	/* 5904 360 */
	{.type There, {.p 360 }},	/* 5904 360 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 5912 */
	{.type Here, {.p 5912 }},	/* 5912 360 */
	{.type There, {.p 360 }},	/* 5912 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 5920 */
	{.type Here, {.p 5920 }},	/* 5920 360 */
	{.type There, {.p 360 }},	/* 5920 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5928 */
	{.type Here, {.p 5928 }},	/* 5928 360 */
	{.type There, {.p 360 }},	/* 5928 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5936 */
	{.type Here, {.p 5936 }},	/* 5936 360 */
	{.type There, {.p 360 }},	/* 5936 360 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 5944 */
	{.type Here, {.p 5944 }},	/* 5944 360 */
	{.type There, {.p 360 }},	/* 5944 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 5952 */
	{.type Here, {.p 5952 }},	/* 5952 360 */
	{.type There, {.p 360 }},	/* 5952 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5960 */
	{.type Here, {.p 5960 }},	/* 5960 360 */
	{.type There, {.p 360 }},	/* 5960 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 5968 */
	{.type Here, {.p 5968 }},	/* 5968 360 */
	{.type There, {.p 360 }},	/* 5968 360 */
	{.type FromDictionary, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 5976 */
	{.type Here, {.p 5976 }},	/* 5976 360 */
	{.type There, {.p 360 }},	/* 5976 360 */
	{.type FromDictionary, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5984 */
	{.type Here, {.p 5984 }},	/* 5984 360 */
	{.type There, {.p 360 }},	/* 5984 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5992 */
	{.type Here, {.p 5992 }},	/* 5992 360 */
	{.type There, {.p 360 }},	/* 5992 360 */
	{.type FromDictionary, {.p L_C_compare_1}, .src = "dd L_C_compare_1		; matches"},		/* dd L_C_compare_1		; matches 6000 */
	{.type Here, {.p 6000 }},	/* 6000 360 */
	{.type There, {.p 360 }},	/* 6000 360 */
	{.type FromDictionary, {.p C_2nip}, .src = "dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- )"},		/* dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- ) 6008 */
	{.type Here, {.p 6008 }},	/* 6008 360 */
	{.type There, {.p 360 }},	/* 6008 360 */
	{.type FromDictionary, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2)"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2) 6016 */
	{.type Here, {.p 6016 }},	/* 6016 360 */
	{.type There, {.p 360 }},	/* 6016 360 */
	{.type FromDictionary, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 -- )"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 -- ) 6024 */
	{.type Here, {.p 6024 }},	/* 6024 360 */
	{.type There, {.p 360 }},	/* 6024 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6032 */
	{.type Here, {.p 6032 }},	/* 6032 360 */
	{.type There, {.p 360 }},	/* 6032 360 */
	{.type Here, {.p 6032 }},	/* 6032 360 */
	{.type There, {.p 360 }},	/* 6032 360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6040 */
	{.type Here, {.p 6040 }},	/* 6040 360 */
	{.type There, {.p 360 }},	/* 6040 360 */
	{.type FromDictionary, {.p L_C_compare}, .src = "dd L_C_compare"},		/* dd L_C_compare 6048 */
	{.type Here, {.p 6048 }},	/* 6048 360 */
	{.type There, {.p 360 }},	/* 6048 360 */
	{.type FromDictionary, {.p C_2drop}, .src = "dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- )"},		/* dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- ) 6056 */
	{.type Here, {.p 6056 }},	/* 6056 360 */
	{.type There, {.p 360 }},	/* 6056 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6064 */
	{.type Here, {.p 6064 }},	/* 6064 360 */
	{.type There, {.p 360 }},	/* 6064 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( n2 n1 -- ) (R -- )"},		/* dd M_rpop	; ( n2 n1 -- ) (R -- ) 6072 */
	{.type Here, {.p 6072 }},	/* 6072 360 */
	{.type There, {.p 360 }},	/* 6072 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus	; ( -- n1-n2 )"},		/* dd M_minus	; ( -- n1-n2 ) 6080 */
	{.type Here, {.p 6080 }},	/* 6080 360 */
	{.type There, {.p 360 }},	/* 6080 360 */
	{.type FromDictionary, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 6088 */
	{.type Here, {.p 6088 }},	/* 6088 360 */
	{.type There, {.p 360 }},	/* 6088 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6096 */
	{.type Here, {.p 6096 }},	/* 6096 360 */
	{.type There, {.p 360 }},	/* 6096 360 */
	{.type Here, {.p 6096 }},	/* 6096 360 */
	{.type There, {.p 360 }},	/* 6096 360 */
	{.type Header, {.hdr { 5, "erase", /* C_erase = 6112 */ colon }}}, /* CENTRY "erase" erase 5 h 6120 */
	{.type Here, {.p 6120 }},	/* 6120 360 */
	{.type There, {.p 360 }},	/* 6120 360 */
	{.type Here, {.p 6120 }},	/* 6120 360 */
	{.type There, {.p 360 }},	/* 6120 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6128 */
	{.type Here, {.p 6128 }},	/* 6128 360 */
	{.type There, {.p 360 }},	/* 6128 360 */
	{.type Absolute, {.p 0}},		/* dd 0 6136 */
	{.type Here, {.p 6136 }},	/* 6136 360 */
	{.type There, {.p 360 }},	/* 6136 360 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6144 */
	{.type Here, {.p 6144 }},	/* 6144 360 */
	{.type There, {.p 360 }},	/* 6144 360 */
	{.type Here, {.p 6144 }},	/* 6144 360 */
	{.type There, {.p 360 }},	/* 6144 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6152 */
	{.type Here, {.p 6152 }},	/* 6152 360 */
	{.type There, {.p 360 }},	/* 6152 360 */
	{.type Absolute, {.p 0}},		/* dd 0 6160 */
	{.type Here, {.p 6160 }},	/* 6160 360 */
	{.type There, {.p 360 }},	/* 6160 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6168 */
	{.type Here, {.p 6168 }},	/* 6168 360 */
	{.type There, {.p 360 }},	/* 6168 360 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6176 */
	{.type Here, {.p 6176 }},	/* 6176 360 */
	{.type There, {.p 360 }},	/* 6176 360 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 6184 */
	{.type Here, {.p 6184 }},	/* 6184 360 */
	{.type There, {.p 360 }},	/* 6184 360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6192 */
	{.type Here, {.p 6192 }},	/* 6192 360 */
	{.type There, {.p 360 }},	/* 6192 360 */
	{.type FromDictionary, {.p L_C_erase}, .src = "dd L_C_erase"},		/* dd L_C_erase 6200 */
	{.type Here, {.p 6200 }},	/* 6200 360 */
	{.type There, {.p 360 }},	/* 6200 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6208 */
	{.type Here, {.p 6208 }},	/* 6208 360 */
	{.type There, {.p 360 }},	/* 6208 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6216 */
	{.type Here, {.p 6216 }},	/* 6216 360 */
	{.type There, {.p 360 }},	/* 6216 360 */
	{.type Here, {.p 6216 }},	/* 6216 360 */
	{.type There, {.p 360 }},	/* 6216 360 */
	{.type Header, {.hdr { 4, "fill", /* C_fill = 6232 */ colon }}}, /* CENTRY "fill" fill 4 h 6240 */
	{.type Here, {.p 6240 }},	/* 6240 360 */
	{.type There, {.p 360 }},	/* 6240 360 */
	{.type Here, {.p 6240 }},	/* 6240 360 */
	{.type There, {.p 360 }},	/* 6240 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6248 */
	{.type Here, {.p 6248 }},	/* 6248 360 */
	{.type There, {.p 360 }},	/* 6248 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6256 */
	{.type Here, {.p 6256 }},	/* 6256 360 */
	{.type There, {.p 360 }},	/* 6256 360 */
	{.type Absolute, {.p 0}},		/* dd 0 6264 */
	{.type Here, {.p 6264 }},	/* 6264 360 */
	{.type There, {.p 360 }},	/* 6264 360 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6272 */
	{.type Here, {.p 6272 }},	/* 6272 360 */
	{.type There, {.p 360 }},	/* 6272 360 */
	{.type Here, {.p 6272 }},	/* 6272 360 */
	{.type There, {.p 360 }},	/* 6272 360 */
	{.type FromDictionary, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 6280 */
	{.type Here, {.p 6280 }},	/* 6280 360 */
	{.type There, {.p 360 }},	/* 6280 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6288 */
	{.type Here, {.p 6288 }},	/* 6288 360 */
	{.type There, {.p 360 }},	/* 6288 360 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6296 */
	{.type Here, {.p 6296 }},	/* 6296 360 */
	{.type There, {.p 360 }},	/* 6296 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6304 */
	{.type Here, {.p 6304 }},	/* 6304 360 */
	{.type There, {.p 360 }},	/* 6304 360 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6312 */
	{.type Here, {.p 6312 }},	/* 6312 360 */
	{.type There, {.p 360 }},	/* 6312 360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6320 */
	{.type Here, {.p 6320 }},	/* 6320 360 */
	{.type There, {.p 360 }},	/* 6320 360 */
	{.type FromDictionary, {.p L_C_fill}, .src = "dd L_C_fill"},		/* dd L_C_fill 6328 */
	{.type Here, {.p 6328 }},	/* 6328 360 */
	{.type There, {.p 360 }},	/* 6328 360 */
	{.type FromDictionary, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 6336 */
	{.type Here, {.p 6336 }},	/* 6336 360 */
	{.type There, {.p 360 }},	/* 6336 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6344 */
	{.type Here, {.p 6344 }},	/* 6344 360 */
	{.type There, {.p 360 }},	/* 6344 360 */
	{.type Here, {.p 6344 }},	/* 6344 360 */
	{.type There, {.p 360 }},	/* 6344 360 */
	{.type Header, {.hdr { 5, "blank", /* C_blank = 6360 */ colon }}}, /* CENTRY "blank" blank 5 h 6368 */
	{.type Here, {.p 6368 }},	/* 6368 360 */
	{.type There, {.p 360 }},	/* 6368 360 */
	{.type Here, {.p 6368 }},	/* 6368 360 */
	{.type There, {.p 360 }},	/* 6368 360 */
	{.type FromDictionary, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 6376 */
	{.type Here, {.p 6376 }},	/* 6376 360 */
	{.type There, {.p 360 }},	/* 6376 360 */
	{.type FromDictionary, {.p C_fill}, .src = "dd C_fill"},		/* dd C_fill 6384 */
	{.type Here, {.p 6384 }},	/* 6384 360 */
	{.type There, {.p 360 }},	/* 6384 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6392 */
	{.type Here, {.p 6392 }},	/* 6392 360 */
	{.type There, {.p 360 }},	/* 6392 360 */
	{.type Here, {.p 6392 }},	/* 6392 360 */
	{.type There, {.p 360 }},	/* 6392 360 */
	{.type Header, {.hdr { 6, "search", /* C_search = 6408 */ colon }}}, /* CENTRY "search" search 6 h 6416 */
	{.type Here, {.p 6416 }},	/* 6416 360 */
	{.type There, {.p 360 }},	/* 6416 360 */
	{.type Here, {.p 6416 }},	/* 6416 360 */
	{.type There, {.p 360 }},	/* 6416 360 */
	{.type FromDictionary, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6424 */
	{.type Here, {.p 6424 }},	/* 6424 360 */
	{.type There, {.p 360 }},	/* 6424 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6432 */
	{.type Here, {.p 6432 }},	/* 6432 360 */
	{.type There, {.p 360 }},	/* 6432 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6440 */
	{.type Here, {.p 6440 }},	/* 6440 360 */
	{.type There, {.p 360 }},	/* 6440 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 6448 */
	{.type Here, {.p 6448 }},	/* 6448 360 */
	{.type There, {.p 360 }},	/* 6448 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 6456 */
	{.type Here, {.p 6456 }},	/* 6456 360 */
	{.type There, {.p 360 }},	/* 6456 360 */
	{.type FromDictionary, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6464 */
	{.type Here, {.p 6464 }},	/* 6464 360 */
	{.type There, {.p 360 }},	/* 6464 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6472 */
	{.type Here, {.p 6472 }},	/* 6472 360 */
	{.type There, {.p 360 }},	/* 6472 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6480 */
	{.type Here, {.p 6480 }},	/* 6480 360 */
	{.type There, {.p 360 }},	/* 6480 360 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 6488 */
	{.type Here, {.p 6488 }},	/* 6488 360 */
	{.type There, {.p 360 }},	/* 6488 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6496 */
	{.type Here, {.p 6496 }},	/* 6496 360 */
	{.type There, {.p 360 }},	/* 6496 360 */
	{.type Absolute, {.p 0}},		/* dd 0 6504 */
	{.type Here, {.p 6504 }},	/* 6504 360 */
	{.type There, {.p 360 }},	/* 6504 360 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6512 */
	{.type Here, {.p 6512 }},	/* 6512 360 */
	{.type There, {.p 360 }},	/* 6512 360 */
	{.type Here, {.p 6512 }},	/* 6512 360 */
	{.type There, {.p 360 }},	/* 6512 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6520 */
	{.type Here, {.p 6520 }},	/* 6520 360 */
	{.type There, {.p 360 }},	/* 6520 360 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6528 */
	{.type Here, {.p 6528 }},	/* 6528 360 */
	{.type There, {.p 360 }},	/* 6528 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6536 */
	{.type Here, {.p 6536 }},	/* 6536 360 */
	{.type There, {.p 360 }},	/* 6536 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6544 */
	{.type Here, {.p 6544 }},	/* 6544 360 */
	{.type There, {.p 360 }},	/* 6544 360 */
	{.type FromDictionary, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6552 */
	{.type Here, {.p 6552 }},	/* 6552 360 */
	{.type There, {.p 360 }},	/* 6552 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6560 */
	{.type Here, {.p 6560 }},	/* 6560 360 */
	{.type There, {.p 360 }},	/* 6560 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6568 */
	{.type Here, {.p 6568 }},	/* 6568 360 */
	{.type There, {.p 360 }},	/* 6568 360 */
	{.type FromDictionary, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6576 */
	{.type Here, {.p 6576 }},	/* 6576 360 */
	{.type There, {.p 360 }},	/* 6576 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6584 */
	{.type Here, {.p 6584 }},	/* 6584 360 */
	{.type There, {.p 360 }},	/* 6584 360 */
	{.type FromDictionary, {.p C_compare}, .src = "dd C_compare"},		/* dd C_compare 6592 */
	{.type Here, {.p 6592 }},	/* 6592 360 */
	{.type There, {.p 360 }},	/* 6592 360 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 6600 */
	{.type Here, {.p 6600 }},	/* 6600 360 */
	{.type There, {.p 360 }},	/* 6600 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 6608 */
	{.type Here, {.p 6608 }},	/* 6608 360 */
	{.type There, {.p 360 }},	/* 6608 360 */
	{.type FromDictionary, {.p L_C_search_1}, .src = "dd L_C_search_1"},		/* dd L_C_search_1 6616 */
	{.type Here, {.p 6616 }},	/* 6616 360 */
	{.type There, {.p 360 }},	/* 6616 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6624 */
	{.type Here, {.p 6624 }},	/* 6624 360 */
	{.type There, {.p 360 }},	/* 6624 360 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6632 */
	{.type Here, {.p 6632 }},	/* 6632 360 */
	{.type There, {.p 360 }},	/* 6632 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6640 */
	{.type Here, {.p 6640 }},	/* 6640 360 */
	{.type There, {.p 360 }},	/* 6640 360 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6648 */
	{.type Here, {.p 6648 }},	/* 6648 360 */
	{.type There, {.p 360 }},	/* 6648 360 */
	{.type FromDictionary, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 6656 */
	{.type Here, {.p 6656 }},	/* 6656 360 */
	{.type There, {.p 360 }},	/* 6656 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6664 */
	{.type Here, {.p 6664 }},	/* 6664 360 */
	{.type There, {.p 360 }},	/* 6664 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6672 */
	{.type Here, {.p 6672 }},	/* 6672 360 */
	{.type There, {.p 360 }},	/* 6672 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6680 */
	{.type Here, {.p 6680 }},	/* 6680 360 */
	{.type There, {.p 360 }},	/* 6680 360 */
	{.type FromDictionary, {.p C_true}, .src = "dd C_true"},		/* dd C_true 6688 */
	{.type Here, {.p 6688 }},	/* 6688 360 */
	{.type There, {.p 360 }},	/* 6688 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6696 */
	{.type Here, {.p 6696 }},	/* 6696 360 */
	{.type There, {.p 360 }},	/* 6696 360 */
	{.type Here, {.p 6696 }},	/* 6696 360 */
	{.type There, {.p 360 }},	/* 6696 360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6704 */
	{.type Here, {.p 6704 }},	/* 6704 360 */
	{.type There, {.p 360 }},	/* 6704 360 */
	{.type FromDictionary, {.p L_C_search}, .src = "dd L_C_search"},		/* dd L_C_search 6712 */
	{.type Here, {.p 6712 }},	/* 6712 360 */
	{.type There, {.p 360 }},	/* 6712 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6720 */
	{.type Here, {.p 6720 }},	/* 6720 360 */
	{.type There, {.p 360 }},	/* 6720 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6728 */
	{.type Here, {.p 6728 }},	/* 6728 360 */
	{.type There, {.p 360 }},	/* 6728 360 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false"},		/* dd C_false 6736 */
	{.type Here, {.p 6736 }},	/* 6736 360 */
	{.type There, {.p 360 }},	/* 6736 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6744 */
	{.type Here, {.p 6744 }},	/* 6744 360 */
	{.type There, {.p 360 }},	/* 6744 360 */
	{.type Here, {.p 6744 }},	/* 6744 360 */
	{.type There, {.p 360 }},	/* 6744 360 */
	{.type Header, {.hdr { 4, "here", /* C_here = 6760 */ colon }}}, /* CENTRY "here" here 4 h 6768 */
	{.type Here, {.p 6768 }},	/* 6768 360 */
	{.type There, {.p 360 }},	/* 6768 360 */
	{.type Here, {.p 6768 }},	/* 6768 360 */
	{.type There, {.p 360 }},	/* 6768 360 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp		; the address on the top of stack is 0x583288, which is correct"},		/* dd MV_Dp		; the address on the top of stack is 0x583288, which is correct 6776 */
	{.type Here, {.p 6776 }},	/* 6776 360 */
	{.type There, {.p 360 }},	/* 6776 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6784 */
	{.type Here, {.p 6784 }},	/* 6784 360 */
	{.type There, {.p 360 }},	/* 6784 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6792 */
	{.type Here, {.p 6792 }},	/* 6792 360 */
	{.type There, {.p 360 }},	/* 6792 360 */
	{.type Here, {.p 6792 }},	/* 6792 360 */
	{.type There, {.p 360 }},	/* 6792 360 */
	{.type Header, {.hdr { 5, "there", /* C_there = 6808 */ colon }}}, /* CENTRY "there" there 5 ; variable here h 6816 */
	{.type Here, {.p 6816 }},	/* 6816 360 */
	{.type There, {.p 360 }},	/* 6816 360 */
	{.type Here, {.p 6816 }},	/* 6816 360 */
	{.type There, {.p 360 }},	/* 6816 360 */
	{.type FromDictionary, {.p MV_Vp}, .src = "dd MV_Vp"},		/* dd MV_Vp 6824 */
	{.type Here, {.p 6824 }},	/* 6824 360 */
	{.type There, {.p 360 }},	/* 6824 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6832 */
	{.type Here, {.p 6832 }},	/* 6832 360 */
	{.type There, {.p 360 }},	/* 6832 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6840 */
	{.type Here, {.p 6840 }},	/* 6840 360 */
	{.type There, {.p 360 }},	/* 6840 360 */
	{.type Here, {.p 6840 }},	/* 6840 360 */
	{.type There, {.p 360 }},	/* 6840 360 */
	{.type Header, {.hdr { 1, ",", /* C_comma = 6856 */ colon }}}, /* CENTRY "," comma 1 h 6864 */
	{.type Here, {.p 6864 }},	/* 6864 360 */
	{.type There, {.p 360 }},	/* 6864 360 */
	{.type Here, {.p 6864 }},	/* 6864 360 */
	{.type There, {.p 360 }},	/* 6864 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6872 */
	{.type Here, {.p 6872 }},	/* 6872 360 */
	{.type There, {.p 360 }},	/* 6872 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6880 */
	{.type Here, {.p 6880 }},	/* 6880 360 */
	{.type There, {.p 360 }},	/* 6880 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6888 */
	{.type Here, {.p 6888 }},	/* 6888 360 */
	{.type There, {.p 360 }},	/* 6888 360 */
	{.type Absolute, {.p 8}},		/* dd 8 6896 */
	{.type Here, {.p 6896 }},	/* 6896 360 */
	{.type There, {.p 360 }},	/* 6896 360 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 6904 */
	{.type Here, {.p 6904 }},	/* 6904 360 */
	{.type There, {.p 360 }},	/* 6904 360 */
	{.type FromDictionary, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6912 */
	{.type Here, {.p 6912 }},	/* 6912 360 */
	{.type There, {.p 360 }},	/* 6912 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6920 */
	{.type Here, {.p 6920 }},	/* 6920 360 */
	{.type There, {.p 360 }},	/* 6920 360 */
	{.type Here, {.p 6920 }},	/* 6920 360 */
	{.type There, {.p 360 }},	/* 6920 360 */
	{.type Header, {.hdr { 2, "c,", /* C_c = 6936 */ colon }}}, /* CENTRY "c," c 2 h 6944 */
	{.type Here, {.p 6944 }},	/* 6944 360 */
	{.type There, {.p 360 }},	/* 6944 360 */
	{.type Here, {.p 6944 }},	/* 6944 360 */
	{.type There, {.p 360 }},	/* 6944 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 6952 */
	{.type Here, {.p 6952 }},	/* 6952 360 */
	{.type There, {.p 360 }},	/* 6952 360 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6960 */
	{.type Here, {.p 6960 }},	/* 6960 360 */
	{.type There, {.p 360 }},	/* 6960 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6968 */
	{.type Here, {.p 6968 }},	/* 6968 360 */
	{.type There, {.p 360 }},	/* 6968 360 */
	{.type Absolute, {.p 1}},		/* dd 1 6976 */
	{.type Here, {.p 6976 }},	/* 6976 360 */
	{.type There, {.p 360 }},	/* 6976 360 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 6984 */
	{.type Here, {.p 6984 }},	/* 6984 360 */
	{.type There, {.p 360 }},	/* 6984 360 */
	{.type FromDictionary, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 6992 */
	{.type Here, {.p 6992 }},	/* 6992 360 */
	{.type There, {.p 360 }},	/* 6992 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7000 */
	{.type Here, {.p 7000 }},	/* 7000 360 */
	{.type There, {.p 360 }},	/* 7000 360 */
	{.type Here, {.p 7000 }},	/* 7000 360 */
	{.type There, {.p 360 }},	/* 7000 360 */
	{.type Header, {.hdr { 5, "allot", /* C_allot = 7016 */ colon }}}, /* CENTRY "allot" allot 5 ; ( n -- ) here = here+n h 7024 */
	{.type Here, {.p 7024 }},	/* 7024 360 */
	{.type There, {.p 360 }},	/* 7024 360 */
	{.type Here, {.p 7024 }},	/* 7024 360 */
	{.type There, {.p 360 }},	/* 7024 360 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 7032 */
	{.type Here, {.p 7032 }},	/* 7032 360 */
	{.type There, {.p 360 }},	/* 7032 360 */
	{.type FromDictionary, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 7040 */
	{.type Here, {.p 7040 }},	/* 7040 360 */
	{.type There, {.p 360 }},	/* 7040 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7048 */
	{.type Here, {.p 7048 }},	/* 7048 360 */
	{.type There, {.p 360 }},	/* 7048 360 */
	{.type Here, {.p 7048 }},	/* 7048 360 */
	{.type There, {.p 360 }},	/* 7048 360 */
	{.type Header, {.hdr { 6, "vallot", /* C_vallot = 7064 */ colon }}}, /* CENTRY "vallot" vallot 6 ; allot on the variable space ( n -- ) there = there+n h 7072 */
	{.type Here, {.p 7072 }},	/* 7072 360 */
	{.type There, {.p 360 }},	/* 7072 360 */
	{.type Here, {.p 7072 }},	/* 7072 360 */
	{.type There, {.p 360 }},	/* 7072 360 */
	{.type FromDictionary, {.p MV_Vp}, .src = "dd MV_Vp"},		/* dd MV_Vp 7080 */
	{.type Here, {.p 7080 }},	/* 7080 360 */
	{.type There, {.p 360 }},	/* 7080 360 */
	{.type FromDictionary, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 7088 */
	{.type Here, {.p 7088 }},	/* 7088 360 */
	{.type There, {.p 360 }},	/* 7088 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7096 */
	{.type Here, {.p 7096 }},	/* 7096 360 */
	{.type There, {.p 360 }},	/* 7096 360 */
	{.type Here, {.p 7096 }},	/* 7096 360 */
	{.type There, {.p 360 }},	/* 7096 360 */
	{.type Header, {.hdr { 3, "pad", /* C_pad = 7112 */ colon }}}, /* CENTRY "pad" pad 3 h 7120 */
	{.type Here, {.p 7120 }},	/* 7120 360 */
	{.type There, {.p 360 }},	/* 7120 360 */
	{.type Here, {.p 7120 }},	/* 7120 360 */
	{.type There, {.p 360 }},	/* 7120 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 7128 */
	{.type Here, {.p 7128 }},	/* 7128 360 */
	{.type There, {.p 360 }},	/* 7128 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7136 */
	{.type Here, {.p 7136 }},	/* 7136 360 */
	{.type There, {.p 360 }},	/* 7136 360 */
	{.type Absolute, {.p 256}},		/* dd 256 7144 */
	{.type Here, {.p 7144 }},	/* 7144 360 */
	{.type There, {.p 360 }},	/* 7144 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7152 */
	{.type Here, {.p 7152 }},	/* 7152 360 */
	{.type There, {.p 360 }},	/* 7152 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7160 */
	{.type Here, {.p 7160 }},	/* 7160 360 */
	{.type There, {.p 360 }},	/* 7160 360 */
	{.type Header, {.hdr { 5, "align", /* C_align = 7176 */ colon }}}, /* CENTRY "align" align 5 ; ( -- ) align here to a cell boundary h 7184 */
	{.type Here, {.p 7184 }},	/* 7184 360 */
	{.type There, {.p 360 }},	/* 7184 360 */
	{.type Here, {.p 7184 }},	/* 7184 360 */
	{.type There, {.p 360 }},	/* 7184 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here		; Dp @"},		/* dd C_here		; Dp @ 7192 */
	{.type Here, {.p 7192 }},	/* 7192 360 */
	{.type There, {.p 360 }},	/* 7192 360 */
	{.type FromDictionary, {.p C_aligned}, .src = "dd C_aligned	; here is aligned to a multiple of 8"},		/* dd C_aligned	; here is aligned to a multiple of 8 7200 */
	{.type Here, {.p 7200 }},	/* 7200 360 */
	{.type There, {.p 360 }},	/* 7200 360 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp			; store the aligned here at Dp"},		/* dd MV_Dp			; store the aligned here at Dp 7208 */
	{.type Here, {.p 7208 }},	/* 7208 360 */
	{.type There, {.p 360 }},	/* 7208 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store		; Dp contains aligned_here"},		/* dd M_store		; Dp contains aligned_here 7216 */
	{.type Here, {.p 7216 }},	/* 7216 360 */
	{.type There, {.p 360 }},	/* 7216 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7224 */
	{.type Here, {.p 7224 }},	/* 7224 360 */
	{.type There, {.p 360 }},	/* 7224 360 */
	{.type Header, {.hdr { 6, "unused", /* C_unused = 7240 */ colon }}}, /* CENTRY "unused" unused 6 h 7248 */
	{.type Here, {.p 7248 }},	/* 7248 360 */
	{.type There, {.p 360 }},	/* 7248 360 */
	{.type Here, {.p 7248 }},	/* 7248 360 */
	{.type There, {.p 360 }},	/* 7248 360 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 7256 */
	{.type Here, {.p 7256 }},	/* 7256 360 */
	{.type There, {.p 360 }},	/* 7256 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7264 */
	{.type Here, {.p 7264 }},	/* 7264 360 */
	{.type There, {.p 360 }},	/* 7264 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 7272 */
	{.type Here, {.p 7272 }},	/* 7272 360 */
	{.type There, {.p 360 }},	/* 7272 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7280 */
	{.type Here, {.p 7280 }},	/* 7280 360 */
	{.type There, {.p 360 }},	/* 7280 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7288 */
	{.type Here, {.p 7288 }},	/* 7288 360 */
	{.type There, {.p 360 }},	/* 7288 360 */
	{.type Header, {.hdr { 2, "<#", /* C_fromhash = 7304 */ colon }}}, /* CENTRY "<#" fromhash 2 h 7312 */
	{.type Here, {.p 7312 }},	/* 7312 360 */
	{.type There, {.p 360 }},	/* 7312 360 */
	{.type Here, {.p 7312 }},	/* 7312 360 */
	{.type There, {.p 360 }},	/* 7312 360 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7320 */
	{.type Here, {.p 7320 }},	/* 7320 360 */
	{.type There, {.p 360 }},	/* 7320 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7328 */
	{.type Here, {.p 7328 }},	/* 7328 360 */
	{.type There, {.p 360 }},	/* 7328 360 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7336 */
	{.type Here, {.p 7336 }},	/* 7336 360 */
	{.type There, {.p 360 }},	/* 7336 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7344 */
	{.type Here, {.p 7344 }},	/* 7344 360 */
	{.type There, {.p 360 }},	/* 7344 360 */
	{.type FromDictionary, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7352 */
	{.type Here, {.p 7352 }},	/* 7352 360 */
	{.type There, {.p 360 }},	/* 7352 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7360 */
	{.type Here, {.p 7360 }},	/* 7360 360 */
	{.type There, {.p 360 }},	/* 7360 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7368 */
	{.type Here, {.p 7368 }},	/* 7368 360 */
	{.type There, {.p 360 }},	/* 7368 360 */
	{.type Here, {.p 7368 }},	/* 7368 360 */
	{.type There, {.p 360 }},	/* 7368 360 */
	{.type Header, {.hdr { 1, "#", /* C_hash = 7384 */ colon }}}, /* CENTRY "#" hash 1 h 7392 */
	{.type Here, {.p 7392 }},	/* 7392 360 */
	{.type There, {.p 360 }},	/* 7392 360 */
	{.type Here, {.p 7392 }},	/* 7392 360 */
	{.type There, {.p 360 }},	/* 7392 360 */
	{.type FromDictionary, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 7400 */
	{.type Here, {.p 7400 }},	/* 7400 360 */
	{.type There, {.p 360 }},	/* 7400 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7408 */
	{.type Here, {.p 7408 }},	/* 7408 360 */
	{.type There, {.p 360 }},	/* 7408 360 */
	{.type FromDictionary, {.p M_uslashmod}, .src = "dd M_uslashmod"},		/* dd M_uslashmod 7416 */
	{.type Here, {.p 7416 }},	/* 7416 360 */
	{.type There, {.p 360 }},	/* 7416 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7424 */
	{.type Here, {.p 7424 }},	/* 7424 360 */
	{.type There, {.p 360 }},	/* 7424 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7432 */
	{.type Here, {.p 7432 }},	/* 7432 360 */
	{.type There, {.p 360 }},	/* 7432 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7440 */
	{.type Here, {.p 7440 }},	/* 7440 360 */
	{.type There, {.p 360 }},	/* 7440 360 */
	{.type Absolute, {.p 9}},		/* dd 9 7448 */
	{.type Here, {.p 7448 }},	/* 7448 360 */
	{.type There, {.p 360 }},	/* 7448 360 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 7456 */
	{.type Here, {.p 7456 }},	/* 7456 360 */
	{.type There, {.p 360 }},	/* 7456 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7464 */
	{.type Here, {.p 7464 }},	/* 7464 360 */
	{.type There, {.p 360 }},	/* 7464 360 */
	{.type FromDictionary, {.p L_C_hash}, .src = "dd L_C_hash"},		/* dd L_C_hash 7472 */
	{.type Here, {.p 7472 }},	/* 7472 360 */
	{.type There, {.p 360 }},	/* 7472 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7480 */
	{.type Here, {.p 7480 }},	/* 7480 360 */
	{.type There, {.p 360 }},	/* 7480 360 */
	{.type Absolute, {.p 97}},		/* dd 97 7488 */
	{.type Here, {.p 7488 }},	/* 7488 360 */
	{.type There, {.p 360 }},	/* 7488 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7496 */
	{.type Here, {.p 7496 }},	/* 7496 360 */
	{.type There, {.p 360 }},	/* 7496 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7504 */
	{.type Here, {.p 7504 }},	/* 7504 360 */
	{.type There, {.p 360 }},	/* 7504 360 */
	{.type Absolute, {.p 10}},		/* dd 10 7512 */
	{.type Here, {.p 7512 }},	/* 7512 360 */
	{.type There, {.p 360 }},	/* 7512 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7520 */
	{.type Here, {.p 7520 }},	/* 7520 360 */
	{.type There, {.p 360 }},	/* 7520 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7528 */
	{.type Here, {.p 7528 }},	/* 7528 360 */
	{.type There, {.p 360 }},	/* 7528 360 */
	{.type FromDictionary, {.p L_C_hash_1}, .src = "dd L_C_hash_1"},		/* dd L_C_hash_1 7536 */
	{.type Here, {.p 7536 }},	/* 7536 360 */
	{.type There, {.p 360 }},	/* 7536 360 */
	{.type Here, {.p 7536 }},	/* 7536 360 */
	{.type There, {.p 360 }},	/* 7536 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7544 */
	{.type Here, {.p 7544 }},	/* 7544 360 */
	{.type There, {.p 360 }},	/* 7544 360 */
	{.type Absolute, {.p 48}},		/* dd 48 7552 */
	{.type Here, {.p 7552 }},	/* 7552 360 */
	{.type There, {.p 360 }},	/* 7552 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7560 */
	{.type Here, {.p 7560 }},	/* 7560 360 */
	{.type There, {.p 360 }},	/* 7560 360 */
	{.type Here, {.p 7560 }},	/* 7560 360 */
	{.type There, {.p 360 }},	/* 7560 360 */
	{.type FromDictionary, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7568 */
	{.type Here, {.p 7568 }},	/* 7568 360 */
	{.type There, {.p 360 }},	/* 7568 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7576 */
	{.type Here, {.p 7576 }},	/* 7576 360 */
	{.type There, {.p 360 }},	/* 7576 360 */
	{.type FromDictionary, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7584 */
	{.type Here, {.p 7584 }},	/* 7584 360 */
	{.type There, {.p 360 }},	/* 7584 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7592 */
	{.type Here, {.p 7592 }},	/* 7592 360 */
	{.type There, {.p 360 }},	/* 7592 360 */
	{.type FromDictionary, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7600 */
	{.type Here, {.p 7600 }},	/* 7600 360 */
	{.type There, {.p 360 }},	/* 7600 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7608 */
	{.type Here, {.p 7608 }},	/* 7608 360 */
	{.type There, {.p 360 }},	/* 7608 360 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7616 */
	{.type Here, {.p 7616 }},	/* 7616 360 */
	{.type There, {.p 360 }},	/* 7616 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7624 */
	{.type Here, {.p 7624 }},	/* 7624 360 */
	{.type There, {.p 360 }},	/* 7624 360 */
	{.type Here, {.p 7624 }},	/* 7624 360 */
	{.type There, {.p 360 }},	/* 7624 360 */
	{.type Header, {.hdr { 2, "#s", /* C_hashs = 7640 */ colon }}}, /* CENTRY "#s" hashs 2 h 7648 */
	{.type Here, {.p 7648 }},	/* 7648 360 */
	{.type There, {.p 360 }},	/* 7648 360 */
	{.type Here, {.p 7648 }},	/* 7648 360 */
	{.type There, {.p 360 }},	/* 7648 360 */
	{.type Here, {.p 7648 }},	/* 7648 360 */
	{.type There, {.p 360 }},	/* 7648 360 */
	{.type FromDictionary, {.p C_hash}, .src = "dd C_hash"},		/* dd C_hash 7656 */
	{.type Here, {.p 7656 }},	/* 7656 360 */
	{.type There, {.p 360 }},	/* 7656 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7664 */
	{.type Here, {.p 7664 }},	/* 7664 360 */
	{.type There, {.p 360 }},	/* 7664 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7672 */
	{.type Here, {.p 7672 }},	/* 7672 360 */
	{.type There, {.p 360 }},	/* 7672 360 */
	{.type FromDictionary, {.p L_C_hashs_1}, .src = "dd L_C_hashs_1"},		/* dd L_C_hashs_1 7680 */
	{.type Here, {.p 7680 }},	/* 7680 360 */
	{.type There, {.p 360 }},	/* 7680 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7688 */
	{.type Here, {.p 7688 }},	/* 7688 360 */
	{.type There, {.p 360 }},	/* 7688 360 */
	{.type FromDictionary, {.p L_C_hashs}, .src = "dd L_C_hashs"},		/* dd L_C_hashs 7696 */
	{.type Here, {.p 7696 }},	/* 7696 360 */
	{.type There, {.p 360 }},	/* 7696 360 */
	{.type Here, {.p 7696 }},	/* 7696 360 */
	{.type There, {.p 360 }},	/* 7696 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7704 */
	{.type Here, {.p 7704 }},	/* 7704 360 */
	{.type There, {.p 360 }},	/* 7704 360 */
	{.type Here, {.p 7704 }},	/* 7704 360 */
	{.type There, {.p 360 }},	/* 7704 360 */
	{.type Header, {.hdr { 2, "#>", /* C_hashfrom = 7720 */ colon }}}, /* CENTRY "#>" hashfrom 2 h 7728 */
	{.type Here, {.p 7728 }},	/* 7728 360 */
	{.type There, {.p 360 }},	/* 7728 360 */
	{.type Here, {.p 7728 }},	/* 7728 360 */
	{.type There, {.p 360 }},	/* 7728 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 7736 */
	{.type Here, {.p 7736 }},	/* 7736 360 */
	{.type There, {.p 360 }},	/* 7736 360 */
	{.type FromDictionary, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7744 */
	{.type Here, {.p 7744 }},	/* 7744 360 */
	{.type There, {.p 360 }},	/* 7744 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7752 */
	{.type Here, {.p 7752 }},	/* 7752 360 */
	{.type There, {.p 360 }},	/* 7752 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7760 */
	{.type Here, {.p 7760 }},	/* 7760 360 */
	{.type There, {.p 360 }},	/* 7760 360 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7768 */
	{.type Here, {.p 7768 }},	/* 7768 360 */
	{.type There, {.p 360 }},	/* 7768 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7776 */
	{.type Here, {.p 7776 }},	/* 7776 360 */
	{.type There, {.p 360 }},	/* 7776 360 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7784 */
	{.type Here, {.p 7784 }},	/* 7784 360 */
	{.type There, {.p 360 }},	/* 7784 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7792 */
	{.type Here, {.p 7792 }},	/* 7792 360 */
	{.type There, {.p 360 }},	/* 7792 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7800 */
	{.type Here, {.p 7800 }},	/* 7800 360 */
	{.type There, {.p 360 }},	/* 7800 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7808 */
	{.type Here, {.p 7808 }},	/* 7808 360 */
	{.type There, {.p 360 }},	/* 7808 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7816 */
	{.type Here, {.p 7816 }},	/* 7816 360 */
	{.type There, {.p 360 }},	/* 7816 360 */
	{.type Here, {.p 7816 }},	/* 7816 360 */
	{.type There, {.p 360 }},	/* 7816 360 */
	{.type Header, {.hdr { 4, "hold", /* C_hold = 7832 */ colon }}}, /* CENTRY "hold" hold 4 h 7840 */
	{.type Here, {.p 7840 }},	/* 7840 360 */
	{.type There, {.p 360 }},	/* 7840 360 */
	{.type Here, {.p 7840 }},	/* 7840 360 */
	{.type There, {.p 360 }},	/* 7840 360 */
	{.type FromDictionary, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7848 */
	{.type Here, {.p 7848 }},	/* 7848 360 */
	{.type There, {.p 360 }},	/* 7848 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7856 */
	{.type Here, {.p 7856 }},	/* 7856 360 */
	{.type There, {.p 360 }},	/* 7856 360 */
	{.type FromDictionary, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7864 */
	{.type Here, {.p 7864 }},	/* 7864 360 */
	{.type There, {.p 360 }},	/* 7864 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7872 */
	{.type Here, {.p 7872 }},	/* 7872 360 */
	{.type There, {.p 360 }},	/* 7872 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 7880 */
	{.type Here, {.p 7880 }},	/* 7880 360 */
	{.type There, {.p 360 }},	/* 7880 360 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7888 */
	{.type Here, {.p 7888 }},	/* 7888 360 */
	{.type There, {.p 360 }},	/* 7888 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 7896 */
	{.type Here, {.p 7896 }},	/* 7896 360 */
	{.type There, {.p 360 }},	/* 7896 360 */
	{.type FromDictionary, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7904 */
	{.type Here, {.p 7904 }},	/* 7904 360 */
	{.type There, {.p 360 }},	/* 7904 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7912 */
	{.type Here, {.p 7912 }},	/* 7912 360 */
	{.type There, {.p 360 }},	/* 7912 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7920 */
	{.type Here, {.p 7920 }},	/* 7920 360 */
	{.type There, {.p 360 }},	/* 7920 360 */
	{.type Here, {.p 7920 }},	/* 7920 360 */
	{.type There, {.p 360 }},	/* 7920 360 */
	{.type Header, {.hdr { 4, "sign", /* C_sign = 7936 */ colon }}}, /* CENTRY "sign" sign 4 h 7944 */
	{.type Here, {.p 7944 }},	/* 7944 360 */
	{.type There, {.p 360 }},	/* 7944 360 */
	{.type Here, {.p 7944 }},	/* 7944 360 */
	{.type There, {.p 360 }},	/* 7944 360 */
	{.type FromDictionary, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 7952 */
	{.type Here, {.p 7952 }},	/* 7952 360 */
	{.type There, {.p 360 }},	/* 7952 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7960 */
	{.type Here, {.p 7960 }},	/* 7960 360 */
	{.type There, {.p 360 }},	/* 7960 360 */
	{.type FromDictionary, {.p L_C_sign}, .src = "dd L_C_sign"},		/* dd L_C_sign 7968 */
	{.type Here, {.p 7968 }},	/* 7968 360 */
	{.type There, {.p 360 }},	/* 7968 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7976 */
	{.type Here, {.p 7976 }},	/* 7976 360 */
	{.type There, {.p 360 }},	/* 7976 360 */
	{.type Absolute, {.p 45}},		/* dd 45 7984 */
	{.type Here, {.p 7984 }},	/* 7984 360 */
	{.type There, {.p 360 }},	/* 7984 360 */
	{.type FromDictionary, {.p C_hold}, .src = "dd C_hold"},		/* dd C_hold 7992 */
	{.type Here, {.p 7992 }},	/* 7992 360 */
	{.type There, {.p 360 }},	/* 7992 360 */
	{.type Here, {.p 7992 }},	/* 7992 360 */
	{.type There, {.p 360 }},	/* 7992 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8000 */
	{.type Here, {.p 8000 }},	/* 8000 360 */
	{.type There, {.p 360 }},	/* 8000 360 */
	{.type Here, {.p 8000 }},	/* 8000 360 */
	{.type There, {.p 360 }},	/* 8000 360 */
	{.type Header, {.hdr { 3, "(.)", /* C_paren_dot_paren = 8016 */ colon }}}, /* CENTRY "(.)" paren_dot_paren 3 ; convert the top of stack to a string ( n1 -- 'text n2 ) h 8024 */
	{.type Here, {.p 8024 }},	/* 8024 360 */
	{.type There, {.p 360 }},	/* 8024 360 */
	{.type Here, {.p 8024 }},	/* 8024 360 */
	{.type There, {.p 360 }},	/* 8024 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup		; ( n -- n n )"},		/* dd M_dup		; ( n -- n n ) 8032 */
	{.type Here, {.p 8032 }},	/* 8032 360 */
	{.type There, {.p 360 }},	/* 8032 360 */
	{.type FromDictionary, {.p C_abs}, .src = "dd C_abs		; ( n n -- n u )"},		/* dd C_abs		; ( n n -- n u ) 8040 */
	{.type Here, {.p 8040 }},	/* 8040 360 */
	{.type There, {.p 360 }},	/* 8040 360 */
	{.type FromDictionary, {.p C_fromhash}, .src = "dd C_fromhash	; pad = h+256; >num = pad+1024"},		/* dd C_fromhash	; pad = h+256; >num = pad+1024 8048 */
	{.type Here, {.p 8048 }},	/* 8048 360 */
	{.type There, {.p 360 }},	/* 8048 360 */
	{.type FromDictionary, {.p C_hashs}, .src = "dd C_hashs		; ( n u1 -- n n2 )"},		/* dd C_hashs		; ( n u1 -- n n2 ) 8056 */
	{.type Here, {.p 8056 }},	/* 8056 360 */
	{.type There, {.p 360 }},	/* 8056 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap		; ( n n2 -- n2 n )"},		/* dd M_xswap		; ( n n2 -- n2 n ) 8064 */
	{.type Here, {.p 8064 }},	/* 8064 360 */
	{.type There, {.p 360 }},	/* 8064 360 */
	{.type FromDictionary, {.p C_sign}, .src = "dd C_sign		; ( n2 n -- n2 )"},		/* dd C_sign		; ( n2 n -- n2 ) 8072 */
	{.type Here, {.p 8072 }},	/* 8072 360 */
	{.type There, {.p 360 }},	/* 8072 360 */
	{.type FromDictionary, {.p C_hashfrom}, .src = "dd C_hashfrom	; ( u1 -- a n )"},		/* dd C_hashfrom	; ( u1 -- a n ) 8080 */
	{.type Here, {.p 8080 }},	/* 8080 360 */
	{.type There, {.p 360 }},	/* 8080 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8088 */
	{.type Here, {.p 8088 }},	/* 8088 360 */
	{.type There, {.p 360 }},	/* 8088 360 */
	{.type Here, {.p 8088 }},	/* 8088 360 */
	{.type There, {.p 360 }},	/* 8088 360 */
	{.type Header, {.hdr { 1, ".", /* C_dot = 8104 */ colon }}}, /* CENTRY "." dot 1 ; print the top of stack ( n -- ) h 8112 */
	{.type Here, {.p 8112 }},	/* 8112 360 */
	{.type There, {.p 360 }},	/* 8112 360 */
	{.type Here, {.p 8112 }},	/* 8112 360 */
	{.type There, {.p 360 }},	/* 8112 360 */
	{.type FromDictionary, {.p C_paren_dot_paren}, .src = "dd C_paren_dot_paren ; ( n1 -- 'text n2 )"},		/* dd C_paren_dot_paren ; ( n1 -- 'text n2 ) 8120 */
	{.type Here, {.p 8120 }},	/* 8120 360 */
	{.type There, {.p 360 }},	/* 8120 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 8128 */
	{.type Here, {.p 8128 }},	/* 8128 360 */
	{.type There, {.p 360 }},	/* 8128 360 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 8136 */
	{.type Here, {.p 8136 }},	/* 8136 360 */
	{.type There, {.p 360 }},	/* 8136 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8144 */
	{.type Here, {.p 8144 }},	/* 8144 360 */
	{.type There, {.p 360 }},	/* 8144 360 */
	{.type Here, {.p 8144 }},	/* 8144 360 */
	{.type There, {.p 360 }},	/* 8144 360 */
	{.type Header, {.hdr { 2, ".r", /* C_dotr = 8160 */ colon }}}, /* CENTRY ".r" dotr 2 h 8168 */
	{.type Here, {.p 8168 }},	/* 8168 360 */
	{.type There, {.p 360 }},	/* 8168 360 */
	{.type Here, {.p 8168 }},	/* 8168 360 */
	{.type There, {.p 360 }},	/* 8168 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 8176 */
	{.type Here, {.p 8176 }},	/* 8176 360 */
	{.type There, {.p 360 }},	/* 8176 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8184 */
	{.type Here, {.p 8184 }},	/* 8184 360 */
	{.type There, {.p 360 }},	/* 8184 360 */
	{.type FromDictionary, {.p C_abs}, .src = "dd C_abs"},		/* dd C_abs 8192 */
	{.type Here, {.p 8192 }},	/* 8192 360 */
	{.type There, {.p 360 }},	/* 8192 360 */
	{.type FromDictionary, {.p C_fromhash}, .src = "dd C_fromhash"},		/* dd C_fromhash 8200 */
	{.type Here, {.p 8200 }},	/* 8200 360 */
	{.type There, {.p 360 }},	/* 8200 360 */
	{.type FromDictionary, {.p C_hashs}, .src = "dd C_hashs"},		/* dd C_hashs 8208 */
	{.type Here, {.p 8208 }},	/* 8208 360 */
	{.type There, {.p 360 }},	/* 8208 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 8216 */
	{.type Here, {.p 8216 }},	/* 8216 360 */
	{.type There, {.p 360 }},	/* 8216 360 */
	{.type FromDictionary, {.p C_sign}, .src = "dd C_sign"},		/* dd C_sign 8224 */
	{.type Here, {.p 8224 }},	/* 8224 360 */
	{.type There, {.p 360 }},	/* 8224 360 */
	{.type FromDictionary, {.p C_hashfrom}, .src = "dd C_hashfrom"},		/* dd C_hashfrom 8232 */
	{.type Here, {.p 8232 }},	/* 8232 360 */
	{.type There, {.p 360 }},	/* 8232 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 8240 */
	{.type Here, {.p 8240 }},	/* 8240 360 */
	{.type There, {.p 360 }},	/* 8240 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 8248 */
	{.type Here, {.p 8248 }},	/* 8248 360 */
	{.type There, {.p 360 }},	/* 8248 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8256 */
	{.type Here, {.p 8256 }},	/* 8256 360 */
	{.type There, {.p 360 }},	/* 8256 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8264 */
	{.type Here, {.p 8264 }},	/* 8264 360 */
	{.type There, {.p 360 }},	/* 8264 360 */
	{.type Absolute, {.p 0}},		/* dd 0 8272 */
	{.type Here, {.p 8272 }},	/* 8272 360 */
	{.type There, {.p 360 }},	/* 8272 360 */
	{.type FromDictionary, {.p C_max}, .src = "dd C_max"},		/* dd C_max 8280 */
	{.type Here, {.p 8280 }},	/* 8280 360 */
	{.type There, {.p 360 }},	/* 8280 360 */
	{.type FromDictionary, {.p C_spaces}, .src = "dd C_spaces"},		/* dd C_spaces 8288 */
	{.type Here, {.p 8288 }},	/* 8288 360 */
	{.type There, {.p 360 }},	/* 8288 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 8296 */
	{.type Here, {.p 8296 }},	/* 8296 360 */
	{.type There, {.p 360 }},	/* 8296 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8304 */
	{.type Here, {.p 8304 }},	/* 8304 360 */
	{.type There, {.p 360 }},	/* 8304 360 */
	{.type Header, {.hdr { 3, "hex", /* C_hex = 8320 */ colon }}}, /* CENTRY "hex" hex 3 h 8328 */
	{.type Here, {.p 8328 }},	/* 8328 360 */
	{.type There, {.p 360 }},	/* 8328 360 */
	{.type Here, {.p 8328 }},	/* 8328 360 */
	{.type There, {.p 360 }},	/* 8328 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8336 */
	{.type Here, {.p 8336 }},	/* 8336 360 */
	{.type There, {.p 360 }},	/* 8336 360 */
	{.type Absolute, {.p 16}},		/* dd 16 8344 */
	{.type Here, {.p 8344 }},	/* 8344 360 */
	{.type There, {.p 360 }},	/* 8344 360 */
	{.type FromDictionary, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8352 */
	{.type Here, {.p 8352 }},	/* 8352 360 */
	{.type There, {.p 360 }},	/* 8352 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8360 */
	{.type Here, {.p 8360 }},	/* 8360 360 */
	{.type There, {.p 360 }},	/* 8360 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8368 */
	{.type Here, {.p 8368 }},	/* 8368 360 */
	{.type There, {.p 360 }},	/* 8368 360 */
	{.type Header, {.hdr { 7, "decimal", /* C_decimal = 8384 */ colon }}}, /* CENTRY "decimal" decimal 7 h 8392 */
	{.type Here, {.p 8392 }},	/* 8392 360 */
	{.type There, {.p 360 }},	/* 8392 360 */
	{.type Here, {.p 8392 }},	/* 8392 360 */
	{.type There, {.p 360 }},	/* 8392 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8400 */
	{.type Here, {.p 8400 }},	/* 8400 360 */
	{.type There, {.p 360 }},	/* 8400 360 */
	{.type Absolute, {.p 10}},		/* dd 10 8408 */
	{.type Here, {.p 8408 }},	/* 8408 360 */
	{.type There, {.p 360 }},	/* 8408 360 */
	{.type FromDictionary, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8416 */
	{.type Here, {.p 8416 }},	/* 8416 360 */
	{.type There, {.p 360 }},	/* 8416 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8424 */
	{.type Here, {.p 8424 }},	/* 8424 360 */
	{.type There, {.p 360 }},	/* 8424 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8432 */
	{.type Here, {.p 8432 }},	/* 8432 360 */
	{.type There, {.p 360 }},	/* 8432 360 */
	{.type Here, {.p 8432 }},	/* 8432 360 */
	{.type There, {.p 360 }},	/* 8432 360 */
	{.type Header, {.hdr { 5, "digit", /* C_digit = 8448 */ colon }}}, /* CENTRY "digit" digit 5 ; ( c -- ) h 8456 */
	{.type Here, {.p 8456 }},	/* 8456 360 */
	{.type There, {.p 360 }},	/* 8456 360 */
	{.type Here, {.p 8456 }},	/* 8456 360 */
	{.type There, {.p 360 }},	/* 8456 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8464 */
	{.type Here, {.p 8464 }},	/* 8464 360 */
	{.type There, {.p 360 }},	/* 8464 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8472 */
	{.type Here, {.p 8472 }},	/* 8472 360 */
	{.type There, {.p 360 }},	/* 8472 360 */
	{.type Absolute, {.p 65}},		/* dd 65 8480 */
	{.type Here, {.p 8480 }},	/* 8480 360 */
	{.type There, {.p 360 }},	/* 8480 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8488 */
	{.type Here, {.p 8488 }},	/* 8488 360 */
	{.type There, {.p 360 }},	/* 8488 360 */
	{.type Absolute, {.p 91}},		/* dd 91 8496 */
	{.type Here, {.p 8496 }},	/* 8496 360 */
	{.type There, {.p 360 }},	/* 8496 360 */
	{.type FromDictionary, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8504 */
	{.type Here, {.p 8504 }},	/* 8504 360 */
	{.type There, {.p 360 }},	/* 8504 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8512 */
	{.type Here, {.p 8512 }},	/* 8512 360 */
	{.type There, {.p 360 }},	/* 8512 360 */
	{.type FromDictionary, {.p L_C_digit}, .src = "dd L_C_digit"},		/* dd L_C_digit 8520 */
	{.type Here, {.p 8520 }},	/* 8520 360 */
	{.type There, {.p 360 }},	/* 8520 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8528 */
	{.type Here, {.p 8528 }},	/* 8528 360 */
	{.type There, {.p 360 }},	/* 8528 360 */
	{.type Absolute, {.p 55}},		/* dd 55 8536 */
	{.type Here, {.p 8536 }},	/* 8536 360 */
	{.type There, {.p 360 }},	/* 8536 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8544 */
	{.type Here, {.p 8544 }},	/* 8544 360 */
	{.type There, {.p 360 }},	/* 8544 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8552 */
	{.type Here, {.p 8552 }},	/* 8552 360 */
	{.type There, {.p 360 }},	/* 8552 360 */
	{.type FromDictionary, {.p L_C_digit_1}, .src = "dd L_C_digit_1"},		/* dd L_C_digit_1 8560 */
	{.type Here, {.p 8560 }},	/* 8560 360 */
	{.type There, {.p 360 }},	/* 8560 360 */
	{.type Here, {.p 8560 }},	/* 8560 360 */
	{.type There, {.p 360 }},	/* 8560 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8568 */
	{.type Here, {.p 8568 }},	/* 8568 360 */
	{.type There, {.p 360 }},	/* 8568 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8576 */
	{.type Here, {.p 8576 }},	/* 8576 360 */
	{.type There, {.p 360 }},	/* 8576 360 */
	{.type Absolute, {.p 97}},		/* dd 97 8584 */
	{.type Here, {.p 8584 }},	/* 8584 360 */
	{.type There, {.p 360 }},	/* 8584 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8592 */
	{.type Here, {.p 8592 }},	/* 8592 360 */
	{.type There, {.p 360 }},	/* 8592 360 */
	{.type Absolute, {.p 123}},		/* dd 123 8600 */
	{.type Here, {.p 8600 }},	/* 8600 360 */
	{.type There, {.p 360 }},	/* 8600 360 */
	{.type FromDictionary, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8608 */
	{.type Here, {.p 8608 }},	/* 8608 360 */
	{.type There, {.p 360 }},	/* 8608 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8616 */
	{.type Here, {.p 8616 }},	/* 8616 360 */
	{.type There, {.p 360 }},	/* 8616 360 */
	{.type FromDictionary, {.p L_C_digit_2}, .src = "dd L_C_digit_2"},		/* dd L_C_digit_2 8624 */
	{.type Here, {.p 8624 }},	/* 8624 360 */
	{.type There, {.p 360 }},	/* 8624 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8632 */
	{.type Here, {.p 8632 }},	/* 8632 360 */
	{.type There, {.p 360 }},	/* 8632 360 */
	{.type Absolute, {.p 87}},		/* dd 87 8640 */
	{.type Here, {.p 8640 }},	/* 8640 360 */
	{.type There, {.p 360 }},	/* 8640 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8648 */
	{.type Here, {.p 8648 }},	/* 8648 360 */
	{.type There, {.p 360 }},	/* 8648 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8656 */
	{.type Here, {.p 8656 }},	/* 8656 360 */
	{.type There, {.p 360 }},	/* 8656 360 */
	{.type FromDictionary, {.p L_C_digit_3}, .src = "dd L_C_digit_3"},		/* dd L_C_digit_3 8664 */
	{.type Here, {.p 8664 }},	/* 8664 360 */
	{.type There, {.p 360 }},	/* 8664 360 */
	{.type Here, {.p 8664 }},	/* 8664 360 */
	{.type There, {.p 360 }},	/* 8664 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8672 */
	{.type Here, {.p 8672 }},	/* 8672 360 */
	{.type There, {.p 360 }},	/* 8672 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8680 */
	{.type Here, {.p 8680 }},	/* 8680 360 */
	{.type There, {.p 360 }},	/* 8680 360 */
	{.type Absolute, {.p 48}},		/* dd 48 8688 */
	{.type Here, {.p 8688 }},	/* 8688 360 */
	{.type There, {.p 360 }},	/* 8688 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8696 */
	{.type Here, {.p 8696 }},	/* 8696 360 */
	{.type There, {.p 360 }},	/* 8696 360 */
	{.type Absolute, {.p 58}},		/* dd 58 8704 */
	{.type Here, {.p 8704 }},	/* 8704 360 */
	{.type There, {.p 360 }},	/* 8704 360 */
	{.type FromDictionary, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8712 */
	{.type Here, {.p 8712 }},	/* 8712 360 */
	{.type There, {.p 360 }},	/* 8712 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8720 */
	{.type Here, {.p 8720 }},	/* 8720 360 */
	{.type There, {.p 360 }},	/* 8720 360 */
	{.type FromDictionary, {.p L_C_digit_4}, .src = "dd L_C_digit_4"},		/* dd L_C_digit_4 8728 */
	{.type Here, {.p 8728 }},	/* 8728 360 */
	{.type There, {.p 360 }},	/* 8728 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8736 */
	{.type Here, {.p 8736 }},	/* 8736 360 */
	{.type There, {.p 360 }},	/* 8736 360 */
	{.type Absolute, {.p 48}},		/* dd 48 8744 */
	{.type Here, {.p 8744 }},	/* 8744 360 */
	{.type There, {.p 360 }},	/* 8744 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8752 */
	{.type Here, {.p 8752 }},	/* 8752 360 */
	{.type There, {.p 360 }},	/* 8752 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8760 */
	{.type Here, {.p 8760 }},	/* 8760 360 */
	{.type There, {.p 360 }},	/* 8760 360 */
	{.type FromDictionary, {.p L_C_digit_5}, .src = "dd L_C_digit_5"},		/* dd L_C_digit_5 8768 */
	{.type Here, {.p 8768 }},	/* 8768 360 */
	{.type There, {.p 360 }},	/* 8768 360 */
	{.type Here, {.p 8768 }},	/* 8768 360 */
	{.type There, {.p 360 }},	/* 8768 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8776 */
	{.type Here, {.p 8776 }},	/* 8776 360 */
	{.type There, {.p 360 }},	/* 8776 360 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8784 */
	{.type Here, {.p 8784 }},	/* 8784 360 */
	{.type There, {.p 360 }},	/* 8784 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8792 */
	{.type Here, {.p 8792 }},	/* 8792 360 */
	{.type There, {.p 360 }},	/* 8792 360 */
	{.type Here, {.p 8792 }},	/* 8792 360 */
	{.type There, {.p 360 }},	/* 8792 360 */
	{.type Here, {.p 8792 }},	/* 8792 360 */
	{.type There, {.p 360 }},	/* 8792 360 */
	{.type Here, {.p 8792 }},	/* 8792 360 */
	{.type There, {.p 360 }},	/* 8792 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8800 */
	{.type Here, {.p 8800 }},	/* 8800 360 */
	{.type There, {.p 360 }},	/* 8800 360 */
	{.type FromDictionary, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8808 */
	{.type Here, {.p 8808 }},	/* 8808 360 */
	{.type There, {.p 360 }},	/* 8808 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 8816 */
	{.type Here, {.p 8816 }},	/* 8816 360 */
	{.type There, {.p 360 }},	/* 8816 360 */
	{.type FromDictionary, {.p M_less}, .src = "dd M_less"},		/* dd M_less 8824 */
	{.type Here, {.p 8824 }},	/* 8824 360 */
	{.type There, {.p 360 }},	/* 8824 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8832 */
	{.type Here, {.p 8832 }},	/* 8832 360 */
	{.type There, {.p 360 }},	/* 8832 360 */
	{.type FromDictionary, {.p L_C_digit_6}, .src = "dd L_C_digit_6"},		/* dd L_C_digit_6 8840 */
	{.type Here, {.p 8840 }},	/* 8840 360 */
	{.type There, {.p 360 }},	/* 8840 360 */
	{.type FromDictionary, {.p C_true}, .src = "dd C_true"},		/* dd C_true 8848 */
	{.type Here, {.p 8848 }},	/* 8848 360 */
	{.type There, {.p 360 }},	/* 8848 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8856 */
	{.type Here, {.p 8856 }},	/* 8856 360 */
	{.type There, {.p 360 }},	/* 8856 360 */
	{.type FromDictionary, {.p L_C_digit_7}, .src = "dd L_C_digit_7"},		/* dd L_C_digit_7 8864 */
	{.type Here, {.p 8864 }},	/* 8864 360 */
	{.type There, {.p 360 }},	/* 8864 360 */
	{.type Here, {.p 8864 }},	/* 8864 360 */
	{.type There, {.p 360 }},	/* 8864 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8872 */
	{.type Here, {.p 8872 }},	/* 8872 360 */
	{.type There, {.p 360 }},	/* 8872 360 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8880 */
	{.type Here, {.p 8880 }},	/* 8880 360 */
	{.type There, {.p 360 }},	/* 8880 360 */
	{.type Here, {.p 8880 }},	/* 8880 360 */
	{.type There, {.p 360 }},	/* 8880 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8888 */
	{.type Here, {.p 8888 }},	/* 8888 360 */
	{.type There, {.p 360 }},	/* 8888 360 */
	{.type Here, {.p 8888 }},	/* 8888 360 */
	{.type There, {.p 360 }},	/* 8888 360 */
	{.type Header, {.hdr { 6, "number", /* C_number = 8904 */ colon }}}, /* CENTRY "number" number 6 ; ( a n1 -- n2 -1 | a n1 0 ) h 8912 */
	{.type Here, {.p 8912 }},	/* 8912 360 */
	{.type There, {.p 360 }},	/* 8912 360 */
	{.type Here, {.p 8912 }},	/* 8912 360 */
	{.type There, {.p 360 }},	/* 8912 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 -- n1 a )"},		/* dd M_xswap	; ( a n1 -- n1 a ) 8920 */
	{.type Here, {.p 8920 }},	/* 8920 360 */
	{.type There, {.p 360 }},	/* 8920 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( n1 a -- n1 a a )"},		/* dd M_dup	; ( n1 a -- n1 a a ) 8928 */
	{.type Here, {.p 8928 }},	/* 8928 360 */
	{.type There, {.p 360 }},	/* 8928 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( n1 a a -- n1 a c )"},		/* dd M_cfetch	; ( n1 a a -- n1 a c ) 8936 */
	{.type Here, {.p 8936 }},	/* 8936 360 */
	{.type There, {.p 360 }},	/* 8936 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8944 */
	{.type Here, {.p 8944 }},	/* 8944 360 */
	{.type There, {.p 360 }},	/* 8944 360 */
	{.type Absolute, {.p 45}},		/* dd 45		; ( n1 a c -- n1 a c - ) 8952 */
	{.type Here, {.p 8952 }},	/* 8952 360 */
	{.type There, {.p 360 }},	/* 8952 360 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal	; ( n1 a c -- n1 a f )"},		/* dd M_equal	; ( n1 a c -- n1 a f ) 8960 */
	{.type Here, {.p 8960 }},	/* 8960 360 */
	{.type There, {.p 360 }},	/* 8960 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump	; ( n1 a c -- n1 a )"},		/* dd M_cjump	; ( n1 a c -- n1 a ) 8968 */
	{.type Here, {.p 8968 }},	/* 8968 360 */
	{.type There, {.p 360 }},	/* 8968 360 */
	{.type FromDictionary, {.p L_C_number}, .src = "dd L_C_number		; c != -"},		/* dd L_C_number		; c != - 8976 */
	{.type Here, {.p 8976 }},	/* 8976 360 */
	{.type There, {.p 360 }},	/* 8976 360 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus	; c == - ( n1 a -- n1 a+1 )"},		/* dd C_1plus	; c == - ( n1 a -- n1 a+1 ) 8984 */
	{.type Here, {.p 8984 }},	/* 8984 360 */
	{.type There, {.p 360 }},	/* 8984 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 8992 */
	{.type Here, {.p 8992 }},	/* 8992 360 */
	{.type There, {.p 360 }},	/* 8992 360 */
	{.type FromDictionary, {.p C_1minus}, .src = "dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 )"},		/* dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 ) 9000 */
	{.type Here, {.p 9000 }},	/* 9000 360 */
	{.type There, {.p 360 }},	/* 9000 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9008 */
	{.type Here, {.p 9008 }},	/* 9008 360 */
	{.type There, {.p 360 }},	/* 9008 360 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( a+1 n1-1 -- a+1 n1-1 -1 ) 9016 */
	{.type Here, {.p 9016 }},	/* 9016 360 */
	{.type There, {.p 360 }},	/* 9016 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1)"},		/* dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1) 9024 */
	{.type Here, {.p 9024 }},	/* 9024 360 */
	{.type There, {.p 360 }},	/* 9024 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9032 */
	{.type Here, {.p 9032 }},	/* 9032 360 */
	{.type There, {.p 360 }},	/* 9032 360 */
	{.type FromDictionary, {.p L_C_number_1}, .src = "dd L_C_number_1"},		/* dd L_C_number_1 9040 */
	{.type Here, {.p 9040 }},	/* 9040 360 */
	{.type There, {.p 360 }},	/* 9040 360 */
	{.type Here, {.p 9040 }},	/* 9040 360 */
	{.type There, {.p 360 }},	/* 9040 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( n1 a -- a n1)"},		/* dd M_xswap	; ( n1 a -- a n1) 9048 */
	{.type Here, {.p 9048 }},	/* 9048 360 */
	{.type There, {.p 360 }},	/* 9048 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9056 */
	{.type Here, {.p 9056 }},	/* 9056 360 */
	{.type There, {.p 360 }},	/* 9056 360 */
	{.type Absolute, {.p 1}},		/* dd 1 9064 */
	{.type Here, {.p 9064 }},	/* 9064 360 */
	{.type There, {.p 360 }},	/* 9064 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1)"},		/* dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1) 9072 */
	{.type Here, {.p 9072 }},	/* 9072 360 */
	{.type There, {.p 360 }},	/* 9072 360 */
	{.type Here, {.p 9072 }},	/* 9072 360 */
	{.type There, {.p 360 }},	/* 9072 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a n1 -- a n1 n1 ) (R nr)"},		/* dd M_dup	; ( a n1 -- a n1 n1 ) (R nr) 9080 */
	{.type Here, {.p 9080 }},	/* 9080 360 */
	{.type There, {.p 360 }},	/* 9080 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1)"},		/* dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1) 9088 */
	{.type Here, {.p 9088 }},	/* 9088 360 */
	{.type There, {.p 360 }},	/* 9088 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9096 */
	{.type Here, {.p 9096 }},	/* 9096 360 */
	{.type There, {.p 360 }},	/* 9096 360 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a n1 -- a n1 0) (R nr n1) 9104 */
	{.type Here, {.p 9104 }},	/* 9104 360 */
	{.type There, {.p 360 }},	/* 9104 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1)"},		/* dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1) 9112 */
	{.type Here, {.p 9112 }},	/* 9112 360 */
	{.type There, {.p 360 }},	/* 9112 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9120 */
	{.type Here, {.p 9120 }},	/* 9120 360 */
	{.type There, {.p 360 }},	/* 9120 360 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a 0 n1 -- a 0 n1 0) (R nr n1) 9128 */
	{.type Here, {.p 9128 }},	/* 9128 360 */
	{.type There, {.p 360 }},	/* 9128 360 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1) 9136 */
	{.type Here, {.p 9136 }},	/* 9136 360 */
	{.type There, {.p 360 }},	/* 9136 360 */
	{.type Here, {.p 9136 }},	/* 9136 360 */
	{.type There, {.p 360 }},	/* 9136 360 */
	{.type FromDictionary, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 9144 */
	{.type Here, {.p 9144 }},	/* 9144 360 */
	{.type There, {.p 360 }},	/* 9144 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1) 9152 */
	{.type Here, {.p 9152 }},	/* 9152 360 */
	{.type There, {.p 360 }},	/* 9152 360 */
	{.type FromDictionary, {.p M_multiply}, .src = "dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1) 9160 */
	{.type Here, {.p 9160 }},	/* 9160 360 */
	{.type There, {.p 360 }},	/* 9160 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1)"},		/* dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1) 9168 */
	{.type Here, {.p 9168 }},	/* 9168 360 */
	{.type There, {.p 360 }},	/* 9168 360 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1) 9176 */
	{.type Here, {.p 9176 }},	/* 9176 360 */
	{.type There, {.p 360 }},	/* 9176 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1) 9184 */
	{.type Here, {.p 9184 }},	/* 9184 360 */
	{.type There, {.p 360 }},	/* 9184 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1)"},		/* dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1) 9192 */
	{.type Here, {.p 9192 }},	/* 9192 360 */
	{.type There, {.p 360 }},	/* 9192 360 */
	{.type FromDictionary, {.p C_digit}, .src = "dd C_digit"},		/* dd C_digit 9200 */
	{.type Here, {.p 9200 }},	/* 9200 360 */
	{.type There, {.p 360 }},	/* 9200 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9208 */
	{.type Here, {.p 9208 }},	/* 9208 360 */
	{.type There, {.p 360 }},	/* 9208 360 */
	{.type FromDictionary, {.p L_C_number_3}, .src = "dd L_C_number_3"},		/* dd L_C_number_3 9216 */
	{.type Here, {.p 9216 }},	/* 9216 360 */
	{.type There, {.p 360 }},	/* 9216 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 9224 */
	{.type Here, {.p 9224 }},	/* 9224 360 */
	{.type There, {.p 360 }},	/* 9224 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9232 */
	{.type Here, {.p 9232 }},	/* 9232 360 */
	{.type There, {.p 360 }},	/* 9232 360 */
	{.type FromDictionary, {.p L_C_number_4}, .src = "dd L_C_number_4"},		/* dd L_C_number_4 9240 */
	{.type Here, {.p 9240 }},	/* 9240 360 */
	{.type There, {.p 360 }},	/* 9240 360 */
	{.type Here, {.p 9240 }},	/* 9240 360 */
	{.type There, {.p 360 }},	/* 9240 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9248 */
	{.type Here, {.p 9248 }},	/* 9248 360 */
	{.type There, {.p 360 }},	/* 9248 360 */
	{.type FromDictionary, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 9256 */
	{.type Here, {.p 9256 }},	/* 9256 360 */
	{.type There, {.p 360 }},	/* 9256 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9264 */
	{.type Here, {.p 9264 }},	/* 9264 360 */
	{.type There, {.p 360 }},	/* 9264 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9272 */
	{.type Here, {.p 9272 }},	/* 9272 360 */
	{.type There, {.p 360 }},	/* 9272 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9280 */
	{.type Here, {.p 9280 }},	/* 9280 360 */
	{.type There, {.p 360 }},	/* 9280 360 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false"},		/* dd C_false 9288 */
	{.type Here, {.p 9288 }},	/* 9288 360 */
	{.type There, {.p 360 }},	/* 9288 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9296 */
	{.type Here, {.p 9296 }},	/* 9296 360 */
	{.type There, {.p 360 }},	/* 9296 360 */
	{.type Here, {.p 9296 }},	/* 9296 360 */
	{.type There, {.p 360 }},	/* 9296 360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 9304 */
	{.type Here, {.p 9304 }},	/* 9304 360 */
	{.type There, {.p 360 }},	/* 9304 360 */
	{.type FromDictionary, {.p L_C_number_2}, .src = "dd L_C_number_2"},		/* dd L_C_number_2 9312 */
	{.type Here, {.p 9312 }},	/* 9312 360 */
	{.type There, {.p 360 }},	/* 9312 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9320 */
	{.type Here, {.p 9320 }},	/* 9320 360 */
	{.type There, {.p 360 }},	/* 9320 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9328 */
	{.type Here, {.p 9328 }},	/* 9328 360 */
	{.type There, {.p 360 }},	/* 9328 360 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 9336 */
	{.type Here, {.p 9336 }},	/* 9336 360 */
	{.type There, {.p 360 }},	/* 9336 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9344 */
	{.type Here, {.p 9344 }},	/* 9344 360 */
	{.type There, {.p 360 }},	/* 9344 360 */
	{.type FromDictionary, {.p M_multiply}, .src = "dd M_multiply"},		/* dd M_multiply 9352 */
	{.type Here, {.p 9352 }},	/* 9352 360 */
	{.type There, {.p 360 }},	/* 9352 360 */
	{.type FromDictionary, {.p C_true}, .src = "dd C_true"},		/* dd C_true 9360 */
	{.type Here, {.p 9360 }},	/* 9360 360 */
	{.type There, {.p 360 }},	/* 9360 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9368 */
	{.type Here, {.p 9368 }},	/* 9368 360 */
	{.type There, {.p 360 }},	/* 9368 360 */
	{.type Here, {.p 9368 }},	/* 9368 360 */
	{.type There, {.p 360 }},	/* 9368 360 */
	{.type Header, {.hdr { 5, "abort", /* C_abort = 9384 */ colon }}}, /* CENTRY "abort" abort 5 h 9392 */
	{.type Here, {.p 9392 }},	/* 9392 360 */
	{.type There, {.p 360 }},	/* 9392 360 */
	{.type Here, {.p 9392 }},	/* 9392 360 */
	{.type There, {.p 360 }},	/* 9392 360 */
	{.type FromDictionary, {.p MV_Abortvec}, .src = "dd MV_Abortvec"},		/* dd MV_Abortvec 9400 */
	{.type Here, {.p 9400 }},	/* 9400 360 */
	{.type There, {.p 360 }},	/* 9400 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9408 */
	{.type Here, {.p 9408 }},	/* 9408 360 */
	{.type There, {.p 360 }},	/* 9408 360 */
	{.type FromDictionary, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 9416 */
	{.type Here, {.p 9416 }},	/* 9416 360 */
	{.type There, {.p 360 }},	/* 9416 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9424 */
	{.type Here, {.p 9424 }},	/* 9424 360 */
	{.type There, {.p 360 }},	/* 9424 360 */
	{.type Here, {.p 9424 }},	/* 9424 360 */
	{.type There, {.p 360 }},	/* 9424 360 */
	{.type Header, {.hdr { 15, "bufferfilename!", /* C_bufferfilename_store = 9448 */ colon }}}, /* CENTRY "bufferfilename!" bufferfilename_store 15 ; ( 'text index -- ) store label h 9456 */
	{.type Here, {.p 9456 }},	/* 9456 360 */
	{.type There, {.p 360 }},	/* 9456 360 */
	{.type Here, {.p 9456 }},	/* 9456 360 */
	{.type There, {.p 360 }},	/* 9456 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 9464 */
	{.type Here, {.p 9464 }},	/* 9464 360 */
	{.type There, {.p 360 }},	/* 9464 360 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 9472 */
	{.type Here, {.p 9472 }},	/* 9472 360 */
	{.type There, {.p 360 }},	/* 9472 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 9480 */
	{.type Here, {.p 9480 }},	/* 9480 360 */
	{.type There, {.p 360 }},	/* 9480 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9488 */
	{.type Here, {.p 9488 }},	/* 9488 360 */
	{.type There, {.p 360 }},	/* 9488 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9496 */
	{.type Here, {.p 9496 }},	/* 9496 360 */
	{.type There, {.p 360 }},	/* 9496 360 */
	{.type Here, {.p 9496 }},	/* 9496 360 */
	{.type There, {.p 360 }},	/* 9496 360 */
	{.type Header, {.hdr { 7, ">word", /* C_toword = 9512 */ colon }}}, /* CENTRY ">word" toword 7 ; ( 'Bufferfds -- 'Wordfd ) h 9520 */
	{.type Here, {.p 9520 }},	/* 9520 360 */
	{.type There, {.p 360 }},	/* 9520 360 */
	{.type Here, {.p 9520 }},	/* 9520 360 */
	{.type There, {.p 360 }},	/* 9520 360 */
	{.type FromDictionary, {.p MC_WORDNUM}, .src = "dd MC_WORDNUM"},		/* dd MC_WORDNUM 9528 */
	{.type Here, {.p 9528 }},	/* 9528 360 */
	{.type There, {.p 360 }},	/* 9528 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 9536 */
	{.type Here, {.p 9536 }},	/* 9536 360 */
	{.type There, {.p 360 }},	/* 9536 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 9544 */
	{.type Here, {.p 9544 }},	/* 9544 360 */
	{.type There, {.p 360 }},	/* 9544 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9552 */
	{.type Here, {.p 9552 }},	/* 9552 360 */
	{.type There, {.p 360 }},	/* 9552 360 */
	{.type Here, {.p 9552 }},	/* 9552 360 */
	{.type There, {.p 360 }},	/* 9552 360 */
	{.type Header, {.hdr { 7, "wordfd@", /* C_wordfd_fetch = 9568 */ colon }}}, /* CENTRY "wordfd@" wordfd_fetch 7 h 9576 */
	{.type Here, {.p 9576 }},	/* 9576 360 */
	{.type There, {.p 360 }},	/* 9576 360 */
	{.type Here, {.p 9576 }},	/* 9576 360 */
	{.type There, {.p 360 }},	/* 9576 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 9584 */
	{.type Here, {.p 9584 }},	/* 9584 360 */
	{.type There, {.p 360 }},	/* 9584 360 */
	{.type FromDictionary, {.p C_toword}, .src = "dd C_toword"},		/* dd C_toword 9592 */
	{.type Here, {.p 9592 }},	/* 9592 360 */
	{.type There, {.p 360 }},	/* 9592 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9600 */
	{.type Here, {.p 9600 }},	/* 9600 360 */
	{.type There, {.p 360 }},	/* 9600 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9608 */
	{.type Here, {.p 9608 }},	/* 9608 360 */
	{.type There, {.p 360 }},	/* 9608 360 */
	{.type Here, {.p 9608 }},	/* 9608 360 */
	{.type There, {.p 360 }},	/* 9608 360 */
	{.type Header, {.hdr { 7, "wordfd!", /* C_wordfd_store = 9624 */ colon }}}, /* CENTRY "wordfd!" wordfd_store 7 h 9632 */
	{.type Here, {.p 9632 }},	/* 9632 360 */
	{.type There, {.p 360 }},	/* 9632 360 */
	{.type Here, {.p 9632 }},	/* 9632 360 */
	{.type There, {.p 360 }},	/* 9632 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 9640 */
	{.type Here, {.p 9640 }},	/* 9640 360 */
	{.type There, {.p 360 }},	/* 9640 360 */
	{.type FromDictionary, {.p C_toword}, .src = "dd C_toword"},		/* dd C_toword 9648 */
	{.type Here, {.p 9648 }},	/* 9648 360 */
	{.type There, {.p 360 }},	/* 9648 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9656 */
	{.type Here, {.p 9656 }},	/* 9656 360 */
	{.type There, {.p 360 }},	/* 9656 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9664 */
	{.type Here, {.p 9664 }},	/* 9664 360 */
	{.type There, {.p 360 }},	/* 9664 360 */
	{.type Here, {.p 9664 }},	/* 9664 360 */
	{.type There, {.p 360 }},	/* 9664 360 */
	{.type Header, {.hdr { 13, "wordfilename@", /* C_wordfilename_fetch = 9688 */ colon }}}, /* CENTRY "wordfilename@" wordfilename_fetch 13 h 9696 */
	{.type Here, {.p 9696 }},	/* 9696 360 */
	{.type There, {.p 360 }},	/* 9696 360 */
	{.type Here, {.p 9696 }},	/* 9696 360 */
	{.type There, {.p 360 }},	/* 9696 360 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 9704 */
	{.type Here, {.p 9704 }},	/* 9704 360 */
	{.type There, {.p 360 }},	/* 9704 360 */
	{.type FromDictionary, {.p C_toword}, .src = "dd C_toword"},		/* dd C_toword 9712 */
	{.type Here, {.p 9712 }},	/* 9712 360 */
	{.type There, {.p 360 }},	/* 9712 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9720 */
	{.type Here, {.p 9720 }},	/* 9720 360 */
	{.type There, {.p 360 }},	/* 9720 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9728 */
	{.type Here, {.p 9728 }},	/* 9728 360 */
	{.type There, {.p 360 }},	/* 9728 360 */
	{.type Here, {.p 9728 }},	/* 9728 360 */
	{.type There, {.p 360 }},	/* 9728 360 */
	{.type Header, {.hdr { 13, "wordfilename!", /* C_wordfilename_store = 9752 */ colon }}}, /* CENTRY "wordfilename!" wordfilename_store 13 h 9760 */
	{.type Here, {.p 9760 }},	/* 9760 360 */
	{.type There, {.p 360 }},	/* 9760 360 */
	{.type Here, {.p 9760 }},	/* 9760 360 */
	{.type There, {.p 360 }},	/* 9760 360 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 9768 */
	{.type Here, {.p 9768 }},	/* 9768 360 */
	{.type There, {.p 360 }},	/* 9768 360 */
	{.type FromDictionary, {.p C_toword}, .src = "dd C_toword"},		/* dd C_toword 9776 */
	{.type Here, {.p 9776 }},	/* 9776 360 */
	{.type There, {.p 360 }},	/* 9776 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9784 */
	{.type Here, {.p 9784 }},	/* 9784 360 */
	{.type There, {.p 360 }},	/* 9784 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9792 */
	{.type Here, {.p 9792 }},	/* 9792 360 */
	{.type There, {.p 360 }},	/* 9792 360 */
	{.type Here, {.p 9792 }},	/* 9792 360 */
	{.type There, {.p 360 }},	/* 9792 360 */
	{.type Header, {.hdr { 7, ">line", /* C_toline = 9808 */ colon }}}, /* CENTRY ">line" toline 7 ; ( 'Bufferfds -- 'Wordfd ) h 9816 */
	{.type Here, {.p 9816 }},	/* 9816 360 */
	{.type There, {.p 360 }},	/* 9816 360 */
	{.type Here, {.p 9816 }},	/* 9816 360 */
	{.type There, {.p 360 }},	/* 9816 360 */
	{.type FromDictionary, {.p MC_LINENUM}, .src = "dd MC_LINENUM"},		/* dd MC_LINENUM 9824 */
	{.type Here, {.p 9824 }},	/* 9824 360 */
	{.type There, {.p 360 }},	/* 9824 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 9832 */
	{.type Here, {.p 9832 }},	/* 9832 360 */
	{.type There, {.p 360 }},	/* 9832 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 9840 */
	{.type Here, {.p 9840 }},	/* 9840 360 */
	{.type There, {.p 360 }},	/* 9840 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9848 */
	{.type Here, {.p 9848 }},	/* 9848 360 */
	{.type There, {.p 360 }},	/* 9848 360 */
	{.type Here, {.p 9848 }},	/* 9848 360 */
	{.type There, {.p 360 }},	/* 9848 360 */
	{.type Header, {.hdr { 7, "linefd@", /* C_linefd_fetch = 9864 */ colon }}}, /* CENTRY "linefd@" linefd_fetch 7 h 9872 */
	{.type Here, {.p 9872 }},	/* 9872 360 */
	{.type There, {.p 360 }},	/* 9872 360 */
	{.type Here, {.p 9872 }},	/* 9872 360 */
	{.type There, {.p 360 }},	/* 9872 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 9880 */
	{.type Here, {.p 9880 }},	/* 9880 360 */
	{.type There, {.p 360 }},	/* 9880 360 */
	{.type FromDictionary, {.p C_toline}, .src = "dd C_toline"},		/* dd C_toline 9888 */
	{.type Here, {.p 9888 }},	/* 9888 360 */
	{.type There, {.p 360 }},	/* 9888 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9896 */
	{.type Here, {.p 9896 }},	/* 9896 360 */
	{.type There, {.p 360 }},	/* 9896 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9904 */
	{.type Here, {.p 9904 }},	/* 9904 360 */
	{.type There, {.p 360 }},	/* 9904 360 */
	{.type Here, {.p 9904 }},	/* 9904 360 */
	{.type There, {.p 360 }},	/* 9904 360 */
	{.type Header, {.hdr { 7, "linefd!", /* C_linefd_store = 9920 */ colon }}}, /* CENTRY "linefd!" linefd_store 7 h 9928 */
	{.type Here, {.p 9928 }},	/* 9928 360 */
	{.type There, {.p 360 }},	/* 9928 360 */
	{.type Here, {.p 9928 }},	/* 9928 360 */
	{.type There, {.p 360 }},	/* 9928 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 9936 */
	{.type Here, {.p 9936 }},	/* 9936 360 */
	{.type There, {.p 360 }},	/* 9936 360 */
	{.type FromDictionary, {.p C_toline}, .src = "dd C_toline"},		/* dd C_toline 9944 */
	{.type Here, {.p 9944 }},	/* 9944 360 */
	{.type There, {.p 360 }},	/* 9944 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 9952 */
	{.type Here, {.p 9952 }},	/* 9952 360 */
	{.type There, {.p 360 }},	/* 9952 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9960 */
	{.type Here, {.p 9960 }},	/* 9960 360 */
	{.type There, {.p 360 }},	/* 9960 360 */
	{.type Here, {.p 9960 }},	/* 9960 360 */
	{.type There, {.p 360 }},	/* 9960 360 */
	{.type Header, {.hdr { 13, "linefilename@", /* C_linefilename_fetch = 9984 */ colon }}}, /* CENTRY "linefilename@" linefilename_fetch 13 h 9992 */
	{.type Here, {.p 9992 }},	/* 9992 360 */
	{.type There, {.p 360 }},	/* 9992 360 */
	{.type Here, {.p 9992 }},	/* 9992 360 */
	{.type There, {.p 360 }},	/* 9992 360 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 10000 */
	{.type Here, {.p 10000 }},	/* 10000 360 */
	{.type There, {.p 360 }},	/* 10000 360 */
	{.type FromDictionary, {.p C_toline}, .src = "dd C_toline"},		/* dd C_toline 10008 */
	{.type Here, {.p 10008 }},	/* 10008 360 */
	{.type There, {.p 360 }},	/* 10008 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10016 */
	{.type Here, {.p 10016 }},	/* 10016 360 */
	{.type There, {.p 360 }},	/* 10016 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10024 */
	{.type Here, {.p 10024 }},	/* 10024 360 */
	{.type There, {.p 360 }},	/* 10024 360 */
	{.type Here, {.p 10024 }},	/* 10024 360 */
	{.type There, {.p 360 }},	/* 10024 360 */
	{.type Header, {.hdr { 13, "linefilename!", /* C_linefilename_store = 10048 */ colon }}}, /* CENTRY "linefilename!" linefilename_store 13 h 10056 */
	{.type Here, {.p 10056 }},	/* 10056 360 */
	{.type There, {.p 360 }},	/* 10056 360 */
	{.type Here, {.p 10056 }},	/* 10056 360 */
	{.type There, {.p 360 }},	/* 10056 360 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 10064 */
	{.type Here, {.p 10064 }},	/* 10064 360 */
	{.type There, {.p 360 }},	/* 10064 360 */
	{.type FromDictionary, {.p C_toline}, .src = "dd C_toline"},		/* dd C_toline 10072 */
	{.type Here, {.p 10072 }},	/* 10072 360 */
	{.type There, {.p 360 }},	/* 10072 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10080 */
	{.type Here, {.p 10080 }},	/* 10080 360 */
	{.type There, {.p 360 }},	/* 10080 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10088 */
	{.type Here, {.p 10088 }},	/* 10088 360 */
	{.type There, {.p 360 }},	/* 10088 360 */
	{.type Here, {.p 10088 }},	/* 10088 360 */
	{.type There, {.p 360 }},	/* 10088 360 */
	{.type Header, {.hdr { 12, ">doublequote", /* C_todoublequote = 10112 */ colon }}}, /* CENTRY ">doublequote" todoublequote 12 ; ( 'Bufferfds -- 'Doublequotefd ) h 10120 */
	{.type Here, {.p 10120 }},	/* 10120 360 */
	{.type There, {.p 360 }},	/* 10120 360 */
	{.type Here, {.p 10120 }},	/* 10120 360 */
	{.type There, {.p 360 }},	/* 10120 360 */
	{.type FromDictionary, {.p MC_LINENUM}, .src = "dd MC_LINENUM"},		/* dd MC_LINENUM 10128 */
	{.type Here, {.p 10128 }},	/* 10128 360 */
	{.type There, {.p 360 }},	/* 10128 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 10136 */
	{.type Here, {.p 10136 }},	/* 10136 360 */
	{.type There, {.p 360 }},	/* 10136 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 10144 */
	{.type Here, {.p 10144 }},	/* 10144 360 */
	{.type There, {.p 360 }},	/* 10144 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10152 */
	{.type Here, {.p 10152 }},	/* 10152 360 */
	{.type There, {.p 360 }},	/* 10152 360 */
	{.type Here, {.p 10152 }},	/* 10152 360 */
	{.type There, {.p 360 }},	/* 10152 360 */
	{.type Header, {.hdr { 14, "doublequotefd@", /* C_doublequotefd_fetch = 10176 */ colon }}}, /* CENTRY "doublequotefd@" doublequotefd_fetch 14 h 10184 */
	{.type Here, {.p 10184 }},	/* 10184 360 */
	{.type There, {.p 360 }},	/* 10184 360 */
	{.type Here, {.p 10184 }},	/* 10184 360 */
	{.type There, {.p 360 }},	/* 10184 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10192 */
	{.type Here, {.p 10192 }},	/* 10192 360 */
	{.type There, {.p 360 }},	/* 10192 360 */
	{.type FromDictionary, {.p C_todoublequote}, .src = "dd C_todoublequote"},		/* dd C_todoublequote 10200 */
	{.type Here, {.p 10200 }},	/* 10200 360 */
	{.type There, {.p 360 }},	/* 10200 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10208 */
	{.type Here, {.p 10208 }},	/* 10208 360 */
	{.type There, {.p 360 }},	/* 10208 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10216 */
	{.type Here, {.p 10216 }},	/* 10216 360 */
	{.type There, {.p 360 }},	/* 10216 360 */
	{.type Here, {.p 10216 }},	/* 10216 360 */
	{.type There, {.p 360 }},	/* 10216 360 */
	{.type Header, {.hdr { 14, "doublequotefd!", /* C_doublequotefd_store = 10240 */ colon }}}, /* CENTRY "doublequotefd!" doublequotefd_store 14 h 10248 */
	{.type Here, {.p 10248 }},	/* 10248 360 */
	{.type There, {.p 360 }},	/* 10248 360 */
	{.type Here, {.p 10248 }},	/* 10248 360 */
	{.type There, {.p 360 }},	/* 10248 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10256 */
	{.type Here, {.p 10256 }},	/* 10256 360 */
	{.type There, {.p 360 }},	/* 10256 360 */
	{.type FromDictionary, {.p C_todoublequote}, .src = "dd C_todoublequote"},		/* dd C_todoublequote 10264 */
	{.type Here, {.p 10264 }},	/* 10264 360 */
	{.type There, {.p 360 }},	/* 10264 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10272 */
	{.type Here, {.p 10272 }},	/* 10272 360 */
	{.type There, {.p 360 }},	/* 10272 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10280 */
	{.type Here, {.p 10280 }},	/* 10280 360 */
	{.type There, {.p 360 }},	/* 10280 360 */
	{.type Here, {.p 10280 }},	/* 10280 360 */
	{.type There, {.p 360 }},	/* 10280 360 */
	{.type Header, {.hdr { 20, "doublequotefilename@", /* C_doublequotefilename_fetch = 10312 */ colon }}}, /* CENTRY "doublequotefilename@" doublequotefilename_fetch 20 h 10320 */
	{.type Here, {.p 10320 }},	/* 10320 360 */
	{.type There, {.p 360 }},	/* 10320 360 */
	{.type Here, {.p 10320 }},	/* 10320 360 */
	{.type There, {.p 360 }},	/* 10320 360 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 10328 */
	{.type Here, {.p 10328 }},	/* 10328 360 */
	{.type There, {.p 360 }},	/* 10328 360 */
	{.type FromDictionary, {.p C_todoublequote}, .src = "dd C_todoublequote"},		/* dd C_todoublequote 10336 */
	{.type Here, {.p 10336 }},	/* 10336 360 */
	{.type There, {.p 360 }},	/* 10336 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10344 */
	{.type Here, {.p 10344 }},	/* 10344 360 */
	{.type There, {.p 360 }},	/* 10344 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10352 */
	{.type Here, {.p 10352 }},	/* 10352 360 */
	{.type There, {.p 360 }},	/* 10352 360 */
	{.type Here, {.p 10352 }},	/* 10352 360 */
	{.type There, {.p 360 }},	/* 10352 360 */
	{.type Header, {.hdr { 20, "doublequotefilename!", /* C_doublequotefilename_store = 10384 */ colon }}}, /* CENTRY "doublequotefilename!" doublequotefilename_store 20 h 10392 */
	{.type Here, {.p 10392 }},	/* 10392 360 */
	{.type There, {.p 360 }},	/* 10392 360 */
	{.type Here, {.p 10392 }},	/* 10392 360 */
	{.type There, {.p 360 }},	/* 10392 360 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 10400 */
	{.type Here, {.p 10400 }},	/* 10400 360 */
	{.type There, {.p 360 }},	/* 10400 360 */
	{.type FromDictionary, {.p C_todoublequote}, .src = "dd C_todoublequote"},		/* dd C_todoublequote 10408 */
	{.type Here, {.p 10408 }},	/* 10408 360 */
	{.type There, {.p 360 }},	/* 10408 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10416 */
	{.type Here, {.p 10416 }},	/* 10416 360 */
	{.type There, {.p 360 }},	/* 10416 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10424 */
	{.type Here, {.p 10424 }},	/* 10424 360 */
	{.type There, {.p 360 }},	/* 10424 360 */
	{.type Here, {.p 10424 }},	/* 10424 360 */
	{.type There, {.p 360 }},	/* 10424 360 */
	{.type Header, {.hdr { 11, ">closeparen", /* C_tocloseparen = 10448 */ colon }}}, /* CENTRY ">closeparen" tocloseparen 11 ; ( 'Bufferfds -- 'Closeparenfd ) h 10456 */
	{.type Here, {.p 10456 }},	/* 10456 360 */
	{.type There, {.p 360 }},	/* 10456 360 */
	{.type Here, {.p 10456 }},	/* 10456 360 */
	{.type There, {.p 360 }},	/* 10456 360 */
	{.type FromDictionary, {.p MC_LINENUM}, .src = "dd MC_LINENUM"},		/* dd MC_LINENUM 10464 */
	{.type Here, {.p 10464 }},	/* 10464 360 */
	{.type There, {.p 360 }},	/* 10464 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 10472 */
	{.type Here, {.p 10472 }},	/* 10472 360 */
	{.type There, {.p 360 }},	/* 10472 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 10480 */
	{.type Here, {.p 10480 }},	/* 10480 360 */
	{.type There, {.p 360 }},	/* 10480 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10488 */
	{.type Here, {.p 10488 }},	/* 10488 360 */
	{.type There, {.p 360 }},	/* 10488 360 */
	{.type Here, {.p 10488 }},	/* 10488 360 */
	{.type There, {.p 360 }},	/* 10488 360 */
	{.type Header, {.hdr { 13, "closeparenfd@", /* C_closeparenfd_fetch = 10512 */ colon }}}, /* CENTRY "closeparenfd@" closeparenfd_fetch 13 h 10520 */
	{.type Here, {.p 10520 }},	/* 10520 360 */
	{.type There, {.p 360 }},	/* 10520 360 */
	{.type Here, {.p 10520 }},	/* 10520 360 */
	{.type There, {.p 360 }},	/* 10520 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10528 */
	{.type Here, {.p 10528 }},	/* 10528 360 */
	{.type There, {.p 360 }},	/* 10528 360 */
	{.type FromDictionary, {.p C_tocloseparen}, .src = "dd C_tocloseparen"},		/* dd C_tocloseparen 10536 */
	{.type Here, {.p 10536 }},	/* 10536 360 */
	{.type There, {.p 360 }},	/* 10536 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10544 */
	{.type Here, {.p 10544 }},	/* 10544 360 */
	{.type There, {.p 360 }},	/* 10544 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10552 */
	{.type Here, {.p 10552 }},	/* 10552 360 */
	{.type There, {.p 360 }},	/* 10552 360 */
	{.type Here, {.p 10552 }},	/* 10552 360 */
	{.type There, {.p 360 }},	/* 10552 360 */
	{.type Header, {.hdr { 13, "closeparenfd!", /* C_closeparenfd_store = 10576 */ colon }}}, /* CENTRY "closeparenfd!" closeparenfd_store 13 h 10584 */
	{.type Here, {.p 10584 }},	/* 10584 360 */
	{.type There, {.p 360 }},	/* 10584 360 */
	{.type Here, {.p 10584 }},	/* 10584 360 */
	{.type There, {.p 360 }},	/* 10584 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10592 */
	{.type Here, {.p 10592 }},	/* 10592 360 */
	{.type There, {.p 360 }},	/* 10592 360 */
	{.type FromDictionary, {.p C_tocloseparen}, .src = "dd C_tocloseparen"},		/* dd C_tocloseparen 10600 */
	{.type Here, {.p 10600 }},	/* 10600 360 */
	{.type There, {.p 360 }},	/* 10600 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10608 */
	{.type Here, {.p 10608 }},	/* 10608 360 */
	{.type There, {.p 360 }},	/* 10608 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10616 */
	{.type Here, {.p 10616 }},	/* 10616 360 */
	{.type There, {.p 360 }},	/* 10616 360 */
	{.type Here, {.p 10616 }},	/* 10616 360 */
	{.type There, {.p 360 }},	/* 10616 360 */
	{.type Header, {.hdr { 19, "closeparenfilename@", /* C_closeparenfilename_fetch = 10648 */ colon }}}, /* CENTRY "closeparenfilename@" closeparenfilename_fetch 19 h 10656 */
	{.type Here, {.p 10656 }},	/* 10656 360 */
	{.type There, {.p 360 }},	/* 10656 360 */
	{.type Here, {.p 10656 }},	/* 10656 360 */
	{.type There, {.p 360 }},	/* 10656 360 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 10664 */
	{.type Here, {.p 10664 }},	/* 10664 360 */
	{.type There, {.p 360 }},	/* 10664 360 */
	{.type FromDictionary, {.p C_tocloseparen}, .src = "dd C_tocloseparen"},		/* dd C_tocloseparen 10672 */
	{.type Here, {.p 10672 }},	/* 10672 360 */
	{.type There, {.p 360 }},	/* 10672 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10680 */
	{.type Here, {.p 10680 }},	/* 10680 360 */
	{.type There, {.p 360 }},	/* 10680 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10688 */
	{.type Here, {.p 10688 }},	/* 10688 360 */
	{.type There, {.p 360 }},	/* 10688 360 */
	{.type Here, {.p 10688 }},	/* 10688 360 */
	{.type There, {.p 360 }},	/* 10688 360 */
	{.type Header, {.hdr { 19, "closeparenfilename!", /* C_closeparenfilename_store = 10720 */ colon }}}, /* CENTRY "closeparenfilename!" closeparenfilename_store 19 h 10728 */
	{.type Here, {.p 10728 }},	/* 10728 360 */
	{.type There, {.p 360 }},	/* 10728 360 */
	{.type Here, {.p 10728 }},	/* 10728 360 */
	{.type There, {.p 360 }},	/* 10728 360 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 10736 */
	{.type Here, {.p 10736 }},	/* 10736 360 */
	{.type There, {.p 360 }},	/* 10736 360 */
	{.type FromDictionary, {.p C_tocloseparen}, .src = "dd C_tocloseparen"},		/* dd C_tocloseparen 10744 */
	{.type Here, {.p 10744 }},	/* 10744 360 */
	{.type There, {.p 360 }},	/* 10744 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10752 */
	{.type Here, {.p 10752 }},	/* 10752 360 */
	{.type There, {.p 360 }},	/* 10752 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10760 */
	{.type Here, {.p 10760 }},	/* 10760 360 */
	{.type There, {.p 360 }},	/* 10760 360 */
	{.type Here, {.p 10760 }},	/* 10760 360 */
	{.type There, {.p 360 }},	/* 10760 360 */
/* ; stdinput : set all buffer fd's to -1, Infd = stdin */	{.type Here, {.p 10760 }},	/* 10760 360 */
	{.type There, {.p 360 }},	/* 10760 360 */
/* ; args : set all buffer fd's to -1, Infd = #p/<pid>/args */	{.type Here, {.p 10760 }},	/* 10760 360 */
	{.type There, {.p 360 }},	/* 10760 360 */
/* ; input@ : buffer fds and Infd -> stack */	{.type Here, {.p 10760 }},	/* 10760 360 */
	{.type There, {.p 360 }},	/* 10760 360 */
/* ; input! : stack -> buffer fds and Infd */	{.type Here, {.p 10760 }},	/* 10760 360 */
	{.type There, {.p 360 }},	/* 10760 360 */
/* ; -input : close all buffer fds and Infd, set buffer fds to -1 */	{.type Here, {.p 10760 }},	/* 10760 360 */
	{.type There, {.p 360 }},	/* 10760 360 */
/* ; buffer file names are setup in boot */	{.type Here, {.p 10760 }},	/* 10760 360 */
	{.type There, {.p 360 }},	/* 10760 360 */
	{.type Here, {.p 10760 }},	/* 10760 360 */
	{.type There, {.p 360 }},	/* 10760 360 */
	{.type Header, {.hdr { 8, "stdinput", /* C_stdinput = 10784 */ colon }}}, /* CENTRY "stdinput" stdinput 8 ; stream input from stdin into Text input buffer h 10792 */
	{.type Here, {.p 10792 }},	/* 10792 360 */
	{.type There, {.p 360 }},	/* 10792 360 */
	{.type Here, {.p 10792 }},	/* 10792 360 */
	{.type There, {.p 360 }},	/* 10792 360 */
	{.type FromDictionary, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 10800 */
	{.type Here, {.p 10800 }},	/* 10800 360 */
	{.type There, {.p 360 }},	/* 10800 360 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 10808 */
	{.type Here, {.p 10808 }},	/* 10808 360 */
	{.type There, {.p 360 }},	/* 10808 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10816 */
	{.type Here, {.p 10816 }},	/* 10816 360 */
	{.type There, {.p 360 }},	/* 10816 360 */
	{.type Here, {.p 10816 }},	/* 10816 360 */
	{.type There, {.p 360 }},	/* 10816 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10824 */
	{.type Here, {.p 10824 }},	/* 10824 360 */
	{.type There, {.p 360 }},	/* 10824 360 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 10832 */
	{.type Here, {.p 10832 }},	/* 10832 360 */
	{.type There, {.p 360 }},	/* 10832 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10840 */
	{.type Here, {.p 10840 }},	/* 10840 360 */
	{.type There, {.p 360 }},	/* 10840 360 */
	{.type Absolute, {.p 0}},		/* dd 0 10848 */
	{.type Here, {.p 10848 }},	/* 10848 360 */
	{.type There, {.p 360 }},	/* 10848 360 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 10856 */
	{.type Here, {.p 10856 }},	/* 10856 360 */
	{.type There, {.p 360 }},	/* 10856 360 */
	{.type Here, {.p 10856 }},	/* 10856 360 */
	{.type There, {.p 360 }},	/* 10856 360 */
	{.type Here, {.p 10856 }},	/* 10856 360 */
	{.type There, {.p 360 }},	/* 10856 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10864 */
	{.type Here, {.p 10864 }},	/* 10864 360 */
	{.type There, {.p 360 }},	/* 10864 360 */
	{.type Absolute, {.p 1}},		/* dd 1 10872 */
	{.type Here, {.p 10872 }},	/* 10872 360 */
	{.type There, {.p 360 }},	/* 10872 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 10880 */
	{.type Here, {.p 10880 }},	/* 10880 360 */
	{.type There, {.p 360 }},	/* 10880 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 10888 */
	{.type Here, {.p 10888 }},	/* 10888 360 */
	{.type There, {.p 360 }},	/* 10888 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 10896 */
	{.type Here, {.p 10896 }},	/* 10896 360 */
	{.type There, {.p 360 }},	/* 10896 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 10904 */
	{.type Here, {.p 10904 }},	/* 10904 360 */
	{.type There, {.p 360 }},	/* 10904 360 */
	{.type Absolute, {.p -1}},		/* dd -1 10912 */
	{.type Here, {.p 10912 }},	/* 10912 360 */
	{.type There, {.p 360 }},	/* 10912 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 10920 */
	{.type Here, {.p 10920 }},	/* 10920 360 */
	{.type There, {.p 360 }},	/* 10920 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10928 */
	{.type Here, {.p 10928 }},	/* 10928 360 */
	{.type There, {.p 360 }},	/* 10928 360 */
	{.type Here, {.p 10928 }},	/* 10928 360 */
	{.type There, {.p 360 }},	/* 10928 360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 10936 */
	{.type Here, {.p 10936 }},	/* 10936 360 */
	{.type There, {.p 360 }},	/* 10936 360 */
	{.type FromDictionary, {.p L_C_stdinput}, .src = "dd L_C_stdinput"},		/* dd L_C_stdinput 10944 */
	{.type Here, {.p 10944 }},	/* 10944 360 */
	{.type There, {.p 360 }},	/* 10944 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 10952 */
	{.type Here, {.p 10952 }},	/* 10952 360 */
	{.type There, {.p 360 }},	/* 10952 360 */
	{.type Here, {.p 10952 }},	/* 10952 360 */
	{.type There, {.p 360 }},	/* 10952 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10960 */
	{.type Here, {.p 10960 }},	/* 10960 360 */
	{.type There, {.p 360 }},	/* 10960 360 */
	{.type Here, {.p 10960 }},	/* 10960 360 */
	{.type There, {.p 360 }},	/* 10960 360 */
	{.type Header, {.hdr { 4, "args", /* C_args = 10976 */ colon }}}, /* CENTRY "args" args 4 ; stream input from #p/<pid>/args into Text input buffer h 10984 */
	{.type Here, {.p 10984 }},	/* 10984 360 */
	{.type There, {.p 360 }},	/* 10984 360 */
	{.type Here, {.p 10984 }},	/* 10984 360 */
	{.type There, {.p 360 }},	/* 10984 360 */
	{.type FromDictionary, {.p MV_Argsfilename}, .src = "dd MV_Argsfilename	; ( 'args_filename_counted_string ) filled by the starter"},		/* dd MV_Argsfilename	; ( 'args_filename_counted_string ) filled by the starter 10992 */
	{.type Here, {.p 10992 }},	/* 10992 360 */
	{.type There, {.p 360 }},	/* 10992 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 11000 */
	{.type Here, {.p 11000 }},	/* 11000 360 */
	{.type There, {.p 360 }},	/* 11000 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11008 */
	{.type Here, {.p 11008 }},	/* 11008 360 */
	{.type There, {.p 360 }},	/* 11008 360 */
	{.type Absolute, {.p 0}},		/* dd 0 11016 */
	{.type Here, {.p 11016 }},	/* 11016 360 */
	{.type There, {.p 360 }},	/* 11016 360 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 11024 */
	{.type Here, {.p 11024 }},	/* 11024 360 */
	{.type There, {.p 360 }},	/* 11024 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11032 */
	{.type Here, {.p 11032 }},	/* 11032 360 */
	{.type There, {.p 360 }},	/* 11032 360 */
	{.type FromDictionary, {.p L_C_args_read}, .src = "dd L_C_args_read"},		/* dd L_C_args_read 11040 */
	{.type Here, {.p 11040 }},	/* 11040 360 */
	{.type There, {.p 360 }},	/* 11040 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11048 */
	{.type Here, {.p 11048 }},	/* 11048 360 */
	{.type There, {.p 360 }},	/* 11048 360 */
	{.type Here, {.p 11048 }},	/* 11048 360 */
	{.type There, {.p 360 }},	/* 11048 360 */
	{.type Here, {.p 11048 }},	/* 11048 360 */
	{.type There, {.p 360 }},	/* 11048 360 */
	{.type FromDictionary, {.p MV_Argsfilename}, .src = "dd MV_Argsfilename"},		/* dd MV_Argsfilename 11056 */
	{.type Here, {.p 11056 }},	/* 11056 360 */
	{.type There, {.p 360 }},	/* 11056 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 11064 */
	{.type Here, {.p 11064 }},	/* 11064 360 */
	{.type There, {.p 360 }},	/* 11064 360 */
	{.type FromDictionary, {.p C_ro}, .src = "dd C_ro"},		/* dd C_ro 11072 */
	{.type Here, {.p 11072 }},	/* 11072 360 */
	{.type There, {.p 360 }},	/* 11072 360 */
	{.type FromDictionary, {.p C_open_file}, .src = "dd C_open_file"},		/* dd C_open_file 11080 */
	{.type Here, {.p 11080 }},	/* 11080 360 */
	{.type There, {.p 360 }},	/* 11080 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 11088 */
	{.type Here, {.p 11088 }},	/* 11088 360 */
	{.type There, {.p 360 }},	/* 11088 360 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 11096 */
	{.type Here, {.p 11096 }},	/* 11096 360 */
	{.type There, {.p 360 }},	/* 11096 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11104 */
	{.type Here, {.p 11104 }},	/* 11104 360 */
	{.type There, {.p 360 }},	/* 11104 360 */
	{.type Here, {.p 11104 }},	/* 11104 360 */
	{.type There, {.p 360 }},	/* 11104 360 */
	{.type FromDictionary, {.p C_interpret}, .src = "dd C_interpret"},		/* dd C_interpret 11112 */
	{.type Here, {.p 11112 }},	/* 11112 360 */
	{.type There, {.p 360 }},	/* 11112 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11120 */
	{.type Here, {.p 11120 }},	/* 11120 360 */
	{.type There, {.p 360 }},	/* 11120 360 */
	{.type Here, {.p 11120 }},	/* 11120 360 */
	{.type There, {.p 360 }},	/* 11120 360 */
	{.type Header, {.hdr { 6, "input@", /* C_input_fetch = 11136 */ colon }}}, /* CENTRY "input@" input_fetch 6 ; ( -- Bufferfds Infd #Buffers+1 ) save input stream onto the stack and replace the buffer fd's with -1 h 11144 */
	{.type Here, {.p 11144 }},	/* 11144 360 */
	{.type There, {.p 360 }},	/* 11144 360 */
	{.type Here, {.p 11144 }},	/* 11144 360 */
	{.type There, {.p 360 }},	/* 11144 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 11152 */
	{.type Here, {.p 11152 }},	/* 11152 360 */
	{.type There, {.p 360 }},	/* 11152 360 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 11160 */
	{.type Here, {.p 11160 }},	/* 11160 360 */
	{.type There, {.p 360 }},	/* 11160 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11168 */
	{.type Here, {.p 11168 }},	/* 11168 360 */
	{.type There, {.p 360 }},	/* 11168 360 */
	{.type Absolute, {.p 0}},		/* dd 0 11176 */
	{.type Here, {.p 11176 }},	/* 11176 360 */
	{.type There, {.p 360 }},	/* 11176 360 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 11184 */
	{.type Here, {.p 11184 }},	/* 11184 360 */
	{.type There, {.p 360 }},	/* 11184 360 */
	{.type Here, {.p 11184 }},	/* 11184 360 */
	{.type There, {.p 360 }},	/* 11184 360 */
	{.type Here, {.p 11184 }},	/* 11184 360 */
	{.type There, {.p 360 }},	/* 11184 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11192 */
	{.type Here, {.p 11192 }},	/* 11192 360 */
	{.type There, {.p 360 }},	/* 11192 360 */
	{.type Absolute, {.p 1}},		/* dd 1 11200 */
	{.type Here, {.p 11200 }},	/* 11200 360 */
	{.type There, {.p 360 }},	/* 11200 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 11208 */
	{.type Here, {.p 11208 }},	/* 11208 360 */
	{.type There, {.p 360 }},	/* 11208 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11216 */
	{.type Here, {.p 11216 }},	/* 11216 360 */
	{.type There, {.p 360 }},	/* 11216 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 11224 */
	{.type Here, {.p 11224 }},	/* 11224 360 */
	{.type There, {.p 360 }},	/* 11224 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11232 */
	{.type Here, {.p 11232 }},	/* 11232 360 */
	{.type There, {.p 360 }},	/* 11232 360 */
	{.type Here, {.p 11232 }},	/* 11232 360 */
	{.type There, {.p 360 }},	/* 11232 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( 'Bufferfd 'Bufferfd )"},		/* dd M_dup	; ( 'Bufferfd 'Bufferfd ) 11240 */
	{.type Here, {.p 11240 }},	/* 11240 360 */
	{.type There, {.p 360 }},	/* 11240 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11248 */
	{.type Here, {.p 11248 }},	/* 11248 360 */
	{.type There, {.p 360 }},	/* 11248 360 */
	{.type Absolute, {.p -1}},		/* dd -1 11256 */
	{.type Here, {.p 11256 }},	/* 11256 360 */
	{.type There, {.p 360 }},	/* 11256 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( 'Bufferfd -1 'Bufferfd )"},		/* dd M_xswap	; ( 'Bufferfd -1 'Bufferfd ) 11264 */
	{.type Here, {.p 11264 }},	/* 11264 360 */
	{.type There, {.p 360 }},	/* 11264 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; ( 'Bufferfd )"},		/* dd M_store	; ( 'Bufferfd ) 11272 */
	{.type Here, {.p 11272 }},	/* 11272 360 */
	{.type There, {.p 360 }},	/* 11272 360 */
	{.type Here, {.p 11272 }},	/* 11272 360 */
	{.type There, {.p 360 }},	/* 11272 360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 11280 */
	{.type Here, {.p 11280 }},	/* 11280 360 */
	{.type There, {.p 360 }},	/* 11280 360 */
	{.type FromDictionary, {.p L_C_input_fetch}, .src = "dd L_C_input_fetch"},		/* dd L_C_input_fetch 11288 */
	{.type Here, {.p 11288 }},	/* 11288 360 */
	{.type There, {.p 360 }},	/* 11288 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 11296 */
	{.type Here, {.p 11296 }},	/* 11296 360 */
	{.type There, {.p 360 }},	/* 11296 360 */
	{.type Here, {.p 11296 }},	/* 11296 360 */
	{.type There, {.p 360 }},	/* 11296 360 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 11304 */
	{.type Here, {.p 11304 }},	/* 11304 360 */
	{.type There, {.p 360 }},	/* 11304 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11312 */
	{.type Here, {.p 11312 }},	/* 11312 360 */
	{.type There, {.p 360 }},	/* 11312 360 */
	{.type Here, {.p 11312 }},	/* 11312 360 */
	{.type There, {.p 360 }},	/* 11312 360 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 11320 */
	{.type Here, {.p 11320 }},	/* 11320 360 */
	{.type There, {.p 360 }},	/* 11320 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11328 */
	{.type Here, {.p 11328 }},	/* 11328 360 */
	{.type There, {.p 360 }},	/* 11328 360 */
	{.type Absolute, {.p 1}},		/* dd 1 11336 */
	{.type Here, {.p 11336 }},	/* 11336 360 */
	{.type There, {.p 360 }},	/* 11336 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11344 */
	{.type Here, {.p 11344 }},	/* 11344 360 */
	{.type There, {.p 360 }},	/* 11344 360 */
	{.type Here, {.p 11344 }},	/* 11344 360 */
	{.type There, {.p 360 }},	/* 11344 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11352 */
	{.type Here, {.p 11352 }},	/* 11352 360 */
	{.type There, {.p 360 }},	/* 11352 360 */
	{.type Here, {.p 11352 }},	/* 11352 360 */
	{.type There, {.p 360 }},	/* 11352 360 */
	{.type Header, {.hdr { 6, "input!", /* C_input_store = 11368 */ colon }}}, /* CENTRY "input!" input_store 6 ; ( <input>|empty -- ) ; restore input stream from the stack or stdinput h 11376 */
	{.type Here, {.p 11376 }},	/* 11376 360 */
	{.type There, {.p 360 }},	/* 11376 360 */
	{.type Here, {.p 11376 }},	/* 11376 360 */
	{.type There, {.p 360 }},	/* 11376 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup		; check if there is #Buffers+1 on the top of stack"},		/* dd M_dup		; check if there is #Buffers+1 on the top of stack 11384 */
	{.type Here, {.p 11384 }},	/* 11384 360 */
	{.type There, {.p 360 }},	/* 11384 360 */
	{.type Here, {.p 11384 }},	/* 11384 360 */
	{.type There, {.p 360 }},	/* 11384 360 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 11392 */
	{.type Here, {.p 11392 }},	/* 11392 360 */
	{.type There, {.p 360 }},	/* 11392 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11400 */
	{.type Here, {.p 11400 }},	/* 11400 360 */
	{.type There, {.p 360 }},	/* 11400 360 */
	{.type Absolute, {.p 1}},		/* dd 1 11408 */
	{.type Here, {.p 11408 }},	/* 11408 360 */
	{.type There, {.p 360 }},	/* 11408 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11416 */
	{.type Here, {.p 11416 }},	/* 11416 360 */
	{.type There, {.p 360 }},	/* 11416 360 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal	; is the top of stack == #Buffers+1"},		/* dd M_equal	; is the top of stack == #Buffers+1 11424 */
	{.type Here, {.p 11424 }},	/* 11424 360 */
	{.type There, {.p 360 }},	/* 11424 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11432 */
	{.type Here, {.p 11432 }},	/* 11432 360 */
	{.type There, {.p 360 }},	/* 11432 360 */
	{.type FromDictionary, {.p L_C_input_store_1}, .src = "dd L_C_input_store_1	; top of stack <> #Buffers+1, there is no input stream on the stack, use the default input"},		/* dd L_C_input_store_1	; top of stack <> #Buffers+1, there is no input stream on the stack, use the default input 11440 */
	{.type Here, {.p 11440 }},	/* 11440 360 */
	{.type There, {.p 360 }},	/* 11440 360 */
	{.type Here, {.p 11440 }},	/* 11440 360 */
	{.type There, {.p 360 }},	/* 11440 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; drop the #Buffers+1 on the top of stack"},		/* dd M_drop	; drop the #Buffers+1 on the top of stack 11448 */
	{.type Here, {.p 11448 }},	/* 11448 360 */
	{.type There, {.p 360 }},	/* 11448 360 */
	{.type Here, {.p 11448 }},	/* 11448 360 */
	{.type There, {.p 360 }},	/* 11448 360 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 11456 */
	{.type Here, {.p 11456 }},	/* 11456 360 */
	{.type There, {.p 360 }},	/* 11456 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11464 */
	{.type Here, {.p 11464 }},	/* 11464 360 */
	{.type There, {.p 360 }},	/* 11464 360 */
	{.type Here, {.p 11464 }},	/* 11464 360 */
	{.type There, {.p 360 }},	/* 11464 360 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 11472 */
	{.type Here, {.p 11472 }},	/* 11472 360 */
	{.type There, {.p 360 }},	/* 11472 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11480 */
	{.type Here, {.p 11480 }},	/* 11480 360 */
	{.type There, {.p 360 }},	/* 11480 360 */
	{.type Absolute, {.p 0}},		/* dd 0 11488 */
	{.type Here, {.p 11488 }},	/* 11488 360 */
	{.type There, {.p 360 }},	/* 11488 360 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 11496 */
	{.type Here, {.p 11496 }},	/* 11496 360 */
	{.type There, {.p 360 }},	/* 11496 360 */
	{.type Here, {.p 11496 }},	/* 11496 360 */
	{.type There, {.p 360 }},	/* 11496 360 */
	{.type Here, {.p 11496 }},	/* 11496 360 */
	{.type There, {.p 360 }},	/* 11496 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 11504 */
	{.type Here, {.p 11504 }},	/* 11504 360 */
	{.type There, {.p 360 }},	/* 11504 360 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 11512 */
	{.type Here, {.p 11512 }},	/* 11512 360 */
	{.type There, {.p 360 }},	/* 11512 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 11520 */
	{.type Here, {.p 11520 }},	/* 11520 360 */
	{.type There, {.p 360 }},	/* 11520 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11528 */
	{.type Here, {.p 11528 }},	/* 11528 360 */
	{.type There, {.p 360 }},	/* 11528 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11536 */
	{.type Here, {.p 11536 }},	/* 11536 360 */
	{.type There, {.p 360 }},	/* 11536 360 */
	{.type Here, {.p 11536 }},	/* 11536 360 */
	{.type There, {.p 360 }},	/* 11536 360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 11544 */
	{.type Here, {.p 11544 }},	/* 11544 360 */
	{.type There, {.p 360 }},	/* 11544 360 */
	{.type FromDictionary, {.p L_C_input_store}, .src = "dd L_C_input_store"},		/* dd L_C_input_store 11552 */
	{.type Here, {.p 11552 }},	/* 11552 360 */
	{.type There, {.p 360 }},	/* 11552 360 */
	{.type Here, {.p 11552 }},	/* 11552 360 */
	{.type There, {.p 360 }},	/* 11552 360 */
	{.type FromDictionary, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 11560 */
	{.type Here, {.p 11560 }},	/* 11560 360 */
	{.type There, {.p 360 }},	/* 11560 360 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off	; reset Eof back to 0"},		/* dd C_off	; reset Eof back to 0 11568 */
	{.type Here, {.p 11568 }},	/* 11568 360 */
	{.type There, {.p 360 }},	/* 11568 360 */
	{.type Here, {.p 11568 }},	/* 11568 360 */
	{.type There, {.p 360 }},	/* 11568 360 */
	{.type FromDictionary, {.p C_true}, .src = "dd C_true	; ( true )"},		/* dd C_true	; ( true ) 11576 */
	{.type Here, {.p 11576 }},	/* 11576 360 */
	{.type There, {.p 360 }},	/* 11576 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11584 */
	{.type Here, {.p 11584 }},	/* 11584 360 */
	{.type There, {.p 360 }},	/* 11584 360 */
	{.type Here, {.p 11584 }},	/* 11584 360 */
	{.type There, {.p 360 }},	/* 11584 360 */
	{.type Here, {.p 11584 }},	/* 11584 360 */
	{.type There, {.p 360 }},	/* 11584 360 */
	{.type FromDictionary, {.p C_stdinput}, .src = "dd C_stdinput	; no input stream on the stack, use default input from now"},		/* dd C_stdinput	; no input stream on the stack, use default input from now 11592 */
	{.type Here, {.p 11592 }},	/* 11592 360 */
	{.type There, {.p 360 }},	/* 11592 360 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false		; ( 0 )"},		/* dd C_false		; ( 0 ) 11600 */
	{.type Here, {.p 11600 }},	/* 11600 360 */
	{.type There, {.p 360 }},	/* 11600 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11608 */
	{.type Here, {.p 11608 }},	/* 11608 360 */
	{.type There, {.p 360 }},	/* 11608 360 */
	{.type Here, {.p 11608 }},	/* 11608 360 */
	{.type There, {.p 360 }},	/* 11608 360 */
/* ; closefds: close all buffer fds and Infd, set buffer fds and Infd to -1 */	{.type Here, {.p 11608 }},	/* 11608 360 */
	{.type There, {.p 360 }},	/* 11608 360 */
	{.type Header, {.hdr { 6, "-input", /* C_close_input = 11624 */ colon }}}, /* CENTRY "-input" close_input 6 ; ( <input>|empty -- ) ; restore input stream from the stack or stdinput h 11632 */
	{.type Here, {.p 11632 }},	/* 11632 360 */
	{.type There, {.p 360 }},	/* 11632 360 */
	{.type Here, {.p 11632 }},	/* 11632 360 */
	{.type There, {.p 360 }},	/* 11632 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 11640 */
	{.type Here, {.p 11640 }},	/* 11640 360 */
	{.type There, {.p 360 }},	/* 11640 360 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 11648 */
	{.type Here, {.p 11648 }},	/* 11648 360 */
	{.type There, {.p 360 }},	/* 11648 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11656 */
	{.type Here, {.p 11656 }},	/* 11656 360 */
	{.type There, {.p 360 }},	/* 11656 360 */
	{.type Absolute, {.p 0}},		/* dd 0 11664 */
	{.type Here, {.p 11664 }},	/* 11664 360 */
	{.type There, {.p 360 }},	/* 11664 360 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 11672 */
	{.type Here, {.p 11672 }},	/* 11672 360 */
	{.type There, {.p 360 }},	/* 11672 360 */
	{.type Here, {.p 11672 }},	/* 11672 360 */
	{.type There, {.p 360 }},	/* 11672 360 */
	{.type Here, {.p 11672 }},	/* 11672 360 */
	{.type There, {.p 360 }},	/* 11672 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11680 */
	{.type Here, {.p 11680 }},	/* 11680 360 */
	{.type There, {.p 360 }},	/* 11680 360 */
	{.type Absolute, {.p 1}},		/* dd 1 11688 */
	{.type Here, {.p 11688 }},	/* 11688 360 */
	{.type There, {.p 360 }},	/* 11688 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 11696 */
	{.type Here, {.p 11696 }},	/* 11696 360 */
	{.type There, {.p 360 }},	/* 11696 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11704 */
	{.type Here, {.p 11704 }},	/* 11704 360 */
	{.type There, {.p 360 }},	/* 11704 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( 'Bufferfd 'Bufferfd )"},		/* dd M_dup	; ( 'Bufferfd 'Bufferfd ) 11712 */
	{.type Here, {.p 11712 }},	/* 11712 360 */
	{.type There, {.p 360 }},	/* 11712 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( 'Bufferfd fd )"},		/* dd M_fetch	; ( 'Bufferfd fd ) 11720 */
	{.type Here, {.p 11720 }},	/* 11720 360 */
	{.type There, {.p 360 }},	/* 11720 360 */
	{.type FromDictionary, {.p C_close_file}, .src = "dd C_close_file	; ( 'Bufferfd ioresult )"},		/* dd C_close_file	; ( 'Bufferfd ioresult ) 11728 */
	{.type Here, {.p 11728 }},	/* 11728 360 */
	{.type There, {.p 360 }},	/* 11728 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; ( 'Bufferfd )"},		/* dd M_drop	; ( 'Bufferfd ) 11736 */
	{.type Here, {.p 11736 }},	/* 11736 360 */
	{.type There, {.p 360 }},	/* 11736 360 */
	{.type Here, {.p 11736 }},	/* 11736 360 */
	{.type There, {.p 360 }},	/* 11736 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( 'Bufferfd 'Bufferfd )"},		/* dd M_dup	; ( 'Bufferfd 'Bufferfd ) 11744 */
	{.type Here, {.p 11744 }},	/* 11744 360 */
	{.type There, {.p 360 }},	/* 11744 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11752 */
	{.type Here, {.p 11752 }},	/* 11752 360 */
	{.type There, {.p 360 }},	/* 11752 360 */
	{.type Absolute, {.p -1}},		/* dd -1 11760 */
	{.type Here, {.p 11760 }},	/* 11760 360 */
	{.type There, {.p 360 }},	/* 11760 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( 'Bufferfd -1 'Bufferfd )"},		/* dd M_xswap	; ( 'Bufferfd -1 'Bufferfd ) 11768 */
	{.type Here, {.p 11768 }},	/* 11768 360 */
	{.type There, {.p 360 }},	/* 11768 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; ( 'Bufferfd )"},		/* dd M_store	; ( 'Bufferfd ) 11776 */
	{.type Here, {.p 11776 }},	/* 11776 360 */
	{.type There, {.p 360 }},	/* 11776 360 */
	{.type Here, {.p 11776 }},	/* 11776 360 */
	{.type There, {.p 360 }},	/* 11776 360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 11784 */
	{.type Here, {.p 11784 }},	/* 11784 360 */
	{.type There, {.p 360 }},	/* 11784 360 */
	{.type FromDictionary, {.p L_C_close_input}, .src = "dd L_C_close_input"},		/* dd L_C_close_input 11792 */
	{.type Here, {.p 11792 }},	/* 11792 360 */
	{.type There, {.p 360 }},	/* 11792 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 11800 */
	{.type Here, {.p 11800 }},	/* 11800 360 */
	{.type There, {.p 360 }},	/* 11800 360 */
	{.type Here, {.p 11800 }},	/* 11800 360 */
	{.type There, {.p 360 }},	/* 11800 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11808 */
	{.type Here, {.p 11808 }},	/* 11808 360 */
	{.type There, {.p 360 }},	/* 11808 360 */
	{.type Absolute, {.p -1}},		/* dd -1 11816 */
	{.type Here, {.p 11816 }},	/* 11816 360 */
	{.type There, {.p 360 }},	/* 11816 360 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd	; ( -1 'Infd )"},		/* dd MV_Infd	; ( -1 'Infd ) 11824 */
	{.type Here, {.p 11824 }},	/* 11824 360 */
	{.type There, {.p 360 }},	/* 11824 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( -1 'Infd 'Infd )"},		/* dd M_dup	; ( -1 'Infd 'Infd ) 11832 */
	{.type Here, {.p 11832 }},	/* 11832 360 */
	{.type There, {.p 360 }},	/* 11832 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( -1 'Infd fd )"},		/* dd M_fetch	; ( -1 'Infd fd ) 11840 */
	{.type Here, {.p 11840 }},	/* 11840 360 */
	{.type There, {.p 360 }},	/* 11840 360 */
	{.type FromDictionary, {.p C_close_file}, .src = "dd C_close_file	; ( -1 'Infd ioresult )"},		/* dd C_close_file	; ( -1 'Infd ioresult ) 11848 */
	{.type Here, {.p 11848 }},	/* 11848 360 */
	{.type There, {.p 360 }},	/* 11848 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; ( -1 'Infd )"},		/* dd M_drop	; ( -1 'Infd ) 11856 */
	{.type Here, {.p 11856 }},	/* 11856 360 */
	{.type There, {.p 360 }},	/* 11856 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11864 */
	{.type Here, {.p 11864 }},	/* 11864 360 */
	{.type There, {.p 360 }},	/* 11864 360 */
	{.type Here, {.p 11864 }},	/* 11864 360 */
	{.type There, {.p 360 }},	/* 11864 360 */
	{.type FromDictionary, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 11872 */
	{.type Here, {.p 11872 }},	/* 11872 360 */
	{.type There, {.p 360 }},	/* 11872 360 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off	; reset Eof back to 0"},		/* dd C_off	; reset Eof back to 0 11880 */
	{.type Here, {.p 11880 }},	/* 11880 360 */
	{.type There, {.p 360 }},	/* 11880 360 */
	{.type Here, {.p 11880 }},	/* 11880 360 */
	{.type There, {.p 360 }},	/* 11880 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11888 */
	{.type Here, {.p 11888 }},	/* 11888 360 */
	{.type There, {.p 360 }},	/* 11888 360 */
	{.type Here, {.p 11888 }},	/* 11888 360 */
	{.type There, {.p 360 }},	/* 11888 360 */
	{.type Header, {.hdr { 7, "-+input", /* C_restore_input = 11904 */ colon }}}, /* CENTRY "-+input" restore_input 7 ; ( <input> -- ) ; use the input stream on the stack or abort h 11912 */
	{.type Here, {.p 11912 }},	/* 11912 360 */
	{.type There, {.p 360 }},	/* 11912 360 */
	{.type Here, {.p 11912 }},	/* 11912 360 */
	{.type There, {.p 360 }},	/* 11912 360 */
	{.type FromDictionary, {.p C_close_input}, .src = "dd C_close_input"},		/* dd C_close_input 11920 */
	{.type Here, {.p 11920 }},	/* 11920 360 */
	{.type There, {.p 360 }},	/* 11920 360 */
	{.type Here, {.p 11920 }},	/* 11920 360 */
	{.type There, {.p 360 }},	/* 11920 360 */
	{.type FromDictionary, {.p C_input_store}, .src = "dd C_input_store"},		/* dd C_input_store 11928 */
	{.type Here, {.p 11928 }},	/* 11928 360 */
	{.type There, {.p 360 }},	/* 11928 360 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 11936 */
	{.type Here, {.p 11936 }},	/* 11936 360 */
	{.type There, {.p 360 }},	/* 11936 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11944 */
	{.type Here, {.p 11944 }},	/* 11944 360 */
	{.type There, {.p 360 }},	/* 11944 360 */
	{.type FromDictionary, {.p L_restore_input}, .src = "dd L_restore_input	; input stream restored"},		/* dd L_restore_input	; input stream restored 11952 */
	{.type Here, {.p 11952 }},	/* 11952 360 */
	{.type There, {.p 360 }},	/* 11952 360 */
	{.type Here, {.p 11952 }},	/* 11952 360 */
	{.type There, {.p 360 }},	/* 11952 360 */
/* ; no input stream on the stack to restore, show error and abort */	{.type Here, {.p 11952 }},	/* 11952 360 */
	{.type There, {.p 360 }},	/* 11952 360 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 11960 */
	{.type Here, {.p 11960 }},	/* 11960 360 */
	{.type There, {.p 360 }},	/* 11960 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11968 */
	{.type Here, {.p 11968 }},	/* 11968 360 */
	{.type There, {.p 360 }},	/* 11968 360 */
	{.type FromDictionary, {.p L137}, .src = "dd L137"},		/* dd L137 11976 */
	{.type Here, {.p 11976 }},	/* 11976 360 */
	{.type There, {.p 360 }},	/* 11976 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 11984 */
	{.type Here, {.p 11984 }},	/* 11984 360 */
	{.type There, {.p 360 }},	/* 11984 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 11992 */
	{.type Here, {.p 11992 }},	/* 11992 360 */
	{.type There, {.p 360 }},	/* 11992 360 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 12000 */
	{.type Here, {.p 12000 }},	/* 12000 360 */
	{.type There, {.p 360 }},	/* 12000 360 */
	{.type FromDictionary, {.p C_depth}, .src = "dd C_depth"},		/* dd C_depth 12008 */
	{.type Here, {.p 12008 }},	/* 12008 360 */
	{.type There, {.p 360 }},	/* 12008 360 */
	{.type FromDictionary, {.p C_dot}, .src = "dd C_dot"},		/* dd C_dot 12016 */
	{.type Here, {.p 12016 }},	/* 12016 360 */
	{.type There, {.p 360 }},	/* 12016 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12024 */
	{.type Here, {.p 12024 }},	/* 12024 360 */
	{.type There, {.p 360 }},	/* 12024 360 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12032 */
	{.type Here, {.p 12032 }},	/* 12032 360 */
	{.type There, {.p 360 }},	/* 12032 360 */
	{.type Here, {.p 12032 }},	/* 12032 360 */
	{.type There, {.p 360 }},	/* 12032 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12040 */
	{.type Here, {.p 12040 }},	/* 12040 360 */
	{.type There, {.p 360 }},	/* 12040 360 */
	{.type Here, {.p 12040 }},	/* 12040 360 */
	{.type There, {.p 360 }},	/* 12040 360 */
	{.type Header, {.hdr { 10, "buffername", /* C_buffername = 12064 */ colon }}}, /* CENTRY "buffername" buffername 10 ; ( index -- 'counted_string ) build the buffer fd's filename h 12072 */
	{.type Here, {.p 12072 }},	/* 12072 360 */
	{.type There, {.p 360 }},	/* 12072 360 */
	{.type Here, {.p 12072 }},	/* 12072 360 */
	{.type There, {.p 360 }},	/* 12072 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells	; ( index*cellsize ) number of bytes"},		/* dd C_cells	; ( index*cellsize ) number of bytes 12080 */
	{.type Here, {.p 12080 }},	/* 12080 360 */
	{.type There, {.p 360 }},	/* 12080 360 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 12088 */
	{.type Here, {.p 12088 }},	/* 12088 360 */
	{.type There, {.p 360 }},	/* 12088 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( index*cellsize+'Bufferfilenames ) address of the filename's counted string"},		/* dd M_plus	; ( index*cellsize+'Bufferfilenames ) address of the filename's counted string 12096 */
	{.type Here, {.p 12096 }},	/* 12096 360 */
	{.type There, {.p 360 }},	/* 12096 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( 'filename_counted_string )"},		/* dd M_fetch	; ( 'filename_counted_string ) 12104 */
	{.type Here, {.p 12104 }},	/* 12104 360 */
	{.type There, {.p 360 }},	/* 12104 360 */
	{.type Here, {.p 12104 }},	/* 12104 360 */
	{.type There, {.p 360 }},	/* 12104 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12112 */
	{.type Here, {.p 12112 }},	/* 12112 360 */
	{.type There, {.p 360 }},	/* 12112 360 */
	{.type FromDictionary, {.p L120}, .src = "dd L120		; address of the counted string 3#n/"},		/* dd L120		; address of the counted string 3#n/ 12120 */
	{.type Here, {.p 12120 }},	/* 12120 360 */
	{.type There, {.p 360 }},	/* 12120 360 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 12128 */
	{.type Here, {.p 12128 }},	/* 12128 360 */
	{.type There, {.p 360 }},	/* 12128 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12136 */
	{.type Here, {.p 12136 }},	/* 12136 360 */
	{.type There, {.p 360 }},	/* 12136 360 */
	{.type Absolute, {.p 4}},		/* dd 4 12144 */
	{.type Here, {.p 12144 }},	/* 12144 360 */
	{.type There, {.p 360 }},	/* 12144 360 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; pad has 3#n/"},		/* dd M_cmove	; pad has 3#n/ 12152 */
	{.type Here, {.p 12152 }},	/* 12152 360 */
	{.type There, {.p 360 }},	/* 12152 360 */
	{.type Here, {.p 12152 }},	/* 12152 360 */
	{.type There, {.p 360 }},	/* 12152 360 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 12160 */
	{.type Here, {.p 12160 }},	/* 12160 360 */
	{.type There, {.p 360 }},	/* 12160 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12168 */
	{.type Here, {.p 12168 }},	/* 12168 360 */
	{.type There, {.p 360 }},	/* 12168 360 */
	{.type Absolute, {.p 4}},		/* dd 4 12176 */
	{.type Here, {.p 12176 }},	/* 12176 360 */
	{.type There, {.p 360 }},	/* 12176 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 'filename_counted_string pad+4 )"},		/* dd M_plus	; ( 'filename_counted_string pad+4 ) 12184 */
	{.type Here, {.p 12184 }},	/* 12184 360 */
	{.type There, {.p 360 }},	/* 12184 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( 'filename_counted_string pad+4 ) (R pad+4 )"},		/* dd M_rpush	; ( 'filename_counted_string pad+4 ) (R pad+4 ) 12192 */
	{.type Here, {.p 12192 }},	/* 12192 360 */
	{.type There, {.p 360 }},	/* 12192 360 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 12200 */
	{.type Here, {.p 12200 }},	/* 12200 360 */
	{.type There, {.p 360 }},	/* 12200 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 12208 */
	{.type Here, {.p 12208 }},	/* 12208 360 */
	{.type There, {.p 360 }},	/* 12208 360 */
	{.type FromDictionary, {.p C_paren_dot_paren}, .src = "dd C_paren_dot_paren ; ( 'filename_counted_string pad+4 'text fd_text_count ) ( R pad+4 )"},		/* dd C_paren_dot_paren ; ( 'filename_counted_string pad+4 'text fd_text_count ) ( R pad+4 ) 12216 */
	{.type Here, {.p 12216 }},	/* 12216 360 */
	{.type There, {.p 360 }},	/* 12216 360 */
	{.type Here, {.p 12216 }},	/* 12216 360 */
	{.type There, {.p 360 }},	/* 12216 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12224 */
	{.type Here, {.p 12224 }},	/* 12224 360 */
	{.type There, {.p 360 }},	/* 12224 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 12232 */
	{.type Here, {.p 12232 }},	/* 12232 360 */
	{.type There, {.p 360 }},	/* 12232 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 12240 */
	{.type Here, {.p 12240 }},	/* 12240 360 */
	{.type There, {.p 360 }},	/* 12240 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush ; ( 'filename_counted_string pad+4 'text fd_text_count ) ( R pad+4+fd_text_count )"},		/* dd M_rpush ; ( 'filename_counted_string pad+4 'text fd_text_count ) ( R pad+4+fd_text_count ) 12248 */
	{.type Here, {.p 12248 }},	/* 12248 360 */
	{.type There, {.p 360 }},	/* 12248 360 */
	{.type Here, {.p 12248 }},	/* 12248 360 */
	{.type There, {.p 360 }},	/* 12248 360 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; now, pad has #n/<infd> ( 'filename_counted_string ) ( R pad+4+fd_text_count )"},		/* dd M_cmove	; now, pad has #n/<infd> ( 'filename_counted_string ) ( R pad+4+fd_text_count ) 12256 */
	{.type Here, {.p 12256 }},	/* 12256 360 */
	{.type There, {.p 360 }},	/* 12256 360 */
	{.type Here, {.p 12256 }},	/* 12256 360 */
	{.type There, {.p 360 }},	/* 12256 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( 'filename_counted_string pad+4+fd_text_count )"},		/* dd M_rpop	; ( 'filename_counted_string pad+4+fd_text_count ) 12264 */
	{.type Here, {.p 12264 }},	/* 12264 360 */
	{.type There, {.p 360 }},	/* 12264 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over	; ( 'filename_counted_string pad+4+fd_text_count 'filename_counted_string )"},		/* dd M_over	; ( 'filename_counted_string pad+4+fd_text_count 'filename_counted_string ) 12272 */
	{.type Here, {.p 12272 }},	/* 12272 360 */
	{.type There, {.p 360 }},	/* 12272 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( 'filename_counted_string pad+4+fd_text_count filename_count )"},		/* dd M_cfetch	; ( 'filename_counted_string pad+4+fd_text_count filename_count ) 12280 */
	{.type Here, {.p 12280 }},	/* 12280 360 */
	{.type There, {.p 360 }},	/* 12280 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( 'filename_counted_string pad+4+fd_text_count ) (R filename_count )"},		/* dd M_rpush	; ( 'filename_counted_string pad+4+fd_text_count ) (R filename_count ) 12288 */
	{.type Here, {.p 12288 }},	/* 12288 360 */
	{.type There, {.p 360 }},	/* 12288 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12296 */
	{.type Here, {.p 12296 }},	/* 12296 360 */
	{.type There, {.p 360 }},	/* 12296 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( 'filename_counted_string pad+4+fd_text_count ) (R filename_count pad+4+fd_text_count )"},		/* dd M_rpush	; ( 'filename_counted_string pad+4+fd_text_count ) (R filename_count pad+4+fd_text_count ) 12304 */
	{.type Here, {.p 12304 }},	/* 12304 360 */
	{.type There, {.p 360 }},	/* 12304 360 */
	{.type Here, {.p 12304 }},	/* 12304 360 */
	{.type There, {.p 360 }},	/* 12304 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( pad+4+fd_text_count 'filename_counted_string ) (R filename_count pad+4+fd_text_count )"},		/* dd M_xswap	; ( pad+4+fd_text_count 'filename_counted_string ) (R filename_count pad+4+fd_text_count ) 12312 */
	{.type Here, {.p 12312 }},	/* 12312 360 */
	{.type There, {.p 360 }},	/* 12312 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count	; ( pad+4+fd_text_count 'filename count ) (R filename_count pad+4+fd_text_count )"},		/* dd C_count	; ( pad+4+fd_text_count 'filename count ) (R filename_count pad+4+fd_text_count ) 12320 */
	{.type Here, {.p 12320 }},	/* 12320 360 */
	{.type There, {.p 360 }},	/* 12320 360 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; now, pad has the whole filename ( ) (R filename_count pad+4+fd_text_count )"},		/* dd M_cmove	; now, pad has the whole filename ( ) (R filename_count pad+4+fd_text_count ) 12328 */
	{.type Here, {.p 12328 }},	/* 12328 360 */
	{.type There, {.p 360 }},	/* 12328 360 */
	{.type Here, {.p 12328 }},	/* 12328 360 */
	{.type There, {.p 360 }},	/* 12328 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 12336 */
	{.type Here, {.p 12336 }},	/* 12336 360 */
	{.type There, {.p 360 }},	/* 12336 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 12344 */
	{.type Here, {.p 12344 }},	/* 12344 360 */
	{.type There, {.p 360 }},	/* 12344 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( pad+4+fd_text_count+filename_count )"},		/* dd M_plus	; ( pad+4+fd_text_count+filename_count ) 12352 */
	{.type Here, {.p 12352 }},	/* 12352 360 */
	{.type There, {.p 360 }},	/* 12352 360 */
	{.type Here, {.p 12352 }},	/* 12352 360 */
	{.type There, {.p 360 }},	/* 12352 360 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 12360 */
	{.type Here, {.p 12360 }},	/* 12360 360 */
	{.type There, {.p 360 }},	/* 12360 360 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 12368 */
	{.type Here, {.p 12368 }},	/* 12368 360 */
	{.type There, {.p 360 }},	/* 12368 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus	; ( pad+4+fd_text_count+filename_count-pad-1 )"},		/* dd M_minus	; ( pad+4+fd_text_count+filename_count-pad-1 ) 12376 */
	{.type Here, {.p 12376 }},	/* 12376 360 */
	{.type There, {.p 360 }},	/* 12376 360 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 12384 */
	{.type Here, {.p 12384 }},	/* 12384 360 */
	{.type There, {.p 360 }},	/* 12384 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; Now, pad has a proper counted string"},		/* dd M_store	; Now, pad has a proper counted string 12392 */
	{.type Here, {.p 12392 }},	/* 12392 360 */
	{.type There, {.p 360 }},	/* 12392 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12400 */
	{.type Here, {.p 12400 }},	/* 12400 360 */
	{.type There, {.p 360 }},	/* 12400 360 */
	{.type Here, {.p 12400 }},	/* 12400 360 */
	{.type There, {.p 360 }},	/* 12400 360 */
/* ; max of a counted string is 256 bytes. Hence, cannot use it. */	{.type Here, {.p 12400 }},	/* 12400 360 */
	{.type There, {.p 360 }},	/* 12400 360 */
	{.type Header, {.hdr { 3, "get", /* C_get = 12416 */ colon }}}, /* CENTRY "get" get 3 ; ( index -- read_count ) read from the indexed Fd in Bufferfds into Tib h 12424 */
	{.type Here, {.p 12424 }},	/* 12424 360 */
	{.type There, {.p 360 }},	/* 12424 360 */
	{.type Here, {.p 12424 }},	/* 12424 360 */
	{.type There, {.p 360 }},	/* 12424 360 */
	{.type FromDictionary, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 12432 */
	{.type Here, {.p 12432 }},	/* 12432 360 */
	{.type There, {.p 360 }},	/* 12432 360 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off	; clear EOF flag"},		/* dd C_off	; clear EOF flag 12440 */
	{.type Here, {.p 12440 }},	/* 12440 360 */
	{.type There, {.p 360 }},	/* 12440 360 */
	{.type Here, {.p 12440 }},	/* 12440 360 */
	{.type There, {.p 360 }},	/* 12440 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12448 */
	{.type Here, {.p 12448 }},	/* 12448 360 */
	{.type There, {.p 360 }},	/* 12448 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells	; ( index index*cellsize ) number of bytes"},		/* dd C_cells	; ( index index*cellsize ) number of bytes 12456 */
	{.type Here, {.p 12456 }},	/* 12456 360 */
	{.type There, {.p 360 }},	/* 12456 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 12464 */
	{.type Here, {.p 12464 }},	/* 12464 360 */
	{.type There, {.p 360 }},	/* 12464 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( index index*cellsize+'Bufferfds ) address of the fd"},		/* dd M_plus	; ( index index*cellsize+'Bufferfds ) address of the fd 12472 */
	{.type Here, {.p 12472 }},	/* 12472 360 */
	{.type There, {.p 360 }},	/* 12472 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( index fd )"},		/* dd M_fetch	; ( index fd ) 12480 */
	{.type Here, {.p 12480 }},	/* 12480 360 */
	{.type There, {.p 360 }},	/* 12480 360 */
	{.type Here, {.p 12480 }},	/* 12480 360 */
	{.type There, {.p 360 }},	/* 12480 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( index fd fd )"},		/* dd M_dup	; ( index fd fd ) 12488 */
	{.type Here, {.p 12488 }},	/* 12488 360 */
	{.type There, {.p 360 }},	/* 12488 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12496 */
	{.type Here, {.p 12496 }},	/* 12496 360 */
	{.type There, {.p 360 }},	/* 12496 360 */
	{.type Absolute, {.p -1}},		/* dd -1 12504 */
	{.type Here, {.p 12504 }},	/* 12504 360 */
	{.type There, {.p 360 }},	/* 12504 360 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 12512 */
	{.type Here, {.p 12512 }},	/* 12512 360 */
	{.type There, {.p 360 }},	/* 12512 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump	; if fd == -1 ( index fd )"},		/* dd M_cjump	; if fd == -1 ( index fd ) 12520 */
	{.type Here, {.p 12520 }},	/* 12520 360 */
	{.type There, {.p 360 }},	/* 12520 360 */
	{.type FromDictionary, {.p L_C_get}, .src = "dd L_C_get	; when not -1"},		/* dd L_C_get	; when not -1 12528 */
	{.type Here, {.p 12528 }},	/* 12528 360 */
	{.type There, {.p 360 }},	/* 12528 360 */
	{.type Here, {.p 12528 }},	/* 12528 360 */
	{.type There, {.p 360 }},	/* 12528 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; when fd == -1 ( index )"},		/* dd M_drop	; when fd == -1 ( index ) 12536 */
	{.type Here, {.p 12536 }},	/* 12536 360 */
	{.type There, {.p 360 }},	/* 12536 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12544 */
	{.type Here, {.p 12544 }},	/* 12544 360 */
	{.type There, {.p 360 }},	/* 12544 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12552 */
	{.type Here, {.p 12552 }},	/* 12552 360 */
	{.type There, {.p 360 }},	/* 12552 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( index index ) (R index )"},		/* dd M_rpush	; ( index index ) (R index ) 12560 */
	{.type Here, {.p 12560 }},	/* 12560 360 */
	{.type There, {.p 360 }},	/* 12560 360 */
	{.type FromDictionary, {.p C_buffername}, .src = "dd C_buffername"},		/* dd C_buffername 12568 */
	{.type Here, {.p 12568 }},	/* 12568 360 */
	{.type There, {.p 360 }},	/* 12568 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count	; ( index 'filename-counted-string -- 'text count )"},		/* dd C_count	; ( index 'filename-counted-string -- 'text count ) 12576 */
	{.type Here, {.p 12576 }},	/* 12576 360 */
	{.type There, {.p 360 }},	/* 12576 360 */
	{.type FromDictionary, {.p C_ro}, .src = "dd C_ro"},		/* dd C_ro 12584 */
	{.type Here, {.p 12584 }},	/* 12584 360 */
	{.type There, {.p 360 }},	/* 12584 360 */
	{.type FromDictionary, {.p C_open_file}, .src = "dd C_open_file	; ( index fd ioresult )"},		/* dd C_open_file	; ( index fd ioresult ) 12592 */
	{.type Here, {.p 12592 }},	/* 12592 360 */
	{.type There, {.p 360 }},	/* 12592 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12600 */
	{.type Here, {.p 12600 }},	/* 12600 360 */
	{.type There, {.p 360 }},	/* 12600 360 */
	{.type FromDictionary, {.p L_C_get_store}, .src = "dd L_C_get_store"},		/* dd L_C_get_store 12608 */
	{.type Here, {.p 12608 }},	/* 12608 360 */
	{.type There, {.p 360 }},	/* 12608 360 */
	{.type Here, {.p 12608 }},	/* 12608 360 */
	{.type There, {.p 360 }},	/* 12608 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; ( index ) (R index ) returned false, could not open-file. write error message"},		/* dd M_drop	; ( index ) (R index ) returned false, could not open-file. write error message 12616 */
	{.type Here, {.p 12616 }},	/* 12616 360 */
	{.type There, {.p 360 }},	/* 12616 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12624 */
	{.type Here, {.p 12624 }},	/* 12624 360 */
	{.type There, {.p 360 }},	/* 12624 360 */
	{.type FromDictionary, {.p L140}, .src = "dd L140		; open error"},		/* dd L140		; open error 12632 */
	{.type Here, {.p 12632 }},	/* 12632 360 */
	{.type There, {.p 360 }},	/* 12632 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 12640 */
	{.type Here, {.p 12640 }},	/* 12640 360 */
	{.type There, {.p 360 }},	/* 12640 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12648 */
	{.type Here, {.p 12648 }},	/* 12648 360 */
	{.type There, {.p 360 }},	/* 12648 360 */
	{.type FromDictionary, {.p C_emit}, .src = "dd C_emit	; show the index"},		/* dd C_emit	; show the index 12656 */
	{.type Here, {.p 12656 }},	/* 12656 360 */
	{.type There, {.p 360 }},	/* 12656 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12664 */
	{.type Here, {.p 12664 }},	/* 12664 360 */
	{.type There, {.p 360 }},	/* 12664 360 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort	; abort on open error. How about terminate?"},		/* dd C_abort	; abort on open error. How about terminate? 12672 */
	{.type Here, {.p 12672 }},	/* 12672 360 */
	{.type There, {.p 360 }},	/* 12672 360 */
	{.type Here, {.p 12672 }},	/* 12672 360 */
	{.type There, {.p 360 }},	/* 12672 360 */
	{.type Here, {.p 12672 }},	/* 12672 360 */
	{.type There, {.p 360 }},	/* 12672 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( index fd fd )"},		/* dd M_dup	; ( index fd fd ) 12680 */
	{.type Here, {.p 12680 }},	/* 12680 360 */
	{.type There, {.p 360 }},	/* 12680 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( index fd fd index )"},		/* dd M_rpop	; ( index fd fd index ) 12688 */
	{.type Here, {.p 12688 }},	/* 12688 360 */
	{.type There, {.p 360 }},	/* 12688 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells	; ( index fd fd index*cellsize ) number of bytes"},		/* dd C_cells	; ( index fd fd index*cellsize ) number of bytes 12696 */
	{.type Here, {.p 12696 }},	/* 12696 360 */
	{.type There, {.p 360 }},	/* 12696 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 12704 */
	{.type Here, {.p 12704 }},	/* 12704 360 */
	{.type There, {.p 360 }},	/* 12704 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( index fd fd index*cellsize+'Bufferfds ) address of the filename's counted string"},		/* dd M_plus	; ( index fd fd index*cellsize+'Bufferfds ) address of the filename's counted string 12712 */
	{.type Here, {.p 12712 }},	/* 12712 360 */
	{.type There, {.p 360 }},	/* 12712 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; ( index fd )"},		/* dd M_store	; ( index fd ) 12720 */
	{.type Here, {.p 12720 }},	/* 12720 360 */
	{.type There, {.p 360 }},	/* 12720 360 */
	{.type Here, {.p 12720 }},	/* 12720 360 */
	{.type There, {.p 360 }},	/* 12720 360 */
	{.type Here, {.p 12720 }},	/* 12720 360 */
	{.type There, {.p 360 }},	/* 12720 360 */
	{.type FromDictionary, {.p MV_Tib}, .src = "dd MV_Tib"},		/* dd MV_Tib 12728 */
	{.type Here, {.p 12728 }},	/* 12728 360 */
	{.type There, {.p 360 }},	/* 12728 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12736 */
	{.type Here, {.p 12736 }},	/* 12736 360 */
	{.type There, {.p 360 }},	/* 12736 360 */
	{.type Absolute, {.p 4096}},		/* dd 4096		; ( index fd Tib 4096 ) 12744 */
	{.type Here, {.p 12744 }},	/* 12744 360 */
	{.type There, {.p 360 }},	/* 12744 360 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot	; ( index Tib 4096 fd )"},		/* dd C_rot	; ( index Tib 4096 fd ) 12752 */
	{.type Here, {.p 12752 }},	/* 12752 360 */
	{.type There, {.p 360 }},	/* 12752 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 12760 */
	{.type Here, {.p 12760 }},	/* 12760 360 */
	{.type There, {.p 360 }},	/* 12760 360 */
	{.type Here, {.p 12760 }},	/* 12760 360 */
	{.type There, {.p 360 }},	/* 12760 360 */
	{.type Here, {.p 12760 }},	/* 12760 360 */
	{.type There, {.p 360 }},	/* 12760 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12768 */
	{.type Here, {.p 12768 }},	/* 12768 360 */
	{.type There, {.p 360 }},	/* 12768 360 */
	{.type Absolute, {.p -1}},		/* dd -1 12776 */
	{.type Here, {.p 12776 }},	/* 12776 360 */
	{.type There, {.p 360 }},	/* 12776 360 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 12784 */
	{.type Here, {.p 12784 }},	/* 12784 360 */
	{.type There, {.p 360 }},	/* 12784 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12792 */
	{.type Here, {.p 12792 }},	/* 12792 360 */
	{.type There, {.p 360 }},	/* 12792 360 */
	{.type FromDictionary, {.p L_C_get_1}, .src = "dd L_C_get_1"},		/* dd L_C_get_1 12800 */
	{.type Here, {.p 12800 }},	/* 12800 360 */
	{.type There, {.p 360 }},	/* 12800 360 */
	{.type Here, {.p 12800 }},	/* 12800 360 */
	{.type There, {.p 360 }},	/* 12800 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12808 */
	{.type Here, {.p 12808 }},	/* 12808 360 */
	{.type There, {.p 360 }},	/* 12808 360 */
	{.type FromDictionary, {.p L141}, .src = "dd L141		; read error"},		/* dd L141		; read error 12816 */
	{.type Here, {.p 12816 }},	/* 12816 360 */
	{.type There, {.p 360 }},	/* 12816 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 12824 */
	{.type Here, {.p 12824 }},	/* 12824 360 */
	{.type There, {.p 360 }},	/* 12824 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12832 */
	{.type Here, {.p 12832 }},	/* 12832 360 */
	{.type There, {.p 360 }},	/* 12832 360 */
	{.type FromDictionary, {.p C_emit}, .src = "dd C_emit	; show the index"},		/* dd C_emit	; show the index 12840 */
	{.type Here, {.p 12840 }},	/* 12840 360 */
	{.type There, {.p 360 }},	/* 12840 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12848 */
	{.type Here, {.p 12848 }},	/* 12848 360 */
	{.type There, {.p 360 }},	/* 12848 360 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort	; abort on read error. How about terminate?"},		/* dd C_abort	; abort on read error. How about terminate? 12856 */
	{.type Here, {.p 12856 }},	/* 12856 360 */
	{.type There, {.p 360 }},	/* 12856 360 */
	{.type Here, {.p 12856 }},	/* 12856 360 */
	{.type There, {.p 360 }},	/* 12856 360 */
	{.type Here, {.p 12856 }},	/* 12856 360 */
	{.type There, {.p 360 }},	/* 12856 360 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip	; ( read_count )"},		/* dd C_nip	; ( read_count ) 12864 */
	{.type Here, {.p 12864 }},	/* 12864 360 */
	{.type There, {.p 360 }},	/* 12864 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( read_count read_count )"},		/* dd M_dup	; ( read_count read_count ) 12872 */
	{.type Here, {.p 12872 }},	/* 12872 360 */
	{.type There, {.p 360 }},	/* 12872 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12880 */
	{.type Here, {.p 12880 }},	/* 12880 360 */
	{.type There, {.p 360 }},	/* 12880 360 */
	{.type Absolute, {.p 0}},		/* dd 0 12888 */
	{.type Here, {.p 12888 }},	/* 12888 360 */
	{.type There, {.p 360 }},	/* 12888 360 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 12896 */
	{.type Here, {.p 12896 }},	/* 12896 360 */
	{.type There, {.p 360 }},	/* 12896 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12904 */
	{.type Here, {.p 12904 }},	/* 12904 360 */
	{.type There, {.p 360 }},	/* 12904 360 */
	{.type FromDictionary, {.p L_C_get_2}, .src = "dd L_C_get_2"},		/* dd L_C_get_2 12912 */
	{.type Here, {.p 12912 }},	/* 12912 360 */
	{.type There, {.p 360 }},	/* 12912 360 */
	{.type Here, {.p 12912 }},	/* 12912 360 */
	{.type There, {.p 360 }},	/* 12912 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; ( ) read_count == 0"},		/* dd M_drop	; ( ) read_count == 0 12920 */
	{.type Here, {.p 12920 }},	/* 12920 360 */
	{.type There, {.p 360 }},	/* 12920 360 */
	{.type FromDictionary, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 12928 */
	{.type Here, {.p 12928 }},	/* 12928 360 */
	{.type There, {.p 360 }},	/* 12928 360 */
	{.type FromDictionary, {.p C_on}, .src = "dd C_on		; end of file, qrestore_input"},		/* dd C_on		; end of file, qrestore_input 12936 */
	{.type Here, {.p 12936 }},	/* 12936 360 */
	{.type There, {.p 360 }},	/* 12936 360 */
	{.type FromDictionary, {.p C_restore_input}, .src = "dd C_restore_input"},		/* dd C_restore_input 12944 */
	{.type Here, {.p 12944 }},	/* 12944 360 */
	{.type There, {.p 360 }},	/* 12944 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12952 */
	{.type Here, {.p 12952 }},	/* 12952 360 */
	{.type There, {.p 360 }},	/* 12952 360 */
	{.type Here, {.p 12952 }},	/* 12952 360 */
	{.type There, {.p 360 }},	/* 12952 360 */
	{.type Here, {.p 12952 }},	/* 12952 360 */
	{.type There, {.p 360 }},	/* 12952 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12960 */
	{.type Here, {.p 12960 }},	/* 12960 360 */
	{.type There, {.p 360 }},	/* 12960 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12968 */
	{.type Here, {.p 12968 }},	/* 12968 360 */
	{.type There, {.p 360 }},	/* 12968 360 */
	{.type Absolute, {.p 4096}},		/* dd 4096 12976 */
	{.type Here, {.p 12976 }},	/* 12976 360 */
	{.type There, {.p 360 }},	/* 12976 360 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 12984 */
	{.type Here, {.p 12984 }},	/* 12984 360 */
	{.type There, {.p 360 }},	/* 12984 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12992 */
	{.type Here, {.p 12992 }},	/* 12992 360 */
	{.type There, {.p 360 }},	/* 12992 360 */
	{.type FromDictionary, {.p L_C_get_3}, .src = "dd L_C_get_3"},		/* dd L_C_get_3 13000 */
	{.type Here, {.p 13000 }},	/* 13000 360 */
	{.type There, {.p 360 }},	/* 13000 360 */
	{.type Here, {.p 13000 }},	/* 13000 360 */
	{.type There, {.p 360 }},	/* 13000 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13008 */
	{.type Here, {.p 13008 }},	/* 13008 360 */
	{.type There, {.p 360 }},	/* 13008 360 */
	{.type FromDictionary, {.p L_C_get_too_long}, .src = "dd L_C_get_too_long ; could not find a delimiter in 4096 bytes, reevaluate"},		/* dd L_C_get_too_long ; could not find a delimiter in 4096 bytes, reevaluate 13016 */
	{.type Here, {.p 13016 }},	/* 13016 360 */
	{.type There, {.p 360 }},	/* 13016 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13024 */
	{.type Here, {.p 13024 }},	/* 13024 360 */
	{.type There, {.p 360 }},	/* 13024 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13032 */
	{.type Here, {.p 13032 }},	/* 13032 360 */
	{.type There, {.p 360 }},	/* 13032 360 */
	{.type FromDictionary, {.p C_emit}, .src = "dd C_emit	; show the read_count"},		/* dd C_emit	; show the read_count 13040 */
	{.type Here, {.p 13040 }},	/* 13040 360 */
	{.type There, {.p 360 }},	/* 13040 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 13048 */
	{.type Here, {.p 13048 }},	/* 13048 360 */
	{.type There, {.p 360 }},	/* 13048 360 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort	; abort on read error. How about terminate?"},		/* dd C_abort	; abort on read error. How about terminate? 13056 */
	{.type Here, {.p 13056 }},	/* 13056 360 */
	{.type There, {.p 360 }},	/* 13056 360 */
	{.type Here, {.p 13056 }},	/* 13056 360 */
	{.type There, {.p 360 }},	/* 13056 360 */
	{.type Here, {.p 13056 }},	/* 13056 360 */
	{.type There, {.p 360 }},	/* 13056 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon	; ( read_count )"},		/* dd M_exitcolon	; ( read_count ) 13064 */
	{.type Here, {.p 13064 }},	/* 13064 360 */
	{.type There, {.p 360 }},	/* 13064 360 */
	{.type Here, {.p 13064 }},	/* 13064 360 */
	{.type There, {.p 360 }},	/* 13064 360 */
	{.type Header, {.hdr { 4, "parse", /* C_parse = 13080 */ colon }}}, /* CENTRY "parse" parse 4 ; ( read_count -- 'Wordb ) Wordb has a counted string. read_count number of bytes read into Tib h 13088 */
	{.type Here, {.p 13088 }},	/* 13088 360 */
	{.type There, {.p 360 }},	/* 13088 360 */
	{.type Here, {.p 13088 }},	/* 13088 360 */
	{.type There, {.p 360 }},	/* 13088 360 */
	{.type Here, {.p 13088 }},	/* 13088 360 */
	{.type There, {.p 360 }},	/* 13088 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( read_count read_count ) check if count > 255 bytes, then invalid word"},		/* dd M_dup	; ( read_count read_count ) check if count > 255 bytes, then invalid word 13096 */
	{.type Here, {.p 13096 }},	/* 13096 360 */
	{.type There, {.p 360 }},	/* 13096 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13104 */
	{.type Here, {.p 13104 }},	/* 13104 360 */
	{.type There, {.p 360 }},	/* 13104 360 */
	{.type Absolute, {.p 256}},		/* dd 256 13112 */
	{.type Here, {.p 13112 }},	/* 13112 360 */
	{.type There, {.p 360 }},	/* 13112 360 */
	{.type FromDictionary, {.p M_less}, .src = "dd M_less"},		/* dd M_less 13120 */
	{.type Here, {.p 13120 }},	/* 13120 360 */
	{.type There, {.p 360 }},	/* 13120 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13128 */
	{.type Here, {.p 13128 }},	/* 13128 360 */
	{.type There, {.p 360 }},	/* 13128 360 */
	{.type FromDictionary, {.p L_C_parse_1}, .src = "dd L_C_parse_1"},		/* dd L_C_parse_1 13136 */
	{.type Here, {.p 13136 }},	/* 13136 360 */
	{.type There, {.p 360 }},	/* 13136 360 */
	{.type Here, {.p 13136 }},	/* 13136 360 */
	{.type There, {.p 360 }},	/* 13136 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( read_count read_count )"},		/* dd M_dup	; ( read_count read_count ) 13144 */
	{.type Here, {.p 13144 }},	/* 13144 360 */
	{.type There, {.p 360 }},	/* 13144 360 */
	{.type FromDictionary, {.p MV_Wordb}, .src = "dd MV_Wordb"},		/* dd MV_Wordb 13152 */
	{.type Here, {.p 13152 }},	/* 13152 360 */
	{.type There, {.p 360 }},	/* 13152 360 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore	; ( store read_count at Wordb[0] )"},		/* dd M_cstore	; ( store read_count at Wordb[0] ) 13160 */
	{.type Here, {.p 13160 }},	/* 13160 360 */
	{.type There, {.p 360 }},	/* 13160 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 13168 */
	{.type Here, {.p 13168 }},	/* 13168 360 */
	{.type There, {.p 360 }},	/* 13168 360 */
	{.type FromDictionary, {.p MV_Tib}, .src = "dd MV_Tib"},		/* dd MV_Tib 13176 */
	{.type Here, {.p 13176 }},	/* 13176 360 */
	{.type There, {.p 360 }},	/* 13176 360 */
	{.type FromDictionary, {.p MV_Wordb}, .src = "dd MV_Wordb"},		/* dd MV_Wordb 13184 */
	{.type Here, {.p 13184 }},	/* 13184 360 */
	{.type There, {.p 360 }},	/* 13184 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13192 */
	{.type Here, {.p 13192 }},	/* 13192 360 */
	{.type There, {.p 360 }},	/* 13192 360 */
	{.type Absolute, {.p 1}},		/* dd 1 13200 */
	{.type Here, {.p 13200 }},	/* 13200 360 */
	{.type There, {.p 360 }},	/* 13200 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 'Tib 'Wordb+1 ) (R read_count )"},		/* dd M_plus	; ( 'Tib 'Wordb+1 ) (R read_count ) 13208 */
	{.type Here, {.p 13208 }},	/* 13208 360 */
	{.type There, {.p 360 }},	/* 13208 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( 'Tib 'Wordb+1 read_count )"},		/* dd M_rpop	; ( 'Tib 'Wordb+1 read_count ) 13216 */
	{.type Here, {.p 13216 }},	/* 13216 360 */
	{.type There, {.p 360 }},	/* 13216 360 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; copy bytes from Tib to Wordb to make it a counted string at Wordb"},		/* dd M_cmove	; copy bytes from Tib to Wordb to make it a counted string at Wordb 13224 */
	{.type Here, {.p 13224 }},	/* 13224 360 */
	{.type There, {.p 360 }},	/* 13224 360 */
	{.type Here, {.p 13224 }},	/* 13224 360 */
	{.type There, {.p 360 }},	/* 13224 360 */
	{.type FromDictionary, {.p MV_Wordb}, .src = "dd MV_Wordb"},		/* dd MV_Wordb 13232 */
	{.type Here, {.p 13232 }},	/* 13232 360 */
	{.type There, {.p 360 }},	/* 13232 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon	; ( 'Wordb ) Wordb has the counted string"},		/* dd M_exitcolon	; ( 'Wordb ) Wordb has the counted string 13240 */
	{.type Here, {.p 13240 }},	/* 13240 360 */
	{.type There, {.p 360 }},	/* 13240 360 */
	{.type Here, {.p 13240 }},	/* 13240 360 */
	{.type There, {.p 360 }},	/* 13240 360 */
	{.type Here, {.p 13240 }},	/* 13240 360 */
	{.type There, {.p 360 }},	/* 13240 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13248 */
	{.type Here, {.p 13248 }},	/* 13248 360 */
	{.type There, {.p 360 }},	/* 13248 360 */
	{.type FromDictionary, {.p L_C_long_word}, .src = "dd L_C_long_word"},		/* dd L_C_long_word 13256 */
	{.type Here, {.p 13256 }},	/* 13256 360 */
	{.type There, {.p 360 }},	/* 13256 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13264 */
	{.type Here, {.p 13264 }},	/* 13264 360 */
	{.type There, {.p 360 }},	/* 13264 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13272 */
	{.type Here, {.p 13272 }},	/* 13272 360 */
	{.type There, {.p 360 }},	/* 13272 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 13280 */
	{.type Here, {.p 13280 }},	/* 13280 360 */
	{.type There, {.p 360 }},	/* 13280 360 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 13288 */
	{.type Here, {.p 13288 }},	/* 13288 360 */
	{.type There, {.p 360 }},	/* 13288 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13296 */
	{.type Here, {.p 13296 }},	/* 13296 360 */
	{.type There, {.p 360 }},	/* 13296 360 */
	{.type Here, {.p 13296 }},	/* 13296 360 */
	{.type There, {.p 360 }},	/* 13296 360 */
	{.type Header, {.hdr { 4, "word", /* C_word = 13312 */ colon }}}, /* CENTRY "word" word 4 ; ( -- 'Wordb ) read from #n/Infd/word into Tib and then parse to a counted string in Wordb h 13320 */
	{.type Here, {.p 13320 }},	/* 13320 360 */
	{.type There, {.p 360 }},	/* 13320 360 */
	{.type Here, {.p 13320 }},	/* 13320 360 */
	{.type There, {.p 360 }},	/* 13320 360 */
	{.type FromDictionary, {.p MC_WORDNUM}, .src = "dd MC_WORDNUM"},		/* dd MC_WORDNUM 13328 */
	{.type Here, {.p 13328 }},	/* 13328 360 */
	{.type There, {.p 360 }},	/* 13328 360 */
	{.type FromDictionary, {.p C_get}, .src = "dd C_get"},		/* dd C_get 13336 */
	{.type Here, {.p 13336 }},	/* 13336 360 */
	{.type There, {.p 360 }},	/* 13336 360 */
	{.type FromDictionary, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 13344 */
	{.type Here, {.p 13344 }},	/* 13344 360 */
	{.type There, {.p 360 }},	/* 13344 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13352 */
	{.type Here, {.p 13352 }},	/* 13352 360 */
	{.type There, {.p 360 }},	/* 13352 360 */
	{.type Here, {.p 13352 }},	/* 13352 360 */
	{.type There, {.p 360 }},	/* 13352 360 */
	{.type Header, {.hdr { 4, "line", /* C_line = 13368 */ colon }}}, /* CENTRY "line" line 4 ; ( -- count ) read from #n/Infd/line into Tib h 13376 */
	{.type Here, {.p 13376 }},	/* 13376 360 */
	{.type There, {.p 360 }},	/* 13376 360 */
	{.type Here, {.p 13376 }},	/* 13376 360 */
	{.type There, {.p 360 }},	/* 13376 360 */
	{.type FromDictionary, {.p MC_LINENUM}, .src = "dd MC_LINENUM"},		/* dd MC_LINENUM 13384 */
	{.type Here, {.p 13384 }},	/* 13384 360 */
	{.type There, {.p 360 }},	/* 13384 360 */
	{.type FromDictionary, {.p C_get}, .src = "dd C_get"},		/* dd C_get 13392 */
	{.type Here, {.p 13392 }},	/* 13392 360 */
	{.type There, {.p 360 }},	/* 13392 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13400 */
	{.type Here, {.p 13400 }},	/* 13400 360 */
	{.type There, {.p 360 }},	/* 13400 360 */
	{.type Here, {.p 13400 }},	/* 13400 360 */
	{.type There, {.p 360 }},	/* 13400 360 */
	{.type Header, {.hdr { 11, "doublequote", /* C_doublequote = 13424 */ colon }}}, /* CENTRY "doublequote" doublequote 11 ; ( -- count ) read from #n/Infd/doublequote into Tib and then parse to a counted string in Wordb h 13432 */
	{.type Here, {.p 13432 }},	/* 13432 360 */
	{.type There, {.p 360 }},	/* 13432 360 */
	{.type Here, {.p 13432 }},	/* 13432 360 */
	{.type There, {.p 360 }},	/* 13432 360 */
	{.type FromDictionary, {.p MC_DOUBLEQUOTENUM}, .src = "dd MC_DOUBLEQUOTENUM"},		/* dd MC_DOUBLEQUOTENUM 13440 */
	{.type Here, {.p 13440 }},	/* 13440 360 */
	{.type There, {.p 360 }},	/* 13440 360 */
	{.type FromDictionary, {.p C_get}, .src = "dd C_get"},		/* dd C_get 13448 */
	{.type Here, {.p 13448 }},	/* 13448 360 */
	{.type There, {.p 360 }},	/* 13448 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13456 */
	{.type Here, {.p 13456 }},	/* 13456 360 */
	{.type There, {.p 360 }},	/* 13456 360 */
	{.type Here, {.p 13456 }},	/* 13456 360 */
	{.type There, {.p 360 }},	/* 13456 360 */
	{.type Header, {.hdr { 11, "cdoublequote", /* C_counted_doublequote = 13480 */ colon }}}, /* CENTRY "cdoublequote" counted_doublequote 11 ; ( -- 'Wordb ) read from #n/Infd/doublequote into Tib and then parse to a counted string in Wordb h 13488 */
	{.type Here, {.p 13488 }},	/* 13488 360 */
	{.type There, {.p 360 }},	/* 13488 360 */
	{.type Here, {.p 13488 }},	/* 13488 360 */
	{.type There, {.p 360 }},	/* 13488 360 */
	{.type FromDictionary, {.p MC_DOUBLEQUOTENUM}, .src = "dd MC_DOUBLEQUOTENUM"},		/* dd MC_DOUBLEQUOTENUM 13496 */
	{.type Here, {.p 13496 }},	/* 13496 360 */
	{.type There, {.p 360 }},	/* 13496 360 */
	{.type FromDictionary, {.p C_get}, .src = "dd C_get"},		/* dd C_get 13504 */
	{.type Here, {.p 13504 }},	/* 13504 360 */
	{.type There, {.p 360 }},	/* 13504 360 */
	{.type FromDictionary, {.p C_parse}, .src = "dd C_parse"},		/* dd C_parse 13512 */
	{.type Here, {.p 13512 }},	/* 13512 360 */
	{.type There, {.p 360 }},	/* 13512 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13520 */
	{.type Here, {.p 13520 }},	/* 13520 360 */
	{.type There, {.p 360 }},	/* 13520 360 */
	{.type Here, {.p 13520 }},	/* 13520 360 */
	{.type There, {.p 360 }},	/* 13520 360 */
	{.type Header, {.hdr { 10, "closeparen", /* C_closeparen = 13544 */ colon }}}, /* CENTRY "closeparen" closeparen 10 ; ( -- count ) read from #n/Infd/closeparen h 13552 */
	{.type Here, {.p 13552 }},	/* 13552 360 */
	{.type There, {.p 360 }},	/* 13552 360 */
	{.type Here, {.p 13552 }},	/* 13552 360 */
	{.type There, {.p 360 }},	/* 13552 360 */
	{.type FromDictionary, {.p MC_CLOSEPARENNUM}, .src = "dd MC_CLOSEPARENNUM"},		/* dd MC_CLOSEPARENNUM 13560 */
	{.type Here, {.p 13560 }},	/* 13560 360 */
	{.type There, {.p 360 }},	/* 13560 360 */
	{.type FromDictionary, {.p C_get}, .src = "dd C_get"},		/* dd C_get 13568 */
	{.type Here, {.p 13568 }},	/* 13568 360 */
	{.type There, {.p 360 }},	/* 13568 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13576 */
	{.type Here, {.p 13576 }},	/* 13576 360 */
	{.type There, {.p 360 }},	/* 13576 360 */
	{.type Here, {.p 13576 }},	/* 13576 360 */
	{.type There, {.p 360 }},	/* 13576 360 */
	{.type Header, {.hdr { 8, "findname", /* C_findname = 13600 */ colon }}}, /* CENTRY "findname" findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names h 13608 */
	{.type Here, {.p 13608 }},	/* 13608 360 */
	{.type There, {.p 360 }},	/* 13608 360 */
	{.type Here, {.p 13608 }},	/* 13608 360 */
	{.type There, {.p 360 }},	/* 13608 360 */
	{.type FromDictionary, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 13616 */
	{.type Here, {.p 13616 }},	/* 13616 360 */
	{.type There, {.p 360 }},	/* 13616 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 13624 */
	{.type Here, {.p 13624 }},	/* 13624 360 */
	{.type There, {.p 360 }},	/* 13624 360 */
	{.type FromDictionary, {.p MV_Dtop}, .src = "dd MV_Dtop"},		/* dd MV_Dtop 13632 */
	{.type Here, {.p 13632 }},	/* 13632 360 */
	{.type There, {.p 360 }},	/* 13632 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; get latest dictionary link"},		/* dd M_fetch	; get latest dictionary link 13640 */
	{.type Here, {.p 13640 }},	/* 13640 360 */
	{.type There, {.p 360 }},	/* 13640 360 */
	{.type Here, {.p 13640 }},	/* 13640 360 */
	{.type There, {.p 360 }},	/* 13640 360 */
	{.type FromDictionary, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 13648 */
	{.type Here, {.p 13648 }},	/* 13648 360 */
	{.type There, {.p 360 }},	/* 13648 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13656 */
	{.type Here, {.p 13656 }},	/* 13656 360 */
	{.type There, {.p 360 }},	/* 13656 360 */
	{.type FromDictionary, {.p L_C_findname_1}, .src = "dd L_C_findname_1	; seached until the first dictionary entry get out"},		/* dd L_C_findname_1	; seached until the first dictionary entry get out 13664 */
	{.type Here, {.p 13664 }},	/* 13664 360 */
	{.type There, {.p 360 }},	/* 13664 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a -- a a )"},		/* dd M_dup	; ( a -- a a ) 13672 */
	{.type Here, {.p 13672 }},	/* 13672 360 */
	{.type There, {.p 360 }},	/* 13672 360 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus	; ( a a -- a a+8) lenth + initial name address"},		/* dd C_cell_plus	; ( a a -- a a+8) lenth + initial name address 13680 */
	{.type Here, {.p 13680 }},	/* 13680 360 */
	{.type There, {.p 360 }},	/* 13680 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name"},		/* dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name 13688 */
	{.type Here, {.p 13688 }},	/* 13688 360 */
	{.type There, {.p 360 }},	/* 13688 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13696 */
	{.type Here, {.p 13696 }},	/* 13696 360 */
	{.type There, {.p 360 }},	/* 13696 360 */
	{.type Absolute, {.p 64}},		/* dd 64		; check the reveal'ed flag 1=hidden, 0=reveal 13704 */
	{.type Here, {.p 13704 }},	/* 13704 360 */
	{.type There, {.p 360 }},	/* 13704 360 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand	; if hidden, goto L_C_findname_3 else L_C_findname_2"},		/* dd M_binand	; if hidden, goto L_C_findname_3 else L_C_findname_2 13712 */
	{.type Here, {.p 13712 }},	/* 13712 360 */
	{.type There, {.p 360 }},	/* 13712 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13720 */
	{.type Here, {.p 13720 }},	/* 13720 360 */
	{.type There, {.p 360 }},	/* 13720 360 */
	{.type FromDictionary, {.p L_C_findname_2}, .src = "dd L_C_findname_2"},		/* dd L_C_findname_2 13728 */
	{.type Here, {.p 13728 }},	/* 13728 360 */
	{.type There, {.p 360 }},	/* 13728 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; smudge'd dictionary entry, get the previous entry"},		/* dd M_fetch	; smudge'd dictionary entry, get the previous entry 13736 */
	{.type Here, {.p 13736 }},	/* 13736 360 */
	{.type There, {.p 360 }},	/* 13736 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13744 */
	{.type Here, {.p 13744 }},	/* 13744 360 */
	{.type There, {.p 360 }},	/* 13744 360 */
	{.type FromDictionary, {.p L_C_findname_3}, .src = "dd L_C_findname_3"},		/* dd L_C_findname_3 13752 */
	{.type Here, {.p 13752 }},	/* 13752 360 */
	{.type There, {.p 360 }},	/* 13752 360 */
	{.type Here, {.p 13752 }},	/* 13752 360 */
	{.type There, {.p 360 }},	/* 13752 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a1 -- a1 a1)"},		/* dd M_dup	; ( a1 -- a1 a1) 13760 */
	{.type Here, {.p 13760 }},	/* 13760 360 */
	{.type There, {.p 360 }},	/* 13760 360 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus	; ( a1 a1 -- a1 a1+8)"},		/* dd C_cell_plus	; ( a1 a1 -- a1 a1+8) 13768 */
	{.type Here, {.p 13768 }},	/* 13768 360 */
	{.type There, {.p 360 }},	/* 13768 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n )"},		/* dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n ) 13776 */
	{.type Here, {.p 13776 }},	/* 13776 360 */
	{.type There, {.p 360 }},	/* 13776 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13784 */
	{.type Here, {.p 13784 }},	/* 13784 360 */
	{.type There, {.p 360 }},	/* 13784 360 */
	{.type Absolute, {.p 63}},		/* dd 63 13792 */
	{.type Here, {.p 13792 }},	/* 13792 360 */
	{.type There, {.p 360 }},	/* 13792 360 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len )"},		/* dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len ) 13800 */
	{.type Here, {.p 13800 }},	/* 13800 360 */
	{.type There, {.p 360 }},	/* 13800 360 */
	{.type FromDictionary, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 13808 */
	{.type Here, {.p 13808 }},	/* 13808 360 */
	{.type There, {.p 360 }},	/* 13808 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13816 */
	{.type Here, {.p 13816 }},	/* 13816 360 */
	{.type There, {.p 360 }},	/* 13816 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 )"},		/* dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 ) 13824 */
	{.type Here, {.p 13824 }},	/* 13824 360 */
	{.type There, {.p 360 }},	/* 13824 360 */
	{.type FromDictionary, {.p C_compare}, .src = "dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name"},		/* dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name 13832 */
	{.type Here, {.p 13832 }},	/* 13832 360 */
	{.type There, {.p 360 }},	/* 13832 360 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq	; found a match?"},		/* dd C_0eq	; found a match? 13840 */
	{.type Here, {.p 13840 }},	/* 13840 360 */
	{.type There, {.p 360 }},	/* 13840 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13848 */
	{.type Here, {.p 13848 }},	/* 13848 360 */
	{.type There, {.p 360 }},	/* 13848 360 */
	{.type FromDictionary, {.p L_C_findname_4}, .src = "dd L_C_findname_4		; no match"},		/* dd L_C_findname_4		; no match 13856 */
	{.type Here, {.p 13856 }},	/* 13856 360 */
	{.type There, {.p 360 }},	/* 13856 360 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus	; match found"},		/* dd C_cell_plus	; match found 13864 */
	{.type Here, {.p 13864 }},	/* 13864 360 */
	{.type There, {.p 360 }},	/* 13864 360 */
	{.type FromDictionary, {.p C_true}, .src = "dd C_true"},		/* dd C_true 13872 */
	{.type Here, {.p 13872 }},	/* 13872 360 */
	{.type There, {.p 360 }},	/* 13872 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13880 */
	{.type Here, {.p 13880 }},	/* 13880 360 */
	{.type There, {.p 360 }},	/* 13880 360 */
	{.type Here, {.p 13880 }},	/* 13880 360 */
	{.type There, {.p 360 }},	/* 13880 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13888 */
	{.type Here, {.p 13888 }},	/* 13888 360 */
	{.type There, {.p 360 }},	/* 13888 360 */
	{.type Here, {.p 13888 }},	/* 13888 360 */
	{.type There, {.p 360 }},	/* 13888 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13896 */
	{.type Here, {.p 13896 }},	/* 13896 360 */
	{.type There, {.p 360 }},	/* 13896 360 */
	{.type FromDictionary, {.p L_C_findname}, .src = "dd L_C_findname"},		/* dd L_C_findname 13904 */
	{.type Here, {.p 13904 }},	/* 13904 360 */
	{.type There, {.p 360 }},	/* 13904 360 */
	{.type Here, {.p 13904 }},	/* 13904 360 */
	{.type There, {.p 360 }},	/* 13904 360 */
	{.type FromDictionary, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 13912 */
	{.type Here, {.p 13912 }},	/* 13912 360 */
	{.type There, {.p 360 }},	/* 13912 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13920 */
	{.type Here, {.p 13920 }},	/* 13920 360 */
	{.type There, {.p 360 }},	/* 13920 360 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false"},		/* dd C_false 13928 */
	{.type Here, {.p 13928 }},	/* 13928 360 */
	{.type There, {.p 360 }},	/* 13928 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13936 */
	{.type Here, {.p 13936 }},	/* 13936 360 */
	{.type There, {.p 360 }},	/* 13936 360 */
	{.type Here, {.p 13936 }},	/* 13936 360 */
	{.type There, {.p 360 }},	/* 13936 360 */
	{.type Header, {.hdr { 4, "find", /* C_find = 13952 */ colon }}}, /* CENTRY "find" find 4 ; ( a1 -- a2 f )? h 13960 */
	{.type Here, {.p 13960 }},	/* 13960 360 */
	{.type There, {.p 360 }},	/* 13960 360 */
	{.type Here, {.p 13960 }},	/* 13960 360 */
	{.type There, {.p 360 }},	/* 13960 360 */
	{.type FromDictionary, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 13968 */
	{.type Here, {.p 13968 }},	/* 13968 360 */
	{.type There, {.p 360 }},	/* 13968 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13976 */
	{.type Here, {.p 13976 }},	/* 13976 360 */
	{.type There, {.p 360 }},	/* 13976 360 */
	{.type FromDictionary, {.p L_C_find}, .src = "dd L_C_find"},		/* dd L_C_find 13984 */
	{.type Here, {.p 13984 }},	/* 13984 360 */
	{.type There, {.p 360 }},	/* 13984 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13992 */
	{.type Here, {.p 13992 }},	/* 13992 360 */
	{.type There, {.p 360 }},	/* 13992 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14000 */
	{.type Here, {.p 14000 }},	/* 14000 360 */
	{.type There, {.p 360 }},	/* 14000 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 14008 */
	{.type Here, {.p 14008 }},	/* 14008 360 */
	{.type There, {.p 360 }},	/* 14008 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 14016 */
	{.type Here, {.p 14016 }},	/* 14016 360 */
	{.type There, {.p 360 }},	/* 14016 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14024 */
	{.type Here, {.p 14024 }},	/* 14024 360 */
	{.type There, {.p 360 }},	/* 14024 360 */
	{.type Absolute, {.p 63}},		/* dd 63 14032 */
	{.type Here, {.p 14032 }},	/* 14032 360 */
	{.type There, {.p 360 }},	/* 14032 360 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 14040 */
	{.type Here, {.p 14040 }},	/* 14040 360 */
	{.type There, {.p 360 }},	/* 14040 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 14048 */
	{.type Here, {.p 14048 }},	/* 14048 360 */
	{.type There, {.p 360 }},	/* 14048 360 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 14056 */
	{.type Here, {.p 14056 }},	/* 14056 360 */
	{.type There, {.p 360 }},	/* 14056 360 */
	{.type FromDictionary, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 14064 */
	{.type Here, {.p 14064 }},	/* 14064 360 */
	{.type There, {.p 360 }},	/* 14064 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 14072 */
	{.type Here, {.p 14072 }},	/* 14072 360 */
	{.type There, {.p 360 }},	/* 14072 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14080 */
	{.type Here, {.p 14080 }},	/* 14080 360 */
	{.type There, {.p 360 }},	/* 14080 360 */
	{.type Absolute, {.p 128}},		/* dd 128 14088 */
	{.type Here, {.p 14088 }},	/* 14088 360 */
	{.type There, {.p 360 }},	/* 14088 360 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 14096 */
	{.type Here, {.p 14096 }},	/* 14096 360 */
	{.type There, {.p 360 }},	/* 14096 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14104 */
	{.type Here, {.p 14104 }},	/* 14104 360 */
	{.type There, {.p 360 }},	/* 14104 360 */
	{.type FromDictionary, {.p L_C_find_1}, .src = "dd L_C_find_1"},		/* dd L_C_find_1 14112 */
	{.type Here, {.p 14112 }},	/* 14112 360 */
	{.type There, {.p 360 }},	/* 14112 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14120 */
	{.type Here, {.p 14120 }},	/* 14120 360 */
	{.type There, {.p 360 }},	/* 14120 360 */
	{.type Absolute, {.p 1}},		/* dd 1 14128 */
	{.type Here, {.p 14128 }},	/* 14128 360 */
	{.type There, {.p 360 }},	/* 14128 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14136 */
	{.type Here, {.p 14136 }},	/* 14136 360 */
	{.type There, {.p 360 }},	/* 14136 360 */
	{.type FromDictionary, {.p L_C_find_2}, .src = "dd L_C_find_2"},		/* dd L_C_find_2 14144 */
	{.type Here, {.p 14144 }},	/* 14144 360 */
	{.type There, {.p 360 }},	/* 14144 360 */
	{.type Here, {.p 14144 }},	/* 14144 360 */
	{.type There, {.p 360 }},	/* 14144 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14152 */
	{.type Here, {.p 14152 }},	/* 14152 360 */
	{.type There, {.p 360 }},	/* 14152 360 */
	{.type Absolute, {.p -1}},		/* dd -1 14160 */
	{.type Here, {.p 14160 }},	/* 14160 360 */
	{.type There, {.p 360 }},	/* 14160 360 */
	{.type Here, {.p 14160 }},	/* 14160 360 */
	{.type There, {.p 360 }},	/* 14160 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14168 */
	{.type Here, {.p 14168 }},	/* 14168 360 */
	{.type There, {.p 360 }},	/* 14168 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14176 */
	{.type Here, {.p 14176 }},	/* 14176 360 */
	{.type There, {.p 360 }},	/* 14176 360 */
	{.type FromDictionary, {.p L_C_find_3}, .src = "dd L_C_find_3"},		/* dd L_C_find_3 14184 */
	{.type Here, {.p 14184 }},	/* 14184 360 */
	{.type There, {.p 360 }},	/* 14184 360 */
	{.type Here, {.p 14184 }},	/* 14184 360 */
	{.type There, {.p 360 }},	/* 14184 360 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false"},		/* dd C_false 14192 */
	{.type Here, {.p 14192 }},	/* 14192 360 */
	{.type There, {.p 360 }},	/* 14192 360 */
	{.type Here, {.p 14192 }},	/* 14192 360 */
	{.type There, {.p 360 }},	/* 14192 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14200 */
	{.type Here, {.p 14200 }},	/* 14200 360 */
	{.type There, {.p 360 }},	/* 14200 360 */
	{.type Here, {.p 14200 }},	/* 14200 360 */
	{.type There, {.p 360 }},	/* 14200 360 */
	{.type Header, {.hdr { 1, "'", /* C_single_quote = 14216 */ colon }}}, /* CENTRY "'" single_quote 1 h 14224 */
	{.type Here, {.p 14224 }},	/* 14224 360 */
	{.type There, {.p 360 }},	/* 14224 360 */
	{.type Here, {.p 14224 }},	/* 14224 360 */
	{.type There, {.p 360 }},	/* 14224 360 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 14232 */
	{.type Here, {.p 14232 }},	/* 14232 360 */
	{.type There, {.p 360 }},	/* 14232 360 */
	{.type FromDictionary, {.p C_find}, .src = "dd C_find"},		/* dd C_find 14240 */
	{.type Here, {.p 14240 }},	/* 14240 360 */
	{.type There, {.p 360 }},	/* 14240 360 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 14248 */
	{.type Here, {.p 14248 }},	/* 14248 360 */
	{.type There, {.p 360 }},	/* 14248 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14256 */
	{.type Here, {.p 14256 }},	/* 14256 360 */
	{.type There, {.p 360 }},	/* 14256 360 */
	{.type FromDictionary, {.p L_C_single_quote}, .src = "dd L_C_single_quote"},		/* dd L_C_single_quote 14264 */
	{.type Here, {.p 14264 }},	/* 14264 360 */
	{.type There, {.p 360 }},	/* 14264 360 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 14272 */
	{.type Here, {.p 14272 }},	/* 14272 360 */
	{.type There, {.p 360 }},	/* 14272 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 14280 */
	{.type Here, {.p 14280 }},	/* 14280 360 */
	{.type There, {.p 360 }},	/* 14280 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 14288 */
	{.type Here, {.p 14288 }},	/* 14288 360 */
	{.type There, {.p 360 }},	/* 14288 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14296 */
	{.type Here, {.p 14296 }},	/* 14296 360 */
	{.type There, {.p 360 }},	/* 14296 360 */
	{.type FromDictionary, {.p L170}, .src = "dd L170"},		/* dd L170 14304 */
	{.type Here, {.p 14304 }},	/* 14304 360 */
	{.type There, {.p 360 }},	/* 14304 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 14312 */
	{.type Here, {.p 14312 }},	/* 14312 360 */
	{.type There, {.p 360 }},	/* 14312 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 14320 */
	{.type Here, {.p 14320 }},	/* 14320 360 */
	{.type There, {.p 360 }},	/* 14320 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 14328 */
	{.type Here, {.p 14328 }},	/* 14328 360 */
	{.type There, {.p 360 }},	/* 14328 360 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 14336 */
	{.type Here, {.p 14336 }},	/* 14336 360 */
	{.type There, {.p 360 }},	/* 14336 360 */
	{.type Here, {.p 14336 }},	/* 14336 360 */
	{.type There, {.p 360 }},	/* 14336 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14344 */
	{.type Here, {.p 14344 }},	/* 14344 360 */
	{.type There, {.p 360 }},	/* 14344 360 */
	{.type Here, {.p 14344 }},	/* 14344 360 */
	{.type There, {.p 360 }},	/* 14344 360 */
	{.type Header, {.hdr { 6, "?stack", /* C_qstack = 14360 */ colon }}}, /* CENTRY "?stack" qstack 6 h 14368 */
	{.type Here, {.p 14368 }},	/* 14368 360 */
	{.type There, {.p 360 }},	/* 14368 360 */
	{.type Here, {.p 14368 }},	/* 14368 360 */
	{.type There, {.p 360 }},	/* 14368 360 */
	{.type FromDictionary, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 14376 */
	{.type Here, {.p 14376 }},	/* 14376 360 */
	{.type There, {.p 360 }},	/* 14376 360 */
	{.type FromDictionary, {.p MV_S0}, .src = "dd MV_S0"},		/* dd MV_S0 14384 */
	{.type Here, {.p 14384 }},	/* 14384 360 */
	{.type There, {.p 360 }},	/* 14384 360 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 14392 */
	{.type Here, {.p 14392 }},	/* 14392 360 */
	{.type There, {.p 360 }},	/* 14392 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14400 */
	{.type Here, {.p 14400 }},	/* 14400 360 */
	{.type There, {.p 360 }},	/* 14400 360 */
	{.type FromDictionary, {.p L_C_qstack}, .src = "dd L_C_qstack"},		/* dd L_C_qstack 14408 */
	{.type Here, {.p 14408 }},	/* 14408 360 */
	{.type There, {.p 360 }},	/* 14408 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14416 */
	{.type Here, {.p 14416 }},	/* 14416 360 */
	{.type There, {.p 360 }},	/* 14416 360 */
	{.type FromDictionary, {.p L173}, .src = "dd L173"},		/* dd L173 14424 */
	{.type Here, {.p 14424 }},	/* 14424 360 */
	{.type There, {.p 360 }},	/* 14424 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 14432 */
	{.type Here, {.p 14432 }},	/* 14432 360 */
	{.type There, {.p 360 }},	/* 14432 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 14440 */
	{.type Here, {.p 14440 }},	/* 14440 360 */
	{.type There, {.p 360 }},	/* 14440 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 14448 */
	{.type Here, {.p 14448 }},	/* 14448 360 */
	{.type There, {.p 360 }},	/* 14448 360 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 14456 */
	{.type Here, {.p 14456 }},	/* 14456 360 */
	{.type There, {.p 360 }},	/* 14456 360 */
	{.type Here, {.p 14456 }},	/* 14456 360 */
	{.type There, {.p 360 }},	/* 14456 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14464 */
	{.type Here, {.p 14464 }},	/* 14464 360 */
	{.type There, {.p 360 }},	/* 14464 360 */
	{.type Here, {.p 14464 }},	/* 14464 360 */
	{.type There, {.p 360 }},	/* 14464 360 */
	{.type FromDictionary, {.p MC_STDOUT}, .src = "dd MC_STDOUT	; ( str -- str 1) ; debug code to show the word found"},		/* dd MC_STDOUT	; ( str -- str 1) ; debug code to show the word found 14472 */
	{.type Here, {.p 14472 }},	/* 14472 360 */
	{.type There, {.p 360 }},	/* 14472 360 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over		; ( str 1 str )"},		/* dd M_over		; ( str 1 str ) 14480 */
	{.type Here, {.p 14480 }},	/* 14480 360 */
	{.type There, {.p 360 }},	/* 14480 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count 		; ( str 1 a n)"},		/* dd C_count 		; ( str 1 a n) 14488 */
	{.type Here, {.p 14488 }},	/* 14488 360 */
	{.type There, {.p 360 }},	/* 14488 360 */
	{.type FromDictionary, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 14496 */
	{.type Here, {.p 14496 }},	/* 14496 360 */
	{.type There, {.p 360 }},	/* 14496 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 14504 */
	{.type Here, {.p 14504 }},	/* 14504 360 */
	{.type There, {.p 360 }},	/* 14504 360 */
	{.type Here, {.p 14504 }},	/* 14504 360 */
	{.type There, {.p 360 }},	/* 14504 360 */
	{.type Header, {.hdr { 9, "interpret", /* C_interpret = 14528 */ colon }}}, /* CENTRY "interpret" interpret 9 ; there is stuff in TIB to be interpreted >In and >Limit are set h 14536 */
	{.type Here, {.p 14536 }},	/* 14536 360 */
	{.type There, {.p 360 }},	/* 14536 360 */
	{.type Here, {.p 14536 }},	/* 14536 360 */
	{.type There, {.p 360 }},	/* 14536 360 */
	{.type Here, {.p 14536 }},	/* 14536 360 */
	{.type There, {.p 360 }},	/* 14536 360 */
	{.type Here, {.p 14536 }},	/* 14536 360 */
	{.type There, {.p 360 }},	/* 14536 360 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word	; ( -- 'Wordb ) Wordb has the counted string"},		/* dd C_word	; ( -- 'Wordb ) Wordb has the counted string 14544 */
	{.type Here, {.p 14544 }},	/* 14544 360 */
	{.type There, {.p 360 }},	/* 14544 360 */
	{.type FromDictionary, {.p C_find}, .src = "dd C_find	; ( 'Wordb -- a1 f )"},		/* dd C_find	; ( 'Wordb -- a1 f ) 14552 */
	{.type Here, {.p 14552 }},	/* 14552 360 */
	{.type There, {.p 360 }},	/* 14552 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14560 */
	{.type Here, {.p 14560 }},	/* 14560 360 */
	{.type There, {.p 360 }},	/* 14560 360 */
	{.type FromDictionary, {.p L_C_interpret_2}, .src = "dd L_C_interpret_2"},		/* dd L_C_interpret_2 14568 */
	{.type Here, {.p 14568 }},	/* 14568 360 */
	{.type There, {.p 360 }},	/* 14568 360 */
	{.type Here, {.p 14568 }},	/* 14568 360 */
	{.type There, {.p 360 }},	/* 14568 360 */
	{.type FromDictionary, {.p M_execute}, .src = "dd M_execute	; found in dictionary, execute"},		/* dd M_execute	; found in dictionary, execute 14576 */
	{.type Here, {.p 14576 }},	/* 14576 360 */
	{.type There, {.p 360 }},	/* 14576 360 */
	{.type Here, {.p 14576 }},	/* 14576 360 */
	{.type There, {.p 360 }},	/* 14576 360 */
	{.type FromDictionary, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 14584 */
	{.type Here, {.p 14584 }},	/* 14584 360 */
	{.type There, {.p 360 }},	/* 14584 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14592 */
	{.type Here, {.p 14592 }},	/* 14592 360 */
	{.type There, {.p 360 }},	/* 14592 360 */
	{.type FromDictionary, {.p L_C_interpret_3}, .src = "dd L_C_interpret_3"},		/* dd L_C_interpret_3 14600 */
	{.type Here, {.p 14600 }},	/* 14600 360 */
	{.type There, {.p 360 }},	/* 14600 360 */
	{.type Here, {.p 14600 }},	/* 14600 360 */
	{.type There, {.p 360 }},	/* 14600 360 */
	{.type Here, {.p 14600 }},	/* 14600 360 */
	{.type There, {.p 360 }},	/* 14600 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 14608 */
	{.type Here, {.p 14608 }},	/* 14608 360 */
	{.type There, {.p 360 }},	/* 14608 360 */
	{.type FromDictionary, {.p C_number}, .src = "dd C_number"},		/* dd C_number 14616 */
	{.type Here, {.p 14616 }},	/* 14616 360 */
	{.type There, {.p 360 }},	/* 14616 360 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 14624 */
	{.type Here, {.p 14624 }},	/* 14624 360 */
	{.type There, {.p 360 }},	/* 14624 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14632 */
	{.type Here, {.p 14632 }},	/* 14632 360 */
	{.type There, {.p 360 }},	/* 14632 360 */
	{.type FromDictionary, {.p L_C_interpret_4}, .src = "dd L_C_interpret_4"},		/* dd L_C_interpret_4 14640 */
	{.type Here, {.p 14640 }},	/* 14640 360 */
	{.type There, {.p 360 }},	/* 14640 360 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space	; the word is neither in the dictionary nor a number"},		/* dd C_space	; the word is neither in the dictionary nor a number 14648 */
	{.type Here, {.p 14648 }},	/* 14648 360 */
	{.type There, {.p 360 }},	/* 14648 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type	; show the word"},		/* dd C_type	; show the word 14656 */
	{.type Here, {.p 14656 }},	/* 14656 360 */
	{.type There, {.p 360 }},	/* 14656 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14664 */
	{.type Here, {.p 14664 }},	/* 14664 360 */
	{.type There, {.p 360 }},	/* 14664 360 */
	{.type FromDictionary, {.p L180}, .src = "dd L180	; error I?"},		/* dd L180	; error I? 14672 */
	{.type Here, {.p 14672 }},	/* 14672 360 */
	{.type There, {.p 360 }},	/* 14672 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 14680 */
	{.type Here, {.p 14680 }},	/* 14680 360 */
	{.type There, {.p 360 }},	/* 14680 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 14688 */
	{.type Here, {.p 14688 }},	/* 14688 360 */
	{.type There, {.p 360 }},	/* 14688 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 14696 */
	{.type Here, {.p 14696 }},	/* 14696 360 */
	{.type There, {.p 360 }},	/* 14696 360 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 14704 */
	{.type Here, {.p 14704 }},	/* 14704 360 */
	{.type There, {.p 360 }},	/* 14704 360 */
	{.type Here, {.p 14704 }},	/* 14704 360 */
	{.type There, {.p 360 }},	/* 14704 360 */
	{.type Here, {.p 14704 }},	/* 14704 360 */
	{.type There, {.p 360 }},	/* 14704 360 */
	{.type Here, {.p 14704 }},	/* 14704 360 */
	{.type There, {.p 360 }},	/* 14704 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14712 */
	{.type Here, {.p 14712 }},	/* 14712 360 */
	{.type There, {.p 360 }},	/* 14712 360 */
	{.type FromDictionary, {.p L_C_interpret}, .src = "dd L_C_interpret"},		/* dd L_C_interpret 14720 */
	{.type Here, {.p 14720 }},	/* 14720 360 */
	{.type There, {.p 360 }},	/* 14720 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14728 */
	{.type Here, {.p 14728 }},	/* 14728 360 */
	{.type There, {.p 360 }},	/* 14728 360 */
	{.type Here, {.p 14728 }},	/* 14728 360 */
	{.type There, {.p 360 }},	/* 14728 360 */
	{.type Header, {.hdr { 6, "create", /* C_create = 14744 */ colon }}}, /* CENTRY "create" create 6 ; compiles dictionary header until the pfa (link, len, name, cfa) h 14752 */
	{.type Here, {.p 14752 }},	/* 14752 360 */
	{.type There, {.p 360 }},	/* 14752 360 */
	{.type Here, {.p 14752 }},	/* 14752 360 */
	{.type There, {.p 360 }},	/* 14752 360 */
	{.type FromDictionary, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 14760 */
	{.type Here, {.p 14760 }},	/* 14760 360 */
	{.type There, {.p 360 }},	/* 14760 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( -- here )"},		/* dd C_here	; ( -- here ) 14768 */
	{.type Here, {.p 14768 }},	/* 14768 360 */
	{.type There, {.p 360 }},	/* 14768 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( -- ) (R -- linkaddr )"},		/* dd M_rpush	; ( -- ) (R -- linkaddr ) 14776 */
	{.type Here, {.p 14776 }},	/* 14776 360 */
	{.type There, {.p 360 }},	/* 14776 360 */
	{.type FromDictionary, {.p MV_Dtop}, .src = "dd MV_Dtop	; ( -- Dtop ) (R -- linkaddr )"},		/* dd MV_Dtop	; ( -- Dtop ) (R -- linkaddr ) 14784 */
	{.type Here, {.p 14784 }},	/* 14784 360 */
	{.type There, {.p 360 }},	/* 14784 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr )"},		/* dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr ) 14792 */
	{.type Here, {.p 14792 }},	/* 14792 360 */
	{.type There, {.p 360 }},	/* 14792 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma	; ( dtop -- ) (R -- linkaddr )"},		/* dd C_comma	; ( dtop -- ) (R -- linkaddr ) 14800 */
	{.type Here, {.p 14800 }},	/* 14800 360 */
	{.type There, {.p 360 }},	/* 14800 360 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word	; get the word from the input stream ( -- 'counted-string ) in Wordb"},		/* dd C_word	; get the word from the input stream ( -- 'counted-string ) in Wordb 14808 */
	{.type Here, {.p 14808 }},	/* 14808 360 */
	{.type There, {.p 360 }},	/* 14808 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a -- a a ) (R -- linkaddr )"},		/* dd M_dup	; ( a -- a a ) (R -- linkaddr ) 14816 */
	{.type Here, {.p 14816 }},	/* 14816 360 */
	{.type There, {.p 360 }},	/* 14816 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a -- a len ) (R -- linkaddr )"},		/* dd M_cfetch	; ( a a -- a len ) (R -- linkaddr ) 14824 */
	{.type Here, {.p 14824 }},	/* 14824 360 */
	{.type There, {.p 360 }},	/* 14824 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( a len -- a len here ) (R -- linkaddr )"},		/* dd C_here	; ( a len -- a len here ) (R -- linkaddr ) 14832 */
	{.type Here, {.p 14832 }},	/* 14832 360 */
	{.type There, {.p 360 }},	/* 14832 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr )"},		/* dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr ) 14840 */
	{.type Here, {.p 14840 }},	/* 14840 360 */
	{.type There, {.p 360 }},	/* 14840 360 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte"},		/* dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte 14848 */
	{.type Here, {.p 14848 }},	/* 14848 360 */
	{.type There, {.p 360 }},	/* 14848 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr )"},		/* dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr ) 14856 */
	{.type Here, {.p 14856 }},	/* 14856 360 */
	{.type There, {.p 360 }},	/* 14856 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 )"},		/* dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 ) 14864 */
	{.type Here, {.p 14864 }},	/* 14864 360 */
	{.type There, {.p 360 }},	/* 14864 360 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 )"},		/* dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 ) 14872 */
	{.type Here, {.p 14872 }},	/* 14872 360 */
	{.type There, {.p 360 }},	/* 14872 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( -- len+1 ) (R -- linkaddr )"},		/* dd M_rpop	; ( -- len+1 ) (R -- linkaddr ) 14880 */
	{.type Here, {.p 14880 }},	/* 14880 360 */
	{.type There, {.p 360 }},	/* 14880 360 */
	{.type FromDictionary, {.p C_allot}, .src = "dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1"},		/* dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1 14888 */
	{.type Here, {.p 14888 }},	/* 14888 360 */
	{.type There, {.p 360 }},	/* 14888 360 */
	{.type FromDictionary, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 14896 */
	{.type Here, {.p 14896 }},	/* 14896 360 */
	{.type There, {.p 360 }},	/* 14896 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14904 */
	{.type Here, {.p 14904 }},	/* 14904 360 */
	{.type There, {.p 360 }},	/* 14904 360 */
	{.type FromDictionary, {.p M_variable}, .src = "dd M_variable"},		/* dd M_variable 14912 */
	{.type Here, {.p 14912 }},	/* 14912 360 */
	{.type There, {.p 360 }},	/* 14912 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( -- variablecfa) (R -- linkaddr )"},		/* dd M_fetch	; ( -- variablecfa) (R -- linkaddr ) 14920 */
	{.type Here, {.p 14920 }},	/* 14920 360 */
	{.type There, {.p 360 }},	/* 14920 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma	; ( -- ) put the variablecfa into the cfa"},		/* dd C_comma	; ( -- ) put the variablecfa into the cfa 14928 */
	{.type Here, {.p 14928 }},	/* 14928 360 */
	{.type There, {.p 360 }},	/* 14928 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( -- linkaddr) (R -- )"},		/* dd M_rpop	; ( -- linkaddr) (R -- ) 14936 */
	{.type Here, {.p 14936 }},	/* 14936 360 */
	{.type There, {.p 360 }},	/* 14936 360 */
	{.type FromDictionary, {.p MV_Dtop}, .src = "dd MV_Dtop"},		/* dd MV_Dtop 14944 */
	{.type Here, {.p 14944 }},	/* 14944 360 */
	{.type There, {.p 360 }},	/* 14944 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; Dtop = just created link address"},		/* dd M_store	; Dtop = just created link address 14952 */
	{.type Here, {.p 14952 }},	/* 14952 360 */
	{.type There, {.p 360 }},	/* 14952 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14960 */
	{.type Here, {.p 14960 }},	/* 14960 360 */
	{.type There, {.p 360 }},	/* 14960 360 */
	{.type Here, {.p 14960 }},	/* 14960 360 */
	{.type There, {.p 360 }},	/* 14960 360 */
	{.type Header, {.hdr { 8, "variable", /* C_variable = 14984 */ colon }}}, /* CENTRY "variable" variable 8 ; compile to put the there then on the stack h 14992 */
	{.type Here, {.p 14992 }},	/* 14992 360 */
	{.type There, {.p 360 }},	/* 14992 360 */
	{.type Here, {.p 14992 }},	/* 14992 360 */
	{.type There, {.p 360 }},	/* 14992 360 */
	{.type FromDictionary, {.p C_create}, .src = "dd C_create"},		/* dd C_create 15000 */
	{.type Here, {.p 15000 }},	/* 15000 360 */
	{.type There, {.p 360 }},	/* 15000 360 */
	{.type FromDictionary, {.p C_there}, .src = "dd C_there"},		/* dd C_there 15008 */
	{.type Here, {.p 15008 }},	/* 15008 360 */
	{.type There, {.p 360 }},	/* 15008 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma	; put the next available variable location in pfa"},		/* dd C_comma	; put the next available variable location in pfa 15016 */
	{.type Here, {.p 15016 }},	/* 15016 360 */
	{.type There, {.p 360 }},	/* 15016 360 */
	{.type Here, {.p 15016 }},	/* 15016 360 */
	{.type There, {.p 360 }},	/* 15016 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15024 */
	{.type Here, {.p 15024 }},	/* 15024 360 */
	{.type There, {.p 360 }},	/* 15024 360 */
	{.type Absolute, {.p 1}},		/* dd 1 15032 */
	{.type Here, {.p 15032 }},	/* 15032 360 */
	{.type There, {.p 360 }},	/* 15032 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 15040 */
	{.type Here, {.p 15040 }},	/* 15040 360 */
	{.type There, {.p 360 }},	/* 15040 360 */
	{.type FromDictionary, {.p C_vallot}, .src = "dd C_vallot	; there = there+8, stored at Vp"},		/* dd C_vallot	; there = there+8, stored at Vp 15048 */
	{.type Here, {.p 15048 }},	/* 15048 360 */
	{.type There, {.p 360 }},	/* 15048 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15056 */
	{.type Here, {.p 15056 }},	/* 15056 360 */
	{.type There, {.p 360 }},	/* 15056 360 */
	{.type Here, {.p 15056 }},	/* 15056 360 */
	{.type There, {.p 360 }},	/* 15056 360 */
	{.type Header, {.hdr { 8, "constant", /* C_constant = 15080 */ colon }}}, /* CENTRY "constant" constant 8 ; ( n -- ) do the same as variable but change the cfa to (constant) h 15088 */
	{.type Here, {.p 15088 }},	/* 15088 360 */
	{.type There, {.p 360 }},	/* 15088 360 */
	{.type Here, {.p 15088 }},	/* 15088 360 */
	{.type There, {.p 360 }},	/* 15088 360 */
	{.type FromDictionary, {.p C_create}, .src = "dd C_create	; create dictionary header upto the cfa"},		/* dd C_create	; create dictionary header upto the cfa 15096 */
	{.type Here, {.p 15096 }},	/* 15096 360 */
	{.type There, {.p 360 }},	/* 15096 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15104 */
	{.type Here, {.p 15104 }},	/* 15104 360 */
	{.type There, {.p 360 }},	/* 15104 360 */
	{.type FromDictionary, {.p M_constant}, .src = "dd M_constant"},		/* dd M_constant 15112 */
	{.type Here, {.p 15112 }},	/* 15112 360 */
	{.type There, {.p 360 }},	/* 15112 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( Contstantcfa -- (constant) )"},		/* dd M_fetch	; ( Contstantcfa -- (constant) ) 15120 */
	{.type Here, {.p 15120 }},	/* 15120 360 */
	{.type There, {.p 360 }},	/* 15120 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( (constant) -- (constant) here )"},		/* dd C_here	; ( (constant) -- (constant) here ) 15128 */
	{.type Here, {.p 15128 }},	/* 15128 360 */
	{.type There, {.p 360 }},	/* 15128 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15136 */
	{.type Here, {.p 15136 }},	/* 15136 360 */
	{.type There, {.p 360 }},	/* 15136 360 */
	{.type Absolute, {.p 1}},		/* dd 1 15144 */
	{.type Here, {.p 15144 }},	/* 15144 360 */
	{.type There, {.p 360 }},	/* 15144 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells	; ( (constant) here -- (constant) here 8 )"},		/* dd C_cells	; ( (constant) here -- (constant) here 8 ) 15152 */
	{.type Here, {.p 15152 }},	/* 15152 360 */
	{.type There, {.p 360 }},	/* 15152 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus	; ( (constant) here 8 -- (constant) here-8 )"},		/* dd M_minus	; ( (constant) here 8 -- (constant) here-8 ) 15160 */
	{.type Here, {.p 15160 }},	/* 15160 360 */
	{.type There, {.p 360 }},	/* 15160 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant) "},		/* dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant)  15168 */
	{.type Here, {.p 15168 }},	/* 15168 360 */
	{.type There, {.p 360 }},	/* 15168 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma	; store n into the dictionary"},		/* dd C_comma	; store n into the dictionary 15176 */
	{.type Here, {.p 15176 }},	/* 15176 360 */
	{.type There, {.p 360 }},	/* 15176 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15184 */
	{.type Here, {.p 15184 }},	/* 15184 360 */
	{.type There, {.p 360 }},	/* 15184 360 */
	{.type Here, {.p 15184 }},	/* 15184 360 */
	{.type There, {.p 360 }},	/* 15184 360 */
	{.type Header, {.hdr { 9, "immediate", /* C_immediate = 15208 */ colon }}}, /* CENTRY "immediate" immediate 9 h 15216 */
	{.type Here, {.p 15216 }},	/* 15216 360 */
	{.type There, {.p 360 }},	/* 15216 360 */
	{.type Here, {.p 15216 }},	/* 15216 360 */
	{.type There, {.p 360 }},	/* 15216 360 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 15224 */
	{.type Here, {.p 15224 }},	/* 15224 360 */
	{.type There, {.p 360 }},	/* 15224 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 15232 */
	{.type Here, {.p 15232 }},	/* 15232 360 */
	{.type There, {.p 360 }},	/* 15232 360 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus"},		/* dd C_cell_plus 15240 */
	{.type Here, {.p 15240 }},	/* 15240 360 */
	{.type There, {.p 360 }},	/* 15240 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15248 */
	{.type Here, {.p 15248 }},	/* 15248 360 */
	{.type There, {.p 360 }},	/* 15248 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 15256 */
	{.type Here, {.p 15256 }},	/* 15256 360 */
	{.type There, {.p 360 }},	/* 15256 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15264 */
	{.type Here, {.p 15264 }},	/* 15264 360 */
	{.type There, {.p 360 }},	/* 15264 360 */
	{.type Absolute, {.p 128}},		/* dd 128 15272 */
	{.type Here, {.p 15272 }},	/* 15272 360 */
	{.type There, {.p 360 }},	/* 15272 360 */
	{.type FromDictionary, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 15280 */
	{.type Here, {.p 15280 }},	/* 15280 360 */
	{.type There, {.p 360 }},	/* 15280 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 15288 */
	{.type Here, {.p 15288 }},	/* 15288 360 */
	{.type There, {.p 360 }},	/* 15288 360 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 15296 */
	{.type Here, {.p 15296 }},	/* 15296 360 */
	{.type There, {.p 360 }},	/* 15296 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15304 */
	{.type Here, {.p 15304 }},	/* 15304 360 */
	{.type There, {.p 360 }},	/* 15304 360 */
	{.type Header, {.hdr { 4, ">cfa", /* C_tocfa = 15320 */ colon }}}, /* CENTRY ">cfa" tocfa 4 h 15328 */
	{.type Here, {.p 15328 }},	/* 15328 360 */
	{.type There, {.p 360 }},	/* 15328 360 */
	{.type Here, {.p 15328 }},	/* 15328 360 */
	{.type There, {.p 360 }},	/* 15328 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 15336 */
	{.type Here, {.p 15336 }},	/* 15336 360 */
	{.type There, {.p 360 }},	/* 15336 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15344 */
	{.type Here, {.p 15344 }},	/* 15344 360 */
	{.type There, {.p 360 }},	/* 15344 360 */
	{.type Absolute, {.p 63}},		/* dd 63 15352 */
	{.type Here, {.p 15352 }},	/* 15352 360 */
	{.type There, {.p 360 }},	/* 15352 360 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 15360 */
	{.type Here, {.p 15360 }},	/* 15360 360 */
	{.type There, {.p 360 }},	/* 15360 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 15368 */
	{.type Here, {.p 15368 }},	/* 15368 360 */
	{.type There, {.p 360 }},	/* 15368 360 */
	{.type FromDictionary, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 15376 */
	{.type Here, {.p 15376 }},	/* 15376 360 */
	{.type There, {.p 360 }},	/* 15376 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15384 */
	{.type Here, {.p 15384 }},	/* 15384 360 */
	{.type There, {.p 360 }},	/* 15384 360 */
	{.type Here, {.p 15384 }},	/* 15384 360 */
	{.type There, {.p 360 }},	/* 15384 360 */
	{.type Header, {.hdr { 7, "compile", /* C_compile = 15400 */ colon }}}, /* CENTRY "compile" compile 7 h 15408 */
	{.type Here, {.p 15408 }},	/* 15408 360 */
	{.type There, {.p 360 }},	/* 15408 360 */
	{.type Here, {.p 15408 }},	/* 15408 360 */
	{.type There, {.p 360 }},	/* 15408 360 */
	{.type FromDictionary, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 15416 */
	{.type Here, {.p 15416 }},	/* 15416 360 */
	{.type There, {.p 360 }},	/* 15416 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15424 */
	{.type Here, {.p 15424 }},	/* 15424 360 */
	{.type There, {.p 360 }},	/* 15424 360 */
	{.type FromDictionary, {.p L_C_compile}, .src = "dd L_C_compile"},		/* dd L_C_compile 15432 */
	{.type Here, {.p 15432 }},	/* 15432 360 */
	{.type There, {.p 360 }},	/* 15432 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15440 */
	{.type Here, {.p 15440 }},	/* 15440 360 */
	{.type There, {.p 360 }},	/* 15440 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 15448 */
	{.type Here, {.p 15448 }},	/* 15448 360 */
	{.type There, {.p 360 }},	/* 15448 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15456 */
	{.type Here, {.p 15456 }},	/* 15456 360 */
	{.type There, {.p 360 }},	/* 15456 360 */
	{.type Absolute, {.p 128}},		/* dd 128 15464 */
	{.type Here, {.p 15464 }},	/* 15464 360 */
	{.type There, {.p 360 }},	/* 15464 360 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 15472 */
	{.type Here, {.p 15472 }},	/* 15472 360 */
	{.type There, {.p 360 }},	/* 15472 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15480 */
	{.type Here, {.p 15480 }},	/* 15480 360 */
	{.type There, {.p 360 }},	/* 15480 360 */
	{.type FromDictionary, {.p L_C_compile_1}, .src = "dd L_C_compile_1"},		/* dd L_C_compile_1 15488 */
	{.type Here, {.p 15488 }},	/* 15488 360 */
	{.type There, {.p 360 }},	/* 15488 360 */
	{.type FromDictionary, {.p C_tocfa}, .src = "dd C_tocfa	; immediate"},		/* dd C_tocfa	; immediate 15496 */
	{.type Here, {.p 15496 }},	/* 15496 360 */
	{.type There, {.p 360 }},	/* 15496 360 */
	{.type FromDictionary, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 15504 */
	{.type Here, {.p 15504 }},	/* 15504 360 */
	{.type There, {.p 360 }},	/* 15504 360 */
	{.type FromDictionary, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 15512 */
	{.type Here, {.p 15512 }},	/* 15512 360 */
	{.type There, {.p 360 }},	/* 15512 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15520 */
	{.type Here, {.p 15520 }},	/* 15520 360 */
	{.type There, {.p 360 }},	/* 15520 360 */
	{.type FromDictionary, {.p L_C_compile_2}, .src = "dd L_C_compile_2"},		/* dd L_C_compile_2 15528 */
	{.type Here, {.p 15528 }},	/* 15528 360 */
	{.type There, {.p 360 }},	/* 15528 360 */
	{.type Here, {.p 15528 }},	/* 15528 360 */
	{.type There, {.p 360 }},	/* 15528 360 */
	{.type FromDictionary, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 15536 */
	{.type Here, {.p 15536 }},	/* 15536 360 */
	{.type There, {.p 360 }},	/* 15536 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15544 */
	{.type Here, {.p 15544 }},	/* 15544 360 */
	{.type There, {.p 360 }},	/* 15544 360 */
	{.type Here, {.p 15544 }},	/* 15544 360 */
	{.type There, {.p 360 }},	/* 15544 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15552 */
	{.type Here, {.p 15552 }},	/* 15552 360 */
	{.type There, {.p 360 }},	/* 15552 360 */
	{.type FromDictionary, {.p L_C_compile_3}, .src = "dd L_C_compile_3"},		/* dd L_C_compile_3 15560 */
	{.type Here, {.p 15560 }},	/* 15560 360 */
	{.type There, {.p 360 }},	/* 15560 360 */
	{.type Here, {.p 15560 }},	/* 15560 360 */
	{.type There, {.p 360 }},	/* 15560 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 15568 */
	{.type Here, {.p 15568 }},	/* 15568 360 */
	{.type There, {.p 360 }},	/* 15568 360 */
	{.type FromDictionary, {.p C_number}, .src = "dd C_number"},		/* dd C_number 15576 */
	{.type Here, {.p 15576 }},	/* 15576 360 */
	{.type There, {.p 360 }},	/* 15576 360 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 15584 */
	{.type Here, {.p 15584 }},	/* 15584 360 */
	{.type There, {.p 360 }},	/* 15584 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15592 */
	{.type Here, {.p 15592 }},	/* 15592 360 */
	{.type There, {.p 360 }},	/* 15592 360 */
	{.type FromDictionary, {.p L_C_compile_4}, .src = "dd L_C_compile_4"},		/* dd L_C_compile_4 15600 */
	{.type Here, {.p 15600 }},	/* 15600 360 */
	{.type There, {.p 360 }},	/* 15600 360 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 15608 */
	{.type Here, {.p 15608 }},	/* 15608 360 */
	{.type There, {.p 360 }},	/* 15608 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 15616 */
	{.type Here, {.p 15616 }},	/* 15616 360 */
	{.type There, {.p 360 }},	/* 15616 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15624 */
	{.type Here, {.p 15624 }},	/* 15624 360 */
	{.type There, {.p 360 }},	/* 15624 360 */
	{.type FromDictionary, {.p L_C_compile_5}, .src = "dd L_C_compile_5"},		/* dd L_C_compile_5 15632 */
	{.type Here, {.p 15632 }},	/* 15632 360 */
	{.type There, {.p 360 }},	/* 15632 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 15640 */
	{.type Here, {.p 15640 }},	/* 15640 360 */
	{.type There, {.p 360 }},	/* 15640 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 15648 */
	{.type Here, {.p 15648 }},	/* 15648 360 */
	{.type There, {.p 360 }},	/* 15648 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 15656 */
	{.type Here, {.p 15656 }},	/* 15656 360 */
	{.type There, {.p 360 }},	/* 15656 360 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 15664 */
	{.type Here, {.p 15664 }},	/* 15664 360 */
	{.type There, {.p 360 }},	/* 15664 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15672 */
	{.type Here, {.p 15672 }},	/* 15672 360 */
	{.type There, {.p 360 }},	/* 15672 360 */
	{.type FromDictionary, {.p L_C_compile_6}, .src = "dd L_C_compile_6"},		/* dd L_C_compile_6 15680 */
	{.type Here, {.p 15680 }},	/* 15680 360 */
	{.type There, {.p 360 }},	/* 15680 360 */
	{.type Here, {.p 15680 }},	/* 15680 360 */
	{.type There, {.p 360 }},	/* 15680 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15688 */
	{.type Here, {.p 15688 }},	/* 15688 360 */
	{.type There, {.p 360 }},	/* 15688 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15696 */
	{.type Here, {.p 15696 }},	/* 15696 360 */
	{.type There, {.p 360 }},	/* 15696 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15704 */
	{.type Here, {.p 15704 }},	/* 15704 360 */
	{.type There, {.p 360 }},	/* 15704 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15712 */
	{.type Here, {.p 15712 }},	/* 15712 360 */
	{.type There, {.p 360 }},	/* 15712 360 */
	{.type Here, {.p 15712 }},	/* 15712 360 */
	{.type There, {.p 360 }},	/* 15712 360 */
	{.type Here, {.p 15712 }},	/* 15712 360 */
	{.type There, {.p 360 }},	/* 15712 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15720 */
	{.type Here, {.p 15720 }},	/* 15720 360 */
	{.type There, {.p 360 }},	/* 15720 360 */
	{.type Here, {.p 15720 }},	/* 15720 360 */
	{.type There, {.p 360 }},	/* 15720 360 */
	{.type Header, {.hdr { 1, "]", /* C_close_bracket = 15736 */ colon }}}, /* CENTRY "]" close_bracket 1 h 15744 */
	{.type Here, {.p 15744 }},	/* 15744 360 */
	{.type There, {.p 360 }},	/* 15744 360 */
	{.type Here, {.p 15744 }},	/* 15744 360 */
	{.type There, {.p 360 }},	/* 15744 360 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 15752 */
	{.type Here, {.p 15752 }},	/* 15752 360 */
	{.type There, {.p 360 }},	/* 15752 360 */
	{.type FromDictionary, {.p C_on}, .src = "dd C_on"},		/* dd C_on 15760 */
	{.type Here, {.p 15760 }},	/* 15760 360 */
	{.type There, {.p 360 }},	/* 15760 360 */
	{.type Here, {.p 15760 }},	/* 15760 360 */
	{.type There, {.p 360 }},	/* 15760 360 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 15768 */
	{.type Here, {.p 15768 }},	/* 15768 360 */
	{.type There, {.p 360 }},	/* 15768 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15776 */
	{.type Here, {.p 15776 }},	/* 15776 360 */
	{.type There, {.p 360 }},	/* 15776 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 15784 */
	{.type Here, {.p 15784 }},	/* 15784 360 */
	{.type There, {.p 360 }},	/* 15784 360 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 15792 */
	{.type Here, {.p 15792 }},	/* 15792 360 */
	{.type There, {.p 360 }},	/* 15792 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15800 */
	{.type Here, {.p 15800 }},	/* 15800 360 */
	{.type There, {.p 360 }},	/* 15800 360 */
	{.type FromDictionary, {.p L_C_close_bracket_1}, .src = "dd L_C_close_bracket_1"},		/* dd L_C_close_bracket_1 15808 */
	{.type Here, {.p 15808 }},	/* 15808 360 */
	{.type There, {.p 360 }},	/* 15808 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 15816 */
	{.type Here, {.p 15816 }},	/* 15816 360 */
	{.type There, {.p 360 }},	/* 15816 360 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 15824 */
	{.type Here, {.p 15824 }},	/* 15824 360 */
	{.type There, {.p 360 }},	/* 15824 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15832 */
	{.type Here, {.p 15832 }},	/* 15832 360 */
	{.type There, {.p 360 }},	/* 15832 360 */
	{.type FromDictionary, {.p L_C_close_bracket_2}, .src = "dd L_C_close_bracket_2"},		/* dd L_C_close_bracket_2 15840 */
	{.type Here, {.p 15840 }},	/* 15840 360 */
	{.type There, {.p 360 }},	/* 15840 360 */
	{.type Here, {.p 15840 }},	/* 15840 360 */
	{.type There, {.p 360 }},	/* 15840 360 */
	{.type FromDictionary, {.p C_compile}, .src = "dd C_compile"},		/* dd C_compile 15848 */
	{.type Here, {.p 15848 }},	/* 15848 360 */
	{.type There, {.p 360 }},	/* 15848 360 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 15856 */
	{.type Here, {.p 15856 }},	/* 15856 360 */
	{.type There, {.p 360 }},	/* 15856 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 15864 */
	{.type Here, {.p 15864 }},	/* 15864 360 */
	{.type There, {.p 360 }},	/* 15864 360 */
	{.type Here, {.p 15864 }},	/* 15864 360 */
	{.type There, {.p 360 }},	/* 15864 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15872 */
	{.type Here, {.p 15872 }},	/* 15872 360 */
	{.type There, {.p 360 }},	/* 15872 360 */
	{.type FromDictionary, {.p L_C_close_bracket_3}, .src = "dd L_C_close_bracket_3"},		/* dd L_C_close_bracket_3 15880 */
	{.type Here, {.p 15880 }},	/* 15880 360 */
	{.type There, {.p 360 }},	/* 15880 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15888 */
	{.type Here, {.p 15888 }},	/* 15888 360 */
	{.type There, {.p 360 }},	/* 15888 360 */
	{.type FromDictionary, {.p L_C_close_bracket}, .src = "dd L_C_close_bracket"},		/* dd L_C_close_bracket 15896 */
	{.type Here, {.p 15896 }},	/* 15896 360 */
	{.type There, {.p 360 }},	/* 15896 360 */
	{.type Here, {.p 15896 }},	/* 15896 360 */
	{.type There, {.p 360 }},	/* 15896 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15904 */
	{.type Here, {.p 15904 }},	/* 15904 360 */
	{.type There, {.p 360 }},	/* 15904 360 */
	{.type Here, {.p 15904 }},	/* 15904 360 */
	{.type There, {.p 360 }},	/* 15904 360 */
	{.type IHeader, {.hdr { 1, "[", /* CI_open_bracket = 15920 */ colon }}}, /* CIENTRY "[" open_bracket 1 h 15928 */
	{.type Here, {.p 15928 }},	/* 15928 360 */
	{.type There, {.p 360 }},	/* 15928 360 */
	{.type Here, {.p 15928 }},	/* 15928 360 */
	{.type There, {.p 360 }},	/* 15928 360 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 15936 */
	{.type Here, {.p 15936 }},	/* 15936 360 */
	{.type There, {.p 360 }},	/* 15936 360 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off"},		/* dd C_off 15944 */
	{.type Here, {.p 15944 }},	/* 15944 360 */
	{.type There, {.p 360 }},	/* 15944 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15952 */
	{.type Here, {.p 15952 }},	/* 15952 360 */
	{.type There, {.p 360 }},	/* 15952 360 */
	{.type Header, {.hdr { 6, "smudge", /* C_smudge = 15968 */ colon }}}, /* CENTRY "smudge" smudge 6 h 15976 */
	{.type Here, {.p 15976 }},	/* 15976 360 */
	{.type There, {.p 360 }},	/* 15976 360 */
	{.type Here, {.p 15976 }},	/* 15976 360 */
	{.type There, {.p 360 }},	/* 15976 360 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 15984 */
	{.type Here, {.p 15984 }},	/* 15984 360 */
	{.type There, {.p 360 }},	/* 15984 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 15992 */
	{.type Here, {.p 15992 }},	/* 15992 360 */
	{.type There, {.p 360 }},	/* 15992 360 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus"},		/* dd C_cell_plus 16000 */
	{.type Here, {.p 16000 }},	/* 16000 360 */
	{.type There, {.p 360 }},	/* 16000 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 16008 */
	{.type Here, {.p 16008 }},	/* 16008 360 */
	{.type There, {.p 360 }},	/* 16008 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 16016 */
	{.type Here, {.p 16016 }},	/* 16016 360 */
	{.type There, {.p 360 }},	/* 16016 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16024 */
	{.type Here, {.p 16024 }},	/* 16024 360 */
	{.type There, {.p 360 }},	/* 16024 360 */
	{.type Absolute, {.p 64}},		/* dd 64 16032 */
	{.type Here, {.p 16032 }},	/* 16032 360 */
	{.type There, {.p 360 }},	/* 16032 360 */
	{.type FromDictionary, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 16040 */
	{.type Here, {.p 16040 }},	/* 16040 360 */
	{.type There, {.p 360 }},	/* 16040 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16048 */
	{.type Here, {.p 16048 }},	/* 16048 360 */
	{.type There, {.p 360 }},	/* 16048 360 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 16056 */
	{.type Here, {.p 16056 }},	/* 16056 360 */
	{.type There, {.p 360 }},	/* 16056 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16064 */
	{.type Here, {.p 16064 }},	/* 16064 360 */
	{.type There, {.p 360 }},	/* 16064 360 */
	{.type Header, {.hdr { 6, "reveal", /* C_reveal = 16080 */ colon }}}, /* CENTRY "reveal" reveal 6 h 16088 */
	{.type Here, {.p 16088 }},	/* 16088 360 */
	{.type There, {.p 360 }},	/* 16088 360 */
	{.type Here, {.p 16088 }},	/* 16088 360 */
	{.type There, {.p 360 }},	/* 16088 360 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 16096 */
	{.type Here, {.p 16096 }},	/* 16096 360 */
	{.type There, {.p 360 }},	/* 16096 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 16104 */
	{.type Here, {.p 16104 }},	/* 16104 360 */
	{.type There, {.p 360 }},	/* 16104 360 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus"},		/* dd C_cell_plus 16112 */
	{.type Here, {.p 16112 }},	/* 16112 360 */
	{.type There, {.p 360 }},	/* 16112 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 16120 */
	{.type Here, {.p 16120 }},	/* 16120 360 */
	{.type There, {.p 360 }},	/* 16120 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 16128 */
	{.type Here, {.p 16128 }},	/* 16128 360 */
	{.type There, {.p 360 }},	/* 16128 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16136 */
	{.type Here, {.p 16136 }},	/* 16136 360 */
	{.type There, {.p 360 }},	/* 16136 360 */
	{.type Absolute, {.p 64}},		/* dd 64 16144 */
	{.type Here, {.p 16144 }},	/* 16144 360 */
	{.type There, {.p 360 }},	/* 16144 360 */
	{.type FromDictionary, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 16152 */
	{.type Here, {.p 16152 }},	/* 16152 360 */
	{.type There, {.p 360 }},	/* 16152 360 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 16160 */
	{.type Here, {.p 16160 }},	/* 16160 360 */
	{.type There, {.p 360 }},	/* 16160 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16168 */
	{.type Here, {.p 16168 }},	/* 16168 360 */
	{.type There, {.p 360 }},	/* 16168 360 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 16176 */
	{.type Here, {.p 16176 }},	/* 16176 360 */
	{.type There, {.p 360 }},	/* 16176 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16184 */
	{.type Here, {.p 16184 }},	/* 16184 360 */
	{.type There, {.p 360 }},	/* 16184 360 */
	{.type Here, {.p 16184 }},	/* 16184 360 */
	{.type There, {.p 360 }},	/* 16184 360 */
	{.type Header, {.hdr { 1, ":", /* C_colon = 16200 */ colon }}}, /* CENTRY ":" colon 1 h 16208 */
	{.type Here, {.p 16208 }},	/* 16208 360 */
	{.type There, {.p 360 }},	/* 16208 360 */
	{.type Here, {.p 16208 }},	/* 16208 360 */
	{.type There, {.p 360 }},	/* 16208 360 */
	{.type FromDictionary, {.p C_create}, .src = "dd C_create	; create a dictionary header with (variable) at cfa"},		/* dd C_create	; create a dictionary header with (variable) at cfa 16216 */
	{.type Here, {.p 16216 }},	/* 16216 360 */
	{.type There, {.p 360 }},	/* 16216 360 */
	{.type FromDictionary, {.p C_smudge}, .src = "dd C_smudge"},		/* dd C_smudge 16224 */
	{.type Here, {.p 16224 }},	/* 16224 360 */
	{.type There, {.p 360 }},	/* 16224 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16232 */
	{.type Here, {.p 16232 }},	/* 16232 360 */
	{.type There, {.p 360 }},	/* 16232 360 */
	{.type FromDictionary, {.p M_colon}, .src = "dd M_colon"},		/* dd M_colon 16240 */
	{.type Here, {.p 16240 }},	/* 16240 360 */
	{.type There, {.p 360 }},	/* 16240 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon"},		/* dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon 16248 */
	{.type Here, {.p 16248 }},	/* 16248 360 */
	{.type There, {.p 360 }},	/* 16248 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( (colon) -- (colon) here )"},		/* dd C_here	; ( (colon) -- (colon) here ) 16256 */
	{.type Here, {.p 16256 }},	/* 16256 360 */
	{.type There, {.p 360 }},	/* 16256 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16264 */
	{.type Here, {.p 16264 }},	/* 16264 360 */
	{.type There, {.p 360 }},	/* 16264 360 */
	{.type Absolute, {.p 1}},		/* dd 1 16272 */
	{.type Here, {.p 16272 }},	/* 16272 360 */
	{.type There, {.p 360 }},	/* 16272 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 16280 */
	{.type Here, {.p 16280 }},	/* 16280 360 */
	{.type There, {.p 360 }},	/* 16280 360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus	; ( (colon) here -- (colon) here-8 )"},		/* dd M_minus	; ( (colon) here -- (colon) here-8 ) 16288 */
	{.type Here, {.p 16288 }},	/* 16288 360 */
	{.type There, {.p 360 }},	/* 16288 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon"},		/* dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon 16296 */
	{.type Here, {.p 16296 }},	/* 16296 360 */
	{.type There, {.p 360 }},	/* 16296 360 */
	{.type FromDictionary, {.p C_close_bracket}, .src = "dd C_close_bracket"},		/* dd C_close_bracket 16304 */
	{.type Here, {.p 16304 }},	/* 16304 360 */
	{.type There, {.p 360 }},	/* 16304 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16312 */
	{.type Here, {.p 16312 }},	/* 16312 360 */
	{.type There, {.p 360 }},	/* 16312 360 */
	{.type Here, {.p 16312 }},	/* 16312 360 */
	{.type There, {.p 360 }},	/* 16312 360 */
	{.type IHeader, {.hdr { 1, ";", /* CI_semicolon = 16328 */ colon }}}, /* CIENTRY ";" semicolon 1 h 16336 */
	{.type Here, {.p 16336 }},	/* 16336 360 */
	{.type There, {.p 360 }},	/* 16336 360 */
	{.type Here, {.p 16336 }},	/* 16336 360 */
	{.type There, {.p 360 }},	/* 16336 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16344 */
	{.type Here, {.p 16344 }},	/* 16344 360 */
	{.type There, {.p 360 }},	/* 16344 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16352 */
	{.type Here, {.p 16352 }},	/* 16352 360 */
	{.type There, {.p 360 }},	/* 16352 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16360 */
	{.type Here, {.p 16360 }},	/* 16360 360 */
	{.type There, {.p 360 }},	/* 16360 360 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 16368 */
	{.type Here, {.p 16368 }},	/* 16368 360 */
	{.type There, {.p 360 }},	/* 16368 360 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off"},		/* dd C_off 16376 */
	{.type Here, {.p 16376 }},	/* 16376 360 */
	{.type There, {.p 360 }},	/* 16376 360 */
	{.type FromDictionary, {.p C_reveal}, .src = "dd C_reveal"},		/* dd C_reveal 16384 */
	{.type Here, {.p 16384 }},	/* 16384 360 */
	{.type There, {.p 360 }},	/* 16384 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16392 */
	{.type Here, {.p 16392 }},	/* 16392 360 */
	{.type There, {.p 360 }},	/* 16392 360 */
	{.type Here, {.p 16392 }},	/* 16392 360 */
	{.type There, {.p 360 }},	/* 16392 360 */
	{.type IHeader, {.hdr { 7, "recurse", /* CI_recurse = 16408 */ colon }}}, /* CIENTRY "recurse" recurse 7 h 16416 */
	{.type Here, {.p 16416 }},	/* 16416 360 */
	{.type There, {.p 360 }},	/* 16416 360 */
	{.type Here, {.p 16416 }},	/* 16416 360 */
	{.type There, {.p 360 }},	/* 16416 360 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 16424 */
	{.type Here, {.p 16424 }},	/* 16424 360 */
	{.type There, {.p 360 }},	/* 16424 360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 16432 */
	{.type Here, {.p 16432 }},	/* 16432 360 */
	{.type There, {.p 360 }},	/* 16432 360 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus"},		/* dd C_cell_plus 16440 */
	{.type Here, {.p 16440 }},	/* 16440 360 */
	{.type There, {.p 360 }},	/* 16440 360 */
	{.type FromDictionary, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 16448 */
	{.type Here, {.p 16448 }},	/* 16448 360 */
	{.type There, {.p 360 }},	/* 16448 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16456 */
	{.type Here, {.p 16456 }},	/* 16456 360 */
	{.type There, {.p 360 }},	/* 16456 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16464 */
	{.type Here, {.p 16464 }},	/* 16464 360 */
	{.type There, {.p 360 }},	/* 16464 360 */
	{.type Here, {.p 16464 }},	/* 16464 360 */
	{.type There, {.p 360 }},	/* 16464 360 */
	{.type Header, {.hdr { 4, "char", /* C_char = 16480 */ colon }}}, /* CENTRY "char" char 4 ; ( -- c ) fetch the first character of the next word from input h 16488 */
	{.type Here, {.p 16488 }},	/* 16488 360 */
	{.type There, {.p 360 }},	/* 16488 360 */
	{.type Here, {.p 16488 }},	/* 16488 360 */
	{.type There, {.p 360 }},	/* 16488 360 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word	; ( -- a ) puts the address of the counted string from the input on the stack"},		/* dd C_word	; ( -- a ) puts the address of the counted string from the input on the stack 16496 */
	{.type Here, {.p 16496 }},	/* 16496 360 */
	{.type There, {.p 360 }},	/* 16496 360 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus	; skip the count"},		/* dd C_1plus	; skip the count 16504 */
	{.type Here, {.p 16504 }},	/* 16504 360 */
	{.type There, {.p 360 }},	/* 16504 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; fetch the first character"},		/* dd M_cfetch	; fetch the first character 16512 */
	{.type Here, {.p 16512 }},	/* 16512 360 */
	{.type There, {.p 360 }},	/* 16512 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16520 */
	{.type Here, {.p 16520 }},	/* 16520 360 */
	{.type There, {.p 360 }},	/* 16520 360 */
	{.type Here, {.p 16520 }},	/* 16520 360 */
	{.type There, {.p 360 }},	/* 16520 360 */
	{.type Header, {.hdr { 7, "literal", /* C_literal = 16536 */ colon }}}, /* CENTRY "literal" literal 7 ; ( n -- ) adds (literal) n to the dictionary h 16544 */
	{.type Here, {.p 16544 }},	/* 16544 360 */
	{.type There, {.p 360 }},	/* 16544 360 */
	{.type Here, {.p 16544 }},	/* 16544 360 */
	{.type There, {.p 360 }},	/* 16544 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16552 */
	{.type Here, {.p 16552 }},	/* 16552 360 */
	{.type There, {.p 360 }},	/* 16552 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16560 */
	{.type Here, {.p 16560 }},	/* 16560 360 */
	{.type There, {.p 360 }},	/* 16560 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16568 */
	{.type Here, {.p 16568 }},	/* 16568 360 */
	{.type There, {.p 360 }},	/* 16568 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16576 */
	{.type Here, {.p 16576 }},	/* 16576 360 */
	{.type There, {.p 360 }},	/* 16576 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16584 */
	{.type Here, {.p 16584 }},	/* 16584 360 */
	{.type There, {.p 360 }},	/* 16584 360 */
	{.type Here, {.p 16584 }},	/* 16584 360 */
	{.type There, {.p 360 }},	/* 16584 360 */
	{.type Header, {.hdr { 8, "sliteral", /* C_sliteral = 16608 */ colon }}}, /* CENTRY "sliteral" sliteral 8 ; ( -- ) adds (sliteral) a n to the dictionary h 16616 */
	{.type Here, {.p 16616 }},	/* 16616 360 */
	{.type There, {.p 360 }},	/* 16616 360 */
	{.type Here, {.p 16616 }},	/* 16616 360 */
	{.type There, {.p 360 }},	/* 16616 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16624 */
	{.type Here, {.p 16624 }},	/* 16624 360 */
	{.type There, {.p 360 }},	/* 16624 360 */
	{.type FromDictionary, {.p M_sliteral}, .src = "dd M_sliteral"},		/* dd M_sliteral 16632 */
	{.type Here, {.p 16632 }},	/* 16632 360 */
	{.type There, {.p 360 }},	/* 16632 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma	; adds (sliteral) to the dictionary"},		/* dd C_comma	; adds (sliteral) to the dictionary 16640 */
	{.type Here, {.p 16640 }},	/* 16640 360 */
	{.type There, {.p 360 }},	/* 16640 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( here )"},		/* dd C_here	; ( here ) 16648 */
	{.type Here, {.p 16648 }},	/* 16648 360 */
	{.type There, {.p 360 }},	/* 16648 360 */
	{.type Here, {.p 16648 }},	/* 16648 360 */
	{.type There, {.p 360 }},	/* 16648 360 */
	{.type FromDictionary, {.p C_counted_doublequote}, .src = "dd C_counted_doublequote	; ( here 'Wordb ) Wordb has the counted string"},		/* dd C_counted_doublequote	; ( here 'Wordb ) Wordb has the counted string 16656 */
	{.type Here, {.p 16656 }},	/* 16656 360 */
	{.type There, {.p 360 }},	/* 16656 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( here 'Wordb 'Wordb )"},		/* dd M_dup	; ( here 'Wordb 'Wordb ) 16664 */
	{.type Here, {.p 16664 }},	/* 16664 360 */
	{.type There, {.p 360 }},	/* 16664 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( here 'Wordb count )"},		/* dd M_cfetch	; ( here 'Wordb count ) 16672 */
	{.type Here, {.p 16672 }},	/* 16672 360 */
	{.type There, {.p 360 }},	/* 16672 360 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus	; ( here 'Wordb count+1 )"},		/* dd C_1plus	; ( here 'Wordb count+1 ) 16680 */
	{.type Here, {.p 16680 }},	/* 16680 360 */
	{.type There, {.p 360 }},	/* 16680 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( here 'Wordb ) (R count+1 )"},		/* dd M_rpush	; ( here 'Wordb ) (R count+1 ) 16688 */
	{.type Here, {.p 16688 }},	/* 16688 360 */
	{.type There, {.p 360 }},	/* 16688 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( 'Wordb here ) (R count+1 )"},		/* dd M_xswap	; ( 'Wordb here ) (R count+1 ) 16696 */
	{.type Here, {.p 16696 }},	/* 16696 360 */
	{.type There, {.p 360 }},	/* 16696 360 */
	{.type FromDictionary, {.p M_rfetch}, .src = "dd M_rfetch	; ( 'Wordb here count+1 ) (R count+1 )"},		/* dd M_rfetch	; ( 'Wordb here count+1 ) (R count+1 ) 16704 */
	{.type Here, {.p 16704 }},	/* 16704 360 */
	{.type There, {.p 360 }},	/* 16704 360 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; ( ) (R count+1 )"},		/* dd M_cmove	; ( ) (R count+1 ) 16712 */
	{.type Here, {.p 16712 }},	/* 16712 360 */
	{.type There, {.p 360 }},	/* 16712 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 16720 */
	{.type Here, {.p 16720 }},	/* 16720 360 */
	{.type There, {.p 360 }},	/* 16720 360 */
	{.type FromDictionary, {.p C_allot}, .src = "dd C_allot	; here = here+count+1"},		/* dd C_allot	; here = here+count+1 16728 */
	{.type Here, {.p 16728 }},	/* 16728 360 */
	{.type There, {.p 360 }},	/* 16728 360 */
	{.type FromDictionary, {.p C_align}, .src = "dd C_align	; align here"},		/* dd C_align	; align here 16736 */
	{.type Here, {.p 16736 }},	/* 16736 360 */
	{.type There, {.p 360 }},	/* 16736 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16744 */
	{.type Here, {.p 16744 }},	/* 16744 360 */
	{.type There, {.p 360 }},	/* 16744 360 */
	{.type Here, {.p 16744 }},	/* 16744 360 */
	{.type There, {.p 360 }},	/* 16744 360 */
	{.type Header, {.hdr { 6, "string", /* C_string = 16760 */ colon }}}, /* CENTRY "string" string 6 ; ( -- ) store the following word as a counted string onto the dictionary h 16768 */
	{.type Here, {.p 16768 }},	/* 16768 360 */
	{.type There, {.p 360 }},	/* 16768 360 */
	{.type Here, {.p 16768 }},	/* 16768 360 */
	{.type There, {.p 360 }},	/* 16768 360 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 16776 */
	{.type Here, {.p 16776 }},	/* 16776 360 */
	{.type There, {.p 360 }},	/* 16776 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 16784 */
	{.type Here, {.p 16784 }},	/* 16784 360 */
	{.type There, {.p 360 }},	/* 16784 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 16792 */
	{.type Here, {.p 16792 }},	/* 16792 360 */
	{.type There, {.p 360 }},	/* 16792 360 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 16800 */
	{.type Here, {.p 16800 }},	/* 16800 360 */
	{.type There, {.p 360 }},	/* 16800 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 16808 */
	{.type Here, {.p 16808 }},	/* 16808 360 */
	{.type There, {.p 360 }},	/* 16808 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 16816 */
	{.type Here, {.p 16816 }},	/* 16816 360 */
	{.type There, {.p 360 }},	/* 16816 360 */
	{.type FromDictionary, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 16824 */
	{.type Here, {.p 16824 }},	/* 16824 360 */
	{.type There, {.p 360 }},	/* 16824 360 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 16832 */
	{.type Here, {.p 16832 }},	/* 16832 360 */
	{.type There, {.p 360 }},	/* 16832 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 16840 */
	{.type Here, {.p 16840 }},	/* 16840 360 */
	{.type There, {.p 360 }},	/* 16840 360 */
	{.type FromDictionary, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 16848 */
	{.type Here, {.p 16848 }},	/* 16848 360 */
	{.type There, {.p 360 }},	/* 16848 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16856 */
	{.type Here, {.p 16856 }},	/* 16856 360 */
	{.type There, {.p 360 }},	/* 16856 360 */
	{.type Here, {.p 16856 }},	/* 16856 360 */
	{.type There, {.p 360 }},	/* 16856 360 */
	{.type IHeader, {.hdr { 6, "[char]", /* CI_char_brackets = 16872 */ colon }}}, /* CIENTRY "[char]" char_brackets 6 ; take the next character from the input stream during compilation h 16880 */
	{.type Here, {.p 16880 }},	/* 16880 360 */
	{.type There, {.p 360 }},	/* 16880 360 */
	{.type Here, {.p 16880 }},	/* 16880 360 */
	{.type There, {.p 360 }},	/* 16880 360 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word	; assuming that the character is a 1-byte word"},		/* dd C_word	; assuming that the character is a 1-byte word 16888 */
	{.type Here, {.p 16888 }},	/* 16888 360 */
	{.type There, {.p 360 }},	/* 16888 360 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 16896 */
	{.type Here, {.p 16896 }},	/* 16896 360 */
	{.type There, {.p 360 }},	/* 16896 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 16904 */
	{.type Here, {.p 16904 }},	/* 16904 360 */
	{.type There, {.p 360 }},	/* 16904 360 */
	{.type FromDictionary, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 16912 */
	{.type Here, {.p 16912 }},	/* 16912 360 */
	{.type There, {.p 360 }},	/* 16912 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16920 */
	{.type Here, {.p 16920 }},	/* 16920 360 */
	{.type There, {.p 360 }},	/* 16920 360 */
	{.type Here, {.p 16920 }},	/* 16920 360 */
	{.type There, {.p 360 }},	/* 16920 360 */
	{.type IHeader, {.hdr { 3, "[']", /* CI_quote_brackets = 16936 */ colon }}}, /* CIENTRY "[']" quote_brackets 3 ; take the address of next token from the input stream during compilation h 16944 */
	{.type Here, {.p 16944 }},	/* 16944 360 */
	{.type There, {.p 360 }},	/* 16944 360 */
	{.type Here, {.p 16944 }},	/* 16944 360 */
	{.type There, {.p 360 }},	/* 16944 360 */
	{.type FromDictionary, {.p C_single_quote}, .src = "dd C_single_quote"},		/* dd C_single_quote 16952 */
	{.type Here, {.p 16952 }},	/* 16952 360 */
	{.type There, {.p 360 }},	/* 16952 360 */
	{.type FromDictionary, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 16960 */
	{.type Here, {.p 16960 }},	/* 16960 360 */
	{.type There, {.p 360 }},	/* 16960 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16968 */
	{.type Here, {.p 16968 }},	/* 16968 360 */
	{.type There, {.p 360 }},	/* 16968 360 */
	{.type Here, {.p 16968 }},	/* 16968 360 */
	{.type There, {.p 360 }},	/* 16968 360 */
	{.type IHeader, {.hdr { 1, "(", /* CI_openparen = 16984 */ colon }}}, /* CIENTRY "(" openparen 1 ; ignore until ) from the input stream during compilation h 16992 */
	{.type Here, {.p 16992 }},	/* 16992 360 */
	{.type There, {.p 360 }},	/* 16992 360 */
	{.type Here, {.p 16992 }},	/* 16992 360 */
	{.type There, {.p 360 }},	/* 16992 360 */
	{.type FromDictionary, {.p C_closeparen}, .src = "dd C_closeparen"},		/* dd C_closeparen 17000 */
	{.type Here, {.p 17000 }},	/* 17000 360 */
	{.type There, {.p 360 }},	/* 17000 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 17008 */
	{.type Here, {.p 17008 }},	/* 17008 360 */
	{.type There, {.p 360 }},	/* 17008 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17016 */
	{.type Here, {.p 17016 }},	/* 17016 360 */
	{.type There, {.p 360 }},	/* 17016 360 */
	{.type Here, {.p 17016 }},	/* 17016 360 */
	{.type There, {.p 360 }},	/* 17016 360 */
	{.type IHeader, {.hdr { 1, "\\", /* CI_backslash = 17032 */ colon }}}, /* CIENTRY "\\" backslash 1 ; if the line is longer than 4096, C_get throws an error h 17040 */
	{.type Here, {.p 17040 }},	/* 17040 360 */
	{.type There, {.p 360 }},	/* 17040 360 */
	{.type Here, {.p 17040 }},	/* 17040 360 */
	{.type There, {.p 360 }},	/* 17040 360 */
	{.type FromDictionary, {.p C_line}, .src = "dd C_line"},		/* dd C_line 17048 */
	{.type Here, {.p 17048 }},	/* 17048 360 */
	{.type There, {.p 360 }},	/* 17048 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17056 */
	{.type Here, {.p 17056 }},	/* 17056 360 */
	{.type There, {.p 360 }},	/* 17056 360 */
	{.type Here, {.p 17056 }},	/* 17056 360 */
	{.type There, {.p 360 }},	/* 17056 360 */
	{.type Header, {.hdr { 8, "(?abort)", /* C_qabort_parens = 17080 */ colon }}}, /* CENTRY "(?abort)" qabort_parens 8 h 17088 */
	{.type Here, {.p 17088 }},	/* 17088 360 */
	{.type There, {.p 360 }},	/* 17088 360 */
	{.type Here, {.p 17088 }},	/* 17088 360 */
	{.type There, {.p 360 }},	/* 17088 360 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 17096 */
	{.type Here, {.p 17096 }},	/* 17096 360 */
	{.type There, {.p 360 }},	/* 17096 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 17104 */
	{.type Here, {.p 17104 }},	/* 17104 360 */
	{.type There, {.p 360 }},	/* 17104 360 */
	{.type FromDictionary, {.p L_C_qabort_parens}, .src = "dd L_C_qabort_parens"},		/* dd L_C_qabort_parens 17112 */
	{.type Here, {.p 17112 }},	/* 17112 360 */
	{.type There, {.p 360 }},	/* 17112 360 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 17120 */
	{.type Here, {.p 17120 }},	/* 17120 360 */
	{.type There, {.p 360 }},	/* 17120 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 17128 */
	{.type Here, {.p 17128 }},	/* 17128 360 */
	{.type There, {.p 360 }},	/* 17128 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 17136 */
	{.type Here, {.p 17136 }},	/* 17136 360 */
	{.type There, {.p 360 }},	/* 17136 360 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 17144 */
	{.type Here, {.p 17144 }},	/* 17144 360 */
	{.type There, {.p 360 }},	/* 17144 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 17152 */
	{.type Here, {.p 17152 }},	/* 17152 360 */
	{.type There, {.p 360 }},	/* 17152 360 */
	{.type FromDictionary, {.p L_C_qabort_parens_1}, .src = "dd L_C_qabort_parens_1"},		/* dd L_C_qabort_parens_1 17160 */
	{.type Here, {.p 17160 }},	/* 17160 360 */
	{.type There, {.p 360 }},	/* 17160 360 */
	{.type Here, {.p 17160 }},	/* 17160 360 */
	{.type There, {.p 360 }},	/* 17160 360 */
	{.type FromDictionary, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 17168 */
	{.type Here, {.p 17168 }},	/* 17168 360 */
	{.type There, {.p 360 }},	/* 17168 360 */
	{.type Here, {.p 17168 }},	/* 17168 360 */
	{.type There, {.p 360 }},	/* 17168 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17176 */
	{.type Here, {.p 17176 }},	/* 17176 360 */
	{.type There, {.p 360 }},	/* 17176 360 */
	{.type Here, {.p 17176 }},	/* 17176 360 */
	{.type There, {.p 360 }},	/* 17176 360 */
	{.type IHeader, {.hdr { 6, "abort\"", /* CI_abort_double_quote = 17192 */ colon }}}, /* CIENTRY "abort\"" abort_double_quote 6 h 17200 */
	{.type Here, {.p 17200 }},	/* 17200 360 */
	{.type There, {.p 360 }},	/* 17200 360 */
	{.type Here, {.p 17200 }},	/* 17200 360 */
	{.type There, {.p 360 }},	/* 17200 360 */
	{.type FromDictionary, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 17208 */
	{.type Here, {.p 17208 }},	/* 17208 360 */
	{.type There, {.p 360 }},	/* 17208 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17216 */
	{.type Here, {.p 17216 }},	/* 17216 360 */
	{.type There, {.p 360 }},	/* 17216 360 */
	{.type FromDictionary, {.p C_qabort_parens}, .src = "dd C_qabort_parens"},		/* dd C_qabort_parens 17224 */
	{.type Here, {.p 17224 }},	/* 17224 360 */
	{.type There, {.p 360 }},	/* 17224 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17232 */
	{.type Here, {.p 17232 }},	/* 17232 360 */
	{.type There, {.p 360 }},	/* 17232 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17240 */
	{.type Here, {.p 17240 }},	/* 17240 360 */
	{.type There, {.p 360 }},	/* 17240 360 */
	{.type Here, {.p 17240 }},	/* 17240 360 */
	{.type There, {.p 360 }},	/* 17240 360 */
/* ; could make this work for strings longer than 256 bytes. */	{.type Here, {.p 17240 }},	/* 17240 360 */
	{.type There, {.p 360 }},	/* 17240 360 */
/* ; But, for now, strings longer than 256 bytes are not supported by " or c" or s" or ." */	{.type Here, {.p 17240 }},	/* 17240 360 */
	{.type There, {.p 360 }},	/* 17240 360 */
/* ; this does not store the count in the dictionary */	{.type Here, {.p 17240 }},	/* 17240 360 */
	{.type There, {.p 360 }},	/* 17240 360 */
	{.type Header, {.hdr { 1, "\"", /* C_double_quote = 17256 */ colon }}}, /* CENTRY "\"" double_quote 1 ; ( | .. " -- 'text count ) stores string in the dictionary and also leaves the address and count of the string on the stack - to use strings at the interpreter prompt h 17264 */
	{.type Here, {.p 17264 }},	/* 17264 360 */
	{.type There, {.p 360 }},	/* 17264 360 */
	{.type Here, {.p 17264 }},	/* 17264 360 */
	{.type There, {.p 360 }},	/* 17264 360 */
	{.type FromDictionary, {.p C_counted_doublequote}, .src = "dd C_counted_doublequote	; ( 'Wordb )"},		/* dd C_counted_doublequote	; ( 'Wordb ) 17272 */
	{.type Here, {.p 17272 }},	/* 17272 360 */
	{.type There, {.p 360 }},	/* 17272 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count			; ( 'Wordb+1 count )"},		/* dd C_count			; ( 'Wordb+1 count ) 17280 */
	{.type Here, {.p 17280 }},	/* 17280 360 */
	{.type There, {.p 360 }},	/* 17280 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush			; ( 'Wordb+1 ) (R count )"},		/* dd M_rpush			; ( 'Wordb+1 ) (R count ) 17288 */
	{.type Here, {.p 17288 }},	/* 17288 360 */
	{.type There, {.p 360 }},	/* 17288 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here			; ( 'Wordb+1 here ) (R count )"},		/* dd C_here			; ( 'Wordb+1 here ) (R count ) 17296 */
	{.type Here, {.p 17296 }},	/* 17296 360 */
	{.type There, {.p 360 }},	/* 17296 360 */
	{.type FromDictionary, {.p M_rfetch}, .src = "dd M_rfetch			; ( 'Wordb+1 here count ) (R count )"},		/* dd M_rfetch			; ( 'Wordb+1 here count ) (R count ) 17304 */
	{.type Here, {.p 17304 }},	/* 17304 360 */
	{.type There, {.p 360 }},	/* 17304 360 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 17312 */
	{.type Here, {.p 17312 }},	/* 17312 360 */
	{.type There, {.p 360 }},	/* 17312 360 */
	{.type Here, {.p 17312 }},	/* 17312 360 */
	{.type There, {.p 360 }},	/* 17312 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( here )"},		/* dd C_here	; ( here ) 17320 */
	{.type Here, {.p 17320 }},	/* 17320 360 */
	{.type There, {.p 360 }},	/* 17320 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( here count )"},		/* dd M_rpop	; ( here count ) 17328 */
	{.type Here, {.p 17328 }},	/* 17328 360 */
	{.type There, {.p 360 }},	/* 17328 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( here count count )"},		/* dd M_dup	; ( here count count ) 17336 */
	{.type Here, {.p 17336 }},	/* 17336 360 */
	{.type There, {.p 360 }},	/* 17336 360 */
	{.type FromDictionary, {.p C_allot}, .src = "dd C_allot	; ( here count ) here = here+count"},		/* dd C_allot	; ( here count ) here = here+count 17344 */
	{.type Here, {.p 17344 }},	/* 17344 360 */
	{.type There, {.p 360 }},	/* 17344 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17352 */
	{.type Here, {.p 17352 }},	/* 17352 360 */
	{.type There, {.p 360 }},	/* 17352 360 */
	{.type Here, {.p 17352 }},	/* 17352 360 */
	{.type There, {.p 360 }},	/* 17352 360 */
	{.type Header, {.hdr { 2, "c\"", /* C_cdouble_quote = 17368 */ colon }}}, /* CENTRY "c\"" cdouble_quote 2 ; ( | ..." -- 'counted-string ) stores counted string in the dictionary. For use in interpretive mode. h 17376 */
	{.type Here, {.p 17376 }},	/* 17376 360 */
	{.type There, {.p 360 }},	/* 17376 360 */
	{.type Here, {.p 17376 }},	/* 17376 360 */
	{.type There, {.p 360 }},	/* 17376 360 */
	{.type FromDictionary, {.p C_counted_doublequote}, .src = "dd C_counted_doublequote	; ( 'Wordb )"},		/* dd C_counted_doublequote	; ( 'Wordb ) 17384 */
	{.type Here, {.p 17384 }},	/* 17384 360 */
	{.type There, {.p 360 }},	/* 17384 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup			; ( 'Wordb 'Wordb )"},		/* dd M_dup			; ( 'Wordb 'Wordb ) 17392 */
	{.type Here, {.p 17392 }},	/* 17392 360 */
	{.type There, {.p 360 }},	/* 17392 360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch			; ( 'Wordb count )"},		/* dd M_cfetch			; ( 'Wordb count ) 17400 */
	{.type Here, {.p 17400 }},	/* 17400 360 */
	{.type There, {.p 360 }},	/* 17400 360 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus			; ( 'Wordb count+1 )"},		/* dd C_1plus			; ( 'Wordb count+1 ) 17408 */
	{.type Here, {.p 17408 }},	/* 17408 360 */
	{.type There, {.p 360 }},	/* 17408 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush			; ( 'Wordb ) (R count+1 )"},		/* dd M_rpush			; ( 'Wordb ) (R count+1 ) 17416 */
	{.type Here, {.p 17416 }},	/* 17416 360 */
	{.type There, {.p 360 }},	/* 17416 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here			; ( 'Wordb here ) (R count+1 )"},		/* dd C_here			; ( 'Wordb here ) (R count+1 ) 17424 */
	{.type Here, {.p 17424 }},	/* 17424 360 */
	{.type There, {.p 360 }},	/* 17424 360 */
	{.type FromDictionary, {.p M_rfetch}, .src = "dd M_rfetch			; ( 'Wordb here count ) (R count+1 )"},		/* dd M_rfetch			; ( 'Wordb here count ) (R count+1 ) 17432 */
	{.type Here, {.p 17432 }},	/* 17432 360 */
	{.type There, {.p 360 }},	/* 17432 360 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 17440 */
	{.type Here, {.p 17440 }},	/* 17440 360 */
	{.type There, {.p 360 }},	/* 17440 360 */
	{.type Here, {.p 17440 }},	/* 17440 360 */
	{.type There, {.p 360 }},	/* 17440 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( here )"},		/* dd C_here	; ( here ) 17448 */
	{.type Here, {.p 17448 }},	/* 17448 360 */
	{.type There, {.p 360 }},	/* 17448 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( here count+1 )"},		/* dd M_rpop	; ( here count+1 ) 17456 */
	{.type Here, {.p 17456 }},	/* 17456 360 */
	{.type There, {.p 360 }},	/* 17456 360 */
	{.type FromDictionary, {.p C_allot}, .src = "dd C_allot	; ( here ) here = here+count+1"},		/* dd C_allot	; ( here ) here = here+count+1 17464 */
	{.type Here, {.p 17464 }},	/* 17464 360 */
	{.type There, {.p 360 }},	/* 17464 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17472 */
	{.type Here, {.p 17472 }},	/* 17472 360 */
	{.type There, {.p 360 }},	/* 17472 360 */
	{.type Here, {.p 17472 }},	/* 17472 360 */
	{.type There, {.p 360 }},	/* 17472 360 */
/* ; for compiling counted strings into the definition. Puts the ( 'text count ) on the stack at run time */	{.type Here, {.p 17472 }},	/* 17472 360 */
	{.type There, {.p 360 }},	/* 17472 360 */
	{.type IHeader, {.hdr { 2, "s\"", /* CI_sdouble_quote = 17488 */ colon }}}, /* CIENTRY "s\"" sdouble_quote 2 ; ( | ..." -- 'text count ) add the string from the input stream to the dictionary as (sliteral) count string - at run-time puts the ( -- addr n) of the counted string on the stack. h 17496 */
	{.type Here, {.p 17496 }},	/* 17496 360 */
	{.type There, {.p 360 }},	/* 17496 360 */
	{.type Here, {.p 17496 }},	/* 17496 360 */
	{.type There, {.p 360 }},	/* 17496 360 */
	{.type FromDictionary, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 17504 */
	{.type Here, {.p 17504 }},	/* 17504 360 */
	{.type There, {.p 360 }},	/* 17504 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17512 */
	{.type Here, {.p 17512 }},	/* 17512 360 */
	{.type There, {.p 360 }},	/* 17512 360 */
	{.type Here, {.p 17512 }},	/* 17512 360 */
	{.type There, {.p 360 }},	/* 17512 360 */
	{.type IHeader, {.hdr { 2, ".\"", /* CI_dotstr = 17528 */ colon }}}, /* CIENTRY ".\"" dotstr 2 ; ( | ..." -- ) ." = s" type h 17536 */
	{.type Here, {.p 17536 }},	/* 17536 360 */
	{.type There, {.p 360 }},	/* 17536 360 */
	{.type Here, {.p 17536 }},	/* 17536 360 */
	{.type There, {.p 360 }},	/* 17536 360 */
	{.type FromDictionary, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 17544 */
	{.type Here, {.p 17544 }},	/* 17544 360 */
	{.type There, {.p 360 }},	/* 17544 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17552 */
	{.type Here, {.p 17552 }},	/* 17552 360 */
	{.type There, {.p 360 }},	/* 17552 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 17560 */
	{.type Here, {.p 17560 }},	/* 17560 360 */
	{.type There, {.p 360 }},	/* 17560 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17568 */
	{.type Here, {.p 17568 }},	/* 17568 360 */
	{.type There, {.p 360 }},	/* 17568 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17576 */
	{.type Here, {.p 17576 }},	/* 17576 360 */
	{.type There, {.p 360 }},	/* 17576 360 */
	{.type Here, {.p 17576 }},	/* 17576 360 */
	{.type There, {.p 360 }},	/* 17576 360 */
	{.type IHeader, {.hdr { 2, "if", /* CI_if = 17592 */ colon }}}, /* CIENTRY "if" if 2 h 17600 */
	{.type Here, {.p 17600 }},	/* 17600 360 */
	{.type There, {.p 360 }},	/* 17600 360 */
	{.type Here, {.p 17600 }},	/* 17600 360 */
	{.type There, {.p 360 }},	/* 17600 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17608 */
	{.type Here, {.p 17608 }},	/* 17608 360 */
	{.type There, {.p 360 }},	/* 17608 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 17616 */
	{.type Here, {.p 17616 }},	/* 17616 360 */
	{.type There, {.p 360 }},	/* 17616 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17624 */
	{.type Here, {.p 17624 }},	/* 17624 360 */
	{.type There, {.p 360 }},	/* 17624 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 17632 */
	{.type Here, {.p 17632 }},	/* 17632 360 */
	{.type There, {.p 360 }},	/* 17632 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17640 */
	{.type Here, {.p 17640 }},	/* 17640 360 */
	{.type There, {.p 360 }},	/* 17640 360 */
	{.type Absolute, {.p 0}},		/* dd 0 17648 */
	{.type Here, {.p 17648 }},	/* 17648 360 */
	{.type There, {.p 360 }},	/* 17648 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17656 */
	{.type Here, {.p 17656 }},	/* 17656 360 */
	{.type There, {.p 360 }},	/* 17656 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17664 */
	{.type Here, {.p 17664 }},	/* 17664 360 */
	{.type There, {.p 360 }},	/* 17664 360 */
	{.type IHeader, {.hdr { 4, "else", /* CI_else = 17680 */ colon }}}, /* CIENTRY "else" else 4 h 17688 */
	{.type Here, {.p 17688 }},	/* 17688 360 */
	{.type There, {.p 360 }},	/* 17688 360 */
	{.type Here, {.p 17688 }},	/* 17688 360 */
	{.type There, {.p 360 }},	/* 17688 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17696 */
	{.type Here, {.p 17696 }},	/* 17696 360 */
	{.type There, {.p 360 }},	/* 17696 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 17704 */
	{.type Here, {.p 17704 }},	/* 17704 360 */
	{.type There, {.p 360 }},	/* 17704 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17712 */
	{.type Here, {.p 17712 }},	/* 17712 360 */
	{.type There, {.p 360 }},	/* 17712 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 17720 */
	{.type Here, {.p 17720 }},	/* 17720 360 */
	{.type There, {.p 360 }},	/* 17720 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 17728 */
	{.type Here, {.p 17728 }},	/* 17728 360 */
	{.type There, {.p 360 }},	/* 17728 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17736 */
	{.type Here, {.p 17736 }},	/* 17736 360 */
	{.type There, {.p 360 }},	/* 17736 360 */
	{.type Absolute, {.p 0}},		/* dd 0 17744 */
	{.type Here, {.p 17744 }},	/* 17744 360 */
	{.type There, {.p 360 }},	/* 17744 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17752 */
	{.type Here, {.p 17752 }},	/* 17752 360 */
	{.type There, {.p 360 }},	/* 17752 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 17760 */
	{.type Here, {.p 17760 }},	/* 17760 360 */
	{.type There, {.p 360 }},	/* 17760 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 17768 */
	{.type Here, {.p 17768 }},	/* 17768 360 */
	{.type There, {.p 360 }},	/* 17768 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 17776 */
	{.type Here, {.p 17776 }},	/* 17776 360 */
	{.type There, {.p 360 }},	/* 17776 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 17784 */
	{.type Here, {.p 17784 }},	/* 17784 360 */
	{.type There, {.p 360 }},	/* 17784 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17792 */
	{.type Here, {.p 17792 }},	/* 17792 360 */
	{.type There, {.p 360 }},	/* 17792 360 */
	{.type IHeader, {.hdr { 4, "then", /* CI_then = 17808 */ colon }}}, /* CIENTRY "then" then 4 h 17816 */
	{.type Here, {.p 17816 }},	/* 17816 360 */
	{.type There, {.p 360 }},	/* 17816 360 */
	{.type Here, {.p 17816 }},	/* 17816 360 */
	{.type There, {.p 360 }},	/* 17816 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 17824 */
	{.type Here, {.p 17824 }},	/* 17824 360 */
	{.type There, {.p 360 }},	/* 17824 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 17832 */
	{.type Here, {.p 17832 }},	/* 17832 360 */
	{.type There, {.p 360 }},	/* 17832 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 17840 */
	{.type Here, {.p 17840 }},	/* 17840 360 */
	{.type There, {.p 360 }},	/* 17840 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17848 */
	{.type Here, {.p 17848 }},	/* 17848 360 */
	{.type There, {.p 360 }},	/* 17848 360 */
	{.type IHeader, {.hdr { 5, "begin", /* CI_begin = 17864 */ colon }}}, /* CIENTRY "begin" begin 5 h 17872 */
	{.type Here, {.p 17872 }},	/* 17872 360 */
	{.type There, {.p 360 }},	/* 17872 360 */
	{.type Here, {.p 17872 }},	/* 17872 360 */
	{.type There, {.p 360 }},	/* 17872 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 17880 */
	{.type Here, {.p 17880 }},	/* 17880 360 */
	{.type There, {.p 360 }},	/* 17880 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17888 */
	{.type Here, {.p 17888 }},	/* 17888 360 */
	{.type There, {.p 360 }},	/* 17888 360 */
	{.type IHeader, {.hdr { 5, "again", /* CI_again = 17904 */ colon }}}, /* CIENTRY "again" again 5 h 17912 */
	{.type Here, {.p 17912 }},	/* 17912 360 */
	{.type There, {.p 360 }},	/* 17912 360 */
	{.type Here, {.p 17912 }},	/* 17912 360 */
	{.type There, {.p 360 }},	/* 17912 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17920 */
	{.type Here, {.p 17920 }},	/* 17920 360 */
	{.type There, {.p 360 }},	/* 17920 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 17928 */
	{.type Here, {.p 17928 }},	/* 17928 360 */
	{.type There, {.p 360 }},	/* 17928 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17936 */
	{.type Here, {.p 17936 }},	/* 17936 360 */
	{.type There, {.p 360 }},	/* 17936 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17944 */
	{.type Here, {.p 17944 }},	/* 17944 360 */
	{.type There, {.p 360 }},	/* 17944 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17952 */
	{.type Here, {.p 17952 }},	/* 17952 360 */
	{.type There, {.p 360 }},	/* 17952 360 */
	{.type IHeader, {.hdr { 5, "until", /* CI_until = 17968 */ colon }}}, /* CIENTRY "until" until 5 h 17976 */
	{.type Here, {.p 17976 }},	/* 17976 360 */
	{.type There, {.p 360 }},	/* 17976 360 */
	{.type Here, {.p 17976 }},	/* 17976 360 */
	{.type There, {.p 360 }},	/* 17976 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17984 */
	{.type Here, {.p 17984 }},	/* 17984 360 */
	{.type There, {.p 360 }},	/* 17984 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 17992 */
	{.type Here, {.p 17992 }},	/* 17992 360 */
	{.type There, {.p 360 }},	/* 17992 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18000 */
	{.type Here, {.p 18000 }},	/* 18000 360 */
	{.type There, {.p 360 }},	/* 18000 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18008 */
	{.type Here, {.p 18008 }},	/* 18008 360 */
	{.type There, {.p 360 }},	/* 18008 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18016 */
	{.type Here, {.p 18016 }},	/* 18016 360 */
	{.type There, {.p 360 }},	/* 18016 360 */
	{.type IHeader, {.hdr { 5, "while", /* CI_while = 18032 */ colon }}}, /* CIENTRY "while" while 5 h 18040 */
	{.type Here, {.p 18040 }},	/* 18040 360 */
	{.type There, {.p 360 }},	/* 18040 360 */
	{.type Here, {.p 18040 }},	/* 18040 360 */
	{.type There, {.p 360 }},	/* 18040 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18048 */
	{.type Here, {.p 18048 }},	/* 18048 360 */
	{.type There, {.p 360 }},	/* 18048 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 18056 */
	{.type Here, {.p 18056 }},	/* 18056 360 */
	{.type There, {.p 360 }},	/* 18056 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18064 */
	{.type Here, {.p 18064 }},	/* 18064 360 */
	{.type There, {.p 360 }},	/* 18064 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 18072 */
	{.type Here, {.p 18072 }},	/* 18072 360 */
	{.type There, {.p 360 }},	/* 18072 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18080 */
	{.type Here, {.p 18080 }},	/* 18080 360 */
	{.type There, {.p 360 }},	/* 18080 360 */
	{.type Absolute, {.p 0}},		/* dd 0 18088 */
	{.type Here, {.p 18088 }},	/* 18088 360 */
	{.type There, {.p 360 }},	/* 18088 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18096 */
	{.type Here, {.p 18096 }},	/* 18096 360 */
	{.type There, {.p 360 }},	/* 18096 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18104 */
	{.type Here, {.p 18104 }},	/* 18104 360 */
	{.type There, {.p 360 }},	/* 18104 360 */
	{.type IHeader, {.hdr { 6, "repeat", /* CI_repeat = 18120 */ colon }}}, /* CIENTRY "repeat" repeat 6 h 18128 */
	{.type Here, {.p 18128 }},	/* 18128 360 */
	{.type There, {.p 360 }},	/* 18128 360 */
	{.type Here, {.p 18128 }},	/* 18128 360 */
	{.type There, {.p 360 }},	/* 18128 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18136 */
	{.type Here, {.p 18136 }},	/* 18136 360 */
	{.type There, {.p 360 }},	/* 18136 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 18144 */
	{.type Here, {.p 18144 }},	/* 18144 360 */
	{.type There, {.p 360 }},	/* 18144 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18152 */
	{.type Here, {.p 18152 }},	/* 18152 360 */
	{.type There, {.p 360 }},	/* 18152 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 18160 */
	{.type Here, {.p 18160 }},	/* 18160 360 */
	{.type There, {.p 360 }},	/* 18160 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18168 */
	{.type Here, {.p 18168 }},	/* 18168 360 */
	{.type There, {.p 360 }},	/* 18168 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 18176 */
	{.type Here, {.p 18176 }},	/* 18176 360 */
	{.type There, {.p 360 }},	/* 18176 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 18184 */
	{.type Here, {.p 18184 }},	/* 18184 360 */
	{.type There, {.p 360 }},	/* 18184 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18192 */
	{.type Here, {.p 18192 }},	/* 18192 360 */
	{.type There, {.p 360 }},	/* 18192 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18200 */
	{.type Here, {.p 18200 }},	/* 18200 360 */
	{.type There, {.p 360 }},	/* 18200 360 */
	{.type IHeader, {.hdr { 2, "do", /* CI_do = 18216 */ colon }}}, /* CIENTRY "do" do 2 h 18224 */
	{.type Here, {.p 18224 }},	/* 18224 360 */
	{.type There, {.p 360 }},	/* 18224 360 */
	{.type Here, {.p 18224 }},	/* 18224 360 */
	{.type There, {.p 360 }},	/* 18224 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18232 */
	{.type Here, {.p 18232 }},	/* 18232 360 */
	{.type There, {.p 360 }},	/* 18232 360 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time"},		/* dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time 18240 */
	{.type Here, {.p 18240 }},	/* 18240 360 */
	{.type There, {.p 360 }},	/* 18240 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma		; puts (do) into the dictionary"},		/* dd C_comma		; puts (do) into the dictionary 18248 */
	{.type Here, {.p 18248 }},	/* 18248 360 */
	{.type There, {.p 360 }},	/* 18248 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18256 */
	{.type Here, {.p 18256 }},	/* 18256 360 */
	{.type There, {.p 360 }},	/* 18256 360 */
	{.type Absolute, {.p 0}},		/* dd 0			; ( -- 0 ) 18264 */
	{.type Here, {.p 18264 }},	/* 18264 360 */
	{.type There, {.p 360 }},	/* 18264 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here		; ( 0 -- 0 here1 )"},		/* dd C_here		; ( 0 -- 0 here1 ) 18272 */
	{.type Here, {.p 18272 }},	/* 18272 360 */
	{.type There, {.p 360 }},	/* 18272 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18280 */
	{.type Here, {.p 18280 }},	/* 18280 360 */
	{.type There, {.p 360 }},	/* 18280 360 */
	{.type IHeader, {.hdr { 4, "loop", /* CI_loop = 18296 */ colon }}}, /* CIENTRY "loop" loop 4 ; ( 0 here1 -- ) h 18304 */
	{.type Here, {.p 18304 }},	/* 18304 360 */
	{.type There, {.p 360 }},	/* 18304 360 */
	{.type Here, {.p 18304 }},	/* 18304 360 */
	{.type There, {.p 360 }},	/* 18304 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18312 */
	{.type Here, {.p 18312 }},	/* 18312 360 */
	{.type There, {.p 360 }},	/* 18312 360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop		; ( 0 here1 -- 0 here1 (loop) )"},		/* dd M_doloop		; ( 0 here1 -- 0 here1 (loop) ) 18320 */
	{.type Here, {.p 18320 }},	/* 18320 360 */
	{.type There, {.p 360 }},	/* 18320 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 )"},		/* dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 ) 18328 */
	{.type Here, {.p 18328 }},	/* 18328 360 */
	{.type There, {.p 360 }},	/* 18328 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 )"},		/* dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 ) 18336 */
	{.type Here, {.p 18336 }},	/* 18336 360 */
	{.type There, {.p 360 }},	/* 18336 360 */
	{.type FromDictionary, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 18344 */
	{.type Here, {.p 18344 }},	/* 18344 360 */
	{.type There, {.p 360 }},	/* 18344 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 18352 */
	{.type Here, {.p 18352 }},	/* 18352 360 */
	{.type There, {.p 360 }},	/* 18352 360 */
	{.type FromDictionary, {.p L234}, .src = "dd L234"},		/* dd L234 18360 */
	{.type Here, {.p 18360 }},	/* 18360 360 */
	{.type There, {.p 360 }},	/* 18360 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 18368 */
	{.type Here, {.p 18368 }},	/* 18368 360 */
	{.type There, {.p 360 }},	/* 18368 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 18376 */
	{.type Here, {.p 18376 }},	/* 18376 360 */
	{.type There, {.p 360 }},	/* 18376 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18384 */
	{.type Here, {.p 18384 }},	/* 18384 360 */
	{.type There, {.p 360 }},	/* 18384 360 */
	{.type Here, {.p 18384 }},	/* 18384 360 */
	{.type There, {.p 360 }},	/* 18384 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18392 */
	{.type Here, {.p 18392 }},	/* 18392 360 */
	{.type There, {.p 360 }},	/* 18392 360 */
	{.type IHeader, {.hdr { 5, "+loop", /* CI_ploop = 18408 */ colon }}}, /* CIENTRY "+loop" ploop 5 h 18416 */
	{.type Here, {.p 18416 }},	/* 18416 360 */
	{.type There, {.p 360 }},	/* 18416 360 */
	{.type Here, {.p 18416 }},	/* 18416 360 */
	{.type There, {.p 360 }},	/* 18416 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18424 */
	{.type Here, {.p 18424 }},	/* 18424 360 */
	{.type There, {.p 360 }},	/* 18424 360 */
	{.type FromDictionary, {.p M_doploop}, .src = "dd M_doploop"},		/* dd M_doploop 18432 */
	{.type Here, {.p 18432 }},	/* 18432 360 */
	{.type There, {.p 360 }},	/* 18432 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18440 */
	{.type Here, {.p 18440 }},	/* 18440 360 */
	{.type There, {.p 360 }},	/* 18440 360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18448 */
	{.type Here, {.p 18448 }},	/* 18448 360 */
	{.type There, {.p 360 }},	/* 18448 360 */
	{.type FromDictionary, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 18456 */
	{.type Here, {.p 18456 }},	/* 18456 360 */
	{.type There, {.p 360 }},	/* 18456 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 18464 */
	{.type Here, {.p 18464 }},	/* 18464 360 */
	{.type There, {.p 360 }},	/* 18464 360 */
	{.type FromDictionary, {.p L236}, .src = "dd L236"},		/* dd L236 18472 */
	{.type Here, {.p 18472 }},	/* 18472 360 */
	{.type There, {.p 360 }},	/* 18472 360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 18480 */
	{.type Here, {.p 18480 }},	/* 18480 360 */
	{.type There, {.p 360 }},	/* 18480 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 18488 */
	{.type Here, {.p 18488 }},	/* 18488 360 */
	{.type There, {.p 360 }},	/* 18488 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18496 */
	{.type Here, {.p 18496 }},	/* 18496 360 */
	{.type There, {.p 360 }},	/* 18496 360 */
	{.type Here, {.p 18496 }},	/* 18496 360 */
	{.type There, {.p 360 }},	/* 18496 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18504 */
	{.type Here, {.p 18504 }},	/* 18504 360 */
	{.type There, {.p 360 }},	/* 18504 360 */
	{.type Header, {.hdr { 3, "w/o", /* C_wo = 18520 */ colon }}}, /* CENTRY "w/o" wo 3 h 18528 */
	{.type Here, {.p 18528 }},	/* 18528 360 */
	{.type There, {.p 360 }},	/* 18528 360 */
	{.type Here, {.p 18528 }},	/* 18528 360 */
	{.type There, {.p 360 }},	/* 18528 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18536 */
	{.type Here, {.p 18536 }},	/* 18536 360 */
	{.type There, {.p 360 }},	/* 18536 360 */
	{.type Absolute, {.p 1}},		/* dd 1 18544 */
	{.type Here, {.p 18544 }},	/* 18544 360 */
	{.type There, {.p 360 }},	/* 18544 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18552 */
	{.type Here, {.p 18552 }},	/* 18552 360 */
	{.type There, {.p 360 }},	/* 18552 360 */
	{.type Absolute, {.p 512}},		/* dd 512 18560 */
	{.type Here, {.p 18560 }},	/* 18560 360 */
	{.type There, {.p 360 }},	/* 18560 360 */
	{.type FromDictionary, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 18568 */
	{.type Here, {.p 18568 }},	/* 18568 360 */
	{.type There, {.p 360 }},	/* 18568 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18576 */
	{.type Here, {.p 18576 }},	/* 18576 360 */
	{.type There, {.p 360 }},	/* 18576 360 */
	{.type Absolute, {.p 64}},		/* dd 64 18584 */
	{.type Here, {.p 18584 }},	/* 18584 360 */
	{.type There, {.p 360 }},	/* 18584 360 */
	{.type FromDictionary, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 18592 */
	{.type Here, {.p 18592 }},	/* 18592 360 */
	{.type There, {.p 360 }},	/* 18592 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18600 */
	{.type Here, {.p 18600 }},	/* 18600 360 */
	{.type There, {.p 360 }},	/* 18600 360 */
	{.type Header, {.hdr { 3, "r/o", /* C_ro = 18616 */ colon }}}, /* CENTRY "r/o" ro 3 h 18624 */
	{.type Here, {.p 18624 }},	/* 18624 360 */
	{.type There, {.p 360 }},	/* 18624 360 */
	{.type Here, {.p 18624 }},	/* 18624 360 */
	{.type There, {.p 360 }},	/* 18624 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18632 */
	{.type Here, {.p 18632 }},	/* 18632 360 */
	{.type There, {.p 360 }},	/* 18632 360 */
	{.type Absolute, {.p 0}},		/* dd 0 18640 */
	{.type Here, {.p 18640 }},	/* 18640 360 */
	{.type There, {.p 360 }},	/* 18640 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18648 */
	{.type Here, {.p 18648 }},	/* 18648 360 */
	{.type There, {.p 360 }},	/* 18648 360 */
	{.type Header, {.hdr { 3, "r/w", /* C_rw = 18664 */ colon }}}, /* CENTRY "r/w" rw 3 h 18672 */
	{.type Here, {.p 18672 }},	/* 18672 360 */
	{.type There, {.p 360 }},	/* 18672 360 */
	{.type Here, {.p 18672 }},	/* 18672 360 */
	{.type There, {.p 360 }},	/* 18672 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18680 */
	{.type Here, {.p 18680 }},	/* 18680 360 */
	{.type There, {.p 360 }},	/* 18680 360 */
	{.type Absolute, {.p 2}},		/* dd 2 18688 */
	{.type Here, {.p 18688 }},	/* 18688 360 */
	{.type There, {.p 360 }},	/* 18688 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18696 */
	{.type Here, {.p 18696 }},	/* 18696 360 */
	{.type There, {.p 360 }},	/* 18696 360 */
	{.type Here, {.p 18696 }},	/* 18696 360 */
	{.type There, {.p 360 }},	/* 18696 360 */
	{.type Header, {.hdr { 7, "cstring", /* C_cstring = 18712 */ colon }}}, /* CENTRY "cstring" cstring 7 ; ( 'text count o -- o+'pad+1024 ) \ copy string to pad+o and add a null byte at the end h 18720 */
	{.type Here, {.p 18720 }},	/* 18720 360 */
	{.type There, {.p 360 }},	/* 18720 360 */
	{.type Here, {.p 18720 }},	/* 18720 360 */
	{.type There, {.p 360 }},	/* 18720 360 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad	; ( 'text count o 'pad )"},		/* dd C_pad	; ( 'text count o 'pad ) 18728 */
	{.type Here, {.p 18728 }},	/* 18728 360 */
	{.type There, {.p 360 }},	/* 18728 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18736 */
	{.type Here, {.p 18736 }},	/* 18736 360 */
	{.type There, {.p 360 }},	/* 18736 360 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( 'text count o 'pad 1024 ) 18744 */
	{.type Here, {.p 18744 }},	/* 18744 360 */
	{.type There, {.p 360 }},	/* 18744 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 'text count o 'pad+1024 )"},		/* dd M_plus	; ( 'text count o 'pad+1024 ) 18752 */
	{.type Here, {.p 18752 }},	/* 18752 360 */
	{.type There, {.p 360 }},	/* 18752 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 'text count o+'pad+1024 ) o=padoffset"},		/* dd M_plus	; ( 'text count o+'pad+1024 ) o=padoffset 18760 */
	{.type Here, {.p 18760 }},	/* 18760 360 */
	{.type There, {.p 360 }},	/* 18760 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 18768 */
	{.type Here, {.p 18768 }},	/* 18768 360 */
	{.type There, {.p 360 }},	/* 18768 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( 'text count o+'pad+1024 ) (R o+'pad+1024 )"},		/* dd M_rpush	; ( 'text count o+'pad+1024 ) (R o+'pad+1024 ) 18776 */
	{.type Here, {.p 18776 }},	/* 18776 360 */
	{.type There, {.p 360 }},	/* 18776 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( 'text o+'pad+1024 count ) (R o+'pad+1024 )"},		/* dd M_xswap	; ( 'text o+'pad+1024 count ) (R o+'pad+1024 ) 18784 */
	{.type Here, {.p 18784 }},	/* 18784 360 */
	{.type There, {.p 360 }},	/* 18784 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( 'text o+'pad+1024 count count ) (R o+'pad+1024 )"},		/* dd M_dup	; ( 'text o+'pad+1024 count count ) (R o+'pad+1024 ) 18792 */
	{.type Here, {.p 18792 }},	/* 18792 360 */
	{.type There, {.p 360 }},	/* 18792 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( 'text o+'pad+1024 count ) (R o+'pad+1024  count )"},		/* dd M_rpush	; ( 'text o+'pad+1024 count ) (R o+'pad+1024  count ) 18800 */
	{.type Here, {.p 18800 }},	/* 18800 360 */
	{.type There, {.p 360 }},	/* 18800 360 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; moves the filename from 'text to o+'pad+1024"},		/* dd M_cmove	; moves the filename from 'text to o+'pad+1024 18808 */
	{.type Here, {.p 18808 }},	/* 18808 360 */
	{.type There, {.p 360 }},	/* 18808 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18816 */
	{.type Here, {.p 18816 }},	/* 18816 360 */
	{.type There, {.p 360 }},	/* 18816 360 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( 0 ) (R o+'pad+1024  count ) 18824 */
	{.type Here, {.p 18824 }},	/* 18824 360 */
	{.type There, {.p 360 }},	/* 18824 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( 0 count ) (R o+'pad+1024 )"},		/* dd M_rpop	; ( 0 count ) (R o+'pad+1024 ) 18832 */
	{.type Here, {.p 18832 }},	/* 18832 360 */
	{.type There, {.p 360 }},	/* 18832 360 */
	{.type FromDictionary, {.p M_rfetch}, .src = "dd M_rfetch	; ( 0 count o+'pad+1024 ) (R o+'pad+1024 )"},		/* dd M_rfetch	; ( 0 count o+'pad+1024 ) (R o+'pad+1024 ) 18840 */
	{.type Here, {.p 18840 }},	/* 18840 360 */
	{.type There, {.p 360 }},	/* 18840 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 0 count+o+'pad+1024 ) (R o+'pad+1024 )"},		/* dd M_plus	; ( 0 count+o+'pad+1024 ) (R o+'pad+1024 ) 18848 */
	{.type Here, {.p 18848 }},	/* 18848 360 */
	{.type There, {.p 360 }},	/* 18848 360 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore	; makes the filename to a null terminated string"},		/* dd M_cstore	; makes the filename to a null terminated string 18856 */
	{.type Here, {.p 18856 }},	/* 18856 360 */
	{.type There, {.p 360 }},	/* 18856 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop ;  ( o+'pad+1024 )"},		/* dd M_rpop ;  ( o+'pad+1024 ) 18864 */
	{.type Here, {.p 18864 }},	/* 18864 360 */
	{.type There, {.p 360 }},	/* 18864 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18872 */
	{.type Here, {.p 18872 }},	/* 18872 360 */
	{.type There, {.p 360 }},	/* 18872 360 */
	{.type Here, {.p 18872 }},	/* 18872 360 */
	{.type There, {.p 360 }},	/* 18872 360 */
	{.type Header, {.hdr { 8, "cstring0", /* C_cstring0 = 18896 */ colon }}}, /* CENTRY "cstring0" cstring0 8 ; ( 'text count -- 'text ) \ copy string to pad+1024 and add a null byte at the end h 18904 */
	{.type Here, {.p 18904 }},	/* 18904 360 */
	{.type There, {.p 360 }},	/* 18904 360 */
	{.type Here, {.p 18904 }},	/* 18904 360 */
	{.type There, {.p 360 }},	/* 18904 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18912 */
	{.type Here, {.p 18912 }},	/* 18912 360 */
	{.type There, {.p 360 }},	/* 18912 360 */
	{.type Absolute, {.p 0}},		/* dd 0 18920 */
	{.type Here, {.p 18920 }},	/* 18920 360 */
	{.type There, {.p 360 }},	/* 18920 360 */
	{.type FromDictionary, {.p C_cstring}, .src = "dd C_cstring"},		/* dd C_cstring 18928 */
	{.type Here, {.p 18928 }},	/* 18928 360 */
	{.type There, {.p 360 }},	/* 18928 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18936 */
	{.type Here, {.p 18936 }},	/* 18936 360 */
	{.type There, {.p 360 }},	/* 18936 360 */
	{.type Here, {.p 18936 }},	/* 18936 360 */
	{.type There, {.p 360 }},	/* 18936 360 */
	{.type Header, {.hdr { 8, "cstring1", /* C_cstring1 = 18960 */ colon }}}, /* CENTRY "cstring1" cstring1 8 ; ( 'text count -- 'text ) \ copy string to pad+1536 and add a null byte at the end h 18968 */
	{.type Here, {.p 18968 }},	/* 18968 360 */
	{.type There, {.p 360 }},	/* 18968 360 */
	{.type Here, {.p 18968 }},	/* 18968 360 */
	{.type There, {.p 360 }},	/* 18968 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18976 */
	{.type Here, {.p 18976 }},	/* 18976 360 */
	{.type There, {.p 360 }},	/* 18976 360 */
	{.type Absolute, {.p 512}},		/* dd 512 18984 */
	{.type Here, {.p 18984 }},	/* 18984 360 */
	{.type There, {.p 360 }},	/* 18984 360 */
	{.type FromDictionary, {.p C_cstring}, .src = "dd C_cstring"},		/* dd C_cstring 18992 */
	{.type Here, {.p 18992 }},	/* 18992 360 */
	{.type There, {.p 360 }},	/* 18992 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19000 */
	{.type Here, {.p 19000 }},	/* 19000 360 */
	{.type There, {.p 360 }},	/* 19000 360 */
	{.type Here, {.p 19000 }},	/* 19000 360 */
	{.type There, {.p 360 }},	/* 19000 360 */
	{.type Header, {.hdr { 9, "open-file", /* C_open_file = 19024 */ colon }}}, /* CENTRY "open-file" open_file 9 ; ( 'text count mode -- fd ioresult ) h 19032 */
	{.type Here, {.p 19032 }},	/* 19032 360 */
	{.type There, {.p 360 }},	/* 19032 360 */
	{.type Here, {.p 19032 }},	/* 19032 360 */
	{.type There, {.p 360 }},	/* 19032 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( 'text count ) (R mode)"},		/* dd M_rpush	; ( 'text count ) (R mode) 19040 */
	{.type Here, {.p 19040 }},	/* 19040 360 */
	{.type There, {.p 360 }},	/* 19040 360 */
	{.type FromDictionary, {.p C_cstring0}, .src = "dd C_cstring0 ; ( 'padtext ) (R mode )"},		/* dd C_cstring0 ; ( 'padtext ) (R mode ) 19048 */
	{.type Here, {.p 19048 }},	/* 19048 360 */
	{.type There, {.p 360 }},	/* 19048 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( 'padtext mode ) (R )"},		/* dd M_rpop	; ( 'padtext mode ) (R ) 19056 */
	{.type Here, {.p 19056 }},	/* 19056 360 */
	{.type There, {.p 360 }},	/* 19056 360 */
	{.type FromDictionary, {.p M_sysopen}, .src = "dd M_sysopen"},		/* dd M_sysopen 19064 */
	{.type Here, {.p 19064 }},	/* 19064 360 */
	{.type There, {.p 360 }},	/* 19064 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 19072 */
	{.type Here, {.p 19072 }},	/* 19072 360 */
	{.type There, {.p 360 }},	/* 19072 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19080 */
	{.type Here, {.p 19080 }},	/* 19080 360 */
	{.type There, {.p 360 }},	/* 19080 360 */
	{.type Absolute, {.p -1}},		/* dd -1 19088 */
	{.type Here, {.p 19088 }},	/* 19088 360 */
	{.type There, {.p 360 }},	/* 19088 360 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 19096 */
	{.type Here, {.p 19096 }},	/* 19096 360 */
	{.type There, {.p 360 }},	/* 19096 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19104 */
	{.type Here, {.p 19104 }},	/* 19104 360 */
	{.type There, {.p 360 }},	/* 19104 360 */
	{.type Here, {.p 19104 }},	/* 19104 360 */
	{.type There, {.p 360 }},	/* 19104 360 */
	{.type Header, {.hdr { 10, "close-file", /* C_close_file = 19128 */ colon }}}, /* CENTRY "close-file" close_file 10 ; ( fd -- ioresult ) h 19136 */
	{.type Here, {.p 19136 }},	/* 19136 360 */
	{.type There, {.p 360 }},	/* 19136 360 */
	{.type Here, {.p 19136 }},	/* 19136 360 */
	{.type There, {.p 360 }},	/* 19136 360 */
	{.type FromDictionary, {.p M_sysclose}, .src = "dd M_sysclose"},		/* dd M_sysclose 19144 */
	{.type Here, {.p 19144 }},	/* 19144 360 */
	{.type There, {.p 360 }},	/* 19144 360 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 19152 */
	{.type Here, {.p 19152 }},	/* 19152 360 */
	{.type There, {.p 360 }},	/* 19152 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19160 */
	{.type Here, {.p 19160 }},	/* 19160 360 */
	{.type There, {.p 360 }},	/* 19160 360 */
	{.type Header, {.hdr { 9, "read-file", /* C_read_file = 19184 */ colon }}}, /* CENTRY "read-file" read_file 9 ; ( 'text count fd -- count2 ioresult ) h 19192 */
	{.type Here, {.p 19192 }},	/* 19192 360 */
	{.type There, {.p 360 }},	/* 19192 360 */
	{.type Here, {.p 19192 }},	/* 19192 360 */
	{.type There, {.p 360 }},	/* 19192 360 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot	; ( n fd a )"},		/* dd C_rot	; ( n fd a ) 19200 */
	{.type Here, {.p 19200 }},	/* 19200 360 */
	{.type There, {.p 360 }},	/* 19200 360 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot	; ( fd a n )"},		/* dd C_rot	; ( fd a n ) 19208 */
	{.type Here, {.p 19208 }},	/* 19208 360 */
	{.type There, {.p 360 }},	/* 19208 360 */
	{.type FromDictionary, {.p M_sysread}, .src = "dd M_sysread"},		/* dd M_sysread 19216 */
	{.type Here, {.p 19216 }},	/* 19216 360 */
	{.type There, {.p 360 }},	/* 19216 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 19224 */
	{.type Here, {.p 19224 }},	/* 19224 360 */
	{.type There, {.p 360 }},	/* 19224 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19232 */
	{.type Here, {.p 19232 }},	/* 19232 360 */
	{.type There, {.p 360 }},	/* 19232 360 */
	{.type Absolute, {.p -1}},		/* dd -1 19240 */
	{.type Here, {.p 19240 }},	/* 19240 360 */
	{.type There, {.p 360 }},	/* 19240 360 */
	{.type FromDictionary, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 19248 */
	{.type Here, {.p 19248 }},	/* 19248 360 */
	{.type There, {.p 360 }},	/* 19248 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19256 */
	{.type Here, {.p 19256 }},	/* 19256 360 */
	{.type There, {.p 360 }},	/* 19256 360 */
	{.type Header, {.hdr { 10, "write-file", /* C_write_file = 19280 */ colon }}}, /* CENTRY "write-file" write_file 10 ; ( 'text count fd -- ioresult ) h 19288 */
	{.type Here, {.p 19288 }},	/* 19288 360 */
	{.type There, {.p 360 }},	/* 19288 360 */
	{.type Here, {.p 19288 }},	/* 19288 360 */
	{.type There, {.p 360 }},	/* 19288 360 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot	; ( n fd a )"},		/* dd C_rot	; ( n fd a ) 19296 */
	{.type Here, {.p 19296 }},	/* 19296 360 */
	{.type There, {.p 360 }},	/* 19296 360 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot	; ( fd a n )"},		/* dd C_rot	; ( fd a n ) 19304 */
	{.type Here, {.p 19304 }},	/* 19304 360 */
	{.type There, {.p 360 }},	/* 19304 360 */
	{.type FromDictionary, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 19312 */
	{.type Here, {.p 19312 }},	/* 19312 360 */
	{.type There, {.p 360 }},	/* 19312 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19320 */
	{.type Here, {.p 19320 }},	/* 19320 360 */
	{.type There, {.p 360 }},	/* 19320 360 */
	{.type Absolute, {.p -1}},		/* dd -1 19328 */
	{.type Here, {.p 19328 }},	/* 19328 360 */
	{.type There, {.p 360 }},	/* 19328 360 */
	{.type FromDictionary, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 19336 */
	{.type Here, {.p 19336 }},	/* 19336 360 */
	{.type There, {.p 360 }},	/* 19336 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19344 */
	{.type Here, {.p 19344 }},	/* 19344 360 */
	{.type There, {.p 360 }},	/* 19344 360 */
	{.type Header, {.hdr { 15, "reposition-file", /* C_reposition_file = 19368 */ colon }}}, /* CENTRY "reposition-file" reposition_file 15 ; ( type n fd -- ioresult ) h 19376 */
	{.type Here, {.p 19376 }},	/* 19376 360 */
	{.type There, {.p 360 }},	/* 19376 360 */
	{.type Here, {.p 19376 }},	/* 19376 360 */
	{.type There, {.p 360 }},	/* 19376 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap		; ( type fd n )"},		/* dd M_xswap		; ( type fd n ) 19384 */
	{.type Here, {.p 19384 }},	/* 19384 360 */
	{.type There, {.p 360 }},	/* 19384 360 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot		; ( fd n type )"},		/* dd C_rot		; ( fd n type ) 19392 */
	{.type Here, {.p 19392 }},	/* 19392 360 */
	{.type There, {.p 360 }},	/* 19392 360 */
	{.type FromDictionary, {.p M_sysseek}, .src = "dd M_sysseek"},		/* dd M_sysseek 19400 */
	{.type Here, {.p 19400 }},	/* 19400 360 */
	{.type There, {.p 360 }},	/* 19400 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19408 */
	{.type Here, {.p 19408 }},	/* 19408 360 */
	{.type There, {.p 360 }},	/* 19408 360 */
	{.type Absolute, {.p -1}},		/* dd -1 19416 */
	{.type Here, {.p 19416 }},	/* 19416 360 */
	{.type There, {.p 360 }},	/* 19416 360 */
	{.type FromDictionary, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 19424 */
	{.type Here, {.p 19424 }},	/* 19424 360 */
	{.type There, {.p 360 }},	/* 19424 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19432 */
	{.type Here, {.p 19432 }},	/* 19432 360 */
	{.type There, {.p 360 }},	/* 19432 360 */
	{.type Header, {.hdr { 7, "?fcheck", /* C_qfcheck = 19448 */ colon }}}, /* CENTRY "?fcheck" qfcheck 7 h 19456 */
	{.type Here, {.p 19456 }},	/* 19456 360 */
	{.type There, {.p 360 }},	/* 19456 360 */
	{.type Here, {.p 19456 }},	/* 19456 360 */
	{.type There, {.p 360 }},	/* 19456 360 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 19464 */
	{.type Here, {.p 19464 }},	/* 19464 360 */
	{.type There, {.p 360 }},	/* 19464 360 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 19472 */
	{.type Here, {.p 19472 }},	/* 19472 360 */
	{.type There, {.p 360 }},	/* 19472 360 */
	{.type FromDictionary, {.p L246}, .src = "dd L246"},		/* dd L246 19480 */
	{.type Here, {.p 19480 }},	/* 19480 360 */
	{.type There, {.p 360 }},	/* 19480 360 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 19488 */
	{.type Here, {.p 19488 }},	/* 19488 360 */
	{.type There, {.p 360 }},	/* 19488 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19496 */
	{.type Here, {.p 19496 }},	/* 19496 360 */
	{.type There, {.p 360 }},	/* 19496 360 */
	{.type FromDictionary, {.p L247}, .src = "dd L247"},		/* dd L247 19504 */
	{.type Here, {.p 19504 }},	/* 19504 360 */
	{.type There, {.p 360 }},	/* 19504 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 19512 */
	{.type Here, {.p 19512 }},	/* 19512 360 */
	{.type There, {.p 360 }},	/* 19512 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 19520 */
	{.type Here, {.p 19520 }},	/* 19520 360 */
	{.type There, {.p 360 }},	/* 19520 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 19528 */
	{.type Here, {.p 19528 }},	/* 19528 360 */
	{.type There, {.p 360 }},	/* 19528 360 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 19536 */
	{.type Here, {.p 19536 }},	/* 19536 360 */
	{.type There, {.p 360 }},	/* 19536 360 */
	{.type Here, {.p 19536 }},	/* 19536 360 */
	{.type There, {.p 360 }},	/* 19536 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19544 */
	{.type Here, {.p 19544 }},	/* 19544 360 */
	{.type There, {.p 360 }},	/* 19544 360 */
	{.type Header, {.hdr { 11, "create-file", /* C_create_file = 19568 */ colon }}}, /* CENTRY "create-file" create_file 11 ; ( a n mode perm -- fd ioresult ) not part of the original ff. could move this to a forth file. h 19576 */
	{.type Here, {.p 19576 }},	/* 19576 360 */
	{.type There, {.p 360 }},	/* 19576 360 */
	{.type Here, {.p 19576 }},	/* 19576 360 */
	{.type There, {.p 360 }},	/* 19576 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a n mode ) (R perm)"},		/* dd M_rpush	; ( a n mode ) (R perm) 19584 */
	{.type Here, {.p 19584 }},	/* 19584 360 */
	{.type There, {.p 360 }},	/* 19584 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a n ) (R perm mode)"},		/* dd M_rpush	; ( a n ) (R perm mode) 19592 */
	{.type Here, {.p 19592 }},	/* 19592 360 */
	{.type There, {.p 360 }},	/* 19592 360 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad	; ( a n padaddr)"},		/* dd C_pad	; ( a n padaddr) 19600 */
	{.type Here, {.p 19600 }},	/* 19600 360 */
	{.type There, {.p 360 }},	/* 19600 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19608 */
	{.type Here, {.p 19608 }},	/* 19608 360 */
	{.type There, {.p 360 }},	/* 19608 360 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( a n padaddr 1024 ) 19616 */
	{.type Here, {.p 19616 }},	/* 19616 360 */
	{.type There, {.p 360 }},	/* 19616 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( a n padaddr+1024 )"},		/* dd M_plus	; ( a n padaddr+1024 ) 19624 */
	{.type Here, {.p 19624 }},	/* 19624 360 */
	{.type There, {.p 360 }},	/* 19624 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( a padaddr+1024 n )"},		/* dd M_xswap	; ( a padaddr+1024 n ) 19632 */
	{.type Here, {.p 19632 }},	/* 19632 360 */
	{.type There, {.p 360 }},	/* 19632 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a padaddr+1024 n n )"},		/* dd M_dup	; ( a padaddr+1024 n n ) 19640 */
	{.type Here, {.p 19640 }},	/* 19640 360 */
	{.type There, {.p 360 }},	/* 19640 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n )"},		/* dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n ) 19648 */
	{.type Here, {.p 19648 }},	/* 19648 360 */
	{.type There, {.p 360 }},	/* 19648 360 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; moves the filename from a to paddaddr+1024"},		/* dd M_cmove	; moves the filename from a to paddaddr+1024 19656 */
	{.type Here, {.p 19656 }},	/* 19656 360 */
	{.type There, {.p 360 }},	/* 19656 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19664 */
	{.type Here, {.p 19664 }},	/* 19664 360 */
	{.type There, {.p 360 }},	/* 19664 360 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( 0 ) 19672 */
	{.type Here, {.p 19672 }},	/* 19672 360 */
	{.type There, {.p 360 }},	/* 19672 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( 0 n ) (R perm mode)"},		/* dd M_rpop	; ( 0 n ) (R perm mode) 19680 */
	{.type Here, {.p 19680 }},	/* 19680 360 */
	{.type There, {.p 360 }},	/* 19680 360 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad	; ( 0 n padaddr)"},		/* dd C_pad	; ( 0 n padaddr) 19688 */
	{.type Here, {.p 19688 }},	/* 19688 360 */
	{.type There, {.p 360 }},	/* 19688 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n )"},		/* dd M_plus	; ( 0 padaddr+n ) 19696 */
	{.type Here, {.p 19696 }},	/* 19696 360 */
	{.type There, {.p 360 }},	/* 19696 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19704 */
	{.type Here, {.p 19704 }},	/* 19704 360 */
	{.type There, {.p 360 }},	/* 19704 360 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( 0 padaddr+n 1024 ) 19712 */
	{.type Here, {.p 19712 }},	/* 19712 360 */
	{.type There, {.p 360 }},	/* 19712 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n+1024 )"},		/* dd M_plus	; ( 0 padaddr+n+1024 ) 19720 */
	{.type Here, {.p 19720 }},	/* 19720 360 */
	{.type There, {.p 360 }},	/* 19720 360 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore	; ( ) makes the filename to a null terminated string"},		/* dd M_cstore	; ( ) makes the filename to a null terminated string 19728 */
	{.type Here, {.p 19728 }},	/* 19728 360 */
	{.type There, {.p 360 }},	/* 19728 360 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 19736 */
	{.type Here, {.p 19736 }},	/* 19736 360 */
	{.type There, {.p 360 }},	/* 19736 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19744 */
	{.type Here, {.p 19744 }},	/* 19744 360 */
	{.type There, {.p 360 }},	/* 19744 360 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( padaddr 1024 ) 19752 */
	{.type Here, {.p 19752 }},	/* 19752 360 */
	{.type There, {.p 360 }},	/* 19752 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( padaddr+1024 )"},		/* dd M_plus	; ( padaddr+1024 ) 19760 */
	{.type Here, {.p 19760 }},	/* 19760 360 */
	{.type There, {.p 360 }},	/* 19760 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 mode) (R perm )"},		/* dd M_rpop	; ( padaddr+1024 mode) (R perm ) 19768 */
	{.type Here, {.p 19768 }},	/* 19768 360 */
	{.type There, {.p 360 }},	/* 19768 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 mode perm ) (R )"},		/* dd M_rpop	; ( padaddr+1024 mode perm ) (R ) 19776 */
	{.type Here, {.p 19776 }},	/* 19776 360 */
	{.type There, {.p 360 }},	/* 19776 360 */
	{.type FromDictionary, {.p M_syscreate}, .src = "dd M_syscreate"},		/* dd M_syscreate 19784 */
	{.type Here, {.p 19784 }},	/* 19784 360 */
	{.type There, {.p 360 }},	/* 19784 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 19792 */
	{.type Here, {.p 19792 }},	/* 19792 360 */
	{.type There, {.p 360 }},	/* 19792 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19800 */
	{.type Here, {.p 19800 }},	/* 19800 360 */
	{.type There, {.p 360 }},	/* 19800 360 */
	{.type Absolute, {.p -1}},		/* dd -1 19808 */
	{.type Here, {.p 19808 }},	/* 19808 360 */
	{.type There, {.p 360 }},	/* 19808 360 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 19816 */
	{.type Here, {.p 19816 }},	/* 19816 360 */
	{.type There, {.p 360 }},	/* 19816 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19824 */
	{.type Here, {.p 19824 }},	/* 19824 360 */
	{.type There, {.p 360 }},	/* 19824 360 */
	{.type Here, {.p 19824 }},	/* 19824 360 */
	{.type There, {.p 360 }},	/* 19824 360 */
	{.type Header, {.hdr { 3, "bye", /* C_bye = 19840 */ colon }}}, /* CENTRY "bye" bye 3 h 19848 */
	{.type Here, {.p 19848 }},	/* 19848 360 */
	{.type There, {.p 360 }},	/* 19848 360 */
	{.type Here, {.p 19848 }},	/* 19848 360 */
	{.type There, {.p 360 }},	/* 19848 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19856 */
	{.type Here, {.p 19856 }},	/* 19856 360 */
	{.type There, {.p 360 }},	/* 19856 360 */
	{.type Absolute, {.p 0}},		/* dd 0 19864 */
	{.type Here, {.p 19864 }},	/* 19864 360 */
	{.type There, {.p 360 }},	/* 19864 360 */
	{.type FromDictionary, {.p M_terminate}, .src = "dd M_terminate"},		/* dd M_terminate 19872 */
	{.type Here, {.p 19872 }},	/* 19872 360 */
	{.type There, {.p 360 }},	/* 19872 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19880 */
	{.type Here, {.p 19880 }},	/* 19880 360 */
	{.type There, {.p 360 }},	/* 19880 360 */
	{.type Here, {.p 19880 }},	/* 19880 360 */
	{.type There, {.p 360 }},	/* 19880 360 */
	{.type Header, {.hdr { 7, "include", /* C_include = 19896 */ colon }}}, /* CENTRY "include" include 7 ; this does not work h 19904 */
	{.type Here, {.p 19904 }},	/* 19904 360 */
	{.type There, {.p 360 }},	/* 19904 360 */
	{.type Here, {.p 19904 }},	/* 19904 360 */
	{.type There, {.p 360 }},	/* 19904 360 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 19912 */
	{.type Here, {.p 19912 }},	/* 19912 360 */
	{.type There, {.p 360 }},	/* 19912 360 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 19920 */
	{.type Here, {.p 19920 }},	/* 19920 360 */
	{.type There, {.p 360 }},	/* 19920 360 */
	{.type Here, {.p 19920 }},	/* 19920 360 */
	{.type There, {.p 360 }},	/* 19920 360 */
	{.type FromDictionary, {.p C_input_fetch}, .src = "dd C_input_fetch	; save the old input onto the stack"},		/* dd C_input_fetch	; save the old input onto the stack 19928 */
	{.type Here, {.p 19928 }},	/* 19928 360 */
	{.type There, {.p 360 }},	/* 19928 360 */
	{.type Here, {.p 19928 }},	/* 19928 360 */
	{.type There, {.p 360 }},	/* 19928 360 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 19936 */
	{.type Here, {.p 19936 }},	/* 19936 360 */
	{.type There, {.p 360 }},	/* 19936 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 19944 */
	{.type Here, {.p 19944 }},	/* 19944 360 */
	{.type There, {.p 360 }},	/* 19944 360 */
	{.type FromDictionary, {.p C_ro}, .src = "dd C_ro"},		/* dd C_ro 19952 */
	{.type Here, {.p 19952 }},	/* 19952 360 */
	{.type There, {.p 360 }},	/* 19952 360 */
	{.type FromDictionary, {.p C_open_file}, .src = "dd C_open_file"},		/* dd C_open_file 19960 */
	{.type Here, {.p 19960 }},	/* 19960 360 */
	{.type There, {.p 360 }},	/* 19960 360 */
	{.type FromDictionary, {.p C_qfcheck}, .src = "dd C_qfcheck"},		/* dd C_qfcheck 19968 */
	{.type Here, {.p 19968 }},	/* 19968 360 */
	{.type There, {.p 360 }},	/* 19968 360 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd		; open the new file"},		/* dd MV_Infd		; open the new file 19976 */
	{.type Here, {.p 19976 }},	/* 19976 360 */
	{.type There, {.p 360 }},	/* 19976 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 19984 */
	{.type Here, {.p 19984 }},	/* 19984 360 */
	{.type There, {.p 360 }},	/* 19984 360 */
	{.type Here, {.p 19984 }},	/* 19984 360 */
	{.type There, {.p 360 }},	/* 19984 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19992 */
	{.type Here, {.p 19992 }},	/* 19992 360 */
	{.type There, {.p 360 }},	/* 19992 360 */
	{.type Here, {.p 19992 }},	/* 19992 360 */
	{.type There, {.p 360 }},	/* 19992 360 */
	{.type Header, {.hdr { 5, "crash", /* C_crash = 20008 */ colon }}}, /* CENTRY "crash" crash 5 h 20016 */
	{.type Here, {.p 20016 }},	/* 20016 360 */
	{.type There, {.p 360 }},	/* 20016 360 */
	{.type Here, {.p 20016 }},	/* 20016 360 */
	{.type There, {.p 360 }},	/* 20016 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20024 */
	{.type Here, {.p 20024 }},	/* 20024 360 */
	{.type There, {.p 360 }},	/* 20024 360 */
	{.type FromDictionary, {.p L251}, .src = "dd L251"},		/* dd L251 20032 */
	{.type Here, {.p 20032 }},	/* 20032 360 */
	{.type There, {.p 360 }},	/* 20032 360 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 20040 */
	{.type Here, {.p 20040 }},	/* 20040 360 */
	{.type There, {.p 360 }},	/* 20040 360 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 20048 */
	{.type Here, {.p 20048 }},	/* 20048 360 */
	{.type There, {.p 360 }},	/* 20048 360 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 20056 */
	{.type Here, {.p 20056 }},	/* 20056 360 */
	{.type There, {.p 360 }},	/* 20056 360 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 20064 */
	{.type Here, {.p 20064 }},	/* 20064 360 */
	{.type There, {.p 360 }},	/* 20064 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 20072 */
	{.type Here, {.p 20072 }},	/* 20072 360 */
	{.type There, {.p 360 }},	/* 20072 360 */
	{.type Here, {.p 20072 }},	/* 20072 360 */
	{.type There, {.p 360 }},	/* 20072 360 */
	{.type Header, {.hdr { 4, "quit", /* C_quit = 20088 */ colon }}}, /* CENTRY "quit" quit 4 ; interpreter loop h 20096 */
	{.type Here, {.p 20096 }},	/* 20096 360 */
	{.type There, {.p 360 }},	/* 20096 360 */
	{.type Here, {.p 20096 }},	/* 20096 360 */
	{.type There, {.p 360 }},	/* 20096 360 */
	{.type FromDictionary, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 20104 */
	{.type Here, {.p 20104 }},	/* 20104 360 */
	{.type There, {.p 360 }},	/* 20104 360 */
	{.type FromDictionary, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 20112 */
	{.type Here, {.p 20112 }},	/* 20112 360 */
	{.type There, {.p 360 }},	/* 20112 360 */
	{.type Here, {.p 20112 }},	/* 20112 360 */
	{.type There, {.p 360 }},	/* 20112 360 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 20120 */
	{.type Here, {.p 20120 }},	/* 20120 360 */
	{.type There, {.p 360 }},	/* 20120 360 */
	{.type Here, {.p 20120 }},	/* 20120 360 */
	{.type There, {.p 360 }},	/* 20120 360 */
/* ; dd MV_toLimit	; show the line read, for debugging */	{.type Here, {.p 20120 }},	/* 20120 360 */
	{.type There, {.p 360 }},	/* 20120 360 */
/* ; dd M_fetch */	{.type Here, {.p 20120 }},	/* 20120 360 */
	{.type There, {.p 360 }},	/* 20120 360 */
/* ; dd MV_Tib */	{.type Here, {.p 20120 }},	/* 20120 360 */
	{.type There, {.p 360 }},	/* 20120 360 */
/* ; dd MC_STDOUT */	{.type Here, {.p 20120 }},	/* 20120 360 */
	{.type There, {.p 360 }},	/* 20120 360 */
/* ; dd M_fswrite */	{.type Here, {.p 20120 }},	/* 20120 360 */
	{.type There, {.p 360 }},	/* 20120 360 */
/* ; dd M_drop		; drop the return value of write */	{.type Here, {.p 20120 }},	/* 20120 360 */
	{.type There, {.p 360 }},	/* 20120 360 */
/* ; dd C_cr */	{.type Here, {.p 20120 }},	/* 20120 360 */
	{.type There, {.p 360 }},	/* 20120 360 */
/* ; dd C_space */	{.type Here, {.p 20120 }},	/* 20120 360 */
	{.type There, {.p 360 }},	/* 20120 360 */
	{.type Here, {.p 20120 }},	/* 20120 360 */
	{.type There, {.p 360 }},	/* 20120 360 */
	{.type FromDictionary, {.p C_interpret}, .src = "dd C_interpret"},		/* dd C_interpret 20128 */
	{.type Here, {.p 20128 }},	/* 20128 360 */
	{.type There, {.p 360 }},	/* 20128 360 */
	{.type Here, {.p 20128 }},	/* 20128 360 */
	{.type There, {.p 360 }},	/* 20128 360 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 20136 */
	{.type Here, {.p 20136 }},	/* 20136 360 */
	{.type There, {.p 360 }},	/* 20136 360 */
	{.type FromDictionary, {.p L_C_quit}, .src = "dd L_C_quit"},		/* dd L_C_quit 20144 */
	{.type Here, {.p 20144 }},	/* 20144 360 */
	{.type There, {.p 360 }},	/* 20144 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed?"},		/* dd M_exitcolon	; why is this needed? 20152 */
	{.type Here, {.p 20152 }},	/* 20152 360 */
	{.type There, {.p 360 }},	/* 20152 360 */
	{.type Here, {.p 20152 }},	/* 20152 360 */
	{.type There, {.p 360 }},	/* 20152 360 */
	{.type Header, {.hdr { 7, "(abort)", /* C_parenabort = 20168 */ colon }}}, /* CENTRY "(abort)" parenabort 7 ; TODO correct below stack notations h 20176 */
	{.type Here, {.p 20176 }},	/* 20176 360 */
	{.type There, {.p 360 }},	/* 20176 360 */
	{.type Here, {.p 20176 }},	/* 20176 360 */
	{.type There, {.p 360 }},	/* 20176 360 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State	; ( mv_State -- )"},		/* dd MV_State	; ( mv_State -- ) 20184 */
	{.type Here, {.p 20184 }},	/* 20184 360 */
	{.type There, {.p 360 }},	/* 20184 360 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off	; off sets variable state = 0"},		/* dd C_off	; off sets variable state = 0 20192 */
	{.type Here, {.p 20192 }},	/* 20192 360 */
	{.type There, {.p 360 }},	/* 20192 360 */
	{.type Here, {.p 20192 }},	/* 20192 360 */
	{.type There, {.p 360 }},	/* 20192 360 */
	{.type FromDictionary, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 20200 */
	{.type Here, {.p 20200 }},	/* 20200 360 */
	{.type There, {.p 360 }},	/* 20200 360 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 20208 */
	{.type Here, {.p 20208 }},	/* 20208 360 */
	{.type There, {.p 360 }},	/* 20208 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20216 */
	{.type Here, {.p 20216 }},	/* 20216 360 */
	{.type There, {.p 360 }},	/* 20216 360 */
	{.type FromDictionary, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 20224 */
	{.type Here, {.p 20224 }},	/* 20224 360 */
	{.type There, {.p 360 }},	/* 20224 360 */
	{.type FromDictionary, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 20232 */
	{.type Here, {.p 20232 }},	/* 20232 360 */
	{.type There, {.p 360 }},	/* 20232 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20240 */
	{.type Here, {.p 20240 }},	/* 20240 360 */
	{.type There, {.p 360 }},	/* 20240 360 */
	{.type FromDictionary, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 20248 */
	{.type Here, {.p 20248 }},	/* 20248 360 */
	{.type There, {.p 360 }},	/* 20248 360 */
	{.type FromDictionary, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 20256 */
	{.type Here, {.p 20256 }},	/* 20256 360 */
	{.type There, {.p 360 }},	/* 20256 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20264 */
	{.type Here, {.p 20264 }},	/* 20264 360 */
	{.type There, {.p 360 }},	/* 20264 360 */
	{.type Here, {.p 20264 }},	/* 20264 360 */
	{.type There, {.p 360 }},	/* 20264 360 */
	{.type FromDictionary, {.p C_stdinput}, .src = "dd C_stdinput"},		/* dd C_stdinput 20272 */
	{.type Here, {.p 20272 }},	/* 20272 360 */
	{.type There, {.p 360 }},	/* 20272 360 */
	{.type FromDictionary, {.p C_quit}, .src = "dd C_quit	; quit resets stacks and is the interpreter loop"},		/* dd C_quit	; quit resets stacks and is the interpreter loop 20280 */
	{.type Here, {.p 20280 }},	/* 20280 360 */
	{.type There, {.p 360 }},	/* 20280 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed? quit does not return unless it breaks"},		/* dd M_exitcolon	; why is this needed? quit does not return unless it breaks 20288 */
	{.type Here, {.p 20288 }},	/* 20288 360 */
	{.type There, {.p 360 }},	/* 20288 360 */
	{.type Here, {.p 20288 }},	/* 20288 360 */
	{.type There, {.p 360 }},	/* 20288 360 */
	{.type Here, {.p 20288 }},	/* 20288 360 */
	{.type There, {.p 360 }},	/* 20288 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal	; test code"},		/* dd M_literal	; test code 20296 */
	{.type Here, {.p 20296 }},	/* 20296 360 */
	{.type There, {.p 360 }},	/* 20296 360 */
	{.type Absolute, {.p 66}},		/* dd 66 20304 */
	{.type Here, {.p 20304 }},	/* 20304 360 */
	{.type There, {.p 360 }},	/* 20304 360 */
	{.type FromDictionary, {.p MV_Wordb}, .src = "dd MV_Wordb"},		/* dd MV_Wordb 20312 */
	{.type Here, {.p 20312 }},	/* 20312 360 */
	{.type There, {.p 360 }},	/* 20312 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20320 */
	{.type Here, {.p 20320 }},	/* 20320 360 */
	{.type There, {.p 360 }},	/* 20320 360 */
	{.type FromDictionary, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 20328 */
	{.type Here, {.p 20328 }},	/* 20328 360 */
	{.type There, {.p 360 }},	/* 20328 360 */
	{.type FromDictionary, {.p MV_Wordb}, .src = "dd MV_Wordb"},		/* dd MV_Wordb 20336 */
	{.type Here, {.p 20336 }},	/* 20336 360 */
	{.type There, {.p 360 }},	/* 20336 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20344 */
	{.type Here, {.p 20344 }},	/* 20344 360 */
	{.type There, {.p 360 }},	/* 20344 360 */
	{.type Absolute, {.p 1}},		/* dd 1 20352 */
	{.type Here, {.p 20352 }},	/* 20352 360 */
	{.type There, {.p 360 }},	/* 20352 360 */
	{.type FromDictionary, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 20360 */
	{.type Here, {.p 20360 }},	/* 20360 360 */
	{.type There, {.p 360 }},	/* 20360 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 20368 */
	{.type Here, {.p 20368 }},	/* 20368 360 */
	{.type There, {.p 360 }},	/* 20368 360 */
	{.type FromDictionary, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 20376 */
	{.type Here, {.p 20376 }},	/* 20376 360 */
	{.type There, {.p 360 }},	/* 20376 360 */
	{.type FromDictionary, {.p MV_Wordb}, .src = "dd MV_Wordb"},		/* dd MV_Wordb 20384 */
	{.type Here, {.p 20384 }},	/* 20384 360 */
	{.type There, {.p 360 }},	/* 20384 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20392 */
	{.type Here, {.p 20392 }},	/* 20392 360 */
	{.type There, {.p 360 }},	/* 20392 360 */
	{.type Absolute, {.p 1}},		/* dd 1 20400 */
	{.type Here, {.p 20400 }},	/* 20400 360 */
	{.type There, {.p 360 }},	/* 20400 360 */
	{.type FromDictionary, {.p M_sysread}, .src = "dd M_sysread"},		/* dd M_sysread 20408 */
	{.type Here, {.p 20408 }},	/* 20408 360 */
	{.type There, {.p 360 }},	/* 20408 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop		; drop the return value of read"},		/* dd M_drop		; drop the return value of read 20416 */
	{.type Here, {.p 20416 }},	/* 20416 360 */
	{.type There, {.p 360 }},	/* 20416 360 */
	{.type Here, {.p 20416 }},	/* 20416 360 */
	{.type There, {.p 360 }},	/* 20416 360 */
	{.type Header, {.hdr { 10, "initialize", /* C_initialize = 20440 */ colon }}}, /* CENTRY "initialize" initialize 10 ; initialize buffer file names and buffer fds, why not hard code this? h 20448 */
	{.type Here, {.p 20448 }},	/* 20448 360 */
	{.type There, {.p 360 }},	/* 20448 360 */
	{.type Here, {.p 20448 }},	/* 20448 360 */
	{.type There, {.p 360 }},	/* 20448 360 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 20456 */
	{.type Here, {.p 20456 }},	/* 20456 360 */
	{.type There, {.p 360 }},	/* 20456 360 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 20464 */
	{.type Here, {.p 20464 }},	/* 20464 360 */
	{.type There, {.p 360 }},	/* 20464 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20472 */
	{.type Here, {.p 20472 }},	/* 20472 360 */
	{.type There, {.p 360 }},	/* 20472 360 */
	{.type Absolute, {.p 0}},		/* dd 0 20480 */
	{.type Here, {.p 20480 }},	/* 20480 360 */
	{.type There, {.p 360 }},	/* 20480 360 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 20488 */
	{.type Here, {.p 20488 }},	/* 20488 360 */
	{.type There, {.p 360 }},	/* 20488 360 */
	{.type Here, {.p 20488 }},	/* 20488 360 */
	{.type There, {.p 360 }},	/* 20488 360 */
	{.type Here, {.p 20488 }},	/* 20488 360 */
	{.type There, {.p 360 }},	/* 20488 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 20496 */
	{.type Here, {.p 20496 }},	/* 20496 360 */
	{.type There, {.p 360 }},	/* 20496 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20504 */
	{.type Here, {.p 20504 }},	/* 20504 360 */
	{.type There, {.p 360 }},	/* 20504 360 */
	{.type Absolute, {.p -1}},		/* dd -1 20512 */
	{.type Here, {.p 20512 }},	/* 20512 360 */
	{.type There, {.p 360 }},	/* 20512 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 20520 */
	{.type Here, {.p 20520 }},	/* 20520 360 */
	{.type There, {.p 360 }},	/* 20520 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20528 */
	{.type Here, {.p 20528 }},	/* 20528 360 */
	{.type There, {.p 360 }},	/* 20528 360 */
	{.type Here, {.p 20528 }},	/* 20528 360 */
	{.type There, {.p 360 }},	/* 20528 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20536 */
	{.type Here, {.p 20536 }},	/* 20536 360 */
	{.type There, {.p 360 }},	/* 20536 360 */
	{.type Absolute, {.p 1}},		/* dd 1 20544 */
	{.type Here, {.p 20544 }},	/* 20544 360 */
	{.type There, {.p 360 }},	/* 20544 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 20552 */
	{.type Here, {.p 20552 }},	/* 20552 360 */
	{.type There, {.p 360 }},	/* 20552 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 20560 */
	{.type Here, {.p 20560 }},	/* 20560 360 */
	{.type There, {.p 360 }},	/* 20560 360 */
	{.type Here, {.p 20560 }},	/* 20560 360 */
	{.type There, {.p 360 }},	/* 20560 360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 20568 */
	{.type Here, {.p 20568 }},	/* 20568 360 */
	{.type There, {.p 360 }},	/* 20568 360 */
	{.type FromDictionary, {.p L_C_initialize}, .src = "dd L_C_initialize"},		/* dd L_C_initialize 20576 */
	{.type Here, {.p 20576 }},	/* 20576 360 */
	{.type There, {.p 360 }},	/* 20576 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 20584 */
	{.type Here, {.p 20584 }},	/* 20584 360 */
	{.type There, {.p 360 }},	/* 20584 360 */
	{.type Here, {.p 20584 }},	/* 20584 360 */
	{.type There, {.p 360 }},	/* 20584 360 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 20592 */
	{.type Here, {.p 20592 }},	/* 20592 360 */
	{.type There, {.p 360 }},	/* 20592 360 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 20600 */
	{.type Here, {.p 20600 }},	/* 20600 360 */
	{.type There, {.p 360 }},	/* 20600 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20608 */
	{.type Here, {.p 20608 }},	/* 20608 360 */
	{.type There, {.p 360 }},	/* 20608 360 */
	{.type Absolute, {.p 0}},		/* dd 0 20616 */
	{.type Here, {.p 20616 }},	/* 20616 360 */
	{.type There, {.p 360 }},	/* 20616 360 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 20624 */
	{.type Here, {.p 20624 }},	/* 20624 360 */
	{.type There, {.p 360 }},	/* 20624 360 */
	{.type Here, {.p 20624 }},	/* 20624 360 */
	{.type There, {.p 360 }},	/* 20624 360 */
	{.type Here, {.p 20624 }},	/* 20624 360 */
	{.type There, {.p 360 }},	/* 20624 360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 20632 */
	{.type Here, {.p 20632 }},	/* 20632 360 */
	{.type There, {.p 360 }},	/* 20632 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20640 */
	{.type Here, {.p 20640 }},	/* 20640 360 */
	{.type There, {.p 360 }},	/* 20640 360 */
	{.type Absolute, {.p 0}},		/* dd 0 20648 */
	{.type Here, {.p 20648 }},	/* 20648 360 */
	{.type There, {.p 360 }},	/* 20648 360 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 20656 */
	{.type Here, {.p 20656 }},	/* 20656 360 */
	{.type There, {.p 360 }},	/* 20656 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20664 */
	{.type Here, {.p 20664 }},	/* 20664 360 */
	{.type There, {.p 360 }},	/* 20664 360 */
	{.type Here, {.p 20664 }},	/* 20664 360 */
	{.type There, {.p 360 }},	/* 20664 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20672 */
	{.type Here, {.p 20672 }},	/* 20672 360 */
	{.type There, {.p 360 }},	/* 20672 360 */
	{.type Absolute, {.p 1}},		/* dd 1 20680 */
	{.type Here, {.p 20680 }},	/* 20680 360 */
	{.type There, {.p 360 }},	/* 20680 360 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 20688 */
	{.type Here, {.p 20688 }},	/* 20688 360 */
	{.type There, {.p 360 }},	/* 20688 360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 20696 */
	{.type Here, {.p 20696 }},	/* 20696 360 */
	{.type There, {.p 360 }},	/* 20696 360 */
	{.type Here, {.p 20696 }},	/* 20696 360 */
	{.type There, {.p 360 }},	/* 20696 360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 20704 */
	{.type Here, {.p 20704 }},	/* 20704 360 */
	{.type There, {.p 360 }},	/* 20704 360 */
	{.type FromDictionary, {.p L_C_initialize_1}, .src = "dd L_C_initialize_1"},		/* dd L_C_initialize_1 20712 */
	{.type Here, {.p 20712 }},	/* 20712 360 */
	{.type There, {.p 360 }},	/* 20712 360 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 20720 */
	{.type Here, {.p 20720 }},	/* 20720 360 */
	{.type There, {.p 360 }},	/* 20720 360 */
	{.type Here, {.p 20720 }},	/* 20720 360 */
	{.type There, {.p 360 }},	/* 20720 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20728 */
	{.type Here, {.p 20728 }},	/* 20728 360 */
	{.type There, {.p 360 }},	/* 20728 360 */
	{.type FromDictionary, {.p L121}, .src = "dd L121"},		/* dd L121 20736 */
	{.type Here, {.p 20736 }},	/* 20736 360 */
	{.type There, {.p 360 }},	/* 20736 360 */
	{.type FromDictionary, {.p C_wordfilename_store}, .src = "dd C_wordfilename_store"},		/* dd C_wordfilename_store 20744 */
	{.type Here, {.p 20744 }},	/* 20744 360 */
	{.type There, {.p 360 }},	/* 20744 360 */
	{.type Here, {.p 20744 }},	/* 20744 360 */
	{.type There, {.p 360 }},	/* 20744 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20752 */
	{.type Here, {.p 20752 }},	/* 20752 360 */
	{.type There, {.p 360 }},	/* 20752 360 */
	{.type FromDictionary, {.p L122}, .src = "dd L122"},		/* dd L122 20760 */
	{.type Here, {.p 20760 }},	/* 20760 360 */
	{.type There, {.p 360 }},	/* 20760 360 */
	{.type FromDictionary, {.p C_linefilename_store}, .src = "dd C_linefilename_store"},		/* dd C_linefilename_store 20768 */
	{.type Here, {.p 20768 }},	/* 20768 360 */
	{.type There, {.p 360 }},	/* 20768 360 */
	{.type Here, {.p 20768 }},	/* 20768 360 */
	{.type There, {.p 360 }},	/* 20768 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20776 */
	{.type Here, {.p 20776 }},	/* 20776 360 */
	{.type There, {.p 360 }},	/* 20776 360 */
	{.type FromDictionary, {.p L123}, .src = "dd L123"},		/* dd L123 20784 */
	{.type Here, {.p 20784 }},	/* 20784 360 */
	{.type There, {.p 360 }},	/* 20784 360 */
	{.type FromDictionary, {.p C_doublequotefilename_store}, .src = "dd C_doublequotefilename_store"},		/* dd C_doublequotefilename_store 20792 */
	{.type Here, {.p 20792 }},	/* 20792 360 */
	{.type There, {.p 360 }},	/* 20792 360 */
	{.type Here, {.p 20792 }},	/* 20792 360 */
	{.type There, {.p 360 }},	/* 20792 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20800 */
	{.type Here, {.p 20800 }},	/* 20800 360 */
	{.type There, {.p 360 }},	/* 20800 360 */
	{.type FromDictionary, {.p L124}, .src = "dd L124"},		/* dd L124 20808 */
	{.type Here, {.p 20808 }},	/* 20808 360 */
	{.type There, {.p 360 }},	/* 20808 360 */
	{.type FromDictionary, {.p C_closeparenfilename_store}, .src = "dd C_closeparenfilename_store"},		/* dd C_closeparenfilename_store 20816 */
	{.type Here, {.p 20816 }},	/* 20816 360 */
	{.type There, {.p 360 }},	/* 20816 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 20824 */
	{.type Here, {.p 20824 }},	/* 20824 360 */
	{.type There, {.p 360 }},	/* 20824 360 */
	{.type Here, {.p 20824 }},	/* 20824 360 */
	{.type There, {.p 360 }},	/* 20824 360 */
	{.type Header, {.hdr { 4, "boot", /* C_boot = 20840 */ colon }}}, /* CENTRY "boot" boot 4 h 20848 */
	{.type Here, {.p 20848 }},	/* 20848 360 */
	{.type There, {.p 360 }},	/* 20848 360 */
	{.type Here, {.p 20848 }},	/* 20848 360 */
	{.type There, {.p 360 }},	/* 20848 360 */
	{.type FromDictionary, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 20856 */
	{.type Here, {.p 20856 }},	/* 20856 360 */
	{.type There, {.p 360 }},	/* 20856 360 */
	{.type FromDictionary, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 20864 */
	{.type Here, {.p 20864 }},	/* 20864 360 */
	{.type There, {.p 360 }},	/* 20864 360 */
	{.type Here, {.p 20864 }},	/* 20864 360 */
	{.type There, {.p 360 }},	/* 20864 360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20872 */
	{.type Here, {.p 20872 }},	/* 20872 360 */
	{.type There, {.p 360 }},	/* 20872 360 */
	{.type FromDictionary, {.p C_parenabort}, .src = "dd C_parenabort ; ( (abort) -- )"},		/* dd C_parenabort ; ( (abort) -- ) 20880 */
	{.type Here, {.p 20880 }},	/* 20880 360 */
	{.type There, {.p 360 }},	/* 20880 360 */
	{.type FromDictionary, {.p MV_Abortvec}, .src = "dd MV_Abortvec	; variable that puts (abort) code address on the stack"},		/* dd MV_Abortvec	; variable that puts (abort) code address on the stack 20888 */
	{.type Here, {.p 20888 }},	/* 20888 360 */
	{.type There, {.p 360 }},	/* 20888 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; variable abortvec = (abort) code address"},		/* dd M_store	; variable abortvec = (abort) code address 20896 */
	{.type Here, {.p 20896 }},	/* 20896 360 */
	{.type There, {.p 360 }},	/* 20896 360 */
	{.type Here, {.p 20896 }},	/* 20896 360 */
	{.type There, {.p 360 }},	/* 20896 360 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 20904 */
	{.type Here, {.p 20904 }},	/* 20904 360 */
	{.type There, {.p 360 }},	/* 20904 360 */
	{.type FromDictionary, {.p MV_H0}, .src = "dd MV_H0	; H0 = here at startup"},		/* dd MV_H0	; H0 = here at startup 20912 */
	{.type Here, {.p 20912 }},	/* 20912 360 */
	{.type There, {.p 360 }},	/* 20912 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20920 */
	{.type Here, {.p 20920 }},	/* 20920 360 */
	{.type There, {.p 360 }},	/* 20920 360 */
	{.type Here, {.p 20920 }},	/* 20920 360 */
	{.type There, {.p 360 }},	/* 20920 360 */
	{.type FromDictionary, {.p C_initialize}, .src = "dd C_initialize	; sets up the buffer filenames and buffer fd's"},		/* dd C_initialize	; sets up the buffer filenames and buffer fd's 20928 */
	{.type Here, {.p 20928 }},	/* 20928 360 */
	{.type There, {.p 360 }},	/* 20928 360 */
	{.type Here, {.p 20928 }},	/* 20928 360 */
	{.type There, {.p 360 }},	/* 20928 360 */
	{.type FromDictionary, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 20936 */
	{.type Here, {.p 20936 }},	/* 20936 360 */
	{.type There, {.p 360 }},	/* 20936 360 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd	; might be overwritten by args below"},		/* dd MV_Infd	; might be overwritten by args below 20944 */
	{.type Here, {.p 20944 }},	/* 20944 360 */
	{.type There, {.p 360 }},	/* 20944 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; stdin = 0"},		/* dd M_store	; stdin = 0 20952 */
	{.type Here, {.p 20952 }},	/* 20952 360 */
	{.type There, {.p 360 }},	/* 20952 360 */
	{.type FromDictionary, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 20960 */
	{.type Here, {.p 20960 }},	/* 20960 360 */
	{.type There, {.p 360 }},	/* 20960 360 */
	{.type FromDictionary, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 20968 */
	{.type Here, {.p 20968 }},	/* 20968 360 */
	{.type There, {.p 360 }},	/* 20968 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20976 */
	{.type Here, {.p 20976 }},	/* 20976 360 */
	{.type There, {.p 360 }},	/* 20976 360 */
	{.type FromDictionary, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 20984 */
	{.type Here, {.p 20984 }},	/* 20984 360 */
	{.type There, {.p 360 }},	/* 20984 360 */
	{.type FromDictionary, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 20992 */
	{.type Here, {.p 20992 }},	/* 20992 360 */
	{.type There, {.p 360 }},	/* 20992 360 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 21000 */
	{.type Here, {.p 21000 }},	/* 21000 360 */
	{.type There, {.p 360 }},	/* 21000 360 */
	{.type Here, {.p 21000 }},	/* 21000 360 */
	{.type There, {.p 360 }},	/* 21000 360 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 21008 */
	{.type Here, {.p 21008 }},	/* 21008 360 */
	{.type There, {.p 360 }},	/* 21008 360 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off	; off stores 0 at state"},		/* dd C_off	; off stores 0 at state 21016 */
	{.type Here, {.p 21016 }},	/* 21016 360 */
	{.type There, {.p 360 }},	/* 21016 360 */
	{.type FromDictionary, {.p C_decimal}, .src = "dd C_decimal	; decimal sets base = 10"},		/* dd C_decimal	; decimal sets base = 10 21024 */
	{.type Here, {.p 21024 }},	/* 21024 360 */
	{.type There, {.p 360 }},	/* 21024 360 */
	{.type Here, {.p 21024 }},	/* 21024 360 */
	{.type There, {.p 360 }},	/* 21024 360 */
	{.type FromDictionary, {.p C_args}, .src = "dd C_args	; process args"},		/* dd C_args	; process args 21032 */
	{.type Here, {.p 21032 }},	/* 21032 360 */
	{.type There, {.p 360 }},	/* 21032 360 */
	{.type FromDictionary, {.p C_close_input}, .src = "dd C_close_input ; if the args opened an input"},		/* dd C_close_input ; if the args opened an input 21040 */
	{.type Here, {.p 21040 }},	/* 21040 360 */
	{.type There, {.p 360 }},	/* 21040 360 */
	{.type FromDictionary, {.p C_stdinput}, .src = "dd C_stdinput	; read lines from stdin, args can change it later"},		/* dd C_stdinput	; read lines from stdin, args can change it later 21048 */
	{.type Here, {.p 21048 }},	/* 21048 360 */
	{.type There, {.p 360 }},	/* 21048 360 */
	{.type FromDictionary, {.p C_quit}, .src = "dd C_quit	; interpreter loop when there are no args or fall through after processing args"},		/* dd C_quit	; interpreter loop when there are no args or fall through after processing args 21056 */
	{.type Here, {.p 21056 }},	/* 21056 360 */
	{.type There, {.p 360 }},	/* 21056 360 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 21064 */
	{.type Here, {.p 21064 }},	/* 21064 360 */
	{.type There, {.p 360 }},	/* 21064 360 */
	{.type Here, {.p 21064 }},	/* 21064 360 */
	{.type There, {.p 360 }},	/* 21064 360 */
	{.type Here, {.p 21064 }},	/* 21064 360 */
	{.type There, {.p 360 }},	/* 21064 360 */
	{.type Chars, {.str "#n/"}},	/* "#n/" 21068 */
	{.type Here, {.p 21068 }},	/* 21068 360 */
	{.type There, {.p 360 }},	/* 21068 360 */
	{.type Here, {.p 21072 }},	/* 21072 360 */
	{.type There, {.p 360 }},	/* 21072 360 */
	{.type Chars, {.str "/word"}},	/* "/word" 21078 */
	{.type Here, {.p 21078 }},	/* 21078 360 */
	{.type There, {.p 360 }},	/* 21078 360 */
	{.type Here, {.p 21080 }},	/* 21080 360 */
	{.type There, {.p 360 }},	/* 21080 360 */
	{.type Chars, {.str "/line"}},	/* "/line" 21086 */
	{.type Here, {.p 21086 }},	/* 21086 360 */
	{.type There, {.p 360 }},	/* 21086 360 */
	{.type Here, {.p 21088 }},	/* 21088 360 */
	{.type There, {.p 360 }},	/* 21088 360 */
	{.type Chars, {.str "/doublequote"}},	/* "/doublequote" 21101 */
	{.type Here, {.p 21101 }},	/* 21101 360 */
	{.type There, {.p 360 }},	/* 21101 360 */
	{.type Here, {.p 21104 }},	/* 21104 360 */
	{.type There, {.p 360 }},	/* 21104 360 */
	{.type Chars, {.str "/closeparen"}},	/* "/closeparen" 21116 */
	{.type Here, {.p 21116 }},	/* 21116 360 */
	{.type There, {.p 360 }},	/* 21116 360 */
	{.type Here, {.p 21116 }},	/* 21116 360 */
	{.type There, {.p 360 }},	/* 21116 360 */
	{.type Here, {.p 21120 }},	/* 21120 360 */
	{.type There, {.p 360 }},	/* 21120 360 */
	{.type Chars, {.str "unable to restore input"}},	/* "unable to restore input" 21144 */
	{.type Here, {.p 21144 }},	/* 21144 360 */
	{.type There, {.p 360 }},	/* 21144 360 */
	{.type Here, {.p 21144 }},	/* 21144 360 */
	{.type There, {.p 360 }},	/* 21144 360 */
	{.type Chars, {.str "open file failed"}},	/* "open file failed" 21161 */
	{.type Here, {.p 21161 }},	/* 21161 360 */
	{.type There, {.p 360 }},	/* 21161 360 */
	{.type Here, {.p 21168 }},	/* 21168 360 */
	{.type There, {.p 360 }},	/* 21168 360 */
	{.type Chars, {.str "read file failed"}},	/* "read file failed" 21185 */
	{.type Here, {.p 21185 }},	/* 21185 360 */
	{.type There, {.p 360 }},	/* 21185 360 */
	{.type Here, {.p 21192 }},	/* 21192 360 */
	{.type There, {.p 360 }},	/* 21192 360 */
	{.type Chars, {.str " Q?"}},	/* " Q?" 21196 */
	{.type Here, {.p 21196 }},	/* 21196 360 */
	{.type There, {.p 360 }},	/* 21196 360 */
	{.type Here, {.p 21200 }},	/* 21200 360 */
	{.type There, {.p 360 }},	/* 21200 360 */
	{.type Chars, {.str " stack underflow"}},	/* " stack underflow" 21217 */
	{.type Here, {.p 21217 }},	/* 21217 360 */
	{.type There, {.p 360 }},	/* 21217 360 */
	{.type Here, {.p 21224 }},	/* 21224 360 */
	{.type There, {.p 360 }},	/* 21224 360 */
	{.type Chars, {.str " I?"}},	/* " I?" 21228 */
	{.type Here, {.p 21228 }},	/* 21228 360 */
	{.type There, {.p 360 }},	/* 21228 360 */
	{.type Here, {.p 21232 }},	/* 21232 360 */
	{.type There, {.p 360 }},	/* 21232 360 */
	{.type Chars, {.str " C?"}},	/* " C?" 21236 */
	{.type Here, {.p 21236 }},	/* 21236 360 */
	{.type There, {.p 360 }},	/* 21236 360 */
	{.type Here, {.p 21240 }},	/* 21240 360 */
	{.type There, {.p 360 }},	/* 21240 360 */
	{.type Chars, {.str "I/O error"}},	/* "I/O error" 21250 */
	{.type Here, {.p 21250 }},	/* 21250 360 */
	{.type There, {.p 360 }},	/* 21250 360 */
	{.type Here, {.p 21256 }},	/* 21256 360 */
	{.type There, {.p 360 }},	/* 21256 360 */
	{.type Chars, {.str "uninitialized execution vector"}},	/* "uninitialized execution vector" 21287 */
	{.type Here, {.p 21287 }},	/* 21287 360 */
	{.type There, {.p 360 }},	/* 21287 360 */
	{.type Here, {.p 21288 }},	/* 21288 360 */
	{.type There, {.p 360 }},	/* 21288 360 */
	{.type Chars, {.str " ok"}},	/* " ok" 21292 */
	{.type Here, {.p 21292 }},	/* 21292 360 */
	{.type There, {.p 360 }},	/* 21292 360 */
	{.type Here, {.p 21296 }},	/* 21296 360 */
	{.type There, {.p 360 }},	/* 21296 360 */
	{.type Chars, {.str "input is longer than 4096 bytes without a delimiter"}},	/* "input is longer than 4096 bytes without a delimiter" 21348 */
	{.type Here, {.p 21348 }},	/* 21348 360 */
	{.type There, {.p 360 }},	/* 21348 360 */
	{.type Here, {.p 21352 }},	/* 21352 360 */
	{.type There, {.p 360 }},	/* 21352 360 */
	{.type Chars, {.str "read error"}},	/* "read error" 21363 */
	{.type Here, {.p 21363 }},	/* 21363 360 */
	{.type There, {.p 360 }},	/* 21363 360 */
	{.type Here, {.p 21368 }},	/* 21368 360 */
	{.type There, {.p 360 }},	/* 21368 360 */
	{.type Chars, {.str "word is too long to be interpreted"}},	/* "word is too long to be interpreted" 21403 */
	{.type Here, {.p 21403 }},	/* 21403 360 */
	{.type There, {.p 360 }},	/* 21403 360 */
	{.type Here, {.p 21408 }},	/* 21408 360 */
	{.type There, {.p 360 }},	/* 21408 360 */
};

