/*
 * TLS 1.3 handshake (RFC 8446) for Inferno.
 *
 * Uses inferno kernel file ops kopen/kread/kwrite/kclose so it can be called
 * from within the emu and talk to /dev/tls.
 *
 * Supported cipher suites (mandatory TLS 1.3 set):
 *   TLS_AES_128_GCM_SHA256        0x1301
 *   TLS_AES_256_GCM_SHA384        0x1302
 *   TLS_CHACHA20_POLY1305_SHA256  0x1303
 *
 * Key exchange: X25519 only.
 *
 * Server certificate signature verification is skeletal; full PKI requires
 * wiring in RSA-PSS or ECDSA which can be added incrementally.
 */

#include "os.h"
#include <mp.h>
#include <libsec.h>

/* kernel I/O – linked from emu; s32 in fns.h mapped to int here */
extern int kopen(char*, int);
extern int kclose(int);
extern int kread(int, void*, int);
extern int kwrite(int, void*, int);

enum {
	TLS13Version	= 0x0304,
	TLS12Legacy	= 0x0303,

	/* record content types */
	RChangeCipher	= 20,
	RAlert		= 21,
	RHandshake	= 22,
	RAppData	= 23,

	/* handshake message types */
	HClientHello		= 1,
	HServerHello		= 2,
	HEncryptedExtensions	= 8,
	HCertificate		= 11,
	HCertificateVerify	= 15,
	HFinished		= 20,

	/* extensions */
	ExtSNI			= 0,
	ExtSupportedGroups	= 10,
	ExtSigAlgs		= 13,
	ExtSupportedVersions	= 43,
	ExtPSKKeyExchangeModes	= 45,
	ExtKeyShare		= 51,

	/* named groups */
	X25519group		= 0x001d,

	/* TLS 1.3 cipher suites */
	TLS_AES_128_GCM_SHA256		= 0x1301,
	TLS_AES_256_GCM_SHA384		= 0x1302,
	TLS_CHACHA20_POLY1305_SHA256	= 0x1303,

	/* RFC 5746: renegotiation SCSV — servers with secure-renegotiation require this */
	TLS_EMPTY_RENEGOTIATION_INFO_SCSV		= 0x00ff,

	/* TLS 1.2 cipher suites (ECDHE with X25519, RFC 8422) */
	TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256		= 0xc02f,
	TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384		= 0xc030,
	TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256	= 0xcca8,
	TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256	= 0xc02b,
	TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384	= 0xc02c,
	TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256	= 0xcca9,

	/* TLS 1.2 handshake message types */
	HServerKeyExchange	= 12,
	HCertificateRequest	= 13,
	HServerHelloDone	= 14,
	HClientKeyExchange	= 16,

	RandomSize	= 32,
	X25519Size	= 32,
	MaxHandMsg	= 1<<15,
};

/*
 * Cipher suite descriptor.
 * encalg must match the name used in devtls ctl "secret" command.
 * hashlen is the output length of the suite's hash function.
 * keylen / ivlen are the AEAD key and per-record nonce sizes.
 */
typedef struct Suite Suite;
struct Suite {
	int id;
	char *encalg;
	int keylen;
	int ivlen;
	int hashlen;
	DigestState* (*hmac)(uchar*,ulong,uchar*,ulong,uchar*,DigestState*);
	DigestState* (*hash)(uchar*,ulong,uchar*,DigestState*);
};

static Suite suites[] = {
	{TLS_AES_128_GCM_SHA256,       "aes_128_gcm_aead_tls13", 16, 12, 32, hmac_sha2_256, sha256},
	{TLS_AES_256_GCM_SHA384,       "aes_256_gcm_aead_tls13", 32, 12, 48, hmac_sha2_384, sha384},
	{TLS_CHACHA20_POLY1305_SHA256, "ccpoly96_aead_tls13",    32, 12, 32, hmac_sha2_256, sha256},
};

static Suite*
findSuite(int id)
{
	int i;
	for(i = 0; i < nelem(suites); i++)
		if(suites[i].id == id)
			return &suites[i];
	return nil;
}

typedef struct Suite12 Suite12;
struct Suite12 {
	int	id;
	char	*encalg;	/* devtls cipher name */
	int	keylen;		/* per-direction key bytes */
	int	ivlen;		/* per-direction IV bytes (4 for GCM, 12 for ChaCha20) */
	int	hashlen;	/* 32 or 48 */
	DigestState* (*hmac)(uchar*,ulong,uchar*,ulong,uchar*,DigestState*);
	DigestState* (*hash)(uchar*,ulong,uchar*,DigestState*);
};

static Suite12 suites12[] = {
	{TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256,         "aes_128_gcm_aead",    16,  4, 32, hmac_sha2_256, sha256},
	{TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,         "aes_256_gcm_aead",    32,  4, 48, hmac_sha2_384, sha384},
	{TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256,   "ccpoly96_aead_tls13", 32, 12, 32, hmac_sha2_256, sha256},
	{TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256,       "aes_128_gcm_aead",    16,  4, 32, hmac_sha2_256, sha256},
	{TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,       "aes_256_gcm_aead",    32,  4, 48, hmac_sha2_384, sha384},
	{TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256, "ccpoly96_aead_tls13", 32, 12, 32, hmac_sha2_256, sha256},
};

static Suite12*
findSuite12(int id)
{
	int i;
	for(i = 0; i < nelem(suites12); i++)
		if(suites12[i].id == id)
			return &suites12[i];
	return nil;
}

/* ---- encoding helpers ---- */

static void put16(uchar *p, int v){ p[0]=v>>8; p[1]=v; }
static void put24(uchar *p, int v){ p[0]=v>>16; p[1]=v>>8; p[2]=v; }
static int get16(uchar *p){ return ((int)p[0]<<8)|p[1]; }
static int get24(uchar *p){ return ((int)p[0]<<16)|((int)p[1]<<8)|p[2]; }

typedef struct Buf Buf;
struct Buf {
	uchar *p;
	uchar data[4096];
};

static void bufinit(Buf *b){ b->p = b->data; }
static int buflen(Buf *b){ return b->p - b->data; }
static void bufbyte(Buf *b, int v){ *b->p++ = v; }
static void bufput16(Buf *b, int v){ put16(b->p, v); b->p += 2; }
static void bufput24(Buf *b, int v){ put24(b->p, v); b->p += 3; }
static void bufbytes(Buf *b, uchar *src, int n){ memmove(b->p, src, n); b->p += n; }

/* ---- HKDF primitives (RFC 5869) ---- */

/*
 * HKDF-Extract(salt, IKM) = HMAC-Hash(salt, IKM)
 * Writes hashlen bytes to prk.
 */
static void
hkdf_extract(uchar *prk,
	uchar *salt, int saltlen,
	uchar *ikm, int ikmlen,
	DigestState* (*hmac)(uchar*,ulong,uchar*,ulong,uchar*,DigestState*))
{
	hmac(ikm, ikmlen, salt, saltlen, prk, nil);
}

/*
 * HKDF-Expand(PRK, info, L) per RFC 5869 §2.3.
 * T(0) = ""
 * T(i) = HMAC(PRK, T(i-1) || info || counter)
 * OKM  = T(1) || T(2) || ... truncated to L bytes.
 */
