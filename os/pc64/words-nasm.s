CENTRY "false" C_false 5
dd M_literal
dd 0
dd M_exitcolon
CENTRY "true" C_true 4
dd M_literal
dd -1
dd M_exitcolon
CENTRY "bl" C_bl 2
dd M_literal
dd 32
dd M_exitcolon
CENTRY "on" C_on 2		; ( a --  ) (G stores -1 at a )
dd M_literal
dd -1
dd M_xswap
dd M_store
dd M_exitcolon
CENTRY "off" C_off 3		; ( a --  ) (G stores 0 at a )
dd M_literal
dd 0
dd M_xswap
dd M_store
dd M_exitcolon
CENTRY ">body" C_tobody 5
dd M_literal
dd 8
dd M_plus
dd M_exitcolon
CENTRY "aligned" C_aligned 7
dd M_literal
dd 7
dd M_plus
dd M_literal
dd -8
dd M_binand
dd M_exitcolon
CENTRY "cells" C_cells 5
dd M_literal
dd 3			; (index << 2) -> (index << 3)for amd64
dd M_lshift
dd M_exitcolon
CENTRY "cell+" C_cellplus 5
dd M_literal
dd 1
dd C_cells
dd M_plus
dd M_exitcolon
CENTRY "depth" C_depth 5
dd M_S0
dd M_stackptr
dd M_minus
dd M_literal
dd 3
dd M_rshift
dd M_literal
dd 1
dd M_minus
dd M_exitcolon
CENTRY "nip" C_nip 3
dd M_xswap
dd M_drop
dd M_exitcolon
CENTRY "rot" C_rot 3
dd M_rpush
dd M_xswap
dd M_rpop
dd M_xswap
dd M_exitcolon
CENTRY "2drop" C_2drop 5
dd M_drop
dd M_drop
dd M_exitcolon
CENTRY "2dup" C_2dup 4
dd M_over
dd M_over
dd M_exitcolon
CENTRY "2nip" C_2nip 4
dd C_nip
dd C_nip
dd M_exitcolon
CENTRY "2swap" C_2swap 5
dd C_rot
dd M_rpush
dd C_rot
dd M_rpop
dd M_exitcolon
CENTRY "?dup" C_qdup 4 ; if (n != 0) ( n -- n n) else ( n -- n )
dd M_dup	; ( n -- n n )
dd M_dup	; ( n n -- n n n )
dd M_literal
dd 0		; ( n n n -- n n n 0 )
dd M_equal	; ( n n n 0 -- n n f )
dd M_cjump	; ( n n f -- n n )
dd L20		; when n != 0, go to L20
dd M_drop	; when n == 0 ( n n -- n)
L20:		; when n != 0 ( n n )
dd M_exitcolon
CENTRY "pick" C_pick 4
dd C_qdup
dd M_cjump
dd L22
dd M_literal
dd 1
dd M_plus
dd C_cells
dd M_stackptr
dd M_plus
dd M_fetch
dd M_jump
dd L23
L22:
dd M_dup
L23:
dd M_exitcolon
CENTRY "tuck" C_tuck 4
dd M_dup
dd M_rpush
dd M_xswap
dd M_rpop
dd M_exitcolon
CENTRY "/" C_divides 1
dd M_slashmod
dd C_nip
dd M_exitcolon
CENTRY "+!" C_plusstore 2
dd M_dup
dd M_fetch
dd C_rot
dd M_plus
dd M_xswap
dd M_store
dd M_exitcolon
CENTRY "invert" C_invert 6
dd M_literal
dd -1
dd M_binxor
dd M_exitcolon
CENTRY "mod" C_mod 3
dd M_slashmod
dd M_drop
dd M_exitcolon
CENTRY "1+" C_1plus 2
dd M_literal
dd 1
dd M_plus
dd M_exitcolon
CENTRY "1-" C_1minus 2
dd M_literal
dd 1
dd M_minus
dd M_exitcolon
CENTRY "negate" C_negate 6
dd M_literal
dd 0
dd M_xswap
dd M_minus
dd M_exitcolon
CENTRY "2*" C_2multiplies 2
dd M_literal
dd 1
dd M_lshift
dd M_exitcolon
CENTRY "2/" C_2divides 2
dd M_literal
dd 1
dd M_rshifta
dd M_exitcolon
CENTRY "0=" C_0eq 2
dd M_literal
dd 0
dd M_equal
dd M_exitcolon
CENTRY "0<" C_0lt 2
dd M_literal
dd 0
dd M_less
dd M_exitcolon
CENTRY "0>" C_0gt 2
dd M_literal
dd 0
dd M_greater
dd M_exitcolon
CENTRY "<>" C_neq 2
dd M_equal
dd C_invert
dd M_exitcolon
CENTRY "0<>" C_0neq 3
dd M_literal
dd 0
dd C_neq
dd M_exitcolon
CENTRY "max" C_max 3
dd C_2dup
dd M_greater
dd M_cjump
dd L40
dd M_drop
dd M_jump
dd L41
L40:
dd C_nip
L41:
dd M_exitcolon
CENTRY "min" C_min 3
dd C_2dup
dd M_less
dd M_cjump
dd L43
dd M_drop
dd M_jump
dd L44
L43:
dd C_nip
L44:
dd M_exitcolon
CENTRY "signum" C_signum 6
dd M_dup
dd C_0gt
dd M_cjump
dd L46
dd M_drop
dd M_literal
dd 1
dd M_jump
dd L47
L46:
dd C_0lt
dd M_cjump
dd L48
dd M_literal
dd -1
dd M_jump
dd L49
L48:
dd M_literal
dd 0
L49:
L47:
dd M_exitcolon
CENTRY "within" C_within 6
dd M_rpush
dd M_over
dd M_greater
dd C_0eq
dd M_xswap
dd M_rpop
dd M_greater
dd C_0eq
dd M_binand
dd M_exitcolon
CENTRY "abs" C_abs 3
dd M_dup
dd C_0lt
dd M_cjump
dd L52
dd C_negate
L52:
dd M_exitcolon

