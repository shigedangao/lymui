//
//  cymk.h
//  lymui
//
//  Created by Marc on 15/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef cymk_h
#define cymk_h

#include <stdio.h>
#include "rgb.h"

/**
 * @brief Cymk structure Object
 */
typedef struct Cymk {
    // C value
    double c;
    // Y value
    double y;
    // M value
    double m;
    // K value
    double k;
    // error char
    char *error;
} Cymk;

/**
 * @brief Create a Cymk struct pointer from an Rgb struct
 * @param rgb a RGB structure
 * @param clamp int
 * @return a uint8_t array
 */
Cymk * getCymkFromRgb(Rgb *rgb, int clamp);

/**
 * @brief Creates a uint8_t array from a Cymk struct pointer
 * @param cymk a Cymk structure
 * @return a uint8_t array
 * @TODO return RGB struct instead
 */
Rgb * getRgbFromCymk(Cymk *cymk);

#endif /* cymk_h */
