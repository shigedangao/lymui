//
//  cymk.c
//  lymui
//
//  Created by Marc on 15/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "cymk.h"
#include "rgb.h"
#include "helper.h"

// Get Cymk From Rgb
Cymk *getCymkFromRgb(Rgb *rgb, int clamp) {
    if (rgb == NULL)
        return NULL;
    
    // Calculate the derived value
    float _r = rgb->r / 255.0f;
    float _g = rgb->g / 255.0f;
    float _b = rgb->b / 255.0f;
    
    // get the max value
    float _m = fmaxf(fmaxf(_r, _g), _b);
    // Calculate the K value
    float _k = 1 - _m;
    
    Cymk *cymk = malloc(sizeof(Cymk));
    
    cymk->k = roundDecimal(_k, clamp);
    if (_k != 1.0f) {
        cymk->c = roundDecimal((1.0f - _r - _k) / (1.0f - _k), clamp);
        cymk->m = roundDecimal((1.0f - _g - _k) / (1.0f - _k), clamp);
        cymk->y = roundDecimal((1.0f - _b - _k) / (1.0f - _k), clamp);
    } else {
        cymk->c = 0.0f;
        cymk->m = 0.0f;
        cymk->y = 0.0f;
    }
    
    return cymk;
}

Rgb * getRawRGBValueFromCymk(Cymk *cymk) {
    if (cymk == NULL)
        return NULL;
    
    uint8_t *value = malloc(sizeof(uint8_t) * 3);
    const uint8_t _kv = 1 - cymk->k;
    
    value[0] = 255 * (1 - cymk->c) * _kv;
    value[1] = 255 * (1 - cymk->m) * _kv;
    value[2] = 255 * (1 - cymk->y) * _kv;
    
    Rgb *rgb = makeRGB(value, 3);
    free(value);
    return rgb;
}
