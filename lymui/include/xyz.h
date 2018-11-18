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

// Constant for the sRGB value to from RGB to XYZ
#define xr 0.4124564f
#define xg 0.3575761f
#define xb 0.1804375f

#define yr 0.2126729f
#define yg 0.7151522f
#define yb 0.0721750f

#define zr 0.0193339f
#define zg 0.1191920f
#define zb 0.9503041f

// Constant for Adobe RGB value from RGB to XYZ
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
#define Xn 0.95047f
#define Yn 1.000f
#define Zn 1.08883f

// Constant for the sRgb value from XYZ to RGB
#define xx 3.2404f
#define xy -1.5371f
#define xz -0.4985f

#define yx -0.9692f
#define yy 1.8760f
#define yz 0.0415f

#define zx 0.0556f
#define zy -0.2040f
#define zz 1.0572f

// Constant for the Adobe RGB value from XYZ to RGB
#define axx 2.0413f
#define axy -0.5649f
#define axz -0.3446f

#define ayx -0.9692f
#define ayy 1.8760f
#define ayz 0.0415f

#define azx 0.0134f
#define azy -0.1183f
#define azz 1.0154f

// Compound

#define ADOBE_RGB_COMPOUND 2.19921875f

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
 * @brief generate Xyz From Rgb generate a Xyz structure
 * @param rgb Struct rgb pointer
 * @param m Matrix
 * @return an Xyz struct
 */
Xyz * generateXyzFromRgb(Rgb *rgb, Matrix m);

/**
 * @brief generate an rgb from xyz struct
 * @param xyz * Xyz
 * @param m Matrix
 * @return rgb * Rgb
 */
Rgb * generateRgbFromXyz(Xyz * xyz, Matrix m);

#endif /* xyz_h */
