//
//  yuv_test.c
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "errors.h"
#include "yuv.h"

MU_TEST(yuv_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Yuv *yuv = getYuvFromRgb(rgb);
    
    mu_assert_double_eq(0.124, roundup(yuv->y, 1000));
    mu_assert_double_eq(0.122, roundup(yuv->u, 1000));
    mu_assert_double_eq(0.063, roundup(yuv->v, 1000));
    
    free(yuv);
    free(rgb);
}

MU_TEST(yuv_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Yuv *yuv = getYuvFromRgb(rgb);
    
    mu_assert_double_eq(1.0, yuv->y);
    mu_assert_double_eq(0.0, yuv->u);
    mu_assert_double_eq(0.0, yuv->v);
    
    free(yuv);
    free(rgb);
}

MU_TEST(yuv_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Yuv *yuv = getYuvFromRgb(rgb);
    
    mu_assert_double_eq(0.0, yuv->y);
    mu_assert_double_eq(0.0, yuv->u);
    mu_assert_double_eq(0.0, yuv->v);
    
    free(yuv);
    free(rgb);
}

MU_TEST(yuv_empty_params) {
    Yuv *yuv = getYuvFromRgb(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, yuv->error);
    
    free(yuv);
}

MU_TEST(rgb_creation) {
    Yuv *yuv = malloc(sizeof(Yuv));
    yuv->y = 0.124;
    yuv->u = 0.122;
    yuv->v = 0.063;
    
    Rgb *rgb = getRgbFromYuv(yuv);
    
    mu_assert_int_eq(50, rgb->r);
    mu_assert_int_eq(10, rgb->g);
    mu_assert_int_eq(95, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_bright_creation) {
    Yuv *yuv = malloc(sizeof(Yuv));
    yuv->y = 1.0;
    yuv->u = 0.0;
    yuv->v = 0.0;
    
    Rgb *rgb = getRgbFromYuv(yuv);
    mu_assert_int_eq(255, rgb->r);
    mu_assert_int_eq(255, rgb->g);
    mu_assert_int_eq(255, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_dark_creation) {
    Yuv *yuv = malloc(sizeof(Yuv));
    yuv->y = 0.0;
    yuv->u = 0.0;
    yuv->v = 0.0;
    
    Rgb *rgb = getRgbFromYuv(yuv);
    mu_assert_int_eq(0, rgb->r);
    mu_assert_int_eq(0, rgb->g);
    mu_assert_int_eq(0, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_empty_params) {
    Rgb *rgb = getRgbFromYuv(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, rgb->error);
    
    free(rgb);
}

MU_TEST_SUITE(yuv_suite) {
    // Rgb -> Yuv
    MU_RUN_TEST(yuv_creation);
    MU_RUN_TEST(yuv_bright_creation);
    MU_RUN_TEST(yuv_dark_creation);
    MU_RUN_TEST(yuv_empty_params);
    
    // Yuv -> Rgb
    MU_RUN_TEST(rgb_creation);
    MU_RUN_TEST(rgb_bright_creation);
    MU_RUN_TEST(rgb_dark_creation);
    MU_RUN_TEST(rgb_empty_params);
}

void wrapYuvTest() {
    MU_RUN_SUITE(yuv_suite);
    MU_REPORT();
    printf("End of YUV test \n");
}
