//
//  node_rgb.c
//  lymui
//
//  Created by Marc Intha on 24/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <node_api.h>
#include "binding_error.h"
#include "node_rgb.h"
#include "node_hex.h"
#include "node_cymk.h"
#include "node_hue.h"
#include "node_ycbcr.h"
#include "node_hsl.h"
#include "node_hsv.h"
#include "node_yuv.h"
#include "node_xyz.h"
#include "convert.h"


#define DECLARE_NAPI_METHOD(name, func) { name, 0, func, 0, 0, 0, napi_default, 0 }

/**
 *  Initialization of our NodeJS module
 */
napi_value Init(napi_env env, napi_value exports) {
    napi_status status;
    
    // define the methods here
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_METHOD("makeRGB", GenerateRGB),
        // Hex
        DECLARE_NAPI_METHOD("getHEX", GetHexFromRGB),
        DECLARE_NAPI_METHOD("getRgbFromHex", GetRGBFromHex),
        // Cymk
        DECLARE_NAPI_METHOD("getCymkFromRgb", GetCymkFromRgb),
        DECLARE_NAPI_METHOD("getRgbFromCymk", GetRgbFromCymk),
        // Hue
        DECLARE_NAPI_METHOD("getHueFromRgb", GetHueFromRgb),
        // Ycbcr
        DECLARE_NAPI_METHOD("getYcbcrFromRgb", GetYcbcrFromRGB),
        DECLARE_NAPI_METHOD("getRgbFromYcbcr", GetRgbFromYcbcr),
        // Hsl
        DECLARE_NAPI_METHOD("getHslFromRgb", GetHslFromRGB),
        DECLARE_NAPI_METHOD("getRgbFromHsl", GetRGBFromHsl),
        // Hsv
        DECLARE_NAPI_METHOD("getHsvFromRgb", GetHsvFromRGB),
        DECLARE_NAPI_METHOD("getRgbFromHsv", GetRGBFromHsv),
        // Yuv
        DECLARE_NAPI_METHOD("getYuvFromRgb", GetYuvFromRGB),
        DECLARE_NAPI_METHOD("getRgbFromYuv", GetRGBFromYuv),
        // Xyz
        DECLARE_NAPI_METHOD("getXyzFromRgb", GetXyzFromRGB),
        DECLARE_NAPI_METHOD("getRgbFromXyz", GetRGBFromXyz),
        // Color Space
        DECLARE_NAPI_METHOD("convert", convert)
    };
    
    status = napi_define_properties(env, exports, sizeof(desc) / sizeof(*desc), desc);
    
    if (status != napi_ok) {
        napi_throw_error(env, NULL, BINDING_ERR);
    }
    
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
