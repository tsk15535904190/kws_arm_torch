// mfcc_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "kws_mfcc.hpp"
#include <iostream>


#include <math.h>
using namespace std;
#include <vector>
#include <math.h>


void TestKwsMFCC(void) {
    auto f64AudBuf = std::vector<double>(16000);
    auto i16AudBuf = std::vector<int16_t>(16000);
    double freqAmp[] = { 1.0, 0, 0.52, 0, 0.25, 0, 0.12, 0, 0.032 };
    double val = 0, maxVal = -1E10;
    for (int i = 0; i < 16000; i++) {
        val = 0;
        for (int j = 0; j < sizeof(freqAmp) / sizeof(double); j++) {
            val += sin(M_2PI / 16000.0 * 4.0 * i * (j + 1)) * freqAmp[j];
        }        
        if (val > maxVal)
            maxVal = val;
        f64AudBuf[i] = val;
    }
    for (int i = 0; i < 16000; i++) {
        f64AudBuf[i] = f64AudBuf[i] / maxVal / 1.000001 / 4.0;
        i16AudBuf[i] = (int16_t)(f64AudBuf[i] * 32768);
    }
    
    auto kws = KWS_MFCC(i16AudBuf.data());
    kws.extract_features();
    auto mfccFeature = std::vector<uint8_t>(MFCC_BUFFER_SIZE);
    kws.store_u8_features(mfccFeature.data());
    for (int i = 0; i < NUM_FRAMES; i++) {
        for (int j = 0; j < NUM_MFCC_COEFFS; j++) {
            printf("%3d ", mfccFeature[i * NUM_MFCC_COEFFS + j]);
        }
        printf(" -%d\n",i);
    }

}

#include "audio_data.h"
void TestKwsMFCC_Off(void)
{
    auto i16AudBuf = std::vector<int16_t>(16000);
    memset(i16AudBuf.data(), 0, 16000 * 2);
    int audLen = sizeof(off_sample_data);
    memcpy(i16AudBuf.data(), off_sample_data, audLen);
    auto kws = KWS_MFCC(i16AudBuf.data());
    kws.extract_features();
    auto mfccFeature = std::vector<uint8_t>(MFCC_BUFFER_SIZE);
    kws.store_u8_features(mfccFeature.data());
    // for (int i = 0; i < NUM_FRAMES; i++) {
    //     for (int j = 0; j < NUM_MFCC_COEFFS; j++) {
    //         printf("%3d ", mfccFeature[i * NUM_MFCC_COEFFS + j]);
    //     }
    //     printf(" -%d\n",i);
    // }
}

int main()
{
    std::cout << "Hello World!\n";
    TestKwsMFCC_Off();
    cout << "-------------------------------------------------------" << endl;
    TestKwsMFCC();
}

