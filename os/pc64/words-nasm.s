 CENTRY `false`, c_false, 5
 dd m_literal
 dd 0
 dd m_exitcolon
 CENTRY `true`, c_true, 4
 dd m_literal
 dd -1
 dd m_exitcolon
 CENTRY `bl`, c_bl, 2
 dd m_literal
 dd 32
 dd m_exitcolon
 CENTRY `on`, c_on, 2		; ( a --  ) (G stores -1 at a )
 dd m_literal
 dd -1
 dd m_xswap
 dd m_store
 dd m_exitcolon
 CENTRY `off`, c_off, 3		; ( a --  ) (G stores 0 at a )
 dd m_literal
 dd 0
 dd m_xswap
 dd m_store
 dd m_exitcolon
 CENTRY `>body`, c_tobody, 5
 dd m_literal
 dd 8
 dd m_plus
 dd m_exitcolon
 CENTRY `aligned`, c_aligned, 7
 dd m_literal
 dd 7
 dd m_plus
 dd m_literal
 dd -8
 dd m_binand
 dd m_exitcolon
 CENTRY `cells`, c_cells, 5
 dd m_literal
 dd 3			; (index << 2) -> (index << 3)for amd64
 dd m_lshift
 dd m_exitcolon
 CENTRY `cell+`, c_cellplus, 5
 dd m_literal
 dd 1
 dd c_cells
 dd m_plus
 dd m_exitcolon
 CENTRY `depth`, c_depth, 5
 dd m_s0
 dd m_stackptr
 dd m_minus
 dd m_literal
 dd 3
 dd m_rshift
 dd m_literal
 dd 1
 dd m_minus
 dd m_exitcolon
 CENTRY `nip`, c_nip, 3
 dd m_xswap
 dd m_drop
 dd m_exitcolon
 CENTRY `rot`, c_rot, 3
 dd m_rpush
 dd m_xswap
 dd m_rpop
 dd m_xswap
 dd m_exitcolon
 CENTRY `2drop`, c_2drop, 5
 dd m_drop
 dd m_drop
 dd m_exitcolon
 CENTRY `2dup`, c_2dup, 4
 dd m_over
 dd m_over
 dd m_exitcolon
 CENTRY `2nip`, c_2nip, 4
 dd c_nip
 dd c_nip
 dd m_exitcolon
 CENTRY `2swap`, c_2swap, 5
 dd c_rot
 dd m_rpush
 dd c_rot
 dd m_rpop
 dd m_exitcolon
 CENTRY `?dup`, c_qdup, 4 ; if (tos != 0) dup ( n -- ) TODO correct stack notations
 dd m_dup	; ( n n -- )
 dd m_dup	; ( n n n -- )
 dd m_literal
 dd 0		; ( n n n 0 -- )
 dd m_equal	; ( n n f -- )
 dd m_cjump	; ( n n -- )
 dd L20
 dd m_drop	; tos == 0 ( n -- )
L20:		; tos != 0 ( n n -- )
 dd m_exitcolon
 CENTRY `pick`, c_pick, 4
 dd c_qdup
 dd m_cjump
 dd L22
 dd m_literal
 dd 1
 dd m_plus
 dd c_cells
 dd m_stackptr
 dd m_plus
 dd m_fetch
 dd m_jump
 dd L23
L22:
 dd m_dup
L23:
 dd m_exitcolon
 CENTRY `tuck`, c_tuck, 4
 dd m_dup
 dd m_rpush
 dd m_xswap
 dd m_rpop
 dd m_exitcolon
 CENTRY `/`, c_divides, 1
 dd m_slashmod
 dd c_nip
 dd m_exitcolon
 CENTRY `+!`, c_plusstore, 2
 dd m_dup
 dd m_fetch
 dd c_rot
 dd m_plus
 dd m_xswap
 dd m_store
 dd m_exitcolon
 CENTRY `invert`, c_invert, 6
 dd m_literal
 dd -1
 dd m_binxor
 dd m_exitcolon
 CENTRY `mod`, c_mod, 3
 dd m_slashmod
 dd m_drop
 dd m_exitcolon
 CENTRY `1+`, c_1plus, 2
 dd m_literal
 dd 1
 dd m_plus
 dd m_exitcolon
 CENTRY `1-`, c_1minus, 2
 dd m_literal
 dd 1
 dd m_minus
 dd m_exitcolon
 CENTRY `negate`, c_negate, 6
 dd m_literal
 dd 0
 dd m_xswap
 dd m_minus
 dd m_exitcolon
 CENTRY `2*`, c_2multiplies, 2
 dd m_literal
 dd 1
 dd m_lshift
 dd m_exitcolon
 CENTRY `2/`, c_2divides, 2
 dd m_literal
 dd 1
 dd m_rshifta
 dd m_exitcolon
 CENTRY `0=`, c_0eq, 2
 dd m_literal
 dd 0
 dd m_equal
 dd m_exitcolon
 CENTRY `0<`, c_0lt, 2
 dd m_literal
 dd 0
 dd m_less
 dd m_exitcolon
 CENTRY `0>`, c_0gt, 2
 dd m_literal
 dd 0
 dd m_greater
 dd m_exitcolon
 CENTRY `<>`, c_neq, 2
 dd m_equal
 dd c_invert
 dd m_exitcolon
 CENTRY `0<>`, c_0neq, 3
 dd m_literal
 dd 0
 dd c_neq
 dd m_exitcolon
 CENTRY `max`, c_max, 3
 dd c_2dup
 dd m_greater
 dd m_cjump
 dd L40
 dd m_drop
 dd m_jump
 dd L41
L40:
 dd c_nip
L41:
 dd m_exitcolon
 CENTRY `min`, c_min, 3
 dd c_2dup
 dd m_less
 dd m_cjump
 dd L43
 dd m_drop
 dd m_jump
 dd L44
L43:
 dd c_nip
