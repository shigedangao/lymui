//
//  helper.c
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "helper.h"

uint8_t doubleToUint(double value) {
    return (uint8_t) round(value);    
}

double getSaturation(double min, double max, double l) {
    // big condition... we also check if max and min is not equal to 1 in order to avoid dividing by 0...
    if (l > 0.5 && (max != 1.0 || min != 1.0))
        return (max - min) / (2.0 - max - min);
    
    // prevent dividing by 0
    if (!max && !min) {
        return 0;
    }

    return (max - min) / (max + min);
}

double getDegFromRad(double r) {
    return 180.0 * r / M_PI;
}

double getRadFromDeg(double d) {
    return d * M_PI / 180.0;
}

double getMinMax(double r, double g, double b, uint8_t op) {
    if (op) {
        return fmin(fmin(r, g), b);
    }
    
    return fmax(fmax(r, g), b);
}
