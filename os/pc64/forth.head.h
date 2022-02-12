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
	Byte,	/* obsolete, all are counted strings now */
	Chars,
	Here,
	There,
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
		s8 b;
		char str[128];
	};
	char src[128];
};