L44:
 dd m_exitcolon
 CENTRY `signum`, c_signum, 6
 dd m_dup
 dd c_0gt
 dd m_cjump
 dd L46
 dd m_drop
 dd m_literal
 dd 1
 dd m_jump
 dd L47
L46:
 dd c_0lt
 dd m_cjump
 dd L48
 dd m_literal
 dd -1
 dd m_jump
 dd L49
L48:
 dd m_literal
 dd 0
L49:
L47:
 dd m_exitcolon
 CENTRY `within`, c_within, 6
 dd m_rpush
 dd m_over
 dd m_greater
 dd c_0eq
 dd m_xswap
 dd m_rpop
 dd m_greater
 dd c_0eq
 dd m_binand
 dd m_exitcolon
 CENTRY `abs`, c_abs, 3
 dd m_dup
 dd c_0lt
 dd m_cjump
 dd L52
 dd c_negate
L52:
 dd m_exitcolon

 CENTRY `key`, c_key, 3	 ; ( -- c ) (G read a single character from the input onto the stack )
 dd m_literal
 dd 1			; ( 1 -- )
 dd mv_Iobuf		; variable iobuf to store the character read
 dd mv_Infd
 dd m_fetch		; ( 1 Iobuf -- 1 Iobuf infd )
 dd m_fthread	; ( 1 Iobuf infd -- n )
 dd c_0eq
 dd m_cjump		; if 0 characters read
 dd L78			; if qread n != 0, jump to L78. If n == 0, jump over
 dd mv_Eof
 dd c_on		; EOF
 dd m_literal
 dd -1			; return -1 when EOF
 dd m_jump
 dd L79
L78:
 dd mv_Iobuf		; get the character from Iobuf to stack
 dd m_cfetch	; ( -- c ) return the character read if not EOF
L79:
 dd m_exitcolon

 CENTRY `emit`, c_emit, 4	; ( character -- )
 dd mv_Iobuf		; variable iobuf address
 dd m_cstore	; variable iobuf has character
 dd mv_Iobuf		; variable iobuf address
 dd m_literal
 dd 1
 dd m_xswap		; ( iobuf 1 --  1 iobuf )
 dd mv_Outfd
 dd m_fetch		; outfd
 dd m_fthwrite	; ( 1 iobuf outfd --  )
 dd m_exitcolon

 CENTRY `type`, c_type, 4	; ( addr n -- ) 
 dd m_xswap			; ( addr n --  n addr )
 dd m_literal
 dd 1				; stdout
 dd m_fthwrite			; ( n addr 1 --  )
 dd m_exitcolon

 CENTRY `cr`, c_cr, 2
 dd m_literal
 dd 10			; ascii value of carriage return
 dd c_emit			; emit
 dd m_exitcolon
 CENTRY `space`, c_space, 5
 dd c_bl
 dd c_emit
 dd m_exitcolon
 CENTRY `emits`, c_emits, 5
L85:
 dd c_qdup
 dd m_cjump
 dd L86
 dd m_over
 dd c_emit
 dd c_1minus
 dd m_jump
 dd L85
L86:
 dd m_drop
 dd m_exitcolon
 CENTRY `spaces`, c_spaces, 6
 dd c_bl
 dd m_xswap
 dd c_emits
 dd m_exitcolon
 CENTRY `count`, c_count, 5 ; ( a -- a+1 n ) a = counted string
 dd c_1plus
 dd m_dup
 dd c_1minus
 dd m_cfetch
 dd m_exitcolon
 CENTRY `compare`, c_compare, 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search
 dd c_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 ) 
 dd c_2dup	; ( -- a1 a2 n2 n1 n2 n1 )
 dd m_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- )
 dd m_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- )
 dd c_min	; ( -- a1 a2 nmin ) (R n1 n2 -- )
 dd m_literal
 dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- )
 dd m_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- )
L55:
 dd m_over
 dd m_i
 dd m_plus
 dd m_cfetch
 dd m_over
 dd m_i
 dd m_plus
 dd m_cfetch
 dd m_minus
 dd c_signum
 dd c_qdup
 dd m_cjump
 dd L56
 dd c_2nip
 dd m_unloop
 dd m_unloop
 dd m_exitcolon
L56:
 dd m_doloop
 dd L55
 dd c_2drop	; ( a1 a2 -- ) (R n1 n2 -- )
 dd m_rpop
 dd m_rpop	; ( n2 n1 -- ) (R -- )
 dd m_minus	; ( -- n1-n2 )
 dd c_signum
 dd m_exitcolon
 CENTRY `erase`, c_erase, 5
 dd m_literal
 dd 0
 dd m_doinit
L58:
 dd m_literal
 dd 0
 dd m_over
 dd m_cstore
 dd c_1plus
 dd m_doloop
 dd L58
 dd m_drop
 dd m_exitcolon
 CENTRY `fill`, c_fill, 4
 dd m_xswap
 dd m_literal
 dd 0
 dd m_doinit
L60:
 dd c_2dup
 dd m_xswap
 dd m_i
 dd m_plus
 dd m_cstore
 dd m_doloop
 dd L60
 dd c_2drop
 dd m_exitcolon
 CENTRY `blank`, c_blank, 5
 dd c_bl
 dd c_fill
 dd m_exitcolon
 CENTRY `search`, c_search, 6
 dd mv_Searchlen
 dd m_store
 dd m_xswap
 dd m_dup
 dd m_rpush
 dd mv_Searchlen
 dd m_fetch
 dd m_minus
 dd c_1plus
 dd m_literal
 dd 0
 dd m_doinit
L64:
 dd m_over
 dd m_i
 dd m_plus
 dd m_over
 dd mv_Searchlen
 dd m_fetch
 dd m_xswap
 dd mv_Searchlen
 dd m_fetch
 dd c_compare
 dd c_0eq
 dd m_cjump
 dd L65
 dd m_drop
 dd m_i
 dd m_plus
 dd m_i
 dd m_unloop
 dd m_rpop
 dd m_xswap
 dd m_minus
 dd c_true
 dd m_exitcolon
