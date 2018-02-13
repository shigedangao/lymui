//
//  helper.c
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "helper.h"

// Global variable of a list of RgbHex
struct RgbHex *list;

// Ushort To Hex
char * ushortToHex(uint8_t v) {
    if (v > 255)
        return NULL;
    
    char HEX[] = "0123456789ABCDEF";
    char *hexa = malloc(1);
    uint8_t accum = 2;
    while(accum > 0) {
        hexa[accum - 1] = HEX[(v % 16)];
        v = v / 16;
        accum--;
    }
    
    return hexa;
}

// Float To Uint
uint8_t floatToUint(float value) {
    if (fabsf(value) != value)
        return 0;
    
    return (uint8_t) value;
}

