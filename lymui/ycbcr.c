//
//  ycbcr.c
//  lymui
//
//  Created by Marc on 12/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdint.h>
#include <stdlib.h>
#include "ycbcr.h"
#include "helper.h"

// constant variable
const float yValue[]  = {0.257, 0.504, 0.098};
const float crValue[] = {0.439, 0.368, 0.071};
const float cbValue[] = {0.148, 0.291, 0.439};
const float YConst    = 1.164;

/**
 * @discussion Make Value calculate the value of the y cb cr based on the pass rgb structure
 * @param rgb an Rgb struct
 * @return **v a multidimensonal array
 */
static float ** makeValue(struct Rgb *rgb) {
    float **v = malloc(3 * 3 * sizeof(float));
    
    // init the multi dimensional array
    v[0] = malloc(sizeof(float) * 3);
    v[1] = malloc(sizeof(float) * 3);
    v[2] = malloc(sizeof(float) * 3);
    
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
struct Ycbcr *makeYcbcr(struct Rgb *rgb) {
    if (rgb == NULL)
        return NULL;
    
    struct Ycbcr *v = malloc(sizeof (struct Ycbcr));
    float **colors = makeValue(rgb);
    uint8_t y  = floatToUint(16  + (colors[0][0] + colors[0][1] + colors[0][2]));
    uint8_t cb = floatToUint(128 + (- colors[1][0] - colors[1][1] + colors[1][2]));
    uint8_t cr = floatToUint(128 + (colors[2][0]  - colors[2][1] - colors[2][2]));
    
    v->y  = y;
    v->cb = cb;
    v->cr = cr;
    
    // don't forget to free when not needed anymore
    free(colors);
    return v;
}

// Get Raw RGB Array Value From Ycbcr
struct Rgb * getRawRGBValueFromYcbcr(struct Ycbcr *cb) {
    if (cb == NULL)
        return NULL;
    
    uint8_t * cArr = malloc(sizeof(char) * 3);
    uint8_t r = floatToUint(YConst * (cb->y - 16) + 1.596 * (cb->cr - 128));
    uint8_t g = floatToUint(YConst * (cb->y - 16) - 0.813 * (cb->cr - 128) - 0.391 * (cb->cb - 128));
    uint8_t b = floatToUint(YConst * (cb->y - 16) + 2.018 * (cb->cb - 128));
    
    cArr[0] = r;
    cArr[1] = g;
    cArr[2] = b;
    
    struct Rgb *rgb = makeRGB(cArr, 3);
    free(cArr);
    
    // don't forget to free when not needed anymore
    return rgb;
}
