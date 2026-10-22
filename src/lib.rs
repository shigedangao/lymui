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
pub mod ydbdr;
pub mod yiq;
pub mod yuv;

// For re-export
pub mod prelude;

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
/// use lymui::{prelude::*, from_rgb_space_to_xyz_space};
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
/// use lymui::{prelude::*, from_rgb_space_to_xyz_space, from_xyz_space_to_rgb_space};
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

/// Convert color from same colorspace
///
/// # Arguments
///
/// * `input_color` - T
///
///
/// # Examples
///
/// ```
/// use lymui::{prelude::*, convert_color_from_same_colorspace};
///
/// let rgb = Rgb {
///     r: 100,
///     g: 20,
///     b: 194,
/// };
///
/// let cymk: Cymk = convert_color_from_same_colorspace(rgb);
/// ```
pub fn convert_color_from_same_colorspace<T, O>(input_color: T) -> O
where
    O: From<T>,
{
    O::from(input_color)
}

/// Create color from a vector of K where K should be a number
///
/// * `K` -> The type of that the slice is passed
/// * `CS` -> The colorspace that is being passed to the slice
/// * `T` -> The type of colorspace that can be used to perform the conversion (depending on what's being supported by the From trait)
/// * `E` -> The colorspace type output that you want
/// * `S` -> The size of the slice
///
/// # Arguments
///
/// * `slice` - [K; S]
///
/// # Examples
///
/// ```
/// use lymui::{prelude::*, convert_color_from_slice};
///
/// let hsl_slice = [210., 50., 0.8];
/// let hwb = convert_color_from_slice::<_, Rgb, Hsl, Hwb, _>(&hsl_slice);
///
/// dbg!(hwb);
/// ```
pub fn convert_color_from_slice<K, CS, T, E, const S: usize>(slice: &[K; S]) -> E
where
    K: Add,
    T: SliceOps<S, Item = K> + From<CS>,
    CS: From<T>,
    E: From<CS>,
{
    let input_color = T::from_slice(slice);
    let converted_colorspace_color = CS::from(input_color);

    E::from(converted_colorspace_color)
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::cymk::Cymk;
    use crate::hex::Hex;
    use crate::hsl::Hsl;
    use crate::hwb::Hwb;
    use crate::xyz::{luv::Luv, srgb::Srgb};

    #[test]
    fn expect_to_convert_color() {
        let rgb = Rgb { r: 6, g: 11, b: 96 };
        let hex: Hex = convert_color_from_same_colorspace(rgb);

        assert_eq!(hex.0, "#060b60");
    }

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

        let hsl = convert_color_from_slice::<_, Rgb, Rgb, Hsl, _>(&rgb_vec);
        util::assert_approx!(hsl.h, 210., 1e-1);
        util::assert_approx!(hsl.s, 50., 1e-1);
        util::assert_approx!(hsl.l, 0.78, 1e-2);
    }

    #[test]
    fn expect_to_convert_hsl_to_hwb() {
        let hsl_slice = [210., 50., 0.8];

        let hwb = convert_color_from_slice::<_, Rgb, Hsl, Hwb, _>(&hsl_slice);

        util::assert_approx!(hwb.h, 210., 1e-4);
        util::assert_approx!(hwb.w, 0.39, 1e-2);
        util::assert_approx!(hwb.b, 98.82, 1e-2);
    }

    #[test]
    fn expect_to_convert_rgb_to_cymk() {
        let rgb = Rgb {
            r: 100,
            g: 20,
            b: 194,
        };
        let cymk: Cymk = convert_color_from_same_colorspace(rgb);

        util::assert_approx!(cymk.c, 0.4845, 1e-4);
        util::assert_approx!(cymk.y, 0.0, 1e-4);
        util::assert_approx!(cymk.m, 0.8969, 1e-4);
        util::assert_approx!(cymk.k, 0.2392, 1e-4);
    }
}
