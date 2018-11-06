//
//  node_yuv.c
//  lymui
//
//  Created by Marc Intha on 06/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "node_yuv.h"
#include <stdlib.h>
#include <node_api.h>
#include "binding_error.h"
#include "bridge.h"
#include "factory.h"
#include "yuv.h"

napi_value GetYuvFromRGB(napi_env env, napi_callback_info info) {
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
    
    // retrieve the min value for clamping the float...
    napi_get_value_int32(env, argv[1], &clamp);
    
    Rgb * rgb = getRGBFromJSObj(env, argv[0]);
    Yuv * yuv = getYuvFromRgb(rgb);
    
    object = YuvJSObjFactory(env, yuv, clamp);
    free(yuv);
    
    return object;
}

napi_value GetRGBFromYuv(napi_env env, napi_callback_info info) {
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
    
    Yuv * yuv = getYuvFromJSObj(env, argv[0]);
    Rgb * rgb = getRgbFromYuv(yuv);
    
    object = RgbJSObjFactory(env, rgb);
    free(yuv);
    
    return object;
}
