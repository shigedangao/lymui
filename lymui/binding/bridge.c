//
//  bridge.c
//  lymui
//
//  Created by Marc Intha on 26/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <node_api.h>
#include "binding_error.h"
#include "binding_util.h"
#include "bridge.h"
#include "rgb.h"
#include "hex.h"
#include "hsl.h"
#include "hsv.h"
#include "yuv.h"
#include "xyz.h"

/**
 * @brief bind value of properties to node_value array
 * @param env napi_env
 * @param name char * array
 * @param obj napi_value
 * @param len size_t
 * @param res napi_vlue * array
 * @void
 */
static void getNamedPropArray(napi_env env, char * name, napi_value obj, size_t len, napi_value * res) {
    uint8_t idx = 0;
    napi_status status;
    const char delimiter[] = ":";
    char * running = strdup(name);
    char * string;
    
    while(idx < len) {
        string = strsep(&running, delimiter);
        status = napi_get_named_property(env, obj, string, &res[idx]);
        if (status != napi_ok) {
            idx = len + 1;
            napi_throw_error(env, NULL, DESERIALIZE_ERR);
        }
        
        idx++;
    }
}

/**
 * @brief get the enum for the kind of color space
 * @param str char array
 */
static LymuiColorSpace getColorSpaceEnum(char * str) {
    char * list[] = {"iRgb", "iXyz","lab", "lch", "luv", "argb", "srgb"};
    uint8_t idx = 0;
    size_t size = 5;
    LymuiColorSpace type = lab;
    
    while(idx < size) {
        if (!strcmp(str, list[idx])) {
            type = idx;
            idx = size + 1;
        }
        
        idx++;
    }
    
    return type;
}

Rgb * getRGBFromJSObj(napi_env env, napi_value obj) {
    napi_value value[3];
    char * prop = "r:g:b";
    
    // check if the object has the property
    if (!hasPropInJSObj(env, obj, prop, RgbPropLen)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, obj, RgbPropLen, value);
    
    // convert the data to the wanted type
    uint8_t red = getUintValue(env, value[0]);
    uint8_t green = getUintValue(env, value[1]);
    uint8_t blue = getUintValue(env, value[2]);
    uint8_t arr[] = {red, green, blue};
    
    Rgb * rgb = makeRGB(arr, sizeof(arr));
    
    return rgb;
}

char * getHEXFromJSObj(napi_env env, napi_value obj) {
    napi_status status;
    size_t hexLen;
    char * hex = malloc(sizeof(char) * HEX_SIZE + 1);
    
    status = napi_get_value_string_utf8(env, obj, hex, HEX_SIZE + 1, &hexLen);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    char * unslashHex = malloc(sizeof(char) * HEX_SIZE);
    strncpy(unslashHex, hex + 1, 7);
    unslashHex[7] = '\0';
    
    free(hex);
    return unslashHex;
}

Cymk * getCymkFromJSObj(napi_env env, napi_value obj) {
    napi_value value[4];
    char * prop = "c:y:m:k";
    
    if (!hasPropInJSObj(env, obj, prop, CymkPropLen)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, obj, CymkPropLen, value);
    Cymk * cymkSt = malloc(sizeof(Cymk));
    cymkSt->c = getFloatValue(env, value[0]);
    cymkSt->y = getFloatValue(env, value[1]);
    cymkSt->m = getFloatValue(env, value[2]);
    cymkSt->k = getFloatValue(env, value[3]);
    
    return cymkSt;
}

Ycbcr * getYcbcrFromJSObj(napi_env env, napi_value obj) {
    napi_value value[3];
    char * prop = "y:cb:cr";
    
    if (!hasPropInJSObj(env, obj, prop, YCbCrLen)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, obj, YCbCrLen, value);
    
    Ycbcr * ycb = malloc(sizeof(Ycbcr));
    ycb->y = getUintValue(env, value[0]);
    ycb->cb = getUintValue(env, value[1]);
    ycb->cr = getUintValue(env, value[2]);
    
    return ycb;
}

