//
//  hue.c
//  lymui
//
//  Created by Marc on 20/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "hue.h"
#include "helper.h"

Hue getHueFromRgb(Rgb *rgb) {
    if (rgb == NULL)
        return 0.0;
    
    double _r = (double) rgb->r;
    double _g = (double) rgb->g;
    double _b = (double) rgb->b;

    double min = getMinMax(_r, _g, _b, 1);
    double max = getMinMax(_r, _g, _b, 0);
    
    // in case of min == max then return 0
    if (max == min)
        return 0.0;
    
    // Create the hue variable here
    Hue hue = 0.0;

    if (max == _r) {
        hue = (_g - _b) / (max - min);
    } else if (max == _g) {
        hue = 2.0 + (_b - _r) / (max - min);
    } else {
        hue = 4.0 + (_r - _g) / (max - min);
    }
     
    hue = hue * 60.0;
    if (hue < 0.0)
        hue = hue + 360.0;
    
    return round(hue);
}
