//
//  node_ycbcr.h
//  lymui
//
//  Created by Marc Intha on 31/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef node_ycbcr_h
#define node_ycbcr_h

#include <stdio.h>
#include <node_api.h>

/**
 * @brief get a ycbcr js object from an rgb object
 * @param env napi_env
 * @param info napi_callback_info
 * @return napi_value
 */
napi_value GetYcbcrFromRGB(napi_env env, napi_callback_info info);

#endif /* node_ycbcr_h */
