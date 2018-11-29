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
 * @return * xyz double
 */
static double gammaCorrection(double c) {
    if (c <= 0.0031308) {
        return c * 12.92;
    }
    
    return 1.055 * pow(c, 1 / 2.4) - 0.055;
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
