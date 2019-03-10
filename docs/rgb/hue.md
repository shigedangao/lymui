## Hue API

The HUE api allow you to generate a Hue value from an [Rgb](rgb.md) color.

### Datatype

The api return a double which represent a hue value of type double

### Methods signature

#### Rgb -> Hue

- Rgb -> Hue: getHueFromRgb()
- *Params*: Rgb* structure
- *Return*: hue double

### Example Rgb to Hue

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <hue.h>

Rgb *rgb  = makeRGB(cvalue, 3);
Hue hue = getHueFromRgb(rgb);
// Output 0.0
```

### Handling errors

- ```0.0```: If you're passing a NULL Rgb structure the method will return ```0.0```
