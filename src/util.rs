use std::f64::consts::PI;

pub(crate) trait AsFloat {
    /// Return inner struct field as a tuple of float64
    fn as_f64(&self) -> (f64, f64, f64);
}

pub(crate) trait PivotFloat {
    /// Get the degree value from a radian value
    fn get_degree_from_radian(self) -> f64;
    /// Get the radian value from a degree value
    fn get_radian_from_degree(self) -> f64;
}

impl PivotFloat for f64 {
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
pub(crate) fn roundup(v: f64, cell: f64) -> f64 {
    (v * cell).round() / cell
}
