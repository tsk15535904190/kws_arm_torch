import onnxruntime 
import onnx
import numpy as np
from onnxruntime.quantization import quantize_dynamic, QuantType

model_fp32 = "best_model.onnx"
model_quant = "best_model_int8.onnx"
quantized_model = quantize_dynamic(model_fp32, model_quant, weight_type=QuantType.QUInt8)

one_mfcc = np.load("mfcc_data/one_mfcc_np.npy")
two_mfcc = np.load("mfcc_data/two_mfcc_np.npy")
three_mfcc = np.load("mfcc_data/three_mfcc_np.npy")
four_mfcc = np.load("mfcc_data/four_mfcc_np.npy")
five_mfcc = np.load("mfcc_data/five_mfcc_np.npy")



def onnx_model_test(path,id):
    session = onnxruntime.InferenceSession(path, None)
    dataset = [0,one_mfcc,two_mfcc,three_mfcc,four_mfcc,five_mfcc]
    a = 0
    for index in range(1700,2000):
        input_data = dataset[id][index]
        input_data = input_data.astype(np.float32) 
        input_data = np.expand_dims(input_data, axis=(0,1))
        raw_result = session.run([], {'input': input_data})
        result = np.argmax(raw_result)
        if(result==id):
            a+=1
    print("success:",a/300*100,"%")
onnx_model_test(model_fp32,5)
#onnx_model_test(model_quant,2)