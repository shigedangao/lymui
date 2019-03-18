//
//  darken.c
//  lymui
//
//  Created by Marc Intha on 17/03/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include "darken.h"
#include <stdlib.h>

Hsl **getDarkerShade(Rgb *rgb) {
    int idx = 0;
    if (rgb == NULL) {
        return NULL;
    }
    
    Hsl **array = malloc(it * sizeof(Hsl*));
    Hsl *baseHsl = getHslFromRgb(rgb);
    if (baseHsl == NULL) {
        free(array);
        return NULL;
    }
    
    if (baseHsl->error != NULL) {
        free(array);
        free(baseHsl);
        return NULL;
    }
    
    double lum = baseHsl->l;
    while (idx < it) {
        array[idx] = malloc(sizeof(Hsl));
        if (array[idx] == NULL) {
            idx = it + 1;
            free(array);
            return NULL;
        }
        
        array[idx]->h = baseHsl->h;
        array[idx]->s = baseHsl->s;
        
        lum = lum - (baseHsl->l / (double) it);
        if (!lum || lum < 0.0) {
            array[idx]->l = 0.0;
        } else {
            array[idx]->l = lum;
        }
        
        idx++;
    }
    
    free(baseHsl);
    
    return array;
}
