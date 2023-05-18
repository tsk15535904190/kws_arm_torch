#include "mfcc.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static mfcc_t my_mfcc = {0};

static  float  MelScale(float freq) {
    return 1127.0f * logf (1.0f + freq / 700.0f);
}

static  float  InverseMelScale(float mel_freq) {
    return 700.0f * (expf (mel_freq / 1127.0f) - 1.0f);
}
void mfcc_init(int num_mfcc_features, int frame_len)
{

    my_mfcc.num_mfcc_features = num_mfcc_features;
    my_mfcc.frame_len = frame_len;

	my_mfcc.frame_len_padded = pow(2, ceil((log(my_mfcc.frame_len) / log(2))));
    //printf("my_mfcc.frame_len_padded:%d\r\n",my_mfcc.frame_len_padded);

	my_mfcc.frame = malloc(my_mfcc.frame_len_padded*sizeof(fft_type));
    //printf("%d\r\n",my_mfcc.frame_len_padded*sizeof(fft_type));

	my_mfcc.buffer = malloc(my_mfcc.frame_len_padded*sizeof(float));

	my_mfcc.mel_energies = malloc(NUM_FBANK_BINS*sizeof(float));

	// create window function
	my_mfcc.window_func = malloc(my_mfcc.frame_len*sizeof(float));
	for (int i = 0; i < my_mfcc.frame_len; i++)
		my_mfcc.window_func[i] = 0.5 - 0.5 * cos(M_2PI * ((float)i) / (my_mfcc.frame_len));

	// create mel filterbank
    my_mfcc.fbank_filter_first = malloc(NUM_FBANK_BINS*sizeof(int32_t));
    my_mfcc.fbank_filter_last = malloc(NUM_FBANK_BINS*sizeof(int32_t));
    my_mfcc.mel_fbank = create_mel_fbank();

	// create DCT matrix
    my_mfcc.dct_matrix = create_dct_matrix(NUM_FBANK_BINS, my_mfcc.num_mfcc_features);
	
#ifdef __ARM_ARCH
    // initialize FFT
	my_mfcc.rfft = malloc(sizeof(arm_rfft_fast_instance_f32));
    arm_rfft_fast_init_f32(my_mfcc.rfft, my_mfcc.frame_len_padded);
#endif
}
float *create_dct_matrix(int32_t input_length, int32_t coefficient_count)
{
    int32_t k, n;
	float *M = malloc(input_length * coefficient_count*sizeof(float));
    float normalizer;
#ifdef __ARM_ARCH
    arm_sqrt_f32(2.0 / (float)input_length, &normalizer);
#else
    normalizer = sqrtf(2.0 / (float)input_length);
#endif
    for (k = 0; k < coefficient_count; k++)
    {
        for (n = 0; n < input_length; n++)
        {
            M[k * input_length + n] = normalizer * cos(((double)M_PI) / input_length * (n + 0.5) * k);
        }
    }
    return M;
}

static float *s_mel_fbank[NUM_FBANK_BINS];
float **create_mel_fbank()
{
    int32_t bin, i;

    int32_t num_fft_bins = my_mfcc.frame_len_padded / 2;
    float fft_bin_width = ((float)SAMP_FREQ) / my_mfcc.frame_len_padded;
    float mel_low_freq = MelScale(MEL_LOW_FREQ);
    float mel_high_freq = MelScale(MEL_HIGH_FREQ);
    float mel_freq_delta = (mel_high_freq - mel_low_freq) / (NUM_FBANK_BINS + 1);

    float *this_bin = malloc(num_fft_bins*sizeof(float));
	
    //my_mfcc.mel_fbank = (void*)malloc(NUM_FBANK_BINS*sizeof(float));//这里是一个值得注意的点
    //float **s_mel_fbank = malloc(NUM_FBANK_BINS*sizeof(float));
    
    for (bin = 0; bin < NUM_FBANK_BINS; bin++)
    {
        float left_mel = mel_low_freq + bin * mel_freq_delta;
        float center_mel = mel_low_freq + (bin + 1) * mel_freq_delta;
        float right_mel = mel_low_freq + (bin + 2) * mel_freq_delta;

        int32_t first_index = -1, last_index = -1;

        for (i = 0; i < num_fft_bins; i++)
        {
            float freq = (fft_bin_width * i); // center freq of this fft bin.
            float mel = MelScale(freq);
            this_bin[i] = 0.0;

            if (mel > left_mel && mel < right_mel)
            {
                float weight;
                if (mel <= center_mel)
                {
                    weight = (mel - left_mel) / (center_mel - left_mel);
                }
                else
                {
                    weight = (right_mel - mel) / (right_mel - center_mel);
                }
                this_bin[i] = weight;
                if (first_index == -1)
                    first_index = i;
                last_index = i;
            }
        }

        my_mfcc.fbank_filter_first[bin] = first_index;
        my_mfcc.fbank_filter_last[bin] = last_index;
        //my_mfcc.mel_fbank[bin] = malloc((last_index - first_index + 1)*sizeof(float));
        s_mel_fbank[bin] = malloc((last_index - first_index + 1)*sizeof(float));

        int32_t j = 0;
        // copy the part we care about
        for (i = first_index; i <= last_index; i++)
        {
            //my_mfcc.mel_fbank[bin][j++] = this_bin[i];
            s_mel_fbank[bin][j++] = this_bin[i];
        }
    }
    free(this_bin);
    //return my_mfcc.mel_fbank;
    return s_mel_fbank;
}

