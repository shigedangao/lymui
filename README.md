##  Lymui

Lymui is a small color conversion library. It's my first project in C !.

## Tests

This project used cunit @itzseven library as it's unit test lib.

[![Coverage Status](https://coveralls.io/repos/github/MarcInthaamnouay/lymui/badge.svg)](https://coveralls.io/github/MarcInthaamnouay/lymui)

[![Build Status](https://travis-ci.org/MarcInthaamnouay/lymui.svg?branch=master)](https://travis-ci.org/MarcInthaamnouay/lymui)

## Status

Version: 1.0.1

## Contribute

Contributions are always welcomed. Open issue if you want to add an other kind of format and submit a PR if you wish to add an other feature such as a format color and many more...

## Install & Compile the project

The project is shipped with a makefile. Below is the command that you can use in order to generate different type of build

- Output lib: ```make lib```
- CLI app: ```make lym```

## Usage

Converting a kind of color required you to import a color of type T. From this type T color you will be able to convert into an other type of color. 

Note that for any color space you have to pass by an Xyz color then to the wanted color. Below is some example of how to use the lib.

Note that each time you convert a base color T to an other format Y, the **base color T will be free** (this might need improvement...)

## NodeJS

A NodeJS compatibility is currently being in WIP by using N-API. You can check the code on the binding folder lymui/binding.

## Example in C

#### Converting an RGB to an XYZ to an Lch(uv)

```c
#include "rgb.h"
#include "xyz.h"
#include "lch.h"

uint8_t c[] = {5, 10, 95};
struct Rgb *rgb = makeRGB(c)

// Convert the Rgb to an Xyz
// generateXyzFromRgb take 2 parameter an Rgb struct pointer and an enum (sRgb | adobeRgb)
struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);

// Convert the xyz to an lch
struct Lch *lch = getLchFromXyz(xyz);
```

#### Converting an Rgb to an Hex

```c
#include <stdlib.h>
#include "rgb.h"
#include "hex.h"

uint8_t c[] = {5, 10, 95};
struct Rgb *rgb = makeRgb(c);

// Convert a rgb struct to an Hex
char * hex = getHexFromRGB(rgb);

printf("Value of the hex %s", hex);
```

## Example in NodeJS

#### Converting an Rgb to an Hex

```js
const lib = require('lymuilib')

const rgb = {
  r: 5,
  g: 10,
  b: 98
};

// note: This method can throw the list of the error can be found on the binding_error.h file
const hex = lib.getHEX(rgb);
```