//
//  hex.h
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef hex_h
#define hex_h

#include <stdio.h>
#include "rgb.h"

// Get Hex From RGB
// Return --> char array
// Params --> struct pointer Rgb
char * getHexFromRGB(struct Rgb *c);

// Get Raw RGB Array Value From Hex
ushort * getRawRGBArrayValueFromHex(char *hex);

// Calculate RGB Value from Hex
void calculateRGBValue(ushort x, ushort y, ushort idx, ushort *arr);

// Set Value
ushort setValue(char *value, ushort var);

#endif /* hex_h */
