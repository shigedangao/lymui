//
//  xyy.c
//  lymui
//
//  Created by Marc on 14/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include "xyy.h"

static float calculateXyyValue(float v, struct Xyz *xyz, uint8_t x) {
    uint8_t cond = !xyz->x && !xyz->y && !xyz->z;
    
    if (!cond)
        return v / (xyz->x + xyz->y + xyz->z);
    
    if (x)
        return chromaX;
    
    return chromaY;
}

struct Xyy * getXyyFromXyz(struct Xyz *xyz) {
    if (xyz == NULL)
        return NULL;
    
    struct Xyy * xyy = malloc(sizeof(struct Xyy));
    xyy->x = calculateXyyValue(xyz->x, xyz, 1);
    xyy->y = calculateXyyValue(xyz->y, xyz, 0);
    xyy->Y = xyz->y;
    
    free(xyz);
    
    return xyy;
}

struct Xyz * getXyzFromXyy(struct Xyy *xyy) {
    if (xyy == NULL)
        return NULL;
    
    struct Xyz *xyz = malloc(sizeof(struct Xyz));
    xyz->x = (xyy->x * xyy->Y) / xyz->y;
    xyz->y = xyy->y;
    xyz->z = ((1.0f - xyy->x - xyy->y) * xyy->Y) / xyz->y;
    
    return xyz;
}
