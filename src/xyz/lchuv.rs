use super::Xyz;
use super::luv::Luv;
use crate::ops::SliceOps;

/// Lch or Hcl is a representation of the HCL colorspace.
/// The current implementation uses the D65 standard illuminent
///
/// The computation reference can be found below
/// @link <https://en.wikipedia.org/wiki/CIELUV
/// @link <https://en.wikipedia.org/wiki/CIELUV#Cylindrical_representation_(CIELCh)
/// @link <https://en.wikipedia.org/wiki/HCL_color_space#Implementations>
/// @link <http://www.brucelindbloom.com/index.html?Eqn_RGB_to_XYZ.html>
#[derive(Debug, Clone, Copy)]
pub struct Lchuv {
    pub l: f64,
    pub c: f64,
    pub h: f64,
}

impl SliceOps<3> for Lchuv {
    type Item = f64;

    fn as_slice(&self) -> [Self::Item; 3] {
        [self.l, self.c, self.h]
    }

    fn to_vec(&self) -> Vec<Self::Item> {
        self.as_slice().to_vec()
    }

    fn from_slice(slice: &[Self::Item; 3]) -> Self {
        Lchuv {
            l: slice[0],
            c: slice[1],
            h: slice[2],
        }
    }
}

impl From<Xyz> for Lchuv {
    fn from(xyz: Xyz) -> Self {
        let luv = Luv::from(xyz);
        let h = luv.v.atan2(luv.u).to_degrees();

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
        let h = lch.h.to_radians();

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
        util::assert_approx!(lch.l, 77.28, 1e-2);
        util::assert_approx!(lch.c, 12.0, 1e-2);
        util::assert_approx!(lch.h, 37.5, 1e-2);
    }

    #[test]
    fn expect_to_create_white_lch() {
        let xyz = Xyz {
            x: 0.950470,
            y: 1.0,
            z: 1.088830,
        };

        let lch = Lchuv::from(xyz);
        util::assert_approx!(lch.l, 100.0, 1e-2);
        util::assert_approx!(lch.c, 0.0, 1e-2);
        util::assert_approx!(lch.h, 360.0, 1e-2);
    }

    #[test]
    fn expect_to_compute_xyz() {
        let lch = Lchuv {
            l: 59.0746,
            c: 94.1630,
            h: 295.1265,
        };

        let xyz = Xyz::from(lch);
        util::assert_approx!(xyz.x, 0.4266, 1e-4);
        util::assert_approx!(xyz.y, 0.2711, 1e-4);
        util::assert_approx!(xyz.z, 0.7783, 1e-4);
    }
}
