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
uint8_t * getRawRGBArrayValueFromHex(char *hex);

// Calculate RGB Value from Hex
void calculateRGBValue(uint8_t x, uint8_t y, uint8_t idx, uint8_t *arr);

// Set Value
uint8_t setValue(char *value, uint8_t var);

uint8_t getUintCharValue(char v);

#endif /* hex_h */
