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

/**
 *  Initialisation of our NodeJS module
 */
napi_value Init(napi_env env, napi_value exports) {
    napi_status status;
    
    // define the methods here
    napi_property_descriptor desc[] = {
        
    };
    
    status = napi_define_properties(env, exports, sizeof(desc) / sizeof(*desc), desc);
    
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Unable to bootstrap methods");
    }
    
    return exports;
}
