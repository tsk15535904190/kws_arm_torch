/*
 * Copyright (C) 2018 Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __KWS_MFCC_H__
#define __KWS_MFCC_H__

#include "mfcc.hpp"
#include <cstdio>
#define SAMP_FREQ 16000
#define SAMP_LEN_MS	1000
#define MFCC_DEC_BITS 1
#define FRAME_SHIFT_MS 20
#define FRAME_SHIFT ((int16_t)(SAMP_FREQ * 0.001 * FRAME_SHIFT_MS))
#define NUM_MFCC_COEFFS 10
#define MFCC_BUFFER_SIZE (NUM_FRAMES * NUM_MFCC_COEFFS)
#define FRAME_LEN_MS 40
#define NUM_FRAMES (1 + (SAMP_LEN_MS - FRAME_LEN_MS) / FRAME_SHIFT_MS) // 1+(1000-40)/20 = 1+960/20=1+48=49
#define FRAME_LEN ((int16_t)(SAMP_FREQ * 0.001 * FRAME_LEN_MS))

class KWS_MFCC
{
public:
  KWS_MFCC(const int16_t* audio_data_buffer);
  KWS_MFCC(int record_win);
  ~KWS_MFCC();

  /*!
 * @brief Extracts the MFCC features from the audio_buffer based on the recording_win size
 * and moves the mfcc_buffer_head accordingly
 */
  void extract_features() {
	  /* Each iteration adds NUM_MFCC_FEATURES MFCC coefficients and moves the mfcc_buffer_head forward accordingly */
	  for (int f = 0; f < recording_win; f++)
	  {
		  mfcc->mfcc_compute(audio_buffer + (f * frame_shift), &mfcc_buffer[mfcc_buffer_head]);
		  mfcc_buffer_head = (mfcc_buffer_head + num_mfcc_features) % MFCC_BUFFER_SIZE;
	  }
    for (int i = 0; i < NUM_FRAMES; i++) {
      for (int j = 0; j < NUM_MFCC_COEFFS; j++) {
        printf("%.3f ", mfcc_buffer[i * NUM_MFCC_COEFFS + j]);
      }
        printf(" -%d\n",i);
    }
  }

  /*!
 * @brief Loads the data from the MFCC buffer, quantizes them and stores them into the inference buffer.
 * 
 * The process starts at the buffer head, traverses the end of the buffer and continues
 * from the beginning till the mfcc_buffer_head is reached again (circular buffer processing).
 *
 * @param out_data output buffer pointer
 */
  void store_u8_features(uint8_t* out_data, float min = -247.0f, float max = 30.0f) {
	  float tmp;
	  for (int i = 0; i < MFCC_BUFFER_SIZE; i++)
	  {
		  tmp = (255.0f * (mfcc_buffer[(i + mfcc_buffer_head) % MFCC_BUFFER_SIZE] - min)) / (max - min);
		  out_data[i] = (uint8_t)round((255.0 * (mfcc_buffer[(i + mfcc_buffer_head) % MFCC_BUFFER_SIZE] - min)) / (max - min));
	  }
  }

  const int16_t* audio_buffer;
  float *mfcc_buffer;
  int num_frames;
  int num_mfcc_features;
  int frame_len;
  int frame_shift;
  int audio_block_size;
  int audio_buffer_size;

protected:
  void init_mfcc();
  MFCC *mfcc;
  int mfcc_buffer_size;
  int recording_win;
  int mfcc_buffer_head;
};

#endif
