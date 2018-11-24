//
//  deserializer_space.c
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "deserializer_space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <node_api.h>
#include "binding_error.h"
#include "binding_util.h"

/**
 * @brief return an enum based on the input string
 * @param str char array
 * @return OSpaceType
 */
static OSpaceType strToOSpaceTypeEnum(char *str) {
    char *type[] = {"xxyz", "lab", "lch", "lchlab", "luv", "argb", "Srgb"};
    uint8_t idx = 0;
    size_t size = 8;
    OSpaceType t = xxyz;
    
    while(idx < size) {
        if (!strcmp(str, type[idx])) {
            t = idx;
            idx = size + 1;
        }
        idx++;
    }
    
    return t;
}

BridgeSpaceObj *deserializeSpace(napi_env env, napi_value obj) {
    BridgeSpaceObj *br = malloc(sizeof(BridgeSpaceObj));
    if (br == NULL) {
        return NULL;
    }
    
    char *inputProps = "input:output";
    napi_value params[2];
    
    if (!hasPropInJSObj(env, obj, inputProps, CONVERT_BASIC_LEN)) {
        br->error = ARG_NB_ERR;
        return br;
    }
    
    getNamedPropArray(env, inputProps, obj, CONVERT_BASIC_LEN, params);
    if (!hasPropInJSObj(env, params[0], XYZ_PROPS, MIN_LEN_TYPE)) {
        br->error = ARG_TYPE_ERR;
        return br;
    }
    
    char *type = getStringValue(env, params[1], MAX_LEN_TYPE);
    if (type == NULL) {
        br->error = CONVERT_ERR;
        return br;
    }
    
    br->color  = params[0];
    br->output = strToOSpaceTypeEnum(type);
    br->error  = NULL;
    
    return br;
}

BridgeSpaceObj *normalizeSpace(napi_env env, napi_value obj) {
    BridgeSpaceObj *br = malloc(sizeof(BridgeSpaceObj));
    if (br == NULL) {
        return NULL;
    }
    
    char *inputProps = "input:type";
    napi_value params[2];
    
    if (!hasPropInJSObj(env, obj, inputProps, CONVERT_BASIC_LEN)) {
        br->error = ARG_NB_ERR;
        return br;
    }
    
    getNamedPropArray(env, inputProps, obj, CONVERT_BASIC_LEN, params);
    char *type = getStringValue(env, params[1], MAX_LEN_TYPE);
    if (type == NULL) {
        br->error = CONVERT_ERR;
        return br;
    }
    
    br->color  = params[0];
    br->output = strToOSpaceTypeEnum(type);
    br->error  = NULL;
    
    return br;
}
