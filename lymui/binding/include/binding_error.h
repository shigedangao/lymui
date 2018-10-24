//
//  binding_error.h
//  lymui
//
//  Created by Marc Intha on 24/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef binding_error_h
#define binding_error_h

#define BINDING_ERR "Unable to bind lib methods"
#define DESERIALIZE_ERR "Unable to deserialize the value"
#define PARSE_ERR "Unable to parse the value"
#define CONVERT_ERR "Error while converting value to an other type"
#define ASSIGN_ERR "Unable to assign value to JS Object"

typedef enum BindingErrorCode {
    bindErrNo = 510,
    deserializeErrNo = 100,
    parseErrNo = 101,
    convertErrNo = 102,
    assignErrNo = 103,
} BindingErrorCode;

#endif /* binding_error_h */