L65:
 dd m_doloop
 dd L64
 dd m_drop
 dd m_rpop
 dd c_false
 dd m_exitcolon
 CENTRY `here`, c_here, 4
 dd m_h0
 dd m_fetch
 dd m_exitcolon
 CENTRY `,`, c_comma, 1
 dd c_here
 dd m_store
 dd m_literal
 dd 8
 dd m_h0
 dd c_plusstore
 dd m_exitcolon
 CENTRY `c,`, c_c, 2
 dd c_here
 dd m_cstore
 dd m_literal
 dd 1
 dd m_h0
 dd c_plusstore
 dd m_exitcolon
 CENTRY `allot`, c_allot, 5
 dd m_h0
 dd c_plusstore
 dd m_exitcolon
 CENTRY `pad`, c_pad, 3
 dd c_here
 dd m_literal
 dd 256
 dd m_plus
 dd m_exitcolon
 CENTRY `align`, c_align, 5
 dd c_here
 dd c_aligned
 dd m_h0
 dd m_store
 dd m_exitcolon
 CENTRY `unused`, c_unused, 6
 dd m_h0
 dd m_fetch
 dd c_here
 dd m_minus
 dd m_exitcolon
 CENTRY `<#`, c_fromhash, 2
 dd c_pad
 dd m_literal
 dd 1024
 dd m_plus
 dd mv_toNum
 dd m_store
 dd m_exitcolon
 CENTRY `#`, c_hash, 1
 dd mv_Base
 dd m_fetch
 dd m_uslashmod
 dd m_xswap
 dd m_dup
 dd m_literal
 dd 9
 dd m_greater
 dd m_cjump
 dd L92
 dd m_literal
 dd 97
 dd m_plus
 dd m_literal
 dd 10
 dd m_minus
 dd m_jump
 dd L93
L92:
 dd m_literal
 dd 48
 dd m_plus
L93:
 dd mv_toNum
 dd m_fetch
 dd c_1minus
 dd m_dup
 dd mv_toNum
 dd m_store
 dd m_cstore
 dd m_exitcolon
 CENTRY `#s`, c_hashs, 2
L95:
 dd c_hash
 dd m_dup
 dd m_cjump
 dd L96
 dd m_jump
 dd L95
L96:
 dd m_exitcolon
 CENTRY `#>`, c_hashfrom, 2
 dd m_drop
 dd mv_toNum
 dd m_fetch
 dd m_dup
 dd c_pad
 dd m_literal
 dd 1024
 dd m_plus
 dd m_xswap
 dd m_minus
 dd m_exitcolon
 CENTRY `hold`, c_hold, 4
 dd mv_toNum
 dd m_fetch
 dd c_1minus
 dd m_dup
 dd m_rpush
 dd m_cstore
 dd m_rpop
 dd mv_toNum
 dd m_store
 dd m_exitcolon
 CENTRY `sign`, c_sign, 4
 dd c_0lt
 dd m_cjump
 dd L100
 dd m_literal
 dd 45
 dd c_hold
L100:
 dd m_exitcolon
 CENTRY `.`, c_dot, 1
 dd m_dup
 dd c_abs
 dd c_fromhash
 dd c_hashs
 dd m_xswap
 dd c_sign
 dd c_hashfrom
 dd c_type
 dd c_space
 dd m_exitcolon
 CENTRY `.r`, c_dotr, 2
 dd m_rpush
 dd m_dup
 dd c_abs
 dd c_fromhash
 dd c_hashs
 dd m_xswap
 dd c_sign
 dd c_hashfrom
 dd m_rpop
 dd m_over
 dd m_minus
 dd m_literal
 dd 0
 dd c_max
 dd c_spaces
 dd c_type
 dd m_exitcolon
 CENTRY `hex`, c_hex, 3
 dd m_literal
 dd 16
 dd mv_Base
 dd m_store
 dd m_exitcolon
 CENTRY `decimal`, c_decimal, 7
 dd m_literal
 dd 10
 dd mv_Base
 dd m_store
 dd m_exitcolon
 CENTRY `digit`, c_digit, 5
 dd m_dup
 dd m_literal
 dd 65
 dd m_literal
 dd 91
 dd c_within
 dd m_cjump
 dd L106
 dd m_literal
 dd 55
 dd m_minus
 dd m_jump
 dd L107
L106:
 dd m_dup
 dd m_literal
 dd 97
 dd m_literal
 dd 123
 dd c_within
 dd m_cjump
 dd L108
 dd m_literal
 dd 87
 dd m_minus
 dd m_jump
 dd L109
L108:
 dd m_dup
 dd m_literal
 dd 48
 dd m_literal
 dd 58
 dd c_within
 dd m_cjump
 dd L110
 dd m_literal
 dd 48
 dd m_minus
 dd m_jump
 dd L111
L110:
 dd m_drop
 dd c_false
 dd m_exitcolon
L111:
L109:
L107:
 dd m_dup
 dd mv_Base
 dd m_fetch
 dd m_less
 dd m_cjump
 dd L112
 dd c_true
 dd m_jump
 dd L113
L112:
 dd m_drop
 dd c_false
L113:
 dd m_exitcolon
 CENTRY `number`, c_number, 6
 dd m_xswap
 dd m_dup
 dd m_cfetch
 dd m_literal
 dd 45
 dd m_equal
 dd m_cjump
 dd L115
 dd c_1plus
 dd m_xswap
 dd c_1minus
 dd m_literal
 dd -1
 dd m_rpush
 dd m_jump
 dd L116
L115:
 dd m_xswap
 dd m_literal
 dd 1
 dd m_rpush
L116:
 dd m_dup
 dd m_rpush
 dd m_literal
 dd 0
 dd m_xswap
 dd m_literal
 dd 0
 dd m_doinit