CENTRY "key" C_key 3	 ; ( -- c ) (G read a single character from the input onto the stack )
dd M_literal
dd 1			; ( 1 -- )
dd MV_Iobuf		; variable iobuf to store the character read
dd MV_Infd
dd M_fetch		; ( 1 Iobuf -- 1 Iobuf infd )
dd M_fthread	; ( 1 Iobuf infd -- n )
dd C_0eq
dd M_cjump		; if 0 characters read
dd L78			; if qread n != 0 jump to L78. If n == 0 jump over
dd MV_Eof
dd C_on		; EOF
dd M_literal
dd -1			; return -1 when EOF
dd M_jump
dd L79
L78:
dd MV_Iobuf		; get the character from Iobuf to stack
dd M_cfetch	; ( -- c ) return the character read if not EOF
L79:
dd M_exitcolon

CENTRY "emit" C_emit 4	; ( character -- )
dd MV_Iobuf		; variable iobuf address
dd M_cstore	; variable iobuf has character
dd MV_Iobuf		; variable iobuf address
dd M_literal
dd 1
dd M_xswap		; ( iobuf 1 --  1 iobuf )
dd MV_Outfd
dd M_fetch		; outfd
dd M_fthwrite	; ( 1 iobuf outfd --  )
dd M_drop		; drop the return value of write
dd M_exitcolon

CENTRY "type" C_type 4	; ( addr n -- )
dd M_xswap			; ( addr n --  n addr )
dd M_literal
dd 1				; stdout
dd M_fthwrite		; ( n addr 1 --  )
dd M_drop		; drop the return value of write
dd M_exitcolon

CENTRY "cr" C_cr 2
dd M_literal
dd 10			; ascii value of carriage return
dd C_emit			; emit
dd M_exitcolon

CENTRY "space" C_space 5
dd C_bl
dd C_emit
dd M_exitcolon

CENTRY "emits" C_emits 5
L85:
dd C_qdup
dd M_cjump
dd L86
dd M_over
dd C_emit
dd C_1minus
dd M_jump
dd L85
L86:
dd M_drop
dd M_exitcolon
CENTRY "spaces" C_spaces 6
dd C_bl
dd M_xswap
dd C_emits
dd M_exitcolon
CENTRY "count" C_count 5 ; ( a -- a+1 n ) a = counted string
dd C_1plus
dd M_dup
dd C_1minus
dd M_cfetch
dd M_exitcolon

dd C_2dup ; debug show the word name to search
dd C_type
dd C_space

dd M_rpush ; debug show the dictionary entry
dd M_rpush
dd C_2dup
dd C_type
dd M_rpop
dd M_rpop
dd C_cr

CENTRY "compare" C_compare 7 ; ( a1 n1 a2 n2 -- f ) a1 = dictionary entry a2 = word name to search
dd C_rot	; ( a1 n1 a2 n2 -- a1 a2 n2 n1 )
dd C_2dup	; ( -- a1 a2 n2 n1 n2 n1 )
dd M_rpush	; ( -- a1 a2 n2 n1 n2 ) (R n1 -- )
dd M_rpush	; ( -- a1 a2 n2 n1 ) (R n1 n2 -- )
dd C_min	; ( -- a1 a2 nmin ) (R n1 n2 -- )
dd M_literal
dd 0		; ( -- a1 a2 nmin 0 ) (R n1 n2 -- )
dd M_doinit	; ( -- a1 a2 ) (R n1 n2 0 nmin -- )
L55:
dd M_over
dd M_i
dd M_plus
dd M_cfetch
dd M_over
dd M_i
dd M_plus
dd M_cfetch
dd M_minus
dd C_signum
dd C_qdup
dd M_cjump
dd L56		; matches
dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- )
dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2)
dd M_unloop	; ( f -- f ) (R n1 n2 -- )
dd M_exitcolon
L56:
dd M_doloop
dd L55
dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- )
dd M_rpop
dd M_rpop	; ( n2 n1 -- ) (R -- )
dd M_minus	; ( -- n1-n2 )
dd C_signum
dd M_exitcolon

CENTRY "erase" C_erase 5
dd M_literal
dd 0
dd M_doinit
L58:
dd M_literal
dd 0
dd M_over
dd M_cstore
dd C_1plus
dd M_doloop
dd L58
dd M_drop
dd M_exitcolon
CENTRY "fill" C_fill 4
dd M_xswap
dd M_literal
dd 0
dd M_doinit
L60:
dd C_2dup
dd M_xswap
dd M_i
dd M_plus
dd M_cstore
dd M_doloop
dd L60
dd C_2drop
dd M_exitcolon
CENTRY "blank" C_blank 5
dd C_bl
dd C_fill
dd M_exitcolon
CENTRY "search" C_search 6
dd MV_Searchlen
dd M_store
dd M_xswap
dd M_dup
dd M_rpush
dd MV_Searchlen
dd M_fetch
dd M_minus
dd C_1plus
dd M_literal
dd 0
dd M_doinit
L64:
dd M_over
dd M_i
dd M_plus
dd M_over
dd MV_Searchlen
dd M_fetch
dd M_xswap
dd MV_Searchlen
dd M_fetch
dd C_compare
dd C_0eq
dd M_cjump
dd L65
dd M_drop
dd M_i
dd M_plus
dd M_i
dd M_unloop
dd M_rpop
dd M_xswap
dd M_minus
dd C_true
dd M_exitcolon
L65:
dd M_doloop
dd L64
dd M_drop
dd M_rpop
dd C_false
dd M_exitcolon
CENTRY "here" C_here 4
dd M_Dp
dd M_fetch
dd M_exitcolon
CENTRY "," C_comma 1
dd C_here
dd M_store
dd M_literal
dd 8
dd M_Dp
dd C_plusstore
dd M_exitcolon
CENTRY "c," C_c 2
dd C_here
dd M_cstore
dd M_literal
dd 1
dd M_Dp
dd C_plusstore
dd M_exitcolon
CENTRY "allot" C_allot 5
dd M_Dp
dd C_plusstore
dd M_exitcolon
CENTRY "pad" C_pad 3
dd C_here
dd M_literal
dd 256
dd M_plus
dd M_exitcolon
CENTRY "align" C_align 5
dd C_here
dd C_aligned
dd M_Dp
dd M_store
dd M_exitcolon
CENTRY "unused" C_unused 6
dd M_Dp
dd M_fetch
dd C_here
dd M_minus
dd M_exitcolon
CENTRY "<#" C_fromhash 2
dd C_pad
dd M_literal
dd 1024
dd M_plus
dd MV_toNum
dd M_store
dd M_exitcolon
CENTRY "#" C_hash 1
dd MV_Base
dd M_fetch
dd M_uslashmod
dd M_xswap
dd M_dup
dd M_literal
dd 9
dd M_greater
dd M_cjump
dd L92
dd M_literal
dd 97
dd M_plus
dd M_literal
dd 10
dd M_minus
dd M_jump
dd L93
L92:
dd M_literal
dd 48
dd M_plus
L93:
dd MV_toNum
dd M_fetch
dd C_1minus
dd M_dup
dd MV_toNum
dd M_store
dd M_cstore
dd M_exitcolon
CENTRY "#s" C_hashs 2
L95:
dd C_hash
dd M_dup
dd M_cjump
dd L96
dd M_jump
dd L95
L96:
dd M_exitcolon
CENTRY "#>" C_hashfrom 2
dd M_drop
dd MV_toNum
dd M_fetch
dd M_dup
dd C_pad
dd M_literal
dd 1024
dd M_plus
dd M_xswap
dd M_minus
dd M_exitcolon
CENTRY "hold" C_hold 4
dd MV_toNum
dd M_fetch
dd C_1minus
dd M_dup
dd M_rpush
dd M_cstore
dd M_rpop
dd MV_toNum
dd M_store
dd M_exitcolon
CENTRY "sign" C_sign 4
dd C_0lt
dd M_cjump
dd L100
dd M_literal
dd 45
dd C_hold
L100:
dd M_exitcolon

