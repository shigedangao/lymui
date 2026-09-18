<div align="center">
  <img src="assets/logo.svg" alt="lymui" width="120" />
  <h1>Lymui 🌈</h1>
</div>

Lymui is a lightweight, dependency-free color library for Rust that converts RGB into 30+ other color spaces (see the full list below).

### Supported colors

| Color         | Supported |
|---------------|-----------|
| Rgb           |   ✅      |
| Ansi          |   ✅      |
| Cymk          |   ✅      |
| Grayscale     |   ✅      |
| Hex           |   ✅      |
| Hsl           |   ✅      |
| Hue           |   ✅      |
| Hwb           |   ✅      |
| Ycbcr         |   ✅      |
| Yuv           |   ✅      |
| Xyz           |   ✅      |
| Adobe RGB     |   ✅      |
| sRGB          |   ✅      |
| Hcl           |   ✅      |
| Hunter lab    |   ✅      |
| Cie Lab       |   ✅      |
| Lch Lab       |   ✅      |
| Luv           |   ✅      |
| Oklab         |   ✅      |
| Oklach        |   ✅      |
| rec.709       |   ✅      |
| rec.2020      |   ✅      |
| rec.2100 (PQ) |   ✅      |
| Xyy           |   ✅      |
| Tone          |   ✅      |
| Ycocg         |   ✅      |
| Ictcp         |   ✅      |
| Tsl           |   ✅      |
| Aces          |   ✅      |
| Ydbdr         |   ✅      |
| Yiq           |   ✅      |

### Usage

Add lymui to your `Cargo.toml`:

```toml
[dependencies]
lymui = "0.2.8" (not yet released)
```

Every conversion starts from the `Rgb` type. Color spaces fall into two families:

- **RGB-based** (`Hex`, `Hsl`, `Cymk`, `Ansi`, …) — convert directly with the `From` trait.
- **XYZ-based** (`Lab`, `Luv`, `OkLab`, `Srgb`, `Rec2020`, …) — derived from `Xyz`, which needs a lumens `Kind` (`D65`, `D50` or `D75`).

```rust
use lymui::{prelude::*, from_rgb_space_to_xyz_space, rgb::FromRgb, xyz::Kind};

fn main() {
    let rgb = Rgb { r: 255, g: 255, b: 255 };

    // RGB-based color: use the `From` trait directly.
    let hex = Hex::from(rgb.clone());
    assert_eq!(hex.0, "#ffffff");

    // XYZ-based color: pick a lumens `Kind`.
    let xyz = Xyz::from_rgb(rgb.clone(), Kind::D65);

    // Or go straight from RGB to any XYZ-based space in a single call.
    // Pass `None` to default to D65, or `Some(Kind::D50)` to choose.
    let luv: Luv = from_rgb_space_to_xyz_space(rgb, None);
}
```

### Examples

An example is available in the example folder. You can run it by using the command below

```sh
cargo run --example example
```
