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
#include "test_header.h"
#include "hex.h"
#include "rgb.h"

ctest_return_t testHexCreationFromRgb(ctest_t *test, void *arg) {
    uint8_t uc[]    = {5, 10, 95};
    struct Rgb *lym = makeRGB(uc, sizeof(uc));
    
    char *hex = getHexFromRGB(lym);
    char *value = "050A5F";
    
    // As the lib does not support the hex test yet
    CTAssertEqual(test, value[0], hex[0], "Hex is not equal to lym values %s", hex);
    CTAssertEqual(test, value[1], hex[1], "Hex is not equal to lym values %s", hex);
    CTAssertEqual(test, value[2], hex[2], "Hex is not equal to lym values %s", hex);
    CTAssertEqual(test, value[3], hex[3], "Hex is not equal to lym values %s", hex);
    CTAssertEqual(test, value[4], hex[4], "Hex is not equal to lym values %s", hex);
    CTAssertEqual(test, value[5], hex[5], "Hex is not equal to lym values %s", hex);
    
    free(lym);
    free(hex);
}

ctcase_t *wrapHexCreationTest() {
    // Create test case
    ctcase_t *hexCase = ctcase("Hex creation test");
    
    // Hex creation
    ctest_t *hexCreation = ctest("Create an Hex from RGB", testHexCreationFromRgb, NULL);
    ctctestadd(hexCase, hexCreation);
    
    return hexCase;
}

