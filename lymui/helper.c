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

char * uintToHex(uint8_t color) {
    if (color > 255)
        return NULL;
    
    char HEX[] = "0123456789ABCDEF";
    char *hexa = malloc(2);
    
    uint8_t accum = 2;
    
    while(accum > 0) {
        hexa[accum - 1] = HEX[(color % 16)];
        color = color / 16;
        accum--;
    }
    
    return hexa;
}

uint8_t floatToUint(float value) {
    if (fabsf(value) == value)
        return (uint8_t) round(value);
    
    return 0;
}

uint8_t doubleToUint(double value) {
    if (fabs(value) == value)
        return (uint8_t) round(value);
    
    return 0;
}

float roundDigit(float value, int factor) {
    return roundf(value * factor) / factor;
}

float roundDecimal(float value, int decimal) {
    return floorf(value * decimal) / decimal;
}

float getSaturation(float min, float max, float l) {
    // big condition... we also check if max and min is not equal to 1 in order to avoid dividing by 0...
    if (l > 0.5f && (max != 1.0f || min != 1.0f))
        return (max - min) / (2.0f - max - min);
    
    // prevent dividing by 0
    if (!max && !min) {
        return 0;
    }

    return (max - min) / (max + min);
}

float *updateConstraintValue(float *value, uint8_t size) {
    for (uint8_t idx = size; idx > 0; idx--) {
        float temp = value[idx - 1];
        if (temp < 0.0f) {
            value[idx - 1] = temp + 1.0f;
        } else if (temp > 1.0f) {
            value[idx - 1] = temp - 1.0f;
        }
    }
    
    return value;
}

float getDegFromRad(float r) {
    return r * (180.0f / M_PI);
}

float getRadFromDeg(float d) {
    return d * M_PI / 180.0f;
}

float clampXyz(float v) {
//    if (v > 1.0f) {
//        return 1.0f;
//    }
    
    return v;
}
