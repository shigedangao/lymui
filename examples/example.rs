use lymui::{from_rgb_compatible_to_xyz_subtype, hex::Hex, rgb::Rgb, xyz::rec2020::Rec2020};

fn main() {
    let c = Rgb {
        r: 170,
        g: 125,
        b: 194,
    };
    // Using the utility method to easily convert an RGB type to any type that implement the XYZ
    let rec2020: Rec2020 = from_rgb_compatible_to_xyz_subtype(c.clone(), None);
    dbg!(rec2020);

    // Convert an RGB to Hex
    let hex = Hex::from(c);
    dbg!(hex);
}
