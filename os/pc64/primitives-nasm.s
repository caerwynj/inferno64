MENTRY "@" fetch 1
MENTRY "!" store 1
MENTRY "c@" cfetch 2
MENTRY "c!" cstore 2
MENTRY "mmap" mmap 4
MENTRY "halt" terminate 4
MENTRY "dump" fthdump 4
MENTRY "clear" clear 5
MENTRY "reset" reset 5
MENTRY "exit" exitcolon 4
MENTRY "(literal)" literal 9
MENTRY "(sliteral)" sliteral 10
MENTRY "(do)" doinit 4
MENTRY "(loop)" doloop 6
MENTRY "(+loop)" doploop 7
MENTRY "r@" rfetch 2
MENTRY "r>" rpop 2
MENTRY ">r" rpush 2
MENTRY "i" i 1
MENTRY "j" j 1
MENTRY "+" plus 1
MENTRY "-" minus 1
MENTRY "*" multiply 1
MENTRY "(if)" cjump 4
MENTRY "(else)" jump 6
MENTRY "/mod" slashmod 4
MENTRY "u/mod" uslashmod 5
MENTRY "and" binand 3
MENTRY "or" binor 2
MENTRY "xor" binxor 3
MENTRY "swap" xswap 4
MENTRY "drop" drop 4
MENTRY "dup" dup 3
MENTRY "over" over 4
MENTRY "=" equal 1
MENTRY ">" greater 1
MENTRY "<" less 1
MENTRY "lshift" lshift 6
MENTRY "rshift" rshift 6
MENTRY "rshifta" rshifta 7
MENTRY "execute" execute 7
MENTRY "unloop" unloop 6
MENTRY "cmove" cmove 5
MENTRY "cmove>" cmoveb 6
MENTRY "(variable)" variable 10
MENTRY "(constant)" constant 10
MENTRY "(:)" colon 3
MENTRY "(does)" dodoes 6
MENTRY "cas" cas 3
MENTRY "(deferred)" deferred 10
MENTRY "s@" stackptr 2	; puts PSP on stack. Not a variable hence lower case.

MENTRY "sysbind" sysbind 7
MENTRY "sysclose" sysclose 8
MENTRY "syscreate" syscreate 9
MENTRY "sysmount" sysmount 8
MENTRY "sysopen" sysopen 7
MENTRY "sysread" sysread 7
MENTRY "sysseek" sysseek 7
MENTRY "syswrite" syswrite 8

MCENTRY "STDIN" STDIN 5	0 ; 3 constants from here CAPITALS
MCENTRY "STDOUT" STDOUT 6 1
MCENTRY "STDERR" STDERR 6 2

MCENTRY	"WORD#" WORDNUM 5 0
MCENTRY	"LINE#" LINENUM 5 1
MCENTRY	"DOUBLEQUOTE#" DOUBLEQUOTENUM 12 2
MCENTRY	"CLOSEPAREN#" CLOSEPARENNUM 11 3
MCENTRY "#BUFFERS" NBUFFERS 8 16

; put address of the defined location on the top of stack
; cannot use H as it is nil in inferno, address where here (next available dictionary cell location) is stored
; here = Dp @
; these memory locations (HERE, DTOP, etc.) are populated with values by the forth initializer
MVDENTRY "Dp" Dp 2 HERE		; here
MVDENTRY "Dtop" Dtop 4 DTOP	; last defined header
MVDENTRY "Vp" Vp 2 THERE	; here of the variables space
MVDENTRY "Pid" Pid 3 FTHPID
MVDENTRY "Parentpid" Parentpid 4 FTHPARENTPID
; the below memory locations are left alone as zeros by the initializer
MVDENTRY "S0" S0 2 PSTACK
MVDENTRY "Wordb" Wordb 5 WORDB
MVDENTRY "Tib" Tib 3 TIB
MVDENTRY "Argsfilename" Argsfilename 12 ARGSFILENAME ; counted string populated by forth starter from params

MVENTRY "Iobuf" Iobuf 5		; the values are not being used from the definition. All are initialized to 0.
MVENTRY "Sourcebuf" Sourcebuf 9	; is there a need for this?
MVENTRY "Wordbuf" Wordbuf 7		; is there a need for this?
MVENTRY ">In" toIn 3
MVENTRY ">Limit" toLimit 6
MVENTRY "Findadr" Findadr 7
MVENTRY "Acceptvec" Acceptvec 9
MVENTRY "Searchlen" Searchlen 9
MVENTRY "Base" Base 4
MVENTRY ">Num" toNum 4
MVENTRY "State" State 5
MVENTRY "Abortvec" Abortvec 8	; not sure if these 3 can be constants instead?
MVENTRY "Infd" Infd 4
MVENTRY "Outfd" Outfd 5
MVENTRY "Errfd" Errfd 5
MVENTRY "Eof" Eof 3
MVENTRY "Ninputs" Ninputs 7
MVENTRY "H0" H0 2		; here at startup

MVENTRY "Bufferfds" Bufferfds 9 16
MVENTRY "Bufferfilenames" Bufferfilenames 15 16 ; counted string labels of the searchers populated by boot

