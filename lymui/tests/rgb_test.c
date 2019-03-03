//
//  rgb_test.c
//  lymui
//
//  Created by Marc on 14/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "test_header.h"
#include <stdlib.h>
#include <stdint.h>
#include <minunit.h>
#include "errors.h"
#include "rgb.h"

MU_TEST(rgb_creation) {
    uint8_t uc[] = {0, 100, 200};
    Rgb *rgb = makeRGB(uc, sizeof(uc));
    
    mu_assert_int_eq(0, rgb->r);
    mu_assert_int_eq(100, rgb->g);
    mu_assert_int_eq(200, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_error_creation) {
    uint8_t uc[] = {0, 100};
    Rgb *rgb = makeRGB(uc, sizeof(uc));
    
    mu_assert_string_eq(rgb->error, WRONG_INPUT_PARAM);
    free(rgb);
}

MU_TEST(rgb_empty_params) {
    Rgb *rgb = makeRGB(NULL, 0);

    mu_assert_string_eq(rgb->error, NULL_INPUT_PARAM);
    free(rgb);
}

MU_TEST(rgb_from_ptr) {
    uint8_t *uc = malloc(sizeof(uint8_t) * 3);
    uc[0] = 100;
    uc[1] = 152;
    uc[2] = 200;
    
    Rgb *rgb = makeRGB(uc, 3);
    
    mu_assert_int_eq(100, rgb->r);
    mu_assert_int_eq(152, rgb->g);
    mu_assert_int_eq(200, rgb->b);
    
    free(rgb);
}

MU_TEST_SUITE(rgb_suite) {
    MU_RUN_TEST(rgb_creation);
    MU_RUN_TEST(rgb_error_creation);
    MU_RUN_TEST(rgb_empty_params);
    MU_RUN_TEST(rgb_from_ptr);
}

int wrapRgbTest() {
    MU_RUN_SUITE(rgb_suite);
    MU_REPORT();
    printf("End of RGB test \n");
    
    return minunit_fail;
}
