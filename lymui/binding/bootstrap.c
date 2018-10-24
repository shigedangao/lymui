//
//  node_rgb.c
//  lymui
//
//  Created by Marc Intha on 24/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <node_api.h>
#include "binding_error.h"
#include "node_rgb.h"


#define DECLARE_NAPI_METHOD(name, func) { name, 0, func, 0, 0, 0, napi_default, 0 }

/**
 *  Initialization of our NodeJS module
 */
napi_value Init(napi_env env, napi_value exports) {
    napi_status status;
    
    // define the methods here
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_METHOD("MakeRGB", GenerateRGB)
    };
    
    status = napi_define_properties(env, exports, sizeof(desc) / sizeof(*desc), desc);
    
    if (status != napi_ok) {
        napi_throw_error(env, (char *) bindErrNo, BINDING_ERR);
    }
    
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
