//
//  rgb.h
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef rgb_h
#define rgb_h

#include <stdio.h>

/*!
 * @brief Rgb structure Object
 */
struct Rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

/*!
 * @discussion Create an RGB structure from an uint8_t array
 * @param c a uint8_t array
 * @param length the length of the array
 * @return a Rgb struct
 */
struct Rgb* makeRGB(uint8_t c[], uint8_t length);

struct Rgb* makeRGBFromArrPointer(uint8_t *c, uint8_t length);

#endif /* rgb_h */
