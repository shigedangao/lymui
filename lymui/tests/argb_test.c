//
//  argb_test.c
//  lymui
//
//  Created by Marc on 14/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "helper.h"
#include "rgb.h"
#include "xyz.h"
#include "argb.h"

ctest_return_t aRgbCreationTestCase(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    struct Xyz *xyz  = generateXyzFromRgb(rgb, adobeRgb);
    struct aRgb *argb = getARgbFromXyz(xyz);
    
    CTAssertEqual(test, 19.6f, roundDigit(argb->r * 100, 100), "Expect R to be equal to X but got %f", roundDigit(argb->r * 100, 100));
    CTAssertEqual(test, 3.89f, roundDigit(argb->g * 100, 100), "Expect R to be equal to X but got %f", roundDigit(argb->g * 100, 100));
    CTAssertEqual(test, 37.25f, roundDigit(argb->b * 100, 100), "Expect R to be equal to X but got %f", roundDigit(argb->b * 100, 100));
    
    free(rgb);
    free(argb);
}

ctest_return_t aRgbNullCreationTestCase(ctest_t *test, void *arg) {
    struct aRgb *argb = getARgbFromXyz(NULL);
    CTAssertNull(test, argb, "Expect argb to be NULL");
    
    free(argb);
}

ctcase_t *wrapARgbCreationTest() {
    ctcase_t *aRgbCase = ctcase("Adobe RGB test case");
    
    ctest_t *aRgbCreation = ctest("Adobe RGB test creation", aRgbCreationTestCase, NULL);
    ctest_t *aNullCreation= ctest("Adobe RGB Null test creation", aRgbNullCreationTestCase, NULL);
    
    ctctestadd(aRgbCase, aRgbCreation);
    ctctestadd(aRgbCase, aNullCreation);
    
    return aRgbCase;
}
