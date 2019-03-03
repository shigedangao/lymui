//
//  tsl_test.c
//  lymui
//
//  Created by Marc Intha on 05/01/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "tsl.h"
#include "errors.h"

MU_TEST(tsl_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 128;
    
    Tsl *tsl = getTslFromRgb(rgb);
    
    mu_assert_double_eq(0.788, roundup(tsl->t, 1000));
    mu_assert_double_eq(0.387, roundup(tsl->s, 1000));
    mu_assert_double_eq(35.412, roundup(tsl->l, 1000));

    free(rgb);
    free(tsl);
}

MU_TEST(tsl_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Tsl *tsl = getTslFromRgb(rgb);
    
    mu_assert_double_eq(0.0, roundup(tsl->t, 1000));
    mu_assert_double_eq(0.0, roundup(tsl->s, 1000));
    mu_assert_double_eq(255.0, roundup(tsl->l, 1000));
    
    free(rgb);
    free(tsl);
}

MU_TEST(tsl_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Tsl *tsl = getTslFromRgb(rgb);
    
    mu_assert_double_eq(0.0, roundup(tsl->t, 1000));
    mu_assert_double_eq(0.0, roundup(tsl->s, 1000));
    mu_assert_double_eq(0.0, roundup(tsl->l, 1000));
    
    free(rgb);
    free(tsl);
}

MU_TEST(tsl_empty_params) {
    Tsl *tsl = getTslFromRgb(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, tsl->error);
    
    free(tsl);
}

MU_TEST(rgb_test) {
    Tsl *tsl = malloc(sizeof(Tsl));
    tsl->t = 0.787;
    tsl->s = 0.386;
    tsl->l = 35.412;
    
    Rgb *rgb = getRgbFromTsl(tsl);
    
    mu_assert_int_eq(50, rgb->r);
    mu_assert_int_eq(10, rgb->g);
    mu_assert_int_eq(128, rgb->b);

    free(rgb);
}

MU_TEST(rgb_bright_test) {
    Tsl *tsl = malloc(sizeof(Tsl));
    tsl->t = 0.0;
    tsl->s = 0.0;
    tsl->l = 255.0;
    
    Rgb *rgb = getRgbFromTsl(tsl);
    
    mu_assert_int_eq(255, rgb->r);
    mu_assert_int_eq(255, rgb->g);
    mu_assert_int_eq(255, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_dark_test) {
    Tsl *tsl = malloc(sizeof(Tsl));
    tsl->t = 0.0;
    tsl->s = 0.0;
    tsl->l = 0.0;
    
    Rgb *rgb = getRgbFromTsl(tsl);
    
    mu_assert_int_eq(0, rgb->r);
    mu_assert_int_eq(0, rgb->g);
    mu_assert_int_eq(0, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_empty_params) {
    Rgb *rgb = getRgbFromTsl(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, rgb->error);
    
    free(rgb);
}

MU_TEST_SUITE(tsl_suite) {
    // Rgb -> Tsl
    MU_RUN_TEST(tsl_creation);
    MU_RUN_TEST(tsl_bright_creation);
    MU_RUN_TEST(tsl_dark_creation);
    MU_RUN_TEST(tsl_empty_params);
    
    // Tsl -> Rgb
    MU_RUN_TEST(rgb_test);
    MU_RUN_TEST(rgb_bright_test);
    MU_RUN_TEST(rgb_dark_test);
    MU_RUN_TEST(rgb_empty_params);
}

int wrapTslTest() {
    MU_RUN_TEST(tsl_suite);
    MU_REPORT();
    printf("End of Tsl test \n");
    
    return minunit_fail;
}
