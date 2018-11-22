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

/**
 * @discussion Adobe Gamma Correction adjust the double value to based generated
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
    
    free(xyz);
    
    return argb;
}
