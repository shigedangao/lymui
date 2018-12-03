//
//  hex.h
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef hex_h
#define hex_h

#include <stdio.h>
#include "rgb.h"

#define HEX_SIZE 7
#define HEX_GROUP_LEN 2

/**
 * @brief Create a char array which is the HEX value
 * @param rgb a RGB structure
 * @return a Char array pointer containing the HEX
 */
char *getHexFromRGB(Rgb *rgb);

/**
 * @brief Get a raw uint8_t array value
 * @param hex a Hex char array
 * @return a uint8_t value
 */
Rgb *getRGBFromHex(char *hex);

/**
 * @brief Get the uint8_t value based on each character of the Hex
 * @param v a char array representing the Hex array
 * @param idx an index
 * @return a uint8_t value
 */
uint8_t getUintCharValue(char *v, uint8_t idx);

#endif /* hex_h */
