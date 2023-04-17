use util::FromVec;

use crate::rgb::{FromRgb, Rgb};
use crate::xyz::{Kind, Xyz};
use std::ops::Add;

pub mod ansi;
pub mod cymk;
pub mod error;
pub mod generator;
pub mod grayscale;
pub mod hex;
pub mod hsl;
pub mod hsv;
pub mod hue;
pub mod hwb;
pub mod rgb;
pub mod util;
pub mod xyz;
pub mod ycbcr;
pub mod yuv;

/// Allows to convert a type T that can be transform into an RGB into a type that can be convert into Xyz
/// This allows you to convert for e.g: a cymk -> sRGB without having to convert it back to rgb then xyz
///
/// # Arguments
///
/// * `f` - T
/// * `k` - Option<Kind>
pub fn from_rgb_compatible_to_xyz_subtype<T, E>(f: T, k: Option<Kind>) -> E
where
    T: Into<Rgb>,
    E: From<Xyz>,
{
    let rgb: Rgb = f.into();
    let xyz = Xyz::from_rgb(rgb, k.unwrap_or(Kind::D65));

    E::from(xyz)
}

/// Allows to convert a type T whichc can be convert into an Xyz to an RGB comptabile type
/// This allows you to convert for e.g: a Luv -> Hex without having to convert to Xyz then to RGB to the type that you want
///
/// # Arguments
///
/// * `c` - T
/// * `k` - Option<Kind>
pub fn from_xyz_compatible_type_to_rgb_subtype<T, E>(c: T, k: Option<Kind>) -> E
where
    T: Into<Xyz>,
    E: From<Rgb>,
{
    let xyz: Xyz = c.into();
    let rgb = xyz.as_rgb(k.unwrap_or(Kind::D65));

    E::from(rgb)
}

/// Create color from a vector of K where K should be a number
///
/// # Arguments
///
/// * `vec` - Vec<K>
pub fn create_color_from_vec<K, T>(vec: Vec<K>) -> T
where
    K: Add,
    T: FromVec<K>,
{
    T::from_vec(vec)
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::cymk::Cymk;
    use crate::hex::Hex;
    use crate::xyz::{luv::Luv, srgb::Srgb};

    #[test]
    fn expect_to_convert_cymk_to_srgb() {
        let cymk = Cymk {
            c: 0.973,
            y: 0.0,
            m: 0.949,
            k: 0.223,
        };

        let res: Srgb = from_rgb_compatible_to_xyz_subtype(cymk, None);
        assert!(res.r.is_normal());
    }

    #[test]
    fn expect_to_convert_luv_to_hex() {
        let luv = Luv {
            l: 100.0,
            u: 0.0,
            v: -0.0,
        };

        let res: Hex = from_xyz_compatible_type_to_rgb_subtype(luv, None);
        assert_eq!(res, "#ffffff");
    }

    #[test]
    fn expect_to_create_rgb_from_vec() {
        let rgb_vec = vec![1, 2, 3];

        let rgb: Rgb = create_color_from_vec(rgb_vec);
        assert_eq!(rgb.r, 1);
        assert_eq!(rgb.g, 2);
        assert_eq!(rgb.b, 3);
    }
}
