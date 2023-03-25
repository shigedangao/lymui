use crate::rgb::Rgb;

#[derive(Debug, Clone, Copy)]
pub struct Yuv {
    pub y: f64,
    pub u: f64,
    pub v: f64
}

impl From<&Rgb> for Yuv {
    fn from(rgb: &Rgb) -> Self {
        let (mut r, mut g, mut b) = rgb.as_f64();
        r = r / 255.0;
        g = g / 255.0;
        b = b / 255.0;

        let y = 0.299 * r + 0.587 * g + 0.114 * b;

        Yuv {
            y,
            u: 0.492 * (b - y),
            v: 0.877 * (r - y)
        }
    }
}

impl From<&Yuv> for Rgb {
    fn from(yuv: &Yuv) -> Self {
        let r = yuv.y + 1.13983 * yuv.v;
        let g = yuv.y - 0.39465 * yuv.u - 0.58060 * yuv.v;
        let b = yuv.y + 2.03211 * yuv.u;

        Rgb {
            r: r as u8,
            g: g as u8,
            b: b as u8
        }
    }
}
