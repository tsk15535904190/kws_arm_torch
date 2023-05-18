#include "kws_mfcc.h"
#include "mfcc.h"
#include <stdlib.h>
#include <stdio.h>
kws_mfcc_t my_kws_mfcc = {0};
void KWS_MFCC_init(void)
{
	my_kws_mfcc.recording_win = NUM_FRAMES;

	my_kws_mfcc.num_mfcc_features = NUM_MFCC_COEFFS;
	my_kws_mfcc.num_frames = NUM_FRAMES;
	my_kws_mfcc.frame_len = FRAME_LEN;
	my_kws_mfcc.frame_shift = FRAME_SHIFT;

	my_kws_mfcc.mfcc_buffer_size = 0;
	my_kws_mfcc.mfcc_buffer_head = 0;

	mfcc_init(my_kws_mfcc.num_mfcc_features, my_kws_mfcc.frame_len);
	my_kws_mfcc.mfcc_buffer = malloc(my_kws_mfcc.num_frames * my_kws_mfcc.num_mfcc_features*sizeof(float));

	my_kws_mfcc.audio_block_size = my_kws_mfcc.recording_win * my_kws_mfcc.frame_shift;
	my_kws_mfcc.audio_buffer_size = my_kws_mfcc.audio_block_size + my_kws_mfcc.frame_len - my_kws_mfcc.frame_shift;
}	
float *KWS_MFCC_compte(const int16_t* audio_data_buffer)
{
	my_kws_mfcc.audio_buffer = audio_data_buffer;
	return KWS_extract_features();
}
float *KWS_extract_features()
{
	for (int f = 0; f < my_kws_mfcc.recording_win; f++)
	{
		mfcc_compute(my_kws_mfcc.audio_buffer + (f * my_kws_mfcc.frame_shift), &my_kws_mfcc.mfcc_buffer[my_kws_mfcc.mfcc_buffer_head]);
		my_kws_mfcc.mfcc_buffer_head = (my_kws_mfcc.mfcc_buffer_head + my_kws_mfcc.num_mfcc_features) % MFCC_BUFFER_SIZE;
	}
	return my_kws_mfcc.mfcc_buffer;
//	for (int i = 0; i < NUM_FRAMES; i++) {
//		for (int j = 0; j < NUM_MFCC_COEFFS; j++) {
//			printf("%.3f ", my_kws_mfcc.mfcc_buffer[i * NUM_MFCC_COEFFS + j]);
//		}
//			printf(" -%d\n",i);
//	}
}

void KWS_store_u8_features(uint8_t* out_data)
{
	float tmp;
	float min = -247.0f;
	float max = 30.0f;
	for (int i = 0; i < MFCC_BUFFER_SIZE; i++)
	{
		tmp = (255.0f * (my_kws_mfcc.mfcc_buffer[(i + my_kws_mfcc.mfcc_buffer_head) % MFCC_BUFFER_SIZE] - min)) / (max - min);
		out_data[i] = (uint8_t)round((255.0 * (my_kws_mfcc.mfcc_buffer[(i + my_kws_mfcc.mfcc_buffer_head) % MFCC_BUFFER_SIZE] - min)) / (max - min));
	}
	// for (int i = 0; i < NUM_FRAMES; i++) {
	// 	for (int j = 0; j < NUM_MFCC_COEFFS; j++) {
	// 		printf("%d ", out_data[i * NUM_MFCC_COEFFS + j]);
	// 	}
	// 		printf(" -%d\n",i);
	// }
}
