//
//  rgb.c
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include "rgb.h"
#include "errors.h"
#include "helper.h"


Rgb *makeRGB(uint8_t c[], size_t length) {
    Rgb *color = malloc(sizeof(Rgb));
    if (color == NULL) {
        return NULL;
    }
    
    if (c == NULL || !length) {
        color->error = NULL_INPUT_PARAM;
        return color;
    }
    
    uint8_t isArrayInvalidValid = length != RGB_ARRAY_LEN;
    if (isArrayInvalidValid) {
        color->error = WRONG_INPUT_PARAM;
        return color;
    }
    
    color->r = c[0];
    color->g = c[1];
    color->b = c[2];
    
    return color;
}

Rgb *initRgb() {
    Rgb *rgb = malloc(sizeof(Rgb));
    if (rgb == NULL) {
        return NULL;
    }
    
    return rgb;
}
