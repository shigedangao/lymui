use crate::util::{AsVec, FromVec, PivotFloat};

use super::luv::Luv;
use super::Xyz;

/// Lch or Hcl is a representation of the HCL colorspace.
/// The current implementation uses the D65 standard illuminent
///
/// The computation reference can be found below
/// @link https://en.wikipedia.org/wiki/CIELUV
/// @link https://en.wikipedia.org/wiki/CIELUV#Cylindrical_representation_(CIELCh)
/// @link https://en.wikipedia.org/wiki/HCL_color_space#Implementations
/// @link http://www.brucelindbloom.com/index.html?Eqn_RGB_to_XYZ.html
#[derive(Debug, Clone, Copy)]
pub struct Lchuv {
    pub l: f64,
    pub c: f64,
    pub h: f64,
}

impl AsVec for Lchuv {
    type Item = f64;

    fn as_vec(&self) -> Vec<Self::Item> {
        vec![self.l, self.c, self.h]
    }
}

impl FromVec<f64> for Lchuv {
    fn from_vec(vec: Vec<f64>) -> Self {
        Lchuv {
            l: vec.first().copied().unwrap_or_default(),
            c: vec.get(1).copied().unwrap_or_default(),
            h: vec.last().copied().unwrap_or_default(),
        }
    }
}

impl From<Xyz> for Lchuv {
    fn from(xyz: Xyz) -> Self {
        let luv = Luv::from(xyz);
        let h = luv.v.atan2(luv.u).get_degree_from_radian();

        let final_h = if h > 0.0 { h } else { h + 360.0 };

        Lchuv {
            l: luv.l,
            c: f64::sqrt(luv.u.powi(2) + luv.v.powi(2)),
            h: final_h,
        }
    }
}

impl From<Lchuv> for Luv {
    fn from(lch: Lchuv) -> Self {
        let h = lch.h.get_radian_from_degree();

        Luv {
            l: lch.l,
            u: lch.c * h.cos(),
            v: lch.c * h.sin(),
        }
    }
}

impl From<Lchuv> for Xyz {
    fn from(lch: Lchuv) -> Self {
        let luv = Luv::from(lch);

        Xyz::from(luv)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_compute_lch() {
        let xyz = Xyz {
            x: 0.51,
            y: 0.52,
            z: 0.51,
        };

        let lch = Lchuv::from(xyz);
        assert_eq!(util::roundup(lch.l, 100.0), 77.28);
        assert_eq!(util::roundup(lch.c, 100.0), 12.0);
        assert_eq!(util::roundup(lch.h, 100.0), 37.5);
    }

    #[test]
    fn expect_to_create_white_lch() {
        let xyz = Xyz {
            x: 0.950470,
            y: 1.0,
            z: 1.088830,
        };

        let lch = Lchuv::from(xyz);
        assert_eq!(util::roundup(lch.l, 100.0), 100.0);
        assert_eq!(util::roundup(lch.c, 100.0), 0.0);
        assert_eq!(util::roundup(lch.h, 100.0), 360.0);
    }

    #[test]
    fn expect_to_compute_xyz() {
        let lch = Lchuv {
            l: 59.0746,
            c: 94.1630,
            h: 295.1265,
        };

        let xyz = Xyz::from(lch);
        assert_eq!(util::roundup(xyz.x, 10000.0), 0.4266);
        assert_eq!(util::roundup(xyz.y, 10000.0), 0.2711);
        assert_eq!(util::roundup(xyz.z, 10000.0), 0.7783);
    }
}
