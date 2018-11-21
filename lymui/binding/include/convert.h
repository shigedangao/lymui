//
//  convert.h
//  lymui
//
//  Created by Marc Intha on 13/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef convert_h
#define convert_h

#include <stdio.h>
#include <node_api.h>

/**
 * @brief convert API for all the color space
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value convert(napi_env env, napi_callback_info info);

#endif /* convert_h */
