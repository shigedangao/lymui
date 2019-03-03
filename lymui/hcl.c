//
//  hcl.c
//  lymui
//
//  Created by Marc Intha on 13/02/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include "hcl.h"
#include <stdlib.h>
#include <math.h>
#include "luv.h"
#include "helper.h"
#include "errors.h"

/**
 * Calculate Hue
 *   Calculate the hue based on the U & V value
 * @param u double
 * @param v double
 * @return double
 */
static double calculateHue(double u, double v) {
    double hue = getDegFromRad(atan2(v, u));
    
    if (hue > 360.0) {
        hue = hue - 360.0;
    } else if (hue < 0.0) {
        hue = hue + 360.0;
    }
    
    return hue;
}

Hcl *getHclFromLuv(Luv *luv) {
    Hcl *hcl = malloc(sizeof(Hcl));
    if (hcl == NULL) {
        return NULL;
    }
    
    if (luv == NULL) {
        hcl->error = NULL_INPUT_PARAM;
        
        return hcl;
    }
    
    hcl->h = calculateHue(luv->v, luv->u);
    hcl->c = sqrt(luv->u * luv->u + luv->v * luv->v);
    hcl->l = luv->l;
    hcl->error = NULL;
    
    free(luv);
    
    return hcl;
}

Luv *getLuvFromHcl(Hcl *hcl) {
    Luv *luv = malloc(sizeof(Luv));
    if (luv == NULL) {
        return NULL;
    }
    
    if (hcl == NULL) {
        luv->error = NULL_INPUT_PARAM;
        return luv;
    }
    
    double h = getRadFromDeg(hcl->h);
    luv->l = hcl->l;
    luv->u = hcl->c * sin(h);
    luv->v = hcl->c * cos(h);
    
    free(hcl);
    
    return luv;
}
