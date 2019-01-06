//
//  grayscale.h
//  lymui
//
//  Created by Marc Intha on 06/01/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#ifndef grayscale_h
#define grayscale_h

#include <stdio.h>
#include "rgb.h"

/**
 * @brief an uint representing the gray color (from 0 to 255)
 */
typedef uint8_t Gray;

/**
 * @brief strategy for calculating the grayscale
 */
typedef enum Strategy {
    Lightness,
    Average,
    Luminosity,
    bt709,
    bt2100
} Strategy;

/**
 * @brief get gray scale from an RGB. All calcation are based from these articles
 *        https://www.johndcook.com/blog/2009/08/24/algorithms-convert-color-grayscale/
 *        https://en.wikipedia.org/wiki/Grayscale
 * @param rgb Rgb struct
 * @param s Strategy
 * @return uint8_t gray
 */
Gray getGrayScale(Rgb *rgb, Strategy s);

#endif /* grayscale_h */
