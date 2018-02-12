//
//  ycbcr.c
//  lymui
//
//  Created by Marc on 12/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "ycbcr.h"
#include <stdlib.h>


// constant variable
const float yValue[]  = {0.299, 0.587, 0.114};
const float cbValue[] = {-0.169, 0.331, 0.5};
const float crValue[] = {0.5, 0.419, -0.081};

// Make Ycbcr
struct Ycbcr *makeYcbcr(struct Rgb *rgb) {
    if (rgb == NULL) {
        return NULL;
    }
    
    struct Ycbcr *v = malloc(sizeof (struct Ycbcr));
    v->y  = yValue[0]  * rgb->r + yValue[1]  * rgb->g + yValue[2]  * rgb->b;
    v->cb = 128 + (cbValue[0] * rgb->r - cbValue[1] * rgb->b + cbValue[2] * rgb->b);
    v->cr = 128 + (crValue[0] * rgb->r - crValue[1] * rgb->b - crValue[2] * rgb->b);
    
    return v;
}
