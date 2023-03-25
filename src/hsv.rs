use crate::rgb::Rgb;
use crate::hue::Hue;

#[derive(Debug)]
pub struct Hsv {
    pub h: f64,
    pub s: f64,
    pub v: f64
}

impl From<Rgb> for Hsv {
    fn from(rgb: Rgb) -> Self {
        let (min, max) = rgb.get_min_max();
        let hue = Hue::from(rgb);

        let delta = max - min;
        let s;

        if max > 0.0 {
            s = (delta / max) * 100.0;
        } else {
            s = 0.0;
        }

        Hsv {
            h: hue,
            s,
            v: max * 100.0
        }
    }
}

impl From<Hsv> for Rgb {
    fn from(hsv: Hsv) -> Self {
        if hsv.s == 0.0 {
            return Rgb {
                r: hsv.v as u8,
                g: hsv.v as u8,
                b: hsv.v as u8
            };
        }

        let hue = hsv.h / 60.0;
        let i = hue as i64;
        let factor = hue - i as f64;

        let v = hsv.v / 100.0;
        let s = hsv.s / 100.0;

        let p = v * (1.0 - s);
        let q = v * (1.0 - (s * factor));
        let t = v * (1.0 - (1.0 - factor));

        let up = (p * 255.0) as u8;
        let uq = (q * 255.0) as u8;
        let ut = (t * 255.0) as u8;
        let uv = (v * 255.0) as u8;

        match i {
            0 => Rgb::new(uv, ut, up),
            1 => Rgb::new(uq, uv, up),
            2 => Rgb::new(up, uv, ut),
            3 => Rgb::new(up, uq, uv),
            4 => Rgb::new(ut, up, uv),
            _ => Rgb::default()
        }
    }
}