//
//  cymk.h
//  lymui
//
//  Created by Marc on 15/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef cymk_h
#define cymk_h

#include <stdio.h>
#include "rgb.h"

struct Cymk {
    float c;
    float y;
    float m;
    float k;
};

struct Cymk *getCymkFromRgb(struct Rgb *rgb);

#endif /* cymk_h */
