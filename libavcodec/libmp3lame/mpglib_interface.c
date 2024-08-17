/* -*- mode: C; mode: fold -*- */
/*
 *      LAME MP3 encoding engine
 *
 *      Copyright (c) 1999-2000 Mark Taylor
 *      Copyright (c) 2003 Olcios
 *      Copyright (c) 2008 Robert Hegemann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/* $Id$ */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#if defined(HAVE_MPGLIB) || defined(HAVE_MPG123)
#define hip_global_struct mpstr_tag

#ifdef HAVE_MPG123

/* libmpg123 */
#include <mpg123.h>
#ifndef MPG123_API_VERSION
#error "Seems like you got the wrong mpg123 header. No MPG123_API_VERSION defined."
#endif
#if (MPG123_API_VERSION < 45)
#error "Need mpg123 API >= 45."
#endif
/* for mpstr_tag */
#include "mpglib/mpglib.h"

#else

/* mpglib */
#include "mpglib/interface.h"

#endif

#include "lame.h"
#include "machine.h"
#include "encoder.h"

/* for plotting_data */
#ifndef NOANALYSIS
#include "lame-analysis.h"
#endif

#include "util.h"

#if DEPRECATED_OR_OBSOLETE_CODE_REMOVED
/*
 * OBSOLETE:
 * - kept to let it link
 * - forward declaration to silence compiler
 */
int CDECL lame_decode_init(void);
int CDECL lame_decode(
        unsigned char *  mp3buf,
        int              len,
        short            pcm_l[],
        short            pcm_r[] );
int CDECL lame_decode_headers(
        unsigned char*   mp3buf,
        int              len,
        short            pcm_l[],
        short            pcm_r[],
        mp3data_struct*  mp3data );
int CDECL lame_decode1(
        unsigned char*  mp3buf,
        int             len,
        short           pcm_l[],
        short           pcm_r[] );
int CDECL lame_decode1_headers(
        unsigned char*   mp3buf,
        int              len,
        short            pcm_l[],
        short            pcm_r[],
        mp3data_struct*  mp3data );
int CDECL lame_decode1_headersB(
        unsigned char*   mp3buf,
        int              len,
        short            pcm_l[],
        short            pcm_r[],
        mp3data_struct*  mp3data,
        int              *enc_delay,
        int              *enc_padding );
int CDECL lame_decode_exit(void);
#endif

#ifdef HAVE_MPGLIB
static MPSTR   mp;
#endif

int
lame_decode_exit(void)
{
#ifdef HAVE_MPGLIB
    ExitMP3(&mp);
#endif
    return 0;
}


int
lame_decode_init(void)
{
#ifdef HAVE_MPGLIB
    (void) InitMP3(&mp);
#endif
    return 0;
}




/* copy mono samples */
#define COPY_MONO(DST_TYPE, SRC_TYPE)                                                           \
    DST_TYPE *pcm_l = (DST_TYPE *)pcm_l_raw;                                                    \
    SRC_TYPE const *p_samples = (SRC_TYPE const *)p;                                            \
    for (i = 0; i < processed_samples; i++)                                                     \
      *pcm_l++ = (DST_TYPE)(*p_samples++);

/* copy stereo samples */
#define COPY_STEREO(DST_TYPE, SRC_TYPE)                                                         \
    DST_TYPE *pcm_l = (DST_TYPE *)pcm_l_raw, *pcm_r = (DST_TYPE *)pcm_r_raw;                    \
    SRC_TYPE const *p_samples = (SRC_TYPE const *)p;                                            \
    for (i = 0; i < processed_samples; i++) {                                                   \
      *pcm_l++ = (DST_TYPE)(*p_samples++);                                                      \
      *pcm_r++ = (DST_TYPE)(*p_samples++);                                                      \
    }



/*
 * For lame_decode:  return code
 * -1     error
 *  0     ok, but need more data before outputing any samples
 *  n     number of samples output.  either 576 or 1152 depending on MP3 file.
 */

