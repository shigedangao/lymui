//
//  yuv.c
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include "helper.h"
#include "yuv.h"

struct Yuv *getYuvFromRgb(struct Rgb *rgb) {
    if (rgb == NULL)
        return NULL;
    
    struct Yuv *yuv = malloc(sizeof(struct Yuv));
    
    float _r = (float) rgb->r / 255;
    float _g = (float) rgb->g / 255;
    float _b = (float) rgb->b / 255;
    float _y = 0.299f * _r + 0.587f * _g + 0.114f * _b;
        
    yuv->y = roundDigit(_y, 1000);
    yuv->u = roundDigit(0.492f * (_b - _y), 1000);
    yuv->v = roundDigit(0.877f * (_r - _y), 1000);
    
    free(rgb);
    
    return yuv;
}

struct Rgb *getRgbFromYuv(struct Yuv *yuv) {
    if (yuv == NULL)
        return NULL;
    
    float _r = yuv->y + 1.13983f * yuv->v;
    float _g = yuv->y - 0.39465f * yuv->u - 0.58060f * yuv->v;
    float _b = yuv->y + 2.03211f * yuv->u;
    
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = floatToUintRound(_r * 255);
    rgb->g = floatToUintRound(_g * 255);
    rgb->b = floatToUintRound(_b * 255);
    
    free(yuv);
    
    return rgb;
}
