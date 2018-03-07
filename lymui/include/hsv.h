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
#include "rgb.h"

/**
 * @brief Hsv data structure
 */
struct Hsv {
    float h;
    float s;
    float v;
};

/*!
 * @discussion Create an Hsv struct from an Rgb Struct
 * @param rgb an Rgb struct pointer
 * @return a struct Hsv pointer
 */
struct Hsv *getHsvFromRgb(struct Rgb *rgb);

/**
 * @discussion Get an RGB value from an HSV struct pointer
 * @param hsv an Hsv struct pointer
 * @return rgb a struct Rgb pointer
 */
struct Rgb *getRgbValueFromHsv(struct Hsv *hsv);

#endif /* hsv_h */