#ifdef HAVE_MPGLIB
static int
decode1_headersB_clipchoice(PMPSTR pmp, unsigned char *buffer, size_t len,
                            char pcm_l_raw[], char pcm_r_raw[], mp3data_struct * mp3data,
                            int *enc_delay, int *enc_padding,
                            char *p, size_t psize, int decoded_sample_size,
                            int (*decodeMP3_ptr) (PMPSTR, unsigned char *, int, char *, int,
                            int *))
{
    static const int smpls[2][4] = {
        /* Layer   I    II   III */
        {0, 384, 1152, 1152}, /* MPEG-1     */
        {0, 384, 1152, 576} /* MPEG-2(.5) */
    };

    int     processed_bytes;
    int     processed_samples; /* processed samples per channel */
    int     ret;
    int     i;
    int const len_l = len < INT_MAX ? (int) len : INT_MAX;
    int const psize_l = psize < INT_MAX ? (int) psize : INT_MAX;

    mp3data->header_parsed = 0;
    ret = (*decodeMP3_ptr) (pmp, buffer, len_l, p, psize_l, &processed_bytes);
    /* three cases:
     * 1. headers parsed, but data not complete
     *       pmp->header_parsed==1
     *       pmp->framesize=0
     *       pmp->fsizeold=size of last frame, or 0 if this is first frame
     *
     * 2. headers, data parsed, but ancillary data not complete
     *       pmp->header_parsed==1
     *       pmp->framesize=size of frame
     *       pmp->fsizeold=size of last frame, or 0 if this is first frame
     *
     * 3. frame fully decoded:
     *       pmp->header_parsed==0
     *       pmp->framesize=0
     *       pmp->fsizeold=size of frame (which is now the last frame)
     *
     */
    if (pmp->header_parsed || pmp->fsizeold > 0 || pmp->framesize > 0) {
        mp3data->header_parsed = 1;
        mp3data->stereo = pmp->fr.stereo;
        mp3data->samplerate = freqs[pmp->fr.sampling_frequency];
        mp3data->mode = pmp->fr.mode;
        mp3data->mode_ext = pmp->fr.mode_ext;
        mp3data->framesize = smpls[pmp->fr.lsf][pmp->fr.lay];

        /* free format, we need the entire frame before we can determine
         * the bitrate.  If we haven't gotten the entire frame, bitrate=0 */
        if (pmp->fsizeold > 0) /* works for free format and fixed, no overrun, temporal results are < 400.e6 */
            mp3data->bitrate = 8 * (4 + pmp->fsizeold) * mp3data->samplerate /
                (1.e3 * mp3data->framesize) + 0.5;
        else if (pmp->framesize > 0)
            mp3data->bitrate = 8 * (4 + pmp->framesize) * mp3data->samplerate /
                (1.e3 * mp3data->framesize) + 0.5;
        else
            mp3data->bitrate = tabsel_123[pmp->fr.lsf][pmp->fr.lay - 1][pmp->fr.bitrate_index];



        if (pmp->num_frames > 0) {
            /* Xing VBR header found and num_frames was set */
            mp3data->totalframes = pmp->num_frames;
            mp3data->nsamp = mp3data->framesize * pmp->num_frames;
            *enc_delay = pmp->enc_delay;
            *enc_padding = pmp->enc_padding;
        }
    }

    switch (ret) {
    case MP3_OK:
        switch (pmp->fr.stereo) {
        case 1:
            processed_samples = processed_bytes / decoded_sample_size;
            if (decoded_sample_size == sizeof(short)) {
                COPY_MONO(short, short)
            }
            else {
                COPY_MONO(sample_t, FLOAT)
            }
            break;
        case 2:
            processed_samples = (processed_bytes / decoded_sample_size) >> 1;
            if (decoded_sample_size == sizeof(short)) {
                COPY_STEREO(short, short)
            }
            else {
                COPY_STEREO(sample_t, FLOAT)
            }
            break;
        default:
            processed_samples = -1;
            assert(0);
            break;
        }
        break;

    case MP3_NEED_MORE:
        processed_samples = 0;
        break;

    case MP3_ERR:
        processed_samples = -1;
        break;

    default:
        processed_samples = -1;
        assert(0);
        break;
    }

    /*fprintf(stderr,"ok, more, err:  %i %i %i\n", MP3_OK, MP3_NEED_MORE, MP3_ERR ); */
    /*fprintf(stderr,"ret = %i out=%i\n", ret, processed_samples ); */
    return processed_samples;
}
#endif


#define OUTSIZE_CLIPPED   (4096*sizeof(short))

