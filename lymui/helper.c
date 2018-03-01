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

uint8_t floatToUint(float value) {
    if (fabsf(value) != value)
        return 0;
    
    return (uint8_t) value;
}

float roundOneDigit(float value) {
    return roundf(value * 10) / 10;
}

float getSaturation(float min, float max, float l) {
    if (l > 0.5f)
        return (max - min) / (2.0f - max - min);
    
    return (max - min) / (max + min);
}

float *updateConstraintValue(float *value, uint8_t size) {
    for (uint8_t idx = size; idx > 0; idx--) {
        if (value[idx - 1] < 0.0f) {
            value[idx - 1] = value[idx - 1] + 1.0f;
        } else if (value[idx - 1] > 1.0f) {
            value[idx - 1] = value[idx - 1] - 1.0f;
        }
    }
    
    return value;
}


