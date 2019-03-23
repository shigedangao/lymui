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
#include "shade.h"
#include "rgb.h"

MU_TEST(darken) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 100;
    rgb->g = 150;
    rgb->b = 255;
    
    Shade *shade = getShade(rgb);
    
    mu_assert_double_eq(221.0, shade->shade[0]->h);
    mu_assert_double_eq(100.0, shade->shade[0]->s);
    mu_assert_double_eq(69.61, roundup(shade->shade[0]->l, 100));
    mu_assert_double_eq(62.65, roundup(shade->shade[1]->l, 100));
    mu_assert_double_eq(55.69, roundup(shade->shade[2]->l, 100));
    mu_assert_double_eq(48.73, roundup(shade->shade[3]->l, 100));
    mu_assert_double_eq(41.76, roundup(shade->shade[4]->l, 100));
    mu_assert_double_eq(34.8,  roundup(shade->shade[5]->l, 100));
    mu_assert_double_eq(27.84, roundup(shade->shade[6]->l, 100));
    mu_assert_double_eq(20.88, roundup(shade->shade[7]->l, 100));
    mu_assert_double_eq(13.92, roundup(shade->shade[8]->l, 100));
    mu_assert_double_eq(6.96,  roundup(shade->shade[9]->l, 100));
    
    releaseShade(shade);
    free(rgb);
}

MU_TEST(darken_bright_test) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Shade *shade = getShade(rgb);

    mu_assert_double_eq(0.0, shade->shade[0]->h);
    mu_assert_double_eq(0.0, shade->shade[0]->s);
    mu_assert_double_eq(100.0, shade->shade[0]->l);
    mu_assert_double_eq(90.0, shade->shade[1]->l);
    mu_assert_double_eq(80.0, shade->shade[2]->l);
    mu_assert_double_eq(70.0, shade->shade[3]->l);
    mu_assert_double_eq(60.0, shade->shade[4]->l);
    mu_assert_double_eq(50.0, shade->shade[5]->l);
    mu_assert_double_eq(40.0, shade->shade[6]->l);
    mu_assert_double_eq(30.0, shade->shade[7]->l);
    mu_assert_double_eq(20.0, shade->shade[8]->l);
    mu_assert_double_eq(10.0, shade->shade[9]->l);

    releaseShade(shade);
    free(rgb);
}


MU_TEST(darken_dark_test) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Shade *shade = getShade(rgb);
    
    mu_assert_double_eq(0.0, shade->shade[0]->h);
    mu_assert_double_eq(0.0, shade->shade[0]->s);
    mu_assert_double_eq(0.0, shade->shade[0]->l);
    mu_assert_double_eq(0.0, shade->shade[1]->l);
    mu_assert_double_eq(0.0, shade->shade[2]->l);
    mu_assert_double_eq(0.0, shade->shade[3]->l);
    mu_assert_double_eq(0.0, shade->shade[4]->l);
    mu_assert_double_eq(0.0, shade->shade[5]->l);
    mu_assert_double_eq(0.0, shade->shade[6]->l);
    mu_assert_double_eq(0.0, shade->shade[7]->l);
    mu_assert_double_eq(0.0, shade->shade[8]->l);
    mu_assert_double_eq(0.0, shade->shade[9]->l);
    
    releaseShade(shade);
    free(rgb);
}

MU_TEST(darken_empty_param) {
    Shade *shade = getShade(NULL);
    
    mu_assert_string_eq("The imput param is empty", shade->error);
    free(shade);
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
