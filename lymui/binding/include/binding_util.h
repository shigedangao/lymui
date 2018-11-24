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

#define CONVERT_BASIC_LEN 2
#define MIN_LEN_TYPE 3
#define MAX_LEN_TYPE 5

/**
 * @brief Enum struct that represent some JavaScript type. Note in JS int and float use the same type we just separate the 2 values for usability purposes
 */
typedef enum JSType {
    numberInt,
    numberDouble,
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
char *getStringValue(napi_env env, napi_value v, size_t size);

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
 * @brief Return an enum from the string
 * @param enumStr * char
 * @return Matrix enum
 */
Matrix getEnumFromStr(char * enumStr);

/**
 * @brief Get the property of an object and set it on a napi_value array
 * @param env napi_env
 * @param name char array
 * @param obj napi_value
 * @param len size_t
 * @param res napi_value
 */
void getNamedPropArray(napi_env env, char *name, napi_value obj, size_t len, napi_value *res);

#endif /* binding_util_h */
