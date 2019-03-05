## Lab APIs

The Lab API allow you to create an Lab color from an Xyz based color. The Lab APIs allow you ton convert back and forth the value

## Xyz to Lab

Use the method **getLabFromXyz**. This method return an Lab struct or NULL

### Error handling

This method will return NULL when:

- Lab struct can't be allocated

This method take as a param an Lab struct with an **error** parameter like so

```c
lab->error = <string>
```

### Parameter

- Xyz pointer struct

### Usage Example

```c
#include "xyz.h"
#include "lab.h"

Xyz *xyz = malloc(sizeof(Xyz));
xyz->x = 0.950470;
xyz->y = 1.0;
xyz->z = 1.088830;
    
Lab *lab  = getLabFromXyz(xyz);

// xyz will not be freed (so that you can reuse this struct)
free(xyz);
```

It return the Lab struct which you can access the property like the example below

```c
double l = lab->l;
double a = lab->a;
double b = lab->b;
char *error = lab->error;
```

## Lab to Xyz

Use the method **getXyzFromLab**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Xyz struct can't be allocated

The method *can return an Xyz struct containing an error property*

- Lab property not passed

### Parameter

- Lab pointer struct

### Usage Example

```c
#include "xyz.h"
#include "lab.h"

Lab *Lab = malloc(sizeof(Lab));
lab->l = 100.0;
lab->a = 0.0;
lab->b = 0.0;

// lab is being freed automatically
Xyz *xyz = getXyzFromLab(Lab);
```

The method will return an Xyz struct which you can access it's property like the example below

```c
double x = xyz->x;
double y = xyz->y;
double z = xyz->z;
char *error = xyz->error;
```

## Xyz to Hunter Lab

Use the method **getHunterLabFromXyz**. Refer to the Xyz to Lab section for usage the process is the same.