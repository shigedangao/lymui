//
//  hex.c
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "hex.h"
#include "helper.h"
#include <stdlib.h>
#include <string.h>

// Get Hex From RGB
char * getHexFromRGB(struct Rgb *c) {
    char *r = ushortToHex(c->r);
    char *g = ushortToHex(c->g);
    char *b = ushortToHex(c->b);
    
    // create a char array of hex value
    char *hex = malloc(sizeof(char) * 5);
    snprintf(hex, sizeof(hex), "%s%s%s", r, g, b);
    return hex;
}

// Get RGB Value From Hex
ushort * getRawRGBArrayValueFromHex(char *hex) {
    ushort *rgbArr = malloc(sizeof (char) * 3);
    ushort idx = 0;
    // As we use the ushort we set 16 as our flag
    ushort x = 16,
           y = 16;
    
    struct RgbHex * list = getCorrespondingStruct();
    
    while (idx <= 6) {
        ushort isquot = idx % 2 == 0;
        for (int i = sizeof(list); i >= 0; i--) {
            if (list[i].id == hex[idx] && strlen(&hex[idx]) != 0) {
                if (isquot)
                    x = list[i].v;
                else
                    y = list[i].v;
            }
        }
        
        if (isquot)
            x = setValue(&hex[idx], x);
        else
            y = setValue(&hex[idx], y);
        
        if (isquot && idx != 0) {
            calculateRGBValue(x, y, idx, rgbArr);
            // reset x and y
            x = 16;
            y = 16;
        }
        
        idx++;
    }
    
    // Don't forget to free it after it's usage
    return rgbArr;
}

ushort setValue(char *value, ushort res) {
    if (res == 16) {
        res = (ushort) strtoul(value, NULL, 0);
    }
    
    return res;
}

// Calculate RGB Value
void calculateRGBValue(ushort x, ushort y, ushort idx, ushort * arr) {
    ushort isquot = idx % 2 == 0;
    if (x == 16 || y == 16) {
        return;
    } else if (!isquot) {
        return;
    }
    
    arr[(idx / 2) - 1] = x + (y * 16);
}

