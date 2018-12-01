//
//  convert_rgb.c
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "convert_rgb.h"
#include <node_api.h>
#include "binding_error.h"
#include "factory.h"
#include "deserializer.h"
#include "normalizer_rgb.h"

/**
 * @brief generate rgb object
 * @param env napi_env
 * @param bridge BridgeObj pointer
 * @return napi_value
 */
static napi_value generateRGB(napi_env env, BridgeObj *bridge) {
    // make a decorator
    switch (bridge->output) {
        case hex:
            return normalizeHex(env, bridge->color);
        case hsl:
            return normalizeHsl(env, bridge->color);
        case hsv:
            return normalizeHsv(env, bridge->color);
        case cymk:
            return normalizeCymk(env, bridge->color);
        case ycbcr:
            return normalizeYcbcr(env, bridge->color);
        case yuv:
            return normalizeYuv(env, bridge->color);
        case xyz:
            return normalizeXyz(env, bridge->color, bridge->matrix);
        default:
            return NULL;
    }
}

/**
 * JS API
 *  const rgb = async toRGB({
 *    input: {
 *      y: 0,
 *      u: 0,
 *      v: 0
 *    },
 *    type: 'yuv',
 *    profile: <optional> 'adobeRgb|srgb'
 *  })
 *
 */
napi_value toRGB(napi_env env, napi_callback_info info) {
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
    
    BridgeObj *bridge = normalize(env, argv[0]);
    if (bridge == NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, ALLOCATION_ERR));
        return promise;
    }
    
    if (bridge->error != NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, bridge->error));
        return promise;
    }
    
    JSObject = generateRGB(env, bridge);
    if (JSObject == NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, CREATE_VALUE_ERR));
        return promise;
    }
    
    napi_resolve_deferred(env, def, JSObject);
    
    return promise;
}
