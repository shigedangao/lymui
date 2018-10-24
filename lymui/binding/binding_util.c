//
//  binding_util.c
//  lymui
//
//  Created by Marc Intha on 24/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "binding_util.h"
#include <node_api.h>
#include <string.h>
#include "binding_error.h"

void assignPropToJSObj(napi_value * jsObj, napi_env env, JSType t, char * name, void * arg) {
    napi_value value;
    napi_status status;
    
    if (t == numberInt) {
        uint8_t v = *(uint8_t *) arg;
        status = napi_create_uint32(env, v, &value);
    } else {
        char * v = (char *) arg;
        status = napi_create_string_utf8(env, v, strlen(v), &value);
    }
    
    if (status != napi_ok) {
        napi_throw_error(env, (char *) convertErrNo, CONVERT_ERR);
    }

    status = napi_set_named_property(env, *jsObj, name, value);

    if (status != napi_ok) {
        napi_throw_error(env, (char *) assignErrNo, ASSIGN_ERR);
    }
}
