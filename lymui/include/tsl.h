//
//  tsl.h
//  lymui
//
//  Created by Marc Intha on 05/01/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#ifndef tsl_h
#define tsl_h

#include <stdio.h>
#include "rgb.h"

/**
 * @brief Tsl struct
 */
typedef struct Tsl {
    double t;
    double s;
    double l;
    char *error;
} Tsl;

/**
 * @brief get a Tsl struct from an Rgb struct
 *      Calculation based on this wiki: https://en.wikipedia.org/wiki/TSL_color_space
 *      Other reference: https://stackoverflow.com/questions/43696998/tsltorgb-colorspace-conversion/43712296#43712296
 * @param rgb Rgb struct
 * @return tsl Tsl struct
 */
Tsl *getTslFromRgb(Rgb *rgb);

/**
 * @brief get a Rgb struct from a Tsl struct
 * @param tsl Tsl struct
 * @return rgb Rgb struct
 */
Rgb *getRgbFromTsl(Tsl *tsl);

#endif /* tsl_h */
