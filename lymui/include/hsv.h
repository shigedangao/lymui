//
//  hsv.h
//  lymui
//
//  Created by Marc on 01/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef hsv_h
#define hsv_h

#include <stdio.h>
#include <stdint.h>
#include "rgb.h"

/**
 * @brief Hsv data structure
 */
typedef struct Hsv {
    double h;
    double s;
    double v;
    char *error;
} Hsv;

/**
 * @brief Create an Hsv struct from an Rgb Struct
 * @param rgb an Rgb struct pointer
 * @return a struct Hsv pointer
 */
Hsv *getHsvFromRgb(Rgb *rgb);

/**
 * @brief Get an RGB value from an HSV struct pointer
 * @param hsv an Hsv struct pointer
 * @return rgb a struct Rgb pointer
 */
Rgb *getRgbFromHsv(Hsv *hsv);

#endif /* hsv_h */