int
lame_decode1_headersB(unsigned char *buffer,
                      int len,
                      short pcm_l[], short pcm_r[], mp3data_struct * mp3data,
                      int *enc_delay, int *enc_padding)
{
    static char out[OUTSIZE_CLIPPED];
#ifdef HAVE_MPGLIB
    return decode1_headersB_clipchoice(&mp, buffer, len, (char *) pcm_l, (char *) pcm_r, mp3data,
                                       enc_delay, enc_padding, out, OUTSIZE_CLIPPED,
                                       sizeof(short), decodeMP3);
#else
    return -1;
#endif
}





/*
 * For lame_decode:  return code
 *  -1     error
 *   0     ok, but need more data before outputing any samples
 *   n     number of samples output.  Will be at most one frame of
 *         MPEG data.
 */

int
lame_decode1_headers(unsigned char *buffer,
                     int len, short pcm_l[], short pcm_r[], mp3data_struct * mp3data)
{
#ifdef HAVE_MPGLIB
    int     enc_delay, enc_padding;
    return lame_decode1_headersB(buffer, len, pcm_l, pcm_r, mp3data, &enc_delay, &enc_padding);
#else
    return -1;
#endif
}


int
lame_decode1(unsigned char *buffer, int len, short pcm_l[], short pcm_r[])
{
#ifdef HAVE_MPGLIB
    mp3data_struct mp3data;

    return lame_decode1_headers(buffer, len, pcm_l, pcm_r, &mp3data);
#else
    return -1;
#endif
}


/*
 * For lame_decode:  return code
 *  -1     error
 *   0     ok, but need more data before outputing any samples
 *   n     number of samples output.  a multiple of 576 or 1152 depending on MP3 file.
 */

int
lame_decode_headers(unsigned char *buffer,
                    int len, short pcm_l[], short pcm_r[], mp3data_struct * mp3data)
{
#ifdef HAVE_MPGLIB
    int     ret;
    int     totsize = 0;     /* number of decoded samples per channel */

    for (;;) {
        switch (ret = lame_decode1_headers(buffer, len, pcm_l + totsize, pcm_r + totsize, mp3data)) {
        case -1:
            return ret;
        case 0:
            return totsize;
        default:
            totsize += ret;
            len = 0;    /* future calls to decodeMP3 are just to flush buffers */
            break;
        }
    }
#else
    return -1;
#endif
}


int
lame_decode(unsigned char *buffer, int len, short pcm_l[], short pcm_r[])
{
#ifdef HAVE_MPGLIB
    mp3data_struct mp3data;

    return lame_decode_headers(buffer, len, pcm_l, pcm_r, &mp3data);
#else
    return -1;
#endif
}




hip_t hip_decode_init(void)
{
    hip_t hip = lame_calloc(hip_global_flags, 1);
    if(!hip)
        return hip;
#ifdef HAVE_MPG123
    mpg123_init();
    hip->mh = mpg123_new(NULL, NULL);
    /* Could allocate on demand only. */
    memset(&hip->mi, 0, sizeof(hip->mi));
    /* Since encoder delay/padding is communicated, I presume implicit
       handling of gapless decoding is not expected. */
    mpg123_param(hip->mh, MPG123_REMOVE_FLAGS, MPG123_GAPLESS, 0.);
    /* We are going to feed buffers. */
    if(mpg123_open_feed(hip->mh) != MPG123_OK)
    {
        mpg123_delete(hip->mh);
        free(hip);
        hip = NULL;
    }
#else
    InitMP3(hip);
#endif
    return hip;
}

hip_t hip_decode_init_gapless(void)
{
    hip_t hip = lame_calloc(hip_global_flags, 1);
    if(!hip)
        return hip;
#ifdef HAVE_MPG123
    mpg123_init();
    hip->mh = mpg123_new(NULL, NULL);
    /* Could allocate on demand only. */
    memset(&hip->mi, 0, sizeof(hip->mi));
    /* Default on, but make it explicit. */
    mpg123_param(hip->mh, MPG123_ADD_FLAGS, MPG123_GAPLESS, 0.);
    /* We are going to feed buffers. */
    if(mpg123_open_feed(hip->mh) != MPG123_OK)
    {
        mpg123_delete(hip->mh);
        free(hip);
        hip = NULL;
    }
#else
    hip = NULL;
#endif
    return hip;
}



int hip_decode_exit(hip_t hip)
{
    if(hip) {
#ifdef HAVE_MPG123
        mpg123_delete(hip->mh); /* Closes implicitly. */
        /* No mpg123_exit(), will be deprecated anyway. */
#else
        ExitMP3(hip);
#endif
        free(hip);
    }
    return 0;
}