CENTRY "." C_dot 1	; print the top of stack ( n -- )
dd M_dup		; ( n -- n n )
dd C_abs		; ( n n -- n u )
dd C_fromhash	; pad = h+256; >num = pad+1024
dd C_hashs		; ( n u1 -- n n2 )
dd M_xswap		; ( n n2 -- n2 n )
dd C_sign		; ( n2 n -- n2 )
dd C_hashfrom	; ( u1 -- a n )
dd C_type		; ( a n -- )
dd C_space
dd M_exitcolon
CENTRY ".r" C_dotr 2
dd M_rpush
dd M_dup
dd C_abs
dd C_fromhash
dd C_hashs
dd M_xswap
dd C_sign
dd C_hashfrom
dd M_rpop
dd M_over
dd M_minus
dd M_literal
dd 0
dd C_max
dd C_spaces
dd C_type
dd M_exitcolon
CENTRY "hex" C_hex 3
dd M_literal
dd 16
dd MV_Base
dd M_store
dd M_exitcolon
CENTRY "decimal" C_decimal 7
dd M_literal
dd 10
dd MV_Base
dd M_store
dd M_exitcolon

CENTRY "digit" C_digit 5 ; ( c -- )
dd M_dup
dd M_literal
dd 65
dd M_literal
dd 91
dd C_within
dd M_cjump
dd L106
dd M_literal
dd 55
dd M_minus
dd M_jump
dd L107
L106:
dd M_dup
dd M_literal
dd 97
dd M_literal
dd 123
dd C_within
dd M_cjump
dd L108
dd M_literal
dd 87
dd M_minus
dd M_jump
dd L109
L108:
dd M_dup
dd M_literal
dd 48
dd M_literal
dd 58
dd C_within
dd M_cjump
dd L110
dd M_literal
dd 48
dd M_minus
dd M_jump
dd L111
L110:
dd M_drop
dd C_false
dd M_exitcolon
L111:
L109:
L107:
dd M_dup
dd MV_Base
dd M_fetch
dd M_less
dd M_cjump
dd L112
dd C_true
dd M_jump
dd L113
L112:
dd M_drop
dd C_false
L113:
dd M_exitcolon

CENTRY "number" C_number 6 ; ( a n1 -- n2 -1 | a n1 0 )
dd M_xswap	; ( a n1 -- n1 a )
dd M_dup	; ( n1 a -- n1 a a )
dd M_cfetch	; ( n1 a a -- n1 a c )
dd M_literal
dd 45		; ( n1 a c -- n1 a c - )
dd M_equal	; ( n1 a c -- n1 a f )
dd M_cjump	; ( n1 a c -- n1 a )
dd L115		; c != -
dd C_1plus	; c == - ( n1 a -- n1 a+1 )
dd M_xswap
dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 )
dd M_literal
dd -1		; ( a+1 n1-1 -- a+1 n1-1 -1 )
dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1)
dd M_jump
dd L116
L115:		; c != -
dd M_xswap	; ( n1 a -- a n1)
dd M_literal
dd 1
dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1)
L116:		; ( a n1 ) (R nr)
dd M_dup	; ( a n1 -- a n1 n1 ) (R nr)
dd M_rpush	; ( a n1 n1 -- a n1 ) (R nr -- nr n1)
dd M_literal
dd 0		; ( a n1 -- a n1 0) (R nr n1)
dd M_xswap	; ( a n1 0 -- a 0 n1) (R nr n1)
dd M_literal
dd 0		; ( a 0 n1 -- a 0 n1 0) (R nr n1)
dd M_doinit	; ( a 0 n1 0 -- a 0 ) (R nr n1 -- nr n1 0 n1)
L117:
dd MV_Base
dd M_fetch	; ( a 0 Base -- a 0 10 ) (R nr n1 -- nr n1 0 n1)
dd M_multiply	; ( a 0 10 -- a 0 ) (R nr n1 -- nr n1 0 n1)
dd M_over	; ( a 0 -- a 0 a) (R nr n1 -- nr n1 0 n1)
dd M_i		; ( a 0 a -- a 0 a n1) (R nr n1 -- nr n1 0 n1)
dd M_plus	; ( a 0 a n1 -- a 0 a+n1) (R nr n1 -- nr n1 0 n1)
dd M_cfetch	; ( a 0 a+n1 -- a 0 c) (R nr n1 -- nr n1 0 n1)
dd C_digit
dd M_cjump
dd L118
dd M_plus
dd M_jump
dd L119
L118:
dd M_drop
dd M_unloop
dd M_rpop
dd M_rpop
dd M_drop
dd C_false
dd M_exitcolon
L119:
dd M_doloop
dd L117
dd M_rpop
dd M_drop
dd C_nip
dd M_rpop
dd M_multiply
dd C_true
dd M_exitcolon

