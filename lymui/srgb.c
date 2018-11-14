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
#include "srgb.h"

/**
 * @discussion Gamma Correction add gamma correction for linear sRGB
 * @param c float
 * @return * xyz float
 */
static float gammaCorrection(float c) {
    if (c <= 0.00313f) {
        return c * 12.92f;
    }
    
    return 1.055f * powf(c, 1 / 2.4) - 0.055f;
}

SRgb *getSRgbFromXyz(Xyz *xyz) {
    if (xyz == NULL)
        return NULL;
    
    float r = xyz->x * srr + xyz->y * srg + xyz->z * srb;
    float g = xyz->x * sgr + xyz->y * sgg + xyz->z * sgb;
    float b = xyz->x * sbr + xyz->y * sbg + xyz->z * sbb;
    
    SRgb *srgb = malloc(sizeof(SRgb));
    srgb->r = gammaCorrection(r);
    srgb->g = gammaCorrection(g);
    srgb->b = gammaCorrection(b);
    
    free(xyz);
    
    return srgb;
}
