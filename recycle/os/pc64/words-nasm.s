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
CENTRY "aligned" C_aligned 7	; align a number to a multiple of 8
dd M_literal
dd 7
dd M_plus
dd M_literal
dd -8
dd M_binand
dd M_exitcolon
CENTRY "cells" C_cells 5
dd M_literal
dd 3			; (index << 2) -> (index << 3) for amd64
dd M_lshift
dd M_exitcolon
CENTRY "cells+" C_cells_plus 6 ; ( n1 n2 -- n1+(n2*cellsize) )
dd C_cells
dd M_plus
dd M_exitcolon
CENTRY "cell+" C_cell_plus 5
dd M_literal
dd 1
dd C_cells_plus
dd M_exitcolon

CENTRY "depth" C_depth 5
dd MV_S0
dd M_stackptr
dd M_minus
dd M_literal
dd 3
dd M_rshift
dd M_literal
dd 1
dd M_minus
dd M_exitcolon
CENTRY "nip" C_nip 3 ; ( n1 n2 -- n2 )
dd M_xswap
dd M_drop
dd M_exitcolon
CENTRY "rot" C_rot 3 ; ( n1 n2 n3 -- n2 n3 n1 )
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
dd L_qdup	; when n != 0, go to L20
dd M_drop	; when n == 0 ( n n -- n)
L_qdup:		; when n != 0 ( n n )
dd M_exitcolon

CENTRY "pick" C_pick 4
dd C_qdup
dd M_cjump
dd L_pick
dd M_literal
dd 1
dd M_plus
dd C_cells
dd M_stackptr
dd M_plus
dd M_fetch
dd M_jump
dd L_pick_1
L_pick:
dd M_dup
L_pick_1:
dd M_exitcolon

CENTRY "tuck" C_tuck 4 ; ( n1 n2 -- n2 n1 n2 )
dd M_dup
dd M_rpush
dd M_xswap
dd M_rpop
dd M_exitcolon
CENTRY "/" C_divides 1
dd M_slashmod
dd C_nip
dd M_exitcolon