CENTRY "abort" C_abort 5
dd MV_Abortvec
dd M_fetch
dd M_execute
dd M_exitcolon
CENTRY "source" C_source 6
dd MV_Sourcebuf
dd M_fetch
dd M_exitcolon

CENTRY "current-input" C_current_input 13 ; ( -- c ) read the next character from the location in Sourcebuf
dd MV_toIn
dd M_fetch
dd C_source
dd M_plus		; Sourcebuf + >In
dd M_cfetch
dd M_exitcolon

CENTRY "save-input" C_save_input 10
dd MV_Infd
dd MV_toIn
dd M_fetch
dd MV_toLimit
dd M_fetch
dd MV_Sourcebuf
dd M_fetch
dd MV_Blk
dd M_fetch
dd M_literal
dd 5
dd MV_Ninputs
dd C_plusstore	; Ninputs++
dd M_exitcolon

CENTRY "default-input" C_default_input 13
dd MC_STDIN
dd MV_toIn
dd C_off
dd MV_toLimit
dd C_off
dd M_Tib
dd MV_Sourcebuf
dd M_store
dd MV_Blk
dd C_off
dd M_exitcolon

CENTRY "restore-input" C_restore_input 13 ; ( <input>|empty -- f )

dd MV_Ninputs	; if Ninputs == 0, leave 0 on the stack. Or, Ninputs--
dd M_fetch
dd C_0neq
dd M_cjump
dd L300
dd MV_Ninputs	; there are <input>'s pending on the stack
dd M_fetch
dd C_1minus
dd MV_Ninputs
dd M_store
dd M_jump
dd L301		; ( <input> -- <input>)
L300:	; no more <input>'s on the stack, put 0 on the stack for the 5 <> below to work
dd M_literal
dd 0

L301:
dd MV_Eof
dd C_off
dd M_literal
dd 5
dd C_neq
dd M_cjump
dd L133
dd C_default_input
dd C_false
dd M_jump
dd L134
L133:
dd MV_Blk
dd M_store
dd MV_Sourcebuf
dd M_store
dd MV_toLimit
dd M_store
dd MV_toIn
dd M_store
dd MV_Infd
dd M_store
dd C_true
L134:
dd M_exitcolon

CENTRY "?restore-input" C_qrestore_input 14 ; ( <input> -- f )
dd C_restore_input
dd C_0eq
dd M_cjump
dd L136
dd C_space
dd M_literal
dd L137
dd M_literal
dd 23
dd C_type
dd C_space
dd C_depth
dd C_dot
dd C_cr
dd C_abort
L136:
dd M_exitcolon

CENTRY "next-input" C_next_input 10 ; when >In < >Limit ( -- true c ). ( --  0 false ) otherwise
dd MV_toIn
dd M_fetch
dd MV_toLimit
dd M_fetch
dd M_less
dd M_cjump
dd L139	; >In >= >Limit
dd C_true	; >In < >Limit
dd C_current_input	; ( -- c )
dd M_jump
dd L140
L139:
dd M_literal
dd 0
dd C_false
L140:
dd M_exitcolon

CENTRY "parse" C_parse 5	; ( c -- a ) Place the counted string in the address in Wordbuf and return that address. c = word delimiter.
dd M_rpush		; ( c -- ) (R -- c )
dd MV_Wordbuf
dd M_fetch		; ( -- Wordb )
dd C_1plus		; ( Wordb -- Wordb+1 )
L142:
dd C_next_input ; ( Wordb+1 -- Wordb+1 f c )
dd M_rfetch 	; ( Wordb+1 f c -- Wordb+1 f  cinitial ) (R c -- c )
dd C_neq 		; ( Wordb+1 f c cinitial -- Wordb+1 f f(c!=cinitial) )
dd M_binand
dd M_cjump
dd L143		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew
dd C_current_input	; ( Wordb+1 -- Wordb+1 c )
dd M_over
dd M_cstore	; ( Wordb+1 c Wordb+1 -- Wordb+1 ) store c at Wordb+1
dd C_1plus		; ( Wordb+1 -- Wordb+2 )
dd M_literal
dd 1
dd MV_toIn
dd C_plusstore	; >In++
dd M_jump
dd L142		; ( Wordb+2 ) repeat
L143:		; ( Wordb+1 ) >In >= >Limit || cinitial == cnew
dd M_literal
dd 1
dd MV_toIn
dd C_plusstore	; >In++
dd M_rpop		; (Wordb+1 -- Wordb+1 c) (R c -- )
dd M_drop		; (Wordb+1 c -- Wordb+1)
dd MV_Wordbuf
dd M_fetch		; (Wordb+1 -- Wordb+1 Wordb)
dd M_dup		; (Wordb+1 Wordb -- Wordb+1 Wordb Wordb)
dd M_rpush		; (Wordb+1 Wordb Wordb -- Wordb+1 Wordb) (R -- Wordb)
dd M_minus		; (Wordb+1 Wordb -- Wordb+1-Wordb) (R -- Wordb)
dd C_1minus	; (Wordb+1-Wordb -- Wordb+1-Wordb-1) (R -- Wordb)
dd M_rfetch	; (Wordb+1-Wordb-1 Wordb -- Wordb+1-Wordb-1 Wordb) (R -- Wordb)
dd M_cstore	; store the length of the string found at Wordb[0]. Counted string at Wordb now.
dd M_rpop		; ( -- Wordb) (R Wordb -- )
dd M_exitcolon

