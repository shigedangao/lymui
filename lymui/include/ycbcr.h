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
    float y;
    float cb;
    float cr;
};

// Make Ycbcr
struct Ycbcr *makeYcbcr(struct Rgb *rgb);

// Get Raw RGB Array Value From Ycbcr
uint8_t * getRawRGBArrayValueFromYcbcr(struct Ycbcr *yc);

#endif /* ycbcr_h */
