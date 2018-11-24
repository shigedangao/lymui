//
//  convert_regular.h
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef convert_regular_h
#define convert_regular_h

#include <stdio.h>
#include <node_api.h>

/**
 * @brief convert a regular type RGB to an other type X
 * @param env napi_env
 * @param info napi_callback_info
 */
napi_value convertRegular(napi_env env, napi_callback_info info);

#endif /* convert_regular_h */
