//
//  luv.c
//  lymui
//
//  Created by Marc on 04/04/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "xyz_constant.h"
#include "errors.h"
#include "luv.h"

/**
 * @brief Calculate Params return the necessary params for calculating the Luv value
 * @param x double
 * @param y double
 * @param z double
 * @return LuvCompounds
 */
static LuvCompounds calculateParams(double x, double y, double z) {
    LuvCompounds compounds;
    if (!x && !y && !z) {
        compounds.u = 0.0;
        compounds.v = 0.0;
        
        return compounds;
    }
    
    compounds.u = (4.0 * x) / (x + 15.0 * y + 3.0 * z);
    compounds.v = (9.0 * y) / (x + 15.0 * y + 3.0 * z);
    
    return compounds;
}

Luv *getLuvFromXyz(Xyz *xyz) {
    Luv *luv = malloc(sizeof(Luv));
    if (luv == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        luv->error = NULL_INPUT_PARAM;
        return luv;
    }
    
    double l = 0.0f;
    // Calculate the nYr value
    double y = xyz->y / Yn;
    LuvCompounds uv  = calculateParams(xyz->x, xyz->y, xyz->z);
    LuvCompounds urv = calculateParams(Xn, Yn, Zn);
    
    if (y > exponent)
        l = 116.0 * powf(y, 1.0 / 3.0) - 16.0;
    else
        l = ko * y;
    
    luv->l = l;
    luv->u = 13.0 * l * (uv.u - urv.u);
    luv->v = 13.0 * l * (uv.v - urv.v);
    luv->error = NULL;
    
    return luv;
}

/**
 * @discussion Calculate Y Value caclulate the y value based on the K and E value
 * @param l double
 * @return double
 */
static double calculateYValue(double l) {
    if (l > (ko * exponent))
        return powf((l + 16.0) / 116.0, 3.0);
    
    return l / ko;
}

/**
 * @discussion Calculate Xyz Params Calculate the required params for converting a luv to an xyz
 * @param luv  Luv pointer
 * @return XyzCompounds
 */
static XyzCompounds calculateXyzParams(Luv *luv) {
    XyzCompounds compounds;
    
    // calculate the u0 and v0 value
    LuvCompounds ur = calculateParams(Xn, Yn, Zn);
    compounds.y = calculateYValue(luv->l);
    compounds.a = (1.0 / 3.0) * ((52.0 * luv->l) / (luv->u + 13.0 * luv->l * ur.u) - 1.0);
    compounds.b = -5.0 * compounds.y;
    compounds.c = -1.0 / 3.0;
    compounds.d = compounds.y * ((39.0 * luv->l) / (luv->v + 13.0 * luv->l * ur.v) - 5.0);
    
    return compounds;
}

Xyz *getXyzFromLuv(Luv *luv) {
    Xyz *xyz = malloc(sizeof(Xyz));
    if (xyz == NULL) {
        return NULL;
    }
    
    if (luv == NULL) {
        xyz->error = NULL_INPUT_PARAM;
        return xyz;
    }
    
    // Calculate the Y value use by other formula...
    XyzCompounds compounds = calculateXyzParams(luv);
    xyz->error = NULL;
    if (!luv->u && !luv->l) {
        xyz->x = 0;
        xyz->y = 0;
        xyz->z = 0;
        free(luv);
        
        return xyz;
    }
    
    double tempX = (compounds.d - compounds.b) / (compounds.a - compounds.c);
    xyz->x = tempX;
    xyz->y = compounds.y;
    xyz->z = (tempX * compounds.a + compounds.b);
    xyz->error = NULL;
    
    free(luv);
    
    return xyz;
}
