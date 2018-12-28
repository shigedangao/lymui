//
//  hwb.c
//  lymui
//
//  Created by Marc Intha on 26/12/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include "hwb.h"
#include "errors.h"
#include "hsv.h"

Hwb *getHwbFromRgb(Rgb *rgb) {
    Hwb *hwb = malloc(sizeof(Hwb));
    if (hwb == NULL) {
        return NULL;
    }
    
    if (rgb == NULL) {
        hwb->error = NULL_INPUT_PARAM;
        return hwb;
    }
    
    Hsv *hsv = getHsvFromRgb(rgb);
    if (hsv == NULL) {
        hwb->error = MALLOC_ERROR;
        return hwb;
    }
    
    if (hsv->error) {
        hwb->error = hsv->error;
        free(hsv);
        return hwb;
    }
    
    double s = hsv->s / 100.0f;
    double v = hsv->v / 100.0f;
    
    hwb->h = hsv->h;
    hwb->w = ((1 - s) * v) * 100.0f;
    hwb->b = (1 - v) * 100.0f;
    
    free(hsv);
    return hwb;
}

Rgb *getRgbFromHwb(Hwb *hwb) {
    Rgb *rgb = initRgb();
    if (rgb == NULL) {
        return NULL;
    }
    
    if (hwb == NULL) {
        rgb->error = NULL_INPUT_PARAM;
        return rgb;
    }
    
    Hsv *hsv = malloc(sizeof(Hsv));
    if (hsv == NULL) {
        rgb->error = MALLOC_ERROR;
        return rgb;
    }
    
    double w = hwb->w / 100.0f;
    double b = hwb->b / 100.0f;
    
    hsv->h = hwb->h;
    hsv->s = (1 - (w / (1 - b))) * 100.0f;
    hsv->v = (1 - b) * 100.0f;
    
    rgb = getRgbFromHsv(hsv);
    
    free(hwb);
    return rgb;
}
