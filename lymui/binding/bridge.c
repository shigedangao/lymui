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

char * getHEXFromJSObj(napi_env env, napi_value obj) {
    napi_status status;
    size_t hexLen;
    char * hex = malloc(sizeof(char) * HEX_SIZE + 1);
    
    status = napi_get_value_string_utf8(env, obj, hex, HEX_SIZE + 1, &hexLen);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    char * unslashHex = malloc(sizeof(char) * HEX_SIZE);
    strncpy(unslashHex, hex + 1, 7);
    unslashHex[7] = '\0';
    
    free(hex);
    return unslashHex;
}

Cymk * getCymkFromJSObj(napi_env env, napi_value obj) {
    napi_status status;
    napi_value c, y, m, k;
    char * prop = malloc(sizeof(char) * CymkPropLen);
    prop[0] = 'c';
    prop[1] = 'y';
    prop[2] = 'm';
    prop[3] = 'k';
    
    uint8_t hasProp = hasPropInJSObj(env, obj, prop, CymkPropLen);
    if (!hasProp) {
        napi_throw_error(env, NULL, PROP_FOUND_ERR);
        // usually it's not necessary to return NULL but in this case idk why it is needed...
        // The napi_throw_error throw but does not stop the execution which is strange...
        return NULL;
    }
    
    status = napi_get_named_property(env, obj, "c", &c);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "y", &y);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "m", &m);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "k", &k);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    
    Cymk * cymkSt = malloc(sizeof(Cymk));
    cymkSt->c = getFloatValue(env, c);
    cymkSt->y = getFloatValue(env, y);
    cymkSt->m = getFloatValue(env, m);
    cymkSt->k = getFloatValue(env, k);
    
    return cymkSt;
}
