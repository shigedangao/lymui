//
//  hsl.h
//  lymui
//
//  Created by Marc on 21/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef hsl_h
#define hsl_h

#include <stdio.h>
#include "rgb.h"

/**
 * @brief Hsl structure
 */
typedef struct Hsl {
    float h;
    float s;
    float l;
} Hsl;

/**
 * @brief Create an Hsl struct from an Rgb Struct
 * @param rgb an rgb struct pointer
 * @return a struct Hsl pointer
 */
Hsl * getHslFromRgb(Rgb *rgb);

/**
 * @brief Get Rgb Value From Hsl
 * @param hsl an Hsl structure
 * @return rgb structure
 */
Rgb * getRgbValueFromHsl(Hsl *hsl);

#endif /* hsl_h */
