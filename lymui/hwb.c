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
    
    double s = hsv->s / 100.0;
    double v = hsv->v / 100.0;
    
    hwb->h = hsv->h;
    hwb->w = ((1.0 - s) * v) * 100.0;
    hwb->b = (1.0 - v) * 100.0;
    
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
    
    double w = hwb->w / 100.0;
    double b = hwb->b / 100.0;
    
    hsv->h = hwb->h;
    hsv->s = (1.0 - (w / (1 - b))) * 100.0;
    hsv->v = (1.0 - b) * 100.0;
    
    rgb = getRgbFromHsv(hsv);
    
    free(hwb);
    return rgb;
}
