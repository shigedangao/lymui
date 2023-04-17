use crate::util::{AsVec, FromVec};

use super::Xyz;

// Constant
const CHROMA_X: f64 = 0.31271;
const CHROMA_Y: f64 = 0.32902;

#[derive(Debug, Clone, Copy)]
pub struct Xyy {
    pub x: f64,
    pub y: f64,
    pub _y: f64,
}

enum Target {
    X(f64),
    Y(f64),
}

impl Xyy {
    /// Compute Xyy based on the xyz fields and the color passed
    ///
    /// # Arguments
    ///
    /// * `xyz` - &Xyz
    /// * `v` - f64
    fn compute_xyy(xyz: &Xyz, v: f64) -> Option<f64> {
        if !xyz.is_null() {
            return Some(v / (xyz.x + xyz.y + xyz.z));
        }

        None
    }

    /// Get the X & Y field from XYZ sruct by computing them or using the default chroma value
    ///
    /// # Arguments
    ///
    /// * `xyz` - &Xyz
    /// * `target` - Target
    fn get_fields_from_xyz(xyz: &Xyz, target: Target) -> f64 {
        match target {
            Target::X(v) => Xyy::compute_xyy(xyz, v).unwrap_or(CHROMA_X),
            Target::Y(v) => Xyy::compute_xyy(xyz, v).unwrap_or(CHROMA_Y),
        }
    }
}

impl From<Xyz> for Xyy {
    fn from(xyz: Xyz) -> Self {
        let x = Xyy::get_fields_from_xyz(&xyz, Target::X(xyz.x));
        let y = Xyy::get_fields_from_xyz(&xyz, Target::Y(xyz.y));

        Xyy { x, y, _y: xyz.y }
    }
}

impl From<Xyy> for Xyz {
    fn from(xyy: Xyy) -> Self {
        if xyy.y == 0.0 {
            return Xyz::default();
        }

        let x = (xyy.x * xyy._y) / xyy.y;
        let z = ((1.0 - xyy.x - xyy.y) * xyy._y) / xyy.y;

        Xyz { x, y: xyy.y, z }
    }
}

impl AsVec for Xyy {
    type Item = f64;

    fn as_vec(&self) -> Vec<Self::Item> {
        vec![self.x, self.y, self._y]
    }
}

impl FromVec<f64> for Xyy {
    fn from_vec(vec: Vec<f64>) -> Self {
        Xyy {
            x: vec.first().copied().unwrap_or_default(),
            y: vec.get(1).copied().unwrap_or_default(),
            _y: vec.last().copied().unwrap_or_default(),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_compute_xyy() {
        let xyz = Xyz {
            x: 0.9,
            y: 0.8,
            z: 0.7,
        };

        let xyy = Xyy::from(xyz);

        assert_eq!(util::roundup(xyy.x, 1000.0), 0.375);
        assert_eq!(util::roundup(xyy.y, 1000.0), 0.333);
        assert_eq!(xyy._y, 0.8);
    }

    #[test]
    fn expect_to_create_dark_xyz() {
        let xyz = Xyz {
            x: 0.0,
            y: 0.0,
            z: 0.0,
        };

        let xyy = Xyy::from(xyz);

        assert_eq!(util::roundup(xyy.x, 1000.0), 0.313);
        assert_eq!(util::roundup(xyy.y, 1000.0), 0.329);
        assert_eq!(util::roundup(xyy._y, 1000.0), 0.0);
    }

    #[test]
    fn expect_to_create_bright_xyy() {
        let xyz = Xyz {
            x: 0.95047,
            y: 1.0,
            z: 1.08883,
        };

        let xyy = Xyy::from(xyz);

        assert_eq!(util::roundup(xyy.x, 1000.0), 0.313);
        assert_eq!(util::roundup(xyy.y, 1000.0), 0.329);
        assert_eq!(util::roundup(xyy._y, 1000.0), 1.0);
    }
}
