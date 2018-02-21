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

float *updateConstraintValue(float *value, uint8_t size) {
    for (uint8_t idx = size; idx > 0; idx--) {
        if (value[idx] < 0.0f) {
            value[idx] = value[idx] + 1;
        } else if (value[idx] > 1.0f) {
            value[idx] = value[idx] - 1;
        }
    }
    
    return value;
}


