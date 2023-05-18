import onnxruntime
import sys
import numpy as np
import pyaudio
import time

sys.path.append('..')
from tools.mfcc import KWS_MFCC
model_fp32 = "best_model.onnx"
session = onnxruntime.InferenceSession(model_fp32, None)
data_out = ["none","one","two","three","four","five"]

CHUNK = 16000
STEP = 0.3
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 16000
RECORD_SECONDS = 1
p = pyaudio.PyAudio()
pa = pyaudio.PyAudio()

stream = p.open(format=FORMAT,
                channels=CHANNELS,
                rate=RATE,
                input=True,
                frames_per_buffer=CHUNK)
stream_out = pa.open(format=FORMAT,
                 channels=CHANNELS,
                 rate=RATE,
                 output=True)

def softmax(x):
    x = x.reshape(-1)
    e_x = np.exp(x - np.max(x))
    return e_x / e_x.sum(axis=0)
def postprocess(result):
    return np.around(softmax(np.array(result)).tolist(), 3)
data_buffer = stream.read(CHUNK) 
data_buffer = np.frombuffer(data_buffer, dtype=np.int16) 
print(data_buffer.shape)
while True:
    data = stream.read(int(CHUNK*STEP))
    stream_out.write(data)
    data = np.frombuffer(data, dtype=np.int16)
    data_buffer = np.roll(data_buffer,-int(CHUNK*STEP))
    data_buffer[CHUNK-int(CHUNK*STEP):CHUNK] = data[0:int(CHUNK*STEP)]
    kws = KWS_MFCC(data_buffer)
    input_data = kws.extract_features().reshape(49, 10)
    input_data = input_data.astype(np.float32)
    input_data = np.expand_dims(input_data, axis=(0, 1))
    raw_result = session.run([], {'input': input_data})
    
    result = postprocess(raw_result)
    result_index = np.argmax(raw_result)
    if(result_index!=0 and result[result_index] == 1):
        print(data_out[result_index])
stream.stop_stream()  # 关闭资源
stream.close()