static void
hkdf_expand(uchar *out, int outlen,
	uchar *prk, int prklen,
	uchar *info, int infolen,
	DigestState* (*hmac)(uchar*,ulong,uchar*,ulong,uchar*,DigestState*),
	int hashlen)
{
	uchar T[64];
	uchar buf[512];
	int blen, n, pos, tlen;
	uchar cnt;

	tlen = 0;
	pos  = 0;
	for(cnt = 1; pos < outlen; cnt++){
		blen = 0;
		memmove(buf+blen, T, tlen);    blen += tlen;
		memmove(buf+blen, info, infolen); blen += infolen;
		buf[blen++] = cnt;
		hmac(buf, blen, prk, prklen, T, nil);
		tlen = hashlen;
		n = outlen - pos;
		if(n > hashlen) n = hashlen;
		memmove(out+pos, T, n);
		pos += n;
	}
	memset(T, 0, sizeof(T));
	memset(buf, 0, sizeof(buf));
}

/*
 * HKDF-Expand-Label(Secret, Label, Context, Length)
 * HkdfLabel = uint16(Length) || uint8(len("tls13 "+Label)) || "tls13 " || Label
 *           || uint8(len(Context)) || Context
 */
static void
hkdf_expand_label(uchar *out, int outlen,
	uchar *secret, int slen,
	char *label, int labellen,
	uchar *ctx, int ctxlen,
	DigestState* (*hmac)(uchar*,ulong,uchar*,ulong,uchar*,DigestState*),
	int hashlen)
{
	uchar info[512];
	uchar *p = info;

	put16(p, outlen); p += 2;
	*p++ = 6 + labellen;
	memmove(p, "tls13 ", 6); p += 6;
	memmove(p, label, labellen); p += labellen;
	*p++ = ctxlen;
	if(ctxlen > 0){ memmove(p, ctx, ctxlen); p += ctxlen; }

	hkdf_expand(out, outlen, secret, slen, info, p-info, hmac, hashlen);
}

/*
 * Derive-Secret(Secret, Label, Messages) =
 *   HKDF-Expand-Label(Secret, Label, Transcript-Hash(Messages), Hash.length)
 */
static void
derive_secret(uchar *out,
	uchar *secret, int slen,
	char *label, int labellen,
	uchar *transcript_hash, int hashlen,
	DigestState* (*hmac)(uchar*,ulong,uchar*,ulong,uchar*,DigestState*))
{
	hkdf_expand_label(out, hashlen, secret, slen,
		label, labellen, transcript_hash, hashlen, hmac, hashlen);
}

/* ---- TLS 1.2 PRF (RFC 5246 §5) ---- */

/*
 * P_hash(secret, seed) using HMAC-Hash.
 * A(0) = seed
 * A(i) = HMAC(secret, A(i-1))
 * output = HMAC(secret, A(1)||seed) || HMAC(secret, A(2)||seed) || ...
 */
static void
p_hash(uchar *out, int outlen,
	uchar *secret, int secretlen,
	uchar *seed, int seedlen,
	DigestState* (*hmac)(uchar*,ulong,uchar*,ulong,uchar*,DigestState*),
	int hashlen)
{
	uchar A[64];		/* A(i), at most SHA-384 = 48 bytes */
	uchar buf[64+256];	/* A(i) || seed */
	uchar tmp[64];
	int pos, n;

	/* A(1) = HMAC(secret, seed) */
	hmac(seed, seedlen, secret, secretlen, A, nil);

	for(pos = 0; pos < outlen; ){
		/* HMAC(secret, A(i) || seed) */
		memmove(buf, A, hashlen);
		memmove(buf+hashlen, seed, seedlen);
		hmac(buf, hashlen+seedlen, secret, secretlen, tmp, nil);
		n = outlen - pos;
		if(n > hashlen) n = hashlen;
		memmove(out+pos, tmp, n);
		pos += n;
		/* A(i+1) = HMAC(secret, A(i)) */
		hmac(A, hashlen, secret, secretlen, A, nil);
	}
	memset(A, 0, sizeof(A));
	memset(buf, 0, sizeof(buf));
	memset(tmp, 0, sizeof(tmp));
}

/*
 * TLS 1.2 PRF(secret, label, seed, outlen) = P_SHA256(secret, label||seed)
 * or P_SHA384 for SHA-384 cipher suites.
 */
static void
tls12prf(uchar *out, int outlen,
	uchar *secret, int secretlen,
	char *label,
	uchar *seed, int seedlen,
	DigestState* (*hmac)(uchar*,ulong,uchar*,ulong,uchar*,DigestState*),
	int hashlen)
{
	uchar ls[512];
	int labellen, lslen;

	labellen = strlen(label);
	lslen = labellen + seedlen;
	memmove(ls, label, labellen);
	memmove(ls+labellen, seed, seedlen);
	p_hash(out, outlen, secret, secretlen, ls, lslen, hmac, hashlen);
	memset(ls, 0, lslen);
}

/* ---- Transcript hash ---- */

typedef struct Transcript Transcript;
struct Transcript {
	DigestState *st256;
	DigestState *st384;
	Suite *s;
};

static void
trInit(Transcript *t, Suite *s)
{
	t->st256 = t->st384 = nil;
	t->s = s;
}

static void
trAdd(Transcript *t, uchar *data, int n)
{
	if(t->s->hashlen == 32)
		t->st256 = sha256(data, n, nil, t->st256);
	else
		t->st384 = sha384(data, n, nil, t->st384);
}

static void
trHash(Transcript *t, uchar *out)
{
	DigestState copy;
	if(t->s->hashlen == 32){
		copy = *t->st256;
		((volatile DigestState*)&copy)->malloced = 0;
		sha256(nil, 0, out, &copy);
	} else {
		copy = *t->st384;
		((volatile DigestState*)&copy)->malloced = 0;
		sha384(nil, 0, out, &copy);
	}
}

static void
trFree(Transcript *t)
{
	free(t->st256);
	free(t->st384);
	t->st256 = t->st384 = nil;
}

/* Add a handshake message (4-byte header + body) to the transcript. */
static void
trAddMsg(Transcript *t, int type, uchar *body, int bodylen)
{
	uchar hdr[4];
	hdr[0] = type;
	put24(hdr+1, bodylen);
	trAdd(t, hdr, 4);
	if(bodylen > 0)
		trAdd(t, body, bodylen);
}

/* ---- TLS 1.3 key schedule ---- */

typedef struct KeySchedule KeySchedule;
struct KeySchedule {
	Suite *s;
	uchar early_secret[64];
	uchar hs_secret[64];
	uchar c_hs[64];	/* client_hs_traffic_secret */
	uchar s_hs[64];	/* server_hs_traffic_secret */
	uchar ms[64];	/* master_secret */
	uchar c_ap[64];	/* client_app_traffic_secret */
	uchar s_ap[64];	/* server_app_traffic_secret */
};

/*
 * Initialise early_secret = HKDF-Extract(zeros, PSK-or-zeros).
 * RFC 8446 §7.1.
 */
