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

/*!
 * @brief Cymk structure Object
 */
struct Cymk {
    // C value
    float c;
    // Y value
    float y;
    // M value
    float m;
    // K value
    float k;
};

/*!
 * @discussion Create a Cymk struct pointer from an Rgb struct
 * @param rgb a RGB structure
 * @return a uint8_t array
 */
struct Cymk *getCymkFromRgb(struct Rgb *rgb);

/*!
 * @discussion Creates a uint8_t array from a Cymk struct pointer
 * @param cymk a Cymk structure
 * @return a uint8_t array
 * @TODO return RGB struct instead
 */
uint8_t * getRawRGBArrayValueFromCymk(struct Cymk *cymk);

#endif /* cymk_h */
