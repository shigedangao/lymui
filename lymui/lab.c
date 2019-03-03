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
        lab->error = NULL_INPUT_PARAM;
        return lab;
    }
    
    lab->l = 116.0 * calculateDomain(xyz->y / refY) - 16.0;
    lab->a = 500.0 * (calculateDomain(xyz->x / refX) - calculateDomain(xyz->y / refY));
    lab->b = 200.0 * (calculateDomain(xyz->y / refY) - calculateDomain(xyz->z / refZ));
    lab->error = NULL;
    
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
        return pow(c, 3.0);
    
    return (116.0 * c - 16.0) / kameah;
}

Xyz *getXyzFromLab(Lab *lab) {
    Xyz *xyz = malloc(sizeof(Xyz));
    if (xyz == NULL) {
        return NULL;
    }
    
    if (lab == NULL) {
        xyz->error = NULL_INPUT_PARAM;
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
    
    xyz->error = NULL;
    
    free(lab);
    
    return xyz;
}