static void
ksEarly(KeySchedule *ks, Suite *s, uchar *psk, int psklen)
{
	uchar zeros[64];
	ks->s = s;
	memset(zeros, 0, s->hashlen);
	if(psk == nil || psklen == 0)
		hkdf_extract(ks->early_secret, zeros, s->hashlen,
			zeros, s->hashlen, s->hmac);
	else
		hkdf_extract(ks->early_secret, zeros, s->hashlen,
			psk, psklen, s->hmac);
}

/*
 * Derive handshake traffic secrets from (EC)DHE shared secret and
 * the transcript hash of ClientHello..ServerHello.
 */
static void
ksHandshake(KeySchedule *ks, uchar *dhe_secret, uchar *ch_sh_hash)
{
	uchar zeros[64];
	uchar empty_hash[64];
	uchar derived[64];
	Suite *s = ks->s;

	memset(zeros, 0, s->hashlen);
	/* empty transcript hash for the "derived" label */
	s->hash(nil, 0, empty_hash, nil);

	/* derived = Derive-Secret(early_secret, "derived", "") */
	derive_secret(derived, ks->early_secret, s->hashlen,
		"derived", 7, empty_hash, s->hashlen, s->hmac);

	/* handshake_secret = HKDF-Extract(derived, DHE) */
	hkdf_extract(ks->hs_secret, derived, s->hashlen,
		dhe_secret, X25519Size, s->hmac);

	/* client/server handshake traffic secrets */
	derive_secret(ks->c_hs, ks->hs_secret, s->hashlen,
		"c hs traffic", 12, ch_sh_hash, s->hashlen, s->hmac);
	derive_secret(ks->s_hs, ks->hs_secret, s->hashlen,
		"s hs traffic", 12, ch_sh_hash, s->hashlen, s->hmac);
}

/*
 * Derive application traffic secrets from transcript hash of
 * ClientHello..server Finished.
 */
static void
ksMaster(KeySchedule *ks, uchar *sf_hash)
{
	uchar zeros[64];
	uchar empty_hash[64];
	uchar derived[64];
	Suite *s = ks->s;

	memset(zeros, 0, s->hashlen);
	s->hash(nil, 0, empty_hash, nil);

	/* derived = Derive-Secret(hs_secret, "derived", "") */
	derive_secret(derived, ks->hs_secret, s->hashlen,
		"derived", 7, empty_hash, s->hashlen, s->hmac);

	/* master_secret = HKDF-Extract(derived, zeros) */
	hkdf_extract(ks->ms, derived, s->hashlen, zeros, s->hashlen, s->hmac);

	/* application traffic secrets */
	derive_secret(ks->c_ap, ks->ms, s->hashlen,
		"c ap traffic", 12, sf_hash, s->hashlen, s->hmac);
	derive_secret(ks->s_ap, ks->ms, s->hashlen,
		"s ap traffic", 12, sf_hash, s->hashlen, s->hmac);
}

/*
 * Compute Finished verify_data:
 *   finished_key = HKDF-Expand-Label(traffic_secret, "finished", "", hashlen)
 *   verify_data  = HMAC(finished_key, transcript_hash)
 */
static void
computeFinished(uchar *out, Suite *s, uchar *traffic_secret, uchar *th)
{
	uchar fkey[64];
	hkdf_expand_label(fkey, s->hashlen, traffic_secret, s->hashlen,
		"finished", 8, nil, 0, s->hmac, s->hashlen);
	s->hmac(th, s->hashlen, fkey, s->hashlen, out, nil);
	memset(fkey, 0, sizeof(fkey));
}

/* ---- traffic key derivation ---- */

static void
deriveKeys(Suite *s, uchar *ts, uchar *key, uchar *iv)
{
	hkdf_expand_label(key, s->keylen, ts, s->hashlen,
		"key", 3, nil, 0, s->hmac, s->hashlen);
	hkdf_expand_label(iv, s->ivlen, ts, s->hashlen,
		"iv", 2, nil, 0, s->hmac, s->hashlen);
}

/* ---- devtls ctl helpers ---- */

static int
ctlFmt(int ctl, char *fmt, ...)
{
	char buf[256];
	char *e;
	va_list a;
	int n;

	va_start(a, fmt);
	e = vseprint(buf, buf+sizeof(buf), fmt, a);
	va_end(a);
	n = e - buf;
	return kwrite(ctl, buf, n);
}

/*
 * Install AEAD keys into devtls.
 * devtls secret format: "secret <hashalg> <encalg> <isclient> <base64>"
 * base64 encodes: client_key + server_key + client_iv + server_iv
 * For TLS 1.3 AEAD there is no separate MAC key, so hashalg is "clear".
 */
static int
installKeys(int ctl, Suite *s,
	uchar *c_ts, uchar *s_ts,  /* client/server traffic secrets */
	int isclient)
{
	uchar ckey[32], civ[12], skey[32], siv[12];
	uchar raw[128];
	char b64[256];
	int n;
	uchar *p = raw;

	deriveKeys(s, c_ts, ckey, civ);
	deriveKeys(s, s_ts, skey, siv);

	memmove(p, ckey, s->keylen); p += s->keylen;
	memmove(p, skey, s->keylen); p += s->keylen;
	memmove(p, civ, s->ivlen);   p += s->ivlen;
	memmove(p, siv, s->ivlen);   p += s->ivlen;
	n = p - raw;

	enc64(b64, sizeof(b64), raw, n);

	if(ctlFmt(ctl, "secret clear %s %d %s", s->encalg, isclient, b64) < 0)
		return -1;

	memset(ckey, 0, sizeof(ckey));
	memset(skey, 0, sizeof(skey));
	memset(civ, 0, sizeof(civ));
	memset(siv, 0, sizeof(siv));
	memset(raw, 0, sizeof(raw));
	return 0;
}

/*
 * Install TLS 1.2 AEAD keys into devtls.
 * key_block from PRF "key expansion" (RFC 5246 §6.3):
 *   c_write_key[keylen] | s_write_key[keylen] | c_write_IV[ivlen] | s_write_IV[ivlen]
 *
 * devtls "secret clear <encalg> 1 <b64>" with isclient=1 (maclen=0):
 *   tos=out: key=x[0], iv=x[2*keylen]  → client sends with tos → tos = c_write_key/c_write_IV
 *   toc=in:  key=x[keylen], iv=x[2*keylen+ivlen] → client receives → toc = s_write_key/s_write_IV
 * key_block is already in the correct layout [c_key|s_key|c_iv|s_iv].
 */
static int
installKeys12(int ctl, Suite12 *s, uchar *key_block)
{
	char b64[256];
	int n = 2*s->keylen + 2*s->ivlen;

	enc64(b64, sizeof(b64), key_block, n);
	if(ctlFmt(ctl, "secret clear %s 1 %s", s->encalg, b64) < 0)
		return -1;
	return 0;
}

/* ---- handshake message I/O (via /dev/tls/N/hand) ---- */

/*
 * Write one handshake message.
 * Format: type(1) || length(3) || body(length)
 * Written as a single kwrite so the header and body go in one TLS record.
 */
static int
hmsgWrite(int hand, int type, uchar *body, int bodylen)
{
	uchar *buf;
	int n, r;

	n = 4 + bodylen;
	buf = malloc(n);
	if(buf == nil) return -1;
	buf[0] = type;
	put24(buf+1, bodylen);
	if(bodylen > 0)
		memmove(buf+4, body, bodylen);
	r = kwrite(hand, buf, n);
	free(buf);
	return (r == n) ? 0 : -1;
}

