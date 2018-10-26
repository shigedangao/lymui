//
//  bridge.c
//  lymui
//
//  Created by Marc Intha on 26/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "bridge.h"
#include <stdlib.h>
#include <node_api.h>
#include "binding_error.h"
#include "binding_util.h"
#include "rgb.h"

Rgb * getRGBFromJSObj(napi_env env, napi_value obj) {
    napi_status status;
    napi_value r, g, b;
    
    // trying to retreive the value
    status = napi_get_named_property(env, obj, "r", &r);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, PROP_FOUND_ERR);
    }
    
    status = napi_get_named_property(env, obj, "g", &g);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, PROP_FOUND_ERR);
    }
    
    status = napi_get_named_property(env, obj, "b", &b);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, PROP_FOUND_ERR);
    }
    
    // convert the data to the wanted type
    uint8_t red = getUintValue(env, r);
    uint8_t green = getUintValue(env, g);
    uint8_t blue = getUintValue(env, b);
    uint8_t arr[] = {red, green, blue};
    
    Rgb * rgb = makeRGB(arr, sizeof(arr));
    
    return rgb;
}
