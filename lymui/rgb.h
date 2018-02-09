//
//  rgb.h
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef rgb_h
#define rgb_h

#include <stdio.h>

// Rgb Struct
struct Rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// Make RGB
struct Rgb* makeRGB(uint8_t c[]);

// Make RGB From Hex
struct Rgb* makeRGBFromHex(char str[]);

// Free RGB
void freeRgb(struct Rgb *c);

#endif /* rgb_h */
