//
//  convert_rgb.h
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef convert_rgb_h
#define convert_rgb_h

#include <stdio.h>
#include <node_api.h>

/**
 * @brief To RGB
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value toRGB(napi_env env, napi_callback_info info);

#endif /* convert_rgb_h */
