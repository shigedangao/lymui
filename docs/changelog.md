---
layout: single
classes: wide
title: Lymui
sidebar:
  nav: "docs"
---

## Changelog

* 1.3.0
* * Add support of generate tint
* * Add support of generate shade
* * Flatten error message
* * Fix unhandled NULL char when converting to an RGB
* * Refactor Xyz
* * Refactor HSL
* * Refactor LUV
* * Move HunterLab to it's own color type 
* * Fix memory leak in Xyz & Lch
* * Change unit test library
* * Move from travis to azure pipelines & coveralls -> codecov

* 1.2.2
* * Fix potentials memory leaks
* * Fix tsl test on debian
* * Refactor ycbcr calculation process (simplifcation)

* 1.2.1
* * Fix short hand hex which cause some random generated value
* * Add missing support for argb -> xyz

* 1.2.0:
* * Remove free on rgb & xyz for user's reusability 
* * Add support for TSL color format
* * Add support for converting shorthand hex -> rgb
* * Add support for HWB color format
* * Add support for grayscale color format

* 1.1.1:
* * Refactor Hex -> Rgb
* * Fix random wrong value when converting Hex to Rgb
* * Add more tests cases on Yuv
* * Update travis config

* 1.1.0: 
* * Refactor error handling
* * Change decimal type to double
* * Fix hex random wrong output issue
* * Fix miscalculation for XYZ type colors
* * Reviewed lab, lch, lchuv color calculation
* * Remove useless use malloc (internal)
* * Update tests
* * Other bug fixes

* 1.0.0: Initial release