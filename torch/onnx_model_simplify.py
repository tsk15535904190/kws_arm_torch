import onnx
from onnxsim import simplify
import onnxoptimizer

input_path = "best_model.onnx"
output_path = "best_model_simplify.onnx"
onnx_model = onnx.load(input_path)  # load onnx model
model_simp, check = simplify(onnx_model)
assert check, "Simplified ONNX model could not be validated"
onnx.save(model_simp, output_path)

new_model = onnxoptimizer.optimize(model_simp)
onnx.save(new_model,'best_model_simplify_optimize.onnx')