CENTRY "word" C_word 4 ; ( c -- a ) skip the c"s. Placed the counted string in a (as in Wordbuf)
dd M_rpush	; ( -- ) (R -- c )
L145:
dd C_next_input ; ( -- f c2 ) (R c1 -- )
dd M_rfetch	; ( f cnew -- f cnew cinitial ) (R cinitial -- cinitial )
dd M_equal		; ( f cnew cinitial -- f f(cnew==cinitial) ) (R cinitial -- cinitial )
dd M_binand	; ( f f2 -- f&&f2 ) (R cinitial -- cinitial )
dd M_cjump
dd L146		; >In >= >Limit || cinitial != cnew
dd M_literal	; >In < >Limit && cinitial == cnew
dd 1
dd MV_toIn
dd C_plusstore	; >In++
dd M_jump		; repeat
dd L145
L146:
dd M_rpop		; ( -- cinitial ) Sourcebuf+>In = location of first non-matching character
dd C_parse
dd M_exitcolon

CENTRY "accept" C_accept 6	; ( a n -- n ) get line or n chars or EOF from input and store at a
dd M_xswap	; ( n a -- )
dd M_dup	; ( n a a -- )
dd M_rpush
dd M_rpush	; ( n -- ) (R a a -- )
L148:
dd C_qdup	; ( n n -- ) (R a a -- )
dd M_cjump	; (if)
dd L149	; n == 0
dd C_key	; n > 0 ( n -- n c )
dd M_dup	; ( -- n c c )
dd M_literal
dd 10		; ( -- n c c 10 )
dd M_equal	; ( n c c 10 -- n c f ) checking for newline
dd M_over	; ( -- n c f c )
dd M_literal
dd -1		; ( -- n c f c -1 )
dd M_equal	; ( -- n c f1 f2 )
dd M_binor	; ( -- n c f )
dd M_cjump
dd L150
dd C_2drop	; n == -1 || n == 10 (	-- )
dd M_rpop
dd M_rpop
dd M_minus	; ( -- a2-a1 )
dd M_exitcolon	; ( -- n ) (R -- )
L150:		; not EOF or newline continue
dd M_rfetch	; ( n c a -- ) (R a a -- )
dd M_cstore	; store the character at a
dd M_rpop	; ( n a -- ) (R a -- )
dd C_1plus
dd M_rpush	; ( n -- ) (R a1 -- a1 a2 ) a1 = begin address a2 = current address
dd C_1minus	; ( n -- n-1 )
dd M_jump
dd L148	; loop again for the next character
L149:		; n == 0 ( -- ) (R a1 a2 -- )
dd M_rpop	; ( -- a2 ) (R a1 a2 -- a1 )
dd M_rpop	; ( a2 a1 -- ) (R a1 -- )
dd M_minus	; ( a2 a1 -- a2-a1 )
dd M_exitcolon

CENTRY "query" C_query 5	; read from input stream into the Text Input Buffer
dd MV_Eof
dd C_off		; clear EOF flag
dd M_Tib	; constant puts address of tibuffer on the top
dd M_literal
dd 4096	; ( tibuffer -- tibuffer 4096 )
dd C_accept ; ( tibuffer 4096 -- n )
dd M_dup	; ( n -- n n )
dd C_0eq	; ( n n -- n f )
dd MV_Eof
dd M_fetch
dd M_binand	; n == 0 && EOF
dd M_cjump
dd L152		; false condition
dd M_drop	; n == 0 && EOF ( n -- )
dd C_qrestore_input
dd M_jump
dd L153
L152:			; n > 0
dd MV_toLimit
dd M_store		; number of characters to read >Limit = n
dd MV_toIn
dd C_off		; start from 0 >In = 0
L153:
dd M_exitcolon

CENTRY "refill" C_refill 6
dd MV_Blk
dd M_fetch
dd M_cjump
dd L155
dd C_false
dd M_jump
dd L156
L155:
dd C_query
dd C_true
L156:
dd M_exitcolon

CENTRY "findname" C_findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names
dd MV_Findadr
dd M_store
dd M_Dtop
dd M_fetch	; get latest dictionary link
L158:
dd C_qdup
dd M_cjump
dd L159	; seached until the first dictionary entry get out
dd M_dup	; ( a -- a a )
dd C_cellplus	; ( a a -- a a+8) lenth + initial name address
dd M_cfetch	; ( a a+8 -- a immediate|hidden|len) length + initial name
dd M_literal
dd 64		; check the reveal'ed flag 1=hidden, 0=reveal
dd M_binand	; if hidden, goto L161 else L160
dd M_cjump
dd L160
dd M_fetch	; smudge'd dictionary entry, get the previous entry
dd M_jump
dd L161
L160:		; reveal'ed dictionary entry
dd M_dup	; ( a1 -- a1 a1)
dd C_cellplus	; ( a1 a1 -- a1 a1+8)
dd C_count	; ( a1 a1+8 -- a1 a1+8+1 n )
dd M_literal
dd 63
dd M_binand	; ( a1 a1+8+1 n 63 -- a1 a1+8+1 n&63=len )
dd MV_Findadr
dd M_fetch
dd C_count	; ( a1 a1+8+1 len=n&63 a2 -- a1 a1+8+1 n&63 a2+1 n2 )
dd C_compare	; ( a1 a1+8+1 len=n&63 a2+1 n2 -- a1 f ) compare dictionary entry with name
dd C_0eq	; found a match?
dd M_cjump
dd L162		; no match
dd C_cellplus	; match found
dd C_true
dd M_exitcolon
L162:
dd M_fetch
L161:
dd M_jump
dd L158
L159:
dd MV_Findadr
dd M_fetch
dd C_false
dd M_exitcolon

