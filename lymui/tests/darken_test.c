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
#include "darken.h"
#include "rgb.h"

MU_TEST(darken_test) {
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

MU_TEST_SUITE(darken_suite) {
    MU_RUN_TEST(darken_test);
}

int wrapDarkenTest() {
    MU_RUN_SUITE(darken_suite);
    MU_REPORT();
    printf("End of Darken test \n");
    
    return minunit_fail;
}
