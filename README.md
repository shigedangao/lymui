##  Lymui

Lymui is a small color conversion library. It's my first project in C !.

## Tests

This project used cunit @itzseven library as it's unit test lib.

[![Coverage Status](https://coveralls.io/repos/github/MarcInthaamnouay/lymui/badge.svg)](https://coveralls.io/github/MarcInthaamnouay/lymui)

[![Build Status](https://travis-ci.org/MarcInthaamnouay/lymui.svg?branch=master)](https://travis-ci.org/MarcInthaamnouay/lymui)

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c443f9099d024a81b2c56b42edf0b147)](https://www.codacy.com/app/mintha/lymui?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=MarcInthaamnouay/lymui&amp;utm_campaign=Badge_Grade)

## Status

Version: 1.1.0a

## Contribute

Contributions are always welcomed. Open issue if you want to add an other kind of format and submit a PR if you wish to add an other feature such as a format color and many more...

## Install & Compile the project

The project is shipped with a makefile. Below is the command that you can use in order to generate different type of build

- Output lib: ```make lib```

Note: If you want to test on **linux** please clone cunit test library. Or if you recommend an other one why not

After cloning cunit lib launch the make command from cunit library and then copy paste the includes and libcunit.a from the bin folder to the lib/cunit folder.
Then you can run the command below

- Test app: ```make lym && make test```

### Note

If you want to test this project with Xcode you will need to add the **binding** folder to the excluded source file names property of xcode

```bash
EXCLUDED_SOURCE_FILE_NAMES = lymui/binding/* 
EXCLUDED_SOURCE_FILE_NAMES = lymui/binding/normalizer/*
```

## Usage

Converting a kind of color required you to import a color of type T. From this type T color you will be able to convert into an other type of color. 

Note that for any color space you have to pass by an Xyz color then to the wanted color. Below is some example of how to use the lib.

**Note**: When converting a color the struct that has been given to a converter will be freed

## Example in C

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

#### Converting an Rgb to an Hsl

```c
#include <stdlib.h>
#include "rgb.h"
#include "hsl.h"

struct Rgb *rgb = initRGB();
// rgb return NULL if malloc fail
rgb->r = 100;
rgb->g = 150;
rgb->b = 200;

// Convert a rgb struct to an Hex
Hsl *hsl = getHslFromRGB(rgb);

// Every Struct either return NULL if malloc fail.
// If it fail internally it return an error char

if (hsl->error != NULL) {
  printf("AYOO !! an error %s", hsl->error);
}

// do anything you want with the struct pointer then :)
double hue = hsl->h;
```

## APIs

Please take a look at the list of available APIs

[APIs list](https://marcinthaamnouay.github.io/lymui/docs/)