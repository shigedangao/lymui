//
//  convert.c
//  lymui
//
//  Created by Marc Intha on 13/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "convert_space.h"
#include <node_api.h>
#include "binding_error.h"
#include "bridge.h"
#include "deserializer_space.h"
#include "factory.h"

static napi_value generateColorSpaceJSObj(napi_env env, BridgeSpaceObj *bridge) {
    Xyz *xyz = getXyzFromJSObj(env, bridge->color);
    if (xyz == NULL) {
        return NULL;
    }
    
    // Create the Object for each type
    switch(bridge->output) {
        case lab:
            return LabJSObjFactory(env, xyz);
        case lch:
            return LchJSObjFactory(env, xyz);
        case lchlab:
            return LchLabJSObjFactory(env, xyz);
        case argb:
            return ArgbJSObjFactory(env, xyz);
        case srgb:
            return SrgbJSObjFactory(env, xyz);
        case luv:
            return LuvJSObjFactory(env, xyz);
        default:
            return NULL;
    }
}

/**
 * JS API
 * const luv = async convertSpace({
 *   input: {
 *     x: 0.50,
 *     y: 1.0,
 *     z: 0.98
 *   },
 *   output: 'lab'
 * })
 *
 */
napi_value convert(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value promise;
    napi_value JSObject;
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
    
    BridgeSpaceObj *bridge = deserialize(env, argv[0]);
    if (bridge == NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, CREATE_VALUE_ERR));
        return promise;
    }
    
    JSObject = generateColorSpaceJSObj(env, bridge);
    if (JSObject == NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, CREATE_VALUE_ERR));
        return promise;
    }
    
    napi_resolve_deferred(env, def, JSObject);
    
    
    return promise;
}
