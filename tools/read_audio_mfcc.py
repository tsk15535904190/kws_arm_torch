import numpy as np
from mfcc import KWS_MFCC

audio_name = "background"
all_num = 2001   #索引到2000
for index in range(1,all_num):
    audio_np_str = "../audio/np_"+audio_name+"/"+audio_name+"_ ("+str(index)+").npy"
    temp_data = np.load(audio_np_str)
    kws = KWS_MFCC(temp_data)
    mfccFeatures = kws.extract_features()
    u8MfccFeatures = kws.extract_uint8_features()
    audio_np_mfcc_str = "../audio/np_"+audio_name+"_mfcc/"+str(index)+".npy"
    np.save(audio_np_mfcc_str, mfccFeatures)
    audio_np_mfcc_str = "../audio/np_"+audio_name+"_mfcc/"+"u8_"+str(index)+".npy"
    np.save(audio_np_mfcc_str, u8MfccFeatures)
    print(index)

