//
//  xyz.c
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//  Big credits to Bruce Lindbloom for all the formulas on the XYZ and other types using XYZ
//  Please visit his website for more information regarding the process (http://www.brucelindbloom.com)
//

#include <stdlib.h>
#include <math.h>
#include "helper.h"
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
        
    return powf(c, ADOBE_RGB_COMPOUND);
}

/**
 * @brief Unpivot SRGB unpivot the calculated SRGB value
 * @param c float
 * @return float
 */
static float unpivotRGB(float c) {
    if (c <= 0.0031308f) {
        return c * 12.92f;
    }
    
    return 1.055f * powf(c, 1 / 2.4f) - 0.055;
}

/**
 * @brief Unpivot ARGB unpivot the calculated Adobe RGB value
 * @param c float
 * @return float
 */
static float unpivotARGB(float c) {
    if (c <= 0.0f) {
        return 0.0f;
    }
    
    return powf(c, 1 / ADOBE_RGB_COMPOUND);
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
    
    float x = xr * r + xg * g + xb * b;
    float y = yr * r + yg * g + yb * b;
    float z = zr * r + zg * g + zb * b;
    
    arr[0] = x > 1.0f ? 1.0f : x;
    arr[1] = y > 1.0f ? 1.0f : y;
    arr[2] = z > 1.0f ? 1.0f : z;
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

Xyz * generateXyzFromRgb(Rgb *rgb, enum Matrix m) {
    if (rgb == NULL)
        return NULL;
    
    float _r = (float) rgb->r / 255;
    float _g = (float) rgb->g / 255;
    float _b = (float) rgb->b / 255;
    
    float *value = malloc(sizeof(float) * 3);
    
    switch(m) {
        case srgb:
            calculateXyzRgb(_r, _g, _b, value);
            break;
        case adobeRgb:
            calculateXyzAdobeRgb(_r, _g, _b, value);
            break;
        default:
            free(rgb);
            return NULL;
    }
    
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = value[0];
    xyz->y = value[1];
    xyz->z = value[2];
    
    free(rgb);
    free(value);
    
    return xyz;
}

/**
 * @brief calculate the linear rgb to xyz based on the matrix
 * @param xyz * Xyz
 * @param m Matrix
 */
static float * calculateLinearRgbToXyz(Xyz * xyz, Matrix m) {
    float * linearRGB = malloc(sizeof(float) * 3);
    float sr, sg, sb;
    
    if (m == srgb) {
        sr = xyz->x * xx + xyz->y * xy + xyz->z * xz;
        sg = xyz->x * yx + xyz->y * yy + xyz->z * yz;
        sb = xyz->x * zx + xyz->y * zy + xyz->z * zz;
        
        linearRGB[0] = unpivotRGB(sr);
        linearRGB[1] = unpivotRGB(sg);
        linearRGB[2] = unpivotRGB(sb);
    } else {
        sr = xyz->x * axx + xyz->y * axy + xyz->z * axz;
        sg = xyz->x * ayx + xyz->y * ayy + xyz->z * ayz;
        sb = xyz->x * azx + xyz->y * azy + xyz->z * azz;
        
        linearRGB[0] = unpivotARGB(sr);
        linearRGB[1] = unpivotARGB(sg);
        linearRGB[2] = unpivotARGB(sb);
    }
    
    
    free(xyz);
    return linearRGB;
}

Rgb * generateRgbFromXyz(Xyz * xyz, Matrix m) {
    if (xyz == NULL) {
        return NULL;
    }
    
    float * matrixValue = calculateLinearRgbToXyz(xyz, m);
    
    Rgb * rgb = malloc(sizeof(rgb));
    if (rgb == NULL) {
        return NULL;
    }
    
    rgb->r = floatToUint(matrixValue[0] * 255);
    rgb->g = floatToUint(matrixValue[1] * 255);
    rgb->b = floatToUint(matrixValue[2] * 255);
    free(matrixValue);
    
    return rgb;
}
