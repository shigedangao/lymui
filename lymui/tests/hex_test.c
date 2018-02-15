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
#include "hex.h"
#include "rgb.h"

ctest_return_t testHexCreationFromRgb(ctest_t *test, void *arg) {
    uint8_t uc[]    = {5, 10, 95};
    struct Rgb *lym = makeRGB(uc, sizeof(uc));
    
    char *hex = getHexFromRGB(lym);
    char *value = malloc(sizeof(char) * 5);
    value = "050A5F";
    
    // As the lib does not support the hex test yet
    CTAssertEqual(test, 0, strcmp(value, hex), "Hex is not equal to lym values %s", hex);
    
    free(lym);
    free(hex);
}

ctest_return_t testUintArrayCreationFromHex(ctest_t *test, void *arg) {
    char *hex = malloc(sizeof (char) * 5);
    hex[0] = '0';
    hex[1] = '5';
    hex[2] = '0';
    hex[3] = 'A';
    hex[4] = '5';
    hex[5] = 'F';
    
    uint8_t *uc = getRawRGBArrayValueFromHex(hex);

    CTAssertEqual(test, 5, uc[0], "UC value is %d where as it should be %d", 5, uc[0]);
    CTAssertEqual(test, 10, uc[1], "UC value is %d where as it should be %d", 10, uc[1]);
    CTAssertEqual(test, 95, uc[2], "UC value is %d where as it should be %d", 95, uc[2]);
    
    free(uc);
}

ctest_return_t testUintNullCreationFromHex(ctest_t *test, void *arg) {
    char *hex = NULL;
    uint8_t *uc = getRawRGBArrayValueFromHex(hex);
    
    CTAssertNull(test, uc, "Test uint null creation, value is not NULL");
}

ctcase_t *wrapHexCreationTest() {
    // Create test case
    ctcase_t *hexCase = ctcase("Hex creation test");
    
    // Hex test
    ctest_t *hexCreation  = ctest("Create an Hex from RGB", testHexCreationFromRgb, NULL);
    ctest_t *uintCreation = ctest("Create an Uint8 Array from HEX", testUintArrayCreationFromHex, NULL);
    ctest_t *uintNull = ctest("Create an Uint8 Array from a Null HEX", testUintNullCreationFromHex, NULL);
    
    // Add test to test case
    ctctestadd(hexCase, hexCreation);
    ctctestadd(hexCase, uintCreation);
    ctctestadd(hexCase, uintNull);
    
    return hexCase;
}



