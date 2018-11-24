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
 * @return params double * array
 */
static double *calculateParams(double x, double y, double z) {
    double u = (4.0 * x) / (x + 15.0 * y + 3.0 * z);
    double v = (9.0 * y) / (x + 15.0 * y + 3.0 * z);
    
    double *params = malloc(sizeof(double) * 2);
    if (params == NULL) {
        return NULL;
    }
    
    params[0] = u;
    params[1] = v;
    
    return params;
}

Luv *getLuvFromXyz(Xyz *xyz) {
    Luv *luv = malloc(sizeof(Luv));
    if (luv == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        luv->error = NULL_INPUT_STRUCT;
        return luv;
    }
    
    double l = 0.0f;
    // Calculate the nYr value
    double y = xyz->y / Yn;
    double *uv  = calculateParams(xyz->x, xyz->y, xyz->z);
    double *urv = calculateParams(Xn, Yn, Zn);
    
    if (uv == NULL && urv == NULL) {
        luv->error = MALLOC_ERROR;
        return luv;
    }
    
    if (y > e)
        l = 116.0 * powf(y, 1.0 / 3.0) - 16.0;
    else
        l = ko * y;
    
    luv->l = l;
    luv->u = 13.0 * l * (uv[0] - urv[0]);
    luv->v = 13.0 * l * (uv[1] - urv[1]);
    
    free(xyz);
    free(urv);
    free(uv);
    
    return luv;
}

/**
 * @discussion Calculate Y Value caclulate the y value based on the K and E value
 * @param l double
 * @return double
 */
static double calculateYValue(double l) {
    if (l > (ko * e))
        return powf((l + 16.0) / 116.0, 3.0);
    
    return l / ko;
}

/**
 * @discussion Calculate Xyz Params Calculate the required params for converting a luv to an xyz
 * @param luv  Luv pointer
 * @return *double params
 */
static double *calculateXyzParams(Luv *luv) {
    // calculate the u0 and v0 value
    double *ur = calculateParams(Xn, Yn, Zn);
    
    
    double y = calculateYValue(luv->l);
    double a = (1.0 / 3.0) * ((52.0 * luv->l) / (luv->u + 13.0 * luv->l * ur[0]) - 1.0);
    double b = -5.0 * y;
    double c = -1.0 / 3.0;
    double d = y * ((39.0 * luv->l) / (luv->v + 13.0 * luv->l * ur[1]) - 5.0);
    
    double *params = malloc(sizeof(double) * 5);
    params[0] = a;
    params[1] = b;
    params[2] = c;
    params[3] = d;
    params[4] = y;
    
    free(ur);
    
    return params;
}

Xyz *getXyzFromLuv(Luv *luv) {
    Xyz *xyz = malloc(sizeof(Xyz));
    if (xyz == NULL) {
        return NULL;
    }
    
    if (luv == NULL) {
        xyz->error = NULL_INPUT_STRUCT;
        return xyz;
    }
    
    // Calculate the Y value use by other formula...
    double *params = calculateXyzParams(luv);
    if (params == NULL) {
        xyz->error = MALLOC_ERROR;
        return xyz;
    }
    
    double tempX = (params[3] - params[1]) / (params[0] - params[2]);
    xyz->x = tempX;
    xyz->y = params[4];
    xyz->z = (tempX * params[0] + params[1]);
    
    free(luv);
    free(params);
    
    return xyz;
}
