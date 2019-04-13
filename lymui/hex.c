//
//  hex.c
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "errors.h"
#include "hex.h"
#include "helper.h"

#ifdef _WIN32
#include <stdarg.h>
#define __ms_vsnprintf(a,b,c,...) snprintf(a,b,c,__VA_ARGS__)
#endif

/**
 * @brief convert an uint8_t to an hex
 *        /!\ Note this is a really inefficient of doing things
 *        sprintf don't return the '0' eg: 5 don't return 05 but return 5
 * @param color uint8_t
 * @return char array
 */
static char *uintToHex(uint8_t color) {
    char *tmp = malloc(sizeof(char) * HEX_GROUP_LEN + 1);
    if (tmp == NULL) {
        return NULL;
    }
    
    snprintf(tmp, HEX_GROUP_LEN + 1, "%x", color);
    if (!tmp[1]) {
        tmp[1] = tmp[0];
        tmp[0] = '0';
        tmp[2] = '\0';

        return tmp;
    }
    
    return tmp;
}

// Get Hex From RGB
char *getHexFromRGB(Rgb *c) {
    if (c == NULL) {
        return NULL;
    }
    
    char *r = uintToHex(c->r);
    char *g = uintToHex(c->g);
    char *b = uintToHex(c->b);
    
    if (r == NULL || g == NULL || b == NULL) {
        return NULL;
    }
    
    // create a char array of hex value
    char *hex = malloc(sizeof(char) * HEX_SIZE);
    if (hex == NULL) {
        return NULL;
    }
    
    snprintf(hex, HEX_SIZE, "%s%s%s", r, g, b);
    
    free(r);
    free(g);
    free(b);
    return hex;
}

/**
 * @brief cut a hex char value to a segment
 * @param hex char array
 * @param segment uint8_t
 * @return char array
 */
static char *splitSegment(char *hex, uint8_t segment) {
    char *part = malloc(sizeof(char *) * HEX_GROUP_LEN);
    if (part == NULL) {
        return NULL;
    }
    
    part[0] = hex[segment - 1];
    part[1] = hex[segment];
    part[2] = '\0';
    
    
    return part;
}

/**
 * @brief convert part of hex into a base 10 value
 * @return uint8_t
 */
static uint8_t convertPart(char *part) {
    int p = (int) strtol(part, NULL, HEX_BASE);
    
    return (uint8_t) p;
}

/**
 * @brief Transform a hex of 3 char to a 6 cha
 * @param hex char
 * @return hex copy
 */
static char *unShorten(char *hex) {
    char *copy = malloc(sizeof(char) * HEX_SIZE);
    if (copy == NULL) {
        return NULL;
    }
    
    snprintf(copy, HEX_SIZE, "%c%c%c%c%c%c",hex[0], hex[0], hex[1], hex[1], hex[2], hex[2]);

    return copy;
}

// Get RGB Value From Hex
Rgb *getRGBFromHex(char *hex) {
    Rgb *rgb = initRgb();
    uint8_t shorten = 0;
    if (rgb == NULL) {
        return NULL;
    }
    
    if (hex == NULL) {
        rgb->error = NULL_INPUT_PARAM;
        return rgb;
    }
    
    size_t len = strlen(hex);
    char *hexstr = NULL;
    if (len < 6) {
        hexstr = unShorten(hex);
        shorten = 1;
    } else {
        hexstr = hex;
    }
    
    char *r = splitSegment(hexstr, 1);
    char *g = splitSegment(hexstr, 3);
    char *b = splitSegment(hexstr, 5);
    
    if (shorten) {
        free(hexstr);
    }
    
    if (r == NULL || g == NULL || b == NULL) {
        rgb->error = MALLOC_ERROR;
        return rgb;
    }
    
    rgb->r = convertPart(r);
    rgb->g = convertPart(g);
    rgb->b = convertPart(b);
    rgb->error = NULL;
    
    free(r);
    free(g);
    free(b);
    
    return rgb;
}
