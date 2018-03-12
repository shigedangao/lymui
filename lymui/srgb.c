//
//  srgb.c
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include "srgb.h"

struct sRgb *getSRgbFromRgb(struct Rgb *rgb) {
    if (rgb == NULL)
        return NULL;
    
    float _r = rgb->r / 255;
    float _g = rgb->g / 255;
    float _b = rgb->b / 255;
    
    return NULL;
}
