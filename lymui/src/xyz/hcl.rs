use super::{luv::Luv, Xyz};
use crate::{
    hue::Hue,
    util::{AsVec, FromVec, PivotFloat},
};

#[cfg(feature = "js")]
use crate::js::prelude::*;

/// Implementation of the Luv to polarLUV (HCL). The implementation is based on the following python implementation
///
/// @link https://github.com/retostauffer/python-colorspace/blob/da56c170fbaa8a6ca27f9483954ac3e2f51af617/colorspace/colorlib.py#L1318
#[cfg_attr(feature = "js", derive(FromJsObj, IntoJsObject))]
#[derive(Debug, Clone, Copy)]
pub struct Hcl {
    pub h: f64,
    pub c: f64,
    pub l: f64,
}

impl AsVec for Hcl {
    type Item = f64;

    fn as_vec(&self) -> Vec<Self::Item> {
        vec![self.h, self.c, self.l]
    }
}

impl FromVec<f64> for Hcl {
    fn from_vec(vec: Vec<f64>) -> Self {
        Hcl {
            h: vec.first().copied().unwrap_or_default(),
            c: vec.get(1).copied().unwrap_or_default(),
            l: vec.last().copied().unwrap_or_default(),
        }
    }
}

impl From<Luv> for Hcl {
    fn from(luv: Luv) -> Self {
        let hue = Hue::from(luv);

        Hcl {
            h: hue,
            c: f64::sqrt(luv.u * luv.u + luv.v * luv.v),
            l: luv.l,
        }
    }
}

impl From<Hcl> for Luv {
    fn from(hcl: Hcl) -> Self {
        let h = hcl.h.get_radian_from_degree();

        Luv {
            l: hcl.l,
            u: hcl.c * h.cos(),
            v: hcl.c * h.sin(),
        }
    }
}

impl From<Hcl> for Xyz {
    fn from(hcl: Hcl) -> Self {
        let luv = Luv::from(hcl);

        Xyz::from(luv)
    }
}

impl From<Xyz> for Hcl {
    fn from(xyz: Xyz) -> Self {
        let luv = Luv::from(xyz);

        Hcl::from(luv)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_create_hcl() {
        let luv = Luv {
            l: 100.0,
            u: 0.0,
            v: -0.0,
        };

        let hcl = Hcl::from(luv);
        assert_eq!(hcl.h, -0_f64);
        assert_eq!(hcl.c, 0_f64);
        assert_eq!(hcl.l, 100_f64);
    }

    #[test]
    fn expect_to_create_other_hcl() {
        let luv = Luv {
            l: 9.605759326542188,
            u: -2.8497902947799596,
            v: -34.83645386504839,
        };

        let hcl = Hcl::from(luv);
        assert_eq!(util::roundup(hcl.h, 1000.0), 265.323);
        assert_eq!(util::roundup(hcl.c, 1000.0), 34.953);
        assert_eq!(util::roundup(hcl.l, 1000.0), 9.606);
    }

    #[test]
    fn expect_to_create_hcl_from_luv() {
        let hcl = Hcl {
            h: -0_f64,
            c: 0_f64,
            l: 100_f64,
        };

        let luv = Luv::from(hcl);
        assert_eq!(luv.l, 100_f64);
        assert_eq!(luv.u, 0_f64);
        assert_eq!(luv.v, 0_f64);
    }

    #[test]
    fn expect_to_create_second_luv_from_hcl() {
        let hcl = Hcl {
            h: 265.32334188039283,
            c: 34.95282281327028,
            l: 9.605759326542188,
        };

        let luv = Luv::from(hcl);
        assert_eq!(util::roundup(luv.l, 1000_f64), 9.606);
        assert_eq!(util::roundup(luv.u, 1000_f64), -2.85);
        assert_eq!(util::roundup(luv.v, 1000_f64), -34.836);
    }
}
