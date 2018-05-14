//
//  lchlab.h
//  lymui
//
//  Created by Marc on 14/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef lchlab_h
#define lchlab_h

#include <stdio.h>
#include "xyz.h"

/**
 * @brief Lchlab structure of the lch(lab) lch based on the lab struct
 */
struct Lchlab {
    float l;
    float c;
    float h;
};

/**
 * @description Get an Lch struct from a Lab struct
 * @param xyz Xyz struct pointer
 * @return Lchlab struct pointer
 */
struct Lchlab * getLchFromLab(struct Xyz *xyz);

/**
 * @description Get an Xyz struct from a Lchlab
 * @param lch Lchlab struct pointer
 * @return xyz Xyz struct pointer
 */
struct Xyz * getXyzFromLch(struct Lchlab *lch);


#endif /* lchlab_h */
