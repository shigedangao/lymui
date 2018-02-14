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
struct Rgb* makeRGB(uint8_t c[], uint8_t length);

// Make RGB From Arr Pointer
struct Rgb* makeRGBFromArrPointer(uint8_t *c, uint8_t length);

#endif /* rgb_h */
