## Hex APIs

The Hex API allow you to create an HEX from an RGB struct and to convert it back to an RGB from an HEX

## RGB to Hex

Use the method: **getHexFromRGB**. This method return a char array or NULL

### Error handling

This method will return NULL when these conditions are meet:

- Unable to convert uint to hex
- Unable to allocate hex char array

### Parameter

- Rgb pointer struct

### Example

```c
#include "rgb.h"
#include "hex.h"

uint8_t colors = {5, 10, 95};
Rgb *rgb = makeRGB(colors, sizeof(colors));

if (rgb == NULL) {
  // ... do something
}

char *hex = getHexFromRGB(rgb);
// rgb will not be freed (so that you can reuse this struct)
free(rgb);

// should print "hex is equal to 050a5f"
printf("hex is equal to %s", hex);
```

## Hex to RGB

Use the method **getRGBFromHex** to get the RGB

### Error handling

This method will return NULL when:

- Rgb struct can't be allocated

The method *can return an RGB struct containing an error property*

- Hex property not passed

### Example

```c
#include "rgb.h"
#include "hex.h"

char *hex = {"050a5f"};
Rgb *rgb = getRGBFromHex(hex);

// RGB will contain R, G, B or an error message
// can be access like so
```

The method will return an Rgb struct which you can access it's property like the example below

```c
uint8_t r = rgb->r;
uint8_t g = rgb->g;
uint8_t b = rgb->b;
char *error = rgb->error;
```