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
#include "errors.h"
#include "helper.h"
#include "hsv.h"
#include "hue.h"
#include "hue.h"

Hsv *getHsvFromRgb(Rgb *rgb) {
    Hsv *hsv = malloc(sizeof( Hsv));
    if (hsv == NULL) {
        return NULL;
    }
    
    if (rgb == NULL) {
        hsv->error = NULL_INPUT_PARAM;
        return hsv;
    }
    
    Hue hue = getHueFromRgb(rgb);
    double _r = (double) rgb->r;
    double _g = (double) rgb->g;
    double _b = (double) rgb->b;
    
    double min = getMinMax(_r, _g, _b, 1) / 255.0;
    double max = getMinMax(_r, _g, _b, 0) / 255.0;
    
    // delta
    double _delta = max - min;
    
    hsv->h = hue;
    hsv->v = roundDigit(max * 100.0, 10);
    
    if (max > 0.0) {
        hsv->s = roundDigit((_delta / max) * 100.0, 10);
    } else {
        hsv->s = 0.0;
    }
    
    free(rgb);
    return hsv;
}

/**
 * @brief Return an RGB based only on Value
 * @param hsv a pointer to the Hsv ure
 * @param rgb Rgb pointer
 */
static void getValueRGB(Hsv *hsv, Rgb *rgb) {
    double v = doubleToUint((hsv->v / 100) * 255);
    rgb->r = v;
    rgb->g = v;
    rgb->b = v;
    
    free(hsv);
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
    Rgb *rgb = malloc(sizeof(Rgb));
    if (rgb == NULL) {
        return NULL;
    }
    
    if (hsv == NULL) {
        rgb->error = NULL_INPUT_PARAM;
        return rgb;
    }
    
    if (!hsv->s) {
        getValueRGB(hsv, rgb);
        return rgb;
    }
    
    double _hue = hsv->h / 60.0;
    int i = (int) _hue;
    double _factor = _hue - i;
    
    double _v = hsv->v / 100.0;
    double _s = hsv->s / 100.0;
    
    double _p = _v * (1.0 - _s);
    double _q = _v * (1.0 - (_s * _factor));
    double _t = _v * (1.0 - (1.0 - _factor) * _s);
    
    // convert to uint the value
    uint8_t up = doubleToUint(_p * 255.0);
    uint8_t uq = doubleToUint(_q * 255.0);
    uint8_t ut = doubleToUint(_t * 255.0);
    uint8_t uv = doubleToUint(_v * 255.0);
    
    
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
