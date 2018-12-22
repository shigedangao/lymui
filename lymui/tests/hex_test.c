//
//  hex_test.c
//  lymui
//
//  Created by Marc on 14/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <cunit.h>
#include <stdlib.h>
#include <string.h>
#include "test_header.h"
#include "errors.h"
#include "hex.h"
#include "rgb.h"

ctest_return_t testHexCreationFromRgb(ctest_t *test, void *arg) {
    uint8_t uc[] = {5, 10, 95};
    Rgb *lym = makeRGB(uc, sizeof(uc));
    
    char *hex = getHexFromRGB(lym);
    char *value = {"050a5f"};
    // As the lib does not support the hex test yet
    CTAssertStringEqual(test, value, hex, "%s is not equal to %s", value, hex);
    
    free(lym);
    free(hex);
}

ctest_return_t testWhiteHexCreationFromRgb(ctest_t *test, void *arg) {
    uint8_t uc[] = {255, 255, 255};
    Rgb *lym = makeRGB(uc, sizeof(uc));
    
    char *hex = getHexFromRGB(lym);
    char *value = {"ffffff"};
    // As the lib does not support the hex test yet
    CTAssertStringEqual(test, value, hex, "%s is not equal to %s", value, hex);
    
    free(lym);
    free(hex);
}

ctest_return_t testUintArrayCreationFromHex(ctest_t *test, void *arg) {
    char *hex = malloc(sizeof (char) * 6 + 1);
    hex[0] = '0';
    hex[1] = '5';
    hex[2] = '0';
    hex[3] = 'a';
    hex[4] = '5';
    hex[5] = 'f';
    
    Rgb *uc = getRGBFromHex(hex);
    CTAssertEqual(test, 5, uc->r, "R value is %d where as it should be 5", uc->r);
    CTAssertEqual(test, 10, uc->g, "G value is %d where as it should be 10", uc->g);
    CTAssertEqual(test, 95, uc->b, "B value is %d where as it should be 95", uc->b);
    
    free(uc);
    free(hex);
}

ctest_return_t testUintArrayCreationFromSecHex(ctest_t *test, void *arg) {
    char *hex = {"abcdef"};
    Rgb *uc = getRGBFromHex(hex);
    
    CTAssertEqual(test, 171, uc->r, "R value expected: 171, value: %i", uc->r);
    CTAssertEqual(test, 205, uc->g, "G value expected: 205, value: %i", uc->g);
    CTAssertEqual(test, 239, uc->b, "B value expected: 239, value: %i", uc->b);

    free(uc);
}

ctest_return_t testHexToRgb(ctest_t *test, void *arg) {
    char *hex = {"050a62"};
    Rgb *uc = getRGBFromHex(hex);
    
    CTAssertEqual(test, 5, uc->r, "R value expected: 5, value: %i", uc->r);
    CTAssertEqual(test, 10, uc->g, "G value expected: 10, value: %i", uc->g);
    CTAssertEqual(test, 98, uc->b, "B value expected: 98, value: %i", uc->b);
    
    free(uc);
}

ctest_return_t testUintNullCreationFromHex(ctest_t *test, void *arg) {
    char *hex = NULL;
    Rgb *uc = getRGBFromHex(hex);
    CTAssertStringEqual(test, uc->error, NULL_INPUT_PARAM, "Expect Error to be equal to %s", NULL_INPUT_PARAM);
    
    free(uc);
}

ctcase_t *wrapHexCreationTest() {
    // Create test case
    ctcase_t *hexCase = ctcase("Hex creation test");
    
    // Hex test
    ctest_t *hexCreation  = ctest("Create an Hex from RGB", testHexCreationFromRgb, NULL);
    ctest_t *whiteCreation = ctest("Create white HEX value", testWhiteHexCreationFromRgb, NULL);
    ctest_t *uintCreation = ctest("Create an Uint8 Array from HEX", testUintArrayCreationFromHex, NULL);
    ctest_t *hexToRgb = ctest("Creation of an Rgb from Hex", testHexToRgb, NULL);
    ctest_t *uintNull = ctest("Create an Uint8 Array from a Null HEX", testUintNullCreationFromHex, NULL);
    ctest_t *uintOtherHex = ctest("Create RGB From String Hex", testUintArrayCreationFromSecHex, NULL);
    
    // Add test to test case
    ctctestadd(hexCase, hexCreation);
    ctctestadd(hexCase, whiteCreation);
    ctctestadd(hexCase, uintCreation);
    ctctestadd(hexCase, hexToRgb);
    ctctestadd(hexCase, uintNull);
    ctctestadd(hexCase, uintOtherHex);
    
    return hexCase;
}



