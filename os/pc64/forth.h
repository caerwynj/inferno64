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
	MV_Sourcebuf = 2120,
	MV_Wordbuf = 2152,
	MV_toIn = 2184,
	MV_toLimit = 2216,
	MV_Findadr = 2248,
	MV_Acceptvec = 2288,
	MV_Searchlen = 2328,
	MV_Base = 2360,
	MV_toNum = 2392,
	MV_State = 2424,
	MV_Abortvec = 2464,
	MV_Infd = 2496,
	MV_Outfd = 2528,
	MV_Errfd = 2560,
	MV_Eof = 2592,
	MV_Ninputs = 2624,
	MV_H0 = 2656,
	MV_Bufferfds = 2696,
	MV_Bufferfilenames = 2736,
	C_false = 2768,
	C_true = 2816,
	C_bl = 2864,
	C_on = 2912,
	C_off = 2976,
	C_tobody = 3040,
	C_aligned = 3096,
	C_cells = 3176,
	C_cells_plus = 3232,
	C_cell_plus = 3280,
	C_depth = 3336,
	C_nip = 3440,
	C_rot = 3488,
	C_2drop = 3552,
	C_2dup = 3600,
	C_2nip = 3648,
	C_2swap = 3696,
	C_qdup = 3760,
	L_C_qdup = 3832,
	C_pick = 3856,
	L_C_pick = 3960,
	L_C_pick_1 = 3968,
	C_tuck = 3992,
	C_divides = 4056,
	C_plusstore = 4104,
	C_invert = 4184,
	C_mod = 4240,
	C_1plus = 4288,
	C_1minus = 4344,
	C_negate = 4400,
	C_2multiplies = 4464,
	C_2divides = 4520,
	C_0eq = 4576,
	C_0lt = 4632,
	C_0gt = 4688,
	C_neq = 4744,
	C_0neq = 4792,
	C_max = 4848,
	L_C_max = 4912,
	L_C_max_1 = 4920,
	C_min = 4944,
	L_C_min = 5008,
	L_C_min_1 = 5016,
	C_signum = 5040,
	L_C_signum = 5120,
	L_C_signum_2 = 5176,
	L_C_signum_3 = 5192,
	L_C_signum_1 = 5192,
	C_within = 5216,
	C_abs = 5320,
	L_C_abs = 5368,
	C_emit = 5392,
	C_type = 5496,
	C_cr = 5592,
	C_space = 5648,
	C_emits = 5696,
	L_C_emits = 5704,
	L_C_emits_1 = 5768,
	C_spaces = 5800,
	C_count = 5856,
	C_compare = 6000,
	L_C_compare = 6072,
	L_C_compare_1 = 6208,
	C_erase = 6288,
	L_C_erase = 6320,
	C_fill = 6408,
	L_C_fill = 6448,
	C_blank = 6536,
	C_search = 6584,
	L_C_search = 6688,
	L_C_search_1 = 6872,
	C_here = 6936,
	C_there = 6984,
	C_comma = 7032,
	C_c = 7112,
	C_allot = 7192,
	C_vallot = 7240,
	C_pad = 7288,
	C_align = 7352,
	C_unused = 7416,
	C_fromhash = 7480,
	C_hash = 7560,
	L_C_hash = 7712,
	L_C_hash_1 = 7736,
	C_hashs = 7816,
	L_C_hashs = 7824,
	L_C_hashs_1 = 7872,
	C_hashfrom = 7896,
	C_hold = 8008,
	C_sign = 8112,
	L_C_sign = 8168,
	C_paren_dot_paren = 8192,
	C_dot = 8280,
	C_dotr = 8336,
	C_hex = 8496,
	C_decimal = 8560,
	C_digit = 8624,
	L_C_digit = 8736,
	L_C_digit_2 = 8840,
	L_C_digit_4 = 8944,
	L_C_digit_5 = 8968,
	L_C_digit_3 = 8968,
	L_C_digit_1 = 8968,
	L_C_digit_6 = 9040,
	L_C_digit_7 = 9056,
	C_number = 9080,
	L_C_number = 9216,
	L_C_number_1 = 9248,
	L_C_number_2 = 9312,
	L_C_number_3 = 9416,
	L_C_number_4 = 9472,
	C_abort = 9560,
	C_source = 9616,
	C_bufferfd = 9672,
	C_Wordfd = 9728,
	C_Linefd = 9784,
	C_Doublequotefd = 9848,
	C_Closeparenfd = 9912,
	C_bufferfilename_store = 9976,
	C_toword = 10040,
	C_wordfd_fetch = 10096,
	C_wordfd_store = 10152,
	C_wordfilename_fetch = 10216,
	C_wordfilename_store = 10280,
	C_toline = 10336,
	C_linefd_fetch = 10392,
	C_linefd_store = 10448,
	C_linefilename_fetch = 10512,
	C_linefilename_store = 10576,
	C_todoublequote = 10640,
	C_doublequotefd_fetch = 10704,
	C_doublequotefd_store = 10768,
	C_doublequotefilename_fetch = 10840,
	C_doublequotefilename_store = 10912,
	C_tocloseparen = 10976,
	C_closeparenfd_fetch = 11040,
	C_closeparenfd_store = 11104,
	C_closeparenfilename_fetch = 11176,
	C_closeparenfilename_store = 11248,
	C_stdinput = 11312,
	L_C_stdinput = 11384,
	C_args = 11504,
	L_C_args_read = 11576,
	C_input_fetch = 11664,
	L_C_input_fetch = 11712,
	C_input_store = 11896,
	L_C_input_store = 12024,
	L_C_input_store_1 = 12112,
	C_close_input = 12160,
	L_C_close_input = 12208,
	C_restore_input = 12440,
	L_restore_input = 12576,
	C_buffername = 12608,
	C_get = 12960,
	L_C_get_store = 13216,
	L_C_get = 13264,
	L_C_get_1 = 13424,
	L_C_get_2 = 13520,
	C_word = 13568,
	C_line = 13616,
	C_doublequote = 13672,
	C_closeparen = 13728,
	C_findname = 13784,
	L_C_findname = 13824,
	L_C_findname_2 = 13936,
	L_C_findname_4 = 14064,
	L_C_findname_3 = 14072,
	L_C_findname_1 = 14088,
	C_find = 14136,
	L_C_find_1 = 14328,
	L_C_find_2 = 14344,
	L_C_find = 14368,
	L_C_find_3 = 14376,
	C_single_quote = 14400,
	L_C_single_quote = 14528,
	C_qstack = 14552,
	L_C_qstack = 14656,
	C_interpret = 14728,
	L_C_interpret = 14736,
	L_C_interpret_2 = 14840,
	L_C_interpret_4 = 14952,
	L_C_interpret_3 = 14952,
	L_C_interpret_1 = 14968,
	C_create = 15000,
	C_variable = 15240,
	C_constant = 15336,
	C_immediate = 15464,
	C_tocfa = 15576,
	C_compile = 15656,
	L_C_compile_1 = 15784,
	L_C_compile_2 = 15800,
	L_C_compile = 15816,
	L_C_compile_4 = 15944,
	L_C_compile_6 = 15976,
	L_C_compile_3 = 15976,
	C_close_bracket = 16000,
	L_C_close_bracket = 16024,
	L_C_close_bracket_1 = 16104,
	L_C_close_bracket_2 = 16128,
	L_C_close_bracket_3 = 16160,
	CI_open_bracket = 16184,
	C_smudge = 16232,
	C_reveal = 16344,
	C_colon = 16464,
	CI_semicolon = 16592,
	CI_recurse = 16672,
	C_char = 16744,
	C_literal = 16800,
	C_sliteral = 16872,
	C_string = 17032,
	CI_char_brackets = 17144,
	CI_quote_brackets = 17208,
	CI_openparen = 17256,
	CI_backslash = 17304,
	C_qabort_parens = 17352,
	L_C_qabort_parens = 17432,
	L_C_qabort_parens_1 = 17440,
	CI_abort_double_quote = 17464,
	C_double_quote = 17528,
	C_cdouble_quote = 17640,
	CI_sdouble_quote = 17760,
	CI_dotstr = 17800,
	CI_if = 17864,
	CI_else = 17952,
	CI_then = 18080,
	CI_begin = 18136,
	CI_again = 18176,
	CI_until = 18240,
	CI_while = 18304,
	CI_repeat = 18392,
	CI_do = 18488,
	CI_loop = 18568,
	L234 = 18656,
	CI_ploop = 18680,
	L236 = 18768,
	C_wo = 18792,
	C_ro = 18888,
	C_rw = 18936,
	C_cstring = 18984,
	C_cstring0 = 19168,
	C_cstring1 = 19232,
	C_open_file = 19296,
	C_close_file = 19400,
	C_read_file = 19456,
	C_write_file = 19552,
	C_reposition_file = 19640,
	C_qfcheck = 19720,
	L246 = 19816,
	C_create_file = 19848,
	C_bye = 20120,
	C_include = 20176,
	C_crash = 20288,
	C_quit = 20376,
	L_C_quit = 20400,
	C_parenabort = 20456,
	C_initialize = 20728,
	L150 = 20776,
	C_boot = 20992,
	L_pid_filename = 21240,
	L_args_prefix = 21247,
	L_args_suffix = 21251,
	L120 = 21257,
	L121 = 21261,
	L122 = 21267,
	L123 = 21273,
	L124 = 21287,
	L137 = 21300,
	L140 = 21324,
	L141 = 21342,
	L170 = 21360,
	L173 = 21364,
	L180 = 21381,
	L_C_compile_5 = 21385,
	L247 = 21389,
	L251 = 21399,
	L255 = 21430,
	L304 = 21434,
	L305 = 21471,
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
	{.type Header, {.hdr { 2, "s@", /* M_stackptr = 1256 */ stackptr }}}, /* MENTRY "s@" stackptr 2	; puts PSP on stack. Not a variable hence lower case. h 1264 */
	{.type Header, {.hdr { 7, "sysbind", /* M_sysbind = 1280 */ sysbind }}}, /* MENTRY "sysbind" sysbind 7 h 1288 */
	{.type Header, {.hdr { 8, "sysclose", /* M_sysclose = 1312 */ sysclose }}}, /* MENTRY "sysclose" sysclose 8 h 1320 */
	{.type Header, {.hdr { 9, "syscreate", /* M_syscreate = 1344 */ syscreate }}}, /* MENTRY "syscreate" syscreate 9 h 1352 */
	{.type Header, {.hdr { 8, "sysmount", /* M_sysmount = 1376 */ sysmount }}}, /* MENTRY "sysmount" sysmount 8 h 1384 */
	{.type Header, {.hdr { 7, "sysopen", /* M_sysopen = 1400 */ sysopen }}}, /* MENTRY "sysopen" sysopen 7 h 1408 */
	{.type Header, {.hdr { 7, "sysread", /* M_sysread = 1424 */ sysread }}}, /* MENTRY "sysread" sysread 7 h 1432 */
	{.type Header, {.hdr { 7, "sysseek", /* M_sysseek = 1448 */ sysseek }}}, /* MENTRY "sysseek" sysseek 7 h 1456 */
	{.type Header, {.hdr { 8, "syswrite", /* M_syswrite = 1480 */ syswrite }}}, /* MENTRY "syswrite" syswrite 8 h 1488 */
	{.type Header, {.hdr { 5, "STDIN", /* MC_STDIN = 1504 */ constant }}}, /* MCENTRY "STDIN" STDIN 5	0 ; 3 constants from here CAPITALS h 1512 */
	{.type Absolute, {.p 0}},		/* 1520 */
	{.type Header, {.hdr { 6, "STDOUT", /* MC_STDOUT = 1536 */ constant }}}, /* MCENTRY "STDOUT" STDOUT 6 1 h 1544 */
	{.type Absolute, {.p 1}},		/* 1552 */
	{.type Header, {.hdr { 6, "STDERR", /* MC_STDERR = 1568 */ constant }}}, /* MCENTRY "STDERR" STDERR 6 2 h 1576 */
	{.type Absolute, {.p 2}},		/* 1584 */
	{.type Header, {.hdr { 5, "WORD#", /* MC_WORDNUM = 1600 */ constant }}}, /* MCENTRY	"WORD#" WORDNUM 5 0 h 1608 */
	{.type Absolute, {.p 0}},		/* 1616 */
	{.type Header, {.hdr { 5, "LINE#", /* MC_LINENUM = 1632 */ constant }}}, /* MCENTRY	"LINE#" LINENUM 5 1 h 1640 */
	{.type Absolute, {.p 1}},		/* 1648 */
	{.type Header, {.hdr { 12, "DOUBLEQUOTE#", /* MC_DOUBLEQUOTENUM = 1672 */ constant }}}, /* MCENTRY	"DOUBLEQUOTE#" DOUBLEQUOTENUM 12 2 h 1680 */
	{.type Absolute, {.p 2}},		/* 1688 */
	{.type Header, {.hdr { 11, "CLOSEPAREN#", /* MC_CLOSEPARENNUM = 1712 */ constant }}}, /* MCENTRY	"CLOSEPAREN#" CLOSEPARENNUM 11 3 h 1720 */
	{.type Absolute, {.p 3}},		/* 1728 */
	{.type Header, {.hdr { 8, "#BUFFERS", /* MC_NBUFFERS = 1752 */ constant }}}, /* MCENTRY "#BUFFERS" NBUFFERS 8 16 h 1760 */
	{.type Absolute, {.p 16}},		/* 1768 */
/* ; put address of the defined location on the top of stack *//* ; cannot use H as it is nil in inferno, address where here (next available dictionary cell location) is stored *//* ; here = Dp @ *//* ; these memory locations (HERE, DTOP, etc.) are populated with values by the forth initializer */	{.type Header, {.hdr { 2, "Dp", /* MV_Dp = 1784 */ variable }}}, /* MVDENTRY "Dp" Dp 2 HERE		; here h 1792 */
	{.type FromH0, {.p HERE }},	/* 1800 0 */
	{.type Header, {.hdr { 4, "Dtop", /* MV_Dtop = 1816 */ variable }}}, /* MVDENTRY "Dtop" Dtop 4 DTOP	; last defined header h 1824 */
	{.type FromH0, {.p DTOP }},	/* 1832 0 */
	{.type Header, {.hdr { 2, "Vp", /* MV_Vp = 1848 */ variable }}}, /* MVDENTRY "Vp" Vp 2 THERE	; here of the variables space h 1856 */
	{.type FromH0, {.p THERE }},	/* 1864 0 */
	{.type Header, {.hdr { 3, "Pid", /* MV_Pid = 1880 */ variable }}}, /* MVDENTRY "Pid" Pid 3 FTHPID h 1888 */
	{.type FromH0, {.p FTHPID }},	/* 1896 0 */
	{.type Header, {.hdr { 4, "Parentpid", /* MV_Parentpid = 1912 */ variable }}}, /* MVDENTRY "Parentpid" Parentpid 4 FTHPARENTPID h 1920 */
	{.type FromH0, {.p FTHPARENTPID }},	/* 1928 0 */