/*
 * Read one handshake message.  Caller must free *bodyp.
 * Returns 0 on success, -1 on error.
 */
static int
hmsgRead(int hand, int *typep, uchar **bodyp, int *bodylenp)
{
	uchar hdr[4];
	uchar *body;
	int len, got, r;

	/* read exactly 4 header bytes */
	for(got = 0; got < 4; ){
		r = kread(hand, hdr+got, 4-got);
		if(r <= 0) return -1;
		got += r;
	}
	*typep = hdr[0];
	len = get24(hdr+1);
	if(len < 0 || len > MaxHandMsg)
		return -1;
	body = nil;
	if(len > 0){
		body = malloc(len);
		if(body == nil) return -1;
		for(got = 0; got < len; ){
			r = kread(hand, body+got, len-got);
			if(r <= 0){ free(body); return -1; }
			got += r;
		}
	}
	*bodyp    = body;
	*bodylenp = len;
	return 0;
}

/* ---- ClientHello builder ---- */

static void
buildClientHello(Buf *b, uchar *crandom, uchar *ks_pub, TLSconn *conn, int offer12)
{
	uchar *ext_lenp, *ext_start;
	int snilen, nsuites;

	bufput16(b, TLS12Legacy);	/* legacy_version */
	bufbytes(b, crandom, RandomSize);
	/* RFC 8446 §D.4: send non-empty session_id when offering TLS 1.3 for compat */
	if(offer12){
		uchar sid[32];
		genrandom(sid, 32);
		bufbyte(b, 32);
		bufbytes(b, sid, 32);
	} else {
		bufbyte(b, 0);			/* empty session_id */
	}

	/* cipher suites: TLS 1.3 mandatory set, plus TLS 1.2 ECDHE if offer12, plus SCSV */
	nsuites = nelem(suites) + (offer12 ? (int)nelem(suites12) : 0) + 1; /* +1 for SCSV */
	bufput16(b, nsuites*2);
	bufput16(b, TLS_AES_128_GCM_SHA256);
	bufput16(b, TLS_AES_256_GCM_SHA384);
	bufput16(b, TLS_CHACHA20_POLY1305_SHA256);
	if(offer12){
		bufput16(b, TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256);
		bufput16(b, TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384);
		bufput16(b, TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256);
		bufput16(b, TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256);
		bufput16(b, TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384);
		bufput16(b, TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256);
	}
	bufput16(b, TLS_EMPTY_RENEGOTIATION_INFO_SCSV);

	/* null compression */
	bufbyte(b, 1);
	bufbyte(b, 0);

	/* extensions */
	ext_lenp  = b->p; bufput16(b, 0);
	ext_start = b->p;

	/* Extension order matches OpenSSL: SNI, ec_point_formats, supported_groups,
	 * session_ticket, encrypt_then_mac, extended_master_secret,
	 * sig_algs, supported_versions, psk_key_exchange_modes, key_share */

	/* SNI */
	if(conn->serverName != nil && conn->serverName[0]){
		snilen = strlen(conn->serverName);
		bufput16(b, ExtSNI);
		bufput16(b, 2+1+2+snilen);
		bufput16(b, 1+2+snilen);
		bufbyte(b, 0);			/* host_name */
		bufput16(b, snilen);
		bufbytes(b, (uchar*)conn->serverName, snilen);
	}

	if(offer12){
		/* ec_point_formats: uncompressed + both compressed forms (matches OpenSSL) */
		bufput16(b, 0x000b); bufput16(b, 4);
		bufbyte(b, 3); bufbyte(b, 0); bufbyte(b, 1); bufbyte(b, 2);
	}

	/* supported_groups */
	if(offer12){
		/* x25519, secp256r1, x448, secp521r1, secp384r1 (matches OpenSSL named EC groups) */
		bufput16(b, ExtSupportedGroups); bufput16(b, 12);
		bufput16(b, 10);
		bufput16(b, 0x001d);	/* x25519 */
		bufput16(b, 0x0017);	/* secp256r1 */
		bufput16(b, 0x001e);	/* x448 */
		bufput16(b, 0x0019);	/* secp521r1 */
		bufput16(b, 0x0018);	/* secp384r1 */
	} else {
		bufput16(b, ExtSupportedGroups); bufput16(b, 4);
		bufput16(b, 2); bufput16(b, X25519group);
	}

	if(offer12){
		/* session_ticket: empty (no ticket to resume) */
		bufput16(b, 0x0023); bufput16(b, 0);
		/* encrypt_then_mac */
		bufput16(b, 0x0016); bufput16(b, 0);
		/* extended_master_secret (RFC 7627) */
		bufput16(b, 0x0017); bufput16(b, 0);
	}

	/* signature_algorithms: 20 entries matching OpenSSL defaults; inner list = 40 bytes */
	if(offer12){
		bufput16(b, ExtSigAlgs); bufput16(b, 42);
		bufput16(b, 40);
		bufput16(b, 0x0403);	/* ecdsa_secp256r1_sha256 */
		bufput16(b, 0x0503);	/* ecdsa_secp384r1_sha384 */
		bufput16(b, 0x0603);	/* ecdsa_secp521r1_sha512 */
		bufput16(b, 0x0807);	/* ed25519 */
		bufput16(b, 0x0808);	/* ed448 */
		bufput16(b, 0x0809);	/* rsa_pss_pss_sha256 */
		bufput16(b, 0x080a);	/* rsa_pss_pss_sha384 */
		bufput16(b, 0x080b);	/* rsa_pss_pss_sha512 */
		bufput16(b, 0x0804);	/* rsa_pss_rsae_sha256 */
		bufput16(b, 0x0805);	/* rsa_pss_rsae_sha384 */
		bufput16(b, 0x0806);	/* rsa_pss_rsae_sha512 */
		bufput16(b, 0x0401);	/* rsa_pkcs1_sha256 */
		bufput16(b, 0x0501);	/* rsa_pkcs1_sha384 */
		bufput16(b, 0x0601);	/* rsa_pkcs1_sha512 */
		bufput16(b, 0x0303);	/* ecdsa_sha224 */
		bufput16(b, 0x0301);	/* rsa_pkcs1_sha224 */
		bufput16(b, 0x0302);	/* dsa_sha224 */
		bufput16(b, 0x0402);	/* dsa_sha256 */
		bufput16(b, 0x0502);	/* dsa_sha384 */
		bufput16(b, 0x0602);	/* dsa_sha512 */
	} else {
		bufput16(b, ExtSigAlgs); bufput16(b, 4);
		bufput16(b, 2); bufput16(b, 0x0804);
	}

	/* supported_versions: TLS 1.3 + TLS 1.2 + TLS 1.1 + TLS 1.0 (matches OpenSSL) */
	if(offer12){
		bufput16(b, ExtSupportedVersions); bufput16(b, 9);
		bufbyte(b, 8);
		bufput16(b, TLS13Version);	/* 0x0304 */
		bufput16(b, TLS12Legacy);	/* 0x0303 */
		bufput16(b, 0x0302);		/* TLS 1.1 */
		bufput16(b, 0x0301);		/* TLS 1.0 */
	} else {
		bufput16(b, ExtSupportedVersions); bufput16(b, 3);
		bufbyte(b, 2); bufput16(b, TLS13Version);
	}

	/* psk_key_exchange_modes: psk_dhe_ke */
	bufput16(b, ExtPSKKeyExchangeModes); bufput16(b, 2);
	bufbyte(b, 1); bufbyte(b, 1);

	/* key_share (TLS 1.3; ignored by TLS 1.2 servers) */
	bufput16(b, ExtKeyShare); bufput16(b, 2+2+2+X25519Size);
	bufput16(b, 2+2+X25519Size);		/* ClientShares length */
	bufput16(b, X25519group); bufput16(b, X25519Size);
	bufbytes(b, ks_pub, X25519Size);

	put16(ext_lenp, b->p - ext_start);
}

