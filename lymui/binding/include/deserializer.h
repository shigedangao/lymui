//
//  deserializer.h
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef deserializer_h
#define deserializer_h

#include <stdio.h>
#include <node_api.h>

#define RGB_PROPS "r:g:b"
#define CMYK_PROPS "c:y:m:k"
#define HSL_PROPS "h:s:l"
#define HSV_PROPS "h:s:v"
#define YCBCR_PROPS "y:cb:cr"
#define YUV_PROPS "y:u:v"
#define XYZ_PROPS "x:y:z"

/**
 * @brief define the supported output by the based deserializer
 */
typedef enum Output {
    hex,
    hsl,
    hsv,
    cymk,
    ycbcr,
    yuv,
    xyz
} OType;

/**
 * @brief structure which will be used to calculate other value
 */
typedef struct BridgeObj {
    napi_value color;
    OType output;
    char *matrix;
    char *error;
} BridgeObj;

/**
 * @brief structure for the optional field deserializer
 */
typedef struct OptFields {
    char *field;
    bool has;
} OptField;

/**
 * @brief deserialize
 * @param env napi_env
 * @param obj napi_value
 * @return BridgeObj pointer
 */
BridgeObj *deserialize(napi_env env, napi_value obj);

/**
 * @brief normalize the value of regular color for being prepare into being convet into RGB (broken english am sick).
 * @param env napi_env
 * @param obj napi_value
 * @return BridgeObj pointer
 */
BridgeObj *normalize(napi_env env, napi_value obj);

/**
 * @brief retrieve an optional field. Note this method is fail passive
 * @param env napi_env
 * @param val napi_value
 * @param field *char
 */
OptField *getOptField(napi_env env, napi_value val, char *field);

#endif /* deserializer_h */
