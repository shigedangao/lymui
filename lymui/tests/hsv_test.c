//
//  hsv_test.c
//  lymui
//
//  Created by Marc on 05/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "errors.h"
#include "rgb.h"
#include "hsv.h"

MU_TEST(hsv_creation) {
    Rgb *rgb = malloc(sizeof( Rgb));
    rgb->r = 50;
    rgb->g = 100;
    rgb->b = 100;
    
    Hsv *hsv = getHsvFromRgb(rgb);
    
    mu_assert_double_eq(180.0, hsv->h);
    mu_assert_double_eq(50.0, hsv->s);
    mu_assert_double_eq(39.216, roundup(hsv->v, 1000));

    free(rgb);
    free(hsv);
}

MU_TEST(hsv_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Hsv *hsv = getHsvFromRgb(rgb);
    
    mu_assert_double_eq(0.0, hsv->h);
    mu_assert_double_eq(0.0, hsv->s);
    mu_assert_double_eq(0.0, hsv->v);
    
    free(rgb);
    free(hsv);
}

MU_TEST(hsv_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Hsv *hsv = getHsvFromRgb(rgb);
    
    mu_assert_double_eq(0.0, hsv->h);
    mu_assert_double_eq(0.0, hsv->s);
    mu_assert_double_eq(100.0, hsv->v);
    
    free(rgb);
    free(hsv);
}

MU_TEST(hsv_other_color_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 156;
    rgb->g = 238;
    rgb->b = 1;
    
    Hsv *hsv = getHsvFromRgb(rgb);
    
    mu_assert_double_eq(81.0, roundup(hsv->h, 10));
    mu_assert_double_eq(99.6, roundup(hsv->s, 10));
    mu_assert_double_eq(93.4, roundup(hsv->v, 10));
    
    free(rgb);
    free(hsv);
}

MU_TEST(hsv_empty_param) {
    Hsv *hsv = getHsvFromRgb(NULL);
    mu_assert_string_eq("The imput param is empty", hsv->error);
    
    free(hsv);
}

MU_TEST(rgb_creation) {
    Hsv *hsv = malloc(sizeof(Hsv));
    hsv->h = 180.0;
    hsv->s = 50.0;
    hsv->v = 39.216;
    
    Rgb *rgb = getRgbFromHsv(hsv);
    
    mu_assert_int_eq(50, rgb->r);
    mu_assert_int_eq(100, rgb->g);
    mu_assert_int_eq(100, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_dark_creation) {
    Hsv *hsv = malloc(sizeof(Hsv));
    hsv->h = 0.0;
    hsv->s = 0.0;
    hsv->v = 0.0;
    
    Rgb *rgb = getRgbFromHsv(hsv);
    
    mu_assert_int_eq(0, rgb->r);
    mu_assert_int_eq(0, rgb->g);
    mu_assert_int_eq(0, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_bright_creation) {
    Hsv *hsv = malloc(sizeof(Hsv));
    hsv->h = 0.0;
    hsv->s = 0.0;
    hsv->v = 100.0;
    
    Rgb *rgb = getRgbFromHsv(hsv);
    
    mu_assert_int_eq(255, rgb->r);
    mu_assert_int_eq(255, rgb->g);
    mu_assert_int_eq(255, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_other_color_creation) {
    Hsv *hsv = malloc(sizeof(Hsv));
    hsv->h = 81.0;
    hsv->s = 99.6;
    hsv->v = 93.4;
    
    Rgb *rgb = getRgbFromHsv(hsv);
    
    mu_assert_int_eq(155, rgb->r);
    mu_assert_int_eq(238, rgb->g);
    mu_assert_int_eq(1, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_empty_param) {
    Rgb *rgb = getRgbFromHsv(NULL);
    mu_assert_string_eq("The imput param is empty", rgb->error);
    
    free(rgb);
}

MU_TEST_SUITE(hsv_test) {
    // Rgb -> Hsv
    MU_RUN_TEST(hsv_creation);
    MU_RUN_TEST(hsv_dark_creation);
    MU_RUN_TEST(hsv_bright_creation);
    MU_RUN_TEST(hsv_other_color_creation);
    MU_RUN_TEST(hsv_empty_param);
    
    // Hsv -> Rgb
    MU_RUN_TEST(rgb_creation);
    MU_RUN_TEST(rgb_dark_creation);
    MU_RUN_TEST(rgb_bright_creation);
    MU_RUN_TEST(rgb_other_color_creation);
    MU_RUN_TEST(rgb_empty_param);
}

void wrapHsvTest() {
    MU_RUN_SUITE(hsv_test);
    MU_REPORT();
    printf("End of HSV test \n");
}