#ifdef HAVE_MPG123
/* One decoding routine to cover all API cases. Any output pointer except pcm_l
   and pcm_r, which are always required to be able to store full MPEG frame
   (1152 samples), can be NULL if you are not really interested in it.
   This always works on one whole MPEG frame, even if sample count can be
   smaller after gapless handling. TODO: Optionally turn on gapless decoding?
   If not, the decoder delay also needs to be communicated.
   Or do we just assume 529 samples? */

int hip123_decode1( hip_t hip, unsigned char *buffer, size_t len,
    unsigned char *pcm_l, unsigned char *pcm_r,
    int *enc_delay, int *enc_padding,
    mp3data_struct *mp3data,
    int unclipped) /* If true, produce unclipped float (sample_t) output. */
{
    int ret;
    unsigned char *mpg123buf;
    size_t mpg123fill;
    long rate;
    int channels;
    int encoding;
    int change_format;
    int samples = 0;
    int want_enc = unclipped ? MPG123_ENC_FLOAT_32 : MPG123_ENC_SIGNED_16;

    if(MPG123_OK != mpg123_feed(hip->mh, buffer, len))
        return -1;
    ret = mpg123_getformat(hip->mh, &rate, &channels, &encoding);
    switch(ret) {
        case MPG123_NEED_MORE:
            return 0;
        case MPG123_OK:
            change_format = encoding != want_enc;
        break;
        default:
            return -1;
    }

    if(change_format)
    {
        mpg123_format_none(hip->mh);
        mpg123_format2(hip->mh, 0, MPG123_MONO|MPG123_STEREO, want_enc);
        /* This triggers renegotiation of output format on next decode. */
        mpg123_decoder(hip->mh, NULL);
    }

    /* Now decode for real. */
    mpg123fill = 0; /* Still zero in case of error/need more. */
    ret = mpg123_decode_frame(hip->mh, NULL, &mpg123buf, &mpg123fill);
    /* A second time if we just got notified of new format. */
    if(!mpg123fill && ret == MPG123_NEW_FORMAT)
    {
        mpg123_getformat(hip->mh, &rate, &channels, &encoding);
        ret = mpg123_decode_frame(hip->mh, NULL, &mpg123buf, &mpg123fill);
        /* True paranoia would check the encoding again. */
    }
    if(ret == MPG123_ERR)
        return -1;
    /* MPG123_NEED_MORE and MPG123_DONE (not happening here, though)
        both result in mpg123fill==0, so return 0 here, which is what fits. */
    samples = mpg123fill /
        (unclipped ? sizeof(float) : sizeof(short)) / channels;
    /* Now demultilex the data in mpg123buf into pcm_l and pcm_r. */
    if(mpg123fill && mpg123buf)
    {
        if(unclipped)
        {
            /* Lame's sample_t could be wider than 32 bit, right? */
            sample_t *spcm_l = (sample_t*)pcm_l;
            sample_t *spcm_r = (sample_t*)pcm_r;
            float    *srcbuf = (float*)mpg123buf;
            int i;

            if(channels == 2) {
                for(i=0; i<samples; ++i) {
                    spcm_l[i] = *srcbuf++;
                    spcm_r[i] = *srcbuf++;
                }
            }
            else
                for(i=0; i<samples; ++i)
                    spcm_l[i] = *srcbuf++;
        }
        else
        {
            /* It's all shorts. */
            short *spcm_l = (short*)pcm_l;
            short *spcm_r = (short*)pcm_r;
            short *srcbuf = (short*)mpg123buf;
            int i;

            if(channels == 2) {
                for(i=0; i<samples; ++i) {
                    spcm_l[i] = *srcbuf++;
                    spcm_r[i] = *srcbuf++;
                }
            }
            else
                memcpy(pcm_l, mpg123buf, sizeof(short)*samples);
        }
    }

    /* If we arrive here, there was some successful parsing of the stream at
       least, so that meaningful info is available. */
    if(mp3data) {
        struct mpg123_frameinfo fi;
        memset(mp3data, 0, sizeof(mp3data_struct));
        /* Re-using last returns from getformat() before. */
        if(MPG123_OK == mpg123_info(hip->mh, &fi)) {
            mp3data->header_parsed = 1;
            mp3data->stereo = channels; /* Channel count correct? Or is dual mono different? */
            mp3data->samplerate = rate;
            mp3data->mode = fi.mode;
            mp3data->mode_ext = fi.mode_ext;
            mp3data->framesize = mpg123_spf(hip->mh);
            mp3data->bitrate = fi.bitrate;
        }
    }
    if(enc_delay) {
        long val;
        mpg123_getstate(hip->mh, MPG123_ENC_DELAY, &val, NULL);
        *enc_delay = val > INT_MAX ? -1 : val;
    }
    if(enc_padding) {
        long val;
        mpg123_getstate(hip->mh, MPG123_ENC_PADDING, &val, NULL);
        *enc_padding = val > INT_MAX ? -1 : val;
    }
    if(hip->pinfo)
        hip_finish_pinfo(hip);
    return samples;
}
#endif


