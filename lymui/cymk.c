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
Cymk *getCymkFromRgb(Rgb *rgb) {
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
    double _m = fmax(fmax(_r, _g), _b);
    // Calculate the K value
    double _k = 1.0 - _m;
    
    cymk->k = _k;
    if (_k != 1.0) {
        cymk->c = (1.0 - _r - _k) / (1.0 - _k);
        cymk->m = (1.0 - _g - _k) / (1.0 - _k);
        cymk->y = (1.0 - _b - _k) / (1.0 - _k);
    } else {
        cymk->c = 0.0;
        cymk->m = 0.0;
        cymk->y = 0.0;
    }
    
    return cymk;
}

Rgb *getRgbFromCymk(Cymk *cymk) {
    Rgb *rgb = initRgb();
    if (rgb == NULL) {
        return NULL;
    }
    
    if (cymk == NULL) {
        rgb->error = NULL_INPUT_PARAM;
        return rgb;
    }
    
    uint8_t *value = malloc(sizeof(uint8_t) * 3);
    if (value == NULL) {
        rgb->error = MALLOC_ERROR;
        return rgb;
    }
    
    double _kv = 1.0 - cymk->k;
    double r = 255.0 * (1.0 - cymk->c) * _kv;
    double g = 255.0 * (1.0 - cymk->m) * _kv;
    double b = 255.0 * (1.0 - cymk->y) * _kv;
    
    rgb->r = doubleToUint(r);
    rgb->g = doubleToUint(g);
    rgb->b = doubleToUint(b);
    
    free(value);
    return rgb;
}
