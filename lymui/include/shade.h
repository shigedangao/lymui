//
//  shade.h
//  lymui
//
//  Created by Marc Intha on 17/03/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#ifndef shade_h
#define shade_h

#include <stdio.h>
#include "hsl.h"
#include "hsv.h"
#include "rgb.h"

#define it 10

/**
 * @brief generating a shade
 */
typedef struct Shade {
    Hsl **shade;
    char *error;
} Shade;

/**
 * @brief generate a shade
 * @param rgb Rgb
 * @return Shade ptr
 */
Shade *getShade(Rgb *rgb);

/**
 * @brief Release memory allocated for generating the shade
 * @param shade Shade ptr
 * @return uint8_t
 */
uint8_t releaseShade(Shade *shade);

#endif /* shade_h */
