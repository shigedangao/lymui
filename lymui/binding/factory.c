//
//  factory.c
//  lymui
//
//  Created by Marc Intha on 01/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "factory.h"
#include <stdlib.h>
#include <node_api.h>
#include "binding_error.h"
#include "binding_util.h"
#include "rgb.h"
#include "cymk.h"
#include "ycbcr.h"
#include "hsl.h"
#include "hsv.h"
#include "yuv.h"
#include "xyz.h"

napi_value RgbJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    
    // assign the value
    assignPropToJSObj(&object, env, numberInt, "r", &rgb->r);
    assignPropToJSObj(&object, env, numberInt, "g", &rgb->g);
    assignPropToJSObj(&object, env, numberInt, "b", &rgb->b);
    
    return object;
}

napi_value CymkJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    Cymk *cymk = getCymkFromRgb(rgb);
    if (cymk == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (cymk->error) {
        assignPropToJSObj(&object, env, string, "error", cymk->error);
        return object;
    }
    
    // assign the cymk object
    assignPropToJSObj(&object, env, numberDouble, "c", &cymk->c);
    assignPropToJSObj(&object, env, numberDouble, "y", &cymk->y);
    assignPropToJSObj(&object, env, numberDouble, "m", &cymk->m);
    assignPropToJSObj(&object, env, numberDouble, "k", &cymk->k);
    
    return object;
}

napi_value YcbcrJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    Ycbcr *ycb = getYcbcrFromRgb(rgb);
    if (ycb == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (ycb->error) {
        assignPropToJSObj(&object, env, string, "error", ycb->error);
        return object;
    }
    
    assignPropToJSObj(&object, env, numberInt, "y", &ycb->y);
    assignPropToJSObj(&object, env, numberInt, "cb", &ycb->cb);
    assignPropToJSObj(&object, env, numberInt, "cr", &ycb->cr);
    
    return object;
}

napi_value HslJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    Hsl *hsl = getHslFromRgb(rgb);
    if (hsl == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (hsl->error) {
        assignPropToJSObj(&object, env, string, "error", hsl->error);
        return object;
    }
    
    assignPropToJSObj(&object, env, numberDouble, "h", &hsl->h);
    assignPropToJSObj(&object, env, numberDouble, "s", &hsl->s);
    assignPropToJSObj(&object, env, numberDouble, "l", &hsl->l);
    
    return object;
}

napi_value HsvJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    Hsv *hsv = getHsvFromRgb(rgb);
    if (hsv == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (hsv->error) {
        assignPropToJSObj(&object, env, string, "error", hsv->error);
        return object;
    }
    
    assignPropToJSObj(&object, env, numberDouble, "h", &hsv->h);
    assignPropToJSObj(&object, env, numberDouble, "s", &hsv->s);
    assignPropToJSObj(&object, env, numberDouble, "v", &hsv->v);
    
    return object;
}

napi_value YuvJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    Yuv *yuv = getYuvFromRgb(rgb);
    if (yuv == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (yuv->error) {
        assignPropToJSObj(&object, env, string, "error", yuv->error);
        return object;
    }
    
    assignPropToJSObj(&object, env, numberDouble, "y", &yuv->y);
    assignPropToJSObj(&object, env, numberDouble, "u", &yuv->u);
    assignPropToJSObj(&object, env, numberDouble, "v", &yuv->v);
    
    return object;
}

napi_value XyzJSObjFactory(napi_env env, Rgb *rgb, char *matrix) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    
    Matrix m = getEnumFromStr(matrix);
    Xyz *xyz = generateXyzFromRgb(rgb, m);
    
    if (xyz == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (xyz->error) {
        assignPropToJSObj(&object, env, string, "error", xyz->error);
        return object;
    }
    
    assignPropToJSObj(&object, env, numberDouble, "x", &xyz->x);
    assignPropToJSObj(&object, env, numberDouble, "y", &xyz->y);
    assignPropToJSObj(&object, env, numberDouble, "z", &xyz->z);
    
    return object;
}

napi_value LabJSObjFactory(napi_env env, Xyz *xyz) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
        return NULL;
    }
    
    Lab *lab = getLabFromXyz(xyz);
    if (lab == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (lab->error) {
        assignPropToJSObj(&object, env, string, "error", lab->error);
        return object;
    }
    
    assignPropToJSObj(&object, env, numberDouble, "l", &lab->l);
    assignPropToJSObj(&object, env, numberDouble, "a", &lab->a);
    assignPropToJSObj(&object, env, numberDouble, "b", &lab->b);
    free(lab);
    
    return object;
}

napi_value LchJSObjFactory(napi_env env, Xyz *xyz) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    Lch *lch = getLchFromXyz(xyz);
    if (lch == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (lch->error) {
        assignPropToJSObj(&object, env, string, "error", lch->error);
        return object;
    }
    
    
    assignPropToJSObj(&object, env, numberDouble, "l", &lch->l);
    assignPropToJSObj(&object, env, numberDouble, "c", &lch->c);
    assignPropToJSObj(&object, env, numberDouble, "h", &lch->h);
    free(lch);
    
    return object;
}

napi_value LuvJSObjFactory(napi_env env, Xyz *xyz) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    Luv *luv = getLuvFromXyz(xyz);
    if (luv == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (luv->error) {
        assignPropToJSObj(&object, env, string, "error", luv->error);
        return object;
    }
    
    assignPropToJSObj(&object, env, numberDouble, "l", &luv->l);
    assignPropToJSObj(&object, env, numberDouble, "u", &luv->u);
    assignPropToJSObj(&object, env, numberDouble, "v", &luv->v);
    
    free(luv);
    
    return object;
}

napi_value ArgbJSObjFactory(napi_env env, Xyz *xyz) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
        return NULL;
    }
    
    Argb *argb = getARgbFromXyz(xyz);
    if (argb == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (argb->error) {
        assignPropToJSObj(&object, env, string, "error", argb->error);
        return object;
    }
    
    assignPropToJSObj(&object, env, numberDouble, "r", &argb->r);
    assignPropToJSObj(&object, env, numberDouble, "g", &argb->g);
    assignPropToJSObj(&object, env, numberDouble, "b", &argb->b);
    
    free(argb);
    
    return object;
}

napi_value SrgbJSObjFactory(napi_env env, Xyz *xyz) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
        return NULL;
    }
    
    SRgb *srgb = getSRgbFromXyz(xyz);
    if (srgb == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (srgb->error) {
        assignPropToJSObj(&object, env, string, "error", srgb->error);
        return object;
    }
    
    assignPropToJSObj(&object, env, numberDouble, "r", &srgb->r);
    assignPropToJSObj(&object, env, numberDouble, "g", &srgb->g);
    assignPropToJSObj(&object, env, numberDouble, "b", &srgb->b);
    
    free(srgb);
    
    return object;
}

napi_value BuildPromiseError(napi_env env, char *error) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
        return NULL;
    }
    
    assignPropToJSObj(&object, env, string, "err", error);
    
    return object;
}
