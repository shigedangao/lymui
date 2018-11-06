//
//  node_hex.c
//  lymui
//
//  Created by Marc Intha on 26/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "node_hex.h"
#include <stdlib.h>
#include <string.h>
#include <node_api.h>
#include "binding_error.h"
#include "binding_util.h"
#include "bridge.h"
#include "factory.h"
#include "rgb.h"
#include "hex.h"

napi_value GetHexFromRGB(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value hex;
    char * prefix = "#";
    char dest[8];
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
        return NULL;
    }
    
    if (argc < 1) {
        napi_throw_type_error(env, NULL, ARG_NB_ERR);
        return NULL;
    }
    
    Rgb * rgb = getRGBFromJSObj(env, argv[0]);
    if (rgb == NULL) {
        napi_throw_error(env, NULL, PROP_NOT_FOUND_ERR);
        return NULL;
    }
    
    char * hexValue = getHexFromRGB(rgb);
    
    // we don't need the RGB struct anymore
    free(rgb);
    
    strncpy(dest, prefix, BUFFER_SIZE - 1);
    strncat(dest, hexValue, BUFFER_SIZE - strlen(dest) - 1);

    // create the hex
    status = napi_create_string_utf8(env, dest, strlen(dest), &hex);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, CREATE_VALUE_ERR);
    }
    
    free(hexValue);
    return hex;
}

napi_value GetRGBFromHex(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value object;
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
        return NULL;
    }
    
    if (argc < 1) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
        return NULL;
    }
    
    char * hex = getHEXFromJSObj(env, argv[0]);
    Rgb * rgb = getRawRGBValueFromHex(hex);
    // create a new js object
    object = RgbJSObjFactory(env, rgb);
    
    free(rgb);
    return object;
}
