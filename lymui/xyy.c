//
//  xyy.c
//  lymui
//
//  Created by Marc on 14/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include "xyy.h"

static float calculateXyyValue(float v, Xyz *xyz, uint8_t x) {
    uint8_t cond = !xyz->x && !xyz->y && !xyz->z;
    
    if (!cond)
        return v / (xyz->x + xyz->y + xyz->z);
    
    if (x)
        return chromaX;
    
    return chromaY;
}

Xyy * getXyyFromXyz(Xyz *xyz) {
    if (xyz == NULL)
        return NULL;
    
    Xyy * xyy = malloc(sizeof(Xyy));
    xyy->x = calculateXyyValue(xyz->x, xyz, 1);
    xyy->y = calculateXyyValue(xyz->y, xyz, 0);
    xyy->Y = xyz->y;
    
    free(xyz);
    
    return xyy;
}

Xyz * getXyzFromXyy(Xyy *xyy) {
    if (xyy == NULL)
        return NULL;
    
    Xyz *xyz = malloc(sizeof(Xyz));
    
    if (!xyy->y) {
        xyz->x = 0.0f;
        xyz->y = 0.0f;
        xyz->z = 0.0f;
        free(xyy);
        
        return xyz;
    }
    
    xyz->x = (xyy->x * xyy->Y) / xyy->y;
    xyz->y = xyy->Y;
    xyz->z = ((1.0f - xyy->x - xyy->y) * xyy->Y) / xyy->y;
    
    free(xyy);
    return xyz;
}
