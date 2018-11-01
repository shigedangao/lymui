//
//  factory.h
//  lymui
//
//  Created by Marc Intha on 01/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef factory_h
#define factory_h

#include <stdio.h>
#include <node_api.h>
#include "rgb.h"

/**
 * @brief Factory creating Rgb Object on the fly
 * @param env napi_env
 * @param rgb Rgb struct pointer
 */
napi_value RgbJSObjFactory(napi_env env, Rgb * rgb);

#endif /* factory_h */
