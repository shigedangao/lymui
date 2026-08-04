use lymui::{
    from_rgb_space_to_xyz_space,
    generator::{GeneratorOps, shade::Shade},
    ops::SliceOps,
    prelude::*,
    rgb::FromRgb,
    xyz::{Kind, rec2020::Rec2020},
};

fn rgb_to_hex() {
    let rgb = Rgb {
        r: 17,
        g: 10,
        b: 94,
    };

    let hex = Hex::from(rgb);
    assert_eq!(hex.0, "#110a5e");

    let rgb = Rgb::try_from(hex).unwrap();
    assert_eq!(rgb.r, 17);
    assert_eq!(rgb.g, 10);
    assert_eq!(rgb.b, 94);
}

fn rgb_to_xyz() {
    let rgb = Rgb {
        r: 255,
        g: 255,
        b: 255,
    };

    let xyz = Xyz::from_rgb(rgb, Kind::D65);
    assert_eq!(xyz.x, 0.95047);
    assert_eq!(xyz.y, 1.0000001);
    assert_eq!(xyz.z, 1.08883);
}

fn main() {
    let rgb = Rgb {
        r: 170,
        g: 125,
        b: 194,
    };
    // Using the utility method to easily convert an RGB type to any type that implement the XYZ
    let rec2020: Rec2020 = from_rgb_space_to_xyz_space(rgb.clone(), None);
    assert_eq!(rec2020.r, (0.5800179952190697 * 100_000.) / 100_000.);
    assert_eq!(rec2020.g, (0.4596835755617258 * 100_000.) / 100_000.);
    assert_eq!(rec2020.b, (0.7109727343600348 * 100_000.) / 100_000.);

    rgb_to_hex();
    rgb_to_xyz();

    // You can also create a color using a slice of rgb
    let hsl = Hsl::from_slice(&rgb.as_slice().map(|v| v as f64));
    assert_eq!(hsl.h, 170.);
    assert_eq!(hsl.s, 125.);
    assert_eq!(hsl.l, 194.);

    // Create a shade of rgb
    let shade = Shade::compute(rgb, 0.1);
    assert!(shade.is_ok());

    let tone = Tone::from(Rgb {
        r: 255,
        g: 255,
        b: 255,
    });
    assert_eq!(tone.0, 100.);
}
