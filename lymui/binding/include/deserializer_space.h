//
//  deserializer_space.h
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef deserializer_space_h
#define deserializer_space_h

#include <stdio.h>
#include <node_api.h>

#define XYZ_PROPS "x:y:z"
#define LAB_PROPS "l:a:b"
#define LCH_PROPS "l:c:h"
#define LUV_PROPS "l:u:v"
#define ARGB_PROPS "r:g:b"
#define SRGB_PROPS "r:g:b"
#define LCHLAB_PROPS "l:a:b"

/**
 * @brief list of color supported color space
 */
typedef enum OutputSpace {
    lab,
    lch,
    llab,
    luv,
    argb,
    Srgb
} OSpaceType;

/**
 * @brief struct that will be used to calculate value
 */
typedef struct BridgeSpaceObj {
    napi_value color;
    OSpaceType output;
    char *error;
    double clamp;
} BridgeSpaceObj;


/**
 * @brief deserialize space color
 * @param env napi_env
 * @param obj napi_value
 * @return BridgeSpaceObj pointer
 */
BridgeSpaceObj *deserializeSpace(napi_env env, napi_value obj);


/**
 * @brief normalize the value of regular color for being prepare into being convet into RGB (broken english am sick).
 * @param env napi_env
 * @param obj napi_value
 * @return BridgeObj pointer
 */
BridgeSpaceObj *normalizeSpace(napi_env env, napi_value obj);

#endif /* deserializer_space_h */