L117:
 dd mv_Base
 dd m_fetch
 dd m_multiply
 dd m_over
 dd m_i
 dd m_plus
 dd m_cfetch
 dd c_digit
 dd m_cjump
 dd L118
 dd m_plus
 dd m_jump
 dd L119
L118:
 dd m_drop
 dd m_unloop
 dd m_rpop
 dd m_rpop
 dd m_drop
 dd c_false
 dd m_exitcolon
L119:
 dd m_doloop
 dd L117
 dd m_rpop
 dd m_drop
 dd c_nip
 dd m_rpop
 dd m_multiply
 dd c_true
 dd m_exitcolon
 CENTRY `abort`, c_abort, 5
 dd mv_Abortvec
 dd m_fetch
 dd m_execute
 dd m_exitcolon
 CENTRY `source`, c_source, 6
 dd mv_Sourcebuf
 dd m_fetch
 dd m_exitcolon
 CENTRY `current-input`, c_current_input, 13 ; ( -- c ) read the next character from the location in Sourcebuf
 dd mv_toIn
 dd m_fetch
 dd c_source
 dd m_plus		; Sourcebuf + >In
 dd m_cfetch
 dd m_exitcolon
 CENTRY `save-input`, c_save_input, 10
 dd mv_Infd 
 dd mv_toIn
 dd m_fetch
 dd mv_toLimit
 dd m_fetch
 dd mv_Sourcebuf
 dd m_fetch
 dd mv_Blk
 dd m_fetch
 dd m_literal
 dd 5
 dd m_exitcolon
 CENTRY `default-input`, c_default_input, 13
 dd mc_STDIN
 dd mv_toIn
 dd c_off
 dd mv_toLimit
 dd c_off
 dd mc_TIB
 dd mv_Sourcebuf
 dd m_store
 dd mv_Blk
 dd c_off
 dd m_exitcolon
 CENTRY `restore-input`, c_restore_input, 13
 dd mv_Eof
 dd c_off
 dd m_literal
 dd 5
 dd c_neq
 dd m_cjump
 dd L133
 dd c_default_input
 dd c_false
 dd m_jump
 dd L134
L133:
 dd mv_Blk
 dd m_store
 dd mv_Sourcebuf
 dd m_store
 dd mv_toLimit
 dd m_store
 dd mv_toIn
 dd m_store
 dd mv_Infd
 dd m_store
 dd c_true
L134:
 dd m_exitcolon
 CENTRY `?restore-input`, c_qrestore_input, 14
 dd c_restore_input
 dd c_0eq
 dd m_cjump
 dd L136
 dd c_space
 dd m_literal
 dd L137
 dd m_literal
 dd 23
 dd c_type
 dd c_cr
 dd c_abort
L136:
 dd m_exitcolon

 CENTRY `next-input`, c_next_input, 10 ; when >In < >Limit ( -- true c ). ( --  0 false ) otherwise
 dd mv_toIn
 dd m_fetch
 dd mv_toLimit
 dd m_fetch
 dd m_less
 dd m_cjump
 dd L139	; >In >= >Limit
 dd c_true	; >In < >Limit
 dd c_current_input	; ( -- c )
 dd m_jump
 dd L140
L139:
 dd m_literal
 dd 0
 dd c_false
L140:
 dd m_exitcolon

 CENTRY `parse`, c_parse, 5	; ( c -- a ) Place the counted string in the address in Wordbuf and return that address. c = word delimiter.
 dd m_rpush		; ( c -- ) (R -- c )
 dd mv_Wordbuf
 dd m_fetch		; ( -- Wordb )
 dd c_1plus		; ( Wordb -- Wordb+1 )
L142:
 dd c_next_input ; ( Wordb+1 -- Wordb+1 f c )
 dd m_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c )
 dd c_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) )
 dd m_binand
 dd m_cjump
 dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew
 dd c_current_input	; ( Wordb+1 -- Wordb+1 c )
 dd m_over
 dd m_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1
 dd c_1plus		; ( Wordb+1 -- Wordb+2 )
 dd m_literal
 dd 1
 dd mv_toIn
 dd c_plusstore	; >In++
 dd m_jump
 dd L142		; ( Wordb+2 ) repeat
L143:		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew
 dd m_literal
 dd 1
 dd mv_toIn
 dd c_plusstore	; >In++
 dd m_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- )
 dd m_drop		; (Wordb+1 c -- Wordb+1)
 dd mv_Wordbuf
 dd m_fetch		; (Wordb+1 -- Wordb+1 Wordb)
 dd m_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb)
 dd m_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb)
 dd m_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb)
 dd c_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb)
 dd m_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb)
 dd m_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now.
 dd m_rpop		; ( -- Wordb) (R Wordb -- )
 dd m_exitcolon

 CENTRY `word`, c_word, 4 ; ( c -- a ) skip the c's. Placed the counted string in a (as in Wordbuf)
 dd m_rpush	; ( -- ) (R -- c )
L145:
 dd c_next_input ; ( -- f c2 ) (R c1 -- )
 dd m_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial )
 dd m_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial )
 dd m_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial )
 dd m_cjump
 dd L146		; >In >= >Limit || cinitial != cnew
 dd m_literal	; >In < >Limit && cinitial == cnew
 dd 1
 dd mv_toIn
 dd c_plusstore	; >In++
 dd m_jump		; repeat
 dd L145
L146:
 dd m_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character
 dd c_parse
 dd m_exitcolon

 CENTRY `accept`, c_accept, 6	; ( a n -- n ) get line or n chars or EOF from input and store at a
 dd m_xswap	; ( n a -- )
 dd m_dup	; ( n a a -- )
 dd m_rpush
 dd m_rpush	; ( n -- ) (R a a -- )
