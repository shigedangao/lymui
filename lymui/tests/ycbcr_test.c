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
#include "errors.h"
#include "ycbcr.h"
#include "rgb.h"

ctest_return_t testYcbcrCreation(ctest_t *test, void *arg) {
    uint8_t uc[] = {0, 100, 200};
    Rgb *rgb     = makeRGB(uc, 3);
    Ycbcr *ycbcr = getYcbcrFromRgb(rgb);
    
    CTAssertEqual(test, 86, ycbcr->y, "Expect Y to be equal to %i but got %i", ycbcr->y, 86);
    CTAssertEqual(test, 187, ycbcr->cb, "Expect Cb to be equal to %i but got %i", ycbcr->cb, 186);
    CTAssertEqual(test, 77, ycbcr->cr, "Expect Cr to be equal to %i but got %i", ycbcr->cr, 100);
    
    free(rgb);
    free(ycbcr);
}

ctest_return_t testYcbcrNullCreation(ctest_t *test, void *arg) {
    Rgb *rgb = NULL;
    Ycbcr *ycbcr = getYcbcrFromRgb(rgb);
    
    CTAssertEqual(test, ycbcr->error, NULL_INPUT_STRUCT, "Expect to return a string message error", NULL_INPUT_STRUCT);
    
    free(rgb);
    free(ycbcr);
}

ctest_return_t testUintCreationFromYcbcr(ctest_t *test, void *arg) {
    Ycbcr *ycbcr = malloc(sizeof( Ycbcr));
    
    ycbcr->y  = 86;
    ycbcr->cb = 186;
    ycbcr->cr = 77;
    
    Rgb *rgb = getRGBFromYcbcr(ycbcr);
    CTAssertEqual(test, 0, rgb->r, "Expect R to be equal to %i but got %i", 0, rgb->r);
    CTAssertEqual(test, 100, rgb->g, "Expect G to be equal to %i but got %i", 100, rgb->g);
    CTAssertEqual(test, 199, rgb->b, "Expect B to be equal to %i but got %i", 198, rgb->b);
    
    free(ycbcr);
    free(rgb);
}

ctest_return_t testUintNullCreationFromYcbcr(ctest_t *test, void *arg) {
    Rgb *rgb = getRGBFromYcbcr(NULL);
    CTAssertStringEqual(test, rgb->error, NULL_INPUT_STRUCT, "Expect to return a string message error", NULL_INPUT_STRUCT);
    
    free(rgb);
}

ctcase_t *wrapYcbcrCreationTest() {
    ctcase_t *ycbcrTest = ctcase("Ycbcr test case");
    
    // Create test case
    ctest_t *testYcbcr = ctest("Creation of a YCbCr from RGB", testYcbcrCreation, NULL);
    ctest_t *testYcbcrNull = ctest("Creation of a NULL YCbCr from NULL Rgb", testYcbcrNullCreation, NULL);
    ctest_t *testRgb = ctest("Create of a RGB from YCbCr", testUintCreationFromYcbcr, NULL);
    ctest_t *testRgbNull = ctest("Create of a NULL RGB from NULL YCbCr", testUintNullCreationFromYcbcr, NULL);
    
    // add test case
    ctctestadd(ycbcrTest, testYcbcr);
    ctctestadd(ycbcrTest, testYcbcrNull);
    ctctestadd(ycbcrTest, testRgb);
    ctctestadd(ycbcrTest, testRgbNull);
    
    return ycbcrTest;
}
