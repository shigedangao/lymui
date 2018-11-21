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

#define srr 3.2406f
#define srg -1.5732f
#define srb -0.4986f

#define sgr -0.9789f
#define sgg 1.8758f
#define sgb 0.0415f

#define sbr 0.0557f
#define sbg -0.2040f
#define sbb 1.0570f

/**
 * @brief a structure defining the sRgb value. It's store float as the sRGB color space value use decimal
 */
typedef struct SRgb {
    float r;
    float g;
    float b;
} SRgb;

/**
 * @discussion get SRgb From Xyz return a new sRgb structure pointer
 * @param xyz a struct pointer Xyz
 * @return sRgb a struct pointer of type sRgb
 */
SRgb *getSRgbFromXyz(Xyz *xyz);

#endif /* srgb_h */
