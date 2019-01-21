//
//  ycbcr.c
//  lymui
//
//  Created by Marc on 12/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include "errors.h"
#include "ycbcr.h"
#include "helper.h"

// constant variable
const double yValue[]  = {0.257, 0.504, 0.098};
const double crValue[] = {0.439, 0.368, 0.071};
const double cbValue[] = {0.148, 0.291, 0.439};

/**
 * @brief Calculate By Indices
 * @param rgb an Rgb struct
 * @param k YcbcrKind
 * @return YBridge
 */
static YBridge calculateByIndices(Rgb *rgb, YcbcrKind k) {
    YBridge bridge;
    switch (k) {
        case y:
            bridge.l = rgb->r * yValue[0];
            bridge.y = rgb->g * yValue[1];
            bridge.m = rgb->b * yValue[2];
            break;
        case cb:
            bridge.l = rgb->r * cbValue[0];
            bridge.y = rgb->g * cbValue[1];
            bridge.m = rgb->b * cbValue[2];
            break;
        case cr:
            bridge.l = rgb->r * crValue[0];
            bridge.y = rgb->g * crValue[1];
            bridge.m = rgb->b * crValue[2];
    }
    
    return bridge;
}

Ycbcr *getYcbcrFromRgb(Rgb *rgb) {
    Ycbcr *v = malloc(sizeof (Ycbcr));
    if (v == NULL) {
        return NULL;
    }
    
    if (rgb == NULL) {
        v->error = NULL_INPUT_STRUCT;
        return v;
    }
    
    YBridge yy = calculateByIndices(rgb, y);
    YBridge yc = calculateByIndices(rgb, cb);
    YBridge yr = calculateByIndices(rgb, cr);
    
    uint8_t y  = doubleToUint(16  + (yy.l + yy.y + yy.m));
    uint8_t cb = doubleToUint(128 + (- yc.l - yc.y + yc.m));
    uint8_t cr = doubleToUint(128 + (yr.l  - yr.y - yr.m));
    
    v->y  = y;
    v->cb = cb;
    v->cr = cr;
    v->error = NULL;
    
    return v;
}

// Get Raw RGB Array Value From Ycbcr
Rgb *getRgbFromYcbcr(Ycbcr *cb) {
    Rgb *rgb = initRgb();
    if (cb == NULL) {
        rgb->error = NULL_INPUT_STRUCT;
        return rgb;
    }
    
    uint8_t r = doubleToUint(YConst * (cb->y - 16) + 1.596 * (cb->cr - 128));
    uint8_t g = doubleToUint(YConst * (cb->y - 16) - 0.813 * (cb->cr - 128) - 0.391 * (cb->cb - 128));
    uint8_t b = doubleToUint(YConst * (cb->y - 16) + 2.018 * (cb->cb - 128));
    
    rgb->r = r;
    rgb->g = g;
    rgb->b = b;
    rgb->error = NULL;
    
    free(cb);
    
    return rgb;
}
