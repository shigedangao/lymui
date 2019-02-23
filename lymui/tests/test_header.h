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

ctcase_t *wrapRgbCreationTest(void);

ctcase_t *wrapHexCreationTest(void);

ctcase_t *wrapYcbcrCreationTest(void);

ctcase_t *wrapCymkCreationTest(void);

ctcase_t *wrapHueCreationTest(void);

ctcase_t *wrapHslCreationTest(void);

ctcase_t *wrapYuvCreationTest(void);

ctcase_t *wrapSRgbCreationTest(void);

ctcase_t *wrapXyzCreationTest(void);

ctcase_t *wrapARgbCreationTest(void);

ctcase_t *wrapLabCreationTest(void);

ctcase_t *wrapLuvCreationTest(void);

ctcase_t *wrapLchCreationTest(void);

ctcase_t *wrapLchLabCreationTest(void);

ctcase_t *wrapXyyCreationTest(void);

ctcase_t *wrapHwbCreationTest(void);

ctcase_t *wrapTslCreationTest(void);

void wrapHsvTest(void);

void wrapGrayScaleTest(void);

void wrapHclTest(void);

#endif /* rgb_test_h */
