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
#include <stdint.h>

#define RGB_ARRAY_LEN 3;

/**
 * @brief Rgb structure Object
 */
typedef struct Rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    char *error;
} Rgb;

/**
 * @brief Create an RGB structure from an uint8_t array
 * @param c a uint8_t array
 * @param length size_t
 * @return a Rgb struct
 */
Rgb *makeRGB(uint8_t c[], size_t length);

/**
 * @brief initialize an empty RGB struct
 */
Rgb *initRgb(void);

#endif /* rgb_h */
