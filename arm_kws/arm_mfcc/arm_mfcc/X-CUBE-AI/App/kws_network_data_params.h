/**
  ******************************************************************************
  * @file    kws_network_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    Tue Jan 17 17:02:09 2023
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef KWS_NETWORK_DATA_PARAMS_H
#define KWS_NETWORK_DATA_PARAMS_H
#pragma once

#include "ai_platform.h"

/*
#define AI_KWS_NETWORK_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_kws_network_data_weights_params[1]))
*/

#define AI_KWS_NETWORK_DATA_CONFIG               (NULL)


#define AI_KWS_NETWORK_DATA_ACTIVATIONS_SIZES \
  { 48640, }
#define AI_KWS_NETWORK_DATA_ACTIVATIONS_SIZE     (48640)
#define AI_KWS_NETWORK_DATA_ACTIVATIONS_COUNT    (1)
#define AI_KWS_NETWORK_DATA_ACTIVATION_1_SIZE    (48640)



#define AI_KWS_NETWORK_DATA_WEIGHTS_SIZES \
  { 179480, }
#define AI_KWS_NETWORK_DATA_WEIGHTS_SIZE         (179480)
#define AI_KWS_NETWORK_DATA_WEIGHTS_COUNT        (1)
#define AI_KWS_NETWORK_DATA_WEIGHT_1_SIZE        (179480)



#define AI_KWS_NETWORK_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_kws_network_activations_table[1])

extern ai_handle g_kws_network_activations_table[1 + 2];



#define AI_KWS_NETWORK_DATA_WEIGHTS_TABLE_GET() \
  (&g_kws_network_weights_table[1])

extern ai_handle g_kws_network_weights_table[1 + 2];


#endif    /* KWS_NETWORK_DATA_PARAMS_H */
