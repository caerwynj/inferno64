#include "dat.h"
#include "fns.h"
#include "error.h"
#include "audio.h"
#include <pulse/simple.h>
#include <pulse/error.h>

/*
 * PulseAudio backend for hosted emu on Linux.
 * Uses the simple API for blocking read/write streams.
 */

#define Audio_Mic_Val		1
#define Audio_Linein_Val	2

#define Audio_Speaker_Val	1
#define Audio_Headphone_Val	2
#define Audio_Lineout_Val	3

#define Audio_Pcm_Val		1
#define Audio_Ulaw_Val		2
#define Audio_Alaw_Val		3

#include "audio-tbls.c"
#define min(a,b) ((a) < (b) ? (a) : (b))

enum {
	A_Pause,
	A_UnPause,
	A_In,
	A_Out,
};

static struct {
	pa_simple *in;
	pa_simple *out;
	int pause;
	int omode;
	int open;
	QLock lk;
} afd = { .in = nil, .out = nil, .pause = A_UnPause, .omode = 0, .open = 0 };

static Audio_t av;
static QLock inlock;
static QLock outlock;

static int audio_open(int);
static int audio_pause(int);
static int audio_set_info(int);

Audio_t*
getaudiodev(void)
{
	return &av;
}

void
audio_file_init(void)
{
	audio_info_init(&av);
}

void
audio_file_open(Chan *c, int omode)
{
	USED(c);
	qlock(&afd.lk);
	if(waserror()){
		qunlock(&afd.lk);
		nexterror();
	}
	if(afd.open)
		error(Einuse);
	if(!audio_open(omode))
		error(Eio);
	poperror();
	qunlock(&afd.lk);
}

void
audio_file_close(Chan *c)
{
	USED(c);
	qlock(&afd.lk);
	if(waserror()){
		qunlock(&afd.lk);
		nexterror();
	}
	if(afd.in != nil){
		pa_simple_free(afd.in);
		afd.in = nil;
	}
	if(afd.out != nil){
		pa_simple_free(afd.out);
		afd.out = nil;
	}
	afd.open = 0;
	afd.omode = 0;
	qunlock(&afd.lk);
	poperror();
}

static int
bytes_per_frame(Audio_d *d)
{
	return (d->bits * d->chan) / Bits_Per_Byte;
}

long
audio_file_read(Chan *c, void *va, long count, vlong offset)
{
	long ba, total, chunk, bufsz;
	int paerr;
	uchar *p;

	USED(c);
	USED(offset);
	qlock(&inlock);
	if(waserror()){
		qunlock(&inlock);
		nexterror();
	}
	if(afd.in == nil)
		error(Eperm);
	ba = bytes_per_frame(&av.in);
	if(ba <= 0 || count % ba)
		error(Ebadarg);
	if(!audio_pause(A_UnPause))
		error(Eio);

	bufsz = av.in.buf * Audio_Max_Buf / Audio_Max_Val;
	if(bufsz <= 0)
		bufsz = ba;
	p = va;
	total = 0;
	while(total < count){
		chunk = min(bufsz, count - total);
		if(pa_simple_read(afd.in, p + total, chunk, &paerr) < 0)
			error(Eio);
		total += chunk;
	}

	poperror();
	qunlock(&inlock);
	return count;
}

long
audio_file_write(Chan *c, void *va, long count, vlong offset)
{
	long ba, total, chunk, bufsz;
	int paerr;
	uchar *p;

	USED(c);
	USED(offset);
	qlock(&outlock);
	if(waserror()){
		qunlock(&outlock);
		nexterror();
	}
	if(afd.out == nil)
		error(Eperm);
	ba = bytes_per_frame(&av.out);
	if(ba <= 0 || count % ba)
		error(Ebadarg);

	bufsz = av.out.buf * Audio_Max_Buf / Audio_Max_Val;
	if(bufsz <= 0)
		error(Ebadarg);
	p = va;
	total = 0;
	while(total < count){
		chunk = min(bufsz, count - total);
		if(pa_simple_write(afd.out, p + total, chunk, &paerr) < 0)
			error(Eio);
		total += chunk;
	}

	poperror();
	qunlock(&outlock);
	return count;
}

