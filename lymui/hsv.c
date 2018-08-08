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
#include "hue.h"

Hsv *getHsvFromRgb(Rgb *rgb) {
    if (rgb == NULL)
        return NULL;
    
    Hue hue = getHueFromRgb(rgb);
    float min = fminf(fminf(rgb->r, rgb->g), rgb->b) / 255;
    float max = fmaxf(fmaxf(rgb->r, rgb->g), rgb->b) / 255;
    
    // delta
    float _delta = max - min;
    
    Hsv *hsv = malloc(sizeof( Hsv));
    hsv->h = hue;
    hsv->v = roundDigit(max * 100, 10);
    
    if (max > 0.0f) {
        hsv->s = roundDigit(_delta / max, 10) * 100;
    } else {
        hsv->s = 0.0f;
    }
    
    free(rgb);
    return hsv;
}

/**
 * @discussion Return an RGB based only on Value
 * @param hsv a pointer to the Hsv ure
 * @return Rgb  pointer
 */
static  Rgb *getValueRGB(Hsv *hsv) {
    float v = floatToUint((hsv->v / 100) * 255);
    
     Rgb *rgb = malloc(sizeof( Rgb));
    rgb->r = v;
    rgb->g = v;
    rgb->b = v;
    
    free(hsv);
    
    return rgb;
}

/**
 * @discussion assign value to an rgb
 * @param r uint8_t
 * @param g uint8_t
 * @param b uint8_t
 * @param rgb  Rgb pointer
 */
static void putRgb(uint8_t r, uint8_t g, uint8_t b, Rgb *rgb) {
    rgb->r = r;
    rgb->g = g;
    rgb->b = b;
}

Rgb *getRgbValueFromHsv(Hsv *hsv) {
    if (hsv == NULL)
        return NULL;
    
    if (!hsv->s)
        return getValueRGB(hsv);
    
    float _hue = hsv->h / 60;
    int i = (int) _hue;
    float _factor = _hue - i;
    
    float _v = hsv->v / 100;
    float _s = hsv->s / 100;
    
    float _p = _v * (1.0f - _s);
    float _q = _v * (1.0f - (_s * _factor));
    float _t = _v * (1.0f - (1.0f - _factor) * _s);
    
    // convert to uint the value
    uint8_t up = floatToUint(_p * 255);
    uint8_t uq = floatToUint(_q * 255);
    uint8_t ut = floatToUint(_t * 255);
    uint8_t uv = floatToUint(_v * 255);
    
    Rgb *rgb = malloc(sizeof(Rgb));
    
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
            putRgb(uv, up, ut, rgb);
    }
    
    free(hsv);
    return rgb;
}
