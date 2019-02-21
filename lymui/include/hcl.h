//
//  hcl.h
//  lymui
//
//  Created by Marc Intha on 13/02/2019.
//  Copyright © 2019 Marc. All rights reserved.
//  The implementation is based on the python-colorspace lib: https://github.com/retostauffer/python-colorspace/blob/da56c170fbaa8a6ca27f9483954ac3e2f51af617/colorspace/colorlib.py#L1318
//  Credits to retostauffer for the original implementation.
//

#ifndef hcl_h
#define hcl_h

#include <stdio.h>
#include "luv.h"

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
 * @brief Retrieve HCL struct from a Luv this color is based actually the polar representation of the CIE-LUV color
 * @param luv Luv*
 * @return Hcl*
 */
Hcl *getHclFromLuv(Luv *luv);

/**
 * @brief Retrieve Rgb From Hcl
 * @param hcl Hcl*
 * @return Luv*
 */
Luv *getLuvFromHcl(Hcl *hcl);

#endif /* hcl_h */
