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
        lch->error = NULL_INPUT_PARAM;
        return lch;
    }
    
    Luv *luv = getLuvFromXyz(xyz);
    if (luv == NULL) {
        lch->error = MALLOC_ERROR;
        return lch;
    }
    
    double H = getDegFromRad(atan2(luv->v, luv->u));
    lch->l = luv->l;
    lch->c = sqrt(pow(luv->u, 2.0) + pow(luv->v, 2.0));
    lch->h = H > 0.0 ? H : H + 360.0;
    lch->error = NULL;
    
    free(luv);
    
    return lch;
}

Xyz *getXyzFromLch(Lch *lch) {
    Xyz *errXyz = malloc(sizeof(Xyz));
    if (errXyz == NULL) {
        return NULL;
    }
    
    if (lch == NULL) {
        errXyz->error = NULL_INPUT_PARAM;
        return errXyz;
    }
    
    Luv *luv = malloc(sizeof(Luv));
    if (luv == NULL) {
        errXyz->error = MALLOC_ERROR;
        return errXyz;
    }
    
    double H = getRadFromDeg(lch->h);
    luv->l = lch->l;
    luv->u = lch->c * cos(H);
    luv->v = lch->c * sin(H);
    
    Xyz *xyz = getXyzFromLuv(luv);
    if (xyz == NULL) {
        errXyz->error = MALLOC_ERROR;
        return errXyz;
    }
    
    xyz->error = NULL;
    free(lch);
    free(errXyz);
    
    return xyz;
}
