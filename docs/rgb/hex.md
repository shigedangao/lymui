## Hex API

The HEX api allow you to generated an hexadecimal value from an [Rgb](rgb.md) struct.

### Example Rgb to Hex

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <hex.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 255;
rgb->g = 255;
rgb->b = 255;

char *hex = getHexFromRGB(rgb);
// Print ffffff
```

### Example Hex to Rgb

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <hex.h>

char *hex = {"fff"};
Rgb *rgb = getRGBFromHex(hex);
```

### Example shorthand Hex to Rgb

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <hex.h>

char *hex = {"fff"};
Rgb *rgb = getRGBFromHex(hex);
```

### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the char array needed for holding the hex value
