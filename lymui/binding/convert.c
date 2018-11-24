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
    napi_value promise;
    napi_deferred def;
    
    status = napi_create_promise(env, &def, &promise);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, PROMISE_ERR);
        return NULL;
    }
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_reject_deferred(env, def, BuildPromiseError(env, DESERIALIZE_ERR));
        return promise;
    }
    
    if (argc < 1) {
        napi_reject_deferred(env, def, BuildPromiseError(env, ARG_NB_ERR));
        return promise;
    }
    
    ColorBridge * b = getColorSpaceData(env, argv[0]);
    if (b == NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, PROP_NOT_FOUND_ERR));
        return promise;
    }
    
    if (b->color == NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, CREATE_TYPE_ERR));
        return promise;
    }
    
    // Make a switch where it output a napi_value
    napi_value object = getColorSpaceJSObj(env, b);
    if (object == NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, OBJ_MAKE_ERR));
        return  promise;
    }
    
    napi_resolve_deferred(env, def, object);
    
    return promise;
}
