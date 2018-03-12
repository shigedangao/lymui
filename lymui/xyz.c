//
//  xyz.c
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
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
    arr[1] = zr * r + zg * g + zb * b;
}

float * generateXyzValue(float r, float g, float b, enum Matrix m) {
    float *value = malloc(sizeof(float) * 3);
    
    switch(m) {
        case sRgb:
            calculateXyzRgb(r,g,b,value);
            break;
    }
    
    return value;
}
