#[derive(Debug)]
pub enum Error {
    Parse(String),
    Hex(String)
}

impl std::error::Error for Error {}

impl std::fmt::Display for Error {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Error::Parse(msg) => write!(f, "A parse error occurred {msg}"),
            Error::Hex(msg) => write!(f, "Error occurred while parsing an Hex {msg}")
        }
    }
}
