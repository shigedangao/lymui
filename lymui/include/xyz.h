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

// Compound

#define ADOBE_RGB_COMPOUND 2.19921875

/**
 * @brief Xyz struct
 */
typedef struct Xyz {
    double x;
    double y;
    double z;
    char *error;
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
Xyz *generateXyzFromRgb(Rgb *rgb, Matrix m);

/**
 * @brief generate an rgb from xyz struct
 * @param xyz * Xyz
 * @param m Matrix
 * @return rgb * Rgb
 */
Rgb *generateRgbFromXyz(Xyz * xyz, Matrix m);

#endif /* xyz_h */
