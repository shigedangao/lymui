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
#include "hex.h"

Rgb *getRGBFromJSObj(napi_env env, napi_value obj) {
    napi_value value[3];
    char *prop = "r:g:b";
    
    // check if the object has the property
    if (!hasPropInJSObj(env, obj, prop, MIN_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, obj, MIN_PARAM_VALUE, value);
    
    // convert the data to the wanted type
    uint8_t red = getUintValue(env, value[0]);
    uint8_t green = getUintValue(env, value[1]);
    uint8_t blue = getUintValue(env, value[2]);
    uint8_t arr[] = {red, green, blue};
    
    Rgb *rgb = makeRGB(arr, sizeof(arr));
    
    return rgb;
}

char * getHEXFromJSObj(napi_env env, napi_value obj) {
    napi_status status;
    size_t hexLen;
    char * hex = malloc(sizeof(char) * HEX_SIZE + 1);
    
    status = napi_get_value_string_utf8(env, obj, hex, HEX_SIZE + 1, &hexLen);
    if (status != napi_ok) {
        return NULL;
    }
    
    char *unslashHex = malloc(sizeof(char) * HEX_SIZE);
    if (unslashHex == NULL) {
        return NULL;
    }
    
    strncpy(unslashHex, hex, 7);
    unslashHex[7] = '\0';
    
    free(hex);
    return unslashHex;
}

Cymk *getCymkFromJSObj(napi_env env, napi_value obj) {
    napi_value value[4];
    char *prop = "c:y:m:k";
    
    if (!hasPropInJSObj(env, obj, prop, MAX_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, obj, MAX_PARAM_VALUE, value);
    Cymk *cymkSt = malloc(sizeof(Cymk));
    if (cymkSt == NULL) {
        return NULL;
    }
    
    cymkSt->c = getDoubleValue(env, value[0]);
    cymkSt->y = getDoubleValue(env, value[1]);
    cymkSt->m = getDoubleValue(env, value[2]);
    cymkSt->k = getDoubleValue(env, value[3]);
    
    return cymkSt;
}

Ycbcr *getYcbcrFromJSObj(napi_env env, napi_value obj) {
    napi_value value[3];
    char *prop = "y:cb:cr";
    
    if (!hasPropInJSObj(env, obj, prop, MIN_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, obj, MIN_PARAM_VALUE, value);
    
    Ycbcr *ycb = malloc(sizeof(Ycbcr));
    if (ycb == NULL) {
        return NULL;
    }
    
    ycb->y = getUintValue(env, value[0]);
    ycb->cb = getUintValue(env, value[1]);
    ycb->cr = getUintValue(env, value[2]);
    
    return ycb;
}

Hsl *getHslFromJSObj(napi_env env, napi_value obj) {
    napi_value value[3];
    char *prop = "h:s:l";
    
    if (!hasPropInJSObj(env, obj, prop, MIN_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, obj, MIN_PARAM_VALUE, value);
    Hsl *hsl = malloc(sizeof(Hsl));
    if (hsl == NULL) {
        return NULL;
    }
    
    hsl->h = getDoubleValue(env, value[0]);
    hsl->s = getDoubleValue(env, value[1]);
    hsl->l = getDoubleValue(env, value[2]);
    
    return hsl;
}

Hsv *getHsvFromJSObj(napi_env env, napi_value obj) {
    napi_value value[3];
    char *prop = "h:s:v";
    
    if (!hasPropInJSObj(env, obj, prop, MIN_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, obj, MIN_PARAM_VALUE, value);
    Hsv *hsv = malloc(sizeof(Hsv));
    if (hsv == NULL) {
        return NULL;
    }
    
    hsv->h = getDoubleValue(env, value[0]);
    hsv->s = getDoubleValue(env, value[1]);
    hsv->v = getDoubleValue(env, value[2]);
    
    return hsv;
}

Yuv *getYuvFromJSObj(napi_env env, napi_value obj) {
    char *prop = "y:u:v";
    napi_value value[3];
    if (!hasPropInJSObj(env, obj, prop, MIN_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, obj, MIN_PARAM_VALUE, value);
    Yuv *yuv = malloc(sizeof(Yuv));
    if (yuv == NULL) {
        return NULL;
    }
    yuv->y = getDoubleValue(env, value[0]);
    yuv->u = getDoubleValue(env, value[1]);
    yuv->v = getDoubleValue(env, value[2]);
    
    return yuv;
}

Xyz *getXyzFromJSObj(napi_env env, napi_value args) {
    char *prop = "x:y:z";
    napi_value value[3];
    
    if (!hasPropInJSObj(env, args, prop, MIN_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, args, MIN_PARAM_VALUE, value);
    Xyz *xyz = malloc(sizeof(Xyz));
    if (xyz == NULL) {
        return NULL;
    }
    
    xyz->x = getDoubleValue(env, value[0]);
    xyz->y = getDoubleValue(env, value[1]);
    xyz->z = getDoubleValue(env, value[2]);
    
    return xyz;
}

Lab *getLabFromJSObj(napi_env env, napi_value args) {
    char *prop = "l:a:b";
    napi_value value[3];
    
    if (!hasPropInJSObj(env, args, prop, MIN_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, args, MIN_PARAM_VALUE, value);
    Lab *lab = malloc(sizeof(Lab));
    if (lab == NULL) {
        return NULL;
    }
    
    lab->l = getDoubleValue(env, value[0]);
    lab->a = getDoubleValue(env, value[1]);
    lab->b = getDoubleValue(env, value[2]);
    
    return lab;
}

Lch *getLchFromJSObj(napi_env env, napi_value args) {
    char *prop = "l:c:h";
    napi_value value[3];
    
    if (!hasPropInJSObj(env, args, prop, MIN_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, args, MIN_PARAM_VALUE, value);
    Lch *lch = malloc(sizeof(Lch));
    if (lch == NULL) {
        return NULL;
    }
    
    lch->l = getDoubleValue(env, value[0]);
    lch->c = getDoubleValue(env, value[1]);
    lch->h = getDoubleValue(env, value[2]);
    
    return lch;
}

LchLab *getLchlabFromJSObj(napi_env env, napi_value args) {
    char *prop = "l:c:h";
    napi_value value[3];
    
    if (!hasPropInJSObj(env, args, prop, MIN_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, args, MIN_PARAM_VALUE, value);
    LchLab *lch = malloc(sizeof(LchLab));
    if (lch == NULL) {
        return NULL;
    }
    
    lch->l = getDoubleValue(env, value[0]);
    lch->c = getDoubleValue(env, value[1]);
    lch->h = getDoubleValue(env, value[2]);
    
    return lch;
}

Luv *getLuvFromJSObj(napi_env env, napi_value args) {
    char *prop = "l:u:v";
    napi_value value[3];
    
    if (!hasPropInJSObj(env, args, prop, MIN_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, args, MIN_PARAM_VALUE, value);
    Luv *luv = malloc(sizeof(Luv));
    if (luv == NULL) {
        return NULL;
    }
    
    luv->l = getDoubleValue(env, value[0]);
    luv->u = getDoubleValue(env, value[1]);
    luv->v = getDoubleValue(env, value[2]);
    
    return luv;
}

Argb *getArgbFromJSObj(napi_env env, napi_value args) {
    char *prop = "r:g:b";
    napi_value value[3];
    
    if (!hasPropInJSObj(env, args, prop, MIN_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, args, MIN_PARAM_VALUE, value);
    Argb *argb = malloc(sizeof(Argb));
    if (argb == NULL) {
        return NULL;
    }
    
    argb->r = getDoubleValue(env, value[0]);
    argb->g = getDoubleValue(env, value[1]);
    argb->b = getDoubleValue(env, value[2]);
    
    return argb;
}

SRgb *getSrgbFromJSObj(napi_env env, napi_value args) {
    char *prop = "r:g:b";
    napi_value value[3];
    
    if (!hasPropInJSObj(env, args, prop, MIN_PARAM_VALUE)) {
        return NULL;
    }
    
    getNamedPropArray(env, prop, args, MIN_PARAM_VALUE, value);
    SRgb *srgb = malloc(sizeof(SRgb));
    if (srgb == NULL) {
        return NULL;
    }
    
    srgb->r = getDoubleValue(env, value[0]);
    srgb->g = getDoubleValue(env, value[1]);
    srgb->b = getDoubleValue(env, value[2]);
    
    return srgb;
}
