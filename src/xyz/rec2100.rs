use crate::util::AsVec;

use super::{matrices::rec2020::*, transfer::HdrCorrection, Xyz};

/// Implementation of the rec.2100 color space but only for the Pq transfer function.
/// So far only the PQ transformation is implemented as I am not even sure that the implementation is correct
/// due to the fact that there are no website where I can test the conversion, but assuming that the PQ extended to 10_000
/// we could assume that the maximum value of an XYZ should be roughly equal to the 10_000 value.
/// The implementation is based on the wikipedia links below.
///
/// The rec.2100 uses the matrices of the rec.2020
///
/// @link https://en.wikipedia.org/wiki/Rec._2100
/// @link https://en.wikipedia.org/wiki/Perceptual_quantizer
#[derive(Debug, Clone, Copy)]
pub struct Rec2100 {
    pub r: f64,
    pub g: f64,
    pub b: f64,
}

impl AsVec for Rec2100 {
    type Item = f64;

    fn as_vec(&self) -> Vec<Self::Item> {
        vec![self.r, self.g, self.b]
    }
}

impl From<Xyz> for Rec2100 {
    fn from(xyz: Xyz) -> Self {
        let r = (xyz.x * XR[0] + xyz.y * XR[1] + xyz.z * XR[2]).pq_eotf();
        let g = (xyz.x * XG[0] + xyz.y * XG[1] + xyz.z * XG[2]).pq_eotf();
        let b = (xyz.x * XB[0] + xyz.y * XB[1] + xyz.z * XB[2]).pq_eotf();

        Rec2100 { r, g, b }
    }
}

impl From<Rec2100> for Xyz {
    fn from(rec: Rec2100) -> Self {
        let r = rec.r.pq_inverse_eotf();
        let g = rec.g.pq_inverse_eotf();
        let b = rec.b.pq_inverse_eotf();

        Xyz {
            x: r * XX[0] + g * XX[1] + b * XX[2],
            y: r * XY[0] + g * XY[1] + b * XY[2],
            z: r * XZ[0] + g * XZ[1] + b * XZ[2],
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_convert_xyz_to_rec2100() {
        // Max value of xyz
        let xyz = Xyz {
            x: 0.950470,
            y: 1.000000,
            z: 1.088830,
        };

        let rec = Rec2100::from(xyz);
        assert_eq!(rec.r.floor(), 10_000_f64);
        assert_eq!(rec.g.ceil(), 10_000_f64);
        assert_eq!(rec.b.ceil(), 10_000_f64);
    }

    #[test]
    fn expect_to_convert_rec2100_to_xyz() {
        let rec = Rec2100 {
            r: 10_000_f64,
            g: 10_000_f64,
            b: 10_000_f64,
        };

        let xyz = Xyz::from(rec);
        assert_eq!(util::roundup(xyz.x, 10_000_f64), 0.9505);
        assert_eq!(util::roundup(xyz.y, 10_000_f64), 1_f64);
        assert_eq!(util::roundup(xyz.z, 10_000_f64), 1.0891);
    }
}
