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

// Constant for Adobe RGB value
#define axr 0.5767f
#define axg 0.1855f
#define axb 0.1881f

#define ayr 0.2973f
#define ayg 0.6273f
#define ayb 0.0752f

#define azr 0.0270f
#define azg 0.0706f
#define azb 0.9911f

// Illuminant for White D65

// Illuminant for D65
#define Xn 95.047f
#define Yn 100.0f
#define Zn 108.883f

/**
 * @brief Xyz struct
 */
typedef struct Xyz {
    float x;
    float y;
    float z;
} Xyz;

/**
 * @brief enum which define the value of the matrix for converting the matrix
 */
typedef enum Matrix {
    srgb,
    adobeRgb
} Matrix;

/**
 * @discussion generate Xyz From Rgb generate a Xyz structure
 * @param rgb Struct rgb pointer
 * @param m Matrix
 * @return an Xyz struct
 */
Xyz * generateXyzFromRgb(Rgb *rgb, Matrix m);

#endif /* xyz_h */
