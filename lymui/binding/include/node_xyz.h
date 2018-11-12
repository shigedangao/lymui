//
//  node_xyz.h
//  lymui
//
//  Created by Marc Intha on 09/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef node_xyz_h
#define node_xyz_h

#include <stdio.h>
#include <node_api.h>

#define XYZ_MATRIX_LEN 9

/**
 * @brief retrieve the Xyz Object from an RGB Object
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value GetXyzFromRGB(napi_env env, napi_callback_info info);

/**
 * @brief retrieve the RGB Object from a Xyz Object
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value GetRGBFromXyz(napi_env env, napi_callback_info info);

#endif /* node_xyz_h */
