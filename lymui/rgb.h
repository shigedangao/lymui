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

struct Rgb {
    ushort r;
    ushort g;
    ushort b;
};

// Make RGB
struct Rgb* makeRGB(ushort c[]);

// Make RGB From Hex
struct Rgb* makeRGBFromHex(char str[]);

// Free RGB
void freeRgb(struct Rgb *c);

#endif /* rgb_h */
