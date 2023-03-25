use super::{Xyz, X, Y, Z};

// Constant
const SR: [f64; 3] = [3.2404542, -1.5371385, -0.4985314];
const SG: [f64; 3] = [-0.9692660, 1.8760108, 0.0415560];
const SB: [f64; 3] = [0.0556434, -0.2040259, 1.0572252];

/// Implementation of the sRGB colorspace.
/// The foruma can be found on the link below
/// 
/// @link https://en.wikipedia.org/wiki/SRGB#:~:text=in%20these%20coefficients).-,From%20CIE%20XYZ%20to%20sRGB,when%20using%20specified%20white%20points).
#[derive(Debug, Clone, Copy)]
pub struct Srgb {
    pub r: f64,
    pub g: f64,
    pub b: f64
}

impl Srgb {
    fn apply_gamma_correction(c: f64) -> f64 {
        if c <= 0.0031308 {
            c * 12.92
        } else {
            1.055 * c.powf(1_f64 / 2.4) - 0.055
        }
    }

    fn reverse_gamma(&self) -> (f64, f64, f64) {
        let colors = vec![self.r, self.g, self.b];
        let reversed: Vec<f64> = colors
            .into_iter()
            .map(|c| {
                if c <= 0.04045 {
                    c / 12.92
                } else {
                    f64::powf((c + 0.055) / 1.055, 2.4)
                }
            })
            .collect();

        (
            *reversed.get(0).unwrap_or(&0.0),
            *reversed.get(1).unwrap_or(&0.0),
            *reversed.get(2).unwrap_or(&0.0)
        )
    }

    /// Transform the non linear sRGB into a linear RGB
    /// 
    /// # Arguments
    /// 
    /// * `&mut self` - Self
    pub fn as_linear(&mut self) {
        self.r = self.r.powf(2.2);
        self.g = self.g.powf(2.2);
        self.b = self.b.powf(2.2);
    }

    /// Transform a linear sRGB into a non linear sRGB
    /// 
    /// # Arguments
    /// 
    /// * `&mut self` - Self
    pub fn as_non_linear(&mut self) {
        self.r = self.r.powf(1_f64 / 2.2);
        self.g = self.g.powf(1_f64 / 2.2);
        self.b = self.b.powf(1_f64 / 2.2);
    }
}

impl From<Xyz> for Srgb {
    fn from(xyz: Xyz) -> Self {
        let r = xyz.x * SR[0] + xyz.y * SR[1] + xyz.z * SR[2];
        let g = xyz.x * SG[0] + xyz.y * SG[1] + xyz.z * SG[2];
        let b = xyz.x * SB[0] + xyz.y * SB[1] + xyz.z * SB[2];

        Srgb {
            r: Srgb::apply_gamma_correction(r),
            g: Srgb::apply_gamma_correction(g),
            b: Srgb::apply_gamma_correction(b)
        }
    }
}

impl From<Srgb> for Xyz {
    fn from(sr: Srgb) -> Self {
        let (r, g, b) = sr.reverse_gamma();

        Xyz {
            x: r * X[0] + g * X[1] + b * X[2],
            y: r * Y[0] + g * Y[1] + b * Y[2],
            z: r * Z[0] + g * Z[1] + b * Z[2],
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::rgb::{Rgb, FromRgb};
    use crate::util;

    #[test]
    fn expect_to_compute_srgb() {
        let rgb = Rgb {
            r: 50,
            g: 10,
            b: 95
        };

        let xyz = Xyz::from_rgb(rgb, crate::xyz::Kind::Std);
        
        let srgb = Srgb::from(xyz);
        assert_eq!(util::roundup(srgb.r, 1000.0), 0.196);
        assert_eq!(util::roundup(srgb.g, 1000.0), 0.039);
        assert_eq!(util::roundup(srgb.b, 1000.0), 0.373);
    }

    #[test]
    fn expect_to_compute_black_srgb() {
        let rgb = Rgb {
            r: 0,
            g: 0,
            b: 0
        };

        let xyz = Xyz::from_rgb(rgb, crate::xyz::Kind::Std);
        
        let srgb = Srgb::from(xyz);
        assert_eq!(srgb.r, 0.0);
        assert_eq!(srgb.g, 0.0);
        assert_eq!(srgb.b, 0.0);
    }

    #[test]
    fn expect_to_compute_white_srgb() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255
        };

        let xyz = Xyz::from_rgb(rgb, crate::xyz::Kind::Std);
        
        let srgb = Srgb::from(xyz);
        assert_eq!(util::roundup(srgb.r, 1000.0), 1.0);
        assert_eq!(util::roundup(srgb.g, 1000.0), 1.0);
        assert_eq!(util::roundup(srgb.b, 1000.0), 1.0);
    }

    #[test]
    fn expect_to_create_xyz_from_srgb() {
        let srgb = Srgb {
            r: 0.19608,
            g: 0.03922,
            b: 0.37255
        };

        let xyz = Xyz::from(srgb);
        assert_eq!(util::roundup(xyz.x, 1000.0), 0.035);
        assert_eq!(util::roundup(xyz.y, 1000.0), 0.017);
        assert_eq!(util::roundup(xyz.z, 1000.0), 0.110);
    }
}
