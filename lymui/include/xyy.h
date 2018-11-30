//
//  xyy.h
//  lymui
//
//  Created by Marc on 14/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef xyy_h
#define xyy_h

#include <stdio.h>
#include "xyz.h"

#define chromaX 0.31271
#define chromaY 0.32902

/**
 * @brief Xyy struct color format
 */
typedef struct Xyy {
    double x;
    double y;
    double Y;
    char *error;
} Xyy;

/**
 * @brief Get an Xyy struct from an Xyz struct
 * @param xyz struct Xyz pointer
 * @return xyy
 */
Xyy *getXyyFromXyz(Xyz *xyz);

/**
 * @brief Get an Xyz struct from an Xyy struct
 * @param xyy struct from Xyy pointer
 * @return xyz
 */
Xyz *getXyzFromXyy(Xyy *xyy);

#endif /* xyy_h */
