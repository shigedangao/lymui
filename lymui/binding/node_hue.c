//
//  node_hue.c
//  lymui
//
//  Created by Marc Intha on 30/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "node_hue.h"
#include <stdlib.h>
#include <node_api.h>
#include "binding_error.h"
#include "bridge.h"
#include "hue.h"

napi_value GetHueFromRgb(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value hue;
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
        return NULL;
    }
    
    if (argc < 1) {
        napi_throw_error(env, NULL, ARG_NB_ERR);
        return NULL;
    }
    
    Rgb * rgb = getRGBFromJSObj(env, argv[0]);
    if (rgb == NULL) {
        napi_throw_error(env, NULL, PROP_NOT_FOUND_ERR);
        return NULL;
    }
    
    Hue h = getHueFromRgb(rgb);
    
    status = napi_create_double(env, (double) h, &hue);
    if (status != napi_ok) {
        free(rgb);
        napi_throw_type_error(env, NULL, CREATE_TYPE_ERR);
        return NULL;
    }
    
    free(rgb);
    return hue;
}
