//
//  binding_util.c
//  lymui
//
//  Created by Marc Intha on 24/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "binding_util.h"
#include "binding_error.h"
#include <node_api.h>
#include <string.h>

void assignPropToJSObj(napi_value *jsObj, napi_env env, JSType t, char * name, void *value) {
    napi_value jsVal;
    napi_status s;
    
    if (t == numberInt) {
        uint8_t v = (uintptr_t) value;
        s = napi_create_uint32(env, v, &jsVal);
    } else if (t == string) {
        char * v = (char *) value;
        s = napi_create_string_utf8(env, v, strlen(v), &jsVal);
    }
    
    
    if (s != napi_ok) {
        napi_throw_error(env, (char *) convertErrNo, CONVERT_ERR);
    }
    
    s = napi_set_named_property(env, *jsObj, name, jsVal);
    
    if (s != napi_ok) {
        napi_throw_error(env, (char *) assignErrNo, ASSIGN_ERR);
    }
}
