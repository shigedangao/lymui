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
#include "deserializer.h"
#include "binding_util.h"
#include "binding_error.h"
#include <node_api.h>

/**
 * @brief return an enum based on the input string
 * @param str char array
 * @return OType
 */
static OType strToOTypeEnum(char *str) {
    char *type[] = {"hex", "hsl", "hsv", "cymk", "ycbcr", "xyz"};
    uint8_t idx = 0;
    size_t size = 7;
    OType t = hex;
    
    while(idx < size) {
        if (!strcmp(str, type[idx])) {
            t = idx;
            idx = size + 1;
        }
        idx++;
    }
    
    return t;
}

OptField *getOptField(napi_env env, napi_value obj, char *field) {
    napi_status status;
    bool hasOptProp;
    napi_value optfield;
    
    OptField *opt = malloc(sizeof(OptField));
    if (opt == NULL) {
        return NULL;
    }
    
    status = napi_has_named_property(env, obj, field, &hasOptProp);
    if (status != napi_ok) {
        opt->has = false;
        return opt;
    }
    
    if (!hasOptProp) {
        opt->has = false;
        return opt;
    }
    
    status = napi_get_named_property(env, obj, field, &optfield);
    if (status != napi_ok) {
        opt->has = false;
        return opt;
    }
    
    char *value = getStringValue(env, optfield, MAX_LEN_TYPE);
    opt->field = value;
    opt->has = true;
    
    return opt;
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

    OptField *opt = getOptField(env, obj, "profile");
    if (opt == NULL) {
        return br;
    }
    
    br->matrix = opt->field;
    free(opt);
    
    return br;
}

BridgeObj *normalize(napi_env env, napi_value obj) {
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
    char *type = getStringValue(env, params[0], MAX_LEN_TYPE);
    
    br->color  = params[0];
    br->output = strToOTypeEnum(type);
    
    OptField *opt = getOptField(env, obj, "profile");
    if (opt == NULL) {
        return br;
    }
    
    br->matrix = opt->field;
    
    return br;
}