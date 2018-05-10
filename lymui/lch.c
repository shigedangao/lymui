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

struct Lch * getLchFromXyz(struct Xyz *xyz) {
    if (xyz == NULL)
        return NULL;
    
    struct Luv *luv = getLuvFromXyz(xyz);
    
    if (luv == NULL) {
        printf("Unable to convert a Xyz to an Luv");
        return NULL;
    }
    
    struct Lch *lch = malloc(sizeof(struct Lch));
    lch->l = luv->l;
    lch->c = sqrtf(powf(luv->u, 2.0f) + powf(luv->v, 2.0f));
    lch->h = atan2f(luv->v, luv->u) >= 0.0f ?
             atan2f(luv->v, luv->u) : atan2f(luv->v, luv->u) + 360.0f;
    
    free(luv);
    free(xyz);
    
    return lch;
}

struct Xyz * getXyzFromLch(struct Lch *lch) {
    if (lch == NULL)
        return NULL;
    
    struct Luv *luv = malloc(sizeof(struct Luv));
    luv->l = lch->l;
    luv->u = lch->c * getDegFromRad(cosf(lch->h));
    luv->v = lch->c * getDegFromRad(sinf(lch->h));
    
    struct Xyz *xyz = getXyzFromLuv(luv);
    
    if (xyz == NULL) {
        printf("Unable to convert a Luv to an Xyz");
        return NULL;
    }
    
    free(luv);
    free(lch);
    
    return xyz;
}
