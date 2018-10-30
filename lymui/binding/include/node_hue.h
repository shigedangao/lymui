//
//  node_hue.h
//  lymui
//
//  Created by Marc Intha on 30/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef node_hue_h
#define node_hue_h

#include <stdio.h>
#include <node_api.h>

/**
 * @brief generate a float hue value from an RGB Object
 * @param env napi_env
 * @param info napi_callback_info
 */
napi_value GetHueFromRgb(napi_env env, napi_callback_info info);

#endif /* node_hue_h */