CENTRY "find" C_find 4 ; ( a1 -- a2 f )?
dd C_findname
dd M_cjump
dd L164
dd M_dup
dd M_cfetch
dd M_xswap
dd M_over
dd M_literal
dd 63
dd M_binand
dd M_plus
dd C_1plus
dd C_aligned
dd M_xswap
dd M_literal
dd 128
dd M_binand
dd M_cjump
dd L165
dd M_literal
dd 1
dd M_jump
dd L166
L165:
dd M_literal
dd -1
L166:
dd M_exitcolon
dd M_jump
dd L167
L164:
dd C_false
L167:
dd M_exitcolon

CENTRY "'" C_single_quote 1
dd C_bl
dd C_word
dd C_find
dd C_0eq
dd M_cjump
dd L169
dd C_space
dd C_count
dd C_type
dd M_literal
dd L170
dd M_literal
dd 3
dd C_type
dd C_cr
dd C_abort
L169:
dd M_exitcolon
CENTRY "?stack" C_qstack 6
dd M_stackptr
dd M_S0
dd M_greater
dd M_cjump
dd L172
dd M_literal
dd L173
dd M_literal
dd 16
dd C_type
dd C_cr
dd C_abort
L172:
dd M_exitcolon


dd M_dup ; debug code to show the word found
dd C_count ; ( -- a n)
dd M_xswap ; ( -- n a)
dd MC_STDOUT
dd M_fthwrite
dd M_drop		; drop the return value of write

CENTRY "interpret" C_interpret 9 ; there is stuff in TIB to be interpreted >In and >Limit are set

L175:
dd C_bl
dd C_word	; ( bl -- a ) a = address of counted string
dd M_dup
dd M_cfetch
dd C_0neq
dd M_cjump
dd L176	; count at a = 0
dd C_find	; ( a -- a1 f ) a = address of counted string
dd M_cjump
dd L177

dd M_execute	; found in dictionary, execute
dd C_qstack
dd M_jump
dd L178
L177:		; not found in the dictionary, check for number?
dd C_count
dd C_number
dd C_0eq
dd M_cjump
dd L179
dd C_space
dd C_type
dd M_literal
dd L180	; error I?
dd M_literal
dd 3
dd C_type
dd C_cr
dd C_abort
L179:		; is a number
L178:
dd M_jump
dd L175
L176:
dd M_drop	; count at a = 0 ( a -- )
dd M_exitcolon

