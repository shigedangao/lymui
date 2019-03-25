## Lymui

Lymui is a static color conversion library. It's my first project in C !.

[![codecov](https://codecov.io/gh/MarcInthaamnouay/lymui/branch/master/graph/badge.svg)](https://codecov.io/gh/MarcInthaamnouay/lymui)
[![Build Status](https://dev.azure.com/androidgs2/lymui/_apis/build/status/MarcInthaamnouay.lymui?branchName=master)](https://dev.azure.com/androidgs2/lymui/_build/latest?definitionId=1&branchName=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c443f9099d024a81b2c56b42edf0b147)](https://www.codacy.com/app/mintha/lymui?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=MarcInthaamnouay/lymui&amp;utm_campaign=Badge_Grade)

## Version

Version: 1.3.0c

## Support OS

- OSX
- Linux
- Windows 

## Quick start

The library is a static library which come with an ```includes``` folder and a ```liblymui.a``` file. In order to use the project just link thoses files to your project.

You can then use the library like so

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <rgb.h>
#include <hex.h>

int main(int argc, const char *argv[]) {
  Rgb *rgb = malloc(sizeof(Rgb));
  rgb->r = 10;
  rgb->g = 20;
  rgb->b = 30;

  char *hex = getHexFromRgb(rgb);
  // do something with the hex
}
```

## Documentation

For further information you can find the documentation [here](https://marcinthaamnouay.github.io/lymui)

## Changelogs

You can consult the changelog [here](https://marcinthaamnouay.github.io/lymui/changelog).

## Contributions

Contributions and feedbacks are always welcomed :)
