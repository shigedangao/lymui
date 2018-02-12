//
//  helper.h
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef helper_h
#define helper_h

#include <stdio.h>

// Rgb Hex Struct
struct RgbHex {
    char id;
    uint8_t v;
};

// Ushort To Hex
char * ushortToHex(uint8_t v);

// Float to Uint
// Use by Ycbcr conversion
uint8_t floatToUint(float value);

#endif /* helper_h */
