//
//  lab.h
//  lymui
//
//  Created by Marc on 19/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef lab_h
#define lab_h

#include <stdio.h>
#include "xyz.h"

#define epsilon 0.008856f
#define kameah 903.3f

/**
 * @brief Lab struct representing the Lab color space
 */
typedef struct Lab {
    float l;
    float a;
    float b;
} Lab;

/**
 * @discussion Get Lab From Xyz return a new Lab struct based on Xyz struct
 * @param xyz Xyz struct
 * @return Lab struct
 */
Lab * getLabFromXyz(Xyz *xyz);

/**
 * @discussion Get Huntere Lab From Xyz return a new Lab struct based on HunterLab calculation..
 * @param xyz Xyz struct
 * @return Lab struct
 */
Lab * getHunterLabFromXyz(Xyz *xyz);

/**
 * @discussion Get Xyz From Lab return a new Xyz struct from a Lab struct
 */
Xyz * getXyzFromLab(Lab *lab);

#endif /* lab_h */
