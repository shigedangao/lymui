//
//  shade.c
//  lymui
//
//  Created by Marc Intha on 17/03/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include "shade.h"
#include <stdlib.h>
#include "errors.h"

Shade *getShade(Rgb *rgb) {
    Shade *shade = malloc(sizeof(Shade));
    if (shade == NULL) {
        return NULL;
    }
    
    int idx = 0;
    if (rgb == NULL) {
        shade->error = NULL_INPUT_PARAM;
        return shade;
    }
    
    Hsl **array = malloc(it * sizeof(Hsl));
    if (array == NULL) {
        shade->error = MALLOC_ERROR;
        return shade;
    }
    
    Hsl *hsl = getHslFromRgb(rgb);
    if (hsl == NULL) {
        shade->error = MALLOC_ERROR;
        free(array);
        return shade;
    }
    
    if (hsl->error != NULL) {
        shade->error = hsl->error;
        free(array);
        free(hsl);
        return shade;
    }
    
    double lum = hsl->l;
    while (idx < it) {
        array[idx] = malloc(sizeof(Hsl));
        if (array[idx] == NULL) {
            free(hsl);
            free(array);
            shade->error = MALLOC_ERROR;
            return shade;
        }
        
        array[idx]->h = hsl->h;
        array[idx]->s = hsl->s;
        
        if (idx) {
            lum = lum - (hsl->l / (double) it);
        }
        
        if (!lum || lum < 0.0) {
            array[idx]->l = 0.0;
        } else {
            array[idx]->l = lum;
        }
        
        idx++;
    }
    
    free(hsl);
    
    shade->shade = array;
    shade->error = NULL;
    
    return shade;
}
