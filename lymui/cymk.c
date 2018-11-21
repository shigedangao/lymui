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
#include "errors.h"
#include "helper.h"

// Get Cymk From Rgb
Cymk *getCymkFromRgb(Rgb *rgb, int clamp) {
    Cymk *cymk = malloc(sizeof(Cymk));
    if (cymk == NULL) {
        return NULL;
    }
    
    if (rgb == NULL) {
        cymk->error = NULL_INPUT_STRUCT;
        return cymk;
    }
    
    // Calculate the derived value
    double _r = rgb->r / 255.0;
    double _g = rgb->g / 255.0;
    double _b = rgb->b / 255.0;
    
    // get the max value
    double _m = fmaxf(fmaxf(_r, _g), _b);
    // Calculate the K value
    double _k = 1.0 - _m;
    
    cymk->k = roundDecimal(_k, clamp);
    if (_k != 1.0) {
        cymk->c = roundDecimal((1.0 - _r - _k) / (1.0 - _k), clamp);
        cymk->m = roundDecimal((1.0 - _g - _k) / (1.0 - _k), clamp);
        cymk->y = roundDecimal((1.0 - _b - _k) / (1.0 - _k), clamp);
    } else {
        cymk->c = 0.0;
        cymk->m = 0.0;
        cymk->y = 0.0;
    }
    
    return cymk;
}

Rgb *getRgbFromCymk(Cymk *cymk) {
    if (cymk == NULL) {
        return NULL;
    }
    
    uint8_t *value = malloc(sizeof(uint8_t) * 3);
    
    float _kv = 1 - cymk->k;
    float r = 255 * (1 - cymk->c) * _kv;
    float g = 255 * (1 - cymk->m) * _kv;
    float b = 255 * (1 - cymk->y) * _kv;
    
    value[0] = floatToUint(r);
    value[1] = floatToUint(g);
    value[2] = floatToUint(b);
    
    Rgb *rgb = makeRGB(value, 3);
    free(value);
    return rgb;
}
