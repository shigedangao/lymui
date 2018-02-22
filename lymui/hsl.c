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
    
    struct Hsl *hsl = malloc(sizeof(hsl));
    hsl->h = hue;
    hsl->l = (min + max) / 2;
    hsl->s = getSaturation(min, max, hsl->l);
    
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
        return getShadeOfGray(hsl);
    }
    
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    
    // choose the luminace formula
    float temp_lum = 0.0f;
    if (round(hsl->l)) {
        temp_lum = (hsl->l + hsl->s) - (hsl->l * hsl->s);
    } else {
        temp_lum = hsl->l * (1.0f + hsl->s);
    }
    
    // get other temp value
    float temp_lum_s = 2 * hsl->l - temp_lum;
    float *temp_rgb  = getTempRgbValue(hsl->h);
    
    rgb->r = calculateEachColoralue(temp_rgb[0], temp_lum, temp_lum_s);
    rgb->g = calculateEachColoralue(temp_rgb[1], temp_lum, temp_lum_s);
    rgb->b = calculateEachColoralue(temp_rgb[2], temp_lum, temp_lum_s);
    
    return rgb;
}

static struct Rgb *getShadeOfGray(struct Hsl *hsl) {
    uint8_t v = hsl->l * 255;
    
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = v;
    rgb->g = v;
    rgb->b = v;
    
    free(hsl);
    
    return rgb;
}

static float *getTempRgbValue(float hue) {
    float *_rgb = malloc(sizeof(uint8_t) * 3);
    float _hue = hue / 360;
    
    // red
    _rgb[0] = _hue + 0.333f;
    // green
    _rgb[1] = _hue;
    // blue
    _rgb[2] = _hue - 0.333f;
    
    return updateConstraintValue(_rgb, sizeof(_rgb) - sizeof(_rgb[0]));
}

static uint8_t calculateEachColoralue(float c, float temp_m, float temp_l) {
    float fv = 0.0f;
    
    if (6.0f * c < 1.0f) {
        fv = temp_l + (temp_m - temp_l) * 6 * c;
    } else if (2.0f * c < 1.0f) {
        fv = temp_m;
    } else if (3.0f * c < 2.0f) {
        fv = temp_l + (temp_m - temp_l) * (0.666f - c) * 6;
    } else {
        fv = temp_l;
    }
    
    return fv * 255;
}
