//
//  lch.c
//  lymui
//
//  Created by Marc on 10/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "helper.h"
#include "lch.h"
#include "luv.h"

Lch * getLchFromXyz(Xyz *xyz) {
    if (xyz == NULL)
        return NULL;
    
     Luv *luv = getLuvFromXyz(xyz);
    
    if (luv == NULL) {
        printf("Unable to convert a Xyz to an Luv");
        return NULL;
    }
    
    Lch *lch = malloc(sizeof( Lch));
    float H = getDegFromRad(atan2f(luv->v, luv->u));
    lch->l = luv->l;
    lch->c = sqrtf(powf(luv->u, 2.0f) + powf(luv->v, 2.0f));
    lch->h = H >= 0.0f ? H : H + 360.0f;
    
    free(luv);
    
    return lch;
}

Xyz * getXyzFromLch(Lch *lch) {
    if (lch == NULL)
        return NULL;
    
    Luv *luv = malloc(sizeof( Luv));
    float H = getRadFromDeg(lch->h);
    luv->l = lch->l;
    luv->u = lch->c * cosf(H);
    luv->v = lch->c * sinf(H);
    
    Xyz *xyz = getXyzFromLuv(luv);
    
    if (xyz == NULL) {
        printf("Unable to convert a Luv to an Xyz");
        return NULL;
    }
    
    free(lch);
    
    return xyz;
}
