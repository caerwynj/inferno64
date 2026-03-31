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

	/* cipher suites */
	TLS_AES_128_GCM_SHA256		= 0x1301,
	TLS_AES_256_GCM_SHA384		= 0x1302,
	TLS_CHACHA20_POLY1305_SHA256	= 0x1303,

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

/* ---- handshake message I/O (via /dev/tls/N/hand) ---- */

/*
 * Write one handshake message.
 * Format: type(1) || length(3) || body(length)
 */
static int
hmsgWrite(int hand, int type, uchar *body, int bodylen)
{
	uchar hdr[4];
	hdr[0] = type;
	put24(hdr+1, bodylen);
	if(kwrite(hand, hdr, 4) != 4)
		return -1;
	if(bodylen > 0 && kwrite(hand, body, bodylen) != bodylen)
		return -1;
	return 0;
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
buildClientHello(Buf *b, uchar *crandom, uchar *ks_pub, TLSconn *conn)
{
	uchar *ext_lenp, *ext_start;
	int snilen;

	bufput16(b, TLS12Legacy);	/* legacy_version */
	bufbytes(b, crandom, RandomSize);
	bufbyte(b, 0);			/* empty session_id */

	/* cipher suites */
	bufput16(b, (int)nelem(suites)*2);
	bufput16(b, TLS_AES_128_GCM_SHA256);
	bufput16(b, TLS_AES_256_GCM_SHA384);
	bufput16(b, TLS_CHACHA20_POLY1305_SHA256);

	/* null compression */
	bufbyte(b, 1);
	bufbyte(b, 0);

	/* extensions */
	ext_lenp  = b->p; bufput16(b, 0);
	ext_start = b->p;

	/* supported_versions: TLS 1.3 */
	bufput16(b, ExtSupportedVersions); bufput16(b, 3);
	bufbyte(b, 2); bufput16(b, TLS13Version);

	/* supported_groups: X25519 */
	bufput16(b, ExtSupportedGroups); bufput16(b, 4);
	bufput16(b, 2); bufput16(b, X25519group);

	/* key_share */
	bufput16(b, ExtKeyShare); bufput16(b, 2+2+2+X25519Size);
	bufput16(b, 2+2+X25519Size);		/* ClientShares length */
	bufput16(b, X25519group); bufput16(b, X25519Size);
	bufbytes(b, ks_pub, X25519Size);

	/* psk_key_exchange_modes: psk_dhe_ke */
	bufput16(b, ExtPSKKeyExchangeModes); bufput16(b, 2);
	bufbyte(b, 1); bufbyte(b, 1);

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

	/* signature_algorithms: rsa_pss_rsae_sha256 (0x0804) */
	bufput16(b, ExtSigAlgs); bufput16(b, 4);
	bufput16(b, 2); bufput16(b, 0x0804);

	put16(ext_lenp, b->p - ext_start);
}

/* ---- tlsClient ---- */

int
tlsClient(int netfd, TLSconn *conn)
{
	char id[16], path[64], errsave[ERRMAX];
	int ctl, hand, data, n, r;
	uchar crandom[RandomSize];
	uchar ks_priv[X25519Size], ks_pub[X25519Size];
	uchar dh_shared[X25519Size];
	uchar th[64];
	Buf msg;
	Suite *s;
	KeySchedule ks;
	Transcript tr;
	int suiteid;
	uchar *body;
	int bodylen, msgtype;
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

	if(ctlFmt(ctl, "fd %d 0x%x", netfd, TLS12Legacy) < 0)
		goto fail;
	if(ctlFmt(ctl, "version 0x%x", TLS12Legacy) < 0)
		goto fail;
	if(ctlFmt(ctl, "tls13 1") < 0)
		goto fail;

	/* ephemeral X25519 */
	genrandom(crandom, RandomSize);
	curve25519_dh_new(ks_priv, ks_pub);

	/* build ClientHello */
	bufinit(&msg);
	buildClientHello(&msg, crandom, ks_pub, conn);
	if(hmsgWrite(hand, HClientHello, msg.data, buflen(&msg)) < 0)
		goto fail;

	/* init transcript; we pick sha256 for now, redo if server picks sha384 */
	s = &suites[0];
	trInit(&tr, s);
	trAddMsg(&tr, HClientHello, msg.data, buflen(&msg));

	/* read ServerHello */
	body = nil;
	if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail;
	if(msgtype != HServerHello || bodylen < 2+RandomSize+1){ free(body); goto fail; }

	suiteid = 0;
	{
		uchar *p = body;
		int sidlen, comp, ext_total, ext_type, ext_len;
		uchar peer_pub[X25519Size];
		int got_ks = 0;

		p += 2;			/* skip legacy_version */
		p += RandomSize;	/* skip server_random */
		sidlen = *p++; p += sidlen;
		suiteid = get16(p); p += 2;
		comp = *p++; USED(comp);

		s = findSuite(suiteid);
		if(s == nil){ free(body); goto fail; }

		/* re-init transcript with correct hash if needed */
		if(s->hashlen == 48){
			trFree(&tr);
			trInit(&tr, s);
			trAddMsg(&tr, HClientHello, msg.data, buflen(&msg));
		}

		if(p+2 > body+bodylen){ free(body); goto fail; }
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
		if(!got_ks){ free(body); goto fail; }
		r = curve25519_dh_finish(ks_priv, peer_pub, dh_shared);
		if(!r){ free(body); goto fail; }

		trAddMsg(&tr, HServerHello, body, bodylen);
	}
	free(body); body = nil;

	/* derive handshake secrets */
	trHash(&tr, th);
	ksEarly(&ks, s, conn->psk, conn->psklen);
	ksHandshake(&ks, dh_shared, th);

	if(installKeys(ctl, s, ks.c_hs, ks.s_hs, 1) < 0) goto fail;
	if(ctlFmt(ctl, "changecipher") < 0) goto fail;


	/* read EncryptedExtensions */
	if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail;
	if(msgtype != HEncryptedExtensions){ free(body); goto fail; }
	trAddMsg(&tr, HEncryptedExtensions, body, bodylen);
	free(body); body = nil;

	/* read Certificate or Finished */
	if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail;
	if(msgtype == HCertificate){
		trAddMsg(&tr, HCertificate, body, bodylen);
		/* extract first cert DER for caller */
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
		if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail;
		if(msgtype != HCertificateVerify){ free(body); goto fail; }
		trAddMsg(&tr, HCertificateVerify, body, bodylen);
		free(body); body = nil;

		/* Finished */
		if(hmsgRead(hand, &msgtype, &body, &bodylen) < 0) goto fail;
	}
	if(msgtype != HFinished || bodylen != s->hashlen){ free(body); goto fail; }

	/* verify server Finished */
	{
		uchar pre_fin_hash[64];
		uchar expected[64];
		/*
		 * Finished verify_data = HMAC(finished_key, transcript_hash)
		 * where transcript_hash covers all messages up to but NOT
		 * including the Finished itself.  trHash() on our current
		 * state gives exactly that (we haven't added Finished yet).
		 */
		trHash(&tr, pre_fin_hash);
		computeFinished(expected, s, ks.s_hs, pre_fin_hash);
		if(tsmemcmp(body, expected, s->hashlen) != 0){
			if(conn->trace)
				conn->trace("tls13: server Finished mismatch\n");
			free(body); goto fail;
		}
	}
	trAddMsg(&tr, HFinished, body, bodylen);
	free(body); body = nil;

	/* derive master / application secrets using transcript through server Finished */
	trHash(&tr, th);
	ksMaster(&ks, th);

	/* send client Finished */
	{
		uchar cfin[64];
		/*
		 * Client finished key uses c_hs traffic secret, but verify_data
		 * is computed over transcript through server Finished (th above).
		 */
		computeFinished(cfin, s, ks.c_hs, th);
		if(hmsgWrite(hand, HFinished, cfin, s->hashlen) < 0) goto fail;
		trAddMsg(&tr, HFinished, cfin, s->hashlen);
	}

	/* switch to application keys */
	if(installKeys(ctl, s, ks.c_ap, ks.s_ap, 1) < 0) goto fail;
	if(ctlFmt(ctl, "changecipher") < 0) goto fail;  /* switches out->sec to c_ap */
	if(ctlFmt(ctl, "setin") < 0) goto fail;          /* switches in->sec to s_ap (no server CCS in TLS 1.3) */
	if(ctlFmt(ctl, "opened") < 0) goto fail;

	ok = data;
	goto done;

fail:
	/* save error now, before kclose clobbers it via devtls checkstate */
	kgerrstr(errsave, sizeof(errsave));
	kclose(data);
	ok = -1;

done:
	trFree(&tr);
	memset(&ks, 0, sizeof(ks));
	memset(ks_priv, 0, sizeof(ks_priv));
	memset(dh_shared, 0, sizeof(dh_shared));
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
