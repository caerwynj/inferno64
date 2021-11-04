#include "os.h"
#include "../include/mp.h"
#include "libsec.h"

mpint*
rsaencrypt(RSApub *rsa, mpint *in, mpint *out)
{
	if(out == nil)
		out = mpnew(0);
	mpexp(in, rsa->ek, rsa->n, out);
	return out;
}
