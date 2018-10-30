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
    }
    
    if (argc < 1) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
    }
    
    // we don't check the status as the value is optional
    napi_get_value_int32(env, argv[1], &clampValue);

    // @TODO if rgb is NULL then return a black RGB Object
    Rgb * rgb = getRGBFromJSObj(env, argv[0]);
    Cymk * cymk = getCymkFromRgb(rgb, clampValue);
    
    if (cymk == NULL) {
        napi_throw_error(env, NULL, CONVERSION_ERR);
    }
    
    status = napi_create_object(env, &jsObj);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    
    double c = floatToDouble(cymk->c, clampValue);
    double y = floatToDouble(cymk->y, clampValue);
    double m = floatToDouble(cymk->m, clampValue);
    double k = floatToDouble(cymk->k, clampValue);
    // assign the cymk object
    assignPropToJSObj(&jsObj, env, numberFloat, "c", &c);
    assignPropToJSObj(&jsObj, env, numberFloat, "y", &y);
    assignPropToJSObj(&jsObj, env, numberFloat, "m", &m);
    assignPropToJSObj(&jsObj, env, numberFloat, "k", &k);
    
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
    }
    
    if (argc < 1) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
    }
    
    // retrieve the Cymk object
    Cymk * cymk = getCymkFromJSObj(env, argv[0]);
    
    if (cymk == NULL) {
        napi_throw_error(env, NULL, CONVERSION_ERR);
        return NULL;
    }
    
    Rgb * rgb = getRawRGBValueFromCymk(cymk);
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
        return NULL;
    }
    // assign the value
    assignPropToJSObj(&object, env, numberInt, "r", &rgb->r);
    assignPropToJSObj(&object, env, numberInt, "g", &rgb->g);
    assignPropToJSObj(&object, env, numberInt, "b", &rgb->b);
    
    free(cymk);
    free(rgb);
    return object;
}
