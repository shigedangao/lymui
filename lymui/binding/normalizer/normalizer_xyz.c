//
//  normalizer_xyz.c
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "normalizer_xyz.h"
#include <node_api.h>
#include "bridge.h"
#include "factory.h"
#include "lab.h"
#include "lch.h"
#include "luv.h"
#include "argb.h"
#include "srgb.h"

napi_value normalizeLab(napi_env env, napi_value obj, double clamp) {
    Lab *lab = getLabFromJSObj(env, obj);
    if (lab == NULL) {
        return NULL;
    }
    
    Xyz *xyz = getXyzFromLab(lab);
    napi_value object = XyzJSObjFactoryNoInst(env, xyz, clamp);
    
    return object;
}

napi_value normalizeLch(napi_env env, napi_value obj, double clamp) {
    Lch *lch = getLchFromJSObj(env, obj);
    if (lch == NULL) {
        return NULL;
    }
    
    Xyz *xyz = getXyzFromLch(lch);
    napi_value object = XyzJSObjFactoryNoInst(env, xyz, clamp);
    
    return object;
}

napi_value normalizeLchLab(napi_env env, napi_value obj, double clamp) {
    LchLab *lch = getLchlabFromJSObj(env, obj);
    if (lch == NULL) {
        return NULL;
    }
    
    Xyz *xyz = getXyzFromLchlab(lch);
    napi_value object = XyzJSObjFactoryNoInst(env, xyz, clamp);
    
    return object;
}

napi_value normalizeLuv(napi_env env, napi_value obj, double clamp) {
    Luv *luv = getLuvFromJSObj(env, obj);
    if (luv == NULL) {
        return NULL;
    }
    
    Xyz *xyz = getXyzFromLuv(luv);
    napi_value object = XyzJSObjFactoryNoInst(env, xyz, clamp);
    
    return object;
}

napi_value normalizeXyy(napi_env env, napi_value obj, double clamp) {
    Xyy *xyy = getXyyFromJSObj(env, obj);
    if (xyy == NULL) {
        return NULL;
    }
        
    Xyz *xyz = getXyzFromXyy(xyy);
    napi_value object = XyzJSObjFactoryNoInst(env, xyz, clamp);
    
    return object;
}

napi_value normalizeSRgb(napi_env env, napi_value obj, double clamp) {
    SRgb *srgb = getSrgbFromJSObj(env, obj);
    if (srgb == NULL) {
        return NULL;
    }
    
    Xyz *xyz = getXyzFromSrgb(srgb);
    napi_value object = XyzJSObjFactoryNoInst(env, xyz, clamp);
    
    return object;
}
