//
//  test_ycbcr.c
//  lymui
//
//  Created by Marc on 14/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <cunit.h>
#include <stdlib.h>
#include "test_header.h"
#include "ycbcr.h"
#include "rgb.h"

ctest_return_t testYcbcrCreation(ctest_t *test, void *arg) {
    uint8_t uc[] = {0, 100, 200};
    struct Rgb *rgb     = makeRGB(uc, 3);
    struct Ycbcr *ycbcr = makeYcbcr(rgb);
    
    CTAssertEqual(test, 86, ycbcr->y, "Y value is wrong %d, expected: %d", ycbcr->y, 86);
    CTAssertEqual(test, 186, ycbcr->cb, "Cb value is wrong %d, expected: %d", ycbcr->cb, 186);
    CTAssertEqual(test, 77, ycbcr->cr, "Cr value is wrong %d, expected: %d", ycbcr->cr, 100);
    
    free(rgb);
    free(ycbcr);
}

ctest_return_t testYcbcrNullCreation(ctest_t *test, void *arg) {
    struct Rgb *rgb = NULL;
    struct Ycbcr *ycbcr = makeYcbcr(rgb);
    
    CTAssertNull(test, ycbcr, "YCbCr is not Null");
    
    free(rgb);
    free(ycbcr);
}

ctest_return_t testUintCreationFromYcbcr(ctest_t *test, void *arg) {
    struct Ycbcr *ycbcr = malloc(sizeof(struct Ycbcr));
    
    ycbcr->y  = 86;
    ycbcr->cb = 186;
    ycbcr->cr = 77;
    
    uint8_t *rgb = getRawRGBArrayValueFromYcbcr(ycbcr);
    CTAssertEqual(test, 0, rgb[0], "R value is wrong %d, expected: %d", rgb[0], 0);
    CTAssertEqual(test, 100, rgb[1], "G value is wrong %d, expected: %d", rgb[1], 100);
    CTAssertEqual(test, 198, rgb[2], "B value is wrong %d, expected: %d", rgb[2], 198);
    
    free(ycbcr);
    free(rgb);
}

ctest_return_t testUintNullCreationFromYcbcr(ctest_t *test, void *arg) {
    uint8_t *rgb = getRawRGBArrayValueFromYcbcr(NULL);
    CTAssertNull(test, rgb, "Rgb from YCbCr is not Null");
    
    free(rgb);
}

ctcase_t *wrapYcbcrCreationTest() {
    ctcase_t *ycbcrTest = ctcase("Ycbcr test case");
    
    // Create test case
    ctest_t *ycbcr = ctest("Create YCbCr from RGB", testYcbcrCreation, NULL);
    ctest_t *ycbcrNull = ctest("Create YCbCr from NULL Rgb", testYcbcrNullCreation, NULL);
    ctest_t *rgbArr = ctest("Create Uint8 Array from YCbCr", testUintCreationFromYcbcr, NULL);
    ctest_t *rgbNull = ctest("Create Uint8 Array should be Null", testUintNullCreationFromYcbcr, NULL);
    
    // add test case
    ctctestadd(ycbcrTest, ycbcr);
    ctctestadd(ycbcrTest, ycbcrNull);
    ctctestadd(ycbcrTest, rgbArr);
    ctctestadd(ycbcrTest, rgbNull);
    
    return ycbcrTest;
}
