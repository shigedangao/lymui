//
//  main.c
//  lymui
//
//  Created by Marc on 05/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include "rgb.h"

int main(int argc, const char * argv[]) {
    ushort c[] = {0, 255, 255};
    struct Rgb *color = makeRGB(c);
    
    printf("g is %i", color->g);
    return 0;
}
