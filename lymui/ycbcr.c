//
//  ycbcr.c
//  lymui
//
//  Created by Marc on 12/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdint.h>
#include <stdlib.h>
#include "errors.h"
#include "ycbcr.h"
#include "helper.h"

// constant variable
const double yValue[]  = {0.257, 0.504, 0.098};
const double crValue[] = {0.439, 0.368, 0.071};
const double cbValue[] = {0.148, 0.291, 0.439};

/**
 * @brief Make Value calculate the value of the y cb cr based on the pass rgb structure
 * @param rgb an Rgb struct
 * @return **v a multidimensonal array
 */
static double ** makeValue(Rgb *rgb) {
    double **v = malloc(3 * 3 * sizeof(double));
    if (v == NULL) {
        return NULL;
    }
    
    // init the multi dimensional array
    v[0] = malloc(sizeof(double) * 3);
    v[1] = malloc(sizeof(double) * 3);
    v[2] = malloc(sizeof(double) * 3);
    
    // Set the YValue
    v[0][0] = rgb->r * yValue[0];
    v[0][1] = rgb->g * yValue[1];
    v[0][2] = rgb->b * yValue[2];
    
    // Set the CRValue
    v[1][0] = rgb->r * cbValue[0];
    v[1][1] = rgb->g * cbValue[1];
    v[1][2] = rgb->b * cbValue[2];
    
    // Set the CBValue
    v[2][0] = rgb->r * crValue[0];
    v[2][1] = rgb->g * crValue[1];
    v[2][2] = rgb->b * crValue[2];
    
    return v;
}

// Make Ycbcr
Ycbcr * getYcbcrFromRgb(Rgb *rgb) {
    Ycbcr *v = malloc(sizeof (Ycbcr));
    if (v == NULL) {
        return NULL;
    }
    
    if (rgb == NULL) {
        v->error = NULL_INPUT_STRUCT;
        return v;
    }
    
    double **colors = makeValue(rgb);
    if (colors == NULL) {
        v->error = MALLOC_ERROR;
        return v;
    }
    
    uint8_t y  = doubleToUint(16  + (colors[0][0] + colors[0][1] + colors[0][2]));
    uint8_t cb = doubleToUint(128 + (- colors[1][0] - colors[1][1] + colors[1][2]));
    uint8_t cr = doubleToUint(128 + (colors[2][0]  - colors[2][1] - colors[2][2]));
    
    v->y  = y;
    v->cb = cb;
    v->cr = cr;
    
    // don't forget to free when not needed anymore
    free(colors);
    return v;
}

// Get Raw RGB Array Value From Ycbcr
Rgb *getRGBFromYcbcr(Ycbcr *cb) {
    Rgb *rgb = initRgb();
    if (cb == NULL) {
        rgb->error = NULL_INPUT_STRUCT;
        return rgb;
    }
    
    uint8_t r = floatToUint(YConst * (cb->y - 16) + 1.596 * (cb->cr - 128));
    uint8_t g = floatToUint(YConst * (cb->y - 16) - 0.813 * (cb->cr - 128) - 0.391 * (cb->cb - 128));
    uint8_t b = floatToUint(YConst * (cb->y - 16) + 2.018 * (cb->cb - 128));
    
    rgb->r = r;
    rgb->g = g;
    rgb->b = b;
    
    // don't forget to free when not needed anymore
    return rgb;
}
