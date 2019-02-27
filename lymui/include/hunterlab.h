//
//  hunterlab.h
//  lymui
//
//  Created by Marc Intha on 26/02/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#ifndef hunterlab_h
#define hunterlab_h

#include <stdio.h>
#include "xyz.h"

/**
 * @brief HLab struct representing the Lab color space
 */
typedef struct HLab {
    double l;
    double a;
    double b;
    char *error;
} HLab;

/**
 * Get HLab from Xyz
 * @brief return a Hunter Lab from an Xyz
 * @param xyz Xyz pointer
 * @return HLab pointer
 */
HLab *getHLabFromXyz(Xyz *xyz);

#endif /* hunterlab_h */
