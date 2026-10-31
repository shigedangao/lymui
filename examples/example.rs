use lymui::{ops::SliceOps, prelude::*, rgb::FromRgb, xyz::Kind};

fn example_one_rgb_to_hex(rgb: Rgb) {
    let hex = Hex::from(rgb);
    assert_eq!(hex.0, "#060b60");

    let rgb = Rgb::from(hex);
    assert_eq!(rgb.r, 6);
    assert_eq!(rgb.g, 11);
    assert_eq!(rgb.b, 96);
}

fn example_two_rgb_to_xyz(rgb: Rgb) {
    let xyz = Xyz::from_rgb(rgb, Kind::D65);

    assert_eq!(xyz.x, 0.02305368595226636);
    assert_eq!(xyz.y, 0.011222952142319187);
    assert_eq!(xyz.z, 0.11159179560350473);
}

fn example_three_rgb_to_hsl_slice(rgb: Rgb) {
    let rgb_slice = rgb.as_slice();
    let hsl = lymui::convert_color_from_slice::<_, Rgb, Rgb, Hsl, 3>(&rgb_slice);

    assert_eq!(hsl.h, 237.);
    assert_eq!(hsl.s, 88.23529411764704);
    assert_eq!(hsl.l, 20.);
}

fn example_four_rgb_to_okhsl(rgb: Rgb) {
    let okhsl = lymui::convert_color_from_any_colorspace::<_, OkHSL, Rgb, Srgb>(rgb);

    assert_eq!(okhsl.h, 0.7397105312164948);
    assert_eq!(okhsl.s, 0.987694725979644);
    assert_eq!(okhsl.l, 0.035486157859664746);
}

fn main() {
    let rgb = Rgb { r: 6, g: 11, b: 96 };

    example_one_rgb_to_hex(rgb);
    example_two_rgb_to_xyz(rgb);
    example_three_rgb_to_hsl_slice(rgb);
    example_four_rgb_to_okhsl(rgb);
}
