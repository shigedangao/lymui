use crate::rgb::Rgb;
use crate::xyz::transfer::HdrCorrection;

// Constants

// This matrix come froms the following article
// @link <https://en.wikipedia.org/wiki/ICtCp>
const MATRIX_RGB: [[f64; 3]; 3] = [
    [1688., 2146., 262.],
    [683., 2951., 462.],
    [99., 309., 3688.],
];

// This matrix come froms the following article
// @link <https://en.wikipedia.org/wiki/ICtCp>
const MATRIX_ICTCP: [[f64; 3]; 3] = [
    [2048., 2048., 0.],
    [6610., -13_613., 7003.],
    [17_933., -17_390., -543.],
];

// The inverse matrix has been computed using this website
// @link <https://matrix.reshish.com/inverse-matrix/>
const INVERSE_MATRIX_ICTCP: [[f64; 3]; 3] = [
    [1.0, 0.008_609_037_037_932_8, 0.111_029_625_003_026],
    [1.0, -0.008_609_037_037_932_8, -0.111_029_625_003_026],
    [1.0, 0.560_031_335_710_679_1, -0.320_627_174_987_318_8],
];

// The inverse matrix has been computed using this website
// @link <https://matrix.reshish.com/inverse-matrix/>
const INVERSE_MATRIX_RGB: [[f64; 3]; 3] = [
    [
        3.436_606_694_333_079,
        -2.506_452_118_656_270_5,
        0.069_845_424_323_191_5,
    ],
    [
        -0.791_329_555_598_928_9,
        1.983_600_451_792_291_2,
        -0.192_270_896_193_362,
    ],
    [
        -0.025_949_899_690_592_7,
        -0.098_913_714_711_726_5,
        1.124_863_614_402_319_2,
    ],
];

#[derive(Clone, Copy, Debug)]
pub struct Ictcp {
    pub i: f64,
    pub ct: f64,
    pub cp: f64,
}

impl Ictcp {
    /// Converts a linear RGB value to an ICTCP value.
    ///
    /// # Arguments
    ///
    /// * `r` - The red component of the RGB value.
    /// * `g` - The green component of the RGB value.
    /// * `b` - The blue component of the RGB value.
    fn new(r: f64, g: f64, b: f64) -> Self {
        let l = (MATRIX_RGB[0][0] * r + MATRIX_RGB[0][1] * g + MATRIX_RGB[0][2] * b) / 4096.;
        let m = (MATRIX_RGB[1][0] * r + MATRIX_RGB[1][1] * g + MATRIX_RGB[1][2] * b) / 4096.;
        let s = (MATRIX_RGB[2][0] * r + MATRIX_RGB[2][1] * g + MATRIX_RGB[2][2] * b) / 4096.;

        let le = l.pq_inverse_eotf();
        let me = m.pq_inverse_eotf();
        let se = s.pq_inverse_eotf();

        let i =
            (MATRIX_ICTCP[0][0] * le + MATRIX_ICTCP[0][1] * me + MATRIX_ICTCP[0][2] * se) / 4096.;
        let ct =
            (MATRIX_ICTCP[1][0] * le + MATRIX_ICTCP[1][1] * me + MATRIX_ICTCP[1][2] * se) / 4096.;
        let cp =
            (MATRIX_ICTCP[2][0] * le + MATRIX_ICTCP[2][1] * me + MATRIX_ICTCP[2][2] * se) / 4096.;

        Ictcp { i, ct, cp }
    }

    fn into_rgb(self) -> Rgb {
        let lp = self.i * INVERSE_MATRIX_ICTCP[0][0]
            + self.ct * INVERSE_MATRIX_ICTCP[0][1]
            + self.cp * INVERSE_MATRIX_ICTCP[0][2];
        let mp = self.i * INVERSE_MATRIX_ICTCP[1][0]
            + self.ct * INVERSE_MATRIX_ICTCP[1][1]
            + self.cp * INVERSE_MATRIX_ICTCP[1][2];
        let sp = self.i * INVERSE_MATRIX_ICTCP[2][0]
            + self.ct * INVERSE_MATRIX_ICTCP[2][1]
            + self.cp * INVERSE_MATRIX_ICTCP[2][2];

        let l = lp.pq_eotf();
        let m = mp.pq_eotf();
        let s = sp.pq_eotf();

        let r = l * INVERSE_MATRIX_RGB[0][0]
            + m * INVERSE_MATRIX_RGB[0][1]
            + s * INVERSE_MATRIX_RGB[0][2];
        let g = l * INVERSE_MATRIX_RGB[1][0]
            + m * INVERSE_MATRIX_RGB[1][1]
            + s * INVERSE_MATRIX_RGB[1][2];
        let b = l * INVERSE_MATRIX_RGB[2][0]
            + m * INVERSE_MATRIX_RGB[2][1]
            + s * INVERSE_MATRIX_RGB[2][2];

        Rgb {
            r: (r * 255.).round() as u8,
            g: (g * 255.).round() as u8,
            b: (b * 255.).round() as u8,
        }
    }
}

impl From<Rgb> for Ictcp {
    fn from(value: Rgb) -> Self {
        let (r, g, b) = value.linear_rescaling();

        Ictcp::new(r, g, b)
    }
}

impl From<Ictcp> for Rgb {
    fn from(value: Ictcp) -> Self {
        value.into_rgb()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_convert_rgb_to_ictcp() {
        let rgb = Rgb { r: 255, g: 0, b: 0 };
        let ictcp = Ictcp::from(rgb);

        assert_eq!(ictcp.i, 0.09320141504128142);
        assert_eq!(ictcp.ct, -0.022974009638254002);
        assert_eq!(ictcp.cp, 0.14759767602400353);
    }

    #[test]
    fn expect_to_convert_ictcp_to_rgb() {
        let rgb = Rgb { r: 255, g: 0, b: 0 };
        let ictcp = Ictcp::from(rgb);
        let rgb2 = Rgb::from(ictcp);

        assert_eq!(rgb, rgb2);
    }
}
