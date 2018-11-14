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
#include "factory.h"

static napi_value getColorSpaceJSObj(napi_env env, ColorBridge * b) {
    // Create the Object for each type
    switch(b->c) {
        case lab:
            return LabJSObjFactory(env, b->color);
        case lch:
            return LchJSObjFactory(env, b->color);
        case argb:
            return ArgbJSObjFactory(env, b->color);
        case spaceRgb:
            return SrgbJSObjFactory(env, b->color);
        case luv:
            return LuvJSObjFactory(env, b->color);
        default:
            return LabJSObjFactory(env, b->color);
    }
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
    object = getColorSpaceJSObj(env, b);
    return object;
}
