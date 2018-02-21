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

/*!
 * @discussion convert an uint character to hex value
 * @param v a Hex char array
 * @return a char
 */
char * ushortToHex(uint8_t v);

/*!
 * @discussion convert a float to a uint
 * @param value float
 * @return a uint8_t value
 */
uint8_t floatToUint(float value);

/*!
 * @discussion Update Constraint Value
 * @param value the float array
 * @return an array of float
 */
float * updateConstraintValue(float *value, uint8_t size);


#endif /* helper_h */