/* ---- tlsClient13: TLS 1.3 handshake completion ---- */
/*
 * Called by tlsClient after ServerHello is read and version confirmed as TLS 1.3.
 * ctl/hand/data are already open; ch_body is the saved ClientHello body.
 * Does NOT close ctl/hand/data — caller owns them.
 * Returns data fd on success, -1 on failure.
 */
static int
tlsClient13(int ctl, int hand, int data,
	uchar *crandom, uchar *ks_priv,
	uchar *ch_body, int ch_bodylen,
	uchar *sh_body, int sh_bodylen,
	TLSconn *conn)
{
	int r;
	uchar dh_shared[X25519Size];
	uchar th[64];
	Suite *s;
	KeySchedule ks;
	Transcript tr;
	int suiteid;
	uchar *body;
	int bodylen, msgtype;

	USED(crandom);

	if(ctlFmt(ctl, "tls13 1") < 0)
		return -1;

	/* parse ServerHello for suite and key share */
	suiteid = 0;
	body = nil;
	{
		uchar *p = sh_body;
		int sidlen, comp, ext_total, ext_type, ext_len;
		uchar peer_pub[X25519Size];
		int got_ks = 0;

		p += 2;			/* skip legacy_version */
		p += RandomSize;	/* skip server_random */
		sidlen = *p++; p += sidlen;
		suiteid = get16(p); p += 2;
		comp = *p++; USED(comp);

		s = findSuite(suiteid);
		if(s == nil) return -1;

		/* init transcript */
		trInit(&tr, s);
		trAddMsg(&tr, HClientHello, ch_body, ch_bodylen);

		if(p+2 > sh_body+sh_bodylen) goto fail13;
		ext_total = get16(p); p += 2;
		uchar *ext_end = p + ext_total;
		while(p+4 <= ext_end){
			ext_type = get16(p); p += 2;
			ext_len  = get16(p); p += 2;
			if(ext_type == ExtKeyShare && ext_len >= 4){
				int grp = get16(p);
				int klen = get16(p+2);
				if(grp == X25519group && klen == X25519Size){
					memmove(peer_pub, p+4, X25519Size);
					got_ks = 1;
				}
			}
			p += ext_len;
		}
		if(!got_ks) goto fail13;
		r = curve25519_dh_finish(ks_priv, peer_pub, dh_shared);
		if(!r) goto fail13;

		trAddMsg(&tr, HServerHello, sh_body, sh_bodylen);
	}

	/* derive handshake secrets */
	trHash(&tr, th);
	ksEarly(&ks, s, conn->psk, conn->psklen);
	ksHandshake(&ks, dh_shared, th);

	if(installKeys(ctl, s, ks.c_hs, ks.s_hs, 1) < 0) goto fail13;
	if(ctlFmt(ctl, "changecipher") < 0) goto fail13;

	/* read EncryptedExtensions */
	if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail13;
	if(msgtype != HEncryptedExtensions){ free(body); goto fail13; }
	trAddMsg(&tr, HEncryptedExtensions, body, bodylen);
	free(body); body = nil;

	/* read Certificate or Finished */
	if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail13;
	if(msgtype == HCertificate){
		trAddMsg(&tr, HCertificate, body, bodylen);
		/* extract first cert DER for caller (TLS 1.3 format: ctx_byte | list_len3 | {cert_len3 | cert | exts2}...) */
		free(conn->cert); conn->cert = nil; conn->certlen = 0;
		if(bodylen > 1){
			uchar *cp = body + 1 + *body;
			if(cp+3 <= body+bodylen){
				int clen = get24(cp); cp += 3;
				if(cp+clen <= body+bodylen && clen > 0){
					conn->cert = malloc(clen);
					if(conn->cert){ memmove(conn->cert, cp, clen); conn->certlen = clen; }
				}
			}
		}
		free(body); body = nil;

		/* CertificateVerify */
		if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail13;
		if(msgtype != HCertificateVerify){ free(body); goto fail13; }
		trAddMsg(&tr, HCertificateVerify, body, bodylen);
		free(body); body = nil;

		/* Finished */
		if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail13;
	}
	if(msgtype != HFinished || bodylen != s->hashlen){ free(body); goto fail13; }

	/* verify server Finished */
	{
		uchar pre_fin_hash[64];
		uchar expected[64];
		trHash(&tr, pre_fin_hash);
		computeFinished(expected, s, ks.s_hs, pre_fin_hash);
		if(tsmemcmp(body, expected, s->hashlen) != 0){
			if(conn->trace)
				conn->trace("tls13: server Finished mismatch\n");
			free(body); goto fail13;
		}
	}
	trAddMsg(&tr, HFinished, body, bodylen);
	free(body); body = nil;

	/* derive master / application secrets */
	trHash(&tr, th);
	ksMaster(&ks, th);

	/* send client Finished */
	{
		uchar cfin[64];
		computeFinished(cfin, s, ks.c_hs, th);
		if(hmsgWrite(hand, HFinished, cfin, s->hashlen) < 0) goto fail13;
		trAddMsg(&tr, HFinished, cfin, s->hashlen);
	}

	/* switch to application keys */
	if(installKeys(ctl, s, ks.c_ap, ks.s_ap, 1) < 0) goto fail13;
	if(ctlFmt(ctl, "changecipher") < 0) goto fail13;
	if(ctlFmt(ctl, "setin") < 0) goto fail13;
	if(ctlFmt(ctl, "opened") < 0) goto fail13;

	trFree(&tr);
	memset(&ks, 0, sizeof(ks));
	memset(dh_shared, 0, sizeof(dh_shared));
	return data;

fail13:
	trFree(&tr);
	memset(&ks, 0, sizeof(ks));
	memset(dh_shared, 0, sizeof(dh_shared));
	return -1;
}

/* ---- tlsClient12: TLS 1.2 handshake completion ---- */
/*
 * Called by tlsClient after ServerHello is read and version confirmed as TLS 1.2.
 * Cipher suites: ECDHE-RSA-AES128/256-GCM-SHA256/384, ECDHE-RSA-ChaCha20-Poly1305.
 * Key exchange: X25519 (RFC 8422).
 * Does NOT close ctl/hand/data — caller owns them.
 * Returns data fd on success, -1 on failure.
 */
