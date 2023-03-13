use super::rgb::{ADBOBE_RGB_COMPOUND};

pub trait PivotFloat {
    /// Unpivot an SRGB value
    /// 
    /// # Arguments
    /// 
    /// * `v` - f64
    fn unpivot_std(self) -> f64;
    /// Unpivot the calculated adobe RGB value
    /// 
    /// # Arguments
    /// 
    /// * `v` - f64
    fn unpivot_argb(self) -> f64;
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
}

/// Roundup a value based on the given cell value
/// 
/// # Arguments
/// 
/// * `v` - f64
/// * `cell` - f64
pub fn roundup(v: f64, cell: f64) -> f64 {
    (v * cell).round() / cell
}
