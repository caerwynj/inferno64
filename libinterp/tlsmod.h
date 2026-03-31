typedef struct{char *name; long sig; void (*fn)(void*); int size; int np; uchar map[16];} Runtab;
Runtab Tlsmodtab[]={
	"tlsclient",0xfdab145e,Tls_tlsclient,80,2,{0x0,0xc0,},
	"tlsserver",0x178a2576,Tls_tlsserver,72,2,{0x0,0x80,},
	0
};
#define Tlsmodlen	2
