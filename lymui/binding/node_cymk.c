//
//  node_cymk.c
//  lymui
//
//  Created by Marc Intha on 29/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "node_cymk.h"
#include <stdlib.h>
#include <node_api.h>
#include "binding_error.h"
#include "binding_util.h"
#include "bridge.h"
#include "factory.h"
#include "rgb.h"
#include "cymk.h"

napi_value GetCymkFromRgb(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value jsObj;
    int clampValue = 1000;
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
        return NULL;
    }
    
    if (argc < 1) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
        return NULL;
    }
    
    // we don't check the status as the value is optional
    napi_get_value_int32(env, argv[1], &clampValue);

    // @TODO if rgb is NULL then return a black RGB Object
    Rgb * rgb = getRGBFromJSObj(env, argv[0]);
    if (rgb == NULL) {
        napi_throw_error(env, NULL, PROP_NOT_FOUND_ERR);
        return NULL;
    }
    
    Cymk * cymk = getCymkFromRgb(rgb, clampValue);
    if (cymk == NULL) {
        napi_throw_error(env, NULL, CONVERSION_ERR);
    }
    
    jsObj = CymkJSObjFactory(env, cymk, clampValue);
    free(rgb);
    
    return jsObj;
}

napi_value GetRgbFromCymk(napi_env env, napi_callback_info info) {
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
    
    // retrieve the Cymk object
    Cymk * cymk = getCymkFromJSObj(env, argv[0]);
    if (cymk == NULL) {
        napi_throw_error(env, NULL, PROP_NOT_FOUND_ERR);
        return NULL;
    }
    
    Rgb * rgb = getRawRGBValueFromCymk(cymk);
    object = RgbJSObjFactory(env, rgb);
    
    free(cymk);
    free(rgb);
    return object;
}
