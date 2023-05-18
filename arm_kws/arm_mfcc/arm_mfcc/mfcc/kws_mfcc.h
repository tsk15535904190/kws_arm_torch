#ifndef __KWS_MFCC_H__
#define __KWS_MFCC_H__

#include "mfcc.h"

#define SAMP_FREQ 16000
#define SAMP_LEN_MS	1000
#define MFCC_DEC_BITS 1
#define FRAME_SHIFT_MS 20
#define FRAME_SHIFT ((int16_t)(SAMP_FREQ * 0.001 * FRAME_SHIFT_MS))
#define NUM_MFCC_COEFFS 10
#define FRAME_LEN_MS 40
#define NUM_FRAMES (1 + (SAMP_LEN_MS - FRAME_LEN_MS) / FRAME_SHIFT_MS) // 1+(1000-40)/20 = 1+960/20=1+48=49
#define FRAME_LEN ((int16_t)(SAMP_FREQ * 0.001 * FRAME_LEN_MS))
#define MFCC_BUFFER_SIZE (NUM_FRAMES * NUM_MFCC_COEFFS)

typedef struct KWS_MFCC
{
    const int16_t* audio_buffer;
    float *mfcc_buffer;
    int num_frames;
    int num_mfcc_features;
    int frame_len;
    int frame_shift;
    int audio_block_size;
    int audio_buffer_size;

    int mfcc_buffer_size;
    int recording_win;
    int mfcc_buffer_head;
}kws_mfcc_t;

void KWS_MFCC_init(void);
float *KWS_MFCC_compte(const int16_t* audio_data_buffer);
float *KWS_extract_features();
void KWS_store_u8_features(uint8_t* out_data);










#endif
