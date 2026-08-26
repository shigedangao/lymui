use crate::rgb::{FromRgb, Rgb};
use crate::xyz::{Kind, Xyz};
use ops::SliceOps;
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
pub mod ictcp;
pub mod ops;
pub mod rgb;
pub mod tone;
pub mod tsl;
pub mod util;
pub mod xyz;
pub mod ycbcr;
pub mod ycocg;
pub mod yuv;

// For re-export
pub mod prelude;

/// Converts a type T that can be converted into an RGB into a type that can be converted into an RGB
///
/// # Arguments
///
/// * `c` - T
///
/// # Returns
///
/// * `E` - E
///
/// # Examples
///
/// ```
/// use lymui::{prelude::*, convert_rgb_subcolor};
///
/// let rgb = Rgb {
///     r: 255,
///     g: 255,
///     b: 255,
/// };
///
/// let hex = convert_rgb_subcolor::<Rgb, Hex>(rgb);
/// assert_eq!(hex.0, "#ffffff");
/// ```
pub fn convert_rgb_subcolor<T, E>(c: T) -> E
where
    T: Into<Rgb>,
    E: From<Rgb>,
{
    let rgb = c.into();

    E::from(rgb)
}

/// Converts a type T that can be converted into an Xyz into a type that can be converted into an Xyz
///
/// # Arguments
///
/// * `c` - T
///
/// # Returns
///
/// * `E` - E
///
/// /// # Examples
///
/// ```
/// use lymui::{prelude::*, convert_xyz_subcolor};
///
/// let xyz = Xyz {
///     x: 0.3,
///     y: 0.5,
///     z: 0.7,
/// };
///
/// let luv = convert_xyz_subcolor::<Xyz, Luv>(xyz);
/// assert_eq!(luv.l, 76.06926101415557);
/// assert_eq!(luv.u, -75.77716622801219);
/// assert_eq!(luv.v, -13.63777539220114);
/// ```
pub fn convert_xyz_subcolor<T, E>(c: T) -> E
where
    T: Into<Xyz>,
    E: From<Xyz>,
{
    let xyz = c.into();

    E::from(xyz)
}

/// Allows to convert a type T that can be transform into an RGB into a type that can be convert into Xyz
/// This allows you to convert for e.g: a cymk -> sRGB without having to convert it back to rgb then xyz
///
/// # Arguments
///
/// * `f` - T
/// * `k` - Option<Kind>
///
/// # Examples
///
/// ```
/// use lymui::{prelude::*, convert_rgb_subcolor, from_rgb_space_to_xyz_space};
///
/// let rgb = Rgb {
///     r: 50,
///     g: 10,
///     b: 95,
/// };
///
/// let xyz = from_rgb_space_to_xyz_space::<Rgb, Xyz>(rgb, None);
/// assert_eq!(xyz.x, 0.03488949569070142);
/// assert_eq!(xyz.y, 0.017213474858538254);
/// assert_eq!(xyz.z, 0.10972685952886765);
/// ```
pub fn from_rgb_space_to_xyz_space<T, E>(f: T, k: Option<Kind>) -> E
where
    T: Into<Rgb>,
    E: From<Xyz>,
{
    let xyz = Xyz::from_rgb(f.into(), k.unwrap_or(Kind::D65));

    E::from(xyz)
}

/// Allows to convert a type T whichc can be convert into an Xyz to an RGB comptabile type
/// This allows you to convert for e.g: a Luv -> Hex without having to convert to Xyz then to RGB to the type that you want
///
/// # Arguments
///
/// * `c` - T
/// * `k` - Option<Kind>
///
/// # Examples
///
/// ```
/// use lymui::{prelude::*, convert_rgb_subcolor, from_rgb_space_to_xyz_space, from_xyz_space_to_rgb_space};
///
/// let rgb = Rgb {
///     r: 50,
///     g: 10,
///     b: 95,
/// };
///
/// let xyz = from_rgb_space_to_xyz_space::<Rgb, Xyz>(rgb, None);
/// let rgb2 = from_xyz_space_to_rgb_space::<Xyz, Rgb>(xyz, None);
/// assert_eq!(rgb2.r, 50);
/// assert_eq!(rgb2.g, 10);
/// assert_eq!(rgb2.b, 95);
/// ```
pub fn from_xyz_space_to_rgb_space<T, E>(c: T, k: Option<Kind>) -> E
where
    T: Into<Xyz>,
    E: From<Rgb>,
{
    let rgb = c.into().as_rgb(k.unwrap_or(Kind::D65));

    E::from(rgb)
}

/// Create color from a vector of K where K should be a number
///
/// # Arguments
///
/// * `vec` - [K; S]
pub fn create_color_from_slice<K, T, const S: usize>(slice: &[K; S]) -> T
where
    K: Add,
    T: SliceOps<S, Item = K>,
{
    T::from_slice(slice)
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

        let res: Srgb = from_rgb_space_to_xyz_space(cymk, None);
        assert!(res.r.is_normal());
    }

    #[test]
    fn expect_to_convert_luv_to_hex() {
        let luv = Luv {
            l: 100.0,
            u: 0.0,
            v: -0.0,
        };

        let res: Hex = from_xyz_space_to_rgb_space(luv, None);
        assert_eq!(res.0, "#ffffff");
    }

    #[test]
    fn expect_to_create_rgb_from_vec() {
        let rgb_vec = [1, 2, 3];

        let rgb: Rgb = create_color_from_slice(&rgb_vec);
        assert_eq!(rgb.r, 1);
        assert_eq!(rgb.g, 2);
        assert_eq!(rgb.b, 3);
    }

    #[test]
    fn expect_to_convert_rgb_to_cymk() {
        let rgb = Rgb {
            r: 100,
            g: 20,
            b: 194,
        };
        let cymk: Cymk = convert_rgb_subcolor(rgb);

        dbg!(cymk);
    }
}
