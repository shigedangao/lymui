#[derive(Debug)]
pub enum Error {
    Parse(String),
    Hex(String),
    Generator,
    Ansi(String),
}

impl std::error::Error for Error {}

impl std::fmt::Display for Error {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Error::Parse(msg) => write!(f, "Uneble to parse a color due to: {msg}"),
            Error::Hex(msg) => write!(
                f,
                "Error occurred while parsing an hexacolor color value due to: {msg}"
            ),
            Error::Generator => {
                write!(f, "Factor should be a number between a float between 0 & 1")
            }
            Error::Ansi(msg) => write!(f, "Unable to process ansi color due to: {msg}"),
        }
    }
}
