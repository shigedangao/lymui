//
//  tint.c
//  lymui
//
//  Created by Marc Intha on 22/03/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include "tint.h"
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

Tint *getTint(Rgb *rgb) {
    Tint *tint = malloc(sizeof(Tint));
    if (tint == NULL) {
        return NULL;
    }
    
    if (rgb == NULL) {
        tint->error = NULL_INPUT_PARAM;
        return tint;
    }
    
    uint8_t idx = 0;
    Hsl **array = malloc(it * sizeof(Hsl));
    if (array == NULL) {
        tint->error = MALLOC_ERROR;
        return tint;
    }
    
    Hsl *hsl = getHslFromRgb(rgb);
    if (hsl == NULL) {
        tint->error = MALLOC_ERROR;
        free(array);
        return tint;
    }
    
    if (hsl->error != NULL) {
        tint->error = hsl->error;
        free(hsl);
        free(array);
        return tint;
    }
    
    double baseLum = hsl->l;
    double steps = hsl->l / (double) it;
    
    if (!steps) {
        steps = 10.0;
    }
    
    while(idx < it) {
        array[idx] = malloc(sizeof(Hsl));
        if (array[idx] == NULL) {
            idx = it + 1;
            free(array);
            tint->error = MALLOC_ERROR;
            return tint;
        }
        
        array[idx]->h = hsl->h;
        array[idx]->s = hsl->s;
        
        if (idx) {
            baseLum = baseLum + steps;
        }
        
        if (baseLum >= 100.0) {
            array[idx]->l = 100.0;
        } else {
            array[idx]->l = baseLum;
        }
        
        idx++;
    }
    
    free(hsl);

    // assign the tint array to the tint
    tint->tint = array;

    return tint;
}
