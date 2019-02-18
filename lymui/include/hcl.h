//
//  hcl.h
//  lymui
//
//  Created by Marc Intha on 13/02/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#ifndef hcl_h
#define hcl_h

#include <stdio.h>
#include "rgb.h"

#define XYZ_ERR "Unable to generate intermediary Xyz value"
#define LUV_ERR "Unable to generate intermediary Luv value"

/**
 * @brief Hcl struct
 */
typedef struct Hcl {
    double h;
    double c;
    double l;
    char *error;
} Hcl;

/**
 * @brief Retrieve HCL struct from an RGB this color is based actually the polar representation of the CIE-LUV color
 * @param rgb Rgb*
 * @return Hcl*
 */
Hcl *getHclFromRgb(Rgb *rgb);

/**
 * @brief Retrieve Rgb From Hcl
 * @param hcl Hcl*
 * @return Rgb*
 */
Rgb *getRgbFromHcl(Hcl *hcl);

#endif /* hcl_h */
