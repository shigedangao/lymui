//
//  luv.h
//  lymui
//
//  Created by Marc on 04/04/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef luv_h
#define luv_h

#include <stdio.h>
#include "xyz.h"

#define e 0.008856f
#define k 903.3f

/**
 * @brief struct representing the Luv format
 */
struct Luv {
    float l;
    float u;
    float v;
};

/**
 * @description Get Luv From Rgb calculate a Luv struct based on the RGB struct
 * @param xyz struct Rgb pointer
 * @return Luv struct
 */
struct Luv * getLuvFromXyz(struct Xyz *xyz);

/**
 * @description Get Xyz From Luv calculate the Xyz struct based on the Luv struct
 * @param luv struct Luv pointer
 * @return Xyz struct
 */
struct Xyz * getXyzFromLuv(struct Luv *luv);

#endif /* luv_h */
