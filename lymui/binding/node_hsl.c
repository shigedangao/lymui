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
    size_t argc = 1;
    napi_value argv[1];
    napi_value object;
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
        return NULL;
    }
    
    if (argc < 1) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
        return NULL;
    }
    
    Rgb * rgb = getRGBFromJSObj(env, argv[0]);
    if (rgb == NULL) {
        napi_throw_error(env, NULL, PROP_NOT_FOUND_ERR);
        return NULL;
    }
    
    Hsl * hsl = getHslFromRgb(rgb);
    
    // percentage
    object = HslJSObjFactory(env, hsl, PERCENT_CLAMP_VALUE);
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
        return NULL;
    }
    
    if (argc < 1) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
        return NULL;
    }
    
    Hsl * hsl = getHslFromJSObj(env, argv[0]);
    if (hsl == NULL) {
        napi_throw_error(env, NULL, PROP_NOT_FOUND_ERR);
        return NULL;
    }
    
    Rgb * rgb = getRgbValueFromHsl(hsl);
    
    object = RgbJSObjFactory(env, rgb);
    free(rgb);
    
    return object;
}
