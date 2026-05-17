/// Trait for converting a struct to a slice of its inner fields
/// As a color type has a defined length. It's better to use a slice rather than a vector to reduce memory usage
pub trait SliceOps<const S: usize> {
    /// The type of each item in the slice
    type Item;
    /// Convert the struct to a slice of its inner fields
    ///
    /// # Arguments
    ///
    /// * `self` - The struct to convert
    ///
    /// # Returns
    ///
    /// A slice of the struct's inner fields
    fn as_slice(&self) -> [Self::Item; S];

    /// Convert a slice of inner fields to a struct
    ///
    /// # Arguments
    ///
    /// * `slice` - The slice of inner fields
    ///
    /// # Returns
    ///
    /// The struct converted from the slice
    fn from_slice(slice: [Self::Item; S]) -> Self;
}

/// AsFloat trait for converting a struct to a tuple of float64
///
/// This trait is used to convert a struct to a tuple of float64 values,
/// which is useful for performing arithmetic operations on color values.
pub(crate) trait AsFloat {
    /// Return inner struct field as a tuple of float64
    fn as_f64(&self) -> (f64, f64, f64);
}
