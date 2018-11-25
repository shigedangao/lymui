//
//  deserializer.c
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <node_api.h>
#include "deserializer.h"
#include "binding_util.h"
#include "binding_error.h"
#include "deserializer_opts.h"

/**
 * @brief return an enum based on the input string
 * @param str char array
 * @return OType
 */
static OType strToOTypeEnum(char *str) {
    char *type[] = {"hex", "hsl", "hsv", "cymk", "ycbcr", "yuv" ,"xyz"};
    uint8_t idx = 0;
    size_t size = 7;
    OType t = hsl;
    
    if (str == NULL) {
        return t;
    }
    
    while(idx < size) {
        if (!strcmp(str, type[idx])) {
            t = idx;
            idx = size + 1;
        }
        idx++;
    }
    
    return t;
}

/**
 * @brief Is Hex
 * @param type char array
 * @return uint8_t
 */
static uint8_t isHex(char *type) {
    if (type == NULL) {
        return 0;
    }
    
    if (!strcmp("hex", type)) {
        return 1;
    }
    
    return 0;
}

/**
 * @brief get the validation props for validating the input color
 * @param o OType
 * @return char *
 */
static char *getValidationPropsFromOType(OType o) {
    switch (o) {
        case cymk:
            return CMYK_PROPS;
        case hsl:
            return HSL_PROPS;
        case hsv:
            return HSV_PROPS;
        case ycbcr:
            return YCBCR_PROPS;
        case yuv:
            return YUV_PROPS;
        case xyz:
            return XYZ_PROPS;
        default:
            return NULL;
    }
}

BridgeObj *deserialize(napi_env env, napi_value obj) {
    BridgeObj *br = malloc(sizeof(BridgeObj));
    if (br == NULL) {
        return NULL;
    }
    
    char *inputProps = "input:output";
    napi_value params[2];
    
    if (!hasPropInJSObj(env, obj, inputProps, CONVERT_BASIC_LEN)) {
        br->error = ARG_NB_ERR;
        return br;
    }
    
    // retrieve the param of the function
    getNamedPropArray(env, inputProps, obj, CONVERT_BASIC_LEN, params);
    if (!hasPropInJSObj(env, params[0], RGB_PROPS, MIN_LEN_TYPE)) {
        br->error = ARG_TYPE_ERR;
        return br;
    }
    
    char *type = getStringValue(env, params[1], MAX_LEN_TYPE);
    if (type == NULL) {
        br->error = CONVERT_ERR;
        return br;
    }
    
    // set the struct
    br->color  = params[0];
    br->output = strToOTypeEnum(type);
    br->error  = NULL;
    br->matrix = NULL;
    br->clamp  = 0.0;

    OptField *opt = getOptField(env, obj, "profile");
    if (opt == NULL) {
        return br;
    }
    
    if (opt->has) {
        char *value = getStringValue(env, opt->field, MAX_LEN_TYPE);
        br->matrix = value;
    }
    
    OptField *clamp = getOptField(env, obj, "clamp");
    if (clamp == NULL) {
        return br;
    }
    
    if (clamp->has) {
        double clampValue = getDoubleValue(env, clamp->field);
        br->clamp = clampValue;
    }
    
    free(opt);
    
    return br;
}

BridgeObj *normalize(napi_env env, napi_value obj) {
    uint8_t hex = 0;
    BridgeObj *br = malloc(sizeof(BridgeObj));
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
    hex = isHex(type);
    OType o = strToOTypeEnum(type);
    
    br->color  = params[0];
    br->output = o;
    br->error  = NULL;
    br->matrix = NULL;
    
    // Special case for the HEX format as it doesn't have any object
    // We test if the type is Hex and if correct we then forward to the converter
    if (hex) {
        return br;
    }
    
    // add an other step of validation
    char *validation = getValidationPropsFromOType(o);
    if (validation == NULL) {
        br->error = ARG_TYPE_ERR;
        return br;
    }
    
    if (!hasPropInJSObj(env, params[0], validation, MIN_LEN_TYPE)) {
        br->error = ARG_TYPE_ERR;
        return br;
    }

    OptField *profile = getOptField(env, obj, "profile");
    if (profile == NULL) {
        return br;
    }
    
    if (profile->has) {
        char *value = getStringValue(env, profile->field, MAX_LEN_TYPE);
        br->matrix = value;
    }
    
    return br;
}
