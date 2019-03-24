//
//  tint.h
//  lymui
//
//  Created by Marc Intha on 22/03/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#ifndef tint_h
#define tint_h

#include <stdio.h>
#include "hsl.h"
#include "rgb.h"

#define it 10

/**
 * @brief Tint structure
 */
typedef struct Tint {
    Hsl **tint;
    char *error;
} Tint;

/**
 * @brief Generate a tint
 * @param rgb Rgb
 * @return Tint ptr
 */
Tint *getTint(Rgb *rgb);

/**
 * @brief Release the memory of the generated tint
 * @param tint Tint ptr
 * @return uint8_t
 */
uint8_t releaseTint(Tint *tint);

#endif /* tint_h */
