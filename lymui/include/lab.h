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

// Illuminant for D65
#define Xn 95.047f
#define Yn 100.0f
#define Zn 108.883

/**
 * @brief Lab struct representing the Lab color space
 */
struct Lab {
    float l;
    float a;
    float b;
};

/**
 * @discussion Get Lab From Xyz return a new Lab struct based on Xyz struct
 * @param xyz Xyz struct
 * @return Lab struct
 */
struct Lab * getLabFromXyz(struct Xyz *xyz);

/**
 * @discussion Get Huntere Lab From Xyz return a new Lab struct based on HunterLab calculation..
 * @param xyz Xyz struct
 * @return Lab struct
 */
struct Lab * getHunterLabFromXyz(struct Xyz *xyz);

/**
 * @discussion Get Xyz From Lab return a new Xyz struct from a Lab struct
 */
struct Xyz * getXyzFromLab(struct Lab *lab);

#endif /* lab_h */
