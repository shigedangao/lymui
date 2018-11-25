//
//  deserializer_opts.h
//  lymui
//
//  Created by Marc Intha on 25/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef deserializer_opts_h
#define deserializer_opts_h

#include <stdio.h>
#include <node_api.h>

/**
 * @brief structure for the optional field deserializer
 */
typedef struct OptFields {
    napi_value field;
    bool has;
} OptField;

/**
 * @brief retrieve an optional field. Note this method is fail passive
 * @param env napi_env
 * @param val napi_value
 * @param field *char
 */
OptField *getOptField(napi_env env, napi_value val, char *field);

#endif /* deserializer_opts_h */
