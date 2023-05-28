use super::{
    matrices::xyz::{RX65, RY65, RZ65, X65, Y65, Z65},
    transfer::GammaCorrection,
    Xyz,
};
use crate::{
    rgb::Rgb,
    util::{AsFloat, AsVec, FromVec},
};

#[cfg(feature = "js")]
use crate::js::prelude::*;

/// Implementation of the sRGB colorspace.
/// The foruma can be found on the link below
///
/// @link https://en.wikipedia.org/wiki/SRGB#:~:text=in%20these%20coefficients).-,From%20CIE%20XYZ%20to%20sRGB,when%20using%20specified%20white%20points).
/// @link http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_RGB.html
/// @link https://www.oceanopticsbook.info/view/photometry-and-visibility/from-xyz-to-rgb
#[cfg_attr(feature = "js", derive(FromJsObj))]
#[derive(Debug, Clone, Copy)]
pub struct Srgb {
    pub r: f64,
    pub g: f64,
    pub b: f64,
}

impl AsVec for Srgb {
    type Item = f64;

    fn as_vec(&self) -> Vec<Self::Item> {
        vec![self.r, self.g, self.b]
    }
}

impl FromVec<f64> for Srgb {
    fn from_vec(vec: Vec<f64>) -> Self {
        Srgb {
            r: vec.first().copied().unwrap_or_default(),
            g: vec.get(1).copied().unwrap_or_default(),
            b: vec.last().copied().unwrap_or_default(),
        }
    }
}

impl AsFloat for Srgb {
    fn as_f64(&self) -> (f64, f64, f64) {
        (self.r, self.g, self.b)
    }
}

impl Srgb {
    /// Transform the non linear sRGB into a linear RGB
    ///
    /// # Arguments
    ///
    /// * `&mut self` - Self
    pub fn as_linear(&mut self) {
        self.r = self.r.powf(2.2);
        self.g = self.g.powf(2.2);
        self.b = self.b.powf(2.2);
    }

    /// Transform a linear sRGB into a non linear sRGB
    ///
    /// # Arguments
    ///
    /// * `&mut self` - Self
    pub fn as_non_linear(&mut self) {
        self.r = self.r.powf(1_f64 / 2.2);
        self.g = self.g.powf(1_f64 / 2.2);
        self.b = self.b.powf(1_f64 / 2.2);
    }
}

impl From<Xyz> for Srgb {
    fn from(xyz: Xyz) -> Self {
        let r = (xyz.x * RX65[0] + xyz.y * RX65[1] + xyz.z * RX65[2]).apply_srgb_gamma_correction();
        let g = (xyz.x * RY65[0] + xyz.y * RY65[1] + xyz.z * RY65[2]).apply_srgb_gamma_correction();
        let b = (xyz.x * RZ65[0] + xyz.y * RZ65[1] + xyz.z * RZ65[2]).apply_srgb_gamma_correction();

        Srgb { r, g, b }
    }
}

impl From<Srgb> for Xyz {
    fn from(sr: Srgb) -> Self {
        let r = sr.r.compute_srgb_gamma_expanded();
        let g = sr.g.compute_srgb_gamma_expanded();
        let b = sr.b.compute_srgb_gamma_expanded();

        Xyz {
            x: r * X65[0] + g * X65[1] + b * X65[2],
            y: r * Y65[0] + g * Y65[1] + b * Y65[2],
            z: r * Z65[0] + g * Z65[1] + b * Z65[2],
        }
    }
}

impl From<Rgb> for Srgb {
    fn from(rgb: Rgb) -> Self {
        let (mut r, mut g, mut b) = rgb.as_f64();
        r /= 255_f64;
        g /= 255_f64;
        b /= 255_f64;

        Srgb {
            r: r.compute_srgb_gamma_expanded(),
            g: g.compute_srgb_gamma_expanded(),
            b: b.compute_srgb_gamma_expanded(),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::rgb::{FromRgb, Rgb};
    use crate::util;
    use crate::xyz::Kind;

    #[test]
    fn expect_to_compute_srgb() {
        let rgb = Rgb {
            r: 50,
            g: 10,
            b: 95,
        };

        let xyz = Xyz::from_rgb(rgb, Kind::D65);

        let srgb = Srgb::from(xyz);
        assert_eq!(util::roundup(srgb.r, 1000.0), 0.196);
        assert_eq!(util::roundup(srgb.g, 1000.0), 0.039);
        assert_eq!(util::roundup(srgb.b, 1000.0), 0.373);
    }

    #[test]
    fn expect_to_compute_black_srgb() {
        let rgb = Rgb { r: 0, g: 0, b: 0 };

        let xyz = Xyz::from_rgb(rgb, Kind::D65);

        let srgb = Srgb::from(xyz);
        assert_eq!(srgb.r, 0.0);
        assert_eq!(srgb.g, 0.0);
        assert_eq!(srgb.b, 0.0);
    }

    #[test]
    fn expect_to_compute_white_srgb() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255,
        };

        let xyz = Xyz::from_rgb(rgb, Kind::D65);

        let srgb = Srgb::from(xyz);
        assert_eq!(util::roundup(srgb.r, 1000.0), 1.0);
        assert_eq!(util::roundup(srgb.g, 1000.0), 1.0);
        assert_eq!(util::roundup(srgb.b, 1000.0), 1.0);
    }

    #[test]
    fn expect_to_create_xyz_from_srgb() {
        let srgb = Srgb {
            r: 0.19608,
            g: 0.03922,
            b: 0.37255,
        };

        let xyz = Xyz::from(srgb);
        assert_eq!(util::roundup(xyz.x, 1000.0), 0.035);
        assert_eq!(util::roundup(xyz.y, 1000.0), 0.017);
        assert_eq!(util::roundup(xyz.z, 1000.0), 0.110);
    }

    #[test]
    fn expect_to_compute_srgb_from_rgb() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255,
        };

        let srgb = Srgb::from(rgb);
        dbg!(srgb);
    }
}
