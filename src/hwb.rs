use crate::rgb::Rgb;
use crate::hsv::Hsv;

#[derive(Debug)]
pub struct Hwb {
    h: f64,
    w: f64,
    b: f64
}

impl From<Rgb> for Hwb {
    fn from(rgb: Rgb) -> Self {
        let hsv = Hsv::from(rgb);

        let s = hsv.s / 100.0;
        let v = hsv.v / 100.0;

        Hwb {
            h: hsv.h,
            w: ((1.0 - s) * v) * 100.0,
            b: (1.0 - v) * 100.0
        }
    }
}

impl From<Hwb> for Rgb {
    fn from(hwb: Hwb) -> Self {
        let w = hwb.w / 100.0;
        let b = hwb.b / 100.0;

        let hsv = Hsv {
            h: hwb.h,
            s: (1.0 - (w / (1.0 - b))) * 100.0,
            v: (1.0 - b) * 100.0
        };

        Rgb::from(hsv)
    }
}