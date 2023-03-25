use super::{Xyz, D65, EPSILON, KAPPA};

/// Lab is a repesentation of the CIELAB colorspace.
/// The current implementation uses the D65 standard illuminent
/// 
/// The computation reference can be found below
/// @link https://en.wikipedia.org/wiki/CIELAB_color_space
/// @link http://www.brucelindbloom.com/index.html?Eqn_RGB_to_XYZ.html
/// @link http://www.brucelindbloom.com/index.html?Eqn_RGB_to_XYZ.html
#[derive(Debug, Clone, Copy)]
pub struct Lab {
    pub l: f64,
    pub a: f64,
    pub b: f64
}

impl Lab {
    /// Compute the 
    fn compute_f(c: f64) -> f64 {
        if c > 0.008856 {
            c.cbrt()
        } else {
            (c * 7.787) + 16.0 / 116.0
        }
    }

    fn reverse_compute_f(c: f64) -> f64 {
        if c.powi(3) > EPSILON {
            c.powi(3)
        } else {
            (116.0 * c - 16.0) / KAPPA
        }
    }
}

impl From<Xyz> for Lab {
    fn from(xyz: Xyz) -> Self {
        Lab {
            l: 116.0 * Lab::compute_f(xyz.y / D65[1]) - 16.0,
            a: 500.0 * (Lab::compute_f(xyz.x / D65[0]) - Lab::compute_f(xyz.y / D65[1])),
            b: 200.0 * (Lab::compute_f(xyz.y / D65[1]) - Lab::compute_f(xyz.z / D65[2]))
        }
    }
}

impl From<Lab> for Xyz {
    fn from(lab: Lab) -> Self {
        let l = (lab.l + 16.0) / 116.0;
        let x = D65[0] * Lab::reverse_compute_f(l + lab.a / 500.0);
        let z = D65[2] * Lab::reverse_compute_f(l - lab.b / 200.0);

        let y = if lab.l > EPSILON * KAPPA {
            D65[1] * l.powi(3)
        } else {
            D65[1] * (lab.l / KAPPA)
        };

        Xyz {
            x,
            y,
            z
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;
    use crate::rgb::{Rgb, FromRgb};
    use crate::util;

    #[test]
    fn expect_to_create_lab_from_xyz() {
        let rgb = Rgb {
            r: 50,
            g: 10,
            b: 195
        };

        let xyz = Xyz::from_rgb(rgb, crate::xyz::Kind::Std);
        
        let lab = Lab::from(xyz);
        assert_eq!(util::roundup(lab.l, 100.0), 26.26);
        assert_eq!(util::roundup(lab.a, 100.0), 63.50);
        assert_eq!(util::roundup(lab.b, 100.0), -83.43);
    }

    #[test]
    fn expect_to_create_lab_dark() {
        let rgb = Rgb {
            r: 0,
            g: 0,
            b: 0
        };

        let xyz = Xyz::from_rgb(rgb, crate::xyz::Kind::Std);
        
        let lab = Lab::from(xyz);
        assert_eq!(util::roundup(lab.l, 100.0), 0.0);
        assert_eq!(util::roundup(lab.a, 100.0), 0.0);
        assert_eq!(util::roundup(lab.b, 100.0), 0.0);
    }

    #[test]
    fn expect_to_create_lab_bright() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255
        };

        let xyz = Xyz::from_rgb(rgb, crate::xyz::Kind::Std);
        
        let lab = Lab::from(xyz);
        assert_eq!(util::roundup(lab.l, 100.0), 100.0);
        assert_eq!(util::roundup(lab.a, 100.0), 0.0);
        assert_eq!(util::roundup(lab.b, 100.0), 0.0);
    }

    #[test]
    fn expect_to_create_from_lab_xyz() {
        let lab = Lab {
            l: 26.65,
            a: 64.26,
            b: -84.64
        };

        let xyz = Xyz::from(lab);
        assert_eq!(util::roundup(xyz.x, 1000.0), 0.116);
        assert_eq!(util::roundup(xyz.y, 1000.0), 0.050);
        assert_eq!(util::roundup(xyz.z, 1000.0), 0.539);
    }

    #[test]
    fn expect_to_create_xyz_from_dark_lab() {
        let lab = Lab {
            l: 0.0,
            a: 0.0,
            b: 0.0
        };

        let xyz = Xyz::from(lab);
        assert_eq!(xyz.x, 0.0);
        assert_eq!(xyz.y, 0.0);
        assert_eq!(xyz.z, 0.0);
    }

    #[test]
    fn expect_to_create_xyz_from_bright_lab() {
        let lab = Lab {
            l: 100.0,
            a: 0.0,
            b: 0.0
        };

        let xyz = Xyz::from(lab);
        assert_eq!(util::roundup(xyz.x, 1000.0), 0.950);
        assert_eq!(util::roundup(xyz.y, 1000.0), 1.000);
        assert_eq!(util::roundup(xyz.z, 1000.0), 1.089);
    }
}
