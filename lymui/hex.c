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
 * @brief Get the uint8_t value based on each character of the Hex
 * @param c a char array representing the Hex array
 * @param idx an index
 * @return a uint8_t value
 */
static uint8_t getUintCharValue(char *c, uint8_t idx) {
    uint8_t n = 0;
    switch (tolower(c[idx])) {
        case 'a': n = 10; break;
        case 'b': n = 11; break;
        case 'c': n = 12; break;
        case 'd': n = 13; break;
        case 'e': n = 14; break;
        case 'f': n = 15; break;
    }
    
    if (!n) {
        char v = c[idx];
        n = strtol(&v, NULL, 10);
    }
    
    return n;
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
    
    uint8_t rgbArr[3];
    uint8_t idx = 0;
    // As we use the ushort we set 16 as our flag
    while (idx < strlen(hex)) {
        int x = getUintCharValue(hex, idx);
        int y = getUintCharValue(hex, idx + 1);
        
        rgbArr[(idx / 2)] = y + (x * 16);
        idx = idx + 2;
    }
    
    // remove the pointer as we don't need it anymore
    rgb->r = rgbArr[0];
    rgb->g = rgbArr[1];
    rgb->b = rgbArr[2];
    rgb->error = NULL;
    
    return rgb;
}
