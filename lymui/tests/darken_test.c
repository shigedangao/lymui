//
//  darken_test.c
//  lymui
//
//  Created by Marc Intha on 18/03/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "darken.h"
#include "rgb.h"

MU_TEST(darken) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 100;
    rgb->g = 150;
    rgb->b = 255;
    
    Hsl **hsl = getDarkerShade(rgb);
    
    mu_assert_double_eq(221.0, hsl[0]->h);
    mu_assert_double_eq(100.0, hsl[0]->s);
    mu_assert_double_eq(62.65, roundup(hsl[0]->l, 100));
    mu_assert_double_eq(55.69, roundup(hsl[1]->l, 100));
    mu_assert_double_eq(48.73, roundup(hsl[2]->l, 100));
    mu_assert_double_eq(41.76, roundup(hsl[3]->l, 100));
    mu_assert_double_eq(34.8,  roundup(hsl[4]->l, 100));
    mu_assert_double_eq(27.84, roundup(hsl[5]->l, 100));
    mu_assert_double_eq(20.88, roundup(hsl[6]->l, 100));
    mu_assert_double_eq(13.92, roundup(hsl[7]->l, 100));
    mu_assert_double_eq(6.96,  roundup(hsl[8]->l, 100));
    mu_assert_double_eq(0.0, hsl[9]->l);
    
    free(hsl);
}

MU_TEST(darken_bright_test) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Hsl **hsl = getDarkerShade(rgb);

    mu_assert_double_eq(0.0, hsl[0]->h);
    mu_assert_double_eq(0.0, hsl[0]->s);
    mu_assert_double_eq(90.0, hsl[0]->l);
    mu_assert_double_eq(80.0, hsl[1]->l);
    mu_assert_double_eq(70.0, hsl[2]->l);
    mu_assert_double_eq(60.0, hsl[3]->l);
    mu_assert_double_eq(50.0, hsl[4]->l);
    mu_assert_double_eq(40.0, hsl[5]->l);
    mu_assert_double_eq(30.0, hsl[6]->l);
    mu_assert_double_eq(20.0, hsl[7]->l);
    mu_assert_double_eq(10.0, hsl[8]->l);
    mu_assert_double_eq(0.0, hsl[9]->l);

    free(hsl);
}


MU_TEST(darken_dark_test) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Hsl **hsl = getDarkerShade(rgb);
    
    mu_assert_double_eq(0.0, hsl[0]->h);
    mu_assert_double_eq(0.0, hsl[0]->s);
    mu_assert_double_eq(0.0, hsl[0]->l);
    mu_assert_double_eq(0.0, hsl[1]->l);
    mu_assert_double_eq(0.0, hsl[2]->l);
    mu_assert_double_eq(0.0, hsl[3]->l);
    mu_assert_double_eq(0.0, hsl[4]->l);
    mu_assert_double_eq(0.0, hsl[5]->l);
    mu_assert_double_eq(0.0, hsl[6]->l);
    mu_assert_double_eq(0.0, hsl[7]->l);
    mu_assert_double_eq(0.0, hsl[8]->l);
    mu_assert_double_eq(0.0, hsl[9]->l);
    
    free(hsl);
}

MU_TEST(darken_empty_param) {
    Hsl **hsl = getDarkerShade(NULL);
    
    mu_assert(hsl == NULL, "Expect HSL Darken to be equal to NULL");
}

MU_TEST_SUITE(darken_suite) {
    MU_RUN_TEST(darken);
    MU_RUN_TEST(darken_bright_test);
    MU_RUN_TEST(darken_dark_test);
    MU_RUN_TEST(darken_empty_param);
}

int wrapDarkenTest() {
    MU_RUN_SUITE(darken_suite);
    MU_REPORT();
    printf("End of Darken test \n");
    
    return minunit_fail;
}
