//
//  factory.c
//  lymui
//
//  Created by Marc Intha on 01/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "factory.h"
#include <node_api.h>
#include "binding_error.h"
#include "binding_util.h"
#include "rgb.h"

napi_value RgbJSObjFactory(napi_env env, Rgb * rgb) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    
    // assign the value
    assignPropToJSObj(&object, env, numberInt, "r", &rgb->r);
    assignPropToJSObj(&object, env, numberInt, "g", &rgb->g);
    assignPropToJSObj(&object, env, numberInt, "b", &rgb->b);
    
    return object;
}
