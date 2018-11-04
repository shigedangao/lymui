//
//  node_hsv.h
//  lymui
//
//  Created by Marc Intha on 04/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef node_hsv_h
#define node_hsv_h

#include <stdio.h>
#include <node_api.h>
#include "hsv.h"

/**
 * @brief generate the hsv js object from an rgb object
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value GetHsvFromRGB(napi_env env, napi_callback_info info);

/**
 * @brief generate a rgb js object from a hsv object
 */
napi_value GetRGBFromHsv(napi_env env, napi_callback_info info);

#endif /* node_hsv_h */
