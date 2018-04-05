//
//  luv.c
//  lymui
//
//  Created by Marc on 04/04/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "luv.h"

/**
 * @discussion Calculate Params return the necessary params for calculating the Luv value
 * @param x float
 * @param y float
 * @param z float
 * @return params float * array
 */
static float * calculateParams(float x, float y, float z) {
    float u = (4.0f * x) / (x + 15.0f * y + 3.0f * z);
    float v = (9.0f * y) / (x + 15.0f * y + 3.0f * z);
    
    float *params = malloc(sizeof(float) * 2);
    params[0] = u;
    params[1] = v;
    
    return params;
}

struct Luv * getLuvFromRgb(struct Xyz *xyz) {
    if (xyz == NULL)
        return NULL;
    
    // Calculate the nYr value
    float nYr = xyz->y / yr;
    float *uv  = calculateParams(xyz->x, xyz->y, xyz->z);
    float *urv = calculateParams(Xn, Yn, Zn);
    float l = 0.0f;
    
    struct Luv *luv = malloc(sizeof(struct Luv));
    if (nYr > e)
        l = 116.0f * powf(Yn, 1/3) - 16;
    else
        l = k * Yn;
    
    luv->l = l;
    luv->u = 13.0f * l * (uv[0] - urv[1]);
    luv->v = 13.0f * l * (uv[1] - urv[1]);
    
    free(xyz);
    
    return luv;
}

struct Xyz * getXyzFromLuv(struct Luv *luv) {
    if (luv == NULL)
        return NULL;
    
    struct Xyz *xyz = malloc(sizeof(struct Xyz));
    
    return xyz;
}
