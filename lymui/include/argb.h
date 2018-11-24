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

#define rr 2.0415
#define rg -0.565
#define rb -0.3447

#define gr -0.9692
#define gg 1.8759
#define gb 0.0415

#define br 0.0134
#define bg -0.1183
#define bb 1.0151

/**
 * @brief aRgb is a struct which is use for representing the adobe RGB
 */
typedef struct Argb {
    double r;
    double g;
    double b;
    char *error;
} Argb;

/**
 * @brief Get ARgb From Xyz return a aRgb structure from a Xyz structure
 * @param xyz Xyz struct
 * @return aRgb struct
 */
Argb *getARgbFromXyz(Xyz *xyz);

#endif /* argb_h */
