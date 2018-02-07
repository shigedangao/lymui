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
    ushort v;
};

// Ushort To Hex
char * ushortToHex(ushort v);

// Return a list of ushort binding to hexa var
struct RgbHex * getCorrespondingStruct(void);

#endif /* helper_h */
