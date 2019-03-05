## Ycbcr APIs

The Ycbcr API allow you to create an Ycbcr color from an RGB based color. The Ycbcr APIs allow you ton convert back and forth the value

## RGB to Ycbcr

Use the method **getYcbcrFromRgb**. This method return an Ycbcr struct or NULL

### Error handling

This method will return NULL when:

- Ycbcr struct can't be allocated

This method take as a param an Ycbcr struct with an **error** parameter like so

```c
ycbcr->error = <string>
```

### Parameter

- Rgb pointer struct

### Usage Example

```c
#include "rgb.h"
#include "ycbcr.h"

uint8_t cvalue[3] = {0, 0, 100};
Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
Ycbcr *ycbcr = getYcbcrFromRgb(rgb);

// rgb will not be freed (so that you can reuse this struct)
free(rgb);
```

Ycbcr return the Ycbcr struct which you can access the property like the example below

```c
uint8_t y = ycbcr->y;
uint8_t cb = ycbcr->cb;
uint8_t cr = ycbcr->cr;
char *error = ycbcr->error;
```

## Ycbcr to RGB

Use the method **getRGBFromYcbcr**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Rgb struct can't be allocated

The method *can return an RGB struct containing an error property*

- Ycbcr property not passed
- When an error happened during the conversion process

### Parameter

- Ycbcr pointer struct

### Usage Example

```c
#include "rgb.h"
#include "ycbcr.h"

Ycbcr *Ycbcr = malloc(sizeof(Ycbcr));
ycbcr->y  = 86;
ycbcr->cb = 186;
ycbcr->cr = 77;

// Ycbcr is being freed automatically
Rgb *rgb = getRgbFromYcbcr(Ycbcr);
```

The method will return an Rgb struct which you can access it's property like the example below

```c
uint8_t r = rgb->r;
uint8_t g = rgb->g;
uint8_t b = rgb->b;
char *error = rgb->error;
```



