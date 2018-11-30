//
//  convert_xyz.c
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "convert_xyz.h"
#include <node_api.h>
#include "binding_error.h"
#include "factory.h"
#include "deserializer_space.h"
#include "normalizer_xyz.h"

/**
 * @brief generate xyz object
 * @param env napi_env
 * @param bridge BridgeSpaceObj pointer
 * @return napi_value
 */
static napi_value generateXYZ(napi_env env, BridgeSpaceObj *bridge) {
    switch (bridge->output) {
        case lab:
            return normalizeLab(env, bridge->color, bridge->clamp);
        case lch:
            return normalizeLch(env, bridge->color, bridge->clamp);
        case llab:
            return normalizeLchLab(env, bridge->color, bridge->clamp);
        case luv:
            return normalizeLuv(env, bridge->color, bridge->clamp);
        case xyy:
            return normalizeXyy(env, bridge->color, bridge->clamp);
        case Srgb:
            return normalizeSRgb(env, bridge->color, bridge->clamp);
        default:
            return NULL;
    }
}

napi_value toXYZ(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value promise;
    napi_deferred def;
    napi_value JSObject;
    
    status = napi_create_promise(env, &def, &promise);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, PROMISE_ERR);
        return NULL;
    }
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_reject_deferred(env, def, BuildPromiseError(env, CB_INFO_ERR));
        return promise;
    }
    
    if (argc < 1) {
        napi_reject_deferred(env, def, BuildPromiseError(env, ARG_NB_ERR));
        return promise;
    }
    
    BridgeSpaceObj *bridge = normalizeSpace(env, argv[0]);
    if (bridge == NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, ALLOCATION_ERR));
        return promise;
    }
    
    if (bridge->error != NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, bridge->error));
        return promise;
    }
    
    JSObject = generateXYZ(env, bridge);
    if (JSObject == NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, CREATE_VALUE_ERR));
        return promise;
    }
    
    napi_resolve_deferred(env, def, JSObject);
    
    return promise;
}
