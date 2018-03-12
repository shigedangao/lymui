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
#include "rgb.h"

/**
 * @brief a structure defining the sRgb value. It's store float as the sRGB color space value use decimal
 */
struct sRgb {
    float r;
    float g;
    float b;
};

/**
 * @discussion getSRgbFromRgb return a new sRgb structure pointer
 * @param rgb a struct pointer RGB
 * @return sRgb a struct pointer of type sRgb
 */
struct sRgb *getSRgbFromRgb(struct Rgb *rgb);

#endif /* srgb_h */
