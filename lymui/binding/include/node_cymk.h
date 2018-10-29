//
//  node_cymk.h
//  lymui
//
//  Created by Marc Intha on 29/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef node_cymk_h
#define node_cymk_h

#include <stdio.h>
#include <node_api.h>

/**
 * @brief generate a cymk object from an rgb object
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value GetCymkFromRgb(napi_env env, napi_callback_info info);

/**
 * @brief generate a rgb object from a cymk js object
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value GetRgbFromCymk(napi_env env, napi_callback_info info);

#endif /* node_cymk_h */
