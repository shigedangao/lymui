//
//  convert.c
//  lymui
//
//  Created by Marc Intha on 13/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "convert.h"
#include <node_api.h>
#include "binding_error.h"
#include "bridge.h"

static napi_value getColorSpaceJSObj(ColorBridge * b) {
    napi_value object;
    
    // Create the Object for each type
    switch(b->c) {
        case nLch:
            break;
        case nLab:
            break;
        case nArgb:
            break;
        case nRgb:
            break;
        case nLuv:
            break;
    }
    
    return object;
}

napi_value convert(napi_env env, napi_callback_info info) {
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
    
    ColorBridge * b = getColorSpaceData(env, argv[0]);
    if (b->color == NULL) {
        return NULL;
    }
    
    // Make a switch where it output a napi_value
    
    return object;
}
