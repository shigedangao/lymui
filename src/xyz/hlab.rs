use super::Xyz;

// Constant for D65 illuminent
const YN: f64 = 1.0;
const XN: f64 = 0.95047;
const ZN: f64 = 1.08883;

#[derive(Debug)]
pub(crate) struct Hlab {
    l: f64,
    a: f64,
    b: f64
}

// Formula can be found here
// @link http://www.easyrgb.com/en/math.php#text5
impl From<Xyz> for Hlab {
    fn from(xyz: Xyz) -> Self {
        let ka = (175.0 / 198.04) * (YN + XN);
        let kb = (70.0 / 218.11) * (YN + ZN);

        Hlab {
            l: 100.0 * f64::sqrt(xyz.y / YN),
            a: 100.0 * ka * ((xyz.x / XN - xyz.y / YN) / f64::sqrt(xyz.y / YN)),
            b: 100.0 * kb * ((xyz.y / YN - xyz.z / ZN) / f64::sqrt(xyz.y / YN))
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::rgb::{FromRgb, Rgb};
    use crate::util;

    #[test]
    fn expect_to_create_hlab() {
        let rgb = Rgb {
            r: 50,
            g: 10,
            b: 195
        };

        let xyz = Xyz::from_rgb(rgb, crate::xyz::Kind::Std);
        let hlab = Hlab::from(xyz);

        assert_eq!(util::roundup(hlab.l, 1000.0), 21.987);
        assert_eq!(util::roundup(hlab.a, 1000.0), 55.063);
        assert_eq!(util::roundup(hlab.b, 1000.0), -130.759);
    }

    #[test]
    fn expect_to_create_hlab_from_white_rgb() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255
        };

        let xyz = Xyz::from_rgb(rgb, crate::xyz::Kind::Std);
        let hlab = Hlab::from(xyz);

        assert_eq!(util::roundup(hlab.l, 1000.0), 100.0);
        assert_eq!(util::roundup(hlab.a, 1000.0), 0.0);
        assert_eq!(util::roundup(hlab.b, 1000.0), 0.0);   
    }
}
