//
//  hsl.c
//  lymui
//
//  Created by Marc on 21/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "helper.h"
#include "hue.h"
#include "rgb.h"
#include "hsl.h"

struct Hsl *getHslFromRgb(struct Rgb *rgb) {
    if (rgb == NULL)
        return NULL;
    
    float hue = getHueFromRgb(rgb);
    float min = fminf(fminf(rgb->r, rgb->g), rgb->b);
    float max = fmaxf(fmaxf(rgb->r, rgb->g), rgb->b);
    
    min = min / 255;
    max = max / 255;
    float _l = (min + max) / 2;
    
    struct Hsl *hsl = malloc(sizeof(struct Hsl));
    hsl->h = hue;
    hsl->s = roundOneDigit(getSaturation(min, max, _l) * 100);
    hsl->l = roundOneDigit(_l * 100);
    
    free(rgb);
    
    return hsl;
}

float getSaturation(float min, float max, float l) {
    if (l > 0.5f)
        return (max - min) / (2.0f - max - min);
    
    return (max - min) / (max + min);
}

struct Rgb *getRgbValueFromHsl(struct Hsl *hsl) {
    if (hsl == NULL) {
        return NULL;
    }
    
    if (!hsl->h && !hsl->s) {
        // return a gray shade rgb struct
        return getShadeOfGray(hsl);
    }
    
    // Create a new RGB struct
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    
    float _l = hsl->l / 100;
    float _s = hsl->s / 100;
    
    // choose the luminace formula
    float temp_lum = 0.0f;
    if (round(_l)) {
        temp_lum = (_l + _s) - (_l * _s);
    } else {
        temp_lum = _l * (1.0f + _s);
    }
    
    // get other temp value
    float temp_lum_s = 2.0f * _l - temp_lum;
    float *temp_rgb  = getTempRgbValue(hsl->h);
    
    rgb->r = calculateEachColoralue(temp_rgb[0], temp_lum, temp_lum_s);
    rgb->g = calculateEachColoralue(temp_rgb[1], temp_lum, temp_lum_s);
    rgb->b = calculateEachColoralue(temp_rgb[2], temp_lum, temp_lum_s);
    
    free(hsl);
    
    return rgb;
}

static struct Rgb *getShadeOfGray(struct Hsl *hsl) {
    uint8_t v = hsl->l / 100 * 255;
    
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = v;
    rgb->g = v;
    rgb->b = v;
    
    free(hsl);
    
    return rgb;
}

static float *getTempRgbValue(float hue) {
    float * _rgb = malloc(sizeof(uint8_t) * 3);
    float _hue  = hue / 360;
    
    // red
    _rgb[0] = _hue + 0.333f;
    // green
    _rgb[1] = _hue;
    // blue
    _rgb[2] = _hue - 0.333f;

    return updateConstraintValue(_rgb, 3);
}

static uint8_t calculateEachColoralue(float c, float temp_m, float temp_l) {
    float fv = 0.0f;
    
    if (6.0f * c < 1.0f) {
        fv = temp_l + (temp_m - temp_l) * 6.0f * c;
    } else if (2.0f * c < 1.0f) {
        fv = temp_m;
    } else if (3.0f * c < 2.0f) {
        fv = temp_l + (temp_m - temp_l) * (0.666f - c) * 6.0f;
    } else {
        fv = temp_l;
    }
    
    return floatToUint(roundf(fv * 255));
}