static int
tlsClient12(int ctl, int hand, int data,
	uchar *crandom, uchar *ks_priv, uchar *ks_pub,
	uchar *ch_body, int ch_bodylen,
	uchar *sh_body, int sh_bodylen,
	TLSconn *conn)
{
	Suite12 *s12;
	Suite sfake;		/* minimal Suite for Transcript dispatch */
	Transcript tr;
	uchar srandom[RandomSize];
	uchar server_pub[X25519Size];
	uchar dh_shared[X25519Size];
	uchar master[48];
	uchar key_block[88];	/* max: 2*32 + 2*12 = 88 for ChaCha20 */
	uchar th[64];
	uchar cfin[12], sfin[12];
	uchar seed[2*RandomSize];
	uchar cke[1+X25519Size];
	uchar *body;
	int bodylen, msgtype, suiteid;
	int ext_ms;	/* extended master secret negotiated (RFC 7627) */
	uchar *p, *end;

	body = nil;

	/* parse ServerHello: extract srandom, suite id, and extensions */
	if(sh_bodylen < 2+RandomSize+1)
		return -1;
	p = sh_body;
	p += 2;				/* skip legacy_version */
	memmove(srandom, p, RandomSize); p += RandomSize;
	p += *p + 1;			/* skip session_id */
	if(p+2 > sh_body+sh_bodylen) return -1;
	suiteid = get16(p); p += 2;

	/* skip compression_method, scan extensions */
	ext_ms = 0;
	if(p < sh_body+sh_bodylen) p++;	/* compression */
	if(p+2 <= sh_body+sh_bodylen){
		int ext_total = get16(p); p += 2;
		uchar *ext_end = p + ext_total;
		if(ext_end > sh_body+sh_bodylen) ext_end = sh_body+sh_bodylen;
		while(p+4 <= ext_end){
			int ext_type = get16(p); p += 2;
			int ext_len  = get16(p); p += 2;
			if(ext_type == 0x0017)	/* extended_master_secret */
				ext_ms = 1;
			p += ext_len;
		}
	}

	s12 = findSuite12(suiteid);
	if(s12 == nil) return -1;
	/* init transcript using a minimal Suite (only hashlen/hmac/hash used) */
	memset(&sfake, 0, sizeof(sfake));
	sfake.hashlen = s12->hashlen;
	sfake.hmac    = s12->hmac;
	sfake.hash    = s12->hash;
	trInit(&tr, &sfake);
	trAddMsg(&tr, HClientHello, ch_body, ch_bodylen);
	trAddMsg(&tr, HServerHello, sh_body, sh_bodylen);

	/* read Certificate */
	if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail12;
	if(msgtype != HCertificate){ free(body); goto fail12; }
	trAddMsg(&tr, HCertificate, body, bodylen);
	/* extract first cert DER (TLS 1.2 format: cert_list_len[3] | {cert_len[3] | cert}...) */
	free(conn->cert); conn->cert = nil; conn->certlen = 0;
	{
		uchar *cp = body;
		end = body + bodylen;
		if(cp+3 <= end){
			int listlen = get24(cp); cp += 3;
			if(cp+3 <= cp+listlen && cp+3 <= end){
				int certlen = get24(cp); cp += 3;
				if(certlen > 0 && cp+certlen <= end){
					conn->cert = malloc(certlen);
					if(conn->cert){ memmove(conn->cert, cp, certlen); conn->certlen = certlen; }
				}
			}
		}
	}
	free(body); body = nil;

	/* read optional CertificateRequest or ServerKeyExchange */
	if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail12;
	if(msgtype == HCertificateRequest){
		trAddMsg(&tr, HCertificateRequest, body, bodylen);
		free(body); body = nil;
		if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail12;
	}
	if(msgtype != HServerKeyExchange){ free(body); goto fail12; }
	trAddMsg(&tr, HServerKeyExchange, body, bodylen);

	/* parse ServerKeyExchange: EC params (RFC 4492)
	 * curve_type[1]=0x03 | named_curve[2] | publen[1] | pub[publen] | [sig...] */
	{
		int grp, pklen;
		p = body; end = body + bodylen;
		if(p+4 > end){ free(body); goto fail12; }
		if(*p++ != 0x03){ free(body); goto fail12; }	/* named_curve */
		grp = get16(p); p += 2;
		if(grp != X25519group){ free(body); goto fail12; }
		pklen = *p++;
		if(pklen != X25519Size || p+pklen > end){ free(body); goto fail12; }
		memmove(server_pub, p, X25519Size);
		/* TODO: verify signature over crandom||srandom||ServerECDHParams */
	}
	free(body); body = nil;

	/* read ServerHelloDone */
	if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail12;
	if(msgtype != HServerHelloDone){ free(body); goto fail12; }
	trAddMsg(&tr, HServerHelloDone, body, bodylen);
	free(body); body = nil;

	/* compute shared secret (curve25519_dh_finish zeroes ks_priv and server_pub) */
	if(!curve25519_dh_finish(ks_priv, server_pub, dh_shared)) goto fail12;

	/* send ClientKeyExchange BEFORE deriving master (needed for ext_ms session hash) */
	cke[0] = X25519Size;
	memmove(cke+1, ks_pub, X25519Size);
	if(hmsgWrite(hand, HClientKeyExchange, cke, sizeof(cke)) < 0) goto fail12;
	trAddMsg(&tr, HClientKeyExchange, cke, sizeof(cke));

	/* derive master secret */
	if(ext_ms){
		/* RFC 7627: PRF(premaster, "extended master secret", Hash(handshake_messages)) */
		trHash(&tr, th);
		tls12prf(master, 48, dh_shared, X25519Size,
			"extended master secret", th, s12->hashlen, s12->hmac, s12->hashlen);
	} else {
		/* RFC 5246: PRF(premaster, "master secret", crandom||srandom) */
		memmove(seed, crandom, RandomSize);
		memmove(seed+RandomSize, srandom, RandomSize);
		tls12prf(master, 48, dh_shared, X25519Size,
			"master secret", seed, 2*RandomSize, s12->hmac, s12->hashlen);
	}
	memset(dh_shared, 0, sizeof(dh_shared));

	/* derive key block: PRF(master, "key expansion", srandom||crandom) */
	memmove(seed, srandom, RandomSize);
	memmove(seed+RandomSize, crandom, RandomSize);
	tls12prf(key_block, 2*s12->keylen + 2*s12->ivlen, master, 48,
		"key expansion", seed, 2*RandomSize, s12->hmac, s12->hashlen);

	/* compute client Finished BEFORE installing keys.
	 * trHash here = Hash(CH+SH+Cert+SKE+SHD+CKE) — same as session_hash. */
	trHash(&tr, th);
	tls12prf(cfin, 12, master, 48,
		"client finished", th, s12->hashlen, s12->hmac, s12->hashlen);

	/* install pending keys */
	if(installKeys12(ctl, s12, key_block) < 0) goto fail12;
	memset(key_block, 0, sizeof(key_block));

	/* changecipher: sends CCS, activates out.sec */
	if(ctlFmt(ctl, "changecipher") < 0) goto fail12;

	/* send encrypted client Finished */
	if(hmsgWrite(hand, HFinished, cfin, 12) < 0) goto fail12;
	trAddMsg(&tr, HFinished, cfin, 12);

	/* read server Finished (devtls auto-activates in.sec when server CCS arrives).
	 * Server may send NewSessionTicket (type 4) before CCS; skip it. */
	if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail12;
	if(msgtype == 4){	/* NewSessionTicket — must be in transcript for server Finished */
		trAddMsg(&tr, msgtype, body, bodylen);
		free(body); body = nil;
		if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail12;
	}
	if(msgtype != HFinished || bodylen != 12){ free(body); goto fail12; }

	/* verify server Finished: PRF(master, "server finished", Hash(all_hs_msgs_incl_cfin)) */
	trHash(&tr, th);
	tls12prf(sfin, 12, master, 48,
		"server finished", th, s12->hashlen, s12->hmac, s12->hashlen);
	if(tsmemcmp(body, sfin, 12) != 0){
		free(body); goto fail12;
	}
	free(body); body = nil;

	if(ctlFmt(ctl, "opened") < 0) goto fail12;

	trFree(&tr);
	memset(master, 0, sizeof(master));
	return data;

fail12:
	trFree(&tr);
	memset(master, 0, sizeof(master));
	memset(key_block, 0, sizeof(key_block));
	return -1;
}

