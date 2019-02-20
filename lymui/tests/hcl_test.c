//
//  hcl_test.c
//  lymui
//
//  Created by Marc Intha on 20/02/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "hcl.h"
#include "rgb.h"

MU_TEST(hcl_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 10;
    rgb->g = 10;
    rgb->b = 200;
    
    Hcl *hcl = getHclFromRgb(rgb);
    
    mu_assert(hcl->h == 240.0, "Expect H to be equal to 240");
    mu_assert_double_eq(roundup(hcl->l, 1000), 25.108);
    mu_assert_double_eq(roundup(hcl->c, 1000), 99.145);
    
    free(hcl);
}

MU_TEST(hcl_black_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Hcl *hcl = getHclFromRgb(rgb);
    
    mu_assert(hcl->h == 0.0, "Expect H to be equal to 0");
    mu_assert(hcl->c == 0.0, "Expect C to be equal to 0");
    mu_assert(hcl->l == 0.0, "Expect L to be equal to 0");

    free(rgb);
    free(hcl);
}

MU_TEST(hcl_white_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Hcl *hcl = getHclFromRgb(rgb);
    
    mu_assert_double_eq(hcl->h, 0.0);
    mu_assert_double_eq(roundup(hcl->c, 1000), 0.001);
    mu_assert_double_eq(hcl->l, 100.0);
}

MU_TEST_SUITE(hcl_suite) {
    MU_RUN_TEST(hcl_creation);
    MU_RUN_TEST(hcl_black_creation);
    MU_RUN_TEST(hcl_white_creation);
}

// use minunit_status
void wrapHclTest() {
    MU_RUN_SUITE(hcl_suite);
    MU_REPORT();
}
