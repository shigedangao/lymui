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
#include "xyz_constant.h"
#include "errors.h"
#include "helper.h"
#include "rgb.h"
#include "xyz.h"

/**
 * @brief Pivot RGB Convert the RGB value to a linear rgb value
 * @param c double
 * @retun c double
 */
static double pivotRGB(double c) {
    if (c <= 0.04045)
        return c / 12.92;
    
    return pow((c + 0.055) / 1.055, 2.4);
}

/**
 * @brief Pivot Adobe RGB Convert the RGB value to a linear Adobe RGB
 * @param c double
 * @return c double
 */
static double pivotAdobeRGB(double c) {
    if (c <= 0.0)
        return 0.0;
        
    return pow(c, ADOBE_RGB_COMPOUND);
}

/**
 * @brief Unpivot SRGB unpivot the calculated SRGB value
 * @param c double
 * @return double
 */
static double unpivotRGB(double c) {
    if (c <= 0.0031308) {
        return c * 12.92;
    }
    
    return 1.055 * pow(c, 1 / 2.4) - 0.055;
}

/**
 * @brief Unpivot ARGB unpivot the calculated Adobe RGB value
 * @param c double
 * @return double
 */
static double unpivotARGB(double c) {
    if (c <= 0.0) {
        return 0.0;
    }
    
    return pow(c, 1 / ADOBE_RGB_COMPOUND);
}

/**
 * @discussion Calculate Xyz Rgb, calculate the xyz for the sRgb value
 * @param r double
 * @param g double
 * @param b double
 * @param arr double
 */
static void calculateXyzRgb(double r, double g, double b, double *arr) {
    r = pivotRGB(r);
    g = pivotRGB(g);
    b = pivotRGB(b);
    
    double x = xr * r + xg * g + xb * b;
    double y = yr * r + yg * g + yb * b;
    double z = zr * r + zg * g + zb * b;
    
    arr[0] = x;
    arr[1] = y;
    arr[2] = z;
}

/**
 * @discussion Calculate Xyz Adobe Rgb calculate the xyz value for the Adobe RGB value
 * @param r double
 * @param g double
 * @param b double
 * @param arr double
 */
static void calculateXyzAdobeRgb(double r, double g, double b, double *arr) {
    r = pivotAdobeRGB(r);
    g = pivotAdobeRGB(g);
    b = pivotAdobeRGB(b);
    
    arr[0] = axr * r + axg * g + axb * b;
    arr[1] = ayr * r + ayg * g + ayb * b;
    arr[2] = azr * r + azg * g + azb * b;
}

Xyz * generateXyzFromRgb(Rgb *rgb, enum Matrix m) {
    Xyz *xyz = malloc(sizeof(Xyz));
    if (xyz == NULL) {
        return NULL;
    }
    
    if (rgb == NULL) {
        xyz->error = NULL_INPUT_STRUCT;
        return xyz;
    }
    
    double _r = (double) rgb->r / 255.0;
    double _g = (double) rgb->g / 255.0;
    double _b = (double) rgb->b / 255.0;
    
    double *value = malloc(sizeof(double) * 3);
    
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
static double * calculateLinearRgbToXyz(Xyz * xyz, Matrix m) {
    double *linearRGB = malloc(sizeof(double) * 3);
    if (linearRGB == NULL) {
        return NULL;
    }
    
    double sr, sg, sb;
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
    Rgb * rgb = malloc(sizeof(rgb));
    if (rgb == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        rgb->error = NULL_INPUT_STRUCT;
        return rgb;
    }
    
    double *matrixValue = calculateLinearRgbToXyz(xyz, m);
    if (matrixValue == NULL) {
        rgb->error = MALLOC_ERROR;
        return rgb;
    }
    
    rgb->r = doubleToUint(matrixValue[0] * 255);
    rgb->g = doubleToUint(matrixValue[1] * 255);
    rgb->b = doubleToUint(matrixValue[2] * 255);
    free(matrixValue);
    
    return rgb;
}
