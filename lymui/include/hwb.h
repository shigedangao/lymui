//
//  hwb.h
//  lymui
//
//  Created by Marc Intha on 26/12/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef hwb_h
#define hwb_h

#include <stdio.h>
#include "rgb.h"

/**
 * @brief Hwb sructure
 */
typedef struct Hwb {
    double h;
    double w;
    double b;
    char *error;
} Hwb;

/**
 * @brief get hwb from rgb
 * @param rgb Rgb pointer struct
 * @return hwb Hwb pointer struct
 */
Hwb *getHwbFromRgb(Rgb *rgb);

/**
 * @brief get rgb from hwb
 * @param hwb Hwb pointer struct
 * @return rgb Rgb pointer struct
 */
Rgb *getRgbFromHwb(Hwb *hwb);

#endif /* hwb_h */
