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
 * @discussion Get the saturation between 2 values
 * @param min float value of the rgb struct
 * @param max float value of the rgb struct
 * @param l   float representing the luminance
 * @return float saturation
 */
float getSaturation(float min, float max, float l);

/*!
 * @discussion Get Rgb Value From Hsl
 * @param hsl an Hsl structure
 * @return rgb structure
 */
struct Rgb *getRgbValueFromHsl(struct Hsl *hsl);

/*!
 * @discussion Get the shade of grey from an HSL
 * @param hsl representing the Luminance
 * @return struct Rgb an rgb struct describing the shade of grey
 */
static struct Rgb *getShadeOfGray(struct Hsl *hsl);

/*!
 * @discussion Get an array of temp _rgb value
 * @param hue a float describing the hue
 * @return an array of float rgb color
 */
static float *getTempRgbValue(float hue);

/*!
 * @discussion Calculate the based on each _temp c pass
 * @param c a float temp color
 * @param temp_m a temporary luminance based on the value of the luminace
 * @param temp_l a temporary luminance based on the temp_m and the current luminance
 */
static float calculateEachColoralue(float c, float temp_m, float temp_l);


#endif /* hsl_h */
