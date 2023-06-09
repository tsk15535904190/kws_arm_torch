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

 /*
  * Description: Keyword spotting example code using MFCC feature extraction
  * and neural network.
  */

#include "kws_mfcc.hpp"

KWS_MFCC::KWS_MFCC(int record_win)
{
	recording_win = record_win;
	init_mfcc();
}

KWS_MFCC::KWS_MFCC(const int16_t* audio_data_buffer)
{
	recording_win = NUM_FRAMES;
	audio_buffer = audio_data_buffer;
	init_mfcc();
}

KWS_MFCC::~KWS_MFCC()
{
	delete mfcc;
	delete mfcc_buffer;
}

void KWS_MFCC::init_mfcc()
{
	num_mfcc_features = NUM_MFCC_COEFFS;
	num_frames = NUM_FRAMES;
	frame_len = FRAME_LEN;
	frame_shift = FRAME_SHIFT;

	mfcc_buffer_size = 0;
	mfcc_buffer_head = 0;

	mfcc = new MFCC(num_mfcc_features, frame_len);
	mfcc_buffer = new float[num_frames * num_mfcc_features];
	audio_block_size = recording_win * frame_shift;
	audio_buffer_size = audio_block_size + frame_len - frame_shift;
}
