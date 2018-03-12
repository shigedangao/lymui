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

// Constant for the sRGB value
#define xr 0.4124564
#define xg 0.3575761
#define xb 0.1804375

#define yr 0.2126729
#define yg 0.7151522
#define yb 0.0721750

#define zr 0.0193339
#define zg 0.1191920
#define zb 0.9503041

/**
 * @brief enum which define the value of the matrix for converting the matrix
 */
typedef enum Matrix {
    sRgb
} Matrix;

/**
 * @discussion generateXyzValue generate a Xyz structure
 * @param r float
 * @param g float
 * @param b float
 * @param m Matrix
 * @return an array of float
 */
float * generateXyzValue(float r, float g, float b, enum Matrix m);

#endif /* xyz_h */
