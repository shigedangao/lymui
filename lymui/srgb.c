//
//  srgb.c
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "xyz_constant.h"
#include "errors.h"
#include "srgb.h"

/**
 * @brief Gamma Correction add gamma correction for linear sRGB
 * @param c double
 * @return double
 */
static double gammaCorrection(double c) {
    if (c <= 0.0031308) {
        return c * 12.92;
    }
    
    return 1.055 * pow(c, 1 / 2.4) - 0.055;
}

/**
 * @brief reverse the gamma correction applied on the conversion from xyz to srgb
 * @param c double
 * @return double
 */
static double reverseGamma(double c) {
    if (c <= 0.04045) {
        return c / 12.92;
    }
    
    return pow((c + 0.055) / 1.055, 2.4);
}

SRgb *getSrgbFromXyz(Xyz *xyz) {
    SRgb *srgb = malloc(sizeof(SRgb));
    if (srgb == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        srgb->error = NULL_INPUT_PARAM;
        return srgb;
    }
    
    double r = xyz->x * srr + xyz->y * srg + xyz->z * srb;
    double g = xyz->x * sgr + xyz->y * sgg + xyz->z * sgb;
    double b = xyz->x * sbr + xyz->y * sbg + xyz->z * sbb;
    
    srgb->r = gammaCorrection(r);
    srgb->g = gammaCorrection(g);
    srgb->b = gammaCorrection(b);
    srgb->error = NULL;
    
    return srgb;
}

Xyz *getXyzFromSrgb(SRgb *srgb) {
    Xyz *xyz = malloc(sizeof(Xyz));
    if (xyz == NULL) {
        return NULL;
    }
    
    if (srgb == NULL) {
        xyz->error = NULL_INPUT_PARAM;
        return xyz;
    }
    
    double _r = reverseGamma(srgb->r);
    double _g = reverseGamma(srgb->g);
    double _b = reverseGamma(srgb->b);
        
    xyz->x = _r * xr + _g * xg + _b * xb;
    xyz->y = _r * yr + _g * yg + _b * yb;
    xyz->z = _r * zr + _g * zg + _b * zb;
    xyz->error = NULL;
    
    free(srgb);
    
    return xyz;
}
