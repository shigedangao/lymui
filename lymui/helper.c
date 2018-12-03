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

double roundDigit(double value, int factor) {
    return round(value * factor) / factor;
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

double *updateConstraintValue(double *value, uint8_t size) {
    size_t idx = size;
    
    while(idx > 0) {
        double tmp = value[idx - 1];
        if (tmp < 0.0)
            value[idx - 1] = tmp + 1.0f;
        else if (tmp > 1.0)
            value[idx - 1] = tmp - 1.0f;
        
        idx--;
    }
        
    return value;
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
