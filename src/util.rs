use std::f64::consts::PI;
use super::rgb::ADBOBE_RGB_COMPOUND;

pub trait AsFloat {
    /// Return inner struct field as a tuple of float64
    fn as_f64(&self) -> (f64, f64, f64);    
}

pub trait PivotFloat {
    /// Unpivot an SRGB value
    fn unpivot_std(self) -> f64;
    /// Unpivot the calculated adobe RGB value
    fn unpivot_argb(self) -> f64;
    /// Get the degree value from a radian value
    fn get_degree_from_radian(self) -> f64;
    /// Get the radian value from a degree value
    fn get_radian_from_degree(self) -> f64;
}

impl PivotFloat for f64 {
    fn unpivot_std(self) -> f64 {
        if self <= 0.0031308 {
            return self * 12.92;
        }

        1.055 * self.powf(1.0 / 2.4) - 0.055
    }
    
    fn unpivot_argb(self) -> f64 {
        if self <= 0.0 {
            return 0.0;
        }

        self.powf(1.0 / ADBOBE_RGB_COMPOUND)
    }

    fn get_degree_from_radian(self) -> f64 {
        180.0 * self / PI
    }

    fn get_radian_from_degree(self) -> f64 {
        self * PI / 180.0
    }
}

/// Roundup a value based on the given cell value
/// 
/// # Arguments
/// 
/// * `v` - f64
/// * `cell` - f64
#[allow(dead_code)]
pub fn roundup(v: f64, cell: f64) -> f64 {
    (v * cell).round() / cell
}
