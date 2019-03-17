//
//  darken.c
//  lymui
//
//  Created by Marc Intha on 17/03/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include "darken.h"
#include <stdlib.h>

Hsl **getDarkerShade(Rgb *rgb, int it) {
    int idx = 0;
    if (rgb == NULL) {
        return NULL;
    }
    
    Hsl **ptrList = malloc(it * sizeof(Hsl));
    if (ptrList == NULL) {
        return NULL;
    }
    
    Hsl *baseHsl = getHslFromRgb(rgb);
    if (baseHsl == NULL) {
        return NULL;
    }
    
    // @TODO maybe print to a log ?
    if (baseHsl->error != NULL) {
        free(ptrList);
        free(baseHsl);
        return NULL;
    }
    
    while (idx < it) {
        ptrList[idx] = malloc(sizeof(Hsl));
        if (ptrList[idx] == NULL) {
            idx = it + 1;
            return NULL;
        }
        
        // @TODO need to define if it's possible to use user's step value of need to have define somewhere
        ptrList[idx]->h = baseHsl->h;
        ptrList[idx]->s = baseHsl->s;
        ptrList[idx]->l = baseHsl->l;
        
        idx++;
    }
    
    return ptrList;
}