long
audio_ctl_write(Chan *c, void *va, long count, vlong offset)
{
	Audio_t tmpav = av;
	int need_in, need_out;

	USED(c);
	USED(offset);
	tmpav.in.flags = 0;
	tmpav.out.flags = 0;

	if(!audioparse(va, count, &tmpav))
		error(Ebadarg);

	if(!canqlock(&inlock))
		error("device busy");
	if(waserror()){
		qunlock(&inlock);
		nexterror();
	}
	if(!canqlock(&outlock))
		error("device busy");
	if(waserror()){
		qunlock(&outlock);
		nexterror();
	}

	need_in = (tmpav.in.flags & AUDIO_MOD_FLAG) != 0;
	need_out = (tmpav.out.flags & AUDIO_MOD_FLAG) != 0;
	av = tmpav;
	av.in.flags = 0;
	av.out.flags = 0;

	if(afd.open){
		if(need_in && !audio_set_info(A_In))
			error(Ebadarg);
		if(need_out && !audio_set_info(A_Out))
			error(Ebadarg);
	}

	poperror();
	qunlock(&outlock);
	poperror();
	qunlock(&inlock);
	return count;
}

static int
audio_sample_spec(Audio_d *d, pa_sample_spec *ss)
{
	switch(d->enc){
	case Audio_Ulaw_Val:
		if(d->bits != 8)
			return 0;
		ss->format = PA_SAMPLE_ULAW;
		break;
	case Audio_Alaw_Val:
		if(d->bits != 8)
			return 0;
		ss->format = PA_SAMPLE_ALAW;
		break;
	case Audio_Pcm_Val:
		if(d->bits == 8)
			ss->format = PA_SAMPLE_U8;
		else if(d->bits == 16)
			ss->format = PA_SAMPLE_S16LE;
		else
			return 0;
		break;
	default:
		return 0;
	}
	if(d->chan < 1)
		return 0;
	ss->channels = d->chan;
	ss->rate = d->rate;
	return pa_sample_spec_valid(ss);
}

static void
audio_buffer_attr(Audio_d *d, pa_buffer_attr *ba, int is_input)
{
	uint32_t bufsz;

	bufsz = d->buf * Audio_Max_Buf / Audio_Max_Val;
	if(bufsz < 1024)
		bufsz = 1024;
	ba->maxlength = (uint32_t)-1;
	ba->tlength = (uint32_t)-1;
	ba->minreq = (uint32_t)-1;
	ba->prebuf = (uint32_t)-1;
	ba->fragsize = (uint32_t)-1;
	if(is_input)
		ba->fragsize = bufsz;
	else
		ba->tlength = bufsz;
}

static int
pulse_new(pa_simple **ps, pa_stream_direction_t dir, Audio_d *d, char *stream_name)
{
	pa_sample_spec ss;
	pa_buffer_attr ba;
	int paerr;

	if(!audio_sample_spec(d, &ss))
		return 0;
	audio_buffer_attr(d, &ba, dir == PA_STREAM_RECORD);
	*ps = pa_simple_new(nil, "inferno-emu", dir, nil, stream_name, &ss, nil, &ba, &paerr);
	if(*ps == nil)
		return 0;
	return 1;
}

static int
audio_set_info(int d)
{
	pa_simple **ps;
	Audio_d *ad;
	pa_stream_direction_t dir;

	if(d == A_In){
		ps = &afd.in;
		ad = &av.in;
		dir = PA_STREAM_RECORD;
	}else{
		ps = &afd.out;
		ad = &av.out;
		dir = PA_STREAM_PLAYBACK;
	}
	if(*ps == nil)
		return 1;
	pa_simple_free(*ps);
	*ps = nil;
	return pulse_new(ps, dir, ad, d == A_In ? "record" : "playback");
}

static int
audio_open(int omode)
{
	if(omode == OREAD || omode == ORDWR){
		if(!pulse_new(&afd.in, PA_STREAM_RECORD, &av.in, "record"))
			goto fail;
	}
	if(omode == OWRITE || omode == ORDWR){
		if(!pulse_new(&afd.out, PA_STREAM_PLAYBACK, &av.out, "playback"))
			goto fail;
	}
	afd.omode = omode;
	afd.open = 1;
	return 1;

fail:
	if(afd.in != nil){
		pa_simple_free(afd.in);
		afd.in = nil;
	}
	if(afd.out != nil){
		pa_simple_free(afd.out);
		afd.out = nil;
	}
	return 0;
}

static int
audio_pause(int f)
{
	int paerr;

	if(afd.pause == f)
		return 1;
	if(f == A_Pause && afd.out != nil)
		(void)pa_simple_drain(afd.out, &paerr);
	afd.pause = f;
	return 1;
}
