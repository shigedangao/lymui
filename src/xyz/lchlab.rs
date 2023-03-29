use crate::util::PivotFloat;

use super::lab::Lab;
use super::Xyz;

#[derive(Debug, Clone, Copy)]
pub struct Lchlab {
    l: f64,
    c: f64,
    h: f64,
}

impl From<Xyz> for Lchlab {
    fn from(xyz: Xyz) -> Self {
        let lab = Lab::from(xyz);
        let h = lab.b.atan2(lab.a).get_degree_from_radian();

        let final_h = if h >= 0.0 { h } else { h + 360.0 };

        Lchlab {
            l: lab.l,
            c: f64::sqrt(lab.a.powi(2) + lab.b.powi(2)),
            h: final_h,
        }
    }
}

impl From<Lchlab> for Lab {
    fn from(lch: Lchlab) -> Self {
        let h = lch.h.get_radian_from_degree();

        Lab {
            l: lch.l,
            a: lch.c * h.cos(),
            b: lch.c * h.sin(),
        }
    }
}

impl From<Lchlab> for Xyz {
    fn from(lch: Lchlab) -> Self {
        let lab = Lab::from(lch);

        Xyz::from(lab)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_create_lchlab() {
        let xyz = Xyz {
            x: 0.1161,
            y: 0.0497,
            z: 0.5376,
        };

        let lch = Lchlab::from(xyz);
        assert_eq!(util::roundup(lch.l, 100.0), 26.65);
        assert_eq!(util::roundup(lch.c, 100.0), 106.19);
        assert_eq!(util::roundup(lch.h, 100.0), 307.24);
    }

    #[test]
    fn expect_to_create_lchlab_white() {
        let xyz = Xyz {
            x: 0.9505,
            y: 1.0,
            z: 1.0888,
        };

        let lch = Lchlab::from(xyz);
        assert_eq!(util::roundup(lch.l, 1000.0), 100.0);
        assert_eq!(util::roundup(lch.c, 1000.0), 0.006);
        assert_eq!(util::roundup(lch.h, 1000.0), 19.248);
    }

    #[test]
    fn expect_to_create_xyz_from_lchlab() {
        let lch = Lchlab {
            l: 48.8158,
            c: 46.0879,
            h: 270.7007,
        };

        let xyz = Xyz::from(lch);
        assert_eq!(util::roundup(xyz.x, 10000.0), 0.1668);
        assert_eq!(util::roundup(xyz.y, 10000.0), 0.1744);
        assert_eq!(util::roundup(xyz.z, 10000.0), 0.5352);
    }
}
