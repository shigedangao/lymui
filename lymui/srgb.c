//
//  srgb.c
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include <math.h>
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

SRgb *getSRgbFromXyz(Xyz *xyz) {
    SRgb *srgb = malloc(sizeof(SRgb));
    if (srgb == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        srgb->error = NULL_INPUT_STRUCT;
        return srgb;
    }
    
    double r = xyz->x * srr + xyz->y * srg + xyz->z * srb;
    double g = xyz->x * sgr + xyz->y * sgg + xyz->z * sgb;
    double b = xyz->x * sbr + xyz->y * sbg + xyz->z * sbb;
    
    srgb->r = gammaCorrection(r);
    srgb->g = gammaCorrection(g);
    srgb->b = gammaCorrection(b);
    srgb->error = NULL;
    
    free(xyz);
    
    return srgb;
}

Xyz *getXyzFromSrgb(SRgb *srgb) {
    Xyz *xyz = malloc(sizeof(Xyz));
    if (xyz == NULL) {
        return NULL;
    }
    
    if (srgb == NULL) {
        xyz->error = NULL_INPUT_STRUCT;
        return xyz;
    }
    
    double _r = reverseGamma(srgb->r);
    double _g = reverseGamma(srgb->g);
    double _b = reverseGamma(srgb->b);
        
    xyz->x = _r * xsr + _g * xsg + _b * xsb;
    xyz->y = _r * ysr + _g * ysg + _b * ysb;
    xyz->z = _r * zsr + _g * zsg + _b * zsb;
    
    free(srgb);
    
    return xyz;
}
