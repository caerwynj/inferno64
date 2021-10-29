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
 VENTRY `s0`, v_s0, 2
 VENTRY `args`, v_args, 4
 CENTRY `on`, c_on, 2
 dd m_literal
 dd -1
 dd m_xswap
 dd m_store
 dd m_exitcolon
 CENTRY `off`, c_off, 3
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
 dd v_s0
 dd m_fetch
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
 VENTRY `iobuf`, v_iobuf, 5
 VENTRY `stdin`, v_stdin, 5
 VENTRY `stdout`, v_stdout, 6
 VENTRY `eof`, v_eof, 3
 CENTRY `key`, c_key, 3
 dd v_iobuf		; variable iobuf
 dd m_literal
 dd 1
 dd v_stdin		; variable stdin
 dd m_fetch	; ( iobuf 1 0 -- )
 dd m_fsread
 dd c_0eq
 dd m_cjump
 dd L78
 dd v_eof
 dd c_on
 dd m_literal
 dd -1
 dd m_jump
 dd L79
L78:
 dd v_iobuf
 dd m_cfetch
L79:
 dd m_exitcolon
 CENTRY `emit`, c_emit, 4	; ( character -- ) TODO correct the below stack notations
 dd v_iobuf			; variable iobuf
 dd m_cstore		; variable iobuf has character
 dd v_iobuf			; variable iobuf
 dd m_literal
 dd 1			; ( iobuf 1 -- )
 dd v_stdout			; variable stdout
 dd m_fetch		; ( iobuf 1 1 -- )
 dd m_fswrite		; ( -- ) writes out the character
 dd m_drop		; the return value of fswrite
 dd m_exitcolon
 CENTRY `type`, c_type, 4	; ( addr n -- ) 
 dd v_stdout			; variable stdout, normally 1
 dd m_fetch		; ( addr n 1 -- )
 dd m_fswrite
 dd m_drop
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
 VENTRY `searchlen`, v_searchlen, 9
 CENTRY `search`, c_search, 6
 dd v_searchlen
 dd m_store
 dd m_xswap
 dd m_dup
 dd m_rpush
 dd v_searchlen
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
 dd v_searchlen
 dd m_fetch
 dd m_xswap
 dd v_searchlen
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
 dd mc_h
 dd m_fetch
 dd m_exitcolon
 CENTRY `,`, c_comma, 1
 dd c_here
 dd m_store
 dd m_literal
 dd 8
 dd mc_h
 dd c_plusstore
 dd m_exitcolon
 CENTRY `c,`, c_c, 2
 dd c_here
 dd m_cstore
 dd m_literal
 dd 1
 dd mc_h
 dd c_plusstore
 dd m_exitcolon
 CENTRY `allot`, c_allot, 5
 dd mc_h
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
 dd mc_h
 dd m_store
 dd m_exitcolon
 CENTRY `unused`, c_unused, 6
 dd mc_heaptop
 dd m_fetch
 dd c_here
 dd m_minus
 dd m_exitcolon
 VENTRY `base`, v_base, 4
 VENTRY `>num`, v_tonum, 4
 CENTRY `<#`, c_fromhash, 2
 dd c_pad
 dd m_literal
 dd 1024
 dd m_plus
 dd v_tonum
 dd m_store
 dd m_exitcolon
 CENTRY `#`, c_hash, 1
 dd v_base
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
 dd v_tonum
 dd m_fetch
 dd c_1minus
 dd m_dup
 dd v_tonum
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
 dd v_tonum
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
 dd v_tonum
 dd m_fetch
 dd c_1minus
 dd m_dup
 dd m_rpush
 dd m_cstore
 dd m_rpop
 dd v_tonum
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
 dd v_base
 dd m_store
 dd m_exitcolon
 CENTRY `decimal`, c_decimal, 7
 dd m_literal
 dd 10
 dd v_base
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
 dd v_base
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
 dd v_base
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
 VENTRY `>in`, v_toin, 3
 VENTRY `>limit`, v_tolimit, 6
 VENTRY `wordbuf`, v_wordbuf, 7
 VENTRY `abortvec`, v_abortvec, 8
 VENTRY `findadr`, v_findadr, 7
 VENTRY `sourcebuf`, v_sourcebuf, 9
 VENTRY `blk`, v_blk, 3
 CENTRY `abort`, c_abort, 5
 dd v_abortvec
 dd m_fetch
 dd m_execute
 dd m_exitcolon
 CENTRY `source`, c_source, 6
 dd v_sourcebuf
 dd m_fetch
 dd m_exitcolon
 CENTRY `current-input`, c_current_input, 13
 dd v_toin
 dd m_fetch
 dd c_source
 dd m_plus
 dd m_cfetch
 dd m_exitcolon
 CENTRY `save-input`, c_save_input, 10
 dd v_stdin
 dd m_fetch
 dd v_toin
 dd m_fetch
 dd v_tolimit
 dd m_fetch
 dd v_sourcebuf
 dd m_fetch
 dd v_blk
 dd m_fetch
 dd m_literal
 dd 5
 dd m_exitcolon
 CENTRY `default-input`, c_default_input, 13
 dd v_stdin
 dd c_off
 dd v_toin
 dd c_off
 dd v_tolimit
 dd c_off
 dd mc_tib
 dd v_sourcebuf
 dd m_store
 dd v_blk
 dd c_off
 dd m_exitcolon
 CENTRY `restore-input`, c_restore_input, 13
 dd v_eof
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
 dd v_blk
 dd m_store
 dd v_sourcebuf
 dd m_store
 dd v_tolimit
 dd m_store
 dd v_toin
 dd m_store
 dd v_stdin
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
 CENTRY `next-input`, c_next_input, 10
 dd v_toin
 dd m_fetch
 dd v_tolimit
 dd m_fetch
 dd m_less
 dd m_cjump
 dd L139
 dd c_true
 dd c_current_input
 dd m_jump
 dd L140
