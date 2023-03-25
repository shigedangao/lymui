use super::Xyz;

// Constant for D65 / 2° illuminent
const XN: f64 = 95.047;
const YN: f64 = 100.0;
const ZN: f64 = 108.883;

#[derive(Debug)]
pub(crate) struct Hlab {
    l: f64,
    a: f64,
    b: f64
}

impl Hlab {
    fn get_ka_kb() -> (f64, f64) {
        let ka = (175.0 / 198.04) * (YN + XN);
        let kb = (70.0 / 218.11) * (YN + ZN);

        (ka, kb)
    }
}

// Formula can be found here
// @link http://www.easyrgb.com/en/math.php#text5
impl From<Xyz> for Hlab {
    fn from(xyz: Xyz) -> Self {
        let (ka, kb) = Hlab::get_ka_kb();
        Hlab {
            l: 1000.0 * f64::sqrt(xyz.y / YN),
            a: 10.0 * ka * ((xyz.x / XN - xyz.y / YN) / f64::sqrt(xyz.y / YN)),
            b: 10.0 * kb * ((xyz.y / YN - xyz.z / ZN) / f64::sqrt(xyz.y / YN))
        }
    }
}

// Formula can be found here
// @link http://www.easyrgb.com/en/math.php#text5
// /!\ Note that the Xyz returns is not scaled. Hence the usage of 0.01
impl From<Hlab> for Xyz {
    fn from(hlab: Hlab) -> Self {
        let (ka, kb) = Hlab::get_ka_kb();
        let y = f64::powf(hlab.l / YN, 2.0) * 100.0;

        Xyz {
            x: (((hlab.a / ka * f64::sqrt(y / YN) + (y / YN)) * XN)) * 0.01,
            y: y * 0.01,
            z: (((hlab.b / kb * f64::sqrt(y / YN) - (y / YN)) * ZN)) * 0.01
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

    #[test]
    fn expect_to_create_xyz_from_hlab() {
        let hlab = Hlab {
            l: 21.987,
            a: 55.063,
            b: -130.759
        };

        let xyz = Xyz::from(hlab);
        assert_eq!(util::roundup(xyz.x, 10000.0), 0.1127);
        assert_eq!(util::roundup(xyz.y, 10000.0), 0.0483);
        assert_eq!(util::roundup(xyz.z, 10000.0), -0.5196);
    }
}
