dict:
  MENTRY "@", fetch, 1
  MENTRY "!", store, 1
  MENTRY "c@", cfetch, 2
  MENTRY "c!", cstore, 2
  MENTRY "read", fthread, 4
  MENTRY "write", fthwrite, 5
  MENTRY "seek", fthseek, 4
  MENTRY "open", fthopen, 4
  MENTRY "close", fthclose, 5
  MENTRY "mmap", mmap, 4
  MENTRY "halt", terminate, 4
  MENTRY "clear", clear, 5
  MENTRY "reset", reset, 5
  MENTRY "exitcolon", exitcolon, 4
  MENTRY "(literal)", literal, 9
  MENTRY "(sliteral)", sliteral, 10
  MENTRY "(do)", doinit, 4
  MENTRY "(loop)", doloop, 6
  MENTRY "(+loop)", doploop, 7
  MENTRY "r@", rfetch, 2
  MENTRY "r>", rpop, 2
  MENTRY ">r", rpush, 2
  MENTRY "i", i, 1
  MENTRY "j", j, 1
  MENTRY "+", plus, 1
  MENTRY "-", minus, 1
  MENTRY "*", multiply, 1
  MENTRY "(if)", cjump, 4
  MENTRY "(else)", jump, 6
  MENTRY "/mod", slashmod, 4
  MENTRY "u/mod", uslashmod, 5
  MENTRY "and", binand, 3
  MENTRY "or", binor, 2
  MENTRY "xor", binxor, 3
  MENTRY "swap", xswap, 4
  MENTRY "drop", drop, 4
  MENTRY "dup", dup, 3
  MENTRY "over", over, 4
  MENTRY "=", equal, 1
  MENTRY ">", greater, 1
  MENTRY "<", less, 1
  MENTRY "lshift", lshift, 6
  MENTRY "rshift", rshift, 6
  MENTRY "rshifta", rshifta, 7
  MENTRY "execute", execute, 7
  MENTRY "unloop", unloop, 6
  MENTRY "cmove", cmove, 5
  MENTRY "cmove>", cmoveb, 6

  MENTRY "Tib", Tib, 3			; variables from here, puts address on stack, mixed case
  MENTRY "Wordb", Wordb, 5
  MENTRY "Hzero", Hzero, 5
  MENTRY "Dp", Dp, 2
  MENTRY ">In", toIn, 3
  MENTRY ">Limit", toLimit, 6
  MENTRY "Findadr", Findadr, 7
  MENTRY "Blk", Blk, 3
  MENTRY "Args", Args, 4
  MENTRY "Iobuf", Iobuf, 5
  MENTRY "Searchlen", Searchlen, 9
  MENTRY "Base", Base, 4
  MENTRY ">Num", toNum, 4
  MENTRY "State", State, 5
  MENTRY "Abortvec", Abortvec, 8	; not sure if these 3 can be constants instead?
  MENTRY "Sourcebuf", Sourcebuf, 9
  MENTRY "Wordbuf", Wordbuf, 7
  MENTRY "Infd", Infd, 5
  MENTRY "Outfd", Outfd, 6
  MENTRY "Errfd", Errfd, 4
  MENTRY "Eof", Eof, 0, 3

  MCENTRY "STDIN", STDIN, 0, 5		; 3 constants from here, CAPITALS
  MCENTRY "STDOUT", STDOUT, 1, 6
  MCENTRY "STDERR", STDERR, 2, 6

  MENTRY "s0", s0, 2
  MENTRY "s@", stackptr, 2		; puts PSP on stack
  MENTRY "(variable)", variable, 10
  MENTRY "(constant)", constant, 10
  MENTRY "(:)", colon, 3
  MENTRY "(does)", dodoes, 6
  MENTRY "cas", cas, 3
  MENTRY "(deferred)", deferred, 10
