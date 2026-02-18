typedef struct{char *name; long sig; void (*fn)(void*); int size; int np; uchar map[16];} Runtab;
Runtab Sqlitemodtab[]={
	"bind_big",0xa7807b27,Sqlite_bind_big,88,2,{0x0,0x80,},
	"bind_int",0x92380fb6,Sqlite_bind_int,88,2,{0x0,0x80,},
	"bind_real",0x9055e80c,Sqlite_bind_real,88,2,{0x0,0x80,},
	"bind_text",0xb78cc57c,Sqlite_bind_text,88,2,{0x0,0xa0,},
	"close",0xaccabe82,Sqlite_close,72,2,{0x0,0x80,},
	"column_big",0x72d0f7c3,Sqlite_column_big,80,2,{0x0,0x80,},
	"column_blob",0x6ff75904,Sqlite_column_blob,80,2,{0x0,0x80,},
	"column_bytes",0xd67dfdfa,Sqlite_column_bytes,80,2,{0x0,0x80,},
	"column_int",0xd67dfdfa,Sqlite_column_int,80,2,{0x0,0x80,},
	"column_real",0x8ded8f64,Sqlite_column_real,80,2,{0x0,0x80,},
	"column_text",0xd99235cd,Sqlite_column_text,80,2,{0x0,0x80,},
	"finalize",0xaccabe82,Sqlite_finalize,72,2,{0x0,0x80,},
	"open",0xd362be2a,Sqlite_open,72,2,{0x0,0x80,},
	"prepare",0x7c6b9aea,Sqlite_prepare,80,2,{0x0,0xc0,},
	"step",0xaccabe82,Sqlite_step,72,2,{0x0,0x80,},
	0
};
#define Sqlitemodlen	15