L148:
 dd c_qdup	; ( n n -- ) (R a a -- )
 dd m_cjump	; (if)
 dd L149	; n == 0
 dd c_key	; n > 0 ( n -- n c )
 dd m_dup	; ( -- n c c )
 dd m_literal
 dd 10		; ( -- n c c 10 )
 dd m_equal	; ( n c c 10 -- n c f ) checking for newline
 dd m_over	; ( -- n c f c )
 dd m_literal
 dd -1		; ( -- n c f c -1 )
 dd m_equal	; ( -- n c f1 f2 )
 dd m_binor	; ( -- n c f )
 dd m_cjump
 dd L150
 dd c_2drop	; n == -1 || n == 10 (	-- )
 dd m_rpop
 dd m_rpop
 dd m_minus	; ( -- a2-a1 )
 dd m_exitcolon	; ( -- n ) (R -- )
L150:		; not EOF or newline, continue
 dd m_rfetch	; ( n c a -- ) (R a a -- )
 dd m_cstore	; store the character at a
 dd m_rpop	; ( n a -- ) (R a -- )
 dd c_1plus
 dd m_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address, a2 = current address
 dd c_1minus	; ( n -- n-1 )
 dd m_jump
 dd L148	; loop again for the next character
L149:		; n == 0 ( -- ) (R a1 a2 -- )
 dd m_rpop	; ( -- a2 ) (R a1 a2 -- a1 )
 dd m_rpop	; ( a2 a1 -- ) (R a1 -- )
 dd m_minus	; ( a2 a1 -- a2-a1 )
 dd m_exitcolon

 CENTRY `query`, c_query, 5	; read from input stream into the Text Input Buffer
 dd mv_Eof
 dd c_off		; clear EOF flag
 dd mc_TIB	; constant puts address of tibuffer on the top
 dd m_literal
 dd 4096	; ( tibuffer -- tibuffer 4096 )
 dd c_accept ; ( tibuffer 4096 -- n )
 dd m_dup	; ( n -- n n )
 dd c_0eq	; ( n n -- n f )
 dd mv_Eof
 dd m_fetch
 dd m_binand	; n == 0 && EOF
 dd m_cjump
 dd L152		; false condition
 dd m_drop		; n == 0 && EOF ( n -- )
 dd c_qrestore_input
 dd m_jump
 dd L153
L152:			; n > 0
 dd mv_toLimit
 dd m_store		; number of characters to read, >Limit = n
 dd mv_toIn
 dd c_off		; start from 0, >In = 0
L153:
 dd m_exitcolon

 CENTRY `refill`, c_refill, 6
 dd mv_Blk
 dd m_fetch
 dd m_cjump
 dd L155
 dd c_false
 dd m_jump
 dd L156
L155:
 dd c_query
 dd c_true
L156:
 dd m_exitcolon

 CENTRY `findname`, c_findname, 8 ; ( a1 -- a2 f ) ; loop through the dictionary names
 dd mv_Findadr
 dd m_store
 dd mv_Dp
 dd m_fetch	; get dictionary link
L158:
 dd c_qdup
 dd m_cjump
 dd L159	; seached until the first dictionary entry, get out
 dd m_dup	; ( a -- a a )
 dd c_cellplus	; lenth + initial name address
 dd m_cfetch	; length + initial name
 dd m_literal
 dd 64		; max name length?
 dd m_binand	; keep only the length
 dd m_cjump
 dd L160
 dd m_fetch
 dd m_jump
 dd L161
L160:		; valid length? ( a -- )
 dd m_dup
 dd c_cellplus
 dd c_count	; ( a1 a1+8 -- a1 a1+8+1 n )
 dd m_literal
 dd 63
 dd m_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63 )
 dd mv_Findadr
 dd m_fetch
 dd c_count	; ( a1 a1+8+1 n&63 a2 n2 -- a1 a1+8+1 n&63 a2+1 n2 )
 dd c_compare	; ( -- a1 n ) compare dictionary entry with name
 dd c_0eq	; found a match?
 dd m_cjump
 dd L162
 dd c_cellplus
 dd c_true
 dd m_exitcolon
L162:
 dd m_fetch
L161:
 dd m_jump
 dd L158
L159:
 dd mv_Findadr
 dd m_fetch
 dd c_false
 dd m_exitcolon
 CENTRY `find`, c_find, 4 ; ( a1 -- a2 f )?
 dd c_findname
 dd m_cjump
 dd L164
 dd m_dup
 dd m_cfetch
 dd m_xswap
 dd m_over
 dd m_literal
 dd 63
 dd m_binand
 dd m_plus
 dd c_1plus
 dd c_aligned
 dd m_xswap
 dd m_literal
 dd 128
 dd m_binand
 dd m_cjump
 dd L165
 dd m_literal
 dd 1
 dd m_jump
 dd L166
L165:
 dd m_literal
 dd -1
L166:
 dd m_exitcolon
 dd m_jump
 dd L167
L164:
 dd c_false
L167:
 dd m_exitcolon
 CENTRY `'`, c_single_quote, 1
 dd c_bl
 dd c_word
 dd c_find
 dd c_0eq
 dd m_cjump
 dd L169
 dd c_space
 dd c_count
 dd c_type
 dd m_literal
 dd L170
 dd m_literal
 dd 3
 dd c_type
 dd c_cr
 dd c_abort
L169:
 dd m_exitcolon
 CENTRY `?stack`, c_qstack, 6
 dd m_stackptr
 dd m_s0
 dd m_greater
 dd m_cjump
 dd L172
 dd m_literal
 dd L173
 dd m_literal
 dd 16
 dd c_type
 dd c_cr
 dd c_abort
L172:
 dd m_exitcolon

 CENTRY `interpret`, c_interpret, 9 ; there is stuff in TIB to be interpreted, >In and >Limit are set
L175:
 dd c_bl
 dd c_word	; ( bl -- a )
 dd m_dup
 dd m_cfetch
 dd c_0neq
 dd m_cjump
 dd L176	; count at a = 0
 dd c_find	; ( a -- ) a = address of counted string
 dd m_cjump
 dd L177
 dd m_execute
 dd c_qstack
 dd m_jump
 dd L178
