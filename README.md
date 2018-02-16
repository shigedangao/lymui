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

## Documentation

## Rgb methods

Create an RGB require 2 parameters

- param: uint8_t array
- param: length of the array (3)
- return struct Rgb* | NULL if the array does not satisfy the method

```c
uint8_t *foo = malloc(sizeof(uint_8t) * 3);
foo[0] = 100;
foo[1] = 200;
foo[2] = 250;

struct Rgb *rgb = makeRGB(foo, 3);
```

## Hex methods

Create an Hex. Create an Hex required an Rgb struct.

- params: struct Rgb (pointer)
- return: char *hex | NULL

```c
// let's take the variable from the above example
char *hex = getHexFromRGB(rgb);
// the size of the hex char arary is 5 eg: "ABCDEF"
```

WIP