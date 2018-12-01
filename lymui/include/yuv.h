//
//  yuv.h
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef yuv_h
#define yuv_h

#include <stdio.h>
#include <stdint.h>
#include "rgb.h"

/**
 * @brief Yuv structure
 */
typedef struct Yuv {
    double y;
    double u;
    double v;
    char *error;
} Yuv;

/**
 * @brief GetYuvFromRgb return a pointer yuv struct from an RGB pointer
 * @param rgb a pointer struct rgb
 * @return an Yuv pointer struct
 */
Yuv *getYuvFromRgb(Rgb *rgb);

/**
 * @brief GetRgbFromYuv return a Rgb pointer struct from a Yuv
 * @param yuv a pointer Yuv struct
 * @return rgb a pointer Rgb struct
 */
Rgb *getRgbFromYuv(Yuv *yuv);

#endif /* yuv_h */