L177:
 dd c_count
 dd c_number
 dd c_0eq
 dd m_cjump
 dd L179
 dd c_space
 dd c_type
 dd m_literal
 dd L180	; error I?
 dd m_literal
 dd 3
 dd c_type
 dd c_cr
 dd c_abort
L179:
L178:
 dd m_jump
 dd L175
L176:
 dd m_drop	; count at a = 0, ( a -- )
 dd m_exitcolon

 CENTRY `create`, c_create, 6
 dd c_align
 dd c_here
 dd m_rpush
 dd mv_Dp
 dd m_fetch
 dd c_comma
 dd c_bl
 dd c_word
 dd m_dup
 dd m_cfetch
 dd c_here
 dd m_xswap
 dd c_1plus
 dd m_dup
 dd m_rpush
 dd m_cmove
 dd m_rpop
 dd c_allot
 dd c_align
 dd m_literal
 dd m_variable
 dd m_fetch
 dd c_comma
 dd m_rpop
 dd mv_Dp
 dd m_store
 dd m_exitcolon
 CENTRY `variable`, c_variable, 8
 dd c_create
 dd m_literal
 dd 0
 dd c_comma
 dd m_exitcolon
 CENTRY `constant`, c_constant, 8
 dd c_create
 dd m_literal
 dd m_constant
 dd m_fetch
 dd c_here
 dd m_literal
 dd 1
 dd c_cells
 dd m_minus
 dd m_store
 dd c_comma
 dd m_exitcolon
 CENTRY `immediate`, c_immediate, 9
 dd mv_Dp
 dd m_fetch
 dd c_cellplus
 dd m_dup
 dd m_cfetch
 dd m_literal
 dd 128
 dd m_binor
 dd m_xswap
 dd m_cstore
 dd m_exitcolon
 CENTRY `>cfa`, c_tocfa, 4
 dd c_count
 dd m_literal
 dd 63
 dd m_binand
 dd m_plus
 dd c_aligned
 dd m_exitcolon
 CENTRY `compile`, c_compile, 7
 dd c_findname
 dd m_cjump
 dd L188
 dd m_dup
 dd m_cfetch
 dd m_literal
 dd 128
 dd m_binand
 dd m_cjump
 dd L189
 dd c_tocfa	; immediate
 dd m_execute
 dd c_qstack
 dd m_jump
 dd L190
L189:
 dd c_tocfa
 dd c_comma
L190:
 dd m_jump
 dd L191
L188:
 dd c_count
 dd c_number
 dd c_0eq
 dd m_cjump
 dd L192
 dd c_space
 dd c_type
 dd m_literal
 dd L193
 dd m_literal
 dd 3
 dd c_type
 dd c_cr
 dd c_abort
 dd m_jump
 dd L194
L192:
 dd m_literal
 dd m_literal
 dd c_comma
 dd c_comma
L194:
L191:
 dd m_exitcolon
 CENTRY `]`, c_close_bracket, 1
 dd mv_State
 dd c_on
L196:
 dd c_bl
 dd c_word
 dd m_dup
 dd m_cfetch
 dd c_0eq
 dd m_cjump
 dd L197
 dd m_drop
 dd c_refill
 dd m_jump
 dd L198
L197:
 dd c_compile
 dd mv_State
 dd m_fetch
L198:
 dd m_cjump
 dd L199
 dd m_jump
 dd L196