/* ---- tlsClient: version-negotiating dispatcher ---- */

int
tlsClient(int netfd, TLSconn *conn)
{
	char id[16], path[64], errsave[ERRMAX];
	int ctl, hand, data, n;
	uchar crandom[RandomSize];
	uchar ks_priv[X25519Size], ks_pub[X25519Size];
	uchar ch_body[4096];
	int ch_bodylen;
	Buf msg;
	uchar *sh_body;
	int sh_bodylen, sh_msgtype;
	int negotiated_ver;
	int ok = -1;

	if(conn == nil) return -1;

	ctl = kopen("/dev/tls/clone", ORDWR);
	if(ctl < 0) return -1;
	n = kread(ctl, id, sizeof(id)-1);
	if(n <= 0){ kclose(ctl); return -1; }
	id[n] = '\0';
	while(n > 0 && (id[n-1]=='\n'||id[n-1]=='\r')) id[--n] = '\0';

	snprint(conn->dir, sizeof(conn->dir), "/dev/tls/%s", id);
	snprint(path, sizeof(path), "/dev/tls/%s/hand", id);
	hand = kopen(path, ORDWR);
	if(hand < 0){ kclose(ctl); return -1; }
	snprint(path, sizeof(path), "/dev/tls/%s/data", id);
	data = kopen(path, ORDWR);
	if(data < 0){ kclose(hand); kclose(ctl); return -1; }

	/* fd command: use 0x0301 (TLS 1.0) for initial record version per RFC 8446 §5.1 compat.
	 * version command: set after ClientHello so the CH record uses 0x0301.
	 * tls13 1 is issued inside tlsClient13 after version is confirmed. */
	if(ctlFmt(ctl, "fd %d 0x%x", netfd, 0x0301) < 0)
		goto fail;

	/* ephemeral X25519 */
	genrandom(crandom, RandomSize);
	curve25519_dh_new(ks_priv, ks_pub);

	/* build and send ClientHello offering TLS 1.3 + TLS 1.2 */
	bufinit(&msg);
	buildClientHello(&msg, crandom, ks_pub, conn, 1);
	ch_bodylen = buflen(&msg);
	memmove(ch_body, msg.data, ch_bodylen);

	if(hmsgWrite(hand, HClientHello, msg.data, ch_bodylen) < 0)
		goto fail;

	/* set negotiated version after ClientHello; required before secret command */
	if(ctlFmt(ctl, "version 0x%x", TLS12Legacy) < 0)
		goto fail;

	/* read ServerHello */
	sh_body = nil;
	if(hmsgRead(hand, &sh_msgtype, &sh_body, &sh_bodylen) < 0) goto fail;
	if(sh_msgtype != HServerHello || sh_bodylen < 2+RandomSize+1){
		free(sh_body); goto fail;
	}

	/* determine negotiated version by scanning for supported_versions extension */
	negotiated_ver = TLS12Legacy;	/* default: TLS 1.2 */
	{
		uchar *p = sh_body;
		uchar *end = sh_body + sh_bodylen;
		p += 2 + RandomSize;		/* skip legacy_version + server_random */
		p += *p + 1;			/* skip session_id */
		p += 2;				/* skip cipher suite */
		p++;				/* skip compression */
		if(p+2 <= end){
			int ext_total = get16(p); p += 2;
			uchar *ext_end = p + ext_total;
			while(p+4 <= ext_end){
				int ext_type = get16(p); p += 2;
				int ext_len  = get16(p); p += 2;
				if(ext_type == ExtSupportedVersions && ext_len == 2){
					if(get16(p) == TLS13Version)
						negotiated_ver = TLS13Version;
				}
				p += ext_len;
			}
		}
	}

	if(negotiated_ver == TLS13Version)
		ok = tlsClient13(ctl, hand, data, crandom, ks_priv,
			ch_body, ch_bodylen, sh_body, sh_bodylen, conn);
	else
		ok = tlsClient12(ctl, hand, data, crandom, ks_priv, ks_pub,
			ch_body, ch_bodylen, sh_body, sh_bodylen, conn);

	free(sh_body);
	if(ok < 0) goto fail;
	goto done;

fail:
	kgerrstr(errsave, sizeof(errsave));
	kclose(data);
	ok = -1;

done:
	memset(ks_priv, 0, sizeof(ks_priv));
	kclose(hand);
	kclose(ctl);
	if(ok < 0)
		kwerrstr("%s", errsave);
	return ok;
}

/* ---- tlsServer ---- */

