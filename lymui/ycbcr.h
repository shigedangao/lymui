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

#endif /* ycbcr_h */
