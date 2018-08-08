//
//  argb.h
//  lymui
//
//  Created by Marc on 14/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef argb_h
#define argb_h

#include <stdio.h>
#include "xyz.h"

#define rr 2.0415f
#define rg -0.565f
#define rb -0.3447f

#define gr -0.9692f
#define gg 1.8759f
#define gb 0.0415f

#define br 0.0134f
#define bg -0.1183f
#define bb 1.0151f

/**
 * @brief aRgb is a struct which is use for representing the adobe RGB
 */
typedef struct aRgb {
    float r;
    float g;
    float b;
} ARgb;

/**
 * @discussion Get ARgb From Xyz return a aRgb structure from a Xyz structure
 * @param xyz Xyz struct
 * @return aRgb struct
 */
ARgb * getARgbFromXyz(Xyz *xyz);

#endif /* argb_h */
