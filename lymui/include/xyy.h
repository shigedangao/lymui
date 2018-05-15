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

#define chromaX 0.31271f
#define chromaY 0.32902f

/**
 * @brief Xyy struct color format
 */
struct Xyy {
    float x;
    float y;
    float Y;
};

/**
 * @description Get an Xyy struct from an Xyz struct
 * @param xyz struct Xyz pointer
 * @return xyy
 */
struct Xyy * getXyyFromXyz(struct Xyz *xyz);

/**
 * @description Get an Xyz struct from an Xyy struct
 * @param xyy struct from Xyy pointer
 * @return xyz
 */
struct Xyz * getXyzFromXyy(struct Xyy *xyy);

#endif /* xyy_h */
