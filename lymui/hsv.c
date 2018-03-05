//
//  hsv.c
//  lymui
//
//  Created by Marc on 01/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "helper.h"
#include "hsv.h"
#include "hue.h"

struct Hsv *getHsvFromRgb(struct Rgb *rgb) {
    if (rgb == NULL)
        return NULL;
    
    float hue = getHueFromRgb(rgb);
    float min = fminf(fminf(rgb->r, rgb->g), rgb->b) / 255;
    float max = fmaxf(fmaxf(rgb->r, rgb->g), rgb->b) / 255;
    
    // delta
    float _delta = max - min;
    
    struct Hsv *hsv = malloc(sizeof(struct Hsv));
    hsv->h = hue;
    hsv->v = roundOneDigit(max * 100);
    
    if (max > 0.0f) {
        hsv->s = roundOneDigit(_delta / max) * 100;
    } else {
        hsv->s = 0.0f;
    }
    
    free(rgb);
    return hsv;
}

/**
 * @discussion Return an RGB based only on Value
 * @param hsv a pointer to the Hsv structure
 * @return Rgb struct pointer
 */
static struct Rgb *getValueRGB(struct Hsv *hsv) {
    float v = hsv->v / 100;
    
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = v;
    rgb->g = v;
    rgb->b = v;
    
    free(hsv);
    
    return rgb;
}

struct Rgb *getRgbValueFromHsv(struct Hsv *hsv) {
    if (hsv == NULL)
        return NULL;
    
    if (!hsv->s && !hsv->h)
        return getValueRGB(hsv);
    
    float _hue = hsv->h >= 360 ? 0.0f : hsv->h / 60;
    int i = (int) _hue;
    float _factor = _hue - i;
    
    float _p = hsv->v * (1.0f - hsv->s);
    float _q = hsv->v * (1.0f - (hsv->s * _factor));
    float _t = hsv->v * (1.0f - (hsv->s * (1.0f * _factor)));
    
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    
    switch(i) {
        case 0:
            rgb->r = hsv->v;
            rgb->g = _t;
            rgb->b = _p;
            break;
        case 1:
            rgb->r = _q;
            rgb->g = hsv->v;
            rgb->b = _p;
            break;
        case 2:
            rgb->r = _p;
            rgb->g = hsv->v;
            rgb->b = _t;
            break;
        case 3:
            rgb->r = _p;
            rgb->g = _p;
            rgb->b = hsv->v;
            break;
        case 4:
            rgb->r = _t;
            rgb->g = _p;
            rgb->b = hsv->v;
            break;
        default:
            rgb->r = hsv->v;
            rgb->g = _p;
            rgb->b = _q;
    }
    
    free(hsv);
    return rgb;
}
