## Hex APIs

The Hex API allow you to create an HEX from an RGB struct and to convert it back to an RGB from an HEX

## RGB to Hex

Use the method: **getHexFromRGB**. This method return a char array or NULL

This method will return NULL when these conditions are meet:

- Unable to convert uint to hex
- Unable to allocate hex char array

### Example

```c
uint8_t colors = {5, 10, 95};
Rgb *rgb = makeRGB(colors, sizeof(colors));

if (rgb == NULL) {
  // ... do something
}

char *hex = getHexFromRGB(rgb);

// should print "hex is equal to 050a5f"
printf("hex is equal to %s", hex);
```

## Hex to RGB

Use the method **getRGBFromHex** to get the RGB

This method will either return the RGB struct or NULL. Below are the condition where the method can return NULL:

- Rgb struct can't be allocated
- Hex is NULL (method param)

### Example

```c
char *hex = {"050a5f"};
Rgb *rgb = getRGBFromHex(hex);

// RGB will contain R, G, B or an error message
// can be access like so

rgb->r;
rgb->g;
rgb->b;
rgb->error;
```

