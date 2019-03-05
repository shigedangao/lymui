## API

The API is pretty simple the color library is exposing generally ```2 methods``` for each types of color.

These methods are following this pattern: ```get<Target>From<Source>```

- Target: The target color that you wish to get
- Source: The color source it can be an Xyz or an RGB

## Example

```c
#include <stdlib.h>
#include "lch.h"

Lch *lch = malloc(sizeof(Lch));
lch->l = 0.0;
lch->c = 0.0;
lch->h = 180.0;

Xyz *xyz = getXyzFromLch(lch)
```