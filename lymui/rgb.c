//
//  rgb.c
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "rgb.h"
#include "helper.h"
#include <stdlib.h>



// Make RGB
// Return RGB struct pointer
// Params : Array of ushort length 3
struct Rgb *makeRGB(uint8_t *c) {
    struct Rgb *color = malloc (sizeof (struct Rgb));
    
    if (color == NULL)
        return NULL;
    
    int isArrayInvalidValid = (sizeof(c) / sizeof(c[0])) < 3;
    
    if (isArrayInvalidValid) {
        free(color);
        return NULL;
    }
    
    color->r = c[0];
    color->g = c[1];
    color->b = c[2];
    
    return color;
}

// Free Rgb
void freeRgb(struct Rgb *c) {
    free(c);
}
