//
//  argb.c
//  lymui
//
//  Created by Marc on 14/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <math.h>
#include <stdlib.h>
#include "errors.h"
#include "argb.h"
#include "rgb.h"
#include "xyz_constant.h"

/**
 * @brief Adobe Gamma Correction adjust the double value to based generated
 * @param c double
 * @return c double
 */
static double adobeGammaCorrection(double c) {
    if (c <= 0.0)
        return 0.0;
    
    if (c >= 1.0)
        return 1.0;
    
    return pow(c, 1 / 2.19921875);
}

/**
 * @brief Reverse ARgb Gamma
 * @param c double
 * @return c double
 */
static double reverseARgbGamma(double c) {
    if (c <= 0.0) {
        return 0.0;
    }
    
    if (c >= 1.0) {
        return 1.0;
    }
    
    return pow(c, 2.19921875);
}

Argb *getARgbFromXyz(Xyz *xyz) {
    Argb *argb = malloc(sizeof(Argb));
    if (argb == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        argb->error = NULL_INPUT_STRUCT;
        return argb;
    }
    
    double r = xyz->x * rr + xyz->y * rg + xyz->z * rb;
    double g = xyz->x * gr + xyz->y * gg + xyz->z * gb;
    double b = xyz->x * br + xyz->y * bg + xyz->z * bb;
    
    argb->r = adobeGammaCorrection(r);
    argb->g = adobeGammaCorrection(g);
    argb->b = adobeGammaCorrection(b);
    argb->error = NULL;
        
    return argb;
}

Xyz *getXyzFromARgb(Argb *argb) {
    Xyz *xyz = malloc(sizeof(Xyz));
    if (xyz == NULL) {
        return NULL;
    }

    if (argb == NULL) {
        xyz->error = NULL_INPUT_PARAM;
        return xyz;
    }

    double _r = reverseARgbGamma(argb->r);
    double _g = reverseARgbGamma(argb->g);
    double _b = reverseARgbGamma(argb->b);

    xyz->x = _r * axr + _g * axg + _b * axb;
    xyz->y = _r * ayr + _g * ayg + _b * ayb;
    xyz->z = _r * azr + _g * azg + _b * azb;
    xyz->error = NULL;
    
    free(argb);
    
    return xyz;
}
