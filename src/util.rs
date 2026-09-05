/// Roundup a value based on the given cell value
///
/// # Arguments
///
/// * `v` - f64
/// * `cell` - f64
#[cfg(test)]
pub(crate) fn roundup(v: f64, cell: f64) -> f64 {
    (v * cell).round() / cell
}

/// Assert that two f64 values are approximately equal within a given epsilon
///
/// # Arguments
///
/// * `left` - f64
/// * `right` - f64
/// * `epsilon` - f64
macro_rules! assert_approx {
    ($left:expr, $right:expr, $epsilon:expr) => {
        assert!(
            f64::abs($left - $right) < $epsilon,
            "left: {}, right: {}",
            $left,
            $right
        );
    };
}

pub(crate) use assert_approx;