L139:
 dd m_literal
 dd 0
 dd c_false
L140:
 dd m_exitcolon
 CENTRY `parse`, c_parse, 5
 dd m_rpush
 dd v_wordbuf
 dd m_fetch
 dd c_1plus
L142:
 dd c_next_input
 dd m_rfetch
 dd c_neq
 dd m_binand
 dd m_cjump
 dd L143
 dd c_current_input
 dd m_over
 dd m_cstore
 dd c_1plus
 dd m_literal
 dd 1
 dd v_toin
 dd c_plusstore
 dd m_jump
 dd L142
L143:
 dd m_literal
 dd 1
 dd v_toin
 dd c_plusstore
 dd m_rpop
 dd m_drop
 dd v_wordbuf
 dd m_fetch
 dd m_dup
 dd m_rpush
 dd m_minus
 dd c_1minus
 dd m_rfetch
 dd m_cstore
 dd m_rpop
 dd m_exitcolon
 CENTRY `word`, c_word, 4 ; ( c -- )
 dd m_rpush	; ( -- ) (R -- c )
L145:
 dd c_next_input ; ( -- c2 ) (R c1 -- )
 dd m_rfetch
 dd m_equal
 dd m_binand
 dd m_cjump
 dd L146
 dd m_literal
 dd 1
 dd v_toin
 dd c_plusstore
 dd m_jump
 dd L145
L146:
 dd m_rpop
 dd c_parse
 dd m_exitcolon
 CENTRY `accept`, c_accept, 6	; ( a n -- ) TODO correct below stack notations
 dd m_xswap	; ( n a -- )
 dd m_dup	; ( n a a -- )
 dd m_rpush
 dd m_rpush	; ( n -- ) (R a a -- )
L148:
 dd c_qdup	; ( n n -- ) (R a a -- )
 dd m_cjump	; (if)
 dd L149	; n == 0
 dd c_key	; n > 0 ( n c -- )
 dd m_dup	; ( n c c -- )
 dd m_literal
 dd 10		; ( n c c 10 -- )
 dd m_equal	; ( n c f -- )
 dd m_over	; ( n c f n -- )
 dd m_literal
 dd -1		; ( n c f n -1 -- )
 dd m_equal	; ( n c f1 f2 -- )
 dd m_binor	; ( n c f -- )
 dd m_cjump
 dd L150
 dd c_2drop	; n == -1 || n == 10 (	-- )
 dd m_rpop
 dd m_rpop
 dd m_minus
 dd m_exitcolon	; ( 0 -- ) (R -- )
