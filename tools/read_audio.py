import wave
import numpy as np
import matplotlib.pyplot as plt

audio_name = "five"
len = 16000
save_index = 1
print("start.")
for index in range(1,2300):
    audio_str = "../audio/"+audio_name+"/audio_"+audio_name+"_ ("+str(index)+").wav"
    wav_file = wave.open(audio_str,"rb")
    params = wav_file.getparams()
    nchannels, sampwidth, framerate, nframes = params[:4]
    if len == nframes:
        str_audio_data = wav_file.readframes(nframes)
        wave_data = np.frombuffer(str_audio_data,dtype=np.short)
        np.save("../audio/np_"+audio_name+"/"+str(save_index)+".npy", wave_data)
        save_index +=1
    wav_file.close()
print("end.")

# time=range(nframes)
# plt.plot(time,wave_data)
# plt.show()