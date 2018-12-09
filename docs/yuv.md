## Yuv APIs

The Yuv API allow you to create an Yuv color from an RGB based color. The Yuv APIs allow you ton convert back and forth the value

## RGB to Yuv

Use the method **getYuvFromRgb**. This method return an Yuv struct or NULL

### Error handling

This method will return NULL when:

- Yuv struct can't be allocated

This method take as a param an Yuv struct with an **error** parameter like so

```c
yuv->error = <string>
```

### Parameter

- Rgb pointer struct


### Usage Example

```c
#include "rgb.h"
#include "yuv.h"

uint8_t cvalue[3] = {100, 150, 255};
Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
Yuv *yuv = getYuvFromRgb(rgb);
```

Yuv return the Yuv struct which you can access the property like the example below

```c
double y = yuv->h;
double u = yuv->s;
double v = yuv->l;
char *error = yuv->error;
```

## Yuv to RGB

Use the method **getRgbFromYuv**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Rgb struct can't be allocated

The method *can return an RGB struct containing an error property*

- Yuv property not passed
- When an error happened during the conversion process

### Parameter

- Yuv pointer struct

### Usage Example

```c
#include "rgb.h"
#include "yuv.h"

Yuv *yuv = malloc(sizeof(Yuv));
yuv->y = 0.124f;
yuv->u = 0.122f;
yuv->v = 0.063f;

Rgb *rgb = getRgbFromYuv(Yuv);
```

The method will return an Rgb struct which you can access it's property like the example below

```c
uint8_t r = rgb->r;
uint8_t g = rgb->g;
uint8_t b = rgb->b;
char *error = rgb->error;
```