CENTRY "create" C_create 6
dd C_align
dd C_here
dd M_rpush
dd M_Dp
dd M_fetch
dd C_comma
dd C_bl
dd C_word
dd M_dup
dd M_cfetch
dd C_here
dd M_xswap
dd C_1plus
dd M_dup
dd M_rpush
dd M_cmove
dd M_rpop
dd C_allot
dd C_align
dd M_literal
dd M_variable
dd M_fetch
dd C_comma
dd M_rpop
dd M_Dp
dd M_store
dd M_exitcolon
CENTRY "variable" C_variable 8
dd C_create
dd M_literal
dd 0
dd C_comma
dd M_exitcolon
CENTRY "constant" C_constant 8
dd C_create
dd M_literal
dd M_constant
dd M_fetch
dd C_here
dd M_literal
dd 1
dd C_cells
dd M_minus
dd M_store
dd C_comma
dd M_exitcolon
CENTRY "immediate" C_immediate 9
dd M_Dp
dd M_fetch
dd C_cellplus
dd M_dup
dd M_cfetch
dd M_literal
dd 128
dd M_binor
dd M_xswap
dd M_cstore
dd M_exitcolon
CENTRY ">cfa" C_tocfa 4
dd C_count
dd M_literal
dd 63
dd M_binand
dd M_plus
dd C_aligned
dd M_exitcolon
CENTRY "compile" C_compile 7
dd C_findname
dd M_cjump
dd L188
dd M_dup
dd M_cfetch
dd M_literal
dd 128
dd M_binand
dd M_cjump
dd L189
dd C_tocfa	; immediate
dd M_execute
dd C_qstack
dd M_jump
dd L190
L189:
dd C_tocfa
dd C_comma
L190:
dd M_jump
dd L191
L188:
dd C_count
dd C_number
dd C_0eq
dd M_cjump
dd L192
dd C_space
dd C_type
dd M_literal
dd L193
dd M_literal
dd 3
dd C_type
dd C_cr
dd C_abort
dd M_jump
dd L194
L192:
dd M_literal
dd M_literal
dd C_comma
dd C_comma
L194:
L191:
dd M_exitcolon
CENTRY "]" C_close_bracket 1
dd MV_State
dd C_on
L196:
dd C_bl
dd C_word
dd M_dup
dd M_cfetch
dd C_0eq
dd M_cjump
dd L197
dd M_drop
dd C_refill
dd M_jump
dd L198
L197:
dd C_compile
dd MV_State
dd M_fetch
L198:
dd M_cjump
dd L199
dd M_jump
dd L196
L199:
dd M_exitcolon
CIENTRY "[" CI_open_bracket 1
dd MV_State
dd C_off
dd M_exitcolon
CENTRY "smudge" C_smudge 6
dd M_Dp
dd M_fetch
dd C_cellplus
dd M_dup
dd M_cfetch
dd M_literal
dd 64
dd M_binor
dd M_xswap
dd M_cstore
dd M_exitcolon
CENTRY "reveal" C_reveal 6
dd M_Dp
dd M_fetch
dd C_cellplus
dd M_dup
dd M_cfetch
dd M_literal
dd 64
dd C_invert
dd M_binand
dd M_xswap
dd M_cstore
dd M_exitcolon
CENTRY ":" C_colon 1
dd C_create
dd C_smudge
dd M_literal
dd M_colon
dd M_fetch
dd C_here
dd M_literal
dd 1
dd C_cells
dd M_minus
dd M_store
dd C_close_bracket
dd M_exitcolon
CIENTRY ";" CI_semicolon 1
dd M_literal
dd M_exitcolon
dd C_comma
dd MV_State
dd C_off
dd C_reveal
dd M_exitcolon
CIENTRY "recurse" CI_recurse 7
dd M_Dp
dd M_fetch
dd C_cellplus
dd C_tocfa
dd C_comma
dd M_exitcolon
CENTRY "char" L206 4
dd C_bl
dd C_word
dd C_1plus
dd M_cfetch
dd M_exitcolon
CENTRY "literal" C_literal 7
dd M_literal
dd M_literal
dd C_comma
dd C_comma
dd M_exitcolon
CENTRY "sliteral" C_sliteral 8
dd M_literal
dd M_sliteral
dd C_comma
dd C_here
dd M_literal
dd 34
dd C_parse
dd M_dup
dd M_cfetch
dd C_1plus
dd M_rpush
dd M_xswap
dd M_rfetch
dd M_cmove
dd M_rpop
dd C_allot
dd C_align
dd M_exitcolon
CENTRY "string" C_string 6
dd C_word
dd M_dup
dd M_cfetch
dd C_1plus
dd M_rpush
dd C_here
dd M_rfetch
dd M_cmove
dd M_rpop
dd C_allot
dd M_exitcolon
CIENTRY "[char]" CI_char_brackets 6
dd C_bl
dd C_word
dd C_1plus
dd M_cfetch
dd C_literal
dd M_exitcolon
CIENTRY "[']" CI_quote_brackets 3
dd C_single_quote
dd C_literal
dd M_exitcolon
CIENTRY "(" CI_openparen 1
dd M_literal
dd 41
dd C_parse
dd M_drop
dd M_exitcolon
CIENTRY "\\" CI_backslash 1
dd MV_Blk
dd M_fetch
dd M_cjump
dd L214
dd MV_toIn
dd M_fetch
dd M_literal
dd 63
dd M_plus
dd M_literal
dd 63
dd C_invert
dd M_binand
dd MV_toIn
dd M_store
dd M_jump
dd L215
L214:
dd MV_toLimit
dd M_fetch
dd MV_toIn
dd M_store
L215:
dd M_exitcolon
CENTRY "(?abort)" C_qabort_parens 8
dd MV_State
dd M_cjump
dd L217
dd C_space
dd C_type
dd C_cr
dd C_abort
dd M_jump
dd L218
L217:
dd C_2drop
L218:
dd M_exitcolon
CIENTRY "abort\"" CI_abort_double_quote 6
dd C_sliteral
dd M_literal
dd C_qabort_parens
dd C_comma
dd M_exitcolon
CENTRY "\"" C_double_quote 1
dd M_literal
dd 34
dd C_word
dd C_count
dd M_rpush
dd C_here
dd M_rfetch
dd M_cmove
dd C_here
dd M_rpop
dd M_dup
dd C_allot
dd M_exitcolon
CENTRY "c\"" C_cdouble_quote 2
dd M_literal
dd 34
dd C_word
dd M_dup
dd M_cfetch
dd C_1plus
dd M_rpush
dd C_here
dd M_rfetch
dd M_cmove
dd C_here
dd M_rpop
dd C_allot
dd M_exitcolon
CIENTRY "s\"" CI_sdouble_quote 2
dd C_sliteral
dd M_exitcolon
CIENTRY ".\"" CI_dotstr 2
dd C_sliteral
dd M_literal
dd C_type
dd C_comma
dd M_exitcolon
CIENTRY "if" CI_if 2
dd M_literal
dd M_cjump
dd C_comma
dd C_here
dd M_literal
dd 0
dd C_comma
dd M_exitcolon
CIENTRY "else" CI_else 4
dd M_literal
dd M_jump
dd C_comma
dd C_here
dd M_rpush
dd M_literal
dd 0
dd C_comma
dd C_here
dd M_xswap
dd M_store
dd M_rpop
dd M_exitcolon
CIENTRY "then" CI_then 4
dd C_here
dd M_xswap
dd M_store
dd M_exitcolon
CIENTRY "begin" CI_begin 5
dd C_here
dd M_exitcolon
CIENTRY "again" CI_again 5
dd M_literal
dd M_jump
dd C_comma
dd C_comma
dd M_exitcolon
CIENTRY "until" CI_until 5
dd M_literal
dd M_cjump
dd C_comma
dd C_comma
dd M_exitcolon
CIENTRY "while" CI_while 5
dd M_literal
dd M_cjump
dd C_comma
dd C_here
dd M_literal
dd 0
dd C_comma
dd M_exitcolon
CIENTRY "repeat" CI_repeat 6
dd M_literal
dd M_jump
dd C_comma
dd M_xswap
dd C_comma
dd C_here
dd M_xswap
dd M_store
dd M_exitcolon
CIENTRY "do" CI_do 2
dd M_literal
dd M_doinit
dd C_comma
dd M_literal
dd 0
dd C_here
dd M_exitcolon
CIENTRY "loop" CI_loop 4
dd M_literal
dd M_doloop
dd C_comma
dd C_comma
dd C_qdup
dd M_cjump
dd L234
dd C_here
dd M_xswap
dd M_store
L234:
dd M_exitcolon
CIENTRY "+loop" CI_ploop 5
dd M_literal
dd M_doploop
dd C_comma
dd C_comma
dd C_qdup
dd M_cjump
dd L236
dd C_here
dd M_xswap
dd M_store
L236:
dd M_exitcolon
CENTRY "w/o" C_wo 3
dd M_literal
dd 1
dd M_literal
dd 512
dd M_binor
dd M_literal
dd 64
dd M_binor
dd M_exitcolon
CENTRY "r/o" C_ro 3
dd M_literal
dd 0
dd M_exitcolon
CENTRY "r/w" C_rw 3
dd M_literal
dd 2
dd M_exitcolon
CENTRY "open-file" C_open_file 9
dd M_rpush
dd C_pad
dd M_literal
dd 1024
dd M_plus
dd M_xswap
dd M_dup
dd M_rpush
dd M_cmove
dd M_literal
dd 0
dd M_rpop
dd C_pad
dd M_plus
dd M_literal
dd 1024
dd M_plus
dd M_cstore
dd C_pad
dd M_literal
dd 1024
dd M_plus
dd M_rpop
dd M_literal
dd 420
dd M_fthopen
dd M_dup
dd M_literal
dd -1
dd M_greater
dd M_exitcolon
CENTRY "close-file" C_close_file 10
dd M_fthclose
dd C_0eq
dd M_exitcolon
CENTRY "read-file" C_read_file 9
dd M_fthread
dd M_dup
dd M_literal
dd -1
dd C_neq
dd M_exitcolon
CENTRY "write-file" C_write_file 10
dd M_fthwrite
dd M_literal
dd -1
dd C_neq
dd M_exitcolon
CENTRY "reposition-file" C_reposition_file 15
dd M_fthseek
dd M_literal
dd -1
dd C_neq
dd M_exitcolon
CENTRY "?fcheck" C_qfcheck 7
dd C_0eq
dd M_cjump
dd L246
dd C_space
dd M_literal
dd L247
dd M_literal
dd 9
dd C_type
dd C_cr
dd C_abort
L246:
dd M_exitcolon
CENTRY "bye" C_bye 3
dd M_literal
dd 0
dd M_terminate
dd M_exitcolon