/* we forbid input with more than 1152 samples per channel for output in the unclipped mode */
#define OUTSIZE_UNCLIPPED (1152*2*sizeof(FLOAT))

int
hip_decode1_unclipped(hip_t hip, unsigned char *buffer, size_t len, sample_t pcm_l[], sample_t pcm_r[])
{
    if (hip) {
#ifdef HAVE_MPG123
        return hip123_decode1( hip, buffer, len,
            (unsigned char*)pcm_l, (unsigned char*)pcm_r,
            NULL, NULL, NULL, 1 );
#else
        mp3data_struct mp3data;
        static char out[OUTSIZE_UNCLIPPED];
        int     enc_delay, enc_padding;
        return decode1_headersB_clipchoice(hip, buffer, len, (char *) pcm_l, (char *) pcm_r, &mp3data,
                                           &enc_delay, &enc_padding, out, OUTSIZE_UNCLIPPED,
                                           sizeof(FLOAT), decodeMP3_unclipped);
#endif
    }
    return 0; /* not -1 ? */
}

/*
 * For hip_decode:  return code
 *  -1     error
 *   0     ok, but need more data before outputing any samples
 *   n     number of samples output.  Will be at most one frame of
 *         MPEG data.
 */

int
hip_decode1_headers(hip_t hip, unsigned char *buffer,
                     size_t len, short pcm_l[], short pcm_r[], mp3data_struct * mp3data)
{
#ifdef HAVE_MPG123
    return hip123_decode1( hip, buffer, len,
        (unsigned char*)pcm_l, (unsigned char*)pcm_r,
        NULL, NULL, mp3data, 0 );
#else
    int     enc_delay, enc_padding;
    return hip_decode1_headersB(hip, buffer, len, pcm_l, pcm_r, mp3data, &enc_delay, &enc_padding);
#endif
}


int
hip_decode1(hip_t hip, unsigned char *buffer, size_t len, short pcm_l[], short pcm_r[])
{
#ifdef HAVE_MPG123
    return hip123_decode1( hip, buffer, len,
        (unsigned char*)pcm_l, (unsigned char*)pcm_r,
        NULL, NULL, NULL, 0 );
#else
    mp3data_struct mp3data;
    return hip_decode1_headers(hip, buffer, len, pcm_l, pcm_r, &mp3data);
#endif
}


/*
 * For hip_decode:  return code
 *  -1     error
 *   0     ok, but need more data before outputing any samples
 *   n     number of samples output.  a multiple of 576 or 1152 depending on MP3 file.
 */

int
hip_decode_headers(hip_t hip, unsigned char *buffer,
                    size_t len, short pcm_l[], short pcm_r[], mp3data_struct * mp3data)
{
    int     ret;
    int     totsize = 0;     /* number of decoded samples per channel */

    for (;;) {
        switch (ret = hip_decode1_headers(hip, buffer, len, pcm_l + totsize, pcm_r + totsize, mp3data)) {
        case -1:
            return ret;
        case 0:
            return totsize;
        default:
            totsize += ret;
            len = 0;    /* future calls to decodeMP3 are just to flush buffers */
            break;
        }
    }
}


int
hip_decode(hip_t hip, unsigned char *buffer, size_t len, short pcm_l[], short pcm_r[])
{
    mp3data_struct mp3data;
    return hip_decode_headers(hip, buffer, len, pcm_l, pcm_r, &mp3data);
}


