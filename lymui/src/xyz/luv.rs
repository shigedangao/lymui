use super::{Xyz, D65, EPSILON, KAPPA};
use crate::util::{AsVec, FromVec};

#[cfg(feature = "js")]
use crate::js::prelude::*;

/// Luv is a representation of the CIELUV colorspace.
/// The current implementation uses the D65 standard illuminent
///
/// The computation reference can be found below
/// @link https://en.wikipedia.org/wiki/CIELUV
/// @link http://www.brucelindbloom.com/index.html?Eqn_RGB_to_XYZ.html
/// @link http://www.brucelindbloom.com/index.html?Eqn_RGB_to_XYZ.html
#[cfg_attr(feature = "js", derive(FromJsObj, IntoJsObject))]
#[derive(Debug, Clone, Copy)]
pub struct Luv {
    pub l: f64,
    pub u: f64,
    pub v: f64,
}

impl AsVec for Luv {
    type Item = f64;

    fn as_vec(&self) -> Vec<Self::Item> {
        vec![self.l, self.u, self.v]
    }
}

impl FromVec<f64> for Luv {
    fn from_vec(vec: Vec<f64>) -> Self {
        Luv {
            l: vec.first().copied().unwrap_or_default(),
            u: vec.get(1).copied().unwrap_or_default(),
            v: vec.last().copied().unwrap_or_default(),
        }
    }
}

impl Luv {
    fn compute_compounds(x: f64, y: f64, z: f64) -> (f64, f64) {
        if x == 0.0 && y == 0.0 && z == 0.0 {
            return (0.0, 0.0);
        }

        let u = (4.0 * x) / (x + 15.0 * y + 3.0 * z);
        let v = (9.0 * y) / (x + 15.0 * y + 3.0 * z);

        (u, v)
    }
}

impl From<Xyz> for Luv {
    fn from(xyz: Xyz) -> Self {
        let y = xyz.y / D65[1];
        let (u, v) = Luv::compute_compounds(xyz.x, xyz.y, xyz.z);
        let (ur, vr) = Luv::compute_compounds(D65[0], D65[1], D65[2]);

        let l = if y > EPSILON {
            116.0 * y.powf(1.0 / 3.0) - 16.0
        } else {
            KAPPA * y
        };

        Luv {
            l,
            u: 13.0 * l * (u - ur),
            v: 13.0 * l * (v - vr),
        }
    }
}

impl From<Luv> for Xyz {
    fn from(luv: Luv) -> Self {
        if luv.u == 0.0 && luv.l == 0.0 {
            return Xyz::default();
        }

        let (ur, vr) = Luv::compute_compounds(D65[0], D65[1], D65[2]);
        let y = if luv.l > (KAPPA * EPSILON) {
            f64::powi((luv.l + 16.0) / 116.0, 3)
        } else {
            luv.l / KAPPA
        };
        let a = (1.0 / 3.0) * ((52.0 * luv.l) / (luv.u + 13.0 * luv.l * ur) - 1.0);
        let b = -5.0 * y;
        let c = -1.0 / 3.0;
        let d = y * ((39.0 * luv.l) / (luv.v + 13.0 * luv.l * vr) - 5.0);

        let x = (d - b) / (a - c);

        Xyz { x, y, z: x * a + b }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::rgb::{FromRgb, Rgb};
    use crate::util;
    use crate::xyz::Kind;

    #[test]
    fn expect_to_compute_luv() {
        let rgb = Rgb { r: 5, g: 10, b: 95 };

        let xyz = Xyz::from_rgb(rgb, Kind::D65);

        let luv = Luv::from(xyz);
        assert_eq!(util::roundup(luv.l, 1000.0), 9.603);
        assert_eq!(util::roundup(luv.u, 1000.0), -2.851);
        assert_eq!(util::roundup(luv.v, 1000.0), -34.829);
    }

    #[test]
    fn expect_to_compute_dark_luv() {
        let rgb = Rgb { r: 0, g: 0, b: 0 };

        let xyz = Xyz::from_rgb(rgb, Kind::D65);

        let luv = Luv::from(xyz);
        assert_eq!(luv.l, 0.0);
        assert_eq!(luv.u, 0.0);
        assert_eq!(luv.v, 0.0);
    }

    #[test]
    fn expect_to_compute_xyz_from_luv() {
        let luv = Luv {
            l: 5.0,
            u: 1.0,
            v: 0.0,
        };

        let xyz = Xyz::from(luv);
        assert_eq!(util::roundup(xyz.x, 100000.0), 0.00567);
        assert_eq!(util::roundup(xyz.y, 100000.0), 0.00554);
        assert_eq!(util::roundup(xyz.z, 100000.0), 0.00589);
    }

    #[test]
    fn expect_to_compute_xyz_from_white_luv() {
        let luv = Luv {
            l: 100.0,
            u: 0.0,
            v: -0.0,
        };

        let xyz = Xyz::from(luv);
        assert_eq!(util::roundup(xyz.x, 100000.0), 0.95047);
        assert_eq!(util::roundup(xyz.y, 100000.0), 1.00000);
        assert_eq!(util::roundup(xyz.z, 100000.0), 1.08883);
    }
}
