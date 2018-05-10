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
 * @brief struct representing the Lch color. Note that for converting an RGB -> LCH color we need to get the Luv value
 */
struct Lch {
    float l;
    float c;
    float h;
};

/**
 * @discussion Get Lch From Xyz return an Lch struct from an Xyz value
 * @param xyz pointer struct of Xyz
 * @return Lch struct pointer
 */
struct Lch * getLchFromXyz(struct Xyz *xyz);

/**
 * @discussion Get Xyz struct from Lch pointer struct
 * @param lch pointer struct of Lch
 * @return Xyz struct pointer
 */
struct Xyz * getXyzFromLch(struct Lch *lch);

#endif /* lch_h */
