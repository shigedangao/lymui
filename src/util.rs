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
