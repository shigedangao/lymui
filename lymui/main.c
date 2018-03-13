//
//  main.c
//  lymui
//
//  Created by Marc on 05/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cunit.h>
#include "rgb.h"
#include "hex.h"
#include "ycbcr.h"
#include "test_header.h"

// @TODO free all the test and the suite and the case
int main(int argc, const char * argv[]) {
    // Create suite case
    ctsuite_t *suite = ctsuite("Lymui test");
    ctcase_t  *rgb   = wrapRgbCreationTest();
    ctcase_t  *hex   = wrapHexCreationTest();
    ctcase_t  *ycbcr = wrapYcbcrCreationTest();
    ctcase_t  *cymk  = wrapCymkCreationTest();
    ctcase_t  *hue   = wrapHueCreationTest();
    ctcase_t  *hsl   = wrapHslCreationTest();
    ctcase_t  *hsv   = wrapHsvCreationTest();
    ctcase_t  *yuv   = wrapYuvCreationTest();
    ctcase_t  *srgb  = wrapSRgbCreationTest();
    ctcase_t  *xyz   = wrapXyzCreationTest();
    
    // Launch suite
    ctscaseadd(suite, rgb);
    ctscaseadd(suite, hex);
    ctscaseadd(suite, ycbcr);
    ctscaseadd(suite, cymk);
    ctscaseadd(suite, hue);
    ctscaseadd(suite, hsl);
    ctscaseadd(suite, hsv);
    ctscaseadd(suite, yuv);
    ctscaseadd(suite, srgb);
    ctscaseadd(suite, xyz);
    ctsrun(suite);
    
    uint8_t failNb = suite->failed;
    
    // free the suite
    ctsfree(suite);
    
    if (failNb > 0)
        return -1;
    
    return 0;
}

