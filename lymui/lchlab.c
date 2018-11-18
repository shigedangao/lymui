//
//  lchlab.c
//  lymui
//
//  Created by Marc on 14/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "helper.h"
#include "lab.h"
#include "lchlab.h"

LchLab * getLchFromLab(Xyz *xyz) {
    if (xyz == NULL)
        return NULL;
    
    Lab *lab = getLabFromXyz(xyz);
    if (lab == NULL) {
        return NULL;
    }
    
    LchLab *lch = malloc(sizeof(LchLab));
    lch->l = lab->l;
    lch->c = sqrtf(powf(lab->a, 2.0f) + powf(lab->b, 2.0f));
    
    float h = getRadFromDeg(atan2f(lab->b, lab->a));
    if (h >= 0.0f) {
        lch->h = h;
    } else {
        lch->h = h + 360.0f;
    }
    
    free(lab);
    
    return lch;
}

Xyz * getXyzFromLchlab(LchLab *lch) {
    if (lch == NULL)
        return NULL;
    
    // Get the lab first
    Lab *lab = malloc(sizeof(Lab));
    
    if (lab == NULL) {
        return NULL;
    }
    
    float H = getRadFromDeg(lch->h);
    lab->l = lch->l;
    lab->a = lch->c * cosf(H);
    lab->b = lch->c * sinf(H);
    
    // get the xyz
    Xyz *xyz = getXyzFromLab(lab);
    
    return xyz;
}
