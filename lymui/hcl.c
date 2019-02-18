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
#include "xyz.h"
#include "luv.h"
#include "hue.h"
#include "helper.h"
#include "errors.h"

Hcl *getHclFromRgb(Rgb *rgb) {
    Hcl *hcl = malloc(sizeof(Hcl));
    if (hcl == NULL) {
        return NULL;
    }
    
    if (rgb == NULL) {
        hcl->error = NULL_INPUT_PARAM;
        return hcl;
    }
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    if (xyz == NULL) {
        hcl->error = XYZ_ERR;
        free(rgb);
        
        return hcl;
    }
    
    Luv *luv = getLuvFromXyz(xyz);
    if (luv == NULL) {
        hcl->error = LUV_ERR;
        free(rgb);
        free(xyz);
        
        return hcl;
    }
    
    hcl->h = getHueFromRgb(rgb);
    hcl->c = sqrt(luv->u * luv->u + luv->v * luv->v);
    hcl->l = luv->l;
    hcl->error = NULL;
    
    free(rgb);
    free(xyz);
    free(luv);
    
    return hcl;
}

Rgb *getRgbFromHcl(Hcl *hcl) {
    Rgb *errRgb = malloc(sizeof(Rgb));
    if (errRgb == NULL) {
        return NULL;
    }
    
    if (hcl == NULL) {
        errRgb->error = NULL_INPUT_PARAM;
        return errRgb;
    }
    
    Luv *luv = malloc(sizeof(Luv));
    if (luv == NULL) {
        errRgb->error = LUV_ERR;
        free(hcl);
        
        return errRgb;
    }
    
    double h = getRadFromDeg(hcl->h);
    luv->l = hcl->l;
    luv->u = hcl->c * cos(h);
    luv->v = hcl->c * sin(h);
    
    Xyz *xyz = getXyzFromLuv(luv);
    if (xyz == NULL) {
        errRgb->error = XYZ_ERR;
        free(hcl);
        free(luv);
        
        return errRgb;
    }
    
    Rgb *color = getRgbFromXyz(xyz, srgb);
    
    free(hcl);
    free(errRgb);
    free(luv);
    free(xyz);
    
    return color;
}
