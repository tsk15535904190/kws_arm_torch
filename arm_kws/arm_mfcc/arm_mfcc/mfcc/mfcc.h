#ifndef __MFCC_H__
#define __MFCC_H__


#ifdef __ARM_ARCH
  #include "arm_math.h"

  typedef float fft_type;
#else
  #include "fft.h"

  #include <math.h>

  typedef double fft_type;
#endif


#include <string.h>
#include <stdint.h>

#define SAMP_FREQ 16000
#define NUM_FBANK_BINS 40
#define MEL_LOW_FREQ 20
#define MEL_HIGH_FREQ 4000

#define M_2PI 6.283185307179586476925286766559005
#define FLT_MIN 1.175494351e-38F 

typedef struct MFCC
{
    int num_mfcc_features;
    int frame_len;
    int frame_len_padded;
    fft_type * frame;
    float * buffer;
    float * mel_energies;
    float * window_func;
    int32_t * fbank_filter_first;
    int32_t * fbank_filter_last;
    float ** mel_fbank;
    float * dct_matrix;
#ifdef __ARM_ARCH
    arm_rfft_fast_instance_f32 * rfft;
#endif
}mfcc_t;

float * create_dct_matrix(int32_t input_length, int32_t coefficient_count); 
float ** create_mel_fbank();

void mfcc_init(int num_mfcc_features, int frame_len);
void mfcc_compute(const int16_t* data, float* mfcc_out);

#endif