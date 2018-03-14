//
//  xyz_test.c
//  lymui
//
//  Created by Marc on 13/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "rgb.h"
#include "xyz.h"
#include "helper.h"

ctest_return_t xyzRgbTestCase(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    
    CTAssertEqual(test, 3.49f, roundDigit(xyz->x * 100, 100), "Expect X to be equal to 3.49 but got %f", roundDigit(xyz->x * 100, 100));
    CTAssertEqual(test, 1.72f, roundDigit(xyz->y * 100, 100), "Expect Y to be equal to 1.72 but got %f", roundDigit(xyz->y * 100, 100));
    CTAssertEqual(test, 10.97f, roundDigit(xyz->z * 100, 100), "Expect Z to be equal to 10.97 but got %f", roundDigit(xyz->z * 100, 100));
    
    free(xyz);
}

ctest_return_t xyzAdobeRgbTestCase(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, adobeRgb);
    
    // Though this test are kinda falsy as i didn't find any XYZ converter with the adobe RGB format online... so take it with grain of salt
    CTAssertEqual(test, 3.76f, roundDigit(xyz->x * 100, 100), "Expect X to be equal to X but got %f", roundDigit(xyz->x * 100, 100));
    CTAssertEqual(test, 1.73f, roundDigit(xyz->y * 100, 100), "Expect Y to be equal to Y but got %f", roundDigit(xyz->y * 100, 100));
    CTAssertEqual(test, 11.38f, roundDigit(xyz->z * 100, 100), "Expect Z to be equal to Z but got %f", roundDigit(xyz->z * 100, 100));
    
    free(xyz);
}

ctest_return_t xyzRgbNullTestCase(ctest_t *test, void *arg) {
    struct Xyz *xyz = generateXyzFromRgb(NULL, sRgb);
    CTAssertNull(test, xyz, "Expect Xyz to be NULL");
    
    free(xyz);
}

ctcase_t *wrapXyzCreationTest() {
    ctcase_t *xyzCase = ctcase("Xyz test case");
    
    // xyz rgb case
    ctest_t *rgbCase  = ctest("Xyz with RGB case", xyzRgbTestCase, NULL);
    ctest_t *nRgbCase = ctest("NULL Xyz value", xyzRgbNullTestCase, NULL);
    ctest_t *adobeCase= ctest("Xyz adobe value", xyzAdobeRgbTestCase, NULL);
    
    // add cases
    ctctestadd(xyzCase, rgbCase);
    ctctestadd(xyzCase, nRgbCase);
    ctctestadd(xyzCase, adobeCase);
    
    return xyzCase;
}