CENTRY "include" C_include 7
dd C_bl
dd C_word
dd M_rpush
dd MV_toLimit
dd M_fetch
dd MV_toIn
dd M_store
dd C_save_input
dd M_rpop
dd C_count
dd C_ro
dd C_open_file
dd C_qfcheck
dd MV_Infd
dd M_store
dd M_exitcolon

CENTRY "crash" C_crash 5
dd M_literal
dd L251
dd M_literal
dd 30
dd C_type
dd C_cr
dd C_abort
dd M_exitcolon

CENTRY "quit" C_quit 4 ; interpreter loop
dd M_reset ; initialize return stack
dd M_clear	; SP = sstack_end initialize data stack
L253:
dd C_query

; dd MV_toLimit	; show the line read, for debugging
; dd M_fetch
; dd M_Tib
; dd MC_STDOUT
; dd M_fthwrite
; dd M_drop		; drop the return value of write
; dd C_cr
; dd C_space

dd C_interpret

dd M_jump
dd L253
dd M_exitcolon	; why is this needed?

CENTRY "(abort)" C_parenabort 7 ; TODO correct below stack notations
dd MV_State	; ( mv_State -- )
dd C_off		; off sets variable state = 0
dd M_Tib	; constant puts address of tibuffer on the top of stack
dd MV_Sourcebuf	; variable sourcebuf
dd M_store	; variable sourcebuf = address of tibuffer
dd MV_Blk	; variable blk
dd C_off	; off variable blk = 0
dd MC_STDIN
dd MV_Infd
dd M_store
dd MC_STDOUT
dd MV_Outfd
dd M_store
dd MC_STDERR
dd MV_Errfd
dd M_store
dd C_quit	; quit resets stacks and is the interpreter loop
dd M_exitcolon	; why is this needed? quit does not return unless it breaks

CENTRY "oldboot" C_oldboot 7 ; TODO correct below stack notations and this is obsolete. leaving it here for reference until it all works well
dd M_reset
dd M_clear	; SP = sstack_end
dd M_stackptr	; (D -- FFEND)
dd M_S0
dd M_store	; s0 = FFEND
dd M_Dp	; heaptop = heapend
dd M_fetch	; ( heapend -- )
dd M_literal
dd 1		; ( heapend 1 -- )
dd C_cells	; cells ( heapend 8 -- )
dd M_minus	; ( heapend-8 -- )
dd M_fetch	; ( contents_from_heapend-8 -- )
dd M_Args	; variable args
dd M_store	; args = contents_from_heapend-8
dd M_literal
dd C_parenabort ; ( (abort) -- )
dd MV_Abortvec	; variable abortvec
dd M_store	; variable abortvec = (abort) code address
dd M_Wordb	; constant puts address of wordbuffer on the top of stack
dd MV_Wordbuf	; variable wordbuf
dd M_store	; variable wordbuf = address of wordbuffer
dd M_Tib	; constant puts address of tibuffer on the top of stack
dd MV_Sourcebuf	; variable sourcebuf
dd M_store	; variable sourcebuf = address of tibuffer
dd M_literal
dd 0
dd MV_Infd
dd M_store	; stdin = 0
dd M_literal
dd 1
dd MV_Outfd
dd M_store	; stdout = 1
dd MV_State
dd C_off	; off stores 0 at state
dd C_decimal	; decimal setting base = 0
dd C_quit	; quit
dd M_exitcolon


dd M_literal	; test code
dd 66
dd M_Wordb
dd M_store
dd M_literal
dd 1
dd M_Wordb
dd MC_STDOUT
dd M_fthwrite
dd M_drop		; drop the return value of write
dd M_literal
dd 1
dd M_Wordb
dd MC_STDIN
dd M_fthread
dd M_drop		; drop the return value of read

CENTRY "boot" C_boot 4

dd M_reset ; initialize return stack
dd M_clear	; SP = sstack_end initialize data stack
			; s0 puts FFEND on the stack
			; no args

dd M_literal
dd C_parenabort ; ( (abort) -- )
dd MV_Abortvec	; variable that puts (abort) code address on the stack
dd M_store	; variable abortvec = (abort) code address

dd M_Wordb	; variable puts address of wordbuffer on the top of stack
dd MV_Wordbuf ; variable wordbuf
dd M_store	; variable wordbuf = address of wordbuffer

dd M_Tib	; constant puts address of tibuffer on the top of stack
dd MV_Sourcebuf	; variable sourcebuf
dd M_store	; variable sourcebuf = address of tibuffer

dd M_Dp
dd MV_H0	; H0 = here at startup
dd M_store

dd MC_STDIN
dd MV_Infd
dd M_store     ; stdin = 0
dd MC_STDOUT
dd MV_Outfd
dd M_store
dd MC_STDERR
dd MV_Errfd
dd M_store

dd MV_State
dd C_off	; off stores 0 at state
dd C_decimal	; decimal sets base = 10

dd C_quit	; quit
dd M_exitcolon

L137:
db "unable to restore input"
L170:
db " Q?"
L173:
db " stack underflow"
L180:
db " I?"
L193:
db " C?"
L247:
db "I/O error"
L251:
db "uninitialized execution vector"
L255:
db " ok"
