//
//  convert_xyz.h
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef convert_xyz_h
#define convert_xyz_h

#include <stdio.h>
#include <node_api.h>

/**
 * @brief To XYZ
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value toXYZ(napi_env env, napi_callback_info info);

#endif /* convert_xyz_h */
