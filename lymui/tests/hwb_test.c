//
//  hwb_test.c
//  lymui
//
//  Created by Marc Intha on 26/12/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <cunit.h>
#include <minunit.h>
#include "test_header.h"
#include "hwb.h"
#include "errors.h"

MU_TEST(hwb_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 17;
    rgb->g = 12;
    rgb->b = 93;
    
    Hwb *hwb = getHwbFromRgb(rgb);
    
    mu_assert_double_eq(244.0, roundup(hwb->h, 10));
    mu_assert_double_eq(4.7, roundup(hwb->w, 10));
    mu_assert_double_eq(63.53, roundup(hwb->b, 100));

    free(rgb);
    free(hwb);
}

MU_TEST(hwb_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Hwb *hwb = getHwbFromRgb(rgb);
    
    mu_assert_double_eq(0.0, roundup(hwb->h, 10));
    mu_assert_double_eq(100.0, roundup(hwb->w, 10));
    mu_assert_double_eq(0.0, roundup(hwb->b, 100));
    
    free(rgb);
    free(hwb);
}

MU_TEST(hwb_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Hwb *hwb = getHwbFromRgb(rgb);
    
    mu_assert_double_eq(0.0, roundup(hwb->h, 10));
    mu_assert_double_eq(0.0, roundup(hwb->w, 10));
    mu_assert_double_eq(100.0, roundup(hwb->b, 100));
    
    free(rgb);
    free(hwb);
}

MU_TEST(hwb_empty_params) {
    Hwb *hwb = getHwbFromRgb(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, hwb->error);
    
    free(hwb);
}

MU_TEST(rgb_creation) {
    Hwb *hwb = malloc(sizeof(Hwb));
    hwb->h = 244.0;
    hwb->w = 4.705;
    hwb->b = 63.52;
    
    Rgb *rgb = getRgbFromHwb(hwb);
    
    mu_assert_int_eq(17, rgb->r);
    mu_assert_int_eq(12, rgb->g);
    mu_assert_int_eq(93, rgb->b);

    free(rgb);
}

MU_TEST(rgb_bright_creation) {
    Hwb *hwb = malloc(sizeof(Hwb));
    hwb->h = 0.0;
    hwb->w = 100.0;
    hwb->b = 0.0;
    
    Rgb *rgb = getRgbFromHwb(hwb);
    
    mu_assert_int_eq(255, rgb->r);
    mu_assert_int_eq(255, rgb->g);
    mu_assert_int_eq(255, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_dark_creation) {
    Hwb *hwb = malloc(sizeof(Hwb));
    hwb->h = 0.0;
    hwb->w = 0.0;
    hwb->b = 100.0;
    
    Rgb *rgb = getRgbFromHwb(hwb);
    
    mu_assert_int_eq(0, rgb->r);
    mu_assert_int_eq(0, rgb->g);
    mu_assert_int_eq(0, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_empty_params) {
    Rgb *rgb = getRgbFromHwb(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, rgb->error);
    
    free(rgb);
}

MU_TEST_SUITE(hwb_suite) {
    // Rgb -> Hwb
    MU_RUN_TEST(hwb_creation);
    MU_RUN_TEST(hwb_bright_creation);
    MU_RUN_TEST(hwb_dark_creation);
    MU_RUN_TEST(hwb_empty_params);
    
    // Hwb -> Rgb
    MU_RUN_TEST(rgb_creation);
    MU_RUN_TEST(rgb_bright_creation);
    MU_RUN_TEST(rgb_dark_creation);
    MU_RUN_TEST(rgb_empty_params);
}

void wrapHwbTest() {
    MU_RUN_SUITE(hwb_suite);
    MU_REPORT();
    printf("End of HWB test \n");
}
