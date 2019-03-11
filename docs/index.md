---
layout: single
classes: wide
title: Lymui
sidebar:
  nav: "docs"
---

## Introduction

Lymui is a static C library that convert color in several format that you can find on this link [supported colors format](list.md)

The library support these Operating Systems below:

- Linux
- OSX
- Windows

### Package

The library contains the following files:

- includes/*.c (.h files)
- liblymui.a

### Usage

The usage is pretty simple. Please refer to the [API explanation](api.md)

### List of colors list

The library is supporting multiples colors. Please refer to the [colors list doc](list.md) for the supported list of colors.

### Unit test

The project has been test with [Minunit](https://github.com/siu/minunit) in these platforms on Azure:

- Linux (ubuntu-16.04)
- OSX (macOS-10.13)
- Windows

The coverage is available on [Codecov](https://codecov.io/gh/MarcInthaamnouay/lymui)

The code is also checked by [Codacy](https://app.codacy.com/project/mintha/lymui/dashboard) in order to check for any bad memory leakage and other C error (Note, this might not prevent everything but still help a lot)

### Resources

Many resources has been used for making this library. Especially regarding the calculation of the color formats. Below is the resources that I used. All credits goes to them.

[Bruce Lindbloom, colorspace](http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html)

[CIE calcuator](http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html)

[Wikipedia](https://en.wikipedia.org/wiki/RGB_color_model)

[ColorMine](http://colormine.org/)

[Python color conversion library](https://github.com/retostauffer/python-colorspace)

[RapidTables](https://www.rapidtables.com/)

[EasyRGB](http://www.easyrgb.com/en/)

[Color NodeJS library](https://github.com/Qix-/color)

[Niwa.nu](http://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/)
