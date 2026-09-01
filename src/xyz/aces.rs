use super::Xyz;
use super::matrices::aces2065::*;
use crate::ops::SliceOps;

/// Aces color space implements the conversion between the Xyz color space and the Aces color space.
/// @link <https://en.wikipedia.org/wiki/Academy_Color_Encoding_System>
#[derive(Debug, Clone, Copy)]
pub struct Aces {
    pub r: f64,
    pub g: f64,
    pub b: f64,
}

impl Aces {
    /// Creates a new Aces color space from an Xyz color space.
    ///
    /// # Arguments
    ///
    /// * `xyz` - The Xyz color space to convert from.
    fn new(xyz: Xyz) -> Self {
        let r = xyz.x * XR[0] + xyz.y * XR[1] + xyz.z * XR[2];
        let g = xyz.x * XG[0] + xyz.y * XG[1] + xyz.z * XG[2];
        let b = xyz.x * XB[0] + xyz.y * XB[1] + xyz.z * XB[2];

        Self { r, g, b }
    }
}

impl SliceOps<3> for Aces {
    type Item = f64;

    fn as_slice(&self) -> [Self::Item; 3] {
        [self.r, self.g, self.b]
    }

    fn to_vec(&self) -> Vec<Self::Item> {
        vec![self.r, self.g, self.b]
    }

    fn from_slice(slice: &[Self::Item; 3]) -> Self {
        Self {
            r: slice[0],
            g: slice[1],
            b: slice[2],
        }
    }
}

impl From<Xyz> for Aces {
    fn from(xyz: Xyz) -> Self {
        Aces::new(xyz)
    }
}

impl From<Aces> for Xyz {
    fn from(aces: Aces) -> Self {
        let x = aces.r * XX[0] + aces.g * XX[1] + aces.b * XX[2];
        let y = aces.r * XY[0] + aces.g * XY[1] + aces.b * XY[2];
        let z = aces.r * XZ[0] + aces.g * XZ[1] + aces.b * XZ[2];

        Self { x, y, z }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util::roundup;

    #[test]
    fn expect_aces_from_xyz_and_back_xyz() {
        let xyz = Xyz {
            x: 0.034_889_495_690_701_42,
            y: 0.017_213_474_858_538_254,
            z: 0.109_726_859_528_867_65,
        };

        let aces = Aces::from(xyz);
        let xyz2 = Xyz::from(aces);

        assert_eq!(roundup(xyz2.x, 100_000_000_000.0), 0.034_889_495_69);
        assert_eq!(roundup(xyz2.y, 100_000_000_000.0), 0.017_213_474_86);
        assert_eq!(roundup(xyz2.z, 100_000_000_000.0), 0.109_726_859_53);
    }
}
