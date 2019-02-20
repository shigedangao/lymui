//
//  test_helper.c
//  lymui
//
//  Created by Marc Intha on 20/02/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "test_header.h"

double roundup(double value, double cell) {
    return ceilf(value * cell) / cell;
}
