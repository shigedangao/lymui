//
//  node_ycbcr.c
//  lymui
//
//  Created by Marc Intha on 31/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "node_ycbcr.h"
#include <stdlib.h>
#include <node_api.h>
#include "binding_error.h"
#include "binding_util.h"
#include "factory.h"
#include "bridge.h"

napi_value GetYcbcrFromRGB(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value object;
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_type_error(env, NULL, DESERIALIZE_ERR);
    }
    
    if (argc < 1) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
    }
    
    Rgb * rgb = getRGBFromJSObj(env, argv[0]);
    Ycbcr * ycb = getYcbcrFromRgb(rgb);
    
    object = YcbcrJSObjFactory(env, ycb);
    free(ycb);
    return object;
}

napi_value GetRgbFromYcbcr(napi_env env, napi_callback_info info) {
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
    
    Ycbcr * ycb = getYcbcrFromJSObj(env, argv[0]);
    Rgb * rgb = getRawRGBValueFromYcbcr(ycb);
    
    // @TODO create a RGB JS Object factory
    object = RgbJSObjFactory(env, rgb);
    
    free(rgb);
    free(ycb);
    return object;
}