void mfcc_compute(const int16_t *audio_data, float *mfcc_out)
{
    int32_t i, j, bin;

    // TensorFlow way of normalizing .wav data to (-1, 1)
    for (i = 0; i < my_mfcc.frame_len; i++)
    {
        my_mfcc.frame[i] = (fft_type)(audio_data[i]) * 1.0 / (1 << 15);
    }
    // Fill up remaining with zeros
    memset(&my_mfcc.frame[my_mfcc.frame_len], 0, sizeof(fft_type) * (my_mfcc.frame_len_padded - my_mfcc.frame_len));

    for (i = 0; i < my_mfcc.frame_len; i++)
    {
        my_mfcc.frame[i] *= my_mfcc.window_func[i];
    }

    // Compute FFT
#ifdef __ARM_ARCH
    arm_rfft_fast_f32(my_mfcc.rfft, my_mfcc.frame, my_mfcc.buffer, 0);
#else
    #define MAX_FFT_LEN 1024 
    #define MAX_FFT_LEN_SQRT  32 
    static int ip[MAX_FFT_LEN_SQRT + 2];
    static double w[MAX_FFT_LEN];
    ip[0] = 0;

    assert(my_mfcc.frame_len_padded <= MAX_FFT_LEN);
    rdft(my_mfcc.frame_len_padded, 1, my_mfcc.frame, ip, w);

    for (i = 0; i < my_mfcc.frame_len_padded; i++)
    {
        my_mfcc.buffer[i] = (float)my_mfcc.frame[i];
    }
#endif

    // Convert to power spectrum
    // frame is stored as [real0, realN/2-1, real1, im1, real2, im2, ...]
    int32_t half_dim = my_mfcc.frame_len_padded / 2;
    float first_energy = my_mfcc.buffer[0] * my_mfcc.buffer[0],
          last_energy = my_mfcc.buffer[1] * my_mfcc.buffer[1]; // handle this special case
    for (i = 1; i < half_dim; i++)
    {
        float real = my_mfcc.buffer[i * 2], im = my_mfcc.buffer[i * 2 + 1];
        my_mfcc.buffer[i] = real * real + im * im;
    }
    my_mfcc.buffer[0] = first_energy;
    my_mfcc.buffer[half_dim] = last_energy;

    float sqrt_data;
    // Apply mel filterbanks
    for (bin = 0; bin < NUM_FBANK_BINS; bin++)
    {
        j = 0;
        float mel_energy = 0;
        int32_t first_index = my_mfcc.fbank_filter_first[bin];
        int32_t last_index = my_mfcc.fbank_filter_last[bin];
        for (i = first_index; i <= last_index; i++)
        {
#ifdef __ARM_ARCH
            arm_sqrt_f32(my_mfcc.buffer[i], &sqrt_data);
#else
            sqrt_data = sqrtf(my_mfcc.buffer[i]);
#endif
            mel_energy += (sqrt_data)*my_mfcc.mel_fbank[bin][j++];
        }
        my_mfcc.mel_energies[bin] = mel_energy;

        // avoid log of zero
        if (mel_energy == 0.0)
            my_mfcc.mel_energies[bin] = FLT_MIN;
    }

    // Take log
    for (bin = 0; bin < NUM_FBANK_BINS; bin++)
        my_mfcc.mel_energies[bin] = logf(my_mfcc.mel_energies[bin]);

    // Take DCT. Uses matrix mul.
    for (i = 0; i <my_mfcc.num_mfcc_features; i++)
    {
        float sum = 0.0;
        for (j = 0; j < NUM_FBANK_BINS; j++)
        {
            sum += my_mfcc.dct_matrix[i * NUM_FBANK_BINS + j] * my_mfcc.mel_energies[j];
        }
        mfcc_out[i] = sum;
    }
}
