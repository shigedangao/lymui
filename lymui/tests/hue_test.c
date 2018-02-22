//
//  hue_test.c
//  lymui
//
//  Created by Marc on 20/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "rgb.h"
#include "hue.h"

ctest_return_t testSimpleHueCreation(ctest_t *test, void *arg) {
    uint8_t cvalue[3] = {255, 255, 255};
    struct Rgb *rgb  = makeRGB(cvalue, 3);
    // get the hue from the rgb
    float hue = getHueFromRgb(rgb);
    
    CTAssertEqual(test, 0.0f, hue, "Expect hue to be equal to 0 but got %f", hue);
    
    free(rgb);
}

ctest_return_t testPurpleHueCreation(ctest_t *test, void *arg) {
    uint8_t cvalue[3] = {255, 100, 255};
    struct Rgb *rgb = makeRGB(cvalue, 3);
    // get the hue
    float hue = getHueFromRgb(rgb);
    
    CTAssertEqual(test, 300.0f, hue, "Expect hue to be equal to 300 but got %f", hue);
    
    free(rgb);
}

ctest_return_t testB(ctest_t *test, void *arg) {
    uint8_t cvalue[3] = {50, 10, 232};
    struct Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    
    float hue = getHueFromRgb(rgb);
    
    CTAssertEqual(test, 251.0f, hue, "Expect hue to be equal to 251 but got %f", hue);
    
    free(rgb);
}

ctest_return_t testG(ctest_t *test, void *arg) {
    uint8_t cvalue[3] = {222, 102, 30};
    struct Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    
    float hue = getHueFromRgb(rgb);
    
    CTAssertEqual(test, 23.0f, hue, "Expect hue to be equal to 23 but got %f", hue);
    
    free(rgb);
}

ctest_return_t testR(ctest_t *test, void *arg) {
    uint8_t cvalue[3] = {244, 100, 200};
    struct Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    
    float hue = getHueFromRgb(rgb);
    CTAssertEqual(test, 318.0f, hue, "Expect hue to be equal to 318 but got %f", hue);
    
    free(rgb);
}

ctcase_t *wrapHueCreationTest() {
    ctcase_t *hueCase = ctcase("Hue test case");
    
    // Create test
    ctest_t *basicHueCreation   = ctest("Simple hue test", testSimpleHueCreation, NULL);
    ctest_t *lessSimpleCreation = ctest("Less simple purple hue creation", testPurpleHueCreation, NULL);
    ctest_t *colorB = ctest("Creation of a dominant B color hue", testB, NULL);
    ctest_t *colorG = ctest("Creation of a dominant G color hue", testG, NULL);
    ctest_t *colorR = ctest("Creation of a dominant R color hue", testR, NULL);
    
    ctctestadd(hueCase, basicHueCreation);
    ctctestadd(hueCase, lessSimpleCreation);
    ctctestadd(hueCase, colorB);
    ctctestadd(hueCase, colorG);
    ctctestadd(hueCase, colorR);
    
    return hueCase;
}
