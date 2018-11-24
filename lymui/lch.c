//
//  lch.c
//  lymui
//
//  Created by Marc on 10/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "errors.h"
#include "helper.h"
#include "lch.h"
#include "luv.h"

Lch *getLchFromXyz(Xyz *xyz) {
    Lch *lch = malloc(sizeof( Lch));
    if (lch == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        lch->error = NULL_INPUT_STRUCT;
        return lch;
    }
    
    Luv *luv = getLuvFromXyz(xyz);
    if (luv == NULL) {
        return NULL;
    }
    
    double H = getDegFromRad(atan2(luv->v, luv->u));
    lch->l = luv->l;
    lch->c = sqrt(pow(luv->u, 2.0f) + pow(luv->v, 2.0f));
    lch->h = H >= 0.0 ? H : H + 360.0;
    
    free(luv);
    
    return lch;
}

Xyz *getXyzFromLch(Lch *lch) {
    Xyz *errXyz = malloc(sizeof(Xyz));
    if (errXyz == NULL) {
        return NULL;
    }
    
    if (lch == NULL) {
        errXyz->error = NULL_INPUT_STRUCT;
        return errXyz;
    }
    
    Luv *luv = malloc(sizeof(Luv));
    if (luv == NULL) {
        errXyz->error = MALLOC_ERROR;
        return errXyz;
    }
    
    double H = getRadFromDeg(lch->h);
    luv->l = lch->l;
    luv->u = lch->c * cosf(H);
    luv->v = lch->c * sinf(H);
    
    Xyz *xyz = getXyzFromLuv(luv);
    if (xyz == NULL) {
        errXyz->error = MALLOC_ERROR;
        return errXyz;
    }
    
    free(lch);
    free(errXyz);
    
    return xyz;
}
