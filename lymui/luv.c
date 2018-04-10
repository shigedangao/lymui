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

struct Luv * getLuvFromXyz(struct Xyz *xyz) {
    if (xyz == NULL)
        return NULL;
    
    // Calculate the nYr value
    float nYr = xyz->y / Yn;
    float *uv  = calculateParams(xyz->x, xyz->y, xyz->z);
    float *urv = calculateParams(Xn, Yn, Zn);
    float l = 0.0f;
    
    struct Luv *luv = malloc(sizeof(struct Luv));
    if (nYr > e)
        l = 116.0f * powf(nYr, 1/3) - 16;
    else
        l = k * nYr;
    
    luv->l = l;
    luv->u = 13.0f * l * (uv[0] - urv[0]);
    luv->v = 13.0f * l * (uv[1] - urv[1]);
    
    printf("value of l %f \n", l);
    
    free(xyz);
    free(urv);
    free(uv);
    
    return luv;
}

/**
 * @discussion Calculate Y Value caclulate the y value based on the K and E value
 * @param l float
 * @return float
 */
static float calculateYValue(float l) {
    if (l > k * e)
        return powf((l + 16.0f) / 116, 3);
    
    return l / k;
}

/**
 * @discussion Calculate Xyz Params Calculate the required params for converting a luv to an xyz
 * @param luv struct Luv pointer
 * @return *float params
 */
static float * calculateXyzParams(struct Luv *luv) {
    // calculate the u0 and v0 value
    float *ur = calculateParams(xr, yr, zr);
    
    float y = calculateYValue(luv->l);
    float a = 1/3 * ((52.0f * luv->l) / (luv->u + 13.0f * luv->l * ur[0]) - 1.0f);
    float b = -5.0f * y;
    float c = -1/3;
    float d = y * ((39.0 * luv->l) / (luv->v + 13.0f * luv->l * ur[1]) - 5.0f);
    
    float *params = malloc(sizeof(float) * 5);
    params[0] = a;
    params[1] = b;
    params[2] = c;
    params[3] = d;
    params[4] = y;
    
    return params;
}

struct Xyz * getXyzFromLuv(struct Luv *luv) {
    if (luv == NULL)
        return NULL;
    
    // Calculate the Y value use by other formula...
    float *params = calculateXyzParams(luv);
    struct Xyz *xyz = malloc(sizeof(struct Xyz));
    
    xyz->x = (params[3] - params[1]) / (params[0] - params[2]);
    xyz->y = params[4];
    xyz->z = xyz->x * params[0] + params[1];
    
    return xyz;
}