int
tlsServer(int netfd, TLSconn *conn)
{
	char id[16], path[64];
	int ctl, hand, data, n;
	uchar srandom[RandomSize];
	uchar ks_priv[X25519Size], ks_pub[X25519Size];
	uchar dh_shared[X25519Size];
	uchar th[64];
	Buf msg;
	Suite *s;
	KeySchedule ks;
	Transcript tr;
	uchar *body;
	int bodylen, msgtype;
	int suiteid, ok = -1;
	int got_tls13, got_ks;
	uchar client_pub[X25519Size];

	if(conn == nil) return -1;

	ctl = kopen("/dev/tls/clone", ORDWR);
	if(ctl < 0) return -1;
	n = kread(ctl, id, sizeof(id)-1);
	if(n <= 0){ kclose(ctl); return -1; }
	id[n] = '\0';
	while(n > 0 && (id[n-1]=='\n'||id[n-1]=='\r')) id[--n] = '\0';

	snprint(conn->dir, sizeof(conn->dir), "/dev/tls/%s", id);
	snprint(path, sizeof(path), "/dev/tls/%s/hand", id);
	hand = kopen(path, ORDWR);
	if(hand < 0){ kclose(ctl); return -1; }
	snprint(path, sizeof(path), "/dev/tls/%s/data", id);
	data = kopen(path, ORDWR);
	if(data < 0){ kclose(hand); kclose(ctl); return -1; }

	if(ctlFmt(ctl, "fd %d 0x%x", netfd, TLS12Legacy) < 0)
		goto fail;
	if(ctlFmt(ctl, "version 0x%x", TLS12Legacy) < 0)
		goto fail;
	if(ctlFmt(ctl, "tls13 1") < 0)
		goto fail;

	/* read ClientHello */
	body = nil;
	if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail;
	if(msgtype != HClientHello || bodylen < 2+RandomSize+1){ free(body); goto fail; }

	s = nil; suiteid = 0; got_tls13 = 0; got_ks = 0;
	memset(client_pub, 0, X25519Size);
	{
		uchar *p = body;
		int sidlen, ncs, complen, ext_total, ext_type, ext_len;
		uchar *ext_end;

		p += 2;				/* legacy_version */
		p += RandomSize;		/* client_random */
		sidlen = *p++; p += sidlen;
		ncs = get16(p); p += 2;
		/* find a supported suite */
		for(int i = 0; i < ncs/2; i++){
			int cs = get16(p); p += 2;
			if(s == nil){ s = findSuite(cs); if(s) suiteid = cs; }
		}
		complen = *p++; p += complen;

		if(s == nil){ free(body); goto fail; }

		if(p+2 > body+bodylen){ free(body); goto fail; }
		ext_total = get16(p); p += 2;
		ext_end = p + ext_total;
		while(p+4 <= ext_end){
			ext_type = get16(p); p += 2;
			ext_len  = get16(p); p += 2;
			if(ext_type == ExtSupportedVersions){
				int vlen = *p;
				for(int i = 0; i+2 <= vlen; i += 2)
					if(get16(p+1+i) == TLS13Version)
						got_tls13 = 1;
			} else if(ext_type == ExtKeyShare){
				int ks_list = get16(p);
				uchar *kp = p+2, *ke = p+2+ks_list;
				while(kp+4 <= ke){
					int grp = get16(kp); kp += 2;
					int klen = get16(kp); kp += 2;
					if(grp == X25519group && klen == X25519Size){
						memmove(client_pub, kp, X25519Size);
						got_ks = 1;
					}
					kp += klen;
				}
			}
			p += ext_len;
		}
		if(!got_tls13 || !got_ks){ free(body); goto fail; }
	}

	/* generate server key share */
	curve25519_dh_new(ks_priv, ks_pub);
	if(!curve25519_dh_finish(ks_priv, client_pub, dh_shared)){ free(body); goto fail; }

	trInit(&tr, s);
	trAddMsg(&tr, HClientHello, body, bodylen);
	free(body); body = nil;

	/* build ServerHello */
	genrandom(srandom, RandomSize);
	bufinit(&msg);
	{
		uchar *ext_lenp, *ext_start;
		bufput16(&msg, TLS12Legacy);
		bufbytes(&msg, srandom, RandomSize);
		bufbyte(&msg, 0);		/* empty session_id */
		bufput16(&msg, suiteid);
		bufbyte(&msg, 0);		/* null compression */

		ext_lenp  = msg.p; bufput16(&msg, 0);
		ext_start = msg.p;

		bufput16(&msg, ExtSupportedVersions); bufput16(&msg, 2);
		bufput16(&msg, TLS13Version);

		bufput16(&msg, ExtKeyShare); bufput16(&msg, 2+2+X25519Size);
		bufput16(&msg, X25519group); bufput16(&msg, X25519Size);
		bufbytes(&msg, ks_pub, X25519Size);

		put16(ext_lenp, msg.p - ext_start);
	}
	if(hmsgWrite(hand, HServerHello, msg.data, buflen(&msg)) < 0) goto fail;
	trAddMsg(&tr, HServerHello, msg.data, buflen(&msg));

	/* derive handshake secrets */
	trHash(&tr, th);
	ksEarly(&ks, s, conn->psk, conn->psklen);
	ksHandshake(&ks, dh_shared, th);

	if(installKeys(ctl, s, ks.c_hs, ks.s_hs, 0) < 0) goto fail;
	if(ctlFmt(ctl, "changecipher") < 0) goto fail;

	/* EncryptedExtensions (empty) */
	{
		uchar ee[2] = {0, 0};
		if(hmsgWrite(hand, HEncryptedExtensions, ee, 2) < 0) goto fail;
		trAddMsg(&tr, HEncryptedExtensions, ee, 2);
	}

	/* Certificate (if we have one) */
	if(conn->chain != nil){
		PEMChain *ch;
		uchar *list_lenp;
		bufinit(&msg);
		bufbyte(&msg, 0);	/* empty request_context */
		list_lenp = msg.p; bufput24(&msg, 0);
		for(ch = conn->chain; ch != nil; ch = ch->next){
			bufput24(&msg, ch->pemlen);
			bufbytes(&msg, (uchar*)ch->pem, ch->pemlen);
			bufput16(&msg, 0);	/* no cert extensions */
		}
		put24(list_lenp, msg.p - list_lenp - 3);
		if(hmsgWrite(hand, HCertificate, msg.data, buflen(&msg)) < 0) goto fail;
		trAddMsg(&tr, HCertificate, msg.data, buflen(&msg));

		/*
		 * CertificateVerify: sign transcript hash with server key.
		 * RFC 8446 §4.4.3: content = "TLS 1.3, server CertificateVerify" (64 spaces + context + 0x00 + hash)
		 * TODO: actual signing once RSA-PSS/ECDSA keys are wired in.
		 * For now emit a zero-length signature so peers that skip verification can proceed.
		 */
		{
			uchar cv[4];
			put16(cv, 0x0804);	/* rsa_pss_rsae_sha256 */
			put16(cv+2, 0);		/* empty signature – placeholder */
			if(hmsgWrite(hand, HCertificateVerify, cv, 4) < 0) goto fail;
			trAddMsg(&tr, HCertificateVerify, cv, 4);
		}
	}

	/* server Finished */
	trHash(&tr, th);
	{
		uchar sfin[64];
		computeFinished(sfin, s, ks.s_hs, th);
		if(hmsgWrite(hand, HFinished, sfin, s->hashlen) < 0) goto fail;
		trAddMsg(&tr, HFinished, sfin, s->hashlen);
	}

	/* derive master / application secrets */
	trHash(&tr, th);
	ksMaster(&ks, th);

	/* read client Finished */
	if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail;
	if(msgtype != HFinished || bodylen != s->hashlen){ free(body); goto fail; }
	{
		uchar expected[64];
		computeFinished(expected, s, ks.c_hs, th);
		if(tsmemcmp(body, expected, s->hashlen) != 0){
			if(conn->trace) conn->trace("tls13: client Finished mismatch\n");
			free(body); goto fail;
		}
	}
	free(body); body = nil;

	/* switch to application keys */
	if(installKeys(ctl, s, ks.c_ap, ks.s_ap, 0) < 0) goto fail;
	if(ctlFmt(ctl, "changecipher") < 0) goto fail;
	if(ctlFmt(ctl, "opened") < 0) goto fail;

	ok = data;
	goto done;

fail:
	kclose(data);
	ok = -1;

done:
	trFree(&tr);
	memset(&ks, 0, sizeof(ks));
	memset(ks_priv, 0, sizeof(ks_priv));
	memset(dh_shared, 0, sizeof(dh_shared));
	kclose(hand);
	kclose(ctl);
	return ok;
}