L150:
 dd m_rfetch	; ( n c a -- ) (R a a -- )
 dd m_cstore
 dd m_rpop	; ( n a -- ) (R a -- )
 dd c_1plus
 dd m_rpush	; ( n -- ) (R a1 a2 -- )
 dd c_1minus	; ( n-1 -- ) (R a1 a2 -- )
 dd m_jump
 dd L148
L149:		; n == 0 ( -- ) (R a a -- )
 dd m_rpop
 dd m_rpop	; ( a a -- )
 dd m_minus	; ( 0 -- )
 dd m_exitcolon
 CENTRY `query`, c_query, 5
 dd v_eof	; variable eof
 dd c_off	; off sets variable eof = 0
 dd mc_tib	; constant puts address of tibuffer on the top
 dd m_literal
 dd 1024	; ( tibuffer -- tibuffer 1024 )
 dd c_accept	; ( tibuffer 1024 -- n )
 dd m_dup
 dd c_0eq
 dd v_eof
 dd m_fetch
 dd m_binand
 dd m_cjump
 dd L152
 dd m_drop
 dd c_qrestore_input
 dd m_jump
 dd L153
L152:
 dd v_tolimit
 dd m_store
 dd v_toin
 dd c_off
L153:
 dd m_exitcolon
 CENTRY `refill`, c_refill, 6
 dd v_blk
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
 dd v_findadr
 dd m_store
 dd mc_dp
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
 dd v_findadr
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
 dd v_findadr
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
 dd v_s0
 dd m_fetch
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
 CENTRY `interpret`, c_interpret, 9
L175:
 dd c_bl
 dd c_word
 dd m_dup
 dd m_cfetch
 dd c_0neq
 dd m_cjump
 dd L176
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
 dd m_drop
 dd m_exitcolon
 CENTRY `create`, c_create, 6
 dd c_align
 dd c_here
 dd m_rpush
 dd mc_dp
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
 dd mc_dp
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
 VENTRY `state`, v_state, 5
 CENTRY `immediate`, c_immediate, 9
 dd mc_dp
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
 dd v_state
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
 dd v_state
 dd m_fetch
L198:
 dd m_cjump
 dd L199
 dd m_jump
 dd L196
L199:
 dd m_exitcolon
 CIENTRY `[`, ci_open_bracket, 1
 dd v_state
 dd c_off
 dd m_exitcolon
 CENTRY `smudge`, c_smudge, 6
 dd mc_dp
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
 dd mc_dp
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
 dd v_state
 dd c_off
 dd c_reveal
 dd m_exitcolon
 CIENTRY `recurse`, ci_recurse, 7
 dd mc_dp
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
 dd v_blk
 dd m_fetch
 dd m_cjump
 dd L214
 dd v_toin
 dd m_fetch
 dd m_literal
 dd 63
 dd m_plus
 dd m_literal
 dd 63
 dd c_invert
 dd m_binand
 dd v_toin
 dd m_store
 dd m_jump
 dd L215
L214:
 dd v_tolimit
 dd m_fetch
 dd v_toin
 dd m_store
L215:
 dd m_exitcolon
 CENTRY `(?abort)`, c_qabort_parens, 8
 dd v_state
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
 dd m_fsopen
 dd m_dup
 dd m_literal
 dd -1
 dd m_greater
 dd m_exitcolon
 CENTRY `close-file`, c_close_file, 10
 dd m_fsclose
 dd c_0eq
 dd m_exitcolon
 CENTRY `read-file`, c_read_file, 9
 dd m_fsread
 dd m_dup
 dd m_literal
 dd -1
 dd c_neq
 dd m_exitcolon
 CENTRY `write-file`, c_write_file, 10
 dd m_fswrite
 dd m_literal
 dd -1
 dd c_neq
 dd m_exitcolon
 CENTRY `reposition-file`, c_reposition_file, 15
 dd m_fsseek
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
 dd m_errstr
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
 dd v_tolimit
 dd m_fetch
 dd v_toin
 dd m_store
 dd c_save_input
 dd m_rpop
 dd c_count
 dd c_ro
 dd c_open_file
 dd c_qfcheck
 dd v_stdin
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
 CENTRY `quit`, c_quit, 4 ; TODO correct below stack notations
 dd m_reset ; initialize return stack
 dd m_clear	; SP = sstack_end, initialize data stack