L199:
 dd m_exitcolon
 CIENTRY `[`, ci_open_bracket, 1
 dd mv_State
 dd c_off
 dd m_exitcolon
 CENTRY `smudge`, c_smudge, 6
 dd mv_Dp
 dd m_fetch
 dd c_cellplus
 dd m_dup
 dd m_cfetch
 dd m_literal
 dd 64
 dd m_binor
 dd m_xswap
 dd m_cstore
 dd m_exitcolon
 CENTRY `reveal`, c_reveal, 6
 dd mv_Dp
 dd m_fetch
 dd c_cellplus
 dd m_dup
 dd m_cfetch
 dd m_literal
 dd 64
 dd c_invert
 dd m_binand
 dd m_xswap
 dd m_cstore
 dd m_exitcolon
 CENTRY `:`, c_colon, 1
 dd c_create
 dd c_smudge
 dd m_literal
 dd m_colon
 dd m_fetch
 dd c_here
 dd m_literal
 dd 1
 dd c_cells
 dd m_minus
 dd m_store
 dd c_close_bracket
 dd m_exitcolon
 CIENTRY `;`, ci_semicolon, 1
 dd m_literal
 dd m_exitcolon
 dd c_comma
 dd mv_State
 dd c_off
 dd c_reveal
 dd m_exitcolon
 CIENTRY `recurse`, ci_recurse, 7
 dd mv_Dp
 dd m_fetch
 dd c_cellplus
 dd c_tocfa
 dd c_comma
 dd m_exitcolon
 CENTRY `char`, L206, 4
 dd c_bl
 dd c_word
 dd c_1plus
 dd m_cfetch
 dd m_exitcolon
 CENTRY `literal`, c_literal, 7
 dd m_literal
 dd m_literal
 dd c_comma
 dd c_comma
 dd m_exitcolon
 CENTRY `sliteral`, c_sliteral, 8
 dd m_literal
 dd m_sliteral
 dd c_comma
 dd c_here
 dd m_literal
 dd 34
 dd c_parse
 dd m_dup
 dd m_cfetch
 dd c_1plus
 dd m_rpush
 dd m_xswap
 dd m_rfetch
 dd m_cmove
 dd m_rpop
 dd c_allot
 dd c_align
 dd m_exitcolon
 CENTRY `string`, c_string, 6
 dd c_word
 dd m_dup
 dd m_cfetch
 dd c_1plus
 dd m_rpush
 dd c_here
 dd m_rfetch
 dd m_cmove
 dd m_rpop
 dd c_allot
 dd m_exitcolon
 CIENTRY `[char]`, ci_char_brackets, 6
 dd c_bl
 dd c_word
 dd c_1plus
 dd m_cfetch
 dd c_literal
 dd m_exitcolon
 CIENTRY `[']`, ci_quote_brackets, 3
 dd c_single_quote
 dd c_literal
 dd m_exitcolon
 CIENTRY `(`, ci_openparen, 1
 dd m_literal
 dd 41
 dd c_parse
 dd m_drop
 dd m_exitcolon
 CIENTRY `\`, ci_backslash, 1
 dd mv_Blk
 dd m_fetch
 dd m_cjump
 dd L214
 dd mv_toIn
 dd m_fetch
 dd m_literal
 dd 63
 dd m_plus
 dd m_literal
 dd 63
 dd c_invert
 dd m_binand
 dd mv_toIn
 dd m_store
 dd m_jump
 dd L215
L214:
 dd mv_toLimit
 dd m_fetch
 dd mv_toIn
 dd m_store
L215:
 dd m_exitcolon
 CENTRY `(?abort)`, c_qabort_parens, 8
 dd mv_State
 dd m_cjump
 dd L217
 dd c_space
 dd c_type
 dd c_cr
 dd c_abort
 dd m_jump
 dd L218
L217:
 dd c_2drop
L218:
 dd m_exitcolon
 CIENTRY `abort"`, ci_abort_double_quote, 6
 dd c_sliteral
 dd m_literal
 dd c_qabort_parens
 dd c_comma
 dd m_exitcolon
 CENTRY `"`, c_double_quote, 1
 dd m_literal
 dd 34
 dd c_word
 dd c_count
 dd m_rpush
 dd c_here
 dd m_rfetch
 dd m_cmove
 dd c_here
 dd m_rpop
 dd m_dup
 dd c_allot
 dd m_exitcolon
 CENTRY `c"`, c_cdouble_quote, 2
 dd m_literal
 dd 34
 dd c_word
 dd m_dup
 dd m_cfetch
 dd c_1plus
 dd m_rpush
 dd c_here
 dd m_rfetch
 dd m_cmove
 dd c_here
 dd m_rpop
 dd c_allot
 dd m_exitcolon
 CIENTRY `s"`, ci_sdouble_quote, 2
 dd c_sliteral
 dd m_exitcolon
 CIENTRY `."`, ci_dotstr, 2
 dd c_sliteral
 dd m_literal
 dd c_type
 dd c_comma
 dd m_exitcolon
 CIENTRY `if`, ci_if, 2
 dd m_literal
 dd m_cjump
 dd c_comma
 dd c_here
 dd m_literal
 dd 0
 dd c_comma
 dd m_exitcolon
 CIENTRY `else`, ci_else, 4
 dd m_literal
 dd m_jump
 dd c_comma
 dd c_here
 dd m_rpush
 dd m_literal
 dd 0
 dd c_comma
 dd c_here
 dd m_xswap
 dd m_store
 dd m_rpop
 dd m_exitcolon
 CIENTRY `then`, ci_then, 4
 dd c_here
 dd m_xswap
 dd m_store
 dd m_exitcolon
 CIENTRY `begin`, ci_begin, 5
 dd c_here
 dd m_exitcolon
 CIENTRY `again`, ci_again, 5
 dd m_literal
 dd m_jump
 dd c_comma
 dd c_comma
 dd m_exitcolon
 CIENTRY `until`, ci_until, 5
 dd m_literal
 dd m_cjump
 dd c_comma
 dd c_comma
 dd m_exitcolon
 CIENTRY `while`, ci_while, 5
 dd m_literal
 dd m_cjump
 dd c_comma
 dd c_here
 dd m_literal
 dd 0
 dd c_comma
 dd m_exitcolon
 CIENTRY `repeat`, ci_repeat, 6
 dd m_literal
 dd m_jump
 dd c_comma
 dd m_xswap
 dd c_comma
 dd c_here
 dd m_xswap
 dd m_store
 dd m_exitcolon
 CIENTRY `do`, ci_do, 2
 dd m_literal
 dd m_doinit
 dd c_comma
 dd m_literal
 dd 0
 dd c_here
 dd m_exitcolon
 CIENTRY `loop`, ci_loop, 4
 dd m_literal
 dd m_doloop
 dd c_comma
 dd c_comma
 dd c_qdup
 dd m_cjump
 dd L234
 dd c_here
 dd m_xswap
 dd m_store
L234:
 dd m_exitcolon
 CIENTRY `+loop`, ci_ploop, 5
 dd m_literal
 dd m_doploop
 dd c_comma
 dd c_comma
 dd c_qdup
 dd m_cjump
 dd L236
 dd c_here
 dd m_xswap
 dd m_store
L236:
 dd m_exitcolon
 CENTRY `w/o`, c_wo, 3
 dd m_literal
 dd 1
 dd m_literal
 dd 512
 dd m_binor
 dd m_literal
 dd 64
 dd m_binor
 dd m_exitcolon
 CENTRY `r/o`, c_ro, 3
 dd m_literal
 dd 0
 dd m_exitcolon
 CENTRY `r/w`, c_rw, 3
 dd m_literal
 dd 2
 dd m_exitcolon
 CENTRY `open-file`, c_open_file, 9
 dd m_rpush
 dd c_pad
 dd m_literal
 dd 1024
 dd m_plus
 dd m_xswap
 dd m_dup
 dd m_rpush
 dd m_cmove
 dd m_literal
 dd 0
 dd m_rpop
 dd c_pad
 dd m_plus
 dd m_literal
 dd 1024
 dd m_plus
 dd m_cstore
 dd c_pad
 dd m_literal
 dd 1024
 dd m_plus
 dd m_rpop
 dd m_literal
 dd 420
 dd m_fthopen
 dd m_dup
 dd m_literal
 dd -1
 dd m_greater
 dd m_exitcolon
 CENTRY `close-file`, c_close_file, 10
 dd m_fthclose
 dd c_0eq
 dd m_exitcolon
 CENTRY `read-file`, c_read_file, 9
 dd m_fthread
 dd m_dup
 dd m_literal
 dd -1
 dd c_neq
 dd m_exitcolon
 CENTRY `write-file`, c_write_file, 10
 dd m_fthwrite
 dd m_literal
 dd -1
 dd c_neq
 dd m_exitcolon
 CENTRY `reposition-file`, c_reposition_file, 15
 dd m_fthseek
 dd m_literal
 dd -1
 dd c_neq
 dd m_exitcolon
 CENTRY `?fcheck`, c_qfcheck, 7
 dd c_0eq
 dd m_cjump
 dd L246
 dd c_space
 dd m_literal
 dd L247
 dd m_literal
 dd 9
 dd c_type
 dd c_cr
 dd c_abort
