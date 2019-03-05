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
#include <stdint.h>
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
 * @brief LinearRGB struct. Use for calculating the linear RGB
 */
typedef struct LinearRGB {
    double sr;
    double sg;
    double sb;
} LinearRGB;

/**
 * @brief enum which define the value of the matrix for converting the matrix
 */
typedef enum Matrix {
    srgb,
    adobeRgb
} Matrix;

/**
 * @brief get Xyz From Rgb generate a Xyz structure
 * @param rgb Struct rgb pointer
 * @param m Matrix
 * @return an Xyz struct
 */
Xyz *getXyzFromRgb(Rgb *rgb, Matrix m);

/**
 * @brief get an rgb from xyz struct
 * @param xyz * Xyz
 * @param m Matrix
 * @return rgb * Rgb
 */
Rgb *getRgbFromXyz(Xyz * xyz, Matrix m);

#endif /* xyz_h */
