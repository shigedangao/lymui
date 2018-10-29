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
    size_t argc = 1;
    napi_value argv[1];
    napi_value jsObj;
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    if (argc < 1) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
    }
    
    // @TODO if rgb is NULL then return a black RGB Object
    Rgb * rgb = getRGBFromJSObj(env, argv[0]);
    Cymk * cymk = getCymkFromRgb(rgb);
    
    if (cymk == NULL) {
        napi_throw_error(env, NULL, CONVERSION_ERR);
    }
    
    status = napi_create_object(env, &jsObj);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    
    // assign the cymk object
    assignPropToJSObj(&jsObj, env, numberFloat, "c", &cymk->c);
    assignPropToJSObj(&jsObj, env, numberFloat, "y", &cymk->y);
    assignPropToJSObj(&jsObj, env, numberFloat, "m", &cymk->m);
    assignPropToJSObj(&jsObj, env, numberFloat, "k", &cymk->k);
    
    free(rgb);
    return jsObj;
}
