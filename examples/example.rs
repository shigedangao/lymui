use lymui::{
    from_rgb_compatible_to_xyz_subtype,
    hex::Hex,
    rgb::{Rgb, FromRgb},
    xyz::Xyz,
    xyz::{rec2020::Rec2020, Kind}
};

fn rgb_to_hex() {
    let rgb = Rgb {
        r: 17,
        g: 10,
        b: 94
    };

    let hex = Hex::from(rgb);
    assert_eq!(hex, "#110a5e");

    let rgb = Rgb::try_from(hex).unwrap();
    assert_eq!(rgb.r, 17);
    assert_eq!(rgb.g, 10);
    assert_eq!(rgb.b, 94);
}

fn rgb_to_xyz() {
    let rgb = Rgb {
        r: 255,
        g: 255,
        b: 255
    };

    let xyz = Xyz::from_rgb(rgb, Kind::D65);
    assert_eq!(xyz.x, 0.95047);
    assert_eq!(xyz.y, 1.0000001);
    assert_eq!(xyz.z, 1.08883);
}

fn main() {
    let c = Rgb {
        r: 170,
        g: 125,
        b: 194,
    };
    // Using the utility method to easily convert an RGB type to any type that implement the XYZ
    let rec2020: Rec2020 = from_rgb_compatible_to_xyz_subtype(c.clone(), None);
    dbg!(rec2020);

    rgb_to_hex();
    rgb_to_xyz();
}
