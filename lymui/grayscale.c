//
//  grayscale.c
//  lymui
//
//  Created by Marc Intha on 06/01/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdlib.h>
#include "grayscale.h"
#include "helper.h"

Gray getGrayScale(Rgb *rgb, Strategy s) {
    if (rgb == NULL) {
        return 0;
    }
    
    double _r = (double) rgb->r;
    double _g = (double) rgb->g;
    double _b = (double) rgb->b;
    double grayscale = 0.0;
    
    switch (s) {
        case Lightness:
            grayscale = (getMinMax(_r, _g, _b, 1) + getMinMax(_r, _g, _b, 0)) / 2.0;
            break;
        case Average:
            grayscale = (_r + _g + _b) / 3.0;
            break;
        case bt709:
            grayscale = 0.2126 * _r + 0.7152 * _g + 0.0722 * _b;
            break;
        case bt2100:
            grayscale = 0.2627 * _r + 0.6780 * _g + 0.0593 * _b;
            break;
        default:
            grayscale = 0.21 * _r + 0.72 * _g + 0.07 * _b;
            break;
    }
    
    return doubleToUint(grayscale);
}
