//
//  xyz.c
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "rgb.h"
#include "xyz.h"

/**
 * @discussion Calculate Xyz Rgb, calculate the xyz for the sRgb value
 * @param r float
 * @param g float
 * @param b float
 * @param arr float
 */
static void calculateXyzRgb(float r, float g, float b, float *arr) {
    arr[0] = xr * r + xg * g + xb * b;
    arr[1] = yr * r + yg * g + yb * b;
    arr[2] = zr * r + zg * g + zb * b;
}

/**
 * @discussion Pivot RGB Convert the RGB value to a linear rgb value
 * @param c float
 * @retun c float
 */
static float pivotRGB(float c) {
    if (c <= 0.04045f)
        return c / 12.92f;
    
    return powf((c + 0.055f) / 1.055f, 2.4f);
}

struct Xyz * generateXyzFromRgb(struct Rgb *rgb, enum Matrix m) {
    if (rgb == NULL)
        return NULL;
    
    float _r = pivotRGB((float) rgb->r / 255);
    float _g = pivotRGB((float) rgb->g / 255);
    float _b = pivotRGB((float) rgb->b / 255);
    
    float *value = malloc(sizeof(float) * 3);
    
    switch(m) {
        case sRgb:
            calculateXyzRgb(_r, _g, _b, value);
            break;
        default:
            free(rgb);
            return NULL;
    }
    
    struct Xyz *xyz = malloc(sizeof(struct Xyz));
    xyz->x = value[0];
    xyz->y = value[1];
    xyz->z = value[2];
    
    free(rgb);
    
    return xyz;
}
