//
//  cymk.c
//  lymui
//
//  Created by Marc on 15/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include "cymk.h"
#include "rgb.h"
#include "helper.h"

// Get Cymk From Rgb
struct Cymk *getCymkFromRgb(struct Rgb *rgb) {
    if (rgb == NULL)
        return NULL;
    
    // Calculate the derived value
    float _r = rgb->r / 255.0f;
    float _g = rgb->g / 255.0f;
    float _b = rgb->b / 255.0f;
    
    // get max value between whose 3 calculate var
    float * _l = malloc(sizeof(float) * 2);
    _l[0] = _r;
    _l[1] = _g;
    _l[2] = _b;
    
    float _m = getMaxValue(_l, 2);
    // Calculate the K value
    float _k = 1 - _m;
    
    struct Cymk *cymk = malloc(sizeof(struct Cymk));
    
    cymk->k = _k;
    
    cymk->c = (1.0f - _r - _k) / (1.0f - _k);
    cymk->m = (1.0f - _g - _k) / (1.0f - _k);
    cymk->y = (1.0f - _b - _k) / (1.0f - _k);
    
    free(_l);
        
    return cymk;
}

struct Rgb * getRawRGBValueFromCymk(struct Cymk *cymk) {
    if (cymk == NULL)
        return NULL;
    
    uint8_t *value = malloc(sizeof(uint8_t) * 2);
    const uint8_t _kv = 1 - cymk->k;
    
    value[0] = 255 * (1 - cymk->c) * _kv;
    value[1] = 255 * (1 - cymk->m) * _kv;
    value[2] = 255 * (1 - cymk->y) * _kv;
    
    struct Rgb *rgb = makeRGB(value, 3);
    free(value);
    return rgb;
}
