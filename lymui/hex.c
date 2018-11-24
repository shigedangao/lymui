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
#include "errors.h"
#include "hex.h"
#include "helper.h"

// Get Hex From RGB
char *getHexFromRGB(Rgb *c) {
    char *r = uintToHex(c->r);
    char *g = uintToHex(c->g);
    char *b = uintToHex(c->b);
    
    // create a char array of hex value
    char *hex = malloc(sizeof(char) * HEX_SIZE);
    if (hex == NULL) {
        return NULL;
    }
    
    snprintf(hex, HEX_SIZE, "%s%s%s", r, g, b);
    return hex;
}

// Get RGB Value From Hex
Rgb *getRGBFromHex(char *hex) {
    Rgb *rgb = initRgb();
    if (rgb == NULL) {
        return NULL;
    }
    
    if (hex == NULL) {
        rgb->error = NULL_INPUT_PARAM;
        return rgb;
    }
    
    // Make a copy of the pointer
    uint8_t *rgbArr = malloc(sizeof (char) * 3);
    if (rgbArr == NULL) {
        rgb->error = MALLOC_ERROR;
        return rgb;
    }
    
    uint8_t idx = 0;
    // As we use the ushort we set 16 as our flag
    while (idx < strlen(hex)) {
        int x = getUintCharValue(hex, idx);
        int y = getUintCharValue(hex, idx + 1);
        
        rgbArr[(idx / 2)] = y + (x * 16);
        idx = idx + 2;
    }
    
    // remove the pointer as we don't need it anymore
    rgb->r = rgbArr[0];
    rgb->g = rgbArr[1];
    rgb->b = rgbArr[2];
    
    free(hex);
    free(rgbArr);

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
        if (v == NULL) {
            // fail passive
            return 0;
        }
        
        v[0] = c[idx];
        n = strtol(v, NULL, 10);
        
        // don't forget to remove the pointer
        free(v);
    }
    
    return n;
}
