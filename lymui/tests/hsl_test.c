//
//  hsl_test.c
//  lymui
//
//  Created by Marc on 22/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "errors.h"
#include "hsl.h"

MU_TEST(hsl_creation) {
    uint8_t cvalue[3] = {5, 10, 95};
    Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    Hsl *hsl = getHslFromRgb(rgb);
    
    mu_assert_double_eq(237.0, roundup(hsl->h, 10));
    mu_assert_double_eq(90.0, roundup(hsl->s, 10));
    mu_assert_double_eq(19.6, roundup(hsl->l, 10));

    free(hsl);
    free(rgb);
}

MU_TEST(hsl_high_saturation_creation) {
    uint8_t cvalue[3] = {100, 150, 255};
    Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    Hsl *hsl = getHslFromRgb(rgb);
    
    mu_assert_double_eq(221.0, roundup(hsl->h, 10));
    mu_assert_double_eq(100.0, roundup(hsl->s, 10));
    mu_assert_double_eq(69.6, roundup(hsl->l, 10));
    
    free(hsl);
    free(rgb);
}

MU_TEST(hsl_low_saturation_creation) {
    uint8_t cvalue[3] = {5, 1, 9};
    Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    Hsl *hsl = getHslFromRgb(rgb);
    
    mu_assert_double_eq(270.0, roundup(hsl->h, 10));
    mu_assert_double_eq(80.0, roundup(hsl->s, 10));
    mu_assert_double_eq(2.0, roundup(hsl->l, 10));
    
    free(hsl);
    free(rgb);
}

MU_TEST(hsl_dark_creation) {
    uint8_t cvalue[3] = {0, 0, 0};
    Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    Hsl *hsl = getHslFromRgb(rgb);
    
    mu_assert_double_eq(0.0, roundup(hsl->h, 10));
    mu_assert_double_eq(0.0, roundup(hsl->s, 10));
    mu_assert_double_eq(0.0, roundup(hsl->l, 10));
    
    free(hsl);
    free(rgb);
}

MU_TEST(hsl_bright_creation) {
    uint8_t cvalue[3] = {255, 255, 255};
    Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    Hsl *hsl = getHslFromRgb(rgb);
    
    mu_assert_double_eq(0.0, roundup(hsl->h, 10));
    mu_assert_double_eq(0.0, roundup(hsl->s, 10));
    mu_assert_double_eq(100.0, roundup(hsl->l, 10));
    
    free(hsl);
    free(rgb);
}

MU_TEST(hsl_empty_params) {
    Hsl *hsl = getHslFromRgb(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, hsl->error);
    
    free(hsl);
}

MU_TEST(rgb_creation) {
    Hsl *hsl = malloc(sizeof(Hsl));
    hsl->h = 0.0;
    hsl->s = 0.0;
    hsl->l = 59.0;
    
    Rgb *rgb = getRgbFromHsl(hsl);
    
    mu_assert_int_eq(150, rgb->r);
    mu_assert_int_eq(150, rgb->g);
    mu_assert_int_eq(150, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_other_creation) {
    Hsl *hsl = malloc(sizeof(Hsl));
    hsl->h = 193.0;
    hsl->s = 67.0;
    hsl->l = 28.0;
    
    Rgb *rgb = getRgbFromHsl(hsl);
    
    mu_assert_int_eq(24, rgb->r);
    mu_assert_int_eq(98, rgb->g);
    mu_assert_int_eq(119, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_another_creation) {
    Hsl *hsl = malloc(sizeof(Hsl));
    hsl->h = 5.0;
    hsl->s = 10.0;
    hsl->l = 98.0;
    
    Rgb *rgb = getRgbFromHsl(hsl);
    
    mu_assert_int_eq(250, rgb->r);
    mu_assert_int_eq(249, rgb->g);
    mu_assert_int_eq(249, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_dark_creation) {
    Hsl *hsl = malloc(sizeof(Hsl));
    hsl->h = 0.0;
    hsl->s = 0.0;
    hsl->l = 0.0;
    
    Rgb *rgb = getRgbFromHsl(hsl);
    
    mu_assert_int_eq(0, rgb->r);
    mu_assert_int_eq(0, rgb->g);
    mu_assert_int_eq(0, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_bright_creation) {
    Hsl *hsl = malloc(sizeof(Hsl));
    hsl->h = 0.0;
    hsl->s = 0.0;
    hsl->l = 100.0;
    
    Rgb *rgb = getRgbFromHsl(hsl);
    
    mu_assert_int_eq(255, rgb->r);
    mu_assert_int_eq(255, rgb->g);
    mu_assert_int_eq(255, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_empty_params) {
    Rgb *rgb = getRgbFromHsl(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, rgb->error);
    
    free(rgb);
}

MU_TEST_SUITE(hsl_suite) {
    // Rgb -> Hsl
    MU_RUN_TEST(hsl_creation);
    MU_RUN_TEST(hsl_high_saturation_creation);
    MU_RUN_TEST(hsl_low_saturation_creation);
    MU_RUN_TEST(hsl_dark_creation);
    MU_RUN_TEST(hsl_bright_creation);
    MU_RUN_TEST(hsl_empty_params);
    
    // Hsl -> Rgb
    MU_RUN_TEST(rgb_creation);
    MU_RUN_TEST(rgb_other_creation);
    MU_RUN_TEST(rgb_another_creation);
    MU_RUN_TEST(rgb_dark_creation);
    MU_RUN_TEST(rgb_bright_creation);
    MU_RUN_TEST(rgb_empty_params);
}

int wrapHslTest() {
    MU_RUN_SUITE(hsl_suite);
    MU_REPORT();
    printf("End of HSL test \n");
    
    return minunit_fail;
}
