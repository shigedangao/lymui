//
//  rgb.c
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <stdint.h>
#include "rgb.h"
#include "helper.h"



// Make RGB
// Return RGB struct pointer
// Params : Array of ushort length 3
Rgb *makeRGB(uint8_t c[], uint8_t length) {
    struct Rgb *color = malloc (sizeof (struct Rgb));
    
    if (color == NULL)
        return NULL;
    
    uint8_t isArrayInvalidValid = length != 3;
    if (isArrayInvalidValid) {
        free(color);
        return NULL;
    }
    
    color->r = c[0];
    color->g = c[1];
    color->b = c[2];
    
    return color;
}
