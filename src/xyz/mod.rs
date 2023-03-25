use crate::rgb::{Rgb, FromRgb};
use super::util::PivotFloat;

pub mod xyy;
pub mod hlab;
pub mod lab;
pub mod luv;
pub mod lchuv;
pub mod lchlab;

// Constant

// Illuminent for D65 2°
const D65: [f64; 3] = [0.95047, 1.0, 1.08883];
const EPSILON: f64 = 0.008856;
const KAPPA: f64 = 903.3;

// For Std RGB
const X: [f64; 3] = [0.4124564, 0.3575761, 0.1804375];
const Y: [f64; 3] = [0.2126729, 0.7151522, 0.0721750];
const Z: [f64; 3] = [0.0193339, 0.1191920, 0.9503041];

// For Adobe RGB
const AX: [f64; 3] = [0.5767309, 0.1855540, 0.1881852];
const AY: [f64; 3] = [0.2973769, 0.6273491, 0.0752741];
const AZ: [f64; 3] = [0.0270343, 0.0706872, 0.9911085];

// srgb from Xyz to std RGB
const RX: [f64; 3] = [3.2404, -1.5371, -0.4985];
const RY: [f64; 3] = [-0.9692, 1.8760, 0.0415];
const RZ: [f64; 3] = [0.0556, -0.2040, 1.0572];

// srgb from Xyz to Adobe RGB
const ARX: [f64; 3] = [2.0413, -0.5649, -0.3446];
const ARY: [f64; 3] = [-0.9692, 1.8760, 0.0415];
const ARZ: [f64; 3] = [0.0134, -0.1183, 1.0154];

#[derive(Debug, Default, Clone, Copy)]
pub struct Xyz {
    x: f64,
    y: f64,
    z: f64
}

enum Kind {
    Adobe,
    Std
}

impl FromRgb<Kind> for Xyz {
    fn from_rgb(rgb: Rgb, kind: Kind) -> Self {
        let pivot = match kind {
            Kind::Std => rgb.pivot_rgb(),
            Kind::Adobe => rgb.pivot_adobe_rgb()
        };

        let (r, g, b) = (
            pivot[0],
            pivot[1],
            pivot[2]
        );

        match kind {
            Kind::Std => Xyz {
                x: X[0] * r + X[1] * g + X[2] * b,
                y: Y[0] * r + Y[1] * g + Y[2] * b,
                z: Z[0] * r + Z[1] * g + Z[2] * b
            },
            Kind::Adobe => Xyz {
                x: AX[0] * r + AX[1] * g + AX[2] * b,
                y: AY[0] * r + AY[1] * g + AY[2] * b,
                z: AZ[0] * r + AZ[1] * g + AZ[2] * b
            }
        }
    }
}

impl Xyz {
    /// Convert the XYZ into an RGB color based on the profile
    /// 
    /// # Arguments
    /// 
    /// * `xyz` - Xyz
    /// * `kind` - Kind
    fn as_rgb(&self, kind: Kind) -> Rgb {
        let (sr, sg, sb) = match kind {
            Kind::Std => {
                let sr = (self.x * RX[0] + self.y * RX[1] + self.z * RX[2]).unpivot_std();
                let sg = (self.x * RY[0] + self.y * RY[1] + self.z * RY[2]).unpivot_std();
                let sb = (self.x * RZ[0] + self.y * RZ[1] + self.z * RZ[2]).unpivot_std();

                (sr, sg, sb)
            },
            Kind::Adobe => {
                let sr = (self.x * ARX[0] + self.y * ARX[1] + self.z * ARX[2]).unpivot_argb();
                let sg = (self.x * ARY[0] + self.y * ARY[1] + self.z * ARY[2]).unpivot_argb();
                let sb = (self.x * ARZ[0] + self.y * ARZ[1] + self.z * ARZ[2]).unpivot_argb();

                (sr, sg, sb)
            }
        };

        Rgb {
            r: (sr * 255.0) as u8,
            g: (sg * 255.0) as u8,
            b: (sb * 255.0) as u8
        }
    }

    /// Check whether the xyz value is null
    fn is_null(&self) -> bool {
        if self.x == 0.0 && self.y == 0.0 && self.z == 0.0 {
            return true
        }

        false
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
            b: 95
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
            b: 95
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
            b: 95
        };

        let xyz = Xyz::from_rgb(rgb, Kind::Std);
        let generated_rgb = xyz.as_rgb(Kind::Std);

        assert_eq!(generated_rgb.r, 50);
        assert_eq!(generated_rgb.g, 9);
        assert_eq!(generated_rgb.b, 94);
    }

    #[test]
    fn expect_to_create_rgb_argb() {
        let rgb = Rgb {
            r: 50,
            g: 10,
            b: 95
        };

        let xyz = Xyz::from_rgb(rgb, Kind::Adobe);
        let generated_rgb = xyz.as_rgb(Kind::Adobe);

        assert_eq!(generated_rgb.r, 50);
        assert_eq!(generated_rgb.g, 9);
        assert_eq!(generated_rgb.b, 94);
    }
}