Hsl * getHslFromJSObj(napi_env env, napi_value obj) {
    napi_value value[3];
    char * prop = "h:s:l";
    
    if (!hasPropInJSObj(env, obj, prop, HslHsvLen)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, obj, HslHsvLen, value);
    Hsl * hsl = malloc(sizeof(Hsl));
    hsl->h = getFloatValue(env, value[0]);
    hsl->s = getFloatValue(env, value[1]);
    hsl->l = getFloatValue(env, value[2]);
    
    return hsl;
}

Hsv * getHsvFromJSObj(napi_env env, napi_value obj) {
    napi_value value[3];
    char * prop = "h:s:v";
    
    if (!hasPropInJSObj(env, obj, prop, HslHsvLen)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, obj, 3, value);
    Hsv * hsv = malloc(sizeof(Hsv));
    hsv->h = getFloatValue(env, value[0]);
    hsv->s = getFloatValue(env, value[1]);
    hsv->v = getFloatValue(env, value[2]);
    
    return hsv;
}

Yuv * getYuvFromJSObj(napi_env env, napi_value obj) {
    char * prop = "y:u:v";
    napi_value value[3];
    
    if (!hasPropInJSObj(env, obj, prop, YUVLen)) {
        return NULL;
    }
    
    // retrieve the property in an array of values
    getNamedPropArray(env, prop, obj, 3, value);
    float yv = getFloatValue(env, value[0]);
    float uv = getFloatValue(env, value[1]);
    float vv = getFloatValue(env, value[2]);
    
    Yuv * yuv = malloc(sizeof(Yuv));
    if (yuv == NULL) {
        napi_throw_error(env, NULL, ALLOCATION_ERR);
    }
    
    yuv->y = yv;
    yuv->u = uv;
    yuv->v = vv;
    
    return yuv;
}

Xyz * getXyzFromJSObj(napi_env env, napi_value args) {
    char * prop = "x:y:z";
    napi_value value[3];
    
    if (!hasPropInJSObj(env, args, prop, XYZLen)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, args, XYZLen, value);
    float x = getFloatValue(env, value[0]);
    float y = getFloatValue(env, value[1]);
    float z = getFloatValue(env, value[2]);
    
    Xyz * xyz = malloc(sizeof(Xyz));
    if (xyz == NULL) {
        return NULL;
    }
    
    xyz->x = x;
    xyz->y = y;
    xyz->z = z;
    
    return xyz;
}


ColorBridge * getColorSpaceData(napi_env env, napi_value args) {
    napi_status status;
    napi_value funcParams[3];
    char * prop = "data:output:colorType";
    char * propValidation = "data:output";
    // 0 -> Data napi_value
    // 2 -> output type String
    // 3 -> color type (optional) String
    bool hasColorType;
    Xyz * xyz = NULL;
    
    if (!hasPropInJSObj(env, args, propValidation, COLOR_SPACE_INPUT_VALIDATION)) {
        return NULL;
    }
    
    status = napi_has_named_property(env, args, "colorType", &hasColorType);
    if (status != napi_ok) {
        return NULL;
    }
    
    // Retrieve the value from the object
    getNamedPropArray(env, prop, args, COLOR_SPACE_INPUT, funcParams);
    // Retrieve the string representation of the enum passed by input & output properties
    char * output = getStringValue(env, funcParams[1], SPACELen);
    
    // If a color type is input this mean that the value is an RGB value
    if (hasColorType) {
        char * colorType = getStringValue(env, funcParams[2], SPACELen);
        Matrix m = getEnumFromStr(colorType);
        Rgb * rgb = getRGBFromJSObj(env, funcParams[0]);
        xyz = generateXyzFromRgb(rgb, m);
    } else {
        xyz = getXyzFromJSObj(env, funcParams[0]);
    }
    
    LymuiColorSpace space = getColorSpaceEnum(output);
    ColorBridge * bridge = malloc(sizeof(ColorBridge));
    bridge->color = xyz;
    bridge->c = space;
    
    return bridge;
}
