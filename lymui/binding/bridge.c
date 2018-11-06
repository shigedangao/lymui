//
//  bridge.c
//  lymui
//
//  Created by Marc Intha on 26/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "bridge.h"
#include <stdlib.h>
#include <string.h>
#include <node_api.h>
#include "binding_error.h"
#include "binding_util.h"
#include "rgb.h"
#include "hex.h"
#include "hsl.h"
#include "hsv.h"
#include "yuv.h"

static void getNamedPropArray(napi_env env, char * name, napi_value obj, size_t len, napi_value * res) {
    uint8_t idx = 0;
    napi_status status;
    const char delimiter[] = ":";
    char * running = strdup(name);
    char * string;
    
    while(idx < len) {
        string = strsep(&running, delimiter);
        status = napi_get_named_property(env, obj, string, &res[idx]);
        if (status != napi_ok) {
            idx = len + 1;
            napi_throw_error(env, NULL, DESERIALIZE_ERR);
        }
        
        idx++;
    }
}

Rgb * getRGBFromJSObj(napi_env env, napi_value obj) {
    napi_status status;
    napi_value r, g, b;
    char * prop = "r:g:b";
    
    // check if the object has the property
    if (!hasPropInJSObj(env, obj, prop, RgbPropLen)) {
        napi_throw_error(env, NULL, PROP_FOUND_ERR);
    }
    // trying to retreive the value
    status = napi_get_named_property(env, obj, "r", &r);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "g", &g);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "b", &b);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    // convert the data to the wanted type
    uint8_t red = getUintValue(env, r);
    uint8_t green = getUintValue(env, g);
    uint8_t blue = getUintValue(env, b);
    uint8_t arr[] = {red, green, blue};
    
    Rgb * rgb = makeRGB(arr, sizeof(arr));
    
    return rgb;
}

char * getHEXFromJSObj(napi_env env, napi_value obj) {
    napi_status status;
    size_t hexLen;
    char * hex = malloc(sizeof(char) * HEX_SIZE + 1);
    
    status = napi_get_value_string_utf8(env, obj, hex, HEX_SIZE + 1, &hexLen);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    char * unslashHex = malloc(sizeof(char) * HEX_SIZE);
    strncpy(unslashHex, hex + 1, 7);
    unslashHex[7] = '\0';
    
    free(hex);
    return unslashHex;
}

Cymk * getCymkFromJSObj(napi_env env, napi_value obj) {
    napi_status status;
    napi_value c, y, m, k;
    char * prop = "c:y:m:k";
    
    if (!hasPropInJSObj(env, obj, prop, CymkPropLen)) {
        napi_throw_error(env, NULL, PROP_FOUND_ERR);
        // usually it's not necessary to return NULL but in this case idk why it is needed...
        // The napi_throw_error throw but does not stop the execution which is strange...
        return NULL;
    }
    
    status = napi_get_named_property(env, obj, "c", &c);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "y", &y);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "m", &m);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "k", &k);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    
    Cymk * cymkSt = malloc(sizeof(Cymk));
    cymkSt->c = getFloatValue(env, c);
    cymkSt->y = getFloatValue(env, y);
    cymkSt->m = getFloatValue(env, m);
    cymkSt->k = getFloatValue(env, k);
    
    return cymkSt;
}

Ycbcr * getYcbcrFromJSObj(napi_env env, napi_value obj) {
    napi_status status;
    napi_value y, cb, cr;
    char * prop = "y:cb:cr";
    
    if (!hasPropInJSObj(env, obj, prop, YCbCrLen)) {
        napi_throw_error(env, NULL, PROP_FOUND_ERR);
    }
    
    status = napi_get_named_property(env, obj, "y", &y);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    };
    
    status = napi_get_named_property(env, obj, "cb", &cb);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    };
    
    status = napi_get_named_property(env, obj, "cr", &cr);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    Ycbcr * ycb = malloc(sizeof(Ycbcr));
    ycb->y = getUintValue(env, y);
    ycb->cb = getUintValue(env, cb);
    ycb->cr = getUintValue(env, cr);
    
    return ycb;
}

Hsl * getHslFromJSObj(napi_env env, napi_value obj) {
    napi_status status;
    napi_value h, s, l;
    char * prop = "h:s:l";
    
    if (!hasPropInJSObj(env, obj, prop, HslHsvLen)) {
        napi_throw_error(env, NULL, PROP_FOUND_ERR);
    }
    
    status = napi_get_named_property(env, obj, "h", &h);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "s", &s);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "l", &l);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    Hsl * hsl = malloc(sizeof(Hsl));
    hsl->h = getFloatValue(env, h);
    hsl->s = getFloatValue(env, s);
    hsl->l = getFloatValue(env, l);
    
    return hsl;
}

Hsv * getHsvFromJSObj(napi_env env, napi_value obj) {
    napi_status status;
    napi_value h, s, v;
    char * prop = "h:s:v";
    
    if (!hasPropInJSObj(env, obj, prop, HslHsvLen)) {
        napi_throw_error(env, NULL, PROP_FOUND_ERR);
    }
    
    status = napi_get_named_property(env, obj, "h", &h);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "s", &s);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    status = napi_get_named_property(env, obj, "v", &v);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, DESERIALIZE_ERR);
    }
    
    Hsv * hsv = malloc(sizeof(Hsv));
    hsv->h = getFloatValue(env, h);
    hsv->s = getFloatValue(env, s);
    hsv->v = getFloatValue(env, v);
    
    return hsv;
}

Yuv * getYuvFromJSObj(napi_env env, napi_value obj) {
    char * prop = "y:u:v";
    napi_value value[3];
    
    if (!hasPropInJSObj(env, obj, prop, YUVLen)) {
        napi_throw_error(env, NULL, PROP_FOUND_ERR);
        return NULL;
    }
    
    // retrieve the property in an array of values
    getNamedPropArray(env, prop, obj, 3, value);
    float yv = getFloatValue(env, value[0]);
    float uv = getFloatValue(env, value[1]);
    float vv = getFloatValue(env, value[2]);
    
    Yuv * yuv = malloc(sizeof(Yuv));
    if (yuv == NULL) {
        napi_throw_error(env, NULL, ALLOCATION_ERR);
    }
    
    yuv->y = yv;
    yuv->u = uv;
    yuv->v = vv;
    
    return yuv;
}
