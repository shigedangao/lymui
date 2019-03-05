## Hsl APIs

The Hsl API allow you to create an HSL color from an RGB based color. The HSL APIs allow you ton convert back and forth the value

## RGB to Hsl

Use the method **getHslFromRgb**. This method return an Hsl struct or NULL

### Error handling

This method will return NULL when:

- Hsl struct can't be allocated

This method take as a param an Hsl struct with an **error** parameter like so

```c
hsl->error = <string>
```

### Parameter

- Rgb pointer struct

### Usage Example

```c
#include "rgb.h"
#include "hsl.h"

uint8_t cvalue[3] = {100, 150, 255};
Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
Hsl *hsl = getHslFromRgb(rgb);

// rgb will not be freed (so that you can reuse this struct)
free(rgb);
```

Hsl return the Hsl struct which you can access the property like the example below

```c
double h = hsl->h;
double s = hsl->s;
double l = hsl->l;
char *error = hsl->error;
```

## Hsl to RGB

Use the method **getRgbFromHsl**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Rgb struct can't be allocated

The method *can return an RGB struct containing an error property*

- Hsl property not passed
- When an error happened during the conversion process

### Parameter

- Hsl pointer struct

### Usage Example

```c
#include "rgb.h"
#include "hsl.h"

Hsl *hsl = malloc(sizeof(Hsl));
hsl->h = 0;
hsl->s = 0;
hsl->l = 59;

// hsl is being freed automatically
Rgb *rgb = getRgbFromHsl(hsl);
```

The method will return an Rgb struct which you can access it's property like the example below

```c
uint8_t r = rgb->r;
uint8_t g = rgb->g;
uint8_t b = rgb->b;
char *error = rgb->error;
```



