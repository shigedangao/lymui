use super::{
    Xyz,
    matrices::xyz::{RX65, RY65, RZ65, X65, Y65, Z65},
    transfer::GammaCorrection,
};
use crate::ops::SliceOps;

/// Rec709 is an implementation of the Rec.709 colorspace
///
/// @link <https://en.wikipedia.org/wiki/Rec._709>
/// @link <https://agraphicsguynotes.com/posts/basic_color_science_for_graphcis_engineer/#rec-709>
#[derive(Debug, Clone, Copy)]
pub struct Rec709 {
    pub r: f64,
    pub g: f64,
    pub b: f64,
}

impl SliceOps<3> for Rec709 {
    type Item = f64;

    fn as_slice(&self) -> [Self::Item; 3] {
        [self.r, self.g, self.b]
    }

    fn to_vec(&self) -> Vec<Self::Item> {
        self.as_slice().to_vec()
    }

    fn from_slice(slice: &[Self::Item; 3]) -> Self {
        Rec709 {
            r: slice[0],
            g: slice[1],
            b: slice[2],
        }
    }
}

impl From<Xyz> for Rec709 {
    fn from(xyz: Xyz) -> Self {
        let r =
            (xyz.x * RX65[0] + xyz.y * RX65[1] + xyz.z * RX65[2]).compute_rec709_gamma_correction();
        let g =
            (xyz.x * RY65[0] + xyz.y * RY65[1] + xyz.z * RY65[2]).compute_rec709_gamma_correction();
        let b =
            (xyz.x * RZ65[0] + xyz.y * RZ65[1] + xyz.z * RZ65[2]).compute_rec709_gamma_correction();

        Rec709 { r, g, b }
    }
}

impl From<Rec709> for Xyz {
    fn from(rec: Rec709) -> Self {
        let r = rec.r.compute_rec709_gamma_expanded();
        let g = rec.g.compute_rec709_gamma_expanded();
        let b = rec.b.compute_rec709_gamma_expanded();

        Xyz {
            x: r * X65[0] + g * X65[1] + b * X65[2],
            y: r * Y65[0] + g * Y65[1] + b * Y65[2],
            z: r * Z65[0] + g * Z65[1] + b * Z65[2],
        }
    }
}

#[cfg(test)]
mod tests {
    use crate::util;

    use super::*;

    #[test]
    fn expect_to_compute_rec709_from_xyz() {
        let xyz = Xyz {
            x: 0.02338,
            y: 0.01172,
            z: 0.10459,
        };

        let rec = Rec709::from(xyz);

        util::assert_approx!(rec.r, 0.02522, 1e-5);
        util::assert_approx!(rec.g, 0.01652, 1e-5);
        util::assert_approx!(rec.b, 0.30717, 1e-5);
    }

    #[test]
    fn expect_to_compute_xyz_from_rec709() {
        let rec709 = Rec709 {
            r: 0.025223205825000036,
            g: 0.016522872911999987,
            b: 0.307169371144681,
        };

        let xyz = Xyz::from(rec709);
        util::assert_approx!(xyz.x, 0.02338, 1e-5);
        util::assert_approx!(xyz.y, 0.01172, 1e-5);
        util::assert_approx!(xyz.z, 0.10459, 1e-5);
    }
}
