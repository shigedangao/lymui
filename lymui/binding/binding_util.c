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
        napi_throw_error(env, NULL, CONVERT_ERR);
    }

    status = napi_set_named_property(env, *jsObj, name, value);

    if (status != napi_ok) {
        napi_throw_error(env, NULL, ASSIGN_ERR);
    }
}

uint8_t isTypeOf(napi_env env, napi_value v, JSType t) {
    napi_valuetype type;
    napi_status status;
    
    status = napi_typeof(env, v, &type);
    
    if (status != napi_ok) {
        napi_throw_error(env, NULL, PARSE_ERR);
    }
    
    // might not be super performant...
    if (type == napi_number &&
        (t == numberInt ||
        t == numberFloat)) {
        return 1;
    }
    
    if (type == napi_string && t == string) {
        return 1;
    }
    
    return 0;
}

uint8_t getUintValue(napi_env env, napi_value v) {
    napi_status status;
    uint32_t res = 0;
    
    status = napi_get_value_uint32(env, v, &res);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, CREATE_TYPE_ERR);
    }
    
    return (uint8_t) res;
}

uint8_t hasPropInJSObj(napi_env env, napi_value v, char * name, size_t len) {
    napi_status status;
    uint8_t idx = 0;
    uint8_t res = 1;
    
    while(idx < len) {
        bool present;
        // convert a char to a string...
        char str[2];
        str[0] = name[idx];
        str[1] = '\0';
        
        status = napi_has_named_property(env, v, str, &present);
        if (status != napi_ok || !present) {
            res = 0;
            idx = len + 1;
        }
        
        idx++;
    }
    
    return res;
}
