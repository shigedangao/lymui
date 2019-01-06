## Argb APIs (adobe rgb from xyz)

The Argb API allow you to create an Argb color from an Xyz based color. The Argb APIs allow you ton convert back and forth the value

## Xyz to Argb

Use the method **getARgbFromXyz**. This method return an Argb struct or NULL

### Error handling

This method will return NULL when:

- Argb struct can't be allocated

This method take as a param an Argb struct with an **error** parameter like so

```c
Argb->error = <string>
```

### Parameter

- Xyz pointer struct

### Usage Example

```c
#include "xyz.h"
#include "argb.h"

Xyz *xyz = malloc(sizeof(Xyz));
xyz->x = 0.950470;
xyz->y = 1.0;
xyz->z = 1.088830;
    
Argb *argb = getArgbFromXyz(xyz);

// xyz will not be freed (so that you can reuse this struct)
free(xyz);
```

It return the Argb struct which you can access the property like the example below

```c
double r = argb->r;
double g = argb->g;
double b = argb->b;
char *error = Argb->error;
```