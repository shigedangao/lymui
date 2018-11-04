//
//  node_hsl.h
//  lymui
//
//  Created by Marc Intha on 04/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef node_hsl_h
#define node_hsl_h

#include <stdio.h>
#include <node_api.h>

/**
 * @brief retrieve a hsl object from a rgb object
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value GetHslFromRGB(napi_env env, napi_callback_info info);

/**
 * @brief retrieve a rgb object from a hsl object
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value GetRGBFromHsl(napi_env env, napi_callback_info info);

#endif /* node_hsl_h */
