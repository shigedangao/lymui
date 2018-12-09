//
//  yuv.c
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include "errors.h"
#include "helper.h"
#include "yuv.h"

Yuv *getYuvFromRgb(Rgb *rgb) {
    Yuv *yuv = malloc(sizeof(Yuv));
    if (yuv == NULL) {
        return NULL;
    }
    
    if (rgb == NULL) {
        yuv->error = NULL_INPUT_PARAM;
        return yuv;
    }
    
    double _r = (double) rgb->r / 255.0;
    double _g = (double) rgb->g / 255.0;
    double _b = (double) rgb->b / 255.0;
    double _y = 0.299 * _r + 0.587 * _g + 0.114 * _b;
        
    yuv->y = _y;
    yuv->u = 0.492 * (_b - _y);
    yuv->v = 0.877 * (_r - _y);
    yuv->error = NULL;
    
    free(rgb);
    
    return yuv;
}

Rgb *getRgbFromYuv(Yuv *yuv) {
    Rgb *rgb = initRgb();
    if (rgb == NULL) {
        return NULL;
    }
    
    if (yuv == NULL) {
        rgb->error = NULL_INPUT_PARAM;
        return rgb;
    }

    double _r = yuv->y + 1.13983 * yuv->v;
    double _g = yuv->y - 0.39465 * yuv->u - 0.58060 * yuv->v;
    double _b = yuv->y + 2.03211 * yuv->u;
    
    rgb->r = doubleToUint(_r * 255);
    rgb->g = doubleToUint(_g * 255);
    rgb->b = doubleToUint(_b * 255);
    rgb->error = NULL;
    
    free(yuv);
    
    return rgb;
}
