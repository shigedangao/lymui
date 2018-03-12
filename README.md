##  Lymui

Lymui is a small color library for fun & testing c

## Status

[![Coverage Status](https://coveralls.io/repos/github/MarcInthaamnouay/lymui/badge.svg)](https://coveralls.io/github/MarcInthaamnouay/lymui)

[![Build Status](https://travis-ci.org/MarcInthaamnouay/lymui.svg?branch=master)](https://travis-ci.org/MarcInthaamnouay/lymui)

## Contribute

Contributions are always welcomed. Please open a PR and assign me or other people who has been involved in the project 🐼.

## Install & Compile the project

Before compiling the project we need to make sure that you have the following prerequisites

- Clang / GCC / LLVM GCC
- Xcode preferably
- CZ cli available here for commit consistency: [CZ-cli](https://github.com/commitizen/cz-cli)

## Instruction

For OSX users: Open the project in Xcode and compile it.
For other users, go to the root of the project and **build the project** with the command ```make```. Test the project with ```make test```

## Usage

Every modules allow you to convert a Type T to an RGB and vice versa

## Example

```c
uint8_t c[] = {5, 10, 95};
struct Rgb *rgb = makeRGB(c)

// convert it to yuv
struct Yuv *yuv = getYuvFromRgb(rgb)

// you can convert it back to rgb too
struct Rgb *rgbFromYuv = getRgbFromYuv(yuv)
```