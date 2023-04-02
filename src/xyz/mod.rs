use super::util::PivotFloat;
use crate::rgb::{FromRgb, Rgb};

pub mod argb;
pub mod hcl;
pub mod hlab;
pub mod lab;
pub mod lchlab;
pub mod lchuv;
pub mod luv;
pub mod oklab;
pub mod oklch;
pub mod srgb;
pub mod xyy;

// Constant
// Illuminent for D65 2°
const D65: [f64; 3] = [0.95047, 1.0, 1.08883];
const EPSILON: f64 = 0.008856;
const KAPPA: f64 = 903.3;

// Matrix to convert from RGB to XYZ
const X: [f64; 3] = [0.4124564, 0.3575761, 0.1804375];
const Y: [f64; 3] = [0.2126729, 0.7151522, 0.0721750];
const Z: [f64; 3] = [0.0193339, 0.1191920, 0.9503041];

// Matrix to convert from RGB to XYZ with the adobe 1998 profile
const AX: [f64; 3] = [0.5767309, 0.1855540, 0.1881852];
const AY: [f64; 3] = [0.2973769, 0.6273491, 0.0752741];
const AZ: [f64; 3] = [0.0270343, 0.0706872, 0.9911085];

// srgb from Xyz to std RGB
pub(crate) const RX: [f64; 3] = [3.2404542, -1.5371385, -0.4985314];
pub(crate) const RY: [f64; 3] = [-0.9692660, 1.8760108, 0.0415560];
pub(crate) const RZ: [f64; 3] = [0.0556434, -0.2040259, 1.0572252];

// srgb from Xyz to Adobe RGB
const ARX: [f64; 3] = [2.0413690, -0.5649464, -0.3446944];
const ARY: [f64; 3] = [-0.9692660, 1.8760108, 0.0415560];
const ARZ: [f64; 3] = [0.0134474, -0.1183897, 1.0154096];

#[derive(Debug, Default, Clone, Copy)]
pub struct Xyz {
    pub x: f64,
    pub y: f64,
    pub z: f64,
}

pub enum Kind {
    Adobe,
    Std,
}

impl FromRgb<Kind> for Xyz {
    fn from_rgb(rgb: Rgb, kind: Kind) -> Self {
        let pivot = match kind {
            Kind::Std => rgb.pivot_rgb(),
            Kind::Adobe => rgb.pivot_adobe_rgb(),
        };

        let (r, g, b) = (pivot[0], pivot[1], pivot[2]);

        match kind {
            Kind::Std => Xyz {
                x: X[0] * r + X[1] * g + X[2] * b,
                y: Y[0] * r + Y[1] * g + Y[2] * b,
                z: Z[0] * r + Z[1] * g + Z[2] * b,
            },
            Kind::Adobe => Xyz {
                x: AX[0] * r + AX[1] * g + AX[2] * b,
                y: AY[0] * r + AY[1] * g + AY[2] * b,
                z: AZ[0] * r + AZ[1] * g + AZ[2] * b,
            },
        }
    }
}

impl Xyz {
    /// Convert the XYZ into an RGB color based on the profile
    ///
    /// # Arguments
    ///
    /// * `&self` - Xyz
    /// * `kind` - Kind
    pub fn as_rgb(&self, kind: Kind) -> Rgb {
        let (sr, sg, sb) = match kind {
            Kind::Std => {
                let sr = (self.x * RX[0] + self.y * RX[1] + self.z * RX[2]).unpivot_std();
                let sg = (self.x * RY[0] + self.y * RY[1] + self.z * RY[2]).unpivot_std();
                let sb = (self.x * RZ[0] + self.y * RZ[1] + self.z * RZ[2]).unpivot_std();

                (sr, sg, sb)
            }
            Kind::Adobe => {
                let sr = (self.x * ARX[0] + self.y * ARX[1] + self.z * ARX[2]).unpivot_argb();
                let sg = (self.x * ARY[0] + self.y * ARY[1] + self.z * ARY[2]).unpivot_argb();
                let sb = (self.x * ARZ[0] + self.y * ARZ[1] + self.z * ARZ[2]).unpivot_argb();

                (sr, sg, sb)
            }
        };

        Rgb {
            r: (sr * 255.0).round() as u8,
            g: (sg * 255.0).round() as u8,
            b: (sb * 255.0).round() as u8,
        }
    }

    /// Check whether the xyz value is null
    ///
    /// # Arguments
    ///
    /// * `&self` - &Xyz
    fn is_null(&self) -> bool {
        if self.x == 0.0 && self.y == 0.0 && self.z == 0.0 {
            return true;
        }

        false
    }

    /// Scale the XYZ value
    ///
    /// # Arguments
    ///
    /// * `&mut self` - Xyz
    pub fn scale(&mut self) {
        self.x *= 100_f64;
        self.y *= 100_f64;
        self.z *= 100_f64;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_compute_xyz_std() {
        let rgb = Rgb {
            r: 50,
            g: 10,
            b: 95,
        };

        let xyz = Xyz::from_rgb(rgb, Kind::Std);
        assert_eq!(xyz.x, 0.03488949569070142);
        assert_eq!(xyz.y, 0.017213474858538254);
        assert_eq!(xyz.z, 0.10972685952886765);
    }

    #[test]
    fn expect_to_compute_xyz_adobe() {
        let rgb = Rgb {
            r: 50,
            g: 10,
            b: 95,
        };

        let xyz = Xyz::from_rgb(rgb, Kind::Adobe);
        assert_eq!(xyz.x, 0.037632178651154785);
        assert_eq!(xyz.y, 0.01735228547582024);
        assert_eq!(xyz.z, 0.11380345919261227);
    }

    #[test]
    fn expect_to_create_rgb_std() {
        let rgb = Rgb {
            r: 50,
            g: 10,
            b: 95,
        };

        let xyz = Xyz::from_rgb(rgb, Kind::Std);
        let generated_rgb = xyz.as_rgb(Kind::Std);

        assert_eq!(generated_rgb.r, 50);
        assert_eq!(generated_rgb.g, 10);
        assert_eq!(generated_rgb.b, 95);
    }

    #[test]
    fn expect_to_create_rgb_argb() {
        let rgb = Rgb {
            r: 50,
            g: 10,
            b: 95,
        };

        let xyz = Xyz::from_rgb(rgb, Kind::Adobe);
        dbg!(&xyz);
        let generated_rgb = xyz.as_rgb(Kind::Adobe);

        assert_eq!(generated_rgb.r, 50);
        assert_eq!(generated_rgb.g, 10);
        assert_eq!(generated_rgb.b, 95);
    }

    #[test]
    fn expect_to_have_the_same_rgb_from_xyz() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255,
        };

        let xyz = Xyz::from_rgb(rgb, Kind::Std);
        let n_rgb = xyz.as_rgb(Kind::Adobe);

        assert_eq!(n_rgb.r, 255);
        assert_eq!(n_rgb.g, 255);
        assert_eq!(n_rgb.b, 255);
    }
}
