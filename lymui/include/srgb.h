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

#define srr 3.2406
#define srg -1.5732
#define srb -0.4986

#define sgr -0.9789
#define sgg 1.8758
#define sgb 0.0415

#define sbr 0.0557
#define sbg -0.2040
#define sbb 1.0570

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

#endif /* srgb_h */
