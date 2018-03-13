//
//  xyz.h
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef xyz_h
#define xyz_h

#include <stdio.h>
#include "rgb.h"

// Constant for the sRGB value
#define xr 0.4124f
#define xg 0.3575f
#define xb 0.1804f

#define yr 0.2126f
#define yg 0.7151f
#define yb 0.0721f

#define zr 0.0193f
#define zg 0.1191f
#define zb 0.9503f

/**
 * @brief Xyz struct
 */
struct Xyz {
    float x;
    float y;
    float z;
};

/**
 * @brief enum which define the value of the matrix for converting the matrix
 */
typedef enum Matrix {
    sRgb
} Matrix;

/**
 * @discussion generate Xyz From Rgb generate a Xyz structure
 * @param rgb Struct rgb pointer
 * @param m Matrix
 * @return an Xyz struct
 */
struct Xyz * generateXyzFromRgb(struct Rgb *rgb, enum Matrix m);

#endif /* xyz_h */
