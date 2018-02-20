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

float * getMinMaxValue(float * value, int size) {
    if (!size)
        return 0;
    
    float _m = value[size];
    float _mn = value[size];
    for (int idx = size; idx >= 0; idx--) {
        if (value[idx] > _m)
            _m = value[idx];
        else if (value[idx] < _mn)
            _mn = value[idx];
    }
    
    float * minmax = malloc(sizeof(float) * 2);
    minmax[0] = _mn;
    minmax[1] = _m;
    
    return minmax;
}


