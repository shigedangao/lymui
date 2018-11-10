//
//  node_xyz.c
//  lymui
//
//  Created by Marc Intha on 09/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "node_xyz.h"
#include <stdlib.h>
#include <string.h>
#include <node_api.h>
#include "binding_error.h"
#include "bridge.h"
#include "factory.h"
#include "rgb.h"
#include "xyz.h"

/**
 * @brief Return an enum from the string
 * @param enumStr * char
 * @return Matrix enum
 */
static Matrix getEnumFromStr(char * enumStr) {
    if (!strcmp(enumStr, "srgb")) {
        return srgb;
    }
    
    return adobeRgb;
}

napi_value GetXyzFromRGB(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value object;
    char * matrix = malloc(sizeof(char) * XYZ_MATRIX_LEN + 1);
    size_t res;
    int clamp = MIN_CLAMP_VALUE;
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
        return NULL;
    }
    
    if (argc < 2) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
        return NULL;
    }
    
    status = napi_get_value_string_utf8(env, argv[1], matrix, XYZ_MATRIX_LEN + 1, &res);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, PARSE_ERR);
    }
    
    status = napi_get_value_int32(env, argv[2], &clamp);
    
    Rgb * rgb = getRGBFromJSObj(env, argv[0]);
    if (rgb == NULL) {
        napi_throw_error(env, NULL, PROP_NOT_FOUND_ERR);
        return NULL;
    }
    
    Matrix m = getEnumFromStr(matrix);
    Xyz * xyz = generateXyzFromRgb(rgb, m);
    
    object = XyzJSObjFactory(env, xyz, clamp);
    free(xyz);
    
    return object;
}
