//
//  lab.c
//  lymui
//
//  Created by Marc on 19/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "lab.h"

/////// Lab calculation

/**
 * @discussion Calculate Domain of the color
 * @credit Big credits to Bruce Lindbloom and to Color Mine lib
 * @param c float
 * @return float
 */
static float calculateDomain(float c) {
    if (c > epsilon)
        return 3.0f * sqrtf(c);
    
    return (c * kameah + 16.0f) / 116.0f;
}

struct Lab *getLabFromXyz(struct Xyz *xyz) {
    if (xyz == NULL)
        return NULL;
    
    struct Lab *lab = malloc(sizeof(struct Lab));
    lab->l = 116.0f * calculateDomain(xyz->y / Yn) - 16.0f;
    lab->a = 500.0f * (calculateDomain(xyz->x / Xn) - calculateDomain(xyz->y / Yn));
    lab->b = 200.0f * (calculateDomain(xyz->y / Yn) - calculateDomain(xyz->z / Zn));
    
    free(xyz);
    
    return lab;
}

/////// HunterLab calculation

/**
 * @discussion Get Ka Kb return the Ka Kb value based on the Xyz value (should exposed ?)
 * @return float Array
 */
static float *getKaKb() {
    float * kAkB = malloc(sizeof(float) * 2);
    kAkB[0] = (175.0f / 198.04f) * (Yn + Xn);
    kAkB[1] = (70.0f / 218.11f) * (Yn + Zn);
    
    return kAkB;
}

struct Lab *getHunterLabFromXyz(struct Xyz *xyz) {
    if (xyz == NULL)
        return NULL;
    
    float * kAkB = getKaKb();
    struct Lab *lab = malloc(sizeof(struct Lab));
    
    lab->l = 100 * sqrtf(xyz->y / Yn);
    lab->a = kAkB[0] * ((xyz->x / Xn - xyz->y / Yn) / sqrtf(xyz->y / Yn));
    lab->b = kAkB[1] * ((xyz->y / Yn - xyz->z / Zn) / sqrtf(xyz->y / Yn));
    
    free(xyz);
    free(kAkB);
    
    return lab;
}

/////// Xyz calculation

/**
 * @discussion Calculate Reverse Domain
 * @param c float
 * @return float
 */
static float calculateReverseDomain(float c) {
    if (powf(c, 3) > epsilon)
        return powf(c, 3.0f);
    
    return (116.0f * c - 16.0f) / kameah;
}

struct Xyz *getXyzFromLab(struct Lab *lab) {
    if (lab == NULL)
        return NULL;
    
    struct Xyz *xyz = malloc(sizeof(struct Xyz));
    
    float labL = (lab->l + 16.0f) / 116.0f;
    xyz->x = Xn * calculateReverseDomain(labL + lab->a / 500.0f);
    xyz->z = Zn * calculateReverseDomain(labL - lab->b / 200.0f);
    
    // special case for y value
    if (lab->l > epsilon * kameah)
        xyz->y = Yn * powf(labL, 3);
    else
        xyz->y = Yn * (lab->l / kameah);
    
    free(lab);
    
    return xyz;
}
