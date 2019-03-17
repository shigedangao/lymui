//
//  rgb_test.h
//  lymui
//
//  Created by Marc on 14/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef rgb_test_h
#define rgb_test_h

#include <stdio.h>

/**
 * Round Up
 *  Round up just round the value to the nearest value
 * @param value double
 * @param cell double
 * @return double
 */
double roundup(double value, double cell);

int wrapRgbTest(void);

int wrapHexTest(void);

int wrapHueTest(void);

int wrapCymkTest(void);

int wrapYcbcrTest(void);

int wrapHslTest(void);

int wrapHsvTest(void);

int wrapYuvTest(void);

int wrapGrayScaleTest(void);

int wrapHwbTest(void);

int wrapTslTest(void);

int wrapXyzTest(void);

int wrapArgbTest(void);

int wrapSrgbTest(void);

int wrapLabTest(void);

int wrapHLabTest(void);

int wrapLuvTest(void);

int wrapLchTest(void);

int wrapLchLabTest(void);

int wrapXyyTest(void);

#endif /* rgb_test_h */
