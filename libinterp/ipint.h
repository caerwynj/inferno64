typedef struct IPint IPint;

#pragma incomplete IPint

//Keyring_IPint*	newIPint(mpint*);
void*	newIPint(mpint*);
//mpint*	checkIPint(Keyring_IPint*);
mpint*	checkIPint(void*);
void	freeIPint(Heap*, int);
void	ipintsmodinit(void);
void	ipinttostr(void *ip, int base, char *buf, int buflen);

extern	Type*	TIPint;
extern	void	mpand(mpint *b1, mpint *b2, mpint *sum);
extern	void	mpor(mpint *b1, mpint *b2, mpint *sum);
extern	void	mpnot(mpint *b, mpint *r);
extern	void	mpxor(mpint *b1, mpint *b2, mpint *sum);