L246:
 dd m_exitcolon
 CENTRY `bye`, c_bye, 3
 dd m_literal
 dd 0
 dd m_terminate
 dd m_exitcolon

 CENTRY `include`, c_include, 7
 dd c_bl
 dd c_word
 dd m_rpush
 dd mv_toLimit
 dd m_fetch
 dd mv_toIn
 dd m_store
 dd c_save_input
 dd m_rpop
 dd c_count
 dd c_ro
 dd c_open_file
 dd c_qfcheck
 dd mv_Infd
 dd m_store
 dd m_exitcolon

 CENTRY `crash`, c_crash, 5
 dd m_literal
 dd L251
 dd m_literal
 dd 30
 dd c_type
 dd c_cr
 dd c_abort
 dd m_exitcolon

 CENTRY `quit`, c_quit, 4 ; interpreter loop
 dd m_reset ; initialize return stack
 dd m_clear	; SP = sstack_end, initialize data stack
L253:
 dd c_query
 dd c_interpret
 dd m_jump
 dd L253
 dd m_exitcolon	; why is this needed?

 CENTRY `(abort)`, c_parenabort, 7 ; TODO correct below stack notations
 dd mv_State	; ( mv_State -- )
 dd c_off		; off sets variable state = 0
 dd mc_TIB	; constant puts address of tibuffer on the top of stack
 dd mv_Sourcebuf	; variable sourcebuf
 dd m_store	; variable sourcebuf = address of tibuffer
 dd mv_Blk	; variable blk
 dd c_off	; off variable blk = 0
 dd mc_STDIN
 dd mv_Infd
 dd m_store
 dd mc_STDOUT
 dd mv_Outfd
 dd m_store
 dd mc_STDERR
 dd mv_Errfd
 dd m_store
 dd c_quit	; quit resets stacks and is the interpreter loop
 dd m_exitcolon	; why is this needed? quit does not return unless it breaks

 CENTRY `oldboot`, c_oldboot, 7 ; TODO correct below stack notations and this is obsolete. leaving it here for reference until it all works well
 dd m_reset
 dd m_clear	; SP = sstack_end
 dd m_stackptr	; (D -- FFEND)
 dd m_s0
 dd m_store	; s0 = FFEND
 dd m_h0	; heaptop = heapend
 dd m_fetch	; ( heapend -- )
 dd m_literal
 dd 1		; ( heapend 1 -- )
 dd c_cells	; cells ( heapend 8 -- ) 
 dd m_minus	; ( heapend-8 -- )
 dd m_fetch	; ( contents_from_heapend-8 -- )
 dd m_args	; variable args
 dd m_store	; args = contents_from_heapend-8
 dd m_literal
 dd c_parenabort ; ( (abort) -- )
 dd mv_Abortvec	; variable abortvec
 dd m_store	; variable abortvec = (abort) code address
 dd mc_WORDB	; constant puts address of wordbuffer on the top of stack
 dd mv_Wordbuf	; variable wordbuf
 dd m_store	; variable wordbuf = address of wordbuffer
 dd mc_TIB	; constant puts address of tibuffer on the top of stack
 dd mv_Sourcebuf	; variable sourcebuf
 dd m_store	; variable sourcebuf = address of tibuffer
 dd m_literal
 dd 0
 dd mv_Infd
 dd m_store	; stdin = 0
 dd m_literal
 dd 1
 dd mv_Outfd
 dd m_store	; stdout = 1
 dd mv_State
 dd c_off	; off stores 0 at state
 dd c_decimal	; decimal setting base = 0
 dd c_quit	; quit
 dd m_exitcolon

 CENTRY `boot`, c_boot, 4
 dd m_reset ; initialize return stack
 dd m_clear	; SP = sstack_end, initialize data stack
			; s0 puts FFEND on the stack
			; no args

 dd m_literal
 dd c_parenabort ; ( (abort) -- )
 dd mv_Abortvec	; variable that puts (abort) code address on the stack
 dd m_store	; variable abortvec = (abort) code address

 dd mc_WORDB	; variable puts address of wordbuffer on the top of stack
 dd mv_Wordbuf ; variable wordbuf
 dd m_store	; variable wordbuf = address of wordbuffer

 dd mc_TIB	; constant puts address of tibuffer on the top of stack
 dd mv_Sourcebuf	; variable sourcebuf
 dd m_store	; variable sourcebuf = address of tibuffer

 dd mc_STDIN
 dd mv_Infd
 dd m_store	; stdin = 0
 dd mc_STDOUT
 dd mv_Outfd
 dd m_store
 dd mc_STDERR
 dd mv_Errfd
 dd m_store

 dd mv_State
 dd c_off	; off stores 0 at state
 dd c_decimal	; decimal setting base = 0
 dd c_quit	; quit
 dd m_exitcolon

L137:
 db 'unable to restore input'
L170:
 db ' Q?'
L173:
 db ' stack underflow'
L180:
 db ' I?'
L193:
 db ' C?'
L247:
 db 'I/O error'
L251:
 db 'uninitialized execution vector'
L255:
 db ' ok'
