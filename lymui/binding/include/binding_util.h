//
//  binding_util.h
//  lymui
//
//  Created by Marc Intha on 24/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef binding_util_h
#define binding_util_h

#include <stdio.h>
#include <node_api.h>

/**
 * @brief Enum struct that represent some JavaScript type. Note in JS int and float use the same type we just separate the 2 values for usability purposes
 */
typedef enum JSType {
    numberInt,
    numberFloat,
    string
} JSType;

/**
 *  @brief assign any kind of property to a JS Object
 *  @param jsObj pointer napi_value
 *  @param env napi_env
 *  @param t JSType
 *  @param name pointer char
 *  @param value any
 */
void assignPropToJSObj(napi_value *jsObj, napi_env env, JSType t, char * name, void *value);

#endif /* binding_util_h */
