use crate::rgb::Rgb;

// Constant use to compute back the RGB from an Ycbcr value
const Y: f64 = 1.164;

#[derive(Debug, Clone, Copy)]
pub struct Ycbcr {
    pub y: f64,
    pub cb: f64,
    pub cr: f64
}

impl Ycbcr {
    fn calculate_indices(rgb: &Rgb, multipliers: (f64, f64, f64)) -> (f64, f64, f64) {
        let (r, g, b) = rgb.as_f64();
        
        (
            r * multipliers.0,
            g * multipliers.1,
            b * multipliers.2
        )
    }
}

impl From<Rgb> for Ycbcr {
    fn from(rgb: Rgb) -> Self {
        let (yl, yy, ym) = Ycbcr::calculate_indices(&rgb, (0.257, 0.504, 0.098));
        let (ycl, ycy, ycm) = Ycbcr::calculate_indices(&rgb, (0.439, 0.368, 0.071));
        let (yrl, yry, yrm) = Ycbcr::calculate_indices(&rgb, (0.148, 0.291, 0.439));

        let y = 16.0 + yl + yy + ym;
        let cb = 128.0 + (- ycl - ycy + ycm);
        let cr = 128.0 + (yrl + yry + yrm);

        Ycbcr {
            y,
            cb,
            cr
        }
    }
}

impl From<Ycbcr> for Rgb {
    fn from(cb: Ycbcr) -> Self {
        let yy = Y * (cb.y - 16.0); 

        let r = Y * yy + 1.596 * (cb.cr - 128.0);
        let g = Y * yy - 0.813 * (cb.cr - 128.0) - 0.391 * (cb.cb - 128.0);
        let b = Y * yy + 2.018 * (cb.cb - 128.0);

        Rgb {
            r: r as u8,
            g: g as u8,
            b: b as u8
        }
    }
}
