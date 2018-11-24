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
#include "xyz.h"

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

/**
 * @brief convert a napi_value to an uint8_t type
 * @param env napi_env
 * @param v napi_value
 * @return uint8_t
 */
uint8_t getUintValue(napi_env env, napi_value v);

/**
 * @brief retrive the float from a napi_value
 * @param env napi_env
 * @param v napi_value
 * @return float
 */
float getFloatValue(napi_env env, napi_value v);

/**
 * @brief Retrieve string value from a napi_value
 * @param env napi_env
 * @param v napi_value
 * @param size size_t
 */
char * getStringValue(napi_env env, napi_value v, size_t size);

/**
 * @brief check if the args has the property within the JS Object
 * @param env napi_env
 * @param v napi_value
 * @param name * char
 * @param len size_t
 * @return uint8_t (0|1) Boolean
 */
uint8_t hasPropInJSObj(napi_env env, napi_value v, char * name, size_t len);

/**
 * @brief convert a float to a double by taking into account the clamp value
 * @param value float
 * @param clamp int
 * @return double
 */
double floatToDouble(float value, int clamp);

/**
 * @brief Return an enum from the string
 * @param enumStr * char
 * @return Matrix enum
 */
Matrix getEnumFromStr(char * enumStr);

#endif /* binding_util_h */
