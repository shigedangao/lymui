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

/*!
 * @brief Hsl structure
 */
struct Hsl {
    float h;
    float s;
    float l;
};

/*!
 * @discussion Create an Hsl struct from an Rgb Struct
 * @param rgb an rgb struct pointer
 * @return a struct Hsl pointer
 */
struct Hsl *getHslFromRgb(struct Rgb *rgb);

/*!
 * @discussion Get Rgb Value From Hsl
 * @param hsl an Hsl structure
 * @return rgb structure
 */
struct Rgb *getRgbValueFromHsl(struct Hsl *hsl);

#endif /* hsl_h */
