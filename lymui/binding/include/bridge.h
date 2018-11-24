//
//  bridge.h
//  lymui
//
//  Created by Marc Intha on 26/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef bridge_h
#define bridge_h

#include <stdio.h>
#include <node_api.h>
#include "rgb.h"
#include "cymk.h"
#include "ycbcr.h"
#include "hsl.h"
#include "hsv.h"
#include "yuv.h"
#include "xyz.h"

#define RgbPropLen 3
#define CymkPropLen 4
#define YCbCrLen 3
#define HslHsvLen 3
#define YUVLen 3
#define XYZLen 3
#define LABLen 3
#define LCHLen 3
#define SPACELen 4
#define MIN_CLAMP_VALUE 1000
#define PERCENT_CLAMP_VALUE 100
#define COLOR_SPACE_INPUT 3
#define COLOR_SPACE_INPUT_VALIDATION 2

/**
 * @brief Extract an RGB Object from a JS Object
 * @param env napi_env
 * @param args napi_value
 * @return rgb struct pointer
 */
Rgb *getRGBFromJSObj(napi_env env, napi_value args);

/**
 * @brief Extract a char array representing the Hex value from JS
 * @param env napi_env
 * @param args napi_value
 * @return char array
 */
char *getHEXFromJSObj(napi_env env, napi_value args);

/**
 * @brief Extract a CYMK Object from a JS Object
 * @param env napi_env
 * @param args napi_value
 * @return cymk pointer Cymk struct
 */
Cymk *getCymkFromJSObj(napi_env env, napi_value args);

/**
 * @brief Extrat a Ycbcr struct from a JS Object
 * @param env napi_env
 * @param args napi_value
 * @return ycbcr pointer struct
 */
Ycbcr *getYcbcrFromJSObj(napi_env env, napi_value args);

/**
 * @brief Extract a Hsl struct from a JS Object
 * @param env napi_env
 * @param args napi_value
 * @return hsl
 */
Hsl *getHslFromJSObj(napi_env env, napi_value args);

/**
 * @brief Extract a HSV struct from a JS Object
 * @param env napi_env
 * @param args napi_value
 * @return hsv
 */
Hsv *getHsvFromJSObj(napi_env env, napi_value args);

/**
 * @brief Extract a YUV struct from a JS Object
 * @param env napi_env
 * @param args napi_value
 * @return yuv
 */
Yuv *getYuvFromJSObj(napi_env env, napi_value args);

/**
 * @brief Extract Xyz struct from a JS Object
 * @param env napi_env
 * @param args napi_value
 * @return xyz
 */
Xyz *getXyzFromJSObj(napi_env env, napi_value args);


#endif /* bridge_h */
