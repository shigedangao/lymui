//
//  node_hex.h
//  lymui
//
//  Created by Marc Intha on 26/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef node_hex_h
#define node_hex_h

#include <stdio.h>
#include <node_api.h>
#include "rgb.h"

#define BUFFER_SIZE 8

/**
 * @brief Generate a Hex from an RGB struct
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value GetHexFromRGB(napi_env env, napi_callback_info info);

#endif /* node_hex_h */
