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

napi_value RgbJSObjFactory(napi_env env, Rgb * rgb) {
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

napi_value CymkJSObjFactory(napi_env env, Cymk * cymk, int clamp) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    
    double c = floatToDouble(cymk->c, clamp);
    double y = floatToDouble(cymk->y, clamp);
    double m = floatToDouble(cymk->m, clamp);
    double k = floatToDouble(cymk->k, clamp);
    // assign the cymk object
    assignPropToJSObj(&object, env, numberFloat, "c", &c);
    assignPropToJSObj(&object, env, numberFloat, "y", &y);
    assignPropToJSObj(&object, env, numberFloat, "m", &m);
    assignPropToJSObj(&object, env, numberFloat, "k", &k);
    
    return object;
}

napi_value YcbcrJSObjFactory(napi_env env, Ycbcr * ycb) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    
    assignPropToJSObj(&object, env, numberInt, "y", &ycb->y);
    assignPropToJSObj(&object, env, numberInt, "cb", &ycb->cb);
    assignPropToJSObj(&object, env, numberInt, "cr", &ycb->cr);
    
    return object;
}

napi_value HslJSObjFactory(napi_env env, Hsl * hsl, int clamp) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    
    double h = floatToDouble(hsl->h, clamp);
    double s = floatToDouble(hsl->s, clamp);
    double l = floatToDouble(hsl->l, clamp);
    
    assignPropToJSObj(&object, env, numberFloat, "h", &h);
    assignPropToJSObj(&object, env, numberFloat, "s", &s);
    assignPropToJSObj(&object, env, numberFloat, "l", &l);
    
    return object;
}

napi_value HsvJSObjFactory(napi_env env, Hsv * hsv, int clamp) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    
    double h = floatToDouble(hsv->h, clamp);
    double s = floatToDouble(hsv->s, clamp);
    double v = floatToDouble(hsv->v, clamp);
    
    assignPropToJSObj(&object, env, numberFloat, "h", &h);
    assignPropToJSObj(&object, env, numberFloat, "s", &s);
    assignPropToJSObj(&object, env, numberFloat, "v", &v);
    
    return object;
}

napi_value YuvJSObjFactory(napi_env env, Yuv * yuv, int clamp) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    
    double y = floatToDouble(yuv->y, clamp);
    double u = floatToDouble(yuv->u, clamp);
    double v = floatToDouble(yuv->v, clamp);
    
    assignPropToJSObj(&object, env, numberFloat, "y", &y);
    assignPropToJSObj(&object, env, numberFloat, "u", &u);
    assignPropToJSObj(&object, env, numberFloat, "v", &v);
    
    return object;
}

napi_value XyzJSObjFactory(napi_env env, Xyz * xyz, int clamp) {
    napi_status status;
    napi_value object;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    
    double x = floatToDouble(xyz->x, clamp);
    double y = floatToDouble(xyz->y, clamp);
    double z = floatToDouble(xyz->z, clamp);
    
    assignPropToJSObj(&object, env, numberFloat, "x", &x);
    assignPropToJSObj(&object, env, numberFloat, "y", &y);
    assignPropToJSObj(&object, env, numberFloat, "z", &z);
    
    return object;
}

napi_value LabJSObjFactory(napi_env env, Xyz * xyz) {
    napi_status status;
    napi_value object;
    Lab * lab = getLabFromXyz(xyz);
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
        return NULL;
    }
    
    double l = floatToDouble(lab->l, COLOR_SPACE_CLAMP);
    double a = floatToDouble(lab->a, COLOR_SPACE_CLAMP);
    double b = floatToDouble(lab->b, COLOR_SPACE_CLAMP);
    
    assignPropToJSObj(&object, env, numberFloat, "l", &l);
    assignPropToJSObj(&object, env, numberFloat, "a", &a);
    assignPropToJSObj(&object, env, numberFloat, "b", &b);
    free(lab);
    
    return object;
}

napi_value LchJSObjFactory(napi_env env, Xyz * xyz) {
    napi_status status;
    napi_value object;
    Lch * lch = getLchFromXyz(xyz);
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
        return NULL;
    }
    
    double l = floatToDouble(lch->l, COLOR_SPACE_CLAMP);
    double c = floatToDouble(lch->c, COLOR_SPACE_CLAMP);
    double h = floatToDouble(lch->h, COLOR_SPACE_CLAMP);
    
    assignPropToJSObj(&object, env, numberFloat, "l", &l);
    assignPropToJSObj(&object, env, numberFloat, "c", &c);
    assignPropToJSObj(&object, env, numberFloat, "h", &h);
    free(lch);
    
    return object;
}

napi_value LuvJSObjFactory(napi_env env, Xyz * xyz) {
    napi_status status;
    napi_value object;
    Luv * luv = getLuvFromXyz(xyz);
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
        return NULL;
    }
    
    double l = floatToDouble(luv->l, COLOR_SPACE_CLAMP);
    double u = floatToDouble(luv->u, COLOR_SPACE_CLAMP);
    double v = floatToDouble(luv->v, COLOR_SPACE_CLAMP);
    
    assignPropToJSObj(&object, env, numberFloat, "l", &l);
    assignPropToJSObj(&object, env, numberFloat, "u", &u);
    assignPropToJSObj(&object, env, numberFloat, "v", &v);
    free(luv);
    
    return object;
}

napi_value ArgbJSObjFactory(napi_env env, Xyz * xyz) {
    napi_status status;
    napi_value object;
    ARgb * argb = getARgbFromXyz(xyz);
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
        return NULL;
    }
    
    double r = floatToDouble(argb->r, COLOR_SPACE_CLAMP);
    double g = floatToDouble(argb->g, COLOR_SPACE_CLAMP);
    double b = floatToDouble(argb->b, COLOR_SPACE_CLAMP);
    
    assignPropToJSObj(&object, env, numberFloat, "r", &r);
    assignPropToJSObj(&object, env, numberFloat, "g", &g);
    assignPropToJSObj(&object, env, numberFloat, "b", &b);
    free(argb);
    
    return object;
}

napi_value SrgbJSObjFactory(napi_env env, Xyz * xyz) {
    napi_status status;
    napi_value object;
    SRgb * srgb = getSRgbFromXyz(xyz);
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
        return NULL;
    }
    
    double r = floatToDouble(srgb->r, COLOR_SPACE_CLAMP);
    double g = floatToDouble(srgb->g, COLOR_SPACE_CLAMP);
    double b = floatToDouble(srgb->b, COLOR_SPACE_CLAMP);
    
    assignPropToJSObj(&object, env, numberFloat, "r", &r);
    assignPropToJSObj(&object, env, numberFloat, "g", &g);
    assignPropToJSObj(&object, env, numberFloat, "b", &b);
    free(srgb);
    
    return object;
}

napi_value BuildPromiseError(napi_env env, char * error) {
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
