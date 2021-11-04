#include "os.h"
#include "../include/mp.h"
void secp256k1(mpint *p, mpint *a, mpint *b, mpint *x, mpint *y, mpint *n, mpint *h){
	strtomp("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F", nil, 16, p);
	mpassign(mpzero, a);
	uitomp(7UL, b);
	strtomp("79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798", nil, 16, x);
	strtomp("483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8", nil, 16, y);
	strtomp("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141", nil, 16, n);
	mpassign(mpone, h);
	}
