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
 *  @param arg any
 */
void assignPropToJSObj(napi_value *jsObj, napi_env env, JSType t, char * name, void * arg);

/**
 *  @brief validate the type of the value
 *  @param env napi_env
 *  @param v napi_value
 *  @param t JSType
 */
uint8_t isTypeOf(napi_env env, napi_value v, JSType t);

#endif /* binding_util_h */
