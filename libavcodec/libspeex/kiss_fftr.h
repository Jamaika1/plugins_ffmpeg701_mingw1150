#ifndef KISS_FTR_H
#define KISS_FTR_H

#include "kiss_fft.h"
#ifdef __cplusplus
extern "C" {
#endif


/*

 Real optimized version can save about 45% cpu time vs. complex fft of a real seq.



 */

typedef struct speex_kiss_fftr_state *speex_kiss_fftr_cfg;


speex_kiss_fftr_cfg speex_kiss_fftr_alloc(int nfft,int inverse_fft,void * mem, size_t * lenmem);
/*
 nfft must be even

 If you don't care to allocate space, use mem = lenmem = NULL
*/


void speex_kiss_fftr(speex_kiss_fftr_cfg cfg,const speex_kiss_fft_scalar *timedata, speex_kiss_fft_cpx *freqdata);
/*
 input timedata has nfft scalar points
 output freqdata has nfft/2+1 complex points
*/

void speex_kiss_fftr2(speex_kiss_fftr_cfg st, const speex_kiss_fft_scalar *timedata, speex_kiss_fft_scalar *freqdata);

void speex_kiss_fftri(speex_kiss_fftr_cfg cfg, const speex_kiss_fft_cpx *freqdata, speex_kiss_fft_scalar *timedata);

void speex_kiss_fftri2(speex_kiss_fftr_cfg st, const speex_kiss_fft_scalar *freqdata, speex_kiss_fft_scalar *timedata);

/*
 input freqdata has  nfft/2+1 complex points
 output timedata has nfft scalar points
*/

#define speex_kiss_fftr_free speex_free

#ifdef __cplusplus
}
#endif
#endif
