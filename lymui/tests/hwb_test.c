//
//  hwb_test.c
//  lymui
//
//  Created by Marc Intha on 26/12/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "test_header.h"
#include <stdlib.h>
#include <stdio.h>
#include <cunit.h>
#include "hwb.h"

ctest_return_t testRgbToHwb(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 17;
    rgb->g = 12;
    rgb->b = 93;
    
    Hwb *hwb = getHwbFromRgb(rgb);
    
    CTAssertDecimalEqual(test, hwb->h, 244.0f, 0.01f, "Expect H to be equal to %f but got %f", 244.0f, hwb->h);
    CTAssertDecimalEqual(test, hwb->w, 4.7f, 0.01f, "Expect W to be equal to %f but got %f", 4.7f, hwb->w);
    CTAssertDecimalEqual(test, hwb->b, 63.52f, 0.01f, "Expect B to be equal to %f but got %f", 63.5f, hwb->b);
    
    free(hwb);
}

ctest_return_t testWhiteRgbToHwb(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Hwb *hwb = getHwbFromRgb(rgb);
    
    CTAssertDecimalEqual(test, hwb->h, 0.0f, 0.01f, "Expect H to be equal to %f but got %f", 0.0f, hwb->h);
    CTAssertDecimalEqual(test, hwb->w, 100.0f, 0.01f, "Expect W to be equal to %f but got %f", 100.0f, hwb->w);
    CTAssertDecimalEqual(test, hwb->b, 0.0f, 0.01f, "Expect B to be equal to %f but got %f", 0.0f, hwb->b);

    free(hwb);
}

ctest_return_t testBlackRgbToHwb(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Hwb *hwb = getHwbFromRgb(rgb);
    
    CTAssertDecimalEqual(test, hwb->h, 0.0f, 0.01f, "Expect H to be equal to %f but got %f", 0.0f, hwb->h);
    CTAssertDecimalEqual(test, hwb->w, 0.0f, 0.01f, "Expect W to be equal to %f but got %f", 0.0f, hwb->w);
    CTAssertDecimalEqual(test, hwb->b, 100.0f, 0.01f, "Expect B to be equal to %f but got %f", 100.0f, hwb->b);
    
    free(hwb);
}


ctcase_t *wrapHwbCreationTest() {
    ctcase_t *hwbCase = ctcase("Hwb creation test");
    
    ctest_t *testHwbCreation = ctest("Creation of hwb", testRgbToHwb, NULL);
    ctest_t *testHwbWhiteCreation = ctest("Creation of a white hwb", testWhiteRgbToHwb, NULL);
    ctest_t *testHwbBlackCreation = ctest("Creation of a black hwb", testBlackRgbToHwb, NULL);
                                          
    ctctestadd(hwbCase, testHwbCreation);
    ctctestadd(hwbCase, testHwbWhiteCreation);
    ctctestadd(hwbCase, testHwbBlackCreation);
    
    return hwbCase;
}
