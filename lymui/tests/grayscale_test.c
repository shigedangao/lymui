//
//  grayscale_test.c
//  lymui
//
//  Created by Marc Intha on 06/01/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "grayscale.h"

MU_TEST(lightness) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 0;
    rgb->b = 0;
    
    uint8_t gray = getGrayScale(rgb, Lightness);
    mu_assert_int_eq(128, gray);
    
    free(rgb);
}

MU_TEST(luminosity) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 0;
    rgb->b = 0;
    
    uint8_t gray = getGrayScale(rgb, Luminosity);
    mu_assert_int_eq(54, gray);
    
    free(rgb);
}

MU_TEST(average) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 0;
    rgb->b = 0;
    
    uint8_t gray = getGrayScale(rgb, Average);
    mu_assert_int_eq(85, gray);
    
    free(rgb);
}

MU_TEST(bt_709) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 0;
    rgb->b = 0;
    
    uint8_t gray = getGrayScale(rgb, bt709);
    mu_assert_int_eq(54, gray);
    
    free(rgb);
}

MU_TEST(bt_2100) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 0;
    rgb->b = 0;
    
    uint8_t gray = getGrayScale(rgb, bt2100);
    mu_assert_int_eq(67, gray);
    
    free(rgb);
}

MU_TEST_SUITE(grayscale_suite) {
    MU_RUN_TEST(lightness);
    MU_RUN_TEST(luminosity);
    MU_RUN_TEST(average);
    MU_RUN_TEST(bt_709);
    MU_RUN_TEST(bt_2100);    
}

int wrapGrayScaleTest() {
    MU_RUN_SUITE(grayscale_suite);
    MU_REPORT();
    printf("End of Grayscale test \n");
    
    return minunit_fail;
}
