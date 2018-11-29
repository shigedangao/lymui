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

#define srr 3.2406
#define srg -1.5732
#define srb -0.4986

#define sgr -0.9789
#define sgg 1.8758
#define sgb 0.0415

#define sbr 0.0557
#define sbg -0.2040
#define sbb 1.0570

// SRGB -> XYZ

#define xsr 0.4124
#define xsg 0.3576
#define xsb 0.1805

#define ysr 0.2126
#define ysg 0.7152
#define ysb 0.0722

#define zsr 0.0193
#define zsg 0.1192
#define zsb 0.9505

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