CENTRY "+!" C_plusstore 2 ; ( n 'a -- ) a@ = a@+n
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
dd L_max
dd M_drop
dd M_jump
dd L_max_1
L_max:
dd C_nip
L_max_1:
dd M_exitcolon

CENTRY "min" C_min 3
dd C_2dup
dd M_less
dd M_cjump
dd L_min
dd M_drop
dd M_jump
dd L_min_1
L_min:
dd C_nip
L_min_1:
dd M_exitcolon

CENTRY "signum" C_signum 6
dd M_dup
dd C_0gt
dd M_cjump
dd L_signum
dd M_drop
dd M_literal
dd 1
dd M_jump
dd L_signum_1
L_signum:
dd C_0lt
dd M_cjump
dd L_signum_2
dd M_literal
dd -1
dd M_jump
dd L_signum_3
L_signum_2:
dd M_literal
dd 0
L_signum_3:
L_signum_1:
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
dd L_abs
dd C_negate
L_abs:
dd M_exitcolon

CENTRY "emit" C_emit 4	; ( character -- )
dd MV_Iobuf		; variable iobuf address
dd M_cstore	; variable iobuf has character
dd MV_Outfd
dd M_fetch		; outfd
dd MV_Iobuf		; variable iobuf address
dd M_literal
dd 1			; ( outfd iobuf 1 )
dd M_syswrite	; ( 1 iobuf outfd --  )
dd M_drop		; drop the return value of write
dd M_exitcolon

CENTRY "type" C_type 4	; ( addr n -- )
dd M_rpush		; ( addr ) (R n )
dd M_rpush		; ( ) (R n addr )
dd MV_Outfd
dd M_fetch		; ( outfd )
dd M_rpop		; ( outfd addr ) (R n )
dd M_rpop		; ( outfd addr n ) (R )
dd M_syswrite	; ( 1 addr n --  )
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
L_emits:
dd C_qdup
dd M_cjump
dd L_emits_1
dd M_over
dd C_emit
dd C_1minus
dd M_jump
dd L_emits
L_emits_1:
dd M_drop
dd M_exitcolon

CENTRY "spaces" C_spaces 6
dd C_bl
dd M_xswap
dd C_emits
dd M_exitcolon

CENTRY "count" C_count 5 ; ( 'counted-string -- 'text count ) a = address of counted string ( a - a+1 a[0])
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
L_compare:
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
dd L_compare_1		; matches
dd C_2nip	; does not match ( a1 a2 f -- f ) (R n1 n2 0 nmin -- )
dd M_unloop	; ( f -- f ) (R n1 n2 0 nmin -- n1 n2)
dd M_unloop	; ( f -- f ) (R n1 n2 -- )
dd M_exitcolon
L_compare_1:
dd M_doloop
dd L_compare
dd C_2drop	; ( a1 a2 -- ) (R n1 n2 -- )
dd M_rpop
dd M_rpop	; ( n2 n1 -- ) (R -- )
dd M_minus	; ( -- n1-n2 )
dd C_signum
dd M_exitcolon

CENTRY "erase" C_erase 5	; ( a n -- ) put 0 at a for n characters
dd M_literal
dd 0
dd M_doinit
L_erase_loop:
dd M_literal
dd 0
dd M_over
dd M_cstore
dd C_1plus
dd M_doloop
dd L_erase_loop
dd M_drop
dd M_exitcolon

CENTRY "fill" C_fill 4	; ( a n c -- ) fill c at a for n characters
dd M_xswap
dd M_literal
dd 0
dd M_doinit
L_fill_loop:
dd C_2dup
dd M_xswap
dd M_i
dd M_plus
dd M_cstore
dd M_doloop
dd L_fill_loop
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
L_search:
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
dd L_search_1
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
L_search_1:
dd M_doloop
dd L_search
dd M_drop
dd M_rpop
dd C_false
dd M_exitcolon

CENTRY "here" C_here 4
dd MV_Here		; the address on the top of stack is 0x583288, which is correct
dd M_fetch
dd M_exitcolon

CENTRY "there" C_there 5	; variable here
dd MV_There
dd M_fetch
dd M_exitcolon

CENTRY "," C_comma 1
dd C_here
dd M_store
dd M_literal
dd 8
dd MV_Here
dd C_plusstore
dd M_exitcolon

CENTRY "c," C_c 2
dd C_here
dd M_cstore
dd M_literal
dd 1
dd MV_Here
dd C_plusstore
dd M_exitcolon

CENTRY "allot" C_allot 5 ; ( n -- ) here = here+n
dd MV_Here
dd C_plusstore
dd M_exitcolon

CENTRY "vallot" C_vallot 6 ; allot on the variable space ( n -- ) there = there+n
dd MV_There
dd C_plusstore
dd M_exitcolon

CENTRY "pad" C_pad 3
dd C_here
dd M_literal
dd 256
dd M_plus
dd M_exitcolon
CENTRY "align" C_align 5	; ( -- ) align here to a cell boundary
dd C_here		; Dp @
dd C_aligned	; here is aligned to a multiple of 8
dd MV_Here			; store the aligned here at Dp
dd M_store		; Dp contains aligned_here
dd M_exitcolon
CENTRY "unused" C_unused 6
dd MV_Here
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
dd L_hash
dd M_literal
dd 97
dd M_plus
dd M_literal
dd 10
dd M_minus
dd M_jump
dd L_hash_1
L_hash:
dd M_literal
dd 48
dd M_plus
L_hash_1:
dd MV_toNum
dd M_fetch
dd C_1minus
dd M_dup
dd MV_toNum
dd M_store
dd M_cstore
dd M_exitcolon

CENTRY "#s" C_hashs 2
L_hashs:
dd C_hash
dd M_dup
dd M_cjump
dd L_hashs_1
dd M_jump
dd L_hashs
L_hashs_1:
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
dd L_sign
dd M_literal
dd 45
dd C_hold
L_sign:
dd M_exitcolon

CENTRY "c(.)" C_counted_paren_dot_paren 4	; convert the top of stack to a counted string ( n1 -- 'cs )
dd C_paren_dot_paren ; ( 'text n2 )
dd M_xswap		; ( n2 'text )
dd M_literal
dd 1
dd M_minus		; ( n2 'text-1 )
dd M_xswap
dd M_over		; ( 'text-1 n2 'text-1 )
dd M_cstore		; ( 'text-1 )
dd M_exitcolon

CENTRY "(.)" C_paren_dot_paren 3	; convert the top of stack to a string ( n1 -- 'text n2 )
dd M_dup		; ( n -- n n )
dd C_abs		; ( n n -- n u )
dd C_fromhash	; pad = h+256; >num = pad+1024
dd C_hashs		; ( n u1 -- n n2 )
dd M_xswap		; ( n n2 -- n2 n )
dd C_sign		; ( n2 n -- n2 )
dd C_hashfrom	; ( u1 -- a n )
dd M_exitcolon

CENTRY "." C_dot 1	; print the top of stack ( n -- )
dd C_paren_dot_paren ; ( n1 -- 'text n2 )
dd C_type
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
dd L_digit
dd M_literal
dd 55
dd M_minus
dd M_jump
dd L_digit_1
L_digit:
dd M_dup
dd M_literal
dd 97
dd M_literal
dd 123
dd C_within
dd M_cjump
dd L_digit_2
dd M_literal
dd 87
dd M_minus
dd M_jump
dd L_digit_3
L_digit_2:
dd M_dup
dd M_literal
dd 48
dd M_literal
dd 58
dd C_within
dd M_cjump
dd L_digit_4
dd M_literal
dd 48
dd M_minus
dd M_jump
dd L_digit_5
L_digit_4:
dd M_drop
dd C_false
dd M_exitcolon
L_digit_5:
L_digit_3:
L_digit_1:
dd M_dup
dd MV_Base
dd M_fetch
dd M_less
dd M_cjump
dd L_digit_6
dd C_true
dd M_jump
dd L_digit_7
L_digit_6:
dd M_drop
dd C_false
L_digit_7:
dd M_exitcolon

CENTRY "number" C_number 6 ; ( a n1 -- n2 -1 | a n1 0 )
dd M_xswap	; ( a n1 -- n1 a )
dd M_dup	; ( n1 a -- n1 a a )
dd M_cfetch	; ( n1 a a -- n1 a c )
dd M_literal
dd 45		; ( n1 a c -- n1 a c - )
dd M_equal	; ( n1 a c -- n1 a f )
dd M_cjump	; ( n1 a c -- n1 a )
dd L_number_no_minus	; c != -

dd C_1plus	; c == - ( n1 a -- n1 a+1 )
dd M_xswap
dd C_1minus	; c == - ( a+1 n1 -- a+1 n1-1 )
dd M_literal
dd -1		; ( a+1 n1-1 -- a+1 n1-1 -1 )
dd M_rpush	; ( a+1 n1-1 -- a+1 n1-1 ) (R -- -1)
dd M_jump
dd L_number_digits

L_number_no_minus:		; c != -
dd M_xswap	; ( n1 a -- a n1)
dd M_literal
dd 1
dd M_rpush	; ( a n1 1 -- a n1 ) (R -- 1)

L_number_digits:	; ( a n1 ) (R sign )
dd M_dup	; ( a n1 n1 ) (R sign)
dd M_rpush	; ( a n1 ) (R sign n1)
dd M_literal
dd 0		; ( a n1 0) (R sign n1)
dd M_xswap	; ( a 0 n1) (R sign n1)
dd M_literal
dd 0		; ( a 0 n1 0) (R sign n1)
dd M_doinit	; ( a num=0 ) (R sign n1 nindex nlimit ) num = 0

L_number_loop:
dd MV_Base	; ( a num Base )	(R sign n1 nindex nlimit )
dd M_fetch	; ( a num base )	(R sign n1 nindex nlimit)
dd M_multiply	; ( a num*base )	(R sign nindex nlimit)
dd M_over	; ( a num*base a)		(R sign nindex nlimit)
dd M_i		; ( a num*base a nindex)	(R sign nindex nlimit)
dd M_plus	; ( a num*base a+nindex)	(R sign nindex nlimit)
dd M_cfetch	; ( a num*base c)		(R sign nindex nlimit)
dd C_digit	; ( a num*base d 0|-1 )		(R sign nindex nlimit)
dd M_cjump
dd L_number_not_a_digit ; not a digit
dd M_plus	; ( a num*base+d )		(R sign nindex nlimit)
dd M_jump
dd L_number_next

L_number_not_a_digit:	; ( a num*base d )		(R sign nindex nlimit)
dd M_drop
dd M_unloop
dd M_rpop
dd M_rpop
dd M_drop
dd C_false
dd M_exitcolon

L_number_next:
dd M_doloop
dd L_number_loop

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

CENTRY "bufferfilename@" C_bufferfilename_fetch 15 ; ( index -- 'counted-string ) fetch label
dd C_cells
dd MV_Bufferfilenames
dd M_plus
dd M_fetch
dd M_exitcolon

CENTRY "bufferfilename!" C_bufferfilename_store 15 ; ( 'text index -- ) store label
dd C_cells
dd MV_Bufferfilenames
dd M_plus
dd M_store
dd M_exitcolon

CENTRY ">word" C_toword 5 ; ( 'Bufferfds -- 'Wordfd )
dd MC_WORDNUM
dd C_cells_plus
dd M_exitcolon

CENTRY "wordfd@" C_wordfd_fetch 7
dd MV_Bufferfds
dd C_toword
dd M_fetch
dd M_exitcolon

CENTRY "wordfd!" C_wordfd_store 7
dd MV_Bufferfds
dd C_toword
dd M_store
dd M_exitcolon

CENTRY "wordfilename@" C_wordfilename_fetch 13
dd MV_Bufferfilenames
dd C_toword
dd M_fetch
dd M_exitcolon

CENTRY "wordfilename!" C_wordfilename_store 13
dd MV_Bufferfilenames
dd C_toword
dd M_store
dd M_exitcolon

CENTRY ">line" C_toline 5 ; ( 'Bufferfds -- 'Wordfd )
dd MC_LINENUM
dd C_cells_plus
dd M_exitcolon

CENTRY "linefd@" C_linefd_fetch 7
dd MV_Bufferfds
dd C_toline
dd M_fetch
dd M_exitcolon

CENTRY "linefd!" C_linefd_store 7
dd MV_Bufferfds
dd C_toline
dd M_store
dd M_exitcolon

CENTRY "linefilename@" C_linefilename_fetch 13
dd MV_Bufferfilenames
dd C_toline
dd M_fetch
dd M_exitcolon

CENTRY "linefilename!" C_linefilename_store 13
dd MV_Bufferfilenames
dd C_toline
dd M_store
dd M_exitcolon

CENTRY ">doublequote" C_todoublequote 12 ; ( 'Bufferfds -- 'Doublequotefd )
dd MC_DOUBLEQUOTENUM
dd C_cells_plus
dd M_exitcolon

CENTRY "doublequotefd@" C_doublequotefd_fetch 14
dd MV_Bufferfds
dd C_todoublequote
dd M_fetch
dd M_exitcolon

CENTRY "doublequotefd!" C_doublequotefd_store 14
dd MV_Bufferfds
dd C_todoublequote
dd M_store
dd M_exitcolon

CENTRY "doublequotefilename@" C_doublequotefilename_fetch 20
dd MV_Bufferfilenames
dd C_todoublequote
dd M_fetch
dd M_exitcolon

CENTRY "doublequotefilename!" C_doublequotefilename_store 20
dd MV_Bufferfilenames
dd C_todoublequote
dd M_store
dd M_exitcolon

CENTRY ">closeparen" C_tocloseparen 11 ; ( 'Bufferfds -- 'Closeparenfd )
dd MC_CLOSEPARENNUM
dd C_cells_plus
dd M_exitcolon

CENTRY "closeparenfd@" C_closeparenfd_fetch 13
dd MV_Bufferfds
dd C_tocloseparen
dd M_fetch
dd M_exitcolon

CENTRY "closeparenfd!" C_closeparenfd_store 13
dd MV_Bufferfds
dd C_tocloseparen
dd M_store
dd M_exitcolon

CENTRY "closeparenfilename@" C_closeparenfilename_fetch 19
dd MV_Bufferfilenames
dd C_tocloseparen
dd M_fetch
dd M_exitcolon

CENTRY "closeparenfilename!" C_closeparenfilename_store 19
dd MV_Bufferfilenames
dd C_tocloseparen
dd M_store
dd M_exitcolon

; stdinput : set all buffer fd's to -1, Infd = stdin
; args : set all buffer fd's to -1, Infd = #p/<pid>/args
; input@ : buffer fds and Infd -> stack
; input! : stack -> buffer fds and Infd
; -input : close all buffer fds and Infd, set buffer fds to -1
; buffer file names are setup in boot

CENTRY "stdinput" C_stdinput 8 ; stream input from stdin into Text input buffer
dd MC_STDIN
dd MV_Infd
dd M_store

dd MV_Bufferfds
dd MC_NBUFFERS
dd M_literal
dd 0
dd M_doinit
L_stdinput_loop:

dd M_literal
dd -1
dd M_over	; ( 'Bufferfd -1 'Bufferfd )
dd M_store

dd M_literal
dd 1
dd C_cells
dd M_plus

dd M_doloop
dd L_stdinput_loop
dd M_drop
dd M_exitcolon

CENTRY "args" C_args 4 ; stream input from #p/<pid>/args into Text input buffer
dd MV_Argsfilename	; ( 'args_filename_counted_string ) filled by the starter
dd M_cfetch
dd M_literal
dd 0
dd M_equal
dd M_cjump
dd L_args_read
dd M_exitcolon

L_args_read:
dd MV_Argsfilename
dd C_count
dd C_ro
dd C_open_file
dd M_drop
dd MV_Infd
dd M_store

dd M_exitcolon

CENTRY "input@" C_input_fetch 6 ; ( -- Bufferfds Infd #Buffers+1 ) save input stream onto the stack and replace the buffer fd's with -1

dd MV_Bufferfds
dd MC_NBUFFERS
dd M_literal
dd 0
dd M_doinit
L_input_fetch_loop:

dd M_dup	; ( 'Bufferfd 'Bufferfd )
dd M_fetch

dd M_xswap	; ( fd 'Bufferfd )

dd M_literal
dd -1
dd M_over	; ( fd 'Bufferfd -1 'Bufferfd )
dd M_store	; ( fd 'Bufferfd )

dd M_literal
dd 1
dd C_cells
dd M_plus

dd M_doloop
dd L_input_fetch_loop
dd M_drop	; ( fd0 fd1 .. fdn )

dd MV_Infd
dd M_fetch	; ( fd0 fd1 .. fdn infd )

dd MC_NBUFFERS
dd M_literal
dd 1
dd M_plus	; ( fd0 fd1 .. fdn infd n+1 )

dd M_exitcolon

CENTRY "input!" C_input_store 6 ; ( fd0 fd1 .. fdn infd n+1 | empty -- ) restore input stream from the stack or stdinput
dd M_dup		; check if there is #Buffers+1 on the top of stack

dd MC_NBUFFERS
dd M_literal
dd 1
dd M_plus
dd M_equal	; is the top of stack == #Buffers+1
dd M_cjump
dd L_input_store_no_stream	; top of stack <> #Buffers+1, there is no input stream on the stack, use the default input

dd M_drop	; drop the #Buffers+1 on the top of stack

dd MV_Infd
dd M_store	; ( fd0 fd1 .. fdn )

dd MV_Bufferfds
dd MC_NBUFFERS
dd C_cells
dd M_plus	; ( fd0 fd1 .. fdn 'Bufferfds+(NBUFFERS*cellsize) )

dd MC_NBUFFERS
dd M_literal
dd 0
dd M_doinit
L_input_store_loop:

dd M_literal
dd 1
dd C_cells
dd M_minus	; ( fd0 fd1 .. fdn 'Bufferfds-(1*cellsize) )
dd M_dup	; ( fd0 fd1 .. fdn 'Bufferfds-(1*cellsize) 'Bufferfds-(1*cellsize) )
dd M_rpush	; ( fd0 fd1 .. fdn 'Bufferfds-(1*cellsize) ) (R 'Bufferfds-(1*cellsize) )
dd M_store

dd M_rpop	; ( fd0 fd1 .. fdn-1 'Bufferfds-(1*cellsize) )

dd M_doloop
dd L_input_store_loop
dd M_drop	; remove the 'Bufferfds on top

dd MV_Eof
dd C_off	; reset Eof back to 0

dd C_true	; ( true )
dd M_exitcolon

L_input_store_no_stream:	; there is no input stream on the stack
dd C_stdinput	; no input stream on the stack, use default input from now
dd C_false		; ( 0 )
dd M_exitcolon

; closefds: close all buffer fds and Infd, set buffer fds and Infd to -1
CENTRY "-input" C_close_input 6 ; (  )	; close the current input stream
dd MV_Bufferfds
dd MC_NBUFFERS
dd M_literal
dd 0
dd M_doinit
L_close_input:

dd M_dup	; ( 'Bufferfd 'Bufferfd )
dd M_fetch
dd M_literal
dd -1
dd C_neq
dd M_cjump
dd L_close_next	; == -1, check next fd

dd M_dup	; ( 'Bufferfd 'Bufferfd )
dd M_fetch	; ( 'Bufferfd fd )
dd C_close_file	; ( 'Bufferfd ioresult )
dd M_drop	; ( 'Bufferfd )

dd M_dup	; ( 'Bufferfd 'Bufferfd )
dd M_literal
dd -1
dd M_xswap	; ( 'Bufferfd -1 'Bufferfd )
dd M_store	; ( 'Bufferfd )

L_close_next:
dd M_literal
dd 1
dd C_cells
dd M_plus

dd M_doloop
dd L_close_input

dd M_drop

dd M_literal
dd -1
dd MV_Infd	; ( -1 'Infd )
dd M_dup	; ( -1 'Infd 'Infd )
dd M_fetch	; ( -1 'Infd fd )
dd C_close_file	; ( -1 'Infd ioresult )
dd M_drop	; ( -1 'Infd )
dd M_store

dd MV_Eof
dd C_off	; reset Eof back to 0

dd M_exitcolon

CENTRY "-+input" C_restore_input 7 ; ( <input> -- ) ; use the input stream on the stack or abort
dd C_close_input

dd C_input_store
dd C_0eq
dd M_cjump
dd L_restore_input_exit	; input stream restored

; no input stream on the stack to restore, show error and abort
dd C_space
dd M_literal
dd L_restore_input_error_message
dd C_count
dd C_type
dd C_space
dd C_depth
dd C_dot
dd C_cr

dd C_abort
L_restore_input_exit:	; input stream restored, get out
dd M_exitcolon

CENTRY "concat" C_concat 6 ; ( 'cs1 'cs2 -- 'cs1+'cs2 ) concatenate counted string2 to counted-string1

; move the contents of cs2 to cs1+1+count1. cs2+1 cs1+c1+1 c2 cmove
dd C_2dup	; ( 'cs1 'cs2 'cs1 'cs2 )
dd M_dup	; ( 'cs1 'cs2 'cs1 'cs2 'cs2 )
dd M_cfetch	; ( 'cs1 'cs2 'cs1 'cs2 c2 )
dd M_rpush	; ( 'cs1 'cs2 'cs1 'cs2 ) (R c2 )
dd C_1plus	; ( 'cs1 'cs2 'cs1 'cs2+1 ) (R c2 )
dd M_over	; ( 'cs1 'cs2 'cs1 'cs2+1 'cs1 ) (R c2 )
dd M_dup	; ( 'cs1 'cs2 'cs1 'cs2+1 'cs1 'cs1 ) (R c2 )
dd M_cfetch	; ( 'cs1 'cs2 'cs1 'cs2+1 'cs1 c1 ) (R c2 )
dd M_plus	; ( 'cs1 'cs2 'cs1 'cs2+1 'cs1+c1 ) (R c2 )
dd C_1plus	; ( 'cs1 'cs2 'cs1 'cs2+1 'cs1+c1+1 ) (R c2 )
dd M_rpop	; ( 'cs1 'cs2 'cs1 'cs2+1 'cs1+c1+1 c2 ) (R )
dd M_cmove	; ( 'cs1 'cs2 'cs1 )

; update the count in cs1. c1 = c1+c2
dd M_cfetch	; ( 'cs1 'cs2 c1 )
dd M_xswap	; ( 'cs1 c1 'cs2 )
dd M_cfetch	; ( 'cs1 c1 c2 )
dd M_plus	; ( 'cs1 c1+c2 )
dd M_over	; ( 'cs1 c1+c2 'cs1 )
dd M_cstore	; ( 'cs1 )

dd M_exitcolon

; if (.) can return a counted string, this would be simpler
CENTRY "buffername" C_buffername 10 ; ( index -- 'counted_string ) build the buffer fd's filename
dd C_bufferfilename_fetch	; ( 'fcs ) fcs = filename counted string
dd M_literal
dd L_bin_prefix	; address of the counted string 3#n/
dd C_pad
dd M_literal
dd 4
dd M_cmove	; pad has 3#n/

dd C_pad	; ( 'fcs pad )
dd MV_Infd
dd M_fetch
dd C_counted_paren_dot_paren ; ( 'fcs pad 'cs )
dd C_concat	; Now, pad has 4#n/0 ( 'fcs pad )

dd M_xswap	; ( pad 'fcs )
dd C_concat	; Now, pad has a proper counted string
dd M_exitcolon

; max of a counted string is 256 bytes. Hence, cannot use it.
; reads into Tib and puts the read count on the stack. Could move the file reading into accept.
CENTRY "query" C_query 5 ; ( index -- read_count ) read from the indexed Fd in Bufferfds into Tib

L_query_again:
dd MV_Eof
dd C_off	; clear EOF flag

dd M_dup
dd C_cells	; ( index index*cellsize ) number of bytes
dd MV_Bufferfds
dd M_plus	; ( index index*cellsize+'Bufferfds ) address of the fd
dd M_fetch	; ( index fd )

dd M_dup	; ( index fd fd )
dd M_literal
dd -1
dd M_equal
dd M_cjump	; if fd == -1 ( index fd )
dd L_query	; when not -1

dd M_drop	; when fd == -1 ( index )
dd M_dup
dd M_dup
dd M_rpush	; ( index index ) (R index )
dd C_buffername
dd C_count	; ( index 'filename-counted-string -- 'text count ) (R index )
dd C_ro
dd C_open_file	; ( index fd ioresult ) (R index )
dd C_invert
dd M_cjump
dd L_query_opened	; if open suceeded, go here

dd M_drop	; ( index ) (R index ) returned false, could not open-file. write error message
dd M_literal
dd L_open_failed		; open error
dd C_count
dd C_type
dd C_dot	; show the index
dd C_cr
dd C_abort	; abort on open error. How about terminate?

L_query_opened:	; ( index fd ) (R index ) store the opened fd
dd M_dup	; ( index fd fd )
dd M_rpop	; ( index fd fd index )
dd C_cells	; ( index fd fd index*cellsize ) number of bytes
dd MV_Bufferfds
dd M_plus	; ( index fd fd index*cellsize+'Bufferfds ) address of the filename's counted string
dd M_store	; ( index fd )

L_query:		; ( index fd ) when fd != -1
dd MV_Tib
dd M_literal
dd 4096		; ( index fd Tib 4096 )
dd C_read_file ; ( index read_count ioresult )
dd M_cjump
dd L_query_read_failed

dd M_dup	; ( index read_count read_count )

dd M_cjump
dd L_query_read_0

dd M_dup	; read_count > 0 ( index read_count read_count )
dd M_literal
dd 4096
dd M_equal

dd M_cjump
dd L_query_read_successful

dd M_literal
dd L_query_too_long ; could not find a delimiter in 4096 bytes, reevaluate
dd C_count
dd C_type
dd C_dot	; show the read_count
dd C_cr
dd C_abort	; abort on read error. How about terminate?
dd M_exitcolon

L_query_read_failed:
dd M_literal
dd L_read_failed ; read error
dd C_count
dd C_type
dd C_dot	; show the index
dd C_cr
dd C_abort	; abort on read error. How about terminate without the fallback interpreter?
dd M_exitcolon

L_query_read_0:

dd M_drop	; ( index ) read_count == 0
dd M_rpush	; ( ) (R index ) save index for use after restoring input
dd MV_Eof
dd C_on		; end of file, qrestore_input
dd C_restore_input

dd M_rpop	; ( index ) (R )
dd M_jump	; ( index )
dd L_query_again

L_query_read_successful:
dd C_nip
dd M_exitcolon	; ( read_count ) successful read, get out

CENTRY "parse" C_parse 5 ; ( read_count -- 'Wordb ) Wordb has a counted string. read_count bytes read into Tib

dd M_dup	; ( read_count read_count ) check if count > 255 bytes, then invalid word
dd M_literal
dd 256
dd M_less
dd M_cjump
dd L_parse_1

dd M_dup	; ( read_count read_count )
dd MV_Wordb
dd M_cstore	; ( store read_count at Wordb[0] )
dd M_rpush
dd MV_Tib
dd MV_Wordb
dd M_literal
dd 1
dd M_plus	; ( 'Tib 'Wordb+1 ) (R read_count )
dd M_rpop	; ( 'Tib 'Wordb+1 read_count )
dd M_cmove	; copy bytes from Tib to Wordb to make it a counted string at Wordb

dd MV_Wordb
dd M_exitcolon	; ( 'Wordb ) Wordb has the counted string

L_parse_1:
dd M_literal
dd L_long_word
dd C_count
dd C_type
dd C_cr
dd C_abort
dd M_exitcolon

CENTRY "word" C_word 4 ; ( -- 'Wordb ) read from #n/Infd/word into Tib and then parse to a counted string in Wordb
dd MC_WORDNUM
dd C_query
dd C_parse
dd M_exitcolon

CENTRY "line" C_line 4 ; ( -- count ) read from #n/Infd/line into Tib
dd MC_LINENUM
dd C_query
dd M_exitcolon

CENTRY "doublequote" C_doublequote 11 ; ( -- count ) read from #n/Infd/doublequote into Tib
dd MC_DOUBLEQUOTENUM
dd C_query
dd M_literal
dd 1
dd M_minus	; to remove the trailing double quote character from the count
dd M_exitcolon

CENTRY "cdoublequote" C_counted_doublequote 12 ; ( -- 'Wordb ) read from #n/Infd/doublequote into Tib and then parse to a counted string in Wordb
dd C_doublequote
dd C_parse
dd M_exitcolon

CENTRY "closeparen" C_closeparen 10 ; ( -- count ) read from #n/Infd/closeparen
dd MC_CLOSEPARENNUM
dd C_query
dd M_exitcolon

CENTRY "findname" C_findname 8 ; ( a1 -- a2 f ) ; loop through the dictionary names
dd MV_Findadr
dd M_store
dd MV_Dtop
dd M_fetch	; get latest dictionary link

L_findname_loop:	( 'link )	address of link dictionary item
dd C_qdup
dd M_cjump
dd L_findname_not_found	; seached until the first dictionary entry, nil now. get out

dd M_dup	; ( 'link 'link )
dd C_cell_plus	; ( 'link 'len) lenth + initial name address
dd M_cfetch	; ( 'link immediate|hidden|len) length + initial name
dd M_literal
dd 64		; check the reveal'ed flag 1=hidden, 0=reveal
dd M_binand	; if hidden, goto L_findname_previous else L_findname_revealed
dd M_cjump
dd L_findname_revealed
dd M_jump	; smudge'd dictionary entry, get the previous entry
dd L_findname_previous

L_findname_revealed:		; reveal'ed dictionary entry
dd M_dup	; ( 'link 'link )
dd C_cell_plus	; ( 'link 'len )
dd C_count	; ( 'link 'name immediate|hidden|len )
dd M_literal
dd 63
dd M_binand	; ( 'link 'name (immediate|hidden|len)&63=len )
dd MV_Findadr
dd M_fetch	; ( 'link 'name (immediate|hidden|len)&63=len 'find ) 'find = counted string to find
dd C_count	; ( 'link 'name (immediate|hidden|len)&63=len 'find-name find-length )
dd C_compare	; ( 'link f ) compare dictionary entry with name
dd C_0eq	; found a match?
dd M_cjump
dd L_findname_previous	; not matched, try previous link
dd C_cell_plus	; match found
dd C_true
dd M_exitcolon

L_findname_previous:
dd M_fetch	; ( 'previous-link ) compare dictionary entry with name
dd M_jump
dd L_findname_loop	; ( 'previous-link ) looping to check it

L_findname_not_found:	; not found, getting out
dd MV_Findadr
dd M_fetch
dd C_false
dd M_exitcolon	( 'find false ) 'find = address of the name not found

CENTRY "find" C_find 4 ; ( a1 -- a2 f )?
dd C_findname
dd M_cjump
dd L_find_4
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
dd L_find_1
dd M_literal
dd 1
dd M_jump
dd L_find_2
L_find_1:
dd M_literal
dd -1
L_find_2:
dd M_exitcolon
dd M_jump
dd L_find_3
L_find_4:
dd C_false
L_find_3:
dd M_exitcolon

CENTRY "'" C_single_quote 1
dd C_word
dd C_find
dd C_0eq
dd M_cjump
dd L_single_quote_exit
dd C_space
dd C_count
dd C_type
dd M_literal
dd L170
dd C_count
dd C_type
dd C_cr
dd C_abort
L_single_quote_exit:
dd M_exitcolon

CENTRY "?stack" C_qstack 6
dd M_stackptr
dd MV_S0
dd M_greater
dd M_cjump
dd L_qstack_exit
dd M_literal
dd L_stack_underflow_message
dd C_count
dd C_type
dd C_cr
dd C_abort
L_qstack_exit:
dd M_exitcolon

dd MC_STDOUT	; ( str -- str 1) ; debug code to show the word found
dd M_over		; ( str 1 str )
dd C_count 		; ( str 1 a n)
dd M_syswrite
dd M_drop		; drop the return value of write

CENTRY "interpret" C_interpret 9 ; ( 'Wordb -- ) there is a counted string in the Wordb

dd C_find	; ( 'Wordb -- a1 f )
dd M_cjump
dd L_interpret_not_found

dd M_execute	; found in dictionary, execute
dd C_qstack		; check stack status
dd M_exitcolon

L_interpret_not_found:	; ( 'Wordb ) not found in the dictionary, check for number?
dd C_count
dd C_number ; ( a n1 -- n2 -1 | a n1 0 )
dd C_0eq
dd M_cjump
dd L_interpret_exit
dd C_space	; the word is neither in the dictionary nor a number
dd C_type	; show the word
dd M_literal
dd L_unknown_interpret_input	; error I?
dd C_count
dd C_type
dd C_cr
dd C_abort

L_interpret_exit:		; is a number
dd M_exitcolon

CENTRY "create" C_create 6	; compiles dictionary header until the pfa (link, len, name, cfa)
dd C_align	; sets Dp = aligned here
dd C_here	; ( -- here )
dd M_rpush	; ( -- ) (R -- linkaddr )
dd MV_Dtop	; ( -- Dtop ) (R -- linkaddr )
dd M_fetch	; ( Dtop -- dtop ) (R -- linkaddr )
dd C_comma	; ( dtop -- ) (R -- linkaddr )
dd C_word	; get the word from the input stream ( -- 'counted-string ) in Wordb
dd M_dup	; ( a -- a a ) (R -- linkaddr )
dd M_cfetch	; ( a a -- a len ) (R -- linkaddr )
dd C_here	; ( a len -- a len here ) (R -- linkaddr )
dd M_xswap	; ( a len here -- a here len ) (R -- linkaddr )
dd C_1plus	; ( a here len -- a here len+1 ) (R -- linkaddr ) using len+1 to copy even the length byte
dd M_dup	; ( a here len+1 -- a here len+1 len+1 ) (R -- linkaddr )
dd M_rpush	; ( a here len+1 len+1 -- a here len+1 ) (R -- linkaddr len+1 )
dd M_cmove	; ( a here len+1 -- ) (R -- linkaddr len+1 )
dd M_rpop	; ( -- len+1 ) (R -- linkaddr )
dd C_allot	; ( -- ) (R -- linkaddr ) here = here+len+1
dd C_align	; sets Dp = aligned here
dd M_literal
dd M_variable
dd M_fetch	; ( -- variablecfa) (R -- linkaddr )
dd C_comma	; ( -- ) put the variablecfa into the cfa
dd M_rpop	; ( -- linkaddr) (R -- )
dd MV_Dtop
dd M_store	; Dtop = just created link address
dd M_exitcolon

CENTRY "variable" C_variable 8	; compile to put the there then on the stack
dd C_create
dd C_there
dd C_comma	; put the next available variable location in pfa

dd M_literal
dd 1
dd C_cells
dd C_vallot	; there = there+8, stored at Vp
dd M_exitcolon

CENTRY "constant" C_constant 8 ; ( n -- ) do the same as variable but change the cfa to (constant)
dd C_create	; create dictionary header upto the cfa
dd M_literal
dd M_constant
dd M_fetch	; ( Contstantcfa -- (constant) )
dd C_here	; ( (constant) -- (constant) here )
dd M_literal
dd 1
dd C_cells	; ( (constant) here -- (constant) here 8 )
dd M_minus	; ( (constant) here 8 -- (constant) here-8 )
dd M_store	; ( (constant) here-8 -- ) changed cfa from (variable) to (constant) 
dd C_comma	; store n into the dictionary
dd M_exitcolon

CENTRY "immediate" C_immediate 9 ; set immediate flag on the latest defined dictionary entry
dd MV_Dtop
dd M_fetch
dd C_cell_plus
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
dd L_compile_not_found	; not found in the dictionary

dd M_dup	; found in the dictionary
dd M_cfetch	; get the immediate|hidden|len byte
dd M_literal
dd 128
dd M_binand
dd M_cjump
dd L_compile_1	; not immediate
dd C_tocfa	; immediate
dd M_execute
dd C_qstack
dd M_jump
dd L_compile_done

L_compile_1:	; not immediate
dd C_tocfa	; store cfa into the dictionary
dd C_comma

L_compile_done:
dd M_jump
dd L_compile_exit

L_compile_not_found:
dd C_count
dd C_number	; ( a n1 -- n2 -1 | a n1 0 )
dd C_0eq
dd M_cjump
dd L_compile_parsed_number
dd C_space
dd C_type
dd M_literal
dd L_unknown_compile_input
dd C_count
dd C_type
dd C_cr
dd C_abort
dd M_jump
dd L_compile_exit

L_compile_parsed_number:
dd M_literal
dd M_literal
dd C_comma
dd C_comma

L_compile_exit:
dd M_exitcolon

CENTRY "]" C_close_bracket 1
dd MV_State
dd C_on
L_close_bracket:
dd C_word
dd M_dup
dd M_cfetch
dd C_0eq
dd M_cjump
dd L_close_bracket_1
dd M_drop
dd C_word
dd M_jump
dd L_close_bracket_2
L_close_bracket_1:
dd C_compile
dd MV_State
dd M_fetch
L_close_bracket_2:
dd M_cjump
dd L_close_bracket_3
dd M_jump
dd L_close_bracket
L_close_bracket_3:
dd M_exitcolon

CIENTRY "[" CI_open_bracket 1
dd MV_State
dd C_off
dd M_exitcolon

CENTRY "smudge" C_smudge 6
dd MV_Dtop
dd M_fetch
dd C_cell_plus
dd M_dup
dd M_cfetch
dd M_literal
dd 64
dd M_binor
dd M_xswap
dd M_cstore
dd M_exitcolon

CENTRY "reveal" C_reveal 6
dd MV_Dtop
dd M_fetch
dd C_cell_plus
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
dd C_create	; create a dictionary header with (variable) at cfa
dd C_smudge
dd M_literal
dd M_colon
dd M_fetch	; ( Coloncfa -- (colon) ) fetches the cfa of M_colon
dd C_here	; ( (colon) -- (colon) here )
dd M_literal
dd 1
dd C_cells
dd M_minus	; ( (colon) here -- (colon) here-8 )
dd M_store	; ( (colon) here-8 -- ) change the cfa from (variable) to colon
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
dd MV_Dtop
dd M_fetch
dd C_cell_plus
dd C_tocfa
dd C_comma
dd M_exitcolon

CENTRY "char" C_char 4	; ( -- c ) fetch the first character of the next word from input
dd C_word	; ( -- a ) puts the address of the counted string from the input on the stack
dd C_1plus	; skip the count
dd M_cfetch	; fetch the first character
dd M_exitcolon

CENTRY "literal" C_literal 7	; ( n -- ) adds (literal) n to the dictionary
dd M_literal
dd M_literal
dd C_comma
dd C_comma
dd M_exitcolon

CENTRY "sliteral" C_sliteral 8	; ( -- ) adds (sliteral) a n to the dictionary
dd M_literal
dd M_sliteral
dd C_comma	; adds (sliteral) to the dictionary
dd C_here	; ( here )

dd C_counted_doublequote	; ( here 'Wordb ) Wordb has the counted string
dd M_dup	; ( here 'Wordb 'Wordb )
dd M_cfetch	; ( here 'Wordb count )
dd C_1plus	; ( here 'Wordb count+1 )
dd M_rpush	; ( here 'Wordb ) (R count+1 )
dd M_xswap	; ( 'Wordb here ) (R count+1 )
dd M_rfetch	; ( 'Wordb here count+1 ) (R count+1 )
dd M_cmove	; ( ) (R count+1 )
dd M_rpop
dd C_allot	; here = here+count+1
dd C_align	; align here
dd M_exitcolon

CENTRY "string" C_string 6 ; ( -- ) store the following word as a counted string onto the dictionary
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

CIENTRY "[char]" CI_char_brackets 6	; take the next character from the input stream during compilation
dd C_word	; assuming that the character is a 1-byte word
dd C_1plus
dd M_cfetch
dd C_literal
dd M_exitcolon

CIENTRY "[']" CI_quote_brackets 3 ; take the address of next token from the input stream during compilation
dd C_single_quote
dd C_literal
dd M_exitcolon

CIENTRY "(" CI_openparen 1	; ignore until ) from the input stream during compilation
dd C_closeparen
dd M_drop
dd M_exitcolon

CIENTRY "\\" CI_backslash 1 ; if the line is longer than 4096, C_query throws an error
dd C_line
dd M_drop
dd M_exitcolon

CENTRY "(?abort)" C_qabort_parens 8
dd MV_State
dd M_cjump
dd L_qabort_parens
dd C_space
dd C_type
dd C_cr
dd C_abort
dd M_jump
dd L_qabort_parens_1
L_qabort_parens:
dd C_2drop
L_qabort_parens_1:
dd M_exitcolon

CIENTRY "abort\"" CI_abort_double_quote 6
dd C_sliteral
dd M_literal
dd C_qabort_parens
dd C_comma
dd M_exitcolon

; could make this work for strings longer than 256 bytes.
; But, for now, strings longer than 256 bytes are not supported by " or c" or s" or ."
; this does not store the count in the dictionary
CENTRY "\"" C_double_quote 1	; ( | .. " -- 'text count ) stores string in the dictionary and also leaves the address and count of the string on the stack - to use strings at the interpreter prompt
dd C_counted_doublequote	; ( 'Wordb )
dd C_count			; ( 'Wordb+1 count )
dd M_rpush			; ( 'Wordb+1 ) (R count )
dd C_here			; ( 'Wordb+1 here ) (R count )
dd M_rfetch			; ( 'Wordb+1 here count ) (R count )
dd M_cmove

dd C_here	; ( here )
dd M_rpop	; ( here count )
dd M_dup	; ( here count count )
dd C_allot	; ( here count ) here = here+count
dd M_exitcolon

CENTRY "c\"" C_counted_double_quote 2	; ( | ..." -- 'counted-string ) stores counted string in the dictionary. For use in interpretive mode.
dd C_counted_doublequote	; ( 'Wordb )
dd M_dup			; ( 'Wordb 'Wordb )
dd M_cfetch			; ( 'Wordb count )
dd C_1plus			; ( 'Wordb count+1 )
dd M_rpush			; ( 'Wordb ) (R count+1 )
dd C_here			; ( 'Wordb here ) (R count+1 )
dd M_rfetch			; ( 'Wordb here count ) (R count+1 )
dd M_cmove

dd C_here	; ( here )
dd M_rpop	; ( here count+1 )
dd C_allot	; ( here ) here = here+count+1
dd M_exitcolon

; for compiling counted strings into the definition. Puts the ( 'text count ) on the stack at run time
CIENTRY "s\"" CI_sdouble_quote 2	; ( | ..." -- 'text count ) add the string from the input stream to the dictionary as (sliteral) count string - at run-time puts the ( -- addr n) of the counted string on the stack.
dd C_sliteral
dd M_exitcolon

CIENTRY ".\"" CI_dotstr 2	; ( | ..." -- ) ." = s" type
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
dd M_doinit		; compile this into the definition. Puts limit and index on the run stack at run time
dd C_comma		; puts (do) into the dictionary
dd M_literal
dd 0			; ( -- 0 )
dd C_here		; ( 0 -- 0 here1 )
dd M_exitcolon
CIENTRY "loop" CI_loop 4	; ( 0 here1 -- )
dd M_literal
dd M_doloop		; ( 0 here1 -- 0 here1 (loop) )
dd C_comma		; dictionary has (do) ... (loop) ( 0 here1 (loop) -- 0 here1 )
dd C_comma		; dictionary has (do) ... (loop) here1 ( 0 here1 -- 0 )
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
CENTRY "r/o" C_ro 3
dd M_literal
dd 0
dd M_exitcolon
CENTRY "w/o" C_wo 3
dd M_literal
dd 1
dd M_exitcolon
CENTRY "r/w" C_rw 3
dd M_literal
dd 2
dd M_exitcolon

CENTRY "cstring" C_cstring 7 ; ( 'text count o -- o+'pad+1024 ) \ copy string to pad+o and add a null byte at the end
dd C_pad	; ( 'text count o 'pad )
dd M_literal
dd 1024		; ( 'text count o 'pad 1024 )
dd M_plus	; ( 'text count o 'pad+1024 )
dd M_plus	; ( 'text count o+'pad+1024 ) o=padoffset
dd M_dup
dd M_rpush	; ( 'text count o+'pad+1024 ) (R o+'pad+1024 )
dd M_xswap	; ( 'text o+'pad+1024 count ) (R o+'pad+1024 )
dd M_dup	; ( 'text o+'pad+1024 count count ) (R o+'pad+1024 )
dd M_rpush	; ( 'text o+'pad+1024 count ) (R o+'pad+1024  count )
dd M_cmove	; moves the filename from 'text to o+'pad+1024
dd M_literal
dd 0		; ( 0 ) (R o+'pad+1024  count )
dd M_rpop	; ( 0 count ) (R o+'pad+1024 )
dd M_rfetch	; ( 0 count o+'pad+1024 ) (R o+'pad+1024 )
dd M_plus	; ( 0 count+o+'pad+1024 ) (R o+'pad+1024 )
dd M_cstore	; makes the filename to a null terminated string
dd M_rpop ;  ( o+'pad+1024 )
dd M_exitcolon

CENTRY "cstring0" C_cstring0 8 ; ( 'text count -- 'text ) \ copy string to pad+1024 and add a null byte at the end
dd M_literal
dd 0
dd C_cstring
dd M_exitcolon

CENTRY "cstring1" C_cstring1 8 ; ( 'text count -- 'text ) \ copy string to pad+1536 and add a null byte at the end
dd M_literal
dd 512
dd C_cstring
dd M_exitcolon

CENTRY "open-file" C_open_file 9 ; ( 'text count mode -- fd ioresult )
dd M_rpush	; ( 'text count ) (R mode)
dd C_cstring0 ; ( 'padtext ) (R mode )
dd M_rpop	; ( 'padtext mode ) (R )
dd M_sysopen
dd M_dup
dd M_literal
dd -1
dd M_greater
dd M_exitcolon

CENTRY "close-file" C_close_file 10	; ( fd -- ioresult )
dd M_sysclose
dd C_0eq
dd M_exitcolon

CENTRY "read-file" C_read_file 9	; ( fd 'text count -- count2 ioresult )
dd M_sysread
dd M_dup
dd M_literal
dd -1
dd C_neq
dd M_exitcolon

CENTRY "write-file" C_write_file 10	; ( fd 'text count -- ioresult )
dd M_syswrite
dd M_literal
dd -1
dd C_neq
dd M_exitcolon

CENTRY "reposition-file" C_reposition_file 15	;	( fd n type -- ioresult )
dd M_sysseek
dd M_literal
dd -1
dd C_neq
dd M_exitcolon

CENTRY "?fcheck" C_qfcheck 7
dd C_0eq
dd M_cjump
dd L_qfcheck_exit
dd C_space
dd M_literal
dd L_io_error
dd C_count
dd C_type
dd C_cr
dd C_abort
L_qfcheck_exit:
dd M_exitcolon

CENTRY "create-file" C_create_file 11 ; ( a n mode perm -- fd ioresult ) not part of the original ff. could move this to a forth file.
dd M_rpush	; ( a n mode ) (R perm)
dd M_rpush	; ( a n ) (R perm mode)
dd C_pad	; ( a n padaddr)
dd M_literal
dd 1024		; ( a n padaddr 1024 )
dd M_plus	; ( a n padaddr+1024 )
dd M_xswap	; ( a padaddr+1024 n )
dd M_dup	; ( a padaddr+1024 n n )
dd M_rpush	; ( a padaddr+1024 n ) (R perm mode n )
dd M_cmove	; moves the filename from a to paddaddr+1024
dd M_literal
dd 0		; ( 0 )
dd M_rpop	; ( 0 n ) (R perm mode)
dd C_pad	; ( 0 n padaddr)
dd M_plus	; ( 0 padaddr+n )
dd M_literal
dd 1024		; ( 0 padaddr+n 1024 )
dd M_plus	; ( 0 padaddr+n+1024 )
dd M_cstore	; ( ) makes the filename to a null terminated string
dd C_pad
dd M_literal
dd 1024		; ( padaddr 1024 )
dd M_plus	; ( padaddr+1024 )
dd M_rpop	; ( padaddr+1024 mode) (R perm )
dd M_rpop	; ( padaddr+1024 mode perm ) (R )
dd M_syscreate
dd M_dup
dd M_literal
dd -1
dd M_greater
dd M_exitcolon

CENTRY "bye" C_bye 3
dd M_literal
dd 0
dd M_terminate
dd M_exitcolon

CENTRY "include" C_include 7	; this does not work
dd C_word

dd M_rpush

dd C_input_fetch	; save the old input onto the stack and clears the input bufferfds

dd M_rpop
dd C_count
dd C_ro
dd C_open_file

dd C_qfcheck

dd MV_Infd		; open the new file
dd M_store
dd M_exitcolon

CENTRY "crash" C_crash 5
dd M_literal
dd L251
dd C_count
dd C_type
dd C_cr
dd C_abort
dd M_exitcolon

CENTRY "quit" C_quit 4 ; interpreter loop
dd M_reset ; initialize return stack
dd M_clear	; SP = sstack_end initialize data stack

L_quit_interpreter_loop:
dd C_word
dd C_interpret
dd M_jump
dd L_quit_interpreter_loop
dd M_exitcolon	; why is this needed?

CENTRY "(abort)" C_parenabort 7 ; TODO correct below stack notations
dd MV_State	; ( mv_State -- )
dd C_off	; off sets variable state = 0

dd MC_STDIN
dd MV_Infd
dd M_store
dd MC_STDOUT
dd MV_Outfd
dd M_store
dd MC_STDERR
dd MV_Errfd
dd M_store

dd C_stdinput
dd C_quit	; quit resets stacks and is the interpreter loop
dd M_exitcolon	; why is this needed? quit does not return unless it breaks


dd M_literal	; test code
dd 66
dd MV_Wordb
dd M_store
dd MC_STDOUT
dd MV_Wordb
dd M_literal
dd 1
dd M_syswrite
dd M_drop		; drop the return value of write
dd MC_STDIN
dd MV_Wordb
dd M_literal
dd 1
dd M_sysread
dd M_drop		; drop the return value of read

CENTRY "initialize" C_initialize 10	; initialize buffer file names and buffer fds, why not hard code this?
dd MV_Bufferfds
dd MC_NBUFFERS
dd M_literal
dd 0
dd M_doinit
L_initialize_fd_loop:

dd M_dup
dd M_literal
dd -1
dd M_xswap
dd M_store

dd M_literal
dd 1
dd C_cells
dd M_plus

dd M_doloop
dd L_initialize_fd_loop
dd M_drop

dd MV_Bufferfilenames
dd MC_NBUFFERS
dd M_literal
dd 0
dd M_doinit
L_initialize_filename_loop:

dd M_dup
dd M_literal
dd 0
dd M_xswap
dd M_store

dd M_literal
dd 1
dd C_cells
dd M_plus

dd M_doloop
dd L_initialize_filename_loop
dd M_drop

dd M_literal
dd L_line_filename
dd C_wordfilename_store

dd M_literal
dd L_word_filename
dd C_linefilename_store

dd M_literal
dd L_doublequote_filename
dd C_doublequotefilename_store

dd M_literal
dd L_closeparen_filename
dd C_closeparenfilename_store
dd M_exitcolon

CENTRY "debug" C_debug 5 ; ( n -- ) show the n along with the debug message and depth
dd M_literal
dd L_debug_msg
dd C_count
dd C_type

dd C_dot
dd C_space

dd C_depth
dd C_dot
dd C_cr
dd M_exitcolon

CENTRY "boot" C_boot 4
dd M_reset ; initialize return stack
dd M_clear	; SP = sstack_end initialize data stack

dd M_literal
dd C_parenabort ; ( (abort) -- )
dd MV_Abortvec	; variable that puts (abort) code address on the stack
dd M_store	; variable abortvec = (abort) code address

dd MC_STDIN
dd MV_Infd	; might be overwritten by args below
dd M_store	; stdin = 0
dd MC_STDOUT
dd MV_Outfd
dd M_store
dd MC_STDERR
dd MV_Errfd
dd M_store

dd MV_State
dd C_off	; off stores 0 at state
dd C_decimal	; decimal sets base = 10

dd C_initialize	; sets up the buffer filenames and buffer fd's

dd C_args	; process args

dd C_quit	; interpreter loop when there are no args or fall through after processing args
dd M_exitcolon

; putting the strings at the bottom to not mess with cell alignment above
L_bin_prefix:
db "#n/"
L_line_filename:
db "/word"
L_word_filename:
db "/line"
L_doublequote_filename:
db "/doublequote"
L_closeparen_filename:
db "/closeparen"

L_restore_input_error_message:
db "unable to restore input from the stack, aborting.." ; comments for testing the awk parser
L_open_failed:
db "open file failed"
L_read_failed:
db "read file failed"
L170:
db " Q?"
L_stack_underflow_message:
db " stack underflow"
L_unknown_interpret_input:
db " I?"
L_unknown_compile_input:
db " C?"
L_io_error:
db "I/O error"
L251:
db "uninitialized execution vector"
L255:
db " ok"
L_query_too_long:
db "input is longer than 4096 bytes without a delimiter"
L305:
db "read error"
L_long_word:
db "word is too long to be interpreted"
L_debug_msg:
db "debug message "
