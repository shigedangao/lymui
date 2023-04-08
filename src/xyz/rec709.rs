use super::{
    gamma::GammaCorrection,
    matrices::xyz::{RX65, RY65, RZ65, X65, Y65, Z65},
    Xyz,
};

/// Rec709 is an implementation of the Rec.709 colorspace
///
/// @link https://en.wikipedia.org/wiki/Rec._709
/// @link https://agraphicsguynotes.com/posts/basic_color_science_for_graphcis_engineer/#rec-709
#[derive(Debug, Clone, Copy)]
pub struct Rec709 {
    pub r: f64,
    pub g: f64,
    pub b: f64,
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

        assert_eq!(util::roundup(rec.r, 100000_f64), 0.02522);
        assert_eq!(util::roundup(rec.g, 100000_f64), 0.01652);
        assert_eq!(util::roundup(rec.b, 100000_f64), 0.30717);
    }

    #[test]
    fn expect_to_compute_xyz_from_rec709() {
        let rec709 = Rec709 {
            r: 0.025223205825000036,
            g: 0.016522872911999987,
            b: 0.307169371144681,
        };

        let xyz = Xyz::from(rec709);
        assert_eq!(util::roundup(xyz.x, 100000_f64), 0.02338);
        assert_eq!(util::roundup(xyz.y, 100000_f64), 0.01172);
        assert_eq!(util::roundup(xyz.z, 100000_f64), 0.10459);
    }
}
