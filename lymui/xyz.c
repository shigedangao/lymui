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
 * @discussion Pivot RGB Convert the RGB value to a linear rgb value
 * @param c float
 * @retun c float
 */
static float pivotRGB(float c) {
    if (c <= 0.04045f)
        return c / 12.92f;
    
    return powf((c + 0.055f) / 1.055f, 2.4f);
}

/**
 * @discussion Pivot Adobe RGB Convert the RGB value to a linear Adobe RGB
 * @param c float
 * @return c float
 */
static float pivotAdobeRGB(float c) {
    if (c <= 0.0f)
        return 0.0f;
        
    return powf(c, 2.19921875f);
}

/**
 * @discussion Calculate Xyz Rgb, calculate the xyz for the sRgb value
 * @param r float
 * @param g float
 * @param b float
 * @param arr float
 */
static void calculateXyzRgb(float r, float g, float b, float *arr) {
    r = pivotRGB(r);
    g = pivotRGB(g);
    b = pivotRGB(b);
    
    arr[0] = xr * r + xg * g + xb * b;
    arr[1] = yr * r + yg * g + yb * b;
    arr[2] = zr * r + zg * g + zb * b;
}

/**
 * @discussion Calculate Xyz Adobe Rgb calculate the xyz value for the Adobe RGB value
 * @param r float
 * @param g float
 * @param b float
 * @param arr float
 */
static void calculateXyzAdobeRgb(float r, float g, float b, float *arr) {
    r = pivotAdobeRGB(r);
    g = pivotAdobeRGB(g);
    b = pivotAdobeRGB(b);
    
    arr[0] = axr * r + axg * g + axb * b;
    arr[1] = ayr * r + ayg * g + ayb * b;
    arr[2] = azr * r + azg * g + azb * b;
}

struct Xyz * generateXyzFromRgb(struct Rgb *rgb, enum Matrix m) {
    if (rgb == NULL)
        return NULL;
    
    float _r = (float) rgb->r / 255;
    float _g = (float) rgb->g / 255;
    float _b = (float) rgb->b / 255;
    
    float *value = malloc(sizeof(float) * 3);
    
    switch(m) {
        case sRgb:
            calculateXyzRgb(_r, _g, _b, value);
            break;
        case adobeRgb:
            calculateXyzAdobeRgb(_r, _g, _b, value);
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
