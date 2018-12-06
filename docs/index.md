## Lymui

Lymui is a small C color conversion library which support the following formats:

- rgb
- hex
- hsl
- hsv
- hue
- lab
- lch(uv)
- lch(lab)
- luv
- sRGB
- aRGB
- xyz
- xyy
- ycbcr
- yuv

This library is provided as a static library that you can plug to your project

## Testing & Generate static lib

Clone this repository.
Testing on MacOSX & Linux based should be pretty straightforward

The test are made with **cunit library**. the provided lib has been build for OSX.

### For OSX Users

I recommended you to download Xcode. As the project is made using Xcode it will be easier for you to run it right away.

By using Xcode you will be able to launch the tests directly by running the project. Every tests are referenced on the ```main.c``` file.

### For Linux user

A makefile is available at the root of the folder. Launch the following commands

- ```make lym``` --> this is going to create an executable file
- ```make test``` --> this is going to run the test

### Generate static lib

On both MacOSX & Linux run the command ```make lib``` this should create a static library within the **bin** folder. 
The bin folder should contain the following folder & files.

```shell
-- includes
-- liblymui.a
```

### APIs

Below is the list of APIs available

