//
//  bridge.h
//  lymui
//
//  Created by Marc Intha on 26/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef bridge_h
#define bridge_h

#include <stdio.h>
#include <node_api.h>
#include "rgb.h"

#define RgbPropLen 3

/**
 * @brief Extract an RGB Object from a JS Object
 * @param env napi_env
 * @param args napi_value
 * @return rgb struct pointer
 */
Rgb * getRGBFromJSObj(napi_env env, napi_value args);

#endif /* bridge_h */
