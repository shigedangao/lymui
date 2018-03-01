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
    float _l  = (min + max) / 2;
    
    struct Hsv *hsv = malloc(sizeof(struct Hsv));
    hsv->h = hue;
    hsv->s = getSaturation(min, max, _l);
    hsv->v = max;
    
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
    
    // WIP
    return NULL;
}
