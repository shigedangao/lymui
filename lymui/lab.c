//
//  lab.c
//  lymui
//
//  Created by Marc on 19/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "xyz_constant.h"
#include "errors.h"
#include "helper.h"
#include "lab.h"

/////// Lab calculation

/**
 * @discussion Calculate Domain of the color
 * @credit Big credits to Bruce Lindbloom and to Color Mine lib
 * @param c double
 * @return double
 */
static double calculateDomain(double c) {
    if (c > 0.008856)
        return cbrt(c);
    
    return (c * 7.787) + (16.0 / 116.0);
}


Lab *getLabFromXyz(Xyz *xyz) {
    Lab *lab = malloc(sizeof(Lab));
    if (lab == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        lab->error = NULL_INPUT_STRUCT;
        return lab;
    }
    
    lab->l = 116.0 * calculateDomain(xyz->y / refY) - 16.0;
    lab->a = 500.0 * (calculateDomain(xyz->x / refX) - calculateDomain(xyz->y / refY));
    lab->b = 200.0 * (calculateDomain(xyz->y / refY) - calculateDomain(xyz->z / refZ));
    
    free(xyz);
    
    return lab;
}

/////// HunterLab calculation

/**
 * @brief Get Ka Kb return the Ka Kb value based on the Xyz value (should exposed ?)
 * @return double Array
 */
static double *getKaKb() {
    double * kAkB = malloc(sizeof(double) * 2);
    kAkB[0] = (175.0 / 198.04) * (Yn + Xn);
    kAkB[1] = (70.0 / 218.11) * (Yn + Zn);
    
    return kAkB;
}

Lab *getHunterLabFromXyz(Xyz *xyz) {
    Lab *lab = malloc(sizeof(Lab));
    if (lab == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        lab->error = NULL_INPUT_STRUCT;
        return lab;
    }
    
    double * kAkB = getKaKb();
    lab->l = 100.0 * sqrt(xyz->y / Yn);
    lab->a = 100.0 * kAkB[0] * ((xyz->x / Xn - xyz->y / Yn) / sqrtf(xyz->y / Yn));
    lab->b = 100.0 * kAkB[1] * ((xyz->y / Yn - xyz->z / Zn) / sqrtf(xyz->y / Yn));
    
    free(xyz);
    free(kAkB);
    
    return lab;
}

/////// Xyz calculation

/**
 * @discussion Calculate Reverse Domain
 * @param c double
 * @return double
 */
static double calculateReverseDomain(double c) {
    if (pow(c, 3.0) > epsilon)
        return powf(c, 3.0);
    
    return (116.0 * c - 16.0) / kameah;
}

Xyz *getXyzFromLab(Lab *lab) {
    Xyz *xyz = malloc(sizeof(Xyz));
    if (xyz == NULL) {
        return NULL;
    }
    
    if (lab == NULL) {
        xyz->error = NULL_INPUT_STRUCT;
        return xyz;
    }
    
    double labL = (lab->l + 16.0) / 116.0;
    xyz->x = refX * calculateReverseDomain(labL + lab->a / 500.0);
    xyz->z = refZ * calculateReverseDomain(labL - lab->b / 200.0);
    
    // special case for y value
    if (lab->l > epsilon * kameah)
        xyz->y = refY * pow(labL, 3);
    else
        xyz->y = refY * (lab->l / kameah);
    
    free(lab);
    
    return xyz;
}