L253:
 dd c_query
 dd c_interpret
 dd v_stdin
 dd m_fetch	; ( 0 -- )
 dd c_0eq
 dd m_cjump
 dd L254
 dd m_literal
 dd L255	; address of string ok
 dd m_literal
 dd 3
 dd c_type	; ( addr n -- ) type 
 dd c_cr	; cr
L254:
 dd m_jump
 dd L253
 dd m_exitcolon
 CENTRY `(abort)`, c_parenabort, 7 ; TODO correct below stack notations
 dd v_state	; ( v_state -- )
 dd c_off		; off sets variable state = 0
 dd mc_tib	; constant puts address of tibuffer on the top of stack
 dd v_sourcebuf	; variable sourcebuf
 dd m_store	; variable sourcebuf = address of tibuffer
 dd v_blk	; variable blk
 dd c_off		; off variable blk = 0
 dd v_stdin		; variable stdin
 dd c_off		; off variable stdin = 0
 dd m_literal
 dd 1		; ( 1 -- )
 dd v_stdout		; variable stdout
 dd m_store	; variable stdout = 1
 dd c_quit	; quit resets return stack and data stack
 dd m_exitcolon
 CENTRY `oldboot`, c_oldboot, 7 ; TODO correct below stack notations
 dd m_reset
 dd m_clear	; SP = sstack_end
 dd m_stackptr	; (D -- FFEND)
 dd v_s0
 dd m_store	; s0 = FFEND
 dd mc_heaptop	; heaptop = heapend
 dd m_fetch	; ( heapend -- )
 dd m_literal
 dd 1		; ( heapend 1 -- )
 dd c_cells	; cells ( heapend 8 -- ) 
 dd m_minus	; ( heapend-8 -- )
 dd m_fetch	; ( contents_from_heapend-8 -- )
 dd v_args	; variable args
 dd m_store	; args = contents_from_heapend-8
 dd m_literal
 dd c_parenabort ; ( (abort) -- )
 dd v_abortvec	; variable abortvec
 dd m_store	; variable abortvec = (abort) code address
 dd mc_wordb	; constant puts address of wordbuffer on the top of stack
 dd v_wordbuf	; variable wordbuf
 dd m_store	; variable wordbuf = address of wordbuffer
 dd mc_tib	; constant puts address of tibuffer on the top of stack
 dd v_sourcebuf	; variable sourcebuf
 dd m_store	; variable sourcebuf = address of tibuffer
 dd m_literal
 dd 0
 dd v_stdin
 dd m_store	; stdin = 0
 dd m_literal
 dd 1
 dd v_stdout
 dd m_store	; stdout = 1
 dd v_state
 dd c_off	; off stores 0 at state
 dd c_decimal	; decimal setting base = 0
 dd c_quit	; quit
 dd m_exitcolon
 CENTRY `boot`, c_boot, 4
 dd m_reset ; initialize return stack
 dd m_clear	; SP = sstack_end, initialize data stack
 dd m_stackptr	; ( -- FFEND)
 dd v_s0
 dd m_store	; s0 = FFEND
			; no args
 dd m_literal
 dd c_parenabort ; ( (abort) -- )
 dd v_abortvec	; variable abortvec
 dd m_store	; variable abortvec = (abort) code address
 dd mc_wordb	; constant puts address of wordbuffer on the top of stack
 dd v_wordbuf	; variable wordbuf
 dd m_store	; variable wordbuf = address of wordbuffer
 dd mc_tib	; constant puts address of tibuffer on the top of stack
 dd v_sourcebuf	; variable sourcebuf
 dd m_store	; variable sourcebuf = address of tibuffer
			; no stdin or stdout
 dd v_state
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
