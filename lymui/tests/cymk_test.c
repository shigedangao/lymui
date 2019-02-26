//
//  cymk_test.c
//  lymui
//
//  Created by Marc on 15/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <minunit.h>
#include "test_header.h"
#include "errors.h"
#include "rgb.h"
#include "cymk.h"

MU_TEST(cymk_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 55;
    rgb->b = 102;
    
    Cymk *cymk = getCymkFromRgb(rgb);

    mu_assert_double_eq(0.0, cymk->c);
    mu_assert_double_eq(0.6, roundup(cymk->y, 100));
    mu_assert_double_eq(0.78, roundup(cymk->m, 100));
    mu_assert_double_eq(0.0, cymk->k);
    
    free(rgb);
    free(cymk);
}

MU_TEST(cymk_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Cymk *cymk = getCymkFromRgb(rgb);
    
    mu_assert_double_eq(0.0, cymk->c);
    mu_assert_double_eq(0.0, cymk->y);
    mu_assert_double_eq(0.0, cymk->m);
    mu_assert_double_eq(1.0, cymk->k);
    
    free(rgb);
    free(cymk);
}

MU_TEST(cymk_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Cymk *cymk = getCymkFromRgb(rgb);
    
    mu_assert_double_eq(0.0, cymk->c);
    mu_assert_double_eq(0.0, cymk->y);
    mu_assert_double_eq(0.0, cymk->m);
    mu_assert_double_eq(0.0, cymk->k);
    
    free(rgb);
    free(cymk);
}

MU_TEST(cymk_empty_param) {
    Cymk *cymk = getCymkFromRgb(NULL);
    
    mu_assert_string_eq("The imput param is empty", cymk->error);
    free(cymk);
}

MU_TEST(rgb_automn_creation) {
    Cymk *cymk = malloc(sizeof(Cymk));
    cymk->c = 0.973;
    cymk->y = 0.0;
    cymk->m = 0.949;
    cymk->k = 0.223;
    
    Rgb *rgb = getRgbFromCymk(cymk);
    
    mu_assert_int_eq(5, rgb->r);
    mu_assert_int_eq(10, rgb->g);
    mu_assert_int_eq(198, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 55;
    rgb->b = 102;
    
    Cymk *cymk = getCymkFromRgb(rgb);
    Rgb *nrgb = getRgbFromCymk(cymk);
    
    mu_assert_int_eq(rgb->r, nrgb->r);
    mu_assert_int_eq(rgb->g, nrgb->g);
    mu_assert_int_eq(rgb->b, nrgb->b);
    
    free(rgb);
    free(nrgb);
}

MU_TEST(rgb_dark_creation) {
    Cymk *cymk = malloc(sizeof(Cymk));
    cymk->c = 0.0f;
    cymk->y = 0.0f;
    cymk->m = 0.0f;
    cymk->k = 1.0f;
    
    Rgb *rgb = getRgbFromCymk(cymk);
    
    mu_assert_int_eq(0, rgb->r);
    mu_assert_int_eq(0, rgb->g);
    mu_assert_int_eq(0, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_bright_creation) {
    Cymk *cymk = malloc(sizeof(Cymk));
    cymk->c = 0.0f;
    cymk->y = 0.0f;
    cymk->m = 0.0f;
    cymk->k = 0.0f;
    
    Rgb *rgb = getRgbFromCymk(cymk);
    
    mu_assert_int_eq(255, rgb->r);
    mu_assert_int_eq(255, rgb->g);
    mu_assert_int_eq(255, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_empty_param) {
    Rgb *rgb = getRgbFromCymk(NULL);
    
    mu_assert_string_eq("The imput param is empty", rgb->error);
    free(rgb);
}

MU_TEST_SUITE(cymk_suite) {
    // Rgb -> Cymk
    MU_RUN_TEST(cymk_creation);
    MU_RUN_TEST(cymk_dark_creation);
    MU_RUN_TEST(cymk_bright_creation);
    MU_RUN_TEST(cymk_empty_param);
    
    // Cymk -> Rgb
    MU_RUN_TEST(rgb_creation);
    MU_RUN_TEST(rgb_automn_creation);
    MU_RUN_TEST(rgb_dark_creation);
    MU_RUN_TEST(rgb_bright_creation);
    MU_RUN_TEST(rgb_empty_param);
}

void wrapCymkTest() {
    MU_RUN_SUITE(cymk_suite);
    MU_REPORT();
    printf("End of CYMK test \n");
}
