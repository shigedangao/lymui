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

#define epsilon 0.008856
#define kameah 24389.0 / 27.0

#define refX 0.95047
#define refY 1.000
#define refZ 1.08883

/**
 * @brief Lab struct representing the Lab color space
 */
typedef struct Lab {
    double l;
    double a;
    double b;
    char *error;
} Lab;

/**
 * @brief Get Lab From Xyz return a new Lab struct based on Xyz struct
 * @param xyz Xyz struct
 * @return Lab struct
 */
Lab *getLabFromXyz(Xyz *xyz);

/**
 * @discussion Get Xyz From Lab return a new Xyz struct from a Lab struct
 */
Xyz *getXyzFromLab(Lab *lab);

#endif /* lab_h */
