//
//  node_xyz.c
//  lymui
//
//  Created by Marc Intha on 09/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "node_xyz.h"
#include <stdlib.h>
#include <node_api.h>
#include "binding_error.h"
#include "bridge.h"
#include "rgb.h"
#include "xyz.h"

napi_value GetXyzFromRGB(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value object;
    char * matrix = malloc(sizeof(char) * XYZ_MATRIX_LEN + 1);
    size_t res;
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
        return NULL;
    }
    
    if (argc < 2) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
        return NULL;
    }
    
    status = napi_get_value_string_utf8(env, argv[1], matrix, XYZ_MATRIX_LEN + 1, &res);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, PARSE_ERR);
    }
    
    Rgb * rgb = getRGBFromJSObj(env, argv[0]);
}
