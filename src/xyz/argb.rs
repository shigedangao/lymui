use super::{transfer::GammaCorrection, Xyz};
use crate::xyz::matrices::argb::{BB, GG, RR, XR, YG, ZB};
use crate::{rgb::Rgb, util::AsFloat};

/// Implementation of the aRGB colorspace. Based on the following links
///
/// @link https://en.wikipedia.org/wiki/Adobe_RGB_color_space#cite_note-AdobeRGBColorImagingEncoding-4#Specifications
/// @link http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
/// @link https://stackoverflow.com/a/40231268/7489243
///
/// /!\ The conversion is not perfect it's quite close based on the implementation above
#[derive(Debug, Clone, Copy)]
pub struct Argb {
    pub r: f64,
    pub g: f64,
    pub b: f64,
}

impl AsFloat for Argb {
    fn as_f64(&self) -> (f64, f64, f64) {
        (self.r, self.g, self.b)
    }
}

impl From<Xyz> for Argb {
    fn from(xyz: Xyz) -> Self {
        let r_lin = xyz.x * XR[0] + xyz.y * XR[1] + xyz.z * XR[2];
        let g_lin = xyz.x * YG[0] + xyz.y * YG[1] + xyz.z * YG[2];
        let b_lin = xyz.x * ZB[0] + xyz.y * ZB[1] + xyz.z * ZB[2];

        Argb {
            r: r_lin.compute_argb_gamma(),
            g: g_lin.compute_argb_gamma(),
            b: b_lin.compute_argb_gamma(),
        }
    }
}

impl From<Argb> for Xyz {
    fn from(argb: Argb) -> Self {
        let r_gamma = argb.r.compute_argb_gamma_expanded();
        let g_gamma = argb.g.compute_argb_gamma_expanded();
        let b_gamma = argb.b.compute_argb_gamma_expanded();

        Xyz {
            x: r_gamma * RR[0] + g_gamma * RR[1] + b_gamma * RR[2],
            y: r_gamma * GG[0] + g_gamma * GG[1] + b_gamma * GG[2],
            z: r_gamma * BB[0] + g_gamma * BB[1] + b_gamma * BB[2],
        }
    }
}

impl From<Rgb> for Argb {
    fn from(rgb: Rgb) -> Self {
        let (mut r, mut g, mut b) = rgb.as_f64();

        r /= 255_f64;
        g /= 255_f64;
        b /= 255_f64;

        Argb {
            r: r.compute_argb_gamma(),
            g: g.compute_argb_gamma(),
            b: b.compute_argb_gamma(),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_create_argb_from_xyz() {
        let xyz = Xyz {
            x: 0.95046,
            y: 1_f64,
            z: 1.08906,
        };

        let argb = Argb::from(xyz);
        assert_eq!(util::roundup(argb.r, 1000_f64), 1_f64);
        assert_eq!(util::roundup(argb.g, 1000_f64), 1_f64);
        assert_eq!(util::roundup(argb.b, 1000_f64), 1_f64);
    }

    #[test]
    fn expect_to_create_xyz_from_argb() {
        let argb = Argb {
            r: 1_f64,
            g: 1_f64,
            b: 1_f64,
        };

        let xyz = Xyz::from(argb);
        assert_eq!(util::roundup(xyz.x, 100000_f64), 0.95047);
        assert_eq!(util::roundup(xyz.y, 100000_f64), 1.0);
        assert_eq!(util::roundup(xyz.z, 100000_f64), 1.08883);
    }

    #[test]
    fn expect_to_convert() {
        let xyz = Xyz {
            x: 0.25,
            y: 0.40,
            z: 0.10,
        };

        let argb = Argb::from(xyz);
        dbg!(argb);
    }
}
