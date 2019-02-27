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
#include <ctcase.h>

/**
 * Round Up
 *  Round up just round the value to the nearest value
 * @param value double
 * @param cell double
 * @return double
 */
double roundup(double value, double cell);

ctcase_t *wrapLchCreationTest(void);

ctcase_t *wrapLchLabCreationTest(void);

ctcase_t *wrapXyyCreationTest(void);

ctcase_t *wrapHwbCreationTest(void);

ctcase_t *wrapTslCreationTest(void);

void wrapRgbTest(void);

void wrapHexTest(void);

void wrapHueTest(void);

void wrapCymkTest(void);

void wrapYcbcrTest(void);

void wrapHslTest(void);

void wrapHsvTest(void);

void wrapYuvTest(void);

void wrapGrayScaleTest(void);

void wrapHclTest(void);

void wrapXyzTest(void);

void wrapArgbTest(void);

void wrapSrgbTest(void);

void wrapLabTest(void);

void wrapHLabTest(void);

void wrapLuvTest(void);

#endif /* rgb_test_h */
