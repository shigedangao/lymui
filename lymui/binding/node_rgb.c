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
    napi_value object;
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    if (argc < 3) {
        napi_throw_type_error(env, NULL, ARG_NB_ERR);
    }
    
    if (!isTypeOf(env, argv[0], numberInt) ||
        !isTypeOf(env, argv[1], numberInt) ||
        !isTypeOf(env, argv[2], numberInt)) {
        napi_throw_error(env, NULL, ARG_TYPE_ERR);
    }
    
    uint32_t r = 0;
    uint32_t g = 0;
    uint32_t b = 0;
    
    status = napi_get_value_uint32(env, argv[0], &r);
    if (status != napi_ok) {
        napi_throw_type_error(env, NULL, PARSE_ERR);
    }
    
    status = napi_get_value_uint32(env, argv[1], &g);
    if (status != napi_ok) {
        napi_throw_type_error(env, NULL, PARSE_ERR);
    }
    
    status = napi_get_value_uint32(env, argv[2], &b);
    if (status != napi_ok) {
        napi_throw_type_error(env, NULL, PARSE_ERR);
    }
    
    // creation of the RGB struct
    uint8_t * arr = malloc(sizeof(uint8_t) * 3);
    arr[0] = (uint8_t) r;
    arr[1] = (uint8_t) g;
    arr[2] = (uint8_t) b;
    Rgb * rgb = makeRGB(arr, 3);
    
    // create a new js object
    status = napi_create_object(env, &object);
    
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    // assign the value
    assignPropToJSObj(&object, env, numberInt, "r", &rgb->r);
    assignPropToJSObj(&object, env, numberInt, "g", &rgb->g);
    assignPropToJSObj(&object, env, numberInt, "b", &rgb->b);
    
    free(arr);
    free(rgb);
    
    return object;
}
