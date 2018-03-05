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

/**
 * @discussion assign value to an rgb struct
 * @param r uint8_t
 * @param g uint8_t
 * @param b uint8_t
 * @param rgb struct Rgb pointer
 */
static void putRgb(uint8_t r, uint8_t g, uint8_t b, struct Rgb *rgb) {
    rgb->r = r;
    rgb->g = g;
    rgb->b = b;
}

struct Rgb *getRgbValueFromHsv(struct Hsv *hsv) {
    if (hsv == NULL)
        return NULL;
    
    if (!hsv->s)
        return getValueRGB(hsv);
    
    float _hue = hsv->h >= 360 ? 0.0f : hsv->h / 60;
    int i = (int) _hue;
    float _factor = _hue - i;
    
    float _v = hsv->v / 100;
    float _s = hsv->s / 100;
    
    float _p = _v * (1.0f - _s);
    float _q = _v * (1.0f - (_s * _factor));
    float _t = _v * (1.0f - (1.0f - _factor) * _s);
    
    // convert to uint the value
    uint8_t up = floatToUintRound(_p * 255);
    uint8_t uq = floatToUintRound(_q * 255);
    uint8_t ut = floatToUintRound(_t * 255);
    uint8_t uv = floatToUintRound(_v * 255);
    
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    
    switch(i) {
        case 0:
            putRgb(uv, ut, up, rgb);
            break;
        case 1:
            putRgb(uq, uv, up, rgb);
            break;
        case 2:
            putRgb(up, uv, ut, rgb);
            break;
        case 3:
            putRgb(up, uq, uv, rgb);
            break;
        case 4:
            putRgb(ut, up, uv, rgb);
            break;
        default:
            putRgb(uv, up, uq, rgb);
    }
    
    free(hsv);
    return rgb;
}
