//
//  factory.h
//  lymui
//
//  Created by Marc Intha on 01/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef factory_h
#define factory_h

#include <stdio.h>
#include <node_api.h>
#include "rgb.h"
#include "cymk.h"
#include "ycbcr.h"
#include "hsl.h"
#include "hsv.h"
#include "yuv.h"
#include "xyz.h"
#include "lab.h"
#include "lch.h"
#include "luv.h"
#include "argb.h"
#include "srgb.h"

#define COLOR_SPACE_CLAMP 10000

/**
 * @brief struct use for handling promise error
 */
typedef struct JSError {
    char * error;
} JSError;


/**
 * @brief Factory creating Rgb Object on the fly
 * @param env napi_env
 * @param rgb Rgb struct pointer
 */
napi_value RgbJSObjFactory(napi_env env, Rgb * rgb);

/**
 * @brief Factory creating Cymk JS Object
 * @param env napi_env
 * @param cymk Cymk struct pointer
 * @param clamp int
 * @return napi_value
 */
napi_value CymkJSObjFactory(napi_env env, Cymk * cymk, int clamp);

/**
 * @brief Factory creating Ycbcr Object
 * @param env napi_env
 * @param ycb Ycbcr struct pointer
 * @return napi_value
 */
napi_value YcbcrJSObjFactory(napi_env env, Ycbcr *ycb);

/**
 * @brief Factory creating Hsl Object
 * @param env napi_env
 * @param hsl Hsl struct pointer
 * @param clamp int
 * @return napi_value
 */
napi_value HslJSObjFactory(napi_env env, Hsl * hsl, int clamp);

/**
 * @breif Creating HSV JS Object
 * @param env napi_env
 * @param hsv struct HSV pointer
 * @param clamp int
 * @return napi_value
 */
napi_value HsvJSObjFactory(napi_env env, Hsv * hsv, int clamp);

/**
 * @brief Creating YUV JS Object
 * @param env napi_env
 * @param yuv * yuv
 * @param clamp int
 * @return napi_value
 */
napi_value YuvJSObjFactory(napi_env env, Yuv * yuv, int clamp);

/**
 * @brief Creating Xyz JS Object
 * @param env napi_env
 * @param xyz * Xyz
 * @param clamp int
 * @return napi_value
 */
napi_value XyzJSObjFactory(napi_env env, Xyz * xyz, int clamp);

/**
 * @brief Creating Lab JS Object
 * @param env napi_env
 * @param xyz * Xyz
 * @return napi_value
 */
napi_value LabJSObjFactory(napi_env env, Xyz * xyz);

/**
 * @brief Creating Lch JS Object
 * @param env napi_env
 * @param xyz * Xyz
 * @return napi_value
 */
napi_value LchJSObjFactory(napi_env env, Xyz * xyz);

/**
 * @brief Creating Luv JS Object
 * @param env napi_env
 * @param xyz * Xyz
 * @return napi_value
 */
napi_value LuvJSObjFactory(napi_env env, Xyz * xyz);

/**
 * @brief Creating ARGB JS Object
 * @param env napi_env
 * @param xyz * Xyz
 * @return napi_value
 */
napi_value ArgbJSObjFactory(napi_env env, Xyz * xyz);

/**
 * @brief Creating Srgb JS Object
 * @param env napi_env
 * @param xyz * Xyz
 * @return napi_value
 */
napi_value SrgbJSObjFactory(napi_env env, Xyz * xyz);

/**
 * @brief Build Promise Error
 * @param env napi_env
 * @param error * char
 * @return napi_value
 */
napi_value BuildPromiseError(napi_env env, char * error);

#endif /* factory_h */
