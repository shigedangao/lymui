//
//  bridge.c
//  lymui
//
//  Created by Marc Intha on 26/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "bridge.h"
#include <stdlib.h>
#include <string.h>
#include <node_api.h>
#include "binding_error.h"
#include "binding_util.h"
#include "rgb.h"
#include "hex.h"

Rgb * getRGBFromJSObj(napi_env env, napi_value obj) {
    napi_status status;
    napi_value r, g, b;
    char * prop = malloc(sizeof(char) * RgbPropLen);
    prop[0] = 'r';
    prop[1] = 'g';
    prop[2] = 'b';
    
    // check if the object has the property
    uint8_t hasProp = hasPropInJSObj(env, obj, prop, RgbPropLen);
    if (!hasProp) {
        napi_throw_error(env, NULL, PROP_FOUND_ERR);
    }
    
    // trying to retreive the value
    status = napi_get_named_property(env, obj, "r", &r);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "g", &g);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "b", &b);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    // convert the data to the wanted type
    uint8_t red = getUintValue(env, r);
    uint8_t green = getUintValue(env, g);
    uint8_t blue = getUintValue(env, b);
    uint8_t arr[] = {red, green, blue};
    
    Rgb * rgb = makeRGB(arr, sizeof(arr));
    
    return rgb;
}

char * getHEXFromJSObj(napi_env env, napi_value args) {
    napi_status status;
    size_t hexLen;
    char * hex = malloc(sizeof(char) * HEX_SIZE + 1);
    
    status = napi_get_value_string_utf8(env, args, hex, HEX_SIZE + 1, &hexLen);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    char * unslashHex = malloc(sizeof(char) * HEX_SIZE);
    strncpy(unslashHex, hex + 1, 7);
    unslashHex[7] = '\0';
    
    free(hex);
    return unslashHex;
}
