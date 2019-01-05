//
//  tsl_test.c
//  lymui
//
//  Created by Marc Intha on 05/01/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "tsl.h"

ctest_return_t testWhiteRgbFromTsl(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Tsl *tsl = getTslFromRgb(rgb);
    
    CTAssertDecimalEqual(test, 0.0, tsl->t, 0.1, "Expect T to be equal to %f but got %f", 0.0, tsl->t);
    CTAssertDecimalEqual(test, 0.0, tsl->s, 0.1, "Expect S to be equal to %f but got %f", 0.0, tsl->s);
    CTAssertDecimalEqual(test, 255.0, tsl->l, 0.1, "Expect L to be equal to %f but got %f", 255.0, tsl->l);
    
    free(tsl);
}

ctest_return_t testBlackRgbFromTsl(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Tsl *tsl = getTslFromRgb(rgb);
    
    CTAssertDecimalEqual(test, 0.0, tsl->t, 0.1, "Expect T to be equal to %f but got %f", 0.0, tsl->t);
    CTAssertDecimalEqual(test, 0.0, tsl->s, 0.1, "Expect S to be equal to %f but got %f", 0.0, tsl->s);
    CTAssertDecimalEqual(test, 0.0, tsl->l, 0.1, "Expect L to be equal to %f but got %f", 0.0, tsl->l);
    
    free(tsl);
}

ctest_return_t testRgbFromTsl(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 128;
    
    Tsl *tsl = getTslFromRgb(rgb);
    
    CTAssertDecimalEqual(test, 0.787, tsl->t, 0.001, "Expect T to be equal to %f but got %f", 0.787, tsl->t);
    CTAssertDecimalEqual(test, 0.386, tsl->s, 0.001, "Expect S to be equal to %f but got %f", 0.386, tsl->s);
    CTAssertDecimalEqual(test, 35.412, tsl->l, 0.001, "Expect L to be equal to %f but got %f", 35.412, tsl->l);
    
    free(tsl);
}

ctcase_t *wrapTslCreationTest() {
    ctcase_t *tslCase = ctcase("Tsl color case");
    
    ctest_t *whiteTsl = ctest("White Rgb -> TSL case", testWhiteRgbFromTsl, NULL);
    ctest_t *blackTsl = ctest("Black Rgb -> TSL case", testBlackRgbFromTsl, NULL);
    ctest_t *regularTsl = ctest("Regular Rgb -> TSL case", testRgbFromTsl, NULL);

    
    ctctestadd(tslCase, whiteTsl);
    ctctestadd(tslCase, blackTsl);
    ctctestadd(tslCase, regularTsl);
    
    return tslCase;
}
