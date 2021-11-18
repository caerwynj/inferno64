dict:
  MENTRY "@", fetch, 1
  MENTRY "!", store, 1
  MENTRY "c@", cfetch, 2
  MENTRY "c!", cstore, 2
  MENTRY "testfsopen", testfsopen, 10
  MENTRY "errstr", errstr, 6
  MENTRY "read", read, 4
  MENTRY "write", write, 5
  MENTRY "seek", seek, 4
  MENTRY "open", open, 4
  MENTRY "close", close, 5
  MENTRY "mmap", mmap, 4
  MENTRY "halt", terminate, 4
  MENTRY "clear", clear, 5
  MENTRY "reset", reset, 5
  MVENTRY "h", h, htop, 1
  MVENTRY "dp", dp, dtop, 2
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
  MVENTRY "tib", tib, tibuffer, 3
  MVENTRY "wordb", wordb, wordbuffer, 5
  MENTRY "s@", stackptr, 2
  MENTRY "lshift", lshift, 6
  MENTRY "rshift", rshift, 6
  MENTRY "rshifta", rshifta, 7
  MENTRY "execute", execute, 7
  MENTRY "unloop", unloop, 6
  MENTRY "cmove", cmove, 5
  MENTRY "cmove>", cmoveb, 6
  MENTRY "(variable)", variable, 10
  MENTRY "(constant)", constant, 10
  MENTRY "(:)", colon, 3
  MENTRY "(does)", dodoes, 6
  MVENTRY "heaptop", heaptop, heapend, 7
  MVENTRY "_start", textbase, ffmain, 6
  MVENTRY "_end", textend, ffend, 4
  MENTRY "cas", cas, 3
  MENTRY "(deferred)", deferred, 10
