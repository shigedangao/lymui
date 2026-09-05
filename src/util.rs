/// Assert that two f64 values are approximately equal within a given epsilon
///
/// # Arguments
///
/// * `left` - f64
/// * `right` - f64
/// * `epsilon` - f64
#[cfg(test)]
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

#[cfg(test)]
pub(crate) use assert_approx;
