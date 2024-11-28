/*
 * Forth dictionary
 */
enum {
	Sourceline,
	Here,
	There,
	Byte,	/* obsolete, all are counted strings now */
	Chars,
	Absolute,
	Absoluteptr,
	Relative,		/* fmem+ value, for defined memory locations */
	Relativevar,	/* fmem+FORTHVARS+ value */
	Relativedictionary,	/* fmem+DICTIONARY+ value */
	Dtop,
	End
};

typedef struct Fentry Fentry;
struct Fentry
{
	int what;	/* Source line or Here or There or Dtop value */
	char desc[1024];
	int type;	/* Byte, Chars, Absolute, Relative, End */
	intptr here;
	intptr there;
	/* union { */
		intptr p;	/* for Absolute and Relative */
		s8 b;		/* for immediates, write the value as immediate + length */
		char str[128];
		void *ptr;
	/* }; */
};
