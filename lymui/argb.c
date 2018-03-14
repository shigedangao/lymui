//
//  argb.c
//  lymui
//
//  Created by Marc on 14/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <math.h>
#include <stdlib.h>
#include "argb.h"

/**
 * @discussion Adobe Gamma Correction adjust the Float value to based generated
 * @param c float
 * @return c float
 */
static float adobeGammaCorrection(float c) {
    if (c <= 0.0f)
        return 0.0f;
    
    if (c >= 1.0f)
        return 1.0f;
    
    return powf(c, 1 / 2.19921875f);
}

struct aRgb *getARgbFromXyz(struct Xyz *xyz) {
    if (xyz == NULL)
        return NULL;
    
    float r = xyz->x * rr + xyz->y * rg + xyz->z * rb;
    float g = xyz->x * gr + xyz->y * gg + xyz->z * gb;
    float b = xyz->x * br + xyz->y * bg + xyz->z * bb;
    
    struct aRgb *argb = malloc(sizeof(struct aRgb));
    
    argb->r = adobeGammaCorrection(r);
    argb->g = adobeGammaCorrection(g);
    argb->b = adobeGammaCorrection(b);
    
    return argb;
}
