#ifndef KISS_FTR_H
#define KISS_FTR_H

#include "kiss_fft.h"
#ifdef __cplusplus
extern "C" {
#endif

/*

 Real optimized version can save about 45% cpu time vs. complex fft of a real
 seq.



 */

typedef struct codec2_kiss_fftr_state *codec2_kiss_fftr_cfg;

codec2_kiss_fftr_cfg codec2_kiss_fftr_alloc(int nfft, int inverse_fft, void * mem,
                                            size_t * lenmem);
/*
 nfft must be even

 If you don't care to allocate space, use mem = lenmem = NULL
*/

void codec2_kiss_fftr(codec2_kiss_fftr_cfg cfg, const codec2_kiss_fft_scalar *timedata,
                      codec2_kiss_fft_cpx *freqdata);
/*
 input timedata has nfft scalar points
 output freqdata has nfft/2+1 complex points
*/

void codec2_kiss_fftri(codec2_kiss_fftr_cfg cfg, const codec2_kiss_fft_cpx *freqdata,
                       codec2_kiss_fft_scalar *timedata);
/*
 input freqdata has  nfft/2+1 complex points
 output timedata has nfft scalar points
*/

#define codec2_kiss_fftr_free free

#ifdef __cplusplus
}
#endif
#endif
