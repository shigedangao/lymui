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
struct Ycbcr {
    uint8_t y;
    uint8_t cb;
    uint8_t cr;
};

/*!
 * @discussion Create a Ycbcr struct pointer from an Rgb struct
 * @param rgb a RGB structure
 * @return a Ycbcr struct pointer
 */
struct Ycbcr *makeYcbcr(struct Rgb *rgb);

/*!
 * @discussion Create a uint_8t array which describe the colors
 * @param yc Ycbcr struct
 * @return a uint8_t array
 * @TODO return RGB struct instead
 */
uint8_t * getRawRGBArrayValueFromYcbcr(struct Ycbcr *yc);

#endif /* ycbcr_h */
