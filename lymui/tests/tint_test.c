//
//  tint_test.c
//  lymui
//
//  Created by Marc Intha on 22/03/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "tint.h"

MU_TEST(tint) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 100;
    rgb->g = 150;
    rgb->b = 255;
    
    Tint *tint = getTint(rgb);
    
    mu_assert_double_eq(221.0, tint->tint[0]->h);
    mu_assert_double_eq(100.0, tint->tint[0]->s);
    mu_assert_double_eq(69.61, roundup(tint->tint[0]->l, 100));
    mu_assert_double_eq(76.57, roundup(tint->tint[1]->l, 100));
    mu_assert_double_eq(83.53, roundup(tint->tint[2]->l, 100));
    mu_assert_double_eq(90.49, roundup(tint->tint[3]->l, 100));
    mu_assert_double_eq(97.45, roundup(tint->tint[4]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[5]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[6]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[7]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[8]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[9]->l, 100));
    
    releaseTint(tint);
    free(rgb);
}

MU_TEST(tint_dark) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Tint *tint = getTint(rgb);
    
    mu_assert_double_eq(0.0, tint->tint[0]->h);
    mu_assert_double_eq(0.0, tint->tint[0]->s);
    mu_assert_double_eq(0.0, roundup(tint->tint[0]->l, 100));
    mu_assert_double_eq(10.0, roundup(tint->tint[1]->l, 100));
    mu_assert_double_eq(20.0, roundup(tint->tint[2]->l, 100));
    mu_assert_double_eq(30.0, roundup(tint->tint[3]->l, 100));
    mu_assert_double_eq(40.0, roundup(tint->tint[4]->l, 100));
    mu_assert_double_eq(50.0, roundup(tint->tint[5]->l, 100));
    mu_assert_double_eq(60.0, roundup(tint->tint[6]->l, 100));
    mu_assert_double_eq(70.0, roundup(tint->tint[7]->l, 100));
    mu_assert_double_eq(80.0, roundup(tint->tint[8]->l, 100));
    mu_assert_double_eq(90.0, roundup(tint->tint[9]->l, 100));
    
    releaseTint(tint);
    free(rgb);
}

MU_TEST(tint_bright) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Tint *tint = getTint(rgb);
    
    mu_assert_double_eq(0.0, tint->tint[0]->h);
    mu_assert_double_eq(0.0, tint->tint[0]->s);
    mu_assert_double_eq(100.0, roundup(tint->tint[0]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[1]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[2]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[3]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[4]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[5]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[6]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[7]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[8]->l, 100));
    mu_assert_double_eq(100.0, roundup(tint->tint[9]->l, 100));
    
    releaseTint(tint);
    free(rgb);
}

MU_TEST(empty_tint) {
    Tint *tint = getTint(NULL);
    
    mu_assert_string_eq("The imput param is empty", tint->error);
    free(tint);
}

MU_TEST(empty_free_tint) {
    uint8_t value = releaseTint(NULL);
    
    mu_assert_int_eq(value, 0);
}

MU_TEST(empty_tint_array) {
    Tint *tint = malloc(sizeof(Tint));
    tint->tint = NULL;
    uint8_t value = releaseTint(tint);
    
    mu_assert_int_eq(value, 1);
}

MU_TEST_SUITE(tint_suite) {
    MU_RUN_TEST(tint);
    MU_RUN_TEST(tint_dark);
    MU_RUN_TEST(tint_bright);
    MU_RUN_TEST(empty_tint);
    
    // release memory
    MU_RUN_TEST(empty_free_tint);
    MU_RUN_TEST(empty_tint_array);
}

int wrapTintTest() {
    MU_RUN_SUITE(tint_suite);
    MU_REPORT();
    printf("End of Tint test \n");
    
    return minunit_fail;
}
