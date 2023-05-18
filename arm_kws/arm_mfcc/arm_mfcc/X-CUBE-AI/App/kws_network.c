/**
  ******************************************************************************
  * @file    kws_network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Tue Jan 17 17:02:09 2023
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "kws_network.h"
#include "kws_network_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_kws_network
 
#undef AI_KWS_NETWORK_MODEL_SIGNATURE
#define AI_KWS_NETWORK_MODEL_SIGNATURE     "48c47d921648a380f1253c708d25834e"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Tue Jan 17 17:02:09 2023"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_KWS_NETWORK_N_BATCHES
#define AI_KWS_NETWORK_N_BATCHES         (1)

static ai_ptr g_kws_network_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_kws_network_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  x_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  x_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  x_3_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  x_3_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  x_7_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  x_7_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  x_11_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  x_11_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  x_15_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  x_15_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  x_19_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)
/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  x_19_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  x_23_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)
/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  x_23_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  x_27_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)
/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  x_27_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  x_31_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)
/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  x_31_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  output_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 23040, AI_STATIC)
/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  input_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 490, AI_STATIC)
/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  output_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6, AI_STATIC)
/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  x_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)
/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  x_3_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)
/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  x_7_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)
/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  x_31_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 640, AI_STATIC)
/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  x_11_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)
/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  x_15_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)
/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  x_19_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)
/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  x_23_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)
/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  x_27_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)
/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  x_31_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3840, AI_STATIC)
/* Array#31 */
AI_ARRAY_OBJ_DECLARE(
  onnxGemm_29_to_chlast_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3840, AI_STATIC)
/* Array#32 */
AI_ARRAY_OBJ_DECLARE(
  output_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 6, AI_STATIC)
