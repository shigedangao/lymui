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
    
    double _r = rgb->r / 255;
    double _g = rgb->g / 255;
    double _b = rgb->b / 255;
    double _y = 0.299 * _r + 0.587 * _g + 0.114 * _b;
    
    yuv->y = _y;
    yuv->u = 0.492 * (_b - _y);
    yuv->v = 0.877 * (_r - _y);
    
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
    rgb->r = floatToUintRound(_r);
    rgb->g = floatToUintRound(_g);
    rgb->b = floatToUintRound(_b);
    
    free(yuv);
    
    return rgb;
}
