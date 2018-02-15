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

// Make Ycbcr
struct Ycbcr *makeYcbcr(struct Rgb *rgb) {
    if (rgb == NULL)
        return NULL;
    
    struct Ycbcr *v = malloc(sizeof (struct Ycbcr));
    uint8_t y  = floatToUint(16  + (yValue[0] * rgb->r + yValue[1] * rgb->g + yValue[2] * rgb->b));
    uint8_t cb = floatToUint(128 + (- (cbValue[0] * rgb->r) - (cbValue[1] * rgb->g) + (cbValue[2] * rgb->b)));
    uint8_t cr = floatToUint(128 + (crValue[0] * rgb->r - crValue[1]  * rgb->g  - crValue[2] * rgb->b));
    
    v->y  = y;
    v->cb = cb;
    v->cr = cr;
    
    // don't forget to free when not needed anymore
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
