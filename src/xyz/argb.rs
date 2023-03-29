use super::Xyz;

// Constant
// From Xyz to aRGB as defined on these specs
//
// @link https://en.wikipedia.org/wiki/Adobe_RGB_color_space#cite_note-AdobeRGBColorImagingEncoding-4#Specifications
// @link https://stackoverflow.com/questions/40017741/mathematical-conversion-srgb-and-adobergb
const XR: [f64; 3] = [2.041588, -0.565007, -0.344731];
const YG: [f64; 3] = [-0.969244, 1.875968, 0.041555];
const ZB: [f64; 3] = [0.013444, -0.118362, 1.015175];

// Constant provided by
// @link http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
const RR: [f64; 3] = [0.5767309, 0.1855540, 0.1881852];
const GG: [f64; 3] = [0.2973769, 0.6273491, 0.0752741];
const BB: [f64; 3] = [0.0270343, 0.0706872, 0.9911085];

/// Implementation of the aRGB colorspace. Based on the following links
///
/// @link https://en.wikipedia.org/wiki/Adobe_RGB_color_space#cite_note-AdobeRGBColorImagingEncoding-4#Specifications
/// @link http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
///
/// /!\ The conversion is not perfect it's quite close based on the implementation above
#[derive(Debug, Clone, Copy)]
pub struct Argb {
    pub r: f64,
    pub g: f64,
    pub b: f64,
}

impl Argb {
    fn linear_rgb(c: f64) -> f64 {
        if c <= 0_f64 {
            0_f64
        } else {
            c.powf(2.19921875)
        }
    }

    fn gamma_rgb(c: f64) -> f64 {
        if c <= 0_f64 {
            0_f64
        } else {
            c.powf(1_f64 / 2.19921875)
        }
    }
}

impl From<Xyz> for Argb {
    fn from(xyz: Xyz) -> Self {
        let r_lin = xyz.x * XR[0] + xyz.y * XR[1] + xyz.z * XR[2];
        let g_lin = xyz.x * YG[0] + xyz.y * YG[1] + xyz.z * YG[2];
        let b_lin = xyz.x * ZB[0] + xyz.y * ZB[1] + xyz.z * ZB[2];

        Argb {
            r: Argb::linear_rgb(r_lin),
            g: Argb::linear_rgb(g_lin),
            b: Argb::linear_rgb(b_lin),
        }
    }
}

impl From<Argb> for Xyz {
    fn from(argb: Argb) -> Self {
        let r_gamma = Argb::gamma_rgb(argb.r);
        let g_gamma = Argb::gamma_rgb(argb.g);
        let b_gamma = Argb::gamma_rgb(argb.b);

        Xyz {
            x: r_gamma * RR[0] + g_gamma * RR[1] + b_gamma * RR[2],
            y: r_gamma * GG[0] + g_gamma * GG[1] + b_gamma * GG[2],
            z: r_gamma * BB[0] + g_gamma * BB[1] + b_gamma * BB[2],
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
}
