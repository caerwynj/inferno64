/*
 * Forth dictionary
 */
#define WORDB		(BY2WD*144)	/* word buffer */
#define TIB			(7*BY2PG)	/* text input buffer */
enum {
	Header,
	IHeader,	/* Immediate dictionary definition */
	Absolute,
	FromH0,
	Chars,
};

typedef struct Hdr Hdr;
		struct Hdr {
			int len;
			char *name;
			void *cfa;
		};
typedef struct Fentry Fentry;
struct Fentry
{
	int type;
	union {
		Hdr hdr;
		intptr p;
		char *str;
	};
};
