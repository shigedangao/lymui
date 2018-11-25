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
#include "hex.h"
#include "cymk.h"
#include "ycbcr.h"
#include "hsl.h"
#include "hsv.h"
#include "yuv.h"
#include "xyz.h"

napi_value RgbJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    if (rgb == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (rgb->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", rgb->error);
        return object;
    }
    
    // assign the value
    assignPropToJSObj(&data, env, numberInt, "r", &rgb->r);
    assignPropToJSObj(&data, env, numberInt, "g", &rgb->g);
    assignPropToJSObj(&data, env, numberInt, "b", &rgb->b);
    
    // assign data to the object
    assignJSObjtoJSObj(env, &object, data, "data");
    
    return object;
}

napi_value HexJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    char *hex = getHexFromRGB(rgb);
    if (hex == NULL) {
        assignPropToJSObj(&object, env, string, "error", BuildPromiseError(env, CONVERT_ERR));
        return object;
    }
    
    assignPropToJSObj(&data, env, string, "hex", hex);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    return object;
}

napi_value CymkJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    Cymk *cymk = getCymkFromRgb(rgb);
    if (cymk == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (cymk->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", cymk->error);
        return object;
    }
    
    // assign the cymk object
    assignPropToJSObj(&data, env, numberDouble, "c", &cymk->c);
    assignPropToJSObj(&data, env, numberDouble, "y", &cymk->y);
    assignPropToJSObj(&data, env, numberDouble, "m", &cymk->m);
    assignPropToJSObj(&data, env, numberDouble, "k", &cymk->k);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    return object;
}

napi_value YcbcrJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    Ycbcr *ycb = getYcbcrFromRgb(rgb);
    if (ycb == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (ycb->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", ycb->error);
        return object;
    }
    
    assignPropToJSObj(&data, env, numberInt, "y", &ycb->y);
    assignPropToJSObj(&data, env, numberInt, "cb", &ycb->cb);
    assignPropToJSObj(&data, env, numberInt, "cr", &ycb->cr);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    return object;
}

napi_value HslJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    Hsl *hsl = getHslFromRgb(rgb);
    if (hsl == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (hsl->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", hsl->error);
        return object;
    }
    
    assignPropToJSObj(&data, env, numberDouble, "h", &hsl->h);
    assignPropToJSObj(&data, env, numberDouble, "s", &hsl->s);
    assignPropToJSObj(&data, env, numberDouble, "l", &hsl->l);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    return object;
}

napi_value HsvJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    Hsv *hsv = getHsvFromRgb(rgb);
    if (hsv == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (hsv->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", hsv->error);
        return object;
    }
    
    assignPropToJSObj(&data, env, numberDouble, "h", &hsv->h);
    assignPropToJSObj(&data, env, numberDouble, "s", &hsv->s);
    assignPropToJSObj(&data, env, numberDouble, "v", &hsv->v);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    return object;
}

napi_value YuvJSObjFactory(napi_env env, Rgb *rgb) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    Yuv *yuv = getYuvFromRgb(rgb);
    if (yuv == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (yuv->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", yuv->error);
        return object;
    }
    
    assignPropToJSObj(&data, env, numberDouble, "y", &yuv->y);
    assignPropToJSObj(&data, env, numberDouble, "u", &yuv->u);
    assignPropToJSObj(&data, env, numberDouble, "v", &yuv->v);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    return object;
}

napi_value XyzJSObjFactory(napi_env env, Rgb *rgb, char *matrix, double clamp) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    Matrix m = getEnumFromStr(matrix);
    Xyz *xyz = generateXyzFromRgb(rgb, m);
    
    if (xyz == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (xyz->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", xyz->error);
        return object;
    }
    
    double x = xyz->x;
    double y = xyz->y;
    double z = xyz->z;
    
    if (clamp) {
        x = clampValue(x, clamp);
        y = clampValue(y, clamp);
        z = clampValue(z, clamp);
    }
    
    assignPropToJSObj(&data, env, numberDouble, "x", &x);
    assignPropToJSObj(&data, env, numberDouble, "y", &y);
    assignPropToJSObj(&data, env, numberDouble, "z", &z);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    return object;
}

napi_value XyzJSObjFactoryNoInst(napi_env env, Xyz *xyz, double clamp) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    if (xyz == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    double x = xyz->x;
    double y = xyz->y;
    double z = xyz->z;
    
    if (clamp) {
        x = clampValue(x, clamp);
        y = clampValue(y, clamp);
        z = clampValue(z, clamp);
    }
    
    assignPropToJSObj(&data, env, numberDouble, "x", &x);
    assignPropToJSObj(&data, env, numberDouble, "y", &y);
    assignPropToJSObj(&data, env, numberDouble, "z", &z);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    return object;
}

