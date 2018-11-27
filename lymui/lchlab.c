//
//  lchlab.c
//  lymui
//
//  Created by Marc on 14/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "errors.h"
#include "helper.h"
#include "lab.h"
#include "lchlab.h"

LchLab *getLchFromLab(Xyz *xyz) {
    LchLab *lch = malloc(sizeof(LchLab));
    if (lch == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        lch->error = NULL_INPUT_STRUCT;
        return lch;
    }
    
    Lab *lab = getLabFromXyz(xyz);
    if (lab == NULL) {
        lch->error = MALLOC_ERROR;
        return lch;
    }
    
    lch->l = lab->l;
    lch->c = sqrt(pow(lab->a, 2.0) + pow(lab->b, 2.0));
    lch->error = NULL;
    double h = getDegFromRad(atan2(lab->b, lab->a));
    if (h >= 0.0) {
        lch->h = h;
    } else {
        lch->h = h + 360.0;
    }
    
    free(lab);
    
    return lch;
}

Xyz *getXyzFromLchlab(LchLab *lch) {
    Xyz *errXyz = malloc(sizeof(Xyz));
    if (errXyz == NULL) {
        return NULL;
    }
    
    if (lch == NULL) {
        errXyz->error = NULL_INPUT_STRUCT;
        return errXyz;
    }
    // Get the lab first
    Lab *lab = malloc(sizeof(Lab));
    if (lab == NULL) {
        errXyz->error = MALLOC_ERROR;
        return errXyz;
    }
    
    double H = getRadFromDeg(lch->h);
    lab->l = lch->l;
    lab->a = lch->c * cos(H);
    lab->b = lch->c * sin(H);
    
    // get the xyz
    Xyz *xyz = getXyzFromLab(lab);
    if (xyz == NULL) {
        errXyz->error = MALLOC_ERROR;
        return errXyz;
    }
    
    xyz->error = NULL;
    free(errXyz);
    
    return xyz;
}
