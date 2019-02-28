//
//  hex_test.c
//  lymui
//
//  Created by Marc on 14/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <minunit.h>
#include "test_header.h"
#include "errors.h"
#include "hex.h"
#include "rgb.h"

MU_TEST(hex_creation) {
    uint8_t uc[] = {5, 10, 95};
    Rgb *rgb = makeRGB(uc, sizeof(uc));
    
    char *hex = getHexFromRGB(rgb);
    mu_assert_string_eq("050a5f", hex);
    
    free(rgb);
    free(hex);
}

MU_TEST(hex_white_creation) {
    uint8_t uc[] = {255, 255, 255};
    Rgb *rgb = makeRGB(uc, sizeof(uc));
    
    char *hex = getHexFromRGB(rgb);
    mu_assert_string_eq("ffffff", hex);
    
    free(rgb);
    free(hex);
}

MU_TEST(hex_empty_params) {
    char *hex = getHexFromRGB(NULL);
    
    mu_assert(hex == NULL, "Expect Hex to be NULL when nothing is passed");
}

MU_TEST(rgb_white_hex_shorthand) {
    char *hex = {"fff"};
    Rgb *rgb = getRGBFromHex(hex);
    
    mu_assert_int_eq(255, rgb->r);
    mu_assert_int_eq(255, rgb->g);
    mu_assert_int_eq(255, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_composite_hex_shorthand) {
    char *hex = {"6f3"};
    Rgb *rgb = getRGBFromHex(hex);
    
    mu_assert_int_eq(102, rgb->r);
    mu_assert_int_eq(255, rgb->g);
    mu_assert_int_eq(51, rgb->b);

    free(rgb);
}

MU_TEST(rgb_creation) {
    char *hex = malloc(sizeof(char) * 6);
    strcpy(hex, "050a5f");
    
    Rgb *rgb = getRGBFromHex(hex);
    mu_assert_int_eq(5, rgb->r);
    mu_assert_int_eq(10, rgb->g);
    mu_assert_int_eq(95, rgb->b);
    
    free(rgb);
    free(hex);
}

MU_TEST(rgb_bright_creation) {
    char *hex = {"abcdef"};
    Rgb *rgb = getRGBFromHex(hex);
    
    mu_assert_int_eq(171, rgb->r);
    mu_assert_int_eq(205, rgb->g);
    mu_assert_int_eq(239, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_october_creation) {
    char *hex = {"050a62"};
    Rgb *rgb = getRGBFromHex(hex);
    
    mu_assert_int_eq(5, rgb->r);
    mu_assert_int_eq(10, rgb->g);
    mu_assert_int_eq(98, rgb->b);
    
    free(rgb);
}

MU_TEST(rgb_empty_params) {
    Rgb *rgb = getRGBFromHex(NULL);
    
    mu_assert_string_eq("The imput param is empty", rgb->error);
    free(rgb);
}

MU_TEST_SUITE(hex_suite) {
    // Rgb -> Hex
    MU_RUN_TEST(hex_creation);
    MU_RUN_TEST(hex_white_creation);
    MU_RUN_TEST(hex_empty_params);
    
    // Hex -> Rgb
    MU_RUN_TEST(rgb_white_hex_shorthand);
    MU_RUN_TEST(rgb_composite_hex_shorthand);
    MU_RUN_TEST(rgb_creation);
    MU_RUN_TEST(rgb_bright_creation);
    MU_RUN_TEST(rgb_october_creation);
    MU_RUN_TEST(rgb_empty_params);
}

int wrapHexTest() {
    MU_RUN_SUITE(hex_suite);
    MU_REPORT();
    printf("End of Hex test \n");
    
    return minunit_fail;
}



