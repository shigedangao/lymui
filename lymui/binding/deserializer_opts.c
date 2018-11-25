//
//  deserializer_opts.c
//  lymui
//
//  Created by Marc Intha on 25/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "deserializer_opts.h"
#include <stdlib.h>

OptField *getOptField(napi_env env, napi_value obj, char *field) {
    napi_status status;
    bool hasOptProp;
    napi_value optfield;
    
    OptField *opt = malloc(sizeof(OptField));
    if (opt == NULL) {
        return NULL;
    }
    
    status = napi_has_named_property(env, obj, field, &hasOptProp);
    if (status != napi_ok) {
        opt->has = false;
        return opt;
    }
    
    if (!hasOptProp) {
        opt->has = false;
        return opt;
    }
    
    status = napi_get_named_property(env, obj, field, &optfield);
    if (status != napi_ok) {
        opt->has = false;
        return opt;
    }
    
    opt->field = optfield;
    opt->has = true;
    
    return opt;
}

