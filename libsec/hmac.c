#include "os.h"
#include <libsec.h>

/* rfc2104 */
static DigestState*
hmac_x(uchar *p, ulong len, uchar *key, ulong klen, uchar *digest, DigestState *s,
	DigestState*(*x)(uchar*, ulong, uchar*, DigestState*), int xlen, int blksz)
{
	int i;
	uchar pad[129], innerdigest[256];

	if(xlen > sizeof(innerdigest))
		return nil;
	if(blksz > sizeof(pad)-1)
		return nil;

	if(klen > blksz){
		(*x)(key, klen, innerdigest, nil);
		key = innerdigest;
		klen = xlen;
	}

	/* first time through */
	if(s == nil || s->seeded == 0){
		memset(pad, 0x36, blksz);
		pad[blksz] = 0;
		for(i=0; i<klen; i++)
			pad[i] ^= key[i];
		s = (*x)(pad, blksz, nil, s);
		if(s == nil)
			return nil;
	}

	s = (*x)(p, len, nil, s);
	if(digest == nil)
		return s;

	/* last time through */
	memset(pad, 0x5c, blksz);
	pad[blksz] = 0;
	for(i=0; i<klen; i++)
		pad[i] ^= key[i];
	(*x)(nil, 0, innerdigest, s);
	s = (*x)(pad, blksz, nil, nil);
	(*x)(innerdigest, xlen, digest, s);
	return nil;
}

DigestState*
hmac_sha1(uchar *p, ulong len, uchar *key, ulong klen, uchar *digest, DigestState *s)
{
	return hmac_x(p, len, key, klen, digest, s, sha1, SHA1dlen, 64);
}

DigestState*
hmac_md5(uchar *p, ulong len, uchar *key, ulong klen, uchar *digest, DigestState *s)
{
	return hmac_x(p, len, key, klen, digest, s, md5, MD5dlen, 64);
}

DigestState*
hmac_sha2_224(uchar *p, ulong len, uchar *key, ulong klen, uchar *digest, DigestState *s)
{
	return hmac_x(p, len, key, klen, digest, s, sha224, SHA224dlen, 64);
}

DigestState*
hmac_sha2_256(uchar *p, ulong len, uchar *key, ulong klen, uchar *digest, DigestState *s)
{
	return hmac_x(p, len, key, klen, digest, s, sha256, SHA256dlen, 64);
}

DigestState*
hmac_sha2_384(uchar *p, ulong len, uchar *key, ulong klen, uchar *digest, DigestState *s)
{
	return hmac_x(p, len, key, klen, digest, s, sha384, SHA384dlen, 128);
}

DigestState*
hmac_sha2_512(uchar *p, ulong len, uchar *key, ulong klen, uchar *digest, DigestState *s)
{
	return hmac_x(p, len, key, klen, digest, s, sha512, SHA512dlen, 128);
}
