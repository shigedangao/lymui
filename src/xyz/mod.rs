use self::{argb::Argb, srgb::Srgb};
use crate::{
    rgb::{FromRgb, Rgb},
    util::AsFloat,
};
use matrices::xyz;
use transfer::GammaCorrection;

pub mod argb;
pub mod hcl;
pub mod hlab;
pub mod lab;
pub mod lchlab;
pub mod lchuv;
pub mod luv;
pub mod oklab;
pub mod oklch;
pub mod rec2020;
pub mod rec2100;
pub mod rec709;
pub mod srgb;
pub mod xyy;

mod matrices;
mod transfer;

// Constant
// Illuminent for D65 2°
const D65: [f64; 3] = [0.95047, 1.0, 1.08883];
const EPSILON: f64 = 0.008856;
const KAPPA: f64 = 903.3;

#[derive(Debug, Default, Clone, Copy)]
pub struct Xyz {
    pub x: f64,
    pub y: f64,
    pub z: f64,
}

/// Xyz support different type of whitepoint. Currently we support
/// - D50
/// - D65
/// - Adobe
///
/// All of these matrices are taken from the website linked below
/// @link http://www.brucelindbloom.com/index.html?Eqn_RGB_to_XYZ.html
pub enum Kind {
    D50,
    D65,
    Adobe,
}

impl FromRgb<Kind> for Xyz {
    fn from_rgb(rgb: Rgb, kind: Kind) -> Self {
        match kind {
            Kind::D65 => {
                Xyz::compute_xyz_from_matrix((xyz::X65, xyz::Y65, xyz::Z65), Srgb::from(rgb))
            }
            Kind::D50 => {
                Xyz::compute_xyz_from_matrix((xyz::X50, xyz::Y50, xyz::Z50), Srgb::from(rgb))
            }
            Kind::Adobe => {
                Xyz::compute_xyz_from_matrix((xyz::AX, xyz::AY, xyz::AZ), Argb::from(rgb))
            }
        }
    }
}

impl Xyz {
    /// Compute the xyz from a set of matrices
    ///
    /// # Arguments
    ///
    /// * `matrices` - ([f64; 3], [f64; 3], [f64; 3])
    /// * `c` - (f64, f64, f64)
    fn compute_xyz_from_matrix<T: AsFloat>(
        matrices: ([f64; 3], [f64; 3], [f64; 3]),
        rgb_compat: T,
    ) -> Self {
        let (r, g, b) = rgb_compat.as_f64();
        let (xm, ym, zm) = matrices;

        let x = xm[0] * r + xm[1] * g + xm[2] * b;
        let y = ym[0] * r + ym[1] * g + ym[2] * b;
        let z = zm[0] * r + zm[1] * g + zm[2] * b;

        Xyz { x, y, z }
    }

    /// Compute the RGB from an XYZ matrix
    ///
    /// # Arguments
    ///
    /// * `&self` - Xyz
    /// * `matrices` - ([f64; 3], [f64; 3], [f64; 3])
    fn compute_rgb_from_xyz_matrix(
        &self,
        matrices: ([f64; 3], [f64; 3], [f64; 3]),
    ) -> (f64, f64, f64) {
        let (rx, ry, rz) = matrices;

        (
            (self.x * rx[0] + self.y * rx[1] + self.z * rx[2]),
            (self.x * ry[0] + self.y * ry[1] + self.z * ry[2]),
            (self.x * rz[0] + self.y * rz[1] + self.z * rz[2]),
        )
    }

    /// Convert the XYZ into an RGB color based on the profile
    ///
    /// # Arguments
    ///
    /// * `&self` - Xyz
    /// * `kind` - Kind
    pub fn as_rgb(&self, kind: Kind) -> Rgb {
        let (sr, sg, sb) = match kind {
            Kind::D65 => {
                let (sr, sg, sb) =
                    self.compute_rgb_from_xyz_matrix((xyz::RX65, xyz::RY65, xyz::RZ65));

                (
                    sr.apply_srgb_gamma_correction(),
                    sg.apply_srgb_gamma_correction(),
                    sb.apply_srgb_gamma_correction(),
                )
            }
            Kind::D50 => {
                let (sr, sg, sb) =
                    self.compute_rgb_from_xyz_matrix((xyz::RX50, xyz::RY50, xyz::RZ50));

                (
                    sr.apply_srgb_gamma_correction(),
                    sg.apply_srgb_gamma_correction(),
                    sb.apply_srgb_gamma_correction(),
                )
            }
            Kind::Adobe => {
                let (sr, sg, sb) = self.compute_rgb_from_xyz_matrix((xyz::ARX, xyz::ARY, xyz::ARZ));

                (
                    sr.compute_argb_gamma_expanded(),
                    sg.compute_argb_gamma_expanded(),
                    sb.compute_argb_gamma_expanded(),
                )
            }
        };

        Rgb {
            r: (sr * 255.0).round() as u8,
            g: (sg * 255.0).round() as u8,
            b: (sb * 255.0).round() as u8,
        }
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
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_compute_xyz_std() {
        let rgb = Rgb {
            r: 50,
            g: 10,
            b: 95,
        };

        let xyz = Xyz::from_rgb(rgb, Kind::D65);
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

        let xyz = Xyz::from_rgb(rgb, Kind::D65);
        let generated_rgb = xyz.as_rgb(Kind::D65);

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

        let xyz = Xyz::from_rgb(rgb, Kind::D65);
        let n_rgb = xyz.as_rgb(Kind::Adobe);

        assert_eq!(n_rgb.r, 255);
        assert_eq!(n_rgb.g, 255);
        assert_eq!(n_rgb.b, 255);
    }

    #[test]
    fn expect_to_compute_rgb_to_xyz_d50() {
        let rgb = Rgb {
            r: 50,
            g: 10,
            b: 95,
        };

        let xyz = Xyz::from_rgb(rgb, Kind::D50);
        assert_eq!(util::roundup(xyz.x, 1000000_f64), 0.031451);
        assert_eq!(util::roundup(xyz.y, 1000000_f64), 0.01621);
        assert_eq!(util::roundup(xyz.z, 1000000_f64), 0.082466);
    }

    #[test]
    fn expect_to_compute_rgb_from_xyz_d50() {
        let xyz = Xyz {
            x: 0.03145128799049186,
            y: 0.016209648492913314,
            z: 0.08246580883446344,
        };

        let rgb = xyz.as_rgb(Kind::D50);
        assert_eq!(rgb.r, 50);
        assert_eq!(rgb.g, 10);
        assert_eq!(rgb.b, 95);
    }
}
