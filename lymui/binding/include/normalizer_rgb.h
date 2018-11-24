//
//  normalizer_rgb.h
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef normalizer_rgb_h
#define normalizer_rgb_h

#include <stdio.h>
#include <node_api.h>

/**
 * @brief normalize hex
 * @param env napi_env
 * @param color napi_value
 * @return napi_value
 */
napi_value NormalizeHEX(napi_env env, napi_value color);

/**
 * @brief normalize HSL
 * @param env napi_env
 * @param color napi_value
 * @return napi_value
 */
napi_value NormalizeHSL(napi_env env, napi_value color);

/**
 * @brief normalize HSV
 * @param env napi_env
 * @param color napi_value
 * @return napi_value
 */
napi_value NormalizeHSV(napi_env env, napi_value color);

/**
 * @brief normalize CYMK
 * @param env napi_env
 * @param color napi_value
 * @return napi_value
 */
napi_value NormalizeCYMK(napi_env env, napi_value color);

/**
 * @brief normalize YCBCR
 * @param env napi_env
 * @param color napi_value
 * @return napi_value
 */
napi_value NormalizeYCBCR(napi_env env, napi_value color);

/**
 * @brief normalize XYZ
 * @param env napi_env
 * @param color napi_value
 * @param m char
 * @return napi_value
 */
napi_value NormalizeXYZ(napi_env env, napi_value color, char *m);

#endif /* normalizer_rgb_h */
