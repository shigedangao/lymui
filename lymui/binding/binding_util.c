//
//  binding_util.c
//  lymui
//
//  Created by Marc Intha on 24/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "binding_util.h"
#include <stdlib.h>
#include <math.h>
#include <node_api.h>
#include <string.h>
#include "binding_error.h"

void assignPropToJSObj(napi_value * jsObj, napi_env env, JSType t, char *name, void *arg) {
    napi_value value;
    napi_status status;
    
    if (t == numberInt) {
        uint8_t v = *(uint8_t *) arg;
        status = napi_create_uint32(env, v, &value);
    } else if (t == numberDouble) {
        double v = *(double *) arg;
        status = napi_create_double(env, (double) v, &value);
    } else {
        char * v = (char *) arg;
        status = napi_create_string_utf8(env, v, strlen(v), &value);
    }
    
    if (status != napi_ok) {
        return;
    }

    status = napi_set_named_property(env, *jsObj, name, value);
    if (status != napi_ok) {
        return;
    }
}

void assignJSObjtoJSObj(napi_env env, napi_value *target, napi_value src, char *name) {
    napi_status status;
    
    status = napi_set_named_property(env, *target, name, src);
    if (status != napi_ok) {
        return;
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
        (t == numberInt || t == numberDouble)) {
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

double getDoubleValue(napi_env env, napi_value v) {
    napi_status status;
    double res = 0;
    
    status = napi_get_value_double(env, v, &res);
    if (status != napi_ok) {
        return 0.0;
    }
    
    return res;
}

char *getStringValue(napi_env env, napi_value v, size_t strLen) {
    napi_status status;
    char * str = malloc(sizeof(char) * strLen);
    size_t len;
    
    status = napi_get_value_string_utf8(env, v, str, strLen + 1, &len);
    if (status != napi_ok) {
        return NULL;
    }
    
    return str;
}

uint8_t hasPropInJSObj(napi_env env, napi_value v, char *name, size_t len) {
    napi_status status;
    uint8_t idx = 0;
    uint8_t res = 1;
    const char delimiter[] = ":";
    char * running = strdup(name);
    char * string;
    
    while(idx < len) {
        bool present;
        // convert a char to a string...
        string = strsep(&running, delimiter);
        status = napi_has_named_property(env, v, string, &present);
        if (status != napi_ok || !present) {
            res = 0;
            idx = len + 1;
        }
        
        idx++;
    }
    
    return res;
}

double clampValue(double value, double clamp) {
    if (!clamp) {
        return value;
    }
    
    return round(value * clamp) / clamp;
}

Matrix getEnumFromStr(char *enumStr) {
    if (enumStr == NULL) {
        return srgb;
    }

    if (!strcmp(enumStr, "adobe")) {
        return adobeRgb;
    }
    
    return srgb;
}

void getNamedPropArray(napi_env env, char * name, napi_value obj, size_t len, napi_value * res) {
    uint8_t idx = 0;
    napi_status status;
    const char delimiter[] = ":";
    char * running = strdup(name);
    char * string;
    
    while(idx < len) {
        string = strsep(&running, delimiter);
        status = napi_get_named_property(env, obj, string, &res[idx]);
        if (status != napi_ok) {
            idx = len + 1;
            napi_throw_error(env, NULL, DESERIALIZE_ERR);
        }
        
        idx++;
    }
}
