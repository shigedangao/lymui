## Hsv APIs

The Hsv API allow you to create an HSV color from an RGB based color. The HSV APIs allow you ton convert back and forth the value

## RGB to Hsv

Use the method **getHsvFromRgb**. This method return an Hsv struct or NULL

### Error handling

This method will return NULL when:

- Hsv struct can't be allocated

This method take as a param an Hsv struct with an **error** parameter like so

```c
hsv->error = <string>
```

### Parameter

- Rgb pointer struct


### Usage Example

```c
#include "rgb.h"
#include "hsv.h"

uint8_t cvalue[3] = {100, 150, 255};
Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
Hsv *hsv = getHsvFromRgb(rgb);

// rgb will not be freed (so that you can reuse this struct)
free(rgb);
```

Hsv return the Hsv struct which you can access the property like the example below

```c
double h = hsv->h;
double s = hsv->s;
double v = hsv->l;
char *error = hsv->error;
```

## Hsv to RGB

Use the method **getRgbFromHsv**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Rgb struct can't be allocated

The method *can return an RGB struct containing an error property*

- Hsv property not passed
- When an error happened during the conversion process

### Parameter

- Hsv pointer struct

### Usage Example

```c
#include "rgb.h"
#include "hsv.h"

Hsv *hsv = malloc(sizeof(Hsv));
hsv->h = 0.0f;
hsv->s = 100.0;
hsv->v = 100.0;

// hsv is being freed automatically
Rgb *rgb = getRgbFromHsv(Hsv);
```

The method will return an Rgb struct which you can access it's property like the example below

```c
uint8_t r = rgb->r;
uint8_t g = rgb->g;
uint8_t b = rgb->b;
char *error = rgb->error;
```



