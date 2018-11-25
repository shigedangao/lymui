//
//  normalizer_xyz.h
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef normalizer_xyz_h
#define normalizer_xyz_h

#include <stdio.h>
#include <node_api.h>

/**
 * @brief normalize lab
 * @param env napi_env
 * @param obj napi_value
 * @return napi_value
 */
napi_value normalizeLab(napi_env env, napi_value obj);

/**
 * @brief normalize lch
 * @param env napi_env
 * @param obj napi_value
 * @return napi_value
 */
napi_value normalizeLch(napi_env env, napi_value obj);

/**
 * @brief normalize lch lab
 * @param env napi_env
 * @param obj napi_value
 * @return napi_value
 */
napi_value normalizeLchLab(napi_env env, napi_value obj);

/**
 * @brief normalize luv
 * @param env napi_env
 * @param obj napi_value
 * @return napi_value
 */
napi_value normalizeLuv(napi_env env, napi_value obj);

#endif /* normalizer_xyz_h */
