//
//  ycbcr.h
//  lymui
//
//  Created by Marc on 12/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef ycbcr_h
#define ycbcr_h

#include <stdio.h>
#include "rgb.h"

// Struct Ycbcr
typedef struct Ycbcr {
    uint8_t y;
    uint8_t cb;
    uint8_t cr;
} Ycbcr;

/*!
 * @discussion Create a Ycbcr struct pointer from an Rgb struct
 * @param rgb a RGB structure
 * @return a Ycbcr struct pointer
 */
Ycbcr *makeYcbcr(Rgb *rgb);

/*!
 * @discussion Create a uint_8t array which describe the colors
 * @param yc Ycbcr struct
 * @return a uint8_t array
 * @TODO return RGB struct instead
 */
Rgb * getRawRGBValueFromYcbcr(Ycbcr *yc);

#endif /* ycbcr_h */