/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  x_weights, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 4, 64), AI_STRIDE_INIT(4, 4, 4, 40, 160),
  1, &x_weights_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  x_bias, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &x_bias_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  x_3_weights, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 64), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &x_3_weights_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  x_3_bias, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &x_3_bias_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  x_7_weights, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 256, 256),
  1, &x_7_weights_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  x_7_bias, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &x_7_bias_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  x_11_weights, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 64), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &x_11_weights_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  x_11_bias, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &x_11_bias_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  x_15_weights, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 256, 256),
  1, &x_15_weights_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  x_15_bias, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &x_15_bias_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  x_19_weights, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 64), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &x_19_weights_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  x_19_bias, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &x_19_bias_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  x_23_weights, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 256, 256),
  1, &x_23_weights_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  x_23_bias, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &x_23_bias_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  x_27_weights, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 64), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &x_27_weights_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  x_27_bias, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &x_27_bias_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  x_31_weights, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 256, 256),
  1, &x_31_weights_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  x_31_bias, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &x_31_bias_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  output_weights, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 3840, 6, 1, 1), AI_STRIDE_INIT(4, 4, 15360, 92160, 92160),
  1, &output_weights_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  input_output, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 10, 49), AI_STRIDE_INIT(4, 4, 4, 4, 40),
  1, &input_output_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  output_bias, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 6, 1, 1), AI_STRIDE_INIT(4, 4, 4, 24, 24),
  1, &output_bias_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  x_output, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 5, 24), AI_STRIDE_INIT(4, 4, 4, 256, 1280),
  1, &x_output_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  x_3_output, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 5, 24), AI_STRIDE_INIT(4, 4, 4, 256, 1280),
  1, &x_3_output_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  x_7_output, AI_STATIC,
  23, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 5, 24), AI_STRIDE_INIT(4, 4, 4, 256, 1280),
  1, &x_7_output_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  x_31_scratch0, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 5, 2), AI_STRIDE_INIT(4, 4, 4, 256, 1280),
  1, &x_31_scratch0_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  x_11_output, AI_STATIC,
  25, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 5, 24), AI_STRIDE_INIT(4, 4, 4, 256, 1280),
  1, &x_11_output_array, NULL)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  x_15_output, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 5, 24), AI_STRIDE_INIT(4, 4, 4, 256, 1280),
  1, &x_15_output_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  x_19_output, AI_STATIC,
  27, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 5, 24), AI_STRIDE_INIT(4, 4, 4, 256, 1280),
  1, &x_19_output_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  x_23_output, AI_STATIC,
  28, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 5, 24), AI_STRIDE_INIT(4, 4, 4, 256, 1280),
  1, &x_23_output_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  x_27_output, AI_STATIC,
  29, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 5, 24), AI_STRIDE_INIT(4, 4, 4, 256, 1280),
  1, &x_27_output_array, NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  x_31_output, AI_STATIC,
  30, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 5, 12), AI_STRIDE_INIT(4, 4, 4, 256, 1280),
  1, &x_31_output_array, NULL)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(
  onnxGemm_29_to_chlast_output, AI_STATIC,
  31, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 12, 64), AI_STRIDE_INIT(4, 4, 4, 20, 240),
  1, &onnxGemm_29_to_chlast_output_array, NULL)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(
  onnxGemm_29_to_chlast_output0, AI_STATIC,
  32, 0x0,
  AI_SHAPE_INIT(4, 1, 3840, 1, 1), AI_STRIDE_INIT(4, 4, 4, 15360, 15360),
  1, &onnxGemm_29_to_chlast_output_array, NULL)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(
  output_output, AI_STATIC,
  33, 0x0,
  AI_SHAPE_INIT(4, 1, 6, 1, 1), AI_STRIDE_INIT(4, 4, 4, 24, 24),
  1, &output_output_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  output_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxGemm_29_to_chlast_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &output_weights, &output_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  output_layer, 21,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &output_chain,
  NULL, &output_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxGemm_29_to_chlast_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_31_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxGemm_29_to_chlast_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxGemm_29_to_chlast_layer, 20,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &onnxGemm_29_to_chlast_chain,
  NULL, &output_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  x_31_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_27_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_31_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &x_31_weights, &x_31_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_31_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  x_31_layer, 19,
  OPTIMIZED_CONV2D_TYPE, 0x0, NULL,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &x_31_chain,
  NULL, &onnxGemm_29_to_chlast_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(1, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  x_27_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_23_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_27_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &x_27_weights, &x_27_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  x_27_layer, 16,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &x_27_chain,
  NULL, &x_31_layer, AI_STATIC, 
  .groups = 64, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  x_23_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_19_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_23_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &x_23_weights, &x_23_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  x_23_layer, 14,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &x_23_chain,
  NULL, &x_27_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  x_19_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_15_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_19_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &x_19_weights, &x_19_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  x_19_layer, 12,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &x_19_chain,
  NULL, &x_23_layer, AI_STATIC, 
  .groups = 64, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  x_15_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_11_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_15_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &x_15_weights, &x_15_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  x_15_layer, 10,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &x_15_chain,
  NULL, &x_19_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  x_11_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_11_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &x_11_weights, &x_11_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  x_11_layer, 8,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &x_11_chain,
  NULL, &x_15_layer, AI_STATIC, 
  .groups = 64, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  x_7_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &x_7_weights, &x_7_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  x_7_layer, 6,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &x_7_chain,
  NULL, &x_11_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  x_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &x_3_weights, &x_3_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  x_3_layer, 4,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &x_3_chain,
  NULL, &x_7_layer, AI_STATIC, 
  .groups = 64, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  x_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &x_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &x_weights, &x_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  x_layer, 2,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &x_chain,
  NULL, &x_3_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 4, 1, 4), 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 179480, 1, 1),
    179480, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 48640, 1, 1),
    48640, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_KWS_NETWORK_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_KWS_NETWORK_OUT_NUM, &output_output),
  &x_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 179480, 1, 1),
      179480, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 48640, 1, 1),
      48640, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_KWS_NETWORK_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_KWS_NETWORK_OUT_NUM, &output_output),
  &x_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool kws_network_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_kws_network_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    input_output_array.data = AI_PTR(g_kws_network_activations_map[0] + 15192);
    input_output_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 15192);
    
    x_output_array.data = AI_PTR(g_kws_network_activations_map[0] + 17152);
    x_output_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 17152);
    
    x_3_output_array.data = AI_PTR(g_kws_network_activations_map[0] + 13824);
    x_3_output_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 13824);
    
    x_7_output_array.data = AI_PTR(g_kws_network_activations_map[0] + 12544);
    x_7_output_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 12544);
    
    x_11_output_array.data = AI_PTR(g_kws_network_activations_map[0] + 9216);
    x_11_output_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 9216);
    
    x_15_output_array.data = AI_PTR(g_kws_network_activations_map[0] + 7936);
    x_15_output_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 7936);
    
    x_19_output_array.data = AI_PTR(g_kws_network_activations_map[0] + 4608);
    x_19_output_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 4608);
    
    x_23_output_array.data = AI_PTR(g_kws_network_activations_map[0] + 3328);
    x_23_output_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 3328);
    
    x_27_output_array.data = AI_PTR(g_kws_network_activations_map[0] + 0);
    x_27_output_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 0);
    
    x_31_scratch0_array.data = AI_PTR(g_kws_network_activations_map[0] + 30720);
    x_31_scratch0_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 30720);
    
    x_31_output_array.data = AI_PTR(g_kws_network_activations_map[0] + 33280);
    x_31_output_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 33280);
    
    onnxGemm_29_to_chlast_output_array.data = AI_PTR(g_kws_network_activations_map[0] + 0);
    onnxGemm_29_to_chlast_output_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 0);
    
    output_output_array.data = AI_PTR(g_kws_network_activations_map[0] + 15360);
    output_output_array.data_start = AI_PTR(g_kws_network_activations_map[0] + 15360);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool kws_network_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_kws_network_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    x_weights_array.format |= AI_FMT_FLAG_CONST;
    x_weights_array.data = AI_PTR(g_kws_network_weights_map[0] + 0);
    x_weights_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 0);
    
    x_bias_array.format |= AI_FMT_FLAG_CONST;
    x_bias_array.data = AI_PTR(g_kws_network_weights_map[0] + 10240);
    x_bias_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 10240);
    
    x_3_weights_array.format |= AI_FMT_FLAG_CONST;
    x_3_weights_array.data = AI_PTR(g_kws_network_weights_map[0] + 10496);
    x_3_weights_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 10496);
    
    x_3_bias_array.format |= AI_FMT_FLAG_CONST;
    x_3_bias_array.data = AI_PTR(g_kws_network_weights_map[0] + 12800);
    x_3_bias_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 12800);
    
    x_7_weights_array.format |= AI_FMT_FLAG_CONST;
    x_7_weights_array.data = AI_PTR(g_kws_network_weights_map[0] + 13056);
    x_7_weights_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 13056);
    
    x_7_bias_array.format |= AI_FMT_FLAG_CONST;
    x_7_bias_array.data = AI_PTR(g_kws_network_weights_map[0] + 29440);
    x_7_bias_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 29440);
    
    x_11_weights_array.format |= AI_FMT_FLAG_CONST;
    x_11_weights_array.data = AI_PTR(g_kws_network_weights_map[0] + 29696);
    x_11_weights_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 29696);
    
    x_11_bias_array.format |= AI_FMT_FLAG_CONST;
    x_11_bias_array.data = AI_PTR(g_kws_network_weights_map[0] + 32000);
    x_11_bias_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 32000);
    
    x_15_weights_array.format |= AI_FMT_FLAG_CONST;
    x_15_weights_array.data = AI_PTR(g_kws_network_weights_map[0] + 32256);
    x_15_weights_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 32256);
    
    x_15_bias_array.format |= AI_FMT_FLAG_CONST;
    x_15_bias_array.data = AI_PTR(g_kws_network_weights_map[0] + 48640);
    x_15_bias_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 48640);
    
    x_19_weights_array.format |= AI_FMT_FLAG_CONST;
    x_19_weights_array.data = AI_PTR(g_kws_network_weights_map[0] + 48896);
    x_19_weights_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 48896);
    
    x_19_bias_array.format |= AI_FMT_FLAG_CONST;
    x_19_bias_array.data = AI_PTR(g_kws_network_weights_map[0] + 51200);
    x_19_bias_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 51200);
    
    x_23_weights_array.format |= AI_FMT_FLAG_CONST;
    x_23_weights_array.data = AI_PTR(g_kws_network_weights_map[0] + 51456);
    x_23_weights_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 51456);
    
    x_23_bias_array.format |= AI_FMT_FLAG_CONST;
    x_23_bias_array.data = AI_PTR(g_kws_network_weights_map[0] + 67840);
    x_23_bias_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 67840);
    
    x_27_weights_array.format |= AI_FMT_FLAG_CONST;
    x_27_weights_array.data = AI_PTR(g_kws_network_weights_map[0] + 68096);
    x_27_weights_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 68096);
    
    x_27_bias_array.format |= AI_FMT_FLAG_CONST;
    x_27_bias_array.data = AI_PTR(g_kws_network_weights_map[0] + 70400);
    x_27_bias_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 70400);
    
    x_31_weights_array.format |= AI_FMT_FLAG_CONST;
    x_31_weights_array.data = AI_PTR(g_kws_network_weights_map[0] + 70656);
    x_31_weights_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 70656);
    
    x_31_bias_array.format |= AI_FMT_FLAG_CONST;
    x_31_bias_array.data = AI_PTR(g_kws_network_weights_map[0] + 87040);
    x_31_bias_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 87040);
    
    output_weights_array.format |= AI_FMT_FLAG_CONST;
    output_weights_array.data = AI_PTR(g_kws_network_weights_map[0] + 87296);
    output_weights_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 87296);
    
    output_bias_array.format |= AI_FMT_FLAG_CONST;
    output_bias_array.data = AI_PTR(g_kws_network_weights_map[0] + 179456);
    output_bias_array.data_start = AI_PTR(g_kws_network_weights_map[0] + 179456);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_kws_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_KWS_NETWORK_MODEL_NAME,
      .model_signature   = AI_KWS_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 2650182,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_bool ai_kws_network_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_KWS_NETWORK_MODEL_NAME,
      .model_signature   = AI_KWS_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 2650182,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_kws_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_kws_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_kws_network_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_kws_network_create(network, AI_KWS_NETWORK_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_kws_network_data_params_get(&params) != true) {
        err = ai_kws_network_get_error(*network);
        return err;
    }
#if defined(AI_KWS_NETWORK_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_KWS_NETWORK_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_kws_network_init(*network, &params) != true) {
        err = ai_kws_network_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_kws_network_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_kws_network_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_kws_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_kws_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= kws_network_configure_weights(net_ctx, params);
  ok &= kws_network_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_kws_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_kws_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_KWS_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

