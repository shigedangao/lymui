//
//  hunterlab.c
//  lymui
//
//  Created by Marc Intha on 26/02/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hunterlab.h"
#include "xyz_constant.h"
#include "errors.h"

/**
 * @brief Get Ka Kb return the Ka Kb value based on the Xyz value
 * @return double Array
 */
static double *getKaKb() {
    double *kAkB = malloc(sizeof(double) * 2);
    if (kAkB == NULL) {
        return NULL;
    }
    
    kAkB[0] = (175.0 / 198.04) * (Yn + Xn);
    kAkB[1] = (70.0 / 218.11) * (Yn + Zn);
    
    return kAkB;
}

HLab *getHLabFromXyz(Xyz *xyz) {
    HLab *hlab = malloc(sizeof(HLab));
    if (hlab == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        hlab->error = NULL_INPUT_PARAM;
        return hlab;
    }
    
    double *kAkB = getKaKb();
    if (kAkB == NULL) {
        hlab->error = MALLOC_ERROR;
        return hlab;
    }
    
    hlab->l = 100.0 * sqrt(xyz->y / Yn);
    hlab->a = 100.0 * kAkB[0] * ((xyz->x / Xn - xyz->y / Yn) / sqrt(xyz->y / Yn));
    hlab->b = 100.0 * kAkB[1] * ((xyz->y / Yn - xyz->z / Zn) / sqrt(xyz->y / Yn));
    hlab->error = NULL;
    
    free(kAkB);
    
    return hlab;
}
