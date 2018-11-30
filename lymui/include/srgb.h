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

// XYZ -> SRGB

#define srr 3.2404542
#define srg -1.5371385
#define srb -0.4985314

#define sgr -0.9692660
#define sgg 1.8760108
#define sgb 0.0415560

#define sbr 0.0556434
#define sbg -0.2040259
#define sbb 1.0572252

/**
 * @brief a structure defining the sRgb value. It's store float as the sRGB color space value use decimal
 */
typedef struct SRgb {
    double r;
    double g;
    double b;
    char *error;
} SRgb;

/**
 * @brief get SRgb From Xyz return a new sRgb structure pointer
 * @param xyz a struct pointer Xyz
 * @return sRgb a struct pointer of type sRgb
 */
SRgb *getSRgbFromXyz(Xyz *xyz);

/**
 * @brief get XYZ from SRGB struct
 * @param srgb Srgb
 * @return xyz
 */
Xyz *getXyzFromSrgb(SRgb *srgb);

#endif /* srgb_h */
