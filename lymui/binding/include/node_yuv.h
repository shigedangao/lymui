//
//  node_yuv.h
//  lymui
//
//  Created by Marc Intha on 06/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef node_yuv_h
#define node_yuv_h

#include <stdio.h>
#include <node_api.h>
#include "yuv.h"

/**
 * @brief Retrieve YUV JS Object from RGB JS Object
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value GetYuvFromRGB(napi_env env, napi_callback_info info);

/**
 * @brief Retrieve JS RGB Object from YUV JS Object
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value GetRGBFromYuv(napi_env env, napi_callback_info info);

#endif /* node_yuv_h */