napi_value LabJSObjFactory(napi_env env, Xyz *xyz, double clamp) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    Lab *lab = getLabFromXyz(xyz);
    if (lab == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (lab->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", lab->error);
        return object;
    }
    
    double l = lab->l;
    double a = lab->a;
    double b = lab->b;
    
    if (clamp) {
        l = clampValue(l, clamp);
        a = clampValue(a, clamp);
        b = clampValue(b, clamp);
    }
    
    assignPropToJSObj(&data, env, numberDouble, "l", &l);
    assignPropToJSObj(&data, env, numberDouble, "a", &a);
    assignPropToJSObj(&data, env, numberDouble, "b", &b);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    free(lab);
    
    return object;
}

napi_value LchJSObjFactory(napi_env env, Xyz *xyz, double clamp) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    Lch *lch = getLchFromXyz(xyz);
    if (lch == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (lch->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", lch->error);
        return object;
    }
    
    double l = lch->l;
    double c = lch->c;
    double h = lch->h;
    
    if (clamp) {
        l = clampValue(l, clamp);
        c = clampValue(c, clamp);
        h = clampValue(h, clamp);
    }
    
    assignPropToJSObj(&data, env, numberDouble, "l", &l);
    assignPropToJSObj(&data, env, numberDouble, "c", &c);
    assignPropToJSObj(&data, env, numberDouble, "h", &h);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    free(lch);
    
    return object;
}

napi_value LchLabJSObjFactory(napi_env env, Xyz *xyz, double clamp) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    LchLab *lchlab = getLchFromLab(xyz);
    if (lchlab == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (lchlab->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", lchlab->error);
        return object;
    }
    
    double l = lchlab->l;
    double c = lchlab->c;
    double h = lchlab->h;
    
    if (clamp) {
        l = clampValue(l, clamp);
        c = clampValue(c, clamp);
        h = clampValue(h, clamp);
    }
    
    assignPropToJSObj(&data, env, numberDouble, "l", &l);
    assignPropToJSObj(&data, env, numberDouble, "c", &c);
    assignPropToJSObj(&data, env, numberDouble, "h", &h);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    free(lchlab);
    
    return object;
}

napi_value LuvJSObjFactory(napi_env env, Xyz *xyz, double clamp) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    Luv *luv = getLuvFromXyz(xyz);
    if (luv == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (luv->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", luv->error);
        return object;
    }
    
    double l = luv->l;
    double u = luv->u;
    double v = luv->v;
    
    if (clamp) {
        l = clampValue(l, clamp);
        u = clampValue(u, clamp);
        v = clampValue(v, clamp);
    }
    
    assignPropToJSObj(&data, env, numberDouble, "l", &l);
    assignPropToJSObj(&data, env, numberDouble, "u", &u);
    assignPropToJSObj(&data, env, numberDouble, "v", &v);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    free(luv);
    
    return object;
}

napi_value ArgbJSObjFactory(napi_env env, Xyz *xyz, double clamp) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    Argb *argb = getARgbFromXyz(xyz);
    if (argb == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (argb->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", argb->error);
        return object;
    }
    
    double r = argb->r;
    double g = argb->g;
    double b = argb->b;
    
    if (clamp) {
        r = clampValue(r, clamp);
        g = clampValue(g, clamp);
        b = clampValue(b, clamp);
    }
    
    assignPropToJSObj(&data, env, numberDouble, "r", &r);
    assignPropToJSObj(&data, env, numberDouble, "g", &g);
    assignPropToJSObj(&data, env, numberDouble, "b", &b);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
    free(argb);
    
    return object;
}

napi_value SrgbJSObjFactory(napi_env env, Xyz *xyz, double clamp) {
    napi_status status;
    napi_value object, data;
    
    status = napi_create_object(env, &object);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, OBJ_MAKE_ERR);
        return NULL;
    }
    
    status = napi_create_object(env, &data);
    if (status != napi_ok) {
        return NULL;
    }
    
    SRgb *srgb = getSRgbFromXyz(xyz);
    if (srgb == NULL) {
        assignPropToJSObj(&object, env, string, "error", OBJ_MAKE_ERR);
        return object;
    }
    
    if (srgb->error != NULL) {
        assignPropToJSObj(&object, env, string, "error", srgb->error);
        return object;
    }
    
    double r = srgb->r;
    double g = srgb->g;
    double b = srgb->b;
    
    if (clamp) {
        r = clampValue(r, clamp);
        g = clampValue(g, clamp);
        b = clampValue(b, clamp);
    }
    
    assignPropToJSObj(&object, env, numberDouble, "r", &r);
    assignPropToJSObj(&object, env, numberDouble, "g", &g);
    assignPropToJSObj(&object, env, numberDouble, "b", &b);
    
    assignJSObjtoJSObj(env, &object, data, "data");
    
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
