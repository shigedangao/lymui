//
//  hex.c
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "hex.h"
#include "helper.h"

// Get Hex From RGB
char * getHexFromRGB(struct Rgb *c) {
    char *r = ushortToHex(c->r);
    char *g = ushortToHex(c->g);
    char *b = ushortToHex(c->b);
    
    // create a char array of hex value
    char *hex = malloc(sizeof(char) * 5);
    snprintf(hex, sizeof(hex) / sizeof(hex[0]), "%s%s%s", r, g, b);
    return hex;
}

// Get RGB Value From Hex
struct Rgb * getRawRGBValueFromHex(char *hex) {
    if (hex == NULL)
        return NULL;
    
    // Make a copy of the pointer
    uint8_t *rgbArr = malloc(sizeof (char) * 3);
    uint8_t idx = 0;
    // As we use the ushort we set 16 as our flag
    
    while (idx < strlen(hex)) {
        int x = getUintCharValue(hex, idx);
        int y = getUintCharValue(hex, idx + 1);
        
        rgbArr[(idx / 2)] = y + (x * 16);
        idx = idx + 2;
    }
    
    // remove the pointer as we don't need it anymore
    free(hex);
    struct Rgb *rgb = makeRGB(rgbArr, 3);
    free(rgbArr);
    // Don't forget to free it after it's usage
    return rgb;
}

// Get Uint Char Value
// Though it could have been better than using a switch...
uint8_t getUintCharValue(char *c, uint8_t idx) {
    uint8_t n = 0;
    switch (c[idx]) {
        case 'A': n = 10; break;
        case 'B': n = 11; break;
        case 'C': n = 12; break;
        case 'D': n = 13; break;
        case 'E': n = 14; break;
        case 'F': n = 15; break;
    }
    
    if (n == 0) {
        char *v = malloc(sizeof(char));
        v[0] = c[idx];
        n = strtol(v, NULL, 10);
        
        // don't forget to remove the pointer
        free(v);
    }
    
    return n;
}
