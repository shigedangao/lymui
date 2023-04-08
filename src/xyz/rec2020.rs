use super::{matrices::rec2020::*, transfer::GammaCorrection, Xyz};

/// Rec2020 is an implementation of the rec2020 colorspace
///
/// @link https://en.wikipedia.org/wiki/Rec._2020
/// @link https://agraphicsguynotes.com/posts/basic_color_science_for_graphcis_engineer/#rec-2020
#[derive(Debug, Clone, Copy)]
pub struct Rec2020 {
    pub r: f64,
    pub g: f64,
    pub b: f64,
}

impl From<Xyz> for Rec2020 {
    fn from(xyz: Xyz) -> Self {
        let r = (xyz.x * XR[0] + xyz.y * XR[1] + xyz.z * XR[2]).compute_rec2020_gamma_correction();
        let g = (xyz.x * XG[0] + xyz.y * XG[1] + xyz.z * XG[2]).compute_rec2020_gamma_correction();
        let b = (xyz.x * XB[0] + xyz.y * XB[1] + xyz.z * XB[2]).compute_rec2020_gamma_correction();

        Rec2020 { r, g, b }
    }
}

impl From<Rec2020> for Xyz {
    fn from(rec: Rec2020) -> Self {
        let r = rec.r.compute_rec2020_gamma_expanded();
        let g = rec.g.compute_rec2020_gamma_expanded();
        let b = rec.b.compute_rec2020_gamma_expanded();

        Xyz {
            x: r * XX[0] + g * XX[1] + b * XX[2],
            y: r * XY[0] + g * XY[1] + b * XY[2],
            z: r * XZ[0] + g * XZ[1] + b * XZ[2],
        }
    }
}

#[cfg(test)]
mod tests {
    use crate::util;

    use super::*;

    #[test]
    fn expect_to_compute_rec2020_from_xyz() {
        let xyz = Xyz {
            x: 0.02338,
            y: 0.01172,
            z: 0.10459,
        };

        let rec = Rec2020::from(xyz);

        assert_eq!(util::roundup(rec.r, 100000_f64), 0.0426);
        assert_eq!(util::roundup(rec.g, 100000_f64), 0.02253);
        assert_eq!(util::roundup(rec.b, 100000_f64), 0.28801);
    }

    #[test]
    fn expect_to_compute_xyz_from_rec2020() {
        let rec = Rec2020 {
            r: 0.04260268719017062,
            g: 0.02253290469387679,
            b: 0.2880065068857291,
        };

        let xyz = Xyz::from(rec);
        assert_eq!(util::roundup(xyz.x, 100000_f64), 0.02338);
        assert_eq!(util::roundup(xyz.y, 100000_f64), 0.01172);
        assert_eq!(util::roundup(xyz.z, 100000_f64), 0.10459);
    }
}
