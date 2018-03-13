//
//  srgb.h
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef srgb_h
#define srgb_h

#include <stdio.h>
#include "xyz.h"
#include "rgb.h"

#define rr 3.2406f
#define rg -1.5732f
#define rb -0.4986f

#define gr -0.9789f
#define gg 1.8758f
#define gb 0.0415f

#define br 0.0557f
#define bg -0.2040f
#define bb 1.0570f

/**
 * @brief a structure defining the sRgb value. It's store float as the sRGB color space value use decimal
 */
struct sRgb {
    float r;
    float g;
    float b;
};

/**
 * @discussion get SRgb From Xyz return a new sRgb structure pointer
 * @param xyz a struct pointer Xyz
 * @return sRgb a struct pointer of type sRgb
 */
struct sRgb *getSRgbFromXyz(struct Xyz *xyz);

#endif /* srgb_h */
