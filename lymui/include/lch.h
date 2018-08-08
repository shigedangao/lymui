//
//  lch.h
//  lymui
//
//  Created by Marc on 10/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef lch_h
#define lch_h

#include <stdio.h>
#include "xyz.h"

/**
 * @brief struct representing the Lch color. Note that for converting an RGB -> LCH(uv) color we need to get the Luv value
 */
typedef struct Lch {
    float l;
    float c;
    float h;
} Lch;

/**
 * @discussion Get Lch From Xyz return an Lch struct from an Xyz value
 * @param xyz pointer struct of Xyz
 * @return Lch struct pointer
 */
Lch * getLchFromXyz(Xyz *xyz);

/**
 * @discussion Get Xyz struct from Lch pointer struct
 * @param lch pointer struct of Lch
 * @return Xyz struct pointer
 */
Xyz * getXyzFromLch(Lch *lch);

#endif /* lch_h */
