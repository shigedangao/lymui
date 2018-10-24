//
//  node_rgb.h
//  lymui
//
//  Created by Marc Intha on 24/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef node_rgb_h
#define node_rgb_h


#include <stdio.h>
#include <node_api.h>

/**
 * @description Generate an RGB pointer struct
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value GenerateRGB(napi_env env, napi_callback_info info);


#endif /* node_rgb_h */
