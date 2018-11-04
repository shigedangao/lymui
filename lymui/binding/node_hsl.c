//
//  node_hsl.c
//  lymui
//
//  Created by Marc Intha on 04/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "node_hsl.h"
#include <stdlib.h>
#include <node_api.h>
#include "binding_error.h"
#include "binding_util.h"
#include "bridge.h"
#include "factory.h"
#include "hsl.h"

napi_value GetHslFromRGB(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value object;
    int clamp = MIN_CLAMP_VALUE;
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    if (argc < 1) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
    }
    
    clamp = napi_get_value_int32(env, argv[1], &clamp);
    Rgb * rgb = getRGBFromJSObj(env, argv[0]);
    Hsl * hsl = getHslFromRgb(rgb);
    
    object = HslJSObjFactory(env, hsl, clamp);
    free(hsl);
    
    return object;
}

napi_value GetRGBFromHsl(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value object;
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    if (argc < 1) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
    }
    
    Hsl * hsl = getHslFromJSObj(env, argv[0]);
    Rgb * rgb = getRgbValueFromHsl(hsl);
    
    object = RgbJSObjFactory(env, rgb);
    free(rgb);
    
    return object;
}
