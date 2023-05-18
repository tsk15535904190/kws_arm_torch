import numpy as np

one_mfcc = []
two_mfcc = []
three_mfcc = []
four_mfcc = []
five_mfcc = []
background_mfcc = []
for index in range(1, 2001):  # 将硬盘中的数据加载到内存中
    # audio_name = "one"
    # audio_np_mfcc_str = "../audio/np_"+audio_name+"_mfcc/"+str(index)+".npy"
    # one_mfcc.append(np.load(audio_np_mfcc_str).reshape(49, 10))
    # audio_name = "two"
    # audio_np_mfcc_str = "../audio/np_"+audio_name+"_mfcc/"+str(index)+".npy"
    # two_mfcc.append(np.load(audio_np_mfcc_str).reshape(49, 10))
    # audio_name = "three"
    # audio_np_mfcc_str = "../audio/np_"+audio_name+"_mfcc/"+str(index)+".npy"
    # three_mfcc.append(np.load(audio_np_mfcc_str).reshape(49, 10))
    # audio_name = "four"
    # audio_np_mfcc_str = "../audio/np_"+audio_name+"_mfcc/"+str(index)+".npy"
    # four_mfcc.append(np.load(audio_np_mfcc_str).reshape(49, 10))
    # audio_name = "five"
    # audio_np_mfcc_str = "../audio/np_"+audio_name+"_mfcc/"+str(index)+".npy"
    # five_mfcc.append(np.load(audio_np_mfcc_str).reshape(49, 10))
    audio_name = "background"
    audio_np_mfcc_str = "../audio/np_"+audio_name+"_mfcc/"+str(index)+".npy"
    background_mfcc.append(np.load(audio_np_mfcc_str).reshape(49, 10))
    print(index)

background_mfcc_np = np.array(background_mfcc)
np.save("mfcc_data/background_mfcc_np.npy", background_mfcc)
# one_mfcc_np = np.array(one_mfcc)
# np.save("mfcc_data/one_mfcc_np.npy", one_mfcc_np)

# two_mfcc_np = np.array(two_mfcc)
# np.save("mfcc_data/two_mfcc_np.npy", two_mfcc_np)

# three_mfcc_np = np.array(three_mfcc)
# np.save("mfcc_data/three_mfcc_np.npy", three_mfcc_np)

# four_mfcc_np = np.array(four_mfcc)
# np.save("mfcc_data/four_mfcc_np.npy", four_mfcc_np)

# five_mfcc_np = np.array(five_mfcc)
# np.save("mfcc_data/five_mfcc_np.npy", five_mfcc_np)