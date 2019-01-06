//
//  xyy.c
//  lymui
//
//  Created by Marc on 14/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include "errors.h"
#include "xyy.h"

static double calculateXyyValue(double v, Xyz *xyz, uint8_t x) {
    uint8_t cond = !xyz->x && !xyz->y && !xyz->z;
    if (!cond)
        return v / (xyz->x + xyz->y + xyz->z);
    
    if (x)
        return chromaX;
    
    return chromaY;
}

Xyy *getXyyFromXyz(Xyz *xyz) {
    Xyy * xyy = malloc(sizeof(Xyy));
    if (xyy == NULL) {
        return NULL;
    }
    
    if (xyz == NULL) {
        xyy->error = NULL_INPUT_STRUCT;
        return xyy;
    }
    
    xyy->x = calculateXyyValue(xyz->x, xyz, 1);
    xyy->y = calculateXyyValue(xyz->y, xyz, 0);
    xyy->Y = xyz->y;
    xyy->error = NULL;
    
    return xyy;
}

Xyz *getXyzFromXyy(Xyy *xyy) {
    Xyz *xyz = malloc(sizeof(Xyz));
    if (xyz == NULL) {
        return NULL;
    }
    
    if (xyy == NULL) {
        xyz->error = NULL_INPUT_STRUCT;
        return xyz;
    }
    
    if (!xyy->y) {
        xyz->x = 0.0;
        xyz->y = 0.0;
        xyz->z = 0.0;
        free(xyy);
        
        return xyz;
    }
    
    xyz->x = (xyy->x * xyy->Y) / xyy->y;
    xyz->y = xyy->Y;
    xyz->z = ((1.0 - xyy->x - xyy->y) * xyy->Y) / xyy->y;
    xyz->error = NULL;
    
    free(xyy);
    return xyz;
}
