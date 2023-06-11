use super::{oklab::OkLab, Xyz};
use crate::util::{AsVec, FromVec};

#[cfg(feature = "js")]
use crate::js::prelude::*;

/// OkLch implement the oklch colorspace (polar form of OkLab). The implementation is based on the article below
///
/// @link https://bottosson.github.io/posts/oklab/#the-oklab-color-space
#[cfg_attr(feature = "js", derive(FromJsObj))]
#[derive(Debug, Clone, Copy)]
pub struct OkLch {
    pub l: f64,
    pub c: f64,
    pub h: f64,
}

impl AsVec for OkLch {
    type Item = f64;

    fn as_vec(&self) -> Vec<Self::Item> {
        vec![self.l, self.c, self.h]
    }
}

impl FromVec<f64> for OkLch {
    fn from_vec(vec: Vec<f64>) -> Self {
        OkLch {
            l: vec.first().copied().unwrap_or_default(),
            c: vec.get(1).copied().unwrap_or_default(),
            h: vec.last().copied().unwrap_or_default(),
        }
    }
}

impl From<OkLab> for OkLch {
    fn from(oklab: OkLab) -> Self {
        OkLch {
            l: oklab.l,
            c: f64::sqrt(oklab.a.powi(2) + oklab.b.powi(2)),
            h: oklab.b.atan2(oklab.a),
        }
    }
}

impl From<OkLch> for OkLab {
    fn from(oklch: OkLch) -> Self {
        OkLab {
            l: oklch.l,
            a: oklch.c * oklch.h.cos(),
            b: oklch.c * oklch.h.sin(),
        }
    }
}

impl From<Xyz> for OkLch {
    fn from(xyz: Xyz) -> Self {
        let oklab = OkLab::from(xyz);

        OkLch::from(oklab)
    }
}

impl From<OkLch> for Xyz {
    fn from(oklch: OkLch) -> Self {
        let oklab = OkLab::from(oklch);

        Xyz::from(oklab)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_compute_oklch() {
        let oklab = OkLab {
            l: 0.26368282277639926,
            a: 0.06116371608383586,
            b: -0.12579731956598594,
        };

        let oklch = OkLch::from(oklab);
        assert_eq!(oklch.l, 0.26368282277639926);
        assert_eq!(oklch.c, 0.13987839638475583);
        assert_eq!(oklch.h, -1.1182427301033124);
    }

    #[test]
    fn expect_to_compute_oklab_from_oklch() {
        let oklch = OkLch {
            l: 0.26368282277639926,
            c: 0.13987839638475583,
            h: -1.1182427301033124,
        };

        let oklab = OkLab::from(oklch);
        assert_eq!(util::roundup(oklab.l, 100000_f64), 0.26368);
        assert_eq!(util::roundup(oklab.a, 100000_f64), 0.06116);
        assert_eq!(util::roundup(oklab.b, 100000_f64), -0.1258);
    }
}
