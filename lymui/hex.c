//
//  hex.c
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "errors.h"
#include "hex.h"
#include "helper.h"

/**
 * @brief convert an uint8_t to an hex
 *        /!\ Note this is a really inefficient of doing things
 *        sprintf don't return the '0' eg: 5 don't return 05 but return 5
 * @param color uint8_t
 * @return char array
 */
static char *uintToHex(uint8_t color) {
    char *tmp = malloc(sizeof(char) * HEX_GROUP_LEN + 1);
    char *hex = malloc(sizeof(char) * HEX_GROUP_LEN + 1);
    if (tmp == NULL || hex == NULL) {
        return NULL;
    }
    
    sprintf(tmp, "%x", color);
    if (!tmp[1]) {
        strcpy(hex, "0");
        strcat(hex, &tmp[0]);
        
        free(tmp);
        return hex;
    }
    
    free(hex);
    return tmp;
}

// Get Hex From RGB
char *getHexFromRGB(Rgb *c) {
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
    char *copy = malloc(sizeof(6));
    if (copy == NULL) {
        return NULL;
    }
    
    snprintf(copy, sizeof(copy) / sizeof(copy[0]), "%c%c%c%c%c%c",hex[0], hex[0], hex[1], hex[1], hex[2], hex[2]);

    return copy;
}

// Get RGB Value From Hex
Rgb *getRGBFromHex(char *hex) {
    Rgb *rgb = initRgb();
    if (rgb == NULL) {
        return NULL;
    }
    
    if (hex == NULL) {
        rgb->error = NULL_INPUT_PARAM;
        return rgb;
    }
    
    char *hexstr = NULL;
    if (strlen(hex) < 6) {
        hexstr = unShorten(hex);
    } else {
        hexstr = hex;
    }
    
    char *r = splitSegment(hexstr, 1);
    char *g = splitSegment(hexstr, 3);
    char *b = splitSegment(hexstr, 5);
    
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
