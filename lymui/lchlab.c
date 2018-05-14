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

struct Lchlab * getLchFromLab(struct Xyz *xyz) {
    if (xyz == NULL)
        return NULL;
    
    struct Lab *lab = getLabFromXyz(xyz);
    
    if (lab == NULL) {
        printf("Can not get Lch as Lab struct is empty");
        return NULL;
    }
    
    struct Lchlab *lch = malloc(sizeof(struct Lchlab));
    lch->l = lab->l;
    lch->c = sqrtf(powf(lab->a, 2.0f) + powf(lab->b, 2.0f));
    lch->h = getDegFromRad(atanf(lab->b / lab->a));
    
    free(lab);
    
    return lch;
}

struct Xyz * getXyzFromLch(struct Lchlab *lch) {
    if (lch == NULL)
        return NULL;
    
    // Get the lab first
    struct Lab *lab = malloc(sizeof(struct Lab));
    float H = getRadFromDeg(lch->h);
    
    lab->l = lch->l;
    lab->a = lch->c * cosf(H);
    lab->b = lch->c * sinf(H);
    
    // get the xyz struct
    struct Xyz *xyz = getXyzFromLab(lab);
    
    return xyz;
}
