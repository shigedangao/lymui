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
 * @param xyz Xyz pointer
 */
static void calculateXyzRgb(double r, double g, double b, Xyz *xyz) {
    r = pivotRGB(r);
    g = pivotRGB(g);
    b = pivotRGB(b);
    
    xyz->x = xr * r + xg * g + xb * b;
    xyz->y = yr * r + yg * g + yb * b;
    xyz->z = zr * r + zg * g + zb * b;
}

/**
 * @discussion Calculate Xyz Adobe Rgb calculate the xyz value for the Adobe RGB value
 * @param r double
 * @param g double
 * @param b double
 * @param xyz Xyz pointer
 */
static void calculateXyzAdobeRgb(double r, double g, double b, Xyz *xyz) {
    r = pivotAdobeRGB(r);
    g = pivotAdobeRGB(g);
    b = pivotAdobeRGB(b);
    
    xyz->x = axr * r + axg * g + axb * b;
    xyz->y = ayr * r + ayg * g + ayb * b;
    xyz->z = azr * r + azg * g + azb * b;
}

Xyz *getXyzFromRgb(Rgb *rgb, enum Matrix m) {
    Xyz *xyz = malloc(sizeof(Xyz));
    if (xyz == NULL) {
        return NULL;
    }
    
    if (rgb == NULL) {
        xyz->error = NULL_INPUT_PARAM;
        return xyz;
    }
    
    double _r = (double) rgb->r / 255.0;
    double _g = (double) rgb->g / 255.0;
    double _b = (double) rgb->b / 255.0;
    
    switch(m) {
        case srgb:
            calculateXyzRgb(_r, _g, _b, xyz);
            break;
        case adobeRgb:
            calculateXyzAdobeRgb(_r, _g, _b, xyz);
            break;
        default:
            free(rgb);
            free(xyz);
            return NULL;
    }
    
    xyz->error = NULL;
    
    return xyz;
}

/**
 * @brief calculate the linear rgb to xyz based on the matrix
 * @param xyz * Xyz
 * @param m Matrix
 * @return LinearRGB
 */
static LinearRGB calculateLinearRgbToXyz(Xyz *xyz, Matrix m) {
    LinearRGB linear;
    
    double sr, sg, sb;
    if (m == srgb) {
        sr = xyz->x * xx + xyz->y * xy + xyz->z * xz;
        sg = xyz->x * yx + xyz->y * yy + xyz->z * yz;
        sb = xyz->x * zx + xyz->y * zy + xyz->z * zz;
        
        linear.sr = unpivotRGB(sr);
        linear.sg = unpivotRGB(sg);
        linear.sb = unpivotRGB(sb);
        
        return linear;
    }
    
    sr = xyz->x * axx + xyz->y * axy + xyz->z * axz;
    sg = xyz->x * ayx + xyz->y * ayy + xyz->z * ayz;
    sb = xyz->x * azx + xyz->y * azy + xyz->z * azz;
    
    linear.sr = unpivotARGB(sr);
    linear.sg = unpivotARGB(sg);
    linear.sb = unpivotARGB(sb);
        
    return linear;
}

Rgb *getRgbFromXyz(Xyz * xyz, Matrix m) {
    Rgb *rgb = malloc(sizeof(Rgb));
    if (rgb == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        rgb->error = NULL_INPUT_PARAM;
        return rgb;
    }
    
    LinearRGB matrixValue = calculateLinearRgbToXyz(xyz, m);
    rgb->r = doubleToUint(matrixValue.sr * 255);
    rgb->g = doubleToUint(matrixValue.sg * 255);
    rgb->b = doubleToUint(matrixValue.sb * 255);
    rgb->error = NULL;
    
    return rgb;
}
