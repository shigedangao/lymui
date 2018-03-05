//
//  hsv_test.c
//  lymui
//
//  Created by Marc on 05/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "rgb.h"
#include "hsv.h"


ctest_return_t testHsvCreation(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 50;
    rgb->g = 100;
    rgb->b = 100;
    
    struct Hsv *hsv = getHsvFromRgb(rgb);
    CTAssertEqual(test, 180, hsv->h, "Expect hue to be equal to 180 but got %f", hsv->h);
    CTAssertEqual(test, 50.0f, hsv->s, "Expect s to be equal to 50 but got %f", hsv->s);
    CTAssertEqual(test, 39.2f, hsv->v, "Expect v to be equal to 39 but got %f", hsv->v);
    
    free(hsv);
}

ctest_return_t testBlackHsvCreation(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    struct Hsv *hsv = getHsvFromRgb(rgb);
    CTAssertEqual(test, 0.0f, hsv->h, "Expect hue to be equal to 0 but got %f", hsv->h);
    CTAssertEqual(test, 0.0f, hsv->s, "Expect s to be equal to 0 but got %f", hsv->s);
    CTAssertEqual(test, 0.0f, hsv->v, "Expect v to be equal to 0 but got %f", hsv->v);
}

ctcase_t *wrapHsvCreationTest() {
    ctcase_t *hsvCase = ctcase("Hsv test case");
    
    // creation of hsv
    ctest_t *hsvCreation = ctest("Hsv creation test from RGB", testHsvCreation, NULL);
    ctest_t *hsvEmptyCreation = ctest("Hsv creation test from black RGB", testBlackHsvCreation, NULL);
    
    // add test
    ctctestadd(hsvCase, hsvCreation);
    ctctestadd(hsvCase, hsvEmptyCreation);
    
    return hsvCase;
}

