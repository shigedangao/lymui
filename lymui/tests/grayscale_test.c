//
//  grayscale_test.c
//  lymui
//
//  Created by Marc Intha on 06/01/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "test_header.h"
#include "grayscale.h"

ctest_return_t getLightnessGrayScale(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 0;
    rgb->b = 0;
    
    uint8_t gray = getGrayScale(rgb, Lightness);
    
    CTAssertEqual(test, 128, gray, "Expect gray lightness to be equal to %i but got %i", 128, gray);
    free(rgb);
}

ctest_return_t getLumuinositryGrayScale(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 0;
    rgb->b = 0;
    
    uint8_t gray = getGrayScale(rgb, Luminosity);
    
    CTAssertEqual(test, 54, gray, "Expect gray to be equal to %i but got %i", 54, gray);
    free(rgb);
}

ctest_return_t getAverageGrayScale(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 0;
    rgb->b = 0;
    
    uint8_t gray = getGrayScale(rgb, Average);
    
    CTAssertEqual(test, 85, gray, "Expect gray to be equal to %i but got %i", 85, gray);
    free(rgb);
}

ctest_return_t getbt709GrayScale(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 0;
    rgb->b = 0;
    
    uint8_t gray = getGrayScale(rgb, bt709);
    
    CTAssertEqual(test, 54, gray, "Expect gray to be equal to %i but got %i", 54, gray);
    free(rgb);
}

ctest_return_t getbt2100GrayScale(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 0;
    rgb->b = 0;
    
    uint8_t gray = getGrayScale(rgb, bt2100);
    
    CTAssertEqual(test, 67, gray, "Expect gray to be equal to %i but got %i", 67, gray);
    free(rgb);
}

ctcase_t *wrapGrayscaleCreationTest() {
    ctcase_t *grayCase = ctcase("Grayscale test");
    
    ctest_t *lightness  = ctest("Lightness case", getLightnessGrayScale, NULL);
    ctest_t *luminosity = ctest("Luminosity case", getLumuinositryGrayScale, NULL);
    ctest_t *average    = ctest("Average case", getAverageGrayScale, NULL);
    ctest_t *bt709      = ctest("bt709 case", getbt709GrayScale, NULL);
    ctest_t *bt2100     = ctest("bt2100 case", getbt2100GrayScale, NULL);
    
    ctctestadd(grayCase, lightness);
    ctctestadd(grayCase, luminosity);
    ctctestadd(grayCase, average);
    ctctestadd(grayCase, bt709);
    ctctestadd(grayCase, bt2100);
    
    return grayCase;
}
