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

double roundDigit(double value, int factor) {
    return round(value * factor) / factor;
}

double roundDecimal(double value, int decimal) {
    return floor(value * decimal) / decimal;
}

double getSaturation(double min, double max, double l) {
    // big condition... we also check if max and min is not equal to 1 in order to avoid dividing by 0...
    if (l > 0.5 && (max != 1.0 || min != 1.0))
        return (max - min) / (2.0 - max - min);
    
    // prevent dividing by 0
    if (!max && !min) {
        return 0;
    }

    return (max - min) / (max + min);
}

double *updateConstraintValue(double *value, uint8_t size) {
    size_t idx = size;
    
    while(idx > 0) {
        double tmp = value[idx - 1];
        if (tmp < 0.0)
            value[idx - 1] = tmp + 1.0f;
        else if (tmp > 1.0)
            value[idx - 1] = tmp - 1.0f;
        
        idx--;
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
    return v;
}

double getMinMax(double r, double g, double b, uint8_t op) {
    if (op) {
        return fmin(fmin(r, g), b);
    }
    
    return fmax(fmax(r, g), b);
}
