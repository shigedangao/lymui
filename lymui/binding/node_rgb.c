//
//  node_rgb.c
//  lymui
//
//  Created by Marc Intha on 24/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <node_api.h>
#include <stdlib.h>
#include "rgb.h"
#include "binding_error.h"
#include "binding_util.h"
#include "node_rgb.h"

napi_value GenerateRGB(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, (char *) deserializeErrNo, DESERIALIZE_ERR);
    }
    
    uint32_t r = 0;
    uint32_t g = 0;
    uint32_t b = 0;
    
    status = napi_get_value_uint32(env, argv[0], &r);
    if (status != napi_ok) {
        napi_throw_type_error(env, (char *) parseErrNo , PARSE_ERR);
    }
    
    status = napi_get_value_uint32(env, argv[1], &g);
    if (status != napi_ok) {
        napi_throw_type_error(env, (char *) parseErrNo, PARSE_ERR);
    }
    
    status = napi_get_value_uint32(env, argv[1], &b);
    if (status != napi_ok) {
        napi_throw_type_error(env, (char *) parseErrNo, PARSE_ERR);
    }
    
    uint8_t * arr = malloc(sizeof(uint8_t) * 3);
    arr[0] = r;
    arr[1] = g;
    arr[2] = b;
    
    Rgb * rgbStruct = makeRGB(arr, 3);
    napi_value JSObj;
    
    assignPropToJSObj(&JSObj, env, numberInt, "R", rgbStruct->r);
    assignPropToJSObj(&JSObj, env, numberInt, "G", rgbStruct->g);
    assignPropToJSObj(&JSObj, env, numberInt, "B", rgbStruct->b);

    return JSObj;
}