int
hip_decode1_headersB(hip_t hip, unsigned char *buffer,
                      size_t len,
                      short pcm_l[], short pcm_r[], mp3data_struct * mp3data,
                      int *enc_delay, int *enc_padding)
{
    if (hip) {
#ifdef HAVE_MPG123
        return hip123_decode1( hip, buffer, len,
            (unsigned char*)pcm_l, (unsigned char*)pcm_r,
            enc_delay, enc_padding, mp3data, 0);
#else
        static char out[OUTSIZE_CLIPPED];
        return decode1_headersB_clipchoice(hip, buffer, len, (char *) pcm_l, (char *) pcm_r, mp3data,
                                           enc_delay, enc_padding, out, OUTSIZE_CLIPPED,
                                           sizeof(short), decodeMP3);
#endif
    }
    return -1;
}


void hip_set_pinfo(hip_t hip, plotting_data* pinfo)
{
    if (hip) {
        hip->pinfo = pinfo;
#ifdef HAVE_MPG123
        mpg123_set_moreinfo(hip->mh, &hip->mi);
#endif
    }
}

void hip_finish_pinfo(hip_t hip)
{
#ifndef NOANALYSIS
#ifdef HAVE_MPG123
    struct mpg123_frameinfo fi;
    long rate;
    plotting_data *pinfo = hip->pinfo;
    if(!hip || !hip->pinfo)
        return;

    /* TODO: convert to pointers to avoid copies. Allocation should be
       on mpg123 side (in form of the struct definition), as that is
       the writing side. */
    memcpy(pinfo->mpg123xr, hip->mi.xr, sizeof(pinfo->mpg123xr));
    memcpy(pinfo->sfb, hip->mi.sfb, sizeof(pinfo->sfb));
    memcpy(pinfo->sfb_s, hip->mi.sfb_s, sizeof(pinfo->sfb_s));
    memcpy(pinfo->qss, hip->mi.qss, sizeof(pinfo->qss));
    memcpy(pinfo->big_values, hip->mi.big_values, sizeof(pinfo->big_values));
    memcpy(pinfo->sub_gain, hip->mi.sub_gain, sizeof(pinfo->sub_gain));
    memcpy(pinfo->scalefac_scale, hip->mi.scalefac_scale, sizeof(pinfo->scalefac_scale));
    memcpy(pinfo->preflag, hip->mi.preflag, sizeof(pinfo->preflag));
    memcpy(pinfo->mpg123blocktype, hip->mi.blocktype, sizeof(pinfo->mpg123blocktype));
    memcpy(pinfo->mixed, hip->mi.mixed, sizeof(pinfo->mixed));
    memcpy(pinfo->mainbits, hip->mi.mainbits, sizeof(pinfo->mainbits));
    memcpy(pinfo->sfbits, hip->mi.sfbits, sizeof(pinfo->sfbits));
    memcpy(pinfo->scfsi, hip->mi.scfsi, sizeof(pinfo->scfsi));
    pinfo->maindata = hip->mi.maindata;
    pinfo->padding  = hip->mi.padding;
    if(MPG123_OK == mpg123_info(hip->mh, &fi)) {
        pinfo->js = (fi.mode == MPG123_M_JOINT);
        pinfo->stereo = fi.mode == MPG123_M_MONO ? 1 : 2;
        pinfo->crc = fi.flags & MPG123_CRC ? 1 : 0;
        pinfo->emph = fi.emphasis;
        pinfo->sampfreq = fi.rate;
        pinfo->bitrate = fi.bitrate;
        pinfo->ms_stereo = pinfo->js ? (fi.mode_ext & 0x2)>>1 : 0;
        pinfo->i_stereo  = pinfo->js ? (fi.mode_ext & 0x1)    : 0;
    }
#endif
#endif
}

void hip_set_errorf(hip_t hip, lame_report_function func)
{
#ifdef HAVE_MPG123
    /* TODO: implement something */
#else
    if (hip) {
        hip->report_err = func;
    }
#endif
}

void hip_set_debugf(hip_t hip, lame_report_function func)
{
#ifdef HAVE_MPG123
    /* TODO: implement something */
#else
    if (hip) {
        hip->report_dbg = func;
    }
#endif
}

void hip_set_msgf  (hip_t hip, lame_report_function func)
{
#ifdef HAVE_MPG123
    /* TODO: implement something */
#else
    if (hip) {
        hip->report_msg = func;
    }
#endif
}

#endif

/* end of mpglib_interface.c */
