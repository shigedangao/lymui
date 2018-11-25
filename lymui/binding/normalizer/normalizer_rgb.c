//
//  normalizer_rgb.c
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "normalizer_rgb.h"
#include <node_api.h>
#include "hex.h"
#include "binding_util.h"
#include "bridge.h"
#include "factory.h"

napi_value normalizeHex(napi_env env, napi_value color) {
    char *hex = getHEXFromJSObj(env, color);
    if (hex == NULL) {
        return NULL;
    }
    
    Rgb *rgb = getRGBFromHex(hex);
    
    napi_value object = RgbJSObjFactory(env, rgb);
    return object;
}

napi_value normalizeHsl(napi_env env, napi_value color) {
    Hsl *hsl = getHslFromJSObj(env, color);
    if (hsl == NULL) {
        return NULL;
    }
    
    Rgb *rgb = getRgbFromHsl(hsl);
    napi_value object = RgbJSObjFactory(env, rgb);
    return object;
}

napi_value normalizeHsv(napi_env env, napi_value color) {
    Hsv *hsv = getHsvFromJSObj(env, color);
    if (hsv == NULL) {
        return NULL;
    }
    
    Rgb *rgb = getRgbFromHsv(hsv);
    napi_value object = RgbJSObjFactory(env, rgb);
    return object;
}

napi_value normalizeCymk(napi_env env, napi_value color) {
    Cymk *cymk = getCymkFromJSObj(env, color);
    if (cymk == NULL) {
        return NULL;
    }
    
    Rgb *rgb = getRgbFromCymk(cymk);
    napi_value object = RgbJSObjFactory(env, rgb);
    
    return object;
}

napi_value normalizeYcbcr(napi_env env, napi_value color) {
    Ycbcr *ycbcr = getYcbcrFromJSObj(env, color);
    if (ycbcr == NULL) {
        return NULL;
    }
    
    Rgb *rgb = getRGBFromYcbcr(ycbcr);
    napi_value object = RgbJSObjFactory(env, rgb);
    
    return object;
}

napi_value normalizeXyz(napi_env env, napi_value color, char *m) {
    Matrix mx = getEnumFromStr(m);
    Xyz *xyz = getXyzFromJSObj(env, color);
    if (xyz == NULL) {
        return NULL;
    }
    
    Rgb *rgb = generateRgbFromXyz(xyz, mx);
    napi_value object = RgbJSObjFactory(env, rgb);
    
    return object;
}
