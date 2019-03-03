//
//  test_ycbcr.c
//  lymui
//
//  Created by Marc on 14/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "errors.h"
#include "ycbcr.h"
#include "rgb.h"

MU_TEST(ycbcr_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 100;
    rgb->b = 200;
    
    Ycbcr *ycbcr = getYcbcrFromRgb(rgb);
    
    mu_assert_int_eq(86, ycbcr->y);
    mu_assert_int_eq(187, ycbcr->cb);
    mu_assert_int_eq(77, ycbcr->cr);

    free(rgb);
    free(ycbcr);
}

MU_TEST(ycbcr_empty_param) {
    Ycbcr *ycbcr = getYcbcrFromRgb(NULL);
    mu_assert_string_eq("The imput param is empty", ycbcr->error);
    
    free(ycbcr);
}

MU_TEST(rgb_creation) {
    Ycbcr *ycbcr = malloc(sizeof(Ycbcr));
    
    ycbcr->y  = 86;
    ycbcr->cb = 186;
    ycbcr->cr = 77;
    
    Rgb *rgb = getRgbFromYcbcr(ycbcr);
    
    mu_assert_int_eq(0, rgb->r);
    mu_assert_int_eq(100, rgb->g);
    mu_assert_int_eq(199, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_empty_param) {
    Rgb *rgb = getRgbFromYcbcr(NULL);
    mu_assert_string_eq("The imput param is empty", rgb->error);
    
    free(rgb);
}

MU_TEST_SUITE(ycbcr_suite) {
    // Rgb -> ycbcr
    MU_RUN_TEST(ycbcr_creation);
    MU_RUN_TEST(ycbcr_empty_param);
    
    // Ycbcr -> rgb
    MU_RUN_TEST(rgb_creation);
    MU_RUN_SUITE(rgb_empty_param);
}

int wrapYcbcrTest() {
    MU_RUN_SUITE(ycbcr_suite);
    MU_REPORT();
    printf("End of Ycbcr test \n");
    
    return minunit_fail;
}