/* ; the below memory locations are left alone as zeros by the initializer */	{.type Header, {.hdr { 2, "S0", /* MV_S0 = 1944 */ variable }}}, /* MVDENTRY "S0" S0 2 PSTACK h 1952 */
	{.type FromH0, {.p PSTACK }},	/* 1960 0 */
	{.type Header, {.hdr { 5, "Wordb", /* MV_Wordb = 1976 */ variable }}}, /* MVDENTRY "Wordb" Wordb 5 WORDB h 1984 */
	{.type FromH0, {.p WORDB }},	/* 1992 0 */
	{.type Header, {.hdr { 3, "Tib", /* MV_Tib = 2008 */ variable }}}, /* MVDENTRY "Tib" Tib 3 TIB h 2016 */
	{.type FromH0, {.p TIB }},	/* 2024 0 */
	{.type Header, {.hdr { 12, "Argsfilename", /* MV_Argsfilename = 2048 */ variable }}}, /* MVDENTRY "Argsfilename" Argsfilename 12 ARGSFILENAME ; counted string populated by forth starter from params h 2056 */
	{.type FromH0, {.p ARGSFILENAME }},	/* 2064 0 */
	{.type Header, {.hdr { 5, "Iobuf", /* MV_Iobuf = 2080 */ variable }}}, /* MVENTRY "Iobuf" Iobuf 5		; the values are not being used from the definition. All are initialized to 0. h 2088 */
	{.type FromV0, {.p 0 }},	/* 2096 0 */
	{.type Header, {.hdr { 9, "Sourcebuf", /* MV_Sourcebuf = 2120 */ variable }}}, /* MVENTRY "Sourcebuf" Sourcebuf 9	; is there a need for this? h 2128 */
	{.type FromV0, {.p 8 }},	/* 2136 8 */
	{.type Header, {.hdr { 7, "Wordbuf", /* MV_Wordbuf = 2152 */ variable }}}, /* MVENTRY "Wordbuf" Wordbuf 7		; is there a need for this? h 2160 */
	{.type FromV0, {.p 16 }},	/* 2168 16 */
	{.type Header, {.hdr { 3, ">In", /* MV_toIn = 2184 */ variable }}}, /* MVENTRY ">In" toIn 3 h 2192 */
	{.type FromV0, {.p 24 }},	/* 2200 24 */
	{.type Header, {.hdr { 6, ">Limit", /* MV_toLimit = 2216 */ variable }}}, /* MVENTRY ">Limit" toLimit 6 h 2224 */
	{.type FromV0, {.p 32 }},	/* 2232 32 */
	{.type Header, {.hdr { 7, "Findadr", /* MV_Findadr = 2248 */ variable }}}, /* MVENTRY "Findadr" Findadr 7 h 2256 */
	{.type FromV0, {.p 40 }},	/* 2264 40 */
	{.type Header, {.hdr { 9, "Acceptvec", /* MV_Acceptvec = 2288 */ variable }}}, /* MVENTRY "Acceptvec" Acceptvec 9 h 2296 */
	{.type FromV0, {.p 48 }},	/* 2304 48 */
	{.type Header, {.hdr { 9, "Searchlen", /* MV_Searchlen = 2328 */ variable }}}, /* MVENTRY "Searchlen" Searchlen 9 h 2336 */
	{.type FromV0, {.p 56 }},	/* 2344 56 */
	{.type Header, {.hdr { 4, "Base", /* MV_Base = 2360 */ variable }}}, /* MVENTRY "Base" Base 4 h 2368 */
	{.type FromV0, {.p 64 }},	/* 2376 64 */
	{.type Header, {.hdr { 4, ">Num", /* MV_toNum = 2392 */ variable }}}, /* MVENTRY ">Num" toNum 4 h 2400 */
	{.type FromV0, {.p 72 }},	/* 2408 72 */
	{.type Header, {.hdr { 5, "State", /* MV_State = 2424 */ variable }}}, /* MVENTRY "State" State 5 h 2432 */
	{.type FromV0, {.p 80 }},	/* 2440 80 */
	{.type Header, {.hdr { 8, "Abortvec", /* MV_Abortvec = 2464 */ variable }}}, /* MVENTRY "Abortvec" Abortvec 8	; not sure if these 3 can be constants instead? h 2472 */
	{.type FromV0, {.p 88 }},	/* 2480 88 */
	{.type Header, {.hdr { 4, "Infd", /* MV_Infd = 2496 */ variable }}}, /* MVENTRY "Infd" Infd 4 h 2504 */
	{.type FromV0, {.p 96 }},	/* 2512 96 */
	{.type Header, {.hdr { 5, "Outfd", /* MV_Outfd = 2528 */ variable }}}, /* MVENTRY "Outfd" Outfd 5 h 2536 */
	{.type FromV0, {.p 104 }},	/* 2544 104 */
	{.type Header, {.hdr { 5, "Errfd", /* MV_Errfd = 2560 */ variable }}}, /* MVENTRY "Errfd" Errfd 5 h 2568 */
	{.type FromV0, {.p 112 }},	/* 2576 112 */
	{.type Header, {.hdr { 3, "Eof", /* MV_Eof = 2592 */ variable }}}, /* MVENTRY "Eof" Eof 3 h 2600 */
	{.type FromV0, {.p 120 }},	/* 2608 120 */
	{.type Header, {.hdr { 7, "Ninputs", /* MV_Ninputs = 2624 */ variable }}}, /* MVENTRY "Ninputs" Ninputs 7 h 2632 */
	{.type FromV0, {.p 128 }},	/* 2640 128 */
	{.type Header, {.hdr { 2, "H0", /* MV_H0 = 2656 */ variable }}}, /* MVENTRY "H0" H0 2		; here at startup h 2664 */
	{.type FromV0, {.p 136 }},	/* 2672 136 */
	{.type Header, {.hdr { 9, "Bufferfds", /* MV_Bufferfds = 2696 */ variable }}}, /* MVENTRY "Bufferfds" Bufferfds 9 16 h 2704 */
	{.type FromV0, {.p 144 }},	/* 2712 144 */
	{.type Header, {.hdr { 15, "Bufferfilenames", /* MV_Bufferfilenames = 2736 */ variable }}}, /* MVENTRY "Bufferfilenames" Bufferfilenames 15 16 ; counted string labels of the searchers populated by boot h 2744 */
	{.type FromV0, {.p 272 }},	/* 2752 272 */
	{.type Header, {.hdr { 5, "false", /* C_false = 2768 */ colon }}}, /* CENTRY "false" false 5 h 2776 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2784 */
	{.type Absolute, {.p 0}},		/* dd 0 2792 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2800 */
	{.type Header, {.hdr { 4, "true", /* C_true = 2816 */ colon }}}, /* CENTRY "true" true 4 h 2824 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2832 */
	{.type Absolute, {.p -1}},		/* dd -1 2840 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2848 */
	{.type Header, {.hdr { 2, "bl", /* C_bl = 2864 */ colon }}}, /* CENTRY "bl" bl 2 h 2872 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2880 */
	{.type Absolute, {.p 32}},		/* dd 32 2888 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2896 */
	{.type Header, {.hdr { 2, "on", /* C_on = 2912 */ colon }}}, /* CENTRY "on" on 2 ; ( a -- ) (G stores -1 at a ) h 2920 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2928 */
	{.type Absolute, {.p -1}},		/* dd -1 2936 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 2944 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 2952 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 2960 */
	{.type Header, {.hdr { 3, "off", /* C_off = 2976 */ colon }}}, /* CENTRY "off" off 3 ; ( a -- ) (G stores 0 at a ) h 2984 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 2992 */
	{.type Absolute, {.p 0}},		/* dd 0 3000 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3008 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 3016 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3024 */
	{.type Header, {.hdr { 5, ">body", /* C_tobody = 3040 */ colon }}}, /* CENTRY ">body" tobody 5 h 3048 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3056 */
	{.type Absolute, {.p 8}},		/* dd 8 3064 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3072 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3080 */
	{.type Header, {.hdr { 7, "aligned", /* C_aligned = 3096 */ colon }}}, /* CENTRY "aligned" aligned 7 ; align a number to a multiple of 8 h 3104 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3112 */
	{.type Absolute, {.p 7}},		/* dd 7 3120 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3128 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3136 */
	{.type Absolute, {.p -8}},		/* dd -8 3144 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 3152 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3160 */
	{.type Header, {.hdr { 5, "cells", /* C_cells = 3176 */ colon }}}, /* CENTRY "cells" cells 5 h 3184 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3192 */
	{.type Absolute, {.p 3}},		/* dd 3			; (index << 2) -> (index << 3) for amd64 3200 */
	{.type FromDictionary, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 3208 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3216 */
	{.type Header, {.hdr { 6, "cells+", /* C_cells_plus = 3232 */ colon }}}, /* CENTRY "cells+" cells_plus 6 ; ( n1 n2 -- n1+(n2*cellsize) ) h 3240 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 3248 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3256 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3264 */
	{.type Header, {.hdr { 5, "cell+", /* C_cell_plus = 3280 */ colon }}}, /* CENTRY "cell+" cell_plus 5 h 3288 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3296 */
	{.type Absolute, {.p 1}},		/* dd 1 3304 */
	{.type FromDictionary, {.p C_cells_plus}, .src = "dd C_cells_plus"},		/* dd C_cells_plus 3312 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3320 */
	{.type Header, {.hdr { 5, "depth", /* C_depth = 3336 */ colon }}}, /* CENTRY "depth" depth 5 h 3344 */
	{.type FromDictionary, {.p MV_S0}, .src = "dd MV_S0"},		/* dd MV_S0 3352 */
	{.type FromDictionary, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 3360 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3368 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3376 */
	{.type Absolute, {.p 3}},		/* dd 3 3384 */
	{.type FromDictionary, {.p M_rshift}, .src = "dd M_rshift"},		/* dd M_rshift 3392 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3400 */
	{.type Absolute, {.p 1}},		/* dd 1 3408 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 3416 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3424 */
	{.type Header, {.hdr { 3, "nip", /* C_nip = 3440 */ colon }}}, /* CENTRY "nip" nip 3 h 3448 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3456 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3464 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3472 */
	{.type Header, {.hdr { 3, "rot", /* C_rot = 3488 */ colon }}}, /* CENTRY "rot" rot 3 h 3496 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3504 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3512 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3520 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 3528 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3536 */
	{.type Header, {.hdr { 5, "2drop", /* C_2drop = 3552 */ colon }}}, /* CENTRY "2drop" 2drop 5 h 3560 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3568 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 3576 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3584 */
	{.type Header, {.hdr { 4, "2dup", /* C_2dup = 3600 */ colon }}}, /* CENTRY "2dup" 2dup 4 h 3608 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3616 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 3624 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3632 */
	{.type Header, {.hdr { 4, "2nip", /* C_2nip = 3648 */ colon }}}, /* CENTRY "2nip" 2nip 4 h 3656 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3664 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 3672 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3680 */
	{.type Header, {.hdr { 5, "2swap", /* C_2swap = 3696 */ colon }}}, /* CENTRY "2swap" 2swap 5 h 3704 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3712 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 3720 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 3728 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 3736 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3744 */
	{.type Header, {.hdr { 4, "?dup", /* C_qdup = 3760 */ colon }}}, /* CENTRY "?dup" qdup 4 ; if (n != 0) ( n -- n n) else ( n -- n ) h 3768 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( n -- n n )"},		/* dd M_dup	; ( n -- n n ) 3776 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( n n -- n n n )"},		/* dd M_dup	; ( n n -- n n n ) 3784 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3792 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( n n n -- n n n 0 ) 3800 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal	; ( n n n 0 -- n n f )"},		/* dd M_equal	; ( n n n 0 -- n n f ) 3808 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump	; ( n n f -- n n )"},		/* dd M_cjump	; ( n n f -- n n ) 3816 */
	{.type FromDictionary, {.p L_C_qdup}, .src = "dd L_C_qdup	; when n != 0, go to L20"},		/* dd L_C_qdup	; when n != 0, go to L20 3824 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; when n == 0 ( n n -- n)"},		/* dd M_drop	; when n == 0 ( n n -- n) 3832 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3840 */
	{.type Header, {.hdr { 4, "pick", /* C_pick = 3856 */ colon }}}, /* CENTRY "pick" pick 4 h 3864 */
	{.type FromDictionary, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 3872 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 3880 */
	{.type FromDictionary, {.p L_C_pick}, .src = "dd L_C_pick"},		/* dd L_C_pick 3888 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 3896 */
	{.type Absolute, {.p 1}},		/* dd 1 3904 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3912 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 3920 */
	{.type FromDictionary, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 3928 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 3936 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 3944 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 3952 */
	{.type FromDictionary, {.p L_C_pick_1}, .src = "dd L_C_pick_1"},		/* dd L_C_pick_1 3960 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 3968 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 3976 */
	{.type Header, {.hdr { 4, "tuck", /* C_tuck = 3992 */ colon }}}, /* CENTRY "tuck" tuck 4 h 4000 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4008 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 4016 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 4024 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 4032 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4040 */
	{.type Header, {.hdr { 1, "/", /* C_divides = 4056 */ colon }}}, /* CENTRY "/" divides 1 h 4064 */
	{.type FromDictionary, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 4072 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4080 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4088 */
	{.type Header, {.hdr { 2, "+!", /* C_plusstore = 4104 */ colon }}}, /* CENTRY "+!" plusstore 2 ; ( n 'a -- ) a@ = a@+n h 4112 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 4120 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 4128 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot"},		/* dd C_rot 4136 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 4144 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 4152 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 4160 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4168 */
	{.type Header, {.hdr { 6, "invert", /* C_invert = 4184 */ colon }}}, /* CENTRY "invert" invert 6 h 4192 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4200 */
	{.type Absolute, {.p -1}},		/* dd -1 4208 */
	{.type FromDictionary, {.p M_binxor}, .src = "dd M_binxor"},		/* dd M_binxor 4216 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4224 */
	{.type Header, {.hdr { 3, "mod", /* C_mod = 4240 */ colon }}}, /* CENTRY "mod" mod 3 h 4248 */
	{.type FromDictionary, {.p M_slashmod}, .src = "dd M_slashmod"},		/* dd M_slashmod 4256 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4264 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4272 */
	{.type Header, {.hdr { 2, "1+", /* C_1plus = 4288 */ colon }}}, /* CENTRY "1+" 1plus 2 h 4296 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4304 */
	{.type Absolute, {.p 1}},		/* dd 1 4312 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 4320 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4328 */
	{.type Header, {.hdr { 2, "1-", /* C_1minus = 4344 */ colon }}}, /* CENTRY "1-" 1minus 2 h 4352 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4360 */
	{.type Absolute, {.p 1}},		/* dd 1 4368 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 4376 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4384 */
	{.type Header, {.hdr { 6, "negate", /* C_negate = 4400 */ colon }}}, /* CENTRY "negate" negate 6 h 4408 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4416 */
	{.type Absolute, {.p 0}},		/* dd 0 4424 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 4432 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 4440 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4448 */
	{.type Header, {.hdr { 2, "2*", /* C_2multiplies = 4464 */ colon }}}, /* CENTRY "2*" 2multiplies 2 h 4472 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4480 */
	{.type Absolute, {.p 1}},		/* dd 1 4488 */
	{.type FromDictionary, {.p M_lshift}, .src = "dd M_lshift"},		/* dd M_lshift 4496 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4504 */
	{.type Header, {.hdr { 2, "2/", /* C_2divides = 4520 */ colon }}}, /* CENTRY "2/" 2divides 2 h 4528 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4536 */
	{.type Absolute, {.p 1}},		/* dd 1 4544 */
	{.type FromDictionary, {.p M_rshifta}, .src = "dd M_rshifta"},		/* dd M_rshifta 4552 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4560 */
	{.type Header, {.hdr { 2, "0=", /* C_0eq = 4576 */ colon }}}, /* CENTRY "0=" 0eq 2 h 4584 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4592 */
	{.type Absolute, {.p 0}},		/* dd 0 4600 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4608 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4616 */
	{.type Header, {.hdr { 2, "0<", /* C_0lt = 4632 */ colon }}}, /* CENTRY "0<" 0lt 2 h 4640 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4648 */
	{.type Absolute, {.p 0}},		/* dd 0 4656 */
	{.type FromDictionary, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4664 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4672 */
	{.type Header, {.hdr { 2, "0>", /* C_0gt = 4688 */ colon }}}, /* CENTRY "0>" 0gt 2 h 4696 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4704 */
	{.type Absolute, {.p 0}},		/* dd 0 4712 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4720 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4728 */
	{.type Header, {.hdr { 2, "<>", /* C_neq = 4744 */ colon }}}, /* CENTRY "<>" neq 2 h 4752 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 4760 */
	{.type FromDictionary, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 4768 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4776 */
	{.type Header, {.hdr { 3, "0<>", /* C_0neq = 4792 */ colon }}}, /* CENTRY "0<>" 0neq 3 h 4800 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 4808 */
	{.type Absolute, {.p 0}},		/* dd 0 4816 */
	{.type FromDictionary, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 4824 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4832 */
	{.type Header, {.hdr { 3, "max", /* C_max = 4848 */ colon }}}, /* CENTRY "max" max 3 h 4856 */
	{.type FromDictionary, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4864 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 4872 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4880 */
	{.type FromDictionary, {.p L_C_max}, .src = "dd L_C_max"},		/* dd L_C_max 4888 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4896 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 4904 */
	{.type FromDictionary, {.p L_C_max_1}, .src = "dd L_C_max_1"},		/* dd L_C_max_1 4912 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 4920 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 4928 */
	{.type Header, {.hdr { 3, "min", /* C_min = 4944 */ colon }}}, /* CENTRY "min" min 3 h 4952 */
	{.type FromDictionary, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 4960 */
	{.type FromDictionary, {.p M_less}, .src = "dd M_less"},		/* dd M_less 4968 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 4976 */
	{.type FromDictionary, {.p L_C_min}, .src = "dd L_C_min"},		/* dd L_C_min 4984 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 4992 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5000 */
	{.type FromDictionary, {.p L_C_min_1}, .src = "dd L_C_min_1"},		/* dd L_C_min_1 5008 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 5016 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5024 */
	{.type Header, {.hdr { 6, "signum", /* C_signum = 5040 */ colon }}}, /* CENTRY "signum" signum 6 h 5048 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 5056 */
	{.type FromDictionary, {.p C_0gt}, .src = "dd C_0gt"},		/* dd C_0gt 5064 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5072 */
	{.type FromDictionary, {.p L_C_signum}, .src = "dd L_C_signum"},		/* dd L_C_signum 5080 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 5088 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5096 */
	{.type Absolute, {.p 1}},		/* dd 1 5104 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5112 */
	{.type FromDictionary, {.p L_C_signum_1}, .src = "dd L_C_signum_1"},		/* dd L_C_signum_1 5120 */
	{.type FromDictionary, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 5128 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5136 */
	{.type FromDictionary, {.p L_C_signum_2}, .src = "dd L_C_signum_2"},		/* dd L_C_signum_2 5144 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5152 */
	{.type Absolute, {.p -1}},		/* dd -1 5160 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5168 */
	{.type FromDictionary, {.p L_C_signum_3}, .src = "dd L_C_signum_3"},		/* dd L_C_signum_3 5176 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5184 */
	{.type Absolute, {.p 0}},		/* dd 0 5192 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5200 */
	{.type Header, {.hdr { 6, "within", /* C_within = 5216 */ colon }}}, /* CENTRY "within" within 6 h 5224 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 5232 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5240 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 5248 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 5256 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 5264 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5272 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 5280 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 5288 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 5296 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5304 */
	{.type Header, {.hdr { 3, "abs", /* C_abs = 5320 */ colon }}}, /* CENTRY "abs" abs 3 h 5328 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 5336 */
	{.type FromDictionary, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 5344 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5352 */
	{.type FromDictionary, {.p L_C_abs}, .src = "dd L_C_abs"},		/* dd L_C_abs 5360 */
	{.type FromDictionary, {.p C_negate}, .src = "dd C_negate"},		/* dd C_negate 5368 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5376 */
	{.type Header, {.hdr { 4, "emit", /* C_emit = 5392 */ colon }}}, /* CENTRY "emit" emit 4 ; ( character -- ) h 5400 */
	{.type FromDictionary, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5408 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore	; variable iobuf has character"},		/* dd M_cstore	; variable iobuf has character 5416 */
	{.type FromDictionary, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 5424 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch		; outfd"},		/* dd M_fetch		; outfd 5432 */
	{.type FromDictionary, {.p MV_Iobuf}, .src = "dd MV_Iobuf		; variable iobuf address"},		/* dd MV_Iobuf		; variable iobuf address 5440 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5448 */
	{.type Absolute, {.p 1}},		/* dd 1			; ( outfd iobuf 1 ) 5456 */
	{.type FromDictionary, {.p M_syswrite}, .src = "dd M_syswrite	; ( 1 iobuf outfd --  )"},		/* dd M_syswrite	; ( 1 iobuf outfd --  ) 5464 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5472 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5480 */
	{.type Header, {.hdr { 4, "type", /* C_type = 5496 */ colon }}}, /* CENTRY "type" type 4 ; ( addr n -- ) h 5504 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush		; ( addr ) (R n )"},		/* dd M_rpush		; ( addr ) (R n ) 5512 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush		; ( ) (R n addr )"},		/* dd M_rpush		; ( ) (R n addr ) 5520 */
	{.type FromDictionary, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 5528 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch		; ( outfd )"},		/* dd M_fetch		; ( outfd ) 5536 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop		; ( outfd addr ) (R n )"},		/* dd M_rpop		; ( outfd addr ) (R n ) 5544 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop		; ( outfd addr n ) (R )"},		/* dd M_rpop		; ( outfd addr n ) (R ) 5552 */
	{.type FromDictionary, {.p M_syswrite}, .src = "dd M_syswrite	; ( 1 addr n --  )"},		/* dd M_syswrite	; ( 1 addr n --  ) 5560 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 5568 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5576 */
	{.type Header, {.hdr { 2, "cr", /* C_cr = 5592 */ colon }}}, /* CENTRY "cr" cr 2 h 5600 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 5608 */
	{.type Absolute, {.p 10}},		/* dd 10			; ascii value of carriage return 5616 */
	{.type FromDictionary, {.p C_emit}, .src = "dd C_emit			; emit"},		/* dd C_emit			; emit 5624 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5632 */
	{.type Header, {.hdr { 5, "space", /* C_space = 5648 */ colon }}}, /* CENTRY "space" space 5 h 5656 */
	{.type FromDictionary, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5664 */
	{.type FromDictionary, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5672 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5680 */
	{.type Header, {.hdr { 5, "emits", /* C_emits = 5696 */ colon }}}, /* CENTRY "emits" emits 5 h 5704 */
	{.type FromDictionary, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 5712 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 5720 */
	{.type FromDictionary, {.p L_C_emits_1}, .src = "dd L_C_emits_1"},		/* dd L_C_emits_1 5728 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 5736 */
	{.type FromDictionary, {.p C_emit}, .src = "dd C_emit"},		/* dd C_emit 5744 */
	{.type FromDictionary, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5752 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 5760 */
	{.type FromDictionary, {.p L_C_emits}, .src = "dd L_C_emits"},		/* dd L_C_emits 5768 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 5776 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5784 */
	{.type Header, {.hdr { 6, "spaces", /* C_spaces = 5800 */ colon }}}, /* CENTRY "spaces" spaces 6 h 5808 */
	{.type FromDictionary, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 5816 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 5824 */
	{.type FromDictionary, {.p C_emits}, .src = "dd C_emits"},		/* dd C_emits 5832 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5840 */
	{.type Header, {.hdr { 5, "count", /* C_count = 5856 */ colon }}}, /* CENTRY "count" count 5 ; ( 'counted-string -- 'text count ) a = address of counted string ( a - a+1 a[0]) h 5864 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 5872 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 5880 */
	{.type FromDictionary, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 5888 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 5896 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 5904 */
	{.type FromDictionary, {.p C_2dup}, .src = "dd C_2dup ; debug show the word name to search"},		/* dd C_2dup ; debug show the word name to search 5912 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5920 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 5928 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush ; debug show the dictionary entry"},		/* dd M_rpush ; debug show the dictionary entry 5936 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 5944 */
	{.type FromDictionary, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 5952 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 5960 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5968 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 5976 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 5984 */
	{.type Header, {.hdr { 7, "compare", /* C_compare = 6000 */ colon }}}, /* CENTRY "compare" compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search h 6008 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 )"},		/* dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 6016 */
	{.type FromDictionary, {.p C_2dup}, .src = "dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 )"},		/* dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 ) 6024 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- ) 6032 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- )"},		/* dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- ) 6040 */
	{.type FromDictionary, {.p C_min}, .src = "dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- )"},		/* dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- ) 6048 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6056 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- ) 6064 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- )"},		/* dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- ) 6072 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6080 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6088 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6096 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 6104 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6112 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6120 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6128 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 6136 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6144 */
	{.type FromDictionary, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 6152 */
	{.type FromDictionary, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 6160 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 6168 */
	{.type FromDictionary, {.p L_C_compare_1}, .src = "dd L_C_compare_1		; matches"},		/* dd L_C_compare_1		; matches 6176 */
	{.type FromDictionary, {.p C_2nip}, .src = "dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- )"},		/* dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- ) 6184 */
	{.type FromDictionary, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2)"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2) 6192 */
	{.type FromDictionary, {.p M_unloop}, .src = "dd M_unloop	; ( f -- f ) (R n1 n2 -- )"},		/* dd M_unloop	; ( f -- f ) (R n1 n2 -- ) 6200 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6208 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6216 */
	{.type FromDictionary, {.p L_C_compare}, .src = "dd L_C_compare"},		/* dd L_C_compare 6224 */
	{.type FromDictionary, {.p C_2drop}, .src = "dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- )"},		/* dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- ) 6232 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6240 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( n2 n1 -- ) (R -- )"},		/* dd M_rpop	; ( n2 n1 -- ) (R -- ) 6248 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus	; ( -- n1-n2 )"},		/* dd M_minus	; ( -- n1-n2 ) 6256 */
	{.type FromDictionary, {.p C_signum}, .src = "dd C_signum"},		/* dd C_signum 6264 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6272 */
	{.type Header, {.hdr { 5, "erase", /* C_erase = 6288 */ colon }}}, /* CENTRY "erase" erase 5 h 6296 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6304 */
	{.type Absolute, {.p 0}},		/* dd 0 6312 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6320 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6328 */
	{.type Absolute, {.p 0}},		/* dd 0 6336 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6344 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6352 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 6360 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6368 */
	{.type FromDictionary, {.p L_C_erase}, .src = "dd L_C_erase"},		/* dd L_C_erase 6376 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6384 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6392 */
	{.type Header, {.hdr { 4, "fill", /* C_fill = 6408 */ colon }}}, /* CENTRY "fill" fill 4 h 6416 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6424 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6432 */
	{.type Absolute, {.p 0}},		/* dd 0 6440 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6448 */
	{.type FromDictionary, {.p C_2dup}, .src = "dd C_2dup"},		/* dd C_2dup 6456 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6464 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6472 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6480 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 6488 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6496 */
	{.type FromDictionary, {.p L_C_fill}, .src = "dd L_C_fill"},		/* dd L_C_fill 6504 */
	{.type FromDictionary, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 6512 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6520 */
	{.type Header, {.hdr { 5, "blank", /* C_blank = 6536 */ colon }}}, /* CENTRY "blank" blank 5 h 6544 */
	{.type FromDictionary, {.p C_bl}, .src = "dd C_bl"},		/* dd C_bl 6552 */
	{.type FromDictionary, {.p C_fill}, .src = "dd C_fill"},		/* dd C_fill 6560 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6568 */
	{.type Header, {.hdr { 6, "search", /* C_search = 6584 */ colon }}}, /* CENTRY "search" search 6 h 6592 */
	{.type FromDictionary, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6600 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 6608 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6616 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 6624 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 6632 */
	{.type FromDictionary, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6640 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6648 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6656 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 6664 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 6672 */
	{.type Absolute, {.p 0}},		/* dd 0 6680 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 6688 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6696 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6704 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6712 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 6720 */
	{.type FromDictionary, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6728 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6736 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6744 */
	{.type FromDictionary, {.p MV_Searchlen}, .src = "dd MV_Searchlen"},		/* dd MV_Searchlen 6752 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6760 */
	{.type FromDictionary, {.p C_compare}, .src = "dd C_compare"},		/* dd C_compare 6768 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 6776 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 6784 */
	{.type FromDictionary, {.p L_C_search_1}, .src = "dd L_C_search_1"},		/* dd L_C_search_1 6792 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6800 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6808 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 6816 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 6824 */
	{.type FromDictionary, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 6832 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6840 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 6848 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 6856 */
	{.type FromDictionary, {.p C_true}, .src = "dd C_true"},		/* dd C_true 6864 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6872 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 6880 */
	{.type FromDictionary, {.p L_C_search}, .src = "dd L_C_search"},		/* dd L_C_search 6888 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 6896 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 6904 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false"},		/* dd C_false 6912 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6920 */
	{.type Header, {.hdr { 4, "here", /* C_here = 6936 */ colon }}}, /* CENTRY "here" here 4 h 6944 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 6952 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 6960 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 6968 */
	{.type Header, {.hdr { 5, "there", /* C_there = 6984 */ colon }}}, /* CENTRY "there" there 5 ; variable here h 6992 */
	{.type FromDictionary, {.p MV_Vp}, .src = "dd MV_Vp"},		/* dd MV_Vp 7000 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7008 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7016 */
	{.type Header, {.hdr { 1, ",", /* C_comma = 7032 */ colon }}}, /* CENTRY "," comma 1 h 7040 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 7048 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7056 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7064 */
	{.type Absolute, {.p 8}},		/* dd 8 7072 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 7080 */
	{.type FromDictionary, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 7088 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7096 */
	{.type Header, {.hdr { 2, "c,", /* C_c = 7112 */ colon }}}, /* CENTRY "c," c 2 h 7120 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 7128 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7136 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7144 */
	{.type Absolute, {.p 1}},		/* dd 1 7152 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 7160 */
	{.type FromDictionary, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 7168 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7176 */
	{.type Header, {.hdr { 5, "allot", /* C_allot = 7192 */ colon }}}, /* CENTRY "allot" allot 5 ; ( n -- ) here = here+n h 7200 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 7208 */
	{.type FromDictionary, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 7216 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7224 */
	{.type Header, {.hdr { 6, "vallot", /* C_vallot = 7240 */ colon }}}, /* CENTRY "vallot" vallot 6 ; allot on the variable space ( n -- ) there = there+n h 7248 */
	{.type FromDictionary, {.p MV_Vp}, .src = "dd MV_Vp"},		/* dd MV_Vp 7256 */
	{.type FromDictionary, {.p C_plusstore}, .src = "dd C_plusstore"},		/* dd C_plusstore 7264 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7272 */
	{.type Header, {.hdr { 3, "pad", /* C_pad = 7288 */ colon }}}, /* CENTRY "pad" pad 3 h 7296 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 7304 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7312 */
	{.type Absolute, {.p 256}},		/* dd 256 7320 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7328 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7336 */
	{.type Header, {.hdr { 5, "align", /* C_align = 7352 */ colon }}}, /* CENTRY "align" align 5 ; ( -- ) align here to a cell boundary h 7360 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here		; Dp @"},		/* dd C_here		; Dp @ 7368 */
	{.type FromDictionary, {.p C_aligned}, .src = "dd C_aligned	; here is aligned to a multiple of 8"},		/* dd C_aligned	; here is aligned to a multiple of 8 7376 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp			; store the aligned here at Dp"},		/* dd MV_Dp			; store the aligned here at Dp 7384 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store		; Dp contains aligned_here"},		/* dd M_store		; Dp contains aligned_here 7392 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7400 */
	{.type Header, {.hdr { 6, "unused", /* C_unused = 7416 */ colon }}}, /* CENTRY "unused" unused 6 h 7424 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 7432 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7440 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 7448 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7456 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7464 */
	{.type Header, {.hdr { 2, "<#", /* C_fromhash = 7480 */ colon }}}, /* CENTRY "<#" fromhash 2 h 7488 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7496 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7504 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7512 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7520 */
	{.type FromDictionary, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7528 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7536 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7544 */
	{.type Header, {.hdr { 1, "#", /* C_hash = 7560 */ colon }}}, /* CENTRY "#" hash 1 h 7568 */
	{.type FromDictionary, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 7576 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7584 */
	{.type FromDictionary, {.p M_uslashmod}, .src = "dd M_uslashmod"},		/* dd M_uslashmod 7592 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7600 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7608 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7616 */
	{.type Absolute, {.p 9}},		/* dd 9 7624 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 7632 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7640 */
	{.type FromDictionary, {.p L_C_hash}, .src = "dd L_C_hash"},		/* dd L_C_hash 7648 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7656 */
	{.type Absolute, {.p 97}},		/* dd 97 7664 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7672 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7680 */
	{.type Absolute, {.p 10}},		/* dd 10 7688 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7696 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7704 */
	{.type FromDictionary, {.p L_C_hash_1}, .src = "dd L_C_hash_1"},		/* dd L_C_hash_1 7712 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7720 */
	{.type Absolute, {.p 48}},		/* dd 48 7728 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7736 */
	{.type FromDictionary, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7744 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7752 */
	{.type FromDictionary, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 7760 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7768 */
	{.type FromDictionary, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7776 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 7784 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 7792 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7800 */
	{.type Header, {.hdr { 2, "#s", /* C_hashs = 7816 */ colon }}}, /* CENTRY "#s" hashs 2 h 7824 */
	{.type FromDictionary, {.p C_hash}, .src = "dd C_hash"},		/* dd C_hash 7832 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7840 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 7848 */
	{.type FromDictionary, {.p L_C_hashs_1}, .src = "dd L_C_hashs_1"},		/* dd L_C_hashs_1 7856 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 7864 */
	{.type FromDictionary, {.p L_C_hashs}, .src = "dd L_C_hashs"},		/* dd L_C_hashs 7872 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7880 */
	{.type Header, {.hdr { 2, "#>", /* C_hashfrom = 7896 */ colon }}}, /* CENTRY "#>" hashfrom 2 h 7904 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 7912 */
	{.type FromDictionary, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 7920 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 7928 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 7936 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 7944 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 7952 */
	{.type Absolute, {.p 1024}},		/* dd 1024 7960 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 7968 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 7976 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 7984 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 7992 */
	{.type Header, {.hdr { 4, "hold", /* C_hold = 8008 */ colon }}}, /* CENTRY "hold" hold 4 h 8016 */
	{.type FromDictionary, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 8024 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 8032 */
	{.type FromDictionary, {.p C_1minus}, .src = "dd C_1minus"},		/* dd C_1minus 8040 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8048 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 8056 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 8064 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 8072 */
	{.type FromDictionary, {.p MV_toNum}, .src = "dd MV_toNum"},		/* dd MV_toNum 8080 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8088 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8096 */
	{.type Header, {.hdr { 4, "sign", /* C_sign = 8112 */ colon }}}, /* CENTRY "sign" sign 4 h 8120 */
	{.type FromDictionary, {.p C_0lt}, .src = "dd C_0lt"},		/* dd C_0lt 8128 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8136 */
	{.type FromDictionary, {.p L_C_sign}, .src = "dd L_C_sign"},		/* dd L_C_sign 8144 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8152 */
	{.type Absolute, {.p 45}},		/* dd 45 8160 */
	{.type FromDictionary, {.p C_hold}, .src = "dd C_hold"},		/* dd C_hold 8168 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8176 */
	{.type Header, {.hdr { 3, "(.)", /* C_paren_dot_paren = 8192 */ colon }}}, /* CENTRY "(.)" paren_dot_paren 3 ; convert the top of stack to a string ( n1 -- 'text n2 ) h 8200 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup		; ( n -- n n )"},		/* dd M_dup		; ( n -- n n ) 8208 */
	{.type FromDictionary, {.p C_abs}, .src = "dd C_abs		; ( n n -- n u )"},		/* dd C_abs		; ( n n -- n u ) 8216 */
	{.type FromDictionary, {.p C_fromhash}, .src = "dd C_fromhash	; pad = h+256; >num = pad+1024"},		/* dd C_fromhash	; pad = h+256; >num = pad+1024 8224 */
	{.type FromDictionary, {.p C_hashs}, .src = "dd C_hashs		; ( n u1 -- n n2 )"},		/* dd C_hashs		; ( n u1 -- n n2 ) 8232 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap		; ( n n2 -- n2 n )"},		/* dd M_xswap		; ( n n2 -- n2 n ) 8240 */
	{.type FromDictionary, {.p C_sign}, .src = "dd C_sign		; ( n2 n -- n2 )"},		/* dd C_sign		; ( n2 n -- n2 ) 8248 */
	{.type FromDictionary, {.p C_hashfrom}, .src = "dd C_hashfrom	; ( u1 -- a n )"},		/* dd C_hashfrom	; ( u1 -- a n ) 8256 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8264 */
	{.type Header, {.hdr { 1, ".", /* C_dot = 8280 */ colon }}}, /* CENTRY "." dot 1 ; print the top of stack ( n -- ) h 8288 */
	{.type FromDictionary, {.p C_paren_dot_paren}, .src = "dd C_paren_dot_paren ; ( n1 -- 'text n2 )"},		/* dd C_paren_dot_paren ; ( n1 -- 'text n2 ) 8296 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 8304 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 8312 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8320 */
	{.type Header, {.hdr { 2, ".r", /* C_dotr = 8336 */ colon }}}, /* CENTRY ".r" dotr 2 h 8344 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 8352 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8360 */
	{.type FromDictionary, {.p C_abs}, .src = "dd C_abs"},		/* dd C_abs 8368 */
	{.type FromDictionary, {.p C_fromhash}, .src = "dd C_fromhash"},		/* dd C_fromhash 8376 */
	{.type FromDictionary, {.p C_hashs}, .src = "dd C_hashs"},		/* dd C_hashs 8384 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 8392 */
	{.type FromDictionary, {.p C_sign}, .src = "dd C_sign"},		/* dd C_sign 8400 */
	{.type FromDictionary, {.p C_hashfrom}, .src = "dd C_hashfrom"},		/* dd C_hashfrom 8408 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 8416 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 8424 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8432 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8440 */
	{.type Absolute, {.p 0}},		/* dd 0 8448 */
	{.type FromDictionary, {.p C_max}, .src = "dd C_max"},		/* dd C_max 8456 */
	{.type FromDictionary, {.p C_spaces}, .src = "dd C_spaces"},		/* dd C_spaces 8464 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 8472 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8480 */
	{.type Header, {.hdr { 3, "hex", /* C_hex = 8496 */ colon }}}, /* CENTRY "hex" hex 3 h 8504 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8512 */
	{.type Absolute, {.p 16}},		/* dd 16 8520 */
	{.type FromDictionary, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8528 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8536 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8544 */
	{.type Header, {.hdr { 7, "decimal", /* C_decimal = 8560 */ colon }}}, /* CENTRY "decimal" decimal 7 h 8568 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8576 */
	{.type Absolute, {.p 10}},		/* dd 10 8584 */
	{.type FromDictionary, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8592 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 8600 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8608 */
	{.type Header, {.hdr { 5, "digit", /* C_digit = 8624 */ colon }}}, /* CENTRY "digit" digit 5 ; ( c -- ) h 8632 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8640 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8648 */
	{.type Absolute, {.p 65}},		/* dd 65 8656 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8664 */
	{.type Absolute, {.p 91}},		/* dd 91 8672 */
	{.type FromDictionary, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8680 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8688 */
	{.type FromDictionary, {.p L_C_digit}, .src = "dd L_C_digit"},		/* dd L_C_digit 8696 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8704 */
	{.type Absolute, {.p 55}},		/* dd 55 8712 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8720 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8728 */
	{.type FromDictionary, {.p L_C_digit_1}, .src = "dd L_C_digit_1"},		/* dd L_C_digit_1 8736 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8744 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8752 */
	{.type Absolute, {.p 97}},		/* dd 97 8760 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8768 */
	{.type Absolute, {.p 123}},		/* dd 123 8776 */
	{.type FromDictionary, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8784 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8792 */
	{.type FromDictionary, {.p L_C_digit_2}, .src = "dd L_C_digit_2"},		/* dd L_C_digit_2 8800 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8808 */
	{.type Absolute, {.p 87}},		/* dd 87 8816 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8824 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8832 */
	{.type FromDictionary, {.p L_C_digit_3}, .src = "dd L_C_digit_3"},		/* dd L_C_digit_3 8840 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8848 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8856 */
	{.type Absolute, {.p 48}},		/* dd 48 8864 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8872 */
	{.type Absolute, {.p 58}},		/* dd 58 8880 */
	{.type FromDictionary, {.p C_within}, .src = "dd C_within"},		/* dd C_within 8888 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 8896 */
	{.type FromDictionary, {.p L_C_digit_4}, .src = "dd L_C_digit_4"},		/* dd L_C_digit_4 8904 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 8912 */
	{.type Absolute, {.p 48}},		/* dd 48 8920 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus"},		/* dd M_minus 8928 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 8936 */
	{.type FromDictionary, {.p L_C_digit_5}, .src = "dd L_C_digit_5"},		/* dd L_C_digit_5 8944 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 8952 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false"},		/* dd C_false 8960 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 8968 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 8976 */
	{.type FromDictionary, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 8984 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 8992 */
	{.type FromDictionary, {.p M_less}, .src = "dd M_less"},		/* dd M_less 9000 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9008 */
	{.type FromDictionary, {.p L_C_digit_6}, .src = "dd L_C_digit_6"},		/* dd L_C_digit_6 9016 */
	{.type FromDictionary, {.p C_true}, .src = "dd C_true"},		/* dd C_true 9024 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9032 */
	{.type FromDictionary, {.p L_C_digit_7}, .src = "dd L_C_digit_7"},		/* dd L_C_digit_7 9040 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9048 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false"},		/* dd C_false 9056 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9064 */
	{.type Header, {.hdr { 6, "number", /* C_number = 9080 */ colon }}}, /* CENTRY "number" number 6 ; ( a n1 -- n2 -1 | a n1 0 ) h 9088 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 -- n1 a )"},		/* dd M_xswap	; ( a n1 -- n1 a ) 9096 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( n1 a -- n1 a a )"},		/* dd M_dup	; ( n1 a -- n1 a a ) 9104 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( n1 a a -- n1 a c )"},		/* dd M_cfetch	; ( n1 a a -- n1 a c ) 9112 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9120 */
	{.type Absolute, {.p 45}},		/* dd 45		; ( n1 a c -- n1 a c - ) 9128 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal	; ( n1 a c -- n1 a f )"},		/* dd M_equal	; ( n1 a c -- n1 a f ) 9136 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump	; ( n1 a c -- n1 a )"},		/* dd M_cjump	; ( n1 a c -- n1 a ) 9144 */
	{.type FromDictionary, {.p L_C_number}, .src = "dd L_C_number		; c != -"},		/* dd L_C_number		; c != - 9152 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus	; c == - ( n1 a -- n1 a+1 )"},		/* dd C_1plus	; c == - ( n1 a -- n1 a+1 ) 9160 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 9168 */
	{.type FromDictionary, {.p C_1minus}, .src = "dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 )"},		/* dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 ) 9176 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9184 */
	{.type Absolute, {.p -1}},		/* dd -1		; ( a+1 n1-1 -- a+1 n1-1 -1 ) 9192 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1)"},		/* dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1) 9200 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9208 */
	{.type FromDictionary, {.p L_C_number_1}, .src = "dd L_C_number_1"},		/* dd L_C_number_1 9216 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( n1 a -- a n1)"},		/* dd M_xswap	; ( n1 a -- a n1) 9224 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9232 */
	{.type Absolute, {.p 1}},		/* dd 1 9240 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1)"},		/* dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1) 9248 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a n1 -- a n1 n1 ) (R nr)"},		/* dd M_dup	; ( a n1 -- a n1 n1 ) (R nr) 9256 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1)"},		/* dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1) 9264 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9272 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a n1 -- a n1 0) (R nr n1) 9280 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1)"},		/* dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1) 9288 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9296 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( a 0 n1 -- a 0 n1 0) (R nr n1) 9304 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1) 9312 */
	{.type FromDictionary, {.p MV_Base}, .src = "dd MV_Base"},		/* dd MV_Base 9320 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1) 9328 */
	{.type FromDictionary, {.p M_multiply}, .src = "dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1)"},		/* dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1) 9336 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1)"},		/* dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1) 9344 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1) 9352 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1)"},		/* dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1) 9360 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1)"},		/* dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1) 9368 */
	{.type FromDictionary, {.p C_digit}, .src = "dd C_digit"},		/* dd C_digit 9376 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 9384 */
	{.type FromDictionary, {.p L_C_number_3}, .src = "dd L_C_number_3"},		/* dd L_C_number_3 9392 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 9400 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 9408 */
	{.type FromDictionary, {.p L_C_number_4}, .src = "dd L_C_number_4"},		/* dd L_C_number_4 9416 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9424 */
	{.type FromDictionary, {.p M_unloop}, .src = "dd M_unloop"},		/* dd M_unloop 9432 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9440 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9448 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9456 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false"},		/* dd C_false 9464 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9472 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 9480 */
	{.type FromDictionary, {.p L_C_number_2}, .src = "dd L_C_number_2"},		/* dd L_C_number_2 9488 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9496 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 9504 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip"},		/* dd C_nip 9512 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 9520 */
	{.type FromDictionary, {.p M_multiply}, .src = "dd M_multiply"},		/* dd M_multiply 9528 */
	{.type FromDictionary, {.p C_true}, .src = "dd C_true"},		/* dd C_true 9536 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9544 */
	{.type Header, {.hdr { 5, "abort", /* C_abort = 9560 */ colon }}}, /* CENTRY "abort" abort 5 h 9568 */
	{.type FromDictionary, {.p MV_Abortvec}, .src = "dd MV_Abortvec"},		/* dd MV_Abortvec 9576 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9584 */
	{.type FromDictionary, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 9592 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9600 */
	{.type Header, {.hdr { 6, "source", /* C_source = 9616 */ colon }}}, /* CENTRY "source" source 6 h 9624 */
	{.type FromDictionary, {.p MV_Sourcebuf}, .src = "dd MV_Sourcebuf"},		/* dd MV_Sourcebuf 9632 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9640 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9648 */
	{.type Header, {.hdr { 8, "bufferfd!", /* C_bufferfd = 9672 */ colon }}}, /* CENTRY "bufferfd!" bufferfd 8 ; ( n -- 'fd ) fd = Bufferfds n + h 9680 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 9688 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 9696 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 9704 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9712 */
	{.type Header, {.hdr { 6, "Wordfd", /* C_Wordfd = 9728 */ colon }}}, /* CENTRY "Wordfd" Wordfd 6 ; ( -- 'fd ) h 9736 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9744 */
	{.type Absolute, {.p 0}},		/* dd 0 9752 */
	{.type FromDictionary, {.p C_bufferfd}, .src = "dd C_bufferfd"},		/* dd C_bufferfd 9760 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9768 */
	{.type Header, {.hdr { 6, "Linefd", /* C_Linefd = 9784 */ colon }}}, /* CENTRY "Linefd" Linefd 6 ; ( -- 'fd ) h 9792 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9800 */
	{.type Absolute, {.p 1}},		/* dd 1 9808 */
	{.type FromDictionary, {.p C_bufferfd}, .src = "dd C_bufferfd"},		/* dd C_bufferfd 9816 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9824 */
	{.type Header, {.hdr { 13, "Doublequotefd", /* C_Doublequotefd = 9848 */ colon }}}, /* CENTRY "Doublequotefd" Doublequotefd 13 ; ( -- 'fd ) h 9856 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9864 */
	{.type Absolute, {.p 2}},		/* dd 2 9872 */
	{.type FromDictionary, {.p C_bufferfd}, .src = "dd C_bufferfd"},		/* dd C_bufferfd 9880 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9888 */
	{.type Header, {.hdr { 12, "Closeparenfd", /* C_Closeparenfd = 9912 */ colon }}}, /* CENTRY "Closeparenfd" Closeparenfd 12 ; ( -- 'fd ) h 9920 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 9928 */
	{.type Absolute, {.p 3}},		/* dd 3 9936 */
	{.type FromDictionary, {.p C_bufferfd}, .src = "dd C_bufferfd"},		/* dd C_bufferfd 9944 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 9952 */
	{.type Header, {.hdr { 15, "bufferfilename!", /* C_bufferfilename_store = 9976 */ colon }}}, /* CENTRY "bufferfilename!" bufferfilename_store 15 ; ( 'text index -- ) store label h 9984 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 9992 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 10000 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 10008 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10016 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10024 */
	{.type Header, {.hdr { 7, ">word", /* C_toword = 10040 */ colon }}}, /* CENTRY ">word" toword 7 ; ( 'Bufferfds -- 'Wordfd ) h 10048 */
	{.type FromDictionary, {.p MC_WORDNUM}, .src = "dd MC_WORDNUM"},		/* dd MC_WORDNUM 10056 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 10064 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 10072 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10080 */
	{.type Header, {.hdr { 7, "wordfd@", /* C_wordfd_fetch = 10096 */ colon }}}, /* CENTRY "wordfd@" wordfd_fetch 7 h 10104 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10112 */
	{.type FromDictionary, {.p C_toword}, .src = "dd C_toword"},		/* dd C_toword 10120 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10128 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10136 */
	{.type Header, {.hdr { 7, "wordfd!", /* C_wordfd_store = 10152 */ colon }}}, /* CENTRY "wordfd!" wordfd_store 7 h 10160 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10168 */
	{.type FromDictionary, {.p C_toword}, .src = "dd C_toword"},		/* dd C_toword 10176 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10184 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10192 */
	{.type Header, {.hdr { 13, "wordfilename@", /* C_wordfilename_fetch = 10216 */ colon }}}, /* CENTRY "wordfilename@" wordfilename_fetch 13 h 10224 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10232 */
	{.type FromDictionary, {.p C_toword}, .src = "dd C_toword"},		/* dd C_toword 10240 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10248 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10256 */
	{.type Header, {.hdr { 13, "wordfilename!", /* C_wordfilename_store = 10280 */ colon }}}, /* CENTRY "wordfilename!" wordfilename_store 13 h 10288 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10296 */
	{.type FromDictionary, {.p C_toword}, .src = "dd C_toword"},		/* dd C_toword 10304 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10312 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10320 */
	{.type Header, {.hdr { 7, ">line", /* C_toline = 10336 */ colon }}}, /* CENTRY ">line" toline 7 ; ( 'Bufferfds -- 'Wordfd ) h 10344 */
	{.type FromDictionary, {.p MC_LINENUM}, .src = "dd MC_LINENUM"},		/* dd MC_LINENUM 10352 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 10360 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 10368 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10376 */
	{.type Header, {.hdr { 7, "linefd@", /* C_linefd_fetch = 10392 */ colon }}}, /* CENTRY "linefd@" linefd_fetch 7 h 10400 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10408 */
	{.type FromDictionary, {.p C_toline}, .src = "dd C_toline"},		/* dd C_toline 10416 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10424 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10432 */
	{.type Header, {.hdr { 7, "linefd!", /* C_linefd_store = 10448 */ colon }}}, /* CENTRY "linefd!" linefd_store 7 h 10456 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10464 */
	{.type FromDictionary, {.p C_toline}, .src = "dd C_toline"},		/* dd C_toline 10472 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10480 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10488 */
	{.type Header, {.hdr { 13, "linefilename@", /* C_linefilename_fetch = 10512 */ colon }}}, /* CENTRY "linefilename@" linefilename_fetch 13 h 10520 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10528 */
	{.type FromDictionary, {.p C_toline}, .src = "dd C_toline"},		/* dd C_toline 10536 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10544 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10552 */
	{.type Header, {.hdr { 13, "linefilename!", /* C_linefilename_store = 10576 */ colon }}}, /* CENTRY "linefilename!" linefilename_store 13 h 10584 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10592 */
	{.type FromDictionary, {.p C_toline}, .src = "dd C_toline"},		/* dd C_toline 10600 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10608 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10616 */
	{.type Header, {.hdr { 12, ">doublequote", /* C_todoublequote = 10640 */ colon }}}, /* CENTRY ">doublequote" todoublequote 12 ; ( 'Bufferfds -- 'Doublequotefd ) h 10648 */
	{.type FromDictionary, {.p MC_LINENUM}, .src = "dd MC_LINENUM"},		/* dd MC_LINENUM 10656 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 10664 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 10672 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10680 */
	{.type Header, {.hdr { 14, "doublequotefd@", /* C_doublequotefd_fetch = 10704 */ colon }}}, /* CENTRY "doublequotefd@" doublequotefd_fetch 14 h 10712 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10720 */
	{.type FromDictionary, {.p C_todoublequote}, .src = "dd C_todoublequote"},		/* dd C_todoublequote 10728 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10736 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10744 */
	{.type Header, {.hdr { 14, "doublequotefd!", /* C_doublequotefd_store = 10768 */ colon }}}, /* CENTRY "doublequotefd!" doublequotefd_store 14 h 10776 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10784 */
	{.type FromDictionary, {.p C_todoublequote}, .src = "dd C_todoublequote"},		/* dd C_todoublequote 10792 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10800 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10808 */
	{.type Header, {.hdr { 20, "doublequotefilename@", /* C_doublequotefilename_fetch = 10840 */ colon }}}, /* CENTRY "doublequotefilename@" doublequotefilename_fetch 20 h 10848 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10856 */
	{.type FromDictionary, {.p C_todoublequote}, .src = "dd C_todoublequote"},		/* dd C_todoublequote 10864 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 10872 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10880 */
	{.type Header, {.hdr { 20, "doublequotefilename!", /* C_doublequotefilename_store = 10912 */ colon }}}, /* CENTRY "doublequotefilename!" doublequotefilename_store 20 h 10920 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 10928 */
	{.type FromDictionary, {.p C_todoublequote}, .src = "dd C_todoublequote"},		/* dd C_todoublequote 10936 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 10944 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 10952 */
	{.type Header, {.hdr { 11, ">closeparen", /* C_tocloseparen = 10976 */ colon }}}, /* CENTRY ">closeparen" tocloseparen 11 ; ( 'Bufferfds -- 'Closeparenfd ) h 10984 */
	{.type FromDictionary, {.p MC_LINENUM}, .src = "dd MC_LINENUM"},		/* dd MC_LINENUM 10992 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 11000 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11008 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11016 */
	{.type Header, {.hdr { 13, "closeparenfd@", /* C_closeparenfd_fetch = 11040 */ colon }}}, /* CENTRY "closeparenfd@" closeparenfd_fetch 13 h 11048 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 11056 */
	{.type FromDictionary, {.p C_tocloseparen}, .src = "dd C_tocloseparen"},		/* dd C_tocloseparen 11064 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11072 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11080 */
	{.type Header, {.hdr { 13, "closeparenfd!", /* C_closeparenfd_store = 11104 */ colon }}}, /* CENTRY "closeparenfd!" closeparenfd_store 13 h 11112 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 11120 */
	{.type FromDictionary, {.p C_tocloseparen}, .src = "dd C_tocloseparen"},		/* dd C_tocloseparen 11128 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11136 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11144 */
	{.type Header, {.hdr { 19, "closeparenfilename@", /* C_closeparenfilename_fetch = 11176 */ colon }}}, /* CENTRY "closeparenfilename@" closeparenfilename_fetch 19 h 11184 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 11192 */
	{.type FromDictionary, {.p C_tocloseparen}, .src = "dd C_tocloseparen"},		/* dd C_tocloseparen 11200 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11208 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11216 */
	{.type Header, {.hdr { 19, "closeparenfilename!", /* C_closeparenfilename_store = 11248 */ colon }}}, /* CENTRY "closeparenfilename!" closeparenfilename_store 19 h 11256 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 11264 */
	{.type FromDictionary, {.p C_tocloseparen}, .src = "dd C_tocloseparen"},		/* dd C_tocloseparen 11272 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11280 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11288 */
/* ; stdinput : set all buffer fd's to -1, Infd = stdin *//* ; args : set all buffer fd's to -1, Infd = #p/<pid>/args *//* ; input@ : buffer fds and Infd -> stack *//* ; input! : stack -> buffer fds and Infd *//* ; -input : close all buffer fds and Infd, set buffer fds to -1 *//* ; buffer file names are setup in boot */	{.type Header, {.hdr { 8, "stdinput", /* C_stdinput = 11312 */ colon }}}, /* CENTRY "stdinput" stdinput 8 ; stream input from stdin into Text input buffer h 11320 */
	{.type FromDictionary, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 11328 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 11336 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11344 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 11352 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 11360 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11368 */
	{.type Absolute, {.p 0}},		/* dd 0 11376 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 11384 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11392 */
	{.type Absolute, {.p 1}},		/* dd 1 11400 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 11408 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11416 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 11424 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11432 */
	{.type Absolute, {.p -1}},		/* dd -1 11440 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 11448 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11456 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 11464 */
	{.type FromDictionary, {.p L_C_stdinput}, .src = "dd L_C_stdinput"},		/* dd L_C_stdinput 11472 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 11480 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11488 */
	{.type Header, {.hdr { 4, "args", /* C_args = 11504 */ colon }}}, /* CENTRY "args" args 4 ; stream input from #p/<pid>/args into Text input buffer h 11512 */
	{.type FromDictionary, {.p MV_Argsfilename}, .src = "dd MV_Argsfilename	; ( 'args_filename_counted_string ) filled by the starter"},		/* dd MV_Argsfilename	; ( 'args_filename_counted_string ) filled by the starter 11520 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 11528 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11536 */
	{.type Absolute, {.p 0}},		/* dd 0 11544 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 11552 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11560 */
	{.type FromDictionary, {.p L_C_args_read}, .src = "dd L_C_args_read"},		/* dd L_C_args_read 11568 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11576 */
	{.type FromDictionary, {.p MV_Argsfilename}, .src = "dd MV_Argsfilename"},		/* dd MV_Argsfilename 11584 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 11592 */
	{.type FromDictionary, {.p C_ro}, .src = "dd C_ro"},		/* dd C_ro 11600 */
	{.type FromDictionary, {.p C_open_file}, .src = "dd C_open_file"},		/* dd C_open_file 11608 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 11616 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 11624 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11632 */
	{.type FromDictionary, {.p C_interpret}, .src = "dd C_interpret"},		/* dd C_interpret 11640 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11648 */
	{.type Header, {.hdr { 4, "input@", /* C_input_fetch = 11664 */ colon }}}, /* CENTRY "input@" input_fetch 4 ; ( -- Bufferfds Infd #Buffers+1 ) save input stream onto the stack and replace the buffer fd's with -1 h 11672 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 11680 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 11688 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11696 */
	{.type Absolute, {.p 0}},		/* dd 0 11704 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 11712 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11720 */
	{.type Absolute, {.p 1}},		/* dd 1 11728 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 11736 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11744 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 11752 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11760 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( 'Bufferfd 'Bufferfd )"},		/* dd M_dup	; ( 'Bufferfd 'Bufferfd ) 11768 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11776 */
	{.type Absolute, {.p -1}},		/* dd -1 11784 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( 'Bufferfd -1 'Bufferfd )"},		/* dd M_xswap	; ( 'Bufferfd -1 'Bufferfd ) 11792 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; ( 'Bufferfd )"},		/* dd M_store	; ( 'Bufferfd ) 11800 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 11808 */
	{.type FromDictionary, {.p L_C_input_fetch}, .src = "dd L_C_input_fetch"},		/* dd L_C_input_fetch 11816 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 11824 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 11832 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 11840 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 11848 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11856 */
	{.type Absolute, {.p 1}},		/* dd 1 11864 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11872 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 11880 */
	{.type Header, {.hdr { 7, "input!", /* C_input_store = 11896 */ colon }}}, /* CENTRY "input!" input_store 7 ; ( <input>|empty -- ) ; restore input stream from the stack or stdinput h 11904 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup		; check if there is #Buffers+1 on the top of stack"},		/* dd M_dup		; check if there is #Buffers+1 on the top of stack 11912 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 11920 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 11928 */
	{.type Absolute, {.p 1}},		/* dd 1 11936 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 11944 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal	; is the top of stack == #Buffers+1"},		/* dd M_equal	; is the top of stack == #Buffers+1 11952 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 11960 */
	{.type FromDictionary, {.p L_C_input_store_1}, .src = "dd L_C_input_store_1	; top of stack <> #Buffers+1, there is no input stream on the stack, use the default input"},		/* dd L_C_input_store_1	; top of stack <> #Buffers+1, there is no input stream on the stack, use the default input 11968 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; drop the #Buffers+1 on the top of stack"},		/* dd M_drop	; drop the #Buffers+1 on the top of stack 11976 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 11984 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 11992 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 12000 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12008 */
	{.type Absolute, {.p 0}},		/* dd 0 12016 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 12024 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 12032 */
	{.type FromDictionary, {.p M_i}, .src = "dd M_i"},		/* dd M_i 12040 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 12048 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 12056 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 12064 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 12072 */
	{.type FromDictionary, {.p L_C_input_store}, .src = "dd L_C_input_store"},		/* dd L_C_input_store 12080 */
	{.type FromDictionary, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 12088 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off	; reset Eof back to 0"},		/* dd C_off	; reset Eof back to 0 12096 */
	{.type FromDictionary, {.p C_true}, .src = "dd C_true	; ( true )"},		/* dd C_true	; ( true ) 12104 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12112 */
	{.type FromDictionary, {.p C_stdinput}, .src = "dd C_stdinput	; no input stream on the stack, use default input from now"},		/* dd C_stdinput	; no input stream on the stack, use default input from now 12120 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false		; ( 0 )"},		/* dd C_false		; ( 0 ) 12128 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12136 */
/* ; closefds: close all buffer fds and Infd, set buffer fds and Infd to -1 */	{.type Header, {.hdr { 8, "-input", /* C_close_input = 12160 */ colon }}}, /* CENTRY "-input" close_input 8 ; ( <input>|empty -- ) ; restore input stream from the stack or stdinput h 12168 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 12176 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 12184 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12192 */
	{.type Absolute, {.p 0}},		/* dd 0 12200 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 12208 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12216 */
	{.type Absolute, {.p 1}},		/* dd 1 12224 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 12232 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 12240 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( 'Bufferfd 'Bufferfd )"},		/* dd M_dup	; ( 'Bufferfd 'Bufferfd ) 12248 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( 'Bufferfd fd )"},		/* dd M_fetch	; ( 'Bufferfd fd ) 12256 */
	{.type FromDictionary, {.p C_close_file}, .src = "dd C_close_file	; ( 'Bufferfd ioresult )"},		/* dd C_close_file	; ( 'Bufferfd ioresult ) 12264 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; ( 'Bufferfd )"},		/* dd M_drop	; ( 'Bufferfd ) 12272 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( 'Bufferfd 'Bufferfd )"},		/* dd M_dup	; ( 'Bufferfd 'Bufferfd ) 12280 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12288 */
	{.type Absolute, {.p -1}},		/* dd -1 12296 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( 'Bufferfd -1 'Bufferfd )"},		/* dd M_xswap	; ( 'Bufferfd -1 'Bufferfd ) 12304 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; ( 'Bufferfd )"},		/* dd M_store	; ( 'Bufferfd ) 12312 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 12320 */
	{.type FromDictionary, {.p L_C_close_input}, .src = "dd L_C_close_input"},		/* dd L_C_close_input 12328 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 12336 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12344 */
	{.type Absolute, {.p -1}},		/* dd -1 12352 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd	; ( -1 'Infd )"},		/* dd MV_Infd	; ( -1 'Infd ) 12360 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( -1 'Infd 'Infd )"},		/* dd M_dup	; ( -1 'Infd 'Infd ) 12368 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( -1 'Infd fd )"},		/* dd M_fetch	; ( -1 'Infd fd ) 12376 */
	{.type FromDictionary, {.p C_close_file}, .src = "dd C_close_file	; ( -1 'Infd ioresult )"},		/* dd C_close_file	; ( -1 'Infd ioresult ) 12384 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; ( -1 'Infd )"},		/* dd M_drop	; ( -1 'Infd ) 12392 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 12400 */
	{.type FromDictionary, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 12408 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off	; reset Eof back to 0"},		/* dd C_off	; reset Eof back to 0 12416 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12424 */
	{.type Header, {.hdr { 7, "-+input", /* C_restore_input = 12440 */ colon }}}, /* CENTRY "-+input" restore_input 7 ; ( <input> -- ) ; use the input stream on the stack or abort h 12448 */
	{.type FromDictionary, {.p C_close_input}, .src = "dd C_close_input"},		/* dd C_close_input 12456 */
	{.type FromDictionary, {.p C_input_store}, .src = "dd C_input_store"},		/* dd C_input_store 12464 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 12472 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 12480 */
	{.type FromDictionary, {.p L_restore_input}, .src = "dd L_restore_input	; input stream restored"},		/* dd L_restore_input	; input stream restored 12488 */
/* ; no input stream on the stack to restore, show error and abort */	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 12496 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12504 */
	{.type FromDictionary, {.p L137}, .src = "dd L137"},		/* dd L137 12512 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12520 */
	{.type Absolute, {.p 23}},		/* dd 23 12528 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 12536 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 12544 */
	{.type FromDictionary, {.p C_depth}, .src = "dd C_depth"},		/* dd C_depth 12552 */
	{.type FromDictionary, {.p C_dot}, .src = "dd C_dot"},		/* dd C_dot 12560 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 12568 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 12576 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12584 */
	{.type Header, {.hdr { 10, "buffername", /* C_buffername = 12608 */ colon }}}, /* CENTRY "buffername" buffername 10 ; ( index -- 'counted_string ) build the buffer fd's filename h 12616 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells	; ( index*cellsize ) number of bytes"},		/* dd C_cells	; ( index*cellsize ) number of bytes 12624 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 12632 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( index*cellsize+'Bufferfilenames ) address of the filename's counted string"},		/* dd M_plus	; ( index*cellsize+'Bufferfilenames ) address of the filename's counted string 12640 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( 'filename_counted_string )"},		/* dd M_fetch	; ( 'filename_counted_string ) 12648 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12656 */
	{.type FromDictionary, {.p L120}, .src = "dd L120		; address of the counted string 3#n/"},		/* dd L120		; address of the counted string 3#n/ 12664 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 12672 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12680 */
	{.type Absolute, {.p 4}},		/* dd 4 12688 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; pad has 3#n/"},		/* dd M_cmove	; pad has 3#n/ 12696 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 12704 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 12712 */
	{.type Absolute, {.p 4}},		/* dd 4 12720 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 'filename_counted_string pad+4 )"},		/* dd M_plus	; ( 'filename_counted_string pad+4 ) 12728 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( 'filename_counted_string pad+4 ) (R pad+4 )"},		/* dd M_rpush	; ( 'filename_counted_string pad+4 ) (R pad+4 ) 12736 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 12744 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 12752 */
	{.type FromDictionary, {.p C_paren_dot_paren}, .src = "dd C_paren_dot_paren ; ( 'filename_counted_string pad+4 'text fd_text_count ) ( R pad+4 )"},		/* dd C_paren_dot_paren ; ( 'filename_counted_string pad+4 'text fd_text_count ) ( R pad+4 ) 12760 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12768 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 12776 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 12784 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush ; ( 'filename_counted_string pad+4 'text fd_text_count ) ( R pad+4+fd_text_count )"},		/* dd M_rpush ; ( 'filename_counted_string pad+4 'text fd_text_count ) ( R pad+4+fd_text_count ) 12792 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; now, pad has #n/<infd> ( 'filename_counted_string ) ( R pad+4+fd_text_count )"},		/* dd M_cmove	; now, pad has #n/<infd> ( 'filename_counted_string ) ( R pad+4+fd_text_count ) 12800 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( 'filename_counted_string pad+4+fd_text_count )"},		/* dd M_rpop	; ( 'filename_counted_string pad+4+fd_text_count ) 12808 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over	; ( 'filename_counted_string pad+4+fd_text_count 'filename_counted_string )"},		/* dd M_over	; ( 'filename_counted_string pad+4+fd_text_count 'filename_counted_string ) 12816 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( 'filename_counted_string pad+4+fd_text_count filename_count )"},		/* dd M_cfetch	; ( 'filename_counted_string pad+4+fd_text_count filename_count ) 12824 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( 'filename_counted_string pad+4+fd_text_count ) (R filename_count )"},		/* dd M_rpush	; ( 'filename_counted_string pad+4+fd_text_count ) (R filename_count ) 12832 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12840 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( 'filename_counted_string pad+4+fd_text_count ) (R filename_count pad+4+fd_text_count )"},		/* dd M_rpush	; ( 'filename_counted_string pad+4+fd_text_count ) (R filename_count pad+4+fd_text_count ) 12848 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( pad+4+fd_text_count 'filename_counted_string ) (R filename_count pad+4+fd_text_count )"},		/* dd M_xswap	; ( pad+4+fd_text_count 'filename_counted_string ) (R filename_count pad+4+fd_text_count ) 12856 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count	; ( pad+4+fd_text_count 'filename count ) (R filename_count pad+4+fd_text_count )"},		/* dd C_count	; ( pad+4+fd_text_count 'filename count ) (R filename_count pad+4+fd_text_count ) 12864 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; now, pad has the whole filename ( ) (R filename_count pad+4+fd_text_count )"},		/* dd M_cmove	; now, pad has the whole filename ( ) (R filename_count pad+4+fd_text_count ) 12872 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 12880 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 12888 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( pad+4+fd_text_count+filename_count )"},		/* dd M_plus	; ( pad+4+fd_text_count+filename_count ) 12896 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 12904 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 12912 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus	; ( pad+4+fd_text_count+filename_count-pad-1 )"},		/* dd M_minus	; ( pad+4+fd_text_count+filename_count-pad-1 ) 12920 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 12928 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; Now, pad has a proper counted string"},		/* dd M_store	; Now, pad has a proper counted string 12936 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 12944 */
	{.type Header, {.hdr { 3, "get", /* C_get = 12960 */ colon }}}, /* CENTRY "get" get 3 ; ( index -- 'counted-string ) read from the indexed Fd in Bufferfds into Tib as a counted string h 12968 */
	{.type FromDictionary, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 12976 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off	; clear EOF flag"},		/* dd C_off	; clear EOF flag 12984 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 12992 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells	; ( index index*cellsize ) number of bytes"},		/* dd C_cells	; ( index index*cellsize ) number of bytes 13000 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 13008 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( index index*cellsize+'Bufferfds ) address of the filename's counted string"},		/* dd M_plus	; ( index index*cellsize+'Bufferfds ) address of the filename's counted string 13016 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( index fd )"},		/* dd M_fetch	; ( index fd ) 13024 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( index fd fd )"},		/* dd M_dup	; ( index fd fd ) 13032 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13040 */
	{.type Absolute, {.p -1}},		/* dd -1 13048 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 13056 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump	; if fd == -1 ( index fd )"},		/* dd M_cjump	; if fd == -1 ( index fd ) 13064 */
	{.type FromDictionary, {.p L_C_get}, .src = "dd L_C_get		; when not -1"},		/* dd L_C_get		; when not -1 13072 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; when fd == -1 ( index )"},		/* dd M_drop	; when fd == -1 ( index ) 13080 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13088 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 13096 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( index index ) (R index )"},		/* dd M_rpush	; ( index index ) (R index ) 13104 */
	{.type FromDictionary, {.p C_buffername}, .src = "dd C_buffername"},		/* dd C_buffername 13112 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count	; ( index 'filename-counted-string -- 'text count )"},		/* dd C_count	; ( index 'filename-counted-string -- 'text count ) 13120 */
	{.type FromDictionary, {.p C_ro}, .src = "dd C_ro"},		/* dd C_ro 13128 */
	{.type FromDictionary, {.p C_open_file}, .src = "dd C_open_file	; ( index fd ioresult )"},		/* dd C_open_file	; ( index fd ioresult ) 13136 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13144 */
	{.type FromDictionary, {.p L_C_get_store}, .src = "dd L_C_get_store"},		/* dd L_C_get_store 13152 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; ( index ) (R index ) returned false, could not open-file. write error message"},		/* dd M_drop	; ( index ) (R index ) returned false, could not open-file. write error message 13160 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13168 */
	{.type FromDictionary, {.p L140}, .src = "dd L140		; open error"},		/* dd L140		; open error 13176 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13184 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13192 */
	{.type FromDictionary, {.p C_emit}, .src = "dd C_emit	; show the index"},		/* dd C_emit	; show the index 13200 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 13208 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort	; abort on open error. How about terminate?"},		/* dd C_abort	; abort on open error. How about terminate? 13216 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( index fd fd )"},		/* dd M_dup	; ( index fd fd ) 13224 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( index fd fd index )"},		/* dd M_rpop	; ( index fd fd index ) 13232 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells	; ( index fd fd index*cellsize ) number of bytes"},		/* dd C_cells	; ( index fd fd index*cellsize ) number of bytes 13240 */
	{.type FromDictionary, {.p MV_Bufferfds}, .src = "dd MV_Bufferfds"},		/* dd MV_Bufferfds 13248 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( index fd fd index*cellsize+'Bufferfds ) address of the filename's counted string"},		/* dd M_plus	; ( index fd fd index*cellsize+'Bufferfds ) address of the filename's counted string 13256 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; ( index fd )"},		/* dd M_store	; ( index fd ) 13264 */
	{.type FromDictionary, {.p MV_Tib}, .src = "dd MV_Tib"},		/* dd MV_Tib 13272 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13280 */
	{.type Absolute, {.p 1}},		/* dd 1 13288 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; Tib 1 +"},		/* dd M_plus	; Tib 1 + 13296 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13304 */
	{.type Absolute, {.p 4095}},		/* dd 4095		; ( index fd Tib+1 4095 ) 13312 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot	; ( index Tib+1 4095 fd )"},		/* dd C_rot	; ( index Tib+1 4095 fd ) 13320 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 13328 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13336 */
	{.type Absolute, {.p -1}},		/* dd -1 13344 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 13352 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13360 */
	{.type FromDictionary, {.p L_C_get_1}, .src = "dd L_C_get_1"},		/* dd L_C_get_1 13368 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13376 */
	{.type FromDictionary, {.p L141}, .src = "dd L141		; read error"},		/* dd L141		; read error 13384 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 13392 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 13400 */
	{.type FromDictionary, {.p C_emit}, .src = "dd C_emit	; show the index"},		/* dd C_emit	; show the index 13408 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 13416 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort	; abort on read error. How about terminate?"},		/* dd C_abort	; abort on read error. How about terminate? 13424 */
	{.type FromDictionary, {.p C_nip}, .src = "dd C_nip	; ( read_count )"},		/* dd C_nip	; ( read_count ) 13432 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( read_count read_count )"},		/* dd M_dup	; ( read_count read_count ) 13440 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13448 */
	{.type Absolute, {.p 0}},		/* dd 0 13456 */
	{.type FromDictionary, {.p M_equal}, .src = "dd M_equal"},		/* dd M_equal 13464 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13472 */
	{.type FromDictionary, {.p L_C_get_2}, .src = "dd L_C_get_2"},		/* dd L_C_get_2 13480 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; ( ) read_count == 0"},		/* dd M_drop	; ( ) read_count == 0 13488 */
	{.type FromDictionary, {.p MV_Eof}, .src = "dd MV_Eof"},		/* dd MV_Eof 13496 */
	{.type FromDictionary, {.p C_on}, .src = "dd C_on		; end of file, qrestore_input"},		/* dd C_on		; end of file, qrestore_input 13504 */
	{.type FromDictionary, {.p C_restore_input}, .src = "dd C_restore_input"},		/* dd C_restore_input 13512 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13520 */
	{.type FromDictionary, {.p MV_Tib}, .src = "dd MV_Tib	; ( read_count 'Tib ) Tib has the counted string read"},		/* dd MV_Tib	; ( read_count 'Tib ) Tib has the counted string read 13528 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 13536 */
	{.type FromDictionary, {.p MV_Tib}, .src = "dd MV_Tib	; ( 'Tib )"},		/* dd MV_Tib	; ( 'Tib ) 13544 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13552 */
	{.type Header, {.hdr { 4, "word", /* C_word = 13568 */ colon }}}, /* CENTRY "word" word 4 ; ( c -- a ) read from #n/Infd/word into Tib h 13576 */
	{.type FromDictionary, {.p MC_WORDNUM}, .src = "dd MC_WORDNUM"},		/* dd MC_WORDNUM 13584 */
	{.type FromDictionary, {.p C_get}, .src = "dd C_get"},		/* dd C_get 13592 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13600 */
	{.type Header, {.hdr { 4, "line", /* C_line = 13616 */ colon }}}, /* CENTRY "line" line 4 ; ( c -- a ) read from #n/Infd/line h 13624 */
	{.type FromDictionary, {.p MC_LINENUM}, .src = "dd MC_LINENUM"},		/* dd MC_LINENUM 13632 */
	{.type FromDictionary, {.p C_get}, .src = "dd C_get"},		/* dd C_get 13640 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13648 */
	{.type Header, {.hdr { 11, "doublequote", /* C_doublequote = 13672 */ colon }}}, /* CENTRY "doublequote" doublequote 11 ; ( c -- a ) read from #n/Infd/doublequote h 13680 */
	{.type FromDictionary, {.p MC_DOUBLEQUOTENUM}, .src = "dd MC_DOUBLEQUOTENUM"},		/* dd MC_DOUBLEQUOTENUM 13688 */
	{.type FromDictionary, {.p C_get}, .src = "dd C_get"},		/* dd C_get 13696 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13704 */
	{.type Header, {.hdr { 10, "closeparen", /* C_closeparen = 13728 */ colon }}}, /* CENTRY "closeparen" closeparen 10 ; ( c -- a ) read from #n/Infd/closeparen h 13736 */
	{.type FromDictionary, {.p MC_CLOSEPARENNUM}, .src = "dd MC_CLOSEPARENNUM"},		/* dd MC_CLOSEPARENNUM 13744 */
	{.type FromDictionary, {.p C_get}, .src = "dd C_get"},		/* dd C_get 13752 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 13760 */
	{.type Header, {.hdr { 8, "findname", /* C_findname = 13784 */ colon }}}, /* CENTRY "findname" findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names h 13792 */
	{.type FromDictionary, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 13800 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 13808 */
	{.type FromDictionary, {.p MV_Dtop}, .src = "dd MV_Dtop"},		/* dd MV_Dtop 13816 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; get latest dictionary link"},		/* dd M_fetch	; get latest dictionary link 13824 */
	{.type FromDictionary, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 13832 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13840 */
	{.type FromDictionary, {.p L_C_findname_1}, .src = "dd L_C_findname_1	; seached until the first dictionary entry get out"},		/* dd L_C_findname_1	; seached until the first dictionary entry get out 13848 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a -- a a )"},		/* dd M_dup	; ( a -- a a ) 13856 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus	; ( a a -- a a+8) lenth + initial name address"},		/* dd C_cell_plus	; ( a a -- a a+8) lenth + initial name address 13864 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name"},		/* dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name 13872 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13880 */
	{.type Absolute, {.p 64}},		/* dd 64		; check the reveal'ed flag 1=hidden, 0=reveal 13888 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand	; if hidden, goto L_C_findname_3 else L_C_findname_2"},		/* dd M_binand	; if hidden, goto L_C_findname_3 else L_C_findname_2 13896 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 13904 */
	{.type FromDictionary, {.p L_C_findname_2}, .src = "dd L_C_findname_2"},		/* dd L_C_findname_2 13912 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; smudge'd dictionary entry, get the previous entry"},		/* dd M_fetch	; smudge'd dictionary entry, get the previous entry 13920 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 13928 */
	{.type FromDictionary, {.p L_C_findname_3}, .src = "dd L_C_findname_3"},		/* dd L_C_findname_3 13936 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a1 -- a1 a1)"},		/* dd M_dup	; ( a1 -- a1 a1) 13944 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus	; ( a1 a1 -- a1 a1+8)"},		/* dd C_cell_plus	; ( a1 a1 -- a1 a1+8) 13952 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n )"},		/* dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n ) 13960 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 13968 */
	{.type Absolute, {.p 63}},		/* dd 63 13976 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len )"},		/* dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len ) 13984 */
	{.type FromDictionary, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 13992 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14000 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 )"},		/* dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 ) 14008 */
	{.type FromDictionary, {.p C_compare}, .src = "dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name"},		/* dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name 14016 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq	; found a match?"},		/* dd C_0eq	; found a match? 14024 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14032 */
	{.type FromDictionary, {.p L_C_findname_4}, .src = "dd L_C_findname_4		; no match"},		/* dd L_C_findname_4		; no match 14040 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus	; match found"},		/* dd C_cell_plus	; match found 14048 */
	{.type FromDictionary, {.p C_true}, .src = "dd C_true"},		/* dd C_true 14056 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14064 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14072 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14080 */
	{.type FromDictionary, {.p L_C_findname}, .src = "dd L_C_findname"},		/* dd L_C_findname 14088 */
	{.type FromDictionary, {.p MV_Findadr}, .src = "dd MV_Findadr"},		/* dd MV_Findadr 14096 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 14104 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false"},		/* dd C_false 14112 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14120 */
	{.type Header, {.hdr { 4, "find", /* C_find = 14136 */ colon }}}, /* CENTRY "find" find 4 ; ( a1 -- a2 f )? h 14144 */
	{.type FromDictionary, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 14152 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14160 */
	{.type FromDictionary, {.p L_C_find}, .src = "dd L_C_find"},		/* dd L_C_find 14168 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14176 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14184 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 14192 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over"},		/* dd M_over 14200 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14208 */
	{.type Absolute, {.p 63}},		/* dd 63 14216 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 14224 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 14232 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 14240 */
	{.type FromDictionary, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 14248 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 14256 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14264 */
	{.type Absolute, {.p 128}},		/* dd 128 14272 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 14280 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14288 */
	{.type FromDictionary, {.p L_C_find_1}, .src = "dd L_C_find_1"},		/* dd L_C_find_1 14296 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14304 */
	{.type Absolute, {.p 1}},		/* dd 1 14312 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14320 */
	{.type FromDictionary, {.p L_C_find_2}, .src = "dd L_C_find_2"},		/* dd L_C_find_2 14328 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14336 */
	{.type Absolute, {.p -1}},		/* dd -1 14344 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14352 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14360 */
	{.type FromDictionary, {.p L_C_find_3}, .src = "dd L_C_find_3"},		/* dd L_C_find_3 14368 */
	{.type FromDictionary, {.p C_false}, .src = "dd C_false"},		/* dd C_false 14376 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14384 */
	{.type Header, {.hdr { 1, "'", /* C_single_quote = 14400 */ colon }}}, /* CENTRY "'" single_quote 1 h 14408 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 14416 */
	{.type FromDictionary, {.p C_find}, .src = "dd C_find"},		/* dd C_find 14424 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 14432 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14440 */
	{.type FromDictionary, {.p L_C_single_quote}, .src = "dd L_C_single_quote"},		/* dd L_C_single_quote 14448 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 14456 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 14464 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 14472 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14480 */
	{.type FromDictionary, {.p L170}, .src = "dd L170"},		/* dd L170 14488 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14496 */
	{.type Absolute, {.p 3}},		/* dd 3 14504 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 14512 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 14520 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 14528 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14536 */
	{.type Header, {.hdr { 6, "?stack", /* C_qstack = 14552 */ colon }}}, /* CENTRY "?stack" qstack 6 h 14560 */
	{.type FromDictionary, {.p M_stackptr}, .src = "dd M_stackptr"},		/* dd M_stackptr 14568 */
	{.type FromDictionary, {.p MV_S0}, .src = "dd MV_S0"},		/* dd MV_S0 14576 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 14584 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14592 */
	{.type FromDictionary, {.p L_C_qstack}, .src = "dd L_C_qstack"},		/* dd L_C_qstack 14600 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14608 */
	{.type FromDictionary, {.p L173}, .src = "dd L173"},		/* dd L173 14616 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14624 */
	{.type Absolute, {.p 16}},		/* dd 16 14632 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 14640 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 14648 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 14656 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14664 */
	{.type FromDictionary, {.p MC_STDOUT}, .src = "dd MC_STDOUT	; ( str -- str 1) ; debug code to show the word found"},		/* dd MC_STDOUT	; ( str -- str 1) ; debug code to show the word found 14672 */
	{.type FromDictionary, {.p M_over}, .src = "dd M_over		; ( str 1 str )"},		/* dd M_over		; ( str 1 str ) 14680 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count 		; ( str 1 a n)"},		/* dd C_count 		; ( str 1 a n) 14688 */
	{.type FromDictionary, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 14696 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 14704 */
	{.type Header, {.hdr { 9, "interpret", /* C_interpret = 14728 */ colon }}}, /* CENTRY "interpret" interpret 9 ; there is stuff in TIB to be interpreted >In and >Limit are set h 14736 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word	; ( bl -- a ) a = address of counted string"},		/* dd C_word	; ( bl -- a ) a = address of counted string 14744 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 14752 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 14760 */
	{.type FromDictionary, {.p C_0neq}, .src = "dd C_0neq"},		/* dd C_0neq 14768 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14776 */
	{.type FromDictionary, {.p L_C_interpret_1}, .src = "dd L_C_interpret_1	; count at a = 0, drop a and exit"},		/* dd L_C_interpret_1	; count at a = 0, drop a and exit 14784 */
	{.type FromDictionary, {.p C_find}, .src = "dd C_find	; ( a -- a1 f ) a = address of counted string"},		/* dd C_find	; ( a -- a1 f ) a = address of counted string 14792 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14800 */
	{.type FromDictionary, {.p L_C_interpret_2}, .src = "dd L_C_interpret_2"},		/* dd L_C_interpret_2 14808 */
	{.type FromDictionary, {.p M_execute}, .src = "dd M_execute	; found in dictionary, execute"},		/* dd M_execute	; found in dictionary, execute 14816 */
	{.type FromDictionary, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 14824 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14832 */
	{.type FromDictionary, {.p L_C_interpret_3}, .src = "dd L_C_interpret_3"},		/* dd L_C_interpret_3 14840 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 14848 */
	{.type FromDictionary, {.p C_number}, .src = "dd C_number"},		/* dd C_number 14856 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 14864 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 14872 */
	{.type FromDictionary, {.p L_C_interpret_4}, .src = "dd L_C_interpret_4"},		/* dd L_C_interpret_4 14880 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space	; the word is neither in the dictionary nor a number"},		/* dd C_space	; the word is neither in the dictionary nor a number 14888 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type	; show the word"},		/* dd C_type	; show the word 14896 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14904 */
	{.type FromDictionary, {.p L180}, .src = "dd L180	; error I?"},		/* dd L180	; error I? 14912 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 14920 */
	{.type Absolute, {.p 3}},		/* dd 3 14928 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 14936 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 14944 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 14952 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 14960 */
	{.type FromDictionary, {.p L_C_interpret}, .src = "dd L_C_interpret"},		/* dd L_C_interpret 14968 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop	; count at a = 0 ( a -- )"},		/* dd M_drop	; count at a = 0 ( a -- ) 14976 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 14984 */
	{.type Header, {.hdr { 6, "create", /* C_create = 15000 */ colon }}}, /* CENTRY "create" create 6 ; compiles dictionary header until the pfa (link, len, name, cfa) h 15008 */
	{.type FromDictionary, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 15016 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( -- here )"},		/* dd C_here	; ( -- here ) 15024 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( -- ) (R -- linkaddr )"},		/* dd M_rpush	; ( -- ) (R -- linkaddr ) 15032 */
	{.type FromDictionary, {.p MV_Dtop}, .src = "dd MV_Dtop	; ( -- Dtop ) (R -- linkaddr )"},		/* dd MV_Dtop	; ( -- Dtop ) (R -- linkaddr ) 15040 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr )"},		/* dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr ) 15048 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma	; ( dtop -- ) (R -- linkaddr )"},		/* dd C_comma	; ( dtop -- ) (R -- linkaddr ) 15056 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word	; get the word from the input stream ( c -- a ) skip any c. Placed the counted string in a (as in Wordbuf)"},		/* dd C_word	; get the word from the input stream ( c -- a ) skip any c. Placed the counted string in a (as in Wordbuf) 15064 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a -- a a ) (R -- linkaddr )"},		/* dd M_dup	; ( a -- a a ) (R -- linkaddr ) 15072 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a -- a len ) (R -- linkaddr )"},		/* dd M_cfetch	; ( a a -- a len ) (R -- linkaddr ) 15080 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( a len -- a len here ) (R -- linkaddr )"},		/* dd C_here	; ( a len -- a len here ) (R -- linkaddr ) 15088 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr )"},		/* dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr ) 15096 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte"},		/* dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte 15104 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr )"},		/* dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr ) 15112 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 )"},		/* dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 ) 15120 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 )"},		/* dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 ) 15128 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( -- len+1 ) (R -- linkaddr )"},		/* dd M_rpop	; ( -- len+1 ) (R -- linkaddr ) 15136 */
	{.type FromDictionary, {.p C_allot}, .src = "dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1"},		/* dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1 15144 */
	{.type FromDictionary, {.p C_align}, .src = "dd C_align	; sets Dp = aligned here"},		/* dd C_align	; sets Dp = aligned here 15152 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15160 */
	{.type FromDictionary, {.p M_variable}, .src = "dd M_variable"},		/* dd M_variable 15168 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( -- variablecfa) (R -- linkaddr )"},		/* dd M_fetch	; ( -- variablecfa) (R -- linkaddr ) 15176 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma	; ( -- ) put the variablecfa into the cfa"},		/* dd C_comma	; ( -- ) put the variablecfa into the cfa 15184 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( -- linkaddr) (R -- )"},		/* dd M_rpop	; ( -- linkaddr) (R -- ) 15192 */
	{.type FromDictionary, {.p MV_Dtop}, .src = "dd MV_Dtop"},		/* dd MV_Dtop 15200 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; Dtop = just created link address"},		/* dd M_store	; Dtop = just created link address 15208 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15216 */
	{.type Header, {.hdr { 8, "variable", /* C_variable = 15240 */ colon }}}, /* CENTRY "variable" variable 8 ; compile to put the there then on the stack h 15248 */
	{.type FromDictionary, {.p C_create}, .src = "dd C_create"},		/* dd C_create 15256 */
	{.type FromDictionary, {.p C_there}, .src = "dd C_there"},		/* dd C_there 15264 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma	; put the next available variable location in pfa"},		/* dd C_comma	; put the next available variable location in pfa 15272 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15280 */
	{.type Absolute, {.p 1}},		/* dd 1 15288 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 15296 */
	{.type FromDictionary, {.p C_vallot}, .src = "dd C_vallot	; there = there+8, stored at Vp"},		/* dd C_vallot	; there = there+8, stored at Vp 15304 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15312 */
	{.type Header, {.hdr { 8, "constant", /* C_constant = 15336 */ colon }}}, /* CENTRY "constant" constant 8 ; ( n -- ) do the same as variable but change the cfa to (constant) h 15344 */
	{.type FromDictionary, {.p C_create}, .src = "dd C_create	; create dictionary header upto the cfa"},		/* dd C_create	; create dictionary header upto the cfa 15352 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15360 */
	{.type FromDictionary, {.p M_constant}, .src = "dd M_constant"},		/* dd M_constant 15368 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( Contstantcfa -- (constant) )"},		/* dd M_fetch	; ( Contstantcfa -- (constant) ) 15376 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( (constant) -- (constant) here )"},		/* dd C_here	; ( (constant) -- (constant) here ) 15384 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15392 */
	{.type Absolute, {.p 1}},		/* dd 1 15400 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells	; ( (constant) here -- (constant) here 8 )"},		/* dd C_cells	; ( (constant) here -- (constant) here 8 ) 15408 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus	; ( (constant) here 8 -- (constant) here-8 )"},		/* dd M_minus	; ( (constant) here 8 -- (constant) here-8 ) 15416 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant) "},		/* dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant)  15424 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma	; store n into the dictionary"},		/* dd C_comma	; store n into the dictionary 15432 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15440 */
	{.type Header, {.hdr { 9, "immediate", /* C_immediate = 15464 */ colon }}}, /* CENTRY "immediate" immediate 9 h 15472 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 15480 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 15488 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus"},		/* dd C_cell_plus 15496 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15504 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 15512 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15520 */
	{.type Absolute, {.p 128}},		/* dd 128 15528 */
	{.type FromDictionary, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 15536 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 15544 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 15552 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15560 */
	{.type Header, {.hdr { 4, ">cfa", /* C_tocfa = 15576 */ colon }}}, /* CENTRY ">cfa" tocfa 4 h 15584 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 15592 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15600 */
	{.type Absolute, {.p 63}},		/* dd 63 15608 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 15616 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 15624 */
	{.type FromDictionary, {.p C_aligned}, .src = "dd C_aligned"},		/* dd C_aligned 15632 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15640 */
	{.type Header, {.hdr { 7, "compile", /* C_compile = 15656 */ colon }}}, /* CENTRY "compile" compile 7 h 15664 */
	{.type FromDictionary, {.p C_findname}, .src = "dd C_findname"},		/* dd C_findname 15672 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15680 */
	{.type FromDictionary, {.p L_C_compile}, .src = "dd L_C_compile"},		/* dd L_C_compile 15688 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 15696 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 15704 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15712 */
	{.type Absolute, {.p 128}},		/* dd 128 15720 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 15728 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15736 */
	{.type FromDictionary, {.p L_C_compile_1}, .src = "dd L_C_compile_1"},		/* dd L_C_compile_1 15744 */
	{.type FromDictionary, {.p C_tocfa}, .src = "dd C_tocfa	; immediate"},		/* dd C_tocfa	; immediate 15752 */
	{.type FromDictionary, {.p M_execute}, .src = "dd M_execute"},		/* dd M_execute 15760 */
	{.type FromDictionary, {.p C_qstack}, .src = "dd C_qstack"},		/* dd C_qstack 15768 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15776 */
	{.type FromDictionary, {.p L_C_compile_2}, .src = "dd L_C_compile_2"},		/* dd L_C_compile_2 15784 */
	{.type FromDictionary, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 15792 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15800 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15808 */
	{.type FromDictionary, {.p L_C_compile_3}, .src = "dd L_C_compile_3"},		/* dd L_C_compile_3 15816 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 15824 */
	{.type FromDictionary, {.p C_number}, .src = "dd C_number"},		/* dd C_number 15832 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 15840 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 15848 */
	{.type FromDictionary, {.p L_C_compile_4}, .src = "dd L_C_compile_4"},		/* dd L_C_compile_4 15856 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 15864 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 15872 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15880 */
	{.type FromDictionary, {.p L_C_compile_5}, .src = "dd L_C_compile_5"},		/* dd L_C_compile_5 15888 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15896 */
	{.type Absolute, {.p 3}},		/* dd 3 15904 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 15912 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 15920 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 15928 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 15936 */
	{.type FromDictionary, {.p L_C_compile_6}, .src = "dd L_C_compile_6"},		/* dd L_C_compile_6 15944 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15952 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 15960 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15968 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 15976 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 15984 */
	{.type Header, {.hdr { 1, "]", /* C_close_bracket = 16000 */ colon }}}, /* CENTRY "]" close_bracket 1 h 16008 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 16016 */
	{.type FromDictionary, {.p C_on}, .src = "dd C_on"},		/* dd C_on 16024 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 16032 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 16040 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 16048 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 16056 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16064 */
	{.type FromDictionary, {.p L_C_close_bracket_1}, .src = "dd L_C_close_bracket_1"},		/* dd L_C_close_bracket_1 16072 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 16080 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 16088 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16096 */
	{.type FromDictionary, {.p L_C_close_bracket_2}, .src = "dd L_C_close_bracket_2"},		/* dd L_C_close_bracket_2 16104 */
	{.type FromDictionary, {.p C_compile}, .src = "dd C_compile"},		/* dd C_compile 16112 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 16120 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 16128 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 16136 */
	{.type FromDictionary, {.p L_C_close_bracket_3}, .src = "dd L_C_close_bracket_3"},		/* dd L_C_close_bracket_3 16144 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 16152 */
	{.type FromDictionary, {.p L_C_close_bracket}, .src = "dd L_C_close_bracket"},		/* dd L_C_close_bracket 16160 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16168 */
	{.type IHeader, {.hdr { 1, "[", /* CI_open_bracket = 16184 */ colon }}}, /* CIENTRY "[" open_bracket 1 h 16192 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 16200 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off"},		/* dd C_off 16208 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16216 */
	{.type Header, {.hdr { 6, "smudge", /* C_smudge = 16232 */ colon }}}, /* CENTRY "smudge" smudge 6 h 16240 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 16248 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 16256 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus"},		/* dd C_cell_plus 16264 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 16272 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 16280 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16288 */
	{.type Absolute, {.p 64}},		/* dd 64 16296 */
	{.type FromDictionary, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 16304 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16312 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 16320 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16328 */
	{.type Header, {.hdr { 6, "reveal", /* C_reveal = 16344 */ colon }}}, /* CENTRY "reveal" reveal 6 h 16352 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 16360 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 16368 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus"},		/* dd C_cell_plus 16376 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 16384 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 16392 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16400 */
	{.type Absolute, {.p 64}},		/* dd 64 16408 */
	{.type FromDictionary, {.p C_invert}, .src = "dd C_invert"},		/* dd C_invert 16416 */
	{.type FromDictionary, {.p M_binand}, .src = "dd M_binand"},		/* dd M_binand 16424 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 16432 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore"},		/* dd M_cstore 16440 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16448 */
	{.type Header, {.hdr { 1, ":", /* C_colon = 16464 */ colon }}}, /* CENTRY ":" colon 1 h 16472 */
	{.type FromDictionary, {.p C_create}, .src = "dd C_create	; create a dictionary header with (variable) at cfa"},		/* dd C_create	; create a dictionary header with (variable) at cfa 16480 */
	{.type FromDictionary, {.p C_smudge}, .src = "dd C_smudge"},		/* dd C_smudge 16488 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16496 */
	{.type FromDictionary, {.p M_colon}, .src = "dd M_colon"},		/* dd M_colon 16504 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon"},		/* dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon 16512 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( (colon) -- (colon) here )"},		/* dd C_here	; ( (colon) -- (colon) here ) 16520 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16528 */
	{.type Absolute, {.p 1}},		/* dd 1 16536 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 16544 */
	{.type FromDictionary, {.p M_minus}, .src = "dd M_minus	; ( (colon) here -- (colon) here-8 )"},		/* dd M_minus	; ( (colon) here -- (colon) here-8 ) 16552 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon"},		/* dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon 16560 */
	{.type FromDictionary, {.p C_close_bracket}, .src = "dd C_close_bracket"},		/* dd C_close_bracket 16568 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16576 */
	{.type IHeader, {.hdr { 1, ";", /* CI_semicolon = 16592 */ colon }}}, /* CIENTRY ";" semicolon 1 h 16600 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16608 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16616 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16624 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 16632 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off"},		/* dd C_off 16640 */
	{.type FromDictionary, {.p C_reveal}, .src = "dd C_reveal"},		/* dd C_reveal 16648 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16656 */
	{.type IHeader, {.hdr { 7, "recurse", /* CI_recurse = 16672 */ colon }}}, /* CIENTRY "recurse" recurse 7 h 16680 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 16688 */
	{.type FromDictionary, {.p M_fetch}, .src = "dd M_fetch"},		/* dd M_fetch 16696 */
	{.type FromDictionary, {.p C_cell_plus}, .src = "dd C_cell_plus"},		/* dd C_cell_plus 16704 */
	{.type FromDictionary, {.p C_tocfa}, .src = "dd C_tocfa"},		/* dd C_tocfa 16712 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16720 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16728 */
	{.type Header, {.hdr { 4, "char", /* C_char = 16744 */ colon }}}, /* CENTRY "char" char 4 ; ( -- c ) fetch the first character of the next word from input h 16752 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word	; ( c -- a ) puts the address of the counted string from the input on the stack"},		/* dd C_word	; ( c -- a ) puts the address of the counted string from the input on the stack 16760 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus	; skip the count"},		/* dd C_1plus	; skip the count 16768 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; fetch the first character"},		/* dd M_cfetch	; fetch the first character 16776 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16784 */
	{.type Header, {.hdr { 7, "literal", /* C_literal = 16800 */ colon }}}, /* CENTRY "literal" literal 7 ; ( n -- ) adds (literal) n to the dictionary h 16808 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16816 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16824 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16832 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 16840 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 16848 */
	{.type Header, {.hdr { 8, "sliteral", /* C_sliteral = 16872 */ colon }}}, /* CENTRY "sliteral" sliteral 8 ; ( -- ) adds (sliteral) a n to the dictionary h 16880 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 16888 */
	{.type FromDictionary, {.p M_sliteral}, .src = "dd M_sliteral"},		/* dd M_sliteral 16896 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma	; adds (sliteral) to the dictionary"},		/* dd C_comma	; adds (sliteral) to the dictionary 16904 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( here )"},		/* dd C_here	; ( here ) 16912 */
	{.type FromDictionary, {.p C_doublequote}, .src = "dd C_doublequote"},		/* dd C_doublequote 16920 */
	{.type FromDictionary, {.p MV_Tib}, .src = "dd MV_Tib"},		/* dd MV_Tib 16928 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( here a -- here a a )"},		/* dd M_dup	; ( here a -- here a a ) 16936 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( here a a -- here a n )"},		/* dd M_cfetch	; ( here a a -- here a n ) 16944 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus	; ( here a n -- here a n+1 ) n+1 as 1 for the count and n for the length of the string"},		/* dd C_1plus	; ( here a n -- here a n+1 ) n+1 as 1 for the count and n for the length of the string 16952 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( here a n+1 -- here a ) (R -- n+1)"},		/* dd M_rpush	; ( here a n+1 -- here a ) (R -- n+1) 16960 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( here a -- a here ) (R -- n+1)"},		/* dd M_xswap	; ( here a -- a here ) (R -- n+1) 16968 */
	{.type FromDictionary, {.p M_rfetch}, .src = "dd M_rfetch	; ( a here -- a here n+1 ) (R -- n+1 )"},		/* dd M_rfetch	; ( a here -- a here n+1 ) (R -- n+1 ) 16976 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; ( a here n+1 -- ) moves n+1 from a to here"},		/* dd M_cmove	; ( a here n+1 -- ) moves n+1 from a to here 16984 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( -- n+1 ) (R -- )"},		/* dd M_rpop	; ( -- n+1 ) (R -- ) 16992 */
	{.type FromDictionary, {.p C_allot}, .src = "dd C_allot	; ( n+1 -- ) here = here+n+1"},		/* dd C_allot	; ( n+1 -- ) here = here+n+1 17000 */
	{.type FromDictionary, {.p C_align}, .src = "dd C_align	; align here"},		/* dd C_align	; align here 17008 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17016 */
	{.type Header, {.hdr { 6, "string", /* C_string = 17032 */ colon }}}, /* CENTRY "string" string 6 ; ( c -- ) h 17040 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 17048 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17056 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 17064 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 17072 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 17080 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 17088 */
	{.type FromDictionary, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 17096 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 17104 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 17112 */
	{.type FromDictionary, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 17120 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17128 */
	{.type IHeader, {.hdr { 6, "[char]", /* CI_char_brackets = 17144 */ colon }}}, /* CIENTRY "[char]" char_brackets 6 ; take the next character from the input stream during compilation h 17152 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 17160 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus"},		/* dd C_1plus 17168 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch"},		/* dd M_cfetch 17176 */
	{.type FromDictionary, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 17184 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17192 */
	{.type IHeader, {.hdr { 3, "[']", /* CI_quote_brackets = 17208 */ colon }}}, /* CIENTRY "[']" quote_brackets 3 ; take the address of next token from the input stream during compilation h 17216 */
	{.type FromDictionary, {.p C_single_quote}, .src = "dd C_single_quote"},		/* dd C_single_quote 17224 */
	{.type FromDictionary, {.p C_literal}, .src = "dd C_literal"},		/* dd C_literal 17232 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17240 */
	{.type IHeader, {.hdr { 1, "(", /* CI_openparen = 17256 */ colon }}}, /* CIENTRY "(" openparen 1 ; ignore until ) from the input stream during compilation h 17264 */
	{.type FromDictionary, {.p C_closeparen}, .src = "dd C_closeparen"},		/* dd C_closeparen 17272 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 17280 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17288 */
/* ; if the line is longer than Tib, then skipping this line is not good enough. hence, throwing an error when >Limit == Tib length */	{.type IHeader, {.hdr { 1, "\\", /* CI_backslash = 17304 */ colon }}}, /* CIENTRY "\\" backslash 1 ; when there is no Acceptvec, find a newline in the buffer and skip until that h 17312 */
	{.type FromDictionary, {.p C_line}, .src = "dd C_line"},		/* dd C_line 17320 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17328 */
	{.type Header, {.hdr { 8, "(?abort)", /* C_qabort_parens = 17352 */ colon }}}, /* CENTRY "(?abort)" qabort_parens 8 h 17360 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 17368 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 17376 */
	{.type FromDictionary, {.p L_C_qabort_parens}, .src = "dd L_C_qabort_parens"},		/* dd L_C_qabort_parens 17384 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 17392 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 17400 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 17408 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 17416 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 17424 */
	{.type FromDictionary, {.p L_C_qabort_parens_1}, .src = "dd L_C_qabort_parens_1"},		/* dd L_C_qabort_parens_1 17432 */
	{.type FromDictionary, {.p C_2drop}, .src = "dd C_2drop"},		/* dd C_2drop 17440 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17448 */
	{.type IHeader, {.hdr { 6, "abort\"", /* CI_abort_double_quote = 17464 */ colon }}}, /* CIENTRY "abort\"" abort_double_quote 6 h 17472 */
	{.type FromDictionary, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 17480 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17488 */
	{.type FromDictionary, {.p C_qabort_parens}, .src = "dd C_qabort_parens"},		/* dd C_qabort_parens 17496 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17504 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17512 */
	{.type Header, {.hdr { 1, "\"", /* C_double_quote = 17528 */ colon }}}, /* CENTRY "\"" double_quote 1 ; ( | .. " -- 'text count ) stores counted string in the dictionary and also leaves the address and count of the string on the stack - to use strings at the interpreter prompt h 17536 */
	{.type FromDictionary, {.p C_doublequote}, .src = "dd C_doublequote"},		/* dd C_doublequote 17544 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 17552 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 17560 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 17568 */
	{.type FromDictionary, {.p M_rfetch}, .src = "dd M_rfetch"},		/* dd M_rfetch 17576 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove"},		/* dd M_cmove 17584 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 17592 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 17600 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 17608 */
	{.type FromDictionary, {.p C_allot}, .src = "dd C_allot"},		/* dd C_allot 17616 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17624 */
	{.type Header, {.hdr { 2, "c\"", /* C_cdouble_quote = 17640 */ colon }}}, /* CENTRY "c\"" cdouble_quote 2 ; ( | ..." -- 'counted-string ) stores counted string in the dictionary and also leaves the address of the counted string on the stack. For use in interpretive mode. shouldn't this be using pad? h 17648 */
	{.type FromDictionary, {.p C_doublequote}, .src = "dd C_doublequote	; ( \" -- a ) a = counted string address. a will be in Wordbuf"},		/* dd C_doublequote	; ( \" -- a ) a = counted string address. a will be in Wordbuf 17656 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a -- a a)"},		/* dd M_dup	; ( a -- a a) 17664 */
	{.type FromDictionary, {.p M_cfetch}, .src = "dd M_cfetch	; ( a a -- a n )"},		/* dd M_cfetch	; ( a a -- a n ) 17672 */
	{.type FromDictionary, {.p C_1plus}, .src = "dd C_1plus	; ( a n -- a n+1 )"},		/* dd C_1plus	; ( a n -- a n+1 ) 17680 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a n -- a ) (R -- n+1)"},		/* dd M_rpush	; ( a n -- a ) (R -- n+1) 17688 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( a -- a here ) (R -- n+1)"},		/* dd C_here	; ( a -- a here ) (R -- n+1) 17696 */
	{.type FromDictionary, {.p M_rfetch}, .src = "dd M_rfetch	; ( a here -- a here n+1) (R -- n+1)"},		/* dd M_rfetch	; ( a here -- a here n+1) (R -- n+1) 17704 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; move counted string from a to here"},		/* dd M_cmove	; move counted string from a to here 17712 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here	; ( -- here )"},		/* dd C_here	; ( -- here ) 17720 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( here -- here n+1 )(R -- )"},		/* dd M_rpop	; ( here -- here n+1 )(R -- ) 17728 */
	{.type FromDictionary, {.p C_allot}, .src = "dd C_allot	; ( here n+1 -- here) here += n+1"},		/* dd C_allot	; ( here n+1 -- here) here += n+1 17736 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17744 */
	{.type IHeader, {.hdr { 2, "s\"", /* CI_sdouble_quote = 17760 */ colon }}}, /* CIENTRY "s\"" sdouble_quote 2 ; ( | ..." -- 'text count ) add the string from the input stream to the dictionary as (sliteral) count string - at run-time puts the ( -- addr n) of the counted string on the stack. h 17768 */
	{.type FromDictionary, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 17776 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17784 */
	{.type IHeader, {.hdr { 2, ".\"", /* CI_dotstr = 17800 */ colon }}}, /* CIENTRY ".\"" dotstr 2 ; ( | ..." -- ) do what s" does and then add a type word to the dictionary to print that string h 17808 */
	{.type FromDictionary, {.p C_sliteral}, .src = "dd C_sliteral"},		/* dd C_sliteral 17816 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17824 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 17832 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17840 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17848 */
	{.type IHeader, {.hdr { 2, "if", /* CI_if = 17864 */ colon }}}, /* CIENTRY "if" if 2 h 17872 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17880 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 17888 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17896 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 17904 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17912 */
	{.type Absolute, {.p 0}},		/* dd 0 17920 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17928 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 17936 */
	{.type IHeader, {.hdr { 4, "else", /* CI_else = 17952 */ colon }}}, /* CIENTRY "else" else 4 h 17960 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 17968 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 17976 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 17984 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 17992 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 18000 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18008 */
	{.type Absolute, {.p 0}},		/* dd 0 18016 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18024 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 18032 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 18040 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18048 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 18056 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18064 */
	{.type IHeader, {.hdr { 4, "then", /* CI_then = 18080 */ colon }}}, /* CIENTRY "then" then 4 h 18088 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 18096 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 18104 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18112 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18120 */
	{.type IHeader, {.hdr { 5, "begin", /* CI_begin = 18136 */ colon }}}, /* CIENTRY "begin" begin 5 h 18144 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 18152 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18160 */
	{.type IHeader, {.hdr { 5, "again", /* CI_again = 18176 */ colon }}}, /* CIENTRY "again" again 5 h 18184 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18192 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 18200 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18208 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18216 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18224 */
	{.type IHeader, {.hdr { 5, "until", /* CI_until = 18240 */ colon }}}, /* CIENTRY "until" until 5 h 18248 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18256 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 18264 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18272 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18280 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18288 */
	{.type IHeader, {.hdr { 5, "while", /* CI_while = 18304 */ colon }}}, /* CIENTRY "while" while 5 h 18312 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18320 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 18328 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18336 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 18344 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18352 */
	{.type Absolute, {.p 0}},		/* dd 0 18360 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18368 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18376 */
	{.type IHeader, {.hdr { 6, "repeat", /* CI_repeat = 18392 */ colon }}}, /* CIENTRY "repeat" repeat 6 h 18400 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18408 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 18416 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18424 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 18432 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18440 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 18448 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 18456 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18464 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18472 */
	{.type IHeader, {.hdr { 2, "do", /* CI_do = 18488 */ colon }}}, /* CIENTRY "do" do 2 h 18496 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18504 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time"},		/* dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time 18512 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma		; puts (do) into the dictionary"},		/* dd C_comma		; puts (do) into the dictionary 18520 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18528 */
	{.type Absolute, {.p 0}},		/* dd 0			; ( -- 0 ) 18536 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here		; ( 0 -- 0 here1 )"},		/* dd C_here		; ( 0 -- 0 here1 ) 18544 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18552 */
	{.type IHeader, {.hdr { 4, "loop", /* CI_loop = 18568 */ colon }}}, /* CIENTRY "loop" loop 4 ; ( 0 here1 -- ) h 18576 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18584 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop		; ( 0 here1 -- 0 here1 (loop) )"},		/* dd M_doloop		; ( 0 here1 -- 0 here1 (loop) ) 18592 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 )"},		/* dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 ) 18600 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 )"},		/* dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 ) 18608 */
	{.type FromDictionary, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 18616 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 18624 */
	{.type FromDictionary, {.p L234}, .src = "dd L234"},		/* dd L234 18632 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 18640 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 18648 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18656 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18664 */
	{.type IHeader, {.hdr { 5, "+loop", /* CI_ploop = 18680 */ colon }}}, /* CIENTRY "+loop" ploop 5 h 18688 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18696 */
	{.type FromDictionary, {.p M_doploop}, .src = "dd M_doploop"},		/* dd M_doploop 18704 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18712 */
	{.type FromDictionary, {.p C_comma}, .src = "dd C_comma"},		/* dd C_comma 18720 */
	{.type FromDictionary, {.p C_qdup}, .src = "dd C_qdup"},		/* dd C_qdup 18728 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 18736 */
	{.type FromDictionary, {.p L236}, .src = "dd L236"},		/* dd L236 18744 */
	{.type FromDictionary, {.p C_here}, .src = "dd C_here"},		/* dd C_here 18752 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 18760 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 18768 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18776 */
	{.type Header, {.hdr { 3, "w/o", /* C_wo = 18792 */ colon }}}, /* CENTRY "w/o" wo 3 h 18800 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18808 */
	{.type Absolute, {.p 1}},		/* dd 1 18816 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18824 */
	{.type Absolute, {.p 512}},		/* dd 512 18832 */
	{.type FromDictionary, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 18840 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18848 */
	{.type Absolute, {.p 64}},		/* dd 64 18856 */
	{.type FromDictionary, {.p M_binor}, .src = "dd M_binor"},		/* dd M_binor 18864 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18872 */
	{.type Header, {.hdr { 3, "r/o", /* C_ro = 18888 */ colon }}}, /* CENTRY "r/o" ro 3 h 18896 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18904 */
	{.type Absolute, {.p 0}},		/* dd 0 18912 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18920 */
	{.type Header, {.hdr { 3, "r/w", /* C_rw = 18936 */ colon }}}, /* CENTRY "r/w" rw 3 h 18944 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 18952 */
	{.type Absolute, {.p 2}},		/* dd 2 18960 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 18968 */
	{.type Header, {.hdr { 7, "cstring", /* C_cstring = 18984 */ colon }}}, /* CENTRY "cstring" cstring 7 ; ( 'text count o -- o+'pad+1024 ) \ copy string to pad+o and add a null byte at the end h 18992 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad	; ( 'text count o 'pad )"},		/* dd C_pad	; ( 'text count o 'pad ) 19000 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19008 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( 'text count o 'pad 1024 ) 19016 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 'text count o 'pad+1024 )"},		/* dd M_plus	; ( 'text count o 'pad+1024 ) 19024 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 'text count o+'pad+1024 ) o=padoffset"},		/* dd M_plus	; ( 'text count o+'pad+1024 ) o=padoffset 19032 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 19040 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( 'text count o+'pad+1024 ) (R o+'pad+1024 )"},		/* dd M_rpush	; ( 'text count o+'pad+1024 ) (R o+'pad+1024 ) 19048 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( 'text o+'pad+1024 count ) (R o+'pad+1024 )"},		/* dd M_xswap	; ( 'text o+'pad+1024 count ) (R o+'pad+1024 ) 19056 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( 'text o+'pad+1024 count count ) (R o+'pad+1024 )"},		/* dd M_dup	; ( 'text o+'pad+1024 count count ) (R o+'pad+1024 ) 19064 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( 'text o+'pad+1024 count ) (R o+'pad+1024  count )"},		/* dd M_rpush	; ( 'text o+'pad+1024 count ) (R o+'pad+1024  count ) 19072 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; moves the filename from 'text to o+'pad+1024"},		/* dd M_cmove	; moves the filename from 'text to o+'pad+1024 19080 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19088 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( 0 ) (R o+'pad+1024  count ) 19096 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( 0 count ) (R o+'pad+1024 )"},		/* dd M_rpop	; ( 0 count ) (R o+'pad+1024 ) 19104 */
	{.type FromDictionary, {.p M_rfetch}, .src = "dd M_rfetch	; ( 0 count o+'pad+1024 ) (R o+'pad+1024 )"},		/* dd M_rfetch	; ( 0 count o+'pad+1024 ) (R o+'pad+1024 ) 19112 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 0 count+o+'pad+1024 ) (R o+'pad+1024 )"},		/* dd M_plus	; ( 0 count+o+'pad+1024 ) (R o+'pad+1024 ) 19120 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore	; makes the filename to a null terminated string"},		/* dd M_cstore	; makes the filename to a null terminated string 19128 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop ;  ( o+'pad+1024 )"},		/* dd M_rpop ;  ( o+'pad+1024 ) 19136 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19144 */
	{.type Header, {.hdr { 8, "cstring0", /* C_cstring0 = 19168 */ colon }}}, /* CENTRY "cstring0" cstring0 8 ; ( 'text count -- 'text ) \ copy string to pad+1024 and add a null byte at the end h 19176 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19184 */
	{.type Absolute, {.p 0}},		/* dd 0 19192 */
	{.type FromDictionary, {.p C_cstring}, .src = "dd C_cstring"},		/* dd C_cstring 19200 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19208 */
	{.type Header, {.hdr { 8, "cstring1", /* C_cstring1 = 19232 */ colon }}}, /* CENTRY "cstring1" cstring1 8 ; ( 'text count -- 'text ) \ copy string to pad+1536 and add a null byte at the end h 19240 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19248 */
	{.type Absolute, {.p 512}},		/* dd 512 19256 */
	{.type FromDictionary, {.p C_cstring}, .src = "dd C_cstring"},		/* dd C_cstring 19264 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19272 */
	{.type Header, {.hdr { 9, "open-file", /* C_open_file = 19296 */ colon }}}, /* CENTRY "open-file" open_file 9 ; ( 'text count mode -- fd ioresult ) h 19304 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( 'text count ) (R mode)"},		/* dd M_rpush	; ( 'text count ) (R mode) 19312 */
	{.type FromDictionary, {.p C_cstring0}, .src = "dd C_cstring0 ; ( 'padtext ) (R mode )"},		/* dd C_cstring0 ; ( 'padtext ) (R mode ) 19320 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( 'padtext mode ) (R )"},		/* dd M_rpop	; ( 'padtext mode ) (R ) 19328 */
	{.type FromDictionary, {.p M_sysopen}, .src = "dd M_sysopen"},		/* dd M_sysopen 19336 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 19344 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19352 */
	{.type Absolute, {.p -1}},		/* dd -1 19360 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 19368 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19376 */
	{.type Header, {.hdr { 10, "close-file", /* C_close_file = 19400 */ colon }}}, /* CENTRY "close-file" close_file 10 ; ( fd -- ioresult ) h 19408 */
	{.type FromDictionary, {.p M_sysclose}, .src = "dd M_sysclose"},		/* dd M_sysclose 19416 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 19424 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19432 */
	{.type Header, {.hdr { 9, "read-file", /* C_read_file = 19456 */ colon }}}, /* CENTRY "read-file" read_file 9 ; ( 'text count fd -- count2 ioresult ) h 19464 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot	; ( n fd a )"},		/* dd C_rot	; ( n fd a ) 19472 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot	; ( fd a n )"},		/* dd C_rot	; ( fd a n ) 19480 */
	{.type FromDictionary, {.p M_sysread}, .src = "dd M_sysread"},		/* dd M_sysread 19488 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 19496 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19504 */
	{.type Absolute, {.p -1}},		/* dd -1 19512 */
	{.type FromDictionary, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 19520 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19528 */
	{.type Header, {.hdr { 10, "write-file", /* C_write_file = 19552 */ colon }}}, /* CENTRY "write-file" write_file 10 ; ( 'text count fd -- ioresult ) h 19560 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot	; ( n fd a )"},		/* dd C_rot	; ( n fd a ) 19568 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot	; ( fd a n )"},		/* dd C_rot	; ( fd a n ) 19576 */
	{.type FromDictionary, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 19584 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19592 */
	{.type Absolute, {.p -1}},		/* dd -1 19600 */
	{.type FromDictionary, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 19608 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19616 */
	{.type Header, {.hdr { 15, "reposition-file", /* C_reposition_file = 19640 */ colon }}}, /* CENTRY "reposition-file" reposition_file 15 ; ( type n fd -- ioresult ) h 19648 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap		; ( type fd n )"},		/* dd M_xswap		; ( type fd n ) 19656 */
	{.type FromDictionary, {.p C_rot}, .src = "dd C_rot		; ( fd n type )"},		/* dd C_rot		; ( fd n type ) 19664 */
	{.type FromDictionary, {.p M_sysseek}, .src = "dd M_sysseek"},		/* dd M_sysseek 19672 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19680 */
	{.type Absolute, {.p -1}},		/* dd -1 19688 */
	{.type FromDictionary, {.p C_neq}, .src = "dd C_neq"},		/* dd C_neq 19696 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19704 */
	{.type Header, {.hdr { 7, "?fcheck", /* C_qfcheck = 19720 */ colon }}}, /* CENTRY "?fcheck" qfcheck 7 h 19728 */
	{.type FromDictionary, {.p C_0eq}, .src = "dd C_0eq"},		/* dd C_0eq 19736 */
	{.type FromDictionary, {.p M_cjump}, .src = "dd M_cjump"},		/* dd M_cjump 19744 */
	{.type FromDictionary, {.p L246}, .src = "dd L246"},		/* dd L246 19752 */
	{.type FromDictionary, {.p C_space}, .src = "dd C_space"},		/* dd C_space 19760 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19768 */
	{.type FromDictionary, {.p L247}, .src = "dd L247"},		/* dd L247 19776 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19784 */
	{.type Absolute, {.p 9}},		/* dd 9 19792 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 19800 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 19808 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 19816 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 19824 */
	{.type Header, {.hdr { 11, "create-file", /* C_create_file = 19848 */ colon }}}, /* CENTRY "create-file" create_file 11 ; ( a n mode perm -- fd ioresult ) not part of the original ff. could move this to a forth file. h 19856 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a n mode ) (R perm)"},		/* dd M_rpush	; ( a n mode ) (R perm) 19864 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a n ) (R perm mode)"},		/* dd M_rpush	; ( a n ) (R perm mode) 19872 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad	; ( a n padaddr)"},		/* dd C_pad	; ( a n padaddr) 19880 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19888 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( a n padaddr 1024 ) 19896 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( a n padaddr+1024 )"},		/* dd M_plus	; ( a n padaddr+1024 ) 19904 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap	; ( a padaddr+1024 n )"},		/* dd M_xswap	; ( a padaddr+1024 n ) 19912 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup	; ( a padaddr+1024 n n )"},		/* dd M_dup	; ( a padaddr+1024 n n ) 19920 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n )"},		/* dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n ) 19928 */
	{.type FromDictionary, {.p M_cmove}, .src = "dd M_cmove	; moves the filename from a to paddaddr+1024"},		/* dd M_cmove	; moves the filename from a to paddaddr+1024 19936 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19944 */
	{.type Absolute, {.p 0}},		/* dd 0		; ( 0 ) 19952 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( 0 n ) (R perm mode)"},		/* dd M_rpop	; ( 0 n ) (R perm mode) 19960 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad	; ( 0 n padaddr)"},		/* dd C_pad	; ( 0 n padaddr) 19968 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n )"},		/* dd M_plus	; ( 0 padaddr+n ) 19976 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 19984 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( 0 padaddr+n 1024 ) 19992 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( 0 padaddr+n+1024 )"},		/* dd M_plus	; ( 0 padaddr+n+1024 ) 20000 */
	{.type FromDictionary, {.p M_cstore}, .src = "dd M_cstore	; ( ) makes the filename to a null terminated string"},		/* dd M_cstore	; ( ) makes the filename to a null terminated string 20008 */
	{.type FromDictionary, {.p C_pad}, .src = "dd C_pad"},		/* dd C_pad 20016 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20024 */
	{.type Absolute, {.p 1024}},		/* dd 1024		; ( padaddr 1024 ) 20032 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus	; ( padaddr+1024 )"},		/* dd M_plus	; ( padaddr+1024 ) 20040 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 mode) (R perm )"},		/* dd M_rpop	; ( padaddr+1024 mode) (R perm ) 20048 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop	; ( padaddr+1024 mode perm ) (R )"},		/* dd M_rpop	; ( padaddr+1024 mode perm ) (R ) 20056 */
	{.type FromDictionary, {.p M_syscreate}, .src = "dd M_syscreate"},		/* dd M_syscreate 20064 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 20072 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20080 */
	{.type Absolute, {.p -1}},		/* dd -1 20088 */
	{.type FromDictionary, {.p M_greater}, .src = "dd M_greater"},		/* dd M_greater 20096 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 20104 */
	{.type Header, {.hdr { 3, "bye", /* C_bye = 20120 */ colon }}}, /* CENTRY "bye" bye 3 h 20128 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20136 */
	{.type Absolute, {.p 0}},		/* dd 0 20144 */
	{.type FromDictionary, {.p M_terminate}, .src = "dd M_terminate"},		/* dd M_terminate 20152 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 20160 */
	{.type Header, {.hdr { 7, "include", /* C_include = 20176 */ colon }}}, /* CENTRY "include" include 7 ; this does not work h 20184 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 20192 */
	{.type FromDictionary, {.p M_rpush}, .src = "dd M_rpush"},		/* dd M_rpush 20200 */
	{.type FromDictionary, {.p C_input_fetch}, .src = "dd C_input_fetch	; save the old input onto the stack"},		/* dd C_input_fetch	; save the old input onto the stack 20208 */
	{.type FromDictionary, {.p M_rpop}, .src = "dd M_rpop"},		/* dd M_rpop 20216 */
	{.type FromDictionary, {.p C_count}, .src = "dd C_count"},		/* dd C_count 20224 */
	{.type FromDictionary, {.p C_ro}, .src = "dd C_ro"},		/* dd C_ro 20232 */
	{.type FromDictionary, {.p C_open_file}, .src = "dd C_open_file"},		/* dd C_open_file 20240 */
	{.type FromDictionary, {.p C_qfcheck}, .src = "dd C_qfcheck"},		/* dd C_qfcheck 20248 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd		; open the new file"},		/* dd MV_Infd		; open the new file 20256 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20264 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 20272 */
	{.type Header, {.hdr { 5, "crash", /* C_crash = 20288 */ colon }}}, /* CENTRY "crash" crash 5 h 20296 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20304 */
	{.type FromDictionary, {.p L251}, .src = "dd L251"},		/* dd L251 20312 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20320 */
	{.type Absolute, {.p 30}},		/* dd 30 20328 */
	{.type FromDictionary, {.p C_type}, .src = "dd C_type"},		/* dd C_type 20336 */
	{.type FromDictionary, {.p C_cr}, .src = "dd C_cr"},		/* dd C_cr 20344 */
	{.type FromDictionary, {.p C_abort}, .src = "dd C_abort"},		/* dd C_abort 20352 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 20360 */
	{.type Header, {.hdr { 4, "quit", /* C_quit = 20376 */ colon }}}, /* CENTRY "quit" quit 4 ; interpreter loop h 20384 */
	{.type FromDictionary, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 20392 */
	{.type FromDictionary, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 20400 */
	{.type FromDictionary, {.p C_word}, .src = "dd C_word"},		/* dd C_word 20408 */
/* ; dd MV_toLimit	; show the line read, for debugging *//* ; dd M_fetch *//* ; dd MV_Tib *//* ; dd MC_STDOUT *//* ; dd M_fswrite *//* ; dd M_drop		; drop the return value of write *//* ; dd C_cr *//* ; dd C_space */	{.type FromDictionary, {.p C_interpret}, .src = "dd C_interpret"},		/* dd C_interpret 20416 */
	{.type FromDictionary, {.p M_jump}, .src = "dd M_jump"},		/* dd M_jump 20424 */
	{.type FromDictionary, {.p L_C_quit}, .src = "dd L_C_quit"},		/* dd L_C_quit 20432 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed?"},		/* dd M_exitcolon	; why is this needed? 20440 */
	{.type Header, {.hdr { 7, "(abort)", /* C_parenabort = 20456 */ colon }}}, /* CENTRY "(abort)" parenabort 7 ; TODO correct below stack notations h 20464 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State	; ( mv_State -- )"},		/* dd MV_State	; ( mv_State -- ) 20472 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off	; off sets variable state = 0"},		/* dd C_off	; off sets variable state = 0 20480 */
	{.type FromDictionary, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 20488 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd"},		/* dd MV_Infd 20496 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20504 */
	{.type FromDictionary, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 20512 */
	{.type FromDictionary, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 20520 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20528 */
	{.type FromDictionary, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 20536 */
	{.type FromDictionary, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 20544 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20552 */
	{.type FromDictionary, {.p C_stdinput}, .src = "dd C_stdinput"},		/* dd C_stdinput 20560 */
	{.type FromDictionary, {.p C_quit}, .src = "dd C_quit	; quit resets stacks and is the interpreter loop"},		/* dd C_quit	; quit resets stacks and is the interpreter loop 20568 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon	; why is this needed? quit does not return unless it breaks"},		/* dd M_exitcolon	; why is this needed? quit does not return unless it breaks 20576 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal	; test code"},		/* dd M_literal	; test code 20584 */
	{.type Absolute, {.p 66}},		/* dd 66 20592 */
	{.type FromDictionary, {.p MV_Wordb}, .src = "dd MV_Wordb"},		/* dd MV_Wordb 20600 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20608 */
	{.type FromDictionary, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 20616 */
	{.type FromDictionary, {.p MV_Wordb}, .src = "dd MV_Wordb"},		/* dd MV_Wordb 20624 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20632 */
	{.type Absolute, {.p 1}},		/* dd 1 20640 */
	{.type FromDictionary, {.p M_syswrite}, .src = "dd M_syswrite"},		/* dd M_syswrite 20648 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop		; drop the return value of write"},		/* dd M_drop		; drop the return value of write 20656 */
	{.type FromDictionary, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 20664 */
	{.type FromDictionary, {.p MV_Wordb}, .src = "dd MV_Wordb"},		/* dd MV_Wordb 20672 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20680 */
	{.type Absolute, {.p 1}},		/* dd 1 20688 */
	{.type FromDictionary, {.p M_sysread}, .src = "dd M_sysread"},		/* dd M_sysread 20696 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop		; drop the return value of read"},		/* dd M_drop		; drop the return value of read 20704 */
	{.type Header, {.hdr { 10, "initialize", /* C_initialize = 20728 */ colon }}}, /* CENTRY "initialize" initialize 10 ; initialize buffer file names, why not hard code this? h 20736 */
	{.type FromDictionary, {.p MV_Bufferfilenames}, .src = "dd MV_Bufferfilenames"},		/* dd MV_Bufferfilenames 20744 */
	{.type FromDictionary, {.p MC_NBUFFERS}, .src = "dd MC_NBUFFERS"},		/* dd MC_NBUFFERS 20752 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20760 */
	{.type Absolute, {.p 0}},		/* dd 0 20768 */
	{.type FromDictionary, {.p M_doinit}, .src = "dd M_doinit"},		/* dd M_doinit 20776 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20784 */
	{.type Absolute, {.p 1}},		/* dd 1 20792 */
	{.type FromDictionary, {.p C_cells}, .src = "dd C_cells"},		/* dd C_cells 20800 */
	{.type FromDictionary, {.p M_plus}, .src = "dd M_plus"},		/* dd M_plus 20808 */
	{.type FromDictionary, {.p M_dup}, .src = "dd M_dup"},		/* dd M_dup 20816 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20824 */
	{.type Absolute, {.p 0}},		/* dd 0 20832 */
	{.type FromDictionary, {.p M_xswap}, .src = "dd M_xswap"},		/* dd M_xswap 20840 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 20848 */
	{.type FromDictionary, {.p M_doloop}, .src = "dd M_doloop"},		/* dd M_doloop 20856 */
	{.type FromDictionary, {.p L150}, .src = "dd L150"},		/* dd L150 20864 */
	{.type FromDictionary, {.p M_drop}, .src = "dd M_drop"},		/* dd M_drop 20872 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20880 */
	{.type FromDictionary, {.p L121}, .src = "dd L121"},		/* dd L121 20888 */
	{.type FromDictionary, {.p C_wordfilename_store}, .src = "dd C_wordfilename_store"},		/* dd C_wordfilename_store 20896 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20904 */
	{.type FromDictionary, {.p L122}, .src = "dd L122"},		/* dd L122 20912 */
	{.type FromDictionary, {.p C_linefilename_store}, .src = "dd C_linefilename_store"},		/* dd C_linefilename_store 20920 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20928 */
	{.type FromDictionary, {.p L123}, .src = "dd L123"},		/* dd L123 20936 */
	{.type FromDictionary, {.p C_doublequotefilename_store}, .src = "dd C_doublequotefilename_store"},		/* dd C_doublequotefilename_store 20944 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 20952 */
	{.type FromDictionary, {.p L124}, .src = "dd L124"},		/* dd L124 20960 */
	{.type FromDictionary, {.p C_closeparenfilename_store}, .src = "dd C_closeparenfilename_store"},		/* dd C_closeparenfilename_store 20968 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 20976 */
	{.type Header, {.hdr { 4, "boot", /* C_boot = 20992 */ colon }}}, /* CENTRY "boot" boot 4 h 21000 */
	{.type FromDictionary, {.p M_reset}, .src = "dd M_reset ; initialize return stack"},		/* dd M_reset ; initialize return stack 21008 */
	{.type FromDictionary, {.p M_clear}, .src = "dd M_clear	; SP = sstack_end initialize data stack"},		/* dd M_clear	; SP = sstack_end initialize data stack 21016 */
	{.type FromDictionary, {.p M_literal}, .src = "dd M_literal"},		/* dd M_literal 21024 */
	{.type FromDictionary, {.p C_parenabort}, .src = "dd C_parenabort ; ( (abort) -- )"},		/* dd C_parenabort ; ( (abort) -- ) 21032 */
	{.type FromDictionary, {.p MV_Abortvec}, .src = "dd MV_Abortvec	; variable that puts (abort) code address on the stack"},		/* dd MV_Abortvec	; variable that puts (abort) code address on the stack 21040 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; variable abortvec = (abort) code address"},		/* dd M_store	; variable abortvec = (abort) code address 21048 */
	{.type FromDictionary, {.p MV_Wordb}, .src = "dd MV_Wordb	; variable puts address of wordbuffer on the top of stack"},		/* dd MV_Wordb	; variable puts address of wordbuffer on the top of stack 21056 */
	{.type FromDictionary, {.p MV_Wordbuf}, .src = "dd MV_Wordbuf ; variable wordbuf"},		/* dd MV_Wordbuf ; variable wordbuf 21064 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; variable wordbuf = address of wordbuffer"},		/* dd M_store	; variable wordbuf = address of wordbuffer 21072 */
	{.type FromDictionary, {.p MV_Dp}, .src = "dd MV_Dp"},		/* dd MV_Dp 21080 */
	{.type FromDictionary, {.p MV_H0}, .src = "dd MV_H0	; H0 = here at startup"},		/* dd MV_H0	; H0 = here at startup 21088 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 21096 */
	{.type FromDictionary, {.p MC_STDIN}, .src = "dd MC_STDIN"},		/* dd MC_STDIN 21104 */
	{.type FromDictionary, {.p MV_Infd}, .src = "dd MV_Infd	; might be overwritten by args below"},		/* dd MV_Infd	; might be overwritten by args below 21112 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store	; stdin = 0"},		/* dd M_store	; stdin = 0 21120 */
	{.type FromDictionary, {.p MC_STDOUT}, .src = "dd MC_STDOUT"},		/* dd MC_STDOUT 21128 */
	{.type FromDictionary, {.p MV_Outfd}, .src = "dd MV_Outfd"},		/* dd MV_Outfd 21136 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 21144 */
	{.type FromDictionary, {.p MC_STDERR}, .src = "dd MC_STDERR"},		/* dd MC_STDERR 21152 */
	{.type FromDictionary, {.p MV_Errfd}, .src = "dd MV_Errfd"},		/* dd MV_Errfd 21160 */
	{.type FromDictionary, {.p M_store}, .src = "dd M_store"},		/* dd M_store 21168 */
	{.type FromDictionary, {.p MV_State}, .src = "dd MV_State"},		/* dd MV_State 21176 */
	{.type FromDictionary, {.p C_off}, .src = "dd C_off	; off stores 0 at state"},		/* dd C_off	; off stores 0 at state 21184 */
	{.type FromDictionary, {.p C_decimal}, .src = "dd C_decimal	; decimal sets base = 10"},		/* dd C_decimal	; decimal sets base = 10 21192 */
	{.type FromDictionary, {.p C_initialize}, .src = "dd C_initialize	; sets up the buffer filenames"},		/* dd C_initialize	; sets up the buffer filenames 21200 */
	{.type FromDictionary, {.p C_args}, .src = "dd C_args	; process args"},		/* dd C_args	; process args 21208 */
	{.type FromDictionary, {.p C_close_input}, .src = "dd C_close_input ; if the args opened an input"},		/* dd C_close_input ; if the args opened an input 21216 */
	{.type FromDictionary, {.p C_stdinput}, .src = "dd C_stdinput	; read lines from stdin, args can change it later"},		/* dd C_stdinput	; read lines from stdin, args can change it later 21224 */
	{.type FromDictionary, {.p C_quit}, .src = "dd C_quit	; interpreter loop when there are no args or fall through after processing args"},		/* dd C_quit	; interpreter loop when there are no args or fall through after processing args 21232 */
	{.type FromDictionary, {.p M_exitcolon}, .src = "dd M_exitcolon"},		/* dd M_exitcolon 21240 */
	{.type Chars, {.str 6}},		/* 21240 */
	{.type Chars, {.str "#c/pid"}},		/* 21247 */
	{.type Chars, {.str 3}},		/* 21247 */
	{.type Chars, {.str "#p/"}},		/* 21251 */
	{.type Chars, {.str 5}},		/* 21251 */
	{.type Chars, {.str "/args"}},		/* 21257 */
	{.type Chars, {.str 3}},		/* 21257 */
	{.type Chars, {.str "#n/"}},		/* 21261 */
	{.type Chars, {.str 5}},		/* 21261 */
	{.type Chars, {.str "/word"}},		/* 21267 */
	{.type Chars, {.str 5}},		/* 21267 */
	{.type Chars, {.str "/line"}},		/* 21273 */
	{.type Chars, {.str 12}},		/* 21274 */
	{.type Chars, {.str "/doublequote"}},		/* 21287 */
	{.type Chars, {.str 11}},		/* 21288 */
	{.type Chars, {.str "/closeparen"}},		/* 21300 */
	{.type Chars, {.str "unable to restore input"}},		/* 21324 */
	{.type Chars, {.str 17}},		/* 21325 */
	{.type Chars, {.str "open file failed"}},		/* 21342 */
	{.type Chars, {.str 17}},		/* 21343 */
	{.type Chars, {.str "read file failed"}},		/* 21360 */
	{.type Chars, {.str " Q?"}},		/* 21364 */
	{.type Chars, {.str " stack underflow"}},		/* 21381 */
	{.type Chars, {.str " I?"}},		/* 21385 */
	{.type Chars, {.str " C?"}},		/* 21389 */
	{.type Chars, {.str "I/O error"}},		/* 21399 */
	{.type Chars, {.str "uninitialized execution vector"}},		/* 21430 */
	{.type Chars, {.str " ok"}},		/* 21434 */
	{.type Chars, {.str "input line is longer than 4096 bytes"}},		/* 21471 */
	{.type Chars, {.str "read error"}},		/* 21482 */
};

